#include "StMyShiftMaker.h"
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
#include "run.h" 
#include "bad_run.h"

ClassImp(StMyShiftMaker)


//-----------------------------------------------------------------------------
StMyShiftMaker::StMyShiftMaker(const char* name, StMuDstMaker *MuMaker, const char* outName,char *recfile1,float RPO,float eta1,float eta2,float eta3,float eta4)
  : StMaker(name)
{
  mMuDstMaker = MuMaker;
  mMuDst = 0;
  mOutName = outName;
  runNumber = -1;
  RPorder = RPO;
  recfile = recfile1;
  eta1shift = eta1;
  eta2shift = eta2;
  eta3shift = eta3;
  eta4shift = eta4;
  //
}//----------------------------------------------------
//----------------------------------------------------- 
StMyShiftMaker::~StMyShiftMaker()
{ /*  */ }
//----------------------------------------------------- 
//-----------------------------------------------------
Int_t StMyShiftMaker::Init() {
  DeclareHistograms();
  return kStOK;
}
//----------------------------------------------------- 
//-----------------------------------------------------
Int_t StMyShiftMaker::Finish() {
  if(mOutName!="") {
    TFile *fout = new TFile(mOutName.Data(),"RECREATE");
    fout->cd();
    WriteHistograms();
    fout->Close();
  }
  return kStOK;
}//-----------------------------------------------------

