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
  Int_t nHits;
  Int_t nHitsFit;
  Int_t nHitsPoss;
  Int_t dEdxHits;
  Int_t charge;
  short flag;
  Double_t pZ;
  Double_t pT;
  Double_t dEdxTruncated;
  Double_t dEdxFit;
  Double_t tof;
  Double_t tofBeta;
  Double_t eta;
  Double_t phi;
  Double_t nSigmaElectron;
  Double_t nSigmaPion;
  Double_t nSigmaKaon;
  Double_t nSigmaProton;
  Double_t length;
  Double_t lengthMeasured;
  Double_t chi2;
  Double_t nSigmaElectronTOF;
  Double_t nSigmaPionTOF;
  Double_t nSigmaKaonTOF;
  Double_t nSigmaProtonTOF;
  Double_t yLocalTOF;
  Double_t zLocalTOF;
  Double_t pathLengthTOF;

  TVector3 globalDCA;
  TVector3 firstPoint;
  TVector3 lastPoint;

  unsigned char tofMatchFlag;

  //Member Functions
  void SetTrackInfo(StMuTrack *track);

  ClassDef(TrackInfo,1);

};

#endif
