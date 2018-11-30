//This macro runs the MakeCorrectionGraphs.cxx source code located in src/embedding
//It generates plots of efficiency and energy loss that will be fit.

void RunMakeEmbeddingCorrectionCurves(TString embeddingFile, TString correctionFile, Int_t pid, Int_t charge){

  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
  gSystem->Load("../bin/ParticleInfo_cxx.so");
  gSystem->Load("../bin/utilityFunctions_cxx.so");
  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");
  gSystem->Load("../bin/EfficiencyFitUtilities_cxx.so");
  gSystem->Load("../bin/MakeCorrectionCurves_cxx.so");
  
  SetVariableUserCuts(4.5,"FixedTarget2015","SL16a");

  MakeCorrectionCurves(embeddingFile, correctionFile, pid, charge);
  
}
