#ifndef StMyShiftMaker_h
#define StMyShiftMaker_h

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
class StMyShiftMaker : public StMaker {
  public:
    StMyShiftMaker(const char* name, StMuDstMaker *MuMaker, const char* outName,char *recfile1,float RPO,float eta1,float eta2,float eta3,float eta4);
    virtual ~StMyShiftMaker();  
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
float RPorder;
float eta1recenter;
float eta2recenter;
float eta3recenter;
float eta4recenter;
float eta1shift;
float eta2shift;
float eta3shift;
float eta4shift;
char *recfile;
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
       int cent_flag;

float   cos_part;
float   sin_part;
float   cos_part_etawest;
float   sin_part_etawest;
float   cos_part_etaeast;
float   sin_part_etaeast;

float   sinsum;
float   cossum;
float   sinsum_etaeast;
float   cossum_etaeast;
float   sinsum_etawest;
float   cossum_etawest;
 
float  coscorrect;
float  sincorrect;
float  coscorrect_etawest;
float  sincorrect_etawest;
float  coscorrect_etaeast;
float  sincorrect_etaeast;
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
TH2F *hQxy;
TH1F *EventPlane;
TH1F *hQx_rc;
TH1F *hQy_rc;
TH2F *hQxy_rc;
TH1F *EventPlane_rc;
TH1F *EventPlane_east;
TH1F *EventPlane_west;
TH1F *hbeta1;
TH1F *recEtabinWest;
TH1F *recEtabinEast;
TH1F *shiftEtabinWest;
TH1F *shiftEtabinEast;

TProfile2D *cosfarwest_correction;
TProfile2D *sinfarwest_correction;
TProfile2D *coswest_correction;
TProfile2D *sinwest_correction;
TProfile2D *coseast_correction;
TProfile2D *sineast_correction;
TProfile2D *cosfareast_correction;
TProfile2D *sinfareast_correction;
TProfile2D *cosfarwest_correction_eta; 
TProfile2D *sinfarwest_correction_eta;
TProfile2D *coswest_correction_eta;
TProfile2D *sinwest_correction_eta;
TProfile2D *coseast_correction_eta;
TProfile2D *sineast_correction_eta;
TProfile2D *cosfareast_correction_eta;
TProfile2D *sinfareast_correction_eta;

//--------^-rihan-^------------

// for shift 
  TProfile *FTPCshift_sin_2;
  TProfile *FTPCshift_cos_2;
  TProfile *FTPCshift_sin_2_west;
  TProfile *FTPCshift_cos_2_west;
  TProfile *FTPCshift_sin_2_east;
  TProfile *FTPCshift_cos_2_east;
/*
  float FTPCshift_sinAvg[30];
  float FTPCshift_cosAvg[30];
  float FTPCshift_sinAvg_west[30];
  float FTPCshift_cosAvg_west[30];
  float FTPCshift_sinAvg_east[30];
  float FTPCshift_cosAvg_east[30]; */
//------------------------------------


float  makeEvent(StMuDst* stMudst);               
       ClassDef(StMyShiftMaker, 1)

};

#endif
