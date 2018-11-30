#include "StMyAnalysisMaker.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuBTofPidTraits.h"
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

ClassImp(StMyAnalysisMaker)

 //*changes with Energy -->
 float resolution_eta[10] = {1.0,0.147663,0.212033,0.306150,0.406854,0.487223,0.528117,0.504172,0.41804,0.317016}; //for 39 GeV

//-----------------------------------------------------
StMyAnalysisMaker::StMyAnalysisMaker(const char* name, StMuDstMaker *muMaker, const char* outName,char *recfile1,char *shiftfile1,float RPO, int _nDeDx, int _nH)
  : StMaker(name)
{
  mMuDstMaker = muMaker;
  mOutName = outName;
  runNumber = -1;
  RPorder = RPO;
  recfile = recfile1;
  shiftfile = shiftfile1;
  nDeDx = _nDeDx;
  nH = _nH;

  
}
//----------------------------------------------------- 
StMyAnalysisMaker::~StMyAnalysisMaker()
{ /*  */ }

//-----------------------------------------------------
Int_t StMyAnalysisMaker::Init() {
  DeclareHistograms();
  return kStOK;
}

//-----------------------------------------------------
Int_t StMyAnalysisMaker::Finish() {
  if(mOutName!="") {
    TFile *fout = new TFile(mOutName.Data(),"RECREATE");
    fout->cd();
    WriteHistograms();
    fout->Close();
  }
  return kStOK;
}

