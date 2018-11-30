#include <iostream>
#include <vector>
#include <utility>

#include <TMath.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TSystem.h>
#include <TRandom3.h>

#include "globalDefinitions.h"
#include "utilityFunctions.h"
#include "StRefMultExtendedCorr.h"
#include "UserCuts.h"
#include "ParticleInfo.h"

using namespace std;

Bool_t draw = false;
Double_t minTPCEfficiency=0.3;
Int_t pidIndex;
Int_t pidCharge;
Double_t pidMass;

//___FUNCTIONS THAT APPLY THE CORRECTIONS (DEFINED BELOW)________________
TGraphErrors *ApplyBackgroundCorrection(TGraphErrors *spectrum, TF1 *efficiencyCurve, Bool_t doSystematics=false); //Correct for tracking eff
TGraphErrors *ApplyEfficiencyCorrection(TGraphErrors *spectrum, TF1 *efficiencyCurve, Bool_t doSystematics=false); //Correct for tracking eff

//___________________________________________________________
void TGraphChop(TGraphErrors *graph, Double_t threshold, Bool_t below){

  //Remove points from graph that are below (or above) the
  //the x value of threshold

  for (Int_t iPoint=graph->GetN()-1; iPoint>=0; iPoint--){

    //If the user wants to remove points above the threshold
    if (!below && graph->GetX()[iPoint] > threshold){
      graph->RemovePoint(iPoint);
    }   

    else if (below && graph->GetX()[iPoint] < threshold) {
      graph->RemovePoint(iPoint);
    }   

  }

}

//___________________________________________________________________________
void RemovePointsWithLargeErrors(TGraphErrors *spectrum, Double_t maxRelativeError=.5){

  //Loop Over the Points of the spectrum. Remove any point which is found
	//to have a relativeError larger than maxRelativeError
	for (int iPoint=spectrum->GetN()-1; iPoint>=0; iPoint--){
	
	    if (spectrum->GetEY()[iPoint] / spectrum->GetY()[iPoint] > maxRelativeError)
	          spectrum->RemovePoint(iPoint);
	}
}

