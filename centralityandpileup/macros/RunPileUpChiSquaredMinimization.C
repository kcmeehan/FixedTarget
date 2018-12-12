//This macro runs the compiled pileupChiSquaredMinimzation binary
void RunPileUpChiSquaredMinimization(TString fitFile="", Int_t fitNumber=0, TString dataFile="", TString glauberFile="", TString outputFile="",
												Int_t normStartBin, Int_t normEndBin, Int_t lastBin, Double_t NegativeBinomialParameterP, Double_t NegativeBinomialParameterN, 
												Int_t numberOfPercentages, Double_t percentBeg, Double_t percentEnd, Int_t nSimulatedEvents){

	//Load the necessary libraries
	//gSystem->Load("../bin/GlauberClass_cxx.so");
	//gSystem->Load("../bin/GlauberModel_cxx.so"); 
	gSystem->Load("/scratch_menkar/kinghorn/fxtcommit/AuAu_4_5GeV_2015/davisdstanalysis/src/submodules/glaubermcmodel/bin/GlauberClass_cxx.so");
  gSystem->Load("/scratch_menkar/kinghorn/fxtcommit/AuAu_4_5GeV_2015/davisdstanalysis/src/submodules/glaubermcmodel/bin/GlauberModel_cxx.so"); 
	gSystem->Load("../bin/pileupChiSquaredMinimization_cxx.so");

  cout <<"made it here 1" <<endl;

	pileupChiSquaredMinimization(fitFile, fitNumber, dataFile, glauberFile, outputFile, normStartBin, normEndBin, lastBin, NegativeBinomialParameterP, NegativeBinomialParameterN, numberOfPercentages, percentBeg, percentEnd, nSimulatedEvents);

}
