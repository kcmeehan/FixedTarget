#include "TObject.h"
#include "TMath.h"
#include "TF1.h"
#include "TF3.h"
#include "TH1.h"
#include "TSpline.h"
#include "TGraph.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"

//define the class and make it inherit from TObject so that we can write it 
//to the root file


enum VarType_t {kdNdpt,kOneOverPtdNdpt,kOneOverMtdNdmt,kdNdmt,kOneOverMtdNdmtMinusM};


class func : public TObject {

public:
   
   func(TF1 *func, Width_t Width, VarType_t haha);
   virtual ~func();

   // spectra tools (for Boltzmann, Levi, Expt)
   Int_t GetLowestNotEmptyBin(const TGraph* h);
   Int_t GetHighestNotEmptyBin(const TGraph* h);

   void GetYield(TGraph* h, Float_t* xc, Float_t* ex, TF1 * f, TFitResultPtr fitr, Double_t &yield, Double_t &yieldError, Float_t min = 0, Float_t max = 100,  Double_t *partialYields=0, Double_t *partialYieldsErrors=0);

   void GetMeanPt(TGraph* h, Float_t* xc, Float_t* ex, Float_t* meanpT, TF1 * f, TFitResultPtr fitr, Double_t &yield, Double_t &yieldError, Float_t min = 0, Float_t max = 100,  Double_t *partialYields=0, Double_t *partialYieldsErrors=0);

   // Boltzmann-Gibbs blast wave
  TF1 * GetBGBW(Double_t mass, Double_t beta, Double_t T,
		Double_t norm, const char * name = "fBGBW");
  
  // Boltzmann
  TF1 * GetBoltzmann(Double_t mass, Double_t T, Double_t norm, const char * name ="fBoltzmann");

  // Tsallis blast wave
  TF1 * GetTsallisBW(Double_t mass, Double_t beta, Double_t T, Double_t q,
		     Double_t norm, Double_t ymax = 0.5, const char * name = "fTsallisBW");

  // Simple exponential in 1/mt*dNdmt
  TF1 * GetMTExp(Double_t mass, Double_t T, Double_t norm, const char * name ="fExp");

  // Simple exponential in 1/pt*dNdpt
  TF1 * GetPTExp(Double_t T, Double_t norm, const char * name ="fExp");

  // Tsallis (no BW, a la CMS)
  TF1 * GetTsallis(Double_t mass, Double_t T, Double_t q, Double_t norm, const char * name="fTsallis") 
  {return GetLevi (mass,T,1/(q-1),norm,name);}
  
  // Levi function (aka Tsallis)
  TF1 * GetLevi(Double_t mass, Double_t T, Double_t n, Double_t norm, const char * name="fLevi");

  // UA1 function 
  TF1 * GetUA1(Double_t mass, Double_t p0star, Double_t pt0, Double_t n, Double_t T, Double_t norm, const char * name="fUA1");

  // Function derived from a histo
  TF1 * GetHistoFunc(TH1 * h, const char * name = "fHisto");

  // Power law
  TF1 * GetPowerLaw(Double_t pt0, Double_t n, Double_t norm, const char * name="fPowerLaw");


  void SetVarType(VarType_t tp) {fVarType=tp;}

  protected:

  // dNdpt here means 1/pt dN/dpt
  
  // Boltzmann-Gibbs Blast Wave
  TF1 * GetBGBWdNdpt(Double_t mass, Double_t beta, Double_t T,
		     Double_t norm, const char * name = "fBGBW");

  // Tsallis blast wave
  TF1 * GetTsallisBWdNdpt(Double_t mass, Double_t beta, Double_t T, Double_t q,
			  Double_t norm, Double_t ymax = 0.5, const char * name = "fTsallisBW");

  // Simple exponential in 1/mt*MT
  TF1 * GetMTExpdNdpt(Double_t mass, Double_t T, Double_t norm, const char * name ="fExp");

  // Boltzmann (exp in 1/mt*dNdmT)
  TF1 * GetBoltzmanndNdpt(Double_t mass, Double_t T, Double_t norm, const char * name ="fBoltzmann");

  // Tsallis (no BW, a la CMS)
  TF1 * GetTsallisdNdpt(Double_t mass, Double_t T, Double_t q, Double_t norm, const char * name="fTsallis");

  // Levi function
  TF1 * GetLevidNdpt(Double_t mass, Double_t T, Double_t n, Double_t norm, const char * name="fLevi");

  // Power Law function
  TF1 * GetPowerLawdNdpt(Double_t pt0, Double_t n, Double_t norm, const char * name="fLevi");

  // UA1 function
  TF1 * GetUA1dNdpt(Double_t pt0, Double_t n, Double_t norm, const char * name="fLevi");

  // TimesPt means dNdpt

  // Boltzmann-Gibbs Blast Wave
  TF1 * GetBGBWdNdptTimesPt(Double_t mass, Double_t beta, Double_t T,
			    Double_t norm, const char * name = "fBGBWTimesPt");

