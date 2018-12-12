/* Implementation File for GlauberClass
   This contains all of the function definitions for the member
   functions of Glauber Class.

   Author: Chris Flores
   Date: July 10, 2014

*/

//We need to include our class declaration and any declarations of 
//classes we are going to use in this implementation file.
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

#include "TMath.h"
#include "TVector3.h"
#include "TRandom3.h"
#include "TF1.h"

#include "GlauberClass.h"

using namespace std;

ClassImp(GlauberClass); //Another ROOT Necessary Directive

enum nucleonDistributions {kUniformSphere, kWoodsSaxon};

// Default Constructor ___________________________________________________
GlauberClass::GlauberClass(){

  crossSection = 0;
  impactParameter = 0;
  nBinaryCollisions = 0;
  nParticipants = 0;

  nNucleons_NucA = 0;
  nNucleons_NucB = 0;

  nParticles = 0;

  rand = new TRandom3(0);
  
  impactParameterDist = new TF1("impactParameterDist","2.0*3.14*x",0,100);
  uniformSphereDist = new TF1("uniformSphereDist","4.0*3.14*x*x",0,100);
  woodsSaxonDist =  new TF1("woodsSaxonDist","x*x*[0]*((1.0+[1]*(x/[2])*(x/[2])) / (1.0+exp((x-[2])/[3])))",0,18);
  negativeBinomialDist = new TF1("negBinomial","[2]*ROOT::Math::negative_binomial_pdf(x,[0],[1])",0,35);

}

// Optional Constructor __________________________________________________
GlauberClass::GlauberClass(Int_t nNucleonsA, Int_t nNucleonsB, Double_t nnCrossSection){

  crossSection = nnCrossSection;
  impactParameter = 0;
  nBinaryCollisions = 0;
  nParticipants = 0;

  nNucleons_NucA = nNucleonsA;
  nucleonPosition_NucA.resize(nNucleons_NucA);

  nNucleons_NucB = nNucleonsB;
  nucleonPosition_NucB.resize(nNucleons_NucB);

  nParticles = 0;

  rand = new TRandom3(0);

  impactParameterDist = new TF1("impactParameterDist","2.0*3.14*x",0,100);
  uniformSphereDist = new TF1("uniformSphereDist","4.0*3.14*x*x",0,100);
  woodsSaxonDist = new TF1("woodsSaxonDist","x*x*[0]*((1.0+[1]*(x/[2])*(x/[2])) / (1.0+exp((x-[2])/[3])))",0,18);
  negativeBinomialDist = new TF1("negBinomial","[2]*ROOT::Math::negative_binomial_pdf(x,[0],[1])",0,35);

}

// Destructor ___________________________________________________________
GlauberClass::~GlauberClass(){

  //If we call "new" in our class then we are responsible for deleting
  //that memory allocation.  We won't do that in our class, but here
  //is the right place do do it with al call like:

  delete rand;
  delete uniformSphereDist;
  delete woodsSaxonDist;
  delete negativeBinomialDist;

}



// Print Class Info _______________________________________________________
void GlauberClass::PrintClassInfo(){

  cout <<"nNucleons NucA: " <<nNucleons_NucA <<endl
       <<"nNucleons NucB: " <<nNucleons_NucB <<endl
       <<"size of Position Vecs(A,B): " <<nucleonPosition_NucA.size() <<" " 
       <<nucleonPosition_NucB.size() <<endl
       <<"Impact Parameter: " <<impactParameter <<endl
       <<"Npart: " <<nParticipants <<endl
       <<"Ncoll: "<<nBinaryCollisions <<endl;
  
}

// Set Impact Parameter _________________________________________________
void GlauberClass::SetImpactParameter(Double_t val, 
				      Double_t min, Double_t max){

  if (val == 0 && min<max)
    impactParameter = impactParameterDist->GetRandom(min,max);
  
  else if (val == 0 && min==max)
    cout <<"WARNING: Did you forget to set min and max?" <<endl;

  else if (val != 0)
    impactParameter = val;

}

// Fill Nucleus with Nucleons _____________________________________________
void GlauberClass::GenerateNucleonPositions(Int_t methodIndex){

  //NOTE: This Uses either a Uniform Sphere Distribution methodIndex = 0
  //           or a Woods-Saxon Distribution methodIndex = 1.

  Double_t  x=0, y=0, z=0, r =0;  

  //Loop over the Nucleus A

  //Determine the method of distributing the nucleons.
  //If the Woods Saxon is specified, but the parameters for a nucleus
  //matchin the number of nucleons is not found in the database, then
  //switch to uniform sphere.
  if (methodIndex == kWoodsSaxon)
    if (SetWoodsSaxonParameters(nNucleons_NucA) == -1)
      methodIndex = kUniformSphere;
  
  for (Int_t iNucleon=0; iNucleon<nNucleons_NucA; iNucleon++){
    
    r = GenerateRadialNucleonPosition(methodIndex,nNucleons_NucA);
    
    rand->Sphere(x,y,z,r);
    
    nucleonPosition_NucA[iNucleon].SetXYZ(x,y,z);
    
  }
  
  //Loop over the Nucleus B
  //Shift all nucleons in the x direction for the impact parameter
  if (methodIndex == kWoodsSaxon)
    if ( SetWoodsSaxonParameters(nNucleons_NucB) == -1)
      methodIndex = kUniformSphere;
  
  for (Int_t iNucleon=0; iNucleon<nNucleons_NucB; iNucleon++){
    
    r = GenerateRadialNucleonPosition(methodIndex,nNucleons_NucB);
    
    rand->Sphere(x,y,z,r);

    nucleonPosition_NucB[iNucleon].SetXYZ(x+impactParameter,y,z);
    
  }
  
}

