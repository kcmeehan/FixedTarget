#include "StMyRecenterMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StThreeVectorF.hh"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TVector2.h"
#include "TVector3.h"
#include "run.h" // change here
#include "bad_run.h"// change here

ClassImp(StMyRecenterMaker)

//-----------------------------------------------------------------------------
StMyRecenterMaker::StMyRecenterMaker(const char* name, StMuDstMaker *MuMaker, const char* outName, float RPO,float etaA1,float etaA2,float etaA3,float etaA4)
  : StMaker(name)
{
  mMuDstMaker = MuMaker;
  mMuDst = 0;
  mOutName = outName;
  //refmultCorrUtil = new StRefMultCorr();
  runNumber = -1;
  RPOrder = RPO;
  eta1 = etaA1;
  eta2 = etaA2;
  eta3 = etaA3;
  eta4 = etaA4;
}//----------------------------------------------------
//----------------------------------------------------- 
StMyRecenterMaker::~StMyRecenterMaker()
{ /*  */ }
//----------------------------------------------------- 
//-----------------------------------------------------
Int_t StMyRecenterMaker::Init() {
  DeclareHistograms();
  return kStOK;
}
//----------------------------------------------------- 
//-----------------------------------------------------
Int_t StMyRecenterMaker::Finish() {
  if(mOutName!="") {
    TFile *fout = new TFile(mOutName.Data(),"RECREATE");
    fout->cd();
    WriteHistograms();
    fout->Close();
  }
  return kStOK;
}//-----------------------------------------------------


bool StMyRecenterMaker::acceptTrack(StMuTrack *track){
  Double_t X = (Double_t)track->nHits()/track->nHitsPoss();
    if(track->nHitsDedx()> 0 && track->nHits()> 5 &&  X > 0.52 && track->flag()>0){
        return true;
      }else{
    return false;
}
//cout<<track->nHitsPoss()<<" "<<track->nHits()<<endl;
}

