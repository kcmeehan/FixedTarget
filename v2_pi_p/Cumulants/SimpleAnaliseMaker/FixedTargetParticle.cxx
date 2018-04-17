#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TClonesArray.h"
#include "TList.h"
#include "TCanvas.h"
#include "TObjArray.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include "FixedTargetParticle.h"
#include <fstream>


ClassImp(FixedTargetParticle)


	FixedTargetParticle::FixedTargetParticle(char* a, double amass2up, double amass2down,  double amass, int acharge, double ansigmaCut ,int aparticleid){
		name = a;
		mass2up = amass2up;
		mass2down = amass2down;
		charge = acharge;
		mass = amass;
		nsigmaCut = ansigmaCut;
		particleid = aparticleid;
		nsigma = 0;
		Count  = 0;
		tofnsigmaCut = 1;
		nsigmaoffset = 0;
 		int binNumber = 200;
		rapCMS = 1.52;
		//anabinN = 10;
		P = new TH1D(Form("p%s",name),Form("P%s",name),binNumber,0,5);
		P->GetXaxis()->SetTitle("p[GeV/c]");
		P->GetYaxis()->SetTitle("dN/dp[1/GeV*c]");
		Pt = new TH1D(Form("p_{T}%s",name),Form("p_{T}%s",name),binNumber,0,5);
		Pt->GetXaxis()->SetTitle("p[GeV/c]");
		Pt->GetYaxis()->SetTitle("dN/dp[c/GeV]");
		nSigmaPr = new TH1D(Form("nSigmaProton%s",name),Form("nSigmaProton%s",name),binNumber,-nsigmaCut+0.105,nsigmaCut+0.105);
		nSigmaPr->GetXaxis()->SetTitle("nSigmaProton");
		nSigmaPr->GetYaxis()->SetTitle("dN/dnSigmaPr");
		nSigmaPi = new TH1D(Form("nSigmaPion%s",name),Form("nSigmaPion%s",name),binNumber,-nsigmaCut,nsigmaCut);
		nSigmaPi->GetXaxis()->SetTitle("nSigmaPion");
		nSigmaPi->GetYaxis()->SetTitle("dN/dnSigmaPi");
		nSigmaK = new TH1D(Form("nSigmaKaon%s",name),Form("nSigmaKaon%s",name),binNumber,-nsigmaCut,nsigmaCut);
		nSigmaK->GetXaxis()->SetTitle("nSigmaKaon");
		nSigmaK->GetYaxis()->SetTitle("dN/dnSigmaKaon");
		nSigmaE = new TH1D(Form("nSigmaElectron%s",name),Form("nSigmaElectron%s",name),binNumber,-nsigmaCut,nsigmaCut);
		nSigmaE->GetXaxis()->SetTitle("nSigmaElectron");
		nSigmaE->GetYaxis()->SetTitle("dN/dnSigmaE");
		mass_2 = new TH1D(Form("mass2%s",name),Form("mass^{2}%s",name),3*binNumber,0,4);//mass2down-0.2,mass2up+0.2);
		mass_2->GetXaxis()->SetTitle("mass^{2}[GeV^{2}/c^{4}]");
		mass_2->GetYaxis()->SetTitle("dN/dmass2");
		y = new TH1D(Form("y%s",name),Form("y%s",name),binNumber,-3,3);
		y->GetXaxis()->SetTitle("y");
		y->GetYaxis()->SetTitle("dN/dy");
		ycms = new TH1D(Form("ycms%s",name),Form("ycms%s",name),3*binNumber,-3,3);
		ycms->GetXaxis()->SetTitle("ycms");
		ycms->GetYaxis()->SetTitle("dN/dycms");
		eta = new TH1D(Form("#eta%s",name),Form("#eta%s",name),3*binNumber,-3,3);
		eta->GetXaxis()->SetTitle("#eta");
		eta->GetYaxis()->SetTitle("dN/d#eta");
		phi = new TH1D("phi","Phi",binNumber,-2*TMath::Pi(),2*TMath::Pi());
		phi->GetXaxis()->SetTitle("#phi");
		phi->GetYaxis()->SetTitle("dN/d#phi");
		mass2vsP = new TH2D(Form("mass2vsP%s",name), Form("mass2VSP%s",name),binNumber,0,5,binNumber,-1,2);
		mass2vsP->GetXaxis()->SetTitle("p[GeV/c]");
		mass2vsP->GetYaxis()->SetTitle("m^{2}[GeV^{2}/c^{4}]");
		NoPerEvent = new TH1D("mult","mult", 100,0,1);		
		dEdxvsP =  new TH2D(Form("dEdxvsp%s",name),Form("dEdXvsp%s",name),binNumber,0,5,binNumber,0,10);
		dEdxvsP ->GetXaxis()->SetTitle("p[GeV/c]");
		dEdxvsP ->GetYaxis()->SetTitle("dE/dx[keV/cm]");
		dEdxvsPt =  new TH2D(Form("dEdxvspt%s",name),Form("dEdXvspt%s",name),binNumber,0,5,binNumber,0,10);
		dEdxvsPt ->GetXaxis()->SetTitle("p_{T}[GeV/c]");
		dEdxvsPt ->GetYaxis()->SetTitle("dE/dx[keV/cm]");
		betavsP = new TH2D(Form("beatvsP%s",name),Form("beatvsp%s",name),4*binNumber,-5,5,4*binNumber,0,1);
		betavsP->GetXaxis()->SetTitle("1/p[GeV/c]");
		betavsP->GetYaxis()->SetTitle("1/#beta");
		//V2deltaPHI = new TH1D(Form("V2deltaPHI%s",name),Form("V2deltaPHI%s",name),90,0,TMath::Pi());
		//V2deltaPHI->GetXaxis()->SetTitle("#delta#phi");
		//V2deltaPHI->GetYaxis()->SetTitle("dN/d#delta#phi");

		
		
		etavsphi = new TH2D("etavsphi","etavsphi",binNumber,-2,0.5,binNumber,0,5);
		etavsphi->GetXaxis()->SetTitle("#eta");
		etavsphi->GetYaxis()->SetTitle("#phi");
		QAToF   = new TH1D("QAToF","qaTof",40,0,5);
		QANoToF = new TH1D("QAnoToF","qaNoTof",40,0,5);
		betaH    = new TH1D("beta","Beta",binNumber,0,1);  
		betaH->GetXaxis()->SetTitle("#beta");
		betaH->GetYaxis()->SetTitle("dN/d#beta");
	 			
		for(int i = 0; i<4 ; i++){
		TofLocal[i] = new TH2D(Form("tofLocal%d",i),Form("toflocal%d",i),250,0,40,250,200,500);
		TofLocal[i]->GetXaxis()->SetTitle("t[ns]");
		TofLocal[i]->GetYaxis()->SetTitle("L [cm]");
		}
		tof = new TH1D("tot","ToT",1000,0,100);
		PL  = new TH1D("pathLenght","pl",150,100,550);
		tofmatch = new TH1D("tofmatch","TM",5,0,5);
		pvsL = new TH2D("pvsl","pvsL",300,0,5,50,0,50);
		Lvst = new TH2D("pvsEta","Lvst",binNumber,-2,0.5,binNumber,0,5);
		runID = new TH1D("runID","ID", 1000,16140033,16141033);
		pxyz = new TH3D("Pxyz","pxyz",100,-3,3,100,-3,3,100,-5,0);		

}

