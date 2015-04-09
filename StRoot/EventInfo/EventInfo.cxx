#include <TObject.h>
#include "TClonesArray.h"
#include "TVector3.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StEvent/StTriggerData.h"

#include "StRoot/PrimaryVertexInfo/PrimaryVertexInfo.h"
#include "EventInfo.h"

ClassImp(EventInfo);

//___________________________________________________________
EventInfo::EventInfo(){

  runNumber = -999;
  eventNumber = -999;
  nPrimaryVertices = 0;
  tofMultiplicity = 0;

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

//__________________________________________________________
void EventInfo::SetEventInfo(StMuDst *dst){

  StMuEvent *event = dst->event();
  
  runNumber = event->runNumber();
  eventNumber = event->eventNumber();
  nPrimaryVertices = dst->primaryVertices()->GetEntries();
  triggerIDs = event->triggerIdCollection().nominal().triggerIds();
  tofMultiplicity = event->triggerData()->tofMultiplicity();

  //Loop Over the Primary Vertices and Fill the Primary Vertex Array
  for (Int_t iVertex=0; iVertex < nPrimaryVertices; iVertex++){
    dst->setVertexIndex(iVertex);
    AddPrimaryVertex(dst,iVertex);
  }


}

//__________________________________________________________
void EventInfo::AddPrimaryVertex(StMuDst *dst, Int_t pos){

  PrimaryVertexInfo *tempVertex = (PrimaryVertexInfo *)primaryVertexArray->ConstructedAt(pos);
  tempVertex->SetRefMultUserRange(-1.8,0);

  tempVertex->SetPrimaryVertexInfo(dst,dst->currentVertexIndex());
}


//__________________________________________________________
void EventInfo::ResetEventInfo(){

  runNumber = -999;
  eventNumber = -999;
  nPrimaryVertices = 0;

  primaryVertexArray->Clear();
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
