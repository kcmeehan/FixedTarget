#include "SimpleAnaliseMaker.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TClonesArray.h"
#include "TList.h"
#include "TCanvas.h"
#include "TProfile2D.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
#include <vector>
#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


ClassImp(SimpleAnaliseMaker)
//void TH1DInit(TH1D *h1,const char* name, const char* title, Int_t bins, float min,float max,const char* XaxisTitle,const 	char* YaxisTitle){
//h1 = new TH1D(name,title,bins,min,max);
//h1->GetXaxis()->SetTitle(XaxisTitle);
//h1->GetYaxis()->SetTitle(YaxisTitle);

//}


void SimpleAnaliseMaker::reactionPlane(TObjArray *P){

	StMuTrack *track;	
	for(int i = 0; i < P->GetEntries() ; i++){
		track = (StMuTrack*)P->At(i);
	
		if(track->pt() > 0.15 && track->pt() < 2){
		qx->Fill(track->pt()*cos(2*track->phi()));
		qy->Fill(track->pt()*sin(2*track->phi()));
		qxy->Fill(track->pt()*cos(2*track->phi()),track->pt()*sin(2*track->phi()));
	}
	
	}

}

void SimpleAnaliseMaker::fillV2ReactionPlane(TObjArray *Tracks, TObjArray *POI){

	Double_t QxA = 0.0;
	Double_t QyA = 0.0;
	Double_t QxB = 0.0;
        Double_t QyB = 0.0;

	Double_t maxetaA = 1;
	Double_t maxetaB = -0.2;
	Double_t minetaA =  0.2;
	Double_t minetaB =  -1;
	StMuTrack *track;
	for(int ii = 0 ; ii < Tracks->GetEntries(); ii++){
			track = (StMuTrack*)Tracks->At(ii);
		if(track->pt() > 0.15 && track->pt() < 2){
			
			if(track->eta() < maxetaA && track->eta() > minetaA){
			QxA += track->pt()*cos(2*track->phi()) - Meanqx;
			QyA += track->pt()*sin(2*track->phi()) - Meanqy;
			}
			
			if(track->eta() < maxetaB && track->eta() > minetaB){
			QxB += track->pt()*cos(2*track->phi()) - Meanqx;
                        QyB += track->pt()*sin(2*track->phi()) - Meanqy;
                        }

		}
	}

	Double_t RPA =  atan(QyA/QxA)/2;
	Double_t RPB =  atan(QyB/QxB)/2;
	ReactionP->Fill(cos(2*(RPA-RPB)));
	
	for(int ii = 0 ; ii < POI->GetEntries(); ii++){
		track = (StMuTrack*)POI->At(ii);
		Double_t DP;
		if(track->eta() > minetaA + (maxetaA- minetaB)/2){
		//Double_t Qx1 = QxA -(track->pt()*cos(2*track->phi()) - Meanqx);
		//Double_t Qy1 = QyA -(track->pt()*sin(2*track->phi()) - Meanqy);
		DP = track->phi() - RPB;
		}else{
		//Double_t Qx1 = QxB -(track->pt()*cos(2*track->phi()) - Meanqx);
                //Double_t Qy1 = QyB -(track->pt()*sin(2*track->phi()) - Meanqy);
		DP = track->phi() - RPA;
		}
		if(DP<0)DP = DP + 2*TMath::Pi();		
		if(DP>TMath::Pi())DP = 2*TMath::Pi() - DP;
		RPdphi->Fill(DP);
		cosdeltaphiBIN->Fill(cos(2*DP));	
	}



}
void SimpleAnaliseMaker::Spectra(TObjArray *part , double mass , TH1D *h1,TH1D *h2){
	
	StMuTrack *track;

	for(int i =0 ; i < part->GetEntries(); i++){
	track = (StMuTrack*)part->At(i);
		Double_t rap = rapidity(track,mass,1);
		if(rap > -1.57 && rap <-1.47){
		Double_t m0m = sqrt(track->pt()*track->pt() + mass*mass)- mass;
		if(track->charge() ==  1)h1->Fill(m0m);
		if(track->charge() == -1)h2->Fill(m0m);
		} 	
	}


} 

