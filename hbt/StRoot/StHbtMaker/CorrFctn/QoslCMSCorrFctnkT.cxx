#include "StHbtMaker/CorrFctn/QoslCMSCorrFctnkT.h"
#include <cstdio>
#include "StHbtMaker/Infrastructure/StHbtReactionPlaneAnalysis.h"
#include "PhysicalConstants.h"
#include "TString.h"
#include "TH3S.h"

#ifdef __ROOT__ 
ClassImp(QoslCMSCorrFctnkT)
#endif
//____________________________
QoslCMSCorrFctnkT::QoslCMSCorrFctnkT(char* title, const int& nbinso, const float& QoLo, const float& QoHi,
			   const int& nbinss, const float& QsLo, const float& QsHi,
			   const int& nbinsl, const float& QlLo, const float& QlHi){

  mCorrection = new StHbtCoulomb;
  mCorrection->SetRadius(5.0);
  mCorrection->SetChargeProduct(1.0);

	qMax = QoHi;

  nKtBins = 5;
  
   	for(int j=0; j<nKtBins; j++) {
      TString TitKt=Form("_kt%i",j);

      // set up numerator
      TString TitNum = "Num";
      TitNum += title;
      TitNum += TitKt.Data();
      mNumerator[j] = new TH3S(TitNum.Data(),TitNum.Data(),nbinso,QoLo,QoHi,
				    nbinss,QsLo,QsHi,
				    nbinsl,QlLo,QlHi);

      // set up denominator
      TString TitDen = "Den";
      TitDen += title;
      TitDen += TitKt.Data();
      mDenominator[j] = new TH3S(TitDen.Data(),TitDen.Data(),nbinso,QoLo,QoHi,
				      nbinss,QsLo,QsHi,
				      nbinsl,QlLo,QlHi);

      //// set up ave qInv
      //char TitQinv[100] = "Qinv";
      //strcat(TitQinv,title);
      //strcat(TitQinv,TitAngle.Data());
      //strcat(TitQinv,TitKt.Data());
      //mQinvHisto[i][j] = new StHbt3DHisto(TitQinv,TitQinv,nbinso,QoLo,QoHi,nbinss,QsLo,QsHi,nbinsl,QlLo,QlHi);

      // set up ave qInv
      TString TitCoul = "Coul";
      TitCoul += title;
      TitCoul += TitKt.Data();
 	   	mCoulHisto[j] = new StHbt3DHisto(TitCoul.Data(),TitCoul.Data(),nbinso,QoLo,QoHi,nbinss,QsLo,QsHi,nbinsl,QlLo,QlHi);

      // to enable error bar calculation...
      //mCoulHisto[i][j]->Sumw2();

    }
  
}

//____________________________
QoslCMSCorrFctnkT::~QoslCMSCorrFctnkT(){
   for(int j=0; j<nKtBins; j++) {
    delete mNumerator[j];
    delete mDenominator[j];
    delete mCoulHisto[j];
   }
}
//_________________________
void QoslCMSCorrFctnkT::Finish(){
  // here is where we should normalize, fit, etc...
//  for(int i=0; i<nRPbins; i++) {
//   for(int j=0; j<nKtBins; j++) {
//    mQinvHisto[i][j]->Divide(mDenominator[i][j]);
//   }
//  }

}

//____________________________
StHbtString QoslCMSCorrFctnkT::Report(){
  string stemp = "QoslCMS Correlation Function Report:\n";
  char ctemp[100];
  sprintf(ctemp,"Number of entries in numerator:\t%E\n",mNumerator[4]->GetEntries());
  stemp += ctemp;
  sprintf(ctemp,"Number of entries in denominator:\t%E\n",mDenominator[4]->GetEntries());
  stemp += ctemp;
  //  stemp += mCoulombWeight->Report();

  StHbtString returnThis = stemp;
  return returnThis;
}
//____________________________
void QoslCMSCorrFctnkT::AddRealPair(const StHbtPair* pair){

  int ktBin;
  ktBin = GetKtBin(pair);
  if(ktBin<0) return;
  
  double Qo = pair->qOutCMS();
  double Qs = pair->qSideCMS();
  double Ql = pair->qLongCMS();

  if(fabs(Qo)>qMax || fabs(Qs)>qMax || fabs(Ql)>qMax) return; 

  mNumerator[ktBin]->Fill(Qo,Qs,Ql);
  mNumerator[4]->Fill(Qo,Qs,Ql);
}
//____________________________
void QoslCMSCorrFctnkT::AddMixedPair(const StHbtPair* pair){

  int ktBin;
  ktBin = GetKtBin(pair);
  if(ktBin<0) return;

  //double Qinv = fabs(pair->qInv());   

  double weight = 1.0;
  if (mCorrection) weight = mCorrection->CoulombCorrect(pair);

  double Qo = pair->qOutCMS();
  double Qs = pair->qSideCMS();
  double Ql = pair->qLongCMS();

	if(fabs(Qo)>qMax || fabs(Qs)>qMax || fabs(Ql)>qMax) return; 

  mDenominator[ktBin]->Fill(Qo,Qs,Ql);
  mCoulHisto[ktBin]->Fill(Qo,Qs,Ql,weight);
  mDenominator[4]->Fill(Qo,Qs,Ql);
  mCoulHisto[4]->Fill(Qo,Qs,Ql,weight);

}
//____________________________
int QoslCMSCorrFctnkT::GetKtBin(const StHbtPair* pair) {

  double kT = fabs(pair->kT());
  int ktBin;

  if(kT<0.15 || kT>0.6) return -1;
  
  if(kT<0.25) 
    ktBin = 0;
  else if( kT >= 0.25 && kT < 0.35 ) 
    ktBin = 1;
  else if( kT >= 0.35 && kT < 0.45 ) 
    ktBin = 2;
  else if( kT >= 0.45 && kT <= 0.6 ) 
    ktBin = 3;

  return ktBin;

}
//____________________________
void QoslCMSCorrFctnkT::SetCorrection(StHbtCoulomb* coulomb) {
  mCorrection = coulomb;
}


