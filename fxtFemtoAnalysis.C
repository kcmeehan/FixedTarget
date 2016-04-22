// This is a basic macro to analyze the fixed target data. In general, it defines/instantiates things
// from "smaller to larger", i.e., defined constants first, then event/track/pair cut objects, then
// Hbt analysis objects, then chains and makers.
//
// Then only thing that's special about this macro is that it uses fxtEventCut and fxtEventCutMonitor 
// objects. The former simply cuts on Vx,Vy,Vz, and the number of Tof matched tracks.

void fxtFemtoAnalysis(const TString fileList = "muDst.list",  
					   const TString outFile = "fxtTestOut.root",
                       const Int_t multBin = = -1, 
					   const Int_t nEvents = 999
                       )
{
	//------------------- Define Cut Values ------------------//

    // Event cuts
    const Int_t mult[2] = {0,1000};
    const Int_t triggerId = 1;
    const Int_t minNumberOfTofMatches = -1;
    const Float_t Vx[2] = {-4,2};
    const Float_t Vy[2] = {-4,0};
    const Float_t Vz[2] = {210,212};
    // const Float_t multCut[7] = {47.5, 60.5, 76.5, 96.5, 120.5, 153.5, 1000}; // Include high multiplicity tracks
    const Float_t multCut[7] = {47.5, 60.5, 76.5, 96.5, 120.5, 153.5, 200}; // Exclude high multiplicity tracks

    // Track Cuts
    const Float_t piMass =  0.13957018; // From PDG
    const Float_t rapidity[2] = {-999,999};
    const Float_t nSigma[2] = {-2,2};
    const Float_t pt[2] = {0.10,0.30};
    // const Float_t pt[2] = {0.15,0.80};
    const Float_t nHitsTpc[2] = {15,50};
    const Float_t dcaGlobal[2] = {0.0, 3.0};
    const Float_t dEdxHits[2] = {1, 60};
    const Float_t hitsRatio[2] = {0.52, 1};

    // Pair Cuts
    const Float_t kt[2] = {0.15,0.60};
    const Float_t quality[2] = {-0.5,0.6};
    const Float_t maxFracMergedRows = 0.1;

    // Hbt Analysis parameters
    const Int_t nEventsToMix = 3;
    const Int_t nQbins = 40;
    const Float_t qRange[2] = {-0.20,0.20};

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
    fxtEventCut* eventCut[2];
    fxtEventCutMonitor* eventPass = new fxtEventCutMonitor("eventPass",""); 
    fxtEventCutMonitor* eventFail = new fxtEventCutMonitor("eventFail","");
    
    for(Int_t i = 0; i <= 1; i++)
    {
        eventCut[i] = new fxtEventCut();
        if( multBin == -1 ) {
            eventCut[i]->SetMult(-1,10000); // No multiplicity cut
        } else if( multBin <= 5 ) {
            eventCut[i]->SetMult(multCut[multBin],multCut[multBin + 1]);
        } else {
            cout << "multBin " << multBin << " is out of range. Exiting." << endl;
            return;
        }

        eventCut[i]->SetMinTofMatches(minNumberOfTofMatches);
        eventCut[i]->SetTriggerId(triggerId);
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
        trackCut[i]->SetNSigmaPion(nSigma[0],nSigma[1]);
        trackCut[i]->SetNSigmaAntiProton(nSigma[0],nSigma[1]);
        trackCut[i]->SetNSigmaAntiKaon(nSigma[0],nSigma[1]);
        trackCut[i]->SetNSigmaAntiElectron(nSigma[0],nSigma[1]);
        trackCut[i]->SetPt(pt[0],pt[1]);
        trackCut[i]->SetNHits(nHitsTpc[0],nHitsTpc[1]);
        trackCut[i]->SetHitsRatio(hitsRatio[0],hitsRatio[1]);
        trackCut[i]->SetNdEdxHits(dEdxHits[0],dEdxHits[1]);
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

    ManyPairCuts* pairCut[2];
    pairCut[0] = new ManyPairCuts();
    pairCut[0]->AddPairCut(ktCut);
    pairCut[0]->AddPairCut(qualityCut);
    pairCut[0]->AddPairCut(mergeCut);
    pairCut[1] = new ManyPairCuts();
    pairCut[1]->AddPairCut(ktCut);
    pairCut[1]->AddPairCut(qualityCut);
    pairCut[1]->AddPairCut(mergeCut);

    fxtPairCutMonitor* pairPiPlusPass = new fxtPairCutMonitor("_PiPlusPass_" );
    fxtPairCutMonitor* pairPiPlusFail = new fxtPairCutMonitor("_PiPlusFail" );
    fxtPairCutMonitor* pairPiMinusPass = new fxtPairCutMonitor("_PiMinusPass_" );
    fxtPairCutMonitor* pairPiMinusFail = new fxtPairCutMonitor("_PiMinusFail" );

    pairCut[0]->AddCutMonitor(pairPiMinusPass,pairPiMinusFail);
    pairCut[1]->AddCutMonitor(pairPiPlusPass,pairPiPlusFail);

	//------------------- Instantiate Hbt Analyses and Correlation Functions ------------------//

    StHbtReactionPlaneAnalysis* fxtAnalysis[2];
    QinvCorrFctn* qinvCF[2];
	QoslCMSCorrFctnRPkT* qCorrFctn[2];
    for(Int_t i = 0; i <=1; i++)
    {
        fxtAnalysis[i] = new StHbtReactionPlaneAnalysis(0,1,-999,999,1,mult[0],multCut[1],1,-999,999); //standard
        fxtAnalysis[i]->SetEventCut(eventCut[i]);
        fxtAnalysis[i]->SetFirstParticleCut(trackCut[i]);
        fxtAnalysis[i]->SetSecondParticleCut(trackCut[i]);
        fxtAnalysis[i]->SetPairCut(pairCut[i]);
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
    Int_t nEventsProcessed = 0;
  
	for (Int_t i = 0; i < nEvents; i++)
    {
        nEventsProcessed++;
		chain->Clear();
		Int_t makeReturn = chain->Make(i);

		if (makeReturn)
        {
			cout << "Out of events!" << endl;
			break;
		}
	} 

    chain->Finish();
    cout << "Processed " << nEventsProcessed << " events\n";
	//--------------------- Write Output ---------------------//
	TFile histoOutput(outFile.Data(),"recreate");

    histoOutput.mkdir("EventCuts");
    histoOutput.cd("EventCuts");
    eventPass->VertexYvsVertexX()->Write();
    eventPass->VertexZ()->Write();
    eventPass->RefMult()->Write();
    eventPass->NPrimary()->Write();
    eventPass->NumberOfTofMatches()->Write();
    eventPass->TriggerId()->Write();
    eventFail->VertexYvsVertexX()->Write();
    eventFail->VertexZ()->Write();
    eventFail->RefMult()->Write();
    eventFail->NPrimary()->Write();
    eventFail->NumberOfTofMatches()->Write();
    eventFail->TriggerId()->Write();

    histoOutput.cd("../");
    histoOutput.mkdir("TrackCuts");
    histoOutput.cd("TrackCuts");
    trackPiPlusPass->DCA()->Write();
    trackPiPlusPass->DCAGlobal()->Write();
    trackPiPlusPass->Nhits()->Write();
    trackPiPlusPass->NhitsDedx()->Write();
    trackPiPlusPass->HitsRatio()->Write();
    trackPiPlusPass->Pt()->Write();
    trackPiPlusPass->NsigmaPion()->Write();
    trackPiPlusPass->ChiSqr()->Write();
    trackPiPlusFail->DCA()->Write();
    trackPiPlusFail->DCAGlobal()->Write();
    trackPiPlusFail->Nhits()->Write();
    trackPiPlusFail->NhitsDedx()->Write();
    trackPiPlusFail->HitsRatio()->Write();
    trackPiPlusFail->Pt()->Write();
    trackPiPlusFail->NsigmaPion()->Write();
    trackPiPlusFail->ChiSqr()->Write();
    trackPiMinusPass->DCA()->Write();
    trackPiMinusPass->DCAGlobal()->Write();
    trackPiMinusPass->Nhits()->Write();
    trackPiMinusFail->NhitsDedx()->Write();
    trackPiMinusFail->HitsRatio()->Write();
    trackPiMinusPass->Pt()->Write();
    trackPiMinusPass->NsigmaPion()->Write();
    trackPiMinusPass->ChiSqr()->Write();
    trackPiMinusFail->DCA()->Write();
    trackPiMinusFail->DCAGlobal()->Write();
    trackPiMinusFail->Nhits()->Write();
    trackPiMinusFail->NhitsDedx()->Write();
    trackPiMinusFail->HitsRatio()->Write();
    trackPiMinusFail->Pt()->Write();
    trackPiMinusFail->NsigmaPion()->Write();
    trackPiMinusFail->ChiSqr()->Write();

    histoOutput.cd("../");
    histoOutput.mkdir("PairCuts");
    histoOutput.cd("PairCuts");
    pairPiPlusPass->Kt()->Write();
    pairPiPlusPass->FractionOfMergedRow()->Write();
    pairPiPlusPass->SplittingLevel()->Write();
    pairPiPlusFail->Kt()->Write();
    pairPiPlusFail->FractionOfMergedRow()->Write();
    pairPiPlusFail->SplittingLevel()->Write();
    pairPiMinusPass->Kt()->Write();
    pairPiMinusPass->FractionOfMergedRow()->Write();
    pairPiMinusPass->SplittingLevel()->Write();
    pairPiMinusFail->Kt()->Write();
    pairPiMinusFail->FractionOfMergedRow()->Write();
    pairPiMinusFail->SplittingLevel()->Write();

    histoOutput.cd("../");
    for(Int_t i = 0; i <=1; i++)
    {

        for(int j=0; j<=4; j++) { //bins 0,1,2,(3) are typical kt bins for this version. Bin 4 is the ktIntegrated histo.
            qCorrFctn[i]->Numerator3D(0,j)->Write();
            qCorrFctn[i]->Denominator3D(0,j)->Write();
            qCorrFctn[i]->CoulHisto3D(0,j)->Write();
        } // End loop over kt bins
    }

    histoOutput.Close();
  
}
