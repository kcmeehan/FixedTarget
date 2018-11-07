#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>

#include <TFile.h>
#include <TClonesArray.h>
#include <TNtuple.h>
#include <TDirectory.h>
#include <TMath.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TColor.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TRandom3.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TString.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TVectorD.h>
#include <TNtupleD.h>

#include "/global/homes/m/meehan/Embedding/AuAu_4_5GeV_2015/EmbeddingForThesis/utilityFunctions.h"
#include "readAuAuFile.C"

//Functions                                                 
struct EventType {

  Double_t minVz;
  Double_t maxVz;
  Double_t minVr;
  Double_t maxVr;

  Double_t minY;
  Double_t maxY;
  Double_t minmTm0;
  Double_t maxmTm0;

  Double_t yBinWidth;
  Double_t mTm0BinWidth;

  Int_t nRapBins;
  Int_t nmTm0Bins;
};

Double_t GetRapidityRangeLow(Int_t rapidityIndex);
Double_t GetRapidityRangeHigh(Int_t rapidityIndex);
Int_t GetRapidityIndex(Double_t rapidity);
Int_t getCentBinMC(Int_t runNumber, Int_t eventNumber, std::vector <std::vector <std::vector <int> > > vCentDB);
void SetEventType(EventType *eventType, Int_t eventName );

