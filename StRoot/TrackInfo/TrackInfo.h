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

  //Data Members
  Int_t nHits;
  Int_t nHitsFit;
  Int_t nHitsPoss;
  Int_t dEdxHits;
  short flag;
  Double_t pZ;
  Double_t pT;
  Int_t charge;
  Double_t dEdx;
  Double_t tof;
  Double_t tofBeta;
  Double_t eta;
  Double_t phi;
  Double_t nSigmaElectron;
  Double_t nSigmaPion;
  Double_t nSigmaKaon;
  Double_t nSigmaProton;
  Double_t length;
  Double_t chi2;
  TVector3 globalDCA;
  TVector3 firstPoint;
  TVector3 lastPoint;

  unsigned char tofMatchFlag;

  //Member Functions
  void SetTrackInfo(StMuTrack *track);

  ClassDef(TrackInfo,1);

};

#endif
