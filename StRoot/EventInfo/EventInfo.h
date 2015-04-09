#ifndef EVENT_INFO_H
#define EVENT_INFO_H

//Forward Declarations
class TClonesArray;
//class TrackInfo;
class StMuDst;
class StMuTrack;

//EventInfo Class Definition
class EventInfo : public TObject {

 public:

  //Data Memebers
  EventInfo();
  virtual ~EventInfo();

  Int_t runNumber;
  Int_t eventNumber;
  Int_t nPrimaryVertices;
  std::vector <unsigned int> triggerIDs;
  unsigned short tofMultiplicity;

  //TClonesArray *trackArray;
  TClonesArray *primaryVertexArray;

  //Member Functions
  Bool_t IsInterestingEvent(StMuDst *dst);
  void SetEventInfo(StMuDst *dst);
  //void AddTrack(StMuTrack *track, Int_t pos);
  void AddPrimaryVertex(StMuDst *dst, Int_t pos);
  void ResetEventInfo();
  void PrintEventInfo();

  ClassDef(EventInfo,1);

};

#endif
