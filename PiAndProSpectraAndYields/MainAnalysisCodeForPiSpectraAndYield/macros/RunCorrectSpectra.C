//Runs the source code responsible for applying all of the corrections to the spectra
//see src/analysis/correctSpectra.cxx

void RunCorrectSpectra(TString spectraFileName, TString correctionFileName, Int_t pid, Int_t charge){
  
  //Load the necessary Librarires
  gSystem->Load("../bin/utilityFunctions_cxx.so");
  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
  gSystem->Load("../bin/DavisDstReader_cxx.so");
  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");
  gSystem->Load("../bin/ParticleInfo_cxx.so");
  gSystem->Load("../bin/correctSpectra_cxx.so");

  SetVariableUserCuts(4.5,"FixedTarget2015","SL16a");
  
  correctSpectra(spectraFileName,correctionFileName,pid,charge);

}
