#ifndef V2Utilities_hh
#define	V2Utilities_hh

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
class TProfile2D;

	class V2Utilities {

	
	public:
		V2Utilities(char *X,float _mass);
		~V2Utilities(){;}
		static const int anabinN = 20;
		double anabin[anabinN];
		float mass;
		char *name;
		int variableID;
		void SetVID(int X);
		void  particleV2Fill(TObjArray *part);
		void  KaonV2Fill(TObjArray *K, TObjArray *pi);
		void  particleV2BINFill(TObjArray *part,double ymin1, double ymax1, double ymin2, double ymax2);
		void  MIXparticleV2BINFill(TObjArray *part,double ymin1,double ymax1,double ymin2,double ymax2,TObjArray *part1,double ymin11,double ymax11,double ymin21,double ymax21);
		void  V2Write(TString id);
		void SetBin(double max, double min);
		void SetMass(double m1, double m2);
		double mass1;
		double mass2;
		void RefParticleV2Fill(TObjArray *P,TObjArray *G, bool BINFlag,double re = 0,double pe = 0,double ge =0,double he = 0,int mult = 1);
		double rapidity(StMuTrack *track, double mass);
		void RPFill(TObjArray *all,TObjArray *poi,double eataS);
		void NoJobV2Calc();
		//TH1D *V2deltaPHI;
		//TH1D *V2cosdeltaPHI[anabinN];
		//TH1D *V2mean2[anabinN];
		//TH1D *V2sin2phi[anabinN];
		//TH1D *V2cos2phi[anabinN];
		//TH1D *WsumPOI[anabinN];
		//TH1D *Wsum2POI[anabinN];
		//TH1D *WsumREF[anabinN];
		//TH1D *Wsum2REF[anabinN];
		TH1D *V2VariableCheck[anabinN];
		//TH1D *V2VariableMult[anabinN];
		//TH1D *V2phiCheck[anabinN];
		//TH1D *V2dphiCheck[anabinN];
		//TH1D *BINV2cosdeltaPHI[anabinN];
              TH1D *BINV2mean2[anabinN];
          //      TH1D *BINV2sinphi1[anabinN];
           //     TH1D *BINV2cosphi1[anabinN];
		//TH1D *BINV2sinphi2[anabinN];
          //      TH1D *BINV2cosphi2[anabinN];
               //TH1D *BINV2VariableCheck[anabinN];
              //  TH1D *BINV2VariableMult[anabinN];
                //TH1D *BINV2phiCheck1[anabinN];
		//TH1D *BINV2phiCheck2[anabinN];
          //      TH1D *BINV2dphiCheck[anabinN];
		//TH1D *RPmPhi[anabinN];
		TH1D *mult1;
		TH1D *mult2;
		TH1D *RP_resolution;
		TH1D *BINREFEtaCheck;
		TH1D *BINPOIEtaCheck;
		TProfile2D *refFlow;
		TProfile2D *difFlow;
		TProfile2D *correctionX;
		TProfile2D *correctionY;
		TProfile2D *correctionX1;
		TProfile2D *correctionY1;
		Double_t sumCorr[240];
		TH1D *sumM1;
		TH1D *sumS11REF;
		Double_t corrX[240];
		Double_t corrY[240];
		TH1D *sum_C2;
		TH1D *sum_C22;		
        TH2D *corrPOIX;
        TH1D *corrREFX;
        TH2D *corrPOIY;
        TH1D *corrREFY;
        TH2D *sum_D2;
        TH2D *sum_D22;
        TH1D *sumREFW;
        TH1D *sumREFW2;
        TH2D *sumPOIW;
        TH2D *sumPOIW2;
		TH2D *sumPOIM2;

ClassDef(V2Utilities,1);

	};


#endif
