{
   gROOT->Reset();

   gROOT->ProcessLine(".L ./func.C+");

   TString cuttag("cut0");
   TString Ecm("5");

   VarType_t var = kOneOverPtdNdpt;
   TF1* funcpar = 0;
   Width_t inwidth = 1;
   TF1* fitfunc = 0;
   func *fm = new func(funcpar, inwidth, var);
   //fitfunc = fm->GetTsallisBW (1.115684, 0.1, 0.2,1.00001, 20);
   //fitfunc = fm->GetBGBW (1.115684, 0.2, 0.2, 20);
   fitfunc = fm->GetBoltzmann (1.115684, 0.2, 20);
   //fitfunc = fm->GetLevi (1.115684, 0.2, 20000, 1.0);
   //const int kParms = 3;
   //fitfunc = fm->GetMTExp (1.115684, 0.2, 20);
   const int kParms = 2;
   cout<<fitfunc->Eval(1)<<" "<<fitfunc->GetName()<<endl;
   fitfunc->SetRange(0,6.);
   fitfunc->Draw();

   TString intfuncname(fitfunc->GetName());
   intfuncname+="*2*3.1415926*x";
   cout<<intfuncname<<endl;
   TF1* intfunc = new TF1("intfunc",intfuncname);

   TString meanfuncname(fitfunc->GetName());
   //meanfuncname+="*2*3.1415926*x*x";
   meanfuncname+="*2*3.1415926*x*(sqrt(1.115684*1.115684+x*x)-1.115684)";
   cout<<meanfuncname<<endl;
   TF1* meanfunc = new TF1("meanfunc",meanfuncname);

   gROOT->ProcessLine(".L ./parameters.C");

   float yfit[kCentBin][kPtBin],yfiterr[kCentBin][kPtBin];
   float ycf[kCentBin][kPtBin],ycferr[kCentBin][kPtBin];
   float ycc[kCentBin][kPtBin],yccerr[kCentBin][kPtBin];
   int i,j;
   float rmc,rrc,r2mc,r2rc;
   TString iyieldname = "auau"+Ecm+"_la_yield_"+cuttag+".txt";
   ifstream iyield(iyieldname);
   for(int i=0;i<kCentBin;i++)
	for(int j=0;j<kPtBin;j++){
	   iyield>>i>>j>>yfit[i][j]>>yfiterr[i][j]>>ycf[i][j]>>ycferr[i][j]>>ycc[i][j]>>yccerr[i][j];
	   //yfiterr[i][j] = sqrt(yfiterr[i][j]*yfiterr[i][j] + (ycf[i][j]-ycc[i][j])*(ycf[i][j]-ycc[i][j]));
	}
   iyield.close();

   float wgt[kCentBin][kPtBin],wgtrelerr[kCentBin][kPtBin],wgterr[kCentBin][kPtBin];
   float expwgt[kCentBin][kPtBin],expwgtrelerr[kCentBin][kPtBin],expwgterr[kCentBin][kPtBin];
   TString ifile = "output/weight_la_"+cuttag+"_low_fp.txt";
   TString iexpfile = "output/weight_la_"+cuttag+"_low_exp.txt";
   ifstream iweight(ifile);
   ifstream iexpweight(iexpfile);
   for(int i=0;i<kCentBin;i++)
	for(int j=0;j<kPtBin;j++){
	   iweight>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>wgt[i][j]>>wgtrelerr[i][j];
	   iexpweight>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>expwgt[i][j]>>expwgtrelerr[i][j];
	   wgterr[i][j]=wgt[i][j]*wgtrelerr[i][j];
	   expwgterr[i][j]=expwgt[i][j]*expwgtrelerr[i][j];
	   if(wgterr[i][j]==0||expwgterr[i][j]==0){
		wgt[i][j]=0;
		wgtrelerr[i][j]=0;
		continue;
	   }
	   if(j<13){
		float wflat = 1.0/wgterr[i][j]/wgterr[i][j];
		float wexp  = 1.0/expwgterr[i][j]/expwgterr[i][j];
		float wtot  = wflat + wexp;
		wgt[i][j] = (wgt[i][j]*wflat + expwgt[i][j]*wexp)/wtot;
		wgterr[i][j] = 1.0/sqrt(wtot);
		wgtrelerr[i][j] = wgterr[i][j]/wgt[i][j];
	   }
	   //if(wgt[i][j]==0)wgt[i][j]==-1;
	}
   iweight.close();
   iexpweight.close();

   float fderr;
   float fd[kCentBin][kPtBin],fdrelerr[kCentBin][kPtBin];
   float fdxi0[kCentBin][kPtBin],fdxi0relerr[kCentBin][kPtBin];
   TString ilafdfile = "output/weight_lafd_"+cuttag+"_fp_combined.txt";
   TString ila0fdfile = "output/weight_la0fd_"+cuttag+"_fp_combined.txt";
   ifstream ifd(ilafdfile);
   ifstream ifdxi0(ila0fdfile);
   for(int i=0;i<kCentBin;i++)
      for(int j=0;j<kPtBin;j++){
         ifd>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>fd[i][j]>>fdrelerr[i][j];
         ifdxi0>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>fdxi0[i][j]>>fdxi0relerr[i][j];
         fderr = sqrt(fdrelerr[i][j]*fd[i][j]*fdrelerr[i][j]*fd[i][j]+fdxi0relerr[i][j]*fdxi0[i][j]*fdxi0relerr[i][j]*fdxi0[i][j])/2.0;
         fd[i][j]=(fd[i][j]+fdxi0[i][j])/2.0;
         fdrelerr[i][j]=fderr/fd[i][j];
      }
   ifd.close();
   ifdxi0.close();

   Float_t ptcenter[kPtBin],pterr[kPtBin];
   for(int i=0;i<kPtBin;i++){
	ptcenter[i]=(ptbd[i+1]+ptbd[i])/2.;
	pterr[i]=(ptbd[i+1]-ptbd[i])/2.;
   }

   Double_t fitparms_cut0[50]={0.0189045,0.15277,0.0201377,0.197553,0.373155,0.190011,8.74182,0.182405,12.4537,0.229874,294.693,0.217672};
   Double_t fitparms_cut1[50]={0.00510345,0.171619,0.067564,0.169922,0.957513,0.17379,7.482,0.185464,98.3905,0.185653,1455.69,0.185748};
   Double_t fitparms_cut2[50]={0.00733846,0.16211,0.069449,0.165728,0.750533,0.171278,9.18304,0.173976,134.269,0.173764,1990.52,0.17296};
   Double_t fitparms_cut3[50]={0.0157371,0.143511,0.338219,0.138163,2.34015,0.148154,26.8311,0.150519,192.273,0.159683,2466.97,0.160234};
   Double_t fitparms_cut4[50]={0.084253,0.117155,0.589394,0.1248,4.25477,0.130476,47.3281,0.132486,807.5,0.129353,26668.3,0.118332};
   Double_t fitparms_cut5[50]={0.00296345,0.181528,0.0439767,0.182838,0.451377,0.18899,5.9003,0.191637,45.5087,0.204948,719.16,0.206377};
   Double_t * fitparms;
   if(cuttag=="cut0")fitparms = fitparms_cut0;
   elseif(cuttag=="cut1")fitparms = fitparms_cut1;
   elseif(cuttag=="cut2")fitparms = fitparms_cut2;
   elseif(cuttag=="cut3")fitparms = fitparms_cut3;
   elseif(cuttag=="cut4")fitparms = fitparms_cut4;
   else fitparms=fitparms_cut5;


   Float_t ptbin[kCentBin][kPtBin];
   Float_t ptmean[kCentBin][kPtBin];
   for(int i=0;i<kCentBin;i++){
	fitfunc->SetParameters(&fitparms[i*kParms]);
	intfunc->SetParameters(&fitparms[i*kParms]);
	meanfunc->SetParameters(&fitparms[i*kParms]);
	for(int j=0;j<kPtBin;j++){
	   //x_c
	   //ptbin[i][j]=(ptbd[j+1]+ptbd[j])/2.;
	   
	   //x_avg
	   //ptbin[i][j]=meanfunc->Integral(ptbd[j],ptbd[j+1])/intfunc->Integral(ptbd[j],ptbd[j+1]);
	   ptmean[i][j]=meanfunc->Integral(ptbd[j],ptbd[j+1])/intfunc->Integral(ptbd[j],ptbd[j+1]);
	   
	   //if(j<2)continue;
	   //x_lw, assuming a decreasing spectra function (dn/dpt)
	   float binavg=fitfunc->Integral(ptbd[j],ptbd[j+1])/(ptbd[j+1]-ptbd[j]);
	   float left = ptbd[j],right=ptbd[j+1];
	   root = (left+right)/2.;
	   while( fabs(fitfunc->Eval(root) - binavg) > 1e-4 * binavg ){
		if(fitfunc->Eval(root)>binavg)left = root;
		else right = root;
		root = (left+right)/2.;
	   }
	   ptbin[i][j]=root;
	}
   }

   TString ihistfile = "output/auau"+Ecm+".mb.la."+cuttag+".histo.root";
   TFile ihm(ihistfile);
   const int kGroup=1;
   TH1D * hmCent[kGroup];
   Double_t tot[kCentBin];
   for(Int_t i=0;i<kCentBin;i++)tot[i]=0;
   for(Int_t i=0;i<kGroup;i++){
	ihm.GetObject(Form("hmCent%d",i),hmCent[i]);
	for(Int_t j=0;j<kCentBin;j++){
	   int cb = (int)(centbd[j]+1.0); int ce = (int)(centbd[j+1]+1.0);
	   for(Int_t k=cb; k<ce; k++)tot[j]+=hmCent[i]->GetBinContent(k+1);
	   cout<<tot[j]<<endl;
	}
   }

   TString oname = "auau"+Ecm+"_la_spectra_"+cuttag+"_low.txt";
   ofstream oyield(oname);

   float br=0.99887*0.639;
   Float_t xidndy[kCentBin];
   Float_t xidndyerr[kCentBin];
   TString xiname = "input/auau"+Ecm+"_xi_cent_cut0.txt";
   ifstream xicent(xiname);
   for(int i=0;i<kCentBin;i++){
	float ftmp;
	xicent>>xidndy[i]>>xidndyerr[i]>>ftmp>>ftmp>>ftmp>>ftmp>>ftmp>>ftmp;
   }
   xicent.close();

   Float_t yield[kCentBin][kPtBin];
   Float_t staterr[kCentBin][kPtBin];
   for(int i=0;i<kCentBin;i++){
	oyield<<"#---------"<<CentName[i]<<"---------"<<endl;
	for(int j=0;j<kPtBin;j++){
         float fdxi = 2.0*tot[i]*0.25*xidndy[i]*fd[i][j]*br;
         float fdxierr = fdxi*sqrt(xidndyerr[i]*xidndyerr[i]/xidndy[i]/xidndy[i]+fdrelerr[i][j]*fdrelerr[i][j]);
         if(yfit[i][j]>0)cout<<i<<" "<<j<<" "<<fdxi/yfit[i][j]<<endl;
         yfit[i][j] -= fdxi;
         yfiterr[i][j] = sqrt(yfiterr[i][j]*yfiterr[i][j]+fdxierr*fdxierr);
	   
	   //yield[i][j] = yfit[i][j]/br/2/0.25/TMath::Pi()/tot[i]/ptbin[i][j]/(ptbd[j+1]-ptbd[j])*pow(10,i-kCentBin+1);
	   if(wgt[i][j]==0) yield[i][j] = 0;
	   else yield[i][j] = yfit[i][j]/wgt[i][j]/br/2/0.25/TMath::Pi()/tot[i]/ptbin[i][j]/(ptbd[j+1]-ptbd[j])*pow(10,i-kCentBin+1);
	   //yield[i][j] = yfit[i][j]/wgt[i][j]/br/2/0.25/TMath::Pi()/tot[i]/ptbin[i][j]/(ptbd[j+1]-ptbd[j]);
	   staterr[i][j] = yield[i][j]*sqrt(yfiterr[i][j]*yfiterr[i][j]/yfit[i][j]/yfit[i][j]+wgtrelerr[i][j]*wgtrelerr[i][j]);
	   if(j>=0&&j<kPtBin)oyield<<ptbin[i][j]<<" "<<yield[i][j]/pow(10,i-kCentBin+1)<<" "<<staterr[i][j]/pow(10,i-kCentBin+1)<<endl;
	}
   }

   Float_t dndy[kCentBin];
   Float_t dndyerr[kCentBin];
   Float_t dndybelow[kCentBin],dndyabove[kCentBin],dndysum[kCentBin];
   Float_t dndybelowerr[kCentBin],dndyaboveerr[kCentBin],dndysumerr[kCentBin];
   Float_t meanpt[kCentBin];
   Float_t meanpterr[kCentBin];

   TGraph *gr[kCentBin];
   for(int i=0;i<kCentBin;i++)
if(i==5)	gr[i] = new TGraphErrors(kPtBin+4,ptbin[i]+4,yield[i]+4,0,staterr[i]+4);
else 		gr[i] = new TGraphErrors(kPtBin,ptbin[i],yield[i],0,staterr[i]);

   gStyle->SetCanvasDefH(800);
   gStyle->SetCanvasDefW(700);
   gStyle->SetPadGridX(0);
   gStyle->SetPadGridY(0);
   //gStyle->SetLabelOffset(.004,"X");
   //gStyle->SetTitleOffset(0.8,"X");
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleOffset(1.3,"Y");
   gStyle->SetLabelSize(.03,"Y");
   gStyle->SetFuncWidth(0);

   gStyle->SetFillColor(10);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetNdivisions(205,"X");
   gStyle->SetNdivisions(205,"Y");

   c1 = new TCanvas("c1","c1");
   c1->SetLogy();
   c1->SetLeftMargin(0.12);
   c1->SetRightMargin(0.09);
   c1->SetFillColor(10);

   gr[0]->SetTitle("#Lambda spectra, Au+Au 4.5 GeV");
   gr[0]->GetXaxis()->SetLimits(0.,7.5);
   gr[0]->GetXaxis()->SetNdivisions(510);
   gr[0]->GetYaxis()->SetNdivisions(510);
   gr[0]->SetMinimum(1e-14);
   gr[0]->SetMaximum(100);
   gr[0]->GetXaxis()->SetTitle("P_{T} (GeV/c)");
   gr[0]->GetYaxis()->SetTitle("1/(N_{ev}2#piP_{T})dN^{2}/dP_{T}dy (GeV/c)^{-2}");

   for(int i=0;i<kCentBin;i++) gr[i]->SetMarkerColor(colorwheel[i]);
   for(int i=0;i<kCentBin;i++){
	gr[i]->SetMarkerSize(1.2);
	gr[i]->SetMarkerStyle(20);

	if(i==0) gr[i]->Draw("AP");
	else gr[i]->Draw("PSAME");

   }

   fitfunc.SetLineWidth(2);
   fitfunc.SetLineStyle(7);
   fitfunc.SetLineColor(kBlue);
   
   for(int icent = 0; icent<kCentBin; icent++){
	double fitmax;
	if(icent==0)fitmax=2.6;
	else fitmax=2.6;
	TFitResultPtr fitr = gr[icent]->Fit(fitfunc,"SN","",0.6,fitmax);
	fitfunc->DrawClone("same");
	fitfunc->GetParameters(&fitparms[icent*kParms]);

	intfunc->SetParameters(fitfunc->GetParameters());
	intfunc->SetParErrors(fitfunc->GetParErrors());
	Double_t yld,ylderr;
	Double_t partyld[3],partylderr[3];
	if(icent==5)fm->GetYield(gr[icent],ptcenter+4, pterr+4,intfunc,fitr,yld,ylderr,0,10,partyld,partylderr);
	else fm->GetYield(gr[icent],ptcenter, pterr,intfunc,fitr,yld,ylderr,0,10,partyld,partylderr);
	dndy[icent]=yld;dndyerr[icent]=ylderr;
	dndysum[icent]=partyld[0];dndysumerr[icent]=partylderr[0];
	dndybelow[icent]=partyld[1];dndybelowerr[icent]=partylderr[1];
	dndyabove[icent]=partyld[2];dndyaboveerr[icent]=partylderr[2];

	/*
	meanfunc->SetParameters(fitfunc->GetParameters());
	meanfunc->SetParErrors(fitfunc->GetParErrors());
	fm->GetMeanPt(gr[icent],ptcenter, pterr, ptmean[icent], meanfunc,fitr,yld,ylderr,0,10);
	meanpt[icent]=yld;meanpterr[icent]=ylderr;
	//float mptrelerr = sqrt(pow(meanpterr[icent]/meanpt[icent],2)+pow(dndyerr[icent]/dndy[icent],2));

	meanpt[icent]=meanpt[icent]/dndy[icent];
	meanpterr[icent]=meanpterr[icent]/dndy[icent];
	//meanpterr[icent]=meanpt[icent]*mptrelerr;

	cout<<"Mean Mt "<<meanpt[icent]<<" "<<meanfunc->Integral(0,5)/intfunc->Integral(0,5)<<endl;
	*/
   }

   leg = new TLegend(0.6163793,0.6658031,0.8735632,0.8639896,NULL,"brNDC");
   for(int i=kCentBin-1;i>=0;i--)
	if(i-kCentBin+1==0) leg->AddEntry(gr[i],Form("%s",CentName[i]),"P");
	else leg->AddEntry(gr[i],Form("%s (x10^{%d})",CentName[i],i-kCentBin+1),"P");
   leg->SetBorderSize(2);
   leg->Draw();

   TString ofigname = "auau"+Ecm+"_la_spectra_"+cuttag+"_low.pdf";
   c1->SaveAs(ofigname);
   TString ointyieldname = "auau"+Ecm+"_la_cent_"+cuttag+"_low.txt";
   ofstream ointyield(ointyieldname);
   for(int i=0;i<kCentBin;i++)
      ointyield<<dndy[i]/pow(10,i-kCentBin+1)<<"\t"<<dndyerr[i]/pow(10,i-kCentBin+1)
         <<"\t"<<dndysum[i]/pow(10,i-kCentBin+1)<<"\t"<<dndysumerr[i]/pow(10,i-kCentBin+1)
         <<"\t"<<dndybelow[i]/pow(10,i-kCentBin+1)<<"\t"<<dndybelowerr[i]/pow(10,i-kCentBin+1)
         <<"\t"<<dndyabove[i]/pow(10,i-kCentBin+1)<<"\t"<<dndyaboveerr[i]/pow(10,i-kCentBin+1)
         <<endl;
   ointyield.close();
   //for(int i=0;i<kCentBin;i++)cout<<meanpt[i]<<"   "<<meanpterr[i]<<endl;
   for(int i=0;i<kCentBin;i++)
	for(int j=0;j<kParms;j++)cout<<fitparms[i*kParms+j]<<",";
   cout<<endl;

   TString ofitparname = "auau"+Ecm+"_la_fit_"+cuttag+"_low.txt";
   ofstream ofitpar(ofitparname);
   for(int i=0;i<kCentBin;i++){
	for(int j=0;j<kParms;j++)ofitpar<<fitparms[i*kParms+j]<<"\t";
	ofitpar<<endl;
   }
   ofitpar.close();

}

