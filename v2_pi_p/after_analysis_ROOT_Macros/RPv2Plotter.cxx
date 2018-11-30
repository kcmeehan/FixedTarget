
Double_t fitFunc(Double_t *x, Double_t *par)
{
   Double_t fitVal = par[0]*(1.+ 2.0*par[1]*TMath::Cos(2.0*x[0]) + 2.0*par[2]*TMath::Cos(4.0*x[0]) );
	// Double_t fitVal = par[0]*(1.+ 2.0*par[1]*TMath::Cos(2.0*x[0]));
  return fitVal;
}


void RPv2Plotter(char *filename,char *plotidpt,char *plotidmt,char *id,int markerid = 20, int colorid = 20){
	
	TFile *f = new TFile(filename);
	TFile *g = new TFile(Form("%sv2RP.root",id),"recreate");

	TH2D *dphiPt = (TH2D*)f->Get(plotidpt);
	TH2D *dphiMt = (TH2D*)f->Get(plotidmt);
	f->GetListOfKeys()->Print();
	TProfile *res = (TProfile*)f->Get("He3CosRes_eta");
	//res->Draw();
	Double_t corRes = sqrt(res->GetBinContent(1));
	Double_t corResE = sqrt(res->GetBinError(1));
	cout<<corRes<<endl;
	//corRes = sqrt(0.0175);
	TGraphErrors *g1pt = new TGraphErrors();
	TGraphErrors *g2pt = new TGraphErrors();
	TGraphErrors *g1mt = new TGraphErrors();
	TGraphErrors *g2mt = new TGraphErrors();
	TGraphErrors *gmtscaled = new TGraphErrors();
	TH1D *resh = new  TH1D("resolution1","resolution1",9,0,30);
	TH1D *resh1 = new  TH1D("resolution","resolution",res->GetNbinsX(),0,30);
	const int A = dphiPt->GetNbinsY();
	const int B = dphiMt->GetNbinsY();
	TH1D *dphi[A];
	TH1D *dphi1[B];
	TH1D *pt;
	TH1D *mt;
	pt = dphiPt->ProjectionY();
	mt = dphiMt->ProjectionY();
	pt->Write();
	mt->Write();
	dphiPt->Write();
	dphiMt->Write();
	double wS   = 0.0;
	double wpt  = 0.0;
	double v2S  = 0.0;
	double v2SE = 0.0;

	for(int zz = 0 ; zz < A ; zz++){
		dphi[zz] = dphiPt->ProjectionX(Form("Pt%d",zz),zz, zz+1,"e");

		TF1 *v2fit = new TF1("v2fit",fitFunc,0., 1.57, 3);
		v2fit->SetParameter(0,dphi[zz]->GetBinContent((int)dphi[zz]->GetNbinsX()/2));
  		v2fit->SetParameter(1,0.04);
  		v2fit->SetParameter(2,0.01);

  		dphi[zz]->Fit("v2fit","ME","",0.,1.57);
  		for(int i = 0 ; i < 50 ; i++){
		if(v2fit->GetChisquare() < 100)break;
			cout<<v2fit->GetChisquare()<<endl;
			v2fit->SetParameter(0,dphi[zz]->GetBinContent((int)dphi[zz]->GetNbinsX()/2));
			v2fit->SetParameter(1,0.04);
			dphi[zz]->Fit("v2fit","ME","",0.,1.57);
		}  		
  		const Double_t *par1     =  v2fit->GetParameters();
  		const Double_t *perr1    =  v2fit->GetParErrors();
  		//cout<<perr1[1]<<endl;
  		 g1pt->SetPoint(zz,(zz+1)*pt->GetBinWidth(zz),par1[1]/corRes);
  		 g2pt->SetPointError(zz,0,perr1[1]);
  		 g2pt->SetPoint(zz,(zz+1)*pt->GetBinWidth(zz),par1[1]);
  		 double Err = sqrt((perr1[1]/corRes)*(perr1[1]/corRes) + pow(corResE*par1[1]/corRes/corRes,2));
  		 g1pt->SetPointError(zz,0,Err);
  		 cout<<"error:"<<Err<<endl;
  		

  		 if(par1[1]/corRes < 0.1 && zz < 14 ){
  		 wpt   = dphi[zz]->GetEntries();
  		 v2S  += par1[1]/corRes*wpt;
  		 v2SE += Err*wpt;
  		 wS   += wpt;
  		 }
  		 

  		 dphi[zz]->Write();
	}

	for(int zz = 0 ; zz < B ; zz++){
		dphi1[zz] = dphiMt->ProjectionX(Form("Mt%d",zz),zz, zz+1,"e");

		TF1 *v2fit = new TF1("v2fit",fitFunc,0., 1.57, 2);
		v2fit->SetParameter(0,dphi1[zz]->GetBinContent((int)dphi1[zz]->GetNbinsX()/2));
		cout<<"Middle:"<<dphi1[zz]->GetBinContent((int)dphi[zz]->GetNbinsX()/2)<<endl;
  		v2fit->SetParameter(1,0.04);
  		v2fit->SetParameter(2,0.01);

  		dphi1[zz]->Fit("v2fit","ME","",0.,1.57);
		for(int i = 0 ; i < 50 ; i++){
		if(v2fit->GetChisquare() < 100)break;
			cout<<v2fit->GetChisquare()<<endl;
			v2fit->SetParameter(0,dphi1[zz]->GetBinContent((int)dphi1[zz]->GetNbinsX()/2));
			v2fit->SetParameter(1,0.04);
			dphi1[zz]->Fit("v2fit","ME","",0.,1.57);
		}  		
  		const Double_t *par1     =  v2fit->GetParameters();
  		const Double_t *perr1    =  v2fit->GetParErrors();
  		//cout<<perr1[1]<<endl;
  		 g1mt->SetPoint(zz,(zz+1)*mt->GetBinWidth(zz),par1[1]/corRes);
  		 //g1->SetPointError(zz,0,perr1[1]);
  		 g2mt->SetPoint(zz,(zz+1)*mt->GetBinWidth(zz),par1[1]);
  		 double Err = sqrt((perr1[1]/corRes)*(perr1[1]/corRes) + pow(corResE*par1[1]/corRes/corRes,2));
  		 g1mt->SetPointError(zz,0,Err);
  		 gmtscaled->SetPoint(zz,(zz+1)*mt->GetBinWidth(zz)/2,par1[1]/corRes/2);
  		 gmtscaled->SetPointError(zz,0,Err/2);
  		 if(markerid == 20) {
  		 	gmtscaled->SetPoint(zz,(zz+1)*mt->GetBinWidth(zz)/3,par1[1]/corRes/3);
  		 	gmtscaled->SetPointError(zz,0,Err/3);
  		 }
  		 dphi1[zz]->Write();
	}
	TGraphErrors *g4 = new TGraphErrors();
	TGraphErrors *g5 = new TGraphErrors();
	for(int y = 2; y<res->GetNbinsX()   ;y++){
		cout<<res->GetBinContent(y)<<" "<<sqrt(res->GetBinContent(y))<<endl;
		if(res->GetBinContent(y) > 0.0){ 
			resh->SetBinContent((7-y),sqrt(res->GetBinContent(y)));
			resh->SetBinError(y,res->GetBinError(y));
			g4->SetPoint(y,35-2.5-5*(y-2),sqrt(res->GetBinContent(y)));
			
		}
	}
	g5->SetPoint(1,8.5,v2S/wS);
	g5->SetPointError(1,0,v2SE/wS);
	g1pt->SetMarkerStyle(markerid);
	g1pt->SetMarkerColor(colorid);
	g1pt->Write("v2ptCorr");
	g2pt->Write("v2pt");
	g1mt->SetMarkerStyle(markerid);
	g1mt->SetMarkerColor(colorid);
	g1mt->Write("v2mtCorr");
	g2mt->Write("v2mt");
	g4->Write("res");
	g5->Write("meanv2");
	gmtscaled->Write("ncq");
	resh->Write();
	f->Close();
	g->Close();

}