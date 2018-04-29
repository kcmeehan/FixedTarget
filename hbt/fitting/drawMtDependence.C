#include "src/plot.cxx"
void change_x_axis(TGraphErrors* graph, Float_t* xPoints);
void formatTGraphMtDependence(TGraphErrors* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle);
// void drawMtDependence(const TString inFileName = "4x5GeVFemto_narrowPt_kt_FitResults.root")
void drawMtDependence(const TString inFileName = "4x5GeVFemto_widePt_kt_FitResults.root")
{

    Int_t n866Points = 3;
    Float_t mtStar[3] = {0.294, 0.400, 0.539};
    Float_t dummyErr[3] = {0,0,0};

    Float_t Rl[3] = {3.62, 3.05, 2.36};
    Float_t RlErr[3] = {0.38, 0.42, 0.34};

    Float_t Rs[3] = {4.90, 3.11, 3.73};
    Float_t RsErr[3] = {0.51, 0.54, 0.57};

    Float_t Ro[3] = {5.57, 4.39, 4.21 };
    Float_t RoErr[3] = {0.41, 0.44, 0.54};

    TGraphErrors* e866TgRl = new TGraphErrors(n866Points, mtStar, Rl, dummyErr, RlErr);
    TGraphErrors* e866TgRs = new TGraphErrors(n866Points, mtStar, Rs, dummyErr, RsErr);
    TGraphErrors* e866TgRo = new TGraphErrors(n866Points, mtStar, Ro, dummyErr, RoErr);

    // -------------------- Get STAR results -----------------//

    TFile inFile(inFileName.Data());
    Float_t fxtCom = 4.5; 
    Float_t sysErrorFactor[3] = {0.095, .065, 0.07};
    TGraphErrors* sTgRout = (TGraphErrors*)inFile.Get("Ro");
    TGraphErrors* sTgRside = (TGraphErrors*)inFile.Get("Rs");
    TGraphErrors* sTgRlong = (TGraphErrors*)inFile.Get("Rl");
    sTgRout->RemovePoint(4);
    sTgRout->RemovePoint(4);
    sTgRside->RemovePoint(4);
    sTgRside->RemovePoint(4);
    sTgRlong->RemovePoint(4);
    sTgRlong->RemovePoint(4);

    Float_t mt[4] = {0.225, 0.264, 0.307, 0.388};
    change_x_axis(sTgRout, mt);
    change_x_axis(sTgRside, mt);
    change_x_axis(sTgRlong, mt);


    // -------------------- E895 Results -----------------//
    // Data points pulled from :
    // http://www.physics.ohio-state.edu/~lisa/FemtoscopyReview2005/Figures/DataFig09.html
    Int_t nE895Points = 3;
    Float_t mtE895[3] = {0.155, 0.202, 0.319};
    Float_t e895Ro[3] = {5.236, 6.206, 4.609};
    Float_t e895RoErr[3] = {0.350, 0.378, 0.424};
    Float_t e895Rs[3] = {5.412, 5.030, 4.136};
    Float_t e895RsErr[3] = {0.347, 0.223, 0.304};
    Float_t e895Rl[3] = {5.170, 5.299, 3.247};
    Float_t e895RlErr[3] = {0.344, 0.213, 0.260};
    
    TGraphErrors* e895TgRl = new TGraphErrors(nE895Points, mtE895, e895Rl, dummyErr, e895RlErr);
    TGraphErrors* e895TgRs = new TGraphErrors(nE895Points, mtE895, e895Rs, dummyErr, e895RsErr);
    TGraphErrors* e895TgRo = new TGraphErrors(nE895Points, mtE895, e895Ro, dummyErr, e895RoErr);

    // -------------------- Put TMultiGraphs Together -----------------//
    
    TMultiGraph* tmRout = new TMultiGraph();
    tmRout->Add(e866TgRo);
    tmRout->Add(e895TgRo);
    tmRout->Add(sTgRout);

    TMultiGraph* tmRside = new TMultiGraph();
    tmRside->Add(e866TgRs);
    tmRside->Add(e895TgRs);
    tmRside->Add(sTgRside);

    TMultiGraph* tmRlong = new TMultiGraph();
    tmRlong->Add(e866TgRl);
    tmRlong->Add(e895TgRl);
    tmRlong->Add(sTgRlong);

    // -------------------- Format things -----------------//

    Float_t markerSize = 3;
    formatTGraphMtDependence(sTgRout, kRed, kFullStar, markerSize, 1);
    formatTGraphMtDependence(sTgRside, kRed, kFullStar, markerSize, 1);
    formatTGraphMtDependence(sTgRlong, kRed, kFullStar, markerSize, 1);

    formatTGraphMtDependence(e866TgRo, kBlack, kFullTriangleUp, markerSize, 1);
    formatTGraphMtDependence(e866TgRs, kBlack, kFullTriangleUp, markerSize, 1);
    formatTGraphMtDependence(e866TgRl, kBlack, kFullTriangleUp, markerSize, 1);

    formatTGraphMtDependence(e895TgRo, kGreen+2, kFullCross, markerSize, 1);
    formatTGraphMtDependence(e895TgRs, kGreen+2, kFullCross, markerSize, 1);
    formatTGraphMtDependence(e895TgRl, kGreen+2, kFullCross, markerSize, 1);

    // -------------------- Create Canvas -----------------//
    TCanvas* cRad = new TCanvas("cRadMtDependence","mT Dependence",700,700);
    cRad->Clear();
    cRad->Divide(1,3,0);

    Float_t xLow = 0.1, xHigh = 0.575;
    Float_t yLow = 1.6, yHigh = 7.2;
    Float_t titleOffset = 0.3;
    Float_t labelSize = 0.2, labelSmall = labelSize / 1.5;
    Float_t titleSize = 0.2, titleSmall = titleSize / 1.5;
    Float_t bottomMargin = 0.15;
    Float_t leftMargin = 0.15;
    plot::setPadMargins(cRad, 3, 1, leftMargin, bottomMargin, 0.05);
    gStyle->SetEndErrorSize(7);

    cRad->cd(1);
    cRad->cd(1)->SetRightMargin(0.01);
    tmRout->Draw("ap");
    tmRout->GetYaxis()->SetTitleSize(titleSize);
    tmRout->GetYaxis()->SetTitleOffset(titleOffset);
    tmRout->GetYaxis()->SetTitle("R_{out} [fm]");
    tmRout->GetXaxis()->SetLimits(xLow, xHigh);
    tmRout->GetYaxis()->SetRangeUser(yLow, yHigh);
    tmRout->GetXaxis()->SetLabelSize(labelSize);
    tmRout->GetXaxis()->SetNdivisions(105,1);
    tmRout->GetYaxis()->SetLabelSize(labelSize);
    tmRout->GetYaxis()->SetNdivisions(105,1);

    cRad->cd(2);
    cRad->cd(2)->SetRightMargin(0.01);
    tmRside->Draw("ap");
    tmRside->GetYaxis()->SetTitleSize(titleSize);
    tmRside->GetYaxis()->SetTitleOffset(titleOffset);
    tmRside->GetYaxis()->SetTitle("R_{side} [fm]");
    tmRside->GetXaxis()->SetLimits(xLow, xHigh);
    tmRside->GetYaxis()->SetRangeUser(yLow, yHigh);
    tmRside->GetXaxis()->SetLabelSize(labelSize);
    tmRside->GetXaxis()->SetNdivisions(105,1);
    tmRside->GetYaxis()->SetLabelSize(labelSize);
    tmRside->GetYaxis()->SetNdivisions(105,1);

    cRad->cd(3);
    cRad->cd(3)->SetRightMargin(0.01);
    tmRlong->Draw("ap");
    tmRlong->GetYaxis()->SetTitleSize(titleSmall);
    tmRlong->GetYaxis()->SetTitleOffset(0.4);
    tmRlong->GetYaxis()->SetTitle("R_{long} [fm]");
    tmRlong->GetYaxis()->SetRangeUser(yLow, yHigh);
    tmRlong->GetYaxis()->SetLabelSize(labelSmall);
    tmRlong->GetYaxis()->SetNdivisions(105,1);
    tmRlong->GetXaxis()->SetLimits(xLow, xHigh);
    tmRlong->GetXaxis()->SetTitle("m_{T} [GeV]");
    tmRlong->GetXaxis()->SetTitleSize(titleSmall);
    tmRlong->GetXaxis()->SetTitleOffset(1.1);
    tmRlong->GetXaxis()->SetLabelSize(labelSmall);
    tmRlong->GetXaxis()->SetNdivisions(105,1);

    // --- I am Legend --- //
    TLegend* leg = new TLegend(0.672,.98,.98,.60);
    leg->SetTextAlign(22);
    leg->SetMargin(0.2);
    leg->AddEntry(e895TgRl,"E895 - 4.3 GeV","p");
    leg->AddEntry(sTgRout,"STAR - 4.5 GeV","p");
    leg->AddEntry(e866TgRo,"E866 - 4.9 GeV","p");
    leg->SetFillColor(0);
    leg->SetBorderSize(1);
    leg->SetTextSize(.08);
    cRad->cd(3);
    leg->Draw();
    gStyle->SetTitleSize(0.06,"t");
    gPad->Modified();

}

