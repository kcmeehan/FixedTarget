//Useful functions

enum particleSpecies {PION, KAON, PROTON, ELECTRON, DEUTERON, TRITON, HELION, ALPHA, MUON};

TString GetParticleSymbol(Int_t speciesIndex, Int_t charge=0);
Double_t GetParticleMass(Int_t speciesIndex);
TString GetParticleName(Int_t speciesIndex,Int_t charge=0);
Style_t GetParticleMarker(Int_t speciesIndex, Int_t charge);
Color_t GetParticleColor(Int_t speciesIndex);
Int_t GetGeantID(Int_t speciesIndex, Int_t charge);
std::pair<int,int> ConvertGeantIDtoParticleIndex(Short_t geantID, Int_t charge=0);
Double_t ComputeRapidity(Double_t trackpT, Double_t trackpZ, Double_t pMass);
Double_t ComputemTm0(Double_t pT, Int_t particleID);
Double_t ConvertmTm0ToPt(Double_t mTm0, Int_t particleID);
Double_t GetRapidityRangeLow(Int_t rapidityIndex);
Double_t GetRapidityRangeHigh(Int_t rapidityIndex);
Int_t GetRapidityIndex(Double_t rapidity);
