void graphRead(TGraphErrors *g, double &X, double &Y,int n, double &Ymin, double &Ymax){
	g->GetPoint(n,X,Y);
	if(Y > Ymax) Ymax = Y;
	if(Y < Ymin) Ymin = Y;
}

void sysQ2v2Plotter(){
	
	TFile *f1 = new TFile("./10dEdxDIR/V2asYangProtons10dEdx.root");
	TFile *f2 = new TFile("./dEdx20DIR/V2asYangProtonsdEdx20.root");
	TFile *f3 = new TFile("./dEdx15DIR/V2asYangProtonsdEdx15.root");
    TFile *f4 = new TFile("./10NDIR/V2asYangProtons10N.root");
    TFile *f5 = new TFile("./20NDIR/V2asYangProtons20N.root");
    TFile *f6 = new TFile("./15NDIR/V2asYangProtons15N.root");


	TGraphErrors *g1 = (TGraphErrors*)f1->Get("GraphPTv2");
	TGraphErrors *g2 = (TGraphErrors*)f2->Get("GraphPTv2");
	TGraphErrors *g3 = (TGraphErrors*)f3->Get("GraphPTv2");
	TGraphErrors *g4 = (TGraphErrors*)f4->Get("GraphPTv2");
	TGraphErrors *g5 = (TGraphErrors*)f5->Get("GraphPTv2");
	TGraphErrors *g6 = (TGraphErrors*)f6->Get("GraphPTv2");

	TGraphErrors *g21 = (TGraphErrors*)f1->Get("meanv2");
	TGraphErrors *g22 = (TGraphErrors*)f2->Get("meanv2");
	TGraphErrors *g23 = (TGraphErrors*)f3->Get("meanv2");
	TGraphErrors *g24 = (TGraphErrors*)f4->Get("meanv2");
	TGraphErrors *g25 = (TGraphErrors*)f5->Get("meanv2");
	TGraphErrors *g26 = (TGraphErrors*)f6->Get("meanv2");

	TGraphErrors *G  = new TGraphErrors();
	TGraphErrors *G1 = new TGraphErrors();

	TGraphErrors *G2  = new TGraphErrors();
	TGraphErrors *G12 = new TGraphErrors();

	double x;
	double y;
	double ymin = 100;
	double ymax = -100;

		graphRead(g21,x,y,0,ymin,ymax);
		graphRead(g22,x,y,0,ymin,ymax);
		graphRead(g23,x,y,0,ymin,ymax);
		graphRead(g24,x,y,0,ymin,ymax);
		graphRead(g25,x,y,0,ymin,ymax);
		graphRead(g26,x,y,0,ymin,ymax);

		G2->SetPoint(0,x,(ymin + ymax)/2);
		G12->SetPoint(0,x,(ymin + ymax)/2);
		G2->SetPointError(0,0,(ymax-ymin)/sqrt(3.0));
		G12->SetPointError(0,0,g21->GetErrorY(0));
		cout<<(ymin + ymax)/2<<endl;
		cout<<g21->GetErrorY(0)<<endl;

	int N = 20;

	
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
		G1->SetPoint(i,x,(ymin + ymax)/2);
		G->SetPointError(i,0,(ymax-ymin)/sqrt(3.0));
		G1->SetPointError(i,0,g1->GetErrorY(i));
		cout<<(ymin + ymax)/2<<endl;
		cout<<g1->GetErrorY(i)<<endl;
  		
	}



	TFile *gf = new TFile("Protonssysv2Q2.root","recreate");
	G->Write("sys");
	G1->Write("stat");
	G2->Write("meansys");
	G12->Write("meanstat");
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