//Main____________________________________________________________
void ProcessEmbedding(const char* MINIMCLIST, TString OUTPUTFILE, TString CENTDB,
		      Double_t ENERGY, Int_t PIDINTEREST, Int_t EVENTNAME){

  //Event Counters
  Long64_t totalEvents(0), usedEvents(0), unusedEvents(0);

  //Define the Number of Centrality Bins
  const int nCentBins = 7;

	//Read in centrality database
	std::vector <std::vector <std::vector<int> > > vCentDB = readAuAuFile(CENTDB); 

  //Create an Event and Set its type        
  EventType event;
  SetEventType(&event,EVENTNAME);
  const char *energy = Form("#sqrt{s_{NN}} = %g GeV",ENERGY);
  const char *pidSymbol = GetParticleSymbol(PIDINTEREST).Data();

  //---Add the files from the miniMCList to the Chain---
     
  //Open the List of miniMC Files       
  ifstream miniMCList (MINIMCLIST);
  if (!miniMCList.is_open()){
    cout <<"MiniMCList not Open!" <<endl;
    exit (EXIT_FAILURE);
  }

  //Read All the Lines of the miniMCList File and Add them to the Chain    
  string miniMCFile;
  TChain *fileChain = new TChain("StMiniMcTree");

    
  while (miniMCList.good()){
    getline(miniMCList, miniMCFile);
    fileChain->Add(miniMCFile.c_str());
  };

  //Close the MiniMCList File  
  miniMCList.close();

  //Create the OutputFile   
  TFile *outFile = new TFile(OUTPUTFILE,"RECREATE");

  //---Set All the Active Branch Addresses---

  //The Event Level Variables             
  Long64_t runNumber(0), eventNumber(0);
  Int_t nEmbTracks(0), nMatchTracks(0), nSplitTracks(0);
  Float_t embVertexX(0), embVertexY(0), embVertexZ(0);
  fileChain->SetBranchAddress("mRunId",&runNumber);
  fileChain->SetBranchAddress("mEventId",&eventNumber);
  fileChain->SetBranchAddress("mNMcGlobal",&nEmbTracks); //mNMcGlobal = # of primary mc tracks (mNMcTrack is number of initial/global mc tracks)
  fileChain->SetBranchAddress("mNMatchedPair",&nMatchTracks);
  fileChain->SetBranchAddress("mNSplitPair",&nSplitTracks);
  fileChain->SetBranchAddress("mMcVertexX",&embVertexX);
  fileChain->SetBranchAddress("mMcVertexY",&embVertexY);
  fileChain->SetBranchAddress("mMcVertexZ",&embVertexZ);

  //Embedded Track Variables              
  const int nArr = 200;
  Float_t embTrackPt[nArr], embTrackPz[nArr];
  Float_t embTrackEta[nArr], embTrackPhi[nArr];
  UShort_t embTrackGeantID[nArr], embTrackParentGeantID[nArr];
  Short_t embTrackNHits[nArr];
  fileChain->SetBranchAddress("mMcTracks.mPtMc",embTrackPt);
  fileChain->SetBranchAddress("mMcTracks.mPzMc",embTrackPz);
  fileChain->SetBranchAddress("mMcTracks.mEtaMc",embTrackEta);
  fileChain->SetBranchAddress("mMcTracks.mPhiMc",embTrackPhi);
  fileChain->SetBranchAddress("mMcTracks.mGeantId",embTrackGeantID);
  fileChain->SetBranchAddress("mMcTracks.mParentGeantId",embTrackParentGeantID);
  fileChain->SetBranchAddress("mMcTracks.mNHitMc",embTrackNHits);

  //Matched Track Variables    
  Float_t matchTrackPtEmb[nArr], matchTrackPzEmb[nArr];
  Float_t matchTrackPtReco[nArr], matchTrackPzReco[nArr];
  UShort_t matchTrackGeantID[nArr], matchTrackParentGeantID[nArr];
  Short_t matchTrackNHits[nArr], matchTrackNFitPts[nArr], matchTrackNPossPts[nArr];
  Float_t matchTrackEtaEmb[nArr], matchTrackPhiEmb[nArr];
  Float_t matchTrackEtaReco[nArr], matchTrackPhiReco[nArr];
  Float_t matchTrackFlag[nArr], matchTrackDCAGl[nArr];
  Float_t matchTrackdEdx[nArr];
  Short_t matchTrackNHitsdEdx[nArr];
  fileChain->SetBranchAddress("mMatchedPairs.mPtMc",matchTrackPtEmb);
  fileChain->SetBranchAddress("mMatchedPairs.mPzMc",matchTrackPzEmb);
  fileChain->SetBranchAddress("mMatchedPairs.mPtPr",matchTrackPtReco);
  fileChain->SetBranchAddress("mMatchedPairs.mPzPr",matchTrackPzReco);
  fileChain->SetBranchAddress("mMatchedPairs.mGeantId",matchTrackGeantID);
  fileChain->SetBranchAddress("mMatchedPairs.mParentGeantId",matchTrackParentGeantID);
  fileChain->SetBranchAddress("mMatchedPairs.mFitPts",matchTrackNFitPts);
  fileChain->SetBranchAddress("mMatchedPairs.mNPossible",matchTrackNPossPts);
  fileChain->SetBranchAddress("mMatchedPairs.mAllPts",matchTrackNHits);
  fileChain->SetBranchAddress("mMatchedPairs.mEtaMc",matchTrackEtaEmb);
  fileChain->SetBranchAddress("mMatchedPairs.mPhiMc",matchTrackPhiEmb);
  fileChain->SetBranchAddress("mMatchedPairs.mEtaPr",matchTrackEtaReco);
  fileChain->SetBranchAddress("mMatchedPairs.mPhiPr",matchTrackPhiReco);
  fileChain->SetBranchAddress("mMatchedPairs.mFlag",matchTrackFlag);
  fileChain->SetBranchAddress("mMatchedPairs.mDcaGl",matchTrackDCAGl);
  fileChain->SetBranchAddress("mMatchedPairs.mDedxPts",matchTrackNHitsdEdx);
  fileChain->SetBranchAddress("mMatchedPairs.mDedx",matchTrackdEdx);

  //Split Track Variables
  Float_t splitTrackEtaEmb[nArr], splitTrackPtEmb[nArr];
  Float_t splitTrackEtaReco[nArr], splitTrackPtReco[nArr];
  UShort_t splitTrackGeantID[nArr], splitTrackParentGeantID[nArr];
  Short_t splitTrackNHits[nArr], splitTrackNFitPts[nArr], splitTrackNPossPts[nArr];
  Float_t splitTrackFlag[nArr], splitTrackDCAGl[nArr];
  Short_t splitTrackNHitsdEdx[nArr];
  fileChain->SetBranchAddress("mSplitPairs.mEtaMc",splitTrackEtaEmb);
  fileChain->SetBranchAddress("mSplitPairs.mPtMc",splitTrackPtEmb);
  fileChain->SetBranchAddress("mSplitPairs.mEtaPr",splitTrackEtaReco);
  fileChain->SetBranchAddress("mSplitPairs.mPtPr",splitTrackPtReco);
  fileChain->SetBranchAddress("mSplitPairs.mGeantId",splitTrackGeantID);
  fileChain->SetBranchAddress("mSplitPairs.mParentGeantId",splitTrackParentGeantID);
  fileChain->SetBranchAddress("mSplitPairs.mFitPts",splitTrackNFitPts);
  fileChain->SetBranchAddress("mSplitPairs.mNPossible",splitTrackNPossPts);
  fileChain->SetBranchAddress("mSplitPairs.mAllPts",splitTrackNHits);
  fileChain->SetBranchAddress("mSplitPairs.mFlag",splitTrackFlag);
  fileChain->SetBranchAddress("mSplitPairs.mDcaGl",splitTrackDCAGl);
  fileChain->SetBranchAddress("mSplitPairs.mDedxPts",splitTrackNHitsdEdx);


  //---Create Histograms----

  //QA Histograms for Embedded Events Before Any Cuts
  TH1F *embZVertexHistoNoCuts;
  TH2F *embXYVertexHistoNoCuts;

  embZVertexHistoNoCuts = new TH1F("embZVertexHistoNoCuts",Form("V_{z} %s %s (No Cuts);z Vertex (cm)",pidSymbol,energy),
				   100,event.minVz-10,event.maxVz+10);
  embXYVertexHistoNoCuts = new TH2F("embXYVertexHistoNoCuts",Form("V_{x},V_{y} %s %s (No Cuts);x Vertex (cm);y Vertex (cm)",
								  pidSymbol,energy),100,-6,6,100,-6,6);

  //QA Histograms for Embedded Event Quantities
  TH1F *embZVertexHisto;
  TH1F *nEmbTrackHisto, *nMatchTrackHisto; 
  TH1F *centralityHisto;
  TH2F *embXYVertexHisto;

  nEmbTrackHisto   = new TH1F("nEmbTrackHisto",Form("nEmbeddedTracks %s %s;nEmbTracks",pidSymbol,energy),
			      nArr,0,nArr);
  nMatchTrackHisto = new TH1F("nMatchTrackHisto",Form("nMatchedTracks %s %s;nMatchTracks",pidSymbol,energy),
			      20,0,20);
  centralityHisto  = new TH1F("centralityHisto",Form("Centrality %s %s;centrality",pidSymbol,energy),
			      10,0,10);
  embZVertexHisto  = new TH1F("embZVertexHisto",Form("V_{z} %s %s;z Vertex (cm)",pidSymbol,energy),
			      100,event.minVz-10,event.maxVz+10);
  embXYVertexHisto = new TH2F("embXYVertexHisto",Form("V_{x},V_{y} %s %s;x Vertex (cm);y Vertex (cm)",
						      pidSymbol,energy),
			      100,-6,6,100,-6,6);

  //QA Histograms for Embedded Track Quantities
  TH2F *embTrackEtaPhiHisto, *embTrackRapidityPtHisto;
  TH1F *embTrackEtaHisto, *embTrackPhiHisto, *embTrackRapidityHisto, *embTrackPtHisto, *embTrackmTm0Histo;
  TH3F *embTrackRapidityPtPhiHisto, *embTrackRapidityPtNHitsHisto, *embTrackEtaPtPhiHisto;

  embTrackEtaPhiHisto     = new TH2F("embTrackEtaPhiHisto",
				     Form("EmbTrack #eta Vs. #phi %s %s;#eta;#phi",pidSymbol,energy),
				     100,-2,2,100,-3.2,3.2);
  embTrackRapidityPtHisto = new TH2F("embTrackRapidityPtHisto",
				     Form("EmbTrackRapidity Vs p_{T} %s %s;y_{%s};p_{T} (GeV)",
					  pidSymbol,energy,pidSymbol),
				     100,-2,2,100,0,2.0);
  embTrackEtaHisto        = new TH1F("embTrackEtaHisto",
				     Form("#eta %s %s;#eta",pidSymbol,energy),
				     100,-2,2);
  embTrackPhiHisto        = new TH1F("embTrackPhiHisto",
				     Form("EmbTrack #phi %s %s;#phi",pidSymbol,energy),
				     100,-4.0,4.0);
  embTrackRapidityHisto   = new TH1F("embTrackRapidityHisto",
				     Form("EmbTrack Rapidity %s %s;y_{%s}",
					  pidSymbol,energy,pidSymbol),
				     100,-2,2);
  embTrackPtHisto         = new TH1F("embTrackPtHisto",
				     Form("EmbTrack p_{T} %s %s;p_{T} (GeV)",pidSymbol,energy),
				     100,0,2.0);
  embTrackmTm0Histo       = new TH1F("embTrackmTm0Histo",
				     Form("EmbTrack m_{T}-m_{%s} %s %s;m_{T}-m_{%s} (GeV)",
					  pidSymbol,pidSymbol,energy,pidSymbol),100,0,2.0);
  embTrackRapidityPtPhiHisto = new TH3F("embTrackRapidityPtPhiHisto",
					Form("EmbTrack m_{T}-m_{%s} %s %s;y_{%s};p_{T} (GeV);#phi",
					     pidSymbol,pidSymbol,energy,pidSymbol),
					event.nRapBins,event.minY,event.maxY,10,0,2.0,60,-3.5,3.5);
  embTrackRapidityPtNHitsHisto = new TH3F("embTrackRapidityPtNHitsHisto",
					  Form("EmbTrack Rapidity Vs. p_{T} %s %s;y_{%s};p_{T} (GeV);NHits",
					       pidSymbol,energy,pidSymbol),
					  event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,50);
  embTrackEtaPtPhiHisto        = new TH3F("embTrackEtaPtPhiHisto",
					  Form("EmbTrack #eta Vs. p_{T} %s %s;#eta;p_{T} (GeV);#phi",
                 pidSymbol,energy),
            event.nRapBins,event.minY,event.maxY,10,0,2.0,60,-3.5,3.5);

  //QA Histograms for the Matched Track Quantities                                                            
  TH2F *matchTrackEtaPhiHisto, *matchTrackRapidityPtHisto;
  TH1F *matchTrackEtaHisto, *matchTrackPhiHisto, *matchTrackRapidityHisto, *matchTrackPtHisto, *matchTrackmTm0Histo;
  TH3F *matchTrackRapidityPtPhiHisto, *matchTrackRapidityPtNHitsHisto;
  TH3F *matchTrackRapidityPtNHitsFitHisto, *matchTrackRapidityPtNHitsPossHisto, *matchTrackRapidityPtNHitsFracHisto;
  TH3F *matchTrackRapidityPtNHitsdEdxHisto, *matchTrackRapidityPtGlobalDCAHisto, *matchTrackEtaPtPhiHisto;
  TH3F *matchTrackEtaPembPrecoHisto, *matchTrackEtaPtembPtrecoHisto, *matchTrackEtaRapidityembRapidityrecoHisto;
  TH3F *matchTrackEtaPtdEdxHisto;

  matchTrackEtaPhiHisto     = new TH2F("matchTrackEtaPhiHisto",
				       Form("MatchedTrack #eta Vs. #phi %s %s;#eta;#phi",pidSymbol,energy),
				       100,-2,2,100,-3.2,3.2);
  matchTrackRapidityPtHisto = new TH2F("matchTrackRapidityPtHisto",
				       Form("MatchedTrack p_{T} %s %s;y_{%s};p_{T}",pidSymbol,energy,pidSymbol),
				       100,-2,2,100,0,2.0);
  matchTrackEtaHisto        = new TH1F("matchTrackEtaHisto",
				       Form("MatchedTrack #eta %s %s;#eta",pidSymbol,energy),
				       100,-2,2);
  matchTrackPhiHisto        = new TH1F("matchTrackPhiHisto",
				       Form("MatchedTrack #phi %s %s;#phi",pidSymbol,energy),
				       100,-3.2,3.2);
  matchTrackRapidityHisto   = new TH1F("matchTrackRapidityHisto",
				       Form("MatchedTrack Rapidity %s %s;y_{%s}",pidSymbol,energy,pidSymbol),
				       100,-2,2);
  matchTrackPtHisto         = new TH1F("matchTrackPtHisto",
				       Form("Matched Track p_{T} %s %s;p_{T} (GeV)",pidSymbol,energy),
				       100,0,2.0);
  matchTrackmTm0Histo       = new TH1F("matchTrackmTm0Histo",
				       Form("Matched Track m_{T}-m_{0} %s %s;m_{T}-m_{%s}",pidSymbol,energy,pidSymbol),
				       100,0,2.0);
  matchTrackRapidityPtPhiHisto = new TH3F("matchTrackRapidityPtPhiHisto",
					  Form("Matched Track Rapidity Vs. p_{T};y_{%s};p_{T} (GeV);#phi",
					       pidSymbol),
					  event.nRapBins,event.minY,event.maxY,10,0,2.0,60,-3.5,3.5);
  matchTrackRapidityPtNHitsHisto = new TH3F("matchTrackRapidityPtNHitsHisto",
					    Form("Matched Track Rapidity Vs. p_{T} Vs. nHits;y_{%s};p_{T} (GeV);NHits",
						 pidSymbol),
					    event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,50);
  matchTrackRapidityPtNHitsFitHisto = new TH3F("matchTrackRapidityPtNHitsFitHisto",
					       Form("Matched Track Rapidity Vs. p_{T} Vs nHitsFit;y_{%s};p_{T} (GeV);NHitsFit",
						    pidSymbol),
					       event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,50);
  matchTrackRapidityPtNHitsPossHisto = new TH3F("matchTrackRapidityPtNHitsPossHisto",
						Form("Matched Track Rapidity Vs. p_{T} Vs. nHitsPoss;y_{%s};p_{T} (GeV);NHitsPoss",
						     pidSymbol),
						event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,50);
  matchTrackRapidityPtNHitsFracHisto = new TH3F("matchTrackRapidityPtNHitsFracHisto",
						Form("Matched Track Rapidity Vs. p_{T} Vs. nHitsFrac;y_{%s};p_{T} (GeV);NHitsFrac",
						     pidSymbol),
						event.nRapBins,event.minY,event.maxY,10,0,2.0,100,0,1);
  matchTrackRapidityPtNHitsdEdxHisto = new TH3F("matchTrackRapidityPtNHitsdEdxHisto",
						Form("Matched Track Rapidity Vs. p_{T} Vs. nHitsdEdx;y_{%s};p_{T} (GeV);NHitsdEdx",
                                                     pidSymbol),
                                                event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,50);
  matchTrackRapidityPtGlobalDCAHisto = new TH3F("matchTrackRapidityPtGlobalDCAHisto",
						Form("Matched Track Rapidity Vs. p_{T} Vs. GlobalDCA (cm);y_{%s};p_{T} (GeV);GlobalDCA (cm)",
                                                     pidSymbol),
                                                event.nRapBins,event.minY,event.maxY,10,0,2.0,50,0,5);
  matchTrackEtaPtPhiHisto            = new TH3F("matchTrackEtaPtPhiHisto",
					      "Matched Track #eta Vs. p_{T} Vs. #phi;#eta;p_{T} (GeV);#phi",
						event.nRapBins,event.minY,event.maxY,10,0,2.0,60,-3.5,3.5);

  matchTrackEtaPembPrecoHisto        = new TH3F("matchTrackEtaPembPrecoHisto",
						"Matched Track #eta^{Emb} Vs. p^{Emb} Vs. p^{Reco};#eta^{Emb};|p^{Emb}| (GeV);|p^{Reco}| (GeV)",
						event.nRapBins,event.minY,event.maxY,100,0,2.0,100,0,2.0);
  matchTrackEtaPtembPtrecoHisto        = new TH3F("matchTrackEtaPtembPtrecoHisto",
						  "Matched Track #eta^{Emb} Vs. p_{T}^{Emb} Vs. p_{T}^{Reco};#eta^{Emb};p_{T}^{Emb} (GeV);p_{T}^{Reco} (GeV)",                                                
						  event.nRapBins,event.minY,event.maxY,100,0,2.0,100,0,2.0);
  matchTrackEtaRapidityembRapidityrecoHisto        = new TH3F("matchTrackEtaRapidityEmbRapidityRecoHisto",
							      Form("Matched Track #eta^{Emb} Vs. p_{Emb} Vs. p_{Reco};#eta^{Emb};y_{%s}^{Emb};y_{%s}^{Reco}",
								   pidSymbol,pidSymbol),
							      event.nRapBins,event.minY,event.maxY,100,event.minY,event.maxY,100,event.minY,event.maxY);
  matchTrackEtaPtdEdxHisto = new TH3F("matchTrackEtaPtdEdxHisto",
				      "MatchTrack #eta^{Emb} Vs. p_{T}^{Emb} Vs. dEdx;#eta^{Emb};p_{T}^{Emb} (GeV);dE/dx (KeV/cm)",
				      event.nRapBins,event.minY,event.maxY,10,0,2.0,100,0,10);

  //Split Track Histograms
  TH2F *splitTrackEtaPtHisto;

  splitTrackEtaPtHisto = new TH2F("splitTrackEtaPtHisto",
				  Form("Split Track #eta^{Emb} Vs. p_{T}^{Emb} %s;#eta^{Emb};p_{T} (GeV)",
				       pidSymbol),
				  event.nRapBins,event.minY,event.maxY,10,0,2.0);

  //Efficiency Related Histograms
  std::vector<std::vector<TH1F *> > embTrackHisto(nCentBins,vector<TH1F *>(event.nRapBins,(TH1F *)NULL));
  std::vector<std::vector<TH1F *> > matchTrackHisto(nCentBins,vector<TH1F *>(event.nRapBins,(TH1F *)NULL));
  for (Int_t centIndex=0; centIndex<nCentBins; centIndex++){
		for (Int_t rapIndex=0; rapIndex<event.nRapBins; rapIndex++){
		  embTrackHisto[centIndex][rapIndex] = new TH1F("","",200,0,2.0);
			embTrackHisto.at(centIndex).at(rapIndex)->SetName(Form("embTrackHisto_Cent%d_yIndex%d",centIndex,rapIndex));
			embTrackHisto.at(centIndex).at(rapIndex)->SetTitle(Form("EmbTracks m_{T}-m_{%s} %s;(m_{T}-m_{%s})^{Emb} (GeV);Tracks", pidSymbol,pidSymbol,pidSymbol));
			matchTrackHisto[centIndex][rapIndex] = new TH1F("","",200,0,2.0);
      matchTrackHisto.at(centIndex).at(rapIndex)->SetName(Form("matchTrackHisto_Cent%d_yIndex%d",centIndex,rapIndex));
			matchTrackHisto.at(centIndex).at(rapIndex)->SetTitle(Form("MatchedTracks Rapidity Vs. m_{T}-m_{%s} %s;(m_{T}-m_{%s})^{Emb} (GeV);Tracks", pidSymbol,pidSymbol,pidSymbol));
  	}
	}

  //Energy Loss Related Histograms
  std::vector< TH3F *> pTLossHisto (nCentBins,(TH3F *)NULL);
  std::vector< TH3F *> rapidityLossHisto (nCentBins,(TH3F *)NULL);
  for (Int_t centIndex=0; centIndex<nCentBins; centIndex++){
    pTLossHisto[centIndex] = new TH3F(Form("pTLossHisto_Cent%d",centIndex),
				      Form("p_{T} Loss, %s;y_{%s}^{Reco};p_{T}^{Reco} (GeV);p_{T}^{Reco}-p_{T}^{Emb} (GeV)",
					   pidSymbol,pidSymbol),
				      event.nRapBins,event.minY,event.maxY,50,0,2.0,100,-.1,.1);
    rapidityLossHisto[centIndex] = new TH3F(Form("rapidityLossHisto_Cent%d",centIndex),
					    Form("Rapidity Loss %s;y_{%s}^{Reco};p_{T}^{Reco} (GeV);y_{%s}^{Reco}-y_{%s}^{Emb} (GeV)",
						 pidSymbol,pidSymbol,pidSymbol,pidSymbol),
					    event.nRapBins,event.minY,event.maxY,50,0,2.0,100,-.1,.1);
  }

  //---Loop Over the Entries of the Chain---
  Long64_t nEntries = fileChain->GetEntries();
  for (Long64_t chainIndex=0; chainIndex<nEntries; chainIndex++){

    cout <<chainIndex <<"/" <<nEntries <<"\n";
    totalEvents++;
    
    //Reset All Arrays to Zero                                                                          
    for (Int_t i=0; i<nArr; i++){
      embTrackPt[i]=embTrackPz[i]=embTrackEta[i]=embTrackPhi[i]=embTrackGeantID[i] = 0;
      embTrackParentGeantID[i]=embTrackNHits[i] = 0;

      matchTrackPtEmb[i]=matchTrackPzEmb[i]=matchTrackPtReco[i]=matchTrackPzReco[i]=0;
      matchTrackGeantID[i]=matchTrackParentGeantID[i]=0;
      matchTrackNHits[i]=matchTrackNFitPts[i]=matchTrackNPossPts[i]=0;
      matchTrackEtaEmb[i]=matchTrackPhiEmb[i]=matchTrackEtaReco[i]=matchTrackPhiReco[i]=0;
      matchTrackFlag[i]=matchTrackDCAGl[i]=matchTrackNHitsdEdx[i]=matchTrackdEdx[i] = 0;

      splitTrackEtaEmb[i]=splitTrackPtEmb[i]=splitTrackEtaReco[i]=splitTrackPtReco[i]=0;
      splitTrackGeantID[i]=splitTrackParentGeantID[i]=0;
      splitTrackNHits[i]=splitTrackNFitPts[i]=splitTrackNPossPts[i]=0;
      splitTrackFlag[i]=splitTrackDCAGl[i]=splitTrackNHitsdEdx[i]=0;


    }

    //Get the Entry of the fileChain                                                                    
    fileChain->GetEntry(chainIndex);
    
    if (nEmbTracks > nArr){
      cout <<"The Number of Embedded Tracks is larger than the Array length!" <<endl;
      cout <<"nEmbeddedTracks: " <<nEmbTracks <<" nArr: " <<nArr <<endl;
      exit (EXIT_FAILURE);
    }

    //Fill The No Cut Histograms
    embZVertexHistoNoCuts->Fill(embVertexZ);
    embXYVertexHistoNoCuts->Fill(embVertexX,embVertexY);

    //Get the Centrality Bin of the Event
    Int_t centralityBin = getCentBinMC(runNumber, eventNumber, vCentDB);
		if (centralityBin == -999) continue; //exclude non-index-0 vertices
		if (centralityBin == -2) continue; //exclude pileUp events
		if (centralityBin == -1) centralityBin = 6; //set events with centrality class > 30% to all be in last bin

    //Fill The Event Level Histograms                                                                   
    nEmbTrackHisto->Fill(nEmbTracks);
    nMatchTrackHisto->Fill(nMatchTracks);
    centralityHisto->Fill(centralityBin);
    embZVertexHisto->Fill(embVertexZ);
    embXYVertexHisto->Fill(embVertexX,embVertexY);

    //-->Loop Over the Embedded Tracks
    for (Int_t embTrackIndex=0; embTrackIndex<nEmbTracks; embTrackIndex++){

      //Make Sure the Track is an embedded track and that it has the right Geant PID                    
      if (embTrackGeantID[embTrackIndex] != GetGeantID(PIDINTEREST) || 
	  embTrackParentGeantID[embTrackIndex] != 0)
        continue;

      //Compute the Tracks Rapidity                                                                     
      Double_t embTrackRapidity = ComputeRapidity(embTrackPt[embTrackIndex],embTrackPz[embTrackIndex],
                                                  GetParticleMass(PIDINTEREST));

			Int_t embTrackRapidityIndex = GetRapidityIndex(embTrackRapidity);

      //Compute the Track's mTm0                                                                        
      Double_t embTrackmTm0 = ComputemTm0(embTrackPt[embTrackIndex],PIDINTEREST);

      //Fill the Embedded Track QA Histograms
      embTrackEtaPhiHisto->Fill(embTrackEta[embTrackIndex],embTrackPhi[embTrackIndex]);
      embTrackRapidityPtHisto->Fill(embTrackRapidity,embTrackPt[embTrackIndex]);
      embTrackEtaHisto->Fill(embTrackEta[embTrackIndex]);
      embTrackPhiHisto->Fill(embTrackPhi[embTrackIndex]);
      embTrackRapidityHisto->Fill(embTrackRapidity);
      embTrackPtHisto->Fill(embTrackPt[embTrackIndex]);
      embTrackmTm0Histo->Fill(embTrackmTm0);
      embTrackRapidityPtPhiHisto->Fill(embTrackRapidity,embTrackPt[embTrackIndex],embTrackPhi[embTrackIndex]);
      embTrackRapidityPtNHitsHisto->Fill(embTrackRapidity,embTrackPt[embTrackIndex],embTrackNHits[embTrackIndex]);
      embTrackEtaPtPhiHisto->Fill(embTrackEta[embTrackIndex],embTrackPt[embTrackIndex],embTrackPhi[embTrackIndex]);

      //Make Sure the Embedded Track is in the Defined Range
      if (embTrackRapidity < event.minY || embTrackRapidity > event.maxY)
	continue;

      //Fill the Efficiency Related Histogram
      embTrackHisto.at(centralityBin).at(embTrackRapidityIndex)->Fill(embTrackmTm0);

    }//End Loop Over Embedded Tracks
    
    //-->Loop Over Split Tracks
    for (Int_t splitTrackIndex=0; splitTrackIndex<nSplitTracks; splitTrackIndex++){

      //Make Sure the Track is an embedded track and that it has the right Geant PID
      if (splitTrackGeantID[splitTrackIndex] != GetGeantID(PIDINTEREST) ||
          splitTrackParentGeantID[splitTrackIndex] != 0)
        continue;

      //**************************************************************
      //TRACK QUALITY CUTS USED IN FINAL ANALYSIS
      //*************************************************************** 
      if (splitTrackNFitPts[splitTrackIndex] < 10 || splitTrackNHitsdEdx[splitTrackIndex] <= 0) {continue;}
      if (splitTrackNFitPts[splitTrackIndex] / (Float_t)splitTrackNPossPts[splitTrackIndex] < .52) {continue;}

      //Fill The SplitTrack Histograms
      splitTrackEtaPtHisto->Fill(splitTrackEtaEmb[splitTrackIndex],splitTrackPtEmb[splitTrackIndex]);

    }

    //-->Loop Over the Matched Tracks
    for (Int_t matchTrackIndex=0; matchTrackIndex<nMatchTracks; matchTrackIndex++){

      //Make Sure the Track is an embedded track and that it has the right Geant PID                    
      if (matchTrackGeantID[matchTrackIndex] != GetGeantID(PIDINTEREST) || 
	  matchTrackParentGeantID[matchTrackIndex] != 0)
        continue;

      //***************************************************************                                 
      //TRACK QUALITY CUTS USED IN FINAL ANALYSIS                                               
      //***************************************************************                                
      if (matchTrackNFitPts[matchTrackIndex] < 10 || matchTrackNHitsdEdx[matchTrackIndex] < 1) {continue;}
      if (matchTrackNFitPts[matchTrackIndex] / (Float_t)matchTrackNPossPts[matchTrackIndex] < .52) {continue;}

      //Compute the Rapidity of The Track                                                               
      Double_t matchTrackRapidityEmb = ComputeRapidity(matchTrackPtEmb[matchTrackIndex],
                                                       matchTrackPzEmb[matchTrackIndex],
                                                       GetParticleMass(PIDINTEREST));
      Double_t matchTrackRapidityReco= ComputeRapidity(matchTrackPtReco[matchTrackIndex],
                                                       matchTrackPzReco[matchTrackIndex],
                                                       GetParticleMass(PIDINTEREST));

			Int_t matchTrackRapidityIndex = GetRapidityIndex(matchTrackRapidityEmb);

      //Compute the mTm0 Of the Track                                                                   
      Double_t matchTrackmTm0Emb = ComputemTm0(matchTrackPtEmb[matchTrackIndex],PIDINTEREST);
      Double_t matchTrackmTm0Reco = ComputemTm0(matchTrackPtReco[matchTrackIndex],PIDINTEREST);

      //Fill the Match Track QA Histograms                                                              
      matchTrackEtaPhiHisto->Fill(matchTrackEtaReco[matchTrackIndex],matchTrackPhiReco[matchTrackIndex]);
      matchTrackRapidityPtHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex]);
      matchTrackEtaHisto->Fill(matchTrackEtaReco[matchTrackIndex]);
      matchTrackPhiHisto->Fill(matchTrackPhiReco[matchTrackIndex]);
      matchTrackRapidityHisto->Fill(matchTrackRapidityReco);
      matchTrackPtHisto->Fill(matchTrackPtReco[matchTrackIndex]);
      matchTrackmTm0Histo->Fill(matchTrackmTm0Reco);
      
      matchTrackRapidityPtPhiHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					 matchTrackPhiReco[matchTrackIndex]);
      matchTrackRapidityPtNHitsHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					   matchTrackNHits[matchTrackIndex]);
      matchTrackRapidityPtNHitsFitHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					      matchTrackNFitPts[matchTrackIndex]);
      matchTrackRapidityPtNHitsPossHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					       matchTrackNPossPts[matchTrackIndex]);
      matchTrackRapidityPtNHitsFracHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					       matchTrackNFitPts[matchTrackIndex]/(Double_t)matchTrackNPossPts[matchTrackIndex]);
      matchTrackRapidityPtNHitsdEdxHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					       matchTrackNHitsdEdx[matchTrackIndex]);
      matchTrackRapidityPtGlobalDCAHisto->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					       matchTrackDCAGl[matchTrackIndex]);
      matchTrackEtaPtPhiHisto->Fill(matchTrackEtaReco[matchTrackIndex],matchTrackPtReco[matchTrackIndex],
				    matchTrackPhiReco[matchTrackIndex]);
      matchTrackEtaPembPrecoHisto->Fill(matchTrackEtaEmb[matchTrackIndex],
					sqrt(pow(matchTrackPtEmb[matchTrackIndex],2)+pow(matchTrackPzEmb[matchTrackIndex],2)),
					sqrt(pow(matchTrackPtReco[matchTrackIndex],2)+pow(matchTrackPzReco[matchTrackIndex],2)));
      matchTrackEtaPtembPtrecoHisto->Fill(matchTrackEtaEmb[matchTrackIndex],matchTrackPtEmb[matchTrackIndex],
					  matchTrackPtReco[matchTrackIndex]);
      matchTrackEtaRapidityembRapidityrecoHisto->Fill(matchTrackEtaEmb[matchTrackIndex],matchTrackRapidityEmb,
						      matchTrackRapidityReco);
      matchTrackEtaPtdEdxHisto->Fill(matchTrackEtaEmb[matchTrackIndex],matchTrackPtEmb[matchTrackIndex],
				     matchTrackdEdx[matchTrackIndex]*pow(10.,6));
      
      //Make Sure that the Rapidity of the Track is in the Defined Range
      if (matchTrackRapidityEmb < event.minY || matchTrackRapidityEmb > event.maxY)
	continue;

      //Fill the Efficiency Related Histograms
      matchTrackHisto.at(centralityBin).at(matchTrackRapidityIndex)->Fill(matchTrackmTm0Emb);

      //Fill the Energy Loss Histograms
      pTLossHisto[centralityBin]->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
				       matchTrackPtReco[matchTrackIndex]-matchTrackPtEmb[matchTrackIndex]);
      rapidityLossHisto[centralityBin]->Fill(matchTrackRapidityReco,matchTrackPtReco[matchTrackIndex],
					     matchTrackRapidityReco-matchTrackRapidityEmb);

    }//End Loop Over Matched Tracks

    usedEvents++;
  }//End Loop Over chainIndex

  //---Save Everything---
  outFile->mkdir("QANoCuts");
  outFile->mkdir("UnusableEvents");
  outFile->mkdir("EventQAPlots");
  outFile->mkdir("EmbeddedTrackQAPlots");
  outFile->mkdir("MatchedTrackQAPlots");
  outFile->mkdir("SplitTrackQAPlots");
  outFile->mkdir("EfficiencyHistograms");
  outFile->mkdir("EnergyLossHistograms");
  
  //Save the No Cuts Plots
  outFile->cd("QANoCuts");
  embZVertexHistoNoCuts->Write();
  embXYVertexHistoNoCuts->Write();

  //Save the QA Plots
  outFile->cd();
  outFile->cd("EventQAPlots");
  nEmbTrackHisto->Write();
  nMatchTrackHisto->Write();
  centralityHisto->Write();
  embZVertexHisto->Write();
  embXYVertexHisto->Write();

  outFile->cd();
  outFile->cd("EmbeddedTrackQAPlots");
  embTrackEtaPhiHisto->Write();
  embTrackRapidityPtHisto->Write();
  embTrackEtaHisto->Write();
  embTrackPhiHisto->Write();
  embTrackRapidityHisto->Write();
  embTrackPtHisto->Write();
  embTrackmTm0Histo->Write();
  embTrackRapidityPtPhiHisto->Write();
  embTrackRapidityPtNHitsHisto->Write();
  embTrackEtaPtPhiHisto->Write();

  outFile->cd();
  outFile->cd("MatchedTrackQAPlots");
  matchTrackEtaPhiHisto->Write();
  matchTrackRapidityPtHisto->Write();
  matchTrackEtaHisto->Write();
  matchTrackPhiHisto->Write();
  matchTrackRapidityHisto->Write();
  matchTrackPtHisto->Write();
  matchTrackmTm0Histo->Write();
  matchTrackRapidityPtPhiHisto->Write();
  matchTrackRapidityPtNHitsHisto->Write();
  matchTrackRapidityPtNHitsFitHisto->Write();
  matchTrackRapidityPtNHitsPossHisto->Write();
  matchTrackRapidityPtNHitsFracHisto->Write();
  matchTrackRapidityPtNHitsdEdxHisto->Write();
  matchTrackRapidityPtGlobalDCAHisto->Write();
  matchTrackEtaPtPhiHisto->Write();
  matchTrackEtaPembPrecoHisto->Write();
  matchTrackEtaPtembPtrecoHisto->Write();
  matchTrackEtaRapidityembRapidityrecoHisto->Write();
  matchTrackEtaPtdEdxHisto->Write();

  outFile->cd();
  outFile->cd("SplitTrackQAPlots");
  splitTrackEtaPtHisto->Write();

  //Save the Efficiency Histogram
  outFile->cd();
  outFile->cd("EfficiencyHistograms");
	for (Int_t centIndex=0; centIndex<nCentBins; centIndex++){
		for (Int_t rapIndex=0; rapIndex<event.nRapBins; rapIndex++){
			embTrackHisto.at(centIndex).at(rapIndex)->Write();
			matchTrackHisto.at(centIndex).at(rapIndex)->Write();
		}
	}

  //Save the Energy Loss Histograms
  outFile->cd();
  outFile->cd("EnergyLossHistograms");
	for (Int_t centIndex=0; centIndex<nCentBins; centIndex++){
		pTLossHisto[centIndex]->Write();
		rapidityLossHisto[centIndex]->Write();
	}

  //Close the File
  outFile->Close();

  //Print Event Statistics
  cout <<"Event Statistics: " <<endl
       <<"  Total:  " <<totalEvents <<endl
       <<"  Used:   " <<usedEvents <<endl
       <<"  Unused: " <<unusedEvents <<endl;

}

