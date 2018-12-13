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

   Float_t ptcenter[kPtBin],pterr[kPtBin];
   for(int i=0;i<kPtBin;i++){
	ptcenter[i]=(ptbd[i+1]+ptbd[i])/2.;
	pterr[i]=(ptbd[i+1]-ptbd[i])/2.;
   }

   Double_t fitparms[kCentBin*kParms];
   
   Float_t ptbin[kCentBin][kPtBin];
   //Float_t ptmean[kCentBin][kPtBin];

   Float_t yield[kCentBin][kPtBin];
   Float_t staterr[kCentBin][kPtBin];

   TString lowname = "auau"+Ecm+"_la_spectra_"+cuttag+"_low.txt";
   TString highname = "auau"+Ecm+"_la_spectra_"+cuttag+"_high.txt";
   ifstream lspectra(lowname);
   ifstream hspectra(highname);
   for(int i=0;i<kCentBin;i++){
	TString tmp;
	lspectra>>tmp;
	hspectra>>tmp;
	Float_t ftmp;
	for(int j=0;j<kPtBin;j++){
	   if(j<8){   //FIXME: be careful here!!!
		lspectra>>ptbin[i][j]>>yield[i][j]>>staterr[i][j];
		hspectra>>ftmp>>ftmp>>ftmp;
	   }
	   else {
		lspectra>>ftmp>>ftmp>>ftmp;
		hspectra>>ptbin[i][j]>>yield[i][j]>>staterr[i][j];
	   }
	}
   }
   lspectra.close();
   hspectra.close();

   TString oname = "auau"+Ecm+"_la_spectra_"+cuttag+".txt";
   ofstream oyield(oname);
   for(int i=0;i<kCentBin;i++){
	oyield<<"#---------"<<CentName[i]<<"---------"<<endl;
	for(int j=0;j<kPtBin;j++){
	   if(j>=0&&j<kPtBin)oyield<<ptbin[i][j]<<" "<<yield[i][j]<<" "<<staterr[i][j]<<endl;
	   yield[i][j] = yield[i][j]*pow(10,i-kCentBin+1);
	   staterr[i][j] = staterr[i][j]*pow(10,i-kCentBin+1);
	}
   }
   oyield.close();

   Float_t ldndy[kCentBin],ldndybelow[kCentBin],ldndysum[kCentBin],ldndyabove[kCentBin];
   Float_t ldndyerr[kCentBin],ldndybelowerr[kCentBin],ldndysumerr[kCentBin],ldndyaboveerr[kCentBin];
   Float_t hdndy[kCentBin],hdndybelow[kCentBin],hdndysum[kCentBin],hdndyabove[kCentBin];
   Float_t hdndyerr[kCentBin],hdndybelowerr[kCentBin],hdndysumerr[kCentBin],hdndyaboveerr[kCentBin];
   TString lowname = "auau"+Ecm+"_la_cent_"+cuttag+"_low.txt";
   TString highname = "auau"+Ecm+"_la_cent_"+cuttag+"_high.txt";
   ifstream lcent(lowname);
   ifstream hcent(highname);
   for(int i=0;i<kCentBin;i++){
	lcent>>ldndy[i]>>ldndyerr[i]>>ldndysum[i]>>ldndysumerr[i]>>ldndybelow[i]>>ldndybelowerr[i]>>ldndyabove[i]>>ldndyaboveerr[i];
	hcent>>hdndy[i]>>hdndyerr[i]>>hdndysum[i]>>hdndysumerr[i]>>hdndybelow[i]>>hdndybelowerr[i]>>hdndyabove[i]>>hdndyaboveerr[i];
   }
   lcent.close();
   hcent.close();

   Float_t dndy[kCentBin];
   Float_t dndyerr[kCentBin];
   Float_t dndybelow[kCentBin],dndyabove[kCentBin],dndysum[kCentBin];
   Float_t dndybelowerr[kCentBin],dndyaboveerr[kCentBin],dndysumerr[kCentBin];
   Float_t meanpt[kCentBin];
   Float_t meanpterr[kCentBin];

   TGraph *gr[kCentBin];
   for(int i=0;i<kCentBin;i++)
	if(i==5) gr[i] = new TGraphErrors(kPtBin+4,ptbin[i]+4,yield[i]+4,0,staterr[i]+4);
	else gr[i] = new TGraphErrors(kPtBin,ptbin[i],yield[i],0,staterr[i]);

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
	if(icent==5) fm->GetYield(gr[icent],ptcenter+4, pterr+4,intfunc,fitr,yld,ylderr,0,10,partyld,partylderr);
	else fm->GetYield(gr[icent],ptcenter, pterr,intfunc,fitr,yld,ylderr,0,10,partyld,partylderr);
	dndy[icent]=yld;dndyerr[icent]=ylderr;
	dndysum[icent]=partyld[0];dndysumerr[icent]=partylderr[0];
	dndybelow[icent]=partyld[1];dndybelowerr[icent]=partylderr[1];
	dndyabove[icent]=partyld[2];dndyaboveerr[icent]=partylderr[2];

	//dndybelow[icent]=ldndybelow[icent]*pow(10,icent-kCentBin+1);dndybelowerr[icent]=ldndybelowerr[icent]*pow(10,icent-kCentBin+1);
	dndyabove[icent]=hdndyabove[icent]*pow(10,icent-kCentBin+1);dndyaboveerr[icent]=hdndyaboveerr[icent]*pow(10,icent-kCentBin+1);
	dndy[icent] = dndysum[icent] + dndybelow[icent] + dndyabove[icent];
	dndyerr[icent] = TMath::Sqrt(dndysumerr[icent]*dndysumerr[icent] + dndybelowerr[icent]*dndybelowerr[icent] + dndyaboveerr[icent]*dndyaboveerr[icent]);

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

   TString ofigname = "auau"+Ecm+"_la_spectra_"+cuttag+".pdf";
   c1->SaveAs(ofigname);
   TString ointyieldname = "auau"+Ecm+"_la_cent_"+cuttag+".txt";
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