  // Tsallis blast wave
  TF1 * GetTsallisBWdNdptTimesPt(Double_t mass, Double_t beta, Double_t T, Double_t q,
				 Double_t norm, Double_t ymax = 0.5, const char * name = "fTsallisBWTimesPt");
  // Levi function
  TF1 * GetLevidNdptTimesPt(Double_t mass, Double_t T, Double_t n, Double_t norm, const char * name="fLevi");

  // UA1 function
  TF1 * GetUA1dNdptTimesPt(Double_t pt0, Double_t n, Double_t norm, const char * name="fLevi");

  // PowerLaw function
  TF1 * GetPowerLawdNdptTimesPt(Double_t pt0, Double_t n, Double_t norm, const char * name="fLevi");

  // Simple exponential in 1/mt*dNdmT
  TF1 * GetMTExpdNdptTimesPt(Double_t mass, Double_t T, Double_t norm, const char * name ="fMtExpTimesPt");

  // Simple exponential in 1/mp*dNdpT
  TF1 * GetPTExpdNdptTimesPt(Double_t T, Double_t norm, const char * name ="fPtExpTimesPt");

  // Boltzmann (exp in 1/mt*dNdmT times mt)
  TF1 * GetBoltzmanndNdptTimesPt(Double_t mass, Double_t T, Double_t norm, const char * name ="fBoltzmannTimesPt");

  // Tsallis (no BW, a la CMS)
  TF1 * GetTsallisdNdptTimesPt(Double_t mass, Double_t T, Double_t q, Double_t norm, const char * name="fTsallisTimesPt");

  // 1/mt dNdmt
  
  // Levi
  TF1 * GetLevidNdmt(Double_t mass, Double_t T, Double_t n, Double_t norm, const char * name = "fLeviMt", VarType_t var = kOneOverMtdNdmt);

  // gereral setters
  void SetLineWidth(Width_t width) { fLineWidth = width;}

  TF1 * GetTestFunc(Double_t mass, Double_t T, Double_t norm, Double_t ymax, const char * name ="fTest") ;

  // static functions for TF1
  // Boltzmann-Gibbs Blast Wave
  static Double_t StaticBGdNdPt(const double * x, const double* p);
  static Double_t StaticBGdNdPtTimesPt(const double * x, const double* p);
  // Tsallis blast wave
  static Double_t StaticTsallisdNdPt(const double * x, const double* p);
  static Double_t StaticTsallisdNdPtTimesPt(const double * x, const double* p);
  // Helper funcs for numeric integration
  static Double_t IntegrandBG(const double * x, const double* p);
  static Double_t IntegrandTsallis(const double * x, const double* p);

  // Test func
  static Double_t StaticTest(const double * x, const double* p);
  static Double_t IntegrandTest(const double * x, const double* p);

  // histo func
  static Double_t StaticHistoFunc(const double * x, const double* p);

  // UA1 parametrization
  static Double_t StaticUA1Func(const double * x, const double* p);

   private:


  TF1 * fLastFunc;     // Last function returned
  Width_t fLineWidth;  // Line width
  VarType_t fVarType;  // Variable types (e.g. dNdpt vs pt, 1/mt dNdmt vs mt...) 
  func(const func&);			  // not implemented
	func& operator=(const func&); // not implemented

   ClassDef (func,1)
};

//Call the ClassImp marco to give the func class RTTI and full I/O
//Capabilities.
#if !defined(__CINT__)
   ClassImp(func)
#endif

func::func(TF1 *func, Width_t Width, VarType_t haha ){

    fLastFunc = 0;
	fLineWidth = 1;
	fVarType = haha;
	cout<<"test	"<<endl;
	cout<<fLineWidth<<endl;
	cout<<fVarType<<endl;

}

func::~func(){
  // clear();
  if (fLastFunc) delete fLastFunc;
}

TF1 * func::GetHistoFunc(TH1 * h, const char * name) {

  // Regardless of the variable type, this returns a function made
  // from the histo * a multiplicative normalization.

  fLastFunc = new TF1 (name, StaticHistoFunc, 0.0, 10, 2);
  fLastFunc->SetParameter(0,1);
  fLastFunc->FixParameter(1,Double_t(Long64_t(h)));
  fLastFunc->SetParNames("norm", "pointer to histo");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;
  

}

Int_t func::GetLowestNotEmptyBin(const TGraph* h) {

  // Return the index of the lowest non empty bin in the histo h

  Double_t tx,ty;

  Int_t nbin = h->GetN();
  for(Int_t ibin = 0; ibin < nbin; ibin++){
     h->GetPoint(ibin,tx,ty);
    if(ty>0) return ibin;
  }
  
  return -1;

}