void SimpleAnaliseMaker::SpectraGraph(TH1D *h1){


}

double SimpleAnaliseMaker::rapidity(StMuTrack *track, Double_t mass, Double_t charge){
		Double_t E = sqrt(mass*mass + abs(charge*charge)*track->p().magnitude()*track->p().magnitude());
		Double_t rapidity = 0.5*log((E+abs(charge)*track->p().z())/(E-abs(charge)*track->p().z()));
		return(rapidity);

}

void SimpleAnaliseMaker::SetxPositionCuts(double min,double max){
	xPositionCutmax = max;
	xPositionCutmin = min;
}
void SimpleAnaliseMaker::SetyPositionCuts(double min,double max){
	yPositionCutmax = max;
	yPositionCutmin = min;
}
void SimpleAnaliseMaker::SetzPositionCuts(double min,double max){
	zPositionCutmax = max;
	zPositionCutmin = min;
}
void SimpleAnaliseMaker::SetxyRadiousCut(double r){
	xyRadiousCut = r;
}
void SimpleAnaliseMaker::SetnsigmaCut(double r){
	nsigmaCut = r;
}
void SimpleAnaliseMaker::acceptEvent(){
	StMuDst *events = maker->muDst();
	int verticies = maker->muDst()->numberOfPrimaryVertices();
	
	for(int i =0 ; i <  verticies; i++){  	
			events->setVertexIndex(i);
			double Y = events->primaryVertex(i)->position().y();
			double X = events->primaryVertex(i)->position().x();
			double Z = events->primaryVertex(i)->position().z();
	 		if(Y<yPositionCutmax && Y>yPositionCutmin && X<xPositionCutmax && X>xPositionCutmin && Z<zPositionCutmax && Z > zPositionCutmin){ //&& events->numberOfPrimaryTracks()>5){

	verticesIndex.push_back(true); 
	
	}else{
	 verticesIndex.push_back(false);
	}
	//cout<<i<<": "<<Y<<" "<<X<<" "<<Z<<" "<<verticesIndex[i]<<endl;
	
	}
}
bool SimpleAnaliseMaker::acceptTrack(StMuTrack *track){
	Double_t X = (Double_t)track->nHits()/track->nHitsPoss();
if(track->nHitsDedx()>dEdxCUT && track->nHits()>nHitsCUT &&  X > nHITPOSSCUT && track->flag()>FLAGCUT){
NHits_Poss->Fill(X);
NinTrack->Fill(track->nHits());
NindEdx->Fill(track->nHitsDedx());
return true;
}else{
return false;
}
//cout<<track->nHitsPoss()<<" "<<track->nHits()<<endl;
}