double FixedTargetParticle::rapidity(StMuTrack *track){ 
	Double_t E = sqrt(mass*mass + fabs(charge*charge)*track->p().magnitude()*track->p().magnitude());
	Double_t rapidity = 0.5*log((E+fabs(charge)*track->p().z())/(E-fabs(charge)*track->p().z()));
	return(rapidity);
}

double FixedTargetParticle::rapidityCMS(StMuTrack *track){
	return(rapidity(track)+rapCMS);

}


float	FixedTargetParticle::mass2(StMuTrack* trk){

    StMuBTofPidTraits tof1 = (StMuBTofPidTraits)trk->btofPidTraits();

    float mass = -10.;
	if(!(tof1.beta() == -999)){
    		float beta2 = pow(tof1.beta(),2);
    		float mom2 = trk->p().mag2();

    		float g2 = 1./(1.-beta2);
    		mass = mom2/(g2*beta2);

    	}
    return mass;
	
}

void    FixedTargetParticle::FillRunID(int x){
	runID->Fill(x);

}




float 	FixedTargetParticle::beta(StMuTrack *trk){

	StMuBTofPidTraits tof1 = (StMuBTofPidTraits)trk->btofPidTraits();
	return tof1.beta();

}

void FixedTargetParticle::SetNSigmaOffset(double X){
nsigmaoffset = X;
}

