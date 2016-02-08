#ifndef EVENT_INFO_H
#define EVENT_INFO_H

//Forward Declarations
class TClonesArray;
class StMuDst;
class StMuTrack;
class StDataCollectionMaker;
class TTree;

class TrackInfo;
class PrimaryVertexInfo;

//EventInfo Class Definition
class EventInfo : public TObject {

 private:

  //Data Members
  Int_t nPrimaryVertices;
  Int_t runNumber;
  Int_t eventNumber;
  Int_t nPileUpVertices;
  Int_t adcSumBBCWest;
  Int_t adcSumBBCEast;
  Int_t tofMultiplicity;
  Float_t meanPt;
  Float_t meanEta;
  std::vector <unsigned int> triggerIDs;

  Float_t refMultUserLow;  //!
  Float_t refMultUserHigh; //!
  
  TrackInfo *track;  //!
  PrimaryVertexInfo *vertex; //!

  //Arrays for Vertices and Tracks
  Int_t vertexIndex; //!
  TClonesArray *vertexArray; //!
  TClonesArray *trackArray;  //!

 public:

  //Constructor/Destructor
  EventInfo();
  virtual ~EventInfo();

  //Member Functions
  Bool_t IsInterestingEvent(StMuDst *dst);
  Bool_t IsInterestingVertex(StMuDst *dst, StDataCollectionMaker *dataCollector);
  void SetEventInfo(StMuDst *dst, StDataCollectionMaker *dataCollector);
  void AddPrimaryVertex(StMuDst *dst);
  void ResetEventInfo();
  void PrintEventInfo(Bool_t printVertices=false, Bool_t printTracks=false);
  void SetTrackArrayPtr(TClonesArray *val);
  void SetVertexArrayPtr(TClonesArray *val);
  void SetRefMultUser(Float_t low, Float_t high){refMultUserLow=low; refMultUserHigh=high;}


  ClassDef(EventInfo,1);

};

#endif
