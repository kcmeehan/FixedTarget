/* 

   Author: Chris Flores
   Date: July 10, 2014

*/
#include <iostream>
#include <iomanip>

#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>

#include <GlauberClass.h>

using namespace std;

void GlauberModel(Int_t nEvents, Int_t nNucleonsA, Int_t nNucleonsB,
		  Double_t nnCrossSection, Int_t model=0, TString outDir="data"){

  //Create the output file name depending on the running configuration
  TString fileName = TString::Format("%s/Glauber_%d_%d_%gmb_%s.root",
				     outDir.Data(),
				     nNucleonsA, nNucleonsB,nnCrossSection,
				     model == 0 ? "UniformSphere" : "WoodsSaxon");
  
  //Create a ROOT File to Save the resulting TTree to
  TFile *outFile = new TFile(fileName,"CREATE");
  
  //Create a Tree 
  TTree *tree = new TTree("GlauberTree","GlauberTree");
  
  //Create an Instance of our Glauber Class
  GlauberClass glauberEvent(nNucleonsA,nNucleonsB,nnCrossSection);

  //Now that we have an instance of our GlauberClass, lets branch the tree so we can save it
  TBranch *branch = tree->Branch("GlauberData",&glauberEvent);
  if (branch == NULL) return;

  //Loop Over all the Events
  Int_t iEvent(0);
  while (iEvent < nEvents){
    //Set the Max Impact Parameter to 1.3 times larger than the sum
    //of the two nuclear radii
    Double_t maxImpactParameter =
      1.3 * (glauberEvent.GetNuclearRadius(nNucleonsA) +
	     glauberEvent.GetNuclearRadius(nNucleonsB));
    
    glauberEvent.SetImpactParameter(0,0,maxImpactParameter);
    
    //Fill the Nuclei with Nucleons
    glauberEvent.GenerateNucleonPositions(model);
    
    //Count nPart and nColl
    glauberEvent.CountNpartNcoll();
    
    //Fill Tree with events that had at least one participating nucleon
    if (glauberEvent.GetNParticipants() > 0){
      tree->Fill();
      iEvent++;
    }
    
    //Reset the GlauberClass event for reuse
    glauberEvent.Reset();

    //Print the Fraction Complete
    cout <<setw(15) <<left <<"Percent Complete: " <<(Int_t)(100* (iEvent/(Double_t)nEvents)) <<"\r";
    
  } //End of Loop Over Events

  tree->Write();
  outFile->Close();

  cout <<"\nGlauber Model Simulation Complete\n"
       <<"Output file can be found here: " <<fileName <<endl;
}
