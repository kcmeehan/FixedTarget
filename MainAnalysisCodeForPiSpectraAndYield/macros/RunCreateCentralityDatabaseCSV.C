
void RunCreateCentralityDatabaseCSV(TString inputFile, TString outFileName, Int_t nEvents=-1, TString starLibrary="",
		      Double_t energy=0, TString eventConfig=""){

  //Load the necessary Librarires
  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
  gSystem->Load("../bin/DavisDstReader_cxx.so");
  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");
  gSystem->Load("../bin/ParticleInfo_cxx.so");
  gSystem->Load("../bin/createCentralityDatabaseCSV_cxx.so");

  //This Sets the event, vertex, and track cuts which in the global scope
  SetVariableUserCuts(energy,eventConfig,starLibrary);

  createCentralityDatabaseCSV(inputFile,outFileName,nEvents);

  
}
