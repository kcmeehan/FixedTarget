//These are various structures used as return trypes for functions

class TH1D;
class TGraph2D;

//____________________________________________
struct NegBinomialSearchResults{

  //This Structure is returned from FindBestFitNegativeBinomialParameters()

  //These are variables used as part of FindBestFitNegativeBinomialParameters()
  Double_t n;
  Double_t p;
  Double_t InverseChi2;
  TH1D *bestFitHisto;
  TGraph2D *chi2Graph;

  //These are variables used as part of FindCentralityBinCuts() and FindNpartNcollDistributions()
  Int_t nCentralityBins;
  std::vector<double> centralityBinDefinitions;
  std::vector<double> centralityBinCuts;
  TH1D *nPartHistos;
  TH1D *nCollHistos;
  TH1D *impactParamHistos;

  std::vector<double> nPartMeans;
  std::vector<double> nPartErrors;
  std::vector<double> nCollMeans;
  std::vector<double> nCollErrors;
  std::vector<double> impactParamMeans;
  std::vector<double> impactParamErrors;

};

