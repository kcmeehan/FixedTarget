#ifndef STAR_StDataCollectionMaker_MAKER
#define STAR_StDataCollectionMaker_MAKER

#ifndef StMaker_H
#include "StMaker.h"
#endif

//Classes Used in the .cxx File                                              
class TFile;
class EventInfo;
class TBranch;

class StDataCollectionMaker : public StMaker {
  
 public:
  StDataCollectionMaker(char *name);
  ~StDataCollectionMaker();
  
  Int_t Init();
  virtual void Clear(const char *opt="");
  Int_t Make();
  Int_t Finish();
  void SetFileIndex(char *val) {mFileIndex=val;}
  void SetOutDir(char *val) {mOutDir=val;}

  //These boolean variables will let us
  //know if the user has specified any vertex cuts
  Bool_t isMinVrSet, isMaxVrSet;
  Bool_t isMinVzSet, isMaxVzSet;
  Bool_t isMinVxSet, isMaxVxSet;
  Bool_t isMinVySet, isMaxVySet;
  Bool_t isBeamSpotSet;
  Bool_t isMinNumberOfPrimaryTracksSet;

  //Sets and Gets for the Vertex Cuts
  void SetMinVr(Double_t val);
  void SetMaxVr(Double_t val);
  void SetMinVz(Double_t val);
  void SetMaxVz(Double_t val);
  void SetMinVx(Double_t val);
  void SetMaxVx(Double_t val);
  void SetMinVy(Double_t val);
  void SetMaxVy(Double_t val);
  void SetBeamSpot(Double_t xVal, Double_t yVal);
  void SetMinNumberOfPrimaryTracks(Int_t val);
  
  Double_t GetMinVr(){return minVr;}
  Double_t GetMaxVr(){return maxVr;}
  Double_t GetMinVz(){return minVz;}
  Double_t GetMaxVz(){return maxVz;}
  Double_t GetMinVx(){return minVx;}
  Double_t GetMaxVx(){return maxVx;}
  Double_t GetMinVy(){return minVy;}
  Double_t GetMaxVy(){return maxVy;}
  Double_t GetBeamSpotX(){return beamSpotX;}
  Double_t GetBeamSpotY(){return beamSpotY;}
  Int_t GetMinNumberOfPrimaryTracks(){return minNumberOfPrimaryTracks;}

 private:
  
  char *fileNameBase;
  char *mFileIndex;
  char *mOutDir;
  
  //Output File                                                              
  TFile *outFile;
  TTree *outTree;
  TBranch *outBranch;

  EventInfo *eventInfo;

  //Variables to hold the values of the cuts
  //if the user chooses to use them
  Double_t minVr, maxVr;
  Double_t minVz, maxVz;
  Double_t minVx, maxVx;
  Double_t minVy, maxVy;
  Double_t beamSpotX, beamSpotY;
  Int_t minNumberOfPrimaryTracks;

  ClassDef(StDataCollectionMaker, 1);
  
};

#endif
