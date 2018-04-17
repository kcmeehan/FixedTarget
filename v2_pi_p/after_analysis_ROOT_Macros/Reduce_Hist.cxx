void Reduce_Hist(char *infile,int N,char *name){
	
		const static int anabinN = N;
                cout<<"hyh"<<endl;
		TFile *H = new TFile(infile);
                cout<<"buy"<<endl;
                int max = 700;

		        TH1D *sum_C2	        = (TH1D*)H->Get("sum_C2");
                TH1D *sum_C22           = (TH1D*)H->Get("sum_C22");	
                TH1D *sumM1		= (TH1D*)H->Get("sum_M1");	
                TH1D *corrREFY		= (TH1D*)H->Get("corrRefX");
                TH1D *sumREFW		= (TH1D*)H->Get("sum_RefW");	
                TH1D *sumREFW2		= (TH1D*)H->Get("sum_RefW2");	
                TH1D *corrREFX		= (TH1D*)H->Get("corrRefY");
                TH1D *sumS11            = (TH1D*)H->Get("sum_S11");
			
		        TH2D *corrPOIX	= (TH2D*)H->Get("corrPoiX");
	       	    TH2D *corrPOIY	= (TH2D*)H->Get("corrPoiY");
	       	    TH2D *sum_D2	= (TH2D*)H->Get("sum_D2");
                TH2D *sum_D22    = (TH2D*)H->Get("sum_D22");
                TH2D *sumPOIW	= (TH2D*)H->Get("sum_PoiW");
                TH2D *sumPOIW2	= (TH2D*)H->Get("sum_PoiW2");
                TH2D *sumPOIM2	= (TH2D*)H->Get("sum_PoiM2");
                TH1D *c2Error   = new TH1D("c2Error","C2Error",max,0,max);
                TH2D *d2Error   = new TH2D("d2Error","D2Error",max,0,max,anabinN,0,anabinN);
                TH1D *c2ErrorY   = new TH1D("c2ErrorY","C2ErrorY",max,0,max);
                TH2D *d2ErrorY   = new TH2D("d2ErrorY","D2ErrorY",max,0,max,anabinN,0,anabinN);

                
                H->GetListOfKeys()->Print();
                /*
                for(int kk = 0 ; kk<max; kk++){
                                        c2 = (TH1D*)H->Get(Form("c2%d",kk));
                                       
                                        c2Error->SetBinContent(kk,c2->GetStdDev());
                                        for(int jj =0 ; jj < anabinN ; jj++){
                                                //cout<<Form("d2%d_%d",kk,jj)<<endl;
                                                d2 = (TH1D*)H->Get((Form("d2%d_%d",kk,jj)));
                                                //cout<<"H"<<endl;
                                                if(d2->GetEntries() > 0)d2Error->SetBinContent(kk,jj,d2->GetStdDev());
                                                //cout<<d2->GetEntries()<<endl;
                                        }
                                }
                */
                Double_t c2dev;
                Double_t d2dev;
                for(int kk = 0 ; kk<max; kk++){
                                        if(sumREFW->GetBinContent(kk) > 0.0) c2dev = sum_C22->GetBinContent(kk)/sumREFW->GetBinContent(kk) - pow(sum_C2->GetBinContent(kk)/sumREFW->GetBinContent(kk),2.0);
                                        c2dev =(c2dev > 0.) ? sqrt(c2dev) : 0.0; 
                                        c2Error->SetBinContent(kk,c2dev);
                                        for(int jj =0 ; jj < anabinN ; jj++){
                                                //cout<<Form("d2%d_%d",kk,jj)<<endl;
                                                if(sumPOIW->GetBinContent(kk,jj) > 0.0)d2dev = sum_D22->GetBinContent(kk,jj)/sumPOIW->GetBinContent(kk,jj) - pow(sum_D2->GetBinContent(kk,jj)/sumPOIW->GetBinContent(kk,jj),2.0);
                                                //cout<<"H"<<endl;
                                                 d2dev =(d2dev > 0.) ? sqrt(d2dev) : 0.0; 
                                                d2Error->SetBinContent(kk,jj,d2dev);
                                                //cout<<d2->GetEntries()<<endl;
                                        }
                                }

                
                
                Double_t G = 0.3;
                TFile *H1 = new TFile(Form("reduced%s.root",name),"recreate");
                sum_C2->Write(); 
                sumM1->Write();       
                corrPOIX->Write();
                corrREFX->Write();
                corrPOIY->Write();
                corrREFY->Write();
                sum_D2->Write();
                sumREFW->Write();
                sumREFW2->Write();
                sumPOIW->Write();
                sumPOIW2->Write();
                sumPOIM2->Write();
                sumS11->Write();
                c2Error->Write();
                d2Error->Write();
                c2ErrorY->Write();
                d2ErrorY->Write();
                H->Close();
                H1->Close();
                }
                