void FixedTargetParticle::SetTofnSigmaCut(double Y){
tofnsigmaCut = Y;
}

void FixedTargetParticle::SetTPCCuts(double incl, double ex){
nsigmaCut   = incl;
exnsigmaCut = ex;
}

bool FixedTargetParticle::AcceptTrackNSigma(StMuTrack *track){
	
		if(track->charge() == charge){	
	switch(particleid){
		case 0:
			if( 	 mass2(track)>mass2down 
				&& mass2(track)<mass2up
			){
			Fill(track);
			
			return true;
			}else{
			
			return false;
			}
			break;
		case 1:
			if(	mass2(track)>mass2down
				&& mass2(track)<mass2up
				&& fabs(track->nSigmaProton()) < nsigmaCut 
				//&& fabs(track->nSigmaProton()) < nsigmaCut
				//&& fabs(track->btofPidTraits().sigmaProton())   < tofnsigmaCut 
				//&& fabs(track->btofPidTraits().sigmaPion())     > 1
				//&& fabs(track->btofPidTraits().sigmaElectron()) > 1
				//&& fabs(track->btofPidTraits().sigmaKaon())     > 1
			){
			nsigma = track->nSigmaProton();
			Fill(track);
			return true;
			}else{
			return false;
			
			}
			break;
		case 2:
			if(mass2(track)>mass2down
				&& mass2(track)<mass2up
				&& fabs(track->nSigmaPion()) < nsigmaCut 
				&& fabs(track->nSigmaProton()) > 1
				//track->nSigmaPion() < nsigmaCut + nsigmaoffset
				//&& track->nSigmaPion() > -nsigmaCut + nsigmaoffset 
				//&& track->btofPidTraits().sigmaPion() < tofnsigmaCut
				//&& track->btofPidTraits().sigmaPion() > -tofnsigmaCut
				//&& fabs(track->nSigmaElectron())                > 1
				//&& fabs(track->btofPidTraits().sigmaProton())   > 1
				//&& fabs(track->btofPidTraits().sigmaElectron()) > 1
				//&& fabs(track->btofPidTraits().sigmaKaon())     > 1
				
			){
			nsigma = track->nSigmaPion();
			Fill(track);
			return true;
			}else{
			return false;
			}
			break;
		case 3:
			if(mass2(track)>mass2down
				&& mass2(track)<mass2up
				&& fabs(track->nSigmaKaon()) < nsigmaCut 
				//track->nSigmaKaon() < nsigmaCut + nsigmaoffset
				//&& track->nSigmaKaon() > -nsigmaCut + nsigmaoffset 
				//&& fabs(track->btofPidTraits().sigmaKaon()) < tofnsigmaCut
				//&& fabs(track->btofPidTraits().sigmaElectron())> 1
			){
			nsigma = track->nSigmaKaon();
			Fill(track);
			return true;
			}else{
			return false;
			}
			break;
		
	}
	}else{
	return false;
	}
}

