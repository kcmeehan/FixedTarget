// this is a txt file reader to store efficiency factors into TH3D histograms

#include <iostream>
#include <fstream>
#include <cmath>
#include "TFile.h"
#include "TH3D.h"
using namespace std;

void read_txt(){
	TFile * outfile = new TFile("KMinusEffTable.root","recreate");
	//Double_t xbin[8] = { 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 80.0 };
	//TH3D * table = new TH3D("PiMinusEffTable","#pi^{-} efficiency table",7,xbin,20,-2.05,-0.05,150,0.0,1.5);
	TH3D * table = new TH3D("KMinusEffTable","#K^{-} efficiency table",7,-0.5,6.5,20,-2.05,-0.05,150,0.0,1.5);
	//table->GetXaxis()->SetTitle("Centrality (%)");
	table->GetXaxis()->SetTitle("Centrality bin");
	table->GetYaxis()->SetTitle("Rapidity");
	table->GetZaxis()->SetTitle("m_{T}-m_{0} (GeV/c^{2})");
	std::ifstream infile("KMinusEffTable.txt");
	Int_t tablebin, centbin, rapiditybin, transvermassbin;
	Double_t transvermass, efficiency;
	while(infile >> centbin >> rapiditybin >> transvermass >> efficiency){
		std::cout<<centbin<<"    "<<rapiditybin<<"    "<<transvermass<<"    "<<efficiency<<endl;
		transvermassbin = (Int_t)std::floor( ( transvermass - 0.0 )*(Double_t)150 / ( 1.5 - 0.0 ) ) + 1;
		tablebin = table->GetBin(7-centbin,rapiditybin+1,transvermassbin);
		table->SetBinContent(tablebin,efficiency);
	}
	table->Write();
}
