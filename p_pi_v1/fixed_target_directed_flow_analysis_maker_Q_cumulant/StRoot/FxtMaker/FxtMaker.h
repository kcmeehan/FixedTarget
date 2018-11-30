#ifndef FxtMaker_def    // Preprocessor to avoid loading hearder file multiple times
#define FxtMaker_def

#include <iostream>
#include "StMaker.h"
#include "TString.h"
#include "TFile.h"
#include "TMath.h"
#include "TComplex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TArrayD.h"
#include "StParticleTypes.hh"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"

const Int_t Ncentralities =   7;
const Int_t 	  N_track = 240;
const Int_t         Nbins =  20;
const Int_t   Nhistograms =  17 + 3*Ncentralities + 141;

class FxtMaker : public StMaker
  {
  private:
    TH2D*               hist_pt_eta;
    StMuDstMaker*       mMuDstMaker;
    TString               JobIdName;
    Double_t                cutTest;
    Double_t              phi_total;
    Double_t             phi_weight[500];
    TFile*                phi_input;
    TFile*               outputFile;
    TH1D*                  Hist_Phi;
    TH1D*               histogram1D[Nhistograms];
    TH2D*               histogram2D[Nhistograms];
    TArrayD*              flowArray;
    TArrayD*              flowArray2;
    TArrayD*              flowArrayCOV1;
    TArrayD*              flowArrayCOV2;
    TArrayD*              flowArrayCOV3;
    TArrayD*              flowArrayCOV4;
    Double_t              Mass_Pion;
    Double_t              Mass_Kaon;
    Double_t            Mass_Proton;
    Double_t                    Low;
    Double_t                   High;
    Double_t            midrapidity;
    Int_t               multCounter[N_track];
    Double_t                 sumS11[N_track][Ncentralities];
    Double_t                 sumM11[N_track][Ncentralities];
    Double_t                sumM111[N_track][Ncentralities];
    Double_t               sumM1111[N_track][Ncentralities];
    Double_t               sumCorr2[N_track][Ncentralities];
    Double_t               sumCorr4[N_track][Ncentralities];
    Double_t              sumAddon1[N_track][Ncentralities];
    Double_t              sumAddon2[N_track][Ncentralities];
    Double_t              sumAddon5[N_track][Ncentralities];
    Double_t              sumAddon6[N_track][Ncentralities];
    Double_t              sumAddon7[N_track][Ncentralities];
    Double_t              sumAddon8[N_track][Ncentralities];
    Double_t          sumS11Squared[N_track][Ncentralities];
    Double_t          sumM11Squared[N_track][Ncentralities];
    Double_t         sumM111Squared[N_track][Ncentralities];
    Double_t        sumM1111Squared[N_track][Ncentralities];
    Double_t        sumCorr2Squared[N_track][Ncentralities];
    Double_t        sumCorr4Squared[N_track][Ncentralities];
    Double_t       sumAddon1Squared[N_track][Ncentralities];
    Double_t       sumAddon2Squared[N_track][Ncentralities];
    Double_t       sumAddon5Squared[N_track][Ncentralities];
    Double_t       sumAddon6Squared[N_track][Ncentralities];
    Double_t       sumAddon7Squared[N_track][Ncentralities];
    Double_t       sumAddon8Squared[N_track][Ncentralities];
    Double_t                  sumMp[Nbins][N_track][Ncentralities];
    Double_t                 sumM01[Nbins][N_track][Ncentralities];
    Double_t                sumM011[Nbins][N_track][Ncentralities];
    Double_t               sumM0111[Nbins][N_track][Ncentralities];
    Double_t        sumCorr2Reduced[Nbins][N_track][Ncentralities];
    Double_t        sumCorr4Reduced[Nbins][N_track][Ncentralities];
    Double_t              sumAddon3[Nbins][N_track][Ncentralities];
    Double_t              sumAddon4[Nbins][N_track][Ncentralities];
    Double_t              sumAddon9[Nbins][N_track][Ncentralities];
    Double_t             sumAddon10[Nbins][N_track][Ncentralities];
    Double_t             sumAddon11[Nbins][N_track][Ncentralities];
    Double_t             sumAddon12[Nbins][N_track][Ncentralities];
    Double_t             sumAddon13[Nbins][N_track][Ncentralities];
    Double_t             sumAddon14[Nbins][N_track][Ncentralities];
    Double_t             sumAddon15[Nbins][N_track][Ncentralities];
    Double_t           sumMpSquared[Nbins][N_track][Ncentralities];
    Double_t          sumM01Squared[Nbins][N_track][Ncentralities];
    Double_t         sumM011Squared[Nbins][N_track][Ncentralities];
    Double_t        sumM0111Squared[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedSquared[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedSquared[Nbins][N_track][Ncentralities];
    Double_t       sumAddon3Squared[Nbins][N_track][Ncentralities];
    Double_t       sumAddon4Squared[Nbins][N_track][Ncentralities];
    Double_t       sumAddon9Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon10Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon11Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon12Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon13Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon14Squared[Nbins][N_track][Ncentralities];
    Double_t      sumAddon15Squared[Nbins][N_track][Ncentralities];
    // Covariance terms
    Double_t                 sumM11M1111[N_track][Ncentralities];
    Double_t               sumCorr2Corr4[N_track][Ncentralities];
    Double_t                   sumM11M01[Nbins][N_track][Ncentralities];
    Double_t        sumCorr2Corr2Reduced[Nbins][N_track][Ncentralities];
    Double_t                 sumM11M0111[Nbins][N_track][Ncentralities];
    Double_t        sumCorr2Corr4Reduced[Nbins][N_track][Ncentralities];
    Double_t                 sumM1111M01[Nbins][N_track][Ncentralities];
    Double_t        sumCorr4Corr2Reduced[Nbins][N_track][Ncentralities];
    Double_t               sumM1111M0111[Nbins][N_track][Ncentralities];
    Double_t        sumCorr4Corr4Reduced[Nbins][N_track][Ncentralities];
    Double_t                 sumM01M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedCorr4Reduced[Nbins][N_track][Ncentralities];
    Double_t    sumM11S11[N_track][Ncentralities];
    Double_t   sumCorr2C1[N_track][Ncentralities];
    Double_t   sumCorr2C2[N_track][Ncentralities];
    Double_t   sumCorr2C5[N_track][Ncentralities];
    Double_t   sumCorr2C6[N_track][Ncentralities];
    Double_t   sumM11M111[N_track][Ncentralities];
    Double_t   sumCorr2C7[N_track][Ncentralities];
    Double_t   sumCorr2C8[N_track][Ncentralities];
    Double_t  sumM1111S11[N_track][Ncentralities];
    Double_t   sumCorr4C1[N_track][Ncentralities];
    Double_t   sumCorr4C2[N_track][Ncentralities];
    Double_t   sumCorr4C5[N_track][Ncentralities];
    Double_t   sumCorr4C6[N_track][Ncentralities];
    Double_t sumM111M1111[N_track][Ncentralities];
    Double_t   sumCorr4C7[N_track][Ncentralities];
    Double_t   sumCorr4C8[N_track][Ncentralities];
    Double_t      sumC1C2[N_track][Ncentralities];
    Double_t      sumC1C5[N_track][Ncentralities];
    Double_t      sumC1C6[N_track][Ncentralities];
    Double_t   sumM111S11[N_track][Ncentralities];
    Double_t sumC1C7[N_track][Ncentralities];
    Double_t sumC1C8[N_track][Ncentralities];
    Double_t sumC2C5[N_track][Ncentralities];
    Double_t sumC2C6[N_track][Ncentralities];
    Double_t sumC2C7[N_track][Ncentralities];
    Double_t sumC2C8[N_track][Ncentralities];
    Double_t sumC5C6[N_track][Ncentralities];
    Double_t sumC5C7[N_track][Ncentralities];
    Double_t sumC5C8[N_track][Ncentralities];
    Double_t sumC6C7[N_track][Ncentralities];
    Double_t sumC6C8[N_track][Ncentralities];
    Double_t sumC7C8[N_track][Ncentralities];
    Double_t sumM11mp[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C3[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C4[Nbins][N_track][Ncentralities];
    Double_t sumM11M011[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C9[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C10[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C11[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C12[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C13[Nbins][N_track][Ncentralities];
    Double_t sumCorr2C14[Nbins][N_track][Ncentralities];
    Double_t sumM01S11[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC1[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC2[Nbins][N_track][Ncentralities];
    Double_t sumM01mp[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC3[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC4[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC5[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC6[Nbins][N_track][Ncentralities];
    Double_t sumM111M01[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC7[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC8[Nbins][N_track][Ncentralities];
    Double_t sumM01M011[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC9[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC10[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC11[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC12[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC13[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedC14[Nbins][N_track][Ncentralities];
    Double_t sumM1111mp[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C3[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C4[Nbins][N_track][Ncentralities];
    Double_t sumM1111M011[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C9[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C10[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C11[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C12[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C13[Nbins][N_track][Ncentralities];
    Double_t sumCorr4C14[Nbins][N_track][Ncentralities];
    Double_t sumM0111S11[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC1[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC2[Nbins][N_track][Ncentralities];
    Double_t sumM0111mp[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC3[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC4[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC5[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC6[Nbins][N_track][Ncentralities];
    Double_t sumM111M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC7[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC8[Nbins][N_track][Ncentralities];
    Double_t sumM011M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC9[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC10[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC11[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC12[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC13[Nbins][N_track][Ncentralities];
    Double_t sumCorr4ReducedC14[Nbins][N_track][Ncentralities];
    Double_t sumS11mp[Nbins][N_track][Ncentralities];
    Double_t sumC1C3[Nbins][N_track][Ncentralities];
    Double_t sumC1C4[Nbins][N_track][Ncentralities];
    Double_t sumM011S11[Nbins][N_track][Ncentralities];
    Double_t sumC1C9[Nbins][N_track][Ncentralities];
    Double_t sumC1C10[Nbins][N_track][Ncentralities];
    Double_t sumC1C11[Nbins][N_track][Ncentralities];
    Double_t sumC1C12[Nbins][N_track][Ncentralities];
    Double_t sumC1C13[Nbins][N_track][Ncentralities];
    Double_t sumC1C14[Nbins][N_track][Ncentralities];
    Double_t sumC2C3[Nbins][N_track][Ncentralities];
    Double_t sumC2C4[Nbins][N_track][Ncentralities];
    Double_t sumC2C9[Nbins][N_track][Ncentralities];
    Double_t sumC2C10[Nbins][N_track][Ncentralities];
    Double_t sumC2C11[Nbins][N_track][Ncentralities];
    Double_t sumC2C12[Nbins][N_track][Ncentralities];
    Double_t sumC2C13[Nbins][N_track][Ncentralities];
    Double_t sumC2C14[Nbins][N_track][Ncentralities];
    Double_t sumC3C4[Nbins][N_track][Ncentralities];
    Double_t sumC3C5[Nbins][N_track][Ncentralities];
    Double_t sumC3C6[Nbins][N_track][Ncentralities];
    Double_t sumM111mp[Nbins][N_track][Ncentralities];
    Double_t sumC3C7[Nbins][N_track][Ncentralities];
    Double_t sumC3C8[Nbins][N_track][Ncentralities];
    Double_t sumM011mp[Nbins][N_track][Ncentralities];
    Double_t sumC3C9[Nbins][N_track][Ncentralities];
    Double_t sumC3C10[Nbins][N_track][Ncentralities];
    Double_t sumC3C11[Nbins][N_track][Ncentralities];
    Double_t sumC3C12[Nbins][N_track][Ncentralities];
    Double_t sumC3C13[Nbins][N_track][Ncentralities];
    Double_t sumC3C14[Nbins][N_track][Ncentralities];
    Double_t sumC4C5[Nbins][N_track][Ncentralities];
    Double_t sumC4C6[Nbins][N_track][Ncentralities];
    Double_t sumC4C7[Nbins][N_track][Ncentralities];
    Double_t sumC4C8[Nbins][N_track][Ncentralities];
    Double_t sumC4C9[Nbins][N_track][Ncentralities];
    Double_t sumC4C10[Nbins][N_track][Ncentralities];
    Double_t sumC4C11[Nbins][N_track][Ncentralities];
    Double_t sumC4C12[Nbins][N_track][Ncentralities];
    Double_t sumC4C13[Nbins][N_track][Ncentralities];
    Double_t sumC4C14[Nbins][N_track][Ncentralities];
    Double_t sumC5C9[Nbins][N_track][Ncentralities];
    Double_t sumC5C10[Nbins][N_track][Ncentralities];
    Double_t sumC5C11[Nbins][N_track][Ncentralities];
    Double_t sumC5C12[Nbins][N_track][Ncentralities];
    Double_t sumC5C13[Nbins][N_track][Ncentralities];
    Double_t sumC5C14[Nbins][N_track][Ncentralities];
    Double_t sumC6C9[Nbins][N_track][Ncentralities];
    Double_t sumC6C10[Nbins][N_track][Ncentralities];
    Double_t sumC6C11[Nbins][N_track][Ncentralities];
    Double_t sumC6C12[Nbins][N_track][Ncentralities];
    Double_t sumC6C13[Nbins][N_track][Ncentralities];
    Double_t sumC6C14[Nbins][N_track][Ncentralities];
    Double_t sumM111M011[Nbins][N_track][Ncentralities];
    Double_t sumC7C9[Nbins][N_track][Ncentralities];
    Double_t sumC7C10[Nbins][N_track][Ncentralities];
    Double_t sumC7C11[Nbins][N_track][Ncentralities];
    Double_t sumC7C12[Nbins][N_track][Ncentralities];
    Double_t sumC7C13[Nbins][N_track][Ncentralities];
    Double_t sumC7C14[Nbins][N_track][Ncentralities];
    Double_t sumC8C9[Nbins][N_track][Ncentralities];
    Double_t sumC8C10[Nbins][N_track][Ncentralities];
    Double_t sumC8C11[Nbins][N_track][Ncentralities];
    Double_t sumC8C12[Nbins][N_track][Ncentralities];
    Double_t sumC8C13[Nbins][N_track][Ncentralities];
    Double_t sumC8C14[Nbins][N_track][Ncentralities];
    Double_t sumC9C10[Nbins][N_track][Ncentralities];
    Double_t sumC9C11[Nbins][N_track][Ncentralities];
    Double_t sumC9C12[Nbins][N_track][Ncentralities];
    Double_t sumC9C13[Nbins][N_track][Ncentralities];
    Double_t sumC9C14[Nbins][N_track][Ncentralities];
    Double_t sumC10C11[Nbins][N_track][Ncentralities];
    Double_t sumC10C12[Nbins][N_track][Ncentralities];
    Double_t sumC10C13[Nbins][N_track][Ncentralities];
    Double_t sumC10C14[Nbins][N_track][Ncentralities];
    Double_t sumC11C12[Nbins][N_track][Ncentralities];
    Double_t sumC11C13[Nbins][N_track][Ncentralities];
    Double_t sumC11C14[Nbins][N_track][Ncentralities];
    Double_t sumC12C13[Nbins][N_track][Ncentralities];
    Double_t sumC12C14[Nbins][N_track][Ncentralities];
    Double_t sumC13C14[Nbins][N_track][Ncentralities];
  public:
    FxtMaker(StMuDstMaker* Maker, TString JobId, Int_t EventsNumber, Double_t inputParameter);
    virtual          ~FxtMaker();
    Int_t            Init();
    Int_t            Make();
    Int_t            Finish();
    Double_t         GetCovariance(Double_t w1,Double_t w1v1,Double_t w2,Double_t w2v2,Double_t w1w2,Double_t w1w2v1v2);
    Double_t              GetError(Double_t w1,Double_t w1square,Double_t w1v1,Double_t w1v1square);
    ClassDef(FxtMaker,1)    // Class title
};

#endif    // End of preprocessor