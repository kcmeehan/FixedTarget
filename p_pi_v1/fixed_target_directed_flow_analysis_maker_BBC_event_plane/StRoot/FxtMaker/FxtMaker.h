// Preprocessor to avoid loading hearder file multiple times
#ifndef FxtMaker_def
#define FxtMaker_def

// Include C/C++ header files
#include <iostream>
#include <stdio.h>
// Include ROOT header files
#include "TString.h"
#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TProfile3D.h"
// Include STAR ROOT header files
#include "StMaker.h"
#include "StEvent/StBTofHeader.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"

// Define global constants
const Int_t daynumber     = 6;
const Int_t Ncentralities = 7;
const Int_t order         = 20;
const Int_t twoorder      = 2 * order;

// Turn individual TPC EP on/off
#ifndef indTPCepIndicator
#define indTPCepIndicator 1
#endif

// Class members
class FxtMaker : public StMaker {
  private:
    // Input parameters
    StMuDstMaker *mMuDstMaker;
    Int_t        nEvents;
    Int_t        nEventsProcessed;
    // Systematic analysis
    Double_t     cutTest1;
    Double_t     cutTest2;
    TString      JobIdName;
    // Particle masses
    Double_t Mass_Pion;
    Double_t Mass_Kaon;
    Double_t Mass_Proton;
    // Which EP indicator
    Bool_t chooseBBCeastEP;
    Bool_t chooseTPCEP;
    // Set rapidity/pseudorapidity range
    Int_t    rapidityBins;
    Double_t rapidityLow;
    Double_t rapidityHigh;
    // Set transverse momentum range
    Int_t    ptBins;
    Double_t ptLow;
    Double_t ptHigh;
    // BBC ADC gain factors
    Double_t egain[16];
    Double_t emean[16];
    Double_t esum[16];
    Double_t emean_c[16];
    Double_t esum_c[16];
    Double_t wgain[16];
    Double_t wmean[16];
    Double_t wsum[16];
    Double_t wmean_c[16];
    Double_t wsum_c[16];
    // EP shifting and recentering
    TFile      *eventPlanes_input;
    TProfile3D *profile3D_proton_phiShift_input;
    TProfile3D *profile3D_pionPlus_phiShift_input;
    TProfile3D *profile3D_pionMinus_phiShift_input;
    TProfile3D *profile3D_tpc_east_Qx_Qy_input;
    TProfile3D *profile3D_tpc_east_psiShift_input;
    TProfile3D *profile3D_tpc_west_Qx_Qy_input;
    TProfile3D *profile3D_tpc_west_psiShift_input;
    TProfile3D *profile3D_tpc_full_Qx_Qy_input;
    TProfile3D *profile3D_tpc_full_psiShift_input;
    TProfile3D *profile3D_thirdEP_Qx_Qy_input;
    TProfile3D *profile3D_thirdEP_psiShift_input;
#if indTPCepIndicator > 0
    TProfile3D *profile3D_tpc_ind_east_Qx_Qy_input;
    TProfile3D *profile3D_tpc_ind_east_psiShift_input;
    TProfile3D *profile3D_tpc_ind_west_Qx_Qy_input;
    TProfile3D *profile3D_tpc_ind_west_psiShift_input;
    TProfile3D *profile3D_tpc_ind_full_Qx_Qy_input;
    TProfile3D *profile3D_tpc_ind_full_psiShift_input;
#endif
    TH1D       *bbc_east_adc_profile_input;
    TProfile3D *profile3D_bbc_east_Qx_Qy_input;
    TProfile3D *profile3D_bbc_east_psiShift_input;
    TH1D       *bbc_west_adc_profile_input;
    TProfile3D *profile3D_bbc_west_Qx_Qy_input;
    TProfile3D *profile3D_bbc_west_psiShift_input;
    TProfile3D *profile3D_bbc_full_Qx_Qy_input;
    TProfile3D *profile3D_bbc_full_psiShift_input;
    // Particle track efficiencies
    TFile *PiPlusEffTableFile;
    TH3D  *PionPlusEfficiencyTable;
	TFile *PiMinusEffTableFile;
	TH3D  *PionMinusEfficiencyTable;
    TFile *KMinusEffTableFile;
    TH3D  *KaonMinusEfficiencyTable;
    TFile *KPlusEffTableFile;
    TH3D  *KaonPlusEfficiencyTable;
	TFile *ProtonEffTableFile;
	TH3D  *ProtonEfficiencyTable;
    // TPC eff
    TFile *TPC_PID_efficiency_file;
    TH2D  *Proton_TPC_efficiency_table;
    //TH2D  *Deuteron_TPC_efficiency_table;
    //TH2D  *Pion_TPC_efficiency_table;
    //TH2D  *Electron_TPC_efficiency_table;
    // Phi weight
    TFile *phi_input;
    TH1D  *Hist_Phi;
    // Output filename
    TFile *outputFile;
    // QA plots
    TH1D *hist_runId;
    TH1D *hist_vertMult;
    TH1D *hist_Vz;
    TH1D *hist_vpdVz;
    TH1D *hist_Vr;
    TH2D *hist_VyVx;
    TH1D *hist_refmult;
    TH1D *hist_grefmult;
    TH1D *hist_tofmult;
    TH1D *hist_trackmult;
    TH1D *hist_realTrackMult;
    TH2D *hist_refmult_grefmult;
    TH2D *hist_refmult_tofmult;
    TH2D *hist_refmult_trackmult;
    TH2D *hist_grefmult_tofmult;
    TH2D *hist_grefmult_trackmult;
    TH2D *hist_tofmult_trackmult;
    TH2D *hist_realTrackMult_refmult;
    TH2D *hist_realTrackMult_grefmult;
    TH2D *hist_realTrackMult_tofmult;
    TH2D *hist_realTrackMult_trackmult;
    TH1D *hist_ndEdx;
    TH1D *hist_nHits;
    TH1D *hist_ratio;
    TH1D *hist_DCA;
    TH1D *hist_gDCA;
    TH1D *hist_cent;
    // Track histograms
    TH1D *hist_pt;
    TH1D *hist_eta;
    TH1D *hist_phi;
    TH2D *hist_dEdx;
    TH2D *hist_beta;
    TH2D *hist_mass;
    
