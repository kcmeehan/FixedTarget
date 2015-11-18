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
#include "StRoot/PrimaryVertexInfo/PrimaryVertexInfo.h"
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
  hvyvz = new TH2D("hvyvz", "Vy vs Vz", 1000,-500,500,1000,-10,10);

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
	
  //Make pre-cuts vyvz histogram to see flange
	Int_t nVert = mMuDst->primaryVertices()->GetEntries();
	for(int ipv=0;ipv<nVert;ipv++){
	  mMuDst->setVertexIndex(ipv);
		hvyvz->Fill(mMuDst->event()->primaryVertexPosition().z(),mMuDst->event()->primaryVertexPosition().y());
	}

  //Add The Event
  eventInfo->SetEventInfo(mMuDst);

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
	hvyvz->Write();
  outTree->Write();

  cout <<"Done Saving\n" <<endl;
  fputs("Done Saving\n",stderr);

  gROOT->GetListOfFiles()->Remove(outFile);
  outFile->Close();

  return kStOK;
}
