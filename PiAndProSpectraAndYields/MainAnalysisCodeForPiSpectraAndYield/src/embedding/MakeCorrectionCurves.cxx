#include <iostream>
#include <vector>

#include <TFile.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TVirtualFitter.h>
#include <TEfficiency.h>
#include <TMinuit.h>
#include <TRandom3.h>
#include <TFitResult.h>

#include "globalDefinitions.h"
#include "utilityFunctions.h"
#include "ParticleInfo.h"
#include "UserCuts.h"

#include "EfficiencyFitUtilities.h"

bool draw = false;

void MakeCorrectionCurves(TString embeddingFile, TString correctionFile, Int_t pid, Int_t charge){

  gStyle->SetOptFit(1);
  TVirtualFitter::SetMaxIterations(20000);
  
  //No spectra will go below mT-m0 = 0.1 so set min fit range
  const double minFitRange = 0.0; //mT-m0
  const int rebinVal = 5;
  ParticleInfo *particleInfo = new ParticleInfo();
  
  //Create the Output Correction File
  TFile *corrFile = new TFile(correctionFile,"UPDATE");
  corrFile->mkdir(Form("%s",particleInfo->GetParticleName(pid,charge).Data()));
  corrFile->cd(Form("%s",particleInfo->GetParticleName(pid,charge).Data()));
  gDirectory->mkdir("EfficiencyGraphs");
  gDirectory->mkdir("EfficiencyFits");
  gDirectory->mkdir("EnergyLossGraphs");
  gDirectory->mkdir("EnergyLossFits");

  //Open the Embedding File
  TFile *embFile = new TFile(embeddingFile,"READ");

  //Creat a canvas (optional)
  TCanvas *canvas = NULL;
  TCanvas *canvas1 = NULL;
  if (draw){
    canvas = new TCanvas("canvas","canvas",20,20,800,600);
    canvas1 = new TCanvas("canvas1","canvas1",20,20,800,600);
  }
  
  //Get the Number of Centrality Bins
  const int nCentBins = 7;
  const int nRapBins = 20;
  std::vector<Int_t> centralityPercents;
	centralityPercents.push_back(5);
	centralityPercents.push_back(10);
	centralityPercents.push_back(15);
	centralityPercents.push_back(20);
	centralityPercents.push_back(25);
	centralityPercents.push_back(30);
	centralityPercents.push_back(100);

  //Pointers to current Efficiency TGraph
  std::vector<std::vector<TGraphAsymmErrors *> > heff(nCentBins,vector<TGraphAsymmErrors *>(nRapBins,(TGraphAsymmErrors *)NULL));

  //Get the TGraph from the file
  for (int iCentBin=0; iCentBin<nCentBins; iCentBin++){
		for (int iRapBin=0; iRapBin<nRapBins; iRapBin++){
			heff[iCentBin][iRapBin] =
				(TGraphAsymmErrors *)embFile->Get(Form("Efficiency_Cent%d_yIndex%d",iCentBin,iRapBin));
		}
  }

  //*****************************************
  //   TPC TRACKING EFFICIENCY
  //*****************************************

  Double_t prevPars[3] = {.85,0.1,2.5};
	
  //Loop Over the centrality bins, for each cent bin construct the 1D efficiency and
  //energy loss graphs for various rapidity bins. Use the fits to the centrality integrated
  //graphs from STEP ONE to fix the turn on parameters.
  for (Int_t iCentBin=0; iCentBin<nCentBins; iCentBin++){

    //Loop Over the Rapidity Bins
    for (int yIndex=0; yIndex<nRapBins; yIndex++){
       
			if (heff[iCentBin][yIndex] == NULL) continue;
      //Rebin
      //embTrackHisto->Rebin(rebinVal);
      //matchTrackHisto->Rebin(rebinVal);
      
      //Create the Efficiency Graph
      corrFile->cd();

      heff[iCentBin][yIndex]->SetMarkerStyle(particleInfo->GetParticleMarker(pid,charge));
      heff[iCentBin][yIndex]->SetMarkerColor(particleInfo->GetParticleColor(pid));
      heff[iCentBin][yIndex]->SetName(Form("tpcEfficiencyGraph_%s_Cent%d_yIndex%d",
				    particleInfo->GetParticleName(pid,charge).Data(),
				    iCentBin,yIndex));
      heff[iCentBin][yIndex]->SetTitle(Form("TPC Tracking Efficiency %s | Cent=[%d,%d]%% | y_{%s}^{Emb}=[%.03g,%.03g];(m_{T}-m_{%s})^{Emb};Efficiency #times Acceptance",
				    particleInfo->GetParticleSymbol(pid,charge).Data(),
						iCentBin == 0 ? 0 : centralityPercents.at(iCentBin-1),
				    centralityPercents.at(iCentBin),
				    particleInfo->GetParticleSymbol(pid).Data(),
				    GetRapidityRangeLow(yIndex),
				    GetRapidityRangeHigh(yIndex),
				    particleInfo->GetParticleSymbol(pid).Data()));
      heff[iCentBin][yIndex]->SetMarkerStyle(particleInfo->GetParticleMarker(pid,charge));
      heff[iCentBin][yIndex]->SetMarkerColor(particleInfo->GetParticleColor(pid));

      
      //Create the Fit
      TF1 efficiencyFit(Form("tpcEfficiencyFit_%s_Cent%d_yIndex%d",
			     particleInfo->GetParticleName(pid,charge).Data(),
			     iCentBin,yIndex),
			"[0]*exp(-([1]/pow(x,[2])))",minFitRange,2.0);
      efficiencyFit.SetNpx(10000);
      efficiencyFit.SetLineWidth(3);
      efficiencyFit.SetLineColor(kRed);
      efficiencyFit.SetLineStyle(7);

      efficiencyFit.SetParameters(prevPars);
			efficiencyFit.SetParLimits(0,0,1);
			efficiencyFit.SetParLimits(1,0,5);
			efficiencyFit.SetParLimits(2,0,5);
      
      TFitResultPtr fitResult = heff[iCentBin][yIndex]->Fit(&efficiencyFit,"RSEX0");
      int attempt(0);
      while (fitResult.Get()->Status() != 0 && attempt < 10) {
				fitResult = heff[iCentBin][yIndex]->Fit(&efficiencyFit,"RSEX0");
				cout <<attempt++ <<endl;;
      }
      
      prevPars[0] = efficiencyFit.GetParameter(0);
      prevPars[1] = efficiencyFit.GetParameter(1);
      prevPars[2] = efficiencyFit.GetParameter(2);

      if (draw){
				canvas->cd();
				TH1F *frame = canvas->DrawFrame(0,0,2.2,1.2);
				frame->SetTitle(heff[iCentBin][yIndex]->GetTitle());
				heff[iCentBin][yIndex]->Draw("PZ");
				efficiencyFit.Draw("SAME");
				canvas->Update();
				gSystem->Sleep(1000);
      }
      
      //Save
      corrFile->cd();
      corrFile->cd(Form("%s",particleInfo->GetParticleName(pid,charge).Data()));
      gDirectory->cd("EfficiencyGraphs");
      heff[iCentBin][yIndex]->Write();
      corrFile->cd();
      corrFile->cd(Form("%s",particleInfo->GetParticleName(pid,charge).Data()));
      gDirectory->cd("EfficiencyFits");
      efficiencyFit.Write();
      corrFile->cd();

      //Clean Up
      if (heff[iCentBin][yIndex]) delete heff[iCentBin][yIndex];


    }//End Loop Over yIndex

  }//End Loop Over Centrality Bin

}//End Main
