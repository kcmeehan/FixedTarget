//This macro runs the compiled pileUpLuminosity binary
void RunPileUpLuminosity(TString fitFile="", Int_t fitNumber, TString dataFile="", TString glauberFile="", TString outputFile="", Double_t energy, TString eventConfig, TString starLibrary, 
												Int_t normStartBin, Int_t normEndBin, Double_t NegativeBinomialParameterP, Double_t NegativeBinomialParameterN, 
												Double_t pileUpEventOccurence, Int_t nSimulatedEvents, Bool_t drawCanvas){

	//Load the necessary libraries
	gSystem->Load("../bin/TrackInfo_cxx.so");
	gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
	gSystem->Load("../bin/EventInfo_cxx.so");
	gSystem->Load("../bin/DavisDstReader_cxx.so");
	gSystem->Load("../bin/ParticleInfo_cxx.so");
	gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
	
	gSystem->Load("../bin/GlauberClass_cxx.so");
	gSystem->Load("../bin/GlauberModel_cxx.so");  

	gSystem->Load("../bin/UserCuts_cxx.so");
	gSystem->Load("../bin/pileupLuminosity_cxx.so");

  //Set the User Cuts
  SetVariableUserCuts(energy,eventConfig,starLibrary);

	pileupLuminosity(fitFile, fitNumber, dataFile, glauberFile, outputFile, normStartBin, normEndBin, NegativeBinomialParameterP, NegativeBinomialParameterN, pileUpEventOccurence, nSimulatedEvents, drawCanvas);

}
