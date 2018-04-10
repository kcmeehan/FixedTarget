#ifndef TRACK_INFO_H
#define TRACK_INFO_H

#include "TVector3.h"

//Forward Declarations
class StMuTrack;
class TVector3;

//StTrackInfo Class Definition
class TrackInfo : public TObject {

 public:

  TrackInfo();
  virtual ~TrackInfo();

  //Note: All Variables are for the primary track
  //      unless prefixed with global.

  //Data Members
  Int_t parentVertex;
  Int_t nHits;
  Int_t nHitsFit;
  Int_t nHitsPoss;
  Int_t dEdxHits;
  Int_t charge;
  short flag;
  Float_t pZ;
  Float_t pT;
  Float_t dEdxTruncated;
  Float_t dEdxFit;
  Float_t tof;
  Float_t tofBeta;
  Float_t eta;
  Float_t phi;
  Float_t nSigmaElectron;
  Float_t nSigmaPion;
  Float_t nSigmaKaon;
  Float_t nSigmaProton;
  Float_t length;
  Float_t lengthMeasured;
  Float_t chi2;
  Float_t nSigmaElectronTOF;
  Float_t nSigmaPionTOF;
  Float_t nSigmaKaonTOF;
  Float_t nSigmaProtonTOF;
  Float_t yLocalTOF;
  Float_t zLocalTOF;
  Float_t pathLengthTOF;

  TVector3 globalDCA;
  TVector3 firstPoint;
  TVector3 lastPoint;

  unsigned char tofMatchFlag;

  //Member Functions
  void SetTrackInfo(StMuTrack *track, Int_t trackIndex);
  void PrintTrackInfo();

  ClassDef(TrackInfo,1);

};

#endif
