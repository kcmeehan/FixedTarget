#include <iostream>
#include <TFile.h>
#include <TGraph.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include "TLegend.h"
#include <TStyle.h>

//#include "GlauberClass.h"
#include "/scratch_menkar/kinghorn/fxtcommit/AuAu_4_5GeV_2015/davisdstanalysis/src/submodules/glaubermcmodel/inc/GlauberClass.h"

void pileupChiSquaredMinimization(TString fitFile="",
																	Int_t fitNumber=0,
                                  TString dataFile="",
																	TString glauberFile="",
																	TString outputFile="",
																	Int_t normStartBin=0,
																	Int_t normEndBin=0,
																	Int_t lastBin=0,
																	Double_t NegativeBinomialParameterP=0,
																	Double_t NegativeBinomialParameterN=0,
																	Int_t numberOfPercentages=0,
																	Double_t percentBeg=0,
																	Double_t percentEnd=0,
																	Int_t nSimulatedEvents=0){

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

  //output file
  TFile *outFile = NULL;
  if (outputFile.CompareTo(""))
    outFile = new TFile(outputFile,"RECREATE");

	Int_t n = numberOfPercentages; //number of pileup histograms. Let n >= 1
	
	cout <<"made it here 3" <<endl;

  TH1D* hPileUp[n];
	TH1D* hNoPileUp[n];
	TH1D* hJustPileUp[n];
	char* histname = new char[n];
	char* histnameNo = new char[n];
	char* histnameJust = new char[n];
	for(int i=0; i<n; i++){
		sprintf(histname,"hPileUp%d",i);
		sprintf(histnameNo,"hNoPileUp%d",i);
		sprintf(histnameJust,"hJustPileUp%d",i);
		hPileUp[i] = new TH1D(histname, "", 1000,0,1000); //fix nBins and binwidth
		hNoPileUp[i] = new TH1D(histnameNo, "", 1000,0,1000);
		hJustPileUp[i] = new TH1D(histnameJust, "", 1000,0,1000);
	}

  cout <<"made it here 4" <<endl;

  TH1D *hBestFit = (TH1D *)inFile->Get("bestFit_"+TString::Format("%d",fitNumber));
	hBestFit->SetName("hBestFit");
	hBestFit->SetTitle("hBestFit");

	TH1D *hGoodTracks = (TH1D *)fData->Get("nGoodTracks");
	hGoodTracks->SetName("hGoodTracks");
	hGoodTracks->Sumw2();
	hGoodTracks->SetMarkerColor(kBlack);
	hGoodTracks->SetMarkerStyle(kFullCircle);

	Int_t startBin = hGoodTracks->FindBin(normStartBin); //normalization region
	Int_t endBin = hGoodTracks->FindBin(normEndBin);

	Int_t badBin = hGoodTracks->FindBin(lastBin); //pileup region. Beyond this bin is where the ChiSquared minimization will take place

	TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
	canvas->SetLogy();

	TTree *glauberTree = (TTree *)localGlauberFile->Get("GlauberTree");
	GlauberClass *glauberEvent = 0;
	glauberTree->FindBranch("GlauberData")->SetAddress(&glauberEvent);
  glauberEvent->SetNegativeBinomialParameters(NegativeBinomialParameterP,NegativeBinomialParameterN);

	TRandom3 rand(1);

	cout <<"here"<<endl;

	if(n==1){
		for (Int_t iEvent=0; iEvent<nSimulatedEvents; iEvent++){
		
			Double_t rGoodTracks = hGoodTracks->GetRandom();
			Double_t rGoodTracksOrig = rGoodTracks;
			if(rGoodTracks>badBin){
				iEvent--;
				continue;
			}

			Double_t r = rand.Uniform(0,1);

			for(int i=0; i<n; i++){
				if(r < percentBeg*.01){
					Int_t rEntry = rand.Uniform(0,hGoodTracks->GetEntries());
					glauberTree->GetEntry(rEntry);
					rGoodTracks += glauberEvent->ProduceParticles();
					hPileUp[i]->Fill(rGoodTracks);
					hJustPileUp[i]->Fill(rGoodTracks);
				}
				else{
					hPileUp[i]->Fill(rGoodTracksOrig);
					hNoPileUp[i]->Fill(rGoodTracksOrig);
				}
			}
		}
	}
	if(n!=1){
		for (Int_t iEvent=0; iEvent<nSimulatedEvents; iEvent++){
		
			Double_t rGoodTracks = hGoodTracks->GetRandom();
			Double_t rGoodTracksOrig = rGoodTracks;
			if(rGoodTracks>badBin){
				iEvent--;
				continue;
			}

			Double_t r = rand.Uniform(0,1);

			for(int i=0; i<n; i++){
				if(r < (percentBeg + i*(percentEnd-percentBeg)/(n-1))*.01){
					Int_t rEntry = rand.Uniform(0,hGoodTracks->GetEntries());
					glauberTree->GetEntry(rEntry);
					rGoodTracks += glauberEvent->ProduceParticles();
					hPileUp[i]->Fill(rGoodTracks);
					hJustPileUp[i]->Fill(rGoodTracks);
					rGoodTracks = rGoodTracksOrig;
				}
				else{
					hPileUp[i]->Fill(rGoodTracksOrig);
					hNoPileUp[i]->Fill(rGoodTracksOrig);
				}
			}
		}
	}	

	cout <<"here"<<endl;

	Double_t PileUpPercent[n];
	Double_t ChiSquaredNDF[n];

	for(int i=0; i<n; i++){
		PileUpPercent[i]=0;
		ChiSquaredNDF[i]=0;
	}

	Int_t scaleFactor = hGoodTracks->Integral(startBin,endBin); //based on range the model should be valid : startBin->endBin
	hBestFit->Scale(scaleFactor); //as the bestFit was normalized in RunCentralityDetermination.sh

	hGoodTracks->Draw();
	hGoodTracks->SetAxisRange(0,
														hGoodTracks->GetBinCenter(hGoodTracks->FindLastBinAbove(0)),
														"X");
	hGoodTracks->SetAxisRange(1,hBestFit->GetBinContent(1),"Y");
	hGoodTracks->SetLineColor(1);
	hGoodTracks->GetXaxis()->SetTitle("Number of Good Tracks");
	hGoodTracks->GetYaxis()->SetTitle("Counts");

	for(int i=0; i<n; i++){
		Double_t modelScaleFactor = hPileUp[i]->Integral( hPileUp[i]->FindBin(startBin),hPileUp[i]->FindBin(endBin) );
		hPileUp[i]->Scale( (Double_t)scaleFactor/modelScaleFactor );
		hNoPileUp[i]->Scale( (Double_t)scaleFactor/modelScaleFactor );
		hJustPileUp[i]->Scale( (Double_t)scaleFactor/modelScaleFactor );
		hPileUp[i]->Draw("SAME");
		hNoPileUp[i]->Draw("SAME");
		hJustPileUp[i]->Draw("SAME");
		if(i!=1){
			hPileUp[i]->SetLineColor(4+i);
			hNoPileUp[i]->SetLineColor(4+i);
			hJustPileUp[i]->SetLineColor(4+i);
		}
		if(i==1){
			hPileUp[0]->SetLineColor(1);
			hNoPileUp[0]->SetLineColor(4);
			hJustPileUp[0]->SetLineColor(2);
		}
		
		Int_t binCounter = 0;
		Double_t ChiSquared = 0;

		//cout<<"iBin"<<'\t'<<"mu"<<'\t'<<"X"<<'\t'<<"sigma"<<'\t'<<"binCounter"<<'\t'<<"ChiSquared"<<endl;
		for(int iBin=badBin; iBin<=hGoodTracks->GetBinCenter(hGoodTracks->FindLastBinAbove(0)); iBin++){
			Double_t mu = hGoodTracks->GetBinContent(iBin);
			Double_t sigma = hGoodTracks->GetBinError(iBin);
			Double_t X = hPileUp[i]->GetBinContent(iBin);
			if(mu != 0 && X != 0){
				binCounter++; 
				ChiSquared += pow((X-mu)/sigma,2);
				//cout<<iBin<<'\t'<<mu<<'\t'<<X<<'\t'<<sigma<<'\t'<<binCounter<<'\t'<<ChiSquared<<endl;
			}
		}
		ChiSquaredNDF[i] = ChiSquared/((double)binCounter-1);
		if(n==1)
			PileUpPercent[i] = percentBeg;
		if(n!=1)
			PileUpPercent[i] = percentBeg+i*(percentEnd-percentBeg)/(n-1);
	}

	TLegend* leg = new TLegend(0.6,0.4,0.85,0.6);
	leg->SetHeader("Fractional percentage pile-up");
	leg->AddEntry(hGoodTracks, "dataFile - nGoodTracks", "p");
	TString fraction;
	for(int i=0; i<n; i++){
		if(n==1){
			fraction.Form("%.2f%%", percentBeg);
			leg->AddEntry(hPileUp[i], fraction,  "l");
		}
		if(n!=1){
			fraction.Form("%.2f%%", percentBeg+i*(percentEnd-percentBeg)/(n-1));		
			leg->AddEntry(hPileUp[i], fraction,  "l");
		}	
	}
	leg->Draw("SAME");

	cout <<"here3"<<endl;

	TF1 *ChiSquaredNDFFit = new TF1("ChiSquaredNDFFit", "[0]*x*x+[1]*x+[2]");
	TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 600);
	canvas2->cd();
	TGraph* gr = new TGraph(n,PileUpPercent,ChiSquaredNDF);
	gr->SetTitle("#chi^{2}_{NDF} vs Percent Pile-Up");
	gr->GetXaxis()->SetTitle("Percent Pile-Up");
	gr->GetYaxis()->SetTitle("#chi^{2}_{NDF}");
	gr->Fit(ChiSquaredNDFFit);	
	gr->Draw("A*");

	outFile->cd();
	hGoodTracks->Write();
	hBestFit->Write();
	for(Int_t i=0; i<n; i++){
		hPileUp[i]->Write();
		hNoPileUp[i]->Write();
		hJustPileUp[i]->Write();
	}
	canvas->Write();
	canvas2->Write();
	
	cout <<'\n'<< "%PU" <<'\t'<< "ChiSquaredNDF" <<endl;
	for(int i=0; i<n; i++){
		cout<< PileUpPercent[i] <<'\t'<< ChiSquaredNDF[i]<<endl;
	}
}
