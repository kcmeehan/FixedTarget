#include <iostream>
#include <cstdio>
#include <vector>

#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "StLorentzVectorF.hh"
#include "StThreeVectorF.hh"
#include "StParticleTypes.hh"
#include "TString.h"


#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StTriggerData.h"
#include "StTriggerIdCollection.h"
#include "StRunInfo.h"

#include "StRoot/TrackInfo/TrackInfo.h"
#include "StRoot/EventInfo/EventInfo.h"
#include "StDataCollectionMaker.h"


ClassImp(StDataCollectionMaker);

//__________________________________________________________________________ 
StDataCollectionMaker::StDataCollectionMaker(char *name): StMaker(name){}

//__________________________________________________________________________                                      
StDataCollectionMaker::~StDataCollectionMaker(){}

//__________________________________________________________________________                                
Int_t StDataCollectionMaker::Init(){

  //Set the Output File Name                                       
  TString fileName = fileNameBase;
  fileName.Append(mFileIndex);
  fileName.Append(".root");
  fileName.Prepend(mOutDir);

  cout <<"Working on output file: " <<fileName <<endl;
  
  //Create the outout Root File                                                                             
  outFile = new TFile(fileName.Data(), "RECREATE");
  
  //Create an Instance of StEventInfo
  eventInfo = new EventInfo();

  //Create the Output TTree
  outTree = new TTree("DataTree","DataTree");
  outBranch = outTree->Branch("EventInfo",&eventInfo,2000000);

  //End of Init                                                              
  fputs("Finished Init()\n", stderr);
  return kStOK;
}

//__________________________________________________________________________                           
void StDataCollectionMaker::Clear(const char *c){
  return StMaker::Clear(c);
}

//__________________________________________________________________________ 
Int_t StDataCollectionMaker::Make(){

  //The MuDst
  StMuDstMaker *muDstMaker = (StMuDstMaker *)GetMaker("MuDst");
  StMuDst *mMuDst = muDstMaker->muDst();

  //Check to make sure the Event is interesting
  if (!eventInfo->IsInterestingEvent(mMuDst))
    return kStOK;

  //Add The Event
  eventInfo->SetEventInfo(mMuDst);

  //Print Info
  //eventInfo->PrintEventInfo();

  //Fill The Tree
  outTree->Fill();

  //Reset the EventInfo
  eventInfo->ResetEventInfo();

  //End of Make  
  return kStOK;
}

//__________________________________________________________________________ 
Int_t StDataCollectionMaker::Finish(){

  //Save things to the file here
  outFile->cd();
  outTree->Write();

  cout <<"Done Saving\n" <<endl;
  fputs("Done Saving\n",stderr);

  gROOT->GetListOfFiles()->Remove(outFile);
  outFile->Close();

  return kStOK;
}
