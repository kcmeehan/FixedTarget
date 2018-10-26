//This gets called by the makefile to compile all your source code. Add to it as needed!
void makeLibs(TString opt=""){

  //Remove the contents of the binary directory if option "clean" is called
  if (opt == "clean"){
    gSystem->Exec("rm -f bin/*");
    return;
  }

  //Check to make sure the bin directory exists. If not create it.
  if (gSystem->OpenDirectory("bin") == 0)
    gSystem->MakeDirectory("bin");
  
  //Set the Build and Include Directories
  gSystem->SetBuildDir("$PWD/bin/",true);
  gSystem->SetIncludePath(TString::Format("-I$ROOTSYS/include -I%s/inc",gSystem->pwd()));

  //Compile Submodules
  gSystem->CompileMacro("src/utilityFunctions.cxx","k");
  gSystem->CompileMacro("src/MiniMcReader.cxx","k");
  gSystem->CompileMacro("src/submodules/strefmultextendedcorr/StRefMultExtendedCorr.cxx","k");
  gSystem->CompileMacro("src/submodules/centralitydatabaseclass/CentralityDatabaseClass/CentralityDatabaseClass.cxx","k");

  gSystem->CompileMacro("src/BinningAndCuts.cxx","k");
  gSystem->CompileMacro("src/ProcessBackgroundSimulations.cxx","k");
}
