/****
**
**
**
**
**
**
****************************************************************************/

#include <iostream>
#include <cstring>
#include <vector>

#include <TROOT.h>
#include <TMath.h>
#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TStyle.h>
#include <TColor.h>
#include <TF1.h>

using namespace std;

//Global Definitions
#define nParticles 12

//Enumerations
enum {kPionPlus,kPionMinus,kKaonPlus,kKaonMinus,kProtonPlus,kProtonMinus,
      kElectronPlus,kElectronMinus,kDeuteronPlus,kDeuteronMinus,
      kTritonPlus,kTritonMinus};

enum {kPion,kKaon,kProton,kElectron};

enum {kTPC,kTOF};

enum {kAuAuCenter,kAuAuDisplacedPosY,kAuAuDisplacedNegY,kAuAlBeampipePosY,kAuAlBeampipeNegY,
      kAuAuFixedTargetPosY,kAuAuFixedTarget2014,kAuAuFixedTarget2015};

enum {kDataMode,kQAMode};

//__________________________________________________________________________
TString GetEventTypeName(Int_t eventType){

  TString eventNames[8] = 
    {"AuAuCenter",
     "AuAuDisplacedPosY",
     "AuAuDisplacedNegY",
     "AuAlBeampipePosY",
     "AuAlBeampipeNegY",
     "AuAuFixedTargetPosY",
     "AuAuFixedTarget2014"
		 "AuAuFixedTarget2015"
    };

  return eventNames[eventType];
}

//__________________________________________________________________________
TString GetParticleName(Int_t ParticleIndex){

  TString particleName[nParticles] =
    {"PionPlus",
     "PionMinus",
     "KaonPlus",
     "KaonMinus",
     "ProtonPlus",
     "ProtonMinus",
     "ElectronPlus",
     "ElectronMinus",
     "DeuteronPlus",
     "DeuteronMinus",
     "TritonPlus",
     "TritonMinus"
    };

  return particleName[ParticleIndex];

}

//________________________________________________________________________
TString GetSpeciesName(Int_t ParticleIndex){

  TString speciesName[nParticles] = 
    {"Pion",
     "Pion",
     "Kaon",
     "Kaon",
     "Proton",
     "Proton",
     "Electron",
     "Electron",
     "Deuteron",
     "Deuteron",
     "Triton",
     "Triton"
    };
  
  return speciesName[ParticleIndex];    

}

//________________________________________________________________________                       
TString GetParticleSymbol(Int_t ParticleIndex){

  TString particleSymbol[nParticles] =
    {"#pi^{+}",
     "#pi^{-}",
     "k^{+}",
     "k^{-}",
     "p",
     "#bar{p}",
     "e^{+}",
     "e^{-}",
     "d",
     "#bar{d}",
     "t",
     "#bar{t}"
    };

  return particleSymbol[ParticleIndex];

}

//________________________________________________________________________
Double_t GetParticleMass(Int_t ParticleIndex){

  Double_t massParticle[nParticles] =
    {.139570,  //Pion                                                                           
     .139570,  //Pion                                                                           
     .493667,  //Kaon                                                                           
     .493667,  //Kaon                                                                           
     .938272,  //Proton                                                                         
     .938272,  //Proton                                                                         
     .000511,  //Electron                                                                       
     .000511,  //Electron                                                                       
     1.8765,   //Deuteron                                                                       
     1.8765,   //Deuteron                                                                       
     2.8148,   //Triton                                                                         
     2.8148    //Triton                                                                         
    };

  return massParticle[ParticleIndex];
}

//_____________________________________________________________________               
Int_t GetParticleCharge(Int_t ParticleIndex){

  Int_t chargeParticle[nParticles] =
    {1,-1,1,-1,1,-1,1,-1,1,-1,1,-1};

  return chargeParticle[ParticleIndex];

}

//_____________________________________________________________________                         
Int_t GetGeantID(Int_t ParticleIndex){
  //NOTE: The The Deuteron and Anti-Deuteron and the                                            
  //      Triton and Anti-Triton are given the same                                             
  //      ID number because GEANT doesn't have IDs                                              
  //      for the anti-particles.                                                               

  Int_t geantIdArray[nParticles] =
    {8, 9, 11, 12, 14, 15, 2, 3, 45, 45, 46, 46};

  return geantIdArray[ParticleIndex];
  //return TString::Format("%d",geantIdArray[ParticleIndex]);                                   
}

