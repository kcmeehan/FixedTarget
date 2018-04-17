
void graphRead(TGraphErrors *g, double &X, double &Y,int n, double &Ymin, double &Ymax){
	g->GetPoint(n,X,Y);
	if(Y > Ymax && Y < 0.2){
		Ymax = Y;
	} 
	if(Y < Ymin && Y > -0.2){
	 Ymin = Y;
	}

}

void sysRPv2Plotter(char *particle,int quarkNumber){
	
	TFile *f1 = new TFile(Form("./10dEdxDIR/10dEdx%sv2RP.root",particle));
	TFile *f2 = new TFile(Form("./20dEdxDIR/20dEdx%sv2RP.root",particle));
	TFile *f3 = new TFile(Form("./15dEdxDIR/15dEdx%sv2RP.root",particle));
    TFile *f4 = new TFile(Form("./10NDIR/10N%sv2RP.root",particle));
    TFile *f5 = new TFile(Form("./20NDIR/20N%sv2RP.root",particle));
    TFile *f6 = new TFile(Form("./15NDIR/15N%sv2RP.root",particle));


	TGraphErrors *g1 = (TGraphErrors*)f1->Get("v2ptCorr");
	TGraphErrors *g2 = (TGraphErrors*)f2->Get("v2ptCorr");
	TGraphErrors *g3 = (TGraphErrors*)f3->Get("v2ptCorr");
	TGraphErrors *g4 = (TGraphErrors*)f4->Get("v2ptCorr");
	TGraphErrors *g5 = (TGraphErrors*)f5->Get("v2ptCorr");
	TGraphErrors *g6 = (TGraphErrors*)f6->Get("v2ptCorr");

	TGraphErrors *g11 = (TGraphErrors*)f1->Get("v2mtCorr");
	TGraphErrors *g21 = (TGraphErrors*)f2->Get("v2mtCorr");
	TGraphErrors *g31 = (TGraphErrors*)f3->Get("v2mtCorr");
	TGraphErrors *g41 = (TGraphErrors*)f4->Get("v2mtCorr");
	TGraphErrors *g51 = (TGraphErrors*)f5->Get("v2mtCorr");
	TGraphErrors *g61 = (TGraphErrors*)f6->Get("v2mtCorr");

	TGraphErrors *gm1 = (TGraphErrors*)f1->Get("meanv2");
	TGraphErrors *gm2 = (TGraphErrors*)f2->Get("meanv2");
	TGraphErrors *gm3 = (TGraphErrors*)f3->Get("meanv2");
	TGraphErrors *gm4 = (TGraphErrors*)f4->Get("meanv2");
	TGraphErrors *gm5 = (TGraphErrors*)f5->Get("meanv2");
	TGraphErrors *gm6 = (TGraphErrors*)f6->Get("meanv2");

	TGraphErrors *G   = new TGraphErrors();
	TGraphErrors *GNCQ = new TGraphErrors();
	TGraphErrors *GMT  = new TGraphErrors();
	TGraphErrors *GS   = new TGraphErrors();
	TGraphErrors *GNCQS = new TGraphErrors();
	TGraphErrors *GMTS  = new TGraphErrors();
	TGraphErrors *M   = new TGraphErrors();
	TGraphErrors *MS   = new TGraphErrors();

	int N = 20;

	double x;
	double y;
	double ymin = 100;
	double ymax = -100;
		graphRead(gm1,x,y,1,ymin,ymax);
		graphRead(gm2,x,y,1,ymin,ymax);
		graphRead(gm3,x,y,1,ymin,ymax);
		graphRead(gm4,x,y,1,ymin,ymax);
		graphRead(gm5,x,y,1,ymin,ymax);
		graphRead(gm6,x,y,1,ymin,ymax);
		M->SetPoint(0,x,(ymin + ymax)/2);
		M->SetPointError(0,0,(ymax-ymin)/sqrt(3.0));
		MS->SetPoint(0,x,(ymin + ymax)/2);
		MS->SetPointError(0,0,g1->GetErrorY(1));
	cout<<"a"<<endl;
	for(int i = 0; i < N ; i++){
		double ymin = 100;
		double ymax = -100;
		graphRead(g1,x,y,i,ymin,ymax);
		graphRead(g2,x,y,i,ymin,ymax);
		graphRead(g3,x,y,i,ymin,ymax);
		graphRead(g4,x,y,i,ymin,ymax);
		graphRead(g5,x,y,i,ymin,ymax);
		graphRead(g6,x,y,i,ymin,ymax);
		G->SetPoint(i,x,(ymin + ymax)/2);
		G->SetPointError(i,0,(ymax-ymin)/sqrt(3.0));
		GS->SetPoint(i,x,(ymin + ymax)/2);
		GS->SetPointError(i,0,g1->GetErrorY(i));

		ymin = 100;
		ymax = -100;
		graphRead(g11,x,y,i,ymin,ymax);
		graphRead(g21,x,y,i,ymin,ymax);
		graphRead(g31,x,y,i,ymin,ymax);
		graphRead(g41,x,y,i,ymin,ymax);
		graphRead(g51,x,y,i,ymin,ymax);
		graphRead(g61,x,y,i,ymin,ymax);

		GMT->SetPoint(i,x,(ymin + ymax)/2);
		GMT->SetPointError(i,0,(ymax-ymin)/sqrt(3.0));  
		GMTS->SetPoint(i,x,(ymin + ymax)/2);
		GMTS->SetPointError(i,0,g11->GetErrorY(i)); 

		GNCQ->SetPoint(i,x/quarkNumber,(ymin + ymax)/2/quarkNumber);
		GNCQ->SetPointError(i,0,(ymax-ymin)/sqrt(3.0)/quarkNumber); 
		GNCQS->SetPoint(i,x/quarkNumber,(ymin + ymax)/2/quarkNumber);
		GNCQS->SetPointError(i,0,g11->GetErrorY(i)/quarkNumber); 		
	}

	TFile *gf = new TFile(Form("%ssys2RP.root",particle),"recreate");
	G->GetXaxis()->SetTitle("p_{T}[GeV/c]");
	G->GetYaxis()->SetTitle("v_{2}");
	G->Write("ptsys");
	GS->GetXaxis()->SetTitle("p_{T}[GeV/c]");
	GS->GetYaxis()->SetTitle("v_{2}");
	GS->Write("ptstat");
	GNCQ->GetXaxis()->SetTitle("(m_{T} - m)/n_{q}[GeV]");
	GNCQ->GetYaxis()->SetTitle("v_{2}/n_{q}");
	GNCQ->Write("nqcsys");
	GNCQS->GetXaxis()->SetTitle("(m_{T} - m)/n_{q}[GeV]");
	GNCQS->GetYaxis()->SetTitle("v_{2}/n_{q}");
	GNCQS->Write("nqcstat");
	GMT->GetXaxis()->SetTitle("(m_{T} - m)");
	GMT->GetYaxis()->SetTitle("v_{2}");
	GMT->Write("mtsys");
	GMTS->GetXaxis()->SetTitle("(m_{T} - m)");
	GMTS->GetYaxis()->SetTitle("v_{2}");
	GMTS->Write("mtstat");

	M->GetXaxis()->SetTitle("E_{LAB}[AGeV]");
	M->GetYaxis()->SetTitle("<v_{2}>");
	M->Write("meansys");
	MS->GetXaxis()->SetTitle("E_{LAB}[AGeV]");
	MS->GetYaxis()->SetTitle("<v_{2}>");
	MS->Write("meanstat");
	gf->Close();
	f1->Close();
	f2->Close();
	f3->Close();
	f4->Close();
	f5->Close();
	f6->Close();
	G->Draw();
	g1->Draw("same");
	g2->Draw("same");
	g3->Draw("same");
	g4->Draw("same");
	g5->Draw("same");
	g6->Draw("same");
}