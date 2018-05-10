#include "src/plot.cxx"
void formatTH1(TH1* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle, Size_t lSize);
TCanvas* makeCanvas(TString fileName, Int_t folder);
void drawCorrelationFunctions( const TString inputFileName = "4x5GeVFemto_narrowPt_FitResults.root"  //input file
            )
{
    // for (Int_t i = 0; i <= 5; i++) {
    //     TCanvas* canvas = makeCanvas(inputFileName, (5-i));

    //     if(i==0){ canvas->Print("CFs.pdf("); }
    //     else if (i == 5) { canvas->Print("CFs.pdf)"); }
    //     else { canvas->Print("CFs.pdf"); }

    // }


    TCanvas* canvas = makeCanvas(inputFileName, 0);
    canvas->Draw();

}

TCanvas* makeCanvas(TString fileName, Int_t folder){

    TH1D* qOut[2];
    TH1D* qSide[2];
    TH1D* qLong[2];

    TFile* file = new TFile(fileName.Data(), "READ");

    file->cd(TString::Format("%i", folder));
    qOut[0] = (TH1D*)gDirectory->Get("qOut");
    qSide[0] = (TH1D*)gDirectory->Get("qSide");
    qLong[0] = (TH1D*)gDirectory->Get("qLong");
    qOut[1] = (TH1D*)gDirectory->Get("qOutFit");
    qSide[1] = (TH1D*)gDirectory->Get("qSideFit");
    qLong[1] = (TH1D*)gDirectory->Get("qLongFit");

    TCanvas* canvas = new TCanvas("cCorrFunc","Projections of the Correlation Function",1000,700);
    canvas->Clear();
    canvas->Divide(3,1,0,0);
    Float_t bottomMargin = 0.15, leftMargin = 0.10;
    plot::setPadMargins(canvas, 1, 3, leftMargin, bottomMargin, 0.05, .05);
    Float_t titleSize = 0.2, titleSmall = titleSize / 1.3;
    Float_t labelSize = 0.13, labelSmall = labelSize / 1.3;

    canvas->cd(1);
    // canvas->cd(1)->SetLeftMargin(leftMargin);
    formatTH1(qOut[0],kBlue,kFullTriangleUp,2,1,2);
    formatTH1(qOut[1],kRed,kFullTriangleUp,2,1,4);
    qOut[0]->Draw();
    qOut[0]->GetXaxis()->SetLabelSize(labelSmall);
    qOut[0]->GetXaxis()->SetLabelOffset(-0.005);
    qOut[0]->GetYaxis()->SetTitleSize(titleSmall);
    qOut[0]->GetYaxis()->SetTitleOffset(.4);
    qOut[0]->GetYaxis()->SetTitle("C(q)");
    qOut[1]->Draw("lchistsame");

    canvas->cd(2);
    formatTH1(qSide[0],kBlue,kFullTriangleUp,2,1,2);
    formatTH1(qSide[1],kRed,kFullTriangleUp,2,1,4);
    qSide[0]->GetXaxis()->SetLabelSize(labelSize);
    qSide[0]->Draw();
    qSide[1]->Draw("lchistsame");

    canvas->cd(3);
    formatTH1(qLong[0],kBlue,kFullTriangleUp,2,1,2);
    formatTH1(qLong[1],kRed,kFullTriangleUp,2,1,4);
    qLong[0]->Draw();
    qLong[0]->GetXaxis()->SetLabelSize(labelSize);
    qLong[0]->GetXaxis()->SetTitle("q [GeV/c]");
    qLong[0]->GetXaxis()->SetTitleSize(titleSmall);
    qLong[0]->GetXaxis()->SetTitleOffset(.50);
    qLong[1]->Draw("lchistsame");


    // ----- Write Labels ----- //
    Float_t labelXPosition = 0, labelYPosition = 0.9;

    TText* outLabel = new TText(labelXPosition, labelYPosition, "Out");
    outLabel->SetTextAlign(22);
    outLabel->SetTextSize(.2/1.3);
    canvas->cd(1);
    outLabel->Draw();

    TText* sideLabel = new TText(labelXPosition, labelYPosition, "Side");
    sideLabel->SetTextAlign(22);
    sideLabel->SetTextSize(.2);
    canvas->cd(2);
    sideLabel->Draw();

    TText* longLabel = new TText(labelXPosition, labelYPosition, "Long");
    longLabel->SetTextAlign(22);
    longLabel->SetTextSize(.2);
    canvas->cd(3);
    // canvas->cd(3)->SetRightMargin(0.01);
    longLabel->Draw();

    gStyle->SetOptStat(0);

    const TString centralityLabels[6] = {"25%-30%","20%-25%","15%-20%","10%-15%","5%-10%","0%-5%"};
    TPaveText* pt = new TPaveText(0,0.8,0.4,.98,"NDC");
    pt->AddText(centralityLabels[folder].Data());
    pt->SetTextSize(.08);

    canvas->cd(3);
    TLegend* leg = new TLegend(0.36,.98,.95,.82);
    leg->SetTextAlign(22);
    leg->SetMargin(0.5);
    leg->AddEntry(qLong[0],"Data","p");
    leg->AddEntry(qLong[1],"Fit","l");
    leg->SetFillColor(0);
    // leg->SetBorderSize(1);
    leg->SetTextSize(.1);
    leg->Draw();
    gStyle->SetTitleSize(0.06,"t");
    gPad->Modified();
    // pt->Draw();
    return canvas;
}

void formatTH1(TH1* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle, Size_t lSize)
{
	graph->SetMarkerColor(color);
	graph->SetLineColor(color);
	graph->SetMarkerStyle(mStyle);
	graph->SetMarkerSize(mSize);
	graph->SetLineStyle(lStyle);
	graph->SetLineWidth(lSize);

    Float_t xRange = 0.18;
    Float_t yLo = 0.84, yHigh = 1.39;
    graph->GetXaxis()->SetRangeUser(-1*xRange,xRange);
    graph->GetXaxis()->SetNdivisions(105,1);
    graph->GetXaxis()->SetLabelSize(.09);
    graph->GetXaxis()->SetLabelOffset(-0.03);
    graph->GetXaxis()->SetTitleSize(.1);
    graph->GetXaxis()->SetTitleOffset(0.45);

    graph->GetYaxis()->SetRangeUser(yLo,yHigh);
    graph->GetYaxis()->SetNdivisions(205,1);
    graph->GetYaxis()->SetLabelSize(.09);
    // graph->GetYaxis()->SetLabelOffset(.09);
    graph->GetYaxis()->SetTitleSize(.06);
    graph->GetYaxis()->SetTitleOffset(0.4);
    graph->SetTitle("");
}
