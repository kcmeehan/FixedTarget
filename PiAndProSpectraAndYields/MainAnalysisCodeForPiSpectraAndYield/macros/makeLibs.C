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

  //Compile the contents of the sub-modules
  gSystem->CompileMacro("src/submodules/datacollectorreaderlibs/TrackInfo/TrackInfo.cxx","k");
  gSystem->CompileMacro("src/submodules/datacollectorreaderlibs/PrimaryVertexInfo/PrimaryVertexInfo.cxx","k");
  gSystem->CompileMacro("src/submodules/datacollectorreaderlibs/EventInfo/EventInfo.cxx","k");
  gSystem->CompileMacro("src/submodules/datacollectorreaderlibs/DavisDstReader/DavisDstReader.cxx","k");
  gSystem->CompileMacro("src/submodules/ParticleInfo/ParticleInfo/ParticleInfo.cxx","k");
  gSystem->CompileMacro("src/submodules/strefmultextendedcorr/StRefMultExtendedCorr.cxx","k");
  
  //Compile your source code
	//PID & Yield Extraction
  gSystem->CompileMacro("userfiles/UserCuts.cxx","k");
	gSystem->CompileMacro("src/analysis/utilityFunctions.cxx","k");
	gSystem->CompileMacro("src/analysis/usefulDataStructs.cxx","k");
  gSystem->CompileMacro("src/analysis/skimmerAndBinner.cxx","k");
	gSystem->CompileMacro("src/analysis/fitZTPCUtilities.cxx","k");
	gSystem->CompileMacro("src/analysis/fitZTPCPions.cxx","k");
	gSystem->CompileMacro("src/analysis/correctSpectra.cxx","k");
	gSystem->CompileMacro("src/analysis/SpectraFitFunctions.cxx","k");
	gSystem->CompileMacro("src/analysis/fitPionSpectraSingleBose.cxx","k");
	gSystem->CompileMacro("src/analysis/fitPionSpectraSingleThermal.cxx","k");
	gSystem->CompileMacro("src/analysis/fitPionSpectraExponential.cxx","k");

	//Background
	gSystem->CompileMacro("src/background/vertexPlotsForStarsim.cxx","k");
	gSystem->CompileMacro("src/background/feeddownBackground.cxx","k");

	//Embedding Related Code
  gSystem->CompileMacro("src/embedding/createCentralityDatabaseCSV.cxx","k");
	gSystem->CompileMacro("src/embedding/EfficiencyFitUtilities.cxx","k");
	gSystem->CompileMacro("src/embedding/MakeCorrectionCurves.cxx","k");
  
}