    TH1D *hist_pt_proton;
    TH1D *hist_eta_proton;
    TH1D *hist_y_proton;
    TH2D *hist_rap_eta_proton;
    TH2D *hist_pt_y_proton;
    TH2D *hist_pt_eta_proton;
    TH1D *hist_phi_proton;
    TH1D *hist_trackmult_proton;
    TH2D *hist_dEdx_proton;
    TH2D *hist_beta_proton;
    TH2D *hist_mass_proton;
    
    TH1D *hist_pt_pionPlus;
    TH1D *hist_eta_pionPlus;
    TH1D *hist_y_pionPlus;
    TH2D *hist_rap_eta_pionPlus;
    TH2D *hist_pt_y_pionPlus;
    TH2D *hist_pt_eta_pionPlus;
    TH1D *hist_phi_pionPlus;
    TH1D *hist_trackmult_pionPlus;
    TH2D *hist_dEdx_pionPlus;
    TH2D *hist_beta_pionPlus;
    TH2D *hist_mass_pionPlus;
    
    TH1D *hist_pt_pionMinus;
    TH1D *hist_eta_pionMinus;
    TH1D *hist_y_pionMinus;
    TH2D *hist_rap_eta_pionMinus;
    TH2D *hist_pt_y_pionMinus;
    TH2D *hist_pt_eta_pionMinus;
    TH1D *hist_phi_pionMinus;
    TH1D *hist_trackmult_pionMinus;
    TH2D *hist_dEdx_pionMinus;
    TH2D *hist_beta_pionMinus;
    TH2D *hist_mass_pionMinus;
    
    TH1D *hist_pt_kaonPlus;
    TH1D *hist_eta_kaonPlus;
    TH1D *hist_y_kaonPlus;
    TH2D *hist_rap_eta_kaonPlus;
    TH2D *hist_pt_y_kaonPlus;
    TH2D *hist_pt_eta_kaonPlus;
    TH1D *hist_phi_kaonPlus;
    TH1D *hist_trackmult_kaonPlus;
    TH2D *hist_dEdx_kaonPlus;
    TH2D *hist_beta_kaonPlus;
    TH2D *hist_mass_kaonPlus;
    
