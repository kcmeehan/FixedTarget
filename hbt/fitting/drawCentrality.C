void drawCentrality()
{

    TFile* fIn = new TFile("4x5GeVFemto_widePt_multiplicity_FitResults.root");

    TMultiGraph* tmGraph = new TMultiGraph();

    TGraphErrors* graphs[3];
    TGraphErrors* sysErrorGraphs[3];
    TString graphNames[3] = {"Ro", "Rs", "Rl"};
    TString sysErrorGraphNames[3] = {"Ro_Err", "Rs_Err", "Rl_Err"};
    Float_t centralities[6] = {27.5, 22.5, 17.5, 12.5, 7.5, 2.5};
    Float_t sysErrorFactor[3] = {0.095, .065, 0.07};
    Float_t shiftFactor[3] = {0.25, 0, -0.25}; // Visually shift each TGraph by a little
    UInt_t markerColors[3] = {kBlack, kBlue, kRed};


    for (Int_t i = 0; i <= 2; ++i) {
        graphs[i] = (TGraphErrors*)fIn->Get(graphNames[i].Data());
        graphs[i]->SetMarkerColor(markerColors[i]);
        graphs[i]->SetMarkerStyle(kFullStar);
        graphs[i]->SetMarkerSize(4);
        graphs[i]->SetLineColor(markerColors[i]);
        graphs[i]->SetLineWidth(2);
        graphs[i]->SetLineWidth(3);
        graphs[i]->SetFillColor(markerColors[i]);
        // graphs[i]->SetFillStyle(3002);
        tmGraph->Add(graphs[i], "e1p");

        // Delete most peripheral bins
        // graphs[i]->RemovePoint(0);
        // graphs[i]->RemovePoint(0);

        Double_t* yValues = graphs[i]->GetY();
        for (Int_t j = 0; j <= 5; ++j) {
            graphs[i]->SetPoint(j, centralities[j]+shiftFactor[i], yValues[j]);
            graphs[i]->SetPointError(j, 0, graphs[i]->GetErrorY(j));
            
        }

        sysErrorGraphs[i] = (TGraphErrors*)graphs[i]->Clone(sysErrorGraphNames[i].Data());
        for (Int_t j = 0; j <= 5; ++j) {
            sysErrorGraphs[i]->SetPointError(j, 0, yValues[j]*sysErrorFactor[i]);
        }

        sysErrorGraphs[i]->SetLineStyle(1);
        sysErrorGraphs[i]->SetLineWidth(3);
        tmGraph->Add(sysErrorGraphs[i], "e2");
            
        
    }

    // -------------------- Create Canvas -----------------//
    TCanvas* cRad = new TCanvas("cRad","Centrality Dependence",1000,700);
    cRad->Clear();

    tmGraph->Draw("ap");
    tmGraph->GetXaxis()->SetLimits(0,30);
    tmGraph->GetYaxis()->SetRangeUser(2.75,5.65);
    tmGraph->GetXaxis()->SetNdivisions(505,1);
    tmGraph->GetYaxis()->SetNdivisions(505,1);
    tmGraph->GetXaxis()->SetTitle("% Centrality    ");
    tmGraph->GetXaxis()->SetTitleSize(.05);
    tmGraph->GetXaxis()->SetLabelSize(.06);
    tmGraph->GetXaxis()->SetTitleOffset(.8);
    tmGraph->GetYaxis()->SetTitle("R [fm]");
    tmGraph->GetYaxis()->SetTitleSize(.06);
    tmGraph->GetYaxis()->SetTitleOffset(.5);
    tmGraph->GetYaxis()->SetLabelSize(.06);
    gStyle->SetEndErrorSize(7);

    TLegend* leg = new TLegend(0.5,.88,.885,.6);
    leg->SetTextAlign(22);
    leg->SetMargin(0.5);
    leg->SetTextSize(3);
    leg->AddEntry(graphs[0],"R_{out}","p");
    leg->AddEntry(graphs[1],"R_{side}","p");
    leg->AddEntry(graphs[2],"R_{long}","p");
    // leg->AddEntry(graphs[0],"Stat. Error","p");
    // leg->AddEntry(sysErrorGraphs[0],"Sys. Error","l");
    leg->SetFillColor(0);
    leg->SetBorderSize(1);
    leg->SetTextSize(.05);
    leg->Draw();
    gStyle->SetTitleSize(0.06,"t");
    gPad->Modified();

}
