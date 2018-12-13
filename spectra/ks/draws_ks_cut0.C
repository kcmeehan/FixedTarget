//xianglei's fitting and drawing macro: read and fit the histograms filled by cuts.C

{
   gROOT->Reset();

   TString cuttag("cut0");
   TString Ecm("5");

   TString ifile = "output/auau"+Ecm+".mb.ks."+cuttag+".histo.root";
   TFile ihm(ifile);

   gROOT->ProcessLine(".L ./parameters.C");

   char PtName[kPtBin][25];
   for(int i=0;i<kPtBin;i++) sprintf(PtName[i],"%.1f-%.1f",ptbd[i],ptbd[i+1]);

   bool kAlwaysFit = false;
   bool kDoubGauss = false;

   //get histograms from root file (the cent binning and pt binning should be fixed)
   const int kCent = 9;
   const int kPt = 60;
   TH1F * hmSigtmp[kCent][kPt]; TH1F * hmBgtmp[kCent][kPt];
   TH1F * hmCentSigtmp[kCent]; TH1F * hmCentBgtmp[kCent];
   for(Int_t icent=0; icent<kCent; icent++){
	ihm.GetObject(Form("hmInvMassCent%d",icent), hmCentSigtmp[icent]);
	ihm.GetObject(Form("hmInvMassBgCent%d",icent), hmCentBgtmp[icent]);
	for(Int_t ipt=0; ipt<kPt; ipt++){
	   ihm.GetObject(Form("hmInvMassCent%dPt%d",icent,ipt), hmSigtmp[icent][ipt]);
	   ihm.GetObject(Form("hmInvMassBgCent%dPt%d",icent,ipt), hmBgtmp[icent][ipt]);
	}
   }

   TH1F * hmIM[kCentBin][kPtBin];   TH1F * hmIMCent[kCentBin];
   TH1F * hmIMbg[kCentBin][kPtBin]; TH1F * hmIMbgCent[kCentBin];
   for(Int_t iIM=0; iIM<kCentBin; iIM++){
	int cb = (int)(centbd[iIM]+1.0); int ce = (int)(centbd[iIM+1]+1.0);
	for(Int_t ii=cb; ii<ce; ii++){
	   if(ii==cb){
		hmIMCent[iIM] = hmCentSigtmp[ii];
		hmIMbgCent[iIM] = hmCentBgtmp[ii];
	   }
	   else {
		hmIMCent[iIM]->Add(hmCentSigtmp[ii]);
		hmIMbgCent[iIM]->Add(hmCentBgtmp[ii]);
	   }
	}
	//hmIMCent[iIM]->Rebin(2);
	for(Int_t jIM=0; jIM<kPtBin; jIM++){
	   int ib = (int)(ptbd[jIM]/0.1+0.5); int ie = (int)(ptbd[jIM+1]/0.1+0.5);
	   for(Int_t ic=cb; ic<ce; ic++){ for(Int_t ii=ib; ii<ie; ii++){
		if(ic==cb&&ii==ib){
		   hmIM[iIM][jIM] = hmSigtmp[ic][ii];
		   hmIMbg[iIM][jIM] = hmBgtmp[ic][ii];
		}
		else {
		   hmIM[iIM][jIM]->Add(hmSigtmp[ic][ii]);
		   hmIMbg[iIM][jIM]->Add(hmBgtmp[ic][ii]);
		}
	   }}
	   //hmIM[iIM][jIM]->Rebin(2);
	   //hmIMbg[iIM][jIM]->Rebin(2);
	   hmIM[iIM][jIM]->Add(hmIMbg[iIM][jIM],-1);
	}
   }

   gStyle->SetPalette(1);  
   gStyle->SetCanvasColor(10);    
   gStyle->SetFrameFillColor(10);
   gStyle->SetTitleFillColor(10);
   gStyle->SetStatColor(10);
   gStyle->SetHistFillColor(10);
   TGaxis::SetMaxDigits(4); 
   gStyle->SetPadTopMargin(0.15);
   //gStyle->SetPadLeftMargin(0.15);
   //gStyle->SetPadBottomMargin(0.15);
   //gStyle->SetPadRightMargin(0.10);
   gStyle->SetOptStat(1111); 
   gStyle->SetOptFit(111);

   Float_t rawyield[kCentBin][kPtBin];
   Float_t staterr[kCentBin][kPtBin];
   Float_t rawyield_ff[kCentBin][kPtBin];
   Float_t staterr_ff[kCentBin][kPtBin];
   Float_t rawyield_cf[kCentBin][kPtBin];
   Float_t staterr_cf[kCentBin][kPtBin];
   Float_t rawyield_cc[kCentBin][kPtBin];
   Float_t staterr_cc[kCentBin][kPtBin];
   Float_t invmass_ff[kCentBin][kPtBin];
   Float_t invmasserr_ff[kCentBin][kPtBin];
   Float_t sigma_ff[kCentBin][kPtBin];
   Float_t sigmaerr_ff[kCentBin][kPtBin];

   Float_t pdgmass = 0.497614;
   Float_t masswidth = 0.098;

   Float_t peak[kCentBin];
   Float_t sigma[kCentBin];

   //prepare fitting functions...
   //pol background
   TF1 *fbg = new TF1("fbg","[0]*[5]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
   //double gaussian (same peak)+ pol
   TF1 *fdoubgausbg = new TF1("fdoubgausbg","[0]*[10]/(2.506628274*[2])*exp(-0.5*((x-[1])/[2])^2)+[3]*[10]/(2.506628274*[4])*exp(-0.5*((x-[1])/[4])^2)+[5]*[10]+[6]*x+[7]*x*x+[8]*x*x*x+[9]*x*x*x*x");
   //single gaussian + pol
   TF1 *fsinggausbg = new TF1("fsinggausbg","[0]*[8]/(2.506628274*[2])*exp(-0.5*((x-[1])/[2])^2)+[3]*[8]+[4]*x+[5]*x*x+[6]*x*x*x+[7]*x*x*x*x");

   fdoubgausbg->SetParNames("Yield1","Mean","Sigma","yield2","Sigma2","Pol0","Pol1","Pol2","Pol3","Pol4","Binwidth");
   fsinggausbg->SetParNames("Yield","Mean","Sigma","Pol0","Pol1","Pol2","Pol3","Pol4","Binwidth");

   TCanvas *c1 = new TCanvas("c1","c1",10,10,700,800); 
   Int_t Nx = 1, Ny = 2;
   c1->Divide(Nx,Ny);
   Int_t Ncells = Nx*Ny;
   TString pdfname = "auau"+Ecm+"_ks_invmass_"+cuttag+".pdf";
   TPDF *pdf = new TPDF(pdfname); 

   for(Int_t iPt=0; iPt<kPtBin; iPt++){
	for(Int_t iIM=0; iIM<kCentBin; iIM++){
	   c1->cd(iIM%Ncells+1);

	   cout<<"-------------CentBin: "<<iIM<<"----PtBin: "<<iPt<<endl;
	   TH1F * hmCurrent = hmIM[iIM][iPt];
	   TH1F * hmBgCurrent = hmIMbg[iIM][iPt];

	   if(hmCurrent->GetEntries() <= 900) hmCurrent->Rebin(2);

	   float mass_l = pdgmass-masswidth;
	   float mass_r = pdgmass+masswidth;

	   //control the zoom levels in X axis (the default is the fitting range)
	   //TH1F * hmFrame = gPad->DrawFrame(0.44,0,0.55,hmCurrent->GetMaximum()*1.2);
	   //TH1F * hmFrame = gPad->DrawFrame(mass_l,0,mass_r,hmCurrent->GetMaximum()*1.2);
	   TH1F * hmFrame = gPad->DrawFrame(hmCurrent->GetXaxis()->GetXmin(),-hmCurrent->GetMaximum()*0.05,hmCurrent->GetXaxis()->GetXmax(),hmCurrent->GetMaximum()*1.2);

	   //draw the histogram
	   TString htitle(Form("K^{0}_{S}, Au+Au %s GeV, %s, p_{T} %s GeV/c", Ecm.Data(), CentName[iIM], PtName[iPt]));
	   hmFrame->SetTitle(htitle);
	   hmFrame->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
	   hmFrame->GetYaxis()->SetTitle("Counts");
	   hmFrame->GetYaxis()->SetTitleOffset(1.2);
	   hmCurrent->SetMarkerStyle(20);
	   hmCurrent->SetMarkerSize(1);
	   hmCurrent->Draw("sames"); //use "same" if stat box is not needed.

	   //fitting curves' styles
	   fbg->SetLineColor(kBlue);
	   fbg->SetLineStyle(2);
	   fbg->SetLineWidth(2);
	   fdoubgausbg->SetLineColor(kRed);
	   fdoubgausbg->SetLineStyle(1);
	   fdoubgausbg->SetLineWidth(2);
	   fsinggausbg->SetLineColor(kRed);
	   fsinggausbg->SetLineStyle(1);
	   fsinggausbg->SetLineWidth(2);

	   //fitting...
	   //first fitting with single gaussian+pol to get the peak position and width, peak count for the second double gaussian fitting. single gaussian+pol is more robust against the initial parameters than double gaussian fitting. so this is a warm-up.
	   fsinggausbg->SetParameters(hmCurrent->GetEntries()/10,pdgmass,0.004,hmCurrent->GetEntries(),-10,30,0,0);
	   fsinggausbg->SetParLimits(1,pdgmass-0.005,pdgmass+0.005);
	   fsinggausbg->SetParLimits(2,0.002,0.012);
	   fsinggausbg->FixParameter(6,0);
	   fsinggausbg->FixParameter(7,0);
	   fsinggausbg->FixParameter(8,hmCurrent->GetBinWidth(1));

	   hmCurrent->Fit("fsinggausbg","N","",mass_l,mass_r); //first fit, to determine whether a reasonable fit can be done. Then set the kFit flag accordingly.
	   bool kFit;
	   if(hmCurrent->GetEntries()>0) kFit = true;
	   else kFit = false;

	   TFitResultPtr pSingle, pDouble;

	   if(kFit && !kDoubGauss)
		pSingle = hmCurrent->Fit("fsinggausbg","S","same",mass_l,mass_r); //fit, plot fsinggausbg 
	   else
		hmCurrent->Fit("fsinggausbg","N","",mass_l,mass_r); //fit, store fsinggausbg, but not plot 

	   //second fitting with double gaussian+pol. get initial parameters from single gaussian fitting.
	   fdoubgausbg->SetParameters(fsinggausbg->GetParameter(0)/2.0,fsinggausbg->GetParameter(1),fsinggausbg->GetParameter(2)*0.7,fsinggausbg->GetParameter(0)/2.0,fsinggausbg->GetParameter(2)*1.5,fsinggausbg->GetParameter(3),fsinggausbg->GetParameter(4),fsinggausbg->GetParameter(5),fsinggausbg->GetParameter(6),fsinggausbg->GetParameter(7));
	   fdoubgausbg->SetParLimits(2,fsinggausbg->GetParameter(2)-0.003,fsinggausbg->GetParameter(2));
	   fdoubgausbg->SetParLimits(4,fsinggausbg->GetParameter(2),fsinggausbg->GetParameter(2)+0.005);
	   fdoubgausbg->FixParameter(8,0);
	   fdoubgausbg->FixParameter(9,0);
	   fdoubgausbg->FixParameter(10,hmCurrent->GetBinWidth(1));
	   if(kFit && kDoubGauss)
		pDouble = hmCurrent->Fit("fdoubgausbg","S","same",mass_l,mass_r); //fit, store the fsinggausbg, but not plot 
	   else	
		hmCurrent->Fit("fdoubgausbg","N","",mass_l,mass_r); //fit, store the fsinggausbg, but not plot 

	   //draw pol background
	   if(kDoubGauss)
		fbg->SetParameters(fdoubgausbg->GetParameter(5),fdoubgausbg->GetParameter(6),fdoubgausbg->GetParameter(7),fdoubgausbg->GetParameter(8),fdoubgausbg->GetParameter(9),fdoubgausbg->GetParameter(10));
	   else
		fbg->SetParameters(fsinggausbg->GetParameter(3),fsinggausbg->GetParameter(4),fsinggausbg->GetParameter(5),fsinggausbg->GetParameter(6),fsinggausbg->GetParameter(7),fsinggausbg->GetParameter(8));
	   //fbg->Draw("same");

	   //get the rawyield with fitting functions
	   //rawyield_ff[iIM][iPt] = fsinggausbg->GetParameter(0);
	   //staterr_ff[iIM][iPt] = fsinggausbg->GetParError(0);
	   invmass_ff[iIM][iPt] = fsinggausbg->GetParameter(1);
	   invmasserr_ff[iIM][iPt] = fsinggausbg->GetParError(1);
	   sigma_ff[iIM][iPt] = fsinggausbg->GetParameter(2);
	   sigmaerr_ff[iIM][iPt] = fsinggausbg->GetParError(2);

	   //determine peak range and side bands ranges
	   //if the fitting is not good, use the values from last pT bin,
	   //should make sure the first pT bin has reasonable value.
	   Double_t masspeak, masswid;
	   if(kDoubGauss) {
		masspeak = fdoubgausbg->GetParameter(1);
		masswid = (fdoubgausbg->GetParameter(0)*fdoubgausbg->GetParameter(2)+fdoubgausbg->GetParameter(3)*fdoubgausbg->GetParameter(4))/(fdoubgausbg->GetParameter(0)+fdoubgausbg->GetParameter(3));
	   }
	   else {
		masspeak = fsinggausbg->GetParameter(1);
		masswid = fsinggausbg->GetParameter(2);
	   }
	   if(kFit){
		peak[iIM]=masspeak;
		sigma[iIM]=masswid;
	   }

	   Float_t nGauss;
	   if(kDoubGauss) nGauss = 4.0;
	   else nGauss = 4.0;
	   Int_t midbin_l = hmCurrent->FindBin(peak[iIM]-sigma[iIM]*nGauss);
	   Int_t midbin_r = hmCurrent->FindBin(peak[iIM]+sigma[iIM]*nGauss);
	   Int_t leftbin_l = hmCurrent->FindBin(peak[iIM]-sigma[iIM]*(2*nGauss+1.0));
	   Int_t leftbin_r = hmCurrent->FindBin(peak[iIM]-sigma[iIM]*(nGauss+1.0));
	   Int_t rightbin_l = hmCurrent->FindBin(peak[iIM]+sigma[iIM]*(nGauss+1.0));
	   Int_t rightbin_r = hmCurrent->FindBin(peak[iIM]+sigma[iIM]*(2*nGauss+1.0));

	   //refine the left and right bin size, to make sure midsize = leftsize + rightsize
	   //also, leftsize is as close as to rightsize.
	   Float_t leftsize = leftbin_r-leftbin_l+1;
	   Float_t rightsize = rightbin_r-rightbin_l+1;
	   Float_t midsize = midbin_r-midbin_l+1;
	   while(midsize!=leftsize+rightsize){
		if(leftsize+rightsize > midsize){
		   if(leftsize>=rightsize)leftbin_r--;
		   else rightbin_l++;
		}
		else{
		   if(leftsize<=rightsize)leftbin_l--;
		   else rightbin_r++;
		}
		leftsize = leftbin_r-leftbin_l+1;
		rightsize = rightbin_r-rightbin_l+1;
	   }
		
	   if(!kAlwaysFit){
		//draw the peak region and side bands region
		TH1F* hmPeak = (TH1F*) hmCurrent->Clone("hmPeak");    //central peak
		hmPeak->GetXaxis()->SetRange(midbin_l,midbin_r);
		hmPeak->SetFillColor(8);
		hmPeak->Draw("Hist same");
		TLine *invmass_l = new TLine(hmCurrent->GetBinCenter(midbin_l),0,hmCurrent->GetBinCenter(midbin_l),hmCurrent->GetMaximum()*0.5);
		TLine *invmass_r = new TLine(hmCurrent->GetBinCenter(midbin_r),0,hmCurrent->GetBinCenter(midbin_r),hmCurrent->GetMaximum()*0.5);
		invmass_l.SetLineColor(kGreen);
		invmass_r.SetLineColor(kGreen);
		invmass_l.SetLineStyle(2);
		invmass_r.SetLineStyle(2);
		invmass_l.SetLineWidth(2);
		invmass_r.SetLineWidth(2);
		invmass_l.Draw("same");
		invmass_r.Draw("same");
		//if(!kFit){
		   TH1F* hmLeftBand = (TH1F*) hmCurrent->Clone("hmLeftBand"); //left band
		   hmLeftBand->GetXaxis()->SetRange(leftbin_l,leftbin_r);
		   hmLeftBand->SetFillColor(4);
		   hmLeftBand->Draw("Hist same");
		   TH1F* hmRightBand = (TH1F*) hmCurrent->Clone("hmRightBand"); //right band
		   hmRightBand->GetXaxis()->SetRange(rightbin_l,rightbin_r);
		   hmRightBand->SetFillColor(4);
		   hmRightBand->Draw("Hist same");

		   TLine *invmassl_l = new TLine(hmCurrent->GetBinCenter(leftbin_l),0,hmCurrent->GetBinCenter(leftbin_l),hmCurrent->GetMaximum()*0.5);
		   TLine *invmassl_r = new TLine(hmCurrent->GetBinCenter(leftbin_r),0,hmCurrent->GetBinCenter(leftbin_r),hmCurrent->GetMaximum()*0.5);
		   TLine *invmassr_l = new TLine(hmCurrent->GetBinCenter(rightbin_l),0,hmCurrent->GetBinCenter(rightbin_l),hmCurrent->GetMaximum()*0.5);
		   TLine *invmassr_r = new TLine(hmCurrent->GetBinCenter(rightbin_r),0,hmCurrent->GetBinCenter(rightbin_r),hmCurrent->GetMaximum()*0.5);
		   invmassl_l.SetLineColor(kBlue);
		   invmassl_r.SetLineColor(kBlue);
		   invmassl_l.SetLineStyle(2);
		   invmassl_r.SetLineStyle(2);
		   invmassl_l.SetLineWidth(2);
		   invmassl_r.SetLineWidth(2);
		   invmassr_l.SetLineColor(kBlue);
		   invmassr_r.SetLineColor(kBlue);
		   invmassr_l.SetLineStyle(2);
		   invmassr_r.SetLineStyle(2);
		   invmassr_l.SetLineWidth(2);
		   invmassr_r.SetLineWidth(2);
		   invmassl_l.Draw("same");
		   invmassl_r.Draw("same");
		   invmassr_l.Draw("same");
		   invmassr_r.Draw("same");
		//}
		//else {
		   if(kDoubGauss){
			fdoubgausbg->SetRange(mass_l,mass_r);
			fdoubgausbg->Draw("same");
		   }
		   else {
			fsinggausbg->SetRange(mass_l,mass_r);
			fsinggausbg->Draw("same");
		   }
		   fbg->SetRange(mass_l,mass_r);
		   fbg->Draw("same");
		//}
	   }
	   else {
		if(kDoubGauss){
		   fdoubgausbg->SetRange(mass_l,mass_r);
		   fdoubgausbg->Draw("same");
		}
		else {
		   fsinggausbg->SetRange(mass_l,mass_r);
		   fsinggausbg->Draw("same");
		}
		fbg->SetRange(mass_l,mass_r);
		fbg->Draw("same");
	   }

	   //debug information
	   cout<<midsize<<" "<<leftsize<<" "<<rightsize<<" "<<leftsize+rightsize-midsize<<endl;
	   cout<<midbin_l<<" "<<midbin_r<<" "<<hmCurrent->GetBinCenter(midbin_l)<<" "<<hmCurrent->GetBinCenter(midbin_r)<<endl;
	   cout<<leftbin_l<<" "<<leftbin_r<<" "<<hmCurrent->GetBinCenter(leftbin_l)<<" "<<hmCurrent->GetBinCenter(leftbin_r)<<endl;
	   cout<<rightbin_l<<" "<<rightbin_r<<" "<<hmCurrent->GetBinCenter(rightbin_l)<<" "<<hmCurrent->GetBinCenter(rightbin_r)<<endl;

	   //direct bin counting
	   Double_t midsum = 0, midsumerr2 = 0;
	   for(Int_t iMB=midbin_l;iMB<=midbin_r;iMB++){
		midsum    += hmCurrent->GetBinContent(iMB);
		midsumerr2 += hmCurrent->GetBinError(iMB) * hmCurrent->GetBinError(iMB);
	   }
	   Double_t leftsum = 0, leftsumerr2 = 0;
	   for(Int_t iLB=leftbin_l;iLB<=leftbin_r;iLB++){
		leftsum     += hmCurrent->GetBinContent(iLB);
		leftsumerr2 += hmCurrent->GetBinError(iLB) * hmCurrent->GetBinError(iLB);
	   }
	   Double_t rightsum = 0, rightsumerr2 = 0;
	   for(Int_t iRB=rightbin_l;iRB<=rightbin_r;iRB++){
		rightsum     += hmCurrent->GetBinContent(iRB);
		rightsumerr2 += hmCurrent->GetBinError(iRB) * hmCurrent->GetBinError(iRB);
	   }
	   rawyield_cc[iIM][iPt] = midsum-leftsum-rightsum;
	   staterr_cc[iIM][iPt] = sqrt(midsumerr2 + leftsumerr2 + rightsumerr2);
	   cout<<"yield (signal counting - bg side band): "<<rawyield_cc[iIM][iPt]<<" "<<staterr_cc[iIM][iPt]<<endl;

	   //signal from bin counting, background from pol if dgaus or sgaus fitting is good
	   Double_t bgsum = fbg->Integral(hmCurrent->GetBinCenter(midbin_l)-hmCurrent->GetBinWidth(midbin_l)/2., hmCurrent->GetBinCenter(midbin_r)+hmCurrent->GetBinWidth(midbin_r)/2.)/hmCurrent->GetBinWidth(1);
	   Double_t bgsumerr = 0;
	   if(!kFit) bgsumerr = 0;
	   else {
		TMatrixDSym covbg(6);
		if(kDoubGauss){
		   cout<<"Double Gaussian fitting..."<<endl;
		   pDouble->Print("V");
		   TMatrixDSym cov = pDouble->GetCovarianceMatrix();
		   TMatrixDSym covtmp(3);
		   cov.GetSub(5,7,covtmp);  //get the reduced covariance matrix for b.g.
		   //covtmp.Print();
		   covtmp.ResizeTo(covbg);
		   covbg=covtmp;
		   covbg.Print();
		}
		else{
		   cout<<"Single Gaussian fitting..."<<endl;
		   pSingle->Print("V");
		   TMatrixDSym cov = pSingle->GetCovarianceMatrix();
		   TMatrixDSym covtmp(3);
		   cov.GetSub(3,5,covtmp);  //get the reduced covariance matrix for b.g.
		   //covtmp.Print();
		   covtmp.ResizeTo(covbg);
		   covbg=covtmp;
		   covbg.Print();
		}
		Double_t bgsumerr = fbg->IntegralError(hmCurrent->GetBinCenter(midbin_l)-hmCurrent->GetBinWidth(midbin_l)/2., hmCurrent->GetBinCenter(midbin_r)+hmCurrent->GetBinWidth(midbin_r)/2., fbg->GetParameters(), covbg.GetMatrixArray())/hmCurrent->GetBinWidth(1);
	   }
	   rawyield_cf[iIM][iPt] = midsum - bgsum;
	   staterr_cf[iIM][iPt] = sqrt(midsumerr2 + bgsumerr*bgsumerr);
	   cout<<"yield (signal counting - bg fitting): "<<rawyield_cf[iIM][iPt]<<" "<<staterr_cf[iIM][iPt]<<endl;

	   //yield from fitting (for checking only! not used in final yield)
	   if(kDoubGauss) {
		rawyield_ff[iIM][iPt] = fdoubgausbg->GetParameter(0) + fdoubgausbg->GetParameter(3);
		staterr_ff[iIM][iPt] = sqrt(fdoubgausbg->GetParError(0)*fdoubgausbg->GetParError(0)+fdoubgausbg->GetParError(3)*fdoubgausbg->GetParError(3)); //still problematic, since two parameters have correlation, but this is not used anyway.
	   }
	   else {
		rawyield_ff[iIM][iPt] = fsinggausbg->GetParameter(0);
		staterr_ff[iIM][iPt] = fsinggausbg->GetParError(0);
	   }
	   cout<<"yield (signal fitting - bg fitting): "<<rawyield_ff[iIM][iPt]<<" "<<staterr_ff[iIM][iPt]<<endl;

	   //if fitting is good, final yield is from signal counting and pol b.g.
	   //otherwise, final yield is signal counting and side-band b.g.
	   if(kFit){
		rawyield[iIM][iPt] = rawyield_cf[iIM][iPt];
		staterr[iIM][iPt] = staterr_cf[iIM][iPt];
	   }
	   else{
		rawyield[iIM][iPt] = rawyield_cc[iIM][iPt];
		staterr[iIM][iPt] = staterr_cc[iIM][iPt];
		rawyield_cf[iIM][iPt] = rawyield_cc[iIM][iPt];
		staterr_cf[iIM][iPt] = staterr_cc[iIM][iPt];
	   }

	   gPad->Update();  //once we are done with a pad, we draw it asap.
	   if(iIM%Ncells==Ncells-1||iIM==kCentBin-1) {
		c1->cd(); //this line is ESSENTIAL for pdf->NewPage() to behave normally.
		c1->Update();
		if(!(iPt==kPtBin&&iIM==kCentBin-1))pdf->NewPage();
	   }
	}
   }

   pdf->Close();
   delete pdf;
   delete c1;

   TString oname = "auau"+Ecm+"_ks_yield_"+cuttag+".txt";
   ofstream oyield(oname);
   for(int iIM=0;iIM<kCentBin;iIM++)
	for(int iPt=0;iPt<kPtBin;iPt++)
	   oyield<<iIM<<" "<<iPt<<" "<<rawyield[iIM][iPt]<<" "<<staterr[iIM][iPt]<<" "<<rawyield_cf[iIM][iPt]<<" "<<staterr_cf[iIM][iPt]<<" "<<rawyield_cc[iIM][iPt]<<" "<<staterr_cc[iIM][iPt]<<endl;
   oyield.close();

   TString oname = "auau"+Ecm+"_ks_invmass_peak_sigma_"+cuttag+".txt";
   ofstream oyield(oname);
   for(int iIM=0;iIM<kCentBin;iIM++)
	for(int iPt=0;iPt<kPtBin;iPt++)
	   oyield<<iIM<<" "<<(ptbd[iPt]+ptbd[iPt+1])/2<<" "<<invmass_ff[iIM][iPt]<<" "<<invmasserr_ff[iIM][iPt]<<" "<<sigma_ff[iIM][iPt]<<" "<<sigmaerr_ff[iIM][iPt]<<endl;
   oyield.close();

   ihm.Close();
}
