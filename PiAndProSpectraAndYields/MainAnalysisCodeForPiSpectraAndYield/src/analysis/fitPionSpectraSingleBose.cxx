//Fit the Spectra

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>
#include <TFile.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TSystem.h>
#include <TVirtualFitter.h>
#include <TLatex.h>

#include "globalDefinitions.h"
#include "utilityFunctions.h"
#include "StRefMultExtendedCorr.h"
#include "UserCuts.h"
#include "ParticleInfo.h"
#include "SpectraFitFunctions.h"

using namespace std;

Bool_t draw = false;

//________________________________________________________________________________________________________
void RemovePointsWithLargeErrors(TGraphErrors *spectrum, Double_t maxRelativeError=.1){

    //Loop Over the Points of the spectrum. Remove any point which is found
    //to have a relativeError larger than maxRelativeError
    for (int iPoint=spectrum->GetN()-1; iPoint>=0; iPoint--){
        if (spectrum->GetEY()[iPoint] / spectrum->GetY()[iPoint] > maxRelativeError)
              spectrum->RemovePoint(iPoint);
    }   
}

//________________________________________________________________________________________________________
void fitPionSpectraSingleBose(TString spectraFileName, TString resultFileName, Int_t pid, Int_t charge, Double_t midY){

  ParticleInfo *particleInfo = new ParticleInfo();
  const int nCentBins = 1;
  Double_t mTm0min, mTm0max, dNdy, dNdyErr, dNdy1, dNdy2, dNdy1Err, dNdy2Err, dNdySystErr;
  Int_t nPoints;
  TGraphErrors *tpcCorrectedSpectrum, *tpcRawSpectrum, *tpcSysErrSpectrum;
  TF1 *fitBoseEinstein, *fitBEextra, *fitBoseEinsteinSystOnly, *tSlopeFit, *tSlopeFitSystOnly;
	vector <TGraphErrors *> tSlopeGraph(nCentBins, (TGraphErrors *)NULL);
	vector <TGraphErrors *> tSlopeGraphSystOnly(nCentBins, (TGraphErrors *)NULL);
	vector <TGraphErrors *> dNdyGraph(nCentBins, (TGraphErrors *)NULL);

  //Create the OutputFile
  TFile *resultsFile = new TFile(resultFileName,"UPDATE");
  resultsFile->cd();
  resultsFile->mkdir(Form("RawSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
  resultsFile->mkdir(Form("CorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
  resultsFile->mkdir(Form("RapidityDensity_%s",particleInfo->GetParticleName(pid,charge).Data()));
  resultsFile->mkdir(Form("TSlopeParameter_%s",particleInfo->GetParticleName(pid,charge).Data()));

  //Create a canvas if drawing
  TCanvas *canvas = NULL;
  TCanvas *dNdyCanvas = NULL;
  if (draw){
    canvas = new TCanvas("canvas","canvas",20,20,800,600);
		dNdyCanvas = new TCanvas("dNdyCanvas","dNdyCanvas",20,750,1200,600);
    gPad->DrawFrame(-2,0,2,150);
  }

  //Open the SpectraFile
  TFile *spectraFile = new TFile(spectraFileName,"READ");

  //Loop Over the Centrality Bins and Rapidity Bins and apply the Corrections
  for (int iCentBin=0; iCentBin<nCentBins; iCentBin++){
   
	  //Create the temperature/inverse slope parameter graph and fit
	  tSlopeGraph.at(iCentBin) = new TGraphErrors();
	  tSlopeGraphSystOnly.at(iCentBin) = new TGraphErrors();
	  tSlopeGraph.at(iCentBin)->GetXaxis()->SetTitle("y_{lab}");
		tSlopeGraph.at(iCentBin)->SetMarkerColor(particleInfo->GetParticleColor(pid));
		tSlopeGraph.at(iCentBin)->SetMarkerStyle(particleInfo->GetParticleMarker(pid, charge));
		tSlopeGraph.at(iCentBin)->SetName(Form("Slope1Parameter_%s_Cent%02d",
              particleInfo->GetParticleName(pid,charge).Data(),
              iCentBin));

		tSlopeFit = new TF1("tSlopeFit1","gaus(0)",-1.8,0.2);
		tSlopeFit->SetNpx(10000);
		tSlopeFit->SetName(Form("SlopeParameter_%s_Cent%02d",
            particleInfo->GetParticleName(pid,charge).Data(),
            iCentBin));
		tSlopeFit->SetParameter(0,0.158);
		tSlopeFit->FixParameter(1,midY); 
		tSlopeFit->SetParameter(2,1.7); 
		tSlopeFit->SetParNames("Amp", "#mu", "#sigma");

		tSlopeFitSystOnly = new TF1("tSlopeFitSystOnly","gaus(0)",-1.8,0.2);
		tSlopeFitSystOnly->SetNpx(10000);
		tSlopeFitSystOnly->SetParameter(0,0.158);
		tSlopeFitSystOnly->FixParameter(1,midY); 
		tSlopeFitSystOnly->SetParameter(2,1.691); 

		//Create the dN/dy Graphs
		dNdyGraph.at(iCentBin) = new TGraphErrors();
		dNdyGraph.at(iCentBin)->SetMarkerStyle(particleInfo->GetParticleMarker(pid,charge));
		dNdyGraph.at(iCentBin)->SetMarkerColor(particleInfo->GetParticleColor(pid));
    dNdyGraph.at(iCentBin)->SetName(Form("RapidityDensityTotal_%s_Cent%02d",
           particleInfo->GetParticleName(pid,charge).Data(),
           iCentBin));

		for(Int_t iRound = 0;iRound<2;iRound++){

			for (int yIndex=GetMinRapidityIndexOfInterest(pid); yIndex<=GetMaxRapidityIndexOfInterest(pid); yIndex++){

				cout <<Form("INFO: - Correcting Spectrum: %s CentIndex: %d yIndex %d",
				particleInfo->GetParticleName(pid,charge).Data(),iCentBin,yIndex) <<endl;

				//Compute Rapidity
				Double_t rapidity = GetRapidityRangeCenter(yIndex);

				//Get Spectra
				spectraFile->cd();
				tpcCorrectedSpectrum = (TGraphErrors *)gDirectory->Get(Form("CorrectedSpectra_%s/correctedSpectra_%s_Cent%02d_yIndex%02d",
									particleInfo->GetParticleName(pid,charge).Data(),
									particleInfo->GetParticleName(pid,charge).Data(),iCentBin,yIndex));
				cout<<"tpcCorrectedSpectrum "<<tpcCorrectedSpectrum<<endl;
				if (!tpcCorrectedSpectrum) continue;
				tpcRawSpectrum = (TGraphErrors *)gDirectory->Get(Form("RawSpectra_%s/rawSpectra_%s_Cent%02d_yIndex%02d",
									particleInfo->GetParticleName(pid,charge).Data(),
									particleInfo->GetParticleName(pid,charge).Data(),iCentBin,yIndex));

        RemovePointsWithLargeErrors(tpcCorrectedSpectrum,0.5);
				nPoints = tpcCorrectedSpectrum->GetN();
				if (nPoints <= 5) continue;
        //mTm0min = 0.08;
				if (tpcCorrectedSpectrum->GetX()[nPoints-1] > 1.4) mTm0max = 1.4;
        else mTm0max = tpcCorrectedSpectrum->GetX()[nPoints-1];
        TGraphChop(tpcCorrectedSpectrum,mTm0min,true);
        TGraphChop(tpcCorrectedSpectrum,mTm0max,false);
				Double_t minmtm0 = tpcCorrectedSpectrum->GetX()[0];

				//Get the fit function
				if (yIndex < 17) fitBoseEinstein = new TF1("",BoseEinsteinFitFunc,minmtm0,0.5,3);
				else if (yIndex == 17) fitBoseEinstein = new TF1("",BoseEinsteinFitFunc,minmtm0,0.5,3);//0.95
				else if (yIndex == 18) fitBoseEinstein = new TF1("",BoseEinsteinFitFunc,minmtm0,0.5,3);//0.82
				fitBEextra = new TF1("",BoseEinsteinFitFunc,0,mTm0max,3);
				//fitBEForIntegral = new TF1("",BoseEinsteinFitFunc,0,5,3);
				fitBoseEinsteinSystOnly = new TF1("",BoseEinsteinFitFunc,0.08,0.5,3);
				fitBoseEinstein->SetName(Form("spectrumFitBoseEinstein_%s_Cent%02d_yIndex%02d",
						particleInfo->GetParticleName(pid,charge).Data(),
						iCentBin,yIndex));
				fitBEextra->SetName(Form("spectrumFitBEextra_%s_Cent%02d_yIndex%02d",
						particleInfo->GetParticleName(pid,charge).Data(),
						iCentBin,yIndex));
				//fitBEForIntegral->SetName(Form("spectrumFitBEForIntegral_%s_Cent%02d_yIndex%02d",
			//			particleInfo->GetParticleName(pid,charge).Data(),
			//			iCentBin,yIndex));
			  			
				fitBoseEinstein->SetParameter(0,65);//65 40
				fitBoseEinstein->SetParameter(1,0.158);//0.16 0.05
				fitBoseEinstein->FixParameter(2,particleInfo->GetParticleMass(pid));
				//fitBoseEinstein->SetParLimits(0,1.,75.);
				//fitBoseEinstein->SetParLimits(1,0.040,0.100);
				fitBoseEinstein->SetParNames("dN/dy_{1}","T_{InverseSlope,1}","#pi mass");
				fitBEextra->SetParNames("dN/dy_{1}","T_{InverseSlope,1}","#pi mass");
				fitBEextra->SetLineStyle(7);

				if (iRound > 0){
						fitBoseEinstein->FixParameter(1,tSlopeFit->Eval(rapidity));
						fitBoseEinsteinSystOnly->FixParameter(1,tSlopeFitSystOnly->Eval(rapidity));
				}

				//Perform the fit
				tpcCorrectedSpectrum->Fit(fitBoseEinstein,"EXO","",minmtm0,0.5);

				fitBEextra->FixParameter(0,fitBoseEinstein->GetParameter(0));
				fitBEextra->FixParameter(1,fitBoseEinstein->GetParameter(1));
				fitBEextra->FixParameter(2,fitBoseEinstein->GetParameter(2));
				tpcCorrectedSpectrum->Fit(fitBEextra,"REXO+");

				//if (yIndex==17) tpcCorrectedSpectrum->Fit(fitBEextra,"REXO+");
				//if (yIndex==18) tpcCorrectedSpectrum->Fit(fitBEextra,"REXO+");
				//fitBEForIntegral->FixParameter(0,fitBoseEinstein->GetParameter(0));
				//fitBEForIntegral->FixParameter(1,fitBoseEinstein->GetParameter(1));
				//fitBEForIntegral->FixParameter(2,fitBoseEinstein->GetParameter(2));
				//tpcCorrectedSpectrum->Fit(fitBEForIntegral,"REXO+");

				if (iRound==0){
				 
				  cout<<"Rapidity: "<<rapidity<<" dN/dy: "<<fitBoseEinstein->GetParameter(0)<<endl;
	       	
					tSlopeGraph.at(iCentBin)->SetPoint(tSlopeGraph.at(iCentBin)->GetN(),
										rapidity, fitBoseEinstein->GetParameter(1));								
					tSlopeGraph.at(iCentBin)->SetPointError(tSlopeGraph.at(iCentBin)->GetN()-1,
										rapidityBinWidth/2.0, fitBoseEinstein->GetParError(1));								
					tSlopeGraphSystOnly.at(iCentBin)->SetPoint(tSlopeGraphSystOnly.at(iCentBin)->GetN(),
										rapidity, fitBoseEinsteinSystOnly->GetParameter(1));								
					tSlopeGraphSystOnly.at(iCentBin)->SetPointError(tSlopeGraphSystOnly.at(iCentBin)->GetN()-1,
										rapidityBinWidth/2.0, fitBoseEinsteinSystOnly->GetParError(1));								

				}

        if (iRound==1){

					dNdy = fitBoseEinstein->GetParameter(0);
					dNdyErr = fitBoseEinstein->GetParError(0);
					dNdyGraph.at(iCentBin)->SetPoint(dNdyGraph.at(iCentBin)->GetN(),rapidity-midY,dNdy);
					dNdyGraph.at(iCentBin)->SetPointError(dNdyGraph.at(iCentBin)->GetN()-1,
									rapidityBinWidth/2.0,dNdyErr);
					dNdySystErr = fitBoseEinsteinSystOnly->GetParError(0);

        }

				if (draw){

					canvas->cd();
					canvas->DrawFrame(0,0.01*TMath::MinElement(tpcCorrectedSpectrum->GetN(),tpcCorrectedSpectrum->GetY()),
								2.0,20*TMath::MaxElement(tpcCorrectedSpectrum->GetN(),tpcCorrectedSpectrum->GetY()));
					canvas->SetLogy();
					tpcCorrectedSpectrum->Draw("APZ");	
					tpcCorrectedSpectrum->GetXaxis()->SetTitle("m_{T}-m_{0} (GeV)");
					
					fitBoseEinstein->SetLineColor(2);
					fitBoseEinstein->SetLineWidth(2);
					fitBoseEinstein->Draw("SAME");
					//fitBEextra->SetLineStyle(7);
					//fitBEextra->SetLineColor(2);
					//fitBEextra->SetLineWidth(2);
					//fitBEextra->Draw("SAME");

				}

				tpcCorrectedSpectrum->GetYaxis()->SetTitle("#frac{1}{N_{Evt}}#times#frac{1}{2#pim_{T}}#times#frac{d^{2}N}{dm_{T}dy} (GeV/c^{2})^{-2}");
				tpcCorrectedSpectrum->GetXaxis()->SetTitle(Form("m_{T}-m_{%s} (GeV/c^{2})",
				             particleInfo->GetParticleSymbol(pid).Data()));
				tpcCorrectedSpectrum->GetYaxis()->SetTitleFont(63);
				tpcCorrectedSpectrum->GetYaxis()->SetTitleSize(25);
        tpcCorrectedSpectrum->GetXaxis()->SetTitleFont(63);
				tpcCorrectedSpectrum->GetXaxis()->SetTitleSize(25);
				tpcCorrectedSpectrum->GetXaxis()->SetTitleOffset(1.3);
				TF1 *extrap = tpcCorrectedSpectrum->GetFunction(Form("spectrumFitBoseEinstein_%s_Cent%02d_yIndex%02d",
				            particleInfo->GetParticleName(pid,charge).Data(),
										iCentBin,yIndex));

				cout<<"Saving Spectra"<<endl;
				//Save Spectra
				if (iRound==1){
					resultsFile->cd();
					resultsFile->cd(Form("CorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
					if (tpcCorrectedSpectrum) tpcCorrectedSpectrum->Write();
					resultsFile->cd();
					resultsFile->cd(Form("RawSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
				  if (tpcCorrectedSpectrum)	tpcRawSpectrum->Write();
					resultsFile->cd();
				}

				cout<<"SAVED"<<endl;

			}//End of rapidity loop

		  if (iRound==0) {
				tSlopeGraph.at(iCentBin)->Fit(tSlopeFit,"EX0","",-1.8,-0.18);//-0.48
				tSlopeGraphSystOnly.at(iCentBin)->Fit(tSlopeFitSystOnly,"REX0");
			}

		}//End of loop over fitting rounds

		if (draw){
			dNdyCanvas->cd();
			dNdyGraph.at(iCentBin)->Draw("APZ");
		}

    //Save Plots
		tSlopeGraph.at(iCentBin)->GetXaxis()->SetTitle("y_{lab}");
		tSlopeGraph.at(iCentBin)->GetYaxis()->SetTitle("T/inverseSlope MeV");

		resultsFile->cd(Form("TSlopeParameter_%s",particleInfo->GetParticleName(pid,charge).Data()));
		if (tSlopeGraph.at(iCentBin)->GetN() > 0){
			tSlopeGraph.at(iCentBin)->Write();
			tSlopeGraphSystOnly.at(iCentBin)->Write();
		}

		resultsFile->cd(Form("RapidityDensity_%s",particleInfo->GetParticleName(pid,charge).Data()));
    if (dNdyGraph.at(iCentBin)->GetN() > 0) dNdyGraph.at(iCentBin)->Write();

	}//End of centrality loop

}//End of function
