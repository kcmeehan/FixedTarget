void drawRsideVsRlong()
{
    // --- Define data sets --- //
    Float_t E895_Rs[4] = {6.280, 5.370, 5.050, 4.830};
    Float_t E895_RsError[4] = {0.200, 0.110, 0.120, 0.210};
    Float_t E895_Rl[4] = {5.150, 5.150, 4.720, 4.640};
    Float_t E895_RlError[4] = {0.190, 0.140, 0.180, 0.240};

    Float_t E866_Rs[1] = {4.550};
    Float_t E866_RsError[1] = {0.420};
    Float_t E866_Rl[1] = {3.610};
    Float_t E866_RlError[1] = {0.300};

    Float_t CERES_Rs[3] = {5.110, 4.858, 4.865};
    Float_t CERES_RsError[3] = {0.292, 0.282, 0.240};
    Float_t CERES_Rl[3] = {4.667, 5.075, 5.849};
    Float_t CERES_RlError[3] = {0.304, 0.294, 0.254};

    Float_t NA49_Rs[5] = {4.73, 4.65, 4.63, 4.74, 4.66};
    Float_t NA49_RsError[5] = {0.22, 0.22, 0.21, 0.22, 0.20};
    Float_t NA49_Rl[5] = {4.42, 4.51, 4.74, 5.17, 5.19};
    Float_t NA49_RlError[5] = {0.32, 0.32, 0.32, 0.34, 0.32};

    // Grab the FXT data from some fit file
    TFile* fIn = new TFile("4x5GeVFemto_widePt_lowKt_FitResults.root");
    // TFile* fIn = new TFile("4x5GeVFemto_widePt_FitResults.root"  );
    Double_t* tempRs = ((TGraphErrors*)fIn->Get("Rs"))->GetY();
    Double_t* tempRl = ((TGraphErrors*)fIn->Get("Rl"))->GetY();
    Double_t STAR_FXT_Rs[1] = {tempRs[5]};
    Double_t STAR_FXT_RsError[1] = {((TGraphErrors*)fIn->Get("Rs"))->GetErrorY(5)};
    Double_t STAR_FXT_Rl[1] = {tempRl[5]};
    Double_t STAR_FXT_RlError[1] = {((TGraphErrors*)fIn->Get("Rl"))->GetErrorY(5)};

    Float_t STAR_BES_Rs[7] = {4.93449, 4.78635, 4.83625, 4.8907, 4.96732, 5.00157, 5.20713};
    Float_t STAR_BES_RsError[7] = {0.0966063, 0.0507441, 0.0332015, 0.0242054, 0.0496485, 0.041259, 0.042596};
    Float_t STAR_BES_Rl[7] = {5.01443, 5.42759, 5.7974, 5.98998, 6.18026, 6.32953, 6.64397};
    Float_t STAR_BES_RlError[7] = {0.113695, 0.0701463, 0.0472674, 0.0350745, 0.0780461, 0.0662081, 0.0688818};

    Float_t ALICE_Rs[1] = {6.36};
    Float_t ALICE_RsError[1] = {0.66};
    Float_t ALICE_Rl[1] = {8.03};
    Float_t ALICE_RlError[1] = {0.57};

    // --- Assemble TGraphErrors --- //
    TGraphErrors* graphs[7];
    TMultiGraph* tmGraph = new TMultiGraph();
    TString graphNames[7] = {"E895", "E866", "STAR - FXT", "STAR - BES", "ALICE"};
    UInt_t pointMarkers[7] = {kFullCross, kFullTriangleUp, kFullStar, kFullStar, 33};
    UInt_t pointColors[7] = {kGreen+2, kBlack, kRed, kBlack, kBlue};
    Int_t graphNPoints[7] = {4, 1, 3, 5, 1, 7, 1};

    graphs[0] = new TGraphErrors(graphNPoints[0], E895_Rl, E895_Rs, E895_RlError, E895_RsError);
    graphs[1] = new TGraphErrors(graphNPoints[1], E866_Rl, E866_Rs, E866_RlError, E866_RsError);
    graphs[2] = new TGraphErrors(graphNPoints[4], STAR_FXT_Rl, STAR_FXT_Rs, STAR_FXT_RlError, STAR_FXT_RsError);
    graphs[3] = new TGraphErrors(graphNPoints[5], STAR_BES_Rl, STAR_BES_Rs, STAR_BES_RlError, STAR_BES_RsError);
    graphs[4] = new TGraphErrors(graphNPoints[6], ALICE_Rl, ALICE_Rs, ALICE_RlError, ALICE_RsError);


    for (Int_t i = 0; i <= 4; ++i) {

        graphs[i]->SetMarkerStyle(pointMarkers[i]);
        graphs[i]->SetMarkerSize(4.5);
        graphs[i]->SetLineWidth(4);
        graphs[i]->SetMarkerColor(pointColors[i]);
        graphs[i]->SetLineColor(pointColors[i]);
        tmGraph->Add(graphs[i]); 
    }

    // I guess for Quark Matter it's super important the the E866 triangle be
    // *slightly smaller* than the rest. So here we go
    graphs[1]->SetMarkerSize(4.0);

    // --- Plot stuff --- //
    Float_t xLow = 2.5, xHigh = 9.5;
    TCanvas* canvas = new TCanvas("cRsideRlong","R_side vs. R_long",1000,1000);
    tmGraph->Draw("ap");
    tmGraph->GetXaxis()->SetLimits(xLow,xHigh);
    tmGraph->SetMinimum(xLow);
    tmGraph->SetMaximum(xHigh);
    tmGraph->GetXaxis()->SetTitleSize(.05);
    tmGraph->GetXaxis()->SetTitleOffset(.8);
    tmGraph->GetXaxis()->SetTitle("R_{long} [fm]");
    tmGraph->GetYaxis()->SetTitleSize(.05);
    tmGraph->GetYaxis()->SetTitleOffset(.6);
    tmGraph->GetYaxis()->SetTitle("R_{side} [fm]");


    TLine* line = new TLine(xLow, xLow, xHigh, xHigh);
    line->SetLineStyle(2);
    line->SetLineWidth(4);
    line->SetLineColor(kBlue);
    line->Draw("same");

    TLegend* leg = new TLegend(0.65,.9,.9,.65);
    for (Int_t i = 0; i <= 4; ++i) { leg->AddEntry(graphs[i],graphNames[i],"p"); }
    leg->SetFillColor(0);
    leg->SetBorderSize(1);
    leg->SetTextSize(.03);
    leg->Draw();
    gStyle->SetTitleSize(0.06,"t");

    gPad->Modified();

    // --- Make labels, etc. --- //
    TString comEnergies[5] = {"2.7 - 4.3", "4.9", "4.5", "7.7 - 200", "2760"};
    Float_t labelAngles[5] = {65, 0, 0, 19, 0};
    Float_t labelX[5] = {4, 2.9, 4.5, 5.5, 8.11};
    Float_t labelY[5] = {5.5,4.8, 4.1, 3.8, 6.5};
    TText* energyLabels[5];

    for (Int_t i = 0; i <= 4; i++)
    {
        energyLabels[i] = new TText(labelX[i], labelY[i], comEnergies[i].Data());
        energyLabels[i]->SetTextAngle(labelAngles[i]);
        energyLabels[i]->SetTextColor(pointColors[i]);
        energyLabels[i]->Draw();
    }


};
