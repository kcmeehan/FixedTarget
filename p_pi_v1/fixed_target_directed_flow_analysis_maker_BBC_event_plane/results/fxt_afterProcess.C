double resEventPlane(double chi) {
    // Calculates the event plane resolution as a function of chi
    
    double con = 0.626657;                   // sqrt(pi/2)/2
    double arg = chi * chi / 4.0;
    
    double res = con * chi * exp(-arg) * (TMath::BesselI0(arg) + TMath::BesselI1(arg));
    
    return res;
}

double chi(double res) {
    // Calculates chi from the event plane resolution
    
    double chi   = 2.0;
    double delta = 1.0;
    
    for (int i = 0; i < 15; i++) {
        //    chi   = (resEventPlane(chi) < res) ? chi + delta : chi - delta;
        //    delta = delta / 2.;
        while(resEventPlane(chi) < res) {chi += delta;}
        delta = delta / 2.0;
        while(resEventPlane(chi) > res) {chi -= delta;}
        delta = delta / 2.0;
    }
    
    return chi;
}

void fxt_afterProcess() {
    TFile *inputFile = new TFile("total.root","read");
    TProfile3D *profile3D_proton_v1 = (TProfile3D*)inputFile->Get("profile3D_proton_v1");
    TProfile3D *profile3D_deuteron_v1 = (TProfile3D*)inputFile->Get("profile3D_deuteron_v1");
    TProfile3D *profile3D_pionPlus_v1 = (TProfile3D*)inputFile->Get("profile3D_pionPlus_v1");
    TProfile3D *profile3D_pionMinus_v1 = (TProfile3D*)inputFile->Get("profile3D_pionMinus_v1");
    TProfile3D *profile3D_kaonPlus_v1 = (TProfile3D*)inputFile->Get("profile3D_kaonPlus_v1");
    TProfile3D *profile3D_kaonMinus_v1 = (TProfile3D*)inputFile->Get("profile3D_kaonMinus_v1");
    
    TProfile *profile_correlation_tpc_east_tpc_west = (TProfile*)inputFile->Get("profile_correlation_tpc_east_tpc_west");
    TProfile *profile_correlation_tpc_east_thirdEP = (TProfile*)inputFile->Get("profile_correlation_tpc_east_thirdEP");
    TProfile *profile_correlation_tpc_east_bbc_east = (TProfile*)inputFile->Get("profile_correlation_tpc_east_bbc_east");
    TProfile *profile_correlation_tpc_east_bbc_west = (TProfile*)inputFile->Get("profile_correlation_tpc_east_bbc_west");
    TProfile *profile_correlation_tpc_west_thirdEP = (TProfile*)inputFile->Get("profile_correlation_tpc_west_thirdEP");
    TProfile *profile_correlation_tpc_west_bbc_east = (TProfile*)inputFile->Get("profile_correlation_tpc_west_bbc_east");
    TProfile *profile_correlation_tpc_west_bbc_west = (TProfile*)inputFile->Get("profile_correlation_tpc_west_bbc_west");
    TProfile *profile_correlation_thirdEP_bbc_east = (TProfile*)inputFile->Get("profile_correlation_thirdEP_bbc_east");
    TProfile *profile_correlation_thirdEP_bbc_west = (TProfile*)inputFile->Get("profile_correlation_thirdEP_bbc_west");
    TProfile *profile_correlation_bbc_east_bbc_west = (TProfile*)inputFile->Get("profile_correlation_bbc_east_bbc_west");
    
    TFile *outputFile = new TFile("result00.root","recreate");
    // flow histograms
    const int Ncentralities = 7;
    // set rapidity/pseudorapidity range
    int rapidityBins = 20; double rapidityLow = -2.0, rapidityHigh = 0.0;
    // set transverse momentum range
    int ptBins = 50; double ptLow = 0.0, ptHigh = 5.0;
    char name[100], description[200];
    TH1D *proton_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_proton_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, Proton v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, Proton v_{1}(y)",30-5*icent,35-5*icent);
        proton_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        proton_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        proton_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *proton_v1_10_25_averaged = new TH1D("hist_proton_v1y_10_25_averaged","10-25% Proton v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    proton_v1_10_25_averaged->GetXaxis()->SetTitle("Rapidity y");
    proton_v1_10_25_averaged->GetYaxis()->SetTitle("v_{1}");
    TH1D *proton_v1_10_30_averaged = new TH1D("hist_proton_v1y_10_30_averaged","10-30% Proton v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    proton_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    proton_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    TH1D *deuteron_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_deuteron_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, Proton v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, Proton v_{1}(y)",30-5*icent,35-5*icent);
        deuteron_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        deuteron_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        deuteron_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *deuteron_v1_10_30_averaged = new TH1D("hist_deuteron_v1y_averaged","10-30% Deuteron v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    deuteron_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    deuteron_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    TH1D *pionPlus_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_pionPlus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, #pi^{#plus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, #pi^{#plus} v_{1}(y)",30-5*icent,35-5*icent);
        pionPlus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        pionPlus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        pionPlus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *pionPlus_v1_10_30_averaged = new TH1D("hist_pionPlus_v1y_averaged","10-30% #pi^{#plus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    pionPlus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    pionPlus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    TH1D *pionMinus_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_pionMinus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, #pi^{#minus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, #pi^{#minus} v_{1}(y)",30-5*icent,35-5*icent);
        pionMinus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        pionMinus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        pionMinus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *pionMinus_v1_10_30_averaged = new TH1D("hist_pionMinus_v1y_averaged","10-30% #pi^{#minus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    pionMinus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    pionMinus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    TH1D *kaonPlus_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_kaonPlus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, K^{#plus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, K^{#plus} v_{1}(y)",30-5*icent,35-5*icent);
        kaonPlus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        kaonPlus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        kaonPlus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *kaonPlus_v1_10_30_averaged = new TH1D("hist_kaonPlus_v1y_averaged","10-30% K^{#plus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    kaonPlus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    kaonPlus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    
    TH1D *kaonMinus_v1_cent[Ncentralities];
    for(int icent=0;icent<Ncentralities;icent++) {
        sprintf(name,"hist_kaonMinus_v1y_cent%d",icent+1);
        if(icent < 1) sprintf(description,"UrQMD FXT 4.5 GeV, centrality >30%%, K^{#minus} v_{1}(y)");
        if(icent > 0) sprintf(description,"UrQMD FXT 4.5 GeV, centrality %d - %d%%, K^{#minus} v_{1}(y)",30-5*icent,35-5*icent);
        kaonMinus_v1_cent[icent] = new TH1D(name,description,rapidityBins,rapidityLow,rapidityHigh);
        kaonMinus_v1_cent[icent]->GetXaxis()->SetTitle("Rapidity y");
        kaonMinus_v1_cent[icent]->GetYaxis()->SetTitle("v_{1}");
    }
    TH1D *kaonMinus_v1_10_30_averaged = new TH1D("hist_kaonMinus_v1y_averaged","10-30% K^{#minus} v_{1}(y)",rapidityBins,rapidityLow,rapidityHigh);
    kaonMinus_v1_10_30_averaged->GetXaxis()->SetTitle("Rapidity y");
    kaonMinus_v1_10_30_averaged->GetYaxis()->SetTitle("v_{1}");
    // EP resolutions
    double xbin[8] = {0.0,5.0,10.0,15.0,20.0,25.0,30.0,35.0};
    TH1D *correlation_tpc_east_tpc_west = new TH1D("correlation_tpc_east_tpc_west","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_tpc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_tpc_west->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_east_thirdEP = new TH1D("correlation_tpc_east_thirdEP","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{3rd}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_east_bbc_east = new TH1D("correlation_tpc_east_bbc_east","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_east_bbc_west = new TH1D("correlation_tpc_east_bbc_west","#sqrt{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_west_thirdEP = new TH1D("correlation_tpc_west_thirdEP","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{3rd}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_thirdEP->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_thirdEP->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_west_bbc_east = new TH1D("correlation_tpc_west_bbc_east","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_tpc_west_bbc_west = new TH1D("correlation_tpc_west_bbc_west","#sqrt{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_tpc_west_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_tpc_west_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_thirdEP_bbc_east = new TH1D("correlation_thirdEP_bbc_east","#sqrt{<cos(#psi^{3rd}_{1} #minus #psi^{BBC east}_{1})>}",Ncentralities,xbin);
    correlation_thirdEP_bbc_east->GetXaxis()->SetTitle("Centrality (%)");
    correlation_thirdEP_bbc_east->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_thirdEP_bbc_west = new TH1D("correlation_thirdEP_bbc_west","#sqrt{<cos(#psi^{3rd}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_thirdEP_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_thirdEP_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    TH1D *correlation_bbc_east_bbc_west = new TH1D("correlation_bbc_east_bbc_west","#sqrt{<cos(#psi^{BBC east}_{1} #minus #psi^{BBC west}_{1})>}",Ncentralities,xbin);
    correlation_bbc_east_bbc_west->GetXaxis()->SetTitle("Centrality (%)");
    correlation_bbc_east_bbc_west->GetYaxis()->SetTitle("Correlation");
    
    TH1D *resolution_tpc_sub = new TH1D("resolution_tpc_sub","#sqrt{<cos(#psi^{TPC sub}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_tpc_sub->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_sub->GetYaxis()->SetTitle("Resolution");
    
    TH1D *resolution_tpc_full = new TH1D("resolution_tpc_full","#sqrt{<cos(#psi^{TPC full}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_tpc_full->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_full->GetYaxis()->SetTitle("Resolution");
    
    TH1D *resolution_bbc_sub = new TH1D("resolution_bbc_sub","#sqrt{<cos(#psi^{BBC sub}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_bbc_sub->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_sub->GetYaxis()->SetTitle("Resolution");
    
    TH1D *resolution_bbc_full = new TH1D("resolution_bbc_full","#sqrt{<cos(#psi^{BBC full}_{1} #minus #psi_{r})>}",Ncentralities,xbin);
    resolution_bbc_full->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_full->GetYaxis()->SetTitle("Resolution");
    // three-EP method
    TH1D *resolution_tpc_east_threeEP = new TH1D("resolution_tpc_east_threeEP","#sqrt{#frac{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})><cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}{<cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}}",Ncentralities,xbin);
    resolution_tpc_east_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_east_threeEP->GetYaxis()->SetTitle("Resolution");
    
    TH1D *resolution_tpc_west_threeEP = new TH1D("resolution_tpc_west_threeEP","#sqrt{#frac{<cos(#psi^{TPC west}_{1} #minus #psi^{TPC east}_{1})><cos(#psi^{TPC west}_{1} #minus #psi^{BBC east}_{1})>}{<cos(#psi^{TPC east}_{1} #minus #psi^{BBC east}_{1})>}}",Ncentralities,xbin);
    resolution_tpc_west_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_tpc_west_threeEP->GetYaxis()->SetTitle("Resolution");
    
    TH1D *resolution_bbc_east_threeEP = new TH1D("resolution_bbc_east_threeEP","#sqrt{#frac{<cos(#psi^{BBC east}_{1} #minus #psi^{TPC east}_{1})><cos(#psi^{BBC east}_{1} #minus #psi^{TPC west}_{1})>}{<cos(#psi^{TPC east}_{1} #minus #psi^{TPC west}_{1})>}}",Ncentralities,xbin);
    resolution_bbc_east_threeEP->GetXaxis()->SetTitle("Centrality (%)");
    resolution_bbc_east_threeEP->GetYaxis()->SetTitle("Resolution");
    // set EP indicator
    Bool_t chooseBBCeastEP = kTRUE;
    //Bool_t chooseBBCeastEP = kFALSE;
    // compute EP resolutions
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
        // three-EP method
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
    // compute flow and apply resolution corrections
    TH1D *psi_resolution_tmp = new TH1D("psi_resolution_tmp","psi_resolution_tmp",rapidityBins,rapidityLow,rapidityHigh);
    for(int icent=1;icent<=Ncentralities;icent++){
        for(int bin=1;bin<=rapidityBins;bin++){
            // prepare resolutions to divide
            if(chooseBBCeastEP) {
                psi_resolution_tmp->SetBinContent(bin,resolution_bbc_east_threeEP->GetBinContent(Ncentralities-icent+1));
                psi_resolution_tmp->SetBinError(bin,resolution_bbc_east_threeEP->GetBinError(Ncentralities-icent+1));
            }
            // average over momentum region
            // proton
          {
            int momentumBottomBin = profile3D_proton_v1->GetYaxis()->FindBin(0.4);
            int momentumTopBin = profile3D_proton_v1->GetYaxis()->FindBin(2.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_proton_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_proton_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_proton_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_proton_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_proton_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_proton_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                proton_v1_cent[icent-1]->SetBinContent(bin,content);
                proton_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // deuteron
          {
            int momentumBottomBin = profile3D_deuteron_v1->GetYaxis()->FindBin(0.0);
            int momentumTopBin = profile3D_deuteron_v1->GetYaxis()->FindBin(5.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_deuteron_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_deuteron_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_deuteron_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_deuteron_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_deuteron_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_deuteron_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                deuteron_v1_cent[icent-1]->SetBinContent(bin,content);
                deuteron_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // pionPlus
          {
            int momentumBottomBin = profile3D_pionPlus_v1->GetYaxis()->FindBin(0.0);
            int momentumTopBin = profile3D_pionPlus_v1->GetYaxis()->FindBin(5.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_pionPlus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_pionPlus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_pionPlus_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_pionPlus_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_pionPlus_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_pionPlus_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                pionPlus_v1_cent[icent-1]->SetBinContent(bin,content);
                pionPlus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // pionMinus
          {
            int momentumBottomBin = profile3D_pionMinus_v1->GetYaxis()->FindBin(0.0);
            int momentumTopBin = profile3D_pionMinus_v1->GetYaxis()->FindBin(5.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_pionMinus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_pionMinus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_pionMinus_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_pionMinus_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_pionMinus_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_pionMinus_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                pionMinus_v1_cent[icent-1]->SetBinContent(bin,content);
                pionMinus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // kaonPlus
          {
            int momentumBottomBin = profile3D_kaonPlus_v1->GetYaxis()->FindBin(0.0);
            int momentumTopBin = profile3D_kaonPlus_v1->GetYaxis()->FindBin(5.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_kaonPlus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_kaonPlus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_kaonPlus_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_kaonPlus_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_kaonPlus_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_kaonPlus_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                kaonPlus_v1_cent[icent-1]->SetBinContent(bin,content);
                kaonPlus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
            // kaonMinus
          {
            int momentumBottomBin = profile3D_kaonMinus_v1->GetYaxis()->FindBin(0.0);
            int momentumTopBin = profile3D_kaonMinus_v1->GetYaxis()->FindBin(5.0);
            double content = 0.0, error = 0.0;
            for(int momentumBin=momentumBottomBin;momentumBin<=momentumTopBin;momentumBin++) {
                if(profile3D_kaonMinus_v1->GetBinError(icent,momentumBin,bin) > 0.0) {
                    int currentBin = profile3D_kaonMinus_v1->GetBin(icent,momentumBin,bin);
                    if(profile3D_kaonMinus_v1->GetBinEntries(currentBin) >= 5) {
                        content += profile3D_kaonMinus_v1->GetBinContent(icent,momentumBin,bin) / TMath::Power(profile3D_kaonMinus_v1->GetBinError(icent,momentumBin,bin),2.0);
                        error += 1.0 / TMath::Power(profile3D_kaonMinus_v1->GetBinError(icent,momentumBin,bin),2.0);
                    }
                }
            }
            if(error > 0.0) {
                content /= error;
                error = TMath::Sqrt(1.0/error);
                kaonMinus_v1_cent[icent-1]->SetBinContent(bin,content);
                kaonMinus_v1_cent[icent-1]->SetBinError(bin,error);
            }
          }
        }
        proton_v1_cent[icent-1]->Divide(psi_resolution_tmp);
        deuteron_v1_cent[icent-1]->Divide(psi_resolution_tmp);
        pionPlus_v1_cent[icent-1]->Divide(psi_resolution_tmp);
        pionMinus_v1_cent[icent-1]->Divide(psi_resolution_tmp);
        kaonPlus_v1_cent[icent-1]->Divide(psi_resolution_tmp);
        kaonMinus_v1_cent[icent-1]->Divide(psi_resolution_tmp);
    }
    // average flow over centralities
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
        // deuteron
      {
        double content = 0.0, error = 0.0;
        for(int icent=2;icent<=5;icent++){
            if(deuteron_v1_cent[icent-1]->GetBinError(bin) > 0.0) {
                content += deuteron_v1_cent[icent-1]->GetBinContent(bin) / TMath::Power(deuteron_v1_cent[icent-1]->GetBinError(bin),2.0);
                error += 1.0 / TMath::Power(deuteron_v1_cent[icent-1]->GetBinError(bin),2.0);
            }
        }
        if(error > 0.0) {
            content /= error;
            error = TMath::Sqrt(1.0/error);
            deuteron_v1_10_30_averaged->SetBinContent(bin,content);
            deuteron_v1_10_30_averaged->SetBinError(bin,error);
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
    // save histograms to output file
    outputFile->Write();
}
