#include <iostream>
#include <vector>

#include <TTree.h>
#include <TMath.h>

#include "MiniMcReader.h"

ClassImp(MiniMcReader);


//__________________________________________________________
MiniMcReader::MiniMcReader(TTree *tree){

  //kMaxEntries;
  miniMCTree = tree;

  //Set the size of the arrays
  miniMCTree->Draw("mNMcTrack","","goff");
  Double_t *arr = miniMCTree->GetV1();
  kMaxEntries = (int) TMath::MaxElement(miniMCTree->GetSelectedRows(),arr);
  kMaxEntries += 100;

  cout <<"MAX ENTRIES: " <<kMaxEntries <<endl;

  Reset();
  Init();
}

//__________________________________________________________
MiniMcReader::~MiniMcReader(){

}

//__________________________________________________________
void MiniMcReader::Init(){

  //Embedded Track Variables                                                                           
  embTrackPt.resize(kMaxEntries,-999);        embTrackPz.resize(kMaxEntries,-999);
  embTrackEta.resize(kMaxEntries,-999);       embTrackPhi.resize(kMaxEntries,-999);
  embTrackGeantID.resize(kMaxEntries,-999);   embTrackParentGeantID.resize(kMaxEntries,-999);
  embTrackNHits.resize(kMaxEntries,-999);

  //Matched Track Variables                                                                            
  matchTrackPtEmb.resize(kMaxEntries,-999);    matchTrackPzEmb.resize(kMaxEntries,-999);
  matchTrackPtReco.resize(kMaxEntries,-999);   matchTrackPzReco.resize(kMaxEntries,-999);
  matchTrackEtaEmb.resize(kMaxEntries,-999);   matchTrackPhiEmb.resize(kMaxEntries,-999);
  matchTrackEtaReco.resize(kMaxEntries,-999);  matchTrackPhiReco.resize(kMaxEntries,-999);
  matchTrackDCAGl.resize(kMaxEntries,-999);    matchTrackdEdx.resize(kMaxEntries,-999);
  matchTrackGeantID.resize(kMaxEntries,-999);  matchTrackParentGeantID.resize(kMaxEntries,-999);
  matchTrackNHits.resize(kMaxEntries,-999);    matchTrackNFitPts.resize(kMaxEntries,-999);
  matchTrackFlag.resize(kMaxEntries,-999);     matchTrackNHitsdEdx.resize(kMaxEntries,-999);
  matchTrackNPossPts.resize(kMaxEntries,-999);

  //Split Track Variables                                                                              
  splitTrackPtEmb.resize(kMaxEntries,-999);    splitTrackPzEmb.resize(kMaxEntries,-999);
  splitTrackPtReco.resize(kMaxEntries,-999);   splitTrackPzReco.resize(kMaxEntries,-999);
  splitTrackEtaEmb.resize(kMaxEntries,-999);   splitTrackPhiEmb.resize(kMaxEntries,-999);
  splitTrackEtaReco.resize(kMaxEntries,-999);  splitTrackPhiReco.resize(kMaxEntries,-999);
  splitTrackDCAGl.resize(kMaxEntries,-999);    splitTrackdEdx.resize(kMaxEntries,-999);
  splitTrackGeantID.resize(kMaxEntries,-999);  splitTrackParentGeantID.resize(kMaxEntries,-999);
  splitTrackNHits.resize(kMaxEntries,-999);    splitTrackNFitPts.resize(kMaxEntries,-999);
  splitTrackFlag.resize(kMaxEntries,-999);     splitTrackNHitsdEdx.resize(kMaxEntries,-999);
  splitTrackNPossPts.resize(kMaxEntries,-999);

  cout <<"Set All vector sizes" <<endl;

  //Set all the Branch Address
  miniMCTree->SetBranchAddress("mRunId",&runNumber);
  miniMCTree->SetBranchAddress("mEventId",&eventNumber);
  miniMCTree->SetBranchAddress("mNMcTrack",&nEmbTracks);
  miniMCTree->SetBranchAddress("mNMatchedPair",&nMatchTracks);
  miniMCTree->SetBranchAddress("mNSplitPair",&nSplitTracks);
  miniMCTree->SetBranchAddress("mNUncorrectedPrimaries",&refMult);
  miniMCTree->SetBranchAddress("mCentralMult",&centralMult);
  miniMCTree->SetBranchAddress("mOriginMult",&originMult);
  miniMCTree->SetBranchAddress("mCentrality",&centrality);
  miniMCTree->SetBranchAddress("mMcVertexX",&embVertexX);
  miniMCTree->SetBranchAddress("mMcVertexY",&embVertexY);
  miniMCTree->SetBranchAddress("mMcVertexZ",&embVertexZ);
  cout <<"Set Event Level Branches" <<endl;
  miniMCTree->SetBranchAddress("mMcTracks.mPtMc",&embTrackPt[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mPzMc",&embTrackPz[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mEtaMc",&embTrackEta[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mPhiMc",&embTrackPhi[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mGeantId",&embTrackGeantID[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mParentGeantId",&embTrackParentGeantID[0]);
  miniMCTree->SetBranchAddress("mMcTracks.mNHitMc",&embTrackNHits[0]);

  miniMCTree->SetBranchAddress("mMatchedPairs.mPtMc",&matchTrackPtEmb[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mPzMc",&matchTrackPzEmb[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mPtPr",&matchTrackPtReco[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mPzPr",&matchTrackPzReco[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mGeantId",&matchTrackGeantID[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mParentGeantId",&matchTrackParentGeantID[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mFitPts",&matchTrackNFitPts[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mNPossible",&matchTrackNPossPts[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mAllPts",&matchTrackNHits[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mEtaMc",&matchTrackEtaEmb[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mPhiMc",&matchTrackPhiEmb[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mEtaPr",&matchTrackEtaReco[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mPhiPr",&matchTrackPhiReco[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mFlag",&matchTrackFlag[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mDcaGl",&matchTrackDCAGl[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mDedxPts",&matchTrackNHitsdEdx[0]);
  miniMCTree->SetBranchAddress("mMatchedPairs.mDedx",&matchTrackdEdx[0]);

  miniMCTree->SetBranchAddress("mSplitPairs.mEtaMc",&splitTrackEtaEmb[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPtMc",&splitTrackPtEmb[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPhiMc",&splitTrackPhiEmb[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPzMc",&splitTrackPzEmb[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mEtaPr",&splitTrackEtaReco[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPtPr",&splitTrackPtReco[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPhiPr",&splitTrackPhiReco[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mPzPr",&splitTrackPzReco[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mDedx",&splitTrackdEdx[0]);  
  miniMCTree->SetBranchAddress("mSplitPairs.mDcaGl",&splitTrackDCAGl[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mDedxPts",&splitTrackNHitsdEdx[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mGeantId",&splitTrackGeantID[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mParentGeantId",&splitTrackParentGeantID[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mFitPts",&splitTrackNFitPts[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mNPossible",&splitTrackNPossPts[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mAllPts",&splitTrackNHits[0]);
  miniMCTree->SetBranchAddress("mSplitPairs.mFlag",&splitTrackFlag[0]);
  cout <<"Set Track Level Branches" <<endl;
}

//__________________________________________________________
void MiniMcReader::Reset(){

  //Event Variables
  runNumber    = -999;
  eventNumber  = -999;
  nEmbTracks   = -999;
  nMatchTracks = -999;
  nSplitTracks = -999;
  refMult      = -999;
  originMult   = -999;
  centrality   = -999;
  centralMult  = -999;
  embVertexX   = -999;
  embVertexY   = -999;
  embVertexZ   = -999;

  if ((int)embTrackPt.size() == 0)
    return;
  
  for (int i=0; i<kMaxEntries; i++){

    //Embedded Track Variables
    embTrackPt[i]              = -999;
    embTrackPz[i]              = -999;
    embTrackEta[i]             = -999;
    embTrackPhi[i]             = -999;
    embTrackGeantID[i]         = -999;
    embTrackParentGeantID[i]   = -999;
    embTrackNHits[i]           = -999;

    //Matched Track Variables
    matchTrackPtEmb[i]         = -999;
    matchTrackPzEmb[i]         = -999;
    matchTrackPtReco[i]        = -999;
    matchTrackPzReco[i]        = -999;
    matchTrackGeantID[i]       = -999;
    matchTrackParentGeantID[i] = -999;
    matchTrackNHits[i]         = -999;
    matchTrackNFitPts[i]       = -999;
    matchTrackNPossPts[i]      = -999;
    matchTrackEtaEmb[i]        = -999;
    matchTrackPhiEmb[i]        = -999;
    matchTrackEtaReco[i]       = -999;
    matchTrackPhiReco[i]       = -999;
    matchTrackFlag[i]          = -999;
    matchTrackDCAGl[i]         = -999;
    matchTrackdEdx[i]          = -999;
    matchTrackNHitsdEdx[i]     = -999;

    //Split Track Variables
    splitTrackEtaEmb[i]        = -999;
    splitTrackPtEmb[i]         = -999;
    splitTrackEtaReco[i]       = -999;
    splitTrackPtReco[i]        = -999;
    splitTrackGeantID[i]       = -999;
    splitTrackParentGeantID[i] = -999;
    splitTrackNHits[i]         = -999;
    splitTrackNFitPts[i]       = -999;
    splitTrackNPossPts[i]      = -999;
    splitTrackFlag[i]          = -999;
    splitTrackDCAGl[i]         = -999;
    splitTrackNHitsdEdx[i]     = -999;
    
    
  }
  
}

//__________________________________________________________
Bool_t MiniMcReader::CheckEmbTrackCount( int index ){

  if ( index >= GetNEmbeddedTracks() ){
    cout <<"ERROR - MiniMcReader::CheckEmbTrackCount() - The index of the requested track is\n"
	 <<"        is GREATER than the number of embedded tracks in this event! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  return true;  
}

//__________________________________________________________
Bool_t MiniMcReader::CheckMatchedTrackCount( int index ){

  if ( index >= GetNMatchedTracks() ){
    cout <<"ERROR - MiniMcReader::CheckMatchedTrackCount() - The index of the requested track is\n"
	 <<"        is GREATER than the number of matched tracks in this event! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  return true;  
}

//__________________________________________________________
Bool_t MiniMcReader::CheckSplitTrackCount( int index ){

  if ( index >= GetNSplitTracks() ){
    cout <<"ERROR - MiniMcReader::CheckSplitTrackCount() - The index of the requested track is\n"
	 <<"        is GREATER than the number of split tracks in this event! EXITING!\n";
    exit (EXIT_FAILURE);
  }

  return true;  
}

/**** EMBEDDED TRACK GETS ****/
//__________________________________________________________
Float_t MiniMcReader::GetEmbTrackPt(int index){
  CheckEmbTrackCount(index);  
  return embTrackPt[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetEmbTrackPz(int index){
  CheckEmbTrackCount(index);
  return embTrackPz[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetEmbTrackEta(int index){
  CheckEmbTrackCount(index);
  return embTrackEta[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetEmbTrackPhi(int index){
  CheckEmbTrackCount(index);
  return embTrackPhi[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetEmbTrackGeantID(int index){
  CheckEmbTrackCount(index);
  return embTrackGeantID[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetEmbTrackParentGeantID(int index){
  CheckEmbTrackCount(index);
  return embTrackParentGeantID[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetEmbTrackNHits(int index){
  CheckEmbTrackCount(index);
  return embTrackNHits[index];
}

/**** MATCHED TRACK GETS ****/
//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPtEmb(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPtEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPzEmb(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPzEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackEtaEmb(int index){
  CheckMatchedTrackCount(index);
  return matchTrackEtaEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPhiEmb(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPhiEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPtReco(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPtReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPzReco(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPzReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackEtaReco(int index){
  CheckMatchedTrackCount(index);
  return matchTrackEtaReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackPhiReco(int index){
  CheckMatchedTrackCount(index);
  return matchTrackPhiReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackDCAGl(int index){
  CheckMatchedTrackCount(index);
  return matchTrackDCAGl[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetMatchedTrackdEdx(int index){
  CheckMatchedTrackCount(index);
  return matchTrackdEdx[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetMatchedTrackGeantID(int index){
  CheckMatchedTrackCount(index);
  return matchTrackGeantID[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetMatchedTrackParentGeantID(int index){
  CheckMatchedTrackCount(index);
  return matchTrackParentGeantID[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetMatchedTrackFlag(int index){
  CheckMatchedTrackCount(index);
  return matchTrackFlag[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetMatchedTrackNHits(int index){
  CheckMatchedTrackCount(index);
  return matchTrackNHits[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetMatchedTrackNHitsFit(int index){
  CheckMatchedTrackCount(index);
  return matchTrackNFitPts[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetMatchedTrackNHitsPoss(int index){
  CheckMatchedTrackCount(index);
  return matchTrackNPossPts[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetMatchedTrackNHitsdEdx(int index){
  CheckMatchedTrackCount(index);
  return matchTrackNHitsdEdx[index];
}

/**** Split TRACK GETS ****/
//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPtEmb(int index){
  CheckSplitTrackCount(index);
  return splitTrackPtEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPzEmb(int index){
  CheckSplitTrackCount(index);
  return splitTrackPzEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackEtaEmb(int index){
  CheckSplitTrackCount(index);
  return splitTrackEtaEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPhiEmb(int index){
  CheckSplitTrackCount(index);
  return splitTrackPhiEmb[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPtReco(int index){
  CheckSplitTrackCount(index);
  return splitTrackPtReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPzReco(int index){
  CheckSplitTrackCount(index);
  return splitTrackPzReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackEtaReco(int index){
  CheckSplitTrackCount(index);
  return splitTrackEtaReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackPhiReco(int index){
  CheckSplitTrackCount(index);
  return splitTrackPhiReco[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackDCAGl(int index){
  CheckSplitTrackCount(index);
  return splitTrackDCAGl[index];
}

//__________________________________________________________
Float_t MiniMcReader::GetSplitTrackdEdx(int index){
  CheckSplitTrackCount(index);
  return splitTrackdEdx[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetSplitTrackGeantID(int index){
  CheckSplitTrackCount(index);
  return splitTrackGeantID[index];
}

//__________________________________________________________
UShort_t MiniMcReader::GetSplitTrackParentGeantID(int index){
  CheckSplitTrackCount(index);
  return splitTrackParentGeantID[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetSplitTrackFlag(int index){
  CheckSplitTrackCount(index);
  return splitTrackFlag[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetSplitTrackNHits(int index){
  CheckSplitTrackCount(index);
  return splitTrackNHits[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetSplitTrackNHitsFit(int index){
  CheckSplitTrackCount(index);
  return splitTrackNFitPts[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetSplitTrackNHitsPoss(int index){
  CheckSplitTrackCount(index);
  return splitTrackNPossPts[index];
}

//__________________________________________________________
Short_t MiniMcReader::GetSplitTrackNHitsdEdx(int index){
  CheckSplitTrackCount(index);
  return splitTrackNHitsdEdx[index];
}
