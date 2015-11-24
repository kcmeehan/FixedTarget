#ifndef PRIMARYVERTEX_INFO_H
#define PRIMARYVERTEX_INFO_H

//Forward Declarations
class TClonesArray;
class StMuDst;
class StMuTrack;

//PrimaryVertexInfo Class Definition
class PrimaryVertexInfo : public TObject {

 public:
  
  //Data Members
  PrimaryVertexInfo();
  virtual ~PrimaryVertexInfo();

  Int_t vertexIndex;
  Int_t nPrimaryTracks;
  Int_t ntofMatches;
  Int_t nPions;
  Double_t refMult;  //Standard RefMult |dN/dEta| < .5
  Double_t refMultUser; //RefMult in User defined Range
  Double_t refMultUserEtaLow;
  Double_t refMultUserEtaHigh;
  Double_t xVertex;
  Double_t yVertex;
  Double_t zVertex;

  TClonesArray *trackArray;

  //Member Functions
  void SetRefMultUserRange(Double_t etaLow, Double_t etaHigh);
  void SetPrimaryVertexInfo(StMuDst *dst, Int_t index);
  void AddTrack(StMuTrack *track, Int_t index);
  void ResetPrimaryVertexInfo();
  void PrintPrimaryVertexInfo();

  ClassDef(PrimaryVertexInfo,1);

};

#endif
