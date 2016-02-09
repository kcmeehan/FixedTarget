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
  Int_t nPrimaryVertices; //Number of vertices passing cuts
  Int_t runNumber;        //Run Number
  Int_t eventNumber;      //Event Number
  Int_t nPileUpVertices;  //Number of Pile-Up vertices reported in MuDst
  Int_t adcSumBBCWest;    //Sum of ADC values from BBC West
  Int_t adcSumBBCEast;    //Sum of ADC values from BBC East
  Int_t tofMultiplicity;  //Total Number of ToF Modules with a hit
  Float_t meanPt;         //Average Pt for all global tracks in this event
  Float_t meanEta;        //Averate Eta for all global tracks in this event
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
  Int_t GetNPrimaryVertices(){return nPrimaryVertices;}
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