//Get the Nuclear Radius________________________________________________
Double_t GlauberClass::GetNuclearRadius(Int_t nNucleons){

  return 1.25 * pow(nNucleons,1./3.);
  
}

//Get the Radial Nucleon Position________________________________________
Double_t GlauberClass::GenerateRadialNucleonPosition(Int_t methodIndex, Int_t nNucleons){

  //methodIndex = 0 is for Uniform Sphere Model
  //methodIndex = 1 is for Woods-Saxon Distribution Model

  if (methodIndex == kUniformSphere){

    //Compute the Maximum Nuclear Radius based on its A
    Double_t rMax = GetNuclearRadius(nNucleons);
    
    return uniformSphereDist->GetRandom(0,rMax);

  }

  else if (methodIndex == kWoodsSaxon){
 
    return woodsSaxonDist->GetRandom();

  }

  //If the Code makes it this far then the method index was not valid
  cout <<"ERROR in GlauberClass::GetRadialNucleonPosition() -- methodIndex not 0 or 1 -- returning 0.0" <<"\n";
  return 0.0;

}

// Set Woods-Saxon Parameters ________________________________________
Int_t GlauberClass::SetWoodsSaxonParameters(Int_t nNucleons){

  //Sets the Woods-Saxon Parameters based on the type of Nucleus
  //This could probably be done more elegently

  //Parameters for Various Elements [p0, w, c, a, B20, B40]
  //Double_t he[] = {0.0,0.0,0.0,0.0,0.0}; //Should not be used with WS
  Double_t al[] = {.169, 0.0, 3.07, 0.519, 0.0, 0.0};
  Double_t au[] = {.169, 0.0, 6.38, 0.535, 0.0, 0.0};
  //Double_t leadParams[] = {};

  if (nNucleons == 27)
    woodsSaxonDist->SetParameters(al[0],al[1],al[2],al[3]);
  else if (nNucleons == 197)
    woodsSaxonDist->SetParameters(au[0],au[1],au[2],au[3]);
  else
    return -1;

  return 1;
}

// Cound Participants and Binary Collisions _______________________________
void GlauberClass::CountNpartNcoll(){

  //Compute nnCrossSection Effective Radius
  Double_t rEff = sqrt(crossSection/(10.0*3.14));

  Double_t nnDistance =0;
  std::vector<int> nucAParticipants (nNucleons_NucA,0);
  std::vector<int> nucBParticipants (nNucleons_NucB,0);

  //Loop Over all the Nucleons in each of the nuclei
  for (Int_t iNucleonA=0; iNucleonA<nNucleons_NucA; iNucleonA++){
    for (Int_t iNucleonB=0; iNucleonB<nNucleons_NucB; iNucleonB++){


      //Compute the Distance Between iNucleonA and iNucleonB, if the distance
      //is less than rEff the nucleons collide
      nnDistance = sqrt(pow(nucleonPosition_NucB[iNucleonB].X()-
			                    nucleonPosition_NucA[iNucleonA].X(),2)+
			            pow(nucleonPosition_NucB[iNucleonB].Y()-
			                    nucleonPosition_NucA[iNucleonA].Y(),2));

      if (nnDistance < rEff){
	nBinaryCollisions++;
	nucAParticipants[iNucleonA] = 1;
	nucBParticipants[iNucleonB] = 1;
	
      }

    }//End Loop over NucA
  }//End Loop over NucB

  nParticipants = std::accumulate(nucAParticipants.begin(),nucAParticipants.end(),0);
  nParticipants = std::accumulate(nucBParticipants.begin(),nucBParticipants.end(),nParticipants);

}

//______________________________________________________________________
void GlauberClass::SetNegativeBinomialParameters(Double_t p, Double_t n){

  //Set the Parmeters of the Negative Binomial Distribution
  negativeBinomialDist->SetParameters(p,n,1.0);

}

//______________________________________________________________________
Int_t GlauberClass::ProduceParticles(){

  Int_t totalParticlesProduced(0);

  //For each binary Collision pick a random number from the neg. binomial
  //distribution and sum them all to find the total number of produced particles
  for (Int_t iBinColl=0; iBinColl<nBinaryCollisions; iBinColl++){

    totalParticlesProduced +=negativeBinomialDist->GetRandom(0,35);

  }

  SetTotalParticlesProduced(totalParticlesProduced);

  return totalParticlesProduced;
}

// Reset the Necessary Variables _________________________________________
void GlauberClass::Reset(){

  impactParameter = 0;
  nBinaryCollisions = 0;
  nParticipants = 0;

}


