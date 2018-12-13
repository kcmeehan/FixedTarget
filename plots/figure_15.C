void figure_15()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Oct 25 10:42:46 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0.03891624,-0.0875,1.786341,0.1625);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogx();
   c->SetLeftMargin(0.15);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1F *hist_Plot1__1 = new TH1F("hist_Plot1__1","",10,2,50);
   hist_Plot1__1->SetMinimum(-0.05);
   hist_Plot1__1->SetMaximum(0.15);
   hist_Plot1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hist_Plot1__1->SetLineColor(ci);
   hist_Plot1__1->GetXaxis()->SetTitle("#sqrt{s_{NN}} (GeV)");
   hist_Plot1__1->GetXaxis()->CenterTitle(true);
   hist_Plot1__1->GetXaxis()->SetMoreLogLabels();
   hist_Plot1__1->GetXaxis()->SetNoExponent();
   hist_Plot1__1->GetXaxis()->SetNdivisions(1404);
   hist_Plot1__1->GetXaxis()->SetLabelFont(42);
   hist_Plot1__1->GetXaxis()->SetLabelSize(0.06);
   hist_Plot1__1->GetXaxis()->SetTitleSize(0.07);
   hist_Plot1__1->GetXaxis()->SetTitleOffset(0.9);
   hist_Plot1__1->GetXaxis()->SetTitleFont(42);
   hist_Plot1__1->GetYaxis()->SetTitle("dv_{1}/dy |_{y=0}");
   hist_Plot1__1->GetYaxis()->CenterTitle(true);
   hist_Plot1__1->GetYaxis()->SetNdivisions(204);
   hist_Plot1__1->GetYaxis()->SetLabelFont(42);
   hist_Plot1__1->GetYaxis()->SetLabelOffset(0.01);
   hist_Plot1__1->GetYaxis()->SetLabelSize(0.06);
   hist_Plot1__1->GetYaxis()->SetTitleSize(0.07);
   hist_Plot1__1->GetYaxis()->SetTitleFont(42);
   hist_Plot1__1->GetZaxis()->SetLabelFont(42);
   hist_Plot1__1->GetZaxis()->SetLabelSize(0.035);
   hist_Plot1__1->GetZaxis()->SetTitleSize(0.035);
   hist_Plot1__1->GetZaxis()->SetTitleFont(42);
   hist_Plot1__1->Draw("P9");
   
   Double_t gP895_fx1001[5] = {
   0,
   2.7,
   3.3,
   3.8,
   4.3};
   Double_t gP895_fy1001[5] = {
   0,
   0.315666,
   0.156451,
   0.102195,
   0.079921};
   Double_t gP895_fex1001[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gP895_fey1001[5] = {
   0,
   0.0136679,
   0.0129588,
   0.0112675,
   0.0102746};
   TGraphErrors *gre = new TGraphErrors(5,gP895_fx1001,gP895_fy1001,gP895_fex1001,gP895_fey1001);
   gre->SetName("gP895");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gP8951001 = new TH1F("Graph_gP8951001","Graph",100,0.00473,4.73);
   Graph_gP8951001->SetMinimum(0);
   Graph_gP8951001->SetMaximum(0.3622673);
   Graph_gP8951001->SetDirectory(0);
   Graph_gP8951001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gP8951001->SetLineColor(ci);
   Graph_gP8951001->GetXaxis()->SetLabelFont(42);
   Graph_gP8951001->GetXaxis()->SetLabelSize(0.035);
   Graph_gP8951001->GetXaxis()->SetTitleSize(0.035);
   Graph_gP8951001->GetXaxis()->SetTitleFont(42);
   Graph_gP8951001->GetYaxis()->SetLabelFont(42);
   Graph_gP8951001->GetYaxis()->SetLabelSize(0.035);
   Graph_gP8951001->GetYaxis()->SetTitleSize(0.035);
   Graph_gP8951001->GetYaxis()->SetTitleOffset(0);
   Graph_gP8951001->GetYaxis()->SetTitleFont(42);
   Graph_gP8951001->GetZaxis()->SetLabelFont(42);
   Graph_gP8951001->GetZaxis()->SetLabelSize(0.035);
   Graph_gP8951001->GetZaxis()->SetTitleSize(0.035);
   Graph_gP8951001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gP8951001);
   
   gre->Draw(" p");
   
   Double_t gP_fx1002[2] = {
   0,
   4.5};
   Double_t gP_fy1002[2] = {
   0,
   0.0822};
   Double_t gP_fex1002[2] = {
   0,
   0};
   Double_t gP_fey1002[2] = {
   0,
   0.0089};
   gre = new TGraphErrors(2,gP_fx1002,gP_fy1002,gP_fex1002,gP_fey1002);
   gre->SetName("gP");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gP1002 = new TH1F("Graph_gP1002","Graph",100,0.00495,4.95);
   Graph_gP1002->SetMinimum(0);
   Graph_gP1002->SetMaximum(0.10021);
   Graph_gP1002->SetDirectory(0);
   Graph_gP1002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gP1002->SetLineColor(ci);
   Graph_gP1002->GetXaxis()->SetLabelFont(42);
   Graph_gP1002->GetXaxis()->SetLabelSize(0.035);
   Graph_gP1002->GetXaxis()->SetTitleSize(0.035);
   Graph_gP1002->GetXaxis()->SetTitleFont(42);
   Graph_gP1002->GetYaxis()->SetLabelFont(42);
   Graph_gP1002->GetYaxis()->SetLabelSize(0.035);
   Graph_gP1002->GetYaxis()->SetTitleSize(0.035);
   Graph_gP1002->GetYaxis()->SetTitleOffset(0);
   Graph_gP1002->GetYaxis()->SetTitleFont(42);
   Graph_gP1002->GetZaxis()->SetLabelFont(42);
   Graph_gP1002->GetZaxis()->SetLabelSize(0.035);
   Graph_gP1002->GetZaxis()->SetTitleSize(0.035);
   Graph_gP1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gP1002);
   
   gre->Draw(" p");
   
   Double_t gLambda_fx1003[2] = {
   0,
   4.5};
   Double_t gLambda_fy1003[2] = {
   0,
   0.094};
   Double_t gLambda_fex1003[2] = {
   0,
   0};
   Double_t gLambda_fey1003[2] = {
   0,
   0.015};
   gre = new TGraphErrors(2,gLambda_fx1003,gLambda_fy1003,gLambda_fex1003,gLambda_fey1003);
   gre->SetName("gLambda");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_gLambda1003 = new TH1F("Graph_gLambda1003","Graph",100,0.00495,4.95);
   Graph_gLambda1003->SetMinimum(0);
   Graph_gLambda1003->SetMaximum(0.1199);
   Graph_gLambda1003->SetDirectory(0);
   Graph_gLambda1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gLambda1003->SetLineColor(ci);
   Graph_gLambda1003->GetXaxis()->SetLabelFont(42);
   Graph_gLambda1003->GetXaxis()->SetLabelSize(0.035);
   Graph_gLambda1003->GetXaxis()->SetTitleSize(0.035);
   Graph_gLambda1003->GetXaxis()->SetTitleFont(42);
   Graph_gLambda1003->GetYaxis()->SetLabelFont(42);
   Graph_gLambda1003->GetYaxis()->SetLabelSize(0.035);
   Graph_gLambda1003->GetYaxis()->SetTitleSize(0.035);
   Graph_gLambda1003->GetYaxis()->SetTitleOffset(0);
   Graph_gLambda1003->GetYaxis()->SetTitleFont(42);
   Graph_gLambda1003->GetZaxis()->SetLabelFont(42);
   Graph_gLambda1003->GetZaxis()->SetLabelSize(0.035);
   Graph_gLambda1003->GetZaxis()->SetTitleSize(0.035);
   Graph_gLambda1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gLambda1003);
   
   gre->Draw(" p");
   
   Double_t gK0_fx1004[2] = {
   0,
   4.5};
   Double_t gK0_fy1004[2] = {
   0,
   -0.022};
   Double_t gK0_fex1004[2] = {
   0,
   0};
   Double_t gK0_fey1004[2] = {
   0,
   0.015};
   gre = new TGraphErrors(2,gK0_fx1004,gK0_fy1004,gK0_fex1004,gK0_fey1004);
   gre->SetName("gK0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gK01004 = new TH1F("Graph_gK01004","Graph",100,0.00495,4.95);
   Graph_gK01004->SetMinimum(-0.0407);
   Graph_gK01004->SetMaximum(0.0037);
   Graph_gK01004->SetDirectory(0);
   Graph_gK01004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gK01004->SetLineColor(ci);
   Graph_gK01004->GetXaxis()->SetLabelFont(42);
   Graph_gK01004->GetXaxis()->SetLabelSize(0.035);
   Graph_gK01004->GetXaxis()->SetTitleSize(0.035);
   Graph_gK01004->GetXaxis()->SetTitleFont(42);
   Graph_gK01004->GetYaxis()->SetLabelFont(42);
   Graph_gK01004->GetYaxis()->SetLabelSize(0.035);
   Graph_gK01004->GetYaxis()->SetTitleSize(0.035);
   Graph_gK01004->GetYaxis()->SetTitleOffset(0);
   Graph_gK01004->GetYaxis()->SetTitleFont(42);
   Graph_gK01004->GetZaxis()->SetLabelFont(42);
   Graph_gK01004->GetZaxis()->SetLabelSize(0.035);
   Graph_gK01004->GetZaxis()->SetTitleSize(0.035);
   Graph_gK01004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gK01004);
   
   gre->Draw(" p");
   
   Double_t gPiPlus_fx1005[2] = {
   0,
   4.5};
   Double_t gPiPlus_fy1005[2] = {
   0,
   -0.021};
   Double_t gPiPlus_fex1005[2] = {
   0,
   0};
   Double_t gPiPlus_fey1005[2] = {
   0,
   0.002};
   gre = new TGraphErrors(2,gPiPlus_fx1005,gPiPlus_fy1005,gPiPlus_fex1005,gPiPlus_fey1005);
   gre->SetName("gPiPlus");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_gPiPlus1005 = new TH1F("Graph_gPiPlus1005","Graph",100,0.00495,4.95);
   Graph_gPiPlus1005->SetMinimum(-0.0253);
   Graph_gPiPlus1005->SetMaximum(0.0023);
   Graph_gPiPlus1005->SetDirectory(0);
   Graph_gPiPlus1005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gPiPlus1005->SetLineColor(ci);
   Graph_gPiPlus1005->GetXaxis()->SetLabelFont(42);
   Graph_gPiPlus1005->GetXaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1005->GetXaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1005->GetXaxis()->SetTitleFont(42);
   Graph_gPiPlus1005->GetYaxis()->SetLabelFont(42);
   Graph_gPiPlus1005->GetYaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1005->GetYaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1005->GetYaxis()->SetTitleOffset(0);
   Graph_gPiPlus1005->GetYaxis()->SetTitleFont(42);
   Graph_gPiPlus1005->GetZaxis()->SetLabelFont(42);
   Graph_gPiPlus1005->GetZaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1005->GetZaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gPiPlus1005);
   
   gre->Draw(" p");
   
   Double_t gPiMinus_fx1006[2] = {
   0,
   4.5};
   Double_t gPiMinus_fy1006[2] = {
   0,
   -0.01};
   Double_t gPiMinus_fex1006[2] = {
   0,
   0};
   Double_t gPiMinus_fey1006[2] = {
   0,
   0.003};
   gre = new TGraphErrors(2,gPiMinus_fx1006,gPiMinus_fy1006,gPiMinus_fex1006,gPiMinus_fey1006);
   gre->SetName("gPiMinus");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_gPiMinus1006 = new TH1F("Graph_gPiMinus1006","Graph",100,0.00495,4.95);
   Graph_gPiMinus1006->SetMinimum(-0.0143);
   Graph_gPiMinus1006->SetMaximum(0.0013);
   Graph_gPiMinus1006->SetDirectory(0);
   Graph_gPiMinus1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gPiMinus1006->SetLineColor(ci);
   Graph_gPiMinus1006->GetXaxis()->SetLabelFont(42);
   Graph_gPiMinus1006->GetXaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1006->GetXaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1006->GetXaxis()->SetTitleFont(42);
   Graph_gPiMinus1006->GetYaxis()->SetLabelFont(42);
   Graph_gPiMinus1006->GetYaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1006->GetYaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1006->GetYaxis()->SetTitleOffset(0);
   Graph_gPiMinus1006->GetYaxis()->SetTitleFont(42);
   Graph_gPiMinus1006->GetZaxis()->SetLabelFont(42);
   Graph_gPiMinus1006->GetZaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1006->GetZaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gPiMinus1006);
   
   gre->Draw(" p");
   
   Double_t bespsys_fx1007[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   210};
   Double_t bespsys_fy1007[8] = {
   0.022534,
   -0.000486069,
   -0.00684062,
   -0.00690107,
   -0.00561899,
   -0.00415636,
   -0.00267291,
   -0.000821396};
   Double_t bespsys_fex1007[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t bespsys_fey1007[8] = {
   0.00447883,
   0.00225644,
   0.0021,
   0.000933001,
   0.0008,
   0.0001,
   0,
   0};
   gre = new TGraphErrors(8,bespsys_fx1007,bespsys_fy1007,bespsys_fex1007,bespsys_fey1007);
   gre->SetName("bespsys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);

   ci = TColor::GetColor("#cccccc");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(24);
   
   TH1F *Graph_bespsys1007 = new TH1F("Graph_bespsys1007","Graph",100,6.93,230.23);
   Graph_bespsys1007->SetMinimum(-0.01253596);
   Graph_bespsys1007->SetMaximum(0.03060817);
   Graph_bespsys1007->SetDirectory(0);
   Graph_bespsys1007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_bespsys1007->SetLineColor(ci);
   Graph_bespsys1007->GetXaxis()->SetLabelFont(42);
   Graph_bespsys1007->GetXaxis()->SetLabelSize(0.035);
   Graph_bespsys1007->GetXaxis()->SetTitleSize(0.035);
   Graph_bespsys1007->GetXaxis()->SetTitleFont(42);
   Graph_bespsys1007->GetYaxis()->SetLabelFont(42);
   Graph_bespsys1007->GetYaxis()->SetLabelSize(0.035);
   Graph_bespsys1007->GetYaxis()->SetTitleSize(0.035);
   Graph_bespsys1007->GetYaxis()->SetTitleOffset(0);
   Graph_bespsys1007->GetYaxis()->SetTitleFont(42);
   Graph_bespsys1007->GetZaxis()->SetLabelFont(42);
   Graph_bespsys1007->GetZaxis()->SetLabelSize(0.035);
   Graph_bespsys1007->GetZaxis()->SetTitleSize(0.035);
   Graph_bespsys1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_bespsys1007);
   
   gre->Draw(" e1");
   
   Double_t besp_fx1008[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   210};
   Double_t besp_fy1008[8] = {
   0.022534,
   -0.000486069,
   -0.00684062,
   -0.00690107,
   -0.00561899,
   -0.00415636,
   -0.00267291,
   -0.000821396};
   Double_t besp_fex1008[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t besp_fey1008[8] = {
   0.000863638,
   0.000618966,
   0.000843574,
   0.000853584,
   0.000836661,
   0.000565664,
   0.00195178,
   0.000211236};
   gre = new TGraphErrors(8,besp_fx1008,besp_fy1008,besp_fex1008,besp_fey1008);
   gre->SetName("besp");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_besp1008 = new TH1F("Graph_besp1008","Graph",100,6.93,230.23);
   Graph_besp1008->SetMinimum(-0.01086988);
   Graph_besp1008->SetMaximum(0.02651287);
   Graph_besp1008->SetDirectory(0);
   Graph_besp1008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_besp1008->SetLineColor(ci);
   Graph_besp1008->GetXaxis()->SetLabelFont(42);
   Graph_besp1008->GetXaxis()->SetLabelSize(0.035);
   Graph_besp1008->GetXaxis()->SetTitleSize(0.035);
   Graph_besp1008->GetXaxis()->SetTitleFont(42);
   Graph_besp1008->GetYaxis()->SetLabelFont(42);
   Graph_besp1008->GetYaxis()->SetLabelSize(0.035);
   Graph_besp1008->GetYaxis()->SetTitleSize(0.035);
   Graph_besp1008->GetYaxis()->SetTitleOffset(0);
   Graph_besp1008->GetYaxis()->SetTitleFont(42);
   Graph_besp1008->GetZaxis()->SetLabelFont(42);
   Graph_besp1008->GetZaxis()->SetLabelSize(0.035);
   Graph_besp1008->GetZaxis()->SetTitleSize(0.035);
   Graph_besp1008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_besp1008);
   
   gre->Draw(" p9");
   
   Double_t bespipsys_fx1009[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   200};
   Double_t bespipsys_fy1009[8] = {
   -0.0249697,
   -0.0245736,
   -0.0189913,
   -0.0169655,
   -0.0136131,
   -0.0108059,
   -0.00587525,
   -0.00235619};
   Double_t bespipsys_fex1009[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t bespipsys_fey1009[8] = {
   0.00022904,
   0.001047249,
   0.001047249,
   7.63896e-05,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(8,bespipsys_fx1009,bespipsys_fy1009,bespipsys_fex1009,bespipsys_fey1009);
   gre->SetName("bespipsys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);
   gre->SetMarkerStyle(25);
   
   TH1F *Graph_bespipsys1009 = new TH1F("Graph_bespipsys1009","Graph",100,6.93,219.23);
   Graph_bespipsys1009->SetMinimum(-0.02794731);
   Graph_bespipsys1009->SetMaximum(-2.97241e-05);
   Graph_bespipsys1009->SetDirectory(0);
   Graph_bespipsys1009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_bespipsys1009->SetLineColor(ci);
   Graph_bespipsys1009->GetXaxis()->SetLabelFont(42);
   Graph_bespipsys1009->GetXaxis()->SetLabelSize(0.035);
   Graph_bespipsys1009->GetXaxis()->SetTitleSize(0.035);
   Graph_bespipsys1009->GetXaxis()->SetTitleFont(42);
   Graph_bespipsys1009->GetYaxis()->SetLabelFont(42);
   Graph_bespipsys1009->GetYaxis()->SetLabelSize(0.035);
   Graph_bespipsys1009->GetYaxis()->SetTitleSize(0.035);
   Graph_bespipsys1009->GetYaxis()->SetTitleOffset(0);
   Graph_bespipsys1009->GetYaxis()->SetTitleFont(42);
   Graph_bespipsys1009->GetZaxis()->SetLabelFont(42);
   Graph_bespipsys1009->GetZaxis()->SetLabelSize(0.035);
   Graph_bespipsys1009->GetZaxis()->SetTitleSize(0.035);
   Graph_bespipsys1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_bespipsys1009);
   
   gre->Draw(" z9");
   
   Double_t bespip_fx1010[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   200};
   Double_t bespip_fy1010[8] = {
   -0.0249697,
   -0.0245736,
   -0.0189913,
   -0.0169655,
   -0.0136131,
   -0.0108059,
   -0.00587525,
   -0.00235619};
   Double_t bespip_fex1010[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t bespip_fey1010[8] = {
   0.000602224,
   0.000464752,
   0.000408242,
   0.000309662,
   0.000278147,
   0.000191003,
   0.00069624,
   5.23337e-05};
   gre = new TGraphErrors(8,bespip_fx1010,bespip_fy1010,bespip_fex1010,bespip_fey1010);
   gre->SetName("bespip");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_bespip1010 = new TH1F("Graph_bespip1010","Graph",100,6.93,219.23);
   Graph_bespip1010->SetMinimum(-0.02789873);
   Graph_bespip1010->SetMaximum(2.295047e-05);
   Graph_bespip1010->SetDirectory(0);
   Graph_bespip1010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_bespip1010->SetLineColor(ci);
   Graph_bespip1010->GetXaxis()->SetLabelFont(42);
   Graph_bespip1010->GetXaxis()->SetLabelSize(0.035);
   Graph_bespip1010->GetXaxis()->SetTitleSize(0.035);
   Graph_bespip1010->GetXaxis()->SetTitleFont(42);
   Graph_bespip1010->GetYaxis()->SetLabelFont(42);
   Graph_bespip1010->GetYaxis()->SetLabelSize(0.035);
   Graph_bespip1010->GetYaxis()->SetTitleSize(0.035);
   Graph_bespip1010->GetYaxis()->SetTitleOffset(0);
   Graph_bespip1010->GetYaxis()->SetTitleFont(42);
   Graph_bespip1010->GetZaxis()->SetLabelFont(42);
   Graph_bespip1010->GetZaxis()->SetLabelSize(0.035);
   Graph_bespip1010->GetZaxis()->SetTitleSize(0.035);
   Graph_bespip1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_bespip1010);
   
   gre->Draw(" p9");
   
   Double_t beslamsys_fx1011[8] = {
   7.9,
   11.7,
   14.7,
   19.8,
   27.1,
   40,
   64.4,
   210};
   Double_t beslamsys_fy1011[8] = {
   0.0219604,
   0.00287503,
   -0.00372834,
   -0.004377403,
   -0.005538417,
   -0.00535152,
   -0.0213087,
   -0.00519764};
   Double_t beslamsys_fex1011[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t beslamsys_fey1011[8] = {
   0.00674509,
   0.00366773,
   0.0032,
   0.00316483,
   0.00158462,
   0.00188411,
   0,
   0};
   gre = new TGraphErrors(8,beslamsys_fx1011,beslamsys_fy1011,beslamsys_fex1011,beslamsys_fey1011);
   gre->SetName("beslamsys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);
   gre->SetMarkerStyle(27);
   
   TH1F *Graph_beslamsys1011 = new TH1F("Graph_beslamsys1011","Graph",100,7.11,230.21);
   Graph_beslamsys1011->SetMinimum(-0.02631012);
   Graph_beslamsys1011->SetMaximum(0.03370691);
   Graph_beslamsys1011->SetDirectory(0);
   Graph_beslamsys1011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_beslamsys1011->SetLineColor(ci);
   Graph_beslamsys1011->GetXaxis()->SetLabelFont(42);
   Graph_beslamsys1011->GetXaxis()->SetLabelSize(0.035);
   Graph_beslamsys1011->GetXaxis()->SetTitleSize(0.035);
   Graph_beslamsys1011->GetXaxis()->SetTitleFont(42);
   Graph_beslamsys1011->GetYaxis()->SetLabelFont(42);
   Graph_beslamsys1011->GetYaxis()->SetLabelSize(0.035);
   Graph_beslamsys1011->GetYaxis()->SetTitleSize(0.035);
   Graph_beslamsys1011->GetYaxis()->SetTitleOffset(0);
   Graph_beslamsys1011->GetYaxis()->SetTitleFont(42);
   Graph_beslamsys1011->GetZaxis()->SetLabelFont(42);
   Graph_beslamsys1011->GetZaxis()->SetLabelSize(0.035);
   Graph_beslamsys1011->GetZaxis()->SetTitleSize(0.035);
   Graph_beslamsys1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_beslamsys1011);
   
   gre->Draw(" z9");
   
   Double_t beslam_fx1012[8] = {
   7.9,
   11.7,
   14.7,
   19.8,
   27.1,
   40,
   64.4,
   210};
   Double_t beslam_fy1012[8] = {
   0.0219604,
   0.00287503,
   -0.00372834,
   -0.004377403,
   -0.005538417,
   -0.00535152,
   -0.0213087,
   -0.00519764};
   Double_t beslam_fex1012[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t beslam_fey1012[8] = {
   0.00277975,
   0.00165445,
   0.0021826,
   0.001498803,
   0.001103134,
   0.00118511,
   0.00422293,
   0.000728209};
   gre = new TGraphErrors(8,beslam_fx1012,beslam_fy1012,beslam_fex1012,beslam_fey1012);
   gre->SetName("beslam");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_beslam1012 = new TH1F("Graph_beslam1012","Graph",100,7.11,230.21);
   Graph_beslam1012->SetMinimum(-0.03055881);
   Graph_beslam1012->SetMaximum(0.02976733);
   Graph_beslam1012->SetDirectory(0);
   Graph_beslam1012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_beslam1012->SetLineColor(ci);
   Graph_beslam1012->GetXaxis()->SetLabelFont(42);
   Graph_beslam1012->GetXaxis()->SetLabelSize(0.035);
   Graph_beslam1012->GetXaxis()->SetTitleSize(0.035);
   Graph_beslam1012->GetXaxis()->SetTitleFont(42);
   Graph_beslam1012->GetYaxis()->SetLabelFont(42);
   Graph_beslam1012->GetYaxis()->SetLabelSize(0.035);
   Graph_beslam1012->GetYaxis()->SetTitleSize(0.035);
   Graph_beslam1012->GetYaxis()->SetTitleOffset(0);
   Graph_beslam1012->GetYaxis()->SetTitleFont(42);
   Graph_beslam1012->GetZaxis()->SetLabelFont(42);
   Graph_beslam1012->GetZaxis()->SetLabelSize(0.035);
   Graph_beslam1012->GetZaxis()->SetTitleSize(0.035);
   Graph_beslam1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_beslam1012);
   
   gre->Draw(" p9");
   
   Double_t besk0sys_fx1013[8] = {
   7.9,
   11.7,
   14.9,
   19.8,
   27.2,
   40,
   68.4,
   200};
   Double_t besk0sys_fy1013[8] = {
   -0.0105555,
   -0.0148316,
   -0.0140691,
   -0.0142977,
   -0.012588,
   -0.00980226,
   -0.0154763,
   -0.00376787};
   Double_t besk0sys_fex1013[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t besk0sys_fey1013[8] = {
   0.0023322,
   0.0021463,
   0.00253,
   0.00132324,
   0.0008521,
   0.0008324,
   0,
   0};
   gre = new TGraphErrors(8,besk0sys_fx1013,besk0sys_fy1013,besk0sys_fex1013,besk0sys_fey1013);
   gre->SetName("besk0sys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);
   gre->SetMarkerStyle(30);
   
   TH1F *Graph_besk0sys1013 = new TH1F("Graph_besk0sys1013","Graph",100,7.11,219.21);
   Graph_besk0sys1013->SetMinimum(-0.0182989);
   Graph_besk0sys1013->SetMaximum(-0.002446867);
   Graph_besk0sys1013->SetDirectory(0);
   Graph_besk0sys1013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_besk0sys1013->SetLineColor(ci);
   Graph_besk0sys1013->GetXaxis()->SetLabelFont(42);
   Graph_besk0sys1013->GetXaxis()->SetLabelSize(0.035);
   Graph_besk0sys1013->GetXaxis()->SetTitleSize(0.035);
   Graph_besk0sys1013->GetXaxis()->SetTitleFont(42);
   Graph_besk0sys1013->GetYaxis()->SetLabelFont(42);
   Graph_besk0sys1013->GetYaxis()->SetLabelSize(0.035);
   Graph_besk0sys1013->GetYaxis()->SetTitleSize(0.035);
   Graph_besk0sys1013->GetYaxis()->SetTitleOffset(0);
   Graph_besk0sys1013->GetYaxis()->SetTitleFont(42);
   Graph_besk0sys1013->GetZaxis()->SetLabelFont(42);
   Graph_besk0sys1013->GetZaxis()->SetLabelSize(0.035);
   Graph_besk0sys1013->GetZaxis()->SetTitleSize(0.035);
   Graph_besk0sys1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_besk0sys1013);
   
   gre->Draw(" z9");
   
   Double_t besk0_fx1014[8] = {
   7.9,
   11.7,
   14.9,
   19.8,
   27.2,
   40,
   68.4,
   200};
   Double_t besk0_fy1014[8] = {
   -0.0105555,
   -0.0148316,
   -0.0140691,
   -0.0142977,
   -0.012588,
   -0.00980226,
   -0.0154763,
   -0.00376787};
   Double_t besk0_fex1014[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t besk0_fey1014[8] = {
   0.00339845,
   0.00178109,
   0.00219612,
   0.001429088,
   0.0009745382,
   0.00102444,
   0.00362509,
   0.000515414};
   gre = new TGraphErrors(8,besk0_fx1014,besk0_fy1014,besk0_fex1014,besk0_fey1014);
   gre->SetName("besk0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_besk01014 = new TH1F("Graph_besk01014","Graph",100,7.11,219.21);
   Graph_besk01014->SetMinimum(-0.02068628);
   Graph_besk01014->SetMaximum(-0.001667563);
   Graph_besk01014->SetDirectory(0);
   Graph_besk01014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_besk01014->SetLineColor(ci);
   Graph_besk01014->GetXaxis()->SetLabelFont(42);
   Graph_besk01014->GetXaxis()->SetLabelSize(0.035);
   Graph_besk01014->GetXaxis()->SetTitleSize(0.035);
   Graph_besk01014->GetXaxis()->SetTitleFont(42);
   Graph_besk01014->GetYaxis()->SetLabelFont(42);
   Graph_besk01014->GetYaxis()->SetLabelSize(0.035);
   Graph_besk01014->GetYaxis()->SetTitleSize(0.035);
   Graph_besk01014->GetYaxis()->SetTitleOffset(0);
   Graph_besk01014->GetYaxis()->SetTitleFont(42);
   Graph_besk01014->GetZaxis()->SetLabelFont(42);
   Graph_besk01014->GetZaxis()->SetLabelSize(0.035);
   Graph_besk01014->GetZaxis()->SetTitleSize(0.035);
   Graph_besk01014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_besk01014);
   
   gre->Draw(" p9");
   
   Double_t besphisys_fx1015[8] = {
   7.5,
   11.3,
   14.5,
   19.8,
   27.2,
   40,
   62.4,
   200};
   Double_t besphisys_fy1015[8] = {
   -999,
   0.0141509,
   -0.033784,
   -0.0276079,
   -0.0217054,
   -0.0166407,
   -999,
   -999};
   Double_t besphisys_fex1015[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t besphisys_fey1015[8] = {
   0.0365171,
   0.0236055,
   0.0248385,
   0.0110184,
   0.00593316,
   0.008107,
   0,
   0};
   gre = new TGraphErrors(8,besphisys_fx1015,besphisys_fy1015,besphisys_fex1015,besphisys_fey1015);
   gre->SetName("besphisys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);
   gre->SetMarkerStyle(34);
   
   TH1F *Graph_besphisys1015 = new TH1F("Graph_besphisys1015","Graph",100,6.75,219.25);
   Graph_besphisys1015->SetMinimum(-1098.944);
   Graph_besphisys1015->SetMaximum(99.94518);
   Graph_besphisys1015->SetDirectory(0);
   Graph_besphisys1015->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_besphisys1015->SetLineColor(ci);
   Graph_besphisys1015->GetXaxis()->SetLabelFont(42);
   Graph_besphisys1015->GetXaxis()->SetLabelSize(0.035);
   Graph_besphisys1015->GetXaxis()->SetTitleSize(0.035);
   Graph_besphisys1015->GetXaxis()->SetTitleFont(42);
   Graph_besphisys1015->GetYaxis()->SetLabelFont(42);
   Graph_besphisys1015->GetYaxis()->SetLabelSize(0.035);
   Graph_besphisys1015->GetYaxis()->SetTitleSize(0.035);
   Graph_besphisys1015->GetYaxis()->SetTitleOffset(0);
   Graph_besphisys1015->GetYaxis()->SetTitleFont(42);
   Graph_besphisys1015->GetZaxis()->SetLabelFont(42);
   Graph_besphisys1015->GetZaxis()->SetLabelSize(0.035);
   Graph_besphisys1015->GetZaxis()->SetTitleSize(0.035);
   Graph_besphisys1015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_besphisys1015);
   
   gre->Draw(" z9");
   
   Double_t besphi_fx1016[8] = {
   7.5,
   11.3,
   14.5,
   19.8,
   27.2,
   40,
   62.4,
   200};
   Double_t besphi_fy1016[8] = {
   -999,
   0.0141509,
   -0.033784,
   -0.0276079,
   -0.0217054,
   -0.0166407,
   -999,
   -999};
   Double_t besphi_fex1016[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t besphi_fey1016[8] = {
   0.0155563,
   0.0156337,
   0.00525107,
   0.00458413,
   0.00413452,
   0.00572114,
   0,
   0};
   gre = new TGraphErrors(8,besphi_fx1016,besphi_fy1016,besphi_fex1016,besphi_fey1016);
   gre->SetName("besphi");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_besphi1016 = new TH1F("Graph_besphi1016","Graph",100,6.75,219.25);
   Graph_besphi1016->SetMinimum(-1098.92);
   Graph_besphi1016->SetMaximum(99.93432);
   Graph_besphi1016->SetDirectory(0);
   Graph_besphi1016->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_besphi1016->SetLineColor(ci);
   Graph_besphi1016->GetXaxis()->SetLabelFont(42);
   Graph_besphi1016->GetXaxis()->SetLabelSize(0.035);
   Graph_besphi1016->GetXaxis()->SetTitleSize(0.035);
   Graph_besphi1016->GetXaxis()->SetTitleFont(42);
   Graph_besphi1016->GetYaxis()->SetLabelFont(42);
   Graph_besphi1016->GetYaxis()->SetLabelSize(0.035);
   Graph_besphi1016->GetYaxis()->SetTitleSize(0.035);
   Graph_besphi1016->GetYaxis()->SetTitleOffset(0);
   Graph_besphi1016->GetYaxis()->SetTitleFont(42);
   Graph_besphi1016->GetZaxis()->SetLabelFont(42);
   Graph_besphi1016->GetZaxis()->SetLabelSize(0.035);
   Graph_besphi1016->GetZaxis()->SetTitleSize(0.035);
   Graph_besphi1016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_besphi1016);
   
   gre->Draw(" p9");
   TLatex *   tex = new TLatex(0.16,0.9,"STAR Preliminary");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.16,0.85,"Statistical Errors Only");
tex->SetNDC();
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(2,0,50,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
      tex = new TLatex(15,0.01,"STAR BES 10-40%");
   tex->SetTextAlign(13);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.6,0.01,"STAR FXT 10-25%");
   tex->SetTextAlign(13);
   tex->SetTextColor(2);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(2.6,0.25,"E895 12-25%");
   tex->SetTextAlign(13);

   ci = TColor::GetColor("#5b9f1d");
   tex->SetTextColor(ci);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.44,0.54,0.94,0.94,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/gP","p (STAR FXT)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gPiPlus","#pi^{#font[122]{+} } (STAR FXT)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gPiMinus","#pi^{#font[122]{-} } (STAR FXT)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gK0","K^{0}_{S} (STAR FXT)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(30);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gLambda","#Lambda (STAR FXT)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/besp","p (STAR BES)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/bespip","#pi^{#font[122]{+} } (STAR BES)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/besk0","K^{0}_{S} (STAR BES)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(30);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/beslam","#Lambda (STAR BES)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gP895","p (E895)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
