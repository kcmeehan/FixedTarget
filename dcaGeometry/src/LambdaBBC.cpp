#define PicoDst_cxx
#include "stdio.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "PicoDst.h"
#include <TF1.h>
#include <TH2.h>
#include <TH3.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>
#include "StDcaGeometry.h"
#include "StRefMultCorr.h"
#include "CentralityMaker.h"
#include <map>
std::map<short, bool> vis;


// ******************************* declaration of pointers to histograms ******************************
TH1I *hEventCounter;
TH1I *hIndexToEvent;
TH1I *hNlambdaPerEvent;
TH1I *hBufferPointer;
TH1I *hVertexIndex;
TH1I *hNtrkA;
TH1I *hNtrkB;
TH1I *hNtrk1;
TH1I *hNtrk2;
TH1I *hNtrk3;
TH2I *hBBCadc;
TH2D *hHitE;

TH1D *hVertexZ;
TH1D *hNhitsFit;
TH1D *hRatio;
TH1D *hMom;
TH1D *hPriMom;
TH1D *hGrefMult;
TH1D *hEta;
TH1D *hEvtPlaneParticlesEta;
TH1D *hEvtPlaneParticlesEtaNhits16andMore;
TH1D *hPhi;
TH1D *hPhiA;
TH1D *hPhiB;

TH1D *hPsi1A;
TH1D *hPsi1correctedA;
TH1D *hPsi1B;
TH1D *hPsi1correctedB;

TH1D *hPsi11;
TH1D *hPsi1corrected1;
TH1D *hPsi12;
TH1D *hPsi1corrected2;
TH1D *hPsi13;
TH1D *hPsi1corrected3;

TH1D *hBbcPsi;
TH1D *hBbcPsiCorrected;
TH1D *hLambdaPhi;
TH1D *hRapidityBeforeV0cuts;
TH1D *hProtonMidRapidity;
TH1D* hEtaEventPlaneCand;
TH1D* hRapidityEventPlaneCand;
TH1D* hProtonMidRapidity1;
TH1D* hDeuteronMidRapidity1;


TH1D *hAminusB;
TH1D *hBBCminusA;
TH1D *hBBCminusB;
TH1D *h1minus2;
TH1D *h1minus3;
TH1D *h2minus3;
TH1D *h1minusBBC;
TH1D *h2minusBBC;

TH2D *hDedx;
TH2D *hQxQyA;
TH2D *hQxQyB;
TH2D *hQxQy1;
TH2D *hQxQy2;
TH2D *hQxQy3;
TH2D *hBbcQxQy;
TH2D *hBbcQxQyCorrected;
TH2D *hBBCvsTpc1eventPlane;

TH2D *hNsigmaPion;
TH2D *hSigmaDeuteron;
//TH2D *hScatterMom;
TH2D *hVertexXY;
TH2D *hPtY;

TH2D *hMixedVsY;
TH2D *hRotatedVsY;
TH2D *hUnlikeSignVsY;
//TH3D *hDCAtoPrimVtxAndPointingAngle;

TH3D *hV1vsM;
TH3D *hV1tpc;
TH3D *hV1vsMPt;
TH3D *hV1tpcPt;
//TH3D *hPxvsM;




// ********************************** declaration of global variables **********************************
int nPions, nProtons, nPrimTracks;
class Particle {
  
public:
  short Id, Charge, MatchFlag;
  double Pt, Eta, Phi, MtdOneOverBeta, GDCA, nSigmaPion;
  StPhysicalHelixD helix;
  StThreeVectorD P;
};


Particle pPion[500], pProton[500];

TLorentzVector LV_Lambda(0,0,0,0);
const float MASS_PI = 0.13957; // in GeV
const float MASS_K = 0.49368; // in GeV
const float MASS_P = 0.93827; // in GeV

//const int BUFFER_SIZE = 434;
const int BUFFER_SIZE = 7;

int BufferPointer, iran;
int BufferEvent_NEvents[BUFFER_SIZE]={0};
int BufferEvent_Full[BUFFER_SIZE]={0};
int BufferEvent_Centrality[BUFFER_SIZE+20*BUFFER_SIZE];
int BufferEvent_nPions[BUFFER_SIZE+20*BUFFER_SIZE];
int BufferEvent_nProtons[BUFFER_SIZE+20*BUFFER_SIZE];
int BufEv_PionCharge[BUFFER_SIZE+20*BUFFER_SIZE][500];
StPhysicalHelixD BufEv_PionHelix[BUFFER_SIZE+20*BUFFER_SIZE][500];
StThreeVectorD BufEv_PionMomVector[BUFFER_SIZE+20*BUFFER_SIZE][500];
double BufEv_PionDca[BUFFER_SIZE+20*BUFFER_SIZE][500];
int BufEv_ProtonCharge[BUFFER_SIZE+20*BUFFER_SIZE][500];
StPhysicalHelixD BufEv_ProtonHelix[BUFFER_SIZE+20*BUFFER_SIZE][500];
StThreeVectorD BufEv_ProtonMomVector[BUFFER_SIZE+20*BUFFER_SIZE][500];
double BufEv_ProtonDca[BUFFER_SIZE+20*BUFFER_SIZE][500];

void makeMixedPairs(int bufferPointer, int nP, Particle *pP, int nPi, Particle *pPi, StThreeVectorD primVtxPos, Float_t MagnetField, int centrality);
void copyCurrentToBuffer(int bufferPointer, int nP, Particle *pP, int nPi, Particle *pPi, int centrality);


