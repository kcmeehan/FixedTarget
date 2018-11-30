#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TSystem.h>
#include <TLatex.h>
#include <THistPainter.h>
#include <TAttLine.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TVector3.h>
#include <TMath.h>

//after- verify that you need all these classes
#include "../submodules/datacollectorreaderlibs/TrackInfo/TrackInfo.h"
#include "../submodules/datacollectorreaderlibs/PrimaryVertexInfo/PrimaryVertexInfo.h"
#include "../submodules/datacollectorreaderlibs/EventInfo/EventInfo.h"
#include "../submodules/datacollectorreaderlibs/DavisDstReader/DavisDstReader.h"
#include "ParticleInfo.h"
#include "UserCuts.h"

using namespace std;

//_____MAIN____________________
void vertexPlotsForStarsim(TString inputDataFile, TString outputFile, Int_t nEvents = -1){

DavisDstReader davisDst(inputDataFile);

TFile *outFile  = new TFile(outputFile,"RECREATE");

TrackInfo *track = NULL;
PrimaryVertexInfo *primaryVertex = NULL;
EventInfo *event = NULL;

//initializing pre-cut vertex histograms
TH1D *VzHisto;
TH2D *VxVyHisto;

VzHisto = new TH1D("AuAu4pt5_zVertex","V_{z} Distribution",140,208,215);
VxVyHisto = new TH2D("AuAu4pt5_xyVertex","V_{y} vs. V_{x} Distribution",500,-5,5,500,-5,5);

Double_t x(0), y(0), z(0), refMultUser(0);
Int_t pvEntries;
Double_t entries;
Double_t runNumber;
if(nEvents > 0) entries = nEvents;
else entries = davisDst.GetEntries();
for(Int_t i=0; i<entries; i++){//loop over triggers
  event = davisDst.GetEntry(i);
	if (!IsGoodEvent(event)) continue;
	runNumber = event->GetRunNumber();
	pvEntries = event->GetNPrimaryVertices();
  for (Int_t j=0; j<pvEntries; j++){//event->primaryVertexArray->GetEntries() 
	  primaryVertex = event->GetPrimaryVertex(j);

    if (!IsGoodVertex(primaryVertex)) continue;
	
	  x = primaryVertex->GetXVertex();
	  y = primaryVertex->GetYVertex();
	  z = primaryVertex->GetZVertex();
	
    //track loop to calculate variables for event cuts
		Int_t nTracks = 0;
		Int_t nPrimaryTracks = primaryVertex->GetNPrimaryTracks();
		for(Int_t k = 0; k<nPrimaryTracks;k++){
		  track = primaryVertex->GetPrimaryTrack(k);
			if (!IsGoodTrack(track, false)) continue;
			nTracks++;
		}

		//Centrality Selection
		if (nTracks < 153 || nTracks > 240) continue;

    if (!IsGoodVertex(primaryVertex)) continue;
    VzHisto->Fill(z); 
    VxVyHisto->Fill(x,y);
 }//end of loop over vertices
}//end of loop over triggers

outFile->Write();

}//end of function
