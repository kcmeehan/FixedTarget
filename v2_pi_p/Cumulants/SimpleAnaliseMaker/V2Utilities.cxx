#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile2D.h"
#include "TClonesArray.h"
#include "TList.h"
#include "TCanvas.h"
#include "TObjArray.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "V2Utilities.h"
#include <fstream>

ClassImp(V2Utilities)


	V2Utilities::V2Utilities(char *X,float _mass){ 
		name = X;
		mass = _mass;
		for(int j =0 ; j< anabinN ; j++){
		//V2cosdeltaPHI[j] = new TH1D(Form("V2cosdeltaPHI%d",j),Form("V2CosdeltaPHI%d",j),100,-1,1);
		//V2cosdeltaPHI[j]->GetXaxis()->SetTitle("cos2#delta#phi");
		//V2cosdeltaPHI[j]->GetYaxis()->SetTitle("dN/dcos2#delta#phi");
		//V2mean2[j] = new TH1D(Form("u%d",j),Form("mean2_%d",j),500,-0.2,0.2);
		//V2cos2phi[j]  = new TH1D(Form("cosphi%d",j),Form("Cosphi%d",j),10000,-1,1);
		//V2sin2phi[j]  = new TH1D(Form("sinphi%d",j),Form("Sinphi%d",j),10000,-1,1);
		V2VariableCheck[j] = new TH1D(Form("VC%d",j),Form("vc%d",j),500,-5,5);
		//V2VariableMult[j]  = new TH1D(Form("VM%d",j),Form("vd%d",j),500,0,500);
		//V2dphiCheck[j]	 = new TH1D(Form("dphiCheck%d",j),Form("DphiCheck%d",j),200,0,TMath::Pi());
		//V2phiCheck[j]   = new TH1D(Form("phiCheck%d",j),Form("phiCheck%d",j),200,-TMath::Pi(),TMath::Pi());
		//BINV2cosdeltaPHI[j] = new TH1D(Form("BINV2cosdeltaPHI%d",j),Form("V2CosdeltaPHI%d",j),100,-1,1);
        //BINV2cosdeltaPHI[j]->GetXaxis()->SetTitle("cos2#delta#phi");
        //BINV2cosdeltaPHI[j]->GetYaxis()->SetTitle("dN/dcos2#delta#phi");
		//BINV2VariableCheck[j] = new TH1D(Form("BINVC%d",j),Form("vc%d",j),500,-5,5);
        BINV2mean2[j] = new TH1D(Form("BINu%d",j),Form("BINmean2_%d",j),500,-0.2,0.2);
        /*BINV2cosphi1[j]  = new TH1D(Form("cosphi1%d",j),Form("Cosphi1%d",j),1000,-1,1);
        BINV2sinphi1[j]  = new TH1D(Form("sinphi1%d",j),Form("Sinphi1%d",j),1000,-1,1);
		BINV2cosphi2[j]  = new TH1D(Form("cosphi2%d",j),Form("Cosphi2%d",j),1000,-1,1);
        BINV2sinphi2[j]  = new TH1D(Form("sinphi2%d",j),Form("Sinphi2%d",j),1000,-1,1);
        
        BINV2VariableMult[j]  = new TH1D(Form("BINVM%d",j),Form("vd%d",j),500,0,500);
        BINV2dphiCheck[j]   = new TH1D(Form("BINdphiCheck%d",j),Form("DphiCheck%d",j),200,-2.5,2.5);
        
		BINV2phiCheck2[j]   = new TH1D(Form("BIN2phiCheck%d",j),Form("phiCheck%d",j),200,-2.5,2.5);
		WsumPOI	[j]	= new TH1D(Form("Wsum%d",j),Form("wsum%d"),10000,0,500);
		Wsum2POI[j]	= new TH1D(Form("Wsum2_%d",j),Form("wsum2_%d",j),100000,0,1000);
		WsumREF[j]		= new TH1D(Form("Wsum%d",j),Form("wsum%d"),10000,0,500);
		Wsum2REF[j]	= new TH1D(Form("Wsum2_%d",j),Form("wsum2_%d",j),100000,0,1000);
		RPmPhi[j]	    = new TH1D(Form("rmMphi%d",j),Form("RPmphi%d",j),200,0,TMath::Pi());
		*/
		}
	BINREFEtaCheck   = new TH1D("REFetaCheck","REFEtaCheck",200,-2.5,2.5);
	BINPOIEtaCheck   = new TH1D("POIetaCheck","POIEtaCheck",200,-2.5,2.5);

	RP_resolution = new TH1D("RPres","reRES",200,-1,1);
	refFlow = new TProfile2D("refFLOW","refFlow2nOrder",240,0,240,anabinN,0,anabinN,-0.2,0.2);
	difFlow = new TProfile2D(Form("difFlow%c",X),Form("difFlow2ndOrder%c",X),240,0,240,anabinN,0,anabinN,-0.2,0.2);
	correctionX = new TProfile2D("corX","CorX",240,0,240,anabinN,0,anabinN,-1,1);
	correctionY = new TProfile2D("corY","CorY",240,0,240,anabinN,0,anabinN,-1,1);
	correctionX1 = new TProfile2D("corX1","CorX1",240,0,240,7,0,7,-1,1);
	correctionY1 = new TProfile2D("corY1","CorY1,",240,0,240,7,0,7,-1,1);

				sum_C2			= new TH1D("sum_C2","Sum_C2",240,0,240);	
                sumM1			= new TH1D("sum_M1","Sum_M1",240,0,240);	
                corrREFY		= new TH1D("corrRefX","CorrRefX",240,0,240);	
                sumREFW			= new TH1D("sum_RefW","Sum_refW",240,0,240);	
                sumREFW2		= new TH1D("sum_RefW2","Sum_refW2",240,0,240);	
                corrREFX		= new TH1D("corrRefY","CorrRefY",240,0,240);
                sum_C22			= new TH1D("sum_C22","Sum_C22",240,0,240);	
		
				sumS11REF	   = new TH1D("sum_S11","Sum_S11",240,0,240);		
				corrPOIX	   = new TH2D("corrPoiX","corrpoiX",240,0,240,anabinN,0,anabinN);
	        	corrPOIY	   = new TH2D("corrPoiY","corrpoiY",240,0,240,anabinN,0,anabinN);
	        	sum_D2		   = new TH2D("sum_D2","Sum_D2",240,0,240,anabinN,0,anabinN);
                sumPOIW		   = new TH2D("sum_PoiW","Sum_PoiW",240,0,240,anabinN,0,anabinN);
                sumPOIW2	   = new TH2D("sum_PoiW2","Sum_PoiW2",240,0,240,anabinN,0,anabinN);
                sumPOIM2	   = new TH2D("sum_PoiM2","Sum_PoiM2",240,0,240,anabinN,0,anabinN);
                sum_D22		   = new TH2D("sum_D22","Sum_D22",240,0,240,anabinN,0,anabinN);


	}

	void V2Utilities::SetBin(double max, double min){
			for(int k = 0; k< anabinN ; k++){
				anabin[k] = min + k*(max -min)/anabinN;	
			}
	
	}

	void  V2Utilities::SetVID(int x){
	variableID = x;

	}

