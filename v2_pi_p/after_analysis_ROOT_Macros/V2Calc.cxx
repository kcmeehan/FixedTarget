	

void V2Calc(/*char *infile2,*/ char *infile,int N,char *name,int markerid, int colorid){
	
		const static int anabinN = N;
		TFile *H = new TFile(infile);
		//TFile *F = new TFile(infile2,"read");

				H->GetListOfKeys()->Print();

				TH1D *sum_C2		= (TH1D*)H->Get("sum_C2");	
                TH1D *sumM1			= (TH1D*)H->Get("sum_M1");	
                TH1D *corrREFY		= (TH1D*)H->Get("corrRefX");
                TH1D *sumREFW		= (TH1D*)H->Get("sum_RefW");	
                TH1D *sumREFW2		= (TH1D*)H->Get("sum_RefW2");	
                TH1D *corrREFX		= (TH1D*)H->Get("corrRefY");
                TH1D *sumS11		= (TH1D*)H->Get("sum_S11");
			
				TH2D *corrPOIX	= (TH2D*)H->Get("corrPoiX");
	       		TH2D *corrPOIY	= (TH2D*)H->Get("corrPoiY");
	       		TH2D *sum_D2	= (TH2D*)H->Get("sum_D2");
                TH2D *sumPOIW	= (TH2D*)H->Get("sum_PoiW");
                TH2D *sumPOIW2	= (TH2D*)H->Get("sum_PoiW2");
                TH2D *sumPOIM2	= (TH2D*)H->Get("sum_PoiM2");
                TH1D *c2      	= (TH1D*)H->Get("c2Error");
                TH2D *d2		= (TH2D*)H->Get("d2Error");	
                

              
				
		
	cout<<sumM1->GetEntries()<<endl;
		
    int max = 700;
    double ptUp = 1.6;
    double ptDown = 0.0;
    if(markerid == 20){
    	 ptUp = 2.0;
    	 ptDown = 0.3;
    }
	TH1D *v2REFmult   = new TH1D("v2REFmult","v2remultf",max,0,max);
	TH2D *v2POImultpt = new TH2D("v2POImultpt","v2poimultpt",max,0,max,anabinN,0,anabinN);
	TH1D *v2POIpt	  = new TH1D("v2POIpt","v2POIPT",anabinN,ptDown,ptUp);
	Double_t MeanREFv2  = 0;
	Double_t MeanREFv2W = 0;
	Double_t MeanPOIv2[anabinN];
	Double_t MeanPOIv2W[anabinN];
	int multup = 240;
	int multdown = 50;

	for(int ij = 0; ij < anabinN ;ij++){
	MeanPOIv2[ij]  = 0.0;
	MeanPOIv2W[ij] = 0.0;
	}

	cout<<"loaded!"<<endl;
	for(int zz = multdown; zz < multup ; zz++){
		Double_t REFc2 =(sumREFW->GetBinContent(zz) > 0.0 && sumM1->GetBinContent(zz) > 0.0 && sumS11->GetBinContent(zz) > 0) ? sum_C2->GetBinContent(zz)/sumREFW->GetBinContent(zz) 
																								- pow(corrREFX->GetBinContent(zz)/sumS11->GetBinContent(zz),2) 
																								- pow(corrREFY->GetBinContent(zz)/sumS11->GetBinContent(zz),2) : 0.0;	
		cout<<REFc2<<endl;
		Double_t REFv2 =(REFc2 > 0) ?  sqrt(REFc2) : 0.0;//-sqrt(fabs(REFc2)) ;
		//cout<<sum_C2->GetBinContent(zz)/sumREFW->GetBinContent(zz)<<" "<<pow(corrREFX->GetBinContent(zz)/sumS11->GetBinContent(zz),2)<<endl;
		Double_t s_2REF = (sumREFW->GetBinContent(zz) > 0.0 && sumREFW2->GetBinContent(zz) > 0 && pow(sumREFW->GetBinContent(zz),2) != sumREFW2->GetBinContent(zz) ) ? c2->GetBinContent(zz)/sqrt(1-(sumREFW2->GetBinContent(zz)/pow(sumREFW->GetBinContent(zz),2))) : 0.0; 
		Double_t v2Error = (sumREFW->GetBinContent(zz) > 0.0 && sumREFW2->GetBinContent(zz) && s_2REF > 0.0) ? 1/REFv2/2*sqrt(sumREFW2->GetBinContent(zz))/sumREFW->GetBinContent(zz)*sqrt(s_2REF) : 0.0;
		if(sumM1->GetBinContent(zz) > 0.0){
		//cout<<"A"<<endl;
		corrREFX->SetBinContent(zz,corrREFX->GetBinContent(zz)/sumS11->GetBinContent(zz));
		corrREFY->SetBinContent(zz,corrREFY->GetBinContent(zz)/sumS11->GetBinContent(zz));
		sum_C2->SetBinContent(zz,sum_C2->GetBinContent(zz)/sumREFW->GetBinContent(zz));
		}else{
		corrREFX->SetBinContent(zz,0);
		corrREFY->SetBinContent(zz,0);
		sum_C2->SetBinContent(zz,0);
		}


		if(REFv2 != 0){
		v2REFmult->SetBinContent(zz,REFv2);
		v2REFmult->SetBinError(zz,v2Error);
		}
		if(REFv2 > 0.0 && v2Error > 0.0){
		MeanREFv2 += REFv2/v2Error;
		MeanREFv2W += 1/v2Error;
		}
	
	 	
		
		//cout<< zz <<" REfflow: "<<REFv2<<" " <<endl;
	 for(int gg = 0 ; gg < anabinN ; gg++){
			Double_t POId2 = (sumPOIW->GetBinContent(zz,gg)  != 0.0 && sumS11->GetBinContent(zz) != 0 && sumPOIM2->GetBinContent(zz,gg)  != 0 ) ? sum_D2->GetBinContent(zz,gg)/sumPOIW->GetBinContent(zz,gg)  
																																				- corrREFX->GetBinContent(zz)*corrPOIX->GetBinContent(zz,gg)/sumPOIM2->GetBinContent(zz,gg)/sumS11->GetBinContent(zz) 
																																				- corrREFY->GetBinContent(zz)*corrPOIY->GetBinContent(zz,gg)/sumPOIM2->GetBinContent(zz,gg)/sumS11->GetBinContent(zz) : 0.0;
			Double_t POIv2 = (REFv2 > 0) ? POId2/REFv2 : 0.0;
			
			Double_t s_2POI = (sumPOIW2->GetBinContent(zz,gg)  > 0.0 && sumPOIW2->GetBinContent(zz,gg)  != pow(sumPOIW->GetBinContent(zz,gg) ,2)) ? d2->GetBinContent(zz,gg)/sqrt(1-(sumPOIW2->GetBinContent(zz,gg)/pow(sumPOIW->GetBinContent(zz,gg),2))) : 0.0;
			
			Double_t POIv2Error =(sumREFW->GetBinContent(zz) > 0.0 && fabs(REFc2) > 0.0 && sumPOIW->GetBinContent(zz,gg) > 0) ? sqrt(0.25/pow(fabs(REFc2),3)*(
																																	pow(POId2,2)*sumREFW2->GetBinContent(zz)/pow(sumREFW->GetBinContent(zz),2)*pow(s_2REF,2)
																																	+4.*pow(REFc2,2)*sumPOIW2->GetBinContent(zz,gg)/pow(sumPOIW->GetBinContent(zz,gg) ,2)*pow(s_2POI,2))) : 0.0;
			//cout<<REFc2<<" "<<1/4/pow(fabs(REFc2),3)<<" "<<pow(POId2,2)*sumREFW2->GetBinContent(zz)/pow(sumREFW->GetBinContent(zz),2)*pow(s_2REF,2)<<" "<<4*pow(REFc2,2)*sumPOIW2->GetBinContent(zz,gg)/pow(sumPOIW->GetBinContent(zz,gg) ,2)*pow(s_2POI,2)<<endl;	

			//if(POIv2 < 0.3 && POIv2 > -0.1 && POIv2Error > 0.0){
			v2POImultpt->SetBinContent(zz,gg,POIv2);
			v2POImultpt->SetBinError(zz,gg,POIv2Error);
			//}
			
		//cout<<zz<<" "<<gg<<" "<<POIv2<<" "<<POIv2Error<<endl;
		
	 }
	}
	cout<<"Done!"<<endl;
	Double_t v2Int = 0.0;
	Double_t v2IntError = 0.0;
	Double_t ptIntWsum = 0.0;
	TGraphErrors *g1 = new TGraphErrors();
	TGraphErrors *gncq = new TGraphErrors();
	for(int tt = 0 ; tt < anabinN ; tt++){
			Double_t v2_bin  = 0.0;	
            Double_t v2_binE = 0.0;

		
		for(int rr = multdown ; rr < multup ; rr++){
		if(v2POImultpt->GetBinError(rr,tt) != 0)v2_bin  += v2POImultpt->GetBinContent(rr,tt)/pow(v2POImultpt->GetBinError(rr,tt),2);
		if(v2POImultpt->GetBinError(rr,tt) != 0)v2_binE += 1.0/pow(v2POImultpt->GetBinError(rr,tt),2);
		}
			
		if(v2_binE > 0){
			v2POIpt->SetBinContent(tt,v2_bin/v2_binE);
			g1->SetPoint(tt,ptDown+(tt-0.5)*(ptUp-ptDown)/anabinN,v2_bin/v2_binE);
			gncq->SetPoint(tt,(ptDown+(tt-0.5)*(ptUp-ptDown)/anabinN)/2,v2_bin/v2_binE/2);
			if(markerid == 20){
				gncq->SetPoint(tt,(ptDown+(tt-0.5)*(ptUp-ptDown)/anabinN)/3,v2_bin/v2_binE/3);
			}
		}
		
		if(v2_binE > 0){
			v2POIpt->SetBinError(tt,sqrt(1/v2_binE));
			g1->SetPointError(tt,0,sqrt(1/v2_binE));
			gncq->SetPointError(tt,0,sqrt(1/v2_binE)/2);
			if(markerid == 20){
			gncq->SetPointError(tt,0,sqrt(1/v2_binE)/2);
			}
		}	
	} 

	v2Int      = v2Int/ptIntWsum;
	v2IntError = sqrt(v2IntError)/ptIntWsum;
	//H->Close();
	cout<<v2Int<<" "<<v2IntError<<endl;
	TGraphErrors *g = new TGraphErrors();
	g->SetPoint(0,8.5,v2Int);
    g->SetPointError(0,0,v2IntError);
    
	v2POIpt->SetMarkerStyle(markerid);
	v2POIpt->SetMarkerColor(colorid);
	
	TFile *f = new TFile(Form("V2asYang%s.root",name),"recreate");
	v2REFmult->Write();
	v2POImultpt->Write();
	v2POIpt->Write();
	corrREFX->Write();
	corrREFY->Write();
	sum_C2->Write();
	g->Write("meanv2");
	g1->Write("GraphPTv2");
	gncq->Write("NCQ");
	f->Close();
	H->Close();
	//F->Close();
}