Int_t func::GetHighestNotEmptyBin(const TGraph* h) {

  // Return the index of the highest non empty bin in the histo h

  Double_t tx,ty;

  Int_t nbin = h->GetN();
  for(Int_t ibin = nbin-1; ibin >= 0; ibin--){
     h->GetPoint(ibin,tx,ty);
    if(ty>0) return ibin;
  }
  
  return -1;
}


void func::GetYield(TGraph* h, Float_t* xc, Float_t* ex, TF1 * f, TFitResultPtr fitr, Double_t &yield, Double_t &yieldError, Float_t min, Float_t max, Double_t *partialYields, Double_t *partialYieldsErrors){

  // Returns the yield extracted from the data in the histo where
  // there are points and from the fit to extrapolate, in the given
  // range.

  // Partial yields are also returned if the corresponding pointers are non null

  Int_t bin1 = GetLowestNotEmptyBin(h);
  Int_t bin2 = GetHighestNotEmptyBin(h);
  Double_t tx,ty;
  h->GetPoint(bin1,tx,ty);
  cout<<bin1<<" "<<xc[bin1]<<" "<<tx<<" "<<ty<<endl;
  Float_t bin1Edge = xc[bin1] - ex[bin1];
  h->GetPoint(bin2,tx,ty);
  cout<<bin2<<" "<<xc[bin2]<<" "<<tx<<" "<<ty<<endl;
  Float_t bin2Edge = xc[bin2] + ex[bin2];

  Double_t integralFromHistoError ;
  Double_t integralFromHisto;
  Double_t sum=0,sumerr2=0;
  for(Int_t ibin = bin1; ibin <= bin2; ibin++) {
     h->GetPoint(ibin,tx,ty);
     sum += ty*2.0*TMath::Pi()*tx*2.0*ex[ibin];
     sumerr2 += pow(2.0*TMath::Pi()*tx*2.0*ex[ibin]*h->GetErrorY(ibin),2);
  }
  integralFromHisto=sum;
  integralFromHistoError = sqrt(sumerr2);

  Double_t integralBelow      = min < bin1Edge ? f->Integral(min,bin1Edge,fitr->GetParams()) : 0;
  Double_t integralBelowError = min < bin1Edge ? f->IntegralError(min,bin1Edge,fitr->GetParams(), (fitr->GetCovarianceMatrix()).GetMatrixArray()) : 0;
  Double_t integralAbove      = max > bin2Edge ? f->Integral(bin2Edge,max,fitr->GetParams()) : 0;
  Double_t integralAboveError = max > bin2Edge ? f->IntegralError(bin2Edge,max,fitr->GetParams(), (fitr->GetCovarianceMatrix()).GetMatrixArray()) : 0;

   cout << "GetYield INFO" << endl;
   cout << " " << "bin1"<<" "<<"bin1Edge" << " " <<"bin2"<<" "<< "bin2Edge" << endl;  
   cout << " " << bin1<<" "<<bin1Edge << " " <<bin2<<" "<< bin2Edge << endl;  
   cout << " " << "integralFromHisto"      << " " << "integralBelow"      << " " << "integralAbove"      << endl;
   cout << " " << integralFromHisto      << " " << integralBelow      << " " << integralAbove      << endl;
   cout << " " << "integralFromHistoError" << " " << "integralBelowError" << " " << "integralAboveError" << endl;
   cout << " " << integralFromHistoError << " " << integralBelowError << " " << integralAboveError << endl;
  
  if(partialYields) {
    partialYields[0] = integralFromHisto;
    partialYields[1] = integralBelow;
    partialYields[2] = integralAbove;
  }
  if(partialYieldsErrors) {
    partialYieldsErrors[0] = integralFromHistoError;
    partialYieldsErrors[1] = integralBelowError;
    partialYieldsErrors[2] = integralAboveError;
  }
  yield      = integralFromHisto+integralBelow+integralAbove;
  yieldError = TMath::Sqrt(integralFromHistoError*integralFromHistoError+
			   integralBelowError*integralBelowError+
			   integralAboveError*integralAboveError);

}

