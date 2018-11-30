//Runs the source code responsible for fitting the pion spectra and extracting
//the dNdy values. 


void RunFitSpectra(TString spectraFileName, TString resultsFileName, Int_t pid, Int_t charge){

  //Load the necessary Librarires
  gSystem->Load("../bin/utilityFunctions_cxx.so");
  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
  gSystem->Load("../bin/DavisDstReader_cxx.so");
  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");
  gSystem->Load("../bin/ParticleInfo_cxx.so");
  gSystem->Load("../bin/SpectraFitFunctions_cxx.so");
  gSystem->Load("../bin/fitPionSpectraSingleBose_cxx.so");

  SetVariableUserCuts(4.5,"FixedTarget2015","SL16a");

  fitPionSpectraSingleBose(spectraFileName,resultsFileName,pid,charge,-1.52);
  //fitPionSpectraSingleThermal(spectraFileName,resultsFileName,pid,charge,-1.52);
  //fitPionSpectraExponential(spectraFileName,resultsFileName,pid,charge,-1.52);
  
}
