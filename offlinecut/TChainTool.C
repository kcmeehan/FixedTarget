//TChainTool.C
//a routine to chain some block files listed in filelist.
//by Xianglei Zhu @ 2008

#include "iostream"
#include "fstream"
#include "TChain.h"

TChain* ChainThem(const char* filelist, const char* treename, int nlist, int block){

   cout << ">>> Load Chain from file: " << filelist << endl;
   ifstream fList(filelist);
   if (!fList)
   {
	cout << "!!! Can't open file " << filelist << endl;
	return NULL;
   }

   TChain *globChain = new TChain(treename);

   int Ncount = 0;
   int Nfiles = 0;
   char lineFromFile[255];
   while(fList.getline(lineFromFile, 250))
   {
	Ncount++;
	if(Ncount<=nlist*block)continue;
	if(Ncount>(nlist+1)*block)break;
	if(globChain->Add(lineFromFile,0)){
	   cout << ">> File '" << lineFromFile << "' has been loaded" << endl;
	   Nfiles ++;
	}
	else
	   cout << ">> Can't load file '" << lineFromFile << "'" << endl;
   }

   cout << ">> Total number of entries: " << globChain->GetEntriesFast() << endl;
   fList.close();

   if(Nfiles == 0){
	delete globChain;
	return NULL;
   }

   return globChain;
}