// **************************************** Loop through Events and Particles ***************************
void PicoDst::Loop( int nEvents = -1)
{
  
  hEventCounter = new TH1I("EventCounter","",10,0,10);
  hIndexToEvent= new TH1I("IndexToEvent","",2000,0,2000);
  hNlambdaPerEvent = new TH1I("NlambdaPerEvent","",10,0,10);
  hBufferPointer = new TH1I("BufferPointer","",BUFFER_SIZE,0,BUFFER_SIZE);
  hVertexIndex = new TH1I("VertexIndex","Index of the Vertex in MuDst",20,0,20);
  hBBCadc = new TH2I("BBCadc","",16,0,16,6000,0,6000);
  hHitE = new TH2D("HitE","",16,0,16,6000,0,6000);
  
  hNtrkA = new TH1I("NumberOfTracksInA","",250,0,250);
  hNtrkB = new TH1I("NumberOfTracksInB","",250,0,250);
  hNtrk1 = new TH1I("NumberOfTracksIn1","",250,0,250);
  hNtrk2 = new TH1I("NumberOfTracksIn2","",250,0,250);
  hNtrk3 = new TH1I("NumberOfTracksIn3","",250,0,250);
  
  hVertexZ = new TH1D("VertexZ","Vertex Z",10000,100,300);
  hVertexXY = new TH2D("VertexXY","VertexXY",500,-10.,10.,500,-10.,10.);
  hGrefMult = new TH1D("GrefMult","",500,0,500);
  
  hNhitsFit = new TH1D("NhitsFit","Number of Tpc Hits",200,-100.,100.);
  hRatio = new TH1D("Ratio","Number of hits Ratio",100,0.,1.);
  
  hEta = new TH1D("Eta","",1000,-10,10);
  hEvtPlaneParticlesEta = new TH1D("EvtPlaneParticlesEta","",300,-3,0);
  hEvtPlaneParticlesEtaNhits16andMore = new TH1D("EvtPlaneParticlesEtaNhits16andMore","",300,-3,0);
  hPhi = new TH1D("Phi","",640,-6.4,6.4);
  hPhiA = new TH1D("PhiA","",315,-3.15,3.15);
  hPhiB = new TH1D("PhiB","",315,-3.15,3.15);
  hEtaEventPlaneCand = new TH1D("EtaEventPlaneCand","",600,-3,3);
  hRapidityEventPlaneCand = new TH1D("RapidityEventPlaneCand","",600,-3,3);
  
  
  
  hMom = new TH1D("Mom","momentum",1000,-10.,10.);
//  hScatterMom = new TH2D("scatterMom","momentum",1000,0.,10., 1000,0.,10.);
  hDedx = new TH2D("Dedx","",1000,-10.,10.,500,0.,5.);
  hNsigmaPion = new TH2D("NsigmaPion","",500,-5.,5.,500,-1000.,1000.);
  hSigmaDeuteron = new TH2D("SigmaDeuteron","",500,0,5.,600,-3,3);
//  hTofPid = new TH2D("TofPid","",1000,0.,10.,1200,-2.,4.);
  hBbcQxQy = new TH2D("BbcQxQy","",600,-3,3,600,-3,3);
  hBbcQxQyCorrected = new TH2D("BbcQxQyCorrected","",600,-3,3,600,-3,3);
  hBbcPsi = new TH1D("BbcPsi","",960,-3.2,6.4);
  hBbcPsiCorrected = new TH1D("BbcPsiCorrected","",960,-3.2,6.4);
  
  hQxQyA = new TH2D("QxQyA","",300,-1.5,1.5,300,-1.5,1.5);
  hPsi1A = new TH1D("Psi1A","",320,-3.2,3.2);
  hPsi1A->GetXaxis()->SetTitle("#Psi^{a}");
  hPsi1correctedA = new TH1D("Psi1correctedA","",320,-3.2,3.2);
  hQxQyB = new TH2D("QxQyB","",300,-1.5,1.5,300,-1.5,1.5);
  hPsi1B = new TH1D("Psi1B","",320,-3.2,3.2);
  hPsi1B->GetXaxis()->SetTitle("#Psi^{b}");
  hPsi1correctedB = new TH1D("Psi1correctedB","",320,-3.2,3.2);
  
  hQxQy1 = new TH2D("QxQy1","",300,-1.5,1.5,300,-1.5,1.5);
  hPsi11 = new TH1D("Psi11","",320,-3.2,3.2);
  hPsi11->GetXaxis()->SetTitle("#Psi^{1}");
  hPsi1corrected1 = new TH1D("Psi1corrected1","",320,-3.2,3.2);
  hQxQy2 = new TH2D("QxQy2","",300,-1.5,1.5,300,-1.5,1.5);
  hPsi12 = new TH1D("Psi12","",320,-3.2,3.2);
  hPsi12->GetXaxis()->SetTitle("#Psi^{2}");
  hPsi1corrected2 = new TH1D("Psi1corrected2","",320,-3.2,3.2);
  hQxQy3 = new TH2D("QxQy3","",300,-1.5,1.5,300,-1.5,1.5);
  hPsi13 = new TH1D("Psi13","",320,-3.2,3.2);
  hPsi13->GetXaxis()->SetTitle("#Psi^{3}");
  hPsi1corrected3 = new TH1D("Psi1corrected3","",320,-3.2,3.2);
  
  
  hBBCvsTpc1eventPlane =  new TH2D("BBCvsTpc1eventPlane","",320,-3.2,3.2,320,-3.2,3.2);
  hLambdaPhi = new TH1D("LambdaPhi","",1000,-5,5);
  hRapidityBeforeV0cuts = new TH1D("RapidityBeforeV0cuts","",60,-3.,0.);
  hProtonMidRapidity = new TH1D("ProtonMidRapidity","",400,-4,4);
  hProtonMidRapidity1 = new TH1D("ProtonMidRapidity1","",400,-4,4);
  hDeuteronMidRapidity1 = new TH1D("DeuteronMidRapidity1","",400,-4,4);
  
  hAminusB = new TH1D("AminusB","",300,-1.5,1.5);
  hBBCminusB = new TH1D("BBCminusB","",300,-1.5,1.5);
  hBBCminusA = new TH1D("BBCminusA","",300,-1.5,1.5);

  h1minus2 = new TH1D("subev1minus2","",300,-1.5,1.5);
  h1minus3 = new TH1D("subev1minus3","",300,-1.5,1.5);
  h2minus3 = new TH1D("subev2minus3","",300,-1.5,1.5);
  h1minusBBC = new TH1D("subev1minusBBC","",300,-1.5,1.5);
  h2minusBBC = new TH1D("subev2minusBBC","",300,-1.5,1.5);

  
  hUnlikeSignVsY = new TH2D("UnlikeSignVsY","",100,-2.,0.,1000,1.,1.5);
  hRotatedVsY = new TH2D("RotatedVsY","",100,-2.,0.,1000,1.,1.5);
  hMixedVsY = new TH2D("MixedVsY","",100,-2.,0.,1000,1.,1.5);
//  hDCAtoPrimVtxAndPointingAngle = new TH3D("DCAtoPrimVtxAndPointingAngle","",100,-2.,0.,400,0,2,200,0,0.2);
  hPtY = new TH2D("PtY","",100,-2,0,200,0,4);
  
  Double_t arrayOfLowEdgesX[11] = {1.080,1.095,1.100,1.110,1.114,1.116,1.120,1.130,1.140,1.160,1.190};
  Double_t arrayOfLowEdgesZ[41] = {0};
  for(int i=0;i<40;i++){
    arrayOfLowEdgesZ[i]=-2+i*0.05;
 	}
  Double_t arrayOfLowEdgesV1[151] = {0};
  for(int i=0;i<151;i++){
    arrayOfLowEdgesV1[i]=-1.5+i*0.02;
 	}
  Double_t arrayOfLowEdgesPx[101] = {0};
  for(int i=0;i<101;i++){
    arrayOfLowEdgesPx[i]=-5+i/(double)10;
 	}
//  hV1vsM = new TH3D("V1vsM","",10,arrayOfLowEdgesX,150,arrayOfLowEdgesV1,40,arrayOfLowEdgesZ);
  hV1vsM = new TH3D("V1vsM","",120,1.08,1.2,220,-1.1,1.1,100,-2,0);
  hV1tpc = new TH3D("V1tpc","",120,1.08,1.2,220,-1.1,1.1,100,-2,0);
  hV1vsMPt = new TH3D("PtV1vsM","",120,1.08,1.2,220,-1.1,1.1,10,0.2,2.2);
  hV1tpcPt = new TH3D("PtV1tpc","",120,1.08,1.2,220,-1.1,1.1,10,0.2,2.2);
  //  hPxvsM = new TH3D("PxvsM","",10,arrayOfLowEdgesX,100,arrayOfLowEdgesPx,40,arrayOfLowEdgesZ);
  
  //   In a ROOT session, you can do:
  //      Root > .L PicoDst.C
  //      Root > PicoDst t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //
  
  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  if ( nEvents > 0 && nEvents < nentries ) nentries = nEvents;
  cout<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) { // event loop
    Long64_t ientry = LoadTree(jentry);
    if(jentry%1000==0) cout << " Procesing event " << jentry << " ... " << endl;
    if (ientry < 0) break;
    fChain->SetCacheSize(10000000);
    fChain->AddBranchToCache("*",kTRUE);
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    hEventCounter->Fill(0);
    //    bool isDiMuon = false;
    //    for(Int_t i=0; i<8; i++) if(Event_mTriggerWordMtd[0] & (1<<i)) isDiMuon = true;
    //    if (!isDiMuon) continue; // cut on trigger

    if(!(Event_mTriggerWord[0] & (1<<0))) continue; 
    hEventCounter->Fill(1);
    StThreeVectorD priVtx(Event_mPrimaryVertex_mX1[0],Event_mPrimaryVertex_mX2[0],Event_mPrimaryVertex_mX3[0]);
    hVertexZ->Fill(priVtx.z());
    hVertexXY->Fill(priVtx.x(), priVtx.y());
    hVertexIndex->Fill(Event_mVertexIndex[0]);
//    if (Event_mVertexIndex[0] > 0) continue;
    if (Event_mPrimaryVertex_mX3[0] > 212 || Event_mPrimaryVertex_mX3[0] < 210) continue;
//    if (Event_mPrimaryVertex_mX1[0] < -1.1 || Event_mPrimaryVertex_mX1[0] > 0.3) continue;
//    if (Event_mPrimaryVertex_mX2[0] < -2.3 || Event_mPrimaryVertex_mX2[0] > -1.3) continue;
    hEventCounter->Fill(2);
    double mCentrality = -999;

    //******************************* Track Selection ****************************************************
    nPions = 0; nProtons = 0; nPrimTracks = 0;
    int nLambda = 0;
    
    int NtrkA = 0;
    double WeightA = 0.;
    double QxA = 0;
    double QyA = 0;
    int NtrkB = 0;
    double WeightB = 0.;
    double QxB = 0;
    double QyB = 0;

    int Ntrk1 = 0;
    double Weight1 = 0.;
    double Qx1 = 0;
    double Qy1 = 0;
    int Ntrk2 = 0;
    double Weight2 = 0.;
    double Qx2 = 0;
    double Qy2 = 0;
    int Ntrk3 = 0;
    double Weight3 = 0.;
    double Qx3 = 0;
    double Qy3 = 0;
    
    double LY[100] = {0};
    double LPt[100] = {0};
    double LM[100] = {0};
    double LPhi[100] = {0};
    double LEta[100] = {0};
    int LProtonId[100] = {0};
    
    for(int i = 0; i<Tracks_; i++){
      vis[Tracks_mId[i]] = false;
      //if (Tracks_mBTofPidTraitsIndex[i]<0) continue; // TOF match
      hNhitsFit->Fill(Tracks_mNHitsFit[i]);
      hRatio->Fill(Tracks_mNHitsFit[i]/(double)Tracks_mNHitsMax[i]);
      if(TMath::Abs(Tracks_mNHitsFit[i]/(double)Tracks_mNHitsMax[i]) < 0.52) continue;
      if(TMath::Abs(Tracks_mNHitsFit[i]) < 10) continue;
      if(Tracks_mNHitsDedx[0] <= 0) continue;
      float charge = Tracks_mNHitsFit[i] > 0 ? 1 : -1;
      //if(TMath::Abs(pPrim.pseudoRapidity()) > 0.8) continue;
      StDcaGeometry dcaGeom;
      dcaGeom.set(Tracks_mPar[i], Tracks_mErrMatrix[i]);
      StPhysicalHelixD trackHelix = dcaGeom.helix();
      StThreeVectorD p = trackHelix.momentum( Event_mBField[0] * kilogauss  );
      double pmag = p.magnitude();
      StThreeVectorD primVtxPos = StThreeVectorD(Event_mPrimaryVertex_mX1[0],Event_mPrimaryVertex_mX2[0],Event_mPrimaryVertex_mX3[0]);
      double gDca = trackHelix.distance(primVtxPos);
      //if(gDca<3) nPrimTracks++;
      StThreeVectorD primMom = StThreeVectorD(Tracks_mPMomentum_mX1[i],Tracks_mPMomentum_mX2[i],Tracks_mPMomentum_mX3[i]);
      if(primMom.mag()>0) {
        nPrimTracks++;
      }
      if(gDca>8) continue;
      if(pmag <= 0) continue;
      if(p.perp() <= 0.1) continue;
      if(TMath::Abs(Tracks_mNHitsFit[i]) < 10) continue;
      hNsigmaPion->Fill(pmag*charge,Tracks_mNSigmaPion[i]);
      hMom->Fill(pmag);
      hEta->Fill(p.pseudoRapidity());
      
      if (gDca > 0.9 && Tracks_mNSigmaPion[i] > -200 && Tracks_mNSigmaPion[i] < 200 && charge < 0) {
        pPion[nPions].Id = Tracks_mId[i];
        pPion[nPions].Charge = charge;
        pPion[nPions].P = p;
        pPion[nPions].helix = trackHelix;
        pPion[nPions].GDCA = gDca;
        nPions++;
      }
      if (gDca > 0.8 && p.perp() > 0.2 && Tracks_mNSigmaProton[i] > -200 && Tracks_mNSigmaProton[i] < 200 && charge > 0) {
        pProton[nProtons].Id = Tracks_mId[i];
        pProton[nProtons].Charge = charge;
        pProton[nProtons].P = p;
        pProton[nProtons].helix = trackHelix;
        pProton[nProtons].GDCA = gDca;
        nProtons++;
      }
    }
    //***********************************  Define Centrality ****************************************
    hGrefMult->Fill(nPrimTracks);
    if (nPrimTracks>152) mCentrality = 0; // 0-5%
    else if (nPrimTracks>121) mCentrality = 1; // 5-10%
    else if (nPrimTracks>97) mCentrality = 2; // 10-15%
    else if (nPrimTracks>77) mCentrality = 3; // 15-20%
    else if (nPrimTracks>61) mCentrality = 4; // 20-25%
    else if (nPrimTracks>48) mCentrality = 5; // 25-30%
    else mCentrality = 6; // >30%
    
    if(nPrimTracks > 240) continue; // remove pile-up tracks
    hEventCounter->Fill(3);

    if(mCentrality>5 || mCentrality<2 ) continue;
    hEventCounter->Fill(4);
    for(int i=0;i<16;i++) hBBCadc->Fill(i,Event_mBbcAdcEast[0][i]);
    
    
    //**************************** Create Unlike-sign Pairs for Lambda Analysis ***********************************
    // pNeg is negative
    // pPos is positive
    
    for (int i=0; i<nProtons; i++) {
      StPhysicalHelixD part1Helix = pProton[i].helix;
      TLorentzVector lvI, lvJ;
      StThreeVectorD p1 = pProton[i].P;
      lvI.SetPtEtaPhiM(p1.perp(),p1.pseudoRapidity(),p1.phi(),MASS_P);
      for (int j=0; j<nPions; j++) {
        if (pProton[i].Id == pPion[j].Id) continue;
        if (pProton[i].Charge - pPion[j].Charge == 0) continue;
        StThreeVectorD p2 = pPion[j].P;
        lvJ.SetPtEtaPhiM(p2.perp(),p2.pseudoRapidity(),p2.phi(),MASS_PI);
        TLorentzVector EstLV_Lambda = lvI + lvJ;
        hRapidityBeforeV0cuts->Fill(EstLV_Lambda.Rapidity());
        if (EstLV_Lambda.M()>1.16) continue; // very loose cut on ivariant mass to speed up analysis
//        if (EstLV_Lambda.M() > 1.105 && EstLV_Lambda.M() < 1.125){
//          vis[pProton[i].Id] = true;
//          vis[pPion[j].Id] = true;
//        }
//        if (pProton[i].GDCA < 0.4 || pPion[j].GDCA < 0.8) continue; // get rid of primary tracks
        StPhysicalHelixD part2Helix = pPion[j].helix;
        pair<double,double> pathLenghts = part1Helix.pathLengths(part2Helix);
        StThreeVectorD pNegPosAtDca = part1Helix.at(pathLenghts.first);
        StThreeVectorD pPosPosAtDca = part2Helix.at(pathLenghts.second);
        StThreeVectorD dcaVector = pNegPosAtDca-pPosPosAtDca;
        StThreeVectorD primVtxPos = StThreeVectorD(Event_mPrimaryVertex_mX1[0],Event_mPrimaryVertex_mX2[0],Event_mPrimaryVertex_mX3[0]);
        StThreeVectorD secVtxPos = pPosPosAtDca+(dcaVector*0.5);
        StThreeVectorD decLenVec = secVtxPos-primVtxPos;
        StThreeVectorD pNegMomAtDca = part1Helix.momentumAt(pathLenghts.first, Event_mBField[0] * kilogauss); //proton
        StThreeVectorD pPosMomAtDca = part2Helix.momentumAt(pathLenghts.second, Event_mBField[0] * kilogauss); //pion
        StThreeVectorD LambdaMomAtDCA = pNegMomAtDca + pPosMomAtDca;
        lvI.SetPtEtaPhiM(pNegMomAtDca.perp(),pNegMomAtDca.pseudoRapidity(),pNegMomAtDca.phi(),MASS_P);
        lvJ.SetPtEtaPhiM(pPosMomAtDca.perp(),pPosMomAtDca.pseudoRapidity(),pPosMomAtDca.phi(),MASS_PI);
        TLorentzVector LV_Lambda = lvI + lvJ;
        double pointingAngle = LambdaMomAtDCA.angle(decLenVec);
        double LambdaDCAtoPrimVtx  = TMath::Abs(decLenVec.mag()*TMath::Sin(pointingAngle));
        if (decLenVec.mag() < 7) continue; // cut on path length
        if (dcaVector.mag() > 1) continue; // cut on track mutual dca
//        if (LV_Lambda.M() > 1.11 && LV_Lambda.M() < 1.122) hDCAtoPrimVtxAndPointingAngle->Fill(LV_Lambda.Rapidity(),LambdaDCAtoPrimVtx,pointingAngle);
        if (TMath::Abs(pointingAngle) > 0.15) continue; // cut on pointing angle
        if (LambdaDCAtoPrimVtx > 1) continue;
        if (LV_Lambda.M() > 1.105 && LV_Lambda.M() < 1.125){
          vis[pProton[i].Id] = true;
          vis[pPion[j].Id] = true;
        }
        hUnlikeSignVsY->Fill(LV_Lambda.Rapidity(),LV_Lambda.M());
//        if (LV_Lambda.M() > 1.085 && LV_Lambda.M() < 1.19 && LV_Lambda.Eta() < -1.2){
//        if (LV_Lambda.M() > 1.113 && LV_Lambda.M() < 1.119 /*&& LV_Lambda.Eta() < -1.2*/){
        if (LV_Lambda.Eta() < 0){
          LY[nLambda] = LV_Lambda.Rapidity();
          LEta[nLambda] = LV_Lambda.PseudoRapidity();
          LPt[nLambda] = LV_Lambda.Pt();
          LPhi[nLambda] = LV_Lambda.Phi();
          LM[nLambda] = LV_Lambda.M();
          [nLambda] = pProton[i].Id;
          hPhi->Fill(LV_Lambda.Phi());
          nLambda++;
          if (LV_Lambda.M() > 1.113 && LV_Lambda.M() < 1.119){
            hPtY->Fill(LV_Lambda.Rapidity(),LV_Lambda.Pt());
          }
        }
      } // loop j through nPions
    } // loop i trough nProtons
    hNlambdaPerEvent->Fill(nLambda);
    
    //**************************** Create Rotated-momentum Pairs for Lambda Analysis ***********************************
    for (int i=0; i<nProtons; i++) {
//      if (pProton[i].GDCA < 0.6) continue; // get rid of primary tracks
      StThreeVectorD primVtxPos = StThreeVectorD(Event_mPrimaryVertex_mX1[0],Event_mPrimaryVertex_mX2[0],Event_mPrimaryVertex_mX3[0]);
      StPhysicalHelixD part1Helix = pProton[i].helix;
      StThreeVectorD tmpMom = part1Helix.momentum(Event_mBField[0] * kilogauss);    //momentum at origin
      StThreeVectorD tmpX1 = part1Helix.origin();    //origin
      tmpMom.setX(-tmpMom.x());
      tmpMom.setY(-tmpMom.y());
      tmpX1.setX(-(tmpX1.x()-primVtxPos.x())+primVtxPos.x());
      tmpX1.setY(-(tmpX1.y()-primVtxPos.y())+primVtxPos.y());
      StPhysicalHelixD helixtmp(tmpMom, tmpX1, Event_mBField[0] * kilogauss, 1);
      part1Helix = helixtmp;
      TLorentzVector lvI, lvJ;
      StThreeVectorD p1 = tmpMom;
      lvI.SetPtEtaPhiM(p1.perp(),p1.pseudoRapidity(),p1.phi(),MASS_P);
      for (int j=0; j<nPions; j++) {
        if (pProton[i].Id == pPion[j].Id) continue;
        if (pProton[i].Charge - pPion[j].Charge == 0) continue;
//        if (pPion[j].GDCA < 0.8) continue; // get rid of primary tracks
        StThreeVectorD p2 = pPion[j].P;
        lvJ.SetPtEtaPhiM(p2.perp(),p2.pseudoRapidity(),p2.phi(),MASS_PI);
        TLorentzVector EstLV_Lambda = lvI + lvJ;
        if (EstLV_Lambda.M()>1.16) continue; // very loose cut on ivariant mass to speed up analysis
        StPhysicalHelixD part2Helix = pPion[j].helix;
        pair<double,double> pathLenghts = part1Helix.pathLengths(part2Helix);
        StThreeVectorD pNegPosAtDca = part1Helix.at(pathLenghts.first);
        StThreeVectorD pPosPosAtDca = part2Helix.at(pathLenghts.second);
        StThreeVectorD dcaVector = pNegPosAtDca-pPosPosAtDca;
        StThreeVectorD secVtxPos = pPosPosAtDca+(dcaVector*0.5);
        StThreeVectorD decLenVec = secVtxPos-primVtxPos;
        if (decLenVec.mag() < 7) continue; // cut on path length
        if (dcaVector.mag() > 1) continue; // cut on track mutual dca
        StThreeVectorD pNegMomAtDca = part1Helix.momentumAt(pathLenghts.first, Event_mBField[0] * kilogauss); //proton
        StThreeVectorD pPosMomAtDca = part2Helix.momentumAt(pathLenghts.second, Event_mBField[0] * kilogauss); //pion
        StThreeVectorD LambdaMomAtDCA = pNegMomAtDca + pPosMomAtDca;
        lvI.SetPtEtaPhiM(pNegMomAtDca.perp(),pNegMomAtDca.pseudoRapidity(),pNegMomAtDca.phi(),MASS_P);
        lvJ.SetPtEtaPhiM(pPosMomAtDca.perp(),pPosMomAtDca.pseudoRapidity(),pPosMomAtDca.phi(),MASS_PI);
        TLorentzVector LV_Lambda = lvI + lvJ;
        double pointingAngle = LambdaMomAtDCA.angle(decLenVec);
        double LambdaDCAtoPrimVtx  = TMath::Abs(decLenVec.mag()*TMath::Sin(pointingAngle));
        if (TMath::Abs(pointingAngle) > 0.15) continue; // cut on pointing angle
        if (LambdaDCAtoPrimVtx > 1) continue;
        hRotatedVsY->Fill(LV_Lambda.Rapidity(),LV_Lambda.M());
      } // loop j through nPions
    } // loop i trough nPions
    
//    cout<<"end of filling"<<endl;
    //***********************************  Define BBC Event Plane ****************************************
    double egain[16]={
      1.105045,  // Tile 1
      0.9370329, // Tile 2
      0.8978093, // Tile 3
      1.171845,  // Tile 4
      0.9141548, // Tile 5
      0.9741560, // Tile 6
      0.8450179, // Tiles 7,9
      0.8332370, // Tile 8
      0.9422224, // Tile 10
      1.173847,  // Tile 11
      1.111965,  // Tile 12
      0.9540058, // Tiles 13,15
      1.190012,  // Tile 14
      1.021805,  // Tile 16
      1.228292,  // Tile 17
      0.9023509  // Tile 18
    };
    double nHitE[16];
    for(int i=0;i<16;i++){
      if(Event_mBbcAdcEast[0][i]>10 && Event_mBbcAdcEast[0][i]<4000){
        nHitE[i] = (double)Event_mBbcAdcEast[0][i]/egain[i];
        hHitE->Fill(i,nHitE[i]);
      }else nHitE[i] = 0;
    }
    TVector2 mQE;
    Double_t mQEx=0., mQEy=0.;
    Float_t eXsum=0., eYsum=0., eWgt=0.,psi_e=0.,psi_e_s=0.;
    for(int iTile = 0; iTile < 16; iTile++) {
      if(Event_mBbcAdcEast[0][iTile]>10 && Event_mBbcAdcEast[0][iTile]<4000){
        //      cout<<"Tile: "<<iTile<<"    Phi: "<<BBC_GetPhi(0,iTile)<<endl;
        //        if(iTile==6){
        //          eXsum += TMath::Cos(BBC_GetPhi(0,16,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eYsum += TMath::Sin(BBC_GetPhi(0,16,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eXsum += TMath::Cos(BBC_GetPhi(0,17,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eYsum += TMath::Sin(BBC_GetPhi(0,17,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eWgt += nHitE[iTile];
        //        }else if(iTile==11){
        //          eXsum += TMath::Cos(BBC_GetPhi(0,18,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eYsum += TMath::Sin(BBC_GetPhi(0,18,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eXsum += TMath::Cos(BBC_GetPhi(0,19,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eYsum += TMath::Sin(BBC_GetPhi(0,19,jentry*(iTile+1)))*nHitE[iTile]/2;
        //          eWgt += nHitE[iTile];
        //        }else{
        eXsum += TMath::Cos(BBC_GetPhi(0,iTile,1))*nHitE[iTile];
        eYsum += TMath::Sin(BBC_GetPhi(0,iTile,1))*nHitE[iTile];
        //      if(nHitE[iTile]>0) cout<<"Tile: "<<iTile<<"    Phi: "<<BBC_GetPhi(1,iTile)<<endl;
        eWgt += nHitE[iTile];
      }
    }
    mQEx= (eWgt>0.0) ? eXsum/eWgt:0.0;
    mQEy= (eWgt>0.0) ? eYsum/eWgt:0.0;
//    cout<<"Q-vectors: "<<mQEx<<"   "<<mQEy<<endl;
    if(TMath::Abs(mQEx)>1) cout<<mQEx<<"   "<<eWgt<<endl;
    if(TMath::Abs(mQEy)>1) cout<<mQEy<<"   "<<eWgt<<endl;
    hBbcQxQy->Fill(mQEx,mQEy);
    double mQExCorrected = mQEx - 2.921513e-04;
    double mQEyCorrected = mQEy + 4.094292e-03;
    hBbcQxQyCorrected->Fill(mQExCorrected,mQEyCorrected);
    mQE.Set(mQExCorrected,mQEyCorrected);
    if(mQE.Mod()){
//      psi_e=TMath::ATan2(mQEyCorrected,mQExCorrected);
      psi_e=mQE.Phi() - TMath::Pi();
//      cout<<"Psi: "<<psi_e<<endl;
//      if(psi_e<0.0) {psi_e +=2*TMath::Pi();}  //done in BBC_GetPsi()
//      cout<<"Psi: "<<psi_e<<endl;
    }
//    psi_e -= TMath::Pi();
    hBbcPsi->Fill(psi_e);
    double sin = TMath::Sin(psi_e);
    double cos = TMath::Cos(psi_e);
    double sin2 = TMath::Sin(2*psi_e);
    double cos2 = TMath::Cos(2*psi_e);
    double sin4 = TMath::Sin(4*psi_e);
    double cos4 = TMath::Cos(4*psi_e);
    double sin6 = TMath::Sin(6*psi_e);
    double cos6 = TMath::Cos(6*psi_e);
    double sin8 = TMath::Sin(8*psi_e);
    double cos8 = TMath::Cos(8*psi_e);
    double sin10 = TMath::Sin(10*psi_e);
    double cos10 = TMath::Cos(10*psi_e);
    double sin12 = TMath::Sin(12*psi_e);
    double cos12 = TMath::Cos(12*psi_e);
    psi_e_s  = psi_e + 2*(0.000587891)*sin - 2*(0.00387237)*cos + (-0.0588431)*sin2 - (-8.37539e-05)*cos2 + 0.5*(0.0155543)*sin4 - 0.5*(-0.000452597)*cos4 + 1./3.*(-0.0118207)*sin6 - 1./3.*(-0.000223721)*cos6 + 1./4.*(0.00213396)*sin8 - 1./4.*(0.000785518)*cos8 + 1./5.*(0.00170258)*sin10 - 1./5.*(0.00115025)*cos10 + 1./6.*(-0.00137621)*sin12 - 1./6.*(-0.000994075)*cos12;
    hBbcPsiCorrected->Fill(psi_e_s);

    //***********************************  Define TPC Event Plane ****************************************
    for(int i = 0; i<Tracks_; i++){
      //      if(vis.count(Tracks_mId[i]) && vis[Tracks_mId[i]]) continue;
      //        if(Tracks_mId[i]==LProtonId[iLambda]) continue;
      if(TMath::Abs(Tracks_mNHitsFit[i]/(double)Tracks_mNHitsMax[i]) < 0.52) continue;
      if(Tracks_mNHitsDedx[0] <= 0) continue;
      if(TMath::Abs(Tracks_mNHitsFit[i]) < 10) continue;
      float charge = Tracks_mNHitsFit[i] > 0 ? 1 : -1;
      StThreeVectorD primMom = StThreeVectorD(Tracks_mPMomentum_mX1[i],Tracks_mPMomentum_mX2[i],Tracks_mPMomentum_mX3[i]);
      double pt = primMom.perp();
      double p = primMom.mag();
      if(p==0) continue;
      double eta  = primMom.pseudoRapidity();
//      StDcaGeometry dcaGeom;
//      dcaGeom.set(Tracks_mPar[i], Tracks_mErrMatrix[i]);
//      StPhysicalHelixD trackHelix = dcaGeom.helix();
//      StThreeVectorD primVtxPos = StThreeVectorD(Event_mPrimaryVertex_mX1[0],Event_mPrimaryVertex_mX2[0],Event_mPrimaryVertex_mX3[0]);
//      double gDca = trackHelix.distance(primVtxPos);
//      StThreeVectorD GlobMom = trackHelix.momentum( Event_mBField[0] * kilogauss  );
      
      //        double rrr = gRandom3->Rndm();
      //        delete gRandom3;
      //        hRandom->Fill(rrr);
      
      if(!gDeuterons){
        cout<<"Pointer to Bichsel graph is empty"<<endl;
        break;
      }
      //      double OneOverBetaTofPredictedForProtons = TMath::Sqrt(1+MASS_P*MASS_P/p/p);
      //      double OneOverBetaTofPredictedForDeuterons = TMath::Sqrt(1+1.8756*1.8756/p/p);
      //      double OneOverBetaTof = 20000./(double)BTofPidTraits_mBTofBeta[Tracks_mBTofPidTraitsIndex[i]];
      //      double TofSigma = OneOverBetaTof-OneOverBetaTofPredictedForProtons;
      //      hTofSigmaD->Fill(p,TofSigma);
      //      if(p>1.25 && Tracks_mBTofPidTraitsIndex[i]<0) continue;
      //      if(TofSigmaDeuterons < -0.35/TMath::Power(p+0.7,1.5)) continue;
      //      if(TofSigma < -0.15/TMath::Power(p+0.9,1.2) || TofSigma > 0.2/TMath::Power(p+0.9,1.2)) continue;
      double SigmaDeuteron = TMath::Log(Tracks_mDedx[i]*0.001) - gDeuterons->Eval(p);
      if(p > 0.3 && eta > -1 && eta < 0 && /*gDca < 3 &&*/ charge > 0){
        //        if(pt > 2) pt = 2;
        if(Tracks_mNSigmaProton[i] > -300 && Tracks_mNSigmaProton[i] < 300){
          double E = TMath::Sqrt(MASS_P*MASS_P+p*p);
          double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
          QxA += (y+1.5212)*pt*TMath::Cos(primMom.phi());
          QyA += (y+1.5212)*pt*TMath::Sin(primMom.phi());
          WeightA += (y+1.5212)*pt;
          NtrkA++;
          hDedx->Fill(p*charge,TMath::Log(Tracks_mDedx[i]*0.001));
          hPhiA->Fill(primMom.phi());
          hEvtPlaneParticlesEta->Fill(eta);
        }
        else if(p>0.4 && p<2 && SigmaDeuteron < 0.25 && SigmaDeuteron > -0.18){
          double E = TMath::Sqrt(1.877*1.877+p*p);
          double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
          QxA += (y+1.5212)*pt*TMath::Cos(primMom.phi());
          QyA += (y+1.5212)*pt*TMath::Sin(primMom.phi());
          WeightA += (y+1.5212)*pt;
          NtrkA++;
          hDedx->Fill(p*charge,TMath::Log(Tracks_mDedx[i]*0.001));
          hPhiA->Fill(primMom.phi());
          hEvtPlaneParticlesEta->Fill(eta);
        }
      }
      if(p > 0.3 && eta > -2 && eta < -1/* && gDca < 3*/ && charge > 0){
        //        if(pt > 2) pt = 2;
        if(Tracks_mNSigmaProton[i] > -300 && Tracks_mNSigmaProton[i] < 300){
          double E = TMath::Sqrt(MASS_P*MASS_P+p*p);
          double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
          QxB += (y+1.5212)*pt*TMath::Cos(primMom.phi());
          QyB += (y+1.5212)*pt*TMath::Sin(primMom.phi());
          WeightB += TMath::Abs(y+1.5212)*pt;
          NtrkB++;
          hPhiB->Fill(primMom.phi());
          hEvtPlaneParticlesEta->Fill(eta);
        }
        else if(p>0.4 && p<2 && SigmaDeuteron < 0.25 && SigmaDeuteron > -0.18){
          double E = TMath::Sqrt(1.877*1.877+p*p);
          double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
          QxB += (y+1.5212)*pt*TMath::Cos(primMom.phi());
          QyB += (y+1.5212)*pt*TMath::Sin(primMom.phi());
          WeightB += TMath::Abs(y+1.5212)*pt;
          NtrkB++;
          hPhiB->Fill(primMom.phi());
          hEvtPlaneParticlesEta->Fill(eta);
        }
      }
    }
//    if(NtrkA < 4 || NtrkB < 4) continue;
//    if(WeightA==0 || WeightA==0)continue;
    hNtrkA->Fill(NtrkA);
    hNtrkB->Fill(NtrkB);
    
//    double qxA = QxA/(double)NtrkA;
//    double qyA = QyA/(double)NtrkA;
    double qxA = (WeightA>0.0) ? QxA/WeightA:0;
    double qyA = (WeightA>0.0) ? QyA/WeightA:0;
    //    cout<<qxA<<"  "<<qyA<<endl;
//    double QxCorrectedA = (qxA - 3.117609e-03)*NtrkA;
//    double QyCorrectedA = (qyA - 3.024766e-02)*NtrkA;
    double QxCorrectedA = qxA - 3.881650e-03;
    double QyCorrectedA = qyA - 3.874203e-02;
    hQxQyA->Fill(qxA,qyA);
    double psiA = TMath::ATan2(QyCorrectedA,QxCorrectedA);
    hPsi1A->Fill(psiA);
    double SinA = TMath::Sin(psiA);
    double CosA = TMath::Cos(psiA);
    double Sin2A = TMath::Sin(2*psiA);
    double Cos2A = TMath::Cos(2*psiA);
    double Sin4A = TMath::Sin(4*psiA);
    double Cos4A = TMath::Cos(4*psiA);
    double PsiCorrectedA = psiA + 2*(0.00147617)*SinA - 2*(0.0132875)*CosA + (0.00229888)*Sin2A - (0.00051621)*Cos2A + 0.5*(0.000270637)*Sin4A - 0.5*(0.000283086)*Cos4A;
    
    hPsi1correctedA->Fill(PsiCorrectedA);
    
//    double qxB = QxB/(double)NtrkB;
//    double qyB = QyB/(double)NtrkB;
    double qxB = (WeightB>0.0) ? QxB/WeightB:0;
    double qyB = (WeightB>0.0) ? QyB/WeightB:0;
//    double QxCorrectedB = (qxB + 2.013283e-03)*NtrkB;
//    double QyCorrectedB = (qyB - 2.263891e-03)*NtrkB;
    double QxCorrectedB = qxB + 5.745124e-03;
    double QyCorrectedB = qyB - 6.448013e-03;
    hQxQyB->Fill(qxB,qyB);
    double psiB = TMath::ATan2(QyCorrectedB,QxCorrectedB);
    hPsi1B->Fill(psiB);
    double SinB = TMath::Sin(psiB);
    double CosB = TMath::Cos(psiB);
    double Sin2B = TMath::Sin(2*psiB);
    double Cos2B = TMath::Cos(2*psiB);
    double Sin4B = TMath::Sin(4*psiB);
    double Cos4B = TMath::Cos(4*psiB);
    double PsiCorrectedB = psiB + 2*(-7.1318e-05)*SinB - 2*(-0.00178315)*CosB + (-0.0109081)*Sin2B - (0.00849651)*Cos2B + 0.5*(0.000535142)*Sin4B - 0.5*(0.000170353)*Cos4B;
    hPsi1correctedB->Fill(PsiCorrectedB);
    
    double BBCminusB = TMath::Cos(psi_e_s-PsiCorrectedB);
    double BBCminusA = TMath::Cos(psi_e_s-PsiCorrectedA);
    double AminusB = TMath::Cos(PsiCorrectedA-PsiCorrectedB);
    hAminusB->Fill(AminusB);
    hBBCminusB->Fill(BBCminusB);
    hBBCminusA->Fill(BBCminusA);
    
    
    for (int iLambda=0; iLambda<nLambda; iLambda++){
      Ntrk1=0; Ntrk2=0; Ntrk3=0; Qx1=0; Qy1=0; Qx2=0; Qy2=0; Qx3=0; Qy3=0;
      Weight1=0; Weight2=0; Weight3=0;
      for(int i = 0; i<Tracks_; i++){
        //      if(vis.count(Tracks_mId[i]) && vis[Tracks_mId[i]]) continue;
        if(Tracks_mId[i]==LProtonId[iLambda]) continue;
        if(TMath::Abs(Tracks_mNHitsFit[i]/(double)Tracks_mNHitsMax[i]) < 0.52) continue;
        if(Tracks_mNHitsDedx[0] <= 0) continue;
        if(TMath::Abs(Tracks_mNHitsFit[i]) < 10) continue;
        float charge = Tracks_mNHitsFit[i] > 0 ? 1 : -1;
        StThreeVectorD primMom = StThreeVectorD(Tracks_mPMomentum_mX1[i],Tracks_mPMomentum_mX2[i],Tracks_mPMomentum_mX3[i]);
        double pt = primMom.perp();
        double p = primMom.mag();
        if(p==0) continue;
        double eta  = primMom.pseudoRapidity();
        if(!gDeuterons){
          cout<<"Pointer to Bichsel graph is empty"<<endl;
          break;
        }
        double SigmaDeuteron = TMath::Log(Tracks_mDedx[i]*0.001) - gDeuterons->Eval(p);
        if(p > 0.3 && eta > -0.9 && eta < 0 && charge > 0){
          //        if(pt > 2) pt = 2;
          if(Tracks_mNSigmaProton[i] > -300 && Tracks_mNSigmaProton[i] < 300){
            double E = TMath::Sqrt(MASS_P*MASS_P+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx1 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy1 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            Weight1 += (y+1.5212)*pt;
            hProtonMidRapidity1->Fill(y+1.5212);
            Ntrk1++;
          }
          else if(p>0.4 && p<2 && SigmaDeuteron < 0.25 && SigmaDeuteron > -0.18){
            double E = TMath::Sqrt(1.877*1.877+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx1 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy1 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            hDeuteronMidRapidity1->Fill(y+1.5212);
            Weight1 += (y+1.5212)*pt;
            Ntrk1++;
          }
        }
        if(p > 0.3 && eta > -1.5 && eta < -0.9 && charge > 0){
          //        if(pt > 2) pt = 2;
          if(Tracks_mNSigmaProton[i] > -300 && Tracks_mNSigmaProton[i] < 300){
            double E = TMath::Sqrt(MASS_P*MASS_P+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx2 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy2 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            Weight2 += (y+1.5212)*pt;
            Ntrk2++;
          }
          else if(p>0.4 && p<2 && SigmaDeuteron < 0.25 && SigmaDeuteron > -0.18){
            double E = TMath::Sqrt(1.877*1.877+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx2 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy2 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            Weight2 += (y+1.5212)*pt;
            Ntrk2++;
          }
        }
        if(p > 0.3 && eta > -2 && eta < -1.5 && charge > 0){
          //        if(pt > 2) pt = 2;
          if(Tracks_mNSigmaProton[i] > -300 && Tracks_mNSigmaProton[i] < 300){
            double E = TMath::Sqrt(MASS_P*MASS_P+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx3 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy3 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            Weight3 += TMath::Abs(y+1.5212)*pt;
            Ntrk3++;
          }
          else if(p>0.4 && p<2 && SigmaDeuteron < 0.25 && SigmaDeuteron > -0.18){
            double E = TMath::Sqrt(1.877*1.877+p*p);
            double y = 0.5*TMath::Log((E+Tracks_mPMomentum_mX3[i])/(E-Tracks_mPMomentum_mX3[i]));
            Qx3 += (y+1.5212)*pt*TMath::Cos(primMom.phi());
            Qy3 += (y+1.5212)*pt*TMath::Sin(primMom.phi());
            Weight3 += TMath::Abs(y+1.5212)*pt;
            Ntrk3++;
          }
        }
      }
//      double qx1 = Qx1/(double)Ntrk1;
//      double qy1 = Qy1/(double)Ntrk1;
      if(Ntrk1 < 3 || Ntrk2 < 3) continue;
      if(Weight1==0 || Weight2==0) continue;
      
      double qx1 = (Weight1>0.0) ? Qx1/Weight1:0.;
      double qy1 = (Weight1>0.0) ? Qy1/Weight1:0;      //    cout<<qxA<<"  "<<qyA<<endl;
      //      double QxCorrected1 = (qx1 - 7.621833e-04)*Ntrk1;
      //      double QyCorrected1 = (qy1 - 4.415208e-02)*Ntrk1;
      double QxCorrected1 = qx1 - 2.396114e-03;
      double QyCorrected1 = qy1 - 3.669179e-02;
      hQxQy1->Fill(qx1,qy1);
      double psi1 = TMath::ATan2(QyCorrected1,QxCorrected1);
      hPsi11->Fill(psi1);
      double Sin1 = TMath::Sin(psi1);
      double Cos1 = TMath::Cos(psi1);
      double Sin21 = TMath::Sin(2*psi1);
      double Cos21 = TMath::Cos(2*psi1);
      double Sin41 = TMath::Sin(4*psi1);
      double Cos41 = TMath::Cos(4*psi1);
      double PsiCorrected1 = psi1 + 2*(0.000728618)*Sin1 - 2*(0.0141385)*Cos1 + (0.00389754)*Sin21 - (-0.000114574)*Cos21 + 0.5*(0.000399192)*Sin41 - 0.5*(-0.00117488)*Cos41;
      
      hPsi1corrected1->Fill(PsiCorrected1);
      
      //      double qx2 = Qx2/(double)Ntrk2;
      //      double qy2 = Qy2/(double)Ntrk2;
      double qx2 = (Weight2>0.0) ? Qx2/Weight2:0.;
      double qy2 = (Weight2>0.0) ? Qy2/Weight2:0.;
      //      double QxCorrected2 = (qx2 - 3.304400e-03)*Ntrk2;
      //      double QyCorrected2 = (qy2 - 8.247172e-03)*Ntrk2;
      double QxCorrected2 = qx2 + 1.661068e-04;
      double QyCorrected2 = qy2 - 5.864255e-03;
      hQxQy2->Fill(qx2,qy2);
      double psi2 = TMath::ATan2(QyCorrected2,QxCorrected2);
      hPsi12->Fill(psi2);
      double Sin2 = TMath::Sin(psi2);
      double Cos2 = TMath::Cos(psi2);
      double Sin22 = TMath::Sin(2*psi2);
      double Cos22 = TMath::Cos(2*psi2);
      double Sin42 = TMath::Sin(4*psi2);
      double Cos42 = TMath::Cos(4*psi2);
      double PsiCorrected2 = psi2 + 2*(-0.00181291)*Sin2 - 2*(0.000222814)*Cos2 + (-0.00830476)*Sin22 - (0.0118158)*Cos22 + 0.5*(-0.000783838)*Sin42 - 0.5*(0.0016496)*Cos42;

      hPsi1corrected2->Fill(PsiCorrected2);
      
      
//      double qx3 = Qx3/(double)Ntrk3;
//      double qy3 = Qy3/(double)Ntrk3;
      double qx3 = (Weight3>0.0) ? Qx3/Weight3:0.;
      double qy3 = (Weight3>0.0) ? Qy3/Weight3:0.;
//      double QxCorrected3 = (qx3 + 4.259928e-03)*Ntrk3;
//      double QyCorrected3 = (qy3 - 1.413188e-03)*Ntrk3;
      double QxCorrected3 = qx3 - 1.657905e-03;
      double QyCorrected3 = qy3 - 2.435806e-03;
      hQxQy3->Fill(qx3,qy3);
      double psi3 = TMath::ATan2(QyCorrected3,QxCorrected3);
      hPsi13->Fill(psi3);
      double Sin3 = TMath::Sin(psi3);
      double Cos3 = TMath::Cos(psi3);
      double Sin23 = TMath::Sin(2*psi3);
      double Cos23 = TMath::Cos(2*psi3);
      double Sin43 = TMath::Sin(4*psi3);
      double Cos43 = TMath::Cos(4*psi3);
      double PsiCorrected3 = psi3 + 2*(2.3319e-05)*Sin3 - 2*(-0.000243141)*Cos3 + (-0.0191275)*Sin23 - (0.00878631)*Cos23 + 0.5*(0.000702631)*Sin43 - 0.5*(0.000813679)*Cos43;
      hPsi1corrected3->Fill(PsiCorrected3);
      
      
      h1minus2->Fill(TMath::Cos(PsiCorrected1-PsiCorrected2));
      h1minus3->Fill(TMath::Cos(PsiCorrected1-PsiCorrected3));
      h2minus3->Fill(TMath::Cos(PsiCorrected2-PsiCorrected3));
      h1minusBBC->Fill(TMath::Cos(PsiCorrected1-psi_e_s));
      h2minusBBC->Fill(TMath::Cos(PsiCorrected2-psi_e_s));
      
      hNtrk1->Fill(Ntrk1);
      hNtrk2->Fill(Ntrk2);
      hNtrk3->Fill(Ntrk3);
      
      
      
      
      hBBCvsTpc1eventPlane->Fill(psi_e_s,PsiCorrected1);
      hV1vsM->Fill(LM[iLambda],TMath::Cos(LPhi[iLambda]-psi_e_s),LY[iLambda]);
      hV1tpc->Fill(LM[iLambda],TMath::Cos(LPhi[iLambda]-PsiCorrected1),LY[iLambda]);
      if(LY[iLambda]>-0.8 && LY[iLambda]<0){
        hV1vsMPt->Fill(LM[iLambda],TMath::Cos(LPhi[iLambda]-psi_e_s),LPt[iLambda]);
        hV1tpcPt->Fill(LM[iLambda],TMath::Cos(LPhi[iLambda]-PsiCorrected1),LPt[iLambda]);
      }
//      hPxvsM->Fill(LM[iLambda],LPt[iLambda]*TMath::Cos(LPhi[iLambda]-psi_e_s),LY[iLambda]);
    }

//    BufferPointer = (int)(2*(int)Event_mGRefMult[0]/2. + (int)(Event_mPrimaryVertex_mX3[0]-209.0)); //offset vz
    
//    BufferPointer = (int)mCentrality*62 + (int)((PsiCorrected + 0.5*TMath::Pi())*20);
    BufferPointer = (int)mCentrality; //offset vz
    hBufferPointer->Fill(BufferPointer);
    if(BufferPointer>=BUFFER_SIZE||BufferPointer<0) continue;
//    makeMixedPairs(BufferPointer, nProtons, pProton, nPions, pPion, priVtx, Event_mBField[0], mCentrality);
//    copyCurrentToBuffer(BufferPointer, nProtons, pProton, nPions, pPion, mCentrality);
  } //loop through events
  fileH->Write();
  cout<<"Buffer Pointer: "<<endl;
  for (int i=0; i<hBufferPointer->GetNbinsX(); i++) cout<<hBufferPointer->GetBinContent(i+1)<<" ";
} //mTree::Loop




//********************************** Mixing event ***********************************
void makeMixedPairs(int bufferPointer, int nP, Particle *pP, int nPi, Particle *pPi, StThreeVectorD primVtxPos, Float_t MagnetField, int centrality){
  TLorentzVector lvI, lvJ;
  for(int k = 0; k < BufferEvent_NEvents[bufferPointer]; k++){
    for(int i = 0; i < nP; i++){ // current protons
      //if (pP[i].GDCA < 0.8) continue; // get rid of primary tracks
      StPhysicalHelixD HelixI = pP[i].helix;
      StThreeVectorD p1 = pP[i].P;
      lvI.SetPtEtaPhiM(p1.perp(),p1.pseudoRapidity(),p1.phi(),MASS_P);
      for(int j=0; j<BufferEvent_nPions[k*BUFFER_SIZE+bufferPointer]; j++){ //buffer pions
        //if (BufEv_PionDca[k*BUFFER_SIZE+bufferPointer][j] < 1) continue;
        if (pP[i].Charge + BufEv_PionCharge[k*BUFFER_SIZE+bufferPointer][j] == 0) {
          lvJ.SetPtEtaPhiM(BufEv_PionMomVector[k*BUFFER_SIZE+bufferPointer][j].perp(),BufEv_PionMomVector[k*BUFFER_SIZE+bufferPointer][j].pseudoRapidity(),BufEv_PionMomVector[k*BUFFER_SIZE+bufferPointer][j].phi(),MASS_PI);
          TLorentzVector EstLV_Lambda = lvI + lvJ;
          if (EstLV_Lambda.M()>1.2) continue;
          StPhysicalHelixD HelixJ = BufEv_PionHelix[k*BUFFER_SIZE+bufferPointer][j];
          pair<double,double> pathLenghts = HelixI.pathLengths(HelixJ);
          StThreeVectorD pNegPosAtDca = HelixI.at(pathLenghts.first);
          StThreeVectorD pPosPosAtDca = HelixJ.at(pathLenghts.second);
          StThreeVectorD dcaVector = pNegPosAtDca-pPosPosAtDca;
          StThreeVectorD secVtxPos = pPosPosAtDca+(dcaVector*0.5);
          StThreeVectorD decLenVec = secVtxPos-primVtxPos;
          if (decLenVec.mag() < 8) continue; // cut on path length
          if (dcaVector.mag() > 1.2) continue; // cut on track mutual dca
          StThreeVectorD pNegMomAtDca = HelixI.momentumAt(pathLenghts.first, MagnetField * kilogauss);
          StThreeVectorD pPosMomAtDca = HelixJ.momentumAt(pathLenghts.second, MagnetField * kilogauss);
          StThreeVectorD LambdaMomAtDCA = pNegMomAtDca + pPosMomAtDca;;
          lvI.SetPtEtaPhiM(pNegMomAtDca.perp(),pNegMomAtDca.pseudoRapidity(),pNegMomAtDca.phi(),MASS_P);
          lvJ.SetPtEtaPhiM(pPosMomAtDca.perp(),pPosMomAtDca.pseudoRapidity(),pPosMomAtDca.phi(),MASS_PI);
          TLorentzVector LV_Lambda = lvI + lvJ;
          double pointingAngle = LambdaMomAtDCA.angle(decLenVec);
          double LambdaDCAtoPrimVtx  = TMath::Abs(decLenVec.mag()*TMath::Sin(pointingAngle));
          if (TMath::Abs(pointingAngle) > 0.06) continue; // cut on pointing angle
          if (LambdaDCAtoPrimVtx > 0.5) continue;
          hMixedVsY->Fill(LV_Lambda.Rapidity(),LV_Lambda.M());
        } // opposite sign condition
      } // loop j
    } // loop i
    for(int i = 0; i < nPi; i++){ // current pions
      //if (pPi[i].GDCA < 1) continue; // get rid of primary tracks
      StPhysicalHelixD HelixI = pPi[i].helix;
      StThreeVectorD p1 = pPi[i].P;
      lvI.SetPtEtaPhiM(p1.perp(),p1.pseudoRapidity(),p1.phi(),MASS_PI);
      for(int j=0; j<BufferEvent_nProtons[k*BUFFER_SIZE+bufferPointer]; j++){ //buffer protons
        //if (BufEv_ProtonDca[k*BUFFER_SIZE+bufferPointer][j] < 0.8) continue;
        if (pPi[i].Charge + BufEv_ProtonCharge[k*BUFFER_SIZE+bufferPointer][j] == 0) {
          lvJ.SetPtEtaPhiM(BufEv_ProtonMomVector[k*BUFFER_SIZE+bufferPointer][j].perp(),BufEv_ProtonMomVector[k*BUFFER_SIZE+bufferPointer][j].pseudoRapidity(),BufEv_ProtonMomVector[k*BUFFER_SIZE+bufferPointer][j].phi(),MASS_P);
          TLorentzVector EstLV_Lambda = lvI + lvJ;
          if (EstLV_Lambda.M()>1.2) continue;
          StPhysicalHelixD HelixJ = BufEv_ProtonHelix[k*BUFFER_SIZE+bufferPointer][j];
          pair<double,double> pathLenghts = HelixI.pathLengths(HelixJ);
          StThreeVectorD pNegPosAtDca = HelixI.at(pathLenghts.first);
          StThreeVectorD pPosPosAtDca = HelixJ.at(pathLenghts.second);
          StThreeVectorD dcaVector = pNegPosAtDca-pPosPosAtDca;
          StThreeVectorD secVtxPos = pPosPosAtDca+(dcaVector*0.5);
          StThreeVectorD decLenVec = secVtxPos-primVtxPos;
          if (decLenVec.mag() < 8) continue; // cut on path length
          if (dcaVector.mag() > 1.2) continue; // cut on track mutual dca
          StThreeVectorD pNegMomAtDca = HelixI.momentumAt(pathLenghts.first, MagnetField * kilogauss);
          StThreeVectorD pPosMomAtDca = HelixJ.momentumAt(pathLenghts.second, MagnetField * kilogauss);
          StThreeVectorD LambdaMomAtDCA = pNegMomAtDca + pPosMomAtDca;;
          lvI.SetPtEtaPhiM(pNegMomAtDca.perp(),pNegMomAtDca.pseudoRapidity(),pNegMomAtDca.phi(),MASS_P);
          lvJ.SetPtEtaPhiM(pPosMomAtDca.perp(),pPosMomAtDca.pseudoRapidity(),pPosMomAtDca.phi(),MASS_PI);
          TLorentzVector LV_Lambda = lvI + lvJ;
          double pointingAngle = LambdaMomAtDCA.angle(decLenVec);
          double LambdaDCAtoPrimVtx  = TMath::Abs(decLenVec.mag()*TMath::Sin(pointingAngle));
          if (TMath::Abs(pointingAngle) > 0.06) continue; // cut on pointing angle
          if (LambdaDCAtoPrimVtx > 0.5) continue;
          hMixedVsY->Fill(LV_Lambda.Rapidity(),LV_Lambda.M());
        } // opposite sign condition
      } // loop j
    } // loop i
  } // loop k
  return;
}

//_____________________________________________________________________
void copyCurrentToBuffer(int bufferPointer, int nP, Particle *pP, int nPi, Particle *pPi, int centrality){
//  cout<<BufferEvent_NEvents[bufferPointer]<<endl;
  if(BufferEvent_NEvents[bufferPointer]>=20) {
    BufferEvent_Full[bufferPointer]=1;
  }
  TRandom3 *gRandom = new TRandom3(iran++);
  int eventPointer = -1;
  if(BufferEvent_Full[bufferPointer]) { // full - random rewrite one
    do {
      double rrr = gRandom->Rndm();
      eventPointer = (int)(20.*(1.0 - rrr));
    } while(eventPointer<0||eventPointer>=20);
  } else eventPointer = BufferEvent_NEvents[bufferPointer]; // not full
  delete gRandom;
  gRandom = NULL;
  BufferEvent_nPions[bufferPointer+BUFFER_SIZE*eventPointer]=nPi;
  BufferEvent_nProtons[bufferPointer+BUFFER_SIZE*eventPointer]=nP;
  BufferEvent_Centrality[bufferPointer+BUFFER_SIZE*eventPointer] = centrality;
  hIndexToEvent->Fill(bufferPointer+BUFFER_SIZE*eventPointer);
  for(int i=0; i<nP; i++){
    BufEv_ProtonCharge[bufferPointer+BUFFER_SIZE*eventPointer][i] = pP[i].Charge;
    BufEv_ProtonHelix[bufferPointer+BUFFER_SIZE*eventPointer][i] = pP[i].helix;
    BufEv_ProtonMomVector[bufferPointer+BUFFER_SIZE*eventPointer][i] = pP[i].P;
    BufEv_ProtonDca[bufferPointer+BUFFER_SIZE*eventPointer][i] = pP[i].GDCA;
  }
  for(int i=0; i<nPi; i++){
    BufEv_PionCharge[bufferPointer+BUFFER_SIZE*eventPointer][i] = pPi[i].Charge;
    BufEv_PionHelix[bufferPointer+BUFFER_SIZE*eventPointer][i] = pPi[i].helix;
    BufEv_PionMomVector[bufferPointer+BUFFER_SIZE*eventPointer][i] = pPi[i].P;
    BufEv_PionDca[bufferPointer+BUFFER_SIZE*eventPointer][i] = pPi[i].GDCA;
  }
  if(BufferEvent_NEvents[bufferPointer]<20) BufferEvent_NEvents[bufferPointer]+=1;
}



PicoDst::PicoDst(TTree *tree, Char_t *output)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("st_mtd_15089023_raw_4500029.picoDst.root");
    if (!f) {
      f = new TFile("st_mtd_15089023_raw_4500029.picoDst.root");
    }
    tree = (TTree*)gDirectory->Get("PicoDst");
  }
  outputFile = output;
  Init(tree,outputFile);
}

PicoDst::~PicoDst()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t PicoDst::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t PicoDst::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void PicoDst::Init(TTree *tree, Char_t *outputFile)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  TFile *fLnDedx = new TFile("/macstar/star3/tlusty/FixedTarget/BichselGraphs.root");
//  TFile *fLnDedx = new TFile("BichselGraphs.root");
  gDeuterons = (TGraph*)fLnDedx->Get("deuterons");
  
  fLnDedx->Close();
//  TFile *fPhi = new TFile("/data/star3/tlusty/FixedTarget/PhiWeights.root");
////  TFile *fPhi = new TFile("PhiWeights.root");
//  if(fPhi == NULL) {
//    cout<<"Can't find PhiWeights.root"<<endl;
//    return;
//  }
//  hwPhi = (TH1D*)fPhi->Get("wPhi");
//  hwPhiA = (TH1D*)fPhi->Get("wPhiA");
//  hwPhiB = (TH1D*)fPhi->Get("wPhiB");
//  hwPhi->SetDirectory(0);
//  hwPhiA->SetDirectory(0);
//  hwPhiB->SetDirectory(0);
//  
//  
//  fPhi->Close();
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  fileH = new TFile(outputFile,"RECREATE");
  
  fChain->SetBranchAddress("Event", &Event_, &b_Event_);
  fChain->SetBranchAddress("Event.mRunId", Event_mRunId, &b_Event_mRunId);
  fChain->SetBranchAddress("Event.mEventId", Event_mEventId, &b_Event_mEventId);
  fChain->SetBranchAddress("Event.mFillId", Event_mFillId, &b_Event_mFillId);
  fChain->SetBranchAddress("Event.mBField", Event_mBField, &b_Event_mBField);
  fChain->SetBranchAddress("Event.mPrimaryVertex.mX1", Event_mPrimaryVertex_mX1, &b_Event_mPrimaryVertex_mX1);
  fChain->SetBranchAddress("Event.mPrimaryVertex.mX2", Event_mPrimaryVertex_mX2, &b_Event_mPrimaryVertex_mX2);
  fChain->SetBranchAddress("Event.mPrimaryVertex.mX3", Event_mPrimaryVertex_mX3, &b_Event_mPrimaryVertex_mX3);
  fChain->SetBranchAddress("Event.mSecondVertex.mX1", Event_mSecondVertex_mX1, &b_Event_mSecondVertex_mX1);
  fChain->SetBranchAddress("Event.mSecondVertex.mX2", Event_mSecondVertex_mX2, &b_Event_mSecondVertex_mX2);
  fChain->SetBranchAddress("Event.mSecondVertex.mX3", Event_mSecondVertex_mX3, &b_Event_mSecondVertex_mX3);
  fChain->SetBranchAddress("Event.mPrimaryVertexError.mX1", Event_mPrimaryVertexError_mX1, &b_Event_mPrimaryVertexError_mX1);
  fChain->SetBranchAddress("Event.mPrimaryVertexError.mX2", Event_mPrimaryVertexError_mX2, &b_Event_mPrimaryVertexError_mX2);
  fChain->SetBranchAddress("Event.mPrimaryVertexError.mX3", Event_mPrimaryVertexError_mX3, &b_Event_mPrimaryVertexError_mX3);
  fChain->SetBranchAddress("Event.mVertexIndex", Event_mVertexIndex, &b_Event_mVertexIndex);
  fChain->SetBranchAddress("Event.mTriggerWord", Event_mTriggerWord, &b_Event_mTriggerWord);
  fChain->SetBranchAddress("Event.mTriggerWordMtd", Event_mTriggerWordMtd, &b_Event_mTriggerWordMtd);
  fChain->SetBranchAddress("Event.mRefMultFtpcEast", Event_mRefMultFtpcEast, &b_Event_mRefMultFtpcEast);
  fChain->SetBranchAddress("Event.mRefMultFtpcWest", Event_mRefMultFtpcWest, &b_Event_mRefMultFtpcWest);
  fChain->SetBranchAddress("Event.mRefMultNeg", Event_mRefMultNeg, &b_Event_mRefMultNeg);
  fChain->SetBranchAddress("Event.mRefMultPos", Event_mRefMultPos, &b_Event_mRefMultPos);
  fChain->SetBranchAddress("Event.mRefMult2NegEast", Event_mRefMult2NegEast, &b_Event_mRefMult2NegEast);
  fChain->SetBranchAddress("Event.mRefMult2PosEast", Event_mRefMult2PosEast, &b_Event_mRefMult2PosEast);
  fChain->SetBranchAddress("Event.mRefMult2NegWest", Event_mRefMult2NegWest, &b_Event_mRefMult2NegWest);
  fChain->SetBranchAddress("Event.mRefMult2PosWest", Event_mRefMult2PosWest, &b_Event_mRefMult2PosWest);
  fChain->SetBranchAddress("Event.mRefMultHalfNegEast", Event_mRefMultHalfNegEast, &b_Event_mRefMultHalfNegEast);
  fChain->SetBranchAddress("Event.mRefMultHalfPosEast", Event_mRefMultHalfPosEast, &b_Event_mRefMultHalfPosEast);
  fChain->SetBranchAddress("Event.mRefMultHalfNegWest", Event_mRefMultHalfNegWest, &b_Event_mRefMultHalfNegWest);
  fChain->SetBranchAddress("Event.mRefMultHalfPosWest", Event_mRefMultHalfPosWest, &b_Event_mRefMultHalfPosWest);
  fChain->SetBranchAddress("Event.mGRefMult", Event_mGRefMult, &b_Event_mGRefMult);
  fChain->SetBranchAddress("Event.mNHitsHFT[4]", Event_mNHitsHFT, &b_Event_mNHitsHFT);
  fChain->SetBranchAddress("Event.mNVpdHitsEast", Event_mNVpdHitsEast, &b_Event_mNVpdHitsEast);
  fChain->SetBranchAddress("Event.mNVpdHitsWest", Event_mNVpdHitsWest, &b_Event_mNVpdHitsWest);
  fChain->SetBranchAddress("Event.mNT0", Event_mNT0, &b_Event_mNT0);
  fChain->SetBranchAddress("Event.mVzVpd", Event_mVzVpd, &b_Event_mVzVpd);
  fChain->SetBranchAddress("Event.mZDCx", Event_mZDCx, &b_Event_mZDCx);
  fChain->SetBranchAddress("Event.mBBCx", Event_mBBCx, &b_Event_mBBCx);
  fChain->SetBranchAddress("Event.mBackgroundRate", Event_mBackgroundRate, &b_Event_mBackgroundRate);
  fChain->SetBranchAddress("Event.mBbcBlueBackgroundRate", Event_mBbcBlueBackgroundRate, &b_Event_mBbcBlueBackgroundRate);
  fChain->SetBranchAddress("Event.mBbcYellowBackgroundRate", Event_mBbcYellowBackgroundRate, &b_Event_mBbcYellowBackgroundRate);
  fChain->SetBranchAddress("Event.mBbcEastRate", Event_mBbcEastRate, &b_Event_mBbcEastRate);
  fChain->SetBranchAddress("Event.mBbcWestRate", Event_mBbcWestRate, &b_Event_mBbcWestRate);
  fChain->SetBranchAddress("Event.mZdcEastRate", Event_mZdcEastRate, &b_Event_mZdcEastRate);
  fChain->SetBranchAddress("Event.mZdcWestRate", Event_mZdcWestRate, &b_Event_mZdcWestRate);
  fChain->SetBranchAddress("Event.mVpd[64]", Event_mVpd, &b_Event_mVpd);
  fChain->SetBranchAddress("Event.mZdcSumAdcEast", Event_mZdcSumAdcEast, &b_Event_mZdcSumAdcEast);
  fChain->SetBranchAddress("Event.mZdcSumAdcWest", Event_mZdcSumAdcWest, &b_Event_mZdcSumAdcWest);
  fChain->SetBranchAddress("Event.mZdcSmdEastHorizontal[8]", Event_mZdcSmdEastHorizontal, &b_Event_mZdcSmdEastHorizontal);
  fChain->SetBranchAddress("Event.mZdcSmdEastVertical[8]", Event_mZdcSmdEastVertical, &b_Event_mZdcSmdEastVertical);
  fChain->SetBranchAddress("Event.mZdcSmdWestHorizontal[8]", Event_mZdcSmdWestHorizontal, &b_Event_mZdcSmdWestHorizontal);
  fChain->SetBranchAddress("Event.mZdcSmdWestVertical[8]", Event_mZdcSmdWestVertical, &b_Event_mZdcSmdWestVertical);
  fChain->SetBranchAddress("Event.mSpaceCharge", Event_mSpaceCharge, &b_Event_mSpaceCharge);
  fChain->SetBranchAddress("Event.mbTofTrayMultiplicity", Event_mbTofTrayMultiplicity, &b_Event_mbTofTrayMultiplicity);
  fChain->SetBranchAddress("Event.mNumberOfGlobalTracks", Event_mNumberOfGlobalTracks, &b_Event_mNumberOfGlobalTracks);
  fChain->SetBranchAddress("Event.mRanking", Event_mRanking, &b_Event_mRanking);
  fChain->SetBranchAddress("Event.mNBEMCMatch", Event_mNBEMCMatch, &b_Event_mNBEMCMatch);
  fChain->SetBranchAddress("Event.mNBTOFMatch", Event_mNBTOFMatch, &b_Event_mNBTOFMatch);
  fChain->SetBranchAddress("Event.mBbcAdcEast[24]", Event_mBbcAdcEast, &b_Event_mBbcAdcEast);
  fChain->SetBranchAddress("Event.mBbcAdcWest[24]", Event_mBbcAdcWest, &b_Event_mBbcAdcWest);
  fChain->SetBranchAddress("Event.mHT_Th[4]", Event_mHT_Th, &b_Event_mHT_Th);
  fChain->SetBranchAddress("Event.mJP_Th[4]", Event_mJP_Th, &b_Event_mJP_Th);
  fChain->SetBranchAddress("EventPlane", &EventPlane_, &b_EventPlane_);
  fChain->SetBranchAddress("EventPlane.fUniqueID", EventPlane_fUniqueID, &b_EventPlane_fUniqueID);
  fChain->SetBranchAddress("EventPlane.fBits", EventPlane_fBits, &b_EventPlane_fBits);
  fChain->SetBranchAddress("EventPlane.mQx_eta_pos", EventPlane_mQx_eta_pos, &b_EventPlane_mQx_eta_pos);
  fChain->SetBranchAddress("EventPlane.mQy_eta_pos", EventPlane_mQy_eta_pos, &b_EventPlane_mQy_eta_pos);
  fChain->SetBranchAddress("EventPlane.mQx_eta_neg", EventPlane_mQx_eta_neg, &b_EventPlane_mQx_eta_neg);
  fChain->SetBranchAddress("EventPlane.mQy_eta_neg", EventPlane_mQy_eta_neg, &b_EventPlane_mQy_eta_neg);
  fChain->SetBranchAddress("EventPlane.mNtrk_eta_pos", EventPlane_mNtrk_eta_pos, &b_EventPlane_mNtrk_eta_pos);
  fChain->SetBranchAddress("EventPlane.mNtrk_eta_neg", EventPlane_mNtrk_eta_neg, &b_EventPlane_mNtrk_eta_neg);
  fChain->SetBranchAddress("EventPlane.mWeight_eta_pos", EventPlane_mWeight_eta_pos, &b_EventPlane_mWeight_eta_pos);
  fChain->SetBranchAddress("EventPlane.mWeight_eta_neg", EventPlane_mWeight_eta_neg, &b_EventPlane_mWeight_eta_neg);
  fChain->SetBranchAddress("EventPlane.mQx_chg_pos", EventPlane_mQx_chg_pos, &b_EventPlane_mQx_chg_pos);
  fChain->SetBranchAddress("EventPlane.mQy_chg_pos", EventPlane_mQy_chg_pos, &b_EventPlane_mQy_chg_pos);
  fChain->SetBranchAddress("EventPlane.mQx_chg_neg", EventPlane_mQx_chg_neg, &b_EventPlane_mQx_chg_neg);
  fChain->SetBranchAddress("EventPlane.mQy_chg_neg", EventPlane_mQy_chg_neg, &b_EventPlane_mQy_chg_neg);
  fChain->SetBranchAddress("EventPlane.mNtrk_chg_pos_eta_pos", EventPlane_mNtrk_chg_pos_eta_pos, &b_EventPlane_mNtrk_chg_pos_eta_pos);
  fChain->SetBranchAddress("EventPlane.mNtrk_chg_pos_eta_neg", EventPlane_mNtrk_chg_pos_eta_neg, &b_EventPlane_mNtrk_chg_pos_eta_neg);
  fChain->SetBranchAddress("EventPlane.mNtrk_chg_neg_eta_pos", EventPlane_mNtrk_chg_neg_eta_pos, &b_EventPlane_mNtrk_chg_neg_eta_pos);
  fChain->SetBranchAddress("EventPlane.mNtrk_chg_neg_eta_neg", EventPlane_mNtrk_chg_neg_eta_neg, &b_EventPlane_mNtrk_chg_neg_eta_neg);
  fChain->SetBranchAddress("EventPlane.mWeight_chg_pos", EventPlane_mWeight_chg_pos, &b_EventPlane_mWeight_chg_pos);
  fChain->SetBranchAddress("EventPlane.mWeight_chg_neg", EventPlane_mWeight_chg_neg, &b_EventPlane_mWeight_chg_neg);
  fChain->SetBranchAddress("EventPlane.mQx_ran_1", EventPlane_mQx_ran_1, &b_EventPlane_mQx_ran_1);
  fChain->SetBranchAddress("EventPlane.mQy_ran_1", EventPlane_mQy_ran_1, &b_EventPlane_mQy_ran_1);
  fChain->SetBranchAddress("EventPlane.mQx_ran_2", EventPlane_mQx_ran_2, &b_EventPlane_mQx_ran_2);
  fChain->SetBranchAddress("EventPlane.mQy_ran_2", EventPlane_mQy_ran_2, &b_EventPlane_mQy_ran_2);
  fChain->SetBranchAddress("EventPlane.mNtrk_ran_1_eta_pos", EventPlane_mNtrk_ran_1_eta_pos, &b_EventPlane_mNtrk_ran_1_eta_pos);
  fChain->SetBranchAddress("EventPlane.mNtrk_ran_1_eta_neg", EventPlane_mNtrk_ran_1_eta_neg, &b_EventPlane_mNtrk_ran_1_eta_neg);
  fChain->SetBranchAddress("EventPlane.mNtrk_ran_2_eta_pos", EventPlane_mNtrk_ran_2_eta_pos, &b_EventPlane_mNtrk_ran_2_eta_pos);
  fChain->SetBranchAddress("EventPlane.mNtrk_ran_2_eta_neg", EventPlane_mNtrk_ran_2_eta_neg, &b_EventPlane_mNtrk_ran_2_eta_neg);
  fChain->SetBranchAddress("EventPlane.mWeight_ran_1", EventPlane_mWeight_ran_1, &b_EventPlane_mWeight_ran_1);
  fChain->SetBranchAddress("EventPlane.mWeight_ran_2", EventPlane_mWeight_ran_2, &b_EventPlane_mWeight_ran_2);
  fChain->SetBranchAddress("Tracks", &Tracks_, &b_Tracks_);
  fChain->SetBranchAddress("Tracks.mId", Tracks_mId, &b_Tracks_mId);
  fChain->SetBranchAddress("Tracks.mChi2", Tracks_mChi2, &b_Tracks_mChi2);
  fChain->SetBranchAddress("Tracks.mPMomentum.mX1", Tracks_mPMomentum_mX1, &b_Tracks_mPMomentum_mX1);
  fChain->SetBranchAddress("Tracks.mPMomentum.mX2", Tracks_mPMomentum_mX2, &b_Tracks_mPMomentum_mX2);
  fChain->SetBranchAddress("Tracks.mPMomentum.mX3", Tracks_mPMomentum_mX3, &b_Tracks_mPMomentum_mX3);
  fChain->SetBranchAddress("Tracks.mDedx", Tracks_mDedx, &b_Tracks_mDedx);
  fChain->SetBranchAddress("Tracks.mNHitsFit", Tracks_mNHitsFit, &b_Tracks_mNHitsFit);
  fChain->SetBranchAddress("Tracks.mNHitsMax", Tracks_mNHitsMax, &b_Tracks_mNHitsMax);
  fChain->SetBranchAddress("Tracks.mNHitsDedx", Tracks_mNHitsDedx, &b_Tracks_mNHitsDedx);
  fChain->SetBranchAddress("Tracks.mNSigmaPion", Tracks_mNSigmaPion, &b_Tracks_mNSigmaPion);
  fChain->SetBranchAddress("Tracks.mNSigmaKaon", Tracks_mNSigmaKaon, &b_Tracks_mNSigmaKaon);
  fChain->SetBranchAddress("Tracks.mNSigmaProton", Tracks_mNSigmaProton, &b_Tracks_mNSigmaProton);
  fChain->SetBranchAddress("Tracks.mNSigmaElectron", Tracks_mNSigmaElectron, &b_Tracks_mNSigmaElectron);
  fChain->SetBranchAddress("Tracks.mMap0", Tracks_mMap0, &b_Tracks_mMap0);
  fChain->SetBranchAddress("Tracks.mMap1", Tracks_mMap1, &b_Tracks_mMap1);
  fChain->SetBranchAddress("Tracks.mPar[6]", Tracks_mPar, &b_Tracks_mPar);
  fChain->SetBranchAddress("Tracks.mErrMatrix[15]", Tracks_mErrMatrix, &b_Tracks_mErrMatrix);
  fChain->SetBranchAddress("Tracks.mEmcPidTraitsIndex", Tracks_mEmcPidTraitsIndex, &b_Tracks_mEmcPidTraitsIndex);
  fChain->SetBranchAddress("Tracks.mBTofPidTraitsIndex", Tracks_mBTofPidTraitsIndex, &b_Tracks_mBTofPidTraitsIndex);
  fChain->SetBranchAddress("Tracks.mMtdPidTraitsIndex", Tracks_mMtdPidTraitsIndex, &b_Tracks_mMtdPidTraitsIndex);
  fChain->SetBranchAddress("EmcTrigger", &EmcTrigger_, &b_EmcTrigger_);
  fChain->SetBranchAddress("EmcTrigger.fUniqueID", EmcTrigger_fUniqueID, &b_EmcTrigger_fUniqueID);
  fChain->SetBranchAddress("EmcTrigger.fBits", EmcTrigger_fBits, &b_EmcTrigger_fBits);
  fChain->SetBranchAddress("EmcTrigger.mFlag", EmcTrigger_mFlag, &b_EmcTrigger_mFlag);
  fChain->SetBranchAddress("EmcTrigger.mId", EmcTrigger_mId, &b_EmcTrigger_mId);
  fChain->SetBranchAddress("EmcTrigger.mAdc", EmcTrigger_mAdc, &b_EmcTrigger_mAdc);
  fChain->SetBranchAddress("MtdTrigger", &MtdTrigger_, &b_MtdTrigger_);
  fChain->SetBranchAddress("MtdTrigger.fUniqueID", MtdTrigger_fUniqueID, &b_MtdTrigger_fUniqueID);
  fChain->SetBranchAddress("MtdTrigger.fBits", MtdTrigger_fBits, &b_MtdTrigger_fBits);
  fChain->SetBranchAddress("MtdTrigger.mQTtacSum[4][8]", MtdTrigger_mQTtacSum, &b_MtdTrigger_mQTtacSum);
  fChain->SetBranchAddress("MtdTrigger.mMT101Tac[4][2]", MtdTrigger_mMT101Tac, &b_MtdTrigger_mMT101Tac);
  fChain->SetBranchAddress("MtdTrigger.mMT101Id[4][2]", MtdTrigger_mMT101Id, &b_MtdTrigger_mMT101Id);
  fChain->SetBranchAddress("MtdTrigger.mTF201TriggerBit", MtdTrigger_mTF201TriggerBit, &b_MtdTrigger_mTF201TriggerBit);
  fChain->SetBranchAddress("MtdTrigger.mShouldHaveRejectEvent", MtdTrigger_mShouldHaveRejectEvent, &b_MtdTrigger_mShouldHaveRejectEvent);
  fChain->SetBranchAddress("BTOWHit", &BTOWHit_, &b_BTOWHit_);
  fChain->SetBranchAddress("BTOWHit.fUniqueID", &BTOWHit_fUniqueID, &b_BTOWHit_fUniqueID);
  fChain->SetBranchAddress("BTOWHit.fBits", &BTOWHit_fBits, &b_BTOWHit_fBits);
  fChain->SetBranchAddress("BTOWHit.mId", &BTOWHit_mId, &b_BTOWHit_mId);
  fChain->SetBranchAddress("BTOWHit.mAdc", &BTOWHit_mAdc, &b_BTOWHit_mAdc);
  fChain->SetBranchAddress("BTOWHit.mE", &BTOWHit_mE, &b_BTOWHit_mE);
  fChain->SetBranchAddress("BTofHit", &BTofHit_, &b_BTofHit_);
  fChain->SetBranchAddress("BTofHit.fUniqueID", &BTofHit_fUniqueID, &b_BTofHit_fUniqueID);
  fChain->SetBranchAddress("BTofHit.fBits", &BTofHit_fBits, &b_BTofHit_fBits);
  fChain->SetBranchAddress("BTofHit.mId", &BTofHit_mId, &b_BTofHit_mId);
  fChain->SetBranchAddress("MtdHit", &MtdHit_, &b_MtdHit_);
  fChain->SetBranchAddress("MtdHit.fUniqueID", MtdHit_fUniqueID, &b_MtdHit_fUniqueID);
  fChain->SetBranchAddress("MtdHit.fBits", MtdHit_fBits, &b_MtdHit_fBits);
  fChain->SetBranchAddress("MtdHit.mgChannel", MtdHit_mgChannel, &b_MtdHit_mgChannel);
  fChain->SetBranchAddress("MtdHit.mTriggerFlag", MtdHit_mTriggerFlag, &b_MtdHit_mTriggerFlag);
  fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.first", MtdHit_mLeadingEdgeTime_first, &b_MtdHit_mLeadingEdgeTime_first);
  fChain->SetBranchAddress("MtdHit.mLeadingEdgeTime.second", MtdHit_mLeadingEdgeTime_second, &b_MtdHit_mLeadingEdgeTime_second);
  fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.first", MtdHit_mTrailingEdgeTime_first, &b_MtdHit_mTrailingEdgeTime_first);
  fChain->SetBranchAddress("MtdHit.mTrailingEdgeTime.second", MtdHit_mTrailingEdgeTime_second, &b_MtdHit_mTrailingEdgeTime_second);
  fChain->SetBranchAddress("EmcPidTraits", &EmcPidTraits_, &b_EmcPidTraits_);
  fChain->SetBranchAddress("EmcPidTraits.fUniqueID", EmcPidTraits_fUniqueID, &b_EmcPidTraits_fUniqueID);
  fChain->SetBranchAddress("EmcPidTraits.fBits", EmcPidTraits_fBits, &b_EmcPidTraits_fBits);
  fChain->SetBranchAddress("EmcPidTraits.mTrackIndex", EmcPidTraits_mTrackIndex, &b_EmcPidTraits_mTrackIndex);
  fChain->SetBranchAddress("EmcPidTraits.mBEMCId", EmcPidTraits_mBEMCId, &b_EmcPidTraits_mBEMCId);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWADC0", EmcPidTraits_mBTOWADC0, &b_EmcPidTraits_mBTOWADC0);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWE0", EmcPidTraits_mBTOWE0, &b_EmcPidTraits_mBTOWE0);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWE", EmcPidTraits_mBTOWE, &b_EmcPidTraits_mBTOWE);
  fChain->SetBranchAddress("EmcPidTraits.mBEMCDistZ", EmcPidTraits_mBEMCDistZ, &b_EmcPidTraits_mBEMCDistZ);
  fChain->SetBranchAddress("EmcPidTraits.mBEMCDistPhi", EmcPidTraits_mBEMCDistPhi, &b_EmcPidTraits_mBEMCDistPhi);
  fChain->SetBranchAddress("EmcPidTraits.mBSMDNEta", EmcPidTraits_mBSMDNEta, &b_EmcPidTraits_mBSMDNEta);
  fChain->SetBranchAddress("EmcPidTraits.mBSMDNPhi", EmcPidTraits_mBSMDNPhi, &b_EmcPidTraits_mBSMDNPhi);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWId", EmcPidTraits_mBTOWId, &b_EmcPidTraits_mBTOWId);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWId23", EmcPidTraits_mBTOWId23, &b_EmcPidTraits_mBTOWId23);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWE1", EmcPidTraits_mBTOWE1, &b_EmcPidTraits_mBTOWE1);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWE2", EmcPidTraits_mBTOWE2, &b_EmcPidTraits_mBTOWE2);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWE3", EmcPidTraits_mBTOWE3, &b_EmcPidTraits_mBTOWE3);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWDistEta", EmcPidTraits_mBTOWDistEta, &b_EmcPidTraits_mBTOWDistEta);
  fChain->SetBranchAddress("EmcPidTraits.mBTOWDistPhi", EmcPidTraits_mBTOWDistPhi, &b_EmcPidTraits_mBTOWDistPhi);
  fChain->SetBranchAddress("BTofPidTraits", &BTofPidTraits_, &b_BTofPidTraits_);
  fChain->SetBranchAddress("BTofPidTraits.fUniqueID", BTofPidTraits_fUniqueID, &b_BTofPidTraits_fUniqueID);
  fChain->SetBranchAddress("BTofPidTraits.fBits", BTofPidTraits_fBits, &b_BTofPidTraits_fBits);
  fChain->SetBranchAddress("BTofPidTraits.mTrackIndex", BTofPidTraits_mTrackIndex, &b_BTofPidTraits_mTrackIndex);
  fChain->SetBranchAddress("BTofPidTraits.mBTofCellId", BTofPidTraits_mBTofCellId, &b_BTofPidTraits_mBTofCellId);
  fChain->SetBranchAddress("BTofPidTraits.mBTofMatchFlag", BTofPidTraits_mBTofMatchFlag, &b_BTofPidTraits_mBTofMatchFlag);
  fChain->SetBranchAddress("BTofPidTraits.mBTof", BTofPidTraits_mBTof, &b_BTofPidTraits_mBTof);
  fChain->SetBranchAddress("BTofPidTraits.mBTofBeta", BTofPidTraits_mBTofBeta, &b_BTofPidTraits_mBTofBeta);
  fChain->SetBranchAddress("BTofPidTraits.mBTofYLocal", BTofPidTraits_mBTofYLocal, &b_BTofPidTraits_mBTofYLocal);
  fChain->SetBranchAddress("BTofPidTraits.mBTofZLocal", BTofPidTraits_mBTofZLocal, &b_BTofPidTraits_mBTofZLocal);
  fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosX", BTofPidTraits_mBTofHitPosX, &b_BTofPidTraits_mBTofHitPosX);
  fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosY", BTofPidTraits_mBTofHitPosY, &b_BTofPidTraits_mBTofHitPosY);
  fChain->SetBranchAddress("BTofPidTraits.mBTofHitPosZ", BTofPidTraits_mBTofHitPosZ, &b_BTofPidTraits_mBTofHitPosZ);
  fChain->SetBranchAddress("MtdPidTraits", &MtdPidTraits_, &b_MtdPidTraits_);
  fChain->SetBranchAddress("MtdPidTraits.fUniqueID", MtdPidTraits_fUniqueID, &b_MtdPidTraits_fUniqueID);
  fChain->SetBranchAddress("MtdPidTraits.fBits", MtdPidTraits_fBits, &b_MtdPidTraits_fBits);
  fChain->SetBranchAddress("MtdPidTraits.mMtdHitChan", MtdPidTraits_mMtdHitChan, &b_MtdPidTraits_mMtdHitChan);
  fChain->SetBranchAddress("MtdPidTraits.mTrackIndex", MtdPidTraits_mTrackIndex, &b_MtdPidTraits_mTrackIndex);
  fChain->SetBranchAddress("MtdPidTraits.mMatchFlag", MtdPidTraits_mMatchFlag, &b_MtdPidTraits_mMatchFlag);
  fChain->SetBranchAddress("MtdPidTraits.mDeltaY", MtdPidTraits_mDeltaY, &b_MtdPidTraits_mDeltaY);
  fChain->SetBranchAddress("MtdPidTraits.mDeltaZ", MtdPidTraits_mDeltaZ, &b_MtdPidTraits_mDeltaZ);
  fChain->SetBranchAddress("MtdPidTraits.mDeltaTimeOfFlight", MtdPidTraits_mDeltaTimeOfFlight, &b_MtdPidTraits_mDeltaTimeOfFlight);
  fChain->SetBranchAddress("MtdPidTraits.mBeta", MtdPidTraits_mBeta, &b_MtdPidTraits_mBeta);
  fChain->SetBranchAddress("V0Ks", &V0Ks_, &b_V0Ks_);
  fChain->SetBranchAddress("V0Ks.mIndex2Track[2]", &V0Ks_mIndex2Track, &b_V0Ks_mIndex2Track);
  fChain->SetBranchAddress("V0Ks.mV0Pos.mX1", &V0Ks_mV0Pos_mX1, &b_V0Ks_mV0Pos_mX1);
  fChain->SetBranchAddress("V0Ks.mV0Pos.mX2", &V0Ks_mV0Pos_mX2, &b_V0Ks_mV0Pos_mX2);
  fChain->SetBranchAddress("V0Ks.mV0Pos.mX3", &V0Ks_mV0Pos_mX3, &b_V0Ks_mV0Pos_mX3);
  fChain->SetBranchAddress("V0Ks.mDcaDaughters", &V0Ks_mDcaDaughters, &b_V0Ks_mDcaDaughters);
  fChain->SetBranchAddress("V0Ks.mDca2Vtx", &V0Ks_mDca2Vtx, &b_V0Ks_mDca2Vtx);
  fChain->SetBranchAddress("V0Ks.mM", &V0Ks_mM, &b_V0Ks_mM);
  fChain->SetBranchAddress("V0L", &V0L_, &b_V0L_);
  fChain->SetBranchAddress("V0L.mIndex2Track[2]", &V0L_mIndex2Track, &b_V0L_mIndex2Track);
  fChain->SetBranchAddress("V0L.mV0Pos.mX1", &V0L_mV0Pos_mX1, &b_V0L_mV0Pos_mX1);
  fChain->SetBranchAddress("V0L.mV0Pos.mX2", &V0L_mV0Pos_mX2, &b_V0L_mV0Pos_mX2);
  fChain->SetBranchAddress("V0L.mV0Pos.mX3", &V0L_mV0Pos_mX3, &b_V0L_mV0Pos_mX3);
  fChain->SetBranchAddress("V0L.mDcaDaughters", &V0L_mDcaDaughters, &b_V0L_mDcaDaughters);
  fChain->SetBranchAddress("V0L.mDca2Vtx", &V0L_mDca2Vtx, &b_V0L_mDca2Vtx);
  fChain->SetBranchAddress("V0L.mM", &V0L_mM, &b_V0L_mM);
  fChain->SetBranchAddress("V0Lbar", &V0Lbar_, &b_V0Lbar_);
  fChain->SetBranchAddress("V0Lbar.mIndex2Track[2]", &V0Lbar_mIndex2Track, &b_V0Lbar_mIndex2Track);
  fChain->SetBranchAddress("V0Lbar.mV0Pos.mX1", &V0Lbar_mV0Pos_mX1, &b_V0Lbar_mV0Pos_mX1);
  fChain->SetBranchAddress("V0Lbar.mV0Pos.mX2", &V0Lbar_mV0Pos_mX2, &b_V0Lbar_mV0Pos_mX2);
  fChain->SetBranchAddress("V0Lbar.mV0Pos.mX3", &V0Lbar_mV0Pos_mX3, &b_V0Lbar_mV0Pos_mX3);
  fChain->SetBranchAddress("V0Lbar.mDcaDaughters", &V0Lbar_mDcaDaughters, &b_V0Lbar_mDcaDaughters);
  fChain->SetBranchAddress("V0Lbar.mDca2Vtx", &V0Lbar_mDca2Vtx, &b_V0Lbar_mDca2Vtx);
  fChain->SetBranchAddress("V0Lbar.mM", &V0Lbar_mM, &b_V0Lbar_mM);
  Notify();
  
 
  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("Event", 1);
  fChain->SetBranchStatus("Event.mRunId", 1);
  fChain->SetBranchStatus("Event.mBField", 1);
  fChain->SetBranchStatus("Event.mPrimaryVertex.mX1", 1);
  fChain->SetBranchStatus("Event.mPrimaryVertex.mX2", 1);
  fChain->SetBranchStatus("Event.mPrimaryVertex.mX3", 1);
  fChain->SetBranchStatus("Event.mVertexIndex",1);
  fChain->SetBranchStatus("Event.mBbcAdcEast[24]",1);
  
