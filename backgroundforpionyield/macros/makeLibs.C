//This is simple ROOT Style Make File

void makeLibs(TString opt=""){
  
  if (opt=="clean"){
    gSystem->Exec("rm -f bin/*");
    return;
  }

  //Check to make sure the bin directory exists, if not create it
  if (gSystem->OpenDirectory("bin") == 0 )
    gSystem->MakeDirectory("bin");

  gSystem->SetBuildDir("$PWD/bin/",true);
  gSystem->SetIncludePath(TString::Format("-I$ROOTSYS/include -I%s/inc",gSystem->pwd()));

  gSystem->Load("bin/URQMDTrack_cxx");
  gSystem->Load("bin/URQMDEvent_cxx");
  gSystem->Load("bin/URQMDReader_cxx");
  gSystem->Load("bin/URQMDPidToGEANTPid_cxx");

  gSystem->CompileMacro("src/MakeStarsimTxFiles.cxx","k-");


}
