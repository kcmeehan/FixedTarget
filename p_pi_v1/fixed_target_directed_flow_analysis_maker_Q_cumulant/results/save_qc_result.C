#include <iostream>
#include "TFile.h"
#include "TMath.h"
#include "TH1D.h"
#include "TArrayD.h"

Double_t GetCovariance(Double_t w1,Double_t w1v1,Double_t w2,Double_t w2v2,Double_t w1w2,Double_t w1w2v1v2){
    Double_t cov = ((w1w2v1v2/w1w2) - (w1v1/w1)*(w2v2/w2))/(w1*w2/w1w2 - 1.);
    if(!TMath::Finite(cov)) cov = 0.0;
    return cov;
}

Double_t GetError(Double_t w1,Double_t w1square,Double_t w1v1,Double_t w1v1square){
    Double_t err = TMath::Abs(((w1v1square/w1) - (w1v1/w1)*(w1v1/w1))/(w1*w1/w1square - 1.));
    if(!TMath::Finite(err)) err = 0.0;
    return err;
}

void save_qc_result(TString jobId,Int_t numberOfJobs)
{
    std::cout<<"FLAG0"<<std::endl;
    char infile[60], outfile[60];
    const Int_t Ncentralities =   7;
    const Int_t   	  N_track = 240;
    const Int_t         Nbins =  20;
    const Int_t   Nhistograms =   3 + 2*Ncentralities;
    Double_t Low = -2., High = 0.;
    //Double_t Low = 0.0, High = 2.0;
    TFile*                    input;
    TArrayD*             flowArrayD;
    TArrayD*            flowArray2D;
	TArrayD*         flowArrayCOV1D;
    TArrayD*         flowArrayCOV2D;
    TArrayD*         flowArrayCOV3D;
    TArrayD*         flowArrayCOV4D;
    TH1D*               histogram1D[ Nhistograms ];
    Int_t               multCounter[N_track];
    Double_t                 sumS11[ N_track ][ Ncentralities ];
    Double_t                 sumM11[ N_track ][ Ncentralities ];
    Double_t                sumM111[ N_track ][ Ncentralities ];
    Double_t               sumM1111[ N_track ][ Ncentralities ];
    Double_t               sumCorr2[ N_track ][ Ncentralities ];
    Double_t               sumCorr4[ N_track ][ Ncentralities ];
    Double_t              sumAddon1[ N_track ][ Ncentralities ];
    Double_t              sumAddon2[ N_track ][ Ncentralities ];
    Double_t              sumAddon5[ N_track ][ Ncentralities ];
    Double_t              sumAddon6[ N_track ][ Ncentralities ];
    Double_t              sumAddon7[ N_track ][ Ncentralities ];
    Double_t              sumAddon8[ N_track ][ Ncentralities ];
    Double_t          sumS11Squared[ N_track ][ Ncentralities ];
    Double_t          sumM11Squared[ N_track ][ Ncentralities ];
    Double_t         sumM111Squared[ N_track ][ Ncentralities ];
    Double_t        sumM1111Squared[ N_track ][ Ncentralities ];
    Double_t        sumCorr2Squared[ N_track ][ Ncentralities ];
    Double_t        sumCorr4Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon1Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon2Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon5Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon6Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon7Squared[ N_track ][ Ncentralities ];
    Double_t       sumAddon8Squared[ N_track ][ Ncentralities ];
    Double_t                  sumMp[ Nbins ][ N_track ][ Ncentralities ];
    Double_t                 sumM01[ Nbins ][ N_track ][ Ncentralities ];
    Double_t                sumM011[ Nbins ][ N_track ][ Ncentralities ];
    Double_t               sumM0111[ Nbins ][ N_track ][ Ncentralities ];
    Double_t        sumCorr2Reduced[ Nbins ][ N_track ][ Ncentralities ];
    Double_t        sumCorr4Reduced[ Nbins ][ N_track ][ Ncentralities ];
    Double_t              sumAddon3[ Nbins ][ N_track ][ Ncentralities ];
    Double_t              sumAddon4[ Nbins ][ N_track ][ Ncentralities ];
    Double_t              sumAddon9[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon10[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon11[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon12[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon13[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon14[ Nbins ][ N_track ][ Ncentralities ];
    Double_t             sumAddon15[ Nbins ][ N_track ][ Ncentralities ];
    Double_t           sumMpSquared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t          sumM01Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t         sumM011Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t        sumM0111Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t sumCorr2ReducedSquared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t sumCorr4ReducedSquared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t       sumAddon3Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t       sumAddon4Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t       sumAddon9Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon10Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon11Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon12Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon13Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon14Squared[ Nbins ][ N_track ][ Ncentralities ];
    Double_t      sumAddon15Squared[ Nbins ][ N_track ][ Ncentralities ];
	// Covariance terms
    Double_t sumM11M1111[N_track][Ncentralities];
    Double_t sumCorr2Corr4[N_track][Ncentralities];
    Double_t sumM11M01[Nbins][N_track][Ncentralities];
    Double_t sumCorr2Corr2Reduced[Nbins][N_track][Ncentralities];
    Double_t sumM11M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr2Corr4Reduced[Nbins][N_track][Ncentralities];
    Double_t sumM1111M01[Nbins][N_track][Ncentralities];
    Double_t sumCorr4Corr2Reduced[Nbins][N_track][Ncentralities];
    Double_t sumM1111M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr4Corr4Reduced[Nbins][N_track][Ncentralities];
    Double_t sumM01M0111[Nbins][N_track][Ncentralities];
    Double_t sumCorr2ReducedCorr4Reduced[Nbins][N_track][Ncentralities];
    Double_t sumM11S11[N_track][Ncentralities];
    Double_t sumCorr2C1[N_track][Ncentralities];
    Double_t sumCorr2C2[N_track][Ncentralities];
    Double_t sumCorr2C5[N_track][Ncentralities];
    Double_t sumCorr2C6[N_track][Ncentralities];
    Double_t sumM11M111[N_track][Ncentralities];
    Double_t sumCorr2C7[N_track][Ncentralities];
    Double_t sumCorr2C8[N_track][Ncentralities];
    Double_t sumM1111S11[N_track][Ncentralities];
    Double_t sumCorr4C1[N_track][Ncentralities];
    Double_t sumCorr4C2[N_track][Ncentralities];
    Double_t sumCorr4C5[N_track][Ncentralities];
    Double_t sumCorr4C6[N_track][Ncentralities];
    Double_t sumM111M1111[N_track][Ncentralities];
    Double_t sumCorr4C7[N_track][Ncentralities];
    Double_t sumCorr4C8[N_track][Ncentralities];
    Double_t sumC1C2[N_track][Ncentralities];
    Double_t sumC1C5[N_track][Ncentralities];
    Double_t sumC1C6[N_track][Ncentralities];
    Double_t sumM111S11[N_track][Ncentralities];
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
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            if(icent == 0) multCounter[itrack] = 0;
            sumS11[itrack][icent] = 0.0;
            sumM11[itrack][icent] = 0.0;
            sumM111[itrack][icent] = 0.0;
            sumM1111[itrack][icent] = 0.0;
            sumCorr2[itrack][icent] = 0.0;
            sumCorr4[itrack][icent] = 0.0;
            sumAddon1[itrack][icent] = 0.0;
            sumAddon2[itrack][icent] = 0.0;
            sumAddon5[itrack][icent] = 0.0;
            sumAddon6[itrack][icent] = 0.0;
            sumAddon7[itrack][icent] = 0.0;
            sumAddon8[itrack][icent] = 0.0;
            sumS11Squared[itrack][icent] = 0.0;
            sumM11Squared[itrack][icent] = 0.0;
            sumM111Squared[itrack][icent] = 0.0;
            sumM1111Squared[itrack][icent] = 0.0;
            sumCorr2Squared[itrack][icent] = 0.0;
            sumCorr4Squared[itrack][icent] = 0.0;
            sumAddon1Squared[itrack][icent] = 0.0;
            sumAddon2Squared[itrack][icent] = 0.0;
            sumAddon5Squared[itrack][icent] = 0.0;
            sumAddon6Squared[itrack][icent] = 0.0;
            sumAddon7Squared[itrack][icent] = 0.0;
            sumAddon8Squared[itrack][icent] = 0.0;
            sumM11M1111[itrack][icent] = 0.0;
            sumCorr2Corr4[itrack][icent] = 0.0;
            sumM11S11[itrack][icent] = 0.0;
            sumCorr2C1[itrack][icent] = 0.0;
            sumCorr2C2[itrack][icent] = 0.0;
            sumCorr2C5[itrack][icent] = 0.0;
            sumCorr2C6[itrack][icent] = 0.0;
            sumM11M111[itrack][icent] = 0.0;
            sumCorr2C7[itrack][icent] = 0.0;
            sumCorr2C8[itrack][icent] = 0.0;
            sumM1111S11[itrack][icent] = 0.0;
            sumCorr4C1[itrack][icent] = 0.0;
            sumCorr4C2[itrack][icent] = 0.0;
            sumCorr4C5[itrack][icent] = 0.0;
            sumCorr4C6[itrack][icent] = 0.0;
            sumM111M1111[itrack][icent] = 0.0;
            sumCorr4C7[itrack][icent] = 0.0;
            sumCorr4C8[itrack][icent] = 0.0;
            sumC1C2[itrack][icent] = 0.0;
            sumC1C5[itrack][icent] = 0.0;
            sumC1C6[itrack][icent] = 0.0;
            sumM111S11[itrack][icent] = 0.0;
            sumC1C7[itrack][icent] = 0.0;
            sumC1C8[itrack][icent] = 0.0;
            sumC2C5[itrack][icent] = 0.0;
            sumC2C6[itrack][icent] = 0.0;
            sumC2C7[itrack][icent] = 0.0;
            sumC2C8[itrack][icent] = 0.0;
            sumC5C6[itrack][icent] = 0.0;
            sumC5C7[itrack][icent] = 0.0;
            sumC5C8[itrack][icent] = 0.0;
            sumC6C7[itrack][icent] = 0.0;
            sumC6C8[itrack][icent] = 0.0;
            sumC7C8[itrack][icent] = 0.0;
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumMp[ibin][itrack][icent] = 0.0;
                sumM01[ibin][itrack][icent] = 0.0;
                sumM011[ibin][itrack][icent] = 0.0;
                sumM0111[ibin][itrack][icent] = 0.0;
                sumCorr2Reduced[ibin][itrack][icent] = 0.0;
                sumCorr4Reduced[ibin][itrack][icent] = 0.0;
                sumAddon3[ibin][itrack][icent] = 0.0;
                sumAddon4[ibin][itrack][icent] = 0.0;
                sumAddon9[ibin][itrack][icent] = 0.0;
                sumAddon10[ibin][itrack][icent] = 0.0;
                sumAddon11[ibin][itrack][icent] = 0.0;
                sumAddon12[ibin][itrack][icent] = 0.0;
                sumAddon13[ibin][itrack][icent] = 0.0;
                sumAddon14[ibin][itrack][icent] = 0.0;
                sumAddon15[ibin][itrack][icent] = 0.0;
                sumMpSquared[ibin][itrack][icent] = 0.0;
                sumM01Squared[ibin][itrack][icent] = 0.0;
                sumM011Squared[ibin][itrack][icent] = 0.0;
                sumM0111Squared[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedSquared[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedSquared[ibin][itrack][icent] = 0.0;
                sumAddon3Squared[ibin][itrack][icent] = 0.0;
                sumAddon4Squared[ibin][itrack][icent] = 0.0;
                sumAddon9Squared[ibin][itrack][icent] = 0.0;
                sumAddon10Squared[ibin][itrack][icent] = 0.0;
                sumAddon11Squared[ibin][itrack][icent] = 0.0;
                sumAddon12Squared[ibin][itrack][icent] = 0.0;
                sumAddon13Squared[ibin][itrack][icent] = 0.0;
                sumAddon14Squared[ibin][itrack][icent] = 0.0;
                sumAddon15Squared[ibin][itrack][icent] = 0.0;
                sumM11M01[ibin][itrack][icent] = 0.0;
                sumCorr2Corr2Reduced[ibin][itrack][icent] = 0.0;
                sumM11M0111[ibin][itrack][icent] = 0.0;
                sumCorr2Corr4Reduced[ibin][itrack][icent] = 0.0;
                sumM1111M01[ibin][itrack][icent] = 0.0;
                sumCorr4Corr2Reduced[ibin][itrack][icent] = 0.0;
                sumM1111M0111[ibin][itrack][icent] = 0.0;
                sumCorr4Corr4Reduced[ibin][itrack][icent] = 0.0;
                sumM01M0111[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedCorr4Reduced[ibin][itrack][icent] = 0.0;
                sumM11mp[ibin][itrack][icent] = 0.0;
                sumCorr2C3[ibin][itrack][icent] = 0.0;
                sumCorr2C4[ibin][itrack][icent] = 0.0;
                sumM11M011[ibin][itrack][icent] = 0.0;
                sumCorr2C9[ibin][itrack][icent] = 0.0;
                sumCorr2C10[ibin][itrack][icent] = 0.0;
                sumCorr2C11[ibin][itrack][icent] = 0.0;
                sumCorr2C12[ibin][itrack][icent] = 0.0;
                sumCorr2C13[ibin][itrack][icent] = 0.0;
                sumCorr2C14[ibin][itrack][icent] = 0.0;
                sumM01S11[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC1[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC2[ibin][itrack][icent] = 0.0;
                sumM01mp[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC3[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC4[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC5[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC6[ibin][itrack][icent] = 0.0;
                sumM111M01[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC7[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC8[ibin][itrack][icent] = 0.0;
                sumM01M011[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC9[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC10[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC11[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC12[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC13[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC14[ibin][itrack][icent] = 0.0;
                sumM1111mp[ibin][itrack][icent] = 0.0;
                sumCorr4C3[ibin][itrack][icent] = 0.0;
                sumCorr4C4[ibin][itrack][icent] = 0.0;
                sumM1111M011[ibin][itrack][icent] = 0.0;
                sumCorr4C9[ibin][itrack][icent] = 0.0;
                sumCorr4C10[ibin][itrack][icent] = 0.0;
                sumCorr4C11[ibin][itrack][icent] = 0.0;
                sumCorr4C12[ibin][itrack][icent] = 0.0;
                sumCorr4C13[ibin][itrack][icent] = 0.0;
                sumCorr4C14[ibin][itrack][icent] = 0.0;
                sumM0111S11[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC1[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC2[ibin][itrack][icent] = 0.0;
                sumM0111mp[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC3[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC4[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC5[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC6[ibin][itrack][icent] = 0.0;
                sumM111M0111[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC7[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC8[ibin][itrack][icent] = 0.0;
                sumM011M0111[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC9[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC10[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC11[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC12[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC13[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC14[ibin][itrack][icent] = 0.0;
                sumS11mp[ibin][itrack][icent] = 0.0;
                sumC1C3[ibin][itrack][icent] = 0.0;
                sumC1C4[ibin][itrack][icent] = 0.0;
                sumM011S11[ibin][itrack][icent] = 0.0;
                sumC1C9[ibin][itrack][icent] = 0.0;
                sumC1C10[ibin][itrack][icent] = 0.0;
                sumC1C11[ibin][itrack][icent] = 0.0;
                sumC1C12[ibin][itrack][icent] = 0.0;
                sumC1C13[ibin][itrack][icent] = 0.0;
                sumC1C14[ibin][itrack][icent] = 0.0;
                sumC2C3[ibin][itrack][icent] = 0.0;
                sumC2C4[ibin][itrack][icent] = 0.0;
                sumC2C9[ibin][itrack][icent] = 0.0;
                sumC2C10[ibin][itrack][icent] = 0.0;
                sumC2C11[ibin][itrack][icent] = 0.0;
                sumC2C12[ibin][itrack][icent] = 0.0;
                sumC2C13[ibin][itrack][icent] = 0.0;
                sumC2C14[ibin][itrack][icent] = 0.0;
                sumC3C4[ibin][itrack][icent] = 0.0;
                sumC3C5[ibin][itrack][icent] = 0.0;
                sumC3C6[ibin][itrack][icent] = 0.0;
                sumM111mp[ibin][itrack][icent] = 0.0;
                sumC3C7[ibin][itrack][icent] = 0.0;
                sumC3C8[ibin][itrack][icent] = 0.0;
                sumM011mp[ibin][itrack][icent] = 0.0;
                sumC3C9[ibin][itrack][icent] = 0.0;
                sumC3C10[ibin][itrack][icent] = 0.0;
                sumC3C11[ibin][itrack][icent] = 0.0;
                sumC3C12[ibin][itrack][icent] = 0.0;
                sumC3C13[ibin][itrack][icent] = 0.0;
                sumC3C14[ibin][itrack][icent] = 0.0;
                sumC4C5[ibin][itrack][icent] = 0.0;
                sumC4C6[ibin][itrack][icent] = 0.0;
                sumC4C7[ibin][itrack][icent] = 0.0;
                sumC4C8[ibin][itrack][icent] = 0.0;
                sumC4C9[ibin][itrack][icent] = 0.0;
                sumC4C10[ibin][itrack][icent] = 0.0;
                sumC4C11[ibin][itrack][icent] = 0.0;
                sumC4C12[ibin][itrack][icent] = 0.0;
                sumC4C13[ibin][itrack][icent] = 0.0;
                sumC4C14[ibin][itrack][icent] = 0.0;
                sumC5C9[ibin][itrack][icent] = 0.0;
                sumC5C10[ibin][itrack][icent] = 0.0;
                sumC5C11[ibin][itrack][icent] = 0.0;
                sumC5C12[ibin][itrack][icent] = 0.0;
                sumC5C13[ibin][itrack][icent] = 0.0;
                sumC5C14[ibin][itrack][icent] = 0.0;
                sumC6C9[ibin][itrack][icent] = 0.0;
                sumC6C10[ibin][itrack][icent] = 0.0;
                sumC6C11[ibin][itrack][icent] = 0.0;
                sumC6C12[ibin][itrack][icent] = 0.0;
                sumC6C13[ibin][itrack][icent] = 0.0;
                sumC6C14[ibin][itrack][icent] = 0.0;
                sumM111M011[ibin][itrack][icent] = 0.0;
                sumC7C9[ibin][itrack][icent] = 0.0;
                sumC7C10[ibin][itrack][icent] = 0.0;
                sumC7C11[ibin][itrack][icent] = 0.0;
                sumC7C12[ibin][itrack][icent] = 0.0;
                sumC7C13[ibin][itrack][icent] = 0.0;
                sumC7C14[ibin][itrack][icent] = 0.0;
                sumC8C9[ibin][itrack][icent] = 0.0;
                sumC8C10[ibin][itrack][icent] = 0.0;
                sumC8C11[ibin][itrack][icent] = 0.0;
                sumC8C12[ibin][itrack][icent] = 0.0;
                sumC8C13[ibin][itrack][icent] = 0.0;
                sumC8C14[ibin][itrack][icent] = 0.0;
                sumC9C10[ibin][itrack][icent] = 0.0;
                sumC9C11[ibin][itrack][icent] = 0.0;
                sumC9C12[ibin][itrack][icent] = 0.0;
                sumC9C13[ibin][itrack][icent] = 0.0;
                sumC9C14[ibin][itrack][icent] = 0.0;
                sumC10C11[ibin][itrack][icent] = 0.0;
                sumC10C12[ibin][itrack][icent] = 0.0;
                sumC10C13[ibin][itrack][icent] = 0.0;
                sumC10C14[ibin][itrack][icent] = 0.0;
                sumC11C12[ibin][itrack][icent] = 0.0;
                sumC11C13[ibin][itrack][icent] = 0.0;
                sumC11C14[ibin][itrack][icent] = 0.0;
                sumC12C13[ibin][itrack][icent] = 0.0;
                sumC12C14[ibin][itrack][icent] = 0.0;
                sumC13C14[ibin][itrack][icent] = 0.0;
              }
          }
      }
    std::cout<<"FLAG1"<<std::endl;
    // Flow plots
    char name[60], description[60];
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        sprintf(name,"v1_2_Proton_%d",icent+1);
        //sprintf(description,"(%d - %d)%% proton v_{1}(y)",80-5*(icent+1),80-5*icent);
        if( icent >  0 ) sprintf(description,"(%d-%d)%% proton v_{1}(y)",30-5*icent,30-5*(icent-1));
        if( icent == 0 ) sprintf(description,">30%% proton v_{1}(y)");
        histogram1D[0+2*icent] = new TH1D(name,description,Nbins,Low,High);
        histogram1D[0+2*icent]->GetXaxis()->SetTitle("Rapidity y");
        histogram1D[0+2*icent]->GetYaxis()->SetTitle("v_{1}");
        histogram1D[0+2*icent]->GetXaxis()->SetTitleSize(0.05);
        histogram1D[0+2*icent]->GetXaxis()->SetTitleOffset(0.8);
        histogram1D[0+2*icent]->GetYaxis()->SetTitleSize(0.05);
        histogram1D[0+2*icent]->GetYaxis()->SetTitleOffset(0.9);
        sprintf(name,"v1_4_Proton_%d",icent+1);
        histogram1D[1+2*icent] = new TH1D(name,description,Nbins,Low,High);
        histogram1D[1+2*icent]->GetXaxis()->SetTitle("Rapidity y");
        histogram1D[1+2*icent]->GetYaxis()->SetTitle("v_{1}");
        histogram1D[1+2*icent]->GetXaxis()->SetTitleSize(0.05);
        histogram1D[1+2*icent]->GetXaxis()->SetTitleOffset(0.8);
        histogram1D[1+2*icent]->GetYaxis()->SetTitleSize(0.05);
        histogram1D[1+2*icent]->GetYaxis()->SetTitleOffset(0.9);
      }
    histogram1D[0+2*Ncentralities] = new TH1D("v1_2_Proton","(10-25)% proton v_{1}(y)",Nbins,Low,High);
    histogram1D[0+2*Ncentralities]->GetXaxis()->SetTitle("Rapidity y");
    histogram1D[0+2*Ncentralities]->GetYaxis()->SetTitle("v_{1}");
    histogram1D[0+2*Ncentralities]->GetXaxis()->SetTitleSize(0.05);
    histogram1D[0+2*Ncentralities]->GetXaxis()->SetTitleOffset(0.9);
    histogram1D[0+2*Ncentralities]->GetYaxis()->SetTitleSize(0.05);
    histogram1D[0+2*Ncentralities]->GetYaxis()->SetTitleOffset(0.9);
	histogram1D[0+2*Ncentralities]->SetMarkerStyle(20);histogram1D[0+2*Ncentralities]->SetMarkerColor(2);histogram1D[0+2*Ncentralities]->SetLineColor(2);
    histogram1D[1+2*Ncentralities] = new TH1D("v1_4_Proton","(10-25)% proton v_{1}(y)",Nbins,Low,High);
    histogram1D[1+2*Ncentralities]->GetXaxis()->SetTitle("Rapidity y");
    histogram1D[1+2*Ncentralities]->GetYaxis()->SetTitle("v_{1}");
    histogram1D[1+2*Ncentralities]->GetXaxis()->SetTitleSize(0.05);
    histogram1D[1+2*Ncentralities]->GetXaxis()->SetTitleOffset(0.9);
    histogram1D[1+2*Ncentralities]->GetYaxis()->SetTitleSize(0.05);
    histogram1D[1+2*Ncentralities]->GetYaxis()->SetTitleOffset(0.9);
	histogram1D[1+2*Ncentralities]->SetMarkerStyle(24);histogram1D[1+2*Ncentralities]->SetMarkerColor(4);histogram1D[1+2*Ncentralities]->SetLineColor(4);
    //sprintf(outfile,"%s_result.root",jobId);
    TString outputName = jobId; TString eachFileName = jobId;
    outputName.Append("_result.root");
    for( Int_t ifile = 0; ifile < numberOfJobs; ifile++ )
      {
        eachFileName = jobId;
        sprintf(infile,"_%d.root",ifile);
		//sprintf(infile,".root");
        eachFileName.Append(infile);
        input = new TFile(eachFileName,"READ");
        if( !input->IsOpen() ) continue;
        flowArrayD = (TArrayD*)input->Get("flowArray");
        flowArray2D = (TArrayD*)input->Get("flowArray2");
		flowArrayCOV1D = (TArrayD*)input->Get("flowArrayCOV1");
		flowArrayCOV2D = (TArrayD*)input->Get("flowArrayCOV2");
		flowArrayCOV3D = (TArrayD*)input->Get("flowArrayCOV3");
		flowArrayCOV4D = (TArrayD*)input->Get("flowArrayCOV4");
        for ( Int_t icent = 0; icent < Ncentralities; icent++ )
          {
            for ( Int_t itrack = 0; itrack < N_track; itrack++ )
              {
                // Read flow variables to TArrayD
                if(icent == 0) multCounter[itrack] += flowArray2D->At(itrack);
                          sumS11[itrack][icent] += flowArrayD->At(  0 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                          sumM11[itrack][icent] += flowArrayD->At(  1 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumM111[itrack][icent] += flowArrayD->At(  2 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                        sumM1111[itrack][icent] += flowArrayD->At(  3 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                        sumCorr2[itrack][icent] += flowArrayD->At(  4 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                        sumCorr4[itrack][icent] += flowArrayD->At(  5 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon1[itrack][icent] += flowArrayD->At(  6 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon2[itrack][icent] += flowArrayD->At(  7 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon5[itrack][icent] += flowArrayD->At(  8 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon6[itrack][icent] += flowArrayD->At(  9 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon7[itrack][icent] += flowArrayD->At( 10 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                       sumAddon8[itrack][icent] += flowArrayD->At( 11 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                   sumS11Squared[itrack][icent] += flowArrayD->At( 12 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                   sumM11Squared[itrack][icent] += flowArrayD->At( 13 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                  sumM111Squared[itrack][icent] += flowArrayD->At( 14 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                 sumM1111Squared[itrack][icent] += flowArrayD->At( 15 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                 sumCorr2Squared[itrack][icent] += flowArrayD->At( 16 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                 sumCorr4Squared[itrack][icent] += flowArrayD->At( 17 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon1Squared[itrack][icent] += flowArrayD->At( 18 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon2Squared[itrack][icent] += flowArrayD->At( 19 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon5Squared[itrack][icent] += flowArrayD->At( 20 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon6Squared[itrack][icent] += flowArrayD->At( 21 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon7Squared[itrack][icent] += flowArrayD->At( 22 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                sumAddon8Squared[itrack][icent] += flowArrayD->At( 23 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
                  {
                                     sumMp[ibin][itrack][icent] += flowArrayD->At( 24 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                    sumM01[ibin][itrack][icent] += flowArrayD->At( 25 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                   sumM011[ibin][itrack][icent] += flowArrayD->At( 26 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                  sumM0111[ibin][itrack][icent] += flowArrayD->At( 27 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                           sumCorr2Reduced[ibin][itrack][icent] += flowArrayD->At( 28 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                           sumCorr4Reduced[ibin][itrack][icent] += flowArrayD->At( 29 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                 sumAddon3[ibin][itrack][icent] += flowArrayD->At( 30 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                 sumAddon4[ibin][itrack][icent] += flowArrayD->At( 31 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                 sumAddon9[ibin][itrack][icent] += flowArrayD->At( 32 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon10[ibin][itrack][icent] += flowArrayD->At( 33 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon11[ibin][itrack][icent] += flowArrayD->At( 34 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon12[ibin][itrack][icent] += flowArrayD->At( 35 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon13[ibin][itrack][icent] += flowArrayD->At( 36 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon14[ibin][itrack][icent] += flowArrayD->At( 37 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                                sumAddon15[ibin][itrack][icent] += flowArrayD->At( 38 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                              sumMpSquared[ibin][itrack][icent] += flowArrayD->At( 39 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                             sumM01Squared[ibin][itrack][icent] += flowArrayD->At( 40 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                            sumM011Squared[ibin][itrack][icent] += flowArrayD->At( 41 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                           sumM0111Squared[ibin][itrack][icent] += flowArrayD->At( 42 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                    sumCorr2ReducedSquared[ibin][itrack][icent] += flowArrayD->At( 43 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                    sumCorr4ReducedSquared[ibin][itrack][icent] += flowArrayD->At( 44 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                          sumAddon3Squared[ibin][itrack][icent] += flowArrayD->At( 45 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                          sumAddon4Squared[ibin][itrack][icent] += flowArrayD->At( 46 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                          sumAddon9Squared[ibin][itrack][icent] += flowArrayD->At( 47 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon10Squared[ibin][itrack][icent] += flowArrayD->At( 48 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon11Squared[ibin][itrack][icent] += flowArrayD->At( 49 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon12Squared[ibin][itrack][icent] += flowArrayD->At( 50 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon13Squared[ibin][itrack][icent] += flowArrayD->At( 51 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon14Squared[ibin][itrack][icent] += flowArrayD->At( 52 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                         sumAddon15Squared[ibin][itrack][icent] += flowArrayD->At( 53 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                  }
              }
          }
		for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            sumM11S11[itrack][icent] += flowArrayCOV1D->At( 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C1[itrack][icent] += flowArrayCOV1D->At( 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C2[itrack][icent] += flowArrayCOV1D->At( 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C5[itrack][icent] += flowArrayCOV1D->At( 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C6[itrack][icent] += flowArrayCOV1D->At( 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumM11M111[itrack][icent] += flowArrayCOV1D->At( 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C7[itrack][icent] += flowArrayCOV1D->At( 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr2C8[itrack][icent] += flowArrayCOV1D->At( 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumM11mp[ibin][itrack][icent] += flowArrayCOV1D->At( 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C3[ibin][itrack][icent] += flowArrayCOV1D->At( 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C4[ibin][itrack][icent] += flowArrayCOV1D->At( 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM11M011[ibin][itrack][icent] += flowArrayCOV1D->At( 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C9[ibin][itrack][icent] += flowArrayCOV1D->At( 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C10[ibin][itrack][icent] += flowArrayCOV1D->At( 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C11[ibin][itrack][icent] += flowArrayCOV1D->At( 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C12[ibin][itrack][icent] += flowArrayCOV1D->At( 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C13[ibin][itrack][icent] += flowArrayCOV1D->At( 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2C14[ibin][itrack][icent] += flowArrayCOV1D->At( 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM01S11[ibin][itrack][icent] += flowArrayCOV1D->At( 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC1[ibin][itrack][icent] += flowArrayCOV1D->At( 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC2[ibin][itrack][icent] += flowArrayCOV1D->At( 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM01mp[ibin][itrack][icent] += flowArrayCOV1D->At( 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC3[ibin][itrack][icent] += flowArrayCOV1D->At( 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC4[ibin][itrack][icent] += flowArrayCOV1D->At( 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC5[ibin][itrack][icent] += flowArrayCOV1D->At( 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC6[ibin][itrack][icent] += flowArrayCOV1D->At( 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM111M01[ibin][itrack][icent] += flowArrayCOV1D->At( 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC7[ibin][itrack][icent] += flowArrayCOV1D->At( 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC8[ibin][itrack][icent] += flowArrayCOV1D->At( 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM01M011[ibin][itrack][icent] += flowArrayCOV1D->At( 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC9[ibin][itrack][icent] += flowArrayCOV1D->At( 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC10[ibin][itrack][icent] += flowArrayCOV1D->At( 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC11[ibin][itrack][icent] += flowArrayCOV1D->At( 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC12[ibin][itrack][icent] += flowArrayCOV1D->At( 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC13[ibin][itrack][icent] += flowArrayCOV1D->At( 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr2ReducedC14[ibin][itrack][icent] += flowArrayCOV1D->At( 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM1111mp[ibin][itrack][icent] += flowArrayCOV1D->At( 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C3[ibin][itrack][icent] += flowArrayCOV1D->At( 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C4[ibin][itrack][icent] += flowArrayCOV1D->At( 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM1111M011[ibin][itrack][icent] += flowArrayCOV1D->At( 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C9[ibin][itrack][icent] += flowArrayCOV1D->At( 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC13C14[ibin][itrack][icent] += flowArrayCOV1D->At( 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            sumM1111S11[itrack][icent] += flowArrayCOV2D->At( 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C1[itrack][icent] += flowArrayCOV2D->At( 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C2[itrack][icent] += flowArrayCOV2D->At( 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C5[itrack][icent] += flowArrayCOV2D->At( 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C6[itrack][icent] += flowArrayCOV2D->At( 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumM111M1111[itrack][icent] += flowArrayCOV2D->At( 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C7[itrack][icent] += flowArrayCOV2D->At( 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumCorr4C8[itrack][icent] += flowArrayCOV2D->At( 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumCorr4C10[ibin][itrack][icent] += flowArrayCOV2D->At( 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C11[ibin][itrack][icent] += flowArrayCOV2D->At( 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C12[ibin][itrack][icent] += flowArrayCOV2D->At( 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C13[ibin][itrack][icent] += flowArrayCOV2D->At( 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4C14[ibin][itrack][icent] += flowArrayCOV2D->At( 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM0111S11[ibin][itrack][icent] += flowArrayCOV2D->At( 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC1[ibin][itrack][icent] += flowArrayCOV2D->At( 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC2[ibin][itrack][icent] += flowArrayCOV2D->At( 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM0111mp[ibin][itrack][icent] += flowArrayCOV2D->At( 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC3[ibin][itrack][icent] += flowArrayCOV2D->At( 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC4[ibin][itrack][icent] += flowArrayCOV2D->At( 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC5[ibin][itrack][icent] += flowArrayCOV2D->At( 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC6[ibin][itrack][icent] += flowArrayCOV2D->At( 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM111M0111[ibin][itrack][icent] += flowArrayCOV2D->At( 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC7[ibin][itrack][icent] += flowArrayCOV2D->At( 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC8[ibin][itrack][icent] += flowArrayCOV2D->At( 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM011M0111[ibin][itrack][icent] += flowArrayCOV2D->At( 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC9[ibin][itrack][icent] += flowArrayCOV2D->At( 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC10[ibin][itrack][icent] += flowArrayCOV2D->At( 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC11[ibin][itrack][icent] += flowArrayCOV2D->At( 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC12[ibin][itrack][icent] += flowArrayCOV2D->At( 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC13[ibin][itrack][icent] += flowArrayCOV2D->At( 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumCorr4ReducedC14[ibin][itrack][icent] += flowArrayCOV2D->At( 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumS11mp[ibin][itrack][icent] += flowArrayCOV2D->At( 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C3[ibin][itrack][icent] += flowArrayCOV2D->At( 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C4[ibin][itrack][icent] += flowArrayCOV2D->At( 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM011S11[ibin][itrack][icent] += flowArrayCOV2D->At( 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C9[ibin][itrack][icent] += flowArrayCOV2D->At( 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C10[ibin][itrack][icent] += flowArrayCOV2D->At( 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C11[ibin][itrack][icent] += flowArrayCOV2D->At( 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C12[ibin][itrack][icent] += flowArrayCOV2D->At( 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C13[ibin][itrack][icent] += flowArrayCOV2D->At( 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC1C14[ibin][itrack][icent] += flowArrayCOV2D->At( 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C3[ibin][itrack][icent] += flowArrayCOV2D->At( 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            sumC1C2[itrack][icent] += flowArrayCOV3D->At( 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC1C5[itrack][icent] += flowArrayCOV3D->At( 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC1C6[itrack][icent] += flowArrayCOV3D->At( 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumM111S11[itrack][icent] += flowArrayCOV3D->At( 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC1C7[itrack][icent] += flowArrayCOV3D->At( 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC1C8[itrack][icent] += flowArrayCOV3D->At( 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC2C5[itrack][icent] += flowArrayCOV3D->At( 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            sumC2C6[itrack][icent] += flowArrayCOV3D->At( 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumC2C4[ibin][itrack][icent] += flowArrayCOV3D->At( 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C9[ibin][itrack][icent] += flowArrayCOV3D->At( 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C10[ibin][itrack][icent] += flowArrayCOV3D->At( 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C11[ibin][itrack][icent] += flowArrayCOV3D->At( 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C12[ibin][itrack][icent] += flowArrayCOV3D->At( 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C13[ibin][itrack][icent] += flowArrayCOV3D->At( 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC2C14[ibin][itrack][icent] += flowArrayCOV3D->At( 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C4[ibin][itrack][icent] += flowArrayCOV3D->At( 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C5[ibin][itrack][icent] += flowArrayCOV3D->At( 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C6[ibin][itrack][icent] += flowArrayCOV3D->At( 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM111mp[ibin][itrack][icent] += flowArrayCOV3D->At( 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C7[ibin][itrack][icent] += flowArrayCOV3D->At( 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C8[ibin][itrack][icent] += flowArrayCOV3D->At( 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumM011mp[ibin][itrack][icent] += flowArrayCOV3D->At( 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C9[ibin][itrack][icent] += flowArrayCOV3D->At( 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C10[ibin][itrack][icent] += flowArrayCOV3D->At( 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C11[ibin][itrack][icent] += flowArrayCOV3D->At( 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C12[ibin][itrack][icent] += flowArrayCOV3D->At( 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C13[ibin][itrack][icent] += flowArrayCOV3D->At( 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC3C14[ibin][itrack][icent] += flowArrayCOV3D->At( 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C5[ibin][itrack][icent] += flowArrayCOV3D->At( 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C6[ibin][itrack][icent] += flowArrayCOV3D->At( 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C7[ibin][itrack][icent] += flowArrayCOV3D->At( 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C8[ibin][itrack][icent] += flowArrayCOV3D->At( 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C9[ibin][itrack][icent] += flowArrayCOV3D->At( 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C10[ibin][itrack][icent] += flowArrayCOV3D->At( 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C11[ibin][itrack][icent] += flowArrayCOV3D->At( 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C12[ibin][itrack][icent] += flowArrayCOV3D->At( 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C13[ibin][itrack][icent] += flowArrayCOV3D->At( 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC4C14[ibin][itrack][icent] += flowArrayCOV3D->At( 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC5C9[ibin][itrack][icent] += flowArrayCOV3D->At( 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC5C10[ibin][itrack][icent] += flowArrayCOV3D->At( 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC5C11[ibin][itrack][icent] += flowArrayCOV3D->At( 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                sumC5C12[ibin][itrack][icent] += flowArrayCOV3D->At( 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            sumC2C7[itrack][icent] += flowArrayCOV4D->At( 0 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC2C8[itrack][icent] += flowArrayCOV4D->At( 1 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC5C6[itrack][icent] += flowArrayCOV4D->At( 2 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC5C7[itrack][icent] += flowArrayCOV4D->At( 3 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC5C8[itrack][icent] += flowArrayCOV4D->At( 4 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC6C7[itrack][icent] += flowArrayCOV4D->At( 5 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC6C8[itrack][icent] += flowArrayCOV4D->At( 6 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            sumC7C8[itrack][icent] += flowArrayCOV4D->At( 7 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumC5C13[ibin][itrack][icent] += flowArrayCOV4D->At( 8 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC5C14[ibin][itrack][icent] += flowArrayCOV4D->At( 9 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C9[ibin][itrack][icent] += flowArrayCOV4D->At( 10 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C10[ibin][itrack][icent] += flowArrayCOV4D->At( 11 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C11[ibin][itrack][icent] += flowArrayCOV4D->At( 12 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C12[ibin][itrack][icent] += flowArrayCOV4D->At( 13 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C13[ibin][itrack][icent] += flowArrayCOV4D->At( 14 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC6C14[ibin][itrack][icent] += flowArrayCOV4D->At( 15 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumM111M011[ibin][itrack][icent] += flowArrayCOV4D->At( 16 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C9[ibin][itrack][icent] += flowArrayCOV4D->At( 17 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C10[ibin][itrack][icent] += flowArrayCOV4D->At( 18 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C11[ibin][itrack][icent] += flowArrayCOV4D->At( 19 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C12[ibin][itrack][icent] += flowArrayCOV4D->At( 20 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C13[ibin][itrack][icent] += flowArrayCOV4D->At( 21 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC7C14[ibin][itrack][icent] += flowArrayCOV4D->At( 22 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C9[ibin][itrack][icent] += flowArrayCOV4D->At( 23 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C10[ibin][itrack][icent] += flowArrayCOV4D->At( 24 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C11[ibin][itrack][icent] += flowArrayCOV4D->At( 25 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C12[ibin][itrack][icent] += flowArrayCOV4D->At( 26 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C13[ibin][itrack][icent] += flowArrayCOV4D->At( 27 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC8C14[ibin][itrack][icent] += flowArrayCOV4D->At( 28 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC9C10[ibin][itrack][icent] += flowArrayCOV4D->At( 29 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC9C11[ibin][itrack][icent] += flowArrayCOV4D->At( 30 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC9C12[ibin][itrack][icent] += flowArrayCOV4D->At( 31 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC9C13[ibin][itrack][icent] += flowArrayCOV4D->At( 32 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC9C14[ibin][itrack][icent] += flowArrayCOV4D->At( 33 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC10C11[ibin][itrack][icent] += flowArrayCOV4D->At( 34 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC10C12[ibin][itrack][icent] += flowArrayCOV4D->At( 35 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC10C13[ibin][itrack][icent] += flowArrayCOV4D->At( 36 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC10C14[ibin][itrack][icent] += flowArrayCOV4D->At( 37 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC11C12[ibin][itrack][icent] += flowArrayCOV4D->At( 38 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC11C13[ibin][itrack][icent] += flowArrayCOV4D->At( 39 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC11C14[ibin][itrack][icent] += flowArrayCOV4D->At( 40 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC12C13[ibin][itrack][icent] += flowArrayCOV4D->At( 41 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                sumC12C14[ibin][itrack][icent] += flowArrayCOV4D->At( 42 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
              }
          }
      }
        std::cout<<ifile+1<<std::endl;
        /*delete[] flowArrayD;
		delete[] flowArrayCOV1D;
		delete[] flowArrayCOV2D;
		delete[] flowArrayCOV3D;
		delete[] flowArrayCOV4D;*/
        input->Close();
        //delete[] input;
      }
    // TArrayD to Save flow variables
    TArrayD* flowArrayS = new TArrayD( (24 + 30*Nbins)*N_track*Ncentralities );
    TArrayD* flowArray2S = new TArrayD( N_track );
	TArrayD* flowArrayCOV1S = new TArrayD( (8 + 34*Nbins)*N_track*Ncentralities );
    TArrayD* flowArrayCOV2S = new TArrayD( (8 + 34*Nbins)*N_track*Ncentralities );
    TArrayD* flowArrayCOV3S = new TArrayD( (8 + 34*Nbins)*N_track*Ncentralities );
    TArrayD* flowArrayCOV4S = new TArrayD( (8 + 35*Nbins)*N_track*Ncentralities );
    // Save flow variables to TArrayD
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayS->AddAt(           sumS11[itrack][icent],  0 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(           sumM11[itrack][icent],  1 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(          sumM111[itrack][icent],  2 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(         sumM1111[itrack][icent],  3 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(         sumCorr2[itrack][icent],  4 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(         sumCorr4[itrack][icent],  5 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon1[itrack][icent],  6 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon2[itrack][icent],  7 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon5[itrack][icent],  8 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon6[itrack][icent],  9 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon7[itrack][icent], 10 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(        sumAddon8[itrack][icent], 11 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(    sumS11Squared[itrack][icent], 12 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(    sumM11Squared[itrack][icent], 13 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(   sumM111Squared[itrack][icent], 14 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(  sumM1111Squared[itrack][icent], 15 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(  sumCorr2Squared[itrack][icent], 16 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt(  sumCorr4Squared[itrack][icent], 17 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon1Squared[itrack][icent], 18 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon2Squared[itrack][icent], 19 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon5Squared[itrack][icent], 20 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon6Squared[itrack][icent], 21 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon7Squared[itrack][icent], 22 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArrayS->AddAt( sumAddon8Squared[itrack][icent], 23 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayS->AddAt(                  sumMp[ibin][itrack][icent], 24 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(                 sumM01[ibin][itrack][icent], 25 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(                sumM011[ibin][itrack][icent], 26 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(               sumM0111[ibin][itrack][icent], 27 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(        sumCorr2Reduced[ibin][itrack][icent], 28 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(        sumCorr4Reduced[ibin][itrack][icent], 29 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(              sumAddon3[ibin][itrack][icent], 30 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(              sumAddon4[ibin][itrack][icent], 31 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(              sumAddon9[ibin][itrack][icent], 32 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon10[ibin][itrack][icent], 33 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon11[ibin][itrack][icent], 34 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon12[ibin][itrack][icent], 35 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon13[ibin][itrack][icent], 36 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon14[ibin][itrack][icent], 37 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(             sumAddon15[ibin][itrack][icent], 38 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(           sumMpSquared[ibin][itrack][icent], 39 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(          sumM01Squared[ibin][itrack][icent], 40 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(         sumM011Squared[ibin][itrack][icent], 41 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(        sumM0111Squared[ibin][itrack][icent], 42 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt( sumCorr2ReducedSquared[ibin][itrack][icent], 43 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt( sumCorr4ReducedSquared[ibin][itrack][icent], 44 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(       sumAddon3Squared[ibin][itrack][icent], 45 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(       sumAddon4Squared[ibin][itrack][icent], 46 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(       sumAddon9Squared[ibin][itrack][icent], 47 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon10Squared[ibin][itrack][icent], 48 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon11Squared[ibin][itrack][icent], 49 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon12Squared[ibin][itrack][icent], 50 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon13Squared[ibin][itrack][icent], 51 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon14Squared[ibin][itrack][icent], 52 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArrayS->AddAt(      sumAddon15Squared[ibin][itrack][icent], 53 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
              }
          }
      }
	for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV1S->AddAt( sumM11S11[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C1[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C2[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C5[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C6[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumM11M111[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C7[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1S->AddAt( sumCorr2C8[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV1S->AddAt( sumM11mp[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C3[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C4[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM11M011[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C9[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C10[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C11[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C12[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C13[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2C14[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM01S11[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC1[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC2[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM01mp[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC3[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC4[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC5[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC6[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM111M01[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC7[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC8[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM01M011[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC9[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC10[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC11[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC12[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC13[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr2ReducedC14[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM1111mp[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr4C3[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr4C4[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumM1111M011[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumCorr4C9[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1S->AddAt( sumC13C14[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV2S->AddAt( sumM1111S11[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C1[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C2[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C5[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C6[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumM111M1111[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C7[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2S->AddAt( sumCorr4C8[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV2S->AddAt( sumCorr4C10[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4C11[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4C12[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4C13[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4C14[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumM0111S11[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC1[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC2[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumM0111mp[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC3[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC4[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC5[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC6[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumM111M0111[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC7[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC8[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumM011M0111[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC9[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC10[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC11[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC12[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC13[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumCorr4ReducedC14[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumS11mp[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C3[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C4[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumM011S11[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C9[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C10[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C11[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C12[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C13[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC1C14[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2S->AddAt( sumC2C3[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV3S->AddAt( sumC1C2[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC1C5[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC1C6[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumM111S11[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC1C7[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC1C8[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC2C5[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3S->AddAt( sumC2C6[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV3S->AddAt( sumC2C4[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C9[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C10[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C11[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C12[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C13[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC2C14[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C4[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C5[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C6[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumM111mp[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C7[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C8[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumM011mp[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C9[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C10[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C11[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C12[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C13[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC3C14[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C5[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C6[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C7[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C8[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C9[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C10[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C11[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C12[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C13[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC4C14[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC5C9[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC5C10[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC5C11[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3S->AddAt( sumC5C12[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV4S->AddAt( sumC2C7[itrack][icent], 0 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC2C8[itrack][icent], 1 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC5C6[itrack][icent], 2 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC5C7[itrack][icent], 3 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC5C8[itrack][icent], 4 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC6C7[itrack][icent], 5 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC6C8[itrack][icent], 6 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4S->AddAt( sumC7C8[itrack][icent], 7 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV4S->AddAt( sumC5C13[ibin][itrack][icent], 8 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC5C14[ibin][itrack][icent], 9 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C9[ibin][itrack][icent], 10 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C10[ibin][itrack][icent], 11 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C11[ibin][itrack][icent], 12 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C12[ibin][itrack][icent], 13 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C13[ibin][itrack][icent], 14 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC6C14[ibin][itrack][icent], 15 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumM111M011[ibin][itrack][icent], 16 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C9[ibin][itrack][icent], 17 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C10[ibin][itrack][icent], 18 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C11[ibin][itrack][icent], 19 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C12[ibin][itrack][icent], 20 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C13[ibin][itrack][icent], 21 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC7C14[ibin][itrack][icent], 22 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C9[ibin][itrack][icent], 23 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C10[ibin][itrack][icent], 24 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C11[ibin][itrack][icent], 25 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C12[ibin][itrack][icent], 26 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C13[ibin][itrack][icent], 27 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC8C14[ibin][itrack][icent], 28 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC9C10[ibin][itrack][icent], 29 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC9C11[ibin][itrack][icent], 30 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC9C12[ibin][itrack][icent], 31 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC9C13[ibin][itrack][icent], 32 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC9C14[ibin][itrack][icent], 33 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC10C11[ibin][itrack][icent], 34 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC10C12[ibin][itrack][icent], 35 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC10C13[ibin][itrack][icent], 36 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC10C14[ibin][itrack][icent], 37 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC11C12[ibin][itrack][icent], 38 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC11C13[ibin][itrack][icent], 39 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC11C14[ibin][itrack][icent], 40 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC12C13[ibin][itrack][icent], 41 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4S->AddAt( sumC12C14[ibin][itrack][icent], 42 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t itrack = 0; itrack < N_track; itrack++ )
      {
        flowArray2S->AddAt(multCounter[itrack],itrack);
      }
    // Reference Flows and their correction terms
    Double_t      v1_2[Nbins][N_track][Ncentralities],
    v1_4[Nbins][N_track][Ncentralities],
    v1_2Error[Nbins][N_track][Ncentralities],
    v1_4Error[Nbins][N_track][Ncentralities],
    reference2_1,
    reference2_2,
    reference2_3,
    reference4_1,
    reference4_2,
    reference4_3,
    reference4_4,
    correction1,
    correction2,
    correction5,
    correction6,
    correction7,
    correction8,
    reference2Error1,
    //reference2Error2,
    reference2Error3,
    reference4Error1,
    //reference4Error2,
    reference4Error3,
    correction1Error,
    correction2Error,
    correction5Error,
    correction6Error,
    correction7Error,
    correction8Error,
    covRef2Ref4,
    covRef2C1,
    covRef2C2,
    covRef2C5,
    covRef2C6,
    covRef2C7,
    covRef2C8,
    covRef4C1,
    covRef4C2,
    covRef4C5,
    covRef4C6,
    covRef4C7,
    covRef4C8,
    covC1C2,
    covC1C5,
    covC1C6,
    covC1C7,
    covC1C8,
    covC2C5,
    covC2C6,
    covC2C7,
    covC2C8,
    covC5C6,
    covC5C7,
    covC5C8,
    covC6C7,
    covC6C8,
    covC7C8,
    sign2,
    sign4,
    dr23r2,
    dr23c1,
    dr23c2,
    dr43r4,
    dr43r2,
    dr43c1,
    dr43c2,
    dr43c5,
    dr43c6,
    dr43c7,
    dr43c8;
    Double_t  differential2_1,
    differential2_2,
    differential4_1,
    differential4_2,
    correction3,
    correction4,
    correction9,
    correction10,
    correction11,
    correction12,
    correction13,
    correction14,
    differential2Error1,
    //differential2Error2,
    differential4Error1,
    //differential4Error2,
    correction3Error,
    correction4Error,
    correction9Error,
    correction10Error,
    correction11Error,
    correction12Error,
    correction13Error,
    correction14Error,
    covRef2Def2,
    covRef2Def4,
    covRef4Def2,
    covRef4Def4,
    covDef2Def4,
    covRef2C3,
    covRef2C4,
    covRef2C9,
    covRef2C10,
    covRef2C11,
    covRef2C12,
    covRef2C13,
    covRef2C14,
    covDef2C1,
    covDef2C2,
    covDef2C3,
    covDef2C4,
    covDef2C5,
    covDef2C6,
    covDef2C7,
    covDef2C8,
    covDef2C9,
    covDef2C10,
    covDef2C11,
    covDef2C12,
    covDef2C13,
    covDef2C14,
    covRef4C3,
    covRef4C4,
    covRef4C9,
    covRef4C10,
    covRef4C11,
    covRef4C12,
    covRef4C13,
    covRef4C14,
    covDef4C1,
    covDef4C2,
    covDef4C3,
    covDef4C4,
    covDef4C5,
    covDef4C6,
    covDef4C7,
    covDef4C8,
    covDef4C9,
    covDef4C10,
    covDef4C11,
    covDef4C12,
    covDef4C13,
    covDef4C14;
    Double_t   covC1C3,
    covC1C4,
    covC1C9,
    covC1C10,
    covC1C11,
    covC1C12,
    covC1C13,
    covC1C14,
    covC2C3,
    covC2C4,
    covC2C9,
    covC2C10,
    covC2C11,
    covC2C12,
    covC2C13,
    covC2C14,
    covC3C4,
    covC3C5,
    covC3C6,
    covC3C7,
    covC3C8,
    covC3C9,
    covC3C10,
    covC3C11,
    covC3C12,
    covC3C13,
    covC3C14,
    covC4C5,
    covC4C6,
    covC4C7,
    covC4C8,
    covC4C9,
    covC4C10,
    covC4C11,
    covC4C12,
    covC4C13,
    covC4C14,
    covC5C9,
    covC5C10,
    covC5C11,
    covC5C12,
    covC5C13,
    covC5C14,
    covC6C9,
    covC6C10,
    covC6C11,
    covC6C12,
    covC6C13,
    covC6C14,
    covC7C9,
    covC7C10,
    covC7C11,
    covC7C12,
    covC7C13,
    covC7C14,
    covC8C9,
    covC8C10,
    covC8C11,
    covC8C12,
    covC8C13,
    covC8C14,
    covC9C10,
    covC9C11,
    covC9C12,
    covC9C13,
    covC9C14,
    covC10C11,
    covC10C12,
    covC10C13,
    covC10C14,
    covC11C12,
    covC11C13,
    covC11C14,
    covC12C13,
    covC12C14,
    covC13C14,
    df2dr2,
    df2dd2,
    df2dc1,
    df2dc2,
    df2dc3,
    df2dc4,
    df4dr2,
    df4dd2,
    df4dr4,
    df4dd4,
    df4dc1,
    df4dc2,
    df4dc3,
    df4dc4,
    df4dc5,
    df4dc6,
    df4dc7,
    df4dc8,
    df4dc9,
    df4dc10,
    df4dc11,
    df4dc12,
    df4dc13,
    df4dc14;
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            if(multCounter[itrack] < 5) continue;
            reference2_1 = 0.;
            reference2_2 = 0.;
            reference2_3 = 0.;
            reference4_1 = 0.;
            reference4_2 = 0.;
            reference4_3 = 0.;
            reference4_4 = 0.;
            correction1 = 0.;
            correction2 = 0.;
            correction5 = 0.;
            correction6 = 0.;
            correction7 = 0.;
            correction8 = 0.;
            reference2Error1 = 0.;
            //reference2Error2 = 0.;
            reference2Error3 = 0.;
            reference4Error1 = 0.;
            //reference4Error2 = 0.;
            reference4Error3 = 0.;
            correction1Error = 0.;
            correction2Error = 0.;
            correction5Error = 0.;
            correction6Error = 0.;
            correction7Error = 0.;
            correction8Error = 0.;
            covRef2Ref4 = 0.;
            covRef2C1 = 0.;
            covRef2C2 = 0.;
            covRef2C5 = 0.;
            covRef2C6 = 0.;
            covRef2C7 = 0.;
            covRef2C8 = 0.;
            covRef4C1 = 0.;
            covRef4C2 = 0.;
            covRef4C5 = 0.;
            covRef4C6 = 0.;
            covRef4C7 = 0.;
            covRef4C8 = 0.;
            covC1C2 = 0.;
            covC1C5 = 0.;
            covC1C6 = 0.;
            covC1C7 = 0.;
            covC1C8 = 0.;
            covC2C5 = 0.;
            covC2C6 = 0.;
            covC2C7 = 0.;
            covC2C8 = 0.;
            covC5C6 = 0.;
            covC5C7 = 0.;
            covC5C8 = 0.;
            covC6C7 = 0.;
            covC6C8 = 0.;
            covC7C8 = 0.;
            sign2 = 0.;
            sign4 = 0.;
            dr23r2 = 0.;
            dr23c1 = 0.;
            dr23c2 = 0.;
            dr43r4 = 0.;
            dr43r2 = 0.;
            dr43c1 = 0.;
            dr43c2 = 0.;
            dr43c5 = 0.;
            dr43c6 = 0.;
            dr43c7 = 0.;
            dr43c8 = 0.;
            // get mean
            reference2_1 = (   sumM11[itrack][icent] != 0.0 ) ?  sumCorr2[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(reference2_1)) reference2_1 = 0.0;
            reference4_1 = ( sumM1111[itrack][icent] != 0.0 ) ?  sumCorr4[itrack][icent] / sumM1111[itrack][icent] : 0.0;
            if(!TMath::Finite(reference4_1)) reference4_1 = 0.0; if(reference2_1 == 0. || reference4_1 == 0.) continue;
            correction1 = (   sumS11[itrack][icent] != 0.0 ) ? sumAddon1[itrack][icent] /   sumS11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction1)) correction1 = 0.0;
            correction2 = (   sumS11[itrack][icent] != 0.0 ) ? sumAddon2[itrack][icent] /   sumS11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction2)) correction2 = 0.0;
            correction5 = (   sumM11[itrack][icent] != 0.0 ) ? sumAddon5[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction5)) correction5 = 0.0;
            correction6 = (   sumM11[itrack][icent] != 0.0 ) ? sumAddon6[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction6)) correction6 = 0.0;
            correction7 = (  sumM111[itrack][icent] != 0.0 ) ? sumAddon7[itrack][icent] /  sumM111[itrack][icent] : 0.0;
            if(!TMath::Finite(correction7)) correction7 = 0.0;
            correction8 = (  sumM111[itrack][icent] != 0.0 ) ? sumAddon8[itrack][icent] /  sumM111[itrack][icent] : 0.0;
            if(!TMath::Finite(correction8)) correction8 = 0.0;
            // get error on mean
            reference2Error1 = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumCorr2[itrack][icent],sumCorr2Squared[itrack][icent]);
            reference4Error1 = GetError(sumM1111[itrack][icent],sumM1111Squared[itrack][icent],sumCorr4[itrack][icent],sumCorr4Squared[itrack][icent]);
             if(reference2Error1 == 0. || reference4Error1 == 0.) continue;
            correction1Error = GetError(sumS11[itrack][icent],sumS11Squared[itrack][icent],sumAddon1[itrack][icent],sumAddon1Squared[itrack][icent]);
            correction2Error = GetError(sumS11[itrack][icent],sumS11Squared[itrack][icent],sumAddon2[itrack][icent],sumAddon2Squared[itrack][icent]);
            correction5Error = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumAddon5[itrack][icent],sumAddon5Squared[itrack][icent]);
            correction6Error = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumAddon6[itrack][icent],sumAddon6Squared[itrack][icent]);
            correction7Error = GetError(sumM111[itrack][icent],sumM111Squared[itrack][icent],sumAddon7[itrack][icent],sumAddon7Squared[itrack][icent]);
            correction8Error = GetError(sumM111[itrack][icent],sumM111Squared[itrack][icent],sumAddon8[itrack][icent],sumAddon8Squared[itrack][icent]);
            // Covariance terms
            covRef2Ref4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM1111[itrack][icent],sumCorr4[itrack][icent],
                                        sumM11M1111[itrack][icent],sumCorr2Corr4[itrack][icent]);
            covRef2C1 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                      sumM11S11[itrack][icent],sumCorr2C1[itrack][icent]);
            covRef2C2 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                      sumM11S11[itrack][icent],sumCorr2C2[itrack][icent]);
            covRef2C5 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                      sumM11Squared[itrack][icent],sumCorr2C5[itrack][icent]);
            covRef2C6 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                      sumM11Squared[itrack][icent],sumCorr2C6[itrack][icent]);
            covRef2C7 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                      sumM11M111[itrack][icent],sumCorr2C7[itrack][icent]);
            covRef2C8 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                      sumM11M111[itrack][icent],sumCorr2C8[itrack][icent]);
            covRef4C1 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                      sumM1111S11[itrack][icent],sumCorr4C1[itrack][icent]);
            covRef4C2 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                      sumM1111S11[itrack][icent],sumCorr4C2[itrack][icent]);
            covRef4C5 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                      sumM11M1111[itrack][icent],sumCorr4C5[itrack][icent]);
            covRef4C6 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                      sumM11M1111[itrack][icent],sumCorr4C6[itrack][icent]);
            covRef4C7 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                      sumM111M1111[itrack][icent],sumCorr4C7[itrack][icent]);
            covRef4C8 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                      sumM111M1111[itrack][icent],sumCorr4C8[itrack][icent]);
            covC1C2 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                    sumS11Squared[itrack][icent],sumC1C2[itrack][icent]);
            covC1C5 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                    sumM11S11[itrack][icent],sumC1C5[itrack][icent]);
            covC1C6 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11S11[itrack][icent],sumC1C6[itrack][icent]);
            covC1C7 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM111S11[itrack][icent],sumC1C7[itrack][icent]);
            covC1C8 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111S11[itrack][icent],sumC1C8[itrack][icent]);
            covC2C5 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                    sumM11S11[itrack][icent],sumC2C5[itrack][icent]);
            covC2C6 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11S11[itrack][icent],sumC2C6[itrack][icent]);
            covC2C7 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM111S11[itrack][icent],sumC2C7[itrack][icent]);
            covC2C8 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111S11[itrack][icent],sumC2C8[itrack][icent]);
            covC5C6 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11Squared[itrack][icent],sumC5C6[itrack][icent]);
            covC5C7 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM11M111[itrack][icent],sumC5C7[itrack][icent]);
            covC5C8 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM11M111[itrack][icent],sumC5C8[itrack][icent]);
            covC6C7 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM11M111[itrack][icent],sumC6C7[itrack][icent]);
            covC6C8 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM11M111[itrack][icent],sumC6C8[itrack][icent]);
            covC7C8 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111Squared[itrack][icent],sumC7C8[itrack][icent]);
            // Corrected Reference Flows
            reference2_2 = reference2_1 - correction1*correction1 - correction2*correction2;
            if(!TMath::Finite(reference2_2)) reference2_2 = 0.0;
            reference4_2 = reference4_1 - 2.0*reference2_1*reference2_1
            - 4.0*correction1*correction7
            + 4.0*correction2*correction8
            - correction5*correction5 - correction6*correction6
            + 4.0*correction5*( correction1*correction1 - correction2*correction2 )
            + 8.0*correction6*correction2*correction1
            + 8.0*reference2_1*( correction1*correction1 + correction2*correction2 )
            - 6.0*TMath::Power( correction1*correction1 + correction2*correction2, 2.0 );
            if(!TMath::Finite(reference4_2)) reference4_2 = 0.0;
            // prepare reference flow to be divided
            //sign2 = (reference2_2 > 0.)? 1.:-1.; sign4 = (reference4_2 > 0.)? 1.:-1.;
            sign2 = 1.; sign4 = -1.;
            reference2_3 = TMath::Sqrt( sign2*reference2_2 );
            if(!TMath::Finite(reference2_3)) reference2_3 = 0.0;
            reference4_3 =  TMath::Power( sign4*reference4_2, 3.0/4.0 );
            if(!TMath::Finite(reference4_3)) reference4_3 = 0.0; //if(reference2_3 == 0. || reference4_3 == 0.) continue;
            // differentiate QC2 reference flow
            dr23r2 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*1.;
            if(!TMath::Finite(dr23r2)) dr23r2 = 0.0;
            dr23c1 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*(-2.*correction1);
            if(!TMath::Finite(dr23c1)) dr23c1 = 0.0;
            dr23c2 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*(-2.*correction2);
            if(!TMath::Finite(dr23c2)) dr23c2 = 0.0;
            // error propagation
            reference2Error3 = TMath::Sqrt(TMath::Power(dr23r2,2.)*reference2Error1
                                           +TMath::Power(dr23c1,2.)*correction1Error
                                           +TMath::Power(dr23c2,2.)*correction2Error
                                           +2.*dr23r2*dr23c1*covRef2C1
                                           +2.*dr23r2*dr23c2*covRef2C2
                                           +2.*dr23c1*dr23c2*covC1C2
                                           );
            if(!TMath::Finite(reference2Error3) || reference2_3 == 0.) reference2Error3 = 0.0;
            // differentiate QC4 reference flow
            dr43r4 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*1.;
            if(!TMath::Finite(dr43r4)) dr43r4 = 0.0;
            dr43r2 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*reference2_1+8.*( correction1*correction1 + correction2*correction2 ));
            if(!TMath::Finite(dr43r2)) dr43r2 = 0.0;
            dr43c1 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*correction7+8.*correction5*correction1+8.*correction6*correction2+16.*reference2_1*correction1
                                                                        -24.*correction1*(correction1*correction1 + correction2*correction2));
            if(!TMath::Finite(dr43c1)) dr43c1 = 0.0;
            dr43c2 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(4.*correction8-8.*correction5*correction2+8.*correction6*correction1+16.*reference2_1*correction2
                                                                        -24.*correction2*(correction1*correction1 + correction2*correction2));
            if(!TMath::Finite(dr43c2)) dr43c2 = 0.0;
            dr43c5 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-2.*correction5+4.*( correction1*correction1 - correction2*correction2 ));
            if(!TMath::Finite(dr43c5)) dr43c5 = 0.0;
            dr43c6 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-2.*correction6+8.*correction2*correction1);
            if(!TMath::Finite(dr43c6)) dr43c6 = 0.0;
            dr43c7 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*correction1);
            if(!TMath::Finite(dr43c7)) dr43c7 = 0.0;
            dr43c8 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(4.*correction2);
            if(!TMath::Finite(dr43c8)) dr43c8 = 0.0;
            // error propagation
            reference4Error3 = TMath::Sqrt(TMath::Power(dr43r4,2.)*reference4Error1
                                           +TMath::Power(dr43r2,2.)*reference2Error1
                                           +TMath::Power(dr43c1,2.)*correction1Error
                                           +TMath::Power(dr43c2,2.)*correction2Error
                                           +TMath::Power(dr43c5,2.)*correction5Error
                                           +TMath::Power(dr43c6,2.)*correction6Error
                                           +TMath::Power(dr43c7,2.)*correction7Error
                                           +TMath::Power(dr43c8,2.)*correction8Error
                                           
                                           +2.*dr43r4*dr43r2*covRef2Ref4
                                           +2.*dr43r4*dr43c1*covRef4C1
                                           +2.*dr43r4*dr43c2*covRef4C2
                                           +2.*dr43r4*dr43c5*covRef4C5
                                           +2.*dr43r4*dr43c6*covRef4C6
                                           +2.*dr43r4*dr43c7*covRef4C7
                                           +2.*dr43r4*dr43c8*covRef4C8
                                           
                                           +2.*dr43r2*dr43c1*covRef2C1
                                           +2.*dr43r2*dr43c2*covRef2C2
                                           +2.*dr43r2*dr43c5*covRef2C5
                                           +2.*dr43r2*dr43c6*covRef2C6
                                           +2.*dr43r2*dr43c7*covRef2C7
                                           +2.*dr43r2*dr43c8*covRef2C8
                                           
                                           +2.*dr43c1*dr43c2*covC1C2
                                           +2.*dr43c1*dr43c5*covC1C5
                                           +2.*dr43c1*dr43c6*covC1C6
                                           +2.*dr43c1*dr43c7*covC1C7
                                           +2.*dr43c1*dr43c8*covC1C8
                                           
                                           +2.*dr43c2*dr43c5*covC2C5
                                           +2.*dr43c2*dr43c6*covC2C6
                                           +2.*dr43c2*dr43c7*covC2C7
                                           +2.*dr43c2*dr43c8*covC2C8
                                           
                                           +2.*dr43c5*dr43c6*covC5C6
                                           +2.*dr43c5*dr43c7*covC5C7
                                           +2.*dr43c5*dr43c8*covC5C8
                                           
                                           +2.*dr43c6*dr43c7*covC6C7
                                           +2.*dr43c6*dr43c8*covC6C8
                                           
                                           +2.*dr43c7*dr43c8*covC7C8
                                           );
            if(!TMath::Finite(reference4Error3) || reference4_3 == 0.) reference4Error3 = 0.0; //if(reference2Error3 == 0. || reference4Error3 == 0.) continue;
            //hr2->SetBinContent(itrack+1,reference2_3);hr2->SetBinError(itrack+1,reference2Error3);
            // QC4 reference flow
            reference4_4 = TMath::Power( sign4*reference4_2, 1.0/4.0 );
            if(!TMath::Finite(reference4_4)) reference4_4 = 0.0;
            //hr4->SetBinContent(itrack+1,reference4_4);hr2->SetBinError(itrack+1,reference4Error3);
            // compute differential flows
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                v1_2[ibin][itrack][icent] = 0.;
                v1_2Error[ibin][itrack][icent] = 0.;
                v1_4[ibin][itrack][icent] = 0.;
                v1_4Error[ibin][itrack][icent] = 0.;
                differential2_1 = 0.;
                differential2_2 = 0.;
                differential4_1 = 0.;
                differential4_2 = 0.;
                correction3 = 0.;
                correction4 = 0.;
                correction9 = 0.;
                correction10 = 0.;
                correction11 = 0.;
                correction12 = 0.;
                correction13 = 0.;
                correction14 = 0.;
                differential2Error1 = 0.;
                //differential2Error2 = 0.;
                differential4Error1 = 0.;
                //differential4Error2 = 0.;
                correction3Error = 0.;
                correction4Error = 0.;
                correction9Error = 0.;
                correction10Error = 0.;
                correction11Error = 0.;
                correction12Error = 0.;
                correction13Error = 0.;
                correction14Error = 0.;
                covRef2Def2 = 0.;
                covRef2Def4 = 0.;
                covRef4Def2 = 0.;
                covRef4Def4 = 0.;
                covDef2Def4 = 0.;
                covRef2C3 = 0.;
                covRef2C4 = 0.;
                covRef2C9 = 0.;
                covRef2C10 = 0.;
                covRef2C11 = 0.;
                covRef2C12 = 0.;
                covRef2C13 = 0.;
                covRef2C14 = 0.;
                covDef2C1 = 0.;
                covDef2C2 = 0.;
                covDef2C3 = 0.;
                covDef2C4 = 0.;
                covDef2C5 = 0.;
                covDef2C6 = 0.;
                covDef2C7 = 0.;
                covDef2C8 = 0.;
                covDef2C9 = 0.;
                covDef2C10 = 0.;
                covDef2C11 = 0.;
                covDef2C12 = 0.;
                covDef2C13 = 0.;
                covDef2C14 = 0.;
                covRef4C3 = 0.;
                covRef4C4 = 0.;
                covRef4C9 = 0.;
                covRef4C10 = 0.;
                covRef4C11 = 0.;
                covRef4C12 = 0.;
                covRef4C13 = 0.;
                covRef4C14 = 0.;
                covDef4C1 = 0.;
                covDef4C2 = 0.;
                covDef4C3 = 0.;
                covDef4C4 = 0.;
                covDef4C5 = 0.;
                covDef4C6 = 0.;
                covDef4C7 = 0.;
                covDef4C8 = 0.;
                covDef4C9 = 0.;
                covDef4C10 = 0.;
                covDef4C11 = 0.;
                covDef4C12 = 0.;
                covDef4C13 = 0.;
                covDef4C14 = 0.;
                covC1C3 = 0.;
                covC1C4 = 0.;
                covC1C9 = 0.;
                covC1C10 = 0.;
                covC1C11 = 0.;
                covC1C12 = 0.;
                covC1C13 = 0.;
                covC1C14 = 0.;
                covC2C3 = 0.;
                covC2C4 = 0.;
                covC2C9 = 0.;
                covC2C10 = 0.;
                covC2C11 = 0.;
                covC2C12 = 0.;
                covC2C13 = 0.;
                covC2C14 = 0.;
                covC3C4 = 0.;
                covC3C5 = 0.;
                covC3C6 = 0.;
                covC3C7 = 0.;
                covC3C8 = 0.;
                covC3C9 = 0.;
                covC3C10 = 0.;
                covC3C11 = 0.;
                covC3C12 = 0.;
                covC3C13 = 0.;
                covC3C14 = 0.;
                covC4C5 = 0.;
                covC4C6 = 0.;
                covC4C7 = 0.;
                covC4C8 = 0.;
                covC4C9 = 0.;
                covC4C10 = 0.;
                covC4C11 = 0.;
                covC4C12 = 0.;
                covC4C13 = 0.;
                covC4C14 = 0.;
                covC5C9 = 0.;
                covC5C10 = 0.;
                covC5C11 = 0.;
                covC5C12 = 0.;
                covC5C13 = 0.;
                covC5C14 = 0.;
                covC6C9 = 0.;
                covC6C10 = 0.;
                covC6C11 = 0.;
                covC6C12 = 0.;
                covC6C13 = 0.;
                covC6C14 = 0.;
                covC7C9 = 0.;
                covC7C10 = 0.;
                covC7C11 = 0.;
                covC7C12 = 0.;
                covC7C13 = 0.;
                covC7C14 = 0.;
                covC8C9 = 0.;
                covC8C10 = 0.;
                covC8C11 = 0.;
                covC8C12 = 0.;
                covC8C13 = 0.;
                covC8C14 = 0.;
                covC9C10 = 0.;
                covC9C11 = 0.;
                covC9C12 = 0.;
                covC9C13 = 0.;
                covC9C14 = 0.;
                covC10C11 = 0.;
                covC10C12 = 0.;
                covC10C13 = 0.;
                covC10C14 = 0.;
                covC11C12 = 0.;
                covC11C13 = 0.;
                covC11C14 = 0.;
                covC12C13 = 0.;
                covC12C14 = 0.;
                covC13C14 = 0.;
                df2dr2 = 0.;
                df2dd2 = 0.;
                df2dc1 = 0.;
                df2dc2 = 0.;
                df2dc3 = 0.;
                df2dc4 = 0.;
                df4dr2 = 0.;
                df4dd2 = 0.;
                df4dr4 = 0.;
                df4dd4 = 0.;
                df4dc1 = 0.;
                df4dc2 = 0.;
                df4dc3 = 0.;
                df4dc4 = 0.;
                df4dc5 = 0.;
                df4dc6 = 0.;
                df4dc7 = 0.;
                df4dc8 = 0.;
                df4dc9 = 0.;
                df4dc10 = 0.;
                df4dc11 = 0.;
                df4dc12 = 0.;
                df4dc13 = 0.;
                df4dc14= 0.;
                // Differential Flows and their correction terms
                differential2_1 = (   sumM01[ibin][itrack][icent] != 0.0 ) ? sumCorr2Reduced[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(differential2_1)) differential2_1 = 0.0;
                differential4_1 = ( sumM0111[ibin][itrack][icent] != 0.0 ) ? sumCorr4Reduced[ibin][itrack][icent] / sumM0111[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(differential4_1)) differential4_1 = 0.0; if(differential2_1 == 0. || differential4_1 == 0.) continue;
                correction3 = (    sumMp[ibin][itrack][icent] != 0.0 ) ?       sumAddon3[ibin][itrack][icent] /    sumMp[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction3)) correction3 = 0.0;
                correction4 = (    sumMp[ibin][itrack][icent] != 0.0 ) ?       sumAddon4[ibin][itrack][icent] /    sumMp[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction4)) correction4 = 0.0;
                correction9 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?       sumAddon9[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction9)) correction9 = 0.0;
                correction10 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon10[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction10)) correction10 = 0.0;
                correction11 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon11[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction11)) correction11 = 0.0;
                correction12 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon12[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction12)) correction12 = 0.0;
                correction13 = (   sumM01[ibin][itrack][icent] != 0.0 ) ?      sumAddon13[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction13)) correction13 = 0.0;
                correction14 = (   sumM01[ibin][itrack][icent] != 0.0 ) ?      sumAddon14[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction14)) correction14 = 0.0;
                // error on mean
                differential2Error1 = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],
                                               sumCorr2Reduced[ibin][itrack][icent],sumCorr2ReducedSquared[ibin][itrack][icent]);
                differential4Error1 = GetError(sumM0111[ibin][itrack][icent],sumM0111Squared[ibin][itrack][icent],
                                               sumCorr4Reduced[ibin][itrack][icent],sumCorr4ReducedSquared[ibin][itrack][icent]);
                 if(differential2Error1 == 0. || differential4Error1 == 0.) continue;
                correction3Error = GetError(sumMp[ibin][itrack][icent],sumMpSquared[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumAddon3Squared[ibin][itrack][icent]);
                correction4Error = GetError(sumMp[ibin][itrack][icent],sumMpSquared[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumAddon4Squared[ibin][itrack][icent]);
                correction9Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumAddon9Squared[ibin][itrack][icent]);
                correction10Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumAddon10Squared[ibin][itrack][icent]);
                correction11Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumAddon11Squared[ibin][itrack][icent]);
                correction12Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumAddon12Squared[ibin][itrack][icent]);
                correction13Error = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],sumAddon13Squared[ibin][itrack][icent]);
                correction14Error = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],sumAddon14Squared[ibin][itrack][icent]);
                // Covariance terms
                covRef2Def2 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],
                                            sumM11M01[ibin][itrack][icent],sumCorr2Corr2Reduced[ibin][itrack][icent]);
                covRef2Def4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM11M0111[ibin][itrack][icent],sumCorr2Corr4Reduced[ibin][itrack][icent]);
                covRef4Def2 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],
                                            sumM1111M01[ibin][itrack][icent],sumCorr4Corr2Reduced[ibin][itrack][icent]);
                covRef4Def4 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM1111M0111[ibin][itrack][icent],sumCorr4Corr4Reduced[ibin][itrack][icent]);
                covDef2Def4 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM01M0111[ibin][itrack][icent],sumCorr2ReducedCorr4Reduced[ibin][itrack][icent]);
                
                covRef2C3 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM11mp[ibin][itrack][icent],sumCorr2C3[ibin][itrack][icent]);
                covRef2C4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM11mp[ibin][itrack][icent],sumCorr2C4[ibin][itrack][icent]);
                covRef2C9 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM11M011[ibin][itrack][icent],sumCorr2C9[ibin][itrack][icent]);
                covRef2C10 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C10[ibin][itrack][icent]);
                covRef2C11 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C11[ibin][itrack][icent]);
                covRef2C12 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C12[ibin][itrack][icent]);
                covRef2C13 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM11M01[ibin][itrack][icent],sumCorr2C13[ibin][itrack][icent]);
                covRef2C14 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM11M01[ibin][itrack][icent],sumCorr2C14[ibin][itrack][icent]);
                
                covRef4C3 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM1111mp[ibin][itrack][icent],sumCorr4C3[ibin][itrack][icent]);
                covRef4C4 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM1111mp[ibin][itrack][icent],sumCorr4C4[ibin][itrack][icent]);
                covRef4C9 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM1111M011[ibin][itrack][icent],sumCorr4C9[ibin][itrack][icent]);
                covRef4C10 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C10[ibin][itrack][icent]);
                covRef4C11 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C11[ibin][itrack][icent]);
                covRef4C12 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C12[ibin][itrack][icent]);
                covRef4C13 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM1111M01[ibin][itrack][icent],sumCorr4C13[ibin][itrack][icent]);
                covRef4C14 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM1111M01[ibin][itrack][icent],sumCorr4C14[ibin][itrack][icent]);
                
                covDef2C1 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                          sumM01S11[ibin][itrack][icent],sumCorr2ReducedC1[ibin][itrack][icent]);
                covDef2C2 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                          sumM01S11[ibin][itrack][icent],sumCorr2ReducedC2[ibin][itrack][icent]);
                covDef2C3 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM01mp[ibin][itrack][icent],sumCorr2ReducedC3[ibin][itrack][icent]);
                covDef2C4 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM01mp[ibin][itrack][icent],sumCorr2ReducedC4[ibin][itrack][icent]);
                covDef2C5 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                          sumM11M01[ibin][itrack][icent],sumCorr2ReducedC5[ibin][itrack][icent]);
                covDef2C6 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                          sumM11M01[ibin][itrack][icent],sumCorr2ReducedC6[ibin][itrack][icent]);
                covDef2C7 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                          sumM111M01[ibin][itrack][icent],sumCorr2ReducedC7[ibin][itrack][icent]);
                covDef2C8 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                          sumM111M01[ibin][itrack][icent],sumCorr2ReducedC8[ibin][itrack][icent]);
                covDef2C9 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumCorr2ReducedC9[ibin][itrack][icent]);
                covDef2C10 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC10[ibin][itrack][icent]);
                covDef2C11 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC11[ibin][itrack][icent]);
                covDef2C12 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC12[ibin][itrack][icent]);
                covDef2C13 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM01Squared[ibin][itrack][icent],sumCorr2ReducedC13[ibin][itrack][icent]);
                covDef2C14 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM01Squared[ibin][itrack][icent],sumCorr2ReducedC14[ibin][itrack][icent]);
                
                covDef4C1 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                          sumM0111S11[ibin][itrack][icent],sumCorr4ReducedC1[ibin][itrack][icent]);
                covDef4C2 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                          sumM0111S11[ibin][itrack][icent],sumCorr4ReducedC2[ibin][itrack][icent]);
                covDef4C3 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM0111mp[ibin][itrack][icent],sumCorr4ReducedC3[ibin][itrack][icent]);
                covDef4C4 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM0111mp[ibin][itrack][icent],sumCorr4ReducedC4[ibin][itrack][icent]);
                covDef4C5 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                          sumM11M0111[ibin][itrack][icent],sumCorr4ReducedC5[ibin][itrack][icent]);
                covDef4C6 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                          sumM11M0111[ibin][itrack][icent],sumCorr4ReducedC6[ibin][itrack][icent]);
                covDef4C7 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                          sumM111M0111[ibin][itrack][icent],sumCorr4ReducedC7[ibin][itrack][icent]);
                covDef4C8 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                          sumM111M0111[ibin][itrack][icent],sumCorr4ReducedC8[ibin][itrack][icent]);
                covDef4C9 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC9[ibin][itrack][icent]);
                covDef4C10 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC10[ibin][itrack][icent]);
                covDef4C11 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC11[ibin][itrack][icent]);
                covDef4C12 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC12[ibin][itrack][icent]);
                covDef4C13 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM01M0111[ibin][itrack][icent],sumCorr4ReducedC13[ibin][itrack][icent]);
                covDef4C14 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM01M0111[ibin][itrack][icent],sumCorr4ReducedC14[ibin][itrack][icent]);
                
                covC1C3 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC1C3[ibin][itrack][icent]);
                covC1C4 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC1C4[ibin][itrack][icent]);
                covC1C9 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011S11[ibin][itrack][icent],sumC1C9[ibin][itrack][icent]);
                covC1C10 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C10[ibin][itrack][icent]);
                covC1C11 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C11[ibin][itrack][icent]);
                covC1C12 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C12[ibin][itrack][icent]);
                covC1C13 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC1C13[ibin][itrack][icent]);
                covC1C14 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC1C14[ibin][itrack][icent]);
                
                covC2C3 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC2C3[ibin][itrack][icent]);
                covC2C4 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC2C4[ibin][itrack][icent]);
                covC2C9 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011S11[ibin][itrack][icent],sumC2C9[ibin][itrack][icent]);
                covC2C10 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C10[ibin][itrack][icent]);
                covC2C11 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C11[ibin][itrack][icent]);
                covC2C12 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C12[ibin][itrack][icent]);
                covC2C13 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC2C13[ibin][itrack][icent]);
                covC2C14 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC2C14[ibin][itrack][icent]);
                
                covC3C4 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumMpSquared[ibin][itrack][icent],sumC3C4[ibin][itrack][icent]);
                covC3C5 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC3C5[ibin][itrack][icent]);
                covC3C6 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC3C6[ibin][itrack][icent]);
                covC3C7 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC3C7[ibin][itrack][icent]);
                covC3C8 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC3C8[ibin][itrack][icent]);
                covC3C9 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011mp[ibin][itrack][icent],sumC3C9[ibin][itrack][icent]);
                covC3C10 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C10[ibin][itrack][icent]);
                covC3C11 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C11[ibin][itrack][icent]);
                covC3C12 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C12[ibin][itrack][icent]);
                covC3C13 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC3C13[ibin][itrack][icent]);
                covC3C14 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC3C14[ibin][itrack][icent]);
                
                covC4C5 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC4C5[ibin][itrack][icent]);
                covC4C6 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC4C6[ibin][itrack][icent]);
                covC4C7 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC4C7[ibin][itrack][icent]);
                covC4C8 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC4C8[ibin][itrack][icent]);
                covC4C9 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011mp[ibin][itrack][icent],sumC4C9[ibin][itrack][icent]);
                covC4C10 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C10[ibin][itrack][icent]);
                covC4C11 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C11[ibin][itrack][icent]);
                covC4C12 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C12[ibin][itrack][icent]);
                covC4C13 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC4C13[ibin][itrack][icent]);
                covC4C14 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC4C14[ibin][itrack][icent]);
                
                covC5C9 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM11M011[ibin][itrack][icent],sumC5C9[ibin][itrack][icent]);
                covC5C10 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C10[ibin][itrack][icent]);
                covC5C11 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C11[ibin][itrack][icent]);
                covC5C12 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C12[ibin][itrack][icent]);
                covC5C13 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC5C13[ibin][itrack][icent]);
                covC5C14 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC5C14[ibin][itrack][icent]);
                
                covC6C9 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM11M011[ibin][itrack][icent],sumC6C9[ibin][itrack][icent]);
                covC6C10 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C10[ibin][itrack][icent]);
                covC6C11 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C11[ibin][itrack][icent]);
                covC6C12 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C12[ibin][itrack][icent]);
                covC6C13 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC6C13[ibin][itrack][icent]);
                covC6C14 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC6C14[ibin][itrack][icent]);
                
                covC7C9 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM111M011[ibin][itrack][icent],sumC7C9[ibin][itrack][icent]);
                covC7C10 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C10[ibin][itrack][icent]);
                covC7C11 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C11[ibin][itrack][icent]);
                covC7C12 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C12[ibin][itrack][icent]);
                covC7C13 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC7C13[ibin][itrack][icent]);
                covC7C14 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC7C14[ibin][itrack][icent]);
                
                covC8C9 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM111M011[ibin][itrack][icent],sumC8C9[ibin][itrack][icent]);
                covC8C10 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C10[ibin][itrack][icent]);
                covC8C11 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C11[ibin][itrack][icent]);
                covC8C12 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C12[ibin][itrack][icent]);
                covC8C13 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC8C13[ibin][itrack][icent]);
                covC8C14 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC8C14[ibin][itrack][icent]);
                
                covC9C10 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C10[ibin][itrack][icent]);
                covC9C11 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C11[ibin][itrack][icent]);
                covC9C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C12[ibin][itrack][icent]);
                covC9C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01M011[ibin][itrack][icent],sumC9C13[ibin][itrack][icent]);
                covC9C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01M011[ibin][itrack][icent],sumC9C14[ibin][itrack][icent]);
                
                covC10C11 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC10C11[ibin][itrack][icent]);
                covC10C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC10C12[ibin][itrack][icent]);
                covC10C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC10C13[ibin][itrack][icent]);
                covC10C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC10C14[ibin][itrack][icent]);
                
                covC11C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC11C12[ibin][itrack][icent]);
                covC11C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC11C13[ibin][itrack][icent]);
                covC11C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC11C14[ibin][itrack][icent]);
                
                covC12C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC12C13[ibin][itrack][icent]);
                covC12C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC12C14[ibin][itrack][icent]);
                
                covC13C14 = GetCovariance(sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01Squared[ibin][itrack][icent],sumC13C14[ibin][itrack][icent]);
                // Corrected Differential Flows
                differential2_2 = differential2_1 - correction3*correction1 - correction4*correction2;
                if(!TMath::Finite(differential2_2)) differential2_2 = 0.0;
                differential4_2 = differential4_1 - 2.0*differential2_1*reference2_1
                - correction3*correction7
                + correction4*correction8
                - correction1*correction9
                + correction2*correction10
                - 2.0*correction1*correction11
                - 2.0*correction2*correction12
                - correction13*correction5
                - correction14*correction6
                + 2.0*correction5*( correction3*correction1 - correction4*correction2 )
                + 2.0*correction6*( correction3*correction2 + correction4*correction1 )
                + 4.0*reference2_1*( correction3*correction1 + correction4*correction2 )
                + 2.0*correction13*( correction1*correction1 - correction2*correction2 )
                + 4.0*correction14*correction1*correction2
                + 4.0*differential2_1*( correction1*correction1 + correction2*correction2 )
                - 6.0*( correction1*correction1 - correction2*correction2 )*( correction3*correction1
                                                                             - correction4*correction2 )
                - 12.0*correction1*correction2*( correction4*correction1 + correction3*correction2 );
                if(!TMath::Finite(differential4_2)) differential4_2 = 0.0;
                // Final flows
                v1_2[ibin][itrack][icent] = ( reference2_3 > 0.0 ) ? sign2*differential2_2 / reference2_3 : 0.0;
                if(!TMath::Finite(v1_2[ibin][itrack][icent])) v1_2[ibin][itrack][icent] = 0.0;
                v1_4[ibin][itrack][icent] = ( reference4_3 > 0.0 ) ? sign4*differential4_2 / reference4_3 : 0.0;
                if(!TMath::Finite(v1_4[ibin][itrack][icent])) v1_4[ibin][itrack][icent] = 0.0;
                // differentiate QC2 differential flow
                df2dr2 = 1.0/(sign2*reference2_2)*(- (sign2*differential2_2)*(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0) ) );
                if(!TMath::Finite(df2dr2)) df2dr2 = 0.0;
                df2dd2 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0) );
                if(!TMath::Finite(df2dd2)) df2dd2 = 0.0;
                df2dc1 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction3) - (sign2*differential2_2)
                                                   *(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0)*(-2.0*correction1) ) );
                if(!TMath::Finite(df2dc1)) df2dc1 = 0.0;
                df2dc2 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction4) - (sign2*differential2_2)
                                                   *(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0)*(-2.0*correction2) ) );
                if(!TMath::Finite(df2dc2)) df2dc2 = 0.0;
                df2dc3 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction1) );
                if(!TMath::Finite(df2dc3)) df2dc3 = 0.0;
                df2dc4 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction2) );
                if(!TMath::Finite(df2dc4)) df2dc4 = 0.0;
                // error propagation
                v1_2Error[ibin][itrack][icent] = TMath::Sqrt( TMath::Power(df2dr2,2.0)*reference2Error1
                                                             + TMath::Power(df2dd2,2.0)*differential2Error1
                                                             + TMath::Power(df2dc1,2.0)*correction1Error
                                                             + TMath::Power(df2dc2,2.0)*correction2Error
                                                             + TMath::Power(df2dc3,2.0)*correction3Error
                                                             + TMath::Power(df2dc4,2.0)*correction4Error
                                                             
                                                             + 2.0*df2dr2*df2dd2*covRef2Def2
                                                             + 2.0*df2dr2*df2dc1*covRef2C1
                                                             + 2.0*df2dr2*df2dc2*covRef2C2
                                                             + 2.0*df2dr2*df2dc3*covRef2C3
                                                             + 2.0*df2dr2*df2dc4*covRef2C4
                                                             
                                                             + 2.0*df2dd2*df2dc1*covDef2C1
                                                             + 2.0*df2dd2*df2dc2*covDef2C2
                                                             + 2.0*df2dd2*df2dc3*covDef2C3
                                                             + 2.0*df2dd2*df2dc4*covDef2C4
                                                             
                                                             + 2.0*df2dc1*df2dc2*covC1C2
                                                             + 2.0*df2dc1*df2dc3*covC1C3
                                                             + 2.0*df2dc1*df2dc4*covC1C4
                                                             
                                                             + 2.0*df2dc2*df2dc3*covC2C3
                                                             + 2.0*df2dc2*df2dc4*covC2C4
                                                             
                                                             + 2.0*df2dc3*df2dc4*covC3C4
                                                             );
                if(!TMath::Finite(v1_2Error[ibin][itrack][icent]) || df2dr2*reference2Error1 == 0. || df2dd2*differential2Error1 == 0. || v1_2[ibin][itrack][icent] == 0.)
                    v1_2Error[ibin][itrack][icent] = 0.0;
                // differentiate QC4 differential flow
                df4dr2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*differential2_1
                                                                                                                     + 4.0*(correction3*correction1 + correction4*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*reference2_1
                                                                                                                                                      + 8.0*(correction1*correction1
                                                                                                                                                             + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dr2)) df4dr2 = 0.0;
                df4dd2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*reference2_1
                                                                                                                     + 4.0*(correction1*correction1 + correction2*correction2) ) );
                if(!TMath::Finite(df4dd2)) df4dd2 = 0.0;
                df4dr4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0) ) );
                if(!TMath::Finite(df4dr4)) df4dr4 = 0.0;
                df4dd4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( sign4*TMath::Power(sign4*reference4_2,3.0/4.0) );
                if(!TMath::Finite(df4dd4)) df4dd4 = 0.0;
                df4dc1 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction9 - 2.0*correction11
                                                                                                                     + 2.0*correction3*correction5
                                                                                                                     + 2.0*correction4*correction6 + 4.0*correction3*reference2_1
                                                                                                                     + 4.0*correction13*correction1 + 4.0*correction14*correction2
                                                                                                                     + 8.0*differential2_1*correction1
                                                                                                                     - 12.0*correction1*(correction3*correction1 - correction4*correction2)
                                                                                                                     - 6.0*correction3*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*(2.0*correction1*correction2*correction4
                                                                                                                             + correction3*correction2*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*correction7
                                                                                                                                                      + 8.0*correction1*correction5
                                                                                                                                                      + 8.0*correction6*correction2
                                                                                                                                                      + 16.0*reference2_1*correction1
                                                                                                                                                      - 24.0*correction1
                                                                                                                                                      *(correction1*correction1
                                                                                                                                                        + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc1)) df4dc1 = 0.0;
                df4dc2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(correction10 - 2.0*correction12
                                                                                                                     - 2.0*correction4*correction5
                                                                                                                     + 2.0*correction3*correction6 + 4.0*correction4*reference2_1
                                                                                                                     - 4.0*correction13*correction2 + 4.0*correction14*correction1
                                                                                                                     + 8.0*differential2_1*correction2
                                                                                                                     + 12.0*correction2*(correction3*correction1 - correction4*correction2)
                                                                                                                     + 6.0*correction4*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*(2.0*correction2*correction1*correction3
                                                                                                                             + correction4*correction1*correction1) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(4.0*correction8
                                                                                                                                                      - 8.0*correction2*correction5
                                                                                                                                                      + 8.0*correction6*correction1
                                                                                                                                                      + 16.0*reference2_1*correction2
                                                                                                                                                      - 24.0*correction2
                                                                                                                                                      *(correction1*correction1
                                                                                                                                                        + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc2)) df4dc2 = 0.0;
                df4dc3 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction7 + 2.0*correction5*correction1 + 2.0*correction6*correction2
                                                                                                                     + 4.0*correction1*reference2_1
                                                                                                                     - 6.0*correction1*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*correction1*correction2*correction2) );
                if(!TMath::Finite(df4dc3)) df4dc3 = 0.0;
                df4dc4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(correction8 - 2.0*correction5*correction2 + 2.0*correction6*correction1
                                                                                                                     + 4.0*correction2*reference2_1
                                                                                                                     + 6.0*correction2*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*correction1*correction1*correction2) );
                if(!TMath::Finite(df4dc4)) df4dc4 = 0.0;
                df4dc5 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction13 + 2.0*(correction3*correction1
                                                                                                                                          - correction4*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-2.0*correction5
                                                                                                                                                      + 4.0*(correction1*correction1
                                                                                                                                                             - correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc5)) df4dc5 = 0.0;
                df4dc6 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction14 + 2.0*(correction3*correction2
                                                                                                                                          + correction4*correction1) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-2.0*correction6
                                                                                                                                                      +8.0*correction1*correction2 ) ) );
                if(!TMath::Finite(df4dc6)) df4dc6 = 0.0;
                df4dc7 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction3)
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*correction1) ) );
                if(!TMath::Finite(df4dc7)) df4dc7 = 0.0;
                df4dc8 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*correction4
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*4.0*correction2 ) );
                if(!TMath::Finite(df4dc8)) df4dc8 = 0.0;
                df4dc9 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction1) );
                if(!TMath::Finite(df4dc9)) df4dc9 = 0.0;
                df4dc10 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*correction2 );
                if(!TMath::Finite(df4dc10)) df4dc10 = 0.0;
                df4dc11 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*correction1) );
                if(!TMath::Finite(df4dc11)) df4dc11 = 0.0;
                df4dc12 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*correction2) );
                if(!TMath::Finite(df4dc12)) df4dc12 = 0.0;
                df4dc13 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction5 + 2.0*(correction1*correction1
                                                                                                                                          - correction2*correction2) ) );
                if(!TMath::Finite(df4dc13)) df4dc13 = 0.0;
                df4dc14 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction6 + 4.0*correction1*correction2 ) );
                if(!TMath::Finite(df4dc14)) df4dc14 = 0.0;
                // error propagation
                v1_4Error[ibin][itrack][icent] = TMath::Sqrt( TMath::Power(df4dr2,2.0)*reference2Error1
                                                             + TMath::Power(df4dd2,2.0)*differential2Error1
                                                             + TMath::Power(df4dr4,2.0)*reference4Error1
                                                             + TMath::Power(df4dd4,2.0)*differential4Error1
                                                             + TMath::Power(df4dc1,2.0)*correction1Error
                                                             + TMath::Power(df4dc2,2.0)*correction2Error
                                                             + TMath::Power(df4dc3,2.0)*correction3Error
                                                             + TMath::Power(df4dc4,2.0)*correction4Error
                                                             + TMath::Power(df4dc5,2.0)*correction5Error
                                                             + TMath::Power(df4dc6,2.0)*correction6Error
                                                             + TMath::Power(df4dc7,2.0)*correction7Error
                                                             + TMath::Power(df4dc8,2.0)*correction8Error
                                                             + TMath::Power(df4dc9,2.0)*correction9Error
                                                             + TMath::Power(df4dc10,2.0)*correction10Error
                                                             + TMath::Power(df4dc11,2.0)*correction11Error
                                                             + TMath::Power(df4dc12,2.0)*correction12Error
                                                             + TMath::Power(df4dc13,2.0)*correction13Error
                                                             + TMath::Power(df4dc14,2.0)*correction14Error
                                                             
                                                             + 2.0*df4dr2*df4dd2*covRef2Def2
                                                             + 2.0*df4dr2*df4dr4*covRef2Ref4
                                                             + 2.0*df4dr2*df4dd4*covRef2Def4
                                                             + 2.0*df4dr2*df4dc1*covRef2C1
                                                             + 2.0*df4dr2*df4dc2*covRef2C2
                                                             + 2.0*df4dr2*df4dc3*covRef2C3
                                                             + 2.0*df4dr2*df4dc4*covRef2C4
                                                             + 2.0*df4dr2*df4dc5*covRef2C5
                                                             + 2.0*df4dr2*df4dc6*covRef2C6
                                                             + 2.0*df4dr2*df4dc7*covRef2C7
                                                             + 2.0*df4dr2*df4dc8*covRef2C8
                                                             + 2.0*df4dr2*df4dc9*covRef2C9
                                                             + 2.0*df4dr2*df4dc10*covRef2C10
                                                             + 2.0*df4dr2*df4dc11*covRef2C11
                                                             + 2.0*df4dr2*df4dc12*covRef2C12
                                                             + 2.0*df4dr2*df4dc13*covRef2C13
                                                             + 2.0*df4dr2*df4dc14*covRef2C14
                                                             
                                                             + 2.0*df4dd2*df4dr4*covRef4Def2
                                                             + 2.0*df4dd2*df4dd4*covDef2Def4
                                                             + 2.0*df4dd2*df4dc1*covDef2C1
                                                             + 2.0*df4dd2*df4dc2*covDef2C2
                                                             + 2.0*df4dd2*df4dc3*covDef2C3
                                                             + 2.0*df4dd2*df4dc4*covDef2C4
                                                             + 2.0*df4dd2*df4dc5*covDef2C5
                                                             + 2.0*df4dd2*df4dc6*covDef2C6
                                                             + 2.0*df4dd2*df4dc7*covDef2C7
                                                             + 2.0*df4dd2*df4dc8*covDef2C8
                                                             + 2.0*df4dd2*df4dc9*covDef2C9
                                                             + 2.0*df4dd2*df4dc10*covDef2C10
                                                             + 2.0*df4dd2*df4dc11*covDef2C11
                                                             + 2.0*df4dd2*df4dc12*covDef2C12
                                                             + 2.0*df4dd2*df4dc13*covDef2C13
                                                             + 2.0*df4dd2*df4dc14*covDef2C14
                                                             
                                                             + 2.0*df4dr4*df4dd4*covRef4Def4
                                                             + 2.0*df4dr4*df4dc1*covRef4C1
                                                             + 2.0*df4dr4*df4dc2*covRef4C2
                                                             + 2.0*df4dr4*df4dc3*covRef4C3
                                                             + 2.0*df4dr4*df4dc4*covRef4C4
                                                             + 2.0*df4dr4*df4dc5*covRef4C5
                                                             + 2.0*df4dr4*df4dc6*covRef4C6
                                                             + 2.0*df4dr4*df4dc7*covRef4C7
                                                             + 2.0*df4dr4*df4dc8*covRef4C8
                                                             + 2.0*df4dr4*df4dc9*covRef4C9
                                                             + 2.0*df4dr4*df4dc10*covRef4C10
                                                             + 2.0*df4dr4*df4dc11*covRef4C11
                                                             + 2.0*df4dr4*df4dc12*covRef4C12
                                                             + 2.0*df4dr4*df4dc13*covRef4C13
                                                             + 2.0*df4dr4*df4dc14*covRef4C14
                                                             
                                                             + 2.0*df4dd4*df4dc1*covDef4C1
                                                             + 2.0*df4dd4*df4dc2*covDef4C2
                                                             + 2.0*df4dd4*df4dc3*covDef4C3
                                                             + 2.0*df4dd4*df4dc4*covDef4C4
                                                             + 2.0*df4dd4*df4dc5*covDef4C5
                                                             + 2.0*df4dd4*df4dc6*covDef4C6
                                                             + 2.0*df4dd4*df4dc7*covDef4C7
                                                             + 2.0*df4dd4*df4dc8*covDef4C8
                                                             + 2.0*df4dd4*df4dc9*covDef4C9
                                                             + 2.0*df4dd4*df4dc10*covDef4C10
                                                             + 2.0*df4dd4*df4dc11*covDef4C11
                                                             + 2.0*df4dd4*df4dc12*covDef4C12
                                                             + 2.0*df4dd4*df4dc13*covDef4C13
                                                             + 2.0*df4dd4*df4dc14*covDef4C14
                                                             
                                                             + 2.0*df4dc1*df4dc2*covC1C2
                                                             + 2.0*df4dc1*df4dc3*covC1C3
                                                             + 2.0*df4dc1*df4dc4*covC1C4
                                                             + 2.0*df4dc1*df4dc5*covC1C5
                                                             + 2.0*df4dc1*df4dc6*covC1C6
                                                             + 2.0*df4dc1*df4dc7*covC1C7
                                                             + 2.0*df4dc1*df4dc8*covC1C8
                                                             + 2.0*df4dc1*df4dc9*covC1C9
                                                             + 2.0*df4dc1*df4dc10*covC1C10
                                                             + 2.0*df4dc1*df4dc11*covC1C11
                                                             + 2.0*df4dc1*df4dc12*covC1C12
                                                             + 2.0*df4dc1*df4dc13*covC1C13
                                                             + 2.0*df4dc1*df4dc14*covC1C14
                                                             
                                                             + 2.0*df4dc2*df4dc3*covC2C3
                                                             + 2.0*df4dc2*df4dc4*covC2C4
                                                             + 2.0*df4dc2*df4dc5*covC2C5
                                                             + 2.0*df4dc2*df4dc6*covC2C6
                                                             + 2.0*df4dc2*df4dc7*covC2C7
                                                             + 2.0*df4dc2*df4dc8*covC2C8
                                                             + 2.0*df4dc2*df4dc9*covC2C9
                                                             + 2.0*df4dc2*df4dc10*covC2C10
                                                             + 2.0*df4dc2*df4dc11*covC2C11
                                                             + 2.0*df4dc2*df4dc12*covC2C12
                                                             + 2.0*df4dc2*df4dc13*covC2C13
                                                             + 2.0*df4dc2*df4dc14*covC2C14
                                                             
                                                             + 2.0*df4dc3*df4dc4*covC3C4
                                                             + 2.0*df4dc3*df4dc5*covC3C5
                                                             + 2.0*df4dc3*df4dc6*covC3C6
                                                             + 2.0*df4dc3*df4dc7*covC3C7
                                                             + 2.0*df4dc3*df4dc8*covC3C8
                                                             + 2.0*df4dc3*df4dc9*covC3C9
                                                             + 2.0*df4dc3*df4dc10*covC3C10
                                                             + 2.0*df4dc3*df4dc11*covC3C11
                                                             + 2.0*df4dc3*df4dc12*covC3C12
                                                             + 2.0*df4dc3*df4dc13*covC3C13
                                                             + 2.0*df4dc3*df4dc14*covC3C14
                                                             
                                                             + 2.0*df4dc4*df4dc5*covC4C5
                                                             + 2.0*df4dc4*df4dc6*covC4C6
                                                             + 2.0*df4dc4*df4dc7*covC4C7
                                                             + 2.0*df4dc4*df4dc8*covC4C8
                                                             + 2.0*df4dc4*df4dc9*covC4C9
                                                             + 2.0*df4dc4*df4dc10*covC4C10
                                                             + 2.0*df4dc4*df4dc11*covC4C11
                                                             + 2.0*df4dc4*df4dc12*covC4C12
                                                             + 2.0*df4dc4*df4dc13*covC4C13
                                                             + 2.0*df4dc4*df4dc14*covC4C14
                                                             
                                                             + 2.0*df4dc5*df4dc6*covC5C6
                                                             + 2.0*df4dc5*df4dc7*covC5C7
                                                             + 2.0*df4dc5*df4dc8*covC5C8
                                                             + 2.0*df4dc5*df4dc9*covC5C9
                                                             + 2.0*df4dc5*df4dc10*covC5C10
                                                             + 2.0*df4dc5*df4dc11*covC5C11
                                                             + 2.0*df4dc5*df4dc12*covC5C12
                                                             + 2.0*df4dc5*df4dc13*covC5C13
                                                             + 2.0*df4dc5*df4dc14*covC5C14
                                                             
                                                             + 2.0*df4dc6*df4dc7*covC6C7
                                                             + 2.0*df4dc6*df4dc8*covC6C8
                                                             + 2.0*df4dc6*df4dc9*covC6C9
                                                             + 2.0*df4dc6*df4dc10*covC6C10
                                                             + 2.0*df4dc6*df4dc11*covC6C11
                                                             + 2.0*df4dc6*df4dc12*covC6C12
                                                             + 2.0*df4dc6*df4dc13*covC6C13
                                                             + 2.0*df4dc6*df4dc14*covC6C14
                                                             
                                                             + 2.0*df4dc7*df4dc8*covC7C8
                                                             + 2.0*df4dc7*df4dc9*covC7C9
                                                             + 2.0*df4dc7*df4dc10*covC7C10
                                                             + 2.0*df4dc7*df4dc11*covC7C11
                                                             + 2.0*df4dc7*df4dc12*covC7C12
                                                             + 2.0*df4dc7*df4dc13*covC7C13
                                                             + 2.0*df4dc7*df4dc14*covC7C14
                                                             
                                                             + 2.0*df4dc8*df4dc9*covC8C9
                                                             + 2.0*df4dc8*df4dc10*covC8C10
                                                             + 2.0*df4dc8*df4dc11*covC8C11
                                                             + 2.0*df4dc8*df4dc12*covC8C12
                                                             + 2.0*df4dc8*df4dc13*covC8C13
                                                             + 2.0*df4dc8*df4dc14*covC8C14
                                                             
                                                             + 2.0*df4dc9*df4dc10*covC9C10
                                                             + 2.0*df4dc9*df4dc11*covC9C11
                                                             + 2.0*df4dc9*df4dc12*covC9C12
                                                             + 2.0*df4dc9*df4dc13*covC9C13
                                                             + 2.0*df4dc9*df4dc14*covC9C14
                                                             
                                                             + 2.0*df4dc10*df4dc11*covC10C11
                                                             + 2.0*df4dc10*df4dc12*covC10C12
                                                             + 2.0*df4dc10*df4dc13*covC10C13
                                                             + 2.0*df4dc10*df4dc14*covC10C14
                                                             
                                                             + 2.0*df4dc11*df4dc12*covC11C12
                                                             + 2.0*df4dc11*df4dc13*covC11C13
                                                             + 2.0*df4dc11*df4dc14*covC11C14
                                                             
                                                             + 2.0*df4dc12*df4dc13*covC12C13
                                                             + 2.0*df4dc12*df4dc14*covC12C14
                                                             
                                                             + 2.0*df4dc13*df4dc14*covC13C14
                                                             );
                if(!TMath::Finite(v1_4Error[ibin][itrack][icent]) || df4dr2*reference2Error1 == 0. || df4dd2*differential2Error1 == 0.
                   || df4dr4*reference4Error1 == 0. || df4dd4*differential4Error1 == 0. || v1_4[ibin][itrack][icent] == 0.)
                    v1_4Error[ibin][itrack][icent] = 0.0;
                /*std::cout<<icent<<"  "<<itrack<<"  "<<ibin<<"  "<<reference2_1<<"  "<<sign2*reference2_2<<"  "<<reference2_3<<"  "
                 <<differential2_1<<"  "<<sign2*differential2_2<<"  "<<v1_2[ibin][itrack][icent]<<"  "<<v1_2Error[ibin][itrack][icent]<<std::endl
                 <<icent<<"  "<<itrack<<"  "<<ibin<<"  "<<reference4_1<<"  "<<sign4*reference4_2<<"  "<<reference4_3<<"  "
                 <<differential4_1<<"  "<<sign4*differential4_2<<"  "<<v1_4[ibin][itrack][icent]<<"  "<<v1_4Error[ibin][itrack][icent]<<std::endl
                 <<std::endl;*/
              }
          }
        std::cout<<icent+1<<std::endl;
      }
    Double_t content2[ Nbins ], error2[ Nbins ], content4[ Nbins ], error4[ Nbins ];
    for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
      {
        content2[ibin] = 0.0; error2[ibin] = 0.0; content4[ibin] = 0.0; error4[ibin] = 0.0;
        //for ( Int_t icent = 0; icent < Ncentralities; icent++ )    // (0-80)%
        for ( Int_t icent = 2; icent < 5; icent++ )    // (10-25)%
          {
            for ( Int_t itrack = 0; itrack < N_track; itrack++ )
              {
                if( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ){
                    content2[ibin] += v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) ;
                      error2[ibin] += 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) ;
                }
                /*content2[ibin] += ( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ) ?
                                    v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error2[ibin] += ( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;*/
                if( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ){
                    content4[ibin] += v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) ;
                      error4[ibin] += 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) ;
                }
                /*content4[ibin] += ( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ) ?
                                    v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error4[ibin] += ( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;*/
              }
          }
        if( error2[ibin] > 0.0 ){
            content2[ibin] *= 1.0 / error2[ibin] ;
            if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
            error2[ibin]  = TMath::Sqrt( 1.0 / error2[ibin] ) ;
            if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;
        }
        /*content2[ibin] *= ( error2[ibin] > 0.0 ) ? 1.0 / error2[ibin] : 0.0;
        if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
        error2[ibin]  = ( error2[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error2[ibin] ) : 0.0;
        if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;*/
        if( error4[ibin] > 0.0 ){
            content4[ibin] *= 1.0 / error4[ibin] ;
            if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
            error4[ibin]  = TMath::Sqrt( 1.0 / error4[ibin] ) ;
            if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;
        }
        /*content4[ibin] *= ( error4[ibin] > 0.0 ) ? 1.0 / error4[ibin] : 0.0;
        if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
        error4[ibin]  = ( error4[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error4[ibin] ) : 0.0;
        if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;*/
        histogram1D[0+2*Ncentralities]->SetBinContent(ibin+1,content2[ibin]); histogram1D[0+2*Ncentralities]->SetBinError(ibin+1,error2[ibin]);
        histogram1D[1+2*Ncentralities]->SetBinContent(ibin+1,content4[ibin]); histogram1D[1+2*Ncentralities]->SetBinError(ibin+1,error4[ibin]);
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
          {
            content2[ibin] = 0.0; error2[ibin] = 0.0; content4[ibin] = 0.0; error4[ibin] = 0.0;
            for ( Int_t itrack = 0; itrack < N_track; itrack++ )
              {
                if( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ){
                    content2[ibin] += v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) ;
                    error2[ibin] += 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) ;
                }
                /*content2[ibin] += ( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ) ?
                 v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                 error2[ibin] += ( v1_2[ibin][itrack][icent] != 0.0 && v1_2Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;*/
                if( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ){
                    content4[ibin] += v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) ;
                    error4[ibin] += 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) ;
                }
                /*content4[ibin] += ( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ) ?
                 v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
                 error4[ibin] += ( v1_4[ibin][itrack][icent] != 0.0 && v1_4Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;*/
              }
            if( error2[ibin] > 0.0 ){
                content2[ibin] *= 1.0 / error2[ibin] ;
                if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
                error2[ibin]  = TMath::Sqrt( 1.0 / error2[ibin] ) ;
                if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;
            }
            /*content2[ibin] *= ( error2[ibin] > 0.0 ) ? 1.0 / error2[ibin] : 0.0;
             if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
             error2[ibin]  = ( error2[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error2[ibin] ) : 0.0;
             if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;*/
            if( error4[ibin] > 0.0 ){
                content4[ibin] *= 1.0 / error4[ibin] ;
                if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
                error4[ibin]  = TMath::Sqrt( 1.0 / error4[ibin] ) ;
                if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;
            }
            /*content4[ibin] *= ( error4[ibin] > 0.0 ) ? 1.0 / error4[ibin] : 0.0;
             if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
             error4[ibin]  = ( error4[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error4[ibin] ) : 0.0;
             if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;*/
            histogram1D[0+2*icent]->SetBinContent(ibin+1,content2[ibin]); histogram1D[0+2*icent]->SetBinError(ibin+1,error2[ibin]);
            histogram1D[1+2*icent]->SetBinContent(ibin+1,content4[ibin]); histogram1D[1+2*icent]->SetBinError(ibin+1,error4[ibin]);
          }  
      }
    TFile *output = new TFile(outputName,"RECREATE");
    for ( Int_t icent = 0; icent <= Ncentralities; icent++ )
      {
		histogram1D[0+2*icent]->Write();
		histogram1D[1+2*icent]->Write();
      }
    output->WriteObject(flowArrayS, "flowArrayS");
    output->WriteObject(flowArray2S, "flowArray2S");
	output->WriteObject(flowArrayCOV1S, "flowArrayCOV1S");
	output->WriteObject(flowArrayCOV2S, "flowArrayCOV2S");
	output->WriteObject(flowArrayCOV3S, "flowArrayCOV3S");
	output->WriteObject(flowArrayCOV4S, "flowArrayCOV4S");
}