bool FixedTargetParticle::AcceptTrack(StMuTrack *track){
	if( 	 mass2(track)>mass2down 
				&& mass2(track)<mass2up
				&& particleid == 0
			){
			Fill(track);
	}	

	if(track->charge() == charge ){//&& track->btofPidTraits().matchFlag() < 1){	
	switch(particleid){
		case 0:
			if( 	 mass2(track)>mass2down 
				&& mass2(track)<mass2up
			){
			Fill(track);
			
			return true;
			}else{
			
			return false;
			}
			break;
		case 1:
			if(fabs(track->nSigmaProton()) < nsigmaCut 
				 
				&& fabs(track->nSigmaPion()     ) > exnsigmaCut 
				&& fabs(track->nSigmaKaon()     ) > exnsigmaCut
				//&& fabs(track->nSigmaElectron() ) > 1
				
			){
			nsigma = track->nSigmaProton();
			Fill(track);
			return true;
			}else{
			return false;
			
			}
			break;
		case 2:
			if(track->nSigmaPion() < nsigmaCut 
				&& track->nSigmaPion() > -nsigmaCut 
				&& fabs(track->nSigmaProton()   ) > exnsigmaCut 
				//&& fabs(track->nSigmaKaon()     ) > exnsigmaCut
				//&& fabs(track->nSigmaElectron() ) > 2
			){
			nsigma = track->nSigmaPion();
			Fill(track);
			return true;
			}else{
			return false;
			}
			break;
		case 3:
			if(track->nSigmaKaon() < nsigmaCut 
				&& track->nSigmaKaon() > -nsigmaCut 
				&& fabs(track->nSigmaProton()   ) > exnsigmaCut 
				&& fabs(track->nSigmaPion()     ) > exnsigmaCut
				//&& fabs(track->nSigmaElectron() ) > 1
			){
			nsigma = track->nSigmaKaon();
			Fill(track);
			return true;
			}else{
			return false;
			}
			break;
		case 4:
			if(track->nSigmaElectron() < nsigmaCut 
				&& track->nSigmaElectron() > -nsigmaCut 
				&& mass2(track)> mass2down
				&& mass2(track)<mass2up
			){
			nsigma = track->nSigmaElectron();
			Fill(track);
			return true;
			}else{
			return false;
			}
			break;

	}
	}else{
	return false;
	}

}

