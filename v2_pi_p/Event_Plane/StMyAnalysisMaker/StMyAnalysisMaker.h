#ifndef StMyAnalysisMaker_h
#define StMyAnalysisMaker_h
#include "StMaker.h"

class StPicoDst;
class StPicoEvent;
class StPicoTrack;

class StPicoDstMaker;
class StMuDstMaker;
class StMuDst;
class StRefMultCorr;
class StMuTrack;

class TString;
class TH1F;
class TH2F;
class TH3F;
class TProfile;
class TProfile2D;
class TLorentzVector;
class StMyAnalysisMaker : public StMaker {
  public:
    StMyAnalysisMaker(const char *name,StMuDstMaker *MuMaker, const char *outName,char  *recfile1,char *shiftfile1,float RPO,int nHitsCut, int nDeDxCut);
    virtual ~StMyAnalysisMaker();  
    virtual Int_t            Init();
    virtual Int_t            Make();
    virtual void Clear(Option_t *opt="");
    virtual Int_t          Finish();
    
    void        DeclareHistograms();
    void          WriteHistograms();
    bool	acceptTrack(StMuTrack *track);    
  private:
    StMuDstMaker*mMuDstMaker;
    StMuDst			*mMuDst;
    Int_t                 runNumber;
    TString                mOutName;

 //---------rihan--------
 float      dMass;      

 int CurrentEvent_nKaon1s;
 float     Pi;
 float  twoPi;
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
char *shiftfile;
char *recfile;
//bool oddeven;

//---------rihan-------------
     float  CurrentEvent_Psi;
       int CurrentEvent_centrality; 
     float  CurrentEvent_vz;
     float  CurrentEvent_vy;
     float  CurrentEvent_vx;
    double         reweight;
     float               Qx;
     float               Qy;
     float       Qx_eta_pos;
     float       Qy_eta_pos;
     float       Qx_eta_neg;
     float       Qy_eta_neg;
       int        runnumber;
       int runnumberPointer;
       int directionPointer;
       int       centrality;
       int   runnumber_flag;
       int        cent_flag;
       int            nDeDx;
       int               nH;

   float           cos_part;
   float           sin_part;
   float   cos_part_etawest;
   float   sin_part_etawest;
   float   cos_part_etaeast;
   float   sin_part_etaeast;

   float             sinsum;
   float             cossum;
   float     sinsum_etaeast;
   float     cossum_etaeast;
   float     sinsum_etawest;
   float     cossum_etawest;
   float     res_weight_eta;

   float         coscorrect;
   float         sincorrect;
   float coscorrect_etawest;
   float sincorrect_etawest;
   float coscorrect_etaeast;
   float sincorrect_etaeast;
   float  dedx_He_th[12000];
  char  name[60], title[60];


  ifstream       f_dedx_th; 
  float             temp_1;
  float         VertexZPos;

  float Centrality(int mult);

 float           psi_Shift;
 float      psi_Shift_east;
 float      psi_Shift_west; 

 TH1F *EventCount;
 TH1F *CentCount;

 TH1F *VertexZ;
 TH2F *VertexXY;
 TH1F *RefMult;
 TH1F *EventP_east_rec;
 TH1F *EventP_west_rec;
 TH1F *EventPlane_east;
 TH1F *EventPlane_west;
 TH1F *recEtabinWest;
 TH1F *recEtabinEast;
 TH1F *shiftEtabinWest;
 TH1F *shiftEtabinEast;

//track loop hists:
      TH2F                *hetaphi;
      TH2F                *dEdxvsp;          
      TH2F               *dEdxvspt;        
      TH2F             *dEdxvspHe3;        
      TH2F         *dEdxvspantiHe3;  
      TH2F                  *hbeta;            
      TH2F                *hmassSq;         
      TH2F            *hmassSq_Pos;     
      TH2F            *hmassSq_Neg; 
      TH2F          *mass2ProtonsTPC;
      TH2F          *mass2ProtonsTPCex; 
      TH2F          *mass2PionsTPC;
      TH2F          *mass2PionsTPCex;  
      TH2F          *mass2ProtonsTPCeta;
      TH2F          *mass2ProtonsTPCexeta; 
      TH2F          *mass2PionsTPCeta;
      TH2F          *mass2PionsTPCexeta;          
  TProfile          *He3CosRes_eta;   
      TH3F      *He3dedxZPhiPt[10]; 
      TH3F     *He3dedxZPhiPt2[10];  
      TH3F  *antiHe3dedxZPhiPt[10];
      TH3F *antiHe3dedxZPhiPt2[10];
      TH3F       *He3gDcaPhiPt[10];     
      TH3F   *antiHe3gDcaPhiPt[10];
      TH2F   *dphiPtALL; 
      TH2F   *dphiPtProtons; 
      TH2F   *dphiPtPosPions; 
      TH2F   *dphiPtNegPions;
      TH2F   *dphiPtPions;
      TH2F   *dphiPtKaons;
      TH2F   *dphiPtPosALL;  

      TH2F   *dphimtProtons; 
      TH2F   *dphimtPosPions; 
      TH2F   *dphimtNegPions;
      TH2F   *dphimtPions;
      TH2F   *dphimtKaons;
      
      TH2F   *EPEW;            
      TH2F   *EPEWNS;             

  TProfile2D     *cosfarwest_correction;
  TProfile2D     *sinfarwest_correction;
  TProfile2D        *coswest_correction;
  TProfile2D        *sinwest_correction;
  TProfile2D        *coseast_correction;
  TProfile2D        *sineast_correction;
  TProfile2D     *cosfareast_correction;
  TProfile2D     *sinfareast_correction;
  TProfile2D    *coswest_correction_eta;
  TProfile2D    *sinwest_correction_eta;
  TProfile2D    *coseast_correction_eta;
  TProfile2D    *sineast_correction_eta;
  TProfile2D *cosfarwest_correction_eta; 
  TProfile2D *sinfarwest_correction_eta;
  TProfile2D *cosfareast_correction_eta;
  TProfile2D *sinfareast_correction_eta;

  float            FTPCshift_sinAvg[30];
  float            FTPCshift_cosAvg[30];
  float       FTPCshift_sinAvg_west[30];
  float       FTPCshift_cosAvg_west[30];
  float       FTPCshift_sinAvg_east[30];
  float       FTPCshift_cosAvg_east[30]; 
//------------------------------------


float  makeEvent(StPicoDst* stpicodst);               
       ClassDef(StMyAnalysisMaker, 1)

};

#endif