//-----------------------------------------------------
void StMyRecenterMaker::DeclareHistograms() {
     PI = 3.14159;
  twoPI = 6.28318;
 k1Mass = 0.49368;
  kMass = 0.49368;
phiMass = 1.01946;
  dMass = 1.87561;//Mass of deuteron
   iran = 0;
iran_sub = 0;
     Pi = 3.14159;
  twoPi = 6.28318;

   CurrentEvent_nKaons = 0;
   CurrentEvent_nKaon1s = 0;
   CurrentEvent_vz = 999.;
   CurrentEvent_vx = 999.;
   CurrentEvent_vy = 999.;
   Qx = 0.;
   Qy = 0.;
   weight = 1.0;

        runnumber = 0;
 runnumberPointer = 0;
 directionPointer = 0;
       centrality = 0;
   runnumber_flag = 6;     // 
        cent_flag = 7;      // 

//--------v-rihan-v-------------
 EventCount = new TH1F("EventCount","EventCount",10,0,10);  //1
 CentCount  = new TH1F("CentCount","CentCount",10,0,10);    //2
CentCountwt = new TH1F("CentCountwt","CentCountwt",10,0,10);//3
   VertexZ  = new TH1F("VertexZ","VertexZ",200,210.,212.); //4
   VertexXY = new TH2F("VertexXY","VertexXY",100,-10.,10., 100,-10.,10.);//5
   RefMult  = new TH1F("RefMult","RefMult",1500,0,1500);//6
        hQx = new TH1F("hQx","Qx",100,-50.,50.);//7
        hQy = new TH1F("hQy","Qy",100,-50.,50.);//8
       hQxy = new TH2F("hQxy","Qxy",100,-50.,50.,100,-50.,50.);//9
 EventPlane = new TH1F("EventPlane","EventPlane",180,0.,Pi);     //10
     hbeta1 = new TH1F("hbeta1","counter for particle loop",20,0.,20.);//20
    hetaphi = new TH2F("hetaphi","eta_phi_ditribution",200,-Pi,Pi,100,-1.,1.);//22
    refEtabinWest = new TH1F("recenterEtabinWest","recenterEtabinWest",200,eta1,eta2);
    refEtabinEast = new TH1F("recenterEtabinEast","recenterEtabinEast",200,eta3,eta4);

// for recenter
mcoscorrect_farwest = new TProfile2D("mcoscorrect_farwest","mcoscorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
msincorrect_farwest = new TProfile2D("msincorrect_farwest","msincorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   mcoscorrect_west = new TProfile2D("mcoscorrect_west","mcoscorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   msincorrect_west = new TProfile2D("msincorrect_west","msincorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   mcoscorrect_east = new TProfile2D("mcoscorrect_east","mcoscorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   msincorrect_east = new TProfile2D("msincorrect_east","msincorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
mcoscorrect_fareast = new TProfile2D("mcoscorrect_fareast","mcoscorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
msincorrect_fareast = new TProfile2D("msincorrect_fareast","msincorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
mcoscorrect_farwest_eta = new TProfile2D("mcoscorrect_farwest_eta","mcoscorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
msincorrect_farwest_eta = new TProfile2D("msincorrect_farwest_eta","msincorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   mcoscorrect_west_eta = new TProfile2D("mcoscorrect_west_eta","mcoscorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   msincorrect_west_eta = new TProfile2D("msincorrect_west_eta","msincorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   mcoscorrect_east_eta = new TProfile2D("mcoscorrect_east_eta","mcoscorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
   msincorrect_east_eta = new TProfile2D("msincorrect_east_eta","msincorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
mcoscorrect_fareast_eta = new TProfile2D("mcoscorrect_fareast_eta","mcoscorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
msincorrect_fareast_eta = new TProfile2D("msincorrect_fareast_eta","msincorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);

}//___________________________________________________________________________
 

//-----------------------------------------------------------------------------
void StMyRecenterMaker::WriteHistograms() {
//event variables:
  EventCount->Write();//1
   CentCount->Write();//2
     VertexZ->Write();//4
    VertexXY->Write();//5
     RefMult->Write();//6
     refEtabinEast->Write();
     refEtabinWest->Write();

//recentre writing:
mcoscorrect_farwest->Write();
msincorrect_farwest->Write();
   mcoscorrect_west->Write();
   msincorrect_west->Write();
   mcoscorrect_east->Write(); 
   msincorrect_east->Write();
mcoscorrect_fareast->Write();
msincorrect_fareast->Write();
mcoscorrect_farwest_eta->Write();
msincorrect_farwest_eta->Write();
   mcoscorrect_west_eta->Write();
   msincorrect_west_eta->Write();
   mcoscorrect_east_eta->Write();
   msincorrect_east_eta->Write();
mcoscorrect_fareast_eta->Write();
msincorrect_fareast_eta->Write();

}//----------------------------------------------------------------------------

float StMyRecenterMaker::Centrality(int mult)  //not used
{
    int central;
    //int CurrentEvent_centrality;
    float centFull[7] = {48,61,77,97,121,153,240}; 
    if      (mult>=centFull[6]) central=7;
    else if (mult>=centFull[5]) central=6;
    else if (mult>=centFull[4]) central=5;
    else if (mult>=centFull[3]) central=4;
    else if (mult>=centFull[2]) central=3;
    else if (mult>=centFull[1]) central=2;
    else if (mult>=centFull[0]) central=1;
    else central = 0;
      return central;
}


//----------------------------------------------------------------------------- 
void StMyRecenterMaker::Clear(Option_t *opt) { }



//----------------------------------------------------------------------------- 
Int_t StMyRecenterMaker::Make() {
  if(!mMuDstMaker) {
    LOG_WARN << " No MuDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mMuDst = mMuDstMaker->muDst();
  if(!mMuDst) {
    LOG_WARN << " No MuDst! Skip! " << endm;
    return kStWarn;
  }

    StMuEvent* mEvent= (StMuEvent*) mMuDst->event(); //load event entry

//----------------------------------------------------
    if(!mEvent)return kStOK;
    EventCount->Fill(0);
//------minbias selction-----------------------------
   // if(!(mEvent->isMinBias())) return kStOK;
   // EventCount->Fill(1);
//----------------------------------------------------
    Int_t maxTriggerIds = mEvent->triggerIdCollection().nominal().maxTriggerIds();
  int trigflag = 0;
        for( Int_t iTrig = 0; iTrig < maxTriggerIds; iTrig++ ){
            if(mEvent->triggerIdCollection().nominal().triggerId(iTrig) == 1) trigflag++;
  }
    if(trigflag<1)return kStOK;
    EventCount->Fill(2);
//----------------------------------------------------

// bad run rejection-----------------------------
    //for(int i=0; i<38; i++){
      //if(bad_run_list_39GeV[i] == mEvent->runId())   return kStOK;
    //}
    //EventCount->Fill(3);
//-----------------------------------------------
              //int Mult = mEvent->numberOfPrimaryTracks();
              TObjArray *eventtracksALL = new TObjArray();
    StThreeVectorF Vertex = mEvent->primaryVertexPosition();
         float VertexXPos = Vertex.x(); 
         float VertexYPos = Vertex.y(); 
         float VertexZPos = Vertex.z(); 
	      
//-----------------------------------------------
  if( (VertexZPos < 1.e-5 && VertexZPos > -1.e-5) &&       
      (VertexXPos < 1.e-5 && VertexXPos > -1.e-5) &&
      (VertexYPos < 1.e-5 && VertexYPos > -1.e-5) )  
      return kStOK;  
    EventCount->Fill(4);
//vertex cut-------------------------------------
//

    if(VertexZPos < 210. || VertexZPos > 212.)                     // Energy wise change Vz cut **
     return kStOK; 

    EventCount->Fill(5);
    //if(sqrt(pow(VertexXPos,2.)+pow(VertexYPos,2.))>=2.0)
    //return kStOK; 
    EventCount->Fill(6);
//------------------------------------------------
     TVector2 Q_tem = TVector2(-9999.,9999);
     float  Qx = Q_tem.X();
     float  Qy = Q_tem.Y();

   if(fabs(Qx) < 1.e-5 && fabs(Qy) < 1.e-5) 
   return  kStOK;  
   EventCount->Fill(7);



    CurrentEvent_vz = VertexZPos;
    int cent =0; 

    if( runNumber != mEvent->runId() ) {
      //refmultCorrUtil->init(mEvent->runId());
      runNumber = mEvent->runId();
    }

    TObjArray *tracksToAnalise = mMuDst->primaryTracks();
    TObjArrayIter GetTracks(tracksToAnalise);
    eventtracksALL->Clear();
    StMuTrack *trackA;
    while((trackA=(StMuTrack*)GetTracks.Next())){
        if(acceptTrack(trackA)){ //track cuts and QA for analysis
      eventtracksALL->Add(trackA);
      }
    }   
    cent = Centrality(eventtracksALL->GetEntries());

    //reweight = 1.0;
    //reweight = refmultCorrUtil->getWeight() ;

//-----------------------------------------------
   if(cent < 1 || cent > 6) return kStOK;
    EventCount->Fill(8);
//-----------------------------------------------

         int centrality = cent;       
CurrentEvent_centrality = centrality ;  

   CentCount->Fill(CurrentEvent_centrality);        
   VertexZ  ->             Fill(VertexZPos);                   
   VertexXY ->  Fill(VertexXPos,VertexYPos);         
   RefMult  ->  Fill(eventtracksALL->GetEntries());                       



int FLAG=0;
 if(runnumber != mEvent->runId()){
    runnumber = mEvent->runId();
    for(int i=0; i<runnumber_flag; i++){
      if(numbers[i] == runnumber) {
        runnumberPointer = i;
        FLAG++;
        break;
      }
      if((i==(runnumber_flag-1))&&(FLAG==0))
        {
          return 0;
        }
    }
  }


 unsigned short i;
int multi = eventtracksALL->GetEntries(); 

for(i = 0; i < multi; i++){//----------------------------TRACK-----------------------------------
  StMuTrack *track = (StMuTrack*) eventtracksALL->At(i); 
 	StThreeVectorF a1  = track->p();
	TVector3 mom(a1.x(),a1.y(),a1.z());
  float    pt =           mom.Perp();
  if(pt == 0)               continue;    
	int       q =      track->charge();
  if(q != +1 && q != -1)    continue;
	if(pt < 0.2)              continue;
	if(pt >  2.0)             continue;
  //if(fabs(gtrack->nSigmaProton()) > 2) continue;
  float  ddca =         track->dcaGlobal().magnitude();
	//if(fabs(ddca)>=2.0)       continue;
	float  eta  = track->eta();
  //if(fabs(eta)>1.0)         continue;
	int nHitsFit   = track->nHits();
	nHitsFit    =     fabs(nHitsFit)+1; 
	float ratio =   (float) nHitsFit  / (float) track->nHitsPoss();
  //if(ratio < 0.52)          continue; 
  //if(ratio >= 1.05)         continue;
  //if(nHitsFit < 15)         continue;
	double     phi = mom.Phi() +    Pi; // 0 to 2pi
        //---Apply pt weight------------
	float      ptw = 1.0;
        if(pt<=2.0) ptw = pt;

     if(eta > eta1 && eta < eta2){	
      mcoscorrect_west ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*cos(RPOrder*phi));
      msincorrect_west ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*sin(RPOrder*phi));
     }

      else if(eta > eta3 && eta < eta4){
      mcoscorrect_east ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*cos(RPOrder*phi));
      msincorrect_east ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*sin(RPOrder*phi));

     }

   
 
 ///////////////////// etasub //////////////////////////////
	      if(eta > eta1 && eta < eta2){
		mcoscorrect_west_eta ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*cos(RPOrder*phi));
		msincorrect_west_eta ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*sin(RPOrder*phi));
    refEtabinWest->Fill(eta);
	      }

	      else if(eta > eta3 && eta < eta4){
		mcoscorrect_east_eta ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*cos(RPOrder*phi));
		msincorrect_east_eta ->Fill(runnumberPointer,CurrentEvent_centrality,ptw*sin(RPOrder*phi));
    refEtabinEast->Fill(eta);
	      }

        }// end of track loop
 
        return kStOK;
}
/////////////  end of the macro ////////////

