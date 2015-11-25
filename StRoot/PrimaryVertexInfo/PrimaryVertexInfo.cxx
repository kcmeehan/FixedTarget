#include <TObject.h>
#include "TClonesArray.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

#include "StRoot/TrackInfo/TrackInfo.h"
#include "PrimaryVertexInfo.h"

ClassImp(PrimaryVertexInfo);

//____________________________________________________________________________
PrimaryVertexInfo::PrimaryVertexInfo(){

  vertexIndex = -999;
  nPrimaryTracks = -999;
  ntofMatches = -999;
  nPions = -999;
  refMult = -999;
  refMultUser = -999;
  refMultUserEtaLow = -.05;
  refMultUserEtaHigh = .05;
  xVertex = -999;
  yVertex = -999;
  zVertex = -999;

  trackArray = new TClonesArray("TrackInfo",0);

}

//___________________________________________________________________________
PrimaryVertexInfo::~PrimaryVertexInfo(){

  delete trackArray;  

}

//___________________________________________________________________________
void PrimaryVertexInfo::SetRefMultUserRange(Double_t etaLow, Double_t etaHigh){

  refMultUserEtaLow = etaLow;
  refMultUserEtaHigh = etaHigh;

}

//___________________________________________________________________________
void PrimaryVertexInfo::SetPrimaryVertexInfo(StMuDst *dst, Int_t index){

  vertexIndex    = index;
  nPrimaryTracks = dst->primaryTracks()->GetEntries();
  ntofMatches    = 0; //Counted in Loop Below
  refMult        = dst->event()->refMult();
  refMultUser    = 0; //Counted In Loop Below
  nPions         = 0; //Counted in Loop Below
  xVertex        = dst->event()->primaryVertexPosition().x();
  yVertex        = dst->event()->primaryVertexPosition().y();
  zVertex        = dst->event()->primaryVertexPosition().z();

  //Loop Over All the Primary Tracks and Add them to the Track Array
  //Also count them as contributing to the refMultUser and ntofMatches
  //if they satisfy the respective conditions
  for (Int_t trackIndex=0; trackIndex < nPrimaryTracks; trackIndex++){
    
    //Add the Track to the Track Array
    AddTrack(dst->primaryTracks(trackIndex),trackIndex);
    
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

  }//End Loop Over Track Index

}

//____________________________________________________________________________
void PrimaryVertexInfo::AddTrack(StMuTrack *track, Int_t index){

  TrackInfo *tempTrack = (TrackInfo *)trackArray->ConstructedAt(index);
  tempTrack->SetTrackInfo(track);  


}

//____________________________________________________________________________
void PrimaryVertexInfo::ResetPrimaryVertexInfo(){

  vertexIndex = -999;
  nPrimaryTracks = -999;
  ntofMatches = -999;
  nPions = -999;
  refMult = -999;
  refMultUser = -999;
  refMultUserEtaLow = -.05;
  refMultUserEtaHigh = .05;
  xVertex = -999;
  yVertex = -999;
  zVertex = -999;

  trackArray->Delete();

}

//____________________________________________________________________________
void PrimaryVertexInfo::PrintPrimaryVertexInfo(){

  cout <<"VertexIndex: "      <<vertexIndex     <<"\n"
       <<"nPrimaryTracks: "   <<nPrimaryTracks  <<"\n"
       <<"ntofMatches: "      <<ntofMatches     <<"\n"
       <<"nPions: "           <<nPions           <<"\n"
       <<"refMult: "          <<refMult         <<"\n"
       <<"refMultUser: "      <<refMultUser     <<"\n"
       <<"VertexLocation: x=" <<xVertex <<", y=" <<yVertex <<", z=" <<zVertex <<"\n";
}
