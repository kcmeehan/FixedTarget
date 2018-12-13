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
   //fitfunc = fm->GetTsallisBW (0.497614, 0.1, 0.2,1.00001, 20);
   //fitfunc = fm->GetBGBW (0.497614, 0.2, 0.2, 20);
   //fitfunc = fm->GetBoltzmann (0.497614, 0.2, 20);
   //fitfunc = fm->GetLevi (0.497614, 0.2, 20000, 1.0);
   //const int kParms = 3;
   fitfunc = fm->GetMTExp (0.497614, 0.2, 20);
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
   meanfuncname+="*2*3.1415926*x*(sqrt(0.497614*0.497614+x*x)-0.497614)";
   cout<<meanfuncname<<endl;
   TF1* meanfunc = new TF1("meanfunc",meanfuncname);

   gROOT->ProcessLine(".L ./parameters.C");

   float yfit[kCentBin][kPtBin],yfiterr[kCentBin][kPtBin];
   float ycf[kCentBin][kPtBin],ycferr[kCentBin][kPtBin];
   float ycc[kCentBin][kPtBin],yccerr[kCentBin][kPtBin];
   int i,j;
   float rmc,rrc,r2mc,r2rc;
   TString iyieldname = "auau"+Ecm+"_ks_yield_"+cuttag+".txt";
   ifstream iyield(iyieldname);
   for(int i=0;i<kCentBin;i++)
	for(int j=0;j<kPtBin;j++){
	   iyield>>i>>j>>yfit[i][j]>>yfiterr[i][j]>>ycf[i][j]>>ycferr[i][j]>>ycc[i][j]>>yccerr[i][j];
	   //yfiterr[i][j] = sqrt(yfiterr[i][j]*yfiterr[i][j] + (ycf[i][j]-ycc[i][j])*(ycf[i][j]-ycc[i][j]));
	}
   iyield.close();

   float wgt[kCentBin][kPtBin],wgtrelerr[kCentBin][kPtBin],wgterr[kCentBin][kPtBin];
   float expwgt[kCentBin][kPtBin],expwgtrelerr[kCentBin][kPtBin],expwgterr[kCentBin][kPtBin];
   TString ifile = "output/weight_k0s_"+cuttag+"_high_fp.txt";
   TString iexpfile = "output/weight_k0s_"+cuttag+"_high_exp.txt";
   ifstream iweight(ifile);
   ifstream iexpweight(iexpfile);
   for(int i=0;i<kCentBin;i++)
	for(int j=0;j<kPtBin;j++){
	   iweight>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>wgt[i][j]>>wgtrelerr[i][j];
	   iexpweight>>i>>j>>rmc>>rrc>>r2mc>>r2rc>>expwgt[i][j]>>expwgtrelerr[i][j];
	   wgterr[i][j]=wgt[i][j]*wgtrelerr[i][j];
	   expwgterr[i][j]=expwgt[i][j]*expwgtrelerr[i][j];
	   if(j<10){
		float wflat = 1.0/wgterr[i][j]/wgterr[i][j];
		float wexp  = 1.0/expwgterr[i][j]/expwgterr[i][j];
		float wtot  = wflat + wexp;
		wgt[i][j] = (wgt[i][j]*wflat + expwgt[i][j]*wexp)/wtot;
		wgterr[i][j] = 1.0/sqrt(wtot);
		wgtrelerr[i][j] = wgterr[i][j]/wgt[i][j];
	   }
	   if(wgt[i][j]==0)wgt[i][j]==-1;
	}
   iweight.close();
   iexpweight.close();

   Float_t ptcenter[kPtBin],pterr[kPtBin];
   for(int i=0;i<kPtBin;i++){
	ptcenter[i]=(ptbd[i+1]+ptbd[i])/2.;
	pterr[i]=(ptbd[i+1]-ptbd[i])/2.;
   }

   Double_t fitparms_cut0[50]={0.000109687,0.179333,0.00258756,0.176135,0.0154873,0.197197,0.256709,0.191183,2.0514,0.214666,44.2453,0.198797};
   Double_t fitparms_cut1[50]={7.24463e-05,0.213478,0.00223261,0.181386,0.0239488,0.187123,0.306231,0.189311,3.58209,0.195722,52.8553,0.194734};
   Double_t fitparms_cut2[50]={0.000144013,0.177897,0.0016719,0.187966,0.0245943,0.181432,0.374655,0.178124,5.06566,0.179818,67.5093,0.181335};
   Double_t fitparms_cut3[50]={0.00035755,0.137704,0.00298244,0.154021,0.0407481,0.155277,0.465684,0.160761,6.71942,0.159098,88.748,0.160478};
   Double_t fitparms_cut4[50]={0.000274287,0.127067,0.00528081,0.126861,0.0896214,0.124478,0.717835,0.13478,7.75087,0.138972,110.754,0.138206};
   Double_t fitparms_cut5[50]={9.19878e-05,0.198893,0.001478,0.191842,0.0230069,0.183863,0.236085,0.197108,3.6718,0.194513,45.7291,0.199304};
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

   TString ihistfile = "output/auau"+Ecm+".mb.ks."+cuttag+".histo.root";
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

   TString oname = "auau"+Ecm+"_ks_spectra_"+cuttag+"_high.txt";
   ofstream oyield(oname);

   float br=0.6920;
   Float_t yield[kCentBin][kPtBin];
   Float_t staterr[kCentBin][kPtBin];
   for(int i=0;i<kCentBin;i++){
	oyield<<"#---------"<<CentName[i]<<"---------"<<endl;
	for(int j=0;j<kPtBin;j++){
	   //yield[i][j] = yfit[i][j]/br/2/0.25/TMath::Pi()/tot[i]/ptbin[i][j]/(ptbd[j+1]-ptbd[j])*pow(10,i-kCentBin+1);
	   yield[i][j] = yfit[i][j]/wgt[i][j]/br/2/0.25/TMath::Pi()/tot[i]/ptbin[i][j]/(ptbd[j+1]-ptbd[j])*pow(10,i-kCentBin+1);
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
	gr[i] = new TGraphErrors(kPtBin,ptbin[i],yield[i],0,staterr[i]);

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

   gr[0]->SetTitle("K^{0}_{S} spectra, Au+Au 4.5 GeV");
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
	if(icent==0)fitmax=2.0;
	else fitmax=2.0;
	/*
	if(icent==0)fitfunc->SetParLimits(1,23,25);
	else if(icent==1)fitfunc->SetParLimits(1,20,40);
	else fitfunc->SetParLimits(1,20,40);
	*/
	TFitResultPtr fitr = gr[icent]->Fit(fitfunc,"SN","",0.2,fitmax);
	fitfunc->DrawClone("same");
	fitfunc->GetParameters(&fitparms[icent*kParms]);

	intfunc->SetParameters(fitfunc->GetParameters());
	intfunc->SetParErrors(fitfunc->GetParErrors());
	Double_t yld,ylderr;
	Double_t partyld[3],partylderr[3];
	fm->GetYield(gr[icent],ptcenter, pterr,intfunc,fitr,yld,ylderr,0,10,partyld,partylderr);
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

   TString ofigname = "auau"+Ecm+"_ks_spectra_"+cuttag+"_high.pdf";
   c1->SaveAs(ofigname);
   TString ointyieldname = "auau"+Ecm+"_ks_cent_"+cuttag+"_high.txt";
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

   TString ofitparname = "auau"+Ecm+"_ks_fit_"+cuttag+"_high.txt";
   ofstream ofitpar(ofitparname);
   for(int i=0;i<kCentBin;i++){
	for(int j=0;j<kParms;j++)ofitpar<<fitparms[i*kParms+j]<<"\t";
	ofitpar<<endl;
   }
   ofitpar.close();

}

