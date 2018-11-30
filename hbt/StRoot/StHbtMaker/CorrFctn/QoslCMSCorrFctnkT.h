#ifndef QoslCMSCorrFctnkT_hh
#define QoslCMSCorrFctnkT_hh

#include "StHbtMaker/Base/StHbtCorrFctn.hh"
#include "StHbtMaker/Base/StHbtPairCut.h"
#include "StHbtMaker/Infrastructure/StHbtCoulomb.h"

class TH3S;

class QoslCMSCorrFctnkT : public StHbtCorrFctn {
public:
  QoslCMSCorrFctnkT(char* title, const int& nbinso, const float& QoLo, const float& QoHi,
	       const int& nbinss, const float& QsLo, const float& QsHi,
	       const int& nbinsl, const float& QlLo, const float& QlHi);
  virtual ~QoslCMSCorrFctnkT();

  virtual StHbtString Report();
  virtual void AddRealPair(const StHbtPair*);
  virtual void AddMixedPair(const StHbtPair*);
  void SetCorrection(StHbtCoulomb*);
  void SetSpecificPairCut(StHbtPairCut*);

  virtual void Finish();

  float qMax;
	
  int nKtBins;
  
  TH3S* Numerator3D(const int& ktBin);
  TH3S* Denominator3D(const int& ktBin);
  StHbt3DHisto* QinvHisto3D(const int& ktBin);
  StHbt3DHisto* CoulHisto3D(const int& ktBin);

private:
  TH3S* mNumerator[5];
  TH3S* mDenominator[5];
  StHbt3DHisto* mQinvHisto[5];
  StHbt3DHisto* mCoulHisto[5];

  StHbtCoulomb* mCorrection; //!
  StHbtPairCut* mPairCut;    //! this is a PairCut specific to THIS CorrFctn

  int GetKtBin(const StHbtPair*);
  
#ifdef __ROOT__ 
  ClassDef(QoslCMSCorrFctnkT, 1)
#endif
};

inline  TH3S* QoslCMSCorrFctnkT::Numerator3D(const int& ktBin){return mNumerator[ktBin];}
inline  TH3S* QoslCMSCorrFctnkT::Denominator3D(const int& ktBin){return mDenominator[ktBin];}
inline  StHbt3DHisto* QoslCMSCorrFctnkT::QinvHisto3D(const int& ktBin){return mQinvHisto[ktBin];}
inline  StHbt3DHisto* QoslCMSCorrFctnkT::CoulHisto3D(const int& ktBin){return mCoulHisto[ktBin];}
inline  void QoslCMSCorrFctnkT::SetSpecificPairCut(StHbtPairCut* pc){mPairCut=pc;}

#endif

