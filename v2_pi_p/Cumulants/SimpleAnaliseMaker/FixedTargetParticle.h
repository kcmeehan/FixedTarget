#ifndef FixedTargetParticle_hh
#define	FixedTargetParticle_hh

#include "StMaker.h"
#include "TString.h"

class TFile;
class StMuDstMaker;
class TH1D;
class TH2D;
class TH3D;
class StMuEvent;
class StMuTrack;
class TCanvas;

class FixedTargetParticle {

	public:

		FixedTargetParticle(char* name, double mass2up, double mass2down, double mass, int charge,double nsigma = 0 ,int particleid =0);
		~FixedTargetParticle(){;}
		bool AcceptTrack(StMuTrack *track);
		bool AcceptTrackNSigma(StMuTrack *track);
		void SetNSigmaOffset(double X);
		void SetTofnSigmaCut(double Y);
		void SetTPCCuts(double a , double b);	
		double mass2up; 
		double mass2down;
		double mass;
		double nsigmaCut;
		double exnsigmaCut;
		double tofnsigmaCut;
		double nsigma;
		double nsigmaoffset;
		double rapCMS;
		int particleid;
		int Count;
		int charge;
		char *name;
		float mass2(StMuTrack *track);
		float beta(StMuTrack *track);
		bool  TofCheck(TObjArray *part);
		double rapidity(StMuTrack *track);
		double rapidityCMS(StMuTrack *track);
		void Fill(StMuTrack *track);
		void Write(TString id);
		void EndEvent();
		void FillRunID(int x);
		TH1D *P;
		TH1D *Pt;
		TH1D *mass_2;
		TH1D *nSigmaPr;
		TH1D *nSigmaPi;
		TH1D *nSigmaK;
		TH1D *NoPerEvent;
		TH1D *nSigmaE;
		TH1D *eta;
		TH1D *y;
		TH1D *ycms;
		TH1D *phi;
		TH1D *betaH;
		TH1D *QAToF;
		TH1D *QANoToF;
		TH2D *dEdxvsP;
		TH2D *dEdxvsPt;
		TH2D *betavsP;
		TH2D *etavsphi;
		TH2D *mass2vsP;
		TH2D *TofLocal[4];
		TH2D *Lvst;
		TH2D *pvsL;
		TH1D *tof;
		TH1D *PL;
		TH1D *tofmatch;
		TH1D *runID;
		TH3D *pxyz;
		//v2 cummulants

		
ClassDef(FixedTargetParticle,1);
};
#endif