void formatTGraphMtDependence(TGraphErrors* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle)
{
	graph->SetMarkerColor(color);
	graph->SetLineColor(color);
	graph->SetMarkerStyle(mStyle);
	graph->SetMarkerSize(mSize);
	graph->SetLineStyle(lStyle);
	graph->SetLineWidth(mSize);

}

void change_x_axis(TGraphErrors* graph, Float_t* xPoints)
{
    Double_t* yPoints = graph->GetY();
    for (Int_t i = 0; i <= 3; i++) {
        graph->SetPoint(i, xPoints[i], yPoints[i]);
    }


}

void setPadMargins(TCanvas* canvas, Float_t leftMargin, Float_t bottomMargin,
                    Int_t nRows, Int_t nColumns)
{

    Float_t dx = (1 - leftMargin) / Float_t(nColumns);
    Float_t dy = (1 - bottomMargin) / Float_t(nRows);
    Float_t padBottomMargin = bottomMargin / (dy + bottomMargin);
    Float_t padLeftMargin = leftMargin / (dx + leftMargin);

    for (Int_t i = 0; i <= (nRows-1); i++) {
        Float_t yLow = -1, yHigh = -1;
        if( i == (nRows-1) ) {
            yLow = 0;
            yHigh = dy + bottomMargin;
        } else {
            yHigh = 1 - i*dy;
            yLow = yHigh - dy;
            // yLow = (i+1)*dy + bottomMargin;
            // yHigh = yLow + dy;
        }

        for (Int_t j = 0; j <= (nColumns-1); j++) {
            Float_t xLow = -1, xHigh = -1;
            if(j == 0) {
                xLow = 0;
                xHigh = dx + leftMargin;
            } else {
                xLow = (j+1)*dx + leftMargin;
                xHigh = xLow + dx;
            }

            Int_t padNumber = i*nColumns + (j+1);
            cout << padNumber << endl;
            cout << xLow << " " << yLow << " " << xHigh << " " << yHigh << endl;
            canvas->cd(padNumber);
            gPad->SetPad(xLow, yLow, xHigh, yHigh);
            if( i == (nRows-1) )  {gPad->SetBottomMargin(padBottomMargin);} 
            if( j == 0 )  {gPad->SetLeftMargin(padLeftMargin);} 
        }
    }
}
