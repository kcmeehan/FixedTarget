

#include <iostream>
#include <exception>

#include "StDcaGeometry.h"

// #include "chain.h"

#include "TList.h"
#include "TString.h"
#include "TChain.h"

#include "PicoDst.h"

int main( int argc, char* argv[] ) {

	Int_t nEvents = stoi( argv[2] );
	Char_t *inputFile= argv[1];
	Char_t *outputFile = argv[3];

	//read the list of files                                                                                                                                                         
	  TList nameList;
	  char str[2000];
	  fstream file_op(inputFile,ios::in);
	  while(file_op >> str){
	    nameList.Add(new TObjString(str));
	  }

	  //put the list into chain                                                                                                                                            
	  TChain *t = new TChain("PicoDst");
	  TIter next(&nameList);
	  TObjString *fileNm;
	  int i=0;
	  while(fileNm=( TObjString*)next()){
	    t->AddFile(fileNm->String());
	    cout<<i<<": "<<fileNm->String()<<endl;
	    i++;
	  }


	  PicoDst *pDst = new PicoDst( t, outputFile );

	  pDst->Loop( nEvents );


	return 0;
}
