#ifndef loadlist_h
#define loadlist_h
#include "TChain.h"
#include "string"
using namespace std;
void loadListRange(  TChain * _chain, string _listFile, int _jobIndex, int _splitBy ){
  
  int min = _jobIndex * _splitBy;
  int max = (_jobIndex + 1) * _splitBy - 1;
  
  if ( 0 > _splitBy || 0 > _jobIndex ){
    return;
  }

  int fileIndex = 0;

  string line;
  ifstream fListFile( _listFile.c_str());
  if ( fListFile.is_open() ){

    while ( getline( fListFile, line ) ){
      
      if ( fileIndex < min || fileIndex > max ){
	// do not add
      } else {
	_chain->Add( line.c_str() );
      }
      fileIndex ++;
    }

    fListFile.close();
    
  } else {
    cout << "ERROR" << endl;
  }
} // loadListRange

#endif
