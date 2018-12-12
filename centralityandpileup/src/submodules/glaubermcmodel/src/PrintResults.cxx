#include <iostream>
#include <iomanip>
#include <vector>

#include "TString.h"

#include "inc/ReturnStructs.h"

void PrintResults(NegBinomialSearchResults *results, Int_t iCentBin,
		  Double_t nPartSysErr, Double_t nCollSysErr,
		  Double_t impactParamSysErr){

  Int_t colWidth = 13;
    
  if (iCentBin == 0){
    cout <<"\n" <<setw(colWidth*7) <<"-----Centrality Binning Study Results-----\n";

    cout <<setw(colWidth) <<left <<"BinIndex"
	 <<setw(colWidth) <<left <<"% Top Cent."
	 <<setw(colWidth) <<left <<"Mult. Cut"
	 <<setw(colWidth) <<left <<"<Npart>"
	 <<setw(colWidth) <<left <<"+- Stat"
	 <<setw(colWidth) <<left <<"+- Sys"
      	 <<setw(colWidth) <<left <<"<Ncoll>"
	 <<setw(colWidth) <<left <<"+- Stat"
	 <<setw(colWidth) <<left <<"+- Sys"
      	 <<setw(colWidth) <<left <<"<b>"
	 <<setw(colWidth) <<left <<"+- Stat"
	 <<setw(colWidth) <<left <<"+- Sys"
	 <<endl;

  }
  
  cout <<setw(colWidth) <<left  <<iCentBin
       <<setw(colWidth)    <<left  <<TString::Format("%g",results->centralityBinDefinitions[iCentBin])
       <<setw(colWidth)    <<left  <<results->centralityBinCuts[iCentBin]
       <<setw(colWidth)    <<left  <<results->nPartMeans[iCentBin]
       <<setw(colWidth)    <<left  <<results->nPartErrors[iCentBin]
       <<setw(colWidth)    <<left  <<nPartSysErr 
       <<setw(colWidth)    <<left  <<results->nCollMeans[iCentBin]
       <<setw(colWidth)    <<left  <<results->nCollErrors[iCentBin]
       <<setw(colWidth)    <<left  <<nCollSysErr
       <<setw(colWidth)    <<left  <<results->impactParamMeans[iCentBin]
       <<setw(colWidth)    <<left  <<results->impactParamErrors[iCentBin]
       <<setw(colWidth)    <<left  <<impactParamSysErr <<"\n";
  


}
