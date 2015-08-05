class StMuDstMaker;
class StMuEvent;
class StMuTrack;

Int_t calcNumberOfTofMatches(TObjArray* tracks);
Bool_t checkTrack(StMuTrack* track); 
Bool_t isElectron(StMuTrack* track);
Bool_t isPion(StMuTrack* track);
Bool_t isKaon(StMuTrack* track);
Bool_t isProton(StMuTrack* track);

void QA(const TString fileList = "FXTFiles.list"
				, const TString outFile = "testOut.root" 
				, const Int_t nEvents = 999 
				)
{

	TStopwatch* timer = new TStopwatch();

	//-----------------  Load Libraries ---------------//
	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();

	//----------------- Instantiate chain and MuDst reader ---------------//
	StChain* chain = new StChain("StChain");
	chain->SetDebug(0);
	StMuDebug::setLevel(0);

	StMuDstMaker* muMaker = new StMuDstMaker(0,0,"",fileList.Data(),"st:MuDst.root", 1000, "MuDst");

	//----------------------- Make Histograms, etc. -----------------------//

	TH1I* hRefmult = new TH1I("hRefmult","refmult", 800,0.5,800.5);
    TH2F* dEdxPion = new TH2F("dEdxPion","dEdxPion",500,-2,2,200,0,0.00004);
    TH2F* dEdx = new TH2F("dEdx","dEdx",500,-2,2,200,0,0.00004);
    TH1D* eventCuts = new TH1D("eventCuts","Event Cuts",5,-0.5,4.5);
    TH1D* particleYield = new TH1D("particleYield","Particle Yield",10,-0.5,9.5);
    const Char_t* yieldTitles[10] = {"All Tracks","Pass Cuts","e+", "e-","Pi+", "Pi-", "K+", "K-", "p+", "p-"};
    const Char_t* eventCutTitles[5] = {"All Events","Vz","Vx", "Vy","Tof Matches"};

    for(Int_t i = 0; i <= 9; i++) { particleYield->GetXaxis()->SetBinLabel(i+1,yieldTitles[i]); }
    for(Int_t i = 0; i <= 4; i++) { eventCuts->GetXaxis()->SetBinLabel(i+1,eventCutTitles[i]); }

	//--------------------- The STAR chain Event loop ---------------------//
	chain->Init();

	// Start  bookeeping stuff. Timer, event counter, etc.
	Double_t overheadTime = timer->RealTime();
	cout << "***** Starting Event Loop. " << overheadTime  << " seconds elapsed so far. *****" << endl;
	timer->Start();
	Int_t iReturn = 0;
	Float_t percentCounter = 0.01;
	Int_t nEventsProcessed = 0;

	// Actual event loop
	for (Int_t iev=0;iev<nEvents; iev++) {

		Float_t progress = (Float_t)iev / (Float_t)nEvents;	
		nEventsProcessed++;
		if(progress >= percentCounter){
			cout << percentCounter * 100 << "% done" << endl;
			percentCounter += .01;
		}

		chain->Clear();
		iReturn = chain->Make(iev); 

		// Assign event quantities
		StMuEvent* event = muMaker->muDst()->event();
        Float_t refmult = event->refMult();
        TObjArray* tracks = muMaker->muDst()->primaryTracks();
        Int_t nTofMatches = calcNumberOfTofMatches(tracks);
        Bool_t eventPass = kTRUE;

        // Do event cuts
        Float_t VzLow = 209, VzHigh = 211, VxLow = -2, VxHigh = 2, VyLow = -4, VyHigh = -2, minTofMatches = 11;
        Float_t vx = event->primaryVertexPosition().x();
        Float_t vy = event->primaryVertexPosition().y();
        Float_t vz = event->primaryVertexPosition().z();
        eventCuts->Fill(0);
        if( (vz > VzLow) && (vz < VzHigh) ) {eventCuts->Fill(1);}
        else { eventPass = kFALSE;}
        if( eventPass && (vx > VxLow) && (vx < VxHigh) ) {eventCuts->Fill(2);}
        else { eventPass = kFALSE;}
        if( eventPass && (vy > VyLow) && (vy < VyHigh) ) {eventCuts->Fill(3);}
        else { eventPass = kFALSE;}
        if ( eventPass && (nTofMatches >= minTofMatches)) {eventCuts->Fill(4);}
        else { eventPass = kFALSE;}

        if(eventPass)
        {
            // Fill histograms
            hRefmult->Fill(refmult);

            StMuTrack* muTrack = 0;
            Int_t nMuTracks = tracks->GetEntries();
            
            for(Int_t j=0; j<nMuTracks; j++)
            {
                muTrack = (StMuTrack*)tracks->UncheckedAt(j);
                particleYield->Fill(0);
                if(checkTrack(muTrack))
                {

                    particleYield->Fill(1);
                    dEdx->Fill(muTrack->dEdx(),muTrack->charge()*muTrack->p().mag());

                    if(isElectron(muTrack)){
                        if(muTrack->charge() == 1) {particleYield->Fill(2);}
                        else {particleYield->Fill(3);}
                    } else if (isPion(muTrack)) {
                        if(muTrack->charge() == 1) {particleYield->Fill(4);}
                        else {particleYield->Fill(5);}
                    } else if (isKaon(muTrack)) {
                        if(muTrack->charge() == 1) {particleYield->Fill(6);}
                        else {particleYield->Fill(7);}
                    } else if (isProton(muTrack)) {
                        if(muTrack->charge() == 1) {particleYield->Fill(8);}
                        else {particleYield->Fill(9);}
                    }

                } // If track is good

            } // Loop over tracks

            if (iReturn) {
                cout << "And... we're done!" << endl;
                break;
            }
        } // If event is good
	} // loop over events 

	Double_t eventLoopTime = timer->RealTime();
	cout << endl << "***** Finished Event Loop. " << eventLoopTime << " seconds to process " << nEventsProcessed << " events."; 
	cout << (Double_t)nEventsProcessed / eventLoopTime << " ev/s." << endl;
	
	chain->Finish();

	TFile* fOut = new TFile(outFile.Data(), "RECREATE");
    hRefmult->Write();
    particleYield->Write();
    eventCuts->Write();
    fOut->Close();

	delete chain;
}

