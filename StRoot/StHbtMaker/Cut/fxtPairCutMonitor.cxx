#include "StHbtMaker/Infrastructure/StHbtPair.hh"
#include "StHbtMaker/Cut/fxtPairCutMonitor.h"
#include <cstdio>
#include <string>
#include "StLorentzVector.hh"

#ifdef __ROOT__ 
ClassImp(fxtPairCutMonitor)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
fxtPairCutMonitor::fxtPairCutMonitor(const char* name){ // default constructor
  string s("fxtPairCutMonitor");
  string n(name);
  mKt= new StHbt1DHisto( (s+n+"mKt").c_str(),"Kt",1500,0.0,1.5); 
  mFractionOfMergedRow= new StHbt1DHisto( (s+n+"mFractionOfMergedRow").c_str(),"Fraction of Merged Hits",100,0.,1.); 
  mSplittingLevel= new StHbt1DHisto( (s+n+"mSplittingLevel").c_str(),"Splitting Level",17,-0.6,1.1); 
  mPairRapidityVsEmissionAngle= new StHbt2DHisto( (s+n+"mPairRapidityVsEmissionAngle").c_str(),"Pair Rapidity vs EmissionAngle",180,0.,360, 200,-1.,1.);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
fxtPairCutMonitor::fxtPairCutMonitor( const  fxtPairCutMonitor& cutMoni)  {
  mKt =new StHbt1DHisto(*(cutMoni.mKt));
  mFractionOfMergedRow =new StHbt1DHisto(*(cutMoni.mFractionOfMergedRow));
  mSplittingLevel =new StHbt1DHisto(*(cutMoni.mSplittingLevel));
  mPairRapidityVsEmissionAngle = new StHbt2DHisto(*(cutMoni.mPairRapidityVsEmissionAngle));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
fxtPairCutMonitor::~fxtPairCutMonitor(){
  delete mKt;
  delete mFractionOfMergedRow;
  delete mSplittingLevel ;
  delete mPairRapidityVsEmissionAngle;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  fxtPairCutMonitor::Fill(const StHbtPair* pair){
  mKt->Fill( pair->kT(), 1.);
  mFractionOfMergedRow->Fill( pair->getFracOfMergedRow(), 1.);
  mSplittingLevel->Fill(pair->quality(), 1.);
  mPairRapidityVsEmissionAngle->Fill(pair->emissionAngle(), pair->rap(), 1.);
}


