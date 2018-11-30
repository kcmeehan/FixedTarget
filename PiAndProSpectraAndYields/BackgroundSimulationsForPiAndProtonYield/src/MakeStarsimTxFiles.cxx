//Reads the root trees made from ConvertURQMDToROOT and generates
//.tx files that are the input to STARSIM.

/*
  NOTES: If no root file containing vertex histograms is given, then
         vX=vY=vZ=0 for all events.

	 eventsPerOutputFile is the number of events that will be written
	 to each .tx file before a new one is generated

	 iterations is the number of times each event in the root file
	 will be used in the .tx files. This acts as an event multiplier.
	 If iterations is greater than 1 each time an event is used it 
	 will be used with a new vertex.

	 reflect allows the longitudinal variables to be reflected about
	 the z=0 axis. This is useful in the case of fixed target experiments
	 where you may want flip the kinematics of the event from URQMD.
	 reflect==false means NO reflection
	 reflect==true means reflection
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TString.h>
#include <TRandom3.h>

#include "URQMDTrack.h"
#include "URQMDEvent.h"
#include "URQMDReader.h"
#include "URQMDPidToGEANTPid.h"

void MakeStarsimTxFiles(TString urqmdROOTFileName, TString outDirName, TString vertexFileName,
			TString vertexHistoBaseName, const int eventsPerOutputFile, const int nTotalEventsDesired=-1){

  //Open the vertexFile and get the vertex histograms
  TFile *vertexFile = NULL;
  TH1F *zVertexHisto = NULL;
  TH2F *xyVertexHisto = NULL;
  if (vertexFileName.Length() > 0 && vertexHistoBaseName.Length() > 0){
    vertexFile = new TFile(vertexFileName.Data(),"READ");
    zVertexHisto = (TH1F *)vertexFile->Get(Form("%s_zVertex",vertexHistoBaseName.Data()));
    xyVertexHisto= (TH2F *)vertexFile->Get(Form("%s_xyVertex",vertexHistoBaseName.Data()));

    //The TH1::GetRandom() function uses the same seed each time. For processes
    //running parallel this means the events will have the same sequence of
    //verticies. To avoid this we choose a random number of times to call
    //TH1::GetRandom before actually using it below.
    TRandom3 rand(0);
    int nThrowAways = rand.Uniform(0,10000);
    for (int iThrowAway=0; iThrowAway<nThrowAways; iThrowAway++){
      zVertexHisto->GetRandom();
    }
    
  }

  //Counters for the output tx file
  int iOutputFile(0);
  int nEventsInTxFile(0);
  int iTotalEvents(0);
  
  //Create an output file name from the urqmdROOTFileName
  TString outFileName(urqmdROOTFileName(0,urqmdROOTFileName.Length()-5));
  while (outFileName.First("/") >= 0){
    int index = outFileName.First("/");
    outFileName = outFileName(index+1,outFileName.Length());
  }
  outDirName+="/";
  outFileName.Prepend(outDirName.Data());
  
  //Create the First output tx file
  outFileName.Append(Form("_%04d.tx",iOutputFile));
  ofstream outFile;
  outFile.open(outFileName.Data());
  
  //Create a URQMD Reader and Event Object
  URQMDReader *reader = new URQMDReader(urqmdROOTFileName);
  URQMDEvent *event = NULL;

  //Loop Over the Events in the file(s)
  const long nEntries = reader->GetEntries();
  while (iTotalEvents < nTotalEventsDesired){
    for (long iEntry=0; iEntry<nEntries; iEntry++){
      
      //Get an Event from the Tree
      event = NULL;
      event = reader->GetEntry(iEntry);
      if (!event){
	cout <<"Unable to read event! Event: " <<iEntry <<endl;
	return;
      }
      
      //Make sure that this is an event that is wanted in the tx files
      
      //URQMD reports nucleons of nuclei as indpendent protons and neutrons
      //with a mass reduced by a binding energy AND number of collisions of zero.
      //We don't want these particles so check to make sure the multiplicity of
      //this event is greater than the number of these particles
      int nBoundNucleons = event->GetNNucleonsOffMass();
      
      if (nBoundNucleons == event->GetMultiplicity()){
	continue;
      }

      //If this output file has enough events,
      //then open a new one and increment file counter
      if (nEventsInTxFile >= eventsPerOutputFile){
	
	outFile.close();
	
	iOutputFile++;
	outFileName = outFileName(0,outFileName.Length()-7);
	outFileName.Append(Form("%04d.tx",iOutputFile));
	outFile.open(outFileName.Data());
	
	nEventsInTxFile = 0;
      }
      
      //Set the event vertex if desired
      if (zVertexHisto && xyVertexHisto){
	event->SetVertex(zVertexHisto,xyVertexHisto);
      }
      
      event->PrintEventInTxFormat(&outFile);
      nEventsInTxFile++;
      iTotalEvents++;
      
    }//End Loop Over Entries
    
  } //End while loop to reach total number of desired events 
  
}
