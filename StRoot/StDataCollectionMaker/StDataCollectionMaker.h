#ifndef STAR_StDataCollectionMaker_MAKER
#define STAR_StDataCollectionMaker_MAKER

#ifndef StMaker_H
#include "StMaker.h"
#endif

//Classes Used in the .cxx File                                              
class TFile;
class TH2D;
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

	TH2D *hvyvz;
  
  
 private:
  
  char *fileNameBase;
  char *mFileIndex;
  char *mOutDir;
  
  //Output File                                                              
  TFile *outFile;
  TTree *outTree;
  TBranch *outBranch;

  EventInfo *eventInfo;

  ClassDef(StDataCollectionMaker, 1);
  
};

#endif
