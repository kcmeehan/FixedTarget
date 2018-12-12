/* Header File for GlauberClass
   This contains the class declaration and all the declarations
   of its data and function members

   Author: Chris Flores
   Date: July 10, 2014

*/

//Compiler Directives - If this file has already been compiled don't
//don't bother compiling it again. (This is good practice and is most
//important if you are working with a large codebase.)
#ifndef GLAUBERCLASS_H
#define GLAUBERCLASS_H

//We need to tell the compiler what external classes we are going to use
//This is called a forward declaration.
class TVector3;
class TRandom3;
class TF1;

//GlauberClass Declaration
class GlauberClass : public TObject{

  //DATA MEMBERS
  //These are typically private as they are here, but they don't have to be.
 private:

  Double_t crossSection;
  Double_t impactParameter;
  Int_t nBinaryCollisions;
  Int_t nParticipants;
  
  //Lets list the variables for each of the two nuclei seperately
  //NucleusA
  Int_t nNucleons_NucA;
  std::vector<TVector3> nucleonPosition_NucA; //!

  //NucleusB
  Int_t nNucleons_NucB;
  std::vector<TVector3> nucleonPosition_NucB; //!

  //Random Number Generator
  TRandom3 *rand; //!

  //Distributions
  TF1 *impactParameterDist; //!
  TF1 *uniformSphereDist; //!
  TF1 *woodsSaxonDist; //!
  TF1 *negativeBinomialDist; //!

  //Particle Production
  Int_t nParticles; //!

  //MEMBER FUNCTIONS
  //These are typically public so that they can be used outside of the class, 
  //but they don't have to be. 
 public:

  //The constructor(s) and destructor - ABSOLUTELY NECESSARY
  GlauberClass(); //Default Constructor
  GlauberClass(Int_t nNucleonsA, Int_t nNucleonsB, Double_t nnCrossSection);
  ~GlauberClass();

  
  //Get Member Functions
  Int_t GetNNucleonsNucA(){return nNucleons_NucA;}
  Int_t GetNNucleonsNucB(){return nNucleons_NucB;}
  Double_t GetImpactParameter(){return impactParameter;}
  Int_t GetNParticipants(){return nParticipants;}
  Int_t GetNBinaryCollisions(){return nBinaryCollisions;}
  TF1 *GetNegativeBinomialDistribution(){return negativeBinomialDist;}
  Double_t GetNuclearRadius(Int_t nNucleons);
  
  Double_t GenerateRadialNucleonPosition(Int_t methodIndex, Int_t nNucleons);

  //Set Member Functions
  void SetNNucleonsNucA(Int_t val){nNucleons_NucA=val;}
  void SetNNucleonsNucB(Int_t val){nNucleons_NucB=val;}
  void SetImpactParameter(Double_t val=0, Double_t min=0, Double_t max=0);
  Int_t SetWoodsSaxonParameters(Int_t nNucleons);
  void SetNegativeBinomialParameters(Double_t p, Double_t n);
  void SetTotalParticlesProduced(Int_t val){nParticles=val;}

  //Other Useful Memeber Functions
  void PrintClassInfo();
  void GenerateNucleonPositions(Int_t methodIndex);
  void CountNpartNcoll();
  Int_t ProduceParticles();
  void Reset();
  
  ClassDef(GlauberClass,1); //This is a ROOT specific directive


}; //A very easy to forget semicolon! ;)


#endif
