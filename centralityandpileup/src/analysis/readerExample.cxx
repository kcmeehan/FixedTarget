//This is just a simple example of how to read a davis DST and create a new file with some stuff

//C++ includes
#include <iostream>

//ROOT includes
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TClonesArray.h>
#include <TCanvas.h>

//DataCollectorReaderLibs Sub-Module Includes
#include "TrackInfo.h"
#include "PrimaryVertexInfo.h"
#include "EventInfo.h"
#include "DavisDstReader.h"
#include "ParticleInfo.h"
#include "StRefMultExtendedCorr.h"
#include "UserCuts.h"

void reader(TString inputDataFile, Int_t maxEvents=-1, TString outputFile=""){

  //Get the Z-Vertex Cuts
  std::pair<double,double> zVertexCuts = GetZVertexCuts();

  //Read the input files
  //If there are valid zVertex cuts then use them in the constructor of the davisdstreader
  DavisDstReader *davisDst = NULL;
  if (zVertexCuts.first != -999 && zVertexCuts.second != 999)
    davisDst = new DavisDstReader(inputDataFile,zVertexCuts.first,zVertexCuts.second);
  else
    davisDst = new DavisDstReader(inputDataFile);

  //If no outputFile was specified then we won't produce one
  //otherwise we will
  TFile *outFile = NULL;
  if (outputFile.CompareTo(""))
    outFile = new TFile(outputFile,"RECREATE");

  //Create some class pointers we will use to access the data in the tree
  TrackInfo *track = NULL;
  PrimaryVertexInfo *primaryVertex = NULL;
  EventInfo *event = NULL;

  //As a demonstration lets fill a few histograms...
  //An event level one...
  TH1D *nPrimaryVertexHisto = new TH1D("nPrimaryVertexHisto",";Number of Primary Vertices;",20,0,20);
  //A vertex level one...
  TH1D *zVertexHisto = new TH1D("zVertexHisto",";Z-Vertex Position (cm);dN/dZ",460,-230,230);
  //And a track level one...
  TH2D *dEdxHisto = new TH2D("dEdxHisto",";|p|q;dE/dx (KeV/cm)",500,.09,5,500,.9,50);


  //Set the number of events to run over
  Long64_t nEvents(0);
  //If the user has specified a number then use that
  if (maxEvents > 0)
    nEvents = maxEvents;
  //Otherwise run over all the events in the tree
  else 
    nEvents = davisDst->GetEntries();
  
  //Loop Over the Events in the tree. For each event loop over its primary
  //vertices, and for each primary vertex loop over its associated primary tracks
  for (Long64_t iEvent=0; iEvent< nEvents; iEvent++){

    //Get the Event Entry and make sure it is good
    event = davisDst->GetEntry(iEvent);
    if (!IsGoodEvent(event))
      continue;

    //Fill the event level histogram
    nPrimaryVertexHisto->Fill(event->GetNTotalVertices());
    
    //Loop Over the Primary Vertices
    Int_t nPrimaryVertices = event->GetNPrimaryVertices(); 
    for (Int_t iPrimaryVertex=0; iPrimaryVertex<nPrimaryVertices; iPrimaryVertex++){

      //Get the ith primary vertex and make sure it is good
      primaryVertex = event->GetPrimaryVertex(iPrimaryVertex);
      if (!IsGoodVertex(primaryVertex))
	continue;
      
      //Fill the vertex level histogram
      zVertexHisto->Fill(primaryVertex->GetZVertex());

      //Loop Over the Primary Tracks associated with this primary vertex
      Int_t nPrimaryTracks = primaryVertex->GetNPrimaryTracks();
      for (Int_t iPrimaryTrack=0; iPrimaryTrack<nPrimaryTracks; iPrimaryTrack++){

	//Get the ith primary Track and make sure it is good
	track = primaryVertex->GetPrimaryTrack(iPrimaryTrack);
	if (!IsGoodTrack(track))
	  continue;
	
	//Compute the Track's Total Momentum
	Double_t totalMomentum = sqrt(pow(track->GetPt(),2) + pow(track->GetPz(),2));

	//Fill the track level histo
	dEdxHisto->Fill(totalMomentum,1000000*track->GetdEdx());	

      }//End Loop Over Primary Vertex

    }//End Loop Over Primary Vertices

  }//End Loop Over Events

  //Create an instance of the ParticleInfo class to draw the dEdx lines
  ParticleInfo *particleInfo = new ParticleInfo(GetStarLibraryVersion(),true);

  //Create a Canvas to Draw the histograms
  TCanvas *canvas = new TCanvas("canvas","canvas",20,20,1200,400);
  canvas->Divide(3,1);

  //Draw the Histograms
  canvas->cd(1);
  nPrimaryVertexHisto->Draw();

  canvas->cd(2);
  zVertexHisto->Draw();

  canvas->cd(3);
  gPad->SetLogz();
  gPad->SetLogy();
  gPad->SetLogx();
  dEdxHisto->Draw("COLZ");
  particleInfo->GetBichselFunction(PION)->Draw("SAME");
  particleInfo->GetBichselFunction(KAON)->Draw("SAME");
  particleInfo->GetBichselFunction(PROTON)->Draw("SAME");
  particleInfo->GetBichselFunction(ELECTRON)->Draw("SAME");
  particleInfo->GetBichselFunction(DEUTERON)->Draw("SAME");
  particleInfo->GetBichselFunction(ALPHA)->Draw("SAME");  

  //If we are creating an output file then save these histograms
  if (outFile){
    outFile->cd();
    nPrimaryVertexHisto->Write();
    zVertexHisto->Write();
    dEdxHisto->Write();
  }
  
  return;

}
