void RunMakeStarsimTxFiles(TString urqmdROOTFile, TString outDirName, TString vertexFile="",
			   TString histoNameBase="", const int eventsPerOutputFile=10, const int nTotalEventsDesired=-1){

  gSystem->Load("../bin/URQMDTrack_cxx");
  gSystem->Load("../bin/URQMDEvent_cxx");
  gSystem->Load("../bin/URQMDReader_cxx");
  gSystem->Load("../bin/URQMDPidToGEANTPid_cxx");
  gSystem->Load("../bin/MakeStarsimTxFiles_cxx");

  TStopwatch watch;

  MakeStarsimTxFiles(urqmdROOTFile,outDirName,vertexFile,histoNameBase,eventsPerOutputFile,nTotalEventsDesired);

  cout <<"Finished Converting " <<urqmdROOTFile.Data() <<" to tx files in " <<watch.RealTime() <<" seconds."<<endl;


}