//___________________________________________________________
Double_t GetRapidityRangeLow(Int_t rapidityIndex){

  return -2.05 + (rapidityIndex * 0.1);
}

//___________________________________________________________
Double_t GetRapidityRangeHigh(Int_t rapidityIndex){

  return GetRapidityRangeLow(rapidityIndex)+0.1;
}

//___________________________________________________________
Int_t GetRapidityIndex(Double_t rapidity){

  //Make sure the value of rapidity is in the [min,max] range
  if (rapidity < -2.05 || rapidity > -0.05)
    return -1;

  //Loop through the rapidity bins and return the index
  //of the bin that this value of rapidity falls into
  for (Int_t index=0; index<20; index++){

    if (rapidity >= GetRapidityRangeLow(index) &&
  rapidity < GetRapidityRangeHigh(index))
      return index;
  }

  return -1;
}


//_______________________________________________________________                     
Int_t getCentBinMC(Int_t runNumber, Int_t eventNumber, std::vector <std::vector <std::vector <int> > > vCentDB){

	Int_t centBin(-999);
	Int_t nRunIndex = runNumber-16140033;
	Int_t nEvents = vCentDB.at(nRunIndex).size();

  for (Int_t i = 0; i<nEvents; i++){	
		if (vCentDB[nRunIndex][i][0] != runNumber){
			cout<<"ERROR: Wrong run number!";
      break;
		}
		if (eventNumber != vCentDB[nRunIndex][i][1]) continue;
    else centBin = vCentDB[nRunIndex][i][2]; 
		if (centBin != -999) break;
  }	

	return centBin;
}

