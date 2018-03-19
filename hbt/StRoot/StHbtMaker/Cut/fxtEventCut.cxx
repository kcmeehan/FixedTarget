#include "StHbtMaker/Cut/fxtEventCut.h"
#include <cstdio>

#ifdef __ROOT__
ClassImp(fxtEventCut)
#endif

fxtEventCut::fxtEventCut(){
  mNEventsPassed =  mNEventsFailed = 0;
} 

Bool_t fxtEventCut::Pass(const StHbtEvent* event){
  Int_t triggerId = event->TriggerId();
  Int_t mult = event->NumberOfGoodPrimaryTracks();
  Int_t nTofMatches = event->NumberOfTofMatches();
  Float_t Vx = event->PrimVertPos().x();
  Float_t Vy = event->PrimVertPos().y();
  Float_t Vz = event->PrimVertPos().z();

  Bool_t goodEvent =
    ((mult >= mMult[0]) && 
     (mult < mMult[1]) && 
     (nTofMatches >= mMinTofMatches) && 
     (triggerId == mTriggerId) && 
     (Vx > mVx[0]) &&
     (Vx < mVx[1]) &&
     (Vy > mVy[0]) &&
     (Vy < mVy[1]) &&
     (Vz > mVz[0]) &&
     (Vz < mVz[1]));

  goodEvent ? mNEventsPassed++ : mNEventsFailed++ ;
  return (goodEvent);
}
//------------------------------
StHbtString fxtEventCut::Report(){
  string Stemp;
  char Ctemp[300];
  sprintf(Ctemp,"\nMultiplicity:\t %E-%E",mMult[0],mMult[1]);
  Stemp = Ctemp;
  sprintf(Ctemp,"\nTrigger Id:\t %d",mTriggerId);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nMin Tof Matches:\t %d",mMinTofMatches);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nVertex X-position:\t %E-%E",mVx[0],mVx[1]);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nVertex Y-position:\t %E-%E",mVy[0],mVy[1]);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nVertex Z-position:\t %E-%E",mVz[0],mVz[1]);
  Stemp += Ctemp;
  sprintf(Ctemp,"\nNumber of events which passed:\t%ld  Number which failed:\t%ld",mNEventsPassed,mNEventsFailed);
  Stemp += Ctemp;
  StHbtString returnThis = Stemp;
  return returnThis;
}
