#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TSystem.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TChain.h>
#include <TNtupleD.h>

#include "globalDefinitions.h"
#include "utilityFunctions.h"
#include "MiniMcReader.h"
#include "StRefMultExtendedCorr.h"
#include "CentralityDatabaseClass.h"
#include "BinningAndCuts.h"


//MAIN_________________________________________________________________________________________
void ProcessBackgroundSimulations(const char *MINIMCLIST, TString OUTPUTFILE){

  const int nCentBins(1);
  
  //Open the List of miniMC Files
  ifstream miniMCList (MINIMCLIST);
  if (!miniMCList.is_open()){
    cout <<"MiniMCList not Open!" <<endl;
    exit (EXIT_FAILURE);
  }

  //Read All the Lines of the MINIMCLIST file and add them to the chain
  string miniMCFile;
  TChain *fileChain = new TChain("StMiniMcTree");
  while (miniMCList.good()){
    getline(miniMCList, miniMCFile);
    fileChain->Add(miniMCFile.c_str());
  }

  //Close the MiniMCList File
  miniMCList.close();

  //Create the MiniMC Reader
  MiniMcReader *minimcReader = new MiniMcReader((TTree *)fileChain);
  cout <<"Created the MiniMCReader! " <<endl;
  //Create the output File
  TFile *outFile = new TFile(OUTPUTFILE,"RECREATE");

  //********** CREATE HISTOGRAMS ******************
  //QA
  TH1D *nEventsHisto = new TH1D("nEventsCentrality","Number of Events in each Centrality Bin; Centrality Bin; Counts",9,0,9);
  
  //MONTE CARLO TRACKS
  TH1D *mcTracksPidHisto = new TH1D("mcTracksPidHisto","PID of MC Tracks",51,0,51);
  std::vector < TH1D *> embTracksCentRapidityLambdaParent(nCentBins, (TH1D *) NULL);

  //MATCHED TRACKS
  TH1D *matchTracksPidHisto = new TH1D("matchTracksPidHisto","PID of Matched Tracks",51,0,51);
  TH1D *matchTracksParentPidHisto = new TH1D("matchTracksParentPidHisto","PID of Parent Matched Tracks",51,0,51);
  TH1D *matchedTracksEtaHisto = new TH1D("matchTracksEtaHisto","#eta of Matched Tracks",200,-4,4);
  TH1D *matchedTracksPhiHisto = new TH1D("matchTracksPhiHisto","#phi of Matched Tracks",200,-TMath::Pi(),TMath::Pi());
  TH2D *matchedTracksEtaPhiHisto = new TH2D("matchedTracksEtaPhiHisto","#eta Vs. #phi of Matched Tracks",200,-4,4,200,-TMath::Pi(),TMath::Pi());
  TH1D *matchedTracksRapidityLambdaParent = new TH1D("matchedTracksRapidityLambdaParent","Rapidity of Matched Tracks with #Lambda as parent",100,-5,5);
  std::vector < TH1D *> matchTracksCentPidHisto(nCentBins,(TH1D *)NULL);
  std::vector < TH1D *> matchTracksCentParentPidHisto(nCentBins,(TH1D *) NULL);
  std::vector < TH1D *> matchTracksCentTrackFlagHisto(nCentBins,(TH1D *) NULL);
  std::vector < TH1D *> matchTracksCentNHitsFitHisto(nCentBins,(TH1D *) NULL);
  std::vector < TH1D *> matchTracksCentNHitsdEdxHisto(nCentBins,(TH1D *) NULL);
  std::vector < TH1D *> matchTracksCentNHitsFracHisto(nCentBins,(TH1D *) NULL); 
  std::vector < TH1D *> matchTracksCentglDCAHisto(nCentBins, (TH1D *) NULL);
  std::vector < TH1D *> matchTracksCentRapidityLambdaParent(nCentBins, (TH1D *) NULL);
  for (unsigned int iCentBin=0; iCentBin<nCentBins; iCentBin++){
    matchTracksCentPidHisto.at(iCentBin) = new TH1D(Form("matchTracksPidHisto_Cent%02d",iCentBin),
						    Form("PID of Matched Tracks | CentBin=%02d",iCentBin),
						    51,0,51);
    matchTracksCentParentPidHisto.at(iCentBin) = new TH1D(Form("matchTracksParentPidHisto_Cent%02d",iCentBin),
							  Form("PID of Parent of Matched Tracks | CentBin=%02d",iCentBin),
							  51,0,51);
    matchTracksCentTrackFlagHisto.at(iCentBin) = new TH1D(Form("matchTracksTrackFlagHisto_Cent%02d",iCentBin),
							  Form("Track Flag of Matched Tracks | CentBin=%02d",iCentBin),
							  10000,0,10000);
    matchTracksCentNHitsFitHisto.at(iCentBin) = new TH1D(Form("matchTracksNHitsFitHisto_Cent%02d",iCentBin),
							 Form("NHits Fit of Matched Tracks | CentBin=%02d",iCentBin),
							 50,0,50);
    matchTracksCentNHitsdEdxHisto.at(iCentBin) = new TH1D(Form("matchTracksNHitsdEdxHisto_Cent%02d",iCentBin),
							  Form("NHits dEdx of Matched Tracks | CentBin=%02d",iCentBin),
							  50,0,50);
    matchTracksCentNHitsFracHisto.at(iCentBin) = new TH1D(Form("matchTracksNHitsFracHisto_Cent%02d",iCentBin),
							  Form("NHits Frac of Matched Tracks | CentBin=%02d",iCentBin),
							  50,0,1);
    matchTracksCentglDCAHisto.at(iCentBin) = new TH1D(Form("matchTracksglDCAHisto_Cent%02d",iCentBin),
						      Form("glDCA of Matched Tracks | CentBin=%02d",iCentBin),
						      1000,0,50);
    matchTracksCentRapidityLambdaParent.at(iCentBin) = new TH1D(Form("matchTracksRapidityLambdaParent_Cent%02d",iCentBin),
								Form("Rapidity of Matched Protons with #Lambda Parent | CentBin=%02d",iCentBin),
								100,-5,5);
    embTracksCentRapidityLambdaParent.at(iCentBin) = new TH1D(Form("embTracksRapidityLambdaParent_Cent%02d",iCentBin),
							      Form("Rapidity of MC Protons with #Lambda Parent | CentBin=%02d",iCentBin),
							      100,-5,5);
  }//End Loop Over Centrality Bins

  //FEED DOWN
  std::vector< std::vector < std::pair<TH3F *, TH3F*> > > feedDownHisto 
    (nCentBins, std::vector< std::pair<TH3F *, TH3F*> >
     (3, std::make_pair((TH3F *)NULL,(TH3F *)NULL)));
  for (unsigned int iCentBin=0; iCentBin<nCentBins; iCentBin++){
    for (unsigned int iSpecies=0; iSpecies<feedDownHisto.at(iCentBin).size(); iSpecies++){

      feedDownHisto.at(iCentBin).at(iSpecies).first = 
	new TH3F(Form("parentGeantIDHisto_%s_cent%02d",GetParticleName(iSpecies,-1).Data(),iCentBin),
		 Form("Parent GeantID Distribution of %s | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2}); Geant Parent ID",
		      GetParticleSymbol(iSpecies,-1).Data(),
		      iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
		      (int)GetCentralityPercent(iCentBin),
		      GetParticleSymbol(iSpecies,-1).Data(),
		      GetParticleSymbol(iSpecies,-1).Data()),
		 nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max,51,0,51);

      feedDownHisto.at(iCentBin).at(iSpecies).second =
        new TH3F(Form("parentGeantIDHisto_%s_cent%02d",GetParticleName(iSpecies,1).Data(),iCentBin),
                 Form("Parent GeantID Distribution of %s | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2}); Geant Parent ID",
                      GetParticleSymbol(iSpecies,1).Data(),
		      iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
		      (int)GetCentralityPercent(iCentBin),
		      GetParticleSymbol(iSpecies,1).Data(),
                      GetParticleSymbol(iSpecies,1).Data()),
                 nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max,51,0,51);
      
    }//End Loop Over Species
  }//End Loop Over Cent Bins

  //MUON Contamination
  std::vector< std::pair<TH2F *, TH2F *> > pionCount
    (nCentBins, std::make_pair((TH2F *)NULL,(TH2F *)NULL));
  std::vector< std::pair<TH2F *, TH2F *> > pionMuonCount
    (nCentBins, std::make_pair((TH2F *)NULL,(TH2F *)NULL));
  
  for (unsigned int iCentBin=0; iCentBin<nCentBins; iCentBin++){
    
    pionCount.at(iCentBin).first =
      new TH2F(Form("pionCount_%s_cent%02d",GetParticleName(0,-1).Data(),iCentBin),
	       Form("%s+%s Multiplicity | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2})",
		    GetParticleSymbol(PION,-1).Data(),GetParticleSymbol(MUON,-1).Data(),
		    iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
		    (int)GetCentralityPercent(iCentBin),
		    GetParticleSymbol(0,-1).Data(),GetParticleSymbol(0,-1).Data()),
	       nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max);
    
    pionMuonCount.at(iCentBin).first = 
      new TH2F(Form("muonCount_%s_cent%02d",GetParticleName(0,-1).Data(),iCentBin),
	       Form("%s Background | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2})",
		    GetParticleSymbol(8,-1).Data(),
		    iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
                    (int)GetCentralityPercent(iCentBin),
		    GetParticleSymbol(0,-1).Data(),GetParticleSymbol(0,-1).Data()),
	       nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max);

    pionCount.at(iCentBin).second =
      new TH2F(Form("pionCount_%s_cent%02d",GetParticleName(0,1).Data(),iCentBin),
               Form("%s+%s Multiplicity | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2})",
		    GetParticleSymbol(PION,1).Data(),GetParticleSymbol(MUON,1).Data(),
		    iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
                    (int)GetCentralityPercent(iCentBin),
		    GetParticleSymbol(0,1).Data(),GetParticleSymbol(0,1).Data()),
               nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max);

    pionMuonCount.at(iCentBin).second =
      new TH2F(Form("muonCount_%s_cent%02d",GetParticleName(0,1).Data(),iCentBin),
	       Form("%s Background | Cent=[%02d,%02d]%%;y_{%s}^{Reco};(m_{T}-m_{%s})^{Reco} (GeV/c^{2})",
		    GetParticleSymbol(8,1).Data(),
		    iCentBin!=nCentBins-1 ? (int)GetCentralityPercent(iCentBin+1):0,
                    (int)GetCentralityPercent(iCentBin),
		    GetParticleSymbol(0,1).Data(),GetParticleSymbol(0,1).Data()),
	       nRapidityBins,rapidityMin,rapidityMax,nmTm0Bins,mTm0Min,mTm0Max);

  }//End Loop Over Cent Bins

  
  //*********** LOOP OVER THE ENTRIES OF THE CHAIN ********************
  Long64_t nEntries = fileChain->GetEntries();
  cout <<"Number of Entries in the Chain: " <<nEntries <<endl;
  for (Long64_t iEntry=0; iEntry<nEntries; iEntry++){

    //Reset the Minimc Reader
    minimcReader->Reset();

    //Get the Entry in the Chain
    fileChain->GetEntry(iEntry);
    //cout <<"Processing Event Number: " <<iEntry <<endl;

    //Check the length of the internal arrays
    if (minimcReader->GetNEmbeddedTracks() >= minimcReader->GetNMaxEntries()){
      cout <<"NEmbTracks: " <<minimcReader->GetNEmbeddedTracks() <<" MaxEntries: " <<minimcReader->GetNMaxEntries() <<endl;
      cout <<"The number of Embedded tracks is larger than the array length!" <<endl;
      exit (EXIT_FAILURE);
    }

    //****** DETERMINE THE CENTRALITY BIN *******
    //Compute the Number of Good Matched Tracks
    int goodMatchedTracks(0);
    for (Int_t matchTrackIndex=0; matchTrackIndex<minimcReader->GetNMatchedTracks(); matchTrackIndex++){

      //Increment the number of good matched tracks
      if (IsGoodTrack(minimcReader,matchTrackIndex,"Matched"))
        goodMatchedTracks++;
    }//End Loop Over the matched Tracks
	 cout<<"Good Matched Tracks: "<<goodMatchedTracks<<endl;

    //Get the Centrality Bin of the Event (skip if bad centrality bin)
	 if (goodMatchedTracks < 153 || goodMatchedTracks > 240) continue;
    int centBin = 0;

    nEventsHisto->Fill(centBin);

    //****** LOOP OVER THE MONTE CARLO TRACKS AND FILL HISTOGRAMS
    cout <<"NMonteCarlo Tracks: " <<minimcReader->GetNEmbeddedTracks() <<endl; 
    for (Int_t embTrackIndex=0; embTrackIndex<minimcReader->GetNEmbeddedTracks(); embTrackIndex++){

      //Get the Track's PID Index
      std::pair <int,int> pid =
        ConvertGeantIDtoParticleIndex(minimcReader->GetEmbTrackGeantID(embTrackIndex));
      if (pid.first < 0)
	continue;

      Double_t rapidity = ComputeRapidity(minimcReader->GetEmbTrackPt(embTrackIndex),
                                          minimcReader->GetEmbTrackPz(embTrackIndex),
                                          GetParticleMass(pid.first));
      Double_t mTm0 = ComputemTm0(minimcReader->GetEmbTrackPt(embTrackIndex),pid.first);

      
      mcTracksPidHisto->Fill(minimcReader->GetEmbTrackGeantID(embTrackIndex));

      if (minimcReader->GetEmbTrackParentGeantID(embTrackIndex) == 18 && minimcReader->GetEmbTrackGeantID(embTrackIndex) == 14){
	embTracksCentRapidityLambdaParent.at(centBin)->Fill(rapidity);
      }
      
    }//End Loop Over Monte Carlo Tracks

    
    //****** LOOP OVER THE MATCHED TRACKS AND FILL HISTOGRAMS ******
    cout <<"NMatched Tracks: " <<minimcReader->GetNMatchedTracks() <<endl;
    for (Int_t matchTrackIndex=0; matchTrackIndex<minimcReader->GetNMatchedTracks(); matchTrackIndex++){

      //Get the Track's PID Index
      std::pair <int,int> pid =
	ConvertGeantIDtoParticleIndex(minimcReader->GetMatchedTrackGeantID(matchTrackIndex));

      //We only need tracks that are part of our definitions (pi,k,p,..,muon)
      if (pid.first < 0)
	continue;
      
      //Skip Bad Tracks
      if (!IsGoodTrack(minimcReader,matchTrackIndex,"Matched"))
	continue;
      
      Double_t rapidity = ComputeRapidity(minimcReader->GetMatchedTrackPtReco(matchTrackIndex),
                                          minimcReader->GetMatchedTrackPzReco(matchTrackIndex),
                                          GetParticleMass(pid.first));
      Double_t mTm0 = ComputemTm0(minimcReader->GetMatchedTrackPtReco(matchTrackIndex),pid.first);
      
      cout <<"y: " <<rapidity <<" " <<"mT-m0: " <<mTm0 <<endl;
      
      matchedTracksEtaHisto->Fill(minimcReader->GetMatchedTrackEtaReco(matchTrackIndex));
      matchedTracksPhiHisto->Fill(minimcReader->GetMatchedTrackPhiReco(matchTrackIndex));
      matchedTracksEtaPhiHisto->Fill(minimcReader->GetMatchedTrackEtaReco(matchTrackIndex),
				     minimcReader->GetMatchedTrackPhiReco(matchTrackIndex));
      if (minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex) == 18){
	matchedTracksRapidityLambdaParent->Fill(rapidity);
	matchTracksCentTrackFlagHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackFlag(matchTrackIndex));
	matchTracksCentNHitsFitHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackNHitsFit(matchTrackIndex));
	matchTracksCentNHitsdEdxHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackNHitsdEdx(matchTrackIndex));
	matchTracksCentNHitsFracHisto.at(centBin)->Fill((double)minimcReader->GetMatchedTrackNHitsFit(matchTrackIndex) /
							(double)minimcReader->GetMatchedTrackNHitsPoss(matchTrackIndex));
	matchTracksCentglDCAHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackDCAGl(matchTrackIndex));
      }
      
      if (minimcReader->GetMatchedTrackGeantID(matchTrackIndex) == 14 &&
	  minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex) == 18){
	matchTracksCentRapidityLambdaParent.at(centBin)->Fill(rapidity);
      }
      
      matchTracksPidHisto->Fill(minimcReader->GetMatchedTrackGeantID(matchTrackIndex));
      matchTracksParentPidHisto->Fill(minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex));
      matchTracksCentPidHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackGeantID(matchTrackIndex));
      matchTracksCentParentPidHisto.at(centBin)->Fill(minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex));

      //***Muon Contamination Plots
      //Count the Pions
      if (pid.first == PION){
	if (pid.second < 0)
	  pionCount.at(centBin).first->Fill(rapidity,mTm0);
	else if (pid.second > 0)
	  pionCount.at(centBin).second->Fill(rapidity,mTm0);
      }

      //If this tracks is a Muon and it has passed the track cuts then it contributes
      //to the Pion Contamination
      if (pid.first == MUON){
	
	//Recompute the rapidity and mTm0 for the pion mass
	Double_t yPi = ComputeRapidity(minimcReader->GetMatchedTrackPtReco(matchTrackIndex),
				       minimcReader->GetMatchedTrackPzReco(matchTrackIndex),
				       GetParticleMass(PION));
	Double_t mTm0Pi = ComputemTm0(minimcReader->GetMatchedTrackPtReco(matchTrackIndex),PION);
	
	
	if (pid.second < 0){
	  pionMuonCount.at(centBin).first->Fill(yPi,mTm0Pi);
	  pionCount.at(centBin).first->Fill(yPi,mTm0Pi);
	}
	else if (pid.second > 0){
	  pionMuonCount.at(centBin).second->Fill(yPi,mTm0Pi);
	  pionCount.at(centBin).second->Fill(yPi,mTm0Pi);
	}
      }

      //Only keeps pions, kaons, and protons beyond this point
      if (pid.first < PION || pid.first > PROTON)
	continue;

      //**** Feed Down Plots
      //If Negative
      if (pid.second < 0){
	feedDownHisto.at(centBin).at(pid.first).first->
	  Fill(rapidity,mTm0,minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex));
      }
      //If Positive
      else if (pid.second > 0){
	feedDownHisto.at(centBin).at(pid.first).second->
          Fill(rapidity,mTm0,minimcReader->GetMatchedTrackParentGeantID(matchTrackIndex));
      }


    }//End Loop Over Matched Tracks

    //cout <<"Event SUMMARY: " <<"CentBin: " <<centBin <<" " <<endl;
  }//End Loop Over Chain Entries

  //******* SAVE ********
  outFile->cd();
  outFile->mkdir("PionMuonContamination");
  outFile->mkdir("FeedDown");
  
  outFile->cd();
  nEventsHisto->Write();
  mcTracksPidHisto->Write();
  matchTracksPidHisto->Write();
  matchTracksParentPidHisto->Write();
  matchTracksPidHisto->Write();
  matchTracksParentPidHisto->Write();
  matchedTracksEtaHisto->Write();
  matchedTracksPhiHisto->Write();
  matchedTracksEtaPhiHisto->Write();
  matchedTracksRapidityLambdaParent->Write();

  for (unsigned int iCentBin=0;iCentBin<nCentBins; iCentBin++){
    embTracksCentRapidityLambdaParent.at(iCentBin)->Write();

    matchTracksCentPidHisto.at(iCentBin)->Write();
    matchTracksCentParentPidHisto.at(iCentBin)->Write();
    matchTracksCentTrackFlagHisto.at(iCentBin)->Write();
    matchTracksCentNHitsFitHisto.at(iCentBin)->Write();
    matchTracksCentNHitsdEdxHisto.at(iCentBin)->Write();
    matchTracksCentNHitsFracHisto.at(iCentBin)->Write();
    matchTracksCentglDCAHisto.at(iCentBin)->Write();
    matchTracksCentRapidityLambdaParent.at(iCentBin)->Write();
  }//End Loop Over Centrality Bins      

  outFile->cd();
  outFile->cd("PionMuonContamination");
  for (unsigned int iCentBin=0;iCentBin<nCentBins; iCentBin++){
    pionCount.at(iCentBin).first->Write();
    pionCount.at(iCentBin).second->Write();
    pionMuonCount.at(iCentBin).first->Write();
    pionMuonCount.at(iCentBin).second->Write();
  }//End Loop Over CentBins

  outFile->cd();
  outFile->cd("FeedDown");
  for (unsigned int iCentBin=0; iCentBin<nCentBins; iCentBin++){
    for (unsigned int iSpecies=0; iSpecies<feedDownHisto.at(iCentBin).size(); iSpecies++){
      feedDownHisto.at(iCentBin).at(iSpecies).first->Write();
      feedDownHisto.at(iCentBin).at(iSpecies).second->Write();
    }//End Loop Over Species
  }//End Loop Over CentBins
  

}
