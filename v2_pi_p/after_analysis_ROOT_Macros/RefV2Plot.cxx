

void RefV2Plot(char *filename, Int_t binC,double delta, char *stringid,char *fileid,int markerid, int colorid){
	const Int_t A = binC;
	Double_t v2DIR[A];
	Double_t v2CUM[A];
	Double_t variable[A];
	Double_t uvariable[A];
	Double_t uv2DIR[A];
	Double_t uv2CUM[A];
	Double_t BINv2DIR[A];
	Double_t BINv2CUM[A];
	Double_t BINvariable[A]; 
	Double_t BINuvariable[A];
	Double_t BINuv2DIR[A], pionBINv2DIR[A];
	Double_t BINuv2CUM[A], pionBINv2CUM[A];
	Double_t sinphi	 ;	
	Double_t cosphi	 ;
	Double_t usinphi ;
	Double_t ucosphi ;	
	Double_t c1 	;
	Double_t uc1	;
	Double_t cum1	;
	Double_t ucum1	;
	Double_t sinphitemp	 ;	
	Double_t cosphitemp	 ;
	Double_t usinphitemp ;
	Double_t ucosphitemp ;	
	Double_t c1temp 	;
	Double_t uc1temp	;
	Double_t cum1temp	;
	Double_t ucum1temp	;
	
	Double_t BINsinphi1	 ;	
	Double_t BINcosphi1	 ;
	Double_t BINusinphi1 ;
	Double_t BINucosphi1 ;	
	Double_t BINsinphi2	 ;	
	Double_t BINcosphi2	 ;
	Double_t BINusinphi2 ;
	Double_t BINucosphi2 ;	
	Double_t BINc1 	;
	Double_t BINuc1	;
	Double_t BINcum1	;
	Double_t BINucum1	;		


	
	TFile *F = new TFile(filename);
	double RefFlow[7];
	double Cent[7] ;
	for(int kk = 0; kk < 1 ; kk++){
	//TH1D *mean2	 = (TH1D*) F->Get(Form("V2cosdeltaPHI%d",kk));
	TH1D *cumtemp    = (TH1D*) F->Get(Form("u%d",kk));
	TH1D *sintemp	 = (TH1D*) F->Get(Form("sinphi%d",kk));
	TH1D *costemp	 = (TH1D*) F->Get(Form("cosphi%d",kk));	
	sinphitemp	 = sintemp->GetMean();	
	cosphitemp	 = costemp->GetMean();
	usinphitemp	 = costemp->GetMeanError();
	ucosphitemp	 = sintemp->GetMeanError();
	cum1temp	= cumtemp->GetMean();
	ucum1temp	= cumtemp->GetMeanError();
	RefFlow[kk] = cum1temp;
	cout<<cum1temp<<endl;
	Cent[kk] = kk;
	}	
	//TH1D *mean2	 = (TH1D*) F->Get(Form("V2cosdeltaPHI%d",0));
	TH1D *cum   	 = (TH1D*) F->Get(Form("u%d",0));
	TH1D *sin	 = (TH1D*) F->Get(Form("sinphi%d",0));
	TH1D *cos	 = (TH1D*) F->Get(Form("cosphi%d",0));
	sinphi	 = sin->GetMean();	
	cosphi	 = cos->GetMean();
	usinphi	 = cos->GetMeanError();
	ucosphi	 = sin->GetMeanError();
	
	//c1 	= mean2->GetMean();
	//uc1	= mean2->GetMeanError();
	cum1	= cum->GetMean();
	ucum1	= cum->GetMeanError();

	Double_t v2cum 	= sqrt(fabs(cum1) - sinphi*sinphi -cosphi*cosphi);
	uv2CUM[0] = sqrt((ucum1*ucum1/4/v2cum/v2cum) 
	+(sinphi*ucosphi)*(sinphi*ucosphi/4/v2cum/v2cum)
	+(sinphi*ucosphi)*(sinphi*ucosphi/4/v2cum/v2cum));
	for(int i = 0; i < binC; i++){
	TH1D *var     	 = (TH1D*) F->Get(Form("VC%d",i));
	//TH1D *BINmean2	 = (TH1D*) F->Get(Form("BINV2cosdeltaPHI%d",i));
	TH1D *BINcum   	 = (TH1D*) F->Get(Form("BINu%d",i));
	TH1D *BINvar     = (TH1D*) F->Get(Form("BINVC%d",i));
	TH1D *BINsin1	 = (TH1D*) F->Get(Form("sinphi1%d",i));
	TH1D *BINcos1	 = (TH1D*) F->Get(Form("cosphi1%d",i));
	
	cout<<"jeb"<<endl;
		
	
	BINsinphi1	 = BINsin1->GetMean();	
	BINcosphi1	 = BINcos1->GetMean();
	BINusinphi1 	 = BINcos1->GetMeanError();
	BINucosphi1	 = BINsin1->GetMeanError();

	BINcum1		= BINcum->GetMean();
	BINucum1	= BINcum->GetMeanError();	
		
	
	variable[i]  = var->GetMean() + delta;
	uvariable[i] = var->GetMeanError();
	
	
	Double_t BINv2cum = (BINcum1 - BINsinphi1*sinphi -BINcosphi1*cosphi);
	BINuv2CUM[i] = sqrt(pow(BINucum1,2) + 
			pow(BINsinphi1*usinphi,2) +
			pow(BINcosphi1*ucosphi,2) +
			pow(BINusinphi1*sinphi,2) +
			pow(BINucosphi1*cosphi,2) );
	
	//if(BINcum1 - BINsinphi1*BINsinphi2 -BINcosphi1*BINcosphi2 < 0)BINv2cum=-BINv2cum;
	
	BINv2CUM [i] = BINv2cum;

	}
	//cout<<"jeb"<<endl;

	
	for(int j = 0 ; j < A ; j++){
	
	cout<<variable[j]<<endl;//
	//variable[j] = j;
	BINuv2CUM[j] = sqrt(pow(BINuv2CUM[j]/v2cum,2)+pow(uv2CUM[0]*BINv2CUM[j]/v2cum/v2cum,2));
	BINv2CUM[j] = (BINv2CUM[j]/v2cum);
	}
	
	
	//TCanvas *can = new TCanvas("c1","c1",400,400,400,400);
	TGraphErrors *BINCUM = new TGraphErrors(binC,variable,BINv2CUM,BINuvariable,BINuv2CUM);
	
	TGraph *REF    = new TGraph(7,Cent,RefFlow);
	BINCUM->SetMarkerStyle(markerid);
	BINCUM->SetMarkerColor(colorid);
	cout<<"vhuj"<<endl;
	//BINCUM->Draw("AP");	
	F->Close();
	TFile *H = new TFile(fileid,"update");
	BINCUM->Write(stringid);
	REF->Write("REF");
	H->Close();
	
	cout<<"kkk"<<endl;
	} 
