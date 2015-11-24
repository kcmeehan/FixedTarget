#include <iostream>
#include <stdlib.h>
#include <TObject.h>
#include "TClonesArray.h"
#include "TVector3.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StEvent/StTriggerData.h"

#include "StRoot/StDataCollectionMaker/StDataCollectionMaker.h"
#include "StRoot/PrimaryVertexInfo/PrimaryVertexInfo.h"
#include "EventInfo.h"

ClassImp(EventInfo);

//___________________________________________________________
EventInfo::EventInfo(){

  runNumber        = -999;
  eventNumber      = -999;
  nPrimaryVertices = -999;
  nPileUpVertices  = -999;
  adcSumBBCWest    = -999;
  adcSumBBCEast    = -999;
  meanPt           = -999;
  meanEta          = -999;
  tofMultiplicity  = -999;
  
  primaryVertexArray = new TClonesArray("PrimaryVertexInfo",0);

  cout <<"Created EventInfo" <<endl;
}

//__________________________________________________________
EventInfo::~EventInfo(){

  delete primaryVertexArray;

}

//__________________________________________________________
Bool_t EventInfo::IsInterestingEvent(StMuDst *dst){

  //Very broad event cuts...These are not analysis cuts!
  
  if (dst->primaryVertices()->GetEntries() == 0)
    return false;
	
   return true;
}

//__________________________________________________________
Bool_t EventInfo::IsInterestingVertex(StMuDst *dst, StDataCollectionMaker *dataCollector){

  //The user can pass in min and max values for vertex cuts.
  //If the user has specified these cuts we test them here

  //Get the Vertex Location of the current vertex index
  StMuEvent *event = dst->event();

  //Get the Number of Primary Tracks for this primary vertex
  Int_t nPrimaryTracks = dst->primaryTracks()->GetEntries();

  //Number of Primary Tracks Cuts
  if (dataCollector->isMinNumberOfPrimaryTracksSet && 
      nPrimaryTracks < dataCollector->GetMinNumberOfPrimaryTracks())
    return false;

  //Get the Vertex Position
  Double_t xVertex = event->primaryVertexPosition().x();
  Double_t yVertex = event->primaryVertexPosition().y();
  Double_t zVertex = event->primaryVertexPosition().z();

  //Z-Vertex Cuts
  if (dataCollector->isMinVzSet && zVertex < dataCollector->GetMinVz())
    return false;
  if (dataCollector->isMaxVzSet && zVertex > dataCollector->GetMaxVz())
    return false;

  //X-Vertex Cuts
  if (dataCollector->isMinVxSet && xVertex < dataCollector->GetMinVx())
    return false;
  if (dataCollector->isMaxVxSet && xVertex > dataCollector->GetMaxVx())
    return false;

  //Y-Vertex Cuts
  if (dataCollector->isMinVySet && yVertex < dataCollector->GetMinVy())
    return false;
  if (dataCollector->isMaxVySet && yVertex < dataCollector->GetMaxVy())
    return false;

  //Compute the Radial Vertex
  Double_t rVertex = sqrt(pow(xVertex,2.0) + pow(yVertex,2.0));

  //R-Vertex Cuts
  if (dataCollector->isMinVrSet && rVertex < dataCollector->GetMinVr())
    return false;
  if (dataCollector->isMaxVrSet && rVertex > dataCollector->GetMaxVr())
    return false;

  //If we make it this far then the vertex passes the cuts
  //so it is interesting
  return true;
}

//__________________________________________________________
void EventInfo::SetEventInfo(StMuDst *dst,StDataCollectionMaker *dataCollector){

  StMuEvent *event = dst->event();
  
  runNumber        = event->runNumber();
  eventNumber      = event->eventNumber();
  nPrimaryVertices = dst->primaryVertices()->GetEntries();
  nPileUpVertices  = event->eventSummary().numberOfPileupVertices();
  adcSumBBCWest    = event->bbcTriggerDetector().adcSumWest();
  adcSumBBCEast    = event->bbcTriggerDetector().adcSumEast();
  meanPt           = event->eventSummary().meanPt();
  meanEta          = event->eventSummary().meanEta();
  triggerIDs       = event->triggerIdCollection().nominal().triggerIds();
  tofMultiplicity  = event->triggerData()->tofMultiplicity();

  //Loop Over the Primary Vertices and Fill the Primary Vertex Array
  for (Int_t iVertex=0; iVertex < nPrimaryVertices; iVertex++){
    
    //THIS IS EXTREMELY IMPORTANT AND MUST BE DONE FIRST!
    //It tells the StMuDst class which primary vertex index
    //you are interested in information from. After this call,
    //any vertex information you obtain from StMuEvent will
    //be particular to this vertex index.
    dst->setVertexIndex(iVertex);

    //Check that this vertex passes the user specified cuts
    //if there are any
    if (!IsInterestingVertex(dst,dataCollector))
      continue;

    //Add the vertex to the primary vertex array
    AddPrimaryVertex(dst);
  }

}

//__________________________________________________________
void EventInfo::AddPrimaryVertex(StMuDst *dst){

  //Add the current primary vertex to the end of the primary
  //vertex array.
  Int_t position = primaryVertexArray->GetEntries();
  PrimaryVertexInfo *tempVertex = 
    (PrimaryVertexInfo *)primaryVertexArray->ConstructedAt(position);

  //Set the RefMult user range.
  tempVertex->SetRefMultUserRange(-1.8,0);

  //NOTE: If the user has specified vertex cuts then the vertex index
  //      in the DavisDST format will be different than the vertex
  //      index in the MuDST format. Hence, we keep a variable
  //      in PrimaryVertexIndex to keep track of which MuDST index
  //      this vertex is.

  //Set the primary vertex info
  tempVertex->SetPrimaryVertexInfo(dst,dst->currentVertexIndex());
}

//__________________________________________________________ 
void EventInfo::ResetEventInfo(){

  runNumber = -999;
  eventNumber = -999;
  nPrimaryVertices = 0;

  primaryVertexArray->Delete();
}

//__________________________________________________________
void EventInfo::PrintEventInfo(){

  cout <<"RunNumber: " <<runNumber <<"\n"
       <<"EventNumber: " <<eventNumber <<"\n"
       <<"nPrimaryVertices: " <<nPrimaryVertices <<"\n"
       <<"VertexArraySize: " <<primaryVertexArray->GetEntries() <<"\n"
       <<"TriggerID 0: " <<triggerIDs.size() <<"\n";

  if (nPrimaryVertices > 0)
    ((PrimaryVertexInfo *)primaryVertexArray->At(0))->PrintPrimaryVertexInfo();
}

