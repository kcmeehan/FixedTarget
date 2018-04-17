#ifndef StMyRecenterMaker_h
#define StMyRecenterMaker_h

#include "StMaker.h"
class StMuDst;
class StMuEvent;
class StMuTrack;

class StMuDstMaker;
class StRefMultCorr;

class TString;
class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TProfile2D;
class TLorentzVector;
class StMyRecenterMaker : public StMaker {
  public:
    StMyRecenterMaker(const char *name, StMuDstMaker *MuMaker, const char *outName,float RPO,float etaA1,float etaA2,float etaA3,float etaA4);
    virtual ~StMyRecenterMaker();  
    virtual Int_t Init();
    virtual Int_t Make();
    virtual void  Clear(Option_t *opt="");
    virtual Int_t Finish();
    
    void    DeclareHistograms();
    void    WriteHistograms();
    bool    acceptTrack(StMuTrack *track);     
  private:
    StMuDstMaker *mMuDstMaker;
    StMuDst      *mMuDst;
    //StRefMultCorr* refmultCorrUtil ;
    Int_t runNumber;
    TString mOutName;

//---------rihan--------
float k1Mass;
float kMass;
float phiMass;
float He3Mass;
float TritonMass;
float dMass;      //Mass of deuteron
        int iran;
        int iran_sub;
int CurrentEvent_nKaon1s;
float Pi;
float twoPi;
float PI;
float twoPI;
float weight;
float RPOrder;
float eta1;
float eta2;
float eta3;
float eta4;
//bool oddeven;

//---------rihan-------------
     float CurrentEvent_Psi;
       int CurrentEvent_centrality; 
     float CurrentEvent_vz;
     float CurrentEvent_vy;
     float CurrentEvent_vx;
    double reweight;
     float Qx;
     float Qy;
     float Qx_eta_pos;
     float Qy_eta_pos;
     float Qx_eta_neg;
     float Qy_eta_neg;
       int runnumber ;
       int runnumberPointer;
       int directionPointer;
       int centrality ;
       int runnumber_flag ;
       int cent_flag ;

float temp_1;
float dedx_He_th[12000];
ifstream f_dedx_th;
 float VertexZPos;

    double tempArray[30][2000]; //lagbe?
       int CurrentEvent_nKaons; //lagbe?
     float Centrality(int mult);

//---------rihan-------------
TH1F *EventCount;
TH1F *CentCount;
TH1F *CentCountwt;
TH1F *VertexZ;
TH2F *VertexXY;
TH1F *RefMult;
TH1F *psiDiff1;
TH1F *hQx;
TH1F *hQy;
TH1F *refEtabinWest;
TH1F *refEtabinEast;
TH2F *hQxy;
TH1F *EventPlane;
TH1F *hbeta1;
TH2F *hetaphi;

TProfile2D *mcoscorrect_farwest;
TProfile2D *msincorrect_farwest;
TProfile2D *mcoscorrect_west;
TProfile2D *msincorrect_west;
TProfile2D *mcoscorrect_east;
TProfile2D *msincorrect_east;
TProfile2D *mcoscorrect_fareast;
TProfile2D *msincorrect_fareast;

TProfile2D *mcoscorrect_farwest_eta;
TProfile2D *msincorrect_farwest_eta;
TProfile2D *mcoscorrect_west_eta;
TProfile2D *msincorrect_west_eta;
TProfile2D *mcoscorrect_east_eta;
TProfile2D *msincorrect_east_eta;
TProfile2D *mcoscorrect_fareast_eta;
TProfile2D *msincorrect_fareast_eta;

//--------^-rihan-^------------

// for shift 
/*   TProfile *FTPCshift_sin_2;
  TProfile *FTPCshift_cos_2;
  TProfile *FTPCshift_sin_2_west;
  TProfile *FTPCshift_cos_2_west;
  TProfile *FTPCshift_sin_2_east;
  TProfile *FTPCshift_cos_2_east;
  float FTPCshift_sinAvg[30];
  float FTPCshift_cosAvg[30];
  float FTPCshift_sinAvg_west[30];
  float FTPCshift_cosAvg_west[30];
  float FTPCshift_sinAvg_east[30];
  float FTPCshift_cosAvg_east[30]; */
//------------------------------------


float  makeEvent(StMuDst* stMudst);               
       ClassDef(StMyRecenterMaker, 1)

};

#endif
