
void RunVertexPlotsForStarsim(TString inputFile, TString outputFile, TString starLibrary, Int_t nEvents, Double_t energy, TString eventConfig){

		//Load the Necessary Libraries
		gSystem->Load("../bin/TrackInfo_cxx.so");
    gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
    gSystem->Load("../bin/EventInfo_cxx.so");
    gSystem->Load("../bin/ParticleInfo_cxx.so");
	  gSystem->Load("../bin/DavisDstReader_cxx.so");
		gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
    gSystem->Load("../bin/UserCuts_cxx.so");
    gSystem->Load("../bin/vertexPlotsForStarsim_cxx.so");

    SetVariableUserCuts(energy,eventConfig,starLibrary);

    vertexPlotsForStarsim(inputFile,outputFile,nEvents);

}