//_______________________________________________________________                     
void SetEventType(EventType *eventType, Int_t eventName){

  //All Events have the same kinematic Bin Widths      
  eventType->yBinWidth = .1; 
  eventType->mTm0BinWidth = .025;

  //All Events have the same mTm0 Range                                          
  eventType->minmTm0 = 0.0;
  eventType->maxmTm0 = 1.5;
  eventType->nmTm0Bins = 200;

  if (eventName == kAuAuCenter){
    eventType->minVz = -30;
    eventType->maxVz = 30; 
    eventType->minVr = 0;
    eventType->maxVr = 2;

    eventType->minY = -1.05;
    eventType->maxY = 1.05;
    eventType->nRapBins = 21; 
  }

  else if (eventName == kAuAuDisplacedPosY){
    eventType->minVz = -200;
    eventType->maxVz = -100;
    eventType->minVr = 0;
    eventType->maxVr = 2;

    eventType->minY = -0.05;
    eventType->maxY = 1.85;
    eventType->nRapBins = 19; 
  }

  else if (eventName == kAuAuDisplacedNegY){
    eventType->minVz = 100;
    eventType->maxVz = 200;
    eventType->minVr = 0;
    eventType->maxVr = 2;

    eventType->minY = -1.85;
    eventType->maxY = 0.05;
    eventType->nRapBins = 19; 
  }

  else if (eventName == kAuAlBeampipePosY){
    eventType->minVz = -200;
    eventType->maxVz = -150;
    eventType->minVr = 2;
    eventType->maxVr = 5;

    eventType->minY = 0.05;
    eventType->maxY = 1.65;
    eventType->nRapBins = 17;
  }

  else if (eventName == kAuAlBeampipeNegY){
    eventType->minVz = 150;
    eventType->maxVz = 200;
    eventType->minVr = 2;
    eventType->maxVr = 5;

    eventType->minY = -1.65;
    eventType->maxY = 0.05;
    eventType->nRapBins = 17;
  }

  else if (eventName == kAuAuFixedTarget2014){
    eventType->minVz = 209;
    eventType->maxVz = 211;
    eventType->minVr = 0;
    eventType->maxVr = 100;

    eventType->minY = -1.42;
    eventType->maxY = -1.32;
    eventType->nRapBins = 1;

  }

  else if (eventName == kAuAuFixedTarget2015){ eventType->minVz = 210; eventType->maxVz = 212; eventType->minVr = 0;
    eventType->maxVr = 100;

    eventType->minY = -2.05;
    eventType->maxY = -0.05;
    eventType->nRapBins = 20;
    eventType->yBinWidth = 0.1;

  }

}