void func::GetMeanPt(TGraph* h, Float_t* xc, Float_t* ex, Float_t* meanpt, TF1 * f, TFitResultPtr fitr, Double_t &yield, Double_t &yieldError, Float_t min, Float_t max, Double_t *partialYields, Double_t *partialYieldsErrors){

  // Returns the yield extracted from the data in the histo where
  // there are points and from the fit to extrapolate, in the given
  // range.

  // Partial yields are also returned if the corresponding pointers are non null

  Int_t bin1 = GetLowestNotEmptyBin(h);
  Int_t bin2 = GetHighestNotEmptyBin(h);
  Double_t tx,ty;
  h->GetPoint(bin1,tx,ty);
  cout<<bin1<<" "<<xc[bin1]<<" "<<tx<<" "<<ty<<endl;
  Float_t bin1Edge = xc[bin1] - ex[bin1];
  h->GetPoint(bin2,tx,ty);
  cout<<bin2<<" "<<xc[bin2]<<" "<<tx<<" "<<ty<<endl;
  Float_t bin2Edge = xc[bin2] + ex[bin2];

  Double_t integralFromHistoError ;
  Double_t integralFromHisto;
  Double_t sum=0,sumerr2=0;
  for(Int_t ibin = bin1; ibin <= bin2; ibin++) {
     h->GetPoint(ibin,tx,ty);
     sum += ty*2.0*TMath::Pi()*tx*2.0*ex[ibin]*meanpt[ibin];
     sumerr2 += pow(2.0*TMath::Pi()*tx*2.0*ex[ibin]*meanpt[ibin]*h->GetErrorY(ibin),2);
  }
  integralFromHisto=sum;
  integralFromHistoError = sqrt(sumerr2);

  Double_t integralBelow      = min < bin1Edge ? f->Integral(min,bin1Edge,fitr->GetParams()) : 0;
  Double_t integralBelowError = min < bin1Edge ? f->IntegralError(min,bin1Edge,fitr->GetParams(), (fitr->GetCovarianceMatrix()).GetMatrixArray()) : 0;
  Double_t integralAbove      = max > bin2Edge ? f->Integral(bin2Edge,max,fitr->GetParams()) : 0;
  Double_t integralAboveError = max > bin2Edge ? f->IntegralError(bin2Edge,max,fitr->GetParams(), (fitr->GetCovarianceMatrix()).GetMatrixArray()) : 0;

   cout << "GetYield INFO" << endl;
   cout << " " << bin1<<" "<<bin1Edge << " " <<bin2<<" "<< bin2Edge << endl;  
   cout << " " << integralFromHisto      << " " << integralBelow      << " " << integralAbove      << endl;
   cout << " " << integralFromHistoError << " " << integralBelowError << " " << integralAboveError << endl;
  
  if(partialYields) {
    partialYields[0] = integralFromHisto;
    partialYields[1] = integralBelow;
    partialYields[2] = integralAbove;
  }
  if(partialYieldsErrors) {
    partialYieldsErrors[0] = integralFromHistoError;
    partialYieldsErrors[1] = integralBelowError;
    partialYieldsErrors[2] = integralAboveError;
  }
  yield      = integralFromHisto+integralBelow+integralAbove;
  yieldError = TMath::Sqrt(integralFromHistoError*integralFromHistoError+
			   integralBelowError*integralBelowError+
			   integralAboveError*integralAboveError);

}