Int_t calcNumberOfTofMatches(TObjArray* tracks) {

	Int_t nPrimary 	= tracks->GetEntries();
	Int_t nTofMatched = 0;
	for (int iNode = 0; iNode < nPrimary; iNode++ ){
		StMuTrack* tPrimary = (StMuTrack*)tracks->UncheckedAt(iNode);

		if ( !tPrimary ) continue;
		if ( tPrimary->vertexIndex() != 0 ) continue;

		StMuBTofPidTraits bTofPidTraits	= tPrimary->btofPidTraits();

		if ( bTofPidTraits.matchFlag() > 0 ) 
			nTofMatched++;
	}

	return nTofMatched;
}

Bool_t checkTrack(StMuTrack* track) {

    Float_t eta = 0.75, ptLow = 0.15, ptHigh = 0.80, nMinHitsTpc = 15, maxDcaGlobal = 3.0;

    Bool_t pass = ( (fabs(track->eta()) < eta)
        && (track->pt() > ptLow)
        && (track->pt() < ptHigh)
	    && (track->topologyMap().numberOfHits(kTpcId) >= 15)
        && (track->dcaGlobal().mag() < maxDcaGlobal)
        );
	
	return pass;
}

Bool_t isElectron(StMuTrack* track)
{

    Bool_t pass = ( fabs(track->nSigmaPion()) > 2) && 
	( fabs(track->nSigmaKaon()) > 2) && 
	( fabs(track->nSigmaProton()) > 2) && 
	( fabs(track->nSigmaElectron()) < 2); 

    return pass;
}

Bool_t isPion(StMuTrack* track)
{

    Bool_t pass = ( fabs(track->nSigmaPion()) < 2) && 
	( fabs(track->nSigmaKaon()) > 2) && 
	( fabs(track->nSigmaProton()) > 2) && 
	( fabs(track->nSigmaElectron()) > 2); 

    return pass;
}

Bool_t isKaon(StMuTrack* track)
{

    Bool_t pass = ( fabs(track->nSigmaPion()) > 2) && 
	( fabs(track->nSigmaKaon()) < 2) && 
	( fabs(track->nSigmaProton()) > 2) && 
	( fabs(track->nSigmaElectron()) > 2); 

    return pass;
}

Bool_t isProton(StMuTrack* track)
{

    Bool_t pass = ( fabs(track->nSigmaPion()) > 2) && 
	( fabs(track->nSigmaKaon()) > 2) && 
	( fabs(track->nSigmaProton()) < 2) && 
	( fabs(track->nSigmaElectron()) > 2); 

    return pass;
}
