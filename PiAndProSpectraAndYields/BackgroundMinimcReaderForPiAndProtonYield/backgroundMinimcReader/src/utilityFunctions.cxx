//Useful functions

#include <iostream>
#include <utility>
#include <TMath.h>
#include <TStyle.h>
#include <TColor.h>

#include "globalDefinitions.h"
#include "utilityFunctions.h"

#define nDefinedParticles 9

//________________________________________________________________________
TString GetParticleSymbol(Int_t speciesIndex, Int_t charge){
  
  TString particleSymbol[] =
    {"#pi","k","p","e","d","t","{}^{3}He","#alpha","#mu"};
  
  if (charge == 0)
    return particleSymbol[speciesIndex];
  
  TString positiveParticleSymbol[] =
    {"#pi^{+}","k^{+}","p","e^{+}","d","t","{}^{3}He","#alpha","#mu^{+}"};
  
  if (charge > 0)
    return positiveParticleSymbol[speciesIndex];
  
  TString negativeParticleSymbol[] =
    {"#pi^{-}","k^{-}","#bar{p}","e^{-}","#bar{d}","#bar{t}","{}^{3}#bar{He}","#bar{#alpha}","#mu^{-}"};
  
  return negativeParticleSymbol[speciesIndex];

}

//___________________________________________________________________
Double_t GetParticleMass(Int_t speciesIndex){

  //Returns the particle mass of type speciesIndex in GeV.

  if (speciesIndex < 0 || speciesIndex >= nDefinedParticles){
    cout <<"WARNING - ParticleInfo::GetParticleMass(): Unknown speciesIndex! Returning NAN.\n";
    return NAN;
  }

    Double_t particleSpeciesMass[] =
      {
	0.13957,    //Pion
	0.49367,    //Kaon
	0.93827,    //Proton
	0.00051099, //Electron
	1.87561,    //Deuteron
	2.80925,    //Triton
	2.8094,     //Helion
	3.72742,    //Alpha
	0.105658    //Muon
      };

    return particleSpeciesMass[speciesIndex];
}

//___________________________________________________________________
TString GetParticleName(Int_t speciesIndex,Int_t charge){

  //Returns the name of a particle species. By default (charge=0) the
  //generic name for the species is given, otherwise Plus or Minus is
  //appended to the name depending of whether charge is positive or negative.

  if (speciesIndex < 0 || speciesIndex >= nDefinedParticles){
    cout <<"WARNING - ParticleInfo::GetParticleName():Unknown speciesIndex! Returning empty string.\n";
    return TString("");
  }

  TString chargeName;
  if (charge > 0)
    chargeName = "Plus";
  else if (charge < 0)
    chargeName = "Minus";
  else
    chargeName = "";

    TString particleSpeciesName[] =
      {"Pion","Kaon","Proton","Electron",
       "Deuteron","Triton","Helion","Alpha","Muon"};

    return TString(particleSpeciesName[speciesIndex]+chargeName);

}

//___________________________________________________________________
Style_t GetParticleMarker(Int_t speciesIndex, Int_t charge){

  //Returns the marker style for particle of type speciesIndex.
  //Negative particles are given closed symbols, while positive particles
  //are given open symbols. By default (charge=0) and the negative particle
  //symbol will be returned.

  if (speciesIndex < 0 || speciesIndex >= nDefinedParticles){
    cout <<"WARNING - ParticleInfo::GetParticleMarker(): Unknown speciesIndex! Using kDot.\n";
    return kDot;
  }

    Style_t negativeParticleMarker[] =
      {kFullCircle,       //Pion
       kFullDiamond,      //Kaon
       kFullSquare,       //Proton
       kFullCircle,       //Electron
       kFullCross,        //Deuteron
       kFullTriangleUp,   //Triton
       kFullTriangleDown, //Helion
       kPlus,             //Alpha
       kStar};            //Muon

    if (charge <= 0)
      return negativeParticleMarker[speciesIndex];

      Style_t positiveParticleMarker[] =
	{kOpenCircle,       //Pion
	 kOpenDiamond,      //Kaon
	 kOpenSquare,       //Proton
	 kOpenCircle,       //Electron
	 kOpenCross,        //Deuteron
	 kOpenTriangleUp,   //Triton
	 kOpenTriangleDown, //Helion
	 kPlus,             //Alpha
	 kStar};            //Muon

      return positiveParticleMarker[speciesIndex];

}

