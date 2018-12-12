//This macro runs the compiled centralityVariableDistributions binary.
//The source can be found at:
//    src/analysis/centralityVariableDistributions.cxx

void RunCentralityVariableDistributions(TString inputFile, TString outputFile="", Long64_t nEvents=-1, TString starLibrary="", Double_t energy=0, TString eventConfig=""){

  //Load the Necessary Libraries
  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
  gSystem->Load("../bin/DavisDstReader_cxx.so");

  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");
  gSystem->Load("../bin/centralityVariableDistributions_cxx.so");

  //Set the User Cuts
  SetVariableUserCuts(energy,eventConfig,starLibrary);
  
  centralityVariableDistributions(inputFile,nEvents,outputFile);

}
