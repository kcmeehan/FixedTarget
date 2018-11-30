#ifndef MINIMCREADER_H
#define MINIMCREADER_H

#ifdef private
#undef private
#endif

//Forward Declarations
class TTree;

class MiniMcReader : public TObject {

 private:
  TTree *miniMCTree;
  //static const int kMaxEntries = 10000;
  int kMaxEntries; 
  
  //Event Level Variables
  Int_t runNumber, eventNumber;
  Int_t nEmbTracks, nMatchTracks, nSplitTracks;
  Int_t refMult, originMult, centrality, centralMult;
  Float_t embVertexX, embVertexY, embVertexZ;

  //Embedded Track Variables
  std::vector<float>  embTrackPt,        embTrackPz;
  std::vector<float>  embTrackEta,       embTrackPhi;
  std::vector<unsigned short> embTrackGeantID,   embTrackParentGeantID;
  std::vector<short>  embTrackNHits;

  //Matched Track Variables
  std::vector<float> matchTrackPtEmb,    matchTrackPzEmb;
  std::vector<float> matchTrackPtReco,   matchTrackPzReco;
  std::vector<float> matchTrackEtaEmb,   matchTrackPhiEmb;
  std::vector<float> matchTrackEtaReco,  matchTrackPhiReco;
  std::vector<float> matchTrackDCAGl,    matchTrackdEdx;
  std::vector<unsigned short> matchTrackGeantID, matchTrackParentGeantID;
  std::vector<short> matchTrackNHits,    matchTrackNFitPts;
  std::vector<short> matchTrackFlag,     matchTrackNHitsdEdx;
  std::vector<short> matchTrackNPossPts;

  //Split Track Variables
  std::vector<float> splitTrackPtEmb,    splitTrackPzEmb;
  std::vector<float> splitTrackPtReco,   splitTrackPzReco;
  std::vector<float> splitTrackEtaEmb,   splitTrackPhiEmb;
  std::vector<float> splitTrackEtaReco,  splitTrackPhiReco;
  std::vector<float> splitTrackDCAGl,    splitTrackdEdx;
  std::vector<unsigned short> splitTrackGeantID, splitTrackParentGeantID;
  std::vector<short> splitTrackNHits,    splitTrackNFitPts;
  std::vector<short> splitTrackFlag,     splitTrackNHitsdEdx;
  std::vector<short> splitTrackNPossPts;


  void Init();
  Bool_t CheckEmbTrackCount( int index );
  Bool_t CheckMatchedTrackCount( int index );
  Bool_t CheckSplitTrackCount( int index );

  
 public:
  MiniMcReader(TTree *tree);
  virtual ~MiniMcReader();
  void Reset();

  //GETS
  Int_t GetNMaxEntries(){ return kMaxEntries; }

  //Event Gets
  Long64_t GetRunNumber()      { return runNumber;    }
  Long64_t GetEventNumber()    { return eventNumber;  }
  Int_t    GetNEmbeddedTracks(){ return nEmbTracks;   }
  Int_t    GetNMatchedTracks() { return nMatchTracks; }
  Int_t    GetNSplitTracks()   { return nSplitTracks; }
  Int_t    GetRefMult()        { return refMult;      }
  Int_t    GetCentralMult()    { return centralMult;  }
  Int_t    GetOriginalRefMult(){ return originMult;   }
  Int_t    GetCentrality()     { return centrality;   }
  Float_t  GetXVertexEmb()     { return embVertexX;   }
  Float_t  GetYVertexEmb()     { return embVertexY;   }
  Float_t  GetZVertexEmb()     { return embVertexZ;   }

  //Embedded Track Gets
  Float_t  GetEmbTrackPt(int index);
  Float_t  GetEmbTrackPz(int index);
  Float_t  GetEmbTrackEta(int index);
  Float_t  GetEmbTrackPhi(int index);
  UShort_t GetEmbTrackGeantID(int index);
  UShort_t GetEmbTrackParentGeantID(int index);
  Short_t  GetEmbTrackNHits(int index);

  //Matched Track Gets
  Float_t GetMatchedTrackPtEmb(int index);
  Float_t GetMatchedTrackPzEmb(int index);
  Float_t GetMatchedTrackEtaEmb(int index);
  Float_t GetMatchedTrackPhiEmb(int index);
  Float_t GetMatchedTrackPtReco(int index);
  Float_t GetMatchedTrackPzReco(int index);
  Float_t GetMatchedTrackEtaReco(int index);
  Float_t GetMatchedTrackPhiReco(int index);
  Float_t GetMatchedTrackDCAGl(int index);
  Float_t GetMatchedTrackdEdx(int index);
  UShort_t GetMatchedTrackGeantID(int index);
  UShort_t GetMatchedTrackParentGeantID(int index);
  Short_t GetMatchedTrackNHits(int index);
  Short_t GetMatchedTrackNHitsFit(int index);
  Short_t GetMatchedTrackNHitsdEdx(int index);
  Short_t GetMatchedTrackNHitsPoss(int index);
  Short_t GetMatchedTrackFlag(int index);

  //Split Track Gets
  Float_t GetSplitTrackPtEmb(int index);
  Float_t GetSplitTrackPzEmb(int index);
  Float_t GetSplitTrackEtaEmb(int index);
  Float_t GetSplitTrackPhiEmb(int index);
  Float_t GetSplitTrackPtReco(int index);
  Float_t GetSplitTrackPzReco(int index);
  Float_t GetSplitTrackEtaReco(int index);
  Float_t GetSplitTrackPhiReco(int index);
  Float_t GetSplitTrackDCAGl(int index);
  Float_t GetSplitTrackdEdx(int index);
  UShort_t GetSplitTrackGeantID(int index);
  UShort_t GetSplitTrackParentGeantID(int index);
  Short_t GetSplitTrackNHits(int index);
  Short_t GetSplitTrackNHitsFit(int index);
  Short_t GetSplitTrackNHitsdEdx(int index);
  Short_t GetSplitTrackNHitsPoss(int index);
  Short_t GetSplitTrackFlag(int index);
  
    
  ClassDef(MiniMcReader,1);
};


#endif
