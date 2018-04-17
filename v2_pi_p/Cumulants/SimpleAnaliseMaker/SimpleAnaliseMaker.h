#ifndef SimpleAnaliseMaker_hh
#define SimpleAnaliseMaker_hh

#include "StMaker.h"
#include "TString.h"
#include "FixedTargetParticle.h"
#include "V2Utilities.h"
#include "TObjArray.h"
#include "TRandom.h"

class TFile;
class StMuDstMaker;
class TH1F;
class TH2D;
class StMuEvent;
class StMuTrack;
class TCanvas;
class TRandom;
class TProfile2D;

class SimpleAnaliseMaker : public StMaker{
public:
	SimpleAnaliseMaker(StMuDstMaker *x,TString y, double max, double mins,int vid,double pTMAX , double pTMIN, double eTAMAX, double eTAMIN,int PID,double dEdxCUT1,double nHitsCUT1,double nHITPOSSCUT1 ,double FLAGCUT1,double eup1,double ed1,double eup2,double ed2,double TPcin,double TPcex,int bin);
	~SimpleAnaliseMaker(){;}
	Int_t  Init();                      
  	Int_t  Make();                      
  	Int_t  Finish(); 
	void acceptEvent();
	bool acceptTrack(StMuTrack *r);
	void SetxPositionCuts(double min,double max);
	void SetyPositionCuts(double min,double max);
	void SetzPositionCuts(double min,double max);
	void SetxyRadiousCut(double r);
	void SetnsigmaCut(double r);
	bool PIDnSigmaAccept(int particleid ,StMuTrack *track);
	float mass2(StMuTrack *track);
	float beta(StMuTrack *track);
	void Spectra(TObjArray *part , double mass ,TH1D *h1,TH1D *h2);
	void SpectraGraph(TH1D *h1);
	void reactionPlane(TObjArray *Tracks);
	void fillV2ReactionPlane(TObjArray *Tracks,TObjArray *Tracks1);
	TString outputFile;
	TFile *outputhistogramfile;
	StMuDstMaker *maker;
	double xPositionCutmin;
	double xPositionCutmax;
	double yPositionCutmin;
	double yPositionCutmax;
	double zPositionCutmin;
	double zPositionCutmax;
	double Meanqx;
	double Meanqy;
	double nsigCut;
	double exnsigCut;
	vector<bool> verticesIndex;
	double xyRadiousCut;
	double nsigmaCut;
	double rapidity(StMuTrack *track, Double_t mass, Double_t charge);
	int VID;
	int PIDflag;
	int binFLAG;
	double MultMin;
	double MultMax;
	double PTMAX;
	double PTMIN;
	double ETAMAX;
	double ETAMIN;
	double dEdxCUT;
	double nHitsCUT;
	double nHITPOSSCUT; 
	double FLAGCUT;
	double etaup1;
	double etadown1;
	double etaup2;
	double etadown2;
	TH1D *centerX;
	TH1D *centerY;
	TH1D *centerZ;
	TH1D *pt;
	TH1D *ptTOF;
	TH1D *N;
	TH1D *eta;
	TH1D *NinTrack;
	TH1D *NindEdx;
	TH2D *EvsP;
	TH2D *mass2vsP;
	TH2D *betavsP;
	TH2D *VertexXYPosition;
	TH2D *VertexXZPosition;
	TH2D *VertexYZPosition;
	TH1D *Nmass2;
	TH1D *cosdeltaphi;
	TH1D *cosdeltaphiBIN;
	TH1D *phi;
	TH1D *dphi;
	TH1D *dphiBIN;	
	TH1D *NHits_Poss;
	TH2D *detadphi;
	TObjArray *Pions;
	TObjArray *PionsP;
	TObjArray *PionsN;
	TObjArray *KaonsP;
	TObjArray *KaonsN;
	TObjArray *Protons;
	TObjArray *Kaons;
	TObjArray *deuteron;
	TObjArray *eventtracksALL;
	TObjArray *eventtracks1;
	TObjArray *eventtracks2;
	FixedTargetParticle *ProtonP;
	FixedTargetParticle *PionP;
	FixedTargetParticle *KaonP;
	FixedTargetParticle *ProtonN;
	FixedTargetParticle *PionN;
	FixedTargetParticle *KaonN;
	FixedTargetParticle *Deuteron;
	FixedTargetParticle *Triton;
	FixedTargetParticle *Electron;
	FixedTargetParticle *Helion;
	V2Utilities *v2Pion;
	V2Utilities *v2Proton;
	V2Utilities *v2Piondir;
        V2Utilities *v2Protondir;
	V2Utilities *v2Kaon;
	V2Utilities *v2All;
	TH1D *pionPSpectra;
	TH1D *protonPSpectra;
	TH1D *kaonPSpectra;
	TH1D *pionNSpectra;
	TH1D *protonNSpectra;
	TH1D *kaonNSpectra;
	TH1D *qx;
	TH1D *qy;
	TH2D *qxy;
	TH1D *ReactionP;
	TH1D *RPdphi;
	TH1D *TofLocal[4];
	TH1D *tot;


		

ClassDef(SimpleAnaliseMaker,1)
};
#endif