//  fChain->SetBranchStatus("Event.mSecondVertex.mX1", 1);
//  fChain->SetBranchStatus("Event.mSecondVertex.mX2", 1);
//  fChain->SetBranchStatus("Event.mSecondVertex.mX3", 1);
//  fChain->SetBranchStatus("Event.mPrimaryVertexError.mX1", 1);
//  fChain->SetBranchStatus("Event.mPrimaryVertexError.mX2", 1);
//  fChain->SetBranchStatus("Event.mPrimaryVertexError.mX3", 1);
  fChain->SetBranchStatus("Event.mTriggerWord",1);
//  fChain->SetBranchStatus("Event.mZDCx", 1);
//  fChain->SetBranchStatus("Event.mBBCx", 1);
//  fChain->SetBranchStatus("Event.mBackgroundRate", 1);
//  fChain->SetBranchStatus("Event.mGRefMult", 1);

  
  fChain->SetBranchStatus("Tracks", 1);
  fChain->SetBranchStatus("Tracks.mId", 1);
  fChain->SetBranchStatus("Tracks.mPMomentum.mX1", 1);
  fChain->SetBranchStatus("Tracks.mPMomentum.mX2", 1);
  fChain->SetBranchStatus("Tracks.mPMomentum.mX3", 1);
  fChain->SetBranchStatus("Tracks.mDedx", 1);
  fChain->SetBranchStatus("Tracks.mNHitsFit", 1);
  fChain->SetBranchStatus("Tracks.mNHitsMax", 1);
  fChain->SetBranchStatus("Tracks.mNHitsDedx", 1);
  fChain->SetBranchStatus("Tracks.mNSigmaPion", 1);