bool StMyShiftMaker::acceptTrack(StMuTrack *track){
  Double_t X = (Double_t)track->nHits()/track->nHitsPoss();
    if(track->nHitsDedx()> 0 && track->nHits()> 5 &&  X > 0.52 && track->flag()>0){
        return true;
      }else{
    return false;
}
//cout<<track->nHitsPoss()<<" "<<track->nHits()<<endl;
}
//-----------------------------------------------------
void StMyShiftMaker::DeclareHistograms() {

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
   weight = 1.;

        runnumber = 11105011;
 runnumberPointer = 0;
 directionPointer = 0;
       centrality = 0;
   runnumber_flag = 6;     // 
        cent_flag = 7;    

//--------v-rihan-v-------------
 EventCount = new TH1F("EventCount","EventCount",14,0,14);  //1
 CentCount  = new TH1F("CentCount","CentCount",10,0,10);    //2
   VertexZ  = new TH1F("VertexZ","VertexZ",400,-100.,100.); //4
   VertexXY = new TH2F("VertexXY","VertexXY",100,-10.,10., 100,-10.,10.);//5
   RefMult  = new TH1F("RefMult","RefMult",1500,0,1500);//6
 
 EventPlane      = new TH1F("EventPlane","EventPlane",180,0.,2*Pi/RPorder);     //10
 EventPlane_rc   = new TH1F("EventPlane_rc","EventPlane_rc",180,0.,2*Pi/RPorder);    //14
 EventPlane_east = new TH1F("EventPlane_east","EventPlane_east",180,0.,2*Pi/RPorder);//15  
 EventPlane_west = new TH1F("EventPlane_west","EventPlane_west",180,0.,2*Pi/RPorder);//16
 shiftEtabinWest = new TH1F("shiftEtabinWest","shiftEtabinWest",200,eta1shift,eta2shift);
 shiftEtabinEast = new TH1F("shiftEtabinEast","shiftEtabinEast",200,eta3shift,eta4shift);

//for recenter reading: define in header:
cosfarwest_correction = new TProfile2D("coscorrect_farwest","coscorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinfarwest_correction = new TProfile2D("sincorrect_farwest","sincorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
coswest_correction  =  new TProfile2D("coscorrect_west","coscorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinwest_correction  =  new TProfile2D("sincorrect_west","sincorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
coseast_correction  =  new TProfile2D("coscorrect_east","coscorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sineast_correction  =  new TProfile2D("sincorrect_east","sincorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
cosfareast_correction = new TProfile2D("coscorrect_fareast","coscorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinfareast_correction = new TProfile2D("sincorrect_fareast","sincorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
///////for eta sub ////////
cosfarwest_correction_eta = new TProfile2D("coscorrect_farwest_eta","coscorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinfarwest_correction_eta = new TProfile2D("sincorrect_farwest_eta","sincorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
coswest_correction_eta  =  new TProfile2D("coscorrect_west_eta","coscorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinwest_correction_eta  =  new TProfile2D("sincorrect_west_eta","sincorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
coseast_correction_eta  =  new TProfile2D("coscorrect_east_eta","coscorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sineast_correction_eta  =  new TProfile2D("sincorrect_east_eta","sincorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
cosfareast_correction_eta = new TProfile2D("coscorrect_fareast_eta","coscorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
sinfareast_correction_eta = new TProfile2D("sincorrect_fareast_eta","sincorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);

//reading from file:  absolute path
 TFile f(recfile); 
         
if(f.IsOpen())
{
  cout<<"read in : "<<f.GetName()<<endl;
    TProfile2D *temp_cos_farwest = (TProfile2D*)f.Get("mcoscorrect_farwest");
    TProfile2D *temp_sin_farwest = (TProfile2D*)f.Get("msincorrect_farwest");
       TProfile2D *temp_cos_west = (TProfile2D*)f.Get("mcoscorrect_west");
       TProfile2D *temp_sin_west = (TProfile2D*)f.Get("msincorrect_west");
       TProfile2D *temp_cos_east = (TProfile2D*)f.Get("mcoscorrect_east");
       TProfile2D *temp_sin_east = (TProfile2D*)f.Get("msincorrect_east");
    TProfile2D *temp_cos_fareast = (TProfile2D*)f.Get("mcoscorrect_fareast");
    TProfile2D *temp_sin_fareast = (TProfile2D*)f.Get("msincorrect_fareast");
    recEtabinEast                = (TH1F*)f.Get("recenterEtabinEast");
    recEtabinWest                = (TH1F*)f.Get("recenterEtabinWest");
    //get the recenter bin borders
eta1recenter = recEtabinWest->GetXaxis()->GetXmin();
eta2recenter = recEtabinWest->GetXaxis()->GetXmax();
eta3recenter = recEtabinEast->GetXaxis()->GetXmin();
eta4recenter = recEtabinEast->GetXaxis()->GetXmax();

    cosfarwest_correction->Add(temp_cos_farwest);
    sinfarwest_correction->Add(temp_sin_farwest);
       coswest_correction->Add(temp_cos_west);
       sinwest_correction->Add(temp_sin_west);
       coseast_correction->Add(temp_cos_east);
       sineast_correction->Add(temp_sin_east);
    cosfareast_correction->Add(temp_cos_fareast);
    sinfareast_correction->Add(temp_sin_fareast);

    delete temp_cos_farwest;
    delete temp_sin_farwest;
    delete temp_cos_west;
    delete temp_sin_west;
    delete temp_cos_east;
    delete temp_sin_east;
    delete temp_cos_fareast;
    delete temp_sin_fareast;
    delete recEtabinWest;
    delete recEtabinEast;

//////////////eta-sub///////////////

    TProfile2D *temp_cos_farwest_eta = (TProfile2D*)f.Get("mcoscorrect_farwest_eta");
    TProfile2D *temp_sin_farwest_eta = (TProfile2D*)f.Get("msincorrect_farwest_eta");
       TProfile2D *temp_cos_west_eta = (TProfile2D*)f.Get("mcoscorrect_west_eta");
       TProfile2D *temp_sin_west_eta = (TProfile2D*)f.Get("msincorrect_west_eta");
       TProfile2D *temp_cos_east_eta = (TProfile2D*)f.Get("mcoscorrect_east_eta");
       TProfile2D *temp_sin_east_eta = (TProfile2D*)f.Get("msincorrect_east_eta");
    TProfile2D *temp_cos_fareast_eta = (TProfile2D*)f.Get("mcoscorrect_fareast_eta");
    TProfile2D *temp_sin_fareast_eta = (TProfile2D*)f.Get("msincorrect_fareast_eta");

    cosfarwest_correction_eta->Add(temp_cos_farwest_eta);
    sinfarwest_correction_eta->Add(temp_sin_farwest_eta);
       coswest_correction_eta->Add(temp_cos_west_eta);
       sinwest_correction_eta->Add(temp_sin_west_eta);
       coseast_correction_eta->Add(temp_cos_east_eta);
       sineast_correction_eta->Add(temp_sin_east_eta);
    cosfareast_correction_eta->Add(temp_cos_fareast_eta);
    sinfareast_correction_eta->Add(temp_sin_fareast_eta);

    delete temp_cos_farwest_eta;
    delete temp_sin_farwest_eta;
    delete temp_cos_west_eta;
    delete temp_sin_west_eta;
    delete temp_cos_east_eta;
    delete temp_sin_east_eta;
    delete temp_cos_fareast_eta;
    delete temp_sin_fareast_eta;

}
  else 
   {
     cout<<"****** ERROR ******\n could not find RECENTER root file.."<<endl;
    for(int j=0;j<runnumber_flag;j++)
     {//runnumber
       for(int k=0; k<9;k++) 
       {//centrality
        cosfarwest_correction->SetBinContent(j+1,k+1, 0.);
        sinfarwest_correction->SetBinContent(j+1,k+1, 0.);
           coswest_correction->SetBinContent(j+1,k+1, 0.);
           sinwest_correction->SetBinContent(j+1,k+1, 0.);
           coseast_correction->SetBinContent(j+1,k+1, 0.);
           sineast_correction->SetBinContent(j+1,k+1, 0.);
        cosfareast_correction->SetBinContent(j+1,k+1, 0.);
        sinfareast_correction->SetBinContent(j+1,k+1, 0.);

	cosfarwest_correction_eta->SetBinContent(j+1,k+1, 0.);
	sinfarwest_correction_eta->SetBinContent(j+1,k+1, 0.);
           coswest_correction_eta->SetBinContent(j+1,k+1, 0.);
           sinwest_correction_eta->SetBinContent(j+1,k+1, 0.);
           coseast_correction_eta->SetBinContent(j+1,k+1, 0.);
           sineast_correction_eta->SetBinContent(j+1,k+1, 0.);
        cosfareast_correction_eta->SetBinContent(j+1,k+1, 0.);
        sinfareast_correction_eta->SetBinContent(j+1,k+1, 0.);
      }//centrality
    }//runnumber
 cout<<"\n Running code without recenter correction...!!!"<<endl;
}

f.Close();
 recEtabinWest = new TH1F("recenterEtabinWest","recenterEtabinWest",200,eta1recenter,eta2recenter);
 recEtabinEast = new TH1F("recenterEtabinEast","recenterEtabinEast",200,eta3recenter,eta4recenter);

//for shift generating: define in header: TO DO
     FTPCshift_sin_2 = new TProfile("FTPCshift_sin_2","FTPCshift_sin_2",20,1,21,-2.,2.);
     FTPCshift_cos_2 = new TProfile("FTPCshift_cos_2","FTPCshift_cos_2",20,1,21,-2.,2.);
FTPCshift_sin_2_west = new TProfile("FTPCshift_sin_2_west","FTPCshift_sin_2_west",20,1,21,-2.,2.);
FTPCshift_cos_2_west = new TProfile("FTPCshift_cos_2_west","FTPCshift_cos_2_west",20,1,21,-2.,2.);
FTPCshift_sin_2_east = new TProfile("FTPCshift_sin_2_east","FTPCshift_sin_2_east",20,1,21,-2.,2.);
FTPCshift_cos_2_east = new TProfile("FTPCshift_cos_2_east","FTPCshift_cos_2_east",20,1,21,-2.,2.);

}//___________________________________________________________________________
 

//-----------------------------------------------------------------------------
void StMyShiftMaker::WriteHistograms() {
//event variables:
  EventCount     ->Write();
  CentCount      ->Write();
  VertexZ        ->Write();
  VertexXY       ->Write();
  RefMult        ->Write();
  EventPlane     ->Write();
  EventPlane_rc  ->Write();
  EventPlane_east->Write();
  EventPlane_west->Write();
  shiftEtabinWest->Write();
  shiftEtabinEast->Write();
  recEtabinEast->Write();
  recEtabinWest->Write();

  FTPCshift_sin_2     ->Write();      
  FTPCshift_cos_2     ->Write();
  FTPCshift_sin_2_west->Write();
  FTPCshift_cos_2_west->Write();
  FTPCshift_sin_2_east->Write();
  FTPCshift_cos_2_east->Write();
}
//----------------------------------------------------------------------------

float StMyShiftMaker::Centrality(int mult)  //not used
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
void StMyShiftMaker::Clear(Option_t *opt) {
}

//----------------------------------------------------------------------------- 
Int_t StMyShiftMaker::Make() {//-----------------EVENT LOOP-----------------
  if(!mMuDstMaker) {
    LOG_WARN << " No MuDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mMuDst = mMuDstMaker->muDst();
  if(!mMuDst) {
    LOG_WARN << " No MuDst! Skip! " << endm;
    return kStWarn;
  }

  CurrentEvent_nKaons = 0;
  CurrentEvent_nKaon1s = 0;
/////////////////////////////////////////////////////////

    StMuEvent* mEvent= (StMuEvent*) mMuDst->event(); //load event entry

//----------------------------------------------------
    if(!mEvent)return kStOK;
    EventCount->Fill(0);
//------minbias selction-----------------------------
    //if(!(mEvent->isMinBias())) return kStOK;
    //EventCount->Fill(1);
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
   // for(int i=0; i<38; i++){
     // if(bad_run_list_39GeV[i] == mEvent->runId())   return kStOK;
    //}
    //EventCount->Fill(3);
//-----------------------------------------------
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
 TVector2 Q_tem = TVector2(-9999,9999);
 float      Qxo =   Q_tem.X(); 
 float      Qyo =   Q_tem.Y();

 if(fabs(Qxo) < 1.e-5 && fabs(Qyo) < 1.e-5) 
  return  kStOK; 
 
  EventCount->Fill(7);
//------------------------------------------------



//------------------------------------------------
    CurrentEvent_vz = VertexZPos;
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
    int cent = Centrality(eventtracksALL->GetEntries());

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

   EventCount->Fill(9);


   cos_part=0.;
   sin_part=0.;
   cos_part_etawest=0.;
   sin_part_etawest=0.;
   cos_part_etaeast=0.;
   sin_part_etaeast=0.;

   sinsum = 0;
   cossum = 0;
   sinsum_etaeast = 0;
   cossum_etaeast = 0;
   sinsum_etawest = 0;
   cossum_etawest = 0;
 
  coscorrect =0.;
  sincorrect =0.;
  coscorrect_etawest =0.;
  sincorrect_etawest =0.;
  coscorrect_etaeast =0.;
  sincorrect_etaeast =0.;

    Qx = 0.;
    Qy = 0.; //intialize for next value
    Qx_eta_pos = 0.;
    Qy_eta_pos = 0.;
    Qx_eta_neg = 0.;
    Qy_eta_neg = 0.;

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
  float      pt_w = 1.0;
        if(pt<=2.0) pt_w = pt;

	//get the recentered <cos(2phi)> and <sin(2phi)>

     if(eta > eta1recenter && eta < eta2recenter){
         coscorrect = coswest_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
         sincorrect = sinwest_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
         }

     else if(eta > eta3recenter && eta > eta4recenter ){
        coscorrect = coseast_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
        sincorrect = sineast_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
        }


     cos_part = pt_w*cos(RPorder*phi)-coscorrect; 
     sin_part = pt_w*sin(RPorder*phi)-sincorrect;

     cossum += cos_part;
     sinsum += sin_part;
/////////////////////// for etasub event plane ///////////////////////////////

    if(eta > eta1recenter && eta < eta2recenter){
       coscorrect_etawest = coswest_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       sincorrect_etawest = sinwest_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
      recEtabinWest->Fill(eta);
     }
     else if(eta > eta3recenter && eta < eta4recenter){
       coscorrect_etaeast = coseast_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       sincorrect_etaeast = sineast_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       recEtabinEast->Fill(eta);
     }

      if( eta > eta1shift && eta < eta2shift)
       {
         cos_part_etawest = pt_w*cos(RPorder*phi)-coscorrect_etawest;
         sin_part_etawest = pt_w*sin(RPorder*phi)-sincorrect_etawest;

         cossum_etawest += cos_part_etawest;
         sinsum_etawest += sin_part_etawest;
         shiftEtabinWest->Fill(eta);
       }

     else if( eta > eta3shift && eta < eta4shift)
       {
         cos_part_etaeast = pt_w*cos(RPorder*phi)-coscorrect_etaeast;
         sin_part_etaeast = pt_w*sin(RPorder*phi)-sincorrect_etaeast;

         cossum_etaeast += cos_part_etaeast;
         sinsum_etaeast += sin_part_etaeast;
         shiftEtabinEast->Fill(eta);
       }
    
}//=========================end of track loop============================
 
    Qx         =         cossum;
    Qy         =         sinsum;
    Qx_eta_pos = cossum_etawest;
    Qy_eta_pos = sinsum_etawest;
    Qx_eta_neg = cossum_etaeast;
    Qy_eta_neg = sinsum_etaeast;

//-----------------------------------------------------------------------
    EventCount->Fill(10);
    if(fabs(Qx)<1.e-5         &&         fabs(Qy)<1.e-5) return  kStOK;
    if(fabs(Qx_eta_pos)<1.e-5 && fabs(Qy_eta_pos)<1.e-5) return  kStOK;
    if(fabs(Qx_eta_neg)<1.e-5 && fabs(Qy_eta_neg)<1.e-5) return  kStOK;
    EventCount->Fill(11);



//-------------------------------------------------------------
 TVector2         Q_full(Qx, Qy);   
 float psi =      Q_full.Phi()/RPorder;
 if(psi<0) psi +=             Pi;
 EventPlane_rc ->      Fill(psi);    

 for(int n=1; n<21; n++){
    FTPCshift_sin_2->Fill(n, sin(RPorder*n*psi));
    FTPCshift_cos_2->Fill(n, cos(RPorder*n*psi));
   }

//-------------------------------------------------------------
  TVector2 Q_west(Qx_eta_pos,Qy_eta_pos);
  double psi_west =     Q_west.Phi()/RPorder;
  if(psi_west<0) psi_west +=          Pi;
  EventPlane_west ->      Fill(psi_west); 
  for(int n=1; n<21; n++){
      FTPCshift_sin_2_west->Fill(n, sin(RPorder*n*psi_west));
      FTPCshift_cos_2_west->Fill(n, cos(RPorder*n*psi_west));
  }

//-------------------------------------------------------------
  TVector2 Q_east(Qx_eta_neg,Qy_eta_neg);
  double psi_east     = Q_east.Phi()/RPorder;
  if(psi_east<0) psi_east +=          Pi;
  EventPlane_east ->      Fill(psi_east);  
  for(int n=1; n<21; n++){
      FTPCshift_sin_2_east->Fill(n, sin(RPorder*n*psi_east));  
      FTPCshift_cos_2_east->Fill(n, cos(RPorder*n*psi_east));
  }
//-------------------------------------------------------------

  //cout<<"old psi = "<<psi_old<<" new psi = "<<psi<<" psi_west = "<<psi_west<<" psi_east = "<<psi_east<<endl;

  return kStOK;


}
/////////////===============  end of the macro=========================== ////////////

