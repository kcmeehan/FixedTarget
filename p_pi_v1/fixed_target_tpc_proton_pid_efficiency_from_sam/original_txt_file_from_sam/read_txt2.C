// this is a txt file reader to read Sam's TPC PID efficiency, and save them into TH2D
// TPC_eff2.txt is same as TPC_eff.txt, except line format was slighted changed to make
// C++ reading more convenient

#include <iostream>
#include <fstream>
#include <cmath>
#include "TFile.h"
#include "TH2D.h"
//using namespace std;

void read_txt2(){
	TFile *outfile = new TFile("TPC_eff.root","recreate");
    
	TH2D *proton_table = new TH2D("ProtonTPCeffTable","Proton TPC PID efficiency table",15,-1.75,-0.25,38,0.05,1.0);
	proton_table->GetYaxis()->SetTitle("Rapidity");
	proton_table->GetZaxis()->SetTitle("m_{T}-m_{0} (GeV/c^{2})");
    
    TH2D *deuteron_table = new TH2D("DeuteronTPCeffTable","Deuteron TPC PID efficiency table",15,-1.75,-0.25,38,0.05,1.0);
    deuteron_table->GetYaxis()->SetTitle("Rapidity");
    deuteron_table->GetZaxis()->SetTitle("m_{T}-m_{0} (GeV/c^{2})");
    
    TH2D *pion_table = new TH2D("PionTPCeffTable","Pion TPC PID efficiency table",15,-1.75,-0.25,38,0.05,1.0);
    pion_table->GetYaxis()->SetTitle("Rapidity");
    pion_table->GetZaxis()->SetTitle("m_{T}-m_{0} (GeV/c^{2})");
    
    TH2D *electron_table = new TH2D("ElectronTPCeffTable","Electron TPC PID efficiency table",15,-1.75,-0.25,38,0.05,1.0);
    electron_table->GetYaxis()->SetTitle("Rapidity");
    electron_table->GetZaxis()->SetTitle("m_{T}-m_{0} (GeV/c^{2})");
    
	std::ifstream infile("TPC_eff2.txt");
	Int_t tablebin, rapiditybin, transvermassbin;
	Double_t rapidity, transvermass, proton_efficiency, deuteron_efficiency, pion_efficiency, electron_efficiency;
    Double_t proton_efficiency_error, deuteron_efficiency_error, pion_efficiency_error, electron_efficiency_error;
    Char_t plusminussymbol[10]; sprintf(plusminussymbol,"+-");
	while(infile >> rapidity >> transvermass >> proton_efficiency >> proton_efficiency_error
          >> deuteron_efficiency >> deuteron_efficiency_error
          >> pion_efficiency >> pion_efficiency_error
          >> electron_efficiency >> electron_efficiency_error
          ){
		/*std::cout<<rapidity<<"    "<<transvermass<<"    "<<proton_efficiency<<" "<<plusminussymbol<<" "<<proton_efficiency_error<<"    "
        <<deuteron_efficiency<<" "<<plusminussymbol<<" "<<deuteron_efficiency_error<<"    "
        <<pion_efficiency<<" "<<plusminussymbol<<" "<<pion_efficiency_error<<"    "
        <<electron_efficiency<<" "<<plusminussymbol<<" "<<electron_efficiency_error<<"    "
        <<std::endl;*/
        rapiditybin = proton_table->GetXaxis()->FindBin(rapidity);
		transvermassbin = proton_table->GetYaxis()->FindBin(transvermass);
        if(transvermassbin < 1 || transvermassbin > 38) std::cout<<"Error occurred!"<<std::endl;
		tablebin = proton_table->GetBin(rapiditybin,transvermassbin);
		proton_table->SetBinContent(tablebin,proton_efficiency);
        proton_table->SetBinError(tablebin,proton_efficiency_error);
        deuteron_table->SetBinContent(tablebin,deuteron_efficiency);
        deuteron_table->SetBinError(tablebin,deuteron_efficiency_error);
        pion_table->SetBinContent(tablebin,pion_efficiency);
        pion_table->SetBinError(tablebin,pion_efficiency_error);
        electron_table->SetBinContent(tablebin,electron_efficiency);
        electron_table->SetBinError(tablebin,electron_efficiency_error);
	}
	outfile->Write();
}
