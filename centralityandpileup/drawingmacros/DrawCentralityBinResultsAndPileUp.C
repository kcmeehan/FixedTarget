//This code draws the centrality variable data histogram,
//the best matched histogram from the glauber simulation,
//and vertical lines denoting the centrality bin results
//that are stored in UserCuts.cxx::GetCentralityCuts()

void DrawCentralityBinResultsAndPileUp(TString pileUpResults,
            TString starLibrary,
            Double_t energy=0,
            TString eventConfig,
						TString system,
			      TString histoTitle="",
			      TString dataHistoTitle="",
			      TString xAxisTitle=""){
  
  //Load the Necessary Libraries
  gSystem->Load("../bin/TrackInfo_cxx.so");
  gSystem->Load("../bin/PrimaryVertexInfo_cxx.so");
  gSystem->Load("../bin/EventInfo_cxx.so");
	gSystem->Load("../bin/StRefMultExtendedCorr_cxx.so");
  gSystem->Load("../bin/UserCuts_cxx.so");

  //Set the User Cuts
  SetVariableUserCuts(energy,eventConfig,starLibrary); 

  //Load the File with the simulated histogram and load the histogram
  /*TFile *centBinResultFile = new TFile(centralityBinResults,"READ");
  TH1D *centVarDataHisto = (TH1D *)centBinResultFile->Get(centralityVarName);
  TH1D *centBinResultHisto = (TH1D *)centBinResultFile->Get("bestFit_2");
*/
	TFile *pileUpResultFile = new TFile(pileUpResults,"READ");
  TH1D *centVarDataHisto = (TH1D *)pileUpResultFile->Get("hGoodTracks");	
  TH1D *centBinResultHisto = (TH1D *)pileUpResultFile->Get("hBestFit");
	TH1D *pileUpHisto = (TH1D *)pileUpResultFile->Get("hJustPileUp");

  //Create a canvas for drawing
  TCanvas *canvas = new TCanvas("centBinResultCanvas","Centrality Binning Results",20,20,800,600);
  canvas->SetTopMargin(.05);
  canvas->SetRightMargin(.05);
  canvas->SetLogy();
  canvas->cd();

  //Set the drawing range of the data histogram
  Int_t lastBin = centVarDataHisto->FindLastBinAbove(0);
  Double_t highRange = centVarDataHisto->GetBinCenter(lastBin);
	Double_t lowY = 1;
	Double_t highY = centBinResultHisto->GetBinContent(1);
	centVarDataHisto->SetTitle(Form(";Multiplicity;Events"));
	centVarDataHisto->GetYaxis()->SetTitleOffset(.8);
  centVarDataHisto->SetAxisRange(0,highRange,"X");
	centVarDataHisto->SetAxisRange(lowY,highY,"Y");
  centVarDataHisto->Draw("E");

  //Set the drawing Attributes of the simulation curve
  centBinResultHisto->SetLineColor(6);
	centBinResultHisto->SetLineWidth(2);
  centBinResultHisto->Draw("SAME");

	//Adding pile up curve
	pileUpHisto->SetLineColor(2);
	pileUpHisto->SetLineWidth(2);
	pileUpHisto->SetLineStyle(9);
	pileUpHisto->Draw("SAME");

  //Create Lines to show the centrality Cuts
  std::vector <int> centCuts = GetCentralityCuts();
  std::vector <double> centPercents = GetCentralityPercents();
	Int_t pileUpCut = GetPileUpCut();

  if (centCuts.size() != centPercents.size()){
    cout <<"ERROR: DrawCentralityBinResults.C - centrality cut and centrality percent vectors are different sizes!" <<endl;
    exit (EXIT_FAILURE);
  }

  const int nLines = (int) centCuts.size();
  TLine *cutLines[50];
  TPaveText *cutLables[50];
  Double_t lineHeight = centBinResultHisto->GetBinContent(centCuts.back())*1.8;
  for (Int_t i=0; i<nLines; i++){
    
    cutLines[i] = new TLine(centCuts.at(i),lowY,centCuts.at(i),lineHeight);
    cutLines[i]->SetLineColor(kGray+3);
    cutLines[i]->SetLineStyle(7);
    cutLines[i]->SetLineWidth(3);
    cutLines[i]->Draw("SAME");

    cutLables[i] = new TPaveText(centCuts.at(i)+5,
				 .01*lineHeight,
				 centCuts.at(i)+8,
				 .05*lineHeight);
    cutLables[i]->SetFillColor(kWhite);
    cutLables[i]->SetBorderSize(0);
    cutLables[i]->AddText(Form("Top %g%%",centPercents.at(i)));
    cutLables[i]->GetLine(0)->SetTextAngle(90);
    cutLables[i]->SetTextSize(.032);
    cutLables[i]->Draw("SAME");

  }


	TLine *pileUpLine;
	TPaveText *pileUpLabel;
	pileUpLine = new TLine(pileUpCut,lowY,pileUpCut,lineHeight);
  pileUpLine->SetLineColor(kGray+3);
  pileUpLine->SetLineStyle(7);
  pileUpLine->SetLineWidth(3);
  pileUpLine->Draw("SAME");

  pileUpLabel = new TPaveText(pileUpCut+5,
			 .01*lineHeight,
			 pileUpCut+8,
			 .07*lineHeight);
  pileUpLabel->SetFillColor(kWhite);
  pileUpLabel->SetBorderSize(0);
  pileUpLabel->AddText(Form("Pile Up"));
  pileUpLabel->GetLine(0)->SetTextAngle(90);
  pileUpLabel->SetTextSize(.032);
  pileUpLabel->Draw("SAME");
  
  //Create Histogram Title
  TPaveText *title = new TPaveText(.5,.88,.95,.93,"NDC");
  title->SetTextSize(.035);
  title->SetFillColor(kWhite);
  title->AddText(histoTitle);
  title->Draw("SAME");
  
  //Create and Draw a Legend
  TLegend *leg = new TLegend(.53,.75,.8,.87);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetTextSize(.032);
  //leg->AddEntry(centVarDataHisto,"Recorded Events","LP");
  leg->AddEntry(centVarDataHisto,Form("STAR %s #sqrt{s_{NN}} = %.03g GeV", system.Data(), energy),"LP");
  leg->AddEntry(centBinResultHisto,"Glauber","LP");
	leg->AddEntry(pileUpHisto,"Pile Up", "LP");
  leg->Draw("SAME");

  gStyle->SetOptStat(0);
  canvas->Modified();
  canvas->Update();
	canvas->Print(Form("%s.pdf",canvas->GetName()));
	canvas->Print(Form("%s.eps",canvas->GetName()));

}
