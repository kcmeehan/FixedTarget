#include <iostream>
#include <utility>
//#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TSystem.h"
#include "TMath.h"
#include "TArrayD.h"

#include "GlauberClass.h"
#include "ReturnStructs.h"

//Functions Defined Below
Double_t ComputeHistogramChiSquared(TH1D *hData, TH1D *hSim, Int_t startBin, Int_t stopBin);
TH1D *HistogramDerivative(TH1D *h);

//Main_____________________________________________________________
NegBinomialSearchResults FindBestFitNegativeBinomialParameters(
							       TH1D *dataHisto, TTree *glauberTree, TFile *outFile,
							       Double_t startMatchingBinCenter, Double_t stopMatchingBinCenter,
							       Int_t nIterations=100, Int_t iTrial=0){
  
  //This is the bin for which we will start the matching procedure
  Int_t startBin = dataHisto->FindBin(startMatchingBinCenter);

  //This is the bin for which we will end the matching procedure. 
  //By default the last bin of the dataHisto is used as the stopping bin.
  //However, if the user has passed in a valid value for the stop bin then use it instead.
  Int_t stopBin = dataHisto->GetNbinsX();
  if (stopMatchingBinCenter > startMatchingBinCenter)
    stopBin = dataHisto->FindBin(stopMatchingBinCenter);
  
  //Prepare the Data Histogram...do this only if sumw2 hasn't been called before
  //this is to protect the histogram in the case of mulitple iterations
  if ( ((TArrayD *)dataHisto->GetSumw2())->GetSize() == 0){
    dataHisto->Sumw2();
    dataHisto->Scale(1.0/(Double_t)dataHisto->Integral(startBin,dataHisto->GetNbinsX()));
    dataHisto->SetMarkerColor(kBlack);
    dataHisto->SetMarkerStyle(kFullCircle);
  }
  
  //Histogram which this simulation will creat, fill, and delete for each iteration
  TH1D *simHisto, *bestFitHisto = NULL;
  TRandom3 rand(0);
  
  //Canvas on which the histograms will be drawn
  TCanvas *canvas = new TCanvas("canvas","canvas",20,20,800,400);
  canvas->Divide(2,1);
  canvas->cd(1);
  gPad->SetLogy();

  //This Graph is Filled with the the Chi2 Values
  TGraph2D *chiSquaredGraph = new TGraph2D();
  chiSquaredGraph->SetName(TString::Format("chiSquaredGraph_%d",iTrial));
  chiSquaredGraph->SetTitle("#Chi^{2} Fit Results;p;n;1/#Chi^{2}");
  chiSquaredGraph->SetMarkerStyle(kFullCircle);

  //Parameters Describing the best fit
  Double_t bestInvChi2(0), bestN(0), bestP(0);

  //Create an instance of the GlauberClass to hold the info from the tree
  GlauberClass *glauberEvent = 0;
  glauberTree->FindBranch("GlauberData")->SetAddress(&glauberEvent);

  //For each iteration choose a new value for n and p for the negative binomial
  //distribution. The set of n and p that create a particle multiplicity distribution
  //which maximizes the 1/Chi2 will be one used to determine the centrality cuts
  Double_t fractionComplete(0);
  for (Int_t iIter=0; iIter<nIterations; iIter++){

    //Create a new histogram to store the particle multiplicity, it needs to have the
    //same number of bins and range as the data histogram
    simHisto = new TH1D("","",dataHisto->GetNbinsX(),
			dataHisto->GetBinLowEdge(1),
			dataHisto->GetBinLowEdge(dataHisto->GetNbinsX())+dataHisto->GetBinWidth(1));

    //Variables that will be changing each time through the loop    
    Double_t chi2(0), n(0), p(0), nParticles(0);

    //Choose values for n and p and set the NB With them
    //If we are less than half of the way through the iterations
    //then sample the parameter space uniformly, 
    if (fractionComplete < .5){
      n = rand.Uniform(0.2,0.9);
      p = rand.Uniform(0.2,0.9);
    }
    //If we are in the last half of iterations, then choose from a Gaussian Distribution
    //centered on the current parameters corresponding to the best Inverse Chi2
    else {
      n = rand.Gaus(bestN,0.1/(Double_t)iIter);
      p = rand.Gaus(bestP,0.1/(Double_t)iIter);
    }
    
    glauberEvent->SetNegativeBinomialParameters(p,n);

    //Loop Over all the entries in the galuber tree and construct the multiplicity distribution
    for (Int_t iEvent=0; iEvent<glauberTree->GetEntries(); iEvent++){

      glauberTree->GetEntry(iEvent);

      //Produce the Particles from the Event
      nParticles = glauberEvent->ProduceParticles();
      simHisto->Fill(nParticles);
      
    }//End Loop Over glauberTree Entries

    //Prepare the simulated Histo for comparison with data histo
    simHisto->Sumw2();
    Double_t scaleFactor = simHisto->Integral(startBin,simHisto->GetNbinsX());

    //If the scale factor is less than 1 then this is a bad histogram...so pretend like
    //this trial never happened
    if (scaleFactor < 1){
      iIter--;
      continue;
    }

    //Scale the Histogram
    simHisto->Scale(1.0/(Double_t)simHisto->Integral(startBin,simHisto->GetNbinsX()));

    //Compute the Chi Squared
    chi2 = ComputeHistogramChiSquared(dataHisto,simHisto,startBin,stopBin);

    //If this combination is the best fit then keep it
    if (1.0/chi2 > bestInvChi2){
      bestInvChi2 = 1.0/chi2;
      bestN = n;
      bestP = p;
      if (bestFitHisto != NULL)
	bestFitHisto->Delete();
      bestFitHisto = (TH1D *)simHisto->Clone(TString::Format("bestFit_%d",iTrial));
      bestFitHisto->SetMarkerColor(kRed);
      bestFitHisto->SetLineColor(kRed);
      
    }

    //Fill the Chi2 Graph
    chiSquaredGraph->SetPoint(chiSquaredGraph->GetN(),p,n,1.0/chi2);

    //Draw and Update the Canvas
    canvas->cd(1);
    dataHisto->Draw("E");
    bestFitHisto->Draw("SAME");
    simHisto->Draw("SAME");
  
    canvas->Update();
    //gSystem->Sleep(100);
    
    delete simHisto;

    fractionComplete = (Double_t)iIter / (Double_t)nIterations;

  }//End Loop Over nIterations

    canvas->cd(2);
    chiSquaredGraph->Draw("APCOL");

    //Save Output to file
    outFile->cd();
    bestFitHisto->Write();
    chiSquaredGraph->Write();
    
    //Clean Up
    delete canvas;

  
    //return std::make_pair(bestN,bestP);
    NegBinomialSearchResults results;
    results.n = bestN;
    results.p = bestP;
    results.InverseChi2 = bestInvChi2;
    results.bestFitHisto = bestFitHisto;
    results.chi2Graph = chiSquaredGraph;

    return results;
}


//_________________________________________________________________
Double_t ComputeHistogramChiSquared(TH1D *hData, TH1D *hSim, Int_t startBin, Int_t stopBin){

  Double_t chi2(0);
  Double_t temp(0);
  
  for (Int_t iBin=startBin; iBin<stopBin; iBin++){

    temp = pow(hData->GetBinContent(iBin) - hSim->GetBinContent(iBin),2)
      / (pow(hData->GetBinError(iBin),2) + pow(hSim->GetBinError(iBin),2));
    
    if (TMath::IsNaN(temp))
      continue;

    chi2 += temp;

  }

  return chi2;
}

//__________________________________________________________________
TH1D *HistogramDerivative(TH1D *h){

  TH1D *hDeriv = new TH1D("hDeriv","hDeriv",
			  h->GetNbinsX(),
			  h->GetBinLowEdge(1),
			  h->GetBinLowEdge(h->GetNbinsX())+h->GetBinWidth(1));

  for (Int_t iBin=1; iBin<h->GetNbinsX()-1; iBin++){

    hDeriv->SetBinContent(iBin,h->GetBinContent(iBin+1) - h->GetBinContent(iBin));

  }

  return hDeriv;
  
}
