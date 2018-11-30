#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include "TFile.h"
#include "TDirectory.h"
#include "TNtuple.h"
#include "TDirectory.h"
#include "TString.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TVectorD.h"
#include "TNtupleD.h"

using namespace std;

//Code to obtain the efficiency vector
Int_t Efficiency(TString infile, TString outfile){

	Int_t nCentBins = 7;
  Int_t nRapBins  = 20;
  
	//Open the embedding plots file
	TFile *embFile = TFile::Open(infile);
  Bool_t embStatus = embFile->IsOpen();
	if(embStatus == 0){
	  cout<<"Error opening output file"<<endl;
	  system("pause");
	  return -1;
	}
  //Create the output file
	TFile *outFile = new TFile(outfile,"RECREATE");

	//Create the histograms
	TH1F* hemb = new TH1F("","",200,0,2);
	TH1F* hmatch = new TH1F("","",200,0,2);
	std::vector<std::vector<TGraphAsymmErrors *> > heff(nCentBins,vector<TGraphAsymmErrors *>(nRapBins,(TGraphAsymmErrors *)NULL));

	//Create the Efficiency Graph

	//Navigate to the efficiency histogram directory
  TDirectoryFile *d1 = (TDirectoryFile*)embFile->Get("EfficiencyHistograms"); 

	//Get Histograms
	for (Int_t centIndex=0; centIndex<nCentBins; centIndex++){
		for (Int_t rapIndex=0; rapIndex<nRapBins; rapIndex++){
			hemb = (TH1F*)d1->Get(Form("embTrackHisto_Cent%d_yIndex%d",centIndex,rapIndex));
		  hmatch = (TH1F*)d1->Get(Form("matchTrackHisto_Cent%d_yIndex%d",centIndex,rapIndex));
			if (hemb->GetEntries() < 10 || hmatch->GetEntries() < 10){
        heff[centIndex][rapIndex] = NULL;
	      hemb->Clear();
        hmatch->Clear();
        continue;
      }   
			heff[centIndex][rapIndex] = new TGraphAsymmErrors();
			heff[centIndex][rapIndex]->Divide(hmatch,hemb);
			heff[centIndex][rapIndex]->SetName(Form("Efficiency_Cent%d_yIndex%d",centIndex,rapIndex));
			heff[centIndex][rapIndex]->SetTitle(Form("Efficiency_Cent%d_yIndex%d",centIndex,rapIndex));
			heff[centIndex][rapIndex]->GetYaxis()->SetRangeUser(0.,1.1);

			//Save the histogram to file
			outFile->cd();
			heff[centIndex][rapIndex]->Write();
			

			//Clear histograms
			hemb->Clear();
			hmatch->Clear();
		}
	}

  outFile->Close();

  return 0;
}//end of program
