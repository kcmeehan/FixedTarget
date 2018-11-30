//Functions used to bin events and cut on tracks

Bool_t IsGoodTrack(MiniMcReader *minimcReader, Int_t trackIndex, TString trackType, Bool_t useThisCut=true);
Double_t GetCentralityPercent(int centBin);
Int_t GetCentralityBin(TTree *centralityTree, CentralityDatabase *centralityDatabase,
                       std::vector<Long64_t> *runNumberLookUpTable, Long64_t runNumber, Long64_t eventNumber);
std::vector<Long64_t> BuildRunNumberLookUpTable(TTree *centralityTree, CentralityDatabase *centralityDatabase);
Int_t GetCentralityBinOfSimulatedEvent(Double_t centVariable, Double_t energy);
