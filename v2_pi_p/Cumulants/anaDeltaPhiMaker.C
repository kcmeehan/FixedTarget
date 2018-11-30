void anaDeltaPhiMaker(TString inFile, TString outFile, int nEvents, double min, double max,int vid,double ptMAX , double ptMIN, double etAMAX, double etAMIN, int pid,double Vxmin,double Vxmax,double Vymin,double Vymax,double Vzmin,double Vzmax,double DedX, double hitS, double PoSS, double FlaG, double e1u, double e1d, double e2u, double e2d,double TPCi,double TPCe,int BINN) {





  cout << "Initialising STAR environment" << endl;
   
gROOT->ProcessLine(".x $STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
gSystem->Load("SimpleAnaliseMaker.so");
  StMuDebug::setLevel(0);
StChain *chain = new StChain();

	StMuDstMaker *maker = new StMuDstMaker(0,0,"",inFile,"MuDst",nEvents);
	//maker -> SetStatus("*",0) ;                // Turn off all branches
 	maker -> SetStatus("MuEvent",1) ;          // Turn on the Event data (esp. Event number)
  	maker -> SetStatus("PrimaryTracks",1) ;
  	//StMuDstMaker *muDstMaker = new StMuDstMaker(0,0,"",inFile,"MuDst",nEvents);
	SimpleAnaliseMaker *SAM = new SimpleAnaliseMaker(maker,outFile,min, max,vid,ptMAX,ptMIN,etAMAX,etAMIN,pid,DedX,hitS,PoSS,FlaG,e1u,e1d,e2u,e2d,TPCi,TPCe,BINN);
	
	SAM->SetxPositionCuts(Vxmin,Vxmax); //-2 2
	SAM->SetyPositionCuts(Vymin,Vymax); //-3.7 -2.5
	SAM->SetzPositionCuts(Vzmin,Vzmax);//208.5 211
	SAM->SetxyRadiousCut(0);
	SAM->SetnsigmaCut(2);
	
	chain->Init();
	cout<<"GO"<<endl;
	chain->EventLoop(1,nEvents);
	chain->Finish();	
	
	delete chain;
	
}
