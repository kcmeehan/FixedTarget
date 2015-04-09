#include "TObject.h"
#include "TVector3.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "TrackInfo.h"

ClassImp(TrackInfo);

//__________________________________________________________
TrackInfo::TrackInfo(){

  nHits = -999;
  nHitsFit = -999;
  nHitsPoss = -999;
  dEdxHits = -999;
  flag = -999;
  pZ = -999;
  pT = -999;
  charge = -999;
  dEdx = -999;
  tof = -999;
  tofBeta = -999;
  eta = -999;
  phi =-999;
  nSigmaElectron = -999;
  nSigmaPion = -999;
  nSigmaKaon = -999;
  nSigmaProton = -999;
  length = -999;
  chi2 = -999;
  globalDCA.SetXYZ(-999,-999,-999);
  firstPoint.SetXYZ(-999,-999,-999);
  lastPoint.SetXYZ(-999,-999,-999);
  tofMatchFlag = 0;
}

//_________________________________________________________
TrackInfo::~TrackInfo(){

  

}

//_________________________________________________________
void TrackInfo::SetTrackInfo(StMuTrack *track){
  
  nHits = track->nHits();
  nHitsFit = track->nHitsFit();
  nHitsPoss = track->nHitsPoss();
  dEdxHits = track->nHitsDedx();
  flag = track->flag();
  pZ = track->p().z();
  pT = track->pt();
  charge = track->charge();
  dEdx = track->dEdx();
  tof = track->btofPidTraits().timeOfFlight();
  tofBeta = track->btofPidTraits().beta();
  eta = track->eta();
  phi =track->phi();
  nSigmaElectron = track->nSigmaElectron();
  nSigmaPion = track->nSigmaPion();
  nSigmaKaon = track->nSigmaKaon();
  nSigmaProton = track->nSigmaProton();
  length = track->length();
  chi2 = track->chi2();
  globalDCA.SetXYZ(track->dcaGlobal().x(),track->dcaGlobal().y(),track->dcaGlobal().z());
  firstPoint.SetXYZ(track->firstPoint().x(),track->firstPoint().y(),track->firstPoint().z());
  lastPoint.SetXYZ(track->lastPoint().x(),track->lastPoint().y(),track->lastPoint().z());
  tofMatchFlag = track->btofPidTraits().matchFlag();


}