void V2Utilities::RefParticleV2Fill(TObjArray *part,TObjArray *POI, bool bin,double refetaleft  ,double refetaright, double poietaleft , double poietaright,int mult){

		
		StMuTrack *track;

	    float Qx1 	= 0.0;
        float Qy1 	= 0.0;
		float S12 	= 0.0;
		float S11   = 0.0;
		float wref 	= 0.0;
        float M1  		= 0.0; //part->GetEntries();
		int multid = 0;
	//double multBin[7] = 	{153,121,97,77,61,48,0};
		if(mult >= 153) 			multid = 0;
		if(mult < 153 && mult >= 121) 	multid = 1;
		if(mult < 121 && mult >= 97)   	multid = 2;
		if(mult <  97 && mult >= 77) 	multid = 3;
		if(mult <  77 && mult >= 61) 	multid = 4;
		if(mult <  61 && mult >= 48) 	multid = 5;
		if(mult <  48)			multid = 6;
			
        for(int i = 0 ; i < part->GetEntries(); i++){
                track = (StMuTrack*)part->At(i);
			if(!bin || (track->eta() > refetaleft && track->eta() < refetaright)){
				
				
		            wref = 1;//track->pt();
					S12 +=  wref*wref;
					S11 +=  wref; 
					Qx1 += wref*sin(2*track->phi());
		            Qy1 += wref*cos(2*track->phi());
					M1 += 1;
					BINREFEtaCheck->Fill(track->eta());
				
            }
		}


        double QQ = Qx1*Qx1 + Qy1*Qy1;
                //double nm1 = M1*(M1-1);
		float S21 = S11*S11;
		double mean2Up = QQ - S12;
		double M01 = S21-S12;
        float mean2ref =(S21-S12 != 0) ? (QQ - S12)/(S21-S12) : 0;
                //float mean2 = (QQ - M1)/nm1;
		float mQx = 0.0;
        float mQy = 0.0;
        if(S11 > 0.0){
        mQx = Qx1/S11;
        mQy = Qy1/S11;
        }
		refFlow->Fill(mult,multid,mean2ref,S21-S12);
		correctionX->Fill(mult,multid,mQx,M1);
		correctionY->Fill(mult,multid,mQy,M1);

		sum_C2->SetBinContent(mult,sum_C2->GetBinContent(mult)+mean2ref*M01);
		sum_C22->SetBinContent(mult,sum_C22->GetBinContent(mult)+mean2ref*mean2ref*M01);
		corrREFX->SetBinContent(mult,corrREFX->GetBinContent(mult)+mQx*S11);
		corrREFY->SetBinContent(mult,corrREFY->GetBinContent(mult)+mQy*S11);
		sumS11REF->SetBinContent(mult,sumS11REF->GetBinContent(mult)+S11);
		sumREFW->SetBinContent(mult,sumREFW->GetBinContent(mult)+M01);
		sumREFW2->SetBinContent(mult,sumREFW2->GetBinContent(mult)+M01*M01);
		sumM1->SetBinContent(mult,sumM1->GetBinContent(mult)+M1);
		
	for(int k = 1 ; k < anabinN ; k++){
	
	TObjArray *BinTracks = new TObjArray;;
	
        	for(int z = 0; z < POI->GetEntries() ; z++){
        	                        track = (StMuTrack*)POI->At(z);
                	        if(track->pt() >  anabin[k-1] && track->pt() < anabin[k]){
                        	        BinTracks->Add(track);
                              V2VariableCheck[k-1]->Fill(track->pt());
                //              BINV2phiCheck[k-1]->Fill(track->phi());
                                                              
				}
		}
	

	 	
                float Qx2 = 0.0;
                float Qy2 = 0.0;
                float M2  = 0.0;//BinTracks->GetEntries();
		float w = 0.0;
		float s12 = 0.0;
		float s11 = 0.0;
            for(int i =0 ; i < BinTracks->GetEntries() ;i++){
                        track = (StMuTrack*)BinTracks->At(i);
                        
			if(!bin || (track->eta() > poietaleft && track->eta() < poietaright)){
				float charge = 1;
				Double_t E = sqrt(mass*mass + fabs(charge*charge)*track->p().magnitude()*track->p().magnitude());
				Double_t rapidity = 0.5*log((E+fabs(charge)*track->p().z())/(E-fabs(charge)*track->p().z()));
				BINPOIEtaCheck->Fill(rapidity);
				if(mass == 0 || (rapidity > -2.0 && rapidity < -1.0)){

						w = 1;//track->pt();
						s12 += w*w;
						s11 += w;
						Qx2 += sin(2.*track->phi());
			            Qy2 += cos(2.*track->phi());
						
						M2 += 1;
				}
                 
			}
		
		
		
		}
		//correctionY->Fill(mult,k,mCy,s11);	

            Double_t mean2 = 0;
		  	Double_t W;
			if(!bin && s11 > 0.0){ 
			if(S11*M2 != s11)mean2 = (Qx1*Qx2 + Qy1*Qy2 - s11)/(S11*M2-s11);
			BINV2mean2[k-1]->Fill(mean2,S11*M2-s11);
			W = (S11*M2-s11);
			//BINV2VariableMult[k-1]->Fill(M2);
			difFlow->Fill(mult,k,mean2,S11*M2-s11);	
			}else {
			if(M2*S11 != 0)mean2 = (Qx1*Qx2 + Qy1*Qy2)/(M2*S11);
			W = S11*M2;
			BINV2mean2[k-1]->Fill(mean2,M2*M1);
			difFlow->Fill(mult,k,mean2,M2*M1);
		  	}

		  	if(M2 > 0.0)
		  	{Qx2 = Qx2/M2;
             Qy2 = Qy2/M2;
            }

			sum_D2->SetBinContent(mult,k,sum_D2->GetBinContent(mult,k)+mean2*W);
			sum_D22->SetBinContent(mult,k,sum_D22->GetBinContent(mult,k)+mean2*mean2*W);
                	//d2[mult][k]->Fill(mean2,W);
                	sumPOIW->SetBinContent(mult,k,sumPOIW->GetBinContent(mult,k)+W);
                	sumPOIW2->SetBinContent(mult,k,sumPOIW2->GetBinContent(mult,k)+W*W);
                	corrPOIX->SetBinContent(mult,k,corrPOIX->GetBinContent(mult,k)+Qx2*M2);
                	corrPOIY->SetBinContent(mult,k,corrPOIY->GetBinContent(mult,k)+Qy2*M2);
					sumPOIM2->SetBinContent(mult,k,sumPOIM2->GetBinContent(mult,k)+M2);
	               
		   			correctionX1->Fill(mult,k,Qx2,M2);
		   			correctionY1->Fill(mult,k,Qy2,M2);
	}
	


}