//____MAIN_______________________________________________________________
void correctSpectra(TString spectraFileName, TString correctionFileName, Int_t pid, Int_t charge){

  ParticleInfo *particleInfo = new ParticleInfo();
  const int nCentBins = 1;//GetNCentralityBins();
  pidIndex = pid;
  pidCharge = charge;
  pidMass = particleInfo->GetParticleMass(pid);
  
  //Open the SpectraFile
  TFile *spectraFile = new TFile(spectraFileName,"UPDATE");
  spectraFile->cd();
  spectraFile->mkdir(Form("CorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
  spectraFile->mkdir(Form("SysErrCorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));

  //Open the Correction File
  TFile *corrFile = new TFile(correctionFileName,"READ");

  //Create a Canvas if drawing
  TCanvas *canvas = NULL;
  if (draw){
    canvas = new TCanvas("canvas","canvas",20,20,800,600);
  }

  //Local Pointers
  TF1 *efficiencyCurve, *hadronicBGCurve;
  TGraphErrors *tpcRawSpectrum, *tpcSysErrSpectrum;
  TGraphErrors *tpcBackgroundCorrectedSpectrum;
  TGraphErrors *tpcEfficiencyCorrectedSpectrum;
  TGraphErrors *tpcFullyCorrectedSpectrum; 

  //Loop Over the Centrality Bins and Rapidity Bins and apply the Corrections
  for (int iCentBin=0; iCentBin<nCentBins; iCentBin++){
    for (int yIndex=GetMinRapidityIndexOfInterest(pid); yIndex<=GetMaxRapidityIndexOfInterest(pid); yIndex++){

      cout <<Form("INFO: - Correcting Spectrum: %s CentIndex: %d yIndex %d",
		  particleInfo->GetParticleName(pid,charge).Data(),iCentBin,yIndex) <<endl;

      //Get the Correction Curves
      corrFile->cd();
			hadronicBGCurve = (TF1 *)corrFile->Get(Form("%s/HadronicBackgroundFits/hadronicBackground_%s_cent%02d_yIndex%02d_Fit",//SecondFit
							particleInfo->GetParticleName(pid,charge).Data(),
							particleInfo->GetParticleName(pid,charge).Data(),
						  iCentBin, yIndex));
			efficiencyCurve = (TF1 *)corrFile->Get(Form("%s/EfficiencyFits/tpcEfficiencyFit_%s_Cent%d_yIndex%d",
						  particleInfo->GetParticleName(pid,charge).Data(),
						  particleInfo->GetParticleName(pid,charge).Data(),
						  iCentBin, yIndex));
      
      //Get the Spectra
      spectraFile->cd();
      spectraFile->cd(Form("RawSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
      tpcRawSpectrum = (TGraphErrors *)gDirectory->Get(Form("rawSpectra_%s_Cent%02d_yIndex%02d",
							    particleInfo->GetParticleName(pid,charge).Data(),
							    iCentBin,yIndex));
      tpcSysErrSpectrum = new TGraphErrors();
		  
      cout <<efficiencyCurve <<" "<<hadronicBGCurve<<" "<<tpcRawSpectrum <<" " <<endl;

			if (!hadronicBGCurve){
				cout <<"    TPC Spectrum does not exist. Skipping this rapidity bin." <<endl;
				continue;
      }

			if (!efficiencyCurve){
				cout <<"    TPC Spectrum does not exist. Skipping this rapidity bin." <<endl;
				continue;
      }
      
      //Skip if the tpcSpectrum doesn't exist
      if (!tpcRawSpectrum){
				cout <<"    TPC Spectrum does not exist. Skipping this rapidity bin." <<endl;
				continue;
      }

      //Skip if the tpcSpectrum has no points
      if (tpcRawSpectrum->GetN() == 0){
	cout <<"    TPC Spectrum has no points. Skipping this rapidity bin." <<endl;
	continue;
      }
     
      if (draw){
				TH1F *frame = canvas->DrawFrame(0,.01,1.5,700);
				frame->GetXaxis()->SetTitle(Form("m_{T}-m_{%s} (GeV/c^{2})",
								particleInfo->GetParticleSymbol(pid).Data()));
				frame->GetYaxis()->SetTitle("#frac{1}{N_{Evt}}#times#frac{1}{2#pim_{T}}#times#frac{d^{2}N}{dm_{T}dy} (GeV/c^{2})^{2}");
				frame->GetYaxis()->SetTitleOffset(1.2);

				canvas->SetRightMargin(.05);
				canvas->SetTopMargin(.05);
				canvas->SetLogy();
      }

      //----Hadronic Background Correction----
			tpcBackgroundCorrectedSpectrum = ApplyBackgroundCorrection(tpcRawSpectrum,hadronicBGCurve);

      //----Efficiency Correction----
      tpcEfficiencyCorrectedSpectrum = ApplyEfficiencyCorrection(tpcBackgroundCorrectedSpectrum,efficiencyCurve);

      //----Fully Corrected Spectra----
      tpcFullyCorrectedSpectrum = tpcEfficiencyCorrectedSpectrum;
 
      //----Systematic Errors ----
      //Create n new spectra. The systematic error is then
      //computed as the RMS of the distribution of corrected yields at each point
      const int nSpectra(500);
      std::vector<TGraphErrors *> sysBackgroundCorrectedSpectra(nSpectra);
      std::vector<TGraphErrors *> sysEfficiencyCorrectedSpectra(nSpectra);
      
      std::vector<TGraphErrors *> sysFullyCorrectedSpectra(nSpectra);
      
      //TPC
      for (int iSpectra=0; iSpectra<nSpectra; iSpectra++){
	
				sysBackgroundCorrectedSpectra.at(iSpectra) =
				ApplyBackgroundCorrection(tpcRawSpectrum,hadronicBGCurve,true);
				
				sysEfficiencyCorrectedSpectra.at(iSpectra) =
					ApplyEfficiencyCorrection(sysBackgroundCorrectedSpectra.at(iSpectra),efficiencyCurve,true);

				sysFullyCorrectedSpectra.at(iSpectra) = sysEfficiencyCorrectedSpectra.at(iSpectra);
				
				delete sysBackgroundCorrectedSpectra.at(iSpectra);
      }
      
      //For each point in the spectrum, combine the statistical error in quadrature with the systematic Error
			//Set up spectra that will carry the systematic-only errors for drawing purposes in later macro

      for (int iPoint=0; iPoint<tpcFullyCorrectedSpectrum->GetN(); iPoint++){
	
				Double_t yErrStat = tpcFullyCorrectedSpectrum->GetEY()[iPoint];
				Double_t xErrStat = tpcFullyCorrectedSpectrum->GetEX()[iPoint];

				Double_t yVal = tpcFullyCorrectedSpectrum->GetY()[iPoint];
				Double_t xVal = tpcFullyCorrectedSpectrum->GetX()[iPoint];

				std::vector<double> ySysVec(nSpectra);
				std::vector<double> xSysVec(nSpectra);
				for (unsigned int iSpectra=0; iSpectra<nSpectra; iSpectra++){
					ySysVec.at(iSpectra) = sysFullyCorrectedSpectra.at(iSpectra)->GetY()[iPoint];
					xSysVec.at(iSpectra) = sysFullyCorrectedSpectra.at(iSpectra)->GetX()[iPoint];
				}

				Double_t yErrSys = TMath::RMS(nSpectra,&ySysVec.at(0));
				Double_t xErrSys = TMath::RMS(nSpectra,&xSysVec.at(0));

				Double_t yErrSysEff = yVal*0.1;//0.05

				//if (yIndex < 10) yErrSysEff = yVal*0.1;
				//if (yIndex < 10) yErrSysEff = yVal*0.1;
				if (yIndex == 7){
				  if (xVal > 0.085 && xVal < 0.09) yErrSysEff = yVal*0.12;
				}
				//if (yIndex == 6 && xVal > 0.10 && xVal < 0.12) yErrSysEff = yVal*0.1;
				if (yIndex < 6){
					if (xVal < 0.34) yErrSysEff = yVal*0.15;
				  if (xVal > 0.10 && xVal < 0.12) yErrSysEff = yVal*0.18;
				}
				if (yIndex == 3){
				  if (xVal > 0.27 && xVal < 0.3) yErrSysEff = yVal*0.25;
				  if (xVal > 0.30 && xVal < 0.32) yErrSysEff = yVal*0.18;
				}


				Double_t yTotalError = TMath::Sqrt(pow(yErrStat,2) + pow(yErrSys,2) + pow(yErrSysEff,2));
				Double_t xTotalError = xErrStat;
				
				tpcFullyCorrectedSpectrum->SetPointError(iPoint,xTotalError,yTotalError);
	  
			  tpcSysErrSpectrum->SetPoint(iPoint,xVal,yVal);
			  tpcSysErrSpectrum->SetPointError(iPoint,xErrSys,yErrSys);

      }

		  RemovePointsWithLargeErrors(tpcFullyCorrectedSpectrum);	
      TGraphChop(tpcFullyCorrectedSpectrum,0.08,true);
      TGraphChop(tpcFullyCorrectedSpectrum,0.5,false);

      //Draw
      if (draw){
	
				for (unsigned int i=0; i<nSpectra; i++){
					sysEfficiencyCorrectedSpectra.at(i)->SetMarkerColor(kBlack);
					sysEfficiencyCorrectedSpectra.at(i)->SetMarkerStyle(kFullTriangleUp);
					sysEfficiencyCorrectedSpectra.at(i)->Draw("P");
				}
				
				tpcEfficiencyCorrectedSpectrum->SetMarkerStyle(kFullCircle);
				
				tpcEfficiencyCorrectedSpectrum->Draw("PZ");

				canvas->Update();
				gSystem->Sleep(2000);

      }


      
      //Set Names and Titles
      tpcFullyCorrectedSpectrum->SetName(Form("correctedSpectra_%s_Cent%02d_yIndex%02d",
					     particleInfo->GetParticleName(pid,charge).Data(),
					     iCentBin,yIndex));
      tpcSysErrSpectrum->SetName(Form("correctedSysErrSpectra_%s_Cent%02d_yIndex%02d",
					     particleInfo->GetParticleName(pid,charge).Data(),
					     iCentBin,yIndex));

      tpcFullyCorrectedSpectrum->SetTitle(Form("Corrected TPC Spectrum %s Cent=[%d,%d]%% y_{%s}=[%.02f,%.02f];m_{T}-m_{%s};",
					       particleInfo->GetParticleSymbol(pidIndex,charge).Data(),
					       iCentBin!=0 ? (int)GetCentralityPercents().at(iCentBin-1):0,
					       (int)GetCentralityPercents().at(iCentBin),
					       particleInfo->GetParticleSymbol(pidIndex).Data(),
					       GetRapidityRangeLow(yIndex),GetRapidityRangeHigh(yIndex),
					       particleInfo->GetParticleSymbol(pidIndex).Data()));

      //Save
      spectraFile->cd();
      spectraFile->cd(Form("SysErrCorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
      tpcSysErrSpectrum->Write();
      spectraFile->cd();
      spectraFile->cd(Form("CorrectedSpectra_%s",particleInfo->GetParticleName(pid,charge).Data()));
      tpcFullyCorrectedSpectrum->Write();

      //Clean Up
      if (tpcRawSpectrum)
	delete tpcRawSpectrum;
      if (efficiencyCurve)
	delete efficiencyCurve;
      if (tpcBackgroundCorrectedSpectrum)
	delete tpcBackgroundCorrectedSpectrum;
      if (tpcEfficiencyCorrectedSpectrum)
	delete tpcEfficiencyCorrectedSpectrum;
    }    

  }
  
}//END MAIN


//_________________________________________________________________
TGraphErrors *ApplyEfficiencyCorrection(TGraphErrors *spectrum, TF1 *efficiencyCurve, Bool_t doSystematics){

  //Apply the TPC Tracking Efficiency Correction
  //and return a new spectrum
  TGraphErrors *corrSpectrum = new TGraphErrors();

  //Create a copy of the efficiency curve in case it is needed
  //to do the systematic errors
  TF1 tempFunc(*efficiencyCurve);
  if (pidIndex !=2 && doSystematics){

    Bool_t isGoodCurve = false;
    while (!isGoodCurve){
      TRandom rand(0);
      tempFunc.SetParameter(0,rand.Gaus(efficiencyCurve->GetParameter(0),efficiencyCurve->GetParError(0)));
      tempFunc.SetParameter(1,rand.Gaus(efficiencyCurve->GetParameter(1),efficiencyCurve->GetParError(1)));
      tempFunc.SetParameter(2,rand.Gaus(efficiencyCurve->GetParameter(2),efficiencyCurve->GetParError(2)));

      //Check the end points to make sure they are within[0,1]
      Double_t min(0),max(0);
      tempFunc.GetRange(min,max);
      if (tempFunc.Eval(min) < 0 || tempFunc.Eval(max) < 0 ||
	  tempFunc.Eval(min) > 1 || tempFunc.Eval(max) > 1)
	isGoodCurve = false;
      else
	isGoodCurve = true;
    }//End Check for good curve

  }//End If Systematics
  
  //Loop Over the Points
  for (int iPoint=0; iPoint<spectrum->GetN(); iPoint++){

    //Get the point info
    Double_t mTm0  = spectrum->GetX()[iPoint];
    Double_t yield = spectrum->GetY()[iPoint];
    Double_t xErr  = spectrum->GetEX()[iPoint];
    Double_t yErr  = spectrum->GetEY()[iPoint]; 

    //Get the Efficiency Correction Factor. By default the correction factor
    //is determined by evaluating the efficiency curve. Otherwise, the parameters
    //of the curve are varied (see above) to determine the systematic error.
    Double_t effCorrFactor = efficiencyCurve->Eval(mTm0);

    //Make sure the TPC tracking efficiency is above the minimum, if not
    //do not add a point to the corrected spectrum
    if (effCorrFactor < minTPCEfficiency)
      continue;    

    //If Systematic Errors are requested
    if (pidIndex !=2 && doSystematics){

      effCorrFactor = tempFunc.Eval(mTm0);
      
    }
    
    //Apply the correction
    corrSpectrum->SetPoint(corrSpectrum->GetN(),mTm0,yield/effCorrFactor);
    corrSpectrum->SetPointError(corrSpectrum->GetN()-1,xErr,yErr/effCorrFactor);
    
  }//End Loop Over Points

  corrSpectrum->SetMarkerStyle(spectrum->GetMarkerStyle());
  corrSpectrum->SetMarkerColor(spectrum->GetMarkerColor());
  
  return corrSpectrum;
  
}

//__________________________________________________________________________________
TGraphErrors *ApplyBackgroundCorrection(TGraphErrors *spectrum, TF1 *backgroundCurve, Bool_t doSystematics){

  //Apply the Knockout Proton Correction and return a new spectrum
  TGraphErrors *corrSpectrum = new TGraphErrors();

  for (int iPoint=0; iPoint<spectrum->GetN(); iPoint++){

    //Get the point info
    Double_t mTm0  = spectrum->GetX()[iPoint];
    Double_t yield = spectrum->GetY()[iPoint];
    Double_t xErr  = spectrum->GetEX()[iPoint];
    Double_t yErr  = spectrum->GetEY()[iPoint];

    //Find the Background fraction by evaluating the backgroundCurve
    Double_t backgroundFraction = backgroundCurve->Eval(mTm0);

    //If we are doing the systematics then evaluate the curve
    //at a random location within the bin
    if (doSystematics){

      TRandom3 rand(0);
      Double_t randommTm0 = rand.Uniform(mTm0-xErr,mTm0+xErr);
      backgroundFraction = backgroundCurve->Eval(randommTm0);

    }//End Do Systematics

    //Compute the Correction Factor
    Double_t correctionFactor = 1.0 - backgroundFraction;

    //Make sure the correction factor is good
    //if bad then set it to 1 so no change will be made
    if (TMath::IsNaN(correctionFactor))
      correctionFactor = 1.0;

    //Apply the Correction
    Double_t correctedYield = yield * correctionFactor;
    Double_t correctedError = yErr * correctionFactor;

    //Set the Point in the corrected Spectrum
    corrSpectrum->SetPoint(corrSpectrum->GetN(),mTm0,correctedYield);
    corrSpectrum->SetPointError(corrSpectrum->GetN()-1,xErr,correctedError);

  }//End Loop Over Points

  corrSpectrum->SetMarkerStyle(spectrum->GetMarkerStyle());
  corrSpectrum->SetMarkerColor(spectrum->GetMarkerColor());

  return corrSpectrum;

}
