Int_t FxtAnalysis(Int_t nEvents, Int_t nFiles, TString InputFileList, TString OutputDir, TString JobIdName, Double_t testParameter)
{
  // Load libraries
  gROOT->Macro("loadMuDst.C");
  gSystem->Load("FxtMaker.so");
  
  // List of member links in the chain
  StChain* chain = new StChain;
  StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"",InputFileList,"MuDst",nFiles);
  FxtMaker* doAnalysis = new FxtMaker(muDstMaker,JobIdName,nEvents,testParameter);
  
    if ( nEvents == 0 )  nEvents = 10000000 ;       // Take all events in nFiles if nEvents = 0
    
    // Loop over the links in the chain
    Int_t iInit = chain -> Init() ;
    if (iInit) chain->Fatal(iInit,"on init");
    
    // chain -> EventLoop(1,nEvents) ;  //will output lots of useless debugging info.
    Int_t istat = 0, i = 1;
    while (i <= nEvents && istat != 2) {
        //if(i==740){i++; continue;}
        if(i%10==0)cout << endl << "== Event " << i << " start ==" << endl;
        chain->Clear();
        istat = chain->Make(i);
        //if(i%1000==0)cout << endl << "== Event " << i << " finish =="<< endl;
        if (istat == 2)
            cout << "Last  event processed. Status = " << istat << endl;
        if (istat == 3)
            cout << "Error event processed. Status = " << istat << endl;
        i++;
    }
    
    if (nEvents > 1) chain -> Finish() ;
    
    // Cleanup
    delete chain ;
    return 0;
}