TF1 * func::GetBGBW(Double_t mass, Double_t beta, Double_t T,
	      Double_t norm, const char * name){

  // Boltzmann-Gibbs blast wave

  switch (fVarType) {
  case kdNdpt:
    return GetBGBWdNdptTimesPt(mass,beta,T,norm,name);
    break;
  case kOneOverPtdNdpt:
    return GetBGBWdNdpt(mass,beta,T,norm,name);
    break;
  case kOneOverMtdNdmt:
    cout<<"Not implemented"<<endl;
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;

}
  

TF1 * func::GetBoltzmann(Double_t mass, Double_t T, Double_t norm, const char * name){
  // Boltzmann
  switch (fVarType) {
  case kdNdpt:
    return GetBoltzmanndNdptTimesPt(mass, T, norm, name);
    break;
  case kOneOverPtdNdpt:
    return GetBoltzmanndNdpt(mass, T, norm, name);
    break;
  case kOneOverMtdNdmt:
    cout<<"Not implemented"<<endl;
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;

}


TF1 * func::GetTsallisBW(Double_t mass, Double_t beta, Double_t T, Double_t q,
			      Double_t norm, Double_t ymax, const char * name){

  // Tsallis blast wave
  switch (fVarType) {
  case kdNdpt:
    return GetTsallisBWdNdptTimesPt(mass,beta,T,q,norm,ymax,name);
    break;
  case kOneOverPtdNdpt:
    return GetTsallisBWdNdpt(mass,beta,T,q,norm,ymax,name);
    break;
  case kOneOverMtdNdmt:
    cout<<"Not implemented"<<endl;
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;
  
}


TF1 * func::GetMTExp(Double_t mass, Double_t T, Double_t norm, const char * name){

  // Simple exponential in 1/mt*MT
  switch (fVarType) {
  case kdNdpt:
    return GetMTExpdNdptTimesPt(mass,T,norm,name);
    break;
  case kOneOverPtdNdpt:
    return GetMTExpdNdpt(mass,T,norm,name);
    break;
  case kOneOverMtdNdmt:
    cout<<"Not implemented"<<endl;
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;


}

TF1 * func::GetPTExp(Double_t T, Double_t norm, const char * name){

  // Simple exponential in 1/mt*MT
  switch (fVarType) {
  case kdNdpt:
    return GetPTExpdNdptTimesPt(T,norm,name);
    break;
  case kOneOverPtdNdpt:
    cout<<"Not implemented"<<endl;
    break;
  case kOneOverMtdNdmt:
    cout<<"Not implemented"<<endl;
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;


}


TF1 * func::GetLevi(Double_t mass, Double_t T, Double_t n, Double_t norm, const char * name){
  // Levi function (aka Tsallis)
  switch (fVarType) {
  case kdNdpt:
    return GetLevidNdptTimesPt(mass,T,n,norm,name);
    break;
  case kOneOverPtdNdpt:
    return GetLevidNdpt(mass,T,n,norm,name);
    break;
  case kOneOverMtdNdmt:
    return GetLevidNdmt(mass,T,n,norm,name,kOneOverMtdNdmt);
    break;
  case kdNdmt:
    return GetLevidNdmt(mass,T,n,norm,name,kdNdmt);
    break;
  case kOneOverMtdNdmtMinusM:
    return GetLevidNdmt(mass,T,n,norm,name,kOneOverMtdNdmtMinusM);
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;


}

TF1 * func::GetPowerLaw(Double_t pt0, Double_t n, Double_t norm, const char * name){
  // power law Nuclear Physics B, Vol. 335, No. 2. (7 May 1990), pp. 261-287.
  // This is sometimes also called Hagedorn or modified Hagedorn

  switch (fVarType) {
  case kdNdpt:
    return GetPowerLawdNdptTimesPt(pt0,n,norm,name);
    break;
  case kOneOverPtdNdpt:
    return GetPowerLawdNdpt(pt0,n,norm,name);
    break;
  case kOneOverMtdNdmt:
    cout<<"Not Implemented"<<endl;
    //    return GetUA1dNdmt(mass,T,n,norm,name);
    break;
  default:
    cout<<"Not implemented"<<endl;
  }
  
  return 0;


}

TF1 * func::GetUA1(Double_t mass, Double_t p0star, Double_t pt0, Double_t n, Double_t T, Double_t norm, const char * name) {
  // UA1 parametrization Nuclear Physics B, Vol. 335, No. 2. (7 May 1990), pp. 261-287.

  switch (fVarType) {
  case kdNdpt:

    fLastFunc = new TF1 (name, StaticUA1Func, 0.0, 10, 6);
    fLastFunc->FixParameter(0,mass);
    fLastFunc->SetParameter(1,p0star);
    fLastFunc->SetParameter(2,pt0);
    fLastFunc->SetParameter(3,n);
    fLastFunc->SetParameter(4,T);
    fLastFunc->SetParameter(5,norm);
    fLastFunc->SetParLimits(1,0.01,1);
    fLastFunc->SetParLimits(2,0.01,100);
    fLastFunc->SetParLimits(3,0.01,100);
    fLastFunc->SetParLimits(4,0.01,100);
    fLastFunc->SetParNames("mass","p0star","pt0","n","T","norm");
    fLastFunc->SetNpx(5000);
    fLastFunc->SetLineWidth(fLineWidth);
    return fLastFunc;

    break;
  case kOneOverPtdNdpt:
    cout<<"Not Implemented"<<endl;
    break;
  case kOneOverMtdNdmt:
    cout<<"Not Implemented"<<endl;
    //    return GetUA1dNdmt(mass,T,n,norm,name);
    break;
  default:
    cout<<"Not implemented"<<endl;
  }

  return 0;
}




// ________________________________________________________________________

// Backend (private functions and support functions for numerical integration)

Double_t func::StaticHistoFunc(const double * x, const double* p){

  // provides a function interpolating a histo with a spline; 
  // using double to store a pointer... This is a bad hack. To be replaced

  double norm = p[0];
  
  TH1 * h     = (TH1*) Long64_t(p[1]);

//    Int_t bin = h->FindBin(x[0]);
//    double value = h->GetBinContent(bin);

  if (h->FindBin(x[0]) > h->GetNbinsX()) return 0;

  static TH1 * oldptr = 0;
  TSpline3 * spl = 0;
  if (h!=oldptr) {
    spl  = new TSpline3(h);
  }
  double value = spl->Eval(x[0]);
  delete spl;

  return value*norm;
  
}

Double_t func::StaticUA1Func(const double * x, const double* p) {
  

  // "mass","p0star","pt0","n","T","norm"
  Double_t mass   = p[0];
  Double_t p0star = p[1];
  Double_t pt0    = p[2];
  Double_t n      = p[3];
  Double_t temp   = p[4];
  Double_t norm   = p[5];
  
  Double_t xx = x[0];

  VarType_t varfunc = kdNdpt;
  TF1* funcparfunc = 0;
  Width_t inwidthfunc = 1;


  static func * self = new func(funcparfunc, inwidthfunc, varfunc);
  static TF1 * fPLaw   = self->GetPowerLawdNdptTimesPt(pt0, n, norm, "fLocalPLawUA1");
  static TF1 * fPMTExp = self->GetMTExpdNdptTimesPt   (mass, temp, norm, "fLocalMTexpUA1");

  fPLaw->SetParameters(norm,pt0,n);
  fPMTExp->SetParameters(1,temp);
  

  Double_t normMT =fPMTExp->Eval(p0star) >0 ? fPLaw->Eval(p0star) / fPMTExp->Eval(p0star) *  fPMTExp->GetParameter(0) : 1;
  fPMTExp->SetParameter(0,normMT);
  
  
  if (TMath::Abs(fPMTExp->Eval(p0star) - fPLaw->Eval(p0star)) > 0.0001 ) {
    Printf("func::StaticUA1Func - Wrong norm") ; 
    Printf(" p0* %f  NMT: %f  N: %f  PL: %f  MT: %f", p0star, normMT, norm, fPLaw->Eval(p0star), fPMTExp->Eval(p0star));
  }

  if (xx > p0star)  return fPLaw->Eval(xx);
  return fPMTExp->Eval(xx);    
  
  

}

Double_t func::IntegrandBG(const double * x, const double* p){
  // integrand for boltzman-gibbs blast wave

  double x0 = x[0]; 
  
  double mass = p[0];
  double pT   = p[1];
  double beta = p[2];
  double temp    = p[3];
  
  double mT      = TMath::Sqrt(mass*mass+pT*pT);

  double rho0   = TMath::ATanH(beta*x0);  
  double arg00 = pT*TMath::SinH(rho0)/temp;
  double arg01 = mT*TMath::CosH(rho0)/temp;
  double f0 = x0*mT*TMath::BesselI0(arg00)*TMath::BesselK1(arg01);

  return f0;
}



Double_t func::StaticBGdNdPt(const double * x, const double* p) {

  // implementation of BGBW (1/pt dNdpt)

  double pT = x[0];;
  

  double mass = p[0];
  double beta = p[1];
  double temp    = p[2];

  static TF1 * fIntBG = 0;
  if(!fIntBG)
    fIntBG = new TF1 ("fIntBG", IntegrandBG, 0, 1, 4);

  fIntBG->SetParameters(mass, pT, beta, temp);
  double result = fIntBG->Integral(0,1);
  return result*p[3];//*1e30;;

}

Double_t func::StaticBGdNdPtTimesPt(const double * x, const double* p) {
  // BGBW dNdpt implementation
  return x[0]*StaticBGdNdPt(x,p);
}


TF1 * func::GetBGBWdNdpt(Double_t mass, Double_t beta, Double_t temp,
			    Double_t norm, const char * name){
  
  // BGBW 1/pt dNdpt

  fLastFunc = new TF1 (name, StaticBGdNdPt, 0.0, 10, 4);
  fLastFunc->SetParameters(mass,beta,temp,norm);    
  fLastFunc->SetParNames("mass", "#beta", "T", "norm");
  fLastFunc->SetLineWidth(fLineWidth);
  fLastFunc->FixParameter(0,mass);
  return fLastFunc;
  
}


//_____________________________________________________________________
// Tsallis

Double_t func::IntegrandTsallis(const double * x, const double* p){

  // integrand for numerical integration (tsallis)

  Double_t r   = x[0]; 
  Double_t phi = x[1];
  Double_t y   = x[2];

  Double_t mass = p[0];
  Double_t pt   = p[1];
  Double_t beta = p[2];
  Double_t temp    = p[3];
  Double_t q    = p[4];
  
  Double_t mt      = TMath::Sqrt(mass*mass+pt*pt);

  Double_t rho    = TMath::ATanH(beta*r); // TODO: implement different velocity profiles  

  Double_t res = mt*
    r*TMath::CosH(y) *TMath::Power( (
				     1+(q-1)/temp * (
						  mt*TMath::CosH(y)*TMath::CosH(rho) -
						  pt*TMath::SinH(rho)*TMath::Cos(phi)
						  )
				     ),
				       -1/(q-1)
				    );			


  return res;
}



Double_t func::StaticTsallisdNdPt(const double * x, const double* p) {

  // tsallis BW implementation 1/pt dNdpt

  double pT = x[0];;
  

  double mass = p[0];
  double beta = p[1];
  double temp    = p[2];
  double q    = p[3];

  Double_t ymax = p[5];


  static TF3 * fInt = 0;
  if(!fInt){
    fInt = new TF3 ("fIntTsa", IntegrandTsallis, 0, 1, -TMath::Pi(), TMath::Pi(), -ymax, ymax, 5);
//     fInt->SetNpx(10000);
//     fInt->SetNpy(10000);
//     fInt->SetNpz(10000);
  }
  
  fInt->SetParameters(mass, pT, beta, temp, q);
  double result = fInt->Integral(0,1, -TMath::Pi(), TMath::Pi(), -ymax, ymax);
  //  double result = fInt->Integral(0,1, -2, 2, -ymax, ymax);
  
  return result*p[4];//*1e30;;

}

Double_t func::StaticTsallisdNdPtTimesPt(const double * x, const double* p) {

  // tsallis BW , implementatio of dNdpt
  return x[0]*StaticTsallisdNdPt(x,p);

}

TF1 * func::GetTsallisBWdNdpt(Double_t mass, Double_t beta, Double_t temp, Double_t q,
				   Double_t norm, Double_t ymax,const char * name){
  

  // tsallis BW, 1/pt dNdpt

  fLastFunc = new TF1 (name, StaticTsallisdNdPt, 0.0, 10, 6);
  fLastFunc->SetParameters(mass,beta,temp,q,norm,ymax);
  fLastFunc->SetParLimits(1,0.0,0.99);
  fLastFunc->SetParLimits(2,0.01,0.99);
  fLastFunc->SetParLimits(3,1.0001,1.9);
  fLastFunc->SetParNames("mass", "#beta", "temp", "q", "norm", "ymax");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;
  
}

// Times Pt funcs
// Boltzmann-Gibbs Blast Wave
TF1 * func::GetBGBWdNdptTimesPt(Double_t mass, Double_t beta, Double_t temp,
				     Double_t norm, const char * name){

  // BGBW, dNdpt

  fLastFunc = new TF1 (name, StaticBGdNdPtTimesPt, 0.0, 10, 4);
  fLastFunc->SetParameters(mass,beta,temp,norm);    
  fLastFunc->SetParNames("mass", "#beta", "temp", "norm");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}



TF1 * func::GetTsallisBWdNdptTimesPt(Double_t mass, Double_t beta, Double_t temp, Double_t q,
					  Double_t norm, Double_t ymax, const char * name){

// Tsallis blast wave, dNdpt

  fLastFunc = new TF1 (name, StaticTsallisdNdPtTimesPt, 0.0, 10, 6);
  fLastFunc->SetParameters(mass,beta,temp,q,norm,ymax);    
  fLastFunc->SetParNames("mass", "#beta", "temp", "q", "norm", "ymax");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;
 

}



TF1 * func::GetMTExpdNdptTimesPt(Double_t mass, Double_t temp, Double_t norm, const char * name){

  // Simple exponential in 1/mt*MT, as a function of dNdpt
  char formula[500];
  sprintf(formula,"[0]*x*exp(-sqrt(x**2+%f**2)/[1])", mass);
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}


TF1 * func::GetPTExpdNdptTimesPt(Double_t temp, Double_t norm, const char * name){

  // Simple exponential in 1/pt*dNdpT, as a function of dNdpt
  char formula[500];
  sprintf(formula,"[0]*x*exp(-x/[1])");
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}


TF1 * func::GetBoltzmanndNdptTimesPt(Double_t mass, Double_t temp, Double_t norm, const char * name){
  // Boltzmann (exp in 1/mt*dNdmT times mt) as a function of dNdpt
 char formula[500];
 sprintf(formula,"[0]*x*sqrt(x**2+%f**2)*exp(-sqrt(x**2+%f**2)/[1])", mass,mass);
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}


// Tsallis (no BW, a la CMS)
// TF1 * func::GetTsallisdNdptTimesPt(Double_t mass, Double_t T, Double_t q, Double_t norm, const char * name){

//   char formula[500];
//   //  sprintf(formula,"[0]*x*pow((1+(([2]-1)/[1])*(sqrt(x**2+%f**2)-%f)),(-1/([2]-1)))", mass, mass); //CMS
//   sprintf(formula,"[0]*x*pow((1+(([2]-1)/[1])*(sqrt(x**2+%f**2))),(-1/([2]-1)))", mass);  // STAR
//   //sprintf(formula,"[0]*x*sqrt(x**2+%f**2)*pow((1+(([2]-1)/[1])*(sqrt(x**2+%f**2))),(-1/([2]-1)))", mass,mass);  // STAR * mt
//   fLastFunc=new TF1(name,formula,0,10);
//   fLastFunc->SetParameters(norm, T, q);
//   fLastFunc->SetParLimits(1, 0.001, 10);
//   fLastFunc->SetParNames("norm", "T", "q");
//   fLastFunc->SetLineWidth(fLineWidth);
//   return fLastFunc;


// }


TF1 * func::GetLevidNdptTimesPt(Double_t mass, Double_t temp, Double_t n, Double_t norm, const char * name){

  // Levi function, dNdpt
  char formula[500];

  sprintf(formula,"( x*[0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + (sqrt([3]*[3]+x*x) -[3])/([1]*[2])  )^(-[1])");
  //  sprintf(formula,"( x*[0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + (sqrt([3]*[3]+x*x))/([1]*[2])  )^(-[1])");
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, n, temp,mass);
  fLastFunc->SetParLimits(2, 0.01, 10);
  fLastFunc->SetParNames("norm (dN/dy)", "n", "T", "mass");
  fLastFunc->FixParameter(3,mass);
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}

TF1 * func::GetPowerLawdNdptTimesPt(Double_t pt0, Double_t n, Double_t norm, const char * name){

  // PowerLaw function, dNdpt
  char formula[500];

  sprintf(formula,"x*[0]*( 1 + x/[1] )^(-[2])");
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, pt0, n);
  fLastFunc->SetParLimits(1, 0.01, 10);
  //fLastFunc->SetParLimits(2, 0.01, 50);
  fLastFunc->SetParNames("norm", "pt0", "n");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}

TF1 * func::GetPowerLawdNdpt(Double_t pt0, Double_t n, Double_t norm, const char * name){

  // PowerLaw function, 1/pt dNdpt
  char formula[500];

  sprintf(formula," [0]*( 1 + x/[1] )^(-[2])");
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, pt0, n);
  //  fLastFunc->SetParLimits(2, 0.01, 10);
  fLastFunc->SetParNames("norm", "pt0", "n");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}


TF1 * func::GetLevidNdpt(Double_t mass, Double_t temp, Double_t n, Double_t norm, const char * name){

  // Levi function, dNdpt
  char formula[500];

  sprintf(formula,"( [0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+%f*([1]-2) )  ) * ( 1 + (sqrt(%f*%f+x*x) -%f)/([1]*[2])  )^(-[1])",mass,mass,mass,mass);
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, n, temp);
  //fLastFunc->SetParLimits(1, 1, 1e10);
  fLastFunc->SetParLimits(2, 0.1, 1);
  fLastFunc->SetParNames("norm (dN/dy)", "n", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}

TF1 * func::GetLevidNdmt(Double_t mass, Double_t temp, Double_t n, Double_t norm, const char * name, VarType_t var){

  // Levi function, 1/mt dNdmt
  char formula[500];
  if (var == kOneOverMtdNdmt)
    sprintf(formula,"( [0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + (x -[3])/([1]*[2])  )^(-[1])");
  else if (var == kdNdmt) 
    sprintf(formula,"( x*[0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + (x-[3])/([1]*[2])  )^(-[1])");
  if (var == kOneOverMtdNdmtMinusM)
    sprintf(formula,"( [0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + (x)/([1]*[2])  )^(-[1])");

  //sprintf(formula,"( [0]*([1]-1)*([1]-2)  )/( [1]*[2]*( [1]*[2]+[3]*([1]-2) )  ) * ( 1 + x/([1]*[2])  )^(-[1])");
  //  sprintf(formula,"[0] * ( 1 + x/([1]*[2])  )^(-[1])");
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, n, temp,mass);
  fLastFunc->SetParLimits(2, 0.01, 10);
  fLastFunc->SetParNames("norm", "n", "T", "mass");
  fLastFunc->FixParameter(3,mass);
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;


}




// Test Function
Double_t func::IntegrandTest(const double * x, const double* p){

  // test function

  Double_t y = x[0];

  Double_t mass = p[0];
  Double_t pt   = p[1];
  Double_t temp    = p[2];

  Double_t mt      = TMath::Sqrt(mass*mass+pt*pt);    
  
  return mt*TMath::CosH(y)*TMath::Exp(-mt*TMath::CosH(y)/temp);

}

Double_t func::StaticTest(const double * x, const double* p) {

  // test function

  double pT = x[0];;
  

  double mass = p[0];
  double temp    = p[1];
  Double_t ymax = p[3];


  static TF3 * fIntTest = 0;
  if(!fIntTest){
    fIntTest = new TF3 ("fIntTest", IntegrandTest, 0, 1, -TMath::Pi(), TMath::Pi(), -ymax, ymax, 5);
    //    fInt->SetNpx(10000);
  }
  
  fIntTest->SetParameters(mass, pT, temp);
  double result = fIntTest->Integral(-ymax, ymax);
  
  return result*p[2];//*1e30;;

}

TF1 * func::GetTestFunc(Double_t mass, Double_t temp, Double_t norm, Double_t ymax, const char * name){
  
  // test function
  
  fLastFunc = new TF1 (name, StaticTest, 0.0, 10, 4);
  fLastFunc->SetParameters(mass,temp,norm,ymax);    
  fLastFunc->SetParNames("mass", "#beta", "T", "q", "norm", "ymax");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;
  
}


//___________________________________________________________


TF1 * func::GetMTExpdNdpt(Double_t mass, Double_t temp, Double_t norm, const char * name){
  // Simple exp in 1/mt dNdmt, as a function of dNdpt
  // mt scaling
  char formula[500];
  sprintf(formula,"[0]*exp(-sqrt(x**2+%f**2)/[1])", mass);
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;
}

TF1 * func::GetBoltzmanndNdpt(Double_t mass, Double_t temp, Double_t norm, const char * name){
  // Boltzmann (exp in 1/mt*dNdmT) as a function of dNdpt
 char formula[500];
 sprintf(formula,"[0]*sqrt(x**2+%f**2)*exp(-sqrt(x**2+%f**2)/[1])", mass,mass);
  fLastFunc=new TF1(name,formula,0,10);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  fLastFunc->SetLineWidth(fLineWidth);
  return fLastFunc;

}


