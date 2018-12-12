#include <iostream>
#include <vector>

#include "DetermineCentralityBin.h"

using namespace std;

//_________________________________________________________________________________
Int_t DetermineCentralityBin16(std::vector<double> centralityCuts, Double_t centralityVar){

  //This Function loops over the centrality bins and determines which bin this event
  //belongs to based on the value of its centralityVar

  const Int_t nCentBins(16);
  for (Int_t iCentBin=0; iCentBin<nCentBins; iCentBin++){

    //Use this as long as we are not looking at the highest cent bin
    if (iCentBin+1 < nCentBins &&
	centralityVar >= centralityCuts[iCentBin] &&
	centralityVar < centralityCuts[iCentBin+1])
      return iCentBin;

    //If we are looking at the highest cent bin then the centrality var
    //only needs to be greater with no upper bound
    else if (iCentBin+1 == nCentBins &&
	     centralityVar >= centralityCuts[iCentBin])
      return iCentBin;

  }//End Loop Over Centrality Bins

  //If for some reason we don't find a centrality bin then return something silly
  return -1;

}

//___________________________________________________________________________________
Int_t DetermineCentralityBin9(std::vector<double> centralityCuts, Double_t centralityVar){

  //This function simply converts the 16 bin centrality down to 9 bins
  
  Int_t centralityBin16 = DetermineCentralityBin16(centralityCuts, centralityVar);

  //Consider Special Cases

  //If this is the highest cent bin
  if (centralityBin16 == 15)
    return 8;
  else if (centralityBin16 == 14)
    return 7;
  else if (centralityBin16 < 0) //This is the case where a bin was not found
    return centralityBin16;

  //The General Case
  return (Int_t)(0.5 * centralityBin16);
  

}

//__________________________________________________________________________________
Int_t DetermineCentralityBin(std::vector<double> centralityCuts, Double_t centralityVar, Int_t nCentBins){

  //This Function simply allows the user to choose from the two above

  if (nCentBins == 16)
    return DetermineCentralityBin16(centralityCuts, centralityVar);

  //Otherwise
  return DetermineCentralityBin9(centralityCuts, centralityVar);

}
