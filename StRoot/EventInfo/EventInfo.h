#ifndef EVENT_INFO_H
#define EVENT_INFO_H

//Forward Declarations
class TClonesArray;
class StMuDst;
class StMuTrack;
class StDataCollectionMaker;

//EventInfo Class Definition
class EventInfo : public TObject {

 public:

  //Data Members
  EventInfo();
  virtual ~EventInfo();

  Int_t runNumber;
  Int_t eventNumber;
  Int_t nPrimaryVertices;
  Int_t nPileUpVertices;
  Int_t adcSumBBCWest;
  Int_t adcSumBBCEast;
  Double_t meanPt;
  Double_t meanEta;
  
  std::vector <unsigned int> triggerIDs;
  unsigned short tofMultiplicity;

  TClonesArray *primaryVertexArray;

  //Member Functions
  Bool_t IsInterestingEvent(StMuDst *dst);
  Bool_t IsInterestingVertex(StMuDst *dst, StDataCollectionMaker *dataCollector);
  void SetEventInfo(StMuDst *dst, StDataCollectionMaker *dataCollector);
  void AddPrimaryVertex(StMuDst *dst);
  void ResetEventInfo();
  void PrintEventInfo();

  ClassDef(EventInfo,1);

};

#endif