//  fChain->SetBranchStatus("Tracks.mNSigmaKaon", 1);
  fChain->SetBranchStatus("Tracks.mNSigmaProton", 1);
//  fChain->SetBranchStatus("Tracks.mNSigmaElectron", 1);
  fChain->SetBranchStatus("Tracks.mPar[6]", 1);
  fChain->SetBranchStatus("Tracks.mErrMatrix[15]", 1);
//  fChain->SetBranchStatus("Tracks.mBTofPidTraitsIndex", 1);
//  fChain->SetBranchStatus("Tracks.mMtdPidTraitsIndex", 1);

//  fChain->SetBranchStatus("Tracks.mMap0", 1);
//  fChain->SetBranchStatus("Tracks.mMap1", 1);
  
  
//  fChain->SetBranchStatus("MtdPidTraits", 1);
//  fChain->SetBranchStatus("MtdPidTraits.fUniqueID", MtdPidTraits_fUniqueID, &b_MtdPidTraits_fUniqueID);
//  fChain->SetBranchStatus("MtdPidTraits.fBits", MtdPidTraits_fBits, &b_MtdPidTraits_fBits);
//  fChain->SetBranchStatus("MtdPidTraits.mMtdHitChan", MtdPidTraits_mMtdHitChan, &b_MtdPidTraits_mMtdHitChan);
//  fChain->SetBranchStatus("MtdPidTraits.mTrackIndex", 1);
//  fChain->SetBranchStatus("MtdPidTraits.mMatchFlag", 1);
//  fChain->SetBranchStatus("MtdPidTraits.mDeltaY", 1);
//  fChain->SetBranchStatus("MtdPidTraits.mDeltaZ", 1);
//  fChain->SetBranchStatus("MtdPidTraits.mDeltaTimeOfFlight", 1);
//  fChain->SetBranchStatus("MtdPidTraits.mBeta", 1);
  
