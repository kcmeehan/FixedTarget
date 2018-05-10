// Class header file
#include "FxtMaker.h"

// Class implementation in CINT
ClassImp(FxtMaker)

// Constructor
FxtMaker::FxtMaker(StMuDstMaker *Maker, TString JobId, Int_t EventsNumber, Double_t inputParameter1, Double_t inputParameter2) : StMaker() {
    // Use input parameters to initialize
    mMuDstMaker      = Maker;
    nEvents          = EventsNumber;
    nEventsProcessed = 0;
    // Systematic analysis parameters
    cutTest1 = inputParameter1;
    cutTest2 = inputParameter2;
    // Name output file by assigned Job ID
    JobIdName = JobId;
    JobIdName.Append(".root");
    // Set particle masses
    Mass_Pion     = 0.139568;
    Mass_Kaon     = 0.493646;
    Mass_Proton   = 0.938272;
    // Choose which EP for flow analysis
    chooseBBCeastEP = kTRUE; chooseTPCEP = kFALSE;
    //chooseBBCeastEP = kFALSE; chooseTPCEP = kTRUE;
    // Set rapidity/pseudorapidity range
    rapidityBins = 8; rapidityLow = -1.72; rapidityHigh = -0.12;
    // Set transverse momentum range
    ptBins = 15; ptLow = 0.0; ptHigh = 3.0;
    // Initialize BBC ADC gain parameters
    for(Int_t i=0;i<16;i++) {
        egain[i] = 1.0; emean[i] = 0.0; esum[i] = 0.0; emean_c[i] = 0.0; esum_c[i] = 0.0;
        wgain[i] = 1.0; wmean[i] = 0.0; wsum[i] = 0.0; wmean_c[i] = 0.0; wsum_c[i] = 0.0;
    }
    // Read input files
    //eventPlanes_input = new TFile("/star/u/ywu27/fxt_res/results/profile.root","read");
    eventPlanes_input = new TFile("./profile.root","read");
    if(!eventPlanes_input->IsOpen()) std::cout<<"No EP file!"<<std::endl;
    if( eventPlanes_input->IsOpen()) {
        std::cout<<"EP file loaded successfully!"<<std::endl;
        // Read TPC EP histograms
        profile3D_tpc_east_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_east_Qx_Qy");
        profile3D_tpc_east_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_east_psiShift");
        profile3D_tpc_west_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_west_Qx_Qy");
        profile3D_tpc_west_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_west_psiShift");
        profile3D_tpc_full_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_full_Qx_Qy");
        profile3D_tpc_full_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_full_psiShift");
        profile3D_thirdEP_Qx_Qy_input     = (TProfile3D*)eventPlanes_input->Get("profile3D_thirdEP_Qx_Qy");
        profile3D_thirdEP_psiShift_input  = (TProfile3D*)eventPlanes_input->Get("profile3D_thirdEP_psiShift");
        // Individual TPC EP
#if indTPCepIndicator > 0
        /*profile3D_tpc_ind_east_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_east_Qx_Qy");
        profile3D_tpc_ind_east_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_east_psiShift");
        profile3D_tpc_ind_west_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_west_Qx_Qy");
        profile3D_tpc_ind_west_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_west_psiShift");
        profile3D_tpc_ind_full_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_full_Qx_Qy");
        profile3D_tpc_ind_full_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_ind_full_psiShift");*/
        
        profile3D_tpc_ind_east_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_east_Qx_Qy");
        profile3D_tpc_ind_east_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_east_psiShift");
        profile3D_tpc_ind_west_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_west_Qx_Qy");
        profile3D_tpc_ind_west_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_west_psiShift");
        profile3D_tpc_ind_full_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_full_Qx_Qy");
        profile3D_tpc_ind_full_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_tpc_full_psiShift");
#endif
        // Read BBC EP histograms
        bbc_east_adc_profile_input        = (TH1D*)eventPlanes_input->Get("bbc_east_adc_profile");
        profile3D_bbc_east_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_east_Qx_Qy");
        profile3D_bbc_east_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_east_psiShift");
        bbc_west_adc_profile_input        = (TH1D*)eventPlanes_input->Get("bbc_west_adc_profile");
        profile3D_bbc_west_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_west_Qx_Qy");
        profile3D_bbc_west_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_west_psiShift");
        profile3D_bbc_full_Qx_Qy_input    = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_full_Qx_Qy");
        profile3D_bbc_full_psiShift_input = (TProfile3D*)eventPlanes_input->Get("profile3D_bbc_full_psiShift");
        // Compute BBC ADC gain parameters
        if(bbc_east_adc_profile_input && bbc_east_adc_profile_input->GetEntries() > 0) {
            Double_t ADCtotal_inner = 0.0, ADCtotal_outer1 = 0.0, ADCtotal_outer2 = 0.0;
            for(Int_t i=1;i<=16;i++) {
                Double_t value1 = bbc_east_adc_profile_input->GetBinContent(i);
                if( i <= 6 ) ADCtotal_inner += value1;
                if( i == 7 || i == 10 || i == 12 || i == 15 ) ADCtotal_outer1 += value1;
                if( i == 8 || i ==  9 || i == 11 || i == 13 || i == 14 || i == 16 ) ADCtotal_outer2 += value1;
            }
            for(Int_t i=1;i<=16;i++) {
                Double_t value1 = bbc_east_adc_profile_input->GetBinContent(i);
                if( i <=  6 ) egain[i-1] = (value1 > 0.0)? ADCtotal_inner/(6.0*value1):0.0;
                if( i ==  7 || i == 12 ) egain[i-1] = (value1 > 0.0)? ADCtotal_outer1/(3.0*value1):0.0;
                if( i == 10 || i == 15 ) egain[i-1] = (value1 > 0.0)? ADCtotal_outer1/(6.0*value1):0.0;
                if( i ==  8 || i == 9 || i == 11 || i == 13 || i == 14 || i == 16 ) egain[i-1] = (value1 > 0.0)? ADCtotal_outer2/(6.0*value1):0.0;
            }
        }
        if(bbc_west_adc_profile_input && bbc_west_adc_profile_input->GetEntries() > 0) {
            Double_t ADCtotal_inner = 0.0, ADCtotal_outer1 = 0.0, ADCtotal_outer2 = 0.0;
            for(Int_t i=1;i<=16;i++) {
                Double_t value1 = bbc_west_adc_profile_input->GetBinContent(i);
                if( i <= 6 ) ADCtotal_inner += value1;
                if( i == 7 || i == 10 || i == 12 || i == 15 ) ADCtotal_outer1 += value1;
                if( i == 8 || i ==  9 || i == 11 || i == 13 || i == 14 || i == 16 ) ADCtotal_outer2 += value1;
            }
            for(Int_t i=1;i<=16;i++) {
                Double_t value1 = bbc_west_adc_profile_input->GetBinContent(i);
                if( i <=  6 ) wgain[i-1] = (value1 > 0.0)? ADCtotal_inner/(6.0*value1):0.0;
                if( i ==  7 || i == 12 ) wgain[i-1] = (value1 > 0.0)? ADCtotal_outer1/(3.0*value1):0.0;
                if( i == 10 || i == 15 ) wgain[i-1] = (value1 > 0.0)? ADCtotal_outer1/(6.0*value1):0.0;
                if( i ==  8 || i == 9 || i == 11 || i == 13 || i == 14 || i == 16 ) wgain[i-1] = (value1 > 0.0)? ADCtotal_outer2/(6.0*value1):0.0;
            }
        }
    }
	// Read particle efficiency table
    PiPlusEffTableFile = new TFile("/star/u/ywu27/Fxt/results/PiPlusEffTable.root","read");
    if( !PiPlusEffTableFile->IsOpen() ) std::cout<<"No Pi+ efficiency table input!"<<std::endl;
    if(  PiPlusEffTableFile->IsOpen() ) {
        std::cout<<"Pi+ efficiency table loaded successfully!"<<std::endl;
        PionPlusEfficiencyTable = (TH3D*)PiPlusEffTableFile->Get("PiPlusEffTable");
    }
    PiMinusEffTableFile = new TFile("/star/u/ywu27/Fxt/results/PiMinusEffTable.root","read");
    if( !PiMinusEffTableFile->IsOpen() ) std::cout<<"No Pi- efficiency table input!"<<std::endl;
    if(  PiMinusEffTableFile->IsOpen() ) {
        std::cout<<"Pi- efficiency table loaded successfully!"<<std::endl;
		PionMinusEfficiencyTable = (TH3D*)PiMinusEffTableFile->Get("PiMinusEffTable");
    }
    KMinusEffTableFile = new TFile("/star/u/ywu27/Fxt/results/KMinusEffTable.root","read");
    if( !KMinusEffTableFile->IsOpen() ) std::cout<<"No K- efficiency table input!"<<std::endl;
    if(  KMinusEffTableFile->IsOpen() ) {
        std::cout<<"K- efficiency table loaded successfully!"<<std::endl;
        KaonMinusEfficiencyTable = (TH3D*)KMinusEffTableFile->Get("KMinusEffTable");
    }
    KPlusEffTableFile = new TFile("/star/u/ywu27/Fxt/results/KPlusEffTable.root","read");
    if( !KPlusEffTableFile->IsOpen() ) std::cout<<"No K+ efficiency table input!"<<std::endl;
    if(  KPlusEffTableFile->IsOpen() ) {
        std::cout<<"K+ efficiency table loaded successfully!"<<std::endl;
        KaonPlusEfficiencyTable = (TH3D*)KPlusEffTableFile->Get("KPlusEffTable");
    }
	ProtonEffTableFile = new TFile("/star/u/ywu27/Fxt/results/ProtonEffTable.root","read");
    if( !ProtonEffTableFile->IsOpen() ) std::cout<<"No Proton efficiency table input!"<<std::endl;
    if(  ProtonEffTableFile->IsOpen() ) {
        std::cout<<"Proton efficiency table loaded successfully!"<<std::endl;
		ProtonEfficiencyTable = (TH3D*)ProtonEffTableFile->Get("ProtonEffTable");
    }
    // TPC eff
    TPC_PID_efficiency_file = new TFile("/star/u/ywu27/Fxt/results/TPC_eff.root","read");
    if( !TPC_PID_efficiency_file->IsOpen() ) std::cout<<"No TPC efficiency table input!"<<std::endl;
    if(  TPC_PID_efficiency_file->IsOpen() ) {
        std::cout<<"TPC efficiency table loaded successfully!"<<std::endl;
        Proton_TPC_efficiency_table = (TH2D*)TPC_PID_efficiency_file->Get("ProtonTPCeffTable");
        //Deuteron_TPC_efficiency_table = (TH2D*)TPC_PID_efficiency_file->Get("DeuteronTPCeffTable");
        //Pion_TPC_efficiency_table = (TH2D*)TPC_PID_efficiency_file->Get("PionTPCeffTable");
        //Electron_TPC_efficiency_table = (TH2D*)TPC_PID_efficiency_file->Get("ElectronTPCeffTable");
    }
    // Read Phi TProfile from file
    phi_input = new TFile("/star/u/ywu27/fxt_res/results/phi_weight.root","READ");
    if( !phi_input->IsOpen() ) std::cout<<"No Phi histogram!"<<std::endl;
    if(  phi_input->IsOpen() )
      {
        std::cout<<"Phi histogram loaded successfully!"<<std::endl;
        Hist_Phi = (TH1D*)phi_input->Get("phi_weight");
      }
}

// Destructor
FxtMaker::~FxtMaker() {/*automatically done by ROOT*/}

