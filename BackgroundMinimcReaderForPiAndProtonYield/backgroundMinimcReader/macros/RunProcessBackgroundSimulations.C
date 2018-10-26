void RunProcessBackgroundSimulations(TString MINIMCLIST, TString OUTPUTFILE){
  
  gSystem->Load("../bin/utilityFunctions_cxx.so");
  gSystem->Load("../bin/MiniMcReader_cxx.so");
  gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/CentralityDatabaseClass_cxx.so");
  gSystem->Load("../bin/BinningAndCuts_cxx.so");
  gSystem->Load("../bin/ProcessBackgroundSimulations_cxx.so");
  
  ProcessBackgroundSimulations(MINIMCLIST.Data(),OUTPUTFILE);
   
}