void FixedTargetParticle::Fill(StMuTrack *track){
	
		Double_t E = sqrt(mass*mass + fabs(charge*charge)*track->p().magnitude()*track->p().magnitude());
		Double_t rapidity = 0.5*log((E+fabs(charge)*track->p().z())/(E-fabs(charge)*track->p().z()));
		dEdxvsP->Fill(track->p().magnitude(),1000000*track->dEdx());
		dEdxvsPt->Fill(track->pt(),1000000*track->dEdx());
		P->Fill(track->p().magnitude());
		Pt->Fill(track->pt());
		eta->Fill(track->eta());
		y->Fill(rapidity);
		ycms->Fill(rapidity +1.52);
		phi->Fill(track->phi());
		etavsphi->Fill(rapidity,track->pt());
		//if((rapidity + 1.52) > 0 && (rapidity + 1.52) < 0.5)Count++;
		pxyz->Fill(track->p().x(),track->p().y(),track->p().z());
		nSigmaPr->Fill(track->nSigmaProton());
		nSigmaPi->Fill(track->nSigmaPion());
		nSigmaK->Fill(track->nSigmaKaon());
		nSigmaE->Fill(track->nSigmaElectron());
		pvsL->Fill(track->eta(),track->pt());
		if((double)track->btofPidTraits().matchFlag() > 0){ 
		//if(track->p().magnitude() > 0.4 && track->p().magnitude() <0.5  && track->btofPidTraits().pathLength() > 447 && track->btofPidTraits().pathLength() < 455){
		QAToF->Fill(track->p().magnitude());
		betaH->Fill(track->btofPidTraits().beta());
		mass2vsP->Fill(track->p().magnitude(),mass2(track));
		mass_2->Fill(mass2(track));
		betavsP->Fill(track->p().magnitude()/track->charge(),beta(track));
		Count++; 
		PL->Fill(track->btofPidTraits().pathLength());
		tof->Fill(track->btofPidTraits().timeOfFlight());
		tofmatch->Fill(track->btofPidTraits().matchFlag());
		//Lvst->Fill(,track->btofPidTraits().timeOfFlight());
		//pvsL->Fill(track->p().z(),track->p().magnitude());
		
		if(track->p().magnitude()>0.25 && track->p().magnitude() < 0.3)TofLocal[0]->Fill(track->btofPidTraits().timeOfFlight(),track->btofPidTraits().pathLength());
		if(track->p().magnitude()>0.3 && track->p().magnitude() < 0.32)TofLocal[1]->Fill(track->btofPidTraits().timeOfFlight(),track->btofPidTraits().pathLength());
		if(track->p().magnitude()>0.4 && track->p().magnitude() < 0.45)TofLocal[2]->Fill(track->btofPidTraits().timeOfFlight(),track->btofPidTraits().pathLength());
		if(track->p().magnitude()>0.5 && track->p().magnitude() < 0.53)TofLocal[3]->Fill(track->btofPidTraits().timeOfFlight(),track->btofPidTraits().pathLength());
		

		}
		QANoToF->Fill(track->p().magnitude());
}

void FixedTargetParticle::Write(TString id){
	
	TFile *file = new TFile(id(0,id.Sizeof()-5) + "PID"+ name + ".root","recreate");
	cout<<name<<endl;
		dEdxvsP->Write();
		dEdxvsPt->Write();
		P->Write();
		Pt->Write();
		betavsP->Write();
		eta->Write();
		y->Write();
		mass_2->Write();
		ycms->Write();
		nSigmaPr->Write();
		nSigmaPi->Write();
		nSigmaK->Write();
		nSigmaE->Write();
		NoPerEvent->Write();
		phi->Write();
		pxyz->Write();
		etavsphi->Write();
		QAToF->Write();
		QANoToF->Write();
		betaH->Write();
		mass2vsP->Write();
		for(int i = 0; i< 4 ;i++)TofLocal[i]->Write();
		PL->Write();
		tof->Write();
		tofmatch->Write();
		runID->Write();
		Lvst->Write();
		pvsL->Write();
	file->Close();

}

void FixedTargetParticle::EndEvent(){
	
		//if(!(Count == 0))NoPerEvent->Fill((Double_t)sinSUM/Count,Count);
		Count = 0;
		//sinSUM = 0;

}

bool FixedTargetParticle::TofCheck(TObjArray *part){
	double good;
	good =0;
	StMuTrack *track;	
	TObjArray *POI = new TObjArray();
	for(int i =0; i< part->GetEntries(); i++){
	track = (StMuTrack*)part->At(i);
	if(track->btofPidTraits().matchFlag() > 0  
	&& track->p().magnitude()> 0.25 
	&& track->p().magnitude()< 0.55
	&& AcceptTrack(track)
	){ 
	POI->Add(track);
	
	}
	//if(Count>50)break;
	}
	
	
	for(int j =0; j< POI->GetEntries(); j++){
		track = (StMuTrack*)POI->At(j);
		if(fabs(track->btofPidTraits().sigmaPion())<2)good = good + 1;
	
	}
	NoPerEvent->Fill((Double_t)good/POI->GetEntries());
	if((Double_t)good/POI->GetEntries() > 0.1){
	return true;
	}else{
	return false;
	}
	
}

