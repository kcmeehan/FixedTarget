class StChain;
StChain *chain=0;

void RunStDataCollectorMaker(Int_t nEvents=1,char *fileList,char *outDir="./",char *index="01",
			     Double_t minVr=-999,Double_t maxVr=-999,
			     Double_t minVz=-999,Double_t maxVz=-999,
			     Double_t minVx=-999,Double_t maxVx=-999,
			     Double_t minVy=-999,Double_t maxVy=-999,
			     Double_t beamSpotX=-999,Double_t beamSpotY=-999,
			     Int_t minNumberOfPrimaryTracks=-999, Int_t maxNumberOfVertices=-999,
			     Int_t badRunRejection_StRefMultCorr=-999,Int_t time=-999){

  //Start the stopwatch
  Double_t allowedRunTime(9999999);
  if (time != -999)
    allowedRunTime = time;
  TStopwatch timer;
  timer.Start();

  //Load the Necessary Libraries
  gROOT->LoadMacro("loadMuDst.C");
  loadMuDst();

  //Load the StRefMutCorr Module for optional bad run rejection
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
  muDstMaker->SetStatus("*",0);
  muDstMaker->SetStatus("MuEvent",1);
  muDstMaker->SetStatus("PrimaryVertices",1);
  muDstMaker->SetStatus("PrimaryTracks",1);
  muDstMaker->SetStatus("GlobalTracks",1);
  muDstMaker->SetStatus("BTof*",1);

  StDataCollectionMaker *davisDstMaker = new StDataCollectionMaker("StDataCollectionMaker");
  davisDstMaker->SetOutDir(outDir);
  davisDstMaker->SetFileIndex(index);

  //By default the values of these cut variables in StDataCollectionMaker are set
  //so that they will not imped on data taking if the user chooses not to set them,
  //but if the User has passed in values for the vertex cuts then set them here
  if (minVr != -999)
    davisDstMaker->SetMinVr(minVr);
  if (maxVr != -999)
    davisDstMaker->SetMaxVr(maxVr);
  if (minVz != -999)
    davisDstMaker->SetMinVz(minVz);
  if (maxVz != -999)
    davisDstMaker->SetMaxVz(maxVz);
  if (minVx != -999)
    davisDstMaker->SetMinVx(minVx);
  if (maxVx != -999)
    davisDstMaker->SetMaxVx(maxVx);
  if (minVy != -999)
    davisDstMaker->SetMinVy(minVy);
  if (maxVy != -999)
    davisDstMaker->SetMaxVy(maxVy);
  if (beamSpotX != -999 && beamSpotY != -999)
    davisDstMaker->SetBeamSpot(beamSpotX,beamSpotY);
  if (minNumberOfPrimaryTracks != -999)
    davisDstMaker->SetMinNumberOfPrimaryTracks(minNumberOfPrimaryTracks);
  if (maxNumberOfVertices != -999)
    davisDstMaker->SetMaxNumberOfVertices(maxNumberOfVertices);

  davisDstMaker->UseStRefMultCorrBadRunRejection(badRunRejection_StRefMultCorr);

  //Initialize
  Int_t initStat = chain->Init();
  if (initStat) 
    chain->Fatal(initStat, "Failure During Init()");

  Int_t istat, iev=1;
  Bool_t timeStatus = true;
 EventLoop: if (iev<=nEvents && istat!=2 && timeStatus==true){
    chain->Clear();
    cout << "---------------------- Processing Event : " << iev << " ----------------------" << endl;
    istat = chain->Make(iev); // This should call the Make() method in ALL makers                   
    cout << "===   Made Event.   === " << endl;
    if (istat == 2) { cout << "Last  Event Processed. Status = " << istat << endl; }
    if (istat == 3) { cout << "Error Event Processed. Status = " << istat << endl; }
    if (timer.RealTime()/60. > allowedRunTime){
      cout <<"Maximum time reched after processing this many events: " <<iev <<endl;
      timeStatus = false;
    }
    timer.Continue();
    iev++; goto EventLoop;
  }

  return;

}