//___________________________________________________________________
Color_t GetParticleColor(Int_t speciesIndex){

  //Returns the color of the particle of type speciesIndex.

  if (speciesIndex < 0 || speciesIndex >= nDefinedParticles){
    cout <<"WARNING - ParticleInfo::GetParticleColor(): Unknown speciesIndex! Using kBlack.\n";
    return kBlack;
  }

    Color_t particleColor[] =
      {kRed-2,           //Pion
       kBlue+2,          //Kaon
       kGreen+2,         //Proton
       kViolet-1,        //Electron
       kCyan+3,          //Deuteron
       kOrange+2,        //Triton
       kMagenta+2,       //Helion
       kOrange-2,        //Alpha
       kPink-9};         //Muon

    return particleColor[speciesIndex];
}

//_____________________________________________________________________
Int_t GetGeantID(Int_t speciesIndex, Int_t charge){
  //NOTE: The The Deuteron and Anti-Deuteron and the
  //      Triton and Anti-Triton are given the same
  //      ID number because GEANT doesn't have IDs
  //      for the anti-particles.

    Int_t geantIdArrayPlus[] =
      {8, 11, 14, 2, 45, 46, 49, 47, 5};

    if (charge > 0)
      return geantIdArrayPlus[speciesIndex];
    
    Int_t geantIdArrayMinus[] =
      {9, 12, 15, 3, 45, 46, 49, 47, 6};

    if (charge < 0)
      return geantIdArrayMinus[speciesIndex];

    if (charge == 0)
      cout <<"WARNING - utilityFunctions::GeatGeantID() - charge can not be 0! Returning -1\n";
    
    return -1;
    
}

//____________________________________________________________________________
std::pair<int,int> ConvertGeantIDtoParticleIndex(Short_t geantID, Int_t charge){

  //Pion
  if (geantID == 8)
    return std::make_pair(0,1);
  else if (geantID == 9)
    return std::make_pair(0,-1);

  //Kaon
  else if (geantID == 11)
    return std::make_pair(1,1);
  else if (geantID == 12)
    return std::make_pair(1,-1);

  //Proton
  else if (geantID == 14)
    return std::make_pair(2,1);
  else if (geantID == 15)
    return std::make_pair(2,-1);

  //Electron
  else if (geantID == 2)
    return std::make_pair(3,1);
  else if (geantID == 3)
    return std::make_pair(3,-1);

  //Deuteron
  else if (geantID == 45){
    if (charge > 0)
      return std::make_pair(4,1);
    else 
      return std::make_pair(4,-1);
  }

  //Triton
  else if (geantID == 46){
    if (charge > 0)
      return std::make_pair(5,1);
    else 
      return std::make_pair(5,-1);
  }
  
  //Alpha
  else if (geantID == 49){
    if (charge > 0)
      return std::make_pair(6,1);
    else
      return std::make_pair(6,-1);
  }
  
  //Helion
  else if (geantID == 47){
    if (charge > 0)
      return std::make_pair(7,1);
    else 
      return std::make_pair(7,-1);
  }
  
  //Muon
  else if (geantID == 5)
    return std::make_pair(8,1);
  else if (geantID == 6)
    return std::make_pair(8,-1);

  return std::make_pair(-1,0);

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

//___________________________________________________________
Double_t GetRapidityRangeLow(Int_t rapidityIndex){

  return rapidityMin + (rapidityIndex * rapidityBinWidth);
}

//___________________________________________________________
Double_t GetRapidityRangeHigh(Int_t rapidityIndex){

  return GetRapidityRangeLow(rapidityIndex)+rapidityBinWidth;
}

//___________________________________________________________
Int_t GetRapidityIndex(Double_t rapidity){

  //Make sure the value of rapidity is in the [min,max] range
  if (rapidity < rapidityMin || rapidity > rapidityMax)
    return -1;

  //Loop through the rapidity bins and return the index
  //of the bin that this value of rapidity falls into
  for (Int_t index=0; index<nRapidityBins; index++){
    
    if (rapidity >= GetRapidityRangeLow(index) &&
	rapidity < GetRapidityRangeHigh(index))
      return index;
  }

  return -1;
}
