#ifndef PRIMARYVERTEX_INFO_H
#define PRIMARYVERTEX_INFO_H

//Forward Declarations
class TClonesArray;
class StMuDst;
class StMuTrack;
class TTree;

class TrackInfo;

//PrimaryVertexInfo Class Definition
class PrimaryVertexInfo : public TObject {

 private:
  Int_t trackStartIndex;  //Index in the track tree
  Int_t trackStopIndex;   //Index in the track tree
  Int_t vertexIndexMuDst; //Index of vertex in the MuDst
  Int_t nPrimaryTracks;   //Number of Primary Tracks
  Int_t ntofMatches;      //Number of Primary Tracks with Tof Matches
  Int_t nPions;           //Rough estimate of number of pions
  Float_t refMult;        //Standard RefMult |dN/dEta| < .5
  Float_t refMultUser;    //RefMult in User defined Range 
  Float_t refMultPosY;    //RefMult in [0.1)
  Float_t refMultNegY;    //RefMult in [-1,0)
  Float_t xVertex;        //X Vertex location (cm)
  Float_t yVertex;        //Y Vertex location (cm)
  Float_t zVertex;        //Z Vertex location (cm)

  Float_t refMultUserEtaLow;  //!
  Float_t refMultUserEtaHigh; //!

  TrackInfo *track;           //!
  TClonesArray *trackArray;   //!
  TClonesArray *vertexArray;  //!

 public:
  
  //Data Members
  PrimaryVertexInfo();
  virtual ~PrimaryVertexInfo();

  //Member Functions
  void SetRefMultUserRange(Float_t etaLow, Float_t etaHigh);
  void SetPrimaryVertexInfo(StMuDst *dst);
  void AddTrack(StMuTrack *track, Int_t index);
  void ResetPrimaryVertexInfo();
  void PrintPrimaryVertexInfo(Bool_t printTracks=false);
  void SetTrackPtr(TrackInfo *val);
  void SetTrackArrayPtr(TClonesArray *val);
  void SetVertexArrayPtr(TClonesArray *val);

  ClassDef(PrimaryVertexInfo,1);

};

#endif