    TH1D *hist_pt_kaonMinus;
    TH1D *hist_eta_kaonMinus;
    TH1D *hist_y_kaonMinus;
    TH2D *hist_rap_eta_kaonMinus;
    TH2D *hist_pt_y_kaonMinus;
    TH2D *hist_pt_eta_kaonMinus;
    TH1D *hist_phi_kaonMinus;
    TH1D *hist_trackmult_kaonMinus;
    TH2D *hist_dEdx_kaonMinus;
    TH2D *hist_beta_kaonMinus;
    TH2D *hist_mass_kaonMinus;
    // Flow histograms
    TProfile3D *profile3D_proton_v1;
    TProfile3D *profile3D_proton_v1_tpc;
    TH1D       *proton_v1_cent[Ncentralities];
    TH1D       *proton_v1_10_25_averaged;
    TH1D       *proton_v1_10_30_averaged;
    
    TProfile3D *profile3D_pionPlus_v1;
    TProfile3D *profile3D_pionPlus_v1_tpc;
    TH1D       *pionPlus_v1_cent[Ncentralities];
    TH1D       *pionPlus_v1_10_30_averaged;
    
    TProfile3D *profile3D_pionMinus_v1;
    TProfile3D *profile3D_pionMinus_v1_tpc;
    TH1D       *pionMinus_v1_cent[Ncentralities];
    TH1D       *pionMinus_v1_10_30_averaged;
    
    TProfile3D *profile3D_kaonPlus_v1;
    TProfile3D *profile3D_kaonPlus_v1_tpc;
    TH1D       *kaonPlus_v1_cent[Ncentralities];
    TH1D       *kaonPlus_v1_10_30_averaged;
    
