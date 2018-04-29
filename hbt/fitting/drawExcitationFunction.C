#include "src/plot.cxx"
void formatTGraphExcitation(TGraphErrors* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle);
void formatTMGraph(TMultiGraph* graph);
void drawExcitationFunction(const TString inFileName = "4x5GeVFemto_narrowPt_FitResults.root" )
{

    // -------------------- Input E895 Results -----------------//
    // http://www.physics.ohio-state.edu/~lisa/FemtoscopyReview2005/Figures/DataFig13.html
    Float_t dummyErr[4] = {0,0,0,0};
    Float_t e895CoMEnergy[4] = {2.70,3.32,3.86,4.3};
    Float_t e895Lambda[4] = { 0.990,0.740,0.630,0.650};
    Float_t e895LambdaErr[4] = {0.060,0.030,0.030,0.050};
    Float_t e895Rout[4] = {6.220,5.790,5.760,5.480};
    Float_t e895RoutErr[4] = {0.260,0.160,0.230,0.310};
    Float_t e895Rside[4] = {6.280,5.370,5.050,4.830};
    Float_t e895RsideErr[4] = {0.200,0.110,0.120,0.210};
    Float_t e895Rlong[4] = {5.150,5.150,4.720,4.640};
    Float_t e895RlongErr[4] = {0.190,0.140,0.180,0.240};

    Float_t e866CoMEnergy[1] = {5.03};
    Float_t e866Lambda[1] = {0.542};
    Float_t e866LambdaErr[1] = {0.041};
    Float_t e866Rout[1] = {5.410};
    Float_t e866RoutErr[1] = {0.330};
    Float_t e866Rside[1] = {4.550};
    Float_t e866RsideErr[1] = {0.420};
    Float_t e866Rlong[1] = {3.610};
    Float_t e866RlongErr[1] = {0.300};

    TGraphErrors* e895TgLambda = new TGraphErrors(4,e895CoMEnergy,e895Lambda,dummyErr,e895LambdaErr);
    TGraphErrors* e895TgRout = new TGraphErrors(4,e895CoMEnergy,e895Rout,dummyErr,e895RoutErr);
    TGraphErrors* e895TgRside = new TGraphErrors(4,e895CoMEnergy,e895Rside,dummyErr,e895RsideErr);
    TGraphErrors* e895TgRlong = new TGraphErrors(4,e895CoMEnergy,e895Rlong,dummyErr,e895RlongErr);

    TGraphErrors* e866TgLambda = new TGraphErrors(1,e866CoMEnergy,e866Lambda,dummyErr,e866LambdaErr);
    TGraphErrors* e866TgRout = new TGraphErrors(1,e866CoMEnergy,e866Rout,dummyErr,e866RoutErr);
    TGraphErrors* e866TgRside = new TGraphErrors(1,e866CoMEnergy,e866Rside,dummyErr,e866RsideErr);
    TGraphErrors* e866TgRlong = new TGraphErrors(1,e866CoMEnergy,e866Rlong,dummyErr,e866RlongErr);

    // -------------------- Get STAR results -----------------//

    TFile inFile(inFileName.Data());
    Float_t fxtCom = 4.5; 
    Float_t sysErrorFactor[3] = {0.095, .065, 0.07};
    TGraphErrors* sTgLambda = (TGraphErrors*)inFile.Get("lam");
    TGraphErrors* sTgRout = (TGraphErrors*)inFile.Get("Ro");
    TGraphErrors* sTgRside = (TGraphErrors*)inFile.Get("Rs");
    TGraphErrors* sTgRlong = (TGraphErrors*)inFile.Get("Rl");

    // Assumes the point we want is originally #1
    /*
    sTgLambda->RemovePoint(0);
    sTgLambda->RemovePoint(1);
    sTgRout->RemovePoint(0);
    sTgRout->RemovePoint(1);
    sTgRside->RemovePoint(0);
    sTgRside->RemovePoint(1);
    sTgRlong->RemovePoint(0);
    sTgRlong->RemovePoint(1);
    */

    // Change from R^2 to R
    Double_t tempY, dummy, tempErr;

    sTgRout->GetPoint(0,dummy,tempY);
    tempErr = sTgRout->GetErrorY(0);
    // tempY = sqrt(tempY);
    // tempErr /= (2*tempY);
    sTgRout->SetPoint(0,fxtCom,tempY);
    sTgRout->SetPointError(0,0,tempY*sysErrorFactor[0]);

    sTgRside->GetPoint(0,dummy,tempY);
    tempErr = sTgRside->GetErrorY(0);
    // tempY = sqrt(tempY);
    // tempErr /= (2*tempY);
    sTgRside->SetPoint(0,fxtCom,tempY);
    sTgRside->SetPointError(0,0,tempY*sysErrorFactor[1]);

    sTgRlong->GetPoint(0,dummy,tempY);
    tempErr = sTgRlong->GetErrorY(0);
    // tempY = sqrt(tempY);
    // tempErr /= (2*tempY);
    sTgRlong->SetPoint(0,fxtCom,tempY);
    sTgRlong->SetPointError(0,0,tempY*sysErrorFactor[1]);

    // Change x-value for lambda

    sTgLambda->GetPoint(0,dummy,tempY);
    sTgLambda->SetPoint(0,fxtCom,tempY);

    // -------------------- Format things -----------------//

    Float_t markerSize = 3;
    formatTGraphExcitation(e895TgLambda, kGreen+2, kFullCross, markerSize, 1);
    formatTGraphExcitation(e895TgRout, kGreen+2, kFullCross, markerSize, 1);
    formatTGraphExcitation(e895TgRside, kGreen+2, kFullCross, markerSize, 1);
    formatTGraphExcitation(e895TgRlong, kGreen+2, kFullCross, markerSize, 1);

    formatTGraphExcitation(e866TgLambda, kBlack, kFullTriangleUp, markerSize, 1);
    formatTGraphExcitation(e866TgRout, kBlack, kFullTriangleUp, markerSize, 1);
    formatTGraphExcitation(e866TgRside, kBlack, kFullTriangleUp, markerSize, 1);
    formatTGraphExcitation(e866TgRlong, kBlack, kFullTriangleUp, markerSize, 1);

    formatTGraphExcitation(sTgLambda, kRed, kFullStar, markerSize+1, 1);
    formatTGraphExcitation(sTgRout, kRed, kFullStar, markerSize+1, 1);
    formatTGraphExcitation(sTgRside, kRed, kFullStar, markerSize+1, 1);
    formatTGraphExcitation(sTgRlong, kRed, kFullStar, markerSize+1, 1);

    // -------------------- Put TMultiGraphs Together -----------------//
    
    TMultiGraph* tmRout = new TMultiGraph();
    tmRout->Add(e895TgRout);
    tmRout->Add(e866TgRout);
    tmRout->Add(sTgRout);

    TMultiGraph* tmRside = new TMultiGraph();
    tmRside->Add(e895TgRside);
    tmRside->Add(e866TgRside);
    tmRside->Add(sTgRside);

    TMultiGraph* tmRlong = new TMultiGraph();
    tmRlong->Add(e895TgRlong);
    tmRlong->Add(e866TgRlong);
    tmRlong->Add(sTgRlong);

    TMultiGraph* tmLambda = new TMultiGraph();
    tmLambda->Add(e895TgLambda);
    tmLambda->Add(e866TgLambda);
    tmLambda->Add(sTgLambda);

    // -------------------- Create Canvas -----------------//
    TCanvas *cRad = new TCanvas("cRadExcitation","Comparison of E895 to STAR",1000,700);
    cRad->Clear();
    cRad->Divide(3,1,0);

    Float_t xLow = 2.8, xHigh = 5.2;
    Float_t yLow = 2.8, yHigh = 7.2;
    Float_t bottomMargin = 0.2, leftMargin = 0.15;
    Float_t titleSize = 0.2, titleSmall = titleSize / 1.7;
    Float_t labelSize = 0.16, labelSmall = labelSize / 1.7;
    plot::setPadMargins(cRad, 1, 3, leftMargin, bottomMargin);

    // cRad->cd(1);
    // tmLambda->Draw("ap");
// //    tmLambda->GetYaxis()->SetTitle("#lambda");
    // formatTMGraph(tmLambda);

    cRad->cd(1);
    tmRout->Draw("ap");
//    tmRout->GetYaxis()->SetTitle("R_{out}");
    tmRout->GetYaxis()->SetRangeUser(yLow,yHigh);
    formatTMGraph(tmRout);
    tmRout->GetYaxis()->SetTitleSize(titleSmall);
    tmRout->GetYaxis()->SetTitleOffset(.9);
    tmRout->GetYaxis()->SetTitle("R [fm]");
    tmRout->GetYaxis()->SetLabelSize(labelSmall);
    tmRout->GetYaxis()->SetLabelOffset(0.04);
    tmRout->GetXaxis()->SetLabelOffset(0.02);
    gStyle->SetEndErrorSize(7);


    cRad->cd(2);
    tmRside->Draw("ap");
    tmRside->GetYaxis()->SetRangeUser(yLow,yHigh);
    formatTMGraph(tmRside);
    tmRside->GetXaxis()->SetLabelSize(labelSize);

    cRad->cd(3);
    tmRlong->Draw("ap");
    formatTMGraph(tmRlong);
    tmRlong->GetYaxis()->SetRangeUser(yLow,yHigh);
    tmRlong->GetXaxis()->SetTitle("#sqrt{s_{NN}} [GeV]");
    tmRlong->GetXaxis()->SetTitleSize(titleSize);
    tmRlong->GetXaxis()->SetLabelSize(labelSize);


    // ----- Write Labels and Legend ----- //

    TLegend* leg = new TLegend(0.0573,.972,.943,.75);
    leg->SetTextAlign(22);
    leg->SetMargin(0.2);
    leg->AddEntry(e895TgLambda,"E895","p");
    leg->AddEntry(sTgLambda,"STAR","p");
    leg->AddEntry(e866TgRlong,"E866","p");
    leg->SetFillColor(0);
    leg->SetBorderSize(1);
    leg->SetTextSize(.10);
    cRad->cd(3);
    leg->Draw();
    gStyle->SetTitleSize(0.06,"t");
    gPad->Modified();

    Float_t labelXPosition = 3.5, labelYPosition = 3.5;

    TText* outLabel = new TText(labelXPosition, labelYPosition, "Out");
    outLabel->SetTextAlign(22);
    outLabel->SetTextSize(.2 / 1.5);
    cRad->cd(1);
    outLabel->Draw();

    TText* sideLabel = new TText(labelXPosition, labelYPosition, "Side");
    sideLabel->SetTextAlign(22);
    sideLabel->SetTextSize(.2);
    cRad->cd(2);
    sideLabel->Draw();

    TText* longLabel = new TText(labelXPosition, labelYPosition, "Long");
    longLabel->SetTextAlign(22);
    longLabel->SetTextSize(.2);
    cRad->cd(3);
    longLabel->Draw();

}

void formatTGraphExcitation(TGraphErrors* graph, Color_t color, Style_t mStyle, Size_t mSize, Style_t lStyle)
{
	graph->SetMarkerColor(color);
	graph->SetLineColor(color);
	graph->SetMarkerStyle(mStyle);
	graph->SetMarkerSize(mSize);
	graph->SetLineStyle(lStyle);
	graph->SetLineWidth(mSize);
}

void formatTMGraph(TMultiGraph* graph)
{

//    graph->GetXaxis()->SetTitle("#sqrt{s_{NN}}");
    graph->GetYaxis()->SetTitleOffset(0.7);
    graph->GetXaxis()->SetLabelOffset(-.03);
    graph->GetXaxis()->SetLimits(2.2,5.4);
    graph->GetXaxis()->SetLabelSize(.10);
    graph->GetXaxis()->SetNdivisions(105,1);
    graph->GetYaxis()->SetNdivisions(205,1);

    graph->GetXaxis()->SetTitleOffset(0.5);
    graph->GetXaxis()->SetTitleSize(.12);
    graph->GetYaxis()->SetLabelSize(.10);
    graph->GetYaxis()->SetTitleSize(.10);

}
