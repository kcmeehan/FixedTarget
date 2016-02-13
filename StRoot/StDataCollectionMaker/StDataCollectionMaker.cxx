#include <iostream>
#include <cstdio>
#include <vector>

#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
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
#include "StRoot/PrimaryVertexInfo/PrimaryVertexInfo.h"
#include "StRoot/EventInfo/EventInfo.h"
#include "StDataCollectionMaker.h"


ClassImp(StDataCollectionMaker);

//__________________________________________________________________________ 
StDataCollectionMaker::StDataCollectionMaker(char *name): StMaker(name){

  //By Default set the status of the cut booleans to false
  isMinVrSet = false;
  isMaxVrSet = false;
  isMinVzSet = false;
  isMaxVzSet = false;
  isMinVxSet = false;
  isMaxVxSet = false;
  isMinVySet = false;
  isMaxVySet = false;
  isBeamSpotSet = false;
  isMinNumberOfPrimaryTracksSet = false;

  //Set default values for the cuts in such away that they won't 
  //interfere with data taking.
  minVr = -1;
  maxVr = 5000;
  minVz = -5000;
  maxVz = 5000;
  minVx = -5000;
  maxVx = 5000;
  minVy = -5000;
  maxVy = 5000;
  beamSpotX = 0.0;
  beamSpotY = 0.0;
  minNumberOfPrimaryTracks = -1;

  cout <<"StDataCollectionMaker Object created" <<endl;
}

//__________________________________________________________________________                                      
StDataCollectionMaker::~StDataCollectionMaker(){}

//__________________________________________________________________________                                
Int_t StDataCollectionMaker::Init(){

  cout <<"Starting Init()" <<endl;

  //Set the Output File Name                                       
  TString fileName = fileNameBase;
  fileName.Append(mFileIndex);
  fileName.Append(".root");
  fileName.Prepend(mOutDir);

  cout <<"Working on output file: " <<fileName <<endl;
  
  //Create the outout Root File                                                                             
  outFile = new TFile(fileName.Data(), "RECREATE");
  
  //Create an Instance of each data object
  eventInfo  = new EventInfo();
  vertexInfo = new PrimaryVertexInfo();
  trackInfo  = new TrackInfo();

  //Create the Vertex and Track Arrays
  vertexArray = new TClonesArray("PrimaryVertexInfo",0);
  trackArray  = new TClonesArray("TrackInfo",0);

  //Create the Output Tree and its Branches
  outTree = new TTree("DataTree","DataTree");
  eventBranch  = outTree->Branch("EventInfo", &eventInfo,  2000000);
  vertexBranch = outTree->Branch("VertexInfo",&vertexArray,2000000);
  trackBranch  = outTree->Branch("TrackInfo", &trackArray, 2000000);

  //Set the Vertex and Track Pointers in EventInfo
  eventInfo->SetVertexArrayPtr(vertexArray);
  eventInfo->SetTrackArrayPtr(trackArray);

  //Set the Range of RefMult User
  //This will be set depending on the +- zVertex location
  eventInfo->SetRefMultUser(0,1.8);

  //End of Init                                                              
  fputs("Finished Init()\n", stderr);
  return kStOK;
}

//__________________________________________________________________________                           
void StDataCollectionMaker::Clear(const char *c){

  eventInfo->ResetEventInfo();

  return StMaker::Clear(c);
}

//__________________________________________________________________________ 
Int_t StDataCollectionMaker::Make(){

  //The MuDst
  StMuDstMaker *muDstMaker = NULL;
  muDstMaker = (StMuDstMaker *)GetMaker("MuDst");
  if (!muDstMaker){
    fputs("ERROR: StDataCollectionMaker::Init() - Can't get pointer to StMuDstMaker!", stderr);
    return kStFATAL;
  }
  cout <<muDstMaker <<endl;
  StMuDst *mMuDst = NULL;
  mMuDst = muDstMaker->muDst();
  if (!mMuDst){
    fputs("ERROR: StDataCollectionMaker::Init() - Can't get pointer to StMuDst!", stderr);
    return kStFATAL;
  }

  //CHECK TO MAKE SURE THE EVENT IS INTERESTING
  //This function makes sure that this event passes some
  //very simple cuts. You can use this to prevent your DavisDSTs
  //from filling up with lots of events that are not useful.
  if (!eventInfo->IsInterestingEvent(mMuDst))
    return kStOK;

  //ADD THE EVENT/TRIGGER
  eventInfo->SetEventInfo(mMuDst,this);
  
  //FILL THE EVENT TREE
  if (eventInfo->GetNPrimaryVertices() > 0)
    outTree->Fill();
  
  //RESET EVENT INFO
  //This function resets the event level variables to their default values
  //and deletes the primary vertex array which then deletes the track array
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

//__________________________________________________________________________
void StDataCollectionMaker::SetMinVr(Double_t val){

  minVr = val;
  isMinVrSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMaxVr(Double_t val){

  maxVr = val;
  isMaxVrSet = true;

}


//__________________________________________________________________________
void StDataCollectionMaker::SetMinVz(Double_t val){

  minVz = val;
  isMinVzSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMaxVz(Double_t val){

  maxVz = val;
  isMaxVzSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMinVx(Double_t val){

  minVx = val;
  isMinVxSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMaxVx(Double_t val){

  maxVx = val;
  isMaxVxSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMinVy(Double_t val){

  minVy = val;
  isMinVySet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMaxVy(Double_t val){

  maxVy = val;
  isMaxVySet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetBeamSpot(Double_t xVal, Double_t yVal){

  beamSpotX = xVal;
  beamSpotY = yVal;
  isBeamSpotSet = true;

}

//__________________________________________________________________________
void StDataCollectionMaker::SetMinNumberOfPrimaryTracks(Int_t val){
  
  minNumberOfPrimaryTracks = val;
  isMinNumberOfPrimaryTracksSet = true;
}

//__________________________________________________________________________
void StDataCollectionMaker::SetMaxNumberOfVertices(Int_t val){

  maxNumberOfVertices = val;
  isMaxNumberOfVerticesSet = true;
}