//_____________________________________________________________________    
Color_t GetParticleColor(Int_t particleID){

  Color_t pColor[nParticles] =
    {kRed,
     kRed,
     kBlue+2,
     kBlue+2,
     kGreen+2,
     kGreen+2,
     kViolet-1,
     kViolet-1,
     kCyan+3,
     kCyan+3,
     kOrange+2,
     kOrange+2};

  return pColor[particleID];

}

//_____________________________________________________________________  
Style_t GetParticleMarker(Int_t particleID){

  Style_t pMarker[nParticles] =
    {kFullCircle,
     kOpenCircle,
     kFullCircle,
     kOpenCircle,
     kFullCircle,
     kOpenCircle,
     kFullCircle,
     kOpenCircle,
     kFullCircle,
     kOpenCircle,
     kFullCircle,
     kOpenCircle};

  return pMarker[particleID];

}

//_____________________________________________________________________
Double_t ComputeEta(Double_t y, Double_t pT, Double_t m0){

  TF1 rapidityFunc("rapidityFunc","log((sqrt([0]*[0] + [1]*[1]*cosh(x)*cosh(x)) + [1]*sinh(x)) /\
 (sqrt([0]*[0] + [1]*[1])) )",0,5);
  rapidityFunc.FixParameter(0,m0);
  rapidityFunc.FixParameter(1,pT);

  Double_t eta = rapidityFunc.GetX(fabs(y));

  return eta;
}

//____________________________________________________________________________         
Double_t ComputeRapidity(Double_t trackpT, Double_t trackpZ, Double_t pMass){

  Double_t energy = sqrt(pow(trackpT,2) + pow(trackpZ,2) + pMass*pMass);

  return 0.5*log((energy + trackpZ)/(energy - trackpZ));

}

//_____________________________________________________________________                        
Double_t ComputemTm0(Double_t pT, Int_t particleID){
  return sqrt(pow(pT,2)+pow(GetParticleMass(particleID),2))-GetParticleMass(particleID);
}

//______________________________________________________________________                        
Double_t ConvertmTm0ToPt(Double_t mTm0, Int_t particleID){
  return sqrt(pow(mTm0+GetParticleMass(particleID),2) - pow(GetParticleMass(particleID),2));
}

//____________________________________________________________________________    
TF1 *tpcPIDFunction[nParticles] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
TF1 *tofPIDFunction[nParticles] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