// Run once at beginning to create output file and histograms
Int_t FxtMaker::Init() {
    outputFile = new TFile(JobIdName,"recreate");
    // QA plots
    hist_runId = new TH1D("hist_runId","Event runId",daynumber,16140032.5,16140038.5);
    hist_runId->GetXaxis()->SetTitle("RunId");
    hist_runId->GetYaxis()->SetTitle("# of events");
    
    hist_vertMult = new TH1D("hist_vertMult","Vertices multiplicity",401,-0.5,400.5);
    hist_vertMult->GetXaxis()->SetTitle("Vertices #");
    hist_vertMult->GetYaxis()->SetTitle("# of events");
    
    hist_Vz = new TH1D("hist_Vz","V_{Z} [cm]",500,200.0,220.0);
    hist_Vz->GetXaxis()->SetTitle("V_{Z} [cm]");
    hist_Vz->GetYaxis()->SetTitle("# of events");
    
    hist_vpdVz = new TH1D("hist_vpdVz","VPD V_{Z} [cm]",500,200.0,220.0);
    hist_vpdVz->GetXaxis()->SetTitle("VPD V_{Z} [cm]");
    hist_vpdVz->GetYaxis()->SetTitle("# of events");
    
    hist_Vr = new TH1D("hist_Vr","V_{R} [cm]",500,0.0,20.0);
    hist_Vr->GetXaxis()->SetTitle("V_{R} [cm]");
    hist_Vr->GetYaxis()->SetTitle("# of events");
    
    hist_VyVx = new TH2D("hist_VyVx","V_{Y} [cm] vs. V_{X} [cm]",500,-3.0,3.0,500,-3.0,3.0);
    hist_VyVx->GetXaxis()->SetTitle("V_{X} [cm]");
    hist_VyVx->GetYaxis()->SetTitle("V_{Y} [cm]");
    
    hist_refmult = new TH1D("hist_refmult","Reference multiplicity",401,-0.5,400.5);
    hist_refmult->GetXaxis()->SetTitle("RefMult");
    hist_refmult->GetXaxis()->SetTitle("# of events");
    
    hist_grefmult = new TH1D("hist_grefmult","Global reference multiplicity",401,-0.5,400.5);
    hist_grefmult->GetXaxis()->SetTitle("gRefMult");
    hist_grefmult->GetXaxis()->SetTitle("# of events");
    
    hist_tofmult = new TH1D("hist_tofmult","TOF multiplicity",401,-0.5,400.5);
    hist_tofmult->GetXaxis()->SetTitle("TofMult");
    hist_tofmult->GetXaxis()->SetTitle("# of events");
    
    hist_trackmult = new TH1D("hist_trackmult","Track multiplicity",401,-0.5,400.5);
    hist_trackmult->GetXaxis()->SetTitle("TrackMult");
    hist_trackmult->GetXaxis()->SetTitle("# of events");
    
    hist_realTrackMult = new TH1D("hist_realTrackMult","Actual track multiplicity",401,-0.5,400.5);
    hist_realTrackMult->GetXaxis()->SetTitle("TrackMult");
    hist_realTrackMult->GetXaxis()->SetTitle("# of events");
    
    hist_realTrackMult_refmult = new TH2D("hist_realTrackMult_refmult","Actual track multiplicity vs. RefMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_realTrackMult_refmult->GetXaxis()->SetTitle("TrackMult");
    hist_realTrackMult_refmult->GetXaxis()->SetTitle("RefMult");
    
    hist_realTrackMult_grefmult = new TH2D("hist_realTrackMult_grefmult","Actual track multiplicity vs. gRefMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_realTrackMult_grefmult->GetXaxis()->SetTitle("TrackMult");
    hist_realTrackMult_grefmult->GetXaxis()->SetTitle("gRefMult");
    
    hist_realTrackMult_tofmult = new TH2D("hist_realTrackMult_tofmult","Actual track multiplicity vs. TofMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_realTrackMult_tofmult->GetXaxis()->SetTitle("TrackMult");
    hist_realTrackMult_tofmult->GetXaxis()->SetTitle("TofMult");
    
    hist_realTrackMult_trackmult = new TH2D("hist_realTrackMult_trackmult","Actual track multiplicity vs. TrackMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_realTrackMult_trackmult->GetXaxis()->SetTitle("Actual TrackMult");
    hist_realTrackMult_trackmult->GetXaxis()->SetTitle("TrackMult");
    
    hist_refmult_grefmult = new TH2D("hist_refmult_grefmult","RefMult vs. gRefMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_refmult_grefmult->GetXaxis()->SetTitle("gRefMult");
    hist_refmult_grefmult->GetYaxis()->SetTitle("RefMult");
    
    hist_refmult_tofmult = new TH2D("hist_refmult_tofmult","RefMult vs. TofMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_refmult_tofmult->GetXaxis()->SetTitle("TofMult");
    hist_refmult_tofmult->GetYaxis()->SetTitle("RefMult");
    
    hist_refmult_trackmult = new TH2D("hist_refmult_trackmult","RefMult vs. TrackMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_refmult_trackmult->GetXaxis()->SetTitle("TrackMult");
    hist_refmult_trackmult->GetYaxis()->SetTitle("RefMult");
    
    hist_grefmult_tofmult = new TH2D("hist_grefmult_tofmult","gRefMult vs. TofMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_grefmult_tofmult->GetXaxis()->SetTitle("TofMult");
    hist_grefmult_tofmult->GetYaxis()->SetTitle("gRefMult");
    
    hist_grefmult_trackmult = new TH2D("hist_grefmult_trackmult","gRefMult vs. TrackMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_grefmult_trackmult->GetXaxis()->SetTitle("TrackMult");
    hist_grefmult_trackmult->GetYaxis()->SetTitle("gRefMult");
    
    hist_tofmult_trackmult = new TH2D("hist_tofmult_trackmult","TofMult vs. TrackMult",401,-0.5,400.5,401,-0.5,400.5);
    hist_tofmult_trackmult->GetXaxis()->SetTitle("TrackMult");
    hist_tofmult_trackmult->GetYaxis()->SetTitle("TofMult");
    
    hist_ndEdx = new TH1D("hist_ndEdx","nDedx",101,-0.5,100.5);
    hist_ndEdx->GetXaxis()->SetTitle("nDedx");
    hist_ndEdx->GetYaxis()->SetTitle("# of tracks");
    
    hist_nHits = new TH1D("hist_nHits","nHits",101,-0.5,100.5);
    hist_nHits->GetXaxis()->SetTitle("nHits");
    hist_nHits->GetYaxis()->SetTitle("# of tracks");
    
    hist_ratio = new TH1D("hist_ratio","nHitsFit/nHitsPoss",101,0.0,1.0);
    hist_ratio->GetXaxis()->SetTitle("nHitsFit/nHitsPoss");
    hist_ratio->GetYaxis()->SetTitle("# of tracks");
    
    hist_DCA = new TH1D("hist_DCA","DCA [cm]",100,0.0,10.0);
    hist_DCA->GetXaxis()->SetTitle("DCA [cm]");
    hist_DCA->GetYaxis()->SetTitle("# of tracks");
    
    hist_gDCA = new TH1D("hist_gDCA","Global DCA [cm]",100,0.0,10.0);
    hist_gDCA->GetXaxis()->SetTitle("Global DCA [cm]");
    hist_gDCA->GetYaxis()->SetTitle("# of tracks");
    
    hist_cent = new TH1D("hist_cent","Centrality",Ncentralities+1,-0.5,Ncentralities+0.5);
    hist_cent->GetXaxis()->SetTitle("Centrality bin");
    hist_cent->GetYaxis()->SetTitle("# of events");
    // Track histograms
    hist_pt = new TH1D("hist_pt","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta = new TH1D("hist_eta","#eta",200,-3.0,0.5);
    hist_eta->GetXaxis()->SetTitle("#eta");
    hist_eta->GetYaxis()->SetTitle("# of tracks");
    
    hist_phi = new TH1D("hist_phi","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi->GetYaxis()->SetTitle("# of tracks");
    
    hist_dEdx = new TH2D("hist_dEdx","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta = new TH2D("hist_beta","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass = new TH2D("hist_mass","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    
    hist_pt_proton = new TH1D("hist_pt_proton","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt_proton->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt_proton->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta_proton = new TH1D("hist_eta_proton","#eta",200,-3.0,0.5);
    hist_eta_proton->GetXaxis()->SetTitle("#eta");
    hist_eta_proton->GetYaxis()->SetTitle("# of tracks");
    
    hist_y_proton = new TH1D("hist_y_proton","Rapidity y",200,-3.0,0.5);
    hist_y_proton->GetXaxis()->SetTitle("Rapidity y");
    hist_y_proton->GetYaxis()->SetTitle("# of tracks");
    
    hist_rap_eta_proton = new TH2D("hist_rap_eta_proton","proton y versus #eta",250,-2.5,0,250,-2.5,0);
    hist_rap_eta_proton->GetXaxis()->SetTitle("Pseudorapidity #eta");
    hist_rap_eta_proton->GetYaxis()->SetTitle("Rapidity y");
    
    hist_pt_y_proton = new TH2D("hist_pt_y_proton","p_{T} [GeV/c] vs. y",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_y_proton->GetXaxis()->SetTitle("y");
    hist_pt_y_proton->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_pt_eta_proton = new TH2D("hist_pt_eta_proton","p_{T} [GeV/c] vs. #eta",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_eta_proton->GetXaxis()->SetTitle("#eta");
    hist_pt_eta_proton->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_phi_proton = new TH1D("hist_phi_proton","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi_proton->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi_proton->GetYaxis()->SetTitle("# of tracks");
    
    hist_trackmult_proton = new TH1D("hist_trackmult_proton","Proton track multiplicity",1001,-0.5,1000.5);
    hist_trackmult_proton->GetXaxis()->SetTitle("Proton #");
    hist_trackmult_proton->GetXaxis()->SetTitle("# of events");
    
    hist_dEdx_proton = new TH2D("hist_dEdx_proton","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx_proton->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx_proton->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta_proton = new TH2D("hist_beta_proton","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta_proton->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta_proton->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass_proton = new TH2D("hist_mass_proton","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass_proton->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass_proton->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    
    hist_pt_pionPlus = new TH1D("hist_pt_pionPlus","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt_pionPlus->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt_pionPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta_pionPlus = new TH1D("hist_eta_pionPlus","#eta",200,-3.0,0.5);
    hist_eta_pionPlus->GetXaxis()->SetTitle("#eta");
    hist_eta_pionPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_y_pionPlus = new TH1D("hist_y_pionPlus","y",200,-3.0,0.5);
    hist_y_pionPlus->GetXaxis()->SetTitle("Rapidity y");
    hist_y_pionPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_rap_eta_pionPlus = new TH2D("hist_rap_eta_pionPlus","pionPlus y versus #eta",250,-2.5,0,250,-2.5,0);
    hist_rap_eta_pionPlus->GetXaxis()->SetTitle("Pseudorapidity #eta");
    hist_rap_eta_pionPlus->GetYaxis()->SetTitle("Rapidity y");
    
    hist_pt_y_pionPlus = new TH2D("hist_pt_y_pionPlus","p_{T} [GeV/c] vs. y",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_y_pionPlus->GetXaxis()->SetTitle("y");
    hist_pt_y_pionPlus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_pt_eta_pionPlus = new TH2D("hist_pt_eta_pionPlus","p_{T} [GeV/c] vs. #eta",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_eta_pionPlus->GetXaxis()->SetTitle("#eta");
    hist_pt_eta_pionPlus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_phi_pionPlus = new TH1D("hist_phi_pionPlus","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi_pionPlus->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi_pionPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_trackmult_pionPlus = new TH1D("hist_trackmult_pionPlus","#pi^{#plus} track multiplicity",1001,-0.5,1000.5);
    hist_trackmult_pionPlus->GetXaxis()->SetTitle("#pi^{#plus} #");
    hist_trackmult_pionPlus->GetXaxis()->SetTitle("# of events");
    
    hist_dEdx_pionPlus = new TH2D("hist_dEdx_pionPlus","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx_pionPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx_pionPlus->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta_pionPlus = new TH2D("hist_beta_pionPlus","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta_pionPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta_pionPlus->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass_pionPlus = new TH2D("hist_mass_pionPlus","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass_pionPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass_pionPlus->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    
    hist_pt_pionMinus = new TH1D("hist_pt_pionMinus","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt_pionMinus->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt_pionMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta_pionMinus = new TH1D("hist_eta_pionMinus","#eta",200,-3.0,0.5);
    hist_eta_pionMinus->GetXaxis()->SetTitle("#eta");
    hist_eta_pionMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_y_pionMinus = new TH1D("hist_y_pionMinus","y",200,-3.0,0.5);
    hist_y_pionMinus->GetXaxis()->SetTitle("Rapidity y");
    hist_y_pionMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_rap_eta_pionMinus = new TH2D("hist_rap_eta_pionMinus","pionMinus y versus #eta",250,-2.5,0,250,-2.5,0);
    hist_rap_eta_pionMinus->GetXaxis()->SetTitle("Pseudorapidity #eta");
    hist_rap_eta_pionMinus->GetYaxis()->SetTitle("Rapidity y");
    
    hist_pt_y_pionMinus = new TH2D("hist_pt_y_pionMinus","p_{T} [GeV/c] vs. y",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_y_pionMinus->GetXaxis()->SetTitle("y");
    hist_pt_y_pionMinus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_pt_eta_pionMinus = new TH2D("hist_pt_eta_pionMinus","p_{T} [GeV/c] vs. #eta",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_eta_pionMinus->GetXaxis()->SetTitle("#eta");
    hist_pt_eta_pionMinus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_phi_pionMinus = new TH1D("hist_phi_pionMinus","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi_pionMinus->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi_pionMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_trackmult_pionMinus = new TH1D("hist_trackmult_pionMinus","#pi^{#minus} track multiplicity",1001,-0.5,1000.5);
    hist_trackmult_pionMinus->GetXaxis()->SetTitle("#pi^{#minus} #");
    hist_trackmult_pionMinus->GetXaxis()->SetTitle("# of events");
    
    hist_dEdx_pionMinus = new TH2D("hist_dEdx_pionMinus","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx_pionMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx_pionMinus->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta_pionMinus = new TH2D("hist_beta_pionMinus","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta_pionMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta_pionMinus->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass_pionMinus = new TH2D("hist_mass_pionMinus","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass_pionMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass_pionMinus->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    
    hist_pt_kaonPlus = new TH1D("hist_pt_kaonPlus","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt_kaonPlus->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt_kaonPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta_kaonPlus = new TH1D("hist_eta_kaonPlus","#eta",200,-3.0,0.5);
    hist_eta_kaonPlus->GetXaxis()->SetTitle("#eta");
    hist_eta_kaonPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_y_kaonPlus = new TH1D("hist_y_kaonPlus","y",200,-3.0,0.5);
    hist_y_kaonPlus->GetXaxis()->SetTitle("Rapidity y");
    hist_y_kaonPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_rap_eta_kaonPlus = new TH2D("hist_rap_eta_kaonPlus","kaonPlus y versus #eta",250,-2.5,0,250,-2.5,0);
    hist_rap_eta_kaonPlus->GetXaxis()->SetTitle("Pseudorapidity #eta");
    hist_rap_eta_kaonPlus->GetYaxis()->SetTitle("Rapidity y");
    
    hist_pt_y_kaonPlus = new TH2D("hist_pt_y_kaonPlus","p_{T} [GeV/c] vs. y",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_y_kaonPlus->GetXaxis()->SetTitle("y");
    hist_pt_y_kaonPlus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_pt_eta_kaonPlus = new TH2D("hist_pt_eta_kaonPlus","p_{T} [GeV/c] vs. #eta",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_eta_kaonPlus->GetXaxis()->SetTitle("#eta");
    hist_pt_eta_kaonPlus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_phi_kaonPlus = new TH1D("hist_phi_kaonPlus","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi_kaonPlus->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi_kaonPlus->GetYaxis()->SetTitle("# of tracks");
    
    hist_trackmult_kaonPlus = new TH1D("hist_trackmult_kaonPlus","K^{#plus} track multiplicity",1001,-0.5,1000.5);
    hist_trackmult_kaonPlus->GetXaxis()->SetTitle("K^{#plus} #");
    hist_trackmult_kaonPlus->GetXaxis()->SetTitle("# of events");
    
    hist_dEdx_kaonPlus = new TH2D("hist_dEdx_kaonPlus","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx_kaonPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx_kaonPlus->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta_kaonPlus = new TH2D("hist_beta_kaonPlus","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta_kaonPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta_kaonPlus->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass_kaonPlus = new TH2D("hist_mass_kaonPlus","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass_kaonPlus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass_kaonPlus->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    
    hist_pt_kaonMinus = new TH1D("hist_pt_kaonMinus","p_{T} [GeV/c]",1000,0.0,5.0);
    hist_pt_kaonMinus->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    hist_pt_kaonMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_eta_kaonMinus = new TH1D("hist_eta_kaonMinus","#eta",200,-3.0,0.5);
    hist_eta_kaonMinus->GetXaxis()->SetTitle("#eta");
    hist_eta_kaonMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_y_kaonMinus = new TH1D("hist_y_kaonMinus","y",200,-3.0,0.5);
    hist_y_kaonMinus->GetXaxis()->SetTitle("Rapidity y");
    hist_y_kaonMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_rap_eta_kaonMinus = new TH2D("hist_rap_eta_kaonMinus","kaonMinus y versus #eta",250,-2.5,0,250,-2.5,0);
    hist_rap_eta_kaonMinus->GetXaxis()->SetTitle("Pseudorapidity #eta");
    hist_rap_eta_kaonMinus->GetYaxis()->SetTitle("Rapidity y");
    
    hist_pt_y_kaonMinus = new TH2D("hist_pt_y_kaonMinus","p_{T} [GeV/c] vs. y",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_y_kaonMinus->GetXaxis()->SetTitle("y");
    hist_pt_y_kaonMinus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_pt_eta_kaonMinus = new TH2D("hist_pt_eta_kaonMinus","p_{T} [GeV/c] vs. #eta",500,-3.0,0.5,500,0.0,3.5);
    hist_pt_eta_kaonMinus->GetXaxis()->SetTitle("#eta");
    hist_pt_eta_kaonMinus->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    
    hist_phi_kaonMinus = new TH1D("hist_phi_kaonMinus","#phi [Radian]",1000,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_phi_kaonMinus->GetXaxis()->SetTitle("#phi [Radian]");
    hist_phi_kaonMinus->GetYaxis()->SetTitle("# of tracks");
    
    hist_trackmult_kaonMinus = new TH1D("hist_trackmult_kaonMinus","K^{#minus} track multiplicity",1001,-0.5,1000.5);
    hist_trackmult_kaonMinus->GetXaxis()->SetTitle("K^{#minus} #");
    hist_trackmult_kaonMinus->GetXaxis()->SetTitle("# of events");
    
    hist_dEdx_kaonMinus = new TH2D("hist_dEdx_kaonMinus","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    hist_dEdx_kaonMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_dEdx_kaonMinus->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    
    hist_beta_kaonMinus = new TH2D("hist_beta_kaonMinus","1/#beta vs q*|p|",1000,-5.0,5.0,500,0.0,5.0);
    hist_beta_kaonMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_beta_kaonMinus->GetYaxis()->SetTitle("1/#beta");
    
    hist_mass_kaonMinus = new TH2D("hist_mass_kaonMinus","m^{2} vs q*|p|",1000,-5.0,5.0,1000,-0.6,4.0);
    hist_mass_kaonMinus->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    hist_mass_kaonMinus->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    // Flow histograms
    profile3D_proton_v1 = new TProfile3D("profile3D_proton_v1","Proton v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_proton_v1->BuildOptions(-1,1,"");
    profile3D_proton_v1->GetXaxis()->SetTitle("Centrality bin");
    profile3D_proton_v1->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_proton_v1->GetZaxis()->SetTitle("y");
    profile3D_proton_v1->Sumw2();
    profile3D_proton_v1_tpc = new TProfile3D("profile3D_proton_v1_tpc","Proton v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_proton_v1_tpc->BuildOptions(-1,1,"");
    profile3D_proton_v1_tpc->GetXaxis()->SetTitle("Centrality bin");
    profile3D_proton_v1_tpc->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_proton_v1_tpc->GetZaxis()->SetTitle("y");
    profile3D_proton_v1_tpc->Sumw2();
    Char_t name[100], description[200];
    for(Int_t icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_proton_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, Proton v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, Proton v_{1}(y)",30-5*icent,35-5*icent);
        proton_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        proton_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        proton_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    proton_v1_10_25_averaged = new TH1D("hist_proton_v1y_10_25_averaged","10-25% Proton v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    proton_v1_10_25_averaged->GetXaxis()->SetTitle("Rapidity y");
    proton_v1_10_25_averaged->GetYaxis()->SetTitle("v_{1}");
    proton_v1_10_30_averaged = new TH1D("hist_proton_v1y_10_30_averaged","10-30% Proton v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    proton_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    proton_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    profile3D_pionPlus_v1 = new TProfile3D("profile3D_pionPlus_v1","#pi^{#plus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_pionPlus_v1->BuildOptions(-1,1,"");
    profile3D_pionPlus_v1->GetXaxis()->SetTitle("Centrality bin");
    profile3D_pionPlus_v1->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_pionPlus_v1->GetZaxis()->SetTitle("y");
    profile3D_pionPlus_v1->Sumw2();
    profile3D_pionPlus_v1_tpc = new TProfile3D("profile3D_pionPlus_v1_tpc","#pi^{#plus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_pionPlus_v1_tpc->BuildOptions(-1,1,"");
    profile3D_pionPlus_v1_tpc->GetXaxis()->SetTitle("Centrality bin");
    profile3D_pionPlus_v1_tpc->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_pionPlus_v1_tpc->GetZaxis()->SetTitle("y");
    profile3D_pionPlus_v1_tpc->Sumw2();
    for(Int_t icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_pionPlus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, #pi^{#plus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, #pi^{#plus} v_{1}(y)",30-5*icent,35-5*icent);
        pionPlus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        pionPlus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        pionPlus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    pionPlus_v1_10_30_averaged = new TH1D("hist_pionPlus_v1y_averaged","10-30% #pi^{#plus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    pionPlus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    pionPlus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    profile3D_pionMinus_v1 = new TProfile3D("profile3D_pionMinus_v1","#pi^{#minus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_pionMinus_v1->BuildOptions(-1,1,"");
    profile3D_pionMinus_v1->GetXaxis()->SetTitle("Centrality bin");
    profile3D_pionMinus_v1->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_pionMinus_v1->GetZaxis()->SetTitle("y");
    profile3D_pionMinus_v1->Sumw2();
    profile3D_pionMinus_v1_tpc = new TProfile3D("profile3D_pionMinus_v1_tpc","#pi^{#minus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_pionMinus_v1_tpc->BuildOptions(-1,1,"");
    profile3D_pionMinus_v1_tpc->GetXaxis()->SetTitle("Centrality bin");
    profile3D_pionMinus_v1_tpc->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_pionMinus_v1_tpc->GetZaxis()->SetTitle("y");
    profile3D_pionMinus_v1_tpc->Sumw2();
    for(Int_t icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_pionMinus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, #pi^{#minus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, #pi^{#minus} v_{1}(y)",30-5*icent,35-5*icent);
        pionMinus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        pionMinus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        pionMinus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    pionMinus_v1_10_30_averaged = new TH1D("hist_pionMinus_v1y_averaged","10-30% #pi^{#minus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    pionMinus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    pionMinus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    profile3D_kaonPlus_v1 = new TProfile3D("profile3D_kaonPlus_v1","K^{#plus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_kaonPlus_v1->BuildOptions(-1,1,"");
    profile3D_kaonPlus_v1->GetXaxis()->SetTitle("Centrality bin");
    profile3D_kaonPlus_v1->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_kaonPlus_v1->GetZaxis()->SetTitle("y");
    profile3D_kaonPlus_v1->Sumw2();
    profile3D_kaonPlus_v1_tpc = new TProfile3D("profile3D_kaonPlus_v1_tpc","K^{#plus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_kaonPlus_v1_tpc->BuildOptions(-1,1,"");
    profile3D_kaonPlus_v1_tpc->GetXaxis()->SetTitle("Centrality bin");
    profile3D_kaonPlus_v1_tpc->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_kaonPlus_v1_tpc->GetZaxis()->SetTitle("y");
    profile3D_kaonPlus_v1_tpc->Sumw2();
    for(Int_t icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_kaonPlus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, K^{#plus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, K^{#plus} v_{1}(y)",30-5*icent,35-5*icent);
        kaonPlus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        kaonPlus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        kaonPlus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    kaonPlus_v1_10_30_averaged = new TH1D("hist_kaonPlus_v1y_averaged","10-30% K^{#plus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    kaonPlus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    kaonPlus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    profile3D_kaonMinus_v1 = new TProfile3D("profile3D_kaonMinus_v1","K^{#minus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_kaonMinus_v1->BuildOptions(-1,1,"");
    profile3D_kaonMinus_v1->GetXaxis()->SetTitle("Centrality bin");
    profile3D_kaonMinus_v1->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_kaonMinus_v1->GetZaxis()->SetTitle("y");
    profile3D_kaonMinus_v1->Sumw2();
    profile3D_kaonMinus_v1_tpc = new TProfile3D("profile3D_kaonMinus_v1_tpc","K^{#minus} v_{1}",Ncentralities,0.5,Ncentralities+0.5,ptBins,ptLow,ptHigh,rapidityBins,rapidityLow,rapidityHigh,"");
    profile3D_kaonMinus_v1_tpc->BuildOptions(-1,1,"");
    profile3D_kaonMinus_v1_tpc->GetXaxis()->SetTitle("Centrality bin");
    profile3D_kaonMinus_v1_tpc->GetYaxis()->SetTitle("p_{T} [GeV/c]");
    profile3D_kaonMinus_v1_tpc->GetZaxis()->SetTitle("y");
    profile3D_kaonMinus_v1_tpc->Sumw2();
    for(Int_t icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_kaonMinus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, K^{#minus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, K^{#minus} v_{1}(y)",30-5*icent,35-5*icent);
        kaonMinus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        kaonMinus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        kaonMinus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    kaonMinus_v1_10_30_averaged = new TH1D("hist_kaonMinus_v1y_averaged","10-30% K^{#minus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    kaonMinus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    kaonMinus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    // EP histograms
    hist_tpc_east_psi_raw = new TH1D("hist_tpc_east_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_east_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_east_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_east_psi_recentered = new TH1D("hist_tpc_east_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_east_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_east_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_east_psi_flattened = new TH1D("hist_tpc_east_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_east_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_east_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_east_Qx_Qy = new TProfile3D("profile3D_tpc_east_Qx_Qy","profile3D_tpc_east_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_east_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_east_psiShift = new TProfile3D("profile3D_tpc_east_psiShift","profile3D_tpc_east_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_east_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_tpc_west_psi_raw = new TH1D("hist_tpc_west_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_west_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_west_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_west_psi_recentered = new TH1D("hist_tpc_west_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_west_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_west_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_west_psi_flattened = new TH1D("hist_tpc_west_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_west_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_west_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_west_Qx_Qy = new TProfile3D("profile3D_tpc_west_Qx_Qy","profile3D_tpc_west_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_west_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_west_psiShift = new TProfile3D("profile3D_tpc_west_psiShift","profile3D_tpc_west_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_west_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_tpc_full_psi_raw = new TH1D("hist_tpc_full_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_full_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_full_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_full_psi_recentered = new TH1D("hist_tpc_full_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_full_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_full_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_full_psi_flattened = new TH1D("hist_tpc_full_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_full_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_full_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_full_Qx_Qy = new TProfile3D("profile3D_tpc_full_Qx_Qy","profile3D_tpc_full_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_full_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_full_psiShift = new TProfile3D("profile3D_tpc_full_psiShift","profile3D_tpc_full_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_full_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_thirdEP_psi_raw = new TH1D("hist_thirdEP_psi_raw","The 3rd EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_thirdEP_psi_raw->GetXaxis()->SetTitle("#psi^{3rd}_{1} [Radian]");
    hist_thirdEP_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_thirdEP_psi_recentered = new TH1D("hist_thirdEP_psi_recentered","The 3rd EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_thirdEP_psi_recentered->GetXaxis()->SetTitle("#psi^{3rd}_{1} [Radian]");
    hist_thirdEP_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_thirdEP_psi_flattened = new TH1D("hist_thirdEP_psi_flattened","The 3rd EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_thirdEP_psi_flattened->GetXaxis()->SetTitle("#psi^{3rd}_{1} [Radian]");
    hist_thirdEP_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_thirdEP_Qx_Qy = new TProfile3D("profile3D_thirdEP_Qx_Qy","profile3D_thirdEP_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_thirdEP_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_thirdEP_psiShift = new TProfile3D("profile3D_thirdEP_psiShift","profile3D_thirdEP_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_thirdEP_psiShift->BuildOptions(-1.0,1.0,"");
#if indTPCepIndicator > 0
    // TPC EP for every track individually
    hist_tpc_ind_east_psi_raw = new TH1D("hist_tpc_ind_east_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_east_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_east_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_east_psi_recentered = new TH1D("hist_tpc_ind_east_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_east_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_east_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_east_psi_flattened = new TH1D("hist_tpc_ind_east_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_east_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_east_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_ind_east_Qx_Qy = new TProfile3D("profile3D_tpc_ind_east_Qx_Qy","profile3D_tpc_ind_east_Qx_Qy"
                                                  ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_ind_east_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_ind_east_psiShift = new TProfile3D("profile3D_tpc_ind_east_psiShift","profile3D_tpc_ind_east_psiShift"
                                                     ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_ind_east_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_tpc_ind_west_psi_raw = new TH1D("hist_tpc_ind_west_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_west_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_west_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_west_psi_recentered = new TH1D("hist_tpc_ind_west_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_west_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_west_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_west_psi_flattened = new TH1D("hist_tpc_ind_west_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_west_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_west_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_ind_west_Qx_Qy = new TProfile3D("profile3D_tpc_ind_west_Qx_Qy","profile3D_tpc_ind_west_Qx_Qy"
                                                  ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_ind_west_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_ind_west_psiShift = new TProfile3D("profile3D_tpc_ind_west_psiShift","profile3D_tpc_ind_west_psiShift"
                                                     ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_ind_west_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_tpc_ind_full_psi_raw = new TH1D("hist_tpc_ind_full_psi_raw","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_full_psi_raw->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_full_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_full_psi_recentered = new TH1D("hist_tpc_ind_full_psi_recentered","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_full_psi_recentered->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_full_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_tpc_ind_full_psi_flattened = new TH1D("hist_tpc_ind_full_psi_flattened","TPC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_tpc_ind_full_psi_flattened->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    hist_tpc_ind_full_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_tpc_ind_full_Qx_Qy = new TProfile3D("profile3D_tpc_ind_full_Qx_Qy","profile3D_tpc_ind_full_Qx_Qy"
                                                  ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_tpc_ind_full_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_tpc_ind_full_psiShift = new TProfile3D("profile3D_tpc_ind_full_psiShift","profile3D_tpc_ind_full_psiShift"
                                                     ,daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_tpc_ind_full_psiShift->BuildOptions(-1.0,1.0,"");
#endif
    // BBC EPs
    bbc_east_adc_profile = new TH1D("bbc_east_adc_profile","bbc_east_adc_profile",16,0.5,16.5);
    bbc_east_gain_corrected_adc_profile = new TH1D("bbc_east_gain_corrected_adc_profile","bbc_east_gain_corrected_adc_profile",16,0.5,16.5);
    
    hist_bbc_east_psi_raw = new TH1D("hist_bbc_east_psi_raw","BBC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_east_psi_raw->GetXaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    hist_bbc_east_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_east_psi_recentered = new TH1D("hist_bbc_east_psi_recentered","BBC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_east_psi_recentered->GetXaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    hist_bbc_east_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_east_psi_flattened = new TH1D("hist_bbc_east_psi_flattened","BBC east EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_east_psi_flattened->GetXaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    hist_bbc_east_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_bbc_east_Qx_Qy = new TProfile3D("profile3D_bbc_east_Qx_Qy","profile3D_bbc_east_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_bbc_east_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_bbc_east_psiShift = new TProfile3D("profile3D_bbc_east_psiShift","profile3D_bbc_east_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_bbc_east_psiShift->BuildOptions(-1.0,1.0,"");
    
    bbc_west_adc_profile = new TH1D("bbc_west_adc_profile","bbc_west_adc_profile",16,0.5,16.5);
    bbc_west_gain_corrected_adc_profile = new TH1D("bbc_west_gain_corrected_adc_profile","bbc_west_gain_corrected_adc_profile",16,0.5,16.5);
    
    hist_bbc_west_psi_raw = new TH1D("hist_bbc_west_psi_raw","BBC west EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_west_psi_raw->GetXaxis()->SetTitle("#psi^{BBC west}_{1} [Radian]");
    hist_bbc_west_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_west_psi_recentered = new TH1D("hist_bbc_west_psi_recentered","BBC west EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_west_psi_recentered->GetXaxis()->SetTitle("#psi^{BBC west}_{1} [Radian]");
    hist_bbc_west_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_west_psi_flattened = new TH1D("hist_bbc_west_psi_flattened","BBC west EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_west_psi_flattened->GetXaxis()->SetTitle("#psi^{BBC west}_{1} [Radian]");
    hist_bbc_west_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_bbc_west_Qx_Qy = new TProfile3D("profile3D_bbc_west_Qx_Qy","profile3D_bbc_west_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_bbc_west_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_bbc_west_psiShift = new TProfile3D("profile3D_bbc_west_psiShift","profile3D_bbc_west_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_bbc_west_psiShift->BuildOptions(-1.0,1.0,"");
    
    hist_bbc_full_psi_raw = new TH1D("hist_bbc_full_psi_raw","BBC full EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_full_psi_raw->GetXaxis()->SetTitle("#psi^{BBC full}_{1} [Radian]");
    hist_bbc_full_psi_raw->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_full_psi_recentered = new TH1D("hist_bbc_full_psi_recentered","BBC full EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_full_psi_recentered->GetXaxis()->SetTitle("#psi^{BBC full}_{1} [Radian]");
    hist_bbc_full_psi_recentered->GetYaxis()->SetTitle("# of events");
    
    hist_bbc_full_psi_flattened = new TH1D("hist_bbc_full_psi_flattened","BBC full EP",500,-0.5*TMath::Pi(),2.5*TMath::Pi());
    hist_bbc_full_psi_flattened->GetXaxis()->SetTitle("#psi^{BBC full}_{1} [Radian]");
    hist_bbc_full_psi_flattened->GetYaxis()->SetTitle("# of events");
    
    profile3D_bbc_full_Qx_Qy = new TProfile3D("profile3D_bbc_full_Qx_Qy","profile3D_bbc_full_Qx_Qy",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,2,0.5,2.5,"");
    profile3D_bbc_full_Qx_Qy->BuildOptions(0.0,0.0,"");
    
    profile3D_bbc_full_psiShift = new TProfile3D("profile3D_bbc_full_psiShift","profile3D_bbc_full_psiShift",daynumber,0.5,daynumber+0.5,Ncentralities,0.5,Ncentralities+0.5,twoorder,0.5,twoorder+0.5,"");
    profile3D_bbc_full_psiShift->BuildOptions(-1.0,1.0,"");
    // EP resolutions plots
    Double_t xbin[8] = {0.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0};
    profile_correlation_tpc_east_tpc_west = new TProfile("profile_correlation_tpc_east_tpc_west","<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_east_tpc_west->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_east_tpc_west->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_east_thirdEP = new TProfile("profile_correlation_tpc_east_thirdEP","<cos(#psi^{TPC east}_{1} #minus #psi^{3rd}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_east_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_east_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_east_bbc_east = new TProfile("profile_correlation_tpc_east_bbc_east","<cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_east_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_east_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_east_bbc_west = new TProfile("profile_correlation_tpc_east_bbc_west","<cos(#psi^{TPC east}_{1} #minus #psi^{BBC west}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_west_thirdEP = new TProfile("profile_correlation_tpc_west_thirdEP","<cos(#psi^{TPC west}_{1} #minus #psi^{3rd}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_west_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_west_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_west_bbc_east = new TProfile("profile_correlation_tpc_west_bbc_east","<cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_west_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_west_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_tpc_west_bbc_west = new TProfile("profile_correlation_tpc_west_bbc_west","<cos(#psi^{TPC west}_{1} #minus #psi^{BBC west}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_tpc_west_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_tpc_west_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_thirdEP_bbc_east = new TProfile("profile_correlation_thirdEP_bbc_east","<cos(#psi^{3rd}_{1} #minus #psi^{BBC east}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_thirdEP_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_thirdEP_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_thirdEP_bbc_west = new TProfile("profile_correlation_thirdEP_bbc_west","<cos(#psi^{3rd}_{1} #minus #psi^{BBC west}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_thirdEP_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_thirdEP_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    profile_correlation_bbc_east_bbc_west = new TProfile("profile_correlation_bbc_east_bbc_west","<cos(#psi^{BBC east}_{1} #minus #psi^{BBC west}_{1})>",Ncentralities,0.5,Ncentralities+0.5,-1.0,1.0,"");
    profile_correlation_bbc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    profile_correlation_bbc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_east_tpc_west = new TH1D("correlation_tpc_east_tpc_west","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_tpc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_tpc_west->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_east_thirdEP = new TH1D("correlation_tpc_east_thirdEP","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{3rd}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_east_bbc_east = new TH1D("correlation_tpc_east_bbc_east","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_east_bbc_west = new TH1D("correlation_tpc_east_bbc_west","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_west_thirdEP = new TH1D("correlation_tpc_west_thirdEP","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{3rd}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_west_bbc_east = new TH1D("correlation_tpc_west_bbc_east","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    correlation_tpc_west_bbc_west = new TH1D("correlation_tpc_west_bbc_west","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    correlation_thirdEP_bbc_east = new TH1D("correlation_thirdEP_bbc_east","#sqrt{<cos(#psi^{3rd}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_thirdEP_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_thirdEP_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    correlation_thirdEP_bbc_west = new TH1D("correlation_thirdEP_bbc_west","#sqrt{<cos(#psi^{3rd}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_thirdEP_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_thirdEP_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    correlation_bbc_east_bbc_west = new TH1D("correlation_bbc_east_bbc_west","#sqrt{<cos(#psi^{BBC east}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_bbc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_bbc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    resolution_tpc_sub = new TH1D("resolution_tpc_sub","#sqrt{<cos(#psi^{TPC sub}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_tpc_sub->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_sub->GetYaxis()->SetTitle("Resolution");
    
    resolution_tpc_full = new TH1D("resolution_tpc_full","#sqrt{<cos(#psi^{TPC full}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_tpc_full->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_full->GetYaxis()->SetTitle("Resolution");
    
    resolution_bbc_sub = new TH1D("resolution_bbc_sub","#sqrt{<cos(#psi^{BBC sub}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_bbc_sub->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_sub->GetYaxis()->SetTitle("Resolution");
    
    resolution_bbc_full = new TH1D("resolution_bbc_full","#sqrt{<cos(#psi^{BBC full}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_bbc_full->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_full->GetYaxis()->SetTitle("Resolution");
    // Three-EP method
    resolution_tpc_east_threeEP = new TH1D("resolution_tpc_east_threeEP","#sqrt{#frac{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})><cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}}",Ncentralities,xbin);
    resolution_tpc_east_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_east_threeEP->GetYaxis()->SetTitle("Resolution");
    
    resolution_tpc_west_threeEP = new TH1D("resolution_tpc_west_threeEP","#sqrt{#frac{<cos(#psi^{TPC west}_{1} #minus #psi^{TPC east}_{1})><cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}}",Ncentralities,xbin);
    resolution_tpc_west_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_west_threeEP->GetYaxis()->SetTitle("Resolution");
    
    resolution_bbc_east_threeEP = new TH1D("resolution_bbc_east_threeEP","#sqrt{#frac{<cos(#psi^{BBC east}_{1} #minus #psi^{TPC east}_{1})><cos(#psi^{BBC east}_{1} #minus #psi^{TPC west}_{1})>}{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})>}}",Ncentralities,xbin);
    resolution_bbc_east_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_east_threeEP->GetYaxis()->SetTitle("Resolution");
	// BBC ADC channels
    for(Int_t i=0;i<16;i++) {
        sprintf(name,"BBC_ADC_EAST%d",i+1);
        BBC_ADC_EAST[i] = new TH1D(name,name,4500,0.0,4500.0);
        BBC_ADC_EAST[i]->GetXaxis()->SetTitle("ADC");
        BBC_ADC_EAST[i]->GetYaxis()->SetTitle("# of events");
        
        sprintf(name,"BBC_ADC_WEST%d",i+1);
        BBC_ADC_WEST[i] = new TH1D(name,name,4500,0.0,4500.0);
        BBC_ADC_WEST[i]->GetXaxis()->SetTitle("ADC");
        BBC_ADC_WEST[i]->GetYaxis()->SetTitle("# of events");
    }
    // EP correlations in 2D
    correlation2D_tpc_sub = new TH2D("correlation2D_tpc_sub","#psi^{TPC east}_{1} vs. #psi^{TPC west}_{1}",50,-0.5*TMath::Pi(),2.5*TMath::Pi(),50,-0.5*TMath::Pi(),2.5*TMath::Pi());
    correlation2D_tpc_sub->GetXaxis()->SetTitle("#psi^{TPC west}_{1} [Radian]");
    correlation2D_tpc_sub->GetYaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    
    correlation2D_bbc_sub = new TH2D("correlation2D_bbc_sub","#psi^{BBC east}_{1} vs. #psi^{BBC west}_{1}",50,-0.5*TMath::Pi(),2.5*TMath::Pi(),50,-0.5*TMath::Pi(),2.5*TMath::Pi());
    correlation2D_bbc_sub->GetXaxis()->SetTitle("#psi^{BBC west}_{1} [Radian]");
    correlation2D_bbc_sub->GetYaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    
    correlation2D_bbc_east_tpc_east = new TH2D("correlation2D_bbc_east_tpc_east","#psi^{BBC east}_{1} vs. #psi^{TPC east}_{1}",50,-0.5*TMath::Pi(),2.5*TMath::Pi(),50,-0.5*TMath::Pi(),2.5*TMath::Pi());
    correlation2D_bbc_east_tpc_east->GetXaxis()->SetTitle("#psi^{TPC east}_{1} [Radian]");
    correlation2D_bbc_east_tpc_east->GetYaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    
    correlation2D_bbc_east_tpc_west = new TH2D("correlation2D_bbc_east_tpc_west","#psi^{BBC east}_{1} vs. #psi^{TPC west}_{1}",50,-0.5*TMath::Pi(),2.5*TMath::Pi(),50,-0.5*TMath::Pi(),2.5*TMath::Pi());
    correlation2D_bbc_east_tpc_west->GetXaxis()->SetTitle("#psi^{TPC west}_{1} [Radian]");
    correlation2D_bbc_east_tpc_west->GetYaxis()->SetTitle("#psi^{BBC east}_{1} [Radian]");
    
    return kStOK;
}

// Run once at the end to do after process
Int_t FxtMaker::Finish() {
    // Compute BBC ADCs mean
    for(Int_t i=0;i<16;i++) {
        if(esum[i] > 0.0) {
            emean[i] /= esum[i];
            bbc_east_adc_profile->SetBinContent(i+1,emean[i]);
        }
        if(esum_c[i] > 0.0) {
            emean_c[i] /= esum_c[i];
            bbc_east_gain_corrected_adc_profile->SetBinContent(i+1,emean_c[i]);
        }
        if(wsum[i] > 0.0) {
            wmean[i] /= wsum[i];
            bbc_west_adc_profile->SetBinContent(i+1,wmean[i]);
        }
        if(wsum_c[i] > 0.0) {
            wmean_c[i] /= wsum_c[i];
            bbc_west_gain_corrected_adc_profile->SetBinContent(i+1,wmean_c[i]);
        }
    }
    // Compute EP resolutions
    for(int icent=1;icent<=Ncentralities;icent++) {
        // TPC EP
      {
        double resolution = profile_correlation_tpc_east_tpc_west->GetBinContent(icent);
        double error = profile_correlation_tpc_east_tpc_west->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_east_tpc_west->SetBinContent(icent,resolution);
            correlation_tpc_east_tpc_west->SetBinError(icent,error);
            resolution_tpc_sub->SetBinContent(icent,resolution);
            resolution_tpc_sub->SetBinError(icent,error);
            resolution_tpc_east_threeEP->SetBinContent(icent,resolution);
            resolution_tpc_east_threeEP->SetBinError(icent,error);
            resolution_tpc_west_threeEP->SetBinContent(icent,resolution);
            resolution_tpc_west_threeEP->SetBinError(icent,error);
            
            double deltaResSub = 0.005;
            double chiSub = chi(resolution);
            double chiSubDelta = chi(resolution + deltaResSub);
            double mRes = resEventPlane(TMath::Sqrt(2.0) * chiSub);
            double mResDelta = resEventPlane(TMath::Sqrt(2.0) * chiSubDelta);
            double mResErr = error * TMath::Abs(mRes - mResDelta) / deltaResSub;
            
            resolution_tpc_full->SetBinContent(icent,mRes);
            resolution_tpc_full->SetBinError(icent,mResErr);
        }
      }
        // BBC EP
      {
        double resolution = profile_correlation_bbc_east_bbc_west->GetBinContent(icent);
        double error = profile_correlation_bbc_east_bbc_west->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_bbc_east_bbc_west->SetBinContent(icent,resolution);
            correlation_bbc_east_bbc_west->SetBinError(icent,error);
            resolution_bbc_sub->SetBinContent(icent,resolution);
            resolution_bbc_sub->SetBinError(icent,error);
            
            double deltaResSub = 0.005;
            double chiSub = chi(resolution);
            double chiSubDelta = chi(resolution + deltaResSub);
            double mRes = resEventPlane(TMath::Sqrt(2.0) * chiSub);
            double mResDelta = resEventPlane(TMath::Sqrt(2.0) * chiSubDelta);
            double mResErr = error * TMath::Abs(mRes - mResDelta) / deltaResSub;
            
            resolution_bbc_full->SetBinContent(icent,mRes);
            resolution_bbc_full->SetBinError(icent,mResErr);
        }
      }
        // Three-EP method
      {
        double resolution = profile_correlation_tpc_east_thirdEP->GetBinContent(icent);
        double error = profile_correlation_tpc_east_thirdEP->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_east_thirdEP->SetBinContent(icent,resolution);
            correlation_tpc_east_thirdEP->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_tpc_east_bbc_east->GetBinContent(icent);
        double error = profile_correlation_tpc_east_bbc_east->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_east_bbc_east->SetBinContent(icent,resolution);
            correlation_tpc_east_bbc_east->SetBinError(icent,error);
            resolution_bbc_east_threeEP->SetBinContent(icent,resolution);
            resolution_bbc_east_threeEP->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_tpc_east_bbc_west->GetBinContent(icent);
        double error = profile_correlation_tpc_east_bbc_west->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_east_bbc_west->SetBinContent(icent,resolution);
            correlation_tpc_east_bbc_west->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_tpc_west_thirdEP->GetBinContent(icent);
        double error = profile_correlation_tpc_west_thirdEP->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_west_thirdEP->SetBinContent(icent,resolution);
            correlation_tpc_west_thirdEP->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_tpc_west_bbc_east->GetBinContent(icent);
        double error = profile_correlation_tpc_west_bbc_east->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_west_bbc_east->SetBinContent(icent,resolution);
            correlation_tpc_west_bbc_east->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_tpc_west_bbc_west->GetBinContent(icent);
        double error = profile_correlation_tpc_west_bbc_west->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_tpc_west_bbc_west->SetBinContent(icent,resolution);
            correlation_tpc_west_bbc_west->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_thirdEP_bbc_east->GetBinContent(icent);
        double error = profile_correlation_thirdEP_bbc_east->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_thirdEP_bbc_east->SetBinContent(icent,resolution);
            correlation_thirdEP_bbc_east->SetBinError(icent,error);
        }
      }
      {
        double resolution = profile_correlation_thirdEP_bbc_west->GetBinContent(icent);
        double error = profile_correlation_thirdEP_bbc_west->GetBinError(icent);
        if(resolution > 0.0 && error > 0.0) {
            error = (resolution > 0.0 && error > 0.0)? TMath::Abs(0.5*TMath::Power(resolution,-0.5)*error) : 0.0;
            resolution = (resolution > 0.0 && error > 0.0)? TMath::Sqrt(resolution) : 0.0;
            
            correlation_thirdEP_bbc_west->SetBinContent(icent,resolution);
            correlation_thirdEP_bbc_west->SetBinError(icent,error);
        }
      }
    }
    resolution_tpc_east_threeEP->Multiply(correlation_tpc_east_bbc_east);
    resolution_tpc_east_threeEP->Divide(correlation_tpc_west_bbc_east);
    
    resolution_tpc_west_threeEP->Multiply(correlation_tpc_west_bbc_east);
    resolution_tpc_west_threeEP->Divide(correlation_tpc_east_bbc_east);
    
    resolution_bbc_east_threeEP->Multiply(correlation_tpc_west_bbc_east);
    resolution_bbc_east_threeEP->Divide(correlation_tpc_east_tpc_west);
    // Compute flow and apply resolution corrections
    TH1D *psi_resolution_tmp = new TH1D("psi_resolution_tmp","psi_resolution_tmp",rapidityBins,rapidityLow,rapidityHigh);
    TH1D *psi_resolution_tmp_half = new TH1D("psi_resolution_tmp_half","psi_resolution_tmp_half",rapidityBins,rapidityLow,rapidityHigh);
    for(int icent=1;icent<=Ncentralities;icent++){
        for(int bin=1;bin<=rapidityBins;bin++){
            // Prepare resolutions to divide
            if(chooseBBCeastEP) {
                psi_resolution_tmp->SetBinContent(bin,resolution_bbc_east_threeEP->GetBinContent(Ncentralities-icent+1));
                psi_resolution_tmp->SetBinError(bin,resolution_bbc_east_threeEP->GetBinError(Ncentralities-icent+1));
            }
            if(chooseTPCEP) {
                psi_resolution_tmp->SetBinContent(bin,resolution_tpc_west_threeEP->GetBinContent(Ncentralities-icent+1));
                psi_resolution_tmp->SetBinError(bin,resolution_tpc_west_threeEP->GetBinError(Ncentralities-icent+1));
            }
            // Average over momentum region
            // Proton
          {
            int momentumBottomBin = profile3D_proton_v1->GetYaxis()->FindBin(0.5);
            int momentumTopBin = profile3D_proton_v1->GetYaxis()->FindBin(2.0);
            double content = 0.0, contentS = 0.0, error = 0.0;
            int entry = 0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_proton_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_proton_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_proton_v1->GetBinEntries(currentBin) >= 5) {
                        double binContent = profile3D_proton_v1->GetBinContent(currentBin);
                        double binEntry = profile3D_proton_v1->GetBinEntries(currentBin);
                        double binError = profile3D_proton_v1->GetBinError(currentBin);
                        double ss = binError*TMath::Sqrt((double)binEntry);
                        content += binContent*binEntry;
                        contentS+= (ss*ss+binContent*binContent)*binEntry;
                        entry   += (int)binEntry;
                    }
                }
            }
            if(entry > 0.0) {
                content /= (double)entry;
                error = (contentS/(double)entry < content*content)? 0.0 : TMath::Sqrt(contentS/(double)entry-content*content);
                error   /= TMath::Sqrt((double)entry);
                proton_v1_cent[icent-1]->SetBinContent(bin,content);
                proton_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            
            // pionPlus
          {
            int momentumBottomBin = profile3D_pionPlus_v1->GetYaxis()->FindBin(0.2);
            int momentumTopBin = profile3D_pionPlus_v1->GetYaxis()->FindBin(1.6);
            double content = 0.0, contentS = 0.0, error = 0.0;
            int entry = 0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_pionPlus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_pionPlus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_pionPlus_v1->GetBinEntries(currentBin) >= 5) {
                        double binContent = profile3D_pionPlus_v1->GetBinContent(currentBin);
                        double binEntry = profile3D_pionPlus_v1->GetBinEntries(currentBin);
                        double binError = profile3D_pionPlus_v1->GetBinError(currentBin);
                        double ss = binError*TMath::Sqrt((double)binEntry);
                        content += binContent*binEntry;
                        contentS+= (ss*ss+binContent*binContent)*binEntry;
                        entry   += (int)binEntry;
                    }
                }
            }
            if(entry > 0.0) {
                content /= (double)entry;
                error = (contentS/(double)entry < content*content)? 0.0 : TMath::Sqrt(contentS/(double)entry-content*content);
                error   /= TMath::Sqrt((double)entry);
                pionPlus_v1_cent[icent-1]->SetBinContent(bin,content);
                pionPlus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
        }
        for(int bin=1;bin<=rapidityBins;bin++){
            // Prepare resolutions to divide
            if(chooseBBCeastEP) {
                psi_resolution_tmp_half->SetBinContent(bin,resolution_bbc_east_threeEP->GetBinContent(Ncentralities-icent+1));
                psi_resolution_tmp_half->SetBinError(bin,resolution_bbc_east_threeEP->GetBinError(Ncentralities-icent+1));
            }
            if(chooseTPCEP) {
                psi_resolution_tmp_half->SetBinContent(bin,resolution_tpc_west_threeEP->GetBinContent(Ncentralities-icent+1));
                psi_resolution_tmp_half->SetBinError(bin,resolution_tpc_west_threeEP->GetBinError(Ncentralities-icent+1));
            }
            // Average over momentum region
            // pionMinus
          {
            int momentumBottomBin = profile3D_pionMinus_v1->GetYaxis()->FindBin(0.2);
            int momentumTopBin = profile3D_pionMinus_v1->GetYaxis()->FindBin(1.6);
            double content = 0.0, contentS = 0.0, error = 0.0;
            int entry = 0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_pionMinus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_pionMinus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_pionMinus_v1->GetBinEntries(currentBin) >= 5) {
                        double binContent = profile3D_pionMinus_v1->GetBinContent(currentBin);
                        double binEntry = profile3D_pionMinus_v1->GetBinEntries(currentBin);
                        double binError = profile3D_pionMinus_v1->GetBinError(currentBin);
                        double ss = binError*TMath::Sqrt((double)binEntry);
                        content += binContent*binEntry;
                        contentS+= (ss*ss+binContent*binContent)*binEntry;
                        entry   += (int)binEntry;
                    }
                }
            }
            if(entry > 0.0) {
                content /= (double)entry;
                error = (contentS/(double)entry < content*content)? 0.0 : TMath::Sqrt(contentS/(double)entry-content*content);
                error   /= TMath::Sqrt((double)entry);
                pionMinus_v1_cent[icent-1]->SetBinContent(bin,content);
                pionMinus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // kaonPlus
          {
            int momentumBottomBin = profile3D_kaonPlus_v1->GetYaxis()->FindBin(0.2);
            int momentumTopBin = profile3D_kaonPlus_v1->GetYaxis()->FindBin(1.6);
            double content = 0.0, contentS = 0.0, error = 0.0;
            int entry = 0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_kaonPlus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_kaonPlus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_kaonPlus_v1->GetBinEntries(currentBin) >= 5) {
                        double binContent = profile3D_kaonPlus_v1->GetBinContent(currentBin);
                        double binEntry = profile3D_kaonPlus_v1->GetBinEntries(currentBin);
                        double binError = profile3D_kaonPlus_v1->GetBinError(currentBin);
                        double ss = binError*TMath::Sqrt((double)binEntry);
                        content += binContent*binEntry;
                        contentS+= (ss*ss+binContent*binContent)*binEntry;
                        entry   += (int)binEntry;
                    }
                }
            }
            if(entry > 0.0) {
                content /= (double)entry;
                error = (contentS/(double)entry < content*content)? 0.0 : TMath::Sqrt(contentS/(double)entry-content*content);
                error   /= TMath::Sqrt((double)entry);
                kaonPlus_v1_cent[icent-1]->SetBinContent(bin,content);
                kaonPlus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // kaonMinus
          {
            int momentumBottomBin = profile3D_kaonMinus_v1->GetYaxis()->FindBin(0.2);
            int momentumTopBin = profile3D_kaonMinus_v1->GetYaxis()->FindBin(1.6);
            double content = 0.0, contentS = 0.0, error = 0.0;
            int entry = 0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_kaonMinus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_kaonMinus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_kaonMinus_v1->GetBinEntries(currentBin) >= 5) {
                        double binContent = profile3D_kaonMinus_v1->GetBinContent(currentBin);
                        double binEntry = profile3D_kaonMinus_v1->GetBinEntries(currentBin);
                        double binError = profile3D_kaonMinus_v1->GetBinError(currentBin);
                        double ss = binError*TMath::Sqrt((double)binEntry);
                        content += binContent*binEntry;
                        contentS+= (ss*ss+binContent*binContent)*binEntry;
                        entry   += (int)binEntry;
                    }
                }
            }
            if(entry > 0.0) {
                content /= (double)entry;
                error = (contentS/(double)entry < content*content)? 0.0 : TMath::Sqrt(contentS/(double)entry-content*content);
                error   /= TMath::Sqrt((double)entry);
                kaonMinus_v1_cent[icent-1]->SetBinContent(bin,content);
                kaonMinus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
        }
        proton_v1_cent[icent-1]->Divide(psi_resolution_tmp_half);
        pionPlus_v1_cent[icent-1]->Divide(psi_resolution_tmp_half);
        pionMinus_v1_cent[icent-1]->Divide(psi_resolution_tmp_half);
        kaonPlus_v1_cent[icent-1]->Divide(psi_resolution_tmp_half);
        kaonMinus_v1_cent[icent-1]->Divide(psi_resolution_tmp_half);
    }
    // Average flow over centralities
    for(int bin=1;bin<=rapidityBins;bin++){
        // proton
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(proton_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += proton_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(proton_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(proton_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            proton_v1_10_30_averaged->SetBinContent(bin,content);
            proton_v1_10_30_averaged->SetBinError(bin,error);
        }
      }
      {
        double content = 0.0, error = 0.0;
        for(int icent=3;icent<=5;icent++){
            if(proton_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += proton_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(proton_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(proton_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            proton_v1_10_25_averaged->SetBinContent(bin,content);
            proton_v1_10_25_averaged->SetBinError(bin,error);
        }
      }
        
        // pionPlus
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(pionPlus_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += pionPlus_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(pionPlus_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(pionPlus_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            pionPlus_v1_10_30_averaged->SetBinContent(bin,content);
            pionPlus_v1_10_30_averaged->SetBinError(bin,error);
        }
      }
    }
    for(int bin=1;bin<=rapidityBins;bin++){
        // pionMinus
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(pionMinus_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += pionMinus_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(pionMinus_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(pionMinus_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            pionMinus_v1_10_30_averaged->SetBinContent(bin,content);
            pionMinus_v1_10_30_averaged->SetBinError(bin,error);
        }
      }
        // kaonPlus
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(kaonPlus_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += kaonPlus_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(kaonPlus_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(kaonPlus_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            kaonPlus_v1_10_30_averaged->SetBinContent(bin,content);
            kaonPlus_v1_10_30_averaged->SetBinError(bin,error);
        }
      }
        // kaonMinus
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(kaonMinus_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += kaonMinus_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(kaonMinus_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(kaonMinus_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            kaonMinus_v1_10_30_averaged->SetBinContent(bin,content);
            kaonMinus_v1_10_30_averaged->SetBinError(bin,error);
        }
      }
    }
    // Save histograms to output file
    outputFile->Write();
    return kStOK;
}

// Run in every event to do analysis
Int_t FxtMaker::Make() {
    // Get the number of Primary Vertices
    Int_t verticesNumber = mMuDstMaker->muDst()->numberOfPrimaryVertices();
    hist_vertMult->Fill(verticesNumber);
    // vertices loop starts
    /*for ( Int_t iv = 0; iv < verticesNumber; iv++ )*/ {
        // set the ith Primary Vertex as current one
        //mMuDstMaker->muDst()->setVertexIndex(iv);
        // Get Event pointer
        StMuEvent *muEvent = mMuDstMaker->muDst()->event();
        // Check if Event pointer isn't Null
        if(muEvent) {
            // Get Event-wise parameters and fill histograms
            Int_t runId = muEvent->runId();
            Double_t Day = (Double_t)runId - 16140032.0;
            hist_runId->Fill(runId);
            
            Double_t primaryVertex_X = (Double_t)muEvent->primaryVertexPosition().x();
            Double_t primaryVertex_Y = (Double_t)muEvent->primaryVertexPosition().y();
            Double_t primaryVertex_Z = (Double_t)muEvent->primaryVertexPosition().z();
            Double_t primaryVertex_perp = (Double_t)muEvent->primaryVertexPosition().perp();
            hist_Vz->Fill(primaryVertex_Z);
            hist_Vr->Fill(primaryVertex_perp);
            hist_VyVx->Fill(primaryVertex_X,primaryVertex_Y);
            
            // Get VPD Vz
            StBTofHeader *btofhead = mMuDstMaker->muDst()->btofHeader();
            if(btofhead) {
                Double_t VpdVz = btofhead->vpdVz();
                hist_vpdVz->Fill(VpdVz);
            }
            
            // Check triggerId
            Bool_t triggerIdSelection = kFALSE;
            if(muEvent->triggerIdCollection().nominal().isTrigger(1)) triggerIdSelection = kTRUE;
            
            Int_t refMult = muEvent->refMult();
            hist_refmult->Fill(refMult);
            
            Int_t grefMult = muEvent->grefmult();
            hist_grefmult->Fill(grefMult);
            hist_refmult_grefmult->Fill(grefMult,refMult);
            
            // Get the number of Primary Tracks
            Int_t trackMult = mMuDstMaker->muDst()->numberOfPrimaryTracks();
            hist_trackmult->Fill(trackMult);
            hist_refmult_trackmult->Fill(trackMult,refMult);
            hist_grefmult_trackmult->Fill(trackMult,grefMult);
            
            // 1st Primary Tracks loop to get tofMult & centrality
            Int_t tofMult = 0;
            Int_t Ntracks = 0;
            for(Int_t itr=0;itr<trackMult;itr++) {
                // Get Track pointer
                StMuTrack *track = mMuDstMaker->muDst()->primaryTracks(itr);
                // Check if Track pointer isn't Null
                if(track) {
                    // Count tofMult number for current Primary Vertex
                    if(track->btofPidTraits().matchFlag()) tofMult++;
                    // Fill track histograms
                    Int_t nHitsDedx = track->nHitsDedx();
                    hist_ndEdx->Fill(nHitsDedx);
                    
                    Int_t nHitsFit = track->nHitsFit();
                    hist_nHits->Fill(nHitsFit);
                    
                    Double_t trackHitsRatio = (Double_t)nHitsFit/track->nHitsPoss();
                    hist_ratio->Fill(trackHitsRatio);
                    
                    Double_t DCA = track->dca().mag();
                    hist_DCA->Fill(DCA);
                    
                    Double_t GlobalDCA = track->dcaGlobal().mag();
                    hist_gDCA->Fill(GlobalDCA);
                    // Apply Track Cuts
                    if( // Cut on nHitsDedx
                       track->nHitsDedx() > 0
                       // Avoid track splitting
                       && (Double_t)track->nHitsFit()/track->nHitsPoss() >= 0.52
                       // Apply other track cuts
                       //&& TMath::Abs( track->eta() ) < 1.0
                       //&& track->pt() > 0.2 && track->pt() < 5.0
                       //&& track->dcaGlobal().mag() < 2.0
                       ) {
                        // Count primary track number after cuts
                        Ntracks++;
                    } // track cuts end
                } // Track pointer check ends
            } // 1st Primary tracks loop ends
            hist_tofmult->Fill(tofMult);
            hist_tofmult_trackmult->Fill(trackMult,tofMult);
            hist_refmult_tofmult->Fill(tofMult,refMult);
            hist_grefmult_tofmult->Fill(tofMult,grefMult);
            // get centrality
            Int_t centrality = 0;
            if( Ntracks >=   1 && Ntracks <  48 ) centrality = 1; // >30%
            if( Ntracks >=  48 && Ntracks <  61 ) centrality = 2; // 25-30%
            if( Ntracks >=  61 && Ntracks <  77 ) centrality = 3; // 20-25%
            if( Ntracks >=  77 && Ntracks <  97 ) centrality = 4; // 15-20%
            if( Ntracks >=  97 && Ntracks < 121 ) centrality = 5; // 10-15%
            if( Ntracks >= 121 && Ntracks < 153 ) centrality = 6; //  5-10%
            if( Ntracks >= 153 && Ntracks < 240 ) centrality = 7; //  0- 5%
            // Apply Event Cuts
            if( // Check if it's FXT runs
               Day >= 1.0 && Day <= 6.0  // run number 16140033 - 38
               // TriggerId cut
               && triggerIdSelection  // trigger ID=1
               // Apply Vertex Cut
               && verticesNumber > 0
               && mMuDstMaker->muDst()->currentVertexIndex() == 0 // 0-rank Primary Vertex
               // Apply Primary Vertex position cuts
               && primaryVertex_Z > 210.0 && primaryVertex_Z < 212.0
               && primaryVertex_X >  -1.5 && primaryVertex_X <   1.0
               && primaryVertex_Y >  -2.5 && primaryVertex_Y <  -1.0
               // Insert systematic check cuts
               //&& TMath::Abs(primaryVertex_Z - 211.0) < 0.8 + 0.04*cutTest1
               //&& TMath::Abs(primaryVertex_X - -0.25) < 1.0 + 0.05*cutTest1
               //&& TMath::Abs(primaryVertex_Y - -1.75) < 0.6 + 0.03*cutTest1
               // Cut on refMult
               //&& refMult > 5
               // Cut on Ntracks & centralities
               && 1 <= Ntracks && Ntracks < 240  // remove pile-up
               ) {
                hist_realTrackMult->Fill(Ntracks);
                hist_cent->Fill(centrality);
                hist_realTrackMult_refmult->Fill(Ntracks,refMult);
                hist_realTrackMult_grefmult->Fill(Ntracks,grefMult);
                hist_realTrackMult_tofmult->Fill(Ntracks,tofMult);
                hist_realTrackMult_trackmult->Fill(Ntracks,trackMult);
                // Define event plane parameters
                Int_t N_tpc_east = 0, N_tpc_west = 0, N_thirdEP = 0;
                Double_t tpc_east_Qx = 0.0, tpc_east_Qy = 0.0, tpc_east_Qweight = 0.0;
                Double_t tpc_west_Qx = 0.0, tpc_west_Qy = 0.0, tpc_west_Qweight = 0.0;
                Double_t tpc_full_Qx = 0.0, tpc_full_Qy = 0.0;
                Double_t tpc_east_plane1 = -999.0, tpc_east_plane2 = -999.0, tpc_east_plane3 = -999.0;
                Double_t tpc_west_plane1 = -999.0, tpc_west_plane2 = -999.0, tpc_west_plane3 = -999.0;
                Double_t tpc_full_plane1 = -999.0, tpc_full_plane2 = -999.0, tpc_full_plane3 = -999.0;
                Double_t thirdEP_Qx = 0.0, thirdEP_Qy = 0.0, thirdEP_Qweight = 0.0;
                Double_t thirdEP_plane1 = -999.0, thirdEP_plane2 = -999.0, thirdEP_plane3 = -999.0;
#if indTPCepIndicator > 0
                // Individual tpc event plane
                Double_t *Qx1_ex_east = new Double_t[trackMult], *Qy1_ex_east = new Double_t[trackMult], *w1_ex_east = new Double_t[trackMult];
                Double_t *Qx1_ex_west = new Double_t[trackMult], *Qy1_ex_west = new Double_t[trackMult], *w1_ex_west = new Double_t[trackMult];
                Double_t *Qx1_ex_full = new Double_t[trackMult], *Qy1_ex_full = new Double_t[trackMult];
                Double_t *reaction_plane1_ex_east = new Double_t[trackMult], *reaction_plane2_ex_east = new Double_t[trackMult], *reaction_plane3_ex_east = new Double_t[trackMult];
                Double_t *reaction_plane1_ex_west = new Double_t[trackMult], *reaction_plane2_ex_west = new Double_t[trackMult], *reaction_plane3_ex_west = new Double_t[trackMult];
                Double_t *reaction_plane1_ex_full = new Double_t[trackMult], *reaction_plane2_ex_full = new Double_t[trackMult], *reaction_plane3_ex_full = new Double_t[trackMult];
                for (Int_t iTrack=0; iTrack<trackMult; iTrack++) {
                    Qx1_ex_east[iTrack] = 0.0; Qy1_ex_east[iTrack] = 0.0; w1_ex_east[iTrack] = 0.0;
                    Qx1_ex_west[iTrack] = 0.0; Qy1_ex_west[iTrack] = 0.0; w1_ex_west[iTrack] = 0.0;
                    Qx1_ex_full[iTrack] = 0.0; Qy1_ex_full[iTrack] = 0.0;
                    reaction_plane1_ex_east[iTrack] = -999.0; reaction_plane2_ex_east[iTrack] = -999.0; reaction_plane3_ex_east[iTrack] = -999.0;
                    reaction_plane1_ex_west[iTrack] = -999.0; reaction_plane2_ex_west[iTrack] = -999.0; reaction_plane3_ex_west[iTrack] = -999.0;
                    reaction_plane1_ex_full[iTrack] = -999.0; reaction_plane2_ex_full[iTrack] = -999.0; reaction_plane3_ex_full[iTrack] = -999.0;
                }
#endif
                // 2nd Primary Tracks loop to get event plane parameters
                for(Int_t itr=0;itr<trackMult;itr++) {
                    // Get Track pointer
                    StMuTrack *track = mMuDstMaker->muDst()->primaryTracks(itr);
                    // Check if Track pointer isn't Null
                    if(track) {
                        // Apply Track Cuts
                        if( // Cut on nHitsDedx
                           track->nHitsDedx() > 0
                           // Sytemactic checks
                           //track->nHitsDedx() > 10
                           //track->nHitsDedx() > 15
                           //track->nHitsDedx() > 20
                           // Avoid track splitting
                           && (Double_t)track->nHitsFit()/track->nHitsPoss() >= 0.52
                           // Apply other track cuts
                           //&& TMath::Abs( track->eta() ) < 1.0
                           //&& track->pt() > 0.2 && track->pt() < 5.0
                           // Sytemactic checks
                           //&& track->dcaGlobal().mag() < 1.0
                           //&& track->dcaGlobal().mag() < 2.0
                           //&& track->dcaGlobal().mag() < 3.0
                           ) {
                            // Fill track-wise parameter histograms
                            Double_t pt = track->pt();
                            hist_pt->Fill(pt);
                            Double_t pz = track->p().z();
                            Double_t eta = track->eta();
                            hist_eta->Fill(eta);
                            // Get PID parameters
                            Double_t Beta = track->btofPidTraits().beta();
                            Double_t trackP = track->p().mag();
                            Double_t mass2 = 0.0;
                            // Check if TOF info available
                            if(Beta != -999.0) {
                                mass2 = trackP*trackP * ( ( 1.0 / ( Beta*Beta ) ) - 1.0 );
                            }
                            Double_t phi = track->phi();
                            if(phi < 0.0            ) phi += 2.0*TMath::Pi();
                            if(phi > 2.0*TMath::Pi()) phi -= 2.0*TMath::Pi();
                            hist_phi->Fill(phi);
                            // Define flow weight
                            Double_t w0 = 0.0, w1 = 0.0;
                            // Proton
                            if( TMath::Abs( track->nSigmaProton() ) < 2.0
                               && ( ( Beta == -999.0 /*&& TMath::Abs( track->nSigmaPion() ) > 0.3*/ ) ||
                                   ( Beta != -999.0
                                    && mass2 > 0.4
                                    && mass2 < 1.4
                                    // Systematic check cuts
                                    //&& mass2 > 0.4 + 0.008*cutTest1
                                    //&& mass2 < 1.4 - 0.028*cutTest1
                                    )
                                   )
                               && track->charge() > 0
                               // Insert systematic check cuts
                               //&& TMath::Abs( track->nSigmaProton() ) < 1.6 + 0.08*cutTest1
                               )
                              {
                                // Get particle track rapidity
                                Double_t energy_Proton = TMath::Sqrt(trackP*trackP + Mass_Proton*Mass_Proton);
                                Double_t rap_Proton = 0.5*TMath::Log( (energy_Proton + pz) / (energy_Proton - pz) );
                                // Get eff corr
                                Double_t efficiency = 0.0;
                                if(ProtonEffTableFile->IsOpen() && ProtonEfficiencyTable->GetEntries()) {
                                    Int_t centralitybin = centrality;
                                    //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                    Int_t rapiditybin = ProtonEfficiencyTable->GetYaxis()->FindBin(rap_Proton);
                                    Double_t transversemass = TMath::Sqrt( Mass_Proton*Mass_Proton + track->pt()*track->pt() ) - Mass_Proton;
                                    //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                    Int_t transversemassbin = ProtonEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                    if( rapiditybin >= 1 && rapiditybin <= 20
                                       && transversemassbin >= 1 && transversemassbin <= 150
                                       ) {
                                        Int_t tablebin = ProtonEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                        efficiency = ProtonEfficiencyTable->GetBinContent(tablebin);
                                        efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                        //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                    }
                                }
                                // Get phi weight
                                Double_t phi_weight = 0.0;
                                if(phi_input->IsOpen() && Hist_Phi->GetEntries()) {
                                    Int_t phi_bin = Hist_Phi->FindBin(phi);
                                    phi_weight = Hist_Phi->GetBinContent(phi_bin);
                                }
                                if(efficiency > 0.0)
                                  {
                                    w0 = rap_Proton + 1.52;
                                    w1 = efficiency * phi_weight;
                                    //w1 = phi_weight;
                                  }
                              }
                            // Pions
                            if( TMath::Abs( track->nSigmaPion() ) < 2.0
                               && ( ( Beta != -999.0
                                     && mass2 > -0.15
                                     && mass2 < 0.14
                                     // Systematic check cuts
                                     //&& mass2 > -0.15 + 0.003*cutTest1
                                     //&& mass2 < 0.14 - 0.0028*cutTest1
                                     )
                                   )
                               // Insert systematic check cuts
                               //&& TMath::Abs( track->nSigmaPion() ) < 1.6 + 0.08*cutTest1
                               )
                              {
                                // Get particle track rapidity
                                Double_t energy_Pion = TMath::Sqrt(trackP*trackP + Mass_Pion*Mass_Pion);
                                Double_t rap_Pion = 0.5*TMath::Log( (energy_Pion + pz) / (energy_Pion - pz) );
                                if(track->charge() > 0)
                                  {
                                    // Get eff corr
                                    Double_t efficiency = 0.0;
                                    if(PiPlusEffTableFile->IsOpen() && PionPlusEfficiencyTable->GetEntries()) {
                                        Int_t centralitybin = centrality;
                                        //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                        Int_t rapiditybin = PionPlusEfficiencyTable->GetYaxis()->FindBin(rap_Pion);
                                        Double_t transversemass = TMath::Sqrt( Mass_Pion*Mass_Pion + track->pt()*track->pt() ) - Mass_Pion;
                                        //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                        Int_t transversemassbin = PionPlusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 20
                                           && transversemassbin >= 1 && transversemassbin <= 150
                                           ) {
                                            Int_t tablebin = PionPlusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                            efficiency = PionPlusEfficiencyTable->GetBinContent(tablebin);
                                            efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                        }
                                    }
                                    if(efficiency > 0.0)
                                      {
                                        w0 = rap_Pion + 1.52;
                                        w1 = efficiency /* -1.0*/;
                                        //w1 = 1.0;
                                      }
                                  }
                                if(track->charge() < 0)
                                  {
                                    // Get eff corr
                                    Double_t efficiency = 0.0;
                                    if(PiMinusEffTableFile->IsOpen() && PionMinusEfficiencyTable->GetEntries()) {
                                        Int_t centralitybin = centrality;
                                        //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                        Int_t rapiditybin = PionMinusEfficiencyTable->GetYaxis()->FindBin(rap_Pion);
                                        Double_t transversemass = TMath::Sqrt( Mass_Pion*Mass_Pion + track->pt()*track->pt() ) - Mass_Pion;
                                        //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                        Int_t transversemassbin = PionMinusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 20
                                           && transversemassbin >= 1 && transversemassbin <= 150
                                           ) {
                                            Int_t tablebin = PionMinusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                            efficiency = PionMinusEfficiencyTable->GetBinContent(tablebin);
                                            efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                        }
                                    }
                                    if(efficiency > 0.0)
                                      {
                                        w0 = rap_Pion + 1.52;
                                        w1 = efficiency /* -1.0*/;
                                        //w1 = 1.0;
                                      }
                                  }
                              }
                            // Kaons
                            if( TMath::Abs( track->nSigmaKaon() ) < 2.0
                               && ( Beta != -999.0
                                   && mass2 > 0.14
                                   && mass2 < 0.4
                                   // Systematic check cuts
                                   //&& mass2 > 0.14 + 0.0028*cutTest1
                                   //&& mass2 < 0.4 - 0.008*cutTest1
                                   )
                               // Insert systematic check cuts
                               //&& TMath::Abs( track->nSigmaKaon() ) < 1.6 + 0.08*cutTest1
                               )
                              {
                                // Get particle track rapidity
                                Double_t energy_Kaon = TMath::Sqrt(trackP*trackP + Mass_Kaon*Mass_Kaon);
                                Double_t rap_Kaon = 0.5*TMath::Log( (energy_Kaon + pz) / (energy_Kaon - pz) );
                                if(track->charge() > 0)
                                  {
                                    // Get eff corr
                                    Double_t efficiency = 0.0;
                                    if(KPlusEffTableFile->IsOpen() && KaonPlusEfficiencyTable->GetEntries()) {
                                        Int_t centralitybin = centrality;
                                        //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                        Int_t rapiditybin = KaonPlusEfficiencyTable->GetYaxis()->FindBin(rap_Kaon);
                                        Double_t transversemass = TMath::Sqrt( Mass_Kaon*Mass_Kaon + track->pt()*track->pt() ) - Mass_Kaon;
                                        //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                        Int_t transversemassbin = KaonPlusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 20
                                           && transversemassbin >= 1 && transversemassbin <= 150
                                           ) {
                                            Int_t tablebin = KaonPlusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                            efficiency = KaonPlusEfficiencyTable->GetBinContent(tablebin);
                                            efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                        }
                                    }
                                    if(efficiency > 0.0)
                                      {
                                        w0 = rap_Kaon + 1.52;
                                        w1 = efficiency /* -1.0*/;
                                        //w1 = 1.0;
                                      }
                                  }
                                if(track->charge() < 0)
                                  {
                                    // Get eff corr
                                    Double_t efficiency = 0.0;
                                    if(KMinusEffTableFile->IsOpen() && KaonMinusEfficiencyTable->GetEntries()) {
                                        Int_t centralitybin = centrality;
                                        //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                        Int_t rapiditybin = KaonMinusEfficiencyTable->GetYaxis()->FindBin(rap_Kaon);
                                        Double_t transversemass = TMath::Sqrt( Mass_Kaon*Mass_Kaon + track->pt()*track->pt() ) - Mass_Kaon;
                                        //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                        Int_t transversemassbin = KaonMinusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 20
                                           && transversemassbin >= 1 && transversemassbin <= 150
                                           ) {
                                            Int_t tablebin = KaonMinusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                            efficiency = KaonMinusEfficiencyTable->GetBinContent(tablebin);
                                            efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                        }
                                    }
                                    if(efficiency > 0.0)
                                      {
                                        w0 = rap_Kaon + 1.52;
                                        w1 = efficiency /* -1.0*/;
                                        //w1 = 1.0;
                                      }
                                  }
                              }
                            // Systematic check
                            /*if(w0 != 0.0 && w1 != 0.0) {
                                if(TMath::Abs(w0) >= 0.8) {
                                    if(w0 > 0.0) w0 = 0.8;
                                    else if(w0 < 0.0) w0 = -0.8;
                                }
                            }*/
                            /*if(w0*w1 != 0.0) {
                                if(w0*w1 > 0.0) {
                                    w0 = 1.0; w1 = 1.0;
                                }
                                if(w0*w1 < 0.0) {
                                    w0 = 1.0; w1 = -1.0;
                                }
                            }*/
                            //w1 *= pt;
                            // Take all charged particles in
                            //w0 = 1.0; w1 = 1.0;
                            // Accumulate flow vectors
                            Bool_t IsEast = kFALSE, IsWest = kFALSE;
                            //if( eta < -1.165 ) IsEast = kTRUE;
                            //if( eta > -1.155 ) IsWest = kTRUE;
                            Double_t randomNumber = gRandom->Uniform(1);
                            if( randomNumber < 0.5 ) IsEast = kTRUE;
                            if( randomNumber >= 0.5 ) IsWest = kTRUE;
                            // East
                            if( IsEast ) {
                                N_tpc_east++;
                                tpc_east_Qx += w0*w1 * TMath::Cos(phi);
                                tpc_east_Qy += w0*w1 * TMath::Sin(phi);
                                tpc_east_Qweight += TMath::Abs(w0*w1);
                            }
                            // West
                            if( IsWest ) {
                                N_tpc_west++;
                                tpc_west_Qx += w0*w1 * TMath::Cos(phi);
                                tpc_west_Qy += w0*w1 * TMath::Sin(phi);
                                tpc_west_Qweight += TMath::Abs(w0*w1);
                            }
#if indTPCepIndicator > 0
                            for(Int_t iTrack2=0;iTrack2<trackMult;iTrack2++) {
                                if(iTrack2 != itr) {
                                    if( IsEast ) {
                                        Qx1_ex_east[iTrack2] += w0*w1 * TMath::Cos(phi);
                                        Qy1_ex_east[iTrack2] += w0*w1 * TMath::Sin(phi);
                                        w1_ex_east[iTrack2] += TMath::Abs(w0*w1);
                                    }
                                    if( IsWest ) {
                                        Qx1_ex_west[iTrack2] += w0*w1 * TMath::Cos(phi);
                                        Qy1_ex_west[iTrack2] += w0*w1 * TMath::Sin(phi);
                                        w1_ex_west[iTrack2] += TMath::Abs(w0*w1);
                                    }
                                }
                            }
#endif
                        } // Track Cuts end
                    } // Track pointer check ends
                } // 2nd Primary tracks loop ends
                // Event centrality cut
                /*if(centrality >= 1 && centrality <= 7)*/ {
                    // Compute tpc event planes
                    // TPC east
                    if(N_tpc_east >= 5 && tpc_east_Qweight > 0.0) {
                        tpc_east_Qx /= tpc_east_Qweight;
                        tpc_east_Qy /= tpc_east_Qweight;
                        if(tpc_east_Qx || tpc_east_Qy) {
                            tpc_east_plane1 = TMath::ATan2(tpc_east_Qy,tpc_east_Qx);
                            if(tpc_east_plane1 < 0.0            ) tpc_east_plane1 += 2.0*TMath::Pi();
                            if(tpc_east_plane1 > 2.0*TMath::Pi()) tpc_east_plane1 -= 2.0*TMath::Pi();
                            hist_tpc_east_psi_raw->Fill(tpc_east_plane1);
                            // Recenter reaction plane vector
                            profile3D_tpc_east_Qx_Qy->Fill(Day,centrality,1,tpc_east_Qx);
                            profile3D_tpc_east_Qx_Qy->Fill(Day,centrality,2,tpc_east_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_tpc_east_Qx_Qy_input && profile3D_tpc_east_Qx_Qy_input->GetEntries() > 0) {
                                tpc_east_Qx -= profile3D_tpc_east_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                tpc_east_Qy -= profile3D_tpc_east_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(tpc_east_Qx || tpc_east_Qy) {
                                tpc_east_plane2 = TMath::ATan2(tpc_east_Qy,tpc_east_Qx);
                                if(tpc_east_plane2 < 0.0            ) tpc_east_plane2 += 2.0*TMath::Pi();
                                if(tpc_east_plane2 > 2.0*TMath::Pi()) tpc_east_plane2 -= 2.0*TMath::Pi();
                                hist_tpc_east_psi_recentered->Fill(tpc_east_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = tpc_east_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_tpc_east_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_tpc_east_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_east_psiShift_input && profile3D_tpc_east_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_tpc_east_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_tpc_east_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( tpc_east_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( tpc_east_plane2*(k+1) ) ) / (k+1);
                                }
                                tpc_east_plane3 = reaction_plane_new;
                                if(tpc_east_plane3 < 0.0            ) tpc_east_plane3 += 2.0*TMath::Pi();
                                if(tpc_east_plane3 > 2.0*TMath::Pi()) tpc_east_plane3 -= 2.0*TMath::Pi();
                                hist_tpc_east_psi_flattened->Fill(tpc_east_plane3);
                            }
                        }
                    }
                    // TPC west
                    if(N_tpc_west >= 5 && tpc_west_Qweight > 0.0) {
                        tpc_west_Qx /= tpc_west_Qweight;
                        tpc_west_Qy /= tpc_west_Qweight;
                        if(tpc_west_Qx || tpc_west_Qy) {
                            tpc_west_plane1 = TMath::ATan2(tpc_west_Qy,tpc_west_Qx);
                            if(tpc_west_plane1 < 0.0            ) tpc_west_plane1 += 2.0*TMath::Pi();
                            if(tpc_west_plane1 > 2.0*TMath::Pi()) tpc_west_plane1 -= 2.0*TMath::Pi();
                            hist_tpc_west_psi_raw->Fill(tpc_west_plane1);
                            // Recenter reaction plane vector
                            profile3D_tpc_west_Qx_Qy->Fill(Day,centrality,1,tpc_west_Qx);
                            profile3D_tpc_west_Qx_Qy->Fill(Day,centrality,2,tpc_west_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_tpc_west_Qx_Qy_input && profile3D_tpc_west_Qx_Qy_input->GetEntries() > 0) {
                                tpc_west_Qx -= profile3D_tpc_west_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                tpc_west_Qy -= profile3D_tpc_west_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(tpc_west_Qx || tpc_west_Qy) {
                                tpc_west_plane2 = TMath::ATan2(tpc_west_Qy,tpc_west_Qx);
                                if(tpc_west_plane2 < 0.0            ) tpc_west_plane2 += 2.0*TMath::Pi();
                                if(tpc_west_plane2 > 2.0*TMath::Pi()) tpc_west_plane2 -= 2.0*TMath::Pi();
                                hist_tpc_west_psi_recentered->Fill(tpc_west_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = tpc_west_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_tpc_west_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_tpc_west_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_west_psiShift_input && profile3D_tpc_west_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_tpc_west_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_tpc_west_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( tpc_west_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( tpc_west_plane2*(k+1) ) ) / (k+1);
                                }
                                tpc_west_plane3 = reaction_plane_new;
                                if(tpc_west_plane3 < 0.0            ) tpc_west_plane3 += 2.0*TMath::Pi();
                                if(tpc_west_plane3 > 2.0*TMath::Pi()) tpc_west_plane3 -= 2.0*TMath::Pi();
                                hist_tpc_west_psi_flattened->Fill(tpc_west_plane3);
                            }
                        }
                    }
                    // TPC full
                    if( (N_tpc_east + N_tpc_west) >= 5 && tpc_east_Qweight > 0.0 && tpc_west_Qweight > 0.0 ) {
                        tpc_full_Qx = tpc_east_Qx/tpc_east_Qweight + tpc_west_Qx/tpc_west_Qweight;
                        tpc_full_Qy = tpc_east_Qy/tpc_east_Qweight + tpc_west_Qy/tpc_west_Qweight;
                        if(tpc_full_Qx || tpc_full_Qy) {
                            tpc_full_plane1 = TMath::ATan2(tpc_full_Qy,tpc_full_Qx);
                            if(tpc_full_plane1 < 0.0            ) tpc_full_plane1 += 2.0*TMath::Pi();
                            if(tpc_full_plane1 > 2.0*TMath::Pi()) tpc_full_plane1 -= 2.0*TMath::Pi();
                            hist_tpc_full_psi_raw->Fill(tpc_full_plane1);
                            // Recenter reaction plane vector
                            profile3D_tpc_full_Qx_Qy->Fill(Day,centrality,1,tpc_full_Qx);
                            profile3D_tpc_full_Qx_Qy->Fill(Day,centrality,2,tpc_full_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_tpc_full_Qx_Qy_input && profile3D_tpc_full_Qx_Qy_input->GetEntries() > 0) {
                                tpc_full_Qx -= profile3D_tpc_full_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                tpc_full_Qy -= profile3D_tpc_full_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(tpc_full_Qx || tpc_full_Qy) {
                                tpc_full_plane2 = TMath::ATan2(tpc_full_Qy,tpc_full_Qx);
                                if(tpc_full_plane2 < 0.0            ) tpc_full_plane2 += 2.0*TMath::Pi();
                                if(tpc_full_plane2 > 2.0*TMath::Pi()) tpc_full_plane2 -= 2.0*TMath::Pi();
                                hist_tpc_full_psi_recentered->Fill(tpc_full_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = tpc_full_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_tpc_full_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_tpc_full_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_full_psiShift_input && profile3D_tpc_full_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_tpc_full_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_tpc_full_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( tpc_full_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( tpc_full_plane2*(k+1) ) ) / (k+1);
                                }
                                tpc_full_plane3 = reaction_plane_new;
                                if(tpc_full_plane3 < 0.0            ) tpc_full_plane3 += 2.0*TMath::Pi();
                                if(tpc_full_plane3 > 2.0*TMath::Pi()) tpc_full_plane3 -= 2.0*TMath::Pi();
                                hist_tpc_full_psi_flattened->Fill(tpc_full_plane3);
                            }
                        }
                    }
                    // 3rd EP
                    if(N_thirdEP >= 5 && thirdEP_Qweight > 0.0) {
                        thirdEP_Qx /= thirdEP_Qweight;
                        thirdEP_Qy /= thirdEP_Qweight;
                        if(thirdEP_Qx || thirdEP_Qy) {
                            thirdEP_plane1 = TMath::ATan2(thirdEP_Qy,thirdEP_Qx);
                            if(thirdEP_plane1 < 0.0            ) thirdEP_plane1 += 2.0*TMath::Pi();
                            if(thirdEP_plane1 > 2.0*TMath::Pi()) thirdEP_plane1 -= 2.0*TMath::Pi();
                            hist_thirdEP_psi_raw->Fill(thirdEP_plane1);
                            // Recenter reaction plane vector
                            profile3D_thirdEP_Qx_Qy->Fill(Day,centrality,1,thirdEP_Qx);
                            profile3D_thirdEP_Qx_Qy->Fill(Day,centrality,2,thirdEP_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_thirdEP_Qx_Qy_input && profile3D_thirdEP_Qx_Qy_input->GetEntries() > 0) {
                                thirdEP_Qx -= profile3D_thirdEP_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                thirdEP_Qy -= profile3D_thirdEP_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(thirdEP_Qx || thirdEP_Qy) {
                                thirdEP_plane2 = TMath::ATan2(thirdEP_Qy,thirdEP_Qx);
                                if(thirdEP_plane2 < 0.0            ) thirdEP_plane2 += 2.0*TMath::Pi();
                                if(thirdEP_plane2 > 2.0*TMath::Pi()) thirdEP_plane2 -= 2.0*TMath::Pi();
                                hist_thirdEP_psi_recentered->Fill(thirdEP_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = thirdEP_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_thirdEP_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_thirdEP_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_thirdEP_psiShift_input && profile3D_thirdEP_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_thirdEP_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_thirdEP_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( thirdEP_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( thirdEP_plane2*(k+1) ) ) / (k+1);
                                }
                                thirdEP_plane3 = reaction_plane_new;
                                if(thirdEP_plane3 < 0.0            ) thirdEP_plane3 += 2.0*TMath::Pi();
                                if(thirdEP_plane3 > 2.0*TMath::Pi()) thirdEP_plane3 -= 2.0*TMath::Pi();
                                hist_thirdEP_psi_flattened->Fill(thirdEP_plane3);
                            }
                        }
                    }
#if indTPCepIndicator > 0
                    for(Int_t iTrack2=0;iTrack2<trackMult;iTrack2++) {
                        // Ind TPC east
                        if(N_tpc_east >= 5 && w1_ex_east[iTrack2] > 0.0) {
                            Qx1_ex_east[iTrack2] /= w1_ex_east[iTrack2];
                            Qy1_ex_east[iTrack2] /= w1_ex_east[iTrack2];
                            if(Qx1_ex_east[iTrack2] || Qy1_ex_east[iTrack2]) {
                                reaction_plane1_ex_east[iTrack2] = TMath::ATan2(Qy1_ex_east[iTrack2],Qx1_ex_east[iTrack2]);
                                if(reaction_plane1_ex_east[iTrack2] < 0.0            ) reaction_plane1_ex_east[iTrack2] += 2.0*TMath::Pi();
                                if(reaction_plane1_ex_east[iTrack2] > 2.0*TMath::Pi()) reaction_plane1_ex_east[iTrack2] -= 2.0*TMath::Pi();
                                hist_tpc_ind_east_psi_raw->Fill(reaction_plane1_ex_east[iTrack2]);
                                // Recenter reaction plane vector
                                profile3D_tpc_ind_east_Qx_Qy->Fill(Day,centrality,1,Qx1_ex_east[iTrack2]);
                                profile3D_tpc_ind_east_Qx_Qy->Fill(Day,centrality,2,Qy1_ex_east[iTrack2]);
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_east_Qx_Qy_input && profile3D_tpc_ind_east_Qx_Qy_input->GetEntries() > 0) {
                                    Qx1_ex_east[iTrack2] -= profile3D_tpc_ind_east_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                    Qy1_ex_east[iTrack2] -= profile3D_tpc_ind_east_Qx_Qy_input->GetBinContent(Day,centrality,2);
                                }
                                if(Qx1_ex_east[iTrack2] || Qy1_ex_east[iTrack2]) {
                                    reaction_plane2_ex_east[iTrack2] = TMath::ATan2(Qy1_ex_east[iTrack2],Qx1_ex_east[iTrack2]);
                                    if(reaction_plane2_ex_east[iTrack2] < 0.0            ) reaction_plane2_ex_east[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane2_ex_east[iTrack2] > 2.0*TMath::Pi()) reaction_plane2_ex_east[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_east_psi_recentered->Fill(reaction_plane2_ex_east[iTrack2]);
                                    // Shift recenterd event plane to flat
                                    Double_t reaction_plane_new = reaction_plane2_ex_east[iTrack2];
                                    for(Int_t k=0;k<order;k++) {
                                        profile3D_tpc_ind_east_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                        profile3D_tpc_ind_east_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                    }
                                    Double_t psi_mean[twoorder];
                                    for(Int_t i=0;i<twoorder;i++) {
                                        psi_mean[i] = 0.0;
                                    }
                                    if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_east_psiShift_input && profile3D_tpc_ind_east_psiShift_input->GetEntries() > 0) {
                                        for(Int_t k=0;k<order;k++) {
                                            psi_mean[0+2*k] = profile3D_tpc_ind_east_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                            psi_mean[1+2*k] = profile3D_tpc_ind_east_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                        }
                                    }
                                    for(Int_t k=0;k<order;k++) {
                                        reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( reaction_plane2_ex_east[iTrack2]*(k+1) )
                                                               + 2.0*psi_mean[0+2*k] * TMath::Sin( reaction_plane2_ex_east[iTrack2]*(k+1) ) ) / (k+1);
                                    }
                                    reaction_plane3_ex_east[iTrack2] = reaction_plane_new;
                                    if(reaction_plane3_ex_east[iTrack2] < 0.0            ) reaction_plane3_ex_east[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane3_ex_east[iTrack2] > 2.0*TMath::Pi()) reaction_plane3_ex_east[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_east_psi_flattened->Fill(reaction_plane3_ex_east[iTrack2]);
                                }
                            }
                        }
                        // Ind TPC west
                        if(N_tpc_west >= 5 && w1_ex_west[iTrack2] > 0.0) {
                            Qx1_ex_west[iTrack2] /= w1_ex_west[iTrack2];
                            Qy1_ex_west[iTrack2] /= w1_ex_west[iTrack2];
                            if(Qx1_ex_west[iTrack2] || Qy1_ex_west[iTrack2]) {
                                reaction_plane1_ex_west[iTrack2] = TMath::ATan2(Qy1_ex_west[iTrack2],Qx1_ex_west[iTrack2]);
                                if(reaction_plane1_ex_west[iTrack2] < 0.0            ) reaction_plane1_ex_west[iTrack2] += 2.0*TMath::Pi();
                                if(reaction_plane1_ex_west[iTrack2] > 2.0*TMath::Pi()) reaction_plane1_ex_west[iTrack2] -= 2.0*TMath::Pi();
                                hist_tpc_ind_west_psi_raw->Fill(reaction_plane1_ex_west[iTrack2]);
                                // Recenter reaction plane vector
                                profile3D_tpc_ind_west_Qx_Qy->Fill(Day,centrality,1,Qx1_ex_west[iTrack2]);
                                profile3D_tpc_ind_west_Qx_Qy->Fill(Day,centrality,2,Qy1_ex_west[iTrack2]);
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_west_Qx_Qy_input && profile3D_tpc_ind_west_Qx_Qy_input->GetEntries() > 0) {
                                    Qx1_ex_west[iTrack2] -= profile3D_tpc_ind_west_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                    Qy1_ex_west[iTrack2] -= profile3D_tpc_ind_west_Qx_Qy_input->GetBinContent(Day,centrality,2);
                                }
                                if(Qx1_ex_west[iTrack2] || Qy1_ex_west[iTrack2]) {
                                    reaction_plane2_ex_west[iTrack2] = TMath::ATan2(Qy1_ex_west[iTrack2],Qx1_ex_west[iTrack2]);
                                    if(reaction_plane2_ex_west[iTrack2] < 0.0            ) reaction_plane2_ex_west[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane2_ex_west[iTrack2] > 2.0*TMath::Pi()) reaction_plane2_ex_west[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_west_psi_recentered->Fill(reaction_plane2_ex_west[iTrack2]);
                                    // Shift recenterd event plane to flat
                                    Double_t reaction_plane_new = reaction_plane2_ex_west[iTrack2];
                                    for(Int_t k=0;k<order;k++) {
                                        profile3D_tpc_ind_west_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                        profile3D_tpc_ind_west_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                    }
                                    Double_t psi_mean[twoorder];
                                    for(Int_t i=0;i<twoorder;i++) {
                                        psi_mean[i] = 0.0;
                                    }
                                    if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_west_psiShift_input && profile3D_tpc_ind_west_psiShift_input->GetEntries() > 0) {
                                        for(Int_t k=0;k<order;k++) {
                                            psi_mean[0+2*k] = profile3D_tpc_ind_west_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                            psi_mean[1+2*k] = profile3D_tpc_ind_west_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                        }
                                    }
                                    for(Int_t k=0;k<order;k++) {
                                        reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( reaction_plane2_ex_west[iTrack2]*(k+1) )
                                                               + 2.0*psi_mean[0+2*k] * TMath::Sin( reaction_plane2_ex_west[iTrack2]*(k+1) ) ) / (k+1);
                                    }
                                    reaction_plane3_ex_west[iTrack2] = reaction_plane_new;
                                    if(reaction_plane3_ex_west[iTrack2] < 0.0            ) reaction_plane3_ex_west[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane3_ex_west[iTrack2] > 2.0*TMath::Pi()) reaction_plane3_ex_west[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_west_psi_flattened->Fill(reaction_plane3_ex_west[iTrack2]);
                                }
                            }
                        }
                        // Ind TPC full
                        if( (N_tpc_east + N_tpc_west) >= 5 && w1_ex_east[iTrack2] > 0.0 && w1_ex_west[iTrack2] > 0.0 ) {
                            Qx1_ex_full[iTrack2] = Qx1_ex_east[iTrack2]/w1_ex_east[iTrack2] + Qx1_ex_west[iTrack2]/w1_ex_west[iTrack2];
                            Qy1_ex_full[iTrack2] = Qy1_ex_east[iTrack2]/w1_ex_east[iTrack2] + Qy1_ex_west[iTrack2]/w1_ex_west[iTrack2];
                            if(Qx1_ex_full[iTrack2] || Qy1_ex_full[iTrack2]) {
                                reaction_plane1_ex_full[iTrack2] = TMath::ATan2(Qy1_ex_full[iTrack2],Qx1_ex_full[iTrack2]);
                                if(reaction_plane1_ex_full[iTrack2] < 0.0            ) reaction_plane1_ex_full[iTrack2] += 2.0*TMath::Pi();
                                if(reaction_plane1_ex_full[iTrack2] > 2.0*TMath::Pi()) reaction_plane1_ex_full[iTrack2] -= 2.0*TMath::Pi();
                                hist_tpc_ind_full_psi_raw->Fill(reaction_plane1_ex_full[iTrack2]);
                                // Recenter reaction plane vector
                                profile3D_tpc_ind_full_Qx_Qy->Fill(Day,centrality,1,Qx1_ex_full[iTrack2]);
                                profile3D_tpc_ind_full_Qx_Qy->Fill(Day,centrality,2,Qy1_ex_full[iTrack2]);
                                if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_full_Qx_Qy_input && profile3D_tpc_ind_full_Qx_Qy_input->GetEntries() > 0) {
                                    Qx1_ex_full[iTrack2] -= profile3D_tpc_ind_full_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                    Qy1_ex_full[iTrack2] -= profile3D_tpc_ind_full_Qx_Qy_input->GetBinContent(Day,centrality,2);
                                }
                                if(Qx1_ex_full[iTrack2] || Qy1_ex_full[iTrack2]) {
                                    reaction_plane2_ex_full[iTrack2] = TMath::ATan2(Qy1_ex_full[iTrack2],Qx1_ex_full[iTrack2]);
                                    if(reaction_plane2_ex_full[iTrack2] < 0.0            ) reaction_plane2_ex_full[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane2_ex_full[iTrack2] > 2.0*TMath::Pi()) reaction_plane2_ex_full[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_full_psi_recentered->Fill(reaction_plane2_ex_full[iTrack2]);
                                    // Shift recenterd event plane to flat
                                    Double_t reaction_plane_new = reaction_plane2_ex_full[iTrack2];
                                    for(Int_t k=0;k<order;k++) {
                                        profile3D_tpc_ind_full_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                        profile3D_tpc_ind_full_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                    }
                                    Double_t psi_mean[twoorder];
                                    for(Int_t i=0;i<twoorder;i++) {
                                        psi_mean[i] = 0.0;
                                    }
                                    if(eventPlanes_input->IsOpen() && profile3D_tpc_ind_full_psiShift_input && profile3D_tpc_ind_full_psiShift_input->GetEntries() > 0) {
                                        for(Int_t k=0;k<order;k++) {
                                            psi_mean[0+2*k] = profile3D_tpc_ind_full_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                            psi_mean[1+2*k] = profile3D_tpc_ind_full_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                        }
                                    }
                                    for(Int_t k=0;k<order;k++) {
                                        reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( reaction_plane2_ex_full[iTrack2]*(k+1) )
                                                               + 2.0*psi_mean[0+2*k] * TMath::Sin( reaction_plane2_ex_full[iTrack2]*(k+1) ) ) / (k+1);
                                    }
                                    reaction_plane3_ex_full[iTrack2] = reaction_plane_new;
                                    if(reaction_plane3_ex_full[iTrack2] < 0.0            ) reaction_plane3_ex_full[iTrack2] += 2.0*TMath::Pi();
                                    if(reaction_plane3_ex_full[iTrack2] > 2.0*TMath::Pi()) reaction_plane3_ex_full[iTrack2] -= 2.0*TMath::Pi();
                                    hist_tpc_ind_full_psi_flattened->Fill(reaction_plane3_ex_full[iTrack2]);
                                }
                            }
                        }
                    }
#endif
                    // Compute bbc event planes
                    Int_t N_bbc_east = 0, N_bbc_west = 0;
                    Double_t bbc_east_Qx = 0.0, bbc_east_Qy = 0.0, bbc_east_Qweight = 0.0;
                    Double_t bbc_west_Qx = 0.0, bbc_west_Qy = 0.0, bbc_west_Qweight = 0.0;
                    Double_t bbc_full_Qx = 0.0, bbc_full_Qy = 0.0;
                    Double_t bbc_east_plane1 = -999.0, bbc_east_plane2 = -999.0, bbc_east_plane3 = -999.0;
                    Double_t bbc_west_plane1 = -999.0, bbc_west_plane2 = -999.0, bbc_west_plane3 = -999.0;
                    Double_t bbc_full_plane1 = -999.0, bbc_full_plane2 = -999.0, bbc_full_plane3 = -999.0;
                    // Get BBC psi
                    Double_t nHitE[16], nHitW[16];
                    for(Int_t i=0;i<16;i++) {
                        nHitE[i] = 0.0;
                        nHitW[i] = 0.0;
                    }
                    Double_t etotal = 0.0, wtotal = 0.0;
                    for(Int_t i=0;i<16;i++) {
                        Double_t eadc = muEvent->bbcTriggerDetector().adc(i); // BBC east
                        BBC_ADC_EAST[i]->Fill(eadc);
                        Double_t wadc = muEvent->bbcTriggerDetector().adc(i+24); // BBC west
                        BBC_ADC_WEST[i]->Fill(wadc);
                        if(eadc > 30 && eadc < 4000) {
                            nHitE[i] = (egain[i] > 0.0)? eadc * egain[i] : eadc;
                            etotal += nHitE[i];
                            
                            emean[i] += eadc;
                            esum[i]++;
                            
                            emean_c[i] += nHitE[i];
                            esum_c[i]++;
                        }
                        if(wadc > 30) {
                            nHitW[i] = (wgain[i] > 0.0)? wadc * wgain[i] : wadc;
                            wtotal += nHitW[i];
                            
                            wmean[i] += wadc;
                            wsum[i]++;
                            
                            wmean_c[i] += nHitW[i];
                            wsum_c[i]++;
                        }
                    }
                    for(Int_t i=0;i<16;i++) {
                        nHitE[i] *= (etotal > 0.0)? 1.0 / etotal : 0.0;
                        nHitW[i] *= (wtotal > 0.0)? 1.0 / wtotal : 0.0;
                    }
                    for(Int_t iTile=0;iTile<16;iTile++) {
                        // BBC east
                        if(nHitE[iTile] > 0.0) {
                            N_bbc_east++;
                            bbc_east_Qx += TMath::Cos( BBC_GetPhi(0,iTile,primaryVertex_X,primaryVertex_Y) ) * nHitE[iTile];
                            bbc_east_Qy += TMath::Sin( BBC_GetPhi(0,iTile,primaryVertex_X,primaryVertex_Y) ) * nHitE[iTile];
                            bbc_east_Qweight += nHitE[iTile];
                        }
                        // BBC west
                        if(nHitW[iTile] > 0.0) {
                            N_bbc_west++;
                            bbc_west_Qx += TMath::Cos( BBC_GetPhi(1,iTile,primaryVertex_X,primaryVertex_Y) ) * nHitW[iTile];
                            bbc_west_Qy += TMath::Sin( BBC_GetPhi(1,iTile,primaryVertex_X,primaryVertex_Y) ) * nHitW[iTile];
                            bbc_west_Qweight += nHitW[iTile];
                        }
                    }
                    // BBC east
                    if(N_bbc_east >= 5 && bbc_east_Qweight > 0.0) {
                        bbc_east_Qx /= bbc_east_Qweight;
                        bbc_east_Qy /= bbc_east_Qweight;
                        if(bbc_east_Qx || bbc_east_Qy) {
                            bbc_east_plane1 = TMath::ATan2(bbc_east_Qy,bbc_east_Qx);
                            if(bbc_east_plane1 < 0.0            ) bbc_east_plane1 += 2.0*TMath::Pi();
                            if(bbc_east_plane1 > 2.0*TMath::Pi()) bbc_east_plane1 -= 2.0*TMath::Pi();
                            hist_bbc_east_psi_raw->Fill(bbc_east_plane1);
                            // Recenter reaction plane vector
                            profile3D_bbc_east_Qx_Qy->Fill(Day,centrality,1,bbc_east_Qx);
                            profile3D_bbc_east_Qx_Qy->Fill(Day,centrality,2,bbc_east_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_bbc_east_Qx_Qy_input && profile3D_bbc_east_Qx_Qy_input->GetEntries() > 0) {
                                bbc_east_Qx -= profile3D_bbc_east_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                bbc_east_Qy -= profile3D_bbc_east_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(bbc_east_Qx || bbc_east_Qy) {
                                bbc_east_plane2 = TMath::ATan2(bbc_east_Qy,bbc_east_Qx);
                                if(bbc_east_plane2 < 0.0            ) bbc_east_plane2 += 2.0*TMath::Pi();
                                if(bbc_east_plane2 > 2.0*TMath::Pi()) bbc_east_plane2 -= 2.0*TMath::Pi();
                                hist_bbc_east_psi_recentered->Fill(bbc_east_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = bbc_east_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_bbc_east_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_bbc_east_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_bbc_east_psiShift_input && profile3D_bbc_east_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_bbc_east_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_bbc_east_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( bbc_east_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( bbc_east_plane2*(k+1) ) ) / (k+1);
                                }
                                bbc_east_plane3 = reaction_plane_new;
                                if(bbc_east_plane3 < 0.0            ) bbc_east_plane3 += 2.0*TMath::Pi();
                                if(bbc_east_plane3 > 2.0*TMath::Pi()) bbc_east_plane3 -= 2.0*TMath::Pi();
                                hist_bbc_east_psi_flattened->Fill(bbc_east_plane3);
                            }
                        }
                    }
                    // BBC west
                    if(N_bbc_west >= 2 && bbc_west_Qweight > 0.0) {
                        bbc_west_Qx /= bbc_west_Qweight;
                        bbc_west_Qy /= bbc_west_Qweight;
                        if(bbc_west_Qx || bbc_west_Qy) {
                            bbc_west_plane1 = TMath::ATan2(bbc_west_Qy,bbc_west_Qx);
                            if(bbc_west_plane1 < 0.0            ) bbc_west_plane1 += 2.0*TMath::Pi();
                            if(bbc_west_plane1 > 2.0*TMath::Pi()) bbc_west_plane1 -= 2.0*TMath::Pi();
                            hist_bbc_west_psi_raw->Fill(bbc_west_plane1);
                            // Recenter reaction plane vector
                            profile3D_bbc_west_Qx_Qy->Fill(Day,centrality,1,bbc_west_Qx);
                            profile3D_bbc_west_Qx_Qy->Fill(Day,centrality,2,bbc_west_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_bbc_west_Qx_Qy_input && profile3D_bbc_west_Qx_Qy_input->GetEntries() > 0) {
                                bbc_west_Qx -= profile3D_bbc_west_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                bbc_west_Qy -= profile3D_bbc_west_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(bbc_west_Qx || bbc_west_Qy) {
                                bbc_west_plane2 = TMath::ATan2(bbc_west_Qy,bbc_west_Qx);
                                if(bbc_west_plane2 < 0.0            ) bbc_west_plane2 += 2.0*TMath::Pi();
                                if(bbc_west_plane2 > 2.0*TMath::Pi()) bbc_west_plane2 -= 2.0*TMath::Pi();
                                hist_bbc_west_psi_recentered->Fill(bbc_west_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = bbc_west_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_bbc_west_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_bbc_west_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_bbc_west_psiShift_input && profile3D_bbc_west_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_bbc_west_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_bbc_west_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( bbc_west_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( bbc_west_plane2*(k+1) ) ) / (k+1);
                                }
                                bbc_west_plane3 = reaction_plane_new;
                                if(bbc_west_plane3 < 0.0            ) bbc_west_plane3 += 2.0*TMath::Pi();
                                if(bbc_west_plane3 > 2.0*TMath::Pi()) bbc_west_plane3 -= 2.0*TMath::Pi();
                                hist_bbc_west_psi_flattened->Fill(bbc_west_plane3);
                            }
                        }
                    }
                    // BBC full
                    if( (N_bbc_east + N_bbc_west) >= 5 && bbc_east_Qweight > 0.0 && bbc_west_Qweight > 0.0 ) {
                        bbc_full_Qx = bbc_east_Qx/bbc_east_Qweight + bbc_west_Qx/bbc_west_Qweight;
                        bbc_full_Qy = bbc_east_Qy/bbc_east_Qweight + bbc_west_Qy/bbc_west_Qweight;
                        if(bbc_full_Qx || bbc_full_Qy) {
                            bbc_full_plane1 = TMath::ATan2(bbc_full_Qy,bbc_full_Qx);
                            if(bbc_full_plane1 < 0.0            ) bbc_full_plane1 += 2.0*TMath::Pi();
                            if(bbc_full_plane1 > 2.0*TMath::Pi()) bbc_full_plane1 -= 2.0*TMath::Pi();
                            hist_bbc_full_psi_raw->Fill(bbc_full_plane1);
                            // Recenter reaction plane vector
                            profile3D_bbc_full_Qx_Qy->Fill(Day,centrality,1,bbc_full_Qx);
                            profile3D_bbc_full_Qx_Qy->Fill(Day,centrality,2,bbc_full_Qy);
                            if(eventPlanes_input->IsOpen() && profile3D_bbc_full_Qx_Qy_input && profile3D_bbc_full_Qx_Qy_input->GetEntries() > 0) {
                                bbc_full_Qx -= profile3D_bbc_full_Qx_Qy_input->GetBinContent(Day,centrality,1);
                                bbc_full_Qy -= profile3D_bbc_full_Qx_Qy_input->GetBinContent(Day,centrality,2);
                            }
                            if(bbc_full_Qx || bbc_full_Qy) {
                                bbc_full_plane2 = TMath::ATan2(bbc_full_Qy,bbc_full_Qx);
                                if(bbc_full_plane2 < 0.0            ) bbc_full_plane2 += 2.0*TMath::Pi();
                                if(bbc_full_plane2 > 2.0*TMath::Pi()) bbc_full_plane2 -= 2.0*TMath::Pi();
                                hist_bbc_full_psi_recentered->Fill(bbc_full_plane2);
                                // Shift recenterd event plane to flat
                                Double_t reaction_plane_new = bbc_full_plane2;
                                for(Int_t k=0;k<order;k++) {
                                    profile3D_bbc_full_psiShift->Fill(Day,centrality,1+2*k,TMath::Cos(reaction_plane_new*(k+1)));
                                    profile3D_bbc_full_psiShift->Fill(Day,centrality,2+2*k,TMath::Sin(reaction_plane_new*(k+1)));
                                }
                                Double_t psi_mean[twoorder];
                                for(Int_t i=0;i<twoorder;i++) {
                                    psi_mean[i] = 0.0;
                                }
                                if(eventPlanes_input->IsOpen() && profile3D_bbc_full_psiShift_input && profile3D_bbc_full_psiShift_input->GetEntries() > 0) {
                                    for(Int_t k=0;k<order;k++) {
                                        psi_mean[0+2*k] = profile3D_bbc_full_psiShift_input->GetBinContent(Day,centrality,1+2*k);
                                        psi_mean[1+2*k] = profile3D_bbc_full_psiShift_input->GetBinContent(Day,centrality,2+2*k);
                                    }
                                }
                                for(Int_t k=0;k<order;k++) {
                                    reaction_plane_new += ( -2.0*psi_mean[1+2*k] * TMath::Cos( bbc_full_plane2*(k+1) )
                                                           + 2.0*psi_mean[0+2*k] * TMath::Sin( bbc_full_plane2*(k+1) ) ) / (k+1);
                                }
                                bbc_full_plane3 = reaction_plane_new;
                                if(bbc_full_plane3 < 0.0            ) bbc_full_plane3 += 2.0*TMath::Pi();
                                if(bbc_full_plane3 > 2.0*TMath::Pi()) bbc_full_plane3 -= 2.0*TMath::Pi();
                                hist_bbc_full_psi_flattened->Fill(bbc_full_plane3);
                            }
                        }
                    }
                    // Accumulate Event Plane correlations
                    Double_t centTMP = Ncentralities-centrality+1;
                    if( tpc_east_plane3 >= 0.0 && tpc_east_plane3 <= 2.0*TMath::Pi() ) {
                        if( tpc_west_plane3 >= 0.0 && tpc_west_plane3 <= 2.0*TMath::Pi() ) {
                            profile_correlation_tpc_east_tpc_west->Fill(centTMP,TMath::Cos(tpc_east_plane3 - tpc_west_plane3));
                            correlation2D_tpc_sub->Fill(tpc_west_plane3,tpc_east_plane3);
                        }
                        
                        if( thirdEP_plane3 >= 0.0 && thirdEP_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_tpc_east_thirdEP->Fill(centTMP,TMath::Cos(tpc_east_plane3 - thirdEP_plane3));
                        
                        if( bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() ) {
                            profile_correlation_tpc_east_bbc_east->Fill(centTMP,TMath::Cos(tpc_east_plane3 - bbc_east_plane3 - TMath::Pi()));
                            correlation2D_bbc_east_tpc_east->Fill(tpc_east_plane3,bbc_east_plane3);
                        }
                        
                        if( bbc_west_plane3 >= 0.0 && bbc_west_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_tpc_east_bbc_west->Fill(centTMP,TMath::Cos(tpc_east_plane3 - bbc_west_plane3));
                    }
                    
                    if( tpc_west_plane3 >= 0.0 && tpc_west_plane3 <= 2.0*TMath::Pi() ) {
                        if( thirdEP_plane3 >= 0.0 && thirdEP_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_tpc_west_thirdEP->Fill(centTMP,TMath::Cos(tpc_west_plane3 - thirdEP_plane3));
                        
                        if( bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() ) {
                            profile_correlation_tpc_west_bbc_east->Fill(centTMP,TMath::Cos(tpc_west_plane3 - bbc_east_plane3 - TMath::Pi()));
                            correlation2D_bbc_east_tpc_west->Fill(tpc_west_plane3,bbc_east_plane3);
                        }
                        
                        if( bbc_west_plane3 >= 0.0 && bbc_west_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_tpc_west_bbc_west->Fill(centTMP,TMath::Cos(tpc_west_plane3 - bbc_west_plane3));
                    }
                    
                    if( thirdEP_plane3 >= 0.0 && thirdEP_plane3 <= 2.0*TMath::Pi() ) {
                        if( bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_thirdEP_bbc_east->Fill(centTMP,TMath::Cos(thirdEP_plane3 - bbc_east_plane3 - TMath::Pi()));
                        
                        if( bbc_west_plane3 >= 0.0 && bbc_west_plane3 <= 2.0*TMath::Pi() )
                            profile_correlation_thirdEP_bbc_west->Fill(centTMP,TMath::Cos(thirdEP_plane3 - bbc_west_plane3));
                    }
                    
                    if( bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() ) {
                        if( bbc_west_plane3 >= 0.0 && bbc_west_plane3 <= 2.0*TMath::Pi() ) {
                            profile_correlation_bbc_east_bbc_west->Fill(centTMP,TMath::Cos(bbc_east_plane3 - bbc_west_plane3 - TMath::Pi()));
                            correlation2D_bbc_sub->Fill(bbc_west_plane3,bbc_east_plane3);
                        }
                    }
                    // Define PID parameters
                    Int_t Nprotons = 0, NpionPlus = 0, NpionMinus = 0, NkaonPlus = 0, NkaonMinus = 0;
                    // 3rd Primary Tracks loop to get flow
                    for(Int_t itr=0;itr<trackMult;itr++) {
                        // Get Track pointer
                        StMuTrack *track = mMuDstMaker->muDst()->primaryTracks(itr);
                        // Check if Track pointer isn't Null
                        if(track) {
                            // Apply Track Cuts
                            if( // Cut on nHitsDedx
                               track->nHitsDedx() > 0
                               // Sytemactic checks
                               //track->nHitsDedx() > 10
                               //track->nHitsDedx() > 15
                               //track->nHitsDedx() > 20
                               // Avoid track splitting
                               && (Double_t)track->nHitsFit()/track->nHitsPoss() >= 0.52
                               // Apply other track cuts
                               //&& TMath::Abs( track->eta() ) < 1.0
                               //&& track->pt() > 0.2 && track->pt() < 5.0
                               // Sytemactic checks
                               //&& track->dcaGlobal().mag() < 1.0
                               //&& track->dcaGlobal().mag() < 2.0
                               //&& track->dcaGlobal().mag() < 3.0
                               ) {
                                // Get track-wise parameter histograms
                                Double_t pt = track->pt();
                                Double_t pz = track->p().z();
                                Double_t eta = track->eta();
                                Double_t phi = track->phi();
                                if(phi < 0.0            ) phi += 2.0*TMath::Pi();
                                if(phi > 2.0*TMath::Pi()) phi -= 2.0*TMath::Pi();
                                // Get PID parameters
                                Int_t charge = track->charge();
                                Double_t Beta = track->btofPidTraits().beta();
                                Double_t trackP = track->p().mag();
                                Double_t mass2 = 0.0;
                                hist_dEdx->Fill(charge*trackP,track->dEdx()*1.0e6);
                                // Check if TOF info available
                                if(Beta != -999.0) {
                                    mass2 = trackP*trackP * ( ( 1.0 / ( Beta*Beta ) ) - 1.0 );
                                    hist_beta->Fill(charge*trackP,1.0/Beta);
                                    hist_mass->Fill(charge*trackP,mass2);
                                }
                                // 2nd particle identifications
                                // Protons
                                if( TMath::Abs( track->nSigmaProton() ) < 2.0
                                   && ( (Beta == -999.0 /*&& TMath::Abs( track->nSigmaPion() ) > 0.3*/ ) ||
                                       ( Beta != -999.0
                                        && mass2 > 0.4
                                        && mass2 < 1.4
                                        // Systematic check cuts
                                        //&& mass2 > 0.4 + 0.008*cutTest1
                                        //&& mass2 < 1.4 - 0.028*cutTest1
                                        )
                                       )
                                   && track->charge() > 0
                                   && pt > 0.4
                                   && pt < 2.0
                                   // Insert systematic check cuts
                                   //&& TMath::Abs( track->nSigmaProton() ) < 1.6 + 0.08*cutTest1
                                   //&& pt > 0.32 + 0.016*cutTest1
                                   //&& pt < 1.6 + 0.08*cutTest1
                                   ) {
                                    // Count proton tracks number
                                    Nprotons++;
                                    // Get particle track rapidity
                                    Double_t energy_Proton = TMath::Sqrt(trackP*trackP + Mass_Proton*Mass_Proton);
                                    Double_t rap_Proton = 0.5*TMath::Log( (energy_Proton + pz) / (energy_Proton - pz) );
                                    // Get eff corr
                                    Double_t efficiency = 0.0;
                                    if(ProtonEffTableFile->IsOpen() && ProtonEfficiencyTable->GetEntries()) {
                                        Int_t centralitybin = centrality;
                                        //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                        Int_t rapiditybin = ProtonEfficiencyTable->GetYaxis()->FindBin(rap_Proton);
                                        Double_t transversemass = TMath::Sqrt( Mass_Proton*Mass_Proton + track->pt()*track->pt() ) - Mass_Proton;
                                        //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                        Int_t transversemassbin = ProtonEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 20
                                           && transversemassbin >= 1 && transversemassbin <= 150
                                           ) {
                                            Int_t tablebin = ProtonEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                            efficiency = ProtonEfficiencyTable->GetBinContent(tablebin);
                                            efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                        }
                                    }
                                    // Get TPC eff corr
                                    Double_t TPC_PID_efficiency = 0.0;
                                    if(TPC_PID_efficiency_file->IsOpen() && Proton_TPC_efficiency_table->GetEntries()) {
                                        Int_t rapiditybin = Proton_TPC_efficiency_table->GetXaxis()->FindBin(rap_Proton);
                                        Double_t transversemass = TMath::Sqrt( Mass_Proton*Mass_Proton + track->pt()*track->pt() ) - Mass_Proton;
                                        Int_t transversemassbin = Proton_TPC_efficiency_table->GetYaxis()->FindBin(transversemass);
                                        if( rapiditybin >= 1 && rapiditybin <= 15
                                           && transversemassbin >= 1 && transversemassbin <= 38
                                           ) {
                                            Int_t tablebin = Proton_TPC_efficiency_table->GetBin(rapiditybin,transversemassbin);
                                            TPC_PID_efficiency = Proton_TPC_efficiency_table->GetBinContent(tablebin);
                                            TPC_PID_efficiency = (TPC_PID_efficiency >= 0.01 && TPC_PID_efficiency <= 1.0)? 1.0 / TPC_PID_efficiency : 0.0;
                                            //cout<<centrality<<"   "<<rapiditybin<<"   "<<transversemass<<"   "<<TPC_PID_efficiency<<endl;
                                        }
                                    }
                                    if(Beta != -999.0) TPC_PID_efficiency = 1.0;
                                    //efficiency *= TPC_PID_efficiency;
                                    // Get phi weight
                                    Double_t phi_weight = 0.0;
                                    if(phi_input->IsOpen() && Hist_Phi->GetEntries()) {
                                        Int_t phi_bin = Hist_Phi->FindBin(phi);
                                        phi_weight = Hist_Phi->GetBinContent(phi_bin);
                                    }
                                    efficiency *= phi_weight;
                                    // Fill histograms
                                    hist_pt_proton->Fill(pt);
                                    hist_eta_proton->Fill(eta);
                                    hist_y_proton->Fill(rap_Proton);
                                    hist_rap_eta_proton->Fill(eta,rap_Proton);
                                    hist_pt_y_proton->Fill(rap_Proton,pt,efficiency);
                                    hist_pt_eta_proton->Fill(eta,pt,efficiency);
                                    hist_phi_proton->Fill(phi);
                                    hist_dEdx_proton->Fill(charge*trackP,track->dEdx()*1.0e6);
                                    if(Beta != -999.0) {
                                        hist_beta_proton->Fill(charge*trackP,1.0/Beta);
                                        hist_mass_proton->Fill(charge*trackP,mass2);
                                    }
                                    // Accumulate flows
                                    if( /*chooseBBCeastEP &&*/ bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                        profile3D_proton_v1->Fill(centrality,pt,rap_Proton/*track->eta()*/,TMath::Cos(phi - bbc_east_plane3 - TMath::Pi()),efficiency/*1.0*/);
                                    }
                                    if( /*chooseTPCEP &&*/ reaction_plane3_ex_west[itr] >= 0.0 && reaction_plane3_ex_west[itr] <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                        profile3D_proton_v1_tpc->Fill(centrality,pt,rap_Proton/*track->eta()*/,TMath::Cos(1.0*phi - reaction_plane3_ex_west[itr]),efficiency/*1.0*/);
                                    }
                                }
                                
                                // Pions
                                /*if( TMath::Abs( track->nSigmaPion() ) < 2.0
                                   && ( ( Beta != -999.0
                                         && mass2 > -0.15
                                         && mass2 < 0.14
                                         )
                                       //&& ( ( trackP < 0.62 && TMath::Abs(mass2) > 0.005 ) || trackP > 0.62 )
                                       )
                                   && track->pt() > 0.2
                                   && track->pt() < 1.6
                                   //&& track->p().mag() < 1.6
                                   )*/
                                // POI selection (Pion), Lukasz's cuts
                                if( TMath::Abs(track->nSigmaPion()) < 1.0
                                   && TMath::Abs(track->btofPidTraits().sigmaPion()) < 1.0
                                   && TMath::Abs(track->btofPidTraits().sigmaKaon()) > 1.0
                                   && TMath::Abs(track->btofPidTraits().sigmaProton()) > 1.0
                                   && TMath::Abs(track->nSigmaElectron()) > 1.0
                                   && track->pt() > 0.2
                                   && track->pt() < 1.6
                                   // Systematic checks
                                   //&& track->p().mag() < 1.6
                                   //&& TMath::Abs(track->nSigmaPion()) < 0.8 + 0.04*cutTest1
                                   //&& TMath::Abs(track->btofPidTraits().sigmaPion()) < 0.8 + 0.04*cutTest1
                                   //&& TMath::Abs(track->btofPidTraits().sigmaKaon()) > 1.0 - 0.02*cutTest1
                                   //&& TMath::Abs(track->btofPidTraits().sigmaProton()) > 1.0 - 0.02*cutTest1
                                   //&& TMath::Abs(track->nSigmaElectron()) > 1.0 - 0.02*cutTest1
                                   //&& pt > 0.16 + 0.008*cutTest1
                                   //&& pt < 1.28 + 0.064*cutTest1
                                   //&& track->p().mag() < 1.4 + 0.02*cutTest1
                                   ) {
                                    // Get particle track rapidity
                                    Double_t energy_Pion = TMath::Sqrt(trackP*trackP + Mass_Pion*Mass_Pion);
                                    Double_t rap_Pion = 0.5*TMath::Log( (energy_Pion + pz) / (energy_Pion - pz) );
                                    // pionPlus
                                    if(charge > 0) {
                                        // Get eff corr
                                        Double_t efficiency = 0.0;
                                        if(PiPlusEffTableFile->IsOpen() && PionPlusEfficiencyTable->GetEntries()) {
                                            Int_t centralitybin = centrality;
                                            //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                            Int_t rapiditybin = PionPlusEfficiencyTable->GetYaxis()->FindBin(rap_Pion);
                                            Double_t transversemass = TMath::Sqrt( Mass_Pion*Mass_Pion + track->pt()*track->pt() ) - Mass_Pion;
                                            //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                            Int_t transversemassbin = PionPlusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                            if( rapiditybin >= 1 && rapiditybin <= 20
                                               && transversemassbin >= 1 && transversemassbin <= 150
                                               ) {
                                                Int_t tablebin = PionPlusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                                efficiency = PionPlusEfficiencyTable->GetBinContent(tablebin);
                                                efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                                //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                            }
                                        }
                                        // Count pionPlus tracks number
                                        NpionPlus++;
                                        // Fill histograms
                                        hist_pt_pionPlus->Fill(pt);
                                        hist_eta_pionPlus->Fill(eta);
                                        hist_y_pionPlus->Fill(rap_Pion);
                                        hist_rap_eta_pionPlus->Fill(eta,rap_Pion);
                                        hist_pt_y_pionPlus->Fill(rap_Pion,pt,efficiency);
                                        hist_pt_eta_pionPlus->Fill(eta,pt,efficiency);
                                        hist_phi_pionPlus->Fill(phi);
                                        hist_dEdx_pionPlus->Fill(charge*trackP,track->dEdx()*1.0e6);
                                        if(Beta != -999.0) {
                                            hist_beta_pionPlus->Fill(charge*trackP,1.0/Beta);
                                            hist_mass_pionPlus->Fill(charge*trackP,mass2);
                                        }
                                        // Accumulate flows
                                        if( /*chooseBBCeastEP &&*/ bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_pionPlus_v1->Fill(centrality,pt,rap_Pion/*track->eta()*/,TMath::Cos(phi - bbc_east_plane3 - TMath::Pi()),efficiency/*1.0*/);
                                        }
                                        
                                        if( /*chooseTPCEP &&*/ reaction_plane3_ex_west[itr] >= 0.0 && reaction_plane3_ex_west[itr] <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_pionPlus_v1_tpc->Fill(centrality,pt,rap_Pion/*track->eta()*/,TMath::Cos(1.0*phi - reaction_plane3_ex_west[itr]),efficiency/*1.0*/);
                                        }
                                    }
                                    // pionMinus
                                    if(charge < 0) {
                                        // Get eff corr
                                        Double_t efficiency = 0.0;
                                        if(PiMinusEffTableFile->IsOpen() && PionMinusEfficiencyTable->GetEntries()) {
                                            Int_t centralitybin = centrality;
                                            //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                            Int_t rapiditybin = PionMinusEfficiencyTable->GetYaxis()->FindBin(rap_Pion);
                                            Double_t transversemass = TMath::Sqrt( Mass_Pion*Mass_Pion + track->pt()*track->pt() ) - Mass_Pion;
                                            //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                            Int_t transversemassbin = PionMinusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                            if( rapiditybin >= 1 && rapiditybin <= 20
                                               && transversemassbin >= 1 && transversemassbin <= 150
                                               ) {
                                                Int_t tablebin = PionMinusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                                efficiency = PionMinusEfficiencyTable->GetBinContent(tablebin);
                                                efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                                //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                            }
                                        }
                                        // Count pionMinus tracks number
                                        NpionMinus++;
                                        // Fill histograms
                                        hist_pt_pionMinus->Fill(pt);
                                        hist_eta_pionMinus->Fill(eta);
                                        hist_y_pionMinus->Fill(rap_Pion);
                                        hist_rap_eta_pionMinus->Fill(eta,rap_Pion);
                                        hist_pt_y_pionMinus->Fill(rap_Pion,pt,efficiency);
                                        hist_pt_eta_pionMinus->Fill(eta,pt,efficiency);
                                        hist_phi_pionMinus->Fill(phi);
                                        hist_dEdx_pionMinus->Fill(charge*trackP,track->dEdx()*1.0e6);
                                        if(Beta != -999.0) {
                                            hist_beta_pionMinus->Fill(charge*trackP,1.0/Beta);
                                            hist_mass_pionMinus->Fill(charge*trackP,mass2);
                                        }
                                        // Accumulate flows
                                        if( /*chooseBBCeastEP &&*/ bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_pionMinus_v1->Fill(centrality,pt,rap_Pion/*track->eta()*/,TMath::Cos(phi - bbc_east_plane3 - TMath::Pi()),efficiency/*1.0*/);
                                        }
                                        if( /*chooseTPCEP &&*/ reaction_plane3_ex_west[itr] >= 0.0 && reaction_plane3_ex_west[itr] <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_pionMinus_v1_tpc->Fill(centrality,pt,rap_Pion/*track->eta()*/,TMath::Cos(1.0*phi - reaction_plane3_ex_west[itr]),efficiency/*1.0*/);
                                        }
                                    }
                                }
                                
                                // Kaons
                                if( TMath::Abs( track->nSigmaKaon() ) < 2.0
                                   && ( Beta != -999.0
                                       && mass2 > 0.14
                                       && mass2 < 0.4
                                       // Systematic check cuts
                                       //&& mass2 > 0.14 + 0.0028*cutTest1
                                       //&& mass2 < 0.4 - 0.008*cutTest1
                                       )
                                   && track->pt() > 0.2
                                   && track->pt() < 1.6
                                   //&& track->p().mag() < 1.6
                                   // Insert systematic check cuts
                                   //&& TMath::Abs( track->nSigmaKaon() ) < 1.6 + 0.08*cutTest1
                                   //&& pt > 0.16 + 0.008*cutTest1
                                   //&& pt < 1.28 + 0.064*cutTest1
                                   ) {
                                    // Get particle track rapidity
                                    Double_t energy_Kaon = TMath::Sqrt(trackP*trackP + Mass_Kaon*Mass_Kaon);
                                    Double_t rap_Kaon = 0.5*TMath::Log( (energy_Kaon + pz) / (energy_Kaon - pz) );
                                    // kaonPlus
                                    if(charge > 0) {
                                        // Get eff corr
                                        Double_t efficiency = 0.0;
                                        if(KPlusEffTableFile->IsOpen() && KaonPlusEfficiencyTable->GetEntries()) {
                                            Int_t centralitybin = centrality;
                                            //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                            Int_t rapiditybin = KaonPlusEfficiencyTable->GetYaxis()->FindBin(rap_Kaon);
                                            Double_t transversemass = TMath::Sqrt( Mass_Kaon*Mass_Kaon + track->pt()*track->pt() ) - Mass_Kaon;
                                            //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                            Int_t transversemassbin = KaonPlusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                            if( rapiditybin >= 1 && rapiditybin <= 20
                                               && transversemassbin >= 1 && transversemassbin <= 150
                                               ) {
                                                Int_t tablebin = KaonPlusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                                efficiency = KaonPlusEfficiencyTable->GetBinContent(tablebin);
                                                efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                                //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                            }
                                        }
                                        //efficiency = 1.0;
                                        // Count kaonPlus tracks number
                                        NkaonPlus++;
                                        // Fill histograms
                                        hist_pt_kaonPlus->Fill(pt);
                                        hist_eta_kaonPlus->Fill(eta);
                                        hist_y_kaonPlus->Fill(rap_Kaon);
                                        hist_rap_eta_kaonPlus->Fill(eta,rap_Kaon);
                                        hist_pt_y_kaonPlus->Fill(rap_Kaon,pt,efficiency);
                                        hist_pt_eta_kaonPlus->Fill(eta,pt,efficiency);
                                        hist_phi_kaonPlus->Fill(phi);
                                        hist_dEdx_kaonPlus->Fill(charge*trackP,track->dEdx()*1.0e6);
                                        if(Beta != -999.0) {
                                            hist_beta_kaonPlus->Fill(charge*trackP,1.0/Beta);
                                            hist_mass_kaonPlus->Fill(charge*trackP,mass2);
                                        }
                                        // Accumulate flows
                                        if( /*chooseBBCeastEP &&*/ bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_kaonPlus_v1->Fill(centrality,pt,rap_Kaon/*track->eta()*/,TMath::Cos(phi - bbc_east_plane3 - TMath::Pi()),efficiency/*1.0*/);
                                        }
                                        
                                        if( /*chooseTPCEP &&*/ reaction_plane3_ex_west[itr] >= 0.0 && reaction_plane3_ex_west[itr] <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_kaonPlus_v1_tpc->Fill(centrality,pt,rap_Kaon/*track->eta()*/,TMath::Cos(1.0*phi - reaction_plane3_ex_west[itr]),efficiency/*1.0*/);
                                        }
                                    }
                                    // kaonMinus
                                    if(charge < 0) {
                                        // Get eff corr
                                        Double_t efficiency = 0.0;
                                        if(KMinusEffTableFile->IsOpen() && KaonMinusEfficiencyTable->GetEntries()) {
                                            Int_t centralitybin = centrality;
                                            //Int_t rapiditybin = (Int_t)TMath::Floor( ( rap_Proton - -2.05 )*(Double_t)20 / ( -0.05 - -2.05 ) ) + 1;
                                            Int_t rapiditybin = KaonMinusEfficiencyTable->GetYaxis()->FindBin(rap_Kaon);
                                            Double_t transversemass = TMath::Sqrt( Mass_Kaon*Mass_Kaon + track->pt()*track->pt() ) - Mass_Kaon;
                                            //Int_t transversemassbin = (Int_t)std::floor( ( transversemass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
                                            Int_t transversemassbin = KaonMinusEfficiencyTable->GetZaxis()->FindBin(transversemass);
                                            if( rapiditybin >= 1 && rapiditybin <= 20
                                               && transversemassbin >= 1 && transversemassbin <= 150
                                               ) {
                                                Int_t tablebin = KaonMinusEfficiencyTable->GetBin(centralitybin,rapiditybin,transversemassbin);
                                                efficiency = KaonMinusEfficiencyTable->GetBinContent(tablebin);
                                                efficiency = (efficiency >= 0.001 && efficiency <= 1.0)? 1.0 / efficiency : 0.0;
                                                //cout<<centrality<<"   "<<rapiditybin-1<<"   "<<transversemass<<"   "<<efficiency<<endl;
                                            }
                                        }
                                        //efficiency = 1.0;
                                        // count kaonMinus tracks number
                                        NkaonMinus++;
                                        // fill histograms
                                        hist_pt_kaonMinus->Fill(pt);
                                        hist_eta_kaonMinus->Fill(eta);
                                        hist_y_kaonMinus->Fill(rap_Kaon);
                                        hist_rap_eta_kaonMinus->Fill(eta,rap_Kaon);
                                        hist_pt_y_kaonMinus->Fill(rap_Kaon,pt,efficiency);
                                        hist_pt_eta_kaonMinus->Fill(eta,pt,efficiency);
                                        hist_phi_kaonMinus->Fill(phi);
                                        hist_dEdx_kaonMinus->Fill(charge*trackP,track->dEdx()*1.0e6);
                                        if(Beta != -999.0) {
                                            hist_beta_kaonMinus->Fill(charge*trackP,1.0/Beta);
                                            hist_mass_kaonMinus->Fill(charge*trackP,mass2);
                                        }
                                        // Accumulate flows
                                        if( /*chooseBBCeastEP &&*/ bbc_east_plane3 >= 0.0 && bbc_east_plane3 <= 2.0*TMath::Pi() && efficiency > 0.0 ) {
                                            profile3D_kaonMinus_v1->Fill(centrality,pt,rap_Kaon/*track->eta()*/,TMath::Cos(phi - bbc_east_plane3 - TMath::Pi()),efficiency/*1.0*/);
                                        }
                                        
                                        if( /*chooseTPCEP &&*/ reaction_plane3_ex_west[itr] >= 0.0 && reaction_plane3_ex_west[itr] <= 2.0*TMath::Pi() && efficiency > 0.0) {
                                            profile3D_kaonMinus_v1_tpc->Fill(centrality,pt,rap_Kaon/*track->eta()*/,TMath::Cos(1.0*phi - reaction_plane3_ex_west[itr]),efficiency/*1.0*/);
                                        }
                                    }
                                }
                            } // Track Cuts end
                        } // Track pointer check ends
                    } // 3rd Primary Tracks loop ends
                    hist_trackmult_proton->Fill(Nprotons);
                    hist_trackmult_pionPlus->Fill(NpionPlus);
                    hist_trackmult_pionMinus->Fill(NpionMinus);
                    hist_trackmult_kaonPlus->Fill(NkaonPlus);
                    hist_trackmult_kaonMinus->Fill(NkaonMinus);
                } // Event centrality cut ends
#if indTPCepIndicator > 0
                // Clean up
                delete[] Qx1_ex_full; delete[] Qy1_ex_full;
                delete[] Qx1_ex_east; delete[] Qy1_ex_east; delete[] w1_ex_east;
                delete[] Qx1_ex_west; delete[] Qy1_ex_west; delete[] w1_ex_west;
                delete[] reaction_plane1_ex_full; delete[] reaction_plane2_ex_full; delete[] reaction_plane3_ex_full;
                delete[] reaction_plane1_ex_east; delete[] reaction_plane2_ex_east; delete[] reaction_plane3_ex_east;
                delete[] reaction_plane1_ex_west; delete[] reaction_plane2_ex_west; delete[] reaction_plane3_ex_west;
#endif
            } // Event selection ends
        } // Check Event pointer ends
    } // Vertices loop ends
    return kStOK;
}

// BBC azimuthal distribution
Double_t FxtMaker::BBC_GetPhi(Int_t e_w,Int_t iTile,Double_t Vx,Double_t Vy) {
    // Get phi of BBC tile
    Double_t Tx = 0.0, Ty = 0.0;
    TRandom *r = new TRandom();
    switch(iTile) {
      case 0: {Ty = 9.64;Tx = 0.0;}
        break;
      case 1: {Ty = 9.64/2.0;Tx = 9.64;}
        break;
      case 2: {Ty = -9.64/2.0;Tx = 9.64;}
        break;
      case 3: {Ty = -9.64;Tx = 0.0;}
        break;
      case 4: {Ty = -9.64/2.0;Tx = -9.64;}
        break;
      case 5: {Ty = 9.64/2.0;Tx = -9.64;}
        break;
      case 6: {Ty = 9.64*3.0/2.0;Tx = (r->Rndm() > 0.5)? 9.64:-9.64;}
        break;
      case 7: {Ty = 9.64*2.0;Tx = 0.0;}
        break;
      case 8: {Ty = 9.64;Tx = 9.64*2.0;}
        break;
      case 9: {Ty = 0.0;Tx = 9.64*2.0;}
        break;
      case 10: {Ty = -9.64;Tx = 9.64*2.0;}
        break;
      case 11: {Ty = -9.64*3.0/2.0;Tx = (r->Rndm() > 0.5)? 9.64:-9.64;}
        break;
      case 12: {Ty = -9.64*2.0;Tx = 0.0;}
        break;
      case 13: {Ty = -9.64;Tx = -9.64*2.0;}
        break;
      case 14: {Ty = 0.0;Tx = -9.64*2.0;}
        break;
      case 15: {Ty = 9.64;Tx = -9.64*2.0;}
        break;
    }
    delete r;
    Double_t bbc_phi = TMath::ATan2(Ty-Vy,Tx-Vx);
    //if(e_w == 1) bbc_phi = bbc_phi - TMath::Pi();
    if(e_w == 0) {
        if (bbc_phi > -0.001) bbc_phi = TMath::Pi() - bbc_phi;
        //if (bbc_phi > 0) bbc_phi = TMath::Pi() - bbc_phi;
        else                  bbc_phi= -TMath::Pi() - bbc_phi;
    }
    if(bbc_phi < 0.0            ) bbc_phi += 2.0*TMath::Pi();
    if(bbc_phi > 2.0*TMath::Pi()) bbc_phi -= 2.0*TMath::Pi();
    return bbc_phi;
}

Double_t FxtMaker::resEventPlane(Double_t chi) {
    // Calculates the event plane resolution as a function of chi
    
    Double_t con = 0.626657;  // sqrt(pi/2)/2
    Double_t arg = chi * chi / 4.0;
    
    Double_t res = con * chi * exp(-arg) * (TMath::BesselI0(arg) + TMath::BesselI1(arg));
    
    return res;
}

Double_t FxtMaker::chi(Double_t res) {
    // Calculates chi from the event plane resolution
    
    Double_t chi   = 2.0;
    Double_t delta = 1.0;
    
    for (Int_t i = 0; i < 15; i++) {
        //    chi   = (resEventPlane(chi) < res) ? chi + delta : chi - delta;
        //    delta = delta / 2.;
        while(resEventPlane(chi) < res) {chi += delta;}
        delta = delta / 2.0;
        while(resEventPlane(chi) > res) {chi -= delta;}
        delta = delta / 2.0;
    }
    
    return chi;
}
