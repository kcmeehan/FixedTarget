#include <TObject.h>
#include "TClonesArray.h"
#include "TTree.h"

#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

#include "StRoot/TrackInfo/TrackInfo.h"
#include "PrimaryVertexInfo.h"

ClassImp(PrimaryVertexInfo);

//____________________________________________________________________________
PrimaryVertexInfo::PrimaryVertexInfo(){

  trackStartIndex    = -999;
  trackStopIndex     = -999;
  vertexIndexMuDst   = -999;
  nPrimaryTracks     = -999;
  ntofMatches        = -999;
  nPions             = -999;
  refMult            = -999;
  refMultUser        = -999;
  refMultPosY        = -999;
  refMultNegY        = -999;
  refMultUserEtaLow  = -.05;
  refMultUserEtaHigh = .05;
  xVertex            = -999;
  yVertex            = -999;
  zVertex            = -999;

}

//___________________________________________________________________________
PrimaryVertexInfo::~PrimaryVertexInfo(){


}

//___________________________________________________________________________
void PrimaryVertexInfo::SetRefMultUserRange(Float_t etaLow, Float_t etaHigh){

  refMultUserEtaLow = etaLow;
  refMultUserEtaHigh = etaHigh;

}

//___________________________________________________________________________
void PrimaryVertexInfo::SetPrimaryVertexInfo(StMuDst *dst){

  trackStartIndex  = trackArray->GetEntries();
  trackStopIndex   = trackStartIndex; //Gets incremented in the loop below
  vertexIndexMuDst = dst->currentVertexIndex();         
  nPrimaryTracks   = dst->primaryTracks()->GetEntries();
  ntofMatches      = 0; //Counted in Loop Below
  refMult          = dst->event()->refMult();
  refMultUser      = 0; //Counted In Loop Below
  refMultPosY      = 0; //Counted in Loop Below
  refMultNegY      = 0; //Counted in Loop Below
  nPions           = 0; //Counted in Loop Below
  xVertex          = dst->event()->primaryVertexPosition().x();
  yVertex          = dst->event()->primaryVertexPosition().y();
  zVertex          = dst->event()->primaryVertexPosition().z();

  //Loop Over All the Primary Tracks and Add them to the Track Array
  //Also count them as contributing to the refMultUser and ntofMatches
  //if they satisfy the respective conditions
  for (Int_t trackIndex=0; trackIndex < nPrimaryTracks; trackIndex++){

    //Add the Track to the Track Tree
    AddTrack(dst->primaryTracks(trackIndex),vertexArray->GetEntries()-1);
   
    //Increment the TrackStopIndex
    trackStopIndex++;

    //If the track has a matchFlag > 0 then 
    if (dst->primaryTracks(trackIndex)->btofPidTraits().matchFlag() > 0)
      ntofMatches++;

    //Count it as part of refMultUser
    if (dst->primaryTracks(trackIndex)->eta() > refMultUserEtaLow &&
	dst->primaryTracks(trackIndex)->eta() < refMultUserEtaHigh)
      refMultUser++;
    
    //Increment nPion if this track passes the pion cut
    if (fabs(dst->primaryTracks(trackIndex)->nSigmaPion()) < 2.0){
      
      if (dst->primaryTracks(trackIndex)->charge() > 0 &&
	  dst->primaryTracks(trackIndex)->nSigmaProton() < -1.0)
	nPions++;
      else
	nPions++;     
    }

    //Increment refMultPosY
    if (dst->primaryTracks(trackIndex)->eta() >= 0.0 &&
	dst->primaryTracks(trackIndex)->eta() < 1.0)
      refMultPosY++;

    //Increment refMultNegY
    if (dst->primaryTracks(trackIndex)->eta() >= -1.0 &&
	dst->primaryTracks(trackIndex)->eta() < 0.0)
      refMultNegY++;

  }//End Loop Over Track Index

}

//____________________________________________________________________________
void PrimaryVertexInfo::AddTrack(StMuTrack *stTrack, Int_t vertexIndex){

  track = new((*trackArray)[trackArray->GetEntriesFast()]) TrackInfo();
  //track = (TrackInfo *)trackArray->ConstructedAt(trackArray->GetEntriesFast());

  if (!track){
    fputs("ERROR: PrimaryVertexInfo::AddTrack() - Pointer to track not obtained from track array.", stderr);
    exit (EXIT_FAILURE);
  }

  track->SetTrackInfo(stTrack,vertexIndex);

}

//____________________________________________________________________________
void PrimaryVertexInfo::ResetPrimaryVertexInfo(){

  

}

//____________________________________________________________________________
void PrimaryVertexInfo::PrintPrimaryVertexInfo(Bool_t printTracks){

  cout <<"VertexIndexMuDst: " <<vertexIndexMuDst <<"\n"
       <<"nPrimaryTracks: "   <<nPrimaryTracks   <<"\n"
       <<"ntofMatches: "      <<ntofMatches      <<"\n"
       <<"nPions: "           <<nPions           <<"\n"
       <<"refMult: "          <<refMult          <<"\n"
       <<"refMultUser: "      <<refMultUser      <<"\n"
       <<"refMultPosY: "      <<refMultPosY      <<"\n"
       <<"refMultNegY: "      <<refMultNegY      <<"\n"
       <<"VertexLocation: x=" <<xVertex <<", y=" <<yVertex <<", z=" <<zVertex <<"\n";

  if (!printTracks)
    return;

  for (Int_t iTrack=trackStartIndex; iTrack<trackStopIndex; iTrack++){
    track = (TrackInfo *)trackArray->At(iTrack);
    track->PrintTrackInfo();
  }

}

//____________________________________________________________________________
void PrimaryVertexInfo::SetTrackPtr(TrackInfo *val){

  if (!val){
    fputs("ERROR: PrimaryVertexInfo::SetTrackPtr() - Pointer to track is NULL!\n",stderr);
    exit (EXIT_FAILURE);
  }
  
  track = val;
  
}

//____________________________________________________________________________
void PrimaryVertexInfo::SetTrackArrayPtr(TClonesArray *val){

  if (!val){
    fputs("ERROR: PrimaryVertexInfo::SetTrackArrayPtr() - Pointer to track array is NULL!\n",stderr);
    exit (EXIT_FAILURE);
  }

  trackArray = val;

}

//____________________________________________________________________________
void PrimaryVertexInfo::SetVertexArrayPtr(TClonesArray *val){
  
  if (!val){
    fputs("ERROR: PrimaryVertexInfo::SetVertexArrayPtr() - Pointer to vertex array is NULL!\n",stderr);
    exit (EXIT_FAILURE);
  }
  
  vertexArray = val;

}