float SimpleAnaliseMaker::mass2(StMuTrack* trk){

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



float SimpleAnaliseMaker::beta(StMuTrack *trk){

	return trk->btofPidTraits().beta();

}

SimpleAnaliseMaker::SimpleAnaliseMaker(StMuDstMaker *x, TString y, double min, double max, int D, double pTMAX , double pTMIN, double eTAMAX, double eTAMIN,int PID,double dEdxCUT1,double nHitsCUT1,double nHITPOSSCUT1 ,double FLAGCUT1,double eup1,double ed1,double eup2,double ed2,double TPCin, double TPCex, int V2BINFLAG) : StMaker("SimpleAnaliseMaker") {
MultMin = min;
MultMax = max;
maker = x;
outputFile = y;
VID = D;
	binFLAG = V2BINFLAG;
	dEdxCUT = dEdxCUT1;
	nHitsCUT = nHitsCUT1;
	nHITPOSSCUT = nHITPOSSCUT1;
	FLAGCUT = FLAGCUT1;
	PTMAX = pTMAX;
	PTMIN = pTMIN;
	ETAMAX = eTAMAX;
	ETAMIN = eTAMIN;
	PIDflag = PID;
	etaup1 = eup1;
	etadown1 = ed1;
	etaup2 = eup2;
    etadown2 = ed2;

	
	 xPositionCutmin = -400;
	 xPositionCutmax = 400;
	 yPositionCutmin = -400;
	 yPositionCutmax = 400;
	 zPositionCutmin = -400;
	 zPositionCutmax = 400;
	 xyRadiousCut = 0;
	 nsigCut = TPCin;
	 exnsigCut  = TPCex;
	Protons = new TObjArray();
	Pions = new TObjArray();
	Kaons = new TObjArray();
	PionsP = new TObjArray();
	PionsN = new TObjArray();
	KaonsP = new TObjArray();
	KaonsN = new TObjArray();	
	eventtracksALL = new TObjArray();
	deuteron = new TObjArray();
	eventtracks1 = new TObjArray();
	eventtracks2 = new TObjArray();	
}

Int_t SimpleAnaliseMaker::Init(){
	int binNumber = 200;
	pt = new TH1D("pt","PT",binNumber,0,2.8);
	ptTOF = new TH1D("ptTOF","PTtof",binNumber,0,2.8);
	N = new TH1D("n","Mulitiplicity",400,0,1000);
	eta = new TH1D("#eta","#eta",3*binNumber,-2.5,2.5);
	EvsP = new TH2D("dEdxvsP","EvsP",binNumber,-5,5,binNumber,0,10);
	NinTrack = new TH1D("hits in Track","Hits in Track reconstructin",50,0,50);
	NindEdx = new TH1D("noofhitsindEdx","Hits in dE/dx calculation",50,0,50);
	centerX = new TH1D("VertexX","vertexx",binNumber,xPositionCutmin,xPositionCutmax);
	centerY = new TH1D("VertexY","vertexy",binNumber,yPositionCutmin,yPositionCutmax);
	centerZ = new TH1D("VertexZ","vertexz",binNumber,zPositionCutmin,zPositionCutmax);
	NHits_Poss = new TH1D("NHits_Poss","nHits_Poss",100,0,1);
	VertexXYPosition = new TH2D				("VertexXYPosition","vertexXYPosition",binNumber,xPositionCutmin,xPositionCutmax,binNumber,yPositionCutmin,yPositionCutmax);
	VertexXZPosition = new TH2D("VertexXZPosition","vertexXZPosition",binNumber,zPositionCutmin,zPositionCutmax,binNumber,xPositionCutmin,xPositionCutmax);
	VertexYZPosition = new TH2D("VertexYZPosition","vertexYZPosition",binNumber,zPositionCutmin,zPositionCutmax,binNumber,yPositionCutmin,yPositionCutmax);
mass2vsP = new TH2D("mas2svsP","mass2vsp",5*binNumber,-5,5,5*binNumber,-0.5,5);
Nmass2 = new TH1D("mas2","mass2",2*binNumber,-0.5,10);
betavsP = new TH2D("betavsP","beatvsp",4*binNumber,-5,5,4*binNumber,0,4);
ProtonP = new FixedTargetParticle("Proton+",1.1,0.6,0.938,1,2,1);
PionP = new FixedTargetParticle("Pion+",0.1,-0.05,0.138,1,2,2);
KaonP = new FixedTargetParticle("Kaon+",0.3,0.2,0.49,1,2,3);
ProtonN = new FixedTargetParticle("Proton-",1.1,0.7,0.938,-1,2,1);
PionN = new FixedTargetParticle("Pion-",0.1,-0.05,0.138,-1,2,2);
KaonN = new FixedTargetParticle("Kaon-",0.3,0.2,0.49,-1,2,3);
Electron = new FixedTargetParticle("Electron",0.01,0,0.005,1,2,4);
Deuteron = new FixedTargetParticle("Deuteron",4.1,2.9,1.85,1);
Triton = new FixedTargetParticle("triton",0.55,0.4,0.938,1,2,1);
Helion = new FixedTargetParticle("helion",-0.1,-0.5,0.138,1,2,2);
	KaonN->SetTofnSigmaCut(2);
	ProtonN->SetTofnSigmaCut(2);
	KaonP->SetTofnSigmaCut(2);
	ProtonP->SetTofnSigmaCut(2);
	PionP->SetTofnSigmaCut(2);
	PionN->SetTofnSigmaCut(2);
	
	KaonN->SetTPCCuts(nsigCut,exnsigCut);
    ProtonN->SetTPCCuts(nsigCut,exnsigCut);
    KaonP->SetTPCCuts(nsigCut,exnsigCut);
    ProtonP->SetTPCCuts(nsigCut,exnsigCut);
    PionN->SetTPCCuts(nsigCut,exnsigCut);
	PionP->SetTPCCuts(nsigCut,exnsigCut);

v2Pion = new V2Utilities("Pions",0.1395);

 v2Pion->SetVID(2);
 v2Pion->SetBin(3.0,0.0);

v2Proton = new V2Utilities("Protons",0.938);

 v2Proton->SetVID(2);
 v2Proton->SetBin(2.0,0.3);


v2Piondir = new V2Utilities("PionsDir",0.1395);

 v2Piondir->SetVID(2);
 v2Piondir->SetBin(1.6,0.0);

v2Protondir = new V2Utilities("ProtonsDir",0.1395);

 v2Protondir->SetVID(2);
 v2Protondir->SetBin(1.6,0.0);
v2Kaon = new V2Utilities("Kaons",0.49);

 v2Kaon->SetVID(2);
 v2Kaon->SetBin(1.6,0.0);
v2All = new V2Utilities("ALL",0);

 v2All->SetVID(2);
 v2All->SetBin(2.5,0.0);
 
dphiBIN = new TH1D("dphiBIN","DphiBin",200,-10,10);
dphi = new TH1D("dphi","Dphi",90,0,TMath::Pi());
RPdphi = new TH1D("dphiRP","DphiRP",90,0,TMath::Pi());
cosdeltaphiBIN = new TH1D("cosdeltaphiBIN","v2cosdeltaphi",binNumber,-1,1);
cosdeltaphi = new TH1D("cosdeltaphi","v2cosdeltaphi",binNumber,-1,1);
phi = new TH1D("phi","Phi",binNumber,-2*TMath::Pi(),2*TMath::Pi());
detadphi = new TH2D("detadphi","dphideta",binNumber,-3.5,3.5,binNumber,0,TMath::Pi());

	for(int i = 0; i<4 ; i++){
		TofLocal[i] = new TH1D(Form("dEdxLocal%d",i),Form("dEdxlocal%d",i),400,0,10);
		TofLocal[i]->GetXaxis()->SetTitle("dEdx[kEV/cm]");
		TofLocal[i]->GetYaxis()->SetTitle("dN/ddEdx");
		}
	tot = new TH1D("tot","ToT",100,0,30);

qx = new  TH1D("qx","Qx",300,-6,6);
qy = new  TH1D("qy","Qy",300,-6,6);
qxy = new TH2D("qxy","Qxy",300,-6,6,300,-6,6);
ReactionP = new TH1D("RP","reactP",100,-TMath::Pi(),TMath::Pi());

Meanqx = 0.0004712;
Meanqy = 0.0001464;
return StMaker::Init();
}



Int_t SimpleAnaliseMaker::Make(){
				
	int numberOfParticles = 0;
	verticesIndex.clear();
	acceptEvent();								//vertex cut implementation
	StMuDst *events = maker->muDst();
	StMuTrack *track;
	//eventtracksALL->Clear();
	/*for(int g = 0; g < verticesIndex.size(); g++){
	
		if(verticesIndex[g]){
			events->setVertexIndex(g);
			TObjArray *tracksToAnalise = events->primaryTracks();
			TObjArrayIter GetTracks(tracksToAnalise);
			while((track=(StMuTrack*)GetTracks.Next())){

	  			if(acceptTrack(track)){					//track QA fot ToF chceck
					eventtracksALL->Add(track);
				}
			}
		}
	}*/



	Int_t maxTriggerIds = events->event()->triggerIdCollection().nominal().maxTriggerIds();
	int trigflag = 0;
        for( Int_t iTrig = 0; iTrig < maxTriggerIds; iTrig++ ){
            if(events->event()->triggerIdCollection().nominal().triggerId(iTrig) == 1) trigflag++;
	}
if(trigflag > 0){	//gtrigger cuts


				// verticesIndex.size(); kk++){		//loop over verticies
for(int kk = 0; kk < 1 ; kk++){ 
	if(verticesIndex[kk]){
		events->setVertexIndex(kk);
		TObjArray *tracksToAnalise = events->primaryTracks();
		TObjArrayIter GetTracks(tracksToAnalise);
		eventtracksALL->Clear();
		while((track=(StMuTrack*)GetTracks.Next())){

	  		if(acceptTrack(track)){	//track cuts and QA for analysis
			eventtracksALL->Add(track);
		
			
			}
		}
	}

if(verticesIndex[kk] && (VID == 2 || eventtracksALL->GetEntries() < MultMax) && (VID == 2 ||  eventtracksALL->GetEntries() > MultMin) && (VID == 1 || events->event()->grefmult() > MultMin) && (VID == 1 || events->event()->grefmult() < MultMax) ){					//event cuts
	
	//cout<<"Events"<<endl;
	double Y = events->primaryVertex(kk)->position().y();
	double X = events->primaryVertex(kk)->position().x();
	double Z = events->primaryVertex(kk)->position().z();
	//reactionPlane(eventtracksALL);
	dphiBIN->Fill(events->primaryVertex(kk)->ranking());
	centerX->Fill(X);
	centerY->Fill(Y);
	centerZ->Fill(Z);
	VertexXYPosition->Fill(X,Y);
	VertexXZPosition->Fill(Z,X);
	VertexYZPosition->Fill(Z,Y);
	
	
	
	
	eventtracks1->Clear();
	eventtracks2->Clear();
	
	

	for(int ii = 0 ; ii< eventtracksALL->GetEntries(); ii++){ 			//loop over tracks
		
		//cout<<"Tracks"<<endl;	
		
		track = (StMuTrack*)eventtracksALL->At(ii);
		if(track->pt() < PTMAX && track->pt() >PTMIN && track->eta()<ETAMAX && track->eta()>ETAMIN && track->charge() != 0)eventtracks1->Add(track);
		if(track->pt() < PTMAX && track->pt() >PTMIN && track->eta()<ETAMAX && track->eta()>ETAMIN && track->charge() != 0 && track->charge() > 0)eventtracks2->Add(track); 
		betavsP->Fill(1/track->p().magnitude()/track->charge(),1/beta(track));		
		EvsP->Fill((Double_t)track->p().magnitude()/track->charge(),1000000*track->dEdx());
		Nmass2->Fill(mass2(track));
		if(track->btofPidTraits().matchFlag()>0)mass2vsP->Fill((Double_t)track->p().magnitude()/track->charge(),mass2(track));
	
		if(track->pt() > 0.2  && track->pt() < 0.6)TofLocal[0]->Fill(1000000*track->dEdx());
		if(track->pt() > 0.6  && track->pt() < 0.8)TofLocal[1]->Fill(1000000*track->dEdx());
		if(track->pt() > 0.8  && track->pt() < 1.0)TofLocal[2]->Fill(1000000*track->dEdx());
		if(track->pt() > 1.2  && track->pt() < 1.4)TofLocal[3]->Fill(1000000*track->dEdx());
		
			//qy->Fill(track->btofPidTraits().matchFlag());
			

		if((PIDflag == 1 || PIDflag == 2) && ProtonP->AcceptTrackNSigma(track) || ProtonN->AcceptTrackNSigma(track)){// || ProtonP->AcceptTrack(track) || ProtonN->AcceptTrack(track)  ){
					
			Protons->Add(track);
			
		}else if((PIDflag == 2 || PIDflag == 3) && (PIDflag == 3 || track->btofPidTraits().matchFlag() < 1) && (ProtonP->AcceptTrack(track) || ProtonN->AcceptTrack(track)) ){
			//if(rapidity(track,0.938,1)>-1.52)
				Protons->Add(track);
		//	qx->Fill(track->btofPidTraits().matchFlag());
		} 

		if((PIDflag == 1 || PIDflag == 2) && (PionP->AcceptTrackNSigma(track) || PionN->AcceptTrackNSigma(track))){//|| PionP->AcceptTrack(track) || PionN->AcceptTrack(track)  ){
				
			Pions->Add(track);
			if(track->charge() > 0){PionsP->Add(track);
			}else{
			PionsN->Add(track);
			}
			//PionP->FillRunID(events->event()->runNumber());

			
		}else if((PIDflag == 2 || PIDflag == 3) && (PIDflag == 3 || track->btofPidTraits().matchFlag() < 1) && (PionN->AcceptTrack(track) || PionP->AcceptTrack(track))  ){
		//qx->Fill(track->btofPidTraits().matchFlag());
			Pions->Add(track);
		 	 if(track->charge() > 0){PionsP->Add(track);
                        }else{
                        PionsN->Add(track);
                        }
		}

		if((PIDflag == 1 || PIDflag == 2) && KaonP->AcceptTrackNSigma(track) || KaonN->AcceptTrackNSigma(track) ){ //|| KaonP->AcceptTrack(track) || KaonN->AcceptTrack(track) ){
					
			Kaons->Add(track);
			 if(track->charge() > 0){KaonsP->Add(track);
                        }else{
                        KaonsN->Add(track);
                        }
		}else if((PIDflag == 2 || PIDflag == 3) && (PIDflag == 3 || track->btofPidTraits().matchFlag() < 1) && (KaonP->AcceptTrack(track) || KaonN->AcceptTrack(track)) ){
			Kaons->Add(track);		
			 if(track->charge() > 0){KaonsP->Add(track);
                        }else{
                        KaonsN->Add(track);
                        }
	
		}
		
		
		Electron->AcceptTrack(track);
		Deuteron->AcceptTrack(track);
		
		//if(track->btofPidTraits().matchFlag() >0 && Unknown->AcceptTrack(track))Unknown->FillRunID(events->event()->runNumber());
		if(track->btofPidTraits().matchFlag() >0) ptTOF->Fill(track->pt()); 
				
		pt->Fill(track->pt());
		eta->Fill(track->eta());
		phi->Fill(track->phi());

	
 	}


	
		

		
//	StMuTrack *track1;
//	StMuTrack *track2;
	 
	/*
	for(Int_t i = 0;i<eventtracks1->GetEntries(); i++){
		track1 = (StMuTrack*)eventtracks1->At(i);
		for(Int_t j = i+1; j<eventtracks2->GetEntries();j++){
			track2 = (StMuTrack*)eventtracks2->At(j);
				Double_t delta = track1->phi()-track2->phi();
				
				if(delta<0)delta += 2*TMath::Pi();
				if(delta > TMath::Pi()) delta =  2*TMath::Pi()-delta;
				dphiBIN->Fill(delta);
				cosdeltaphiBIN->Fill(TMath::Cos(2*delta));
				
			
		}
		
		
	}

	for(Int_t i = 0;i<eventtracksALL->GetEntries(); i++){
		track1 = (StMuTrack*)eventtracksALL->At(i);
		for(Int_t j = i+1; j<eventtracksALL->GetEntries();j++){
			track2 = (StMuTrack*)eventtracksALL->At(j);
				Double_t delta = track1->phi()-track2->phi();
				Double_t deta  = track1->eta()-track2->eta();
				
				if(delta<0)delta += 2*TMath::Pi();
				if(delta > TMath::Pi()) delta =  2*TMath::Pi()-delta;
				dphi->Fill(delta);
				cosdeltaphi->Fill(TMath::Cos(2*delta));
				detadphi->Fill(deta,delta);
				
			
		}
		
	
	}
	
	*/	
		

		//Spectra(Protons,ProtonP->mass,protonPSpectra,protonNSpectra);
		//Spectra(Pions,PionP->mass,pionPSpectra,pionNSpectra);
		//Spectra(Kaons,KaonP->mass,kaonPSpectra,kaonNSpectra);
		//fillV2ReactionPlane(eventtracksALL,eventtracksALL);	
		//ProtonP->particleV2Fill(Protons);
		//PionP->particleV2Fill(Pions);
		//ProtonP2->particleV2Fill(Protons);
		//PionP2->particleV2Fill(Pions);
		//KaonP->particleV2Fill(Kaons);
		//KaonN->particleV2Fill(Kaons);
		//Triton->particleV2Fill(eventtracksALL);
		//Triton->particleV2BINFill(eventtracksALL,-2.0,-1.3,-0.9,0.0);//deta = 0.05
		//PionP2->particleV2BINFill(Pions,-2.0,-1.6,-1.1,0.0);//de 
		//
		//v2Proton->MIXparticleV2BINFill(Protons,etaup1,etadown1,etaup2,etadown2,eventtracks1,etaup1,etadown1,etaup2,etadown2);
		int bin = binFLAG;
		int mult = (int)eventtracksALL->GetEntries();
		cout<<"V2"<<endl;
		v2All->RefParticleV2Fill(eventtracks1,eventtracks1,bin,etaup1,etadown1,etaup2,etadown2,mult);
		v2Pion->RefParticleV2Fill(eventtracks1,PionsN,bin,etaup1,etadown1,etaup2,etadown2,mult);
		v2Piondir->RefParticleV2Fill(eventtracks1,PionsP,bin,etaup1,etadown1,etaup2,etadown2,mult);
		v2Proton->RefParticleV2Fill(eventtracks1,Protons,bin,etaup1,etadown1,etaup2,etadown2,mult);
		v2Kaon->RefParticleV2Fill(eventtracks1,Kaons,bin,etaup1,etadown1,etaup2,etadown2,mult);
		v2Protondir->RefParticleV2Fill(eventtracks1,Pions,bin,etaup1,etadown1,etaup2,etadown2,mult);
		//v2All->RPFill(eventtracks1,eventtracks1,-1);
		//v2Pion->RPFill(eventtracks1,PionsN,-1);
		//v2Piondir->RPFill(eventtracks1,PionsP,-1);
		//v2Proton->RPFill(eventtracks1,Protons,-1);
		
		//v2Piondir->particleV2BINFill(Pions,etaup1,etadown1,etaup2,etadown2);
		//v2Protondir->particleV2BINFill(Protons,etaup1,etadown1,etaup2,etadown2);
		//v2Pion->MIXparticleV2BINFill(Pions,etaup1,etadown1,etaup2,etadown2,eventtracks1,etaup1,etadown1,etaup2,etadown2);
		//v2Kaon->MIXparticleV2BINFill(Kaons,etaup1,etadown1,etaup2,etadown2,eventtracks1,etaup1,etadown1,etaup2,etadown2);
//		KaonP->particleV2BINFill(Kaons,-2.0,-1.3,-0.9,0.0);
		//ProtonP2->particleV2BINFill(racksALL,-2.0,-1.6,-1.1,0.0);//deat = 0.5
		Protons->Clear();
		Pions->Clear();
		Kaons->Clear();
		PionsP->Clear();
		PionsN->Clear();
		KaonsP->Clear();
		KaonsN->Clear();
		eventtracks1->Clear();
		eventtracks2->Clear();
		N->Fill(events->numberOfPrimaryTracks());
	 	eventtracksALL->Clear();
	}
	}	//KaonP->KaonV2Fill(Kaons,Pions);
		//ProtonP->particleV2BINFill(Protons, 0, 0.25, 0.5, 1);
		//PionP->particleV2BINFill(Pions, 0, 0.25, 0.5, 1);
		//KaonP->particleV2BINFill(Kaons, 0, 0.25, 0.5, 1);
	}	
	


		/*ProtonP->EndEvent();
		KaonP->EndEvent();
		PionP->EndEvent();
		ProtonN->EndEvent();
		KaonN->EndEvent();
		PionN->EndEvent();
		Deuteron->EndEvent();
		Triton->EndEvent();
		Unknown->EndEvent();*/


		
return kStOK;
}



Int_t SimpleAnaliseMaker::Finish(){

	
	centerX->GetXaxis()->SetTitle("x [cm]");
	centerX->GetYaxis()->SetTitle("dN/dx [1/cm]");
	centerY->GetXaxis()->SetTitle("y [cm]");
	centerY->GetYaxis()->SetTitle("dN/dy [1/cm]");
	centerZ->GetXaxis()->SetTitle("z [cm]");
	centerZ->GetYaxis()->SetTitle("dN/dz [1/cm]");
	N->GetXaxis()->SetTitle("Mulitiplicity");
	N->GetYaxis()->SetTitle("Number of events[]");
	pt->GetXaxis()->SetTitle("p_{T}[GeV/c]");
	pt->GetYaxis()->SetTitle("dN/dpt");
	NinTrack->GetXaxis()->SetTitle("Number of hits used[]");
	NinTrack->GetYaxis()->SetTitle("Number of Events[]");
	NindEdx->GetXaxis()->SetTitle("Number of tracks used[]");
	NindEdx->GetYaxis()->SetTitle("Number of Events[]");
	EvsP ->GetXaxis()->SetTitle("p[GeV/c]");
	EvsP ->GetYaxis()->SetTitle("dE/dx[keV/cm]");
	VertexXYPosition->GetXaxis()->SetTitle("x[cm]");
	VertexXYPosition->GetYaxis()->SetTitle("y[cm]");
	mass2vsP->GetXaxis()->SetTitle("p[GeV/c]");
	Nmass2->GetXaxis()->SetTitle("m^{2}[GeV^{2}/c^{4}]");
	mass2vsP->GetYaxis()->SetTitle("m^{2}[GeV^{2}/c^{4}]");
	betavsP->GetXaxis()->SetTitle("1/p[1/(GeV/c)]");
	betavsP->GetYaxis()->SetTitle("1/#beta");
	TString id = outputFile;
	ProtonP->Write(id);
	PionP->Write(id);
	KaonP->Write(id);
	ProtonN->Write(id);
	PionN->Write(id);
	KaonN->Write(id);
	//Electron->Write(id);
	//Deuteron->Write(id);
	//Triton->Write(id);
	//Unknown->Write(id);
	v2Proton->V2Write(id);
	v2Pion->V2Write(id);
	v2Protondir->V2Write(id);
    v2Piondir->V2Write(id);
	//ProtonP2->V2Write(id);
	//PionP2->V2Write(id);
	v2Kaon->V2Write(id);
	v2All->V2Write(id);
//	v2All->NoJobV2Calc();
//	v2Proton->NoJobV2Calc();
	//KaonN->V2Write(id);
	//Electron->V2Write(id);
	//Triton->V2Write(id);
	
TFile *file = new TFile(outputFile,"recreate");
	centerX->Write();
	centerY->Write();
	centerZ->Write();
	N->Write();
	eta->Write();
	pt->Write();
	ptTOF->Write();
	NinTrack->Write();
	NindEdx->Write();
	EvsP->Write();
	VertexXYPosition->Write();
	VertexXZPosition->Write();
	VertexYZPosition->Write();
	mass2vsP->Write();
	betavsP->Write();
	Nmass2->Write();
	cosdeltaphi->Write();
	cosdeltaphiBIN->Write();
	cout<<outputFile<<"-> Saved"<<endl;
	phi->Write();
	dphi->Write();
	dphiBIN->Write();
	NHits_Poss->Write();
	detadphi->Write();
	//protonPSpectra->Write();
	//pionPSpectra->Write();
	//kaonPSpectra->Write();
	//protonNSpectra->Write();
	//pionNSpectra->Write();
	//kaonNSpectra->Write();
	qx->Write();
	qy->Write();
	qxy->Write();
	ReactionP->Write();
	RPdphi->Write();
	for(int i = 0; i< 4 ;i++)TofLocal[i]->Write();	
	tot->Write();	

	
	
	
	file->Close();
return kStOK;
}