//-----------------------------------------------------
void StMyAnalysisMaker::DeclareHistograms() {

   dMass =  1.87561;   //Mass of deuteron in GeV
   Pi    =  3.14159;
   twoPi =   2.0*Pi;  

   CurrentEvent_vz = 999.;
   CurrentEvent_vx = 999.;
   CurrentEvent_vy = 999.;
   Qx = 0.;
   Qy = 0.;
   weight = 1.;

  runnumber        =   1;
  runnumberPointer =   0;
  directionPointer =   0;
  centrality       =   0;
  runnumber_flag   =   6;     
  cent_flag        =   7;    

//--------v-rihan-v-------------
 EventCount      = new TH1F("EventCount","Event num. Count", 14,   0,  14); 
 CentCount       = new TH1F("CentCount","Centrality Count ", 10,   0,  10);    
 VertexZ         = new TH1F("VertexZ"," VertexZ dist.(cm) ",400,210, 212); 
 VertexXY        = new TH2F("VertexXY","VertexXY", 200,-5,  5, 200, -5,5);
 RefMult         = new TH1F("RefMult"," RefMult ",1500,  0, 1500);
 EventPlane_east = new TH1F("EventPlane_east","EventPlane_east",180,0,2*Pi/RPorder);
 EventPlane_west = new TH1F("EventPlane_west","EventPlane_west",180,0,2*Pi/RPorder);
 EventP_east_rec = new TH1F("EventP_east_rec","EP_east_recentr",180,0,2*Pi/RPorder);
 EventP_west_rec = new TH1F("EventP_west_rec","EP_west_recentr",180,0,2*Pi/RPorder);
 He3CosRes_eta   = new TProfile("He3CosRes_eta","He3CosRes_eta",11,-1,10,-1.,1.); 

 
 dphimtProtons   = new TH2F("dphimtProtons","dphimtprotns",50,0,Pi/2.0,20,0.3,2.5);
 dphimtPosPions  = new TH2F("dphimtPosPion","dphimtpospion",50,0,Pi/2.0,20,0.0,2);
 dphimtNegPions  = new TH2F("dphimtNegPion","dphimtnegpion",50,0,Pi/2.0,20,0.0,2); 
 dphimtPions  = new TH2F("dphimtPion","dphimtpion",50,0,Pi/2.0,20,0.0,2);  
 dphimtKaons  = new TH2F("dphimtKaon","dphimtKaon",50,0,Pi/2.0,20,0.0,2);   

 dphiPtProtons   = new TH2F("dphiPtProtons","dphiptprotns",50,0,Pi/2.0,20,0.2,3);
 dphiPtPosPions  = new TH2F("dphiPtPosPion","dphiptpospion",50,0,Pi/2.0,20,0.1,3);
 dphiPtNegPions  = new TH2F("dphiPtNegPion","dphiptnegpion",50,0,Pi/2.0,20,0.1,3); 
 dphiPtPions  = new TH2F("dphiPtPion","dphiptpion",50,0,Pi/2.0,20,0.1,3);  
 dphiPtKaons  = new TH2F("dphiPtKaon","dphiptKaon",50,0,Pi/2.0,20,0.1,3);  
 dphiPtALL       = new TH2F("dphiPtALL","dphiPtALL",50,0,Pi/2.0,20,0.1,3);
 dphiPtPosALL    = new TH2F("dphiPtPosALL","dphiPtposALL",50,0,Pi/2.0,20,0.1,3);          


 hetaphi         = new TH2F("hetaphi","eta_phi_d", 200, -Pi,  Pi,  100,-1.,  1.);
 dEdxvsp         = new TH2F("dEdxvsp","dEdx vs p",1000, -5.,  5., 2000, 0., 50.);                    
 dEdxvspt        = new TH2F("dEdxvspt","dEdxvspt", 400,-10., 10.,  500, 0.,100.);                    
 dEdxvspHe3      = new TH2F("dEdxvspHe3","  dEdx  vs  p  He3",400, -10.,10., 500, 0., 100.);         
 dEdxvspantiHe3  = new TH2F("dEdxvspantiHe3","dEdx vs p anti",400, -10.,10., 500, 0., 100.);
 hbeta           = new TH2F("hbeta","1/beta vs  momentum", 200, 0, 10, 500, 0.0, 5.0);                            
 hmassSq         = new TH2F("hmasssSq","Mass Square vs p", 200, 0, 10, 500,-0.5, 9.5);                        
 hmassSq_Pos     = new TH2F("hmasssSq_Pos","M^2 vs p,+ve", 200, 0, 10, 500,-0.5, 9.5);    
 hmassSq_Neg     = new TH2F("hmasssSq_Neg","M^2 vs p,-ve", 200, 0, 10, 500,-0.5, 9.5); 
 EPEW            = new TH2F("EPew","EpEW",180,0,Pi,180,0,Pi);
 EPEWNS          = new TH2F("EPewNS","EPewns",180,0,Pi,180,0,Pi); 
 mass2ProtonsTPC = new TH2F("protTOFTestpt","PTprotTOFtest",300,0,5,100,0,7);  
 mass2ProtonsTPCex = new TH2F("protTOFExTestpt","PTprotTOFextest",300,0,5,100,0,7); 
 mass2PionsTPC = new TH2F("pionTOFTestpt","PTpionTOFtest",300,0,5,100,0,7);  
 mass2PionsTPCex = new TH2F("pionTOFExTestpt","PTpionTOFextest",300,0,5,100,0,7); 
 mass2ProtonsTPCeta = new TH2F("protTOFTesteta","ETAprotTOFtest",300,0,5,100,-2,0);  
 mass2ProtonsTPCexeta = new TH2F("protTOFExTesteta","ETAprotTOFextest",300,0,5,100,-2,0); 
 mass2PionsTPCeta = new TH2F("pionTOFTesteta","ETApionTOFtest",300,0,5,100,-2,0);  
 mass2PionsTPCexeta = new TH2F("pionTOFExTesteta","ETApionTOFextest",300,0,5,100,-2,0); 
                    
 for(int i=0;i<10;i++)
    {
     //--------- Z - distribution---------------
      sprintf( name,"He3dedxZPhiPt_Cen_%d",i);
      sprintf(title,"He3dedxZPhiPt_Cen_%d",i);
      He3dedxZPhiPt[i]    = new TH3F(name,title, 200, 0.,5, 5, 0.,Pi/2.0, 2000,0,200);
      He3dedxZPhiPt[i]    ->Sumw2();
      sprintf( name,"antiHe3dedxZPhiPt_Cen_%d",i);
      sprintf(title,"antiHe3dedxZPhiPt_Cen_%d",i);
      antiHe3dedxZPhiPt[i]= new TH3F(name,title, 200, 0.,5, 5, 0.,Pi/2.0, 2000,0,200);
      antiHe3dedxZPhiPt[i]->Sumw2();

      //-------- Z - without re-weight-------------------
      sprintf( name,"He3dedxZPhiPt2_Cen_%d",i);
      sprintf(title,"He3dedxZPhiPt2_Cen_%d",i);
      He3dedxZPhiPt2[i]    = new TH3F(name,title, 200, 0.,5, 5, 0.,Pi/2, 2000,0,200);
      He3dedxZPhiPt2[i]    ->Sumw2();
      sprintf( name,"antiHe3dedxZPhiPt2_Cen_%d",i);
      sprintf(title,"antiHe3dedxZPhiPt2_Cen_%d",i);
      antiHe3dedxZPhiPt2[i]= new TH3F(name,title, 200, 0.,5, 5, 0.,Pi/2.0, 2000,0,200);
      antiHe3dedxZPhiPt2[i]->Sumw2();

      //--------- dca distribution---------------
      sprintf(name,"He3gDcaPhiPt_Cen_%d",i);
      sprintf(title,"He3gDcaPhiPt_Cen_%d",i);
      He3gDcaPhiPt[i]    = new TH3F(name,title, 200, 0.,5, 5,0.,Pi/2, 200,0.,5.0);
      He3gDcaPhiPt[i]    ->Sumw2();
      sprintf(name,"antiHe3gDcaPhiPt_Cen_%d",i);
      sprintf(title,"antiHe3gDcaPhiPt_Cen_%d",i);
      antiHe3gDcaPhiPt[i]= new TH3F(name,title, 200, 0.,5, 5,0.,Pi/2, 200,0.,5.0); 
      antiHe3gDcaPhiPt[i]->Sumw2();
    }  
  


//to read recenter histograms (full event):
 cosfarwest_correction = new TProfile2D("coscorrect_farwest","coscorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinfarwest_correction = new TProfile2D("sincorrect_farwest","sincorrect_farwest",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 coswest_correction    = new TProfile2D("coscorrect_west","coscorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinwest_correction    = new TProfile2D("sincorrect_west","sincorrect_west",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 coseast_correction    = new TProfile2D("coscorrect_east","coscorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sineast_correction    = new TProfile2D("sincorrect_east","sincorrect_east",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 cosfareast_correction = new TProfile2D("coscorrect_fareast","coscorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinfareast_correction = new TProfile2D("sincorrect_fareast","sincorrect_fareast",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);

//to read recenter histograms (eta sub-event):
 cosfarwest_correction_eta = new TProfile2D("coscorrect_farwest_eta","coscorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinfarwest_correction_eta = new TProfile2D("sincorrect_farwest_eta","sincorrect_farwest_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 coswest_correction_eta    = new TProfile2D("coscorrect_west_eta","coscorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinwest_correction_eta    = new TProfile2D("sincorrect_west_eta","sincorrect_west_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 coseast_correction_eta    = new TProfile2D("coscorrect_east_eta","coscorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sineast_correction_eta    = new TProfile2D("sincorrect_east_eta","sincorrect_east_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 cosfareast_correction_eta = new TProfile2D("coscorrect_fareast_eta","coscorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);
 sinfareast_correction_eta = new TProfile2D("sincorrect_fareast_eta","sincorrect_fareast_eta",runnumber_flag,0,runnumber_flag,cent_flag,0,cent_flag);





//reading root file containing recenter histograms:
     TFile f(recfile);  //<----------- provide absolute path

if(f.IsOpen())
{
  cout<<"Success read: "<<f.GetName()<<endl;

    TProfile2D *temp_cos_farwest_eta = (TProfile2D*)f.Get("mcoscorrect_farwest_eta");
    TProfile2D *temp_sin_farwest_eta = (TProfile2D*)f.Get("msincorrect_farwest_eta");
    TProfile2D *temp_cos_west_eta    = (TProfile2D*)   f.Get("mcoscorrect_west_eta");
    TProfile2D *temp_sin_west_eta    = (TProfile2D*)   f.Get("msincorrect_west_eta");
    TProfile2D *temp_cos_east_eta    = (TProfile2D*)   f.Get("mcoscorrect_east_eta");
    TProfile2D *temp_sin_east_eta    = (TProfile2D*)   f.Get("msincorrect_east_eta");
    TProfile2D *temp_cos_fareast_eta = (TProfile2D*)f.Get("mcoscorrect_fareast_eta");
    TProfile2D *temp_sin_fareast_eta = (TProfile2D*)f.Get("msincorrect_fareast_eta");
    recEtabinEast                = (TH1F*)f.Get("recenterEtabinEast");
    recEtabinWest                = (TH1F*)f.Get("recenterEtabinWest");
    //get the recenter bin borders
    eta1recenter = recEtabinWest->GetXaxis()->GetXmin();
    eta2recenter = recEtabinWest->GetXaxis()->GetXmax();
    eta3recenter = recEtabinEast->GetXaxis()->GetXmin();
    eta4recenter = recEtabinEast->GetXaxis()->GetXmax();

    cosfarwest_correction_eta->Add(temp_cos_farwest_eta);
    sinfarwest_correction_eta->Add(temp_sin_farwest_eta);
    coswest_correction_eta   ->   Add(temp_cos_west_eta);
    sinwest_correction_eta   ->   Add(temp_sin_west_eta);
    coseast_correction_eta   ->   Add(temp_cos_east_eta);
    sineast_correction_eta   ->   Add(temp_sin_east_eta);
    cosfareast_correction_eta->Add(temp_cos_fareast_eta);
    sinfareast_correction_eta->Add(temp_sin_fareast_eta);

    delete temp_cos_farwest_eta;
    delete temp_sin_farwest_eta;
    delete    temp_cos_west_eta;
    delete    temp_sin_west_eta;
    delete    temp_cos_east_eta;
    delete    temp_sin_east_eta;
    delete temp_cos_fareast_eta;
    delete temp_sin_fareast_eta;
    delete recEtabinEast;
    delete recEtabinWest;
}

  else 
   {
    cout<<" *** Warning: No recenter correction, file not found ***"<<endl;
    for(int j=0;j<runnumber_flag;j++)
     {//runnumber loop
       for(int k=0; k<9;k++) 
       {//centrality loop
        cosfarwest_correction->SetBinContent(j+1,k+1, 0.);
        sinfarwest_correction->SetBinContent(j+1,k+1, 0.);
        coswest_correction   ->SetBinContent(j+1,k+1, 0.);
        sinwest_correction   ->SetBinContent(j+1,k+1, 0.);
        coseast_correction   ->SetBinContent(j+1,k+1, 0.);
        sineast_correction   ->SetBinContent(j+1,k+1, 0.);
        cosfareast_correction->SetBinContent(j+1,k+1, 0.);
        sinfareast_correction->SetBinContent(j+1,k+1, 0.);

	cosfarwest_correction_eta->SetBinContent(j+1,k+1, 0.);
	sinfarwest_correction_eta->SetBinContent(j+1,k+1, 0.);
        coswest_correction_eta   ->SetBinContent(j+1,k+1, 0.);
        sinwest_correction_eta   ->SetBinContent(j+1,k+1, 0.);
        coseast_correction_eta   ->SetBinContent(j+1,k+1, 0.);
        sineast_correction_eta   ->SetBinContent(j+1,k+1, 0.);
        cosfareast_correction_eta->SetBinContent(j+1,k+1, 0.);
        sinfareast_correction_eta->SetBinContent(j+1,k+1, 0.);
      }
    }
  }

f.Close();

 // Read Shift correction histograms:
 TFile *fin1 = new TFile(shiftfile);  //<----------- provide absolute path

 for(int i=0; i<20; i++){ //initialize arrays
   FTPCshift_sinAvg_west[i] = 999; FTPCshift_cosAvg_west[i] = 999;
   FTPCshift_sinAvg_east[i] = 999; FTPCshift_cosAvg_east[i] = 999;
 }

if(fin1->IsOpen()) {
  cout<<" Success read: "<<fin1->GetName()<<endl;
 TProfile *FTPCshift_sin_west = (TProfile*)fin1->Get("FTPCshift_sin_2_west");
 TProfile *FTPCshift_cos_west = (TProfile*)fin1->Get("FTPCshift_cos_2_west");
 TProfile *FTPCshift_sin_east = (TProfile*)fin1->Get("FTPCshift_sin_2_east");
 TProfile *FTPCshift_cos_east = (TProfile*)fin1->Get("FTPCshift_cos_2_east");

 for(int i=0; i<20; i++){ //fill arrays
     FTPCshift_sinAvg_east[i] = FTPCshift_sin_east->GetBinContent(i+1);
     FTPCshift_cosAvg_east[i] = FTPCshift_cos_east->GetBinContent(i+1);
     cout<<"FTPCshift_sinAvg_east["<<i<<"] = "<<FTPCshift_sinAvg_east[i]<< "\t FTPCshift_cosAvg_east["<<i<<"] = "<< FTPCshift_cosAvg_east[i]<<endl;
   }

 for(int i=0; i<20; i++){
     FTPCshift_sinAvg_west[i] = FTPCshift_sin_west->GetBinContent(i+1);
     FTPCshift_cosAvg_west[i] = FTPCshift_cos_west->GetBinContent(i+1);
     cout<<"FTPCshift_sinAvg_west["<<i<<"] = "<<FTPCshift_sinAvg_west[i]<< "\t FTPCshift_cosAvg_west["<<i<<"] = "<< FTPCshift_cosAvg_west[i]<<endl;
   }
    shiftEtabinEast                = (TH1F*)fin1->Get("shiftEtabinEast");
    shiftEtabinWest                = (TH1F*)fin1->Get("shiftEtabinWest");
    //get the recenter bin borders
eta1shift = shiftEtabinWest->GetXaxis()->GetXmin();
eta2shift = shiftEtabinWest->GetXaxis()->GetXmax();
eta3shift = shiftEtabinEast->GetXaxis()->GetXmin();
eta4shift = shiftEtabinEast->GetXaxis()->GetXmax();

  delete FTPCshift_sin_west;
  delete FTPCshift_cos_west;
  delete FTPCshift_sin_east;
  delete FTPCshift_cos_east;
  delete shiftEtabinEast;
  delete shiftEtabinWest;
 }



 fin1->Close();

//Get the theoritical dEdx value (in KeV/cm) for He3 from the file.
f_dedx_th.open("/star/u/lukkoz/offline/paper/psn0623/StRoot/bichsel/dedx_mean_Deuteron_dx2cm.dat");  //<----------- provide absolute path

 if(!f_dedx_th){ 
  cout<<"\n ****WARNING****\n could not read theoritical dedx value\n\n"<<endl; 
  }

//filling dE/dx theory values in an array:
   if(f_dedx_th){
    for(int ik=0;ik<11901;ik++)
     {
      f_dedx_th>>temp_1>>dedx_He_th[ik];            
     }                                                                                                                                                      
   }
   f_dedx_th.close();


   cout<<eta1recenter<<" "<<eta2recenter<<" "<<eta3recenter<<" "<<eta4recenter<<" "<<endl;
   cout<<eta1shift<<" "<<eta2shift<<" "<<eta3shift<<" "<<eta4shift<<endl;    
    recEtabinWest = new TH1F("recenterEtabinWest","recenterEtabinWest",200,eta1recenter,eta2recenter);
    recEtabinEast = new TH1F("recenterEtabinEast","recenterEtabinEast",200,eta3recenter,eta4recenter);
    shiftEtabinWest = new TH1F("shiftEtabinWest","shiftEtabinWest",200,eta1shift,eta2shift);
    shiftEtabinEast = new TH1F("shiftEtabinEast","shiftEtabinEast",200,eta3shift,eta4shift);
}
 

//-----------------------------------------------------------------------------
void StMyAnalysisMaker::WriteHistograms() {
//event variables:
  EventCount     ->Write();
  CentCount      ->Write();
  VertexZ        ->Write();
  VertexXY       ->Write();
  RefMult        ->Write();
  EventP_east_rec->Write();
  EventP_west_rec->Write();
  EventPlane_east->Write();
  EventPlane_west->Write();
  recEtabinEast->Write();
  recEtabinWest->Write();
  shiftEtabinEast->Write();
  shiftEtabinWest->Write();
//track variables:
  dEdxvsp        ->Write();
  dEdxvspt       ->Write();   
  dEdxvspHe3     ->Write();    
  dEdxvspantiHe3 ->Write();    
  hbeta          ->Write();     
  hetaphi        ->Write(); 
  hmassSq        ->Write();      
  hmassSq_Pos    ->Write();       
  hmassSq_Neg    ->Write();        
  He3CosRes_eta  ->Write();
   
  dphiPtALL      ->Write(); 
  dphiPtProtons  ->Write(); 
  dphiPtPosPions ->Write(); 
  dphiPtNegPions ->Write();
  dphiPtPions ->Write();
  dphiPtKaons ->Write();
  dphiPtPosALL   ->Write(); 

  dphimtProtons  ->Write(); 
  dphimtPosPions ->Write(); 
  dphimtNegPions ->Write();
  dphimtPions ->Write();
  dphimtKaons ->Write(); 

  EPEW           ->Write();
  EPEWNS         ->Write();
  mass2ProtonsTPC->Write();
  mass2ProtonsTPCex->Write();

  mass2PionsTPC->Write();
  mass2PionsTPCex->Write();

  mass2ProtonsTPCeta->Write();
  mass2ProtonsTPCexeta->Write();

  mass2PionsTPCeta->Write();
  mass2PionsTPCexeta->Write();

  /*for(int i=0;i<10;i++)
  He3dedxZPhiPt[i]     ->Write();
  for(int i=0;i<10;i++)
  antiHe3dedxZPhiPt[i] ->Write();      
  for(int i=0;i<10;i++)
  He3dedxZPhiPt2[i]    ->Write();
  for(int i=0;i<10;i++)
  antiHe3dedxZPhiPt2[i]->Write();  
  for(int i=0;i<10;i++)    
  He3gDcaPhiPt[i]      ->Write();
  for(int i=0;i<10;i++)
  antiHe3gDcaPhiPt[i]  ->Write();
  */
}//----------------------------------------------------------------------------

bool StMyAnalysisMaker::acceptTrack(StMuTrack *track){
  Double_t X = (Double_t)track->nHits()/track->nHitsPoss();
    if(track->nHitsDedx()> 0 && track->nHits()> 5 &&  X > 0.52 && track->flag()>0){
        return true;
      }else{
    return false;
}
//cout<<track->nHitsPoss()<<" "<<track->nHits()<<endl;
}

float StMyAnalysisMaker::Centrality(int mult)
{ //-----  This function is not in use -------
     int central;
    float centFull[7] = {48,61,77,97,121,153,240}; 
    if      (mult>=centFull[6]) central=7; //0-5%
    else if (mult>=centFull[5]) central=6; //5-10%
    else if (mult>=centFull[4]) central=5; //10-15%
    else if (mult>=centFull[3]) central=4; //15-20%
    else if (mult>=centFull[2]) central=3; //20-25%
    else if (mult>=centFull[1]) central=2; //25-30%
    else if (mult>=centFull[0]) central=1; // > 30%

      return central;
}


void StMyAnalysisMaker::Clear(Option_t *opt) { }


//-----------------EVENT LOOP---------------------
Int_t StMyAnalysisMaker::Make() {
   if(!mMuDstMaker) {
    LOG_WARN << " No MuDstMaker! Skip! " << endm;
    return kStWarn;
  }

  mMuDst = mMuDstMaker->muDst();
  if(!mMuDst) {
    LOG_WARN << " No MuDst! Skip! " << endm;
    return kStWarn;
  }

 //CurrentEvent_nKaons = 0;
 //CurrentEvent_nKaon1s = 0;
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

  int cent;
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
    cent = Centrality(eventtracksALL->GetEntries());

    reweight = 1.0;
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

   EventCount   ->Fill(9);
   coscorrect         = 0;
   sincorrect         = 0;
   cos_part           = 0;
   sin_part           = 0;
   cossum             = 0;
   sinsum             = 0;
   cos_part_etawest   = 0;
   sin_part_etawest   = 0;
   cos_part_etaeast   = 0;
   sin_part_etaeast   = 0;
   sinsum_etaeast     = 0;
   cossum_etaeast     = 0;
   sinsum_etawest     = 0;
   cossum_etawest     = 0;
   coscorrect_etawest = 0;
   sincorrect_etawest = 0;
   coscorrect_etaeast = 0;
   sincorrect_etaeast = 0;
   Qx                 = 0;
   Qy                 = 0; 
   Qx_eta_pos         = 0;
   Qy_eta_pos         = 0;
   Qx_eta_neg         = 0;
   Qy_eta_neg         = 0;

//---------------Track loop for Event plane ----------------------
   unsigned short i;
 int multi = eventtracksALL->GetEntries(); 
 cout<<"EP"<<endl;

for(i = 0; i < multi; i++){//----------------------------TRACK-----------------------------------
   StMuTrack *track = (StMuTrack*) eventtracksALL->At(i); 
  StThreeVectorF a1  = track->p();
  TVector3 mom(a1.x(),a1.y(),a1.z());
  float pt =           mom.Perp();
  if(pt == 0)               continue;    
  int q =      track->charge();
  if(q != +1 && q != -1)    continue;
  if(pt < 0.2)              continue;
  if(pt >  2.0)             continue;
  float  ddca = track->dcaGlobal().magnitude();
  //if(fabs(ddca)>=2.0)       continue;
  float  eta  = track->eta();
  //if(fabs(eta)>1.0)         continue;
  int nHitsFit = track->nHits();
  nHitsFit     = fabs(nHitsFit)+1; 
  float ratio  = (float) nHitsFit  / (float) track->nHitsPoss();
  //if(ratio < 0.52)          continue; 
  //if(ratio >= 1.05)         continue;
  //if(nHitsFit < 15)         continue;
  double     phi = mom.Phi() +    Pi; // 0 to 2pi
        //---Apply pt weight------------
	float   pt_w = 1.0;
        if(pt<=2.0) pt_w =  pt; 


        if(eta > eta1recenter && eta < eta2recenter){
         coscorrect = coswest_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
         sincorrect = sinwest_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
         }
        else if(eta >  eta3recenter && eta < eta4recenter){
        coscorrect = coseast_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
        sincorrect = sineast_correction->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
        }

        cos_part = pt_w*cos(RPorder*phi)-coscorrect; 
        sin_part = pt_w*sin(RPorder*phi)-sincorrect;
        cossum  +=                    cos_part; 
        sinsum  +=                    sin_part; 

       //------------ eta sub-event plane --------------
       if(eta > eta1recenter && eta < eta2recenter){
       coscorrect_etawest = coswest_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       sincorrect_etawest = sinwest_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       recEtabinWest->Fill(eta);
       }
       else if(eta >  eta3recenter && eta < eta4recenter){
       coscorrect_etaeast = coseast_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       sincorrect_etaeast = sineast_correction_eta->GetBinContent(runnumberPointer+1,CurrentEvent_centrality+1);
       recEtabinEast->Fill(eta);
       }
       

      if( eta > eta1shift && eta < eta2shift){
         cos_part_etawest = pt_w*cos(RPorder*phi)-coscorrect_etawest;
         sin_part_etawest = pt_w*sin(RPorder*phi)-sincorrect_etawest;
         cossum_etawest += cos_part_etawest;
         sinsum_etawest += sin_part_etawest;
         shiftEtabinWest->Fill(eta);
       }
     if( eta > eta3shift && eta < eta4shift){
         cos_part_etaeast = pt_w*cos(RPorder*phi)-coscorrect_etaeast;
         sin_part_etaeast = pt_w*sin(RPorder*phi)-sincorrect_etaeast;
         cossum_etaeast += cos_part_etaeast;
         sinsum_etaeast += sin_part_etaeast;
         shiftEtabinEast->Fill(eta);
       }
    
}//------------------track loop for EVENT PLANE Ends---------------------------

    Qx         =         cossum;              
    Qy         =         sinsum;              
    Qx_eta_pos = cossum_etawest;
    Qy_eta_pos = sinsum_etawest;
    Qx_eta_neg = cossum_etaeast;
    Qy_eta_neg = sinsum_etaeast;
    EventCount ->      Fill(10);
//-----------------------------------------------------------------------

     if(fabs(Qx)        < 1.e-5 && fabs(Qy)        < 1.e-5)
     return         kStOK;
     if(fabs(Qx_eta_pos)< 1.e-5 && fabs(Qy_eta_pos)< 1.e-5)
     return         kStOK;
     if(fabs(Qx_eta_neg)< 1.e-5 && fabs(Qy_eta_neg)< 1.e-5)
     return         kStOK;
     EventCount->Fill(11);

cout<<"shift corr"<<endl;
//------------ --apply shift correction-------------------
     TVector2   Q_new_neg(Qx_eta_neg,Qy_eta_neg);     
     float  psi_east       = Q_new_neg.Phi()/RPorder;
     if(psi_east<0.)              psi_east  += (3.-RPorder)*Pi;  
     if(psi_east>=(3.-RPorder)*Pi) psi_east -= (3.-RPorder)*Pi;
     EventP_east_rec       ->     Fill(psi_east);  
     float psi_Shift_f_east =                  0;
     psi_Shift_east         =                  0; 
     for(int n=1; n<21; n++)                    {
     psi_Shift_f_east += ((3.-RPorder)/(1.0*n))*(-FTPCshift_sinAvg_east[n-1]*cos(RPorder*n*psi_east) + FTPCshift_cosAvg_east[n-1]*sin(RPorder*n*psi_east));
     }
     psi_Shift_east = psi_east + psi_Shift_f_east;
     if(psi_Shift_east<0.)                psi_Shift_east += (3.-RPorder)*Pi;
     if(psi_Shift_east>(3.-RPorder)*Pi)   psi_Shift_east -= (3.-RPorder)*Pi;
     EventPlane_east     ->  Fill(psi_Shift_east);       //<--- psi_2 east
//--------------------------------------------------------
     TVector2    Q_new_pos(Qx_eta_pos,Qy_eta_pos);
     float         psi_west = Q_new_pos.Phi()/RPorder;
     if(psi_west<0.)               psi_west += (3.-RPorder)*Pi;  
     if(psi_west>=(3.-RPorder)*Pi)  psi_west -= (3.-RPorder)*Pi;
     EventP_west_rec        ->     Fill(psi_west);  
     float psi_Shift_f_west =                   0;
     psi_Shift_west         =                   0;    
     for(int n=1; n<21; n++)                     {
     psi_Shift_f_west += ((3.-RPorder)/(1.0*n))*(-FTPCshift_sinAvg_west[n-1]*cos(RPorder*n*psi_west) + FTPCshift_cosAvg_west[n-1]*sin(RPorder*n*psi_west));
     }
     psi_Shift_west = psi_west + psi_Shift_f_west;
     if(psi_Shift_west<0.)                psi_Shift_west += (3.-RPorder)*Pi;
     if(psi_Shift_west>(3.-RPorder)*Pi)   psi_Shift_west -= (3.-RPorder)*Pi;
     EventPlane_west  ->     Fill(psi_Shift_west);       //<--- psi_2 west
//------------------------------------------------------

      He3CosRes_eta->Fill(CurrentEvent_centrality,cos(2.0*(psi_Shift_west-psi_Shift_east)));
      He3CosRes_eta->Fill(-1.0, cos(2.0*(psi_Shift_west-psi_Shift_east)));
      weight       =      reweight*res_weight_eta;
      EPEW->Fill(psi_Shift_west,psi_Shift_east);
      EPEWNS->Fill(psi_west,psi_east);



cout<<"dphi"<<endl;
//------- Track Loop for v2 analysis :-----------------
    for(i = 0; i < multi; i++){
      StMuTrack* gtrack = (StMuTrack*) mMuDst->primaryTracks(i); 
 	    StThreeVectorF a3   =   gtrack->p();   
	    TVector3  mom3(a3.x(), a3.y(), a3.z());
        float  pt  =               mom3.Perp();
  if(pt==0)                     continue;                
	int     q  =          gtrack->charge();
  if(q != +1 && q != -1)        continue;
	if(pt < 0.1)                 continue;
	if(pt > 3.0)                 continue;       
  float gdca =             gtrack->dca().magnitude();
	//if(fabs(gdca)>3.0)            continue; 
	float eta    =   gtrack->eta();
  //if(fabs(eta) >1.0)            continue;     
	float nHitsFit  =   gtrack->nHits();
	nHitsFit        =     fabs(nHitsFit)+1;   
  int  nHitsdEdx  =  gtrack->nHitsDedx();
  float     dedx  =      1000000*gtrack->dEdx();
	float    ratio  = (float)   nHitsFit / (float) gtrack->nHitsPoss();
        if(nHitsFit < nH )            continue; 
        if(ratio <= 0.52)             continue;
        if(nHitsdEdx < nDeDx)         continue;
  //      if(dedx<= 1.e-10)             continue; 
	//if(nHitsFit<25||nHitsFit>50)  continue;  
        float Beta      =                -999.;
        Beta            =   gtrack->btofPidTraits().beta();
        float p         =           mom3.Mag();    
        float m1        =                -999.;
  if(Beta>0.)                           {
	hbeta           ->     Fill(p,1./Beta); 
        m1          =  p*p*(1./(Beta*Beta)-1.); 
	if(fabs(gdca)<1.0)                    {
        hmassSq         ->          Fill(p,m1);   
        if(q>0)  hmassSq_Pos->      Fill(p,m1);
        if(q<0)  hmassSq_Neg->      Fill(p,m1); 
        }
	}
	//-------- calc. Z variable------------
        int indx      = int((p-0.1)/0.001+0.5);
        if(indx<0)                indx =     0;
        if(indx>11900)            indx = 11900;
        double dedxZ_He3 = TMath::Log(dedx/dedx_He_th[indx]);
	     if(fabs(gdca)<1.0)                    {
        dEdxvsp         ->     Fill(p*q, dedx);
        dEdxvspt        ->     Fill(pt*q,dedx);   
	      hetaphi         ->Fill(mom3.Phi(),eta);
	}
	//------- Fill Z, phi-psi2, pT---------
      //  if(fabs(dedxZ_He3) < 1.0)             {
        float Current_He3Px     =     mom3.X();
        float Current_He3Py     =     mom3.Y();
        float Current_He3Pz     =     mom3.Z();
        float dedxZHe3          =    dedxZ_He3;
        int   Current_He3Charge =            q;
        TLorentzVector        pnHe3LV(0,0,0,0);
        pnHe3LV.SetXYZM(Current_He3Px,Current_He3Py,Current_He3Pz,dMass);
        if(eta >  eta3shift && eta < eta4shift) psi_Shift = psi_Shift_west;
        if(eta >  eta1shift && eta < eta2shift) psi_Shift = psi_Shift_east;
        float dphi   = pnHe3LV.Phi()-psi_Shift;    
        if(dphi<0)               dphi += twoPi;
        if(dphi>=Pi)      dphi  = twoPi - dphi;
        if(dphi>(Pi/2.0)) dphi  =    Pi - dphi;     
	//------------ ToF cut-----------------
       /* if(pt>0.6)                            {
        if(m1 < 2.81 || m1 > 4.22)    continue;   
        }
        if(pt<=0.6 && Beta>0.0)               {
        if (m1 < 2.81 || m1 > 4.22)   continue;  
        }

	*/    
        bool tofflag = (gtrack->btofPidTraits().matchFlag() > 0) ? true : false;
        float rapidityLeft = -2.0;
        float rapidityRight = -1.0;
        dphiPtALL->Fill(dphi,pnHe3LV.Pt());

        if(tofflag && fabs(gtrack->nSigmaProton()) < 2){
         mass2ProtonsTPC->Fill(m1,gtrack->pt());
         mass2ProtonsTPCeta->Fill(m1,gtrack->eta());
         if(fabs(gtrack->nSigmaPion()) > 1){
          mass2ProtonsTPCex->Fill(m1,gtrack->pt());
          mass2ProtonsTPCeta->Fill(m1,gtrack->eta());
         }

     }

        if(tofflag && fabs(gtrack->nSigmaPion()) < 2){
         mass2PionsTPC->Fill(m1,gtrack->pt());
         mass2PionsTPCeta->Fill(m1,gtrack->eta());
         if(fabs(gtrack->nSigmaProton()) > 1){
          mass2PionsTPCex->Fill(m1,gtrack->pt());
          mass2PionsTPCexeta->Fill(m1,gtrack->eta());

        }
       }

        if(q > 0) dphiPtPosALL->Fill(dphi,pnHe3LV.Pt());

        if(q > 0 && ((fabs(gtrack->nSigmaProton()) < 2 ) && ((m1 > 0.6 && m1 < 1.1) || !tofflag))){
        float mass = 0.938;
        float charge = 1;
        Double_t E = sqrt(mass*mass + fabs(charge*charge)*gtrack->p().magnitude()*gtrack->p().magnitude());
        Double_t rapidity = 0.5*log((E+fabs(charge)*gtrack->p().z())/(E-fabs(charge)*gtrack->p().z()));
        if(rapidity > rapidityLeft && rapidity < rapidityRight){
         dphiPtProtons->Fill(dphi,pnHe3LV.Pt());
         dphimtProtons->Fill(dphi,(sqrt(pow(E,2) - pow(gtrack->p().z(),2)) - mass));
        }
       }
        if(q > 0 && (( fabs(gtrack->nSigmaPion()) < 2  && (fabs(gtrack->nSigmaProton()) > 1 || tofflag )) && ((m1 > 0.0 && m1 <0.1) || !tofflag))){
        float mass = 0.1395;
        float charge = 1;
        Double_t E = sqrt(mass*mass + fabs(charge*charge)*gtrack->p().magnitude()*gtrack->p().magnitude());
        Double_t rapidity = 0.5*log((E+fabs(charge)*gtrack->p().z())/(E-fabs(charge)*gtrack->p().z()));
        if(rapidity > rapidityLeft && rapidity < rapidityRight){

         dphiPtPosPions->Fill(dphi,pnHe3LV.Pt());
         dphimtPosPions->Fill(dphi,(sqrt(pow(E,2) - pow(gtrack->p().z(),2)) - mass));
        }
       }
        if(q < 0 && ((fabs(gtrack->nSigmaPion()) < 2 && ((m1 > 0.0 && m1 < 0.1) || !tofflag)))){
        float mass = 0.1395;
        float charge = 1;
        Double_t E = sqrt(mass*mass + fabs(charge*charge)*gtrack->p().magnitude()*gtrack->p().magnitude());
        Double_t rapidity = 0.5*log((E+fabs(charge)*gtrack->p().z())/(E-fabs(charge)*gtrack->p().z()));
        if(rapidity > rapidityLeft && rapidity < rapidityRight){

         dphiPtNegPions->Fill(dphi,pnHe3LV.Pt());
         dphimtNegPions->Fill(dphi,(sqrt(pow(E,2) - pow(gtrack->p().z(),2)) - mass));
          }
        }
        if((fabs(gtrack->nSigmaPion()) < 2 && (fabs(gtrack->nSigmaProton()) > 1) || tofflag || q > 0) && ((m1 > 0.0 && m1 < 0.1) || !tofflag)){
        float mass = 0.1395;
        float charge = 1;
        Double_t E = sqrt(mass*mass + fabs(charge*charge)*gtrack->p().magnitude()*gtrack->p().magnitude());
        Double_t rapidity = 0.5*log((E+fabs(charge)*gtrack->p().z())/(E-fabs(charge)*gtrack->p().z()));
        if(rapidity > rapidityLeft && rapidity < rapidityRight){
          dphiPtPions->Fill(dphi,pnHe3LV.Pt());
          dphimtPions->Fill(dphi,(sqrt(pow(E,2) - pow(gtrack->p().z(),2)) - mass));
          }
        }
        if((fabs(gtrack->nSigmaKaon()) < 3 && (fabs(gtrack->nSigmaPion()) > 2 && fabs(gtrack->nSigmaProton()) > 2) || tofflag) || ((m1 > 0.3 && m1 <0.4) || !tofflag)){
        float mass = 0.49;
        float charge = 1;
        Double_t E = sqrt(mass*mass + fabs(charge*charge)*gtrack->p().magnitude()*gtrack->p().magnitude());
        Double_t rapidity = 0.5*log((E+fabs(charge)*gtrack->p().z())/(E-fabs(charge)*gtrack->p().z()));
        if(rapidity > rapidityLeft && rapidity < rapidityRight){
         dphiPtKaons->Fill(dphi,pnHe3LV.Pt());
         dphimtKaons->Fill(dphi,(sqrt(pow(E,2) - pow(gtrack->p().z(),2)) - mass));
          }
        }
      
    }//------------- 2nd Track Loop ENDS--------------- 

  return kStOK;
 }


