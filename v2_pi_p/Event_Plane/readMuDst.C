
#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;
class StMuDstMaker;

//StChain *chain;
void readPicoDst(const Char_t *inputFile="test.list",float RPO, const Char_t *outputFile="test.root",char *recfile,char *shiftfile)
{
        Int_t nEvents = 10000000;
	
        gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	gSystem->Load("StPicoDstMaker");
	gSystem->Load("StRefMultCorr");
        gSystem->Load("StMyAnalysisMaker");
	gSystem->Load("StMyRecenterMaker");

	StChain *anachain = new StChain();
	Int_t mode = 0;
	StMuDstMaker *picoMaker = new StMuDstMaker(0,mode,"",inputFile,"MuDst",nEvents);
	//cout<<"PicoDst declared!"<<endl;
        StMyAnalysisMaker *anaMaker = new StMyAnalysisMaker("ana",picoMaker,outputFile,recfile,shiftfile,RPO);
	
	anachain->Init();
	cout<<"chain->Init();"<<endl;
	if(mode == 0){
	int total = picoMaker->chain()->GetEntries();
	}
	else{
	int total = 1;
	}
        cout << " Total entries = " << total << endl;
	nEvents = total;

 	for (Int_t i=0; i<nEvents; i++){
	  if(i%1000==0)
	  cout << "Working on eventNumber " << i << endl;
		
	  anachain->Clear();
	  int iret = anachain->Make(i);
		
	  if (iret) { cout << "Bad return code!" << iret << endl; break;}

	  total++;
		
	}
	
	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!" << endl;
	cout << "****************************************** " << endl;
	anachain->Finish();
	cout << "****************************************** " << endl;
	cout << "total number of events in input files was = "<< nEvents << endl;
	cout << "****************************************** " << endl;
	
	delete anachain;
	
	
}
