//Implementations of Binning and Cutting Functions

#include <iostream>
#include <vector>

#include <TTree.h>

#include "MiniMcReader.h"
#include "CentralityDatabaseClass.h"
#include "BinningAndCuts.h"

//___________________________________________________________
std::vector<Long64_t> BuildRunNumberLookUpTable(TTree *centralityTree, CentralityDatabase *centralityDatabase){

  std::vector<Long64_t> runNumberLookUpTable;
  
  //Loop Over the centrality tree and add each run number to the look up table
  for (Long64_t iEntry=0; iEntry<centralityTree->GetEntries(); iEntry++){
    
    centralityTree->GetEntry(iEntry);
    runNumberLookUpTable.push_back(centralityDatabase->GetRunNumber());
    
  }
  
  return runNumberLookUpTable;
  
}

//___________________________________________________________
Double_t GetCentralityPercent(int centBin){

  //Assuming 9 centrality bins
  const int nCentBins(9);

  //Check to make sure the input bin is in range
  if (centBin < 0 || centBin >=nCentBins){
    cout <<"ERROR! - BinningAndCuts::GetCentralityPercent() - centBin out of range! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  //Define the centrality percent array
  Double_t centralityPercentages[nCentBins] = 
    {80.,70.,60.,50.,40.,30.,20.,10.,5.};

  return centralityPercentages[centBin];
}

//___________________________________________________________
Int_t GetCentralityBin(TTree *centralityTree, CentralityDatabase *centralityDatabase,
		       std::vector<Long64_t> *runNumberLookUpTable, Long64_t runNumber, Long64_t eventNumber){
  
  Int_t centralityBin(-1);
  
  for (unsigned int i=0; i<runNumberLookUpTable->size(); i++){
    
    if (runNumberLookUpTable->at(i) != runNumber)
      continue;
    
    centralityTree->GetEntry(i);
    centralityBin = centralityDatabase->GetCentralityBin(eventNumber);
    
    if (centralityBin >= 0)
      return centralityBin;
  }
  
  //Failure Mode
  return -1;
  
}

//____________________________________________________________
Bool_t IsGoodTrack(MiniMcReader *minimcReader, Int_t trackIndex, TString trackType, Bool_t useThisCut){

  //These track cuts should be the same as what you use in your analysis
  Short_t flag(0);
  Short_t nHitsFit(0);
  Short_t nHitsPoss(0);
  Short_t nHitsdEdx(0);
  Double_t globalDCA(0);

  //Fill the variables depending on the track type;
  if (trackType.Contains("Matched")){
    flag      = minimcReader->GetMatchedTrackFlag(trackIndex);
    nHitsFit  = minimcReader->GetMatchedTrackNHitsFit(trackIndex);
    nHitsPoss = minimcReader->GetMatchedTrackNHitsPoss(trackIndex);
    nHitsdEdx = minimcReader->GetMatchedTrackNHitsdEdx(trackIndex);
    globalDCA = minimcReader->GetMatchedTrackDCAGl(trackIndex);
  }
  else if (trackType.Contains("Split")){
    flag      = minimcReader->GetSplitTrackFlag(trackIndex);
    nHitsFit  = minimcReader->GetSplitTrackNHitsFit(trackIndex);
    nHitsPoss = minimcReader->GetSplitTrackNHitsPoss(trackIndex);
    nHitsdEdx = minimcReader->GetSplitTrackNHitsdEdx(trackIndex);
    globalDCA = minimcReader->GetSplitTrackDCAGl(trackIndex);
  }
  else {
    cout <<"ERROR - ProcessEmbedding::IsGoodTrack() trackType is not recognized! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  //Apply the cuts

  if (nHitsdEdx < 6)
    return false;
  cout<<"nHitsdEdx: "<<nHitsdEdx<<endl;

  if (nHitsFit < 12)
    return false;

  if ((double)nHitsFit/(double)nHitsPoss < 0.52)
    return false;

  if (useThisCut){
    if (globalDCA > 3.0)
      return false;
  }
  
  //If it passes all the cuts it is a good track
  return true;

}

//____________________________________________________________
Int_t GetCentralityBinOfSimulatedEvent(Double_t centVariable, Double_t energy){

  //Centrality cuts for simulated events can be determined using the codes
  //ConstructMultiplicityDistributions.cxx and DetermineCentralityBinsOfSimEvents.C
  const int nCentBins(9);
  Double_t AuAu07[nCentBins] = {4,8,15,26,41,63,93,134,161};
  Double_t AuAu11[nCentBins] = {5,10,18,31,50,76,112,163,195};
  Double_t AuAu14[nCentBins] = {5,10,19,32,51,78,114,166,199};
  Double_t AuAu19[nCentBins] = {6,12,23,39,62,94,139,202,242};
  Double_t AuAu27[nCentBins] = {6,13,24,41,66,102,148,216,259};
  Double_t AuAu39[nCentBins] = {7,14,27,46,74,113,166,242,289};
  Double_t AuAu62[nCentBins] = {8,16,30,52,85,129,191,277,331};
  
  Double_t *cutArray = NULL;
  if (fabs(energy-7.7) < 0.2)
    cutArray = AuAu07;
  else if (fabs(energy-11.5) < 0.2)
    cutArray = AuAu11;
  else if (fabs(energy-14.5) < 0.2)
    cutArray = AuAu14;
  else if (fabs(energy-19.6) < 0.2)
    cutArray = AuAu19;
  else if (fabs(energy-27.0) < 0.2)
    cutArray = AuAu27;
  else if (fabs(energy-39.0) < 0.2)
    cutArray = AuAu39;
  else if (fabs(energy-62.4) < 0.2)
    cutArray = AuAu62;

  if (!cutArray){
    cout <<"ERROR: BinningAndCuts::GetCentralityBinOfSimulatedEvent() - Cut array not found! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  //Check that it passes the minimum Multiplicity
  if (centVariable < cutArray[0])
    return -1;

  //Loop Over the Centrality bins and determine 
  //which bin the event falls into
  for (int iCentBin=nCentBins-1; iCentBin>=0; iCentBin--){
    if (centVariable >= cutArray[iCentBin])
      return iCentBin;
  }

  //If for some reason the function makes it this far
  //then the centrality bin was not determined.
  return -1;

}
