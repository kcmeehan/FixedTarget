// This is a basic macro to analyze the fixed target data. In general, it defines/instantiates things
// from "smaller to larger", i.e., defined constants first, then event/track/pair cut objects, then
// Hbt analysis objects, then chains and makers.
//
// Then only thing that's special about this macro is that it uses fxtEventCut and fxtEventCutMonitor 
// objects. The former simply cuts on Vx,Vy,Vz, and the number of Tof matched tracks.

void fxtFemtoAnalysis(const TString fileList = "4x5GeVfxtFiles.list" 
					   , const TString outFile = "fxtTestOut.root"
					   , const Int_t nEvents = 999
                       )
{
	//------------------- Define Cut Values ------------------//

    // Event cuts
    const Int_t mult[2] = {0,1000};
    const Int_t minNumberOfTofMatches = 2;
    const Float_t Vx[2] = {-4,2};
    const Float_t Vy[2] = {-4,0};
    const Float_t Vz[2] = {210,212};

    // Track Cuts
    const Float_t piMass =  0.13957018; // From PDG
    const Float_t rapidity[2] = {-0.75,75};
    const Float_t nSigma[2] = {-2,2};
    const Float_t pt[2] = {0.15,0.80};
    const Float_t nHitsTpc[2] = {15,50};
    const Float_t dcaGlobal[2] = {0.0, 3.0};

    // Pair Cuts
    const Float_t kt[2] = {0.15,0.60};
    const Float_t quality[2] = {-0.5,0.6};
    const Float_t maxFracMergedRows = 0.1;

    // Hbt Analysis parameters
    const Int_t nEventsToMix = 3;
    const Int_t nQbins = 50;
    const Float_t qRange[2] = {0,0.20};

	//------------------- Load Shared Libraries ------------------//

	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();
	gSystem->Load("StFlowMaker");
	gSystem->Load("StHbtMaker");

	//------------------- Instantiate Cut Objects ------------------//

    // We instantiate two sets of event cuts so that each can have it's own cut monitor,
    // which avoids double counting. However, we still only need to have one set of monitors,
    // since they're the same event cuts.
    //
    // Incidentally, I haven't added any track/pair cut monitors, but they can be included
    // in the same way.
    fxtEventCut* eventCut[2];
    fxtEventCutMonitor* eventPass = new fxtEventCutMonitor("eventPass",""); 
    fxtEventCutMonitor* eventFail = new fxtEventCutMonitor("eventFail","");
    
    for(Int_t i = 0; i <= 1; i++)
    {
        eventCut[i] = new fxtEventCut();
        eventCut[i]->SetMult(mult[0],mult[1]);
        eventCut[i]->SetMinTofMatches(minNumberOfTofMatches);
        eventCut[i]->SetVx(Vx[0],Vx[1]);
        eventCut[i]->SetVy(Vy[0],Vy[1]);
        eventCut[i]->SetVz(Vz[0],Vz[1]);
    }

    eventCut[0]->AddCutMonitor(eventPass,eventFail); 

    // Two sets of track cuts, one for pi+ and on for pi-
    franksTrackCut* trackCut[2];
    fxtTrackCutMonitor* trackPiPlusPass = new fxtTrackCutMonitor("_PiPlusPass_",piMass );
    fxtTrackCutMonitor* trackPiPlusFail = new fxtTrackCutMonitor("_PiPlusFail",piMass );
    fxtTrackCutMonitor* trackPiMinusPass = new fxtTrackCutMonitor("_PiMinusPass_",piMass );
    fxtTrackCutMonitor* trackPiMinusFail = new fxtTrackCutMonitor("_PiMinusFail",piMass );

    for(Int_t i = 0; i <=1; i++)
    {
        trackCut[i] = new franksTrackCut;
        trackCut[i]->SetMass(piMass);
        trackCut[i]->SetEta(rapidity[0],rapidity[1]);
        trackCut[i]->SetNSigmaProton(-1000,nSigma[0]);
        trackCut[i]->SetNSigmaKaon(-1000,nSigma[0]);
        trackCut[i]->SetNSigmaPion(nSigma[0],nSigma[1]);
        trackCut[i]->SetNSigmaElectron(-1000,nSigma[0]);
        trackCut[i]->SetPt(pt[0],pt[1]);
        trackCut[i]->SetNHits(nHitsTpc[0],nHitsTpc[1]);
        trackCut[i]->SetDCAGlobal(dcaGlobal[0],dcaGlobal[1]);
        Int_t charge = i ? 1 : -1;
        trackCut[i]->SetCharge(charge);
    }

    trackCut[0]->AddCutMonitor(trackPiMinusPass,trackPiMinusFail);
    trackCut[1]->AddCutMonitor(trackPiPlusPass,trackPiPlusFail);

    // Pair Cuts
    kTPairCut* ktCut = new kTPairCut();
    ktCut->SetkTRange(kt[0],kt[1]);

	qualityPairCut* qualityCut = new qualityPairCut;
	qualityCut->SetQualityCut(quality[0],quality[1]);

	HitMergingPairCut* mergeCut = new HitMergingPairCut;
	mergeCut->setDefaultFullFieldMergingPar();
	mergeCut->setMaxFracOfMergedRow(maxFracMergedRows);

    ManyPairCuts* pairCut = new ManyPairCuts();
    pairCut->AddPairCut(ktCut);
    pairCut->AddPairCut(qualityCut);
    pairCut->AddPairCut(mergeCut);

	//------------------- Instantiate Hbt Analyses and Correlation Functions ------------------//

    StHbtReactionPlaneAnalysis* fxtAnalysis[2];
    QinvCorrFctn* qinvCF[2];
	QoslCMSCorrFctnRPkT* qCorrFctn[2];
    for(Int_t i = 0; i <=1; i++)
    {
        fxtAnalysis[i] = new StHbtReactionPlaneAnalysis(0,1,-999,999,1,1,1000,1,-999,999); //standard
        fxtAnalysis[i]->SetEventCut(eventCut[i]);
        fxtAnalysis[i]->SetFirstParticleCut(trackCut[i]);
        fxtAnalysis[i]->SetSecondParticleCut(trackCut[i]);
        fxtAnalysis[i]->SetPairCut(pairCut);
        fxtAnalysis[i]->SetNumEventsToMix(nEventsToMix);

        TString title = "";
        if(i==0) {title += "PiMinus";}
        if(i==1) {title += "PiPlus";}
//        qinvCF[i] = new QinvCorrFctn(title.Data(),nQbins,qRange[0],qRange[1]);
        qCorrFctn[i] = new QoslCMSCorrFctnRPkT(title.Data(),nQbins,qRange[0],qRange[1],nQbins,qRange[0],qRange[1],nQbins,qRange[0],qRange[1],1);
//        fxtAnalysis[i]->AddCorrFctn(qinvCF[i]);
        fxtAnalysis[i]->AddCorrFctn(qCorrFctn[i]);
    }


	//------------------- Instantiate Chain and Makers ------------------//

	StChain* chain = new StChain("StChain");
	chain->SetDebug(0);

	StMuDstMaker* muMaker = new StMuDstMaker(0,0,"",fileList.Data(),"st:MuDst.root", 1000, "MuDst");
	StHbtMaker* hbtMaker = new StHbtMaker;
    StHbtMuDstMakerReader* reader = new StHbtMuDstMakerReader(muMaker);
	hbtMaker->HbtManager()->SetEventReader(reader);

    for(Int_t i = 0; i <=1; i++)
    {
        hbtMaker->HbtManager()->AddAnalysis(fxtAnalysis[i]);
    }
        
	//--------------------- The STAR chain Event loop ---------------------//

	chain->Init();
  
	for (Int_t i = 0; i < nEvents; i++)
    {

		chain->Clear();
		Int_t makeReturn = chain->Make(i);

		if (makeReturn)
        {
			cout << "Out of events!" << endl;
			break;
		}
	} 

    chain->Finish();

	//--------------------- Write Output ---------------------//
	TFile histoOutput(outFile.Data(),"recreate");

    eventPass->VertexYvsVertexX()->Write();
    eventPass->VertexZ()->Write();
    eventPass->RefMult()->Write();
    eventPass->NumberOfTofMatches()->Write();
    eventFail->VertexYvsVertexX()->Write();
    eventFail->VertexZ()->Write();
    eventFail->RefMult()->Write();
    eventFail->NumberOfTofMatches()->Write();

    for(Int_t i = 0; i <=1; i++)
    {
        /*
        qinvCF[i]->Numerator()->Write();
        qinvCF[i]->Denominator()->Write();
        qinvCF[i]->Ratio()->Write();
        */

        for(int j=0; j<4; j++) { //bins 0,1,2,(3) are typical kt bins for this version. Bin 4 is the ktIntegrated histo.
            qCorrFctn[i]->Numerator3D(0,j)->Write();
            qCorrFctn[i]->Denominator3D(0,j)->Write();
            qCorrFctn[i]->CoulHisto3D(0,j)->Write();
        } // End loop over kt bins
    }

    histoOutput.Close();
  
}
