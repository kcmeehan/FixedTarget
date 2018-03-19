#include <iostream>
#include <exception>

#include "StDcaGeometry.h"

// #include "chain.h"

#include "TList.h"
#include "TString.h"
#include "TChain.h"
#include "loadlist.h"
#include "PicoDst.h"
#include <sstream>

int main( int argc, char* argv[] ) {

	Int_t nEvents = stoi(argv[2]);
	Char_t *inputFile= argv[1];
	Char_t *outputdir = argv[3];
	Int_t index = stoi(argv[4]);

	TChain *t = new TChain("PicoDst");
	loadListRange(t,inputFile,index,1);
	stringstream outputfile;
	outputfile << outputdir << argv[4] << ".root";
	const Char_t * outf = outputfile.str().c_str();
      	PicoDst *pDst = new PicoDst( t, (Char_t*)outf );

	pDst->Loop( nEvents );
	
	
	return 0;
}
