#include <iostream>

#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include "TLegend.h"
#include <TStyle.h>

#include "GlauberClass.h"

#include "TrackInfo.h"
#include "PrimaryVertexInfo.h"
#include "EventInfo.h"
#include "DavisDstReader.h"
#include "ParticleInfo.h"
#include "UserCuts.h"


void pileupLuminosity(TString fitFile="",
											Int_t fitNumber=0,
											TString dataFile="", 
											TString glauberFile="", 
											TString outputFile="",
											Int_t normStartBin=0,
											Int_t normEndBin=0,
											Double_t NegativeBinomialParameterP=0,
											Double_t NegativeBinomialParameterN=0,
											Double_t pileUpEventOccurence=0,
											Int_t nSimulatedEvents=100000,
											Bool_t drawCanvas=false){

	Double_t occurence = pileUpEventOccurence; // between 0 and 1

	Int_t nBins = 1000;
	Int_t Bin_i = 0;
	Int_t Bin_f = 1000;

	const int nCentralityBins = GetNCentralityBins();
  std::vector <int> centCuts = GetCentralityCuts();
  std::vector <double> centPercents = GetCentralityPercents();
	Int_t pileUpBin = GetPileUpCut();

  if (centCuts.size() != centPercents.size()){
    cout <<"ERROR: DrawCentralityBinResults.C - centrality cut and centrality percent vectors are different sizes!" <<endl;
    exit (EXIT_FAILURE);
  }

  if (normEndBin<normStartBin){
    cout <<"ERROR: Cannot Normalize! Check that normEndBin > normStartBin" <<endl;
    exit (EXIT_FAILURE);
  }	

	Int_t endNumber = GetPileUpCut(); //pileup cut

	Int_t startBin = normStartBin; //region where model should match
	Int_t endBin = normEndBin;

	//input files
  TFile *inFile = NULL;
  if (fitFile.CompareTo(""))
    inFile = new TFile(fitFile,"READ");

	TFile *fData = NULL;
	if (dataFile.CompareTo(""))
		fData = new TFile(dataFile,"READ");

  TFile *localGlauberFile = NULL;
  if (glauberFile.CompareTo(""))
    localGlauberFile = new TFile(glauberFile,"READ");

  //If no output file was specified then we won't produce one
  TFile *outFile = NULL;
  if (outputFile.CompareTo(""))
    outFile = new TFile(outputFile,"RECREATE");

	//histograms needed
	TH1D *hPileUp = new TH1D("hPileUp", "hPileUp", nBins,Bin_i,Bin_f); //pileup model
	TH1D *hNoPileUp = new TH1D("hNoPileUp", "hNoPileUp", nBins,Bin_i,Bin_f);
	TH1D *hJustPileUp = new TH1D("hJustPileUp", "hJustPileUp", nBins,Bin_i,Bin_f);

	TH1D *hBestFit = (TH1D *)inFile->Get("bestFit_"+TString::Format("%d",fitNumber));
	hBestFit->SetName("hBestFit");
	hBestFit->SetTitle("hBestFit");

	TH1D *hGoodTracks = (TH1D *)fData->Get("nGoodTracks");
	hGoodTracks->SetName("hGoodTracks");
	hGoodTracks->Sumw2();
	hGoodTracks->SetMarkerColor(kBlack);
	hGoodTracks->SetMarkerStyle(kFullCircle);

	//Glauber tree	
	TTree *glauberTree = (TTree *)localGlauberFile->Get("GlauberTree");
	GlauberClass *glauberEvent = NULL;
	glauberTree->SetBranchAddress("GlauberData",&glauberEvent);
	glauberEvent->SetNegativeBinomialParameters(NegativeBinomialParameterP,NegativeBinomialParameterN);

	TRandom3 rand(0);

	for(Int_t iEvent=0; iEvent<nSimulatedEvents; iEvent++){
		Double_t rGoodTracks = hGoodTracks->GetRandom();
		Double_t rGoodTracksOrig = rGoodTracks;
		if(rGoodTracks>endNumber){ //Avoiding pure pileup bins
			iEvent--;
			continue;
		}
		
		Double_t r = rand.Uniform(0,1);
	
		if(r < occurence){
			Int_t rEntry = rand.Uniform(0,hGoodTracks->GetEntries());
			glauberTree->GetEntry(rEntry);
			rGoodTracks += glauberEvent->ProduceParticles();
			hPileUp->Fill(rGoodTracks);
			hJustPileUp->Fill(rGoodTracks);
		}
		else{
			hPileUp->Fill(rGoodTracksOrig);
			hNoPileUp->Fill(rGoodTracksOrig);
		}
	}


	Int_t scaleFactor = hGoodTracks->Integral(hGoodTracks->FindBin(startBin),hGoodTracks->FindBin(endBin)); //based on range the model should be valid : startBin->endBin
	hBestFit->Scale(scaleFactor); //as the bestFit was normalized in RunCentralityDetermination.sh

	Int_t modelScaleFactor = hPileUp->Integral(hPileUp->FindBin(startBin),hPileUp->FindBin(endBin));

	hPileUp->Scale( (Double_t)scaleFactor/(Double_t)modelScaleFactor ); //black
	hNoPileUp->Scale( (Double_t)scaleFactor/(Double_t)modelScaleFactor ); //blue
	hJustPileUp->Scale( (Double_t)scaleFactor/(Double_t)modelScaleFactor ); //red

	Double_t triggerEfficiency=-1;
	Double_t fractionPileUp=-1;

	for(Int_t iCentBin=0; iCentBin<nCentralityBins; iCentBin++){
	
		Double_t dataBinsIntegral = (iCentBin==0) ? hGoodTracks->Integral(hGoodTracks->FindBin(centCuts.at(iCentBin)),hGoodTracks->FindBin(pileUpBin)) :
																								hGoodTracks->Integral(hGoodTracks->FindBin(centCuts.at(iCentBin)),hGoodTracks->FindBin((Int_t) centCuts.at(iCentBin-1) -1) );
		Double_t bestFitIntegral = (iCentBin==0) ? hBestFit->Integral(hBestFit->FindBin(centCuts.at(iCentBin)),hBestFit->FindBin(pileUpBin)) :
																							hBestFit->Integral(hBestFit->FindBin(centCuts.at(iCentBin)),hBestFit->FindBin((Int_t) centCuts.at(iCentBin-1) -1) );
		Double_t pileUpIntegral = (iCentBin==0) ? hJustPileUp->Integral(hJustPileUp->FindBin(centCuts.at(iCentBin)),hJustPileUp->FindBin(pileUpBin)) :
																							hJustPileUp->Integral(hJustPileUp->FindBin(centCuts.at(iCentBin)),hJustPileUp->FindBin((Int_t) centCuts.at(iCentBin-1) -1) ); 
				
		fractionPileUp = pileUpIntegral/dataBinsIntegral; //fraction pile up in each centrality bin

		if(dataBinsIntegral>bestFitIntegral)
			triggerEfficiency = 1. - (dataBinsIntegral-bestFitIntegral)/bestFitIntegral;
		else
			triggerEfficiency =  1. - (bestFitIntegral-dataBinsIntegral)/bestFitIntegral;

		cout<<Form("centralityIndex %d, bins %d-%d : \n\t TriggerEfficiency : %f\% \n\t PileUp : %f\%",
							iCentBin,
							centCuts.at(iCentBin),((iCentBin==0) ? pileUpBin:(Int_t)centCuts.at(iCentBin-1)-1),
							triggerEfficiency*100.,
							fractionPileUp*100.)<<endl;
	}
	
	hBestFit->Write("hBestFit");
	hGoodTracks->Write("hGoodTracks");
	hJustPileUp->Write();

	if(drawCanvas){
		TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
		canvas->cd(1);
		gStyle->SetOptStat(11);
		gPad->SetLogy();
		hGoodTracks->Draw();
		hGoodTracks->SetAxisRange(0,
															hGoodTracks->GetBinCenter(hGoodTracks->FindLastBinAbove(0)),
															"X");
		hGoodTracks->SetAxisRange(1,hBestFit->GetBinContent(1),"Y");
		hGoodTracks->SetLineColor(1);
		hPileUp->Draw("SAME");
		hJustPileUp->Draw("SAME");
		hNoPileUp->Draw("SAME");
		hGoodTracks->GetYaxis()->SetTitleOffset(1.5);
		hBestFit->SetLineColor(6);
		hPileUp->SetLineColor(1);
		hJustPileUp->SetLineColor(2);
		hNoPileUp->SetLineColor(4);
		hBestFit->Draw("SAME");

		TLegend *leg = new TLegend(0.6,0.4,0.85,0.6);
		leg->AddEntry(hGoodTracks, "dataFile - nGoodTracks", "P");
		leg->AddEntry(hBestFit, "Glauber + NBP","LPE");
		leg->AddEntry(hPileUp, "JustPileUp + NoPileUp", "L");
		leg->AddEntry(hJustPileUp, "JustPileUp", "L");
		leg->AddEntry(hNoPileUp, "NoPileUp", "L");
		leg->Draw();

		hNoPileUp->Write();
		hPileUp->Write();
		canvas->Write();
	}

	outFile->Close();
}	
