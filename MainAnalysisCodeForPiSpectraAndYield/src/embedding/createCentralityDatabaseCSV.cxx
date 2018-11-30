//This code reads a data file and generates a .csv centrality database to store the centralities of events. 
//This is used to apply centrality selection with embedding data when obtaining efficiencies.
//The centrality bins are indexed starting at 0 (most central). Pileup returns an index of -2. 
//Events which are not able to be assigned a bin are given the index of -1. 

//C++ includes
#include <iostream>
#include <fstream>

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

using namespace std;

void createCentralityDatabaseCSV(TString inputDataFile, TString outFileName, Int_t maxEvents=-1){

  //Get the Z-Vertex Cuts
  std::pair<double,double> zVertexCuts = GetZVertexCuts();
	Int_t nGoodTracks, runNumber, eveNumber, centBin;

  //Read the input files
  //If there are valid zVertex cuts then use them in the constructor of the davisdstreader
  DavisDstReader *davisDst = NULL;
  if (zVertexCuts.first != -999 && zVertexCuts.second != 999)
    davisDst = new DavisDstReader(inputDataFile,zVertexCuts.first,zVertexCuts.second);
  else
    davisDst = new DavisDstReader(inputDataFile);

  //Create output csv file
	ofstream outFile;
  outFile.open(outFileName);

  //Create some class pointers we will use to access the data in the tree
  TrackInfo *track = NULL;
  PrimaryVertexInfo *primaryVertex = NULL;
  EventInfo *event = NULL;

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

    //Loop Over the Primary Vertices
    Int_t nPrimaryVertices = event->GetNPrimaryVertices(); 
    for (Int_t iPrimaryVertex=0; iPrimaryVertex<nPrimaryVertices; iPrimaryVertex++){

      //Get the ith primary vertex and make sure it is good
      primaryVertex = event->GetPrimaryVertex(iPrimaryVertex);
      if (!IsGoodVertex(primaryVertex))
	continue;

	    runNumber = event->GetRunNumber(); 
			eveNumber = event->GetEventNumber();
      
      //Loop Over the Primary Tracks associated with this primary vertex
      nGoodTracks = 0;
      Int_t nPrimaryTracks = primaryVertex->GetNPrimaryTracks();
      for (Int_t iPrimaryTrack=0; iPrimaryTrack<nPrimaryTracks; iPrimaryTrack++){

				//Get the ith primary Track and make sure it is good
				track = primaryVertex->GetPrimaryTrack(iPrimaryTrack);
				if (!IsGoodTrack(track, false))
					continue;
        nGoodTracks++;	
			}
			
      //determine centrality bin here
      centBin = GetCentralityBin(nGoodTracks, 999, 999); 
       
			outFile<<runNumber<<"   "<<eveNumber<<"   "<<centBin<< endl;

    }//End Loop Over Primary Vertices

  }//End Loop Over Events

  return;

}
