#include <iostream>
#include "TObject.h"
#include "TVector3.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TrackInfo.h"

ClassImp(TrackInfo);

//__________________________________________________________
TrackInfo::TrackInfo(){
  
  parentVertex = -999;
  nHits = -999;
  nHitsFit = -999;
  nHitsPoss = -999;
  dEdxHits = -999;
  flag = -999;
  pZ = -999;
  pT = -999;
  charge = -999;
  dEdxTruncated = -999;
  dEdxFit = -999;
  tof = -999;
  tofBeta = -999;
  eta = -999;
  phi =-999;
  nSigmaElectron = -999;
  nSigmaPion = -999;
  nSigmaKaon = -999;
  nSigmaProton = -999;
  length = -999;
  lengthMeasured = -999;
  chi2 = -999;
  nSigmaElectronTOF = -999;
  nSigmaPionTOF = -999;
  nSigmaKaonTOF = -999;
  nSigmaProtonTOF = -999;
  yLocalTOF = -999;
  zLocalTOF = -999;
  pathLengthTOF = -999;
  globalDCA.SetXYZ(-999,-999,-999);
  firstPoint.SetXYZ(-999,-999,-999);
  lastPoint.SetXYZ(-999,-999,-999);
  tofMatchFlag = 0;
}

//_________________________________________________________
TrackInfo::~TrackInfo(){

  //Nothing to do here!

}

//_________________________________________________________
void TrackInfo::SetTrackInfo(StMuTrack *track, Int_t vertexIndex){
  
  parentVertex      = vertexIndex;
  nHits             = track->nHits();
  nHitsFit          = track->nHitsFit();
  nHitsPoss         = track->nHitsPoss();
  dEdxHits          = track->nHitsDedx();
  flag              = track->flag();
  pZ                = track->p().z();
  pT                = track->pt();
  charge            = track->charge();
  dEdxTruncated     = track->probPidTraits().dEdxTruncated();
  dEdxFit           = track->probPidTraits().dEdxFit();
  tof               = track->btofPidTraits().timeOfFlight();
  tofBeta           = track->btofPidTraits().beta();
  eta               = track->eta();
  phi               = track->phi();
  nSigmaElectron    = track->nSigmaElectron();
  nSigmaPion        = track->nSigmaPion();
  nSigmaKaon        = track->nSigmaKaon();
  nSigmaProton      = track->nSigmaProton();
  length            = track->length();
  lengthMeasured    = track->lengthMeasured();
  chi2              = track->chi2();
  nSigmaElectronTOF = track->btofPidTraits().sigmaElectron();
  nSigmaPionTOF     = track->btofPidTraits().sigmaPion();
  nSigmaKaonTOF     = track->btofPidTraits().sigmaKaon();
  nSigmaProtonTOF   = track->btofPidTraits().sigmaProton();
  yLocalTOF         = track->btofPidTraits().yLocal();
  zLocalTOF         = track->btofPidTraits().zLocal();
  pathLengthTOF     = track->btofPidTraits().pathLength();


  globalDCA.SetXYZ(track->dcaGlobal().x(),track->dcaGlobal().y(),track->dcaGlobal().z());
  firstPoint.SetXYZ(track->firstPoint().x(),track->firstPoint().y(),track->firstPoint().z());
  lastPoint.SetXYZ(track->lastPoint().x(),track->lastPoint().y(),track->lastPoint().z());
  tofMatchFlag = track->btofPidTraits().matchFlag();
}

//_________________________________________________________
void TrackInfo::PrintTrackInfo(){

  cout <<"parentVertex: " <<parentVertex <<"\n";

}