void V2Utilities::V2Write(TString id){
	TFile *G = new TFile(Form(id(0,id.Sizeof()-5) + "V2"+ name + ".root"),"recreate");
	refFlow->Write();
	difFlow->Write();
	correctionX->Write();
	correctionY->Write();
	correctionX1->Write();
	correctionY1->Write();
	RP_resolution->Write();
	for(int j =0 ; j< anabinN ; j++){
		//V2cosdeltaPHI[j]->Write();
		//V2mean2[j]->Write();
		//V2cos2phi[j]->Write();
		//V2sin2phi[j]->Write();
		//V2VariableCheck[j]->Write();
		//V2VariableMult[j]->Write();		
		//V2phiCheck[j]->Write();
		//V2dphiCheck[j]->Write();
		//BINV2cosdeltaPHI[j]->Write(); 
         BINV2mean2[j]->Write(); 
        // BINV2cosphi1[j]->Write();
         //BINV2sinphi1[j]->Write();
	     //BINV2cosphi2[j]->Write();
         //BINV2sinphi2[j]->Write();
         V2VariableCheck[j]->Write();
         //BINV2VariableMult[j]->Write();
         //BINV2dphiCheck[j]->Write();
         //BINV2phiCheck1[j]->Write();
         //BINV2phiCheck2[j]->Write();
		//RPmPhi[j]->Write();
		//WsumPOI[j]->Write();
		//Wsum2POI[j]->Write();
		//WsumREF[j]->Write();
		//Wsum2REF[j]->Write();
	}	
	 G->Close();

	TFile *K = new TFile(Form(id(0,id.Sizeof()-5)+"v2Hist"+name+".root"),"recreate");
		
	sum_C2->Write();
	sum_C22 ->Write();	
    corrPOIX->Write();
    corrREFX->Write();
    corrPOIY->Write();
    corrREFY->Write();
    sum_D2->Write();
    sum_D22->Write();
	sumM1->Write();
	sumS11REF->Write();
    sumREFW->Write();
    sumREFW2->Write();
	sumPOIW->Write();
	sumPOIW2->Write();
    sumPOIM2->Write();
    BINPOIEtaCheck->Write();
    BINREFEtaCheck->Write();
	K->Close();

}
double V2Utilities::rapidity(StMuTrack *track, double mass){ 
	Double_t E = sqrt(mass*mass + track->p().magnitude()*track->p().magnitude());
	Double_t rapidity = 0.5*log((E+track->p().z())/(E-track->p().z()));
	return(rapidity);
}

void V2Utilities::SetMass(double M1, double M2){
mass1 = M1;
mass2 = M2;
}

void V2Utilities::NoJobV2Calc(){


}


	