//  fChain->SetBranchStatus("BTofPidTraits", 1);
//  fChain->SetBranchStatus("BTofPidTraits", 1);
//  fChain->SetBranchStatus("BTofPidTraits.mBTofBeta", 1);
//  fChain->SetBranchStatus("BTofPidTraits.mBTofYLocal", 1);
//  fChain->SetBranchStatus("BTofPidTraits.mBTofZLocal", 1);
  
}

Bool_t PicoDst::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void PicoDst::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t PicoDst::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
Double_t PicoDst::BBC_GetPhi(int e_w,int iTile, int seed) {
  
  //get phi of BBC tile
  float pi = TMath::Pi();
  float phi_div = pi /6.0;
  float bbc_phi=phi_div;
  switch(iTile) {
    case 0: bbc_phi=3*phi_div;//pi/2        Tile  1
      break;
    case 1: bbc_phi=phi_div;//pi/6          Tile  2
      break;
    case 2: bbc_phi=-1*phi_div; // -pi/6    Tile  3
      break;
    case 3: bbc_phi=-3*phi_div; // -pi/2    Tile  4
      break;
    case 4: bbc_phi=-5*phi_div; // -5pi/6   Tile  5
      break;
    case 5: bbc_phi=5*phi_div; // 5pi/6     Tile  6
      break;
    case 6: bbc_phi=3*phi_div;  // pi/2     Tiles 7 and 9
      break;
    case 7: bbc_phi=3*phi_div; // pi/2      Tile  8
      break;
    case 8: bbc_phi=phi_div;   //           Tile 10
      break;
    case 9: bbc_phi=0.;        //           Tile 11
      break;
    case 10: bbc_phi=-phi_div; //           Tile 12
      break;
    case 11: bbc_phi=-3*phi_div; //       Tiles 13 and 15
      break;
    case 12: bbc_phi=-3*phi_div;   //       Tile 14
      break;
    case 13: bbc_phi=-5*phi_div;   //       Tile 16
      break;
    case 14: bbc_phi= pi;          //       Tile 17
      break;
    case 15: bbc_phi=5*phi_div;    //       Tile 18
      break;
  }
  
  if(e_w==0){
    if (bbc_phi > -0.001){ bbc_phi = pi-bbc_phi;}
  else {bbc_phi= -pi-bbc_phi;}
  }

  if(bbc_phi<0.0) bbc_phi +=2*pi;
  if(bbc_phi>2*pi) bbc_phi -=2*pi;
  
  return bbc_phi;
  
}
//Double_t PicoDst::BBC_GetPhi(int e_w,int iTile, int seed) {
//  
//  //get phi of BBC tile
//  float pi = TMath::Pi();
//  float phi_div = pi /6.0;
//  float bbc_phi=phi_div;
//  gRandom->SetSeed(seed);
//  switch(iTile) {
//    case 0: bbc_phi=3*phi_div;//pi/2        Tile  1
//      break;
//    case 1: bbc_phi=phi_div;//pi/6          Tile  2
//      break;
//    case 2: bbc_phi=-1*phi_div; // -pi/6    Tile  3
//      break;
//    case 3: bbc_phi=-3*phi_div; // -pi/2    Tile  4
//      break;
//    case 4: bbc_phi=-5*phi_div; // -5pi/6   Tile  5
//      break;
//    case 5: bbc_phi=5*phi_div; // 5pi/6     Tile  6
//      break;
//    case 6: bbc_phi= (gRandom->Rndm()>0.5) ? 2*phi_div:4*phi_div; // pi/3 or 2pi/3                                 Tiles 7 and 9
//      break;
//    case 7: bbc_phi=3*phi_div; // pi/2      Tile  8
//      break;
//    case 8: bbc_phi=phi_div;   //           Tile 10
//      break;
//    case 9: bbc_phi=0.;        //           Tile 11
//      break;
//    case 10: bbc_phi=-phi_div; //           Tile 12
//      break;
//    case 11: bbc_phi=(gRandom->Rndm()>0.5) ? -2*phi_div:-4*phi_div;
//      break;                   //           Tiles 13 and 15
//    case 12: bbc_phi=-3*phi_div;   //       Tile 14
//      break;
//    case 13: bbc_phi=-5*phi_div;   //       Tile 16
//      break;
//    case 14: bbc_phi= pi;          //       Tile 17
//      break;
//    case 15: bbc_phi=5*phi_div;    //       Tile 18
//      break;
//    case 16: bbc_phi=2*phi_div;     //       Tile 7
//      break;
//    case 17: bbc_phi=4*phi_div;     //       Tile 9
//      break;
//    case 18: bbc_phi=-2*phi_div;     //       Tile 13
//      break;
//    case 19: bbc_phi=-4*phi_div;     //       Tile 15
//      break;
//  }
//  
//  if(e_w==0){
//    if (bbc_phi > -0.001){ bbc_phi = pi-bbc_phi;}
//    else {bbc_phi= -pi-bbc_phi;}
//  }
//  
//  if(bbc_phi<0.0) bbc_phi +=2*pi;
//  if(bbc_phi>2*pi) bbc_phi -=2*pi;
//  
//  return bbc_phi;
//  
//}




