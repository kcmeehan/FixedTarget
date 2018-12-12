#include <iostream>
#include <vector>

#include "TH1D.h"
#include "TTree.h"
#include <vector>

#include "TH1D.h"
#include "TMath.h"


#include "GlauberClass.h"
#include "ReturnStructs.h"
#include "inc/DetermineCentralityBin.h"


using namespace std;

void FindNpartNcollDistributions(NegBinomialSearchResults *glauberResult, TTree *glauberTree){

  //Create the Structure that will be returned
  Int_t nCentBins = glauberResult->nCentralityBins;
  //cout <<"The Number of Centrality Bins is: " <<nCentBins <<endl;
  glauberResult->nPartHistos = new TH1D[nCentBins];
  glauberResult->nCollHistos = new TH1D[nCentBins];
  glauberResult->impactParamHistos = new TH1D[nCentBins];
  
  for (Int_t iCentBin=0; iCentBin<nCentBins; iCentBin++){
    
    //Setup the Histograms to have the same properties as the dataHisto
    (glauberResult->nPartHistos)[iCentBin].SetBins(450,0,450);
    (glauberResult->nCollHistos)[iCentBin].SetBins(2000,0,2000);
    (glauberResult->impactParamHistos)[iCentBin].SetBins(20,0,20);
    
  }//End Loop Over iCentBin

  //Create an instance of the GlauberClass to hold the info from the tree
  GlauberClass *glauberEvent = 0;
  glauberTree->FindBranch("GlauberData")->SetAddress(&glauberEvent);

  //Vectors to used to compute means
  std::vector<std::vector<double> > nPart(nCentBins);
  std::vector<std::vector<double> > nColl(nCentBins);
  std::vector<std::vector<double> > impactParam(nCentBins);

  //Loop Over the events of the glauberTree. For each event generate the event's
  //particle multiplicity using the negative binomial parameters stored in glauberResult.
  //Find the centrality bin this event and store its nPart, nColl, and impact parameter
  //in the histograms
  Double_t nParticles(0);
  Int_t centBinIndex(-1);
  glauberEvent->SetNegativeBinomialParameters(glauberResult->p,glauberResult->n);
  for (Int_t iEvent=0; iEvent<glauberTree->GetEntries(); iEvent++){

    glauberTree->GetEntry(iEvent);

    //Run the particle production Model
    nParticles = glauberEvent->ProduceParticles();

    //Determine the Centrality Bin of This Event
    centBinIndex = DetermineCentralityBin(glauberResult->centralityBinCuts,
					  nParticles,glauberResult->nCentralityBins);

    //If this event does not have a valid centrality bin index then skip it
    if (centBinIndex < 0)
      continue;

    //Fill the Vectors to keep track of the unbinned values
    nPart[centBinIndex].push_back(glauberEvent->GetNParticipants());
    nColl[centBinIndex].push_back(glauberEvent->GetNBinaryCollisions());
    impactParam[centBinIndex].push_back(glauberEvent->GetImpactParameter());
    
    //Fill the Hisograms depending on which centrality bin the event was
    glauberResult->nCollHistos[centBinIndex].Fill(glauberEvent->GetNParticipants());
    glauberResult->nPartHistos[centBinIndex].Fill(glauberEvent->GetNBinaryCollisions());
    glauberResult->impactParamHistos[centBinIndex].Fill(glauberEvent->GetImpactParameter());    
    
  }//End Loop Over Glauber Tree

  //Compute the Average Npart, Ncoll, and Impact Parameter for each centrality bin
  for (Int_t iCentBin=0; iCentBin<nCentBins; iCentBin++){

    //If there are not entries for a centrality bin then set its errors to 0
    if (nPart[iCentBin].size() == 0){
      glauberResult->nPartMeans.push_back(0);
      glauberResult->nCollMeans.push_back(0);
      glauberResult->impactParamMeans.push_back(0);

      glauberResult->nPartErrors.push_back(0);
      glauberResult->nCollErrors.push_back(0);
      glauberResult->impactParamErrors.push_back(0);

      continue;
    }
    
    
    //Averages
    glauberResult->nPartMeans.push_back(TMath::Mean((Int_t)nPart[iCentBin].size(),&nPart[iCentBin].at(0)));
    glauberResult->nCollMeans.push_back(TMath::Mean((Int_t)nColl[iCentBin].size(),&nColl[iCentBin].at(0)));
    glauberResult->impactParamMeans.push_back((double)TMath::Mean((Int_t)impactParam[iCentBin].size(),
								  &impactParam[iCentBin].at(0)));
    
    //Errors
    glauberResult->nPartErrors.push_back(TMath::RMS((Int_t)nPart[iCentBin].size(),
						    &nPart[iCentBin].at(0)) / sqrt((Double_t)nPart[iCentBin].size()));
    glauberResult->nCollErrors.push_back(TMath::RMS((Int_t)nColl[iCentBin].size(),
						    &nColl[iCentBin].at(0)) / sqrt((Double_t)nColl[iCentBin].size()));
    glauberResult->impactParamErrors.push_back(TMath::RMS((Int_t)impactParam[iCentBin].size(),
    							  &impactParam[iCentBin].at(0)) / sqrt((Double_t)impactParam[iCentBin].size()));
    
  }
  cout <<"Finished finding nPart and nColl Distributions" <<endl;

  /*
  cout <<"In Each Centrality bin there are this many collisions" <<endl;
  for (Int_t i=0; i<16; i++){
    cout <<i <<"  " <<nPart[i].size() <<endl;
  }
  */
}
