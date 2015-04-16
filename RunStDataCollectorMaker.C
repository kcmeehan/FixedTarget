class StChain;
StChain *chain=0;

void RunStDataCollectorMaker(Int_t nEvents=1,
			     char *fileList,
			     char *outDir="./",
			     char *index="01"){

  //Load the Necessary Libraries                                                                                                                  
  gROOT->LoadMacro("loadMuDst.C");
  loadMuDst();
  gROOT->Macro("LoadLogger.C");
  gSystem->Load("StDetectorDbMaker");
  gSystem->Load("StTpcDb");
  
  gSystem->Load("StDbBroker");
  gSystem->Load("StDbUtilities");
  gSystem->Load("StDaqLib");
  gSystem->Load("StEmcRawMaker");
  gSystem->Load("StEmcADCtoEMaker");
  gSystem->Load("StPreEclMaker");
  gSystem->Load("StEpcMaker");
  
  gSystem->Load("St_db_Maker");
  gSystem->Load("StEEmcUtil");
  gSystem->Load("StRefMultCorr");

  //Load Our Maker
  gSystem->Load("TrackInfo");
  gSystem->Load("PrimaryVertexInfo");
  gSystem->Load("EventInfo");
  gSystem->Load("StDataCollectionMaker");

  //The Main Chain
  chain = new StChain("StChain");
  chain->SetDebug();

  //Add The Makers to the Chain                                              
  StMuDstMaker *muDstMaker = new StMuDstMaker(0,0,"",fileList,"",100);
  St_db_Maker *dbMaker = new St_db_Maker("StarDb","MySQL:StarDb");

  StDataCollectionMaker *myMaker = new StDataCollectionMaker("StDataCollectionMaker");

  myMaker->SetOutDir(outDir);
  myMaker->SetFileIndex(index);

  //Initialize
  Int_t initStat = chain->Init();
  if (initStat) chain->Fatal(initStat, "Failure During Init()");


  Int_t istat, iev=1;
 EventLoop: if (iev<=nEvents && istat!=2){
    chain->Clear();
    cout << "---------------------- Processing Event : " << iev << " ----------------------" << endl;
    istat = chain->Make(iev); // This should call the Make() method in ALL makers                   
    cout << "===   Made Event.   === " << endl;
    if (istat == 2) { cout << "Last  Event Processed. Status = " << istat << endl; }
    if (istat == 3) { cout << "Error Event Processed. Status = " << istat << endl; }
    iev++; goto EventLoop;
  }

  return;

}