void LoadPIDFunctions(TString fileName,Double_t energy){

  //If the pid functions have already been loaded then don't bother
  //loading them again.
  if (tpcPIDFunction[0] != NULL)
    return;

  TFile *file = new TFile(fileName,"READ");

  //Set the Directory Name 
  TString dirName = " ";
  if (energy > 6 && energy < 8)
    dirName = "AuAu7";
  else if (energy > 10 && energy < 12)
    dirName = "AuAu11";
  else if (energy > 13 && energy < 15)
    dirName = "AuAu14";
  else if (energy > 18 && energy < 20)
    dirName = "AuAu19";

  file->cd(dirName);

  tpcPIDFunction[kPionPlus] = (TF1 *)gDirectory->Get("bichselPion");
  tpcPIDFunction[kPionMinus] = (TF1 *)gDirectory->Get("bichselPion");
  tpcPIDFunction[kKaonPlus] = (TF1 *)gDirectory->Get("bichselKaon");
  tpcPIDFunction[kKaonMinus] = (TF1 *)gDirectory->Get("bichselKaon");
  tpcPIDFunction[kProtonPlus] = (TF1 *)gDirectory->Get("bichselProton");
  tpcPIDFunction[kProtonMinus] = (TF1 *)gDirectory->Get("bichselProton");
  tpcPIDFunction[kElectronPlus] = (TF1 *)gDirectory->Get("bichselElectron");
  tpcPIDFunction[kElectronMinus] = (TF1 *)gDirectory->Get("bichselElectron");
  tpcPIDFunction[kDeuteronPlus] = (TF1 *)gDirectory->Get("bichselDeuteron");
  tpcPIDFunction[kDeuteronMinus] = (TF1 *)gDirectory->Get("bichselDeuteron");
  tpcPIDFunction[kTritonPlus] = (TF1 *)gDirectory->Get("bichselTriton");
  tpcPIDFunction[kTritonMinus] = (TF1 *)gDirectory->Get("bichselTriton");

  cout <<"GOT THE TPC PION PID FUNC! " <<tpcPIDFunction[kPionPlus] <<endl;

  file->cd();
  file->cd("TOF");
  tofPIDFunction[kPionPlus] = (TF1 *)gDirectory->Get("TOFPion");
  tofPIDFunction[kPionMinus] = (TF1 *)gDirectory->Get("TOFPion");
  tofPIDFunction[kKaonPlus] = (TF1 *)gDirectory->Get("TOFKaon");
  tofPIDFunction[kKaonMinus] = (TF1 *)gDirectory->Get("TOFKaon");
  tofPIDFunction[kProtonPlus] = (TF1 *)gDirectory->Get("TOFProton");
  tofPIDFunction[kProtonMinus] = (TF1 *)gDirectory->Get("TOFProton");
  tofPIDFunction[kElectronPlus] = (TF1 *)gDirectory->Get("TOFElectron");
  tofPIDFunction[kElectronMinus] = (TF1 *)gDirectory->Get("TOFElectron");
  tofPIDFunction[kDeuteronPlus] = (TF1 *)gDirectory->Get("TOFDeuteron");
  tofPIDFunction[kDeuteronMinus] = (TF1 *)gDirectory->Get("TOFDeuteron");
  tofPIDFunction[kTritonPlus] = (TF1 *)gDirectory->Get("PionTriton");
  tofPIDFunction[kTritonMinus] = (TF1 *)gDirectory->Get("PionTriton");

  cout <<"GOT THE TOF PION PID FUNC" <<tofPIDFunction[kPionPlus] <<endl;

}

//_____________________________________________________________________   
TF1 *GetPIDFunction(Int_t detector, Int_t particleID){

  if (detector == kTPC)
    return tpcPIDFunction[particleID];

  else if (detector == kTOF)
    return tofPIDFunction[particleID];

  //Failure                                                                                    
  return NULL;

}


//_____________________________________________________________________
Double_t ComputeTPCZ(Double_t trackdEdx, Double_t trackPt,
                     Double_t trackPz, Int_t particleID){

  Double_t measdEdx = trackdEdx*pow(10,6);
  Double_t trackP = sqrt(pow(trackPt,2)+pow(trackPz,2));
  Double_t expecteddEdx = tpcPIDFunction[particleID]->Eval(trackP);

  return log(measdEdx/expecteddEdx);
}

//_____________________________________________________________________ 
Double_t ComputeTOFZ(Double_t trackTOFBeta, Double_t trackPt,
                     Double_t trackPz, Int_t particleID){

  Double_t measInvBeta = 1.0/trackTOFBeta;
  Double_t trackP = sqrt(pow(trackPt,2)+pow(trackPz,2));
  Double_t expectedInvBeta = tofPIDFunction[particleID]->Eval(trackP);

  return log(measInvBeta/expectedInvBeta);
}

//______________________________________________________________________________
Double_t PredictTPCZ(Int_t interestPID, Int_t confoundPID, Double_t totalP){

  if (confoundPID % 2 != 0)
    confoundPID = confoundPID - 1;  

  Double_t interestdEdx = tpcPIDFunction[interestPID]->Eval(totalP);
  Double_t confounddEdx = tpcPIDFunction[confoundPID]->Eval(totalP);

  return log(confounddEdx/interestdEdx);

}

//_______________________________________________________________________
Double_t PredictTOFZ(Int_t interestPID, Int_t confoundPID, Double_t totalP){

  Double_t interestInvBeta = tofPIDFunction[interestPID]->Eval(totalP);
  Double_t confoundInvBeta = tofPIDFunction[confoundPID]->Eval(totalP);

  return log(confoundInvBeta/interestInvBeta);

}