    TProfile3D *profile3D_kaonMinus_v1;
    TProfile3D *profile3D_kaonMinus_v1_tpc;
    TH1D       *kaonMinus_v1_cent[Ncentralities];
    TH1D       *kaonMinus_v1_10_30_averaged;
    // EP histograms
    TH1D       *hist_tpc_east_psi_raw;
    TH1D       *hist_tpc_east_psi_recentered;
    TH1D       *hist_tpc_east_psi_flattened;
    TProfile3D *profile3D_tpc_east_Qx_Qy;
    TProfile3D *profile3D_tpc_east_psiShift;
    TH1D       *hist_tpc_west_psi_raw;
    TH1D       *hist_tpc_west_psi_recentered;
    TH1D       *hist_tpc_west_psi_flattened;
    TProfile3D *profile3D_tpc_west_Qx_Qy;
    TProfile3D *profile3D_tpc_west_psiShift;
    TH1D       *hist_tpc_full_psi_raw;
    TH1D       *hist_tpc_full_psi_recentered;
    TH1D       *hist_tpc_full_psi_flattened;
    TProfile3D *profile3D_tpc_full_Qx_Qy;
    TProfile3D *profile3D_tpc_full_psiShift;
    TH1D       *hist_thirdEP_psi_raw;
    TH1D       *hist_thirdEP_psi_recentered;
    TH1D       *hist_thirdEP_psi_flattened;
    TProfile3D *profile3D_thirdEP_Qx_Qy;
    TProfile3D *profile3D_thirdEP_psiShift;
#if indTPCepIndicator > 0
    TH1D       *hist_tpc_ind_east_psi_raw;
    TH1D       *hist_tpc_ind_east_psi_recentered;
    TH1D       *hist_tpc_ind_east_psi_flattened;
    TProfile3D *profile3D_tpc_ind_east_Qx_Qy;
    TProfile3D *profile3D_tpc_ind_east_psiShift;
    TH1D       *hist_tpc_ind_west_psi_raw;
    TH1D       *hist_tpc_ind_west_psi_recentered;
    TH1D       *hist_tpc_ind_west_psi_flattened;
    TProfile3D *profile3D_tpc_ind_west_Qx_Qy;
    TProfile3D *profile3D_tpc_ind_west_psiShift;
    TH1D       *hist_tpc_ind_full_psi_raw;
    TH1D       *hist_tpc_ind_full_psi_recentered;
    TH1D       *hist_tpc_ind_full_psi_flattened;
    TProfile3D *profile3D_tpc_ind_full_Qx_Qy;
    TProfile3D *profile3D_tpc_ind_full_psiShift;
#endif
    TH1D       *bbc_east_adc_profile;
    TH1D       *bbc_east_gain_corrected_adc_profile;
    TH1D       *hist_bbc_east_psi_raw;
    TH1D       *hist_bbc_east_psi_recentered;
    TH1D       *hist_bbc_east_psi_flattened;
    TProfile3D *profile3D_bbc_east_Qx_Qy;
    TProfile3D *profile3D_bbc_east_psiShift;
    TH1D       *bbc_west_adc_profile;
    TH1D       *bbc_west_gain_corrected_adc_profile;
    TH1D       *hist_bbc_west_psi_raw;
    TH1D       *hist_bbc_west_psi_recentered;
    TH1D       *hist_bbc_west_psi_flattened;
    TProfile3D *profile3D_bbc_west_Qx_Qy;
    TProfile3D *profile3D_bbc_west_psiShift;
    TH1D       *hist_bbc_full_psi_raw;
    TH1D       *hist_bbc_full_psi_recentered;
    TH1D       *hist_bbc_full_psi_flattened;
    TProfile3D *profile3D_bbc_full_Qx_Qy;
    TProfile3D *profile3D_bbc_full_psiShift;
    // EP resolutions
    TProfile *profile_correlation_tpc_east_tpc_west;
    TProfile *profile_correlation_tpc_east_thirdEP;
    TProfile *profile_correlation_tpc_east_bbc_east;
    TProfile *profile_correlation_tpc_east_bbc_west;
    TProfile *profile_correlation_tpc_west_thirdEP;
    TProfile *profile_correlation_tpc_west_bbc_east;
    TProfile *profile_correlation_tpc_west_bbc_west;
    TProfile *profile_correlation_thirdEP_bbc_east;
    TProfile *profile_correlation_thirdEP_bbc_west;
    TProfile *profile_correlation_bbc_east_bbc_west;
    TH1D     *correlation_tpc_east_tpc_west;
    TH1D     *correlation_tpc_east_thirdEP;
    TH1D     *correlation_tpc_east_bbc_east;
    TH1D     *correlation_tpc_east_bbc_west;
    TH1D     *correlation_tpc_west_thirdEP;
    TH1D     *correlation_tpc_west_bbc_east;
    TH1D     *correlation_tpc_west_bbc_west;
    TH1D     *correlation_thirdEP_bbc_east;
    TH1D     *correlation_thirdEP_bbc_west;
    TH1D     *correlation_bbc_east_bbc_west;
    TH1D     *resolution_tpc_sub;
    TH1D     *resolution_tpc_full;
    TH1D     *resolution_bbc_sub;
    TH1D     *resolution_bbc_full;
    TH1D     *resolution_tpc_east_threeEP;
    TH1D     *resolution_tpc_west_threeEP;
    TH1D     *resolution_bbc_east_threeEP;
    // BBC ADC channels
    TH1D *BBC_ADC_EAST[16];
    TH1D *BBC_ADC_WEST[16];
    // EP correlations in 2D
    TH2D *correlation2D_tpc_sub;
    TH2D *correlation2D_bbc_sub;
    TH2D *correlation2D_bbc_east_tpc_east;
    TH2D *correlation2D_bbc_east_tpc_west;
  public:
    FxtMaker(StMuDstMaker *Maker, TString JobId, Int_t EventsNumber, Double_t inputParameter1, Double_t inputParameter2);
    virtual ~FxtMaker();
    Int_t    Init();
    Int_t    Make();
    Int_t    Finish();
    Double_t BBC_GetPhi(Int_t e_w,Int_t iTile,Double_t Vx,Double_t Vy);
	Double_t resEventPlane(Double_t chi);
	Double_t chi(Double_t res);
    ClassDef(FxtMaker,1) // Class title
};

#endif // End of preprocessor
