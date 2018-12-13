void figure_4()
{
//=========Macro generated from canvas: c/c
//=========  (Tue Oct 30 16:52:17 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-2.634146,-19.6875,2.243902,111.5625);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogz();
   c->SetLeftMargin(0.13);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {-2, -1.96, -1.92, -1.88, -1.84, -1.8, -1.76, -1.72, -1.68, -1.64, -1.6, -1.56, -1.52, -1.48, -1.44, -1.4, -1.36, -1.32, -1.28, -1.24, -1.2, -1.16, -1.12, -1.08, -1.04, -1, -0.96, -0.92, -0.88, -0.84, -0.8, -0.76, -0.72, -0.68, -0.64, -0.6, -0.56, -0.52, -0.48, -0.44, -0.4, -0.36, -0.32, -0.28, -0.24, -0.2, -0.16, -0.12, -0.08, -0.04, 1.235123e-15, 0.04, 0.08, 0.12, 0.16, 0.2, 0.24, 0.28, 0.32, 0.36, 0.4, 0.44, 0.48, 0.52, 0.56, 0.6, 0.64, 0.68, 0.72, 0.76, 0.8, 0.84, 0.88, 0.92, 0.96, 1, 1.04, 1.08, 1.12, 1.16, 1.2, 1.24, 1.28, 1.32, 1.36, 1.4, 1.44, 1.48, 1.52, 1.56, 1.6, 1.64, 1.68, 1.72, 1.76, 1.8, 1.84, 1.88, 1.92, 1.96, 2}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(0);
   frame_5PN2__1->SetMaximum(105);
   frame_5PN2__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetTitle("y-y_{CM}");
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.06111111);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.07222223);
   frame_5PN2__1->GetXaxis()->SetTitleOffset(0.9);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("dN/dy");
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.06111111);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.07222223);
   frame_5PN2__1->GetYaxis()->SetTitleOffset(0.85);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t E895_fx1001[29] = {
   -1.2,
   -1.1,
   -1,
   -0.9,
   -0.8,
   -0.7,
   -0.6,
   -0.5,
   -0.4,
   -0.3,
   -0.2,
   -0.1,
   0,
   0.1,
   0.2,
   0.3,
   0.4,
   0.5,
   0.6,
   0.7,
   0.8,
   0.9,
   1,
   1.1,
   1.2,
   1.3,
   1.4,
   1.5,
   1.5};
   Double_t E895_fy1001[29] = {
   22.852,
   25.778,
   29.23,
   32.378,
   36.666,
   43.563,
   45.53,
   51.348,
   53.07,
   56.732,
   58.606,
   58.362,
   60.844,
   61.01,
   60.915,
   59.05,
   55.77,
   52.22,
   47.773,
   44.318,
   40.31,
   35.796,
   30.993,
   27.961,
   25.212,
   19.799,
   15.081,
   11.04,
   11.04};
   Double_t E895_fex1001[29] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t E895_fey1001[29] = {
   5.656854,
   5.656854,
   5.656854,
   5.656854,
   5.656854,
   9.899495,
   9.899495,
   4.242641,
   4.242641,
   4.242641,
   4.242641,
   4.242641,
   7.071068,
   7.071068,
   7.071068,
   5.656854,
   5.656854,
   5.656854,
   4.242641,
   4.242641,
   4.242641,
   4.242641,
   2.828427,
   2.828427,
   2.828427,
   1.414214,
   1.414214,
   1.414214,
   1.414214};
   TGraphErrors *gre = new TGraphErrors(29,E895_fx1001,E895_fy1001,E895_fex1001,E895_fey1001);
   gre->SetName("E895");
   gre->SetTitle("");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_E8951001 = new TH1F("Graph_E8951001","",100,-1.47,1.77);
   Graph_E8951001->SetMinimum(3.780258);
   Graph_E8951001->SetMaximum(73.9266);
   Graph_E8951001->SetDirectory(0);
   Graph_E8951001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_E8951001->SetLineColor(ci);
   Graph_E8951001->GetXaxis()->SetLabelFont(42);
   Graph_E8951001->GetXaxis()->SetLabelSize(0.035);
   Graph_E8951001->GetXaxis()->SetTitleSize(0.035);
   Graph_E8951001->GetXaxis()->SetTitleFont(42);
   Graph_E8951001->GetYaxis()->SetLabelFont(42);
   Graph_E8951001->GetYaxis()->SetLabelSize(0.035);
   Graph_E8951001->GetYaxis()->SetTitleSize(0.035);
   Graph_E8951001->GetYaxis()->SetTitleOffset(0);
   Graph_E8951001->GetYaxis()->SetTitleFont(42);
   Graph_E8951001->GetZaxis()->SetLabelFont(42);
   Graph_E8951001->GetZaxis()->SetLabelSize(0.035);
   Graph_E8951001->GetZaxis()->SetTitleSize(0.035);
   Graph_E8951001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_E8951001);
   
   gre->Draw(" pz");
   
   Double_t E802_fx1002[8] = {
   0.35,
   0.45,
   0.55,
   0.65,
   0.75,
   0.85,
   0.95,
   0.95};
   Double_t E802_fy1002[8] = {
   67,
   62,
   58,
   53,
   50,
   45,
   41,
   41};
   Double_t E802_fex1002[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t E802_fey1002[8] = {
   2,
   1,
   1,
   1,
   1,
   1,
   3,
   3};
   gre = new TGraphErrors(8,E802_fx1002,E802_fy1002,E802_fex1002,E802_fey1002);
   gre->SetName("E802");
   gre->SetTitle("");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_E8021002 = new TH1F("Graph_E8021002","",100,0.29,1.01);
   Graph_E8021002->SetMinimum(34.9);
   Graph_E8021002->SetMaximum(72.1);
   Graph_E8021002->SetDirectory(0);
   Graph_E8021002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_E8021002->SetLineColor(ci);
   Graph_E8021002->GetXaxis()->SetLabelFont(42);
   Graph_E8021002->GetXaxis()->SetLabelSize(0.035);
   Graph_E8021002->GetXaxis()->SetTitleSize(0.035);
   Graph_E8021002->GetXaxis()->SetTitleFont(42);
   Graph_E8021002->GetYaxis()->SetLabelFont(42);
   Graph_E8021002->GetYaxis()->SetLabelSize(0.035);
   Graph_E8021002->GetYaxis()->SetTitleSize(0.035);
   Graph_E8021002->GetYaxis()->SetTitleOffset(0);
   Graph_E8021002->GetYaxis()->SetTitleFont(42);
   Graph_E8021002->GetZaxis()->SetLabelFont(42);
   Graph_E8021002->GetZaxis()->SetLabelSize(0.035);
   Graph_E8021002->GetZaxis()->SetTitleSize(0.035);
   Graph_E8021002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_E8021002);
   
   gre->Draw(" pz");
   
   Double_t E802Ref_fx1003[8] = {
   -0.35,
   -0.45,
   -0.55,
   -0.65,
   -0.75,
   -0.85,
   -0.95,
   -0.95};
   Double_t E802Ref_fy1003[8] = {
   67,
   62,
   58,
   53,
   50,
   45,
   41,
   41};
   Double_t E802Ref_fex1003[8] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t E802Ref_fey1003[8] = {
   2,
   1,
   1,
   1,
   1,
   1,
   3,
   3};
   gre = new TGraphErrors(8,E802Ref_fx1003,E802Ref_fy1003,E802Ref_fex1003,E802Ref_fey1003);
   gre->SetName("E802Ref");
   gre->SetTitle("");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_E802Ref1003 = new TH1F("Graph_E802Ref1003","",100,-1.01,-0.29);
   Graph_E802Ref1003->SetMinimum(34.9);
   Graph_E802Ref1003->SetMaximum(72.1);
   Graph_E802Ref1003->SetDirectory(0);
   Graph_E802Ref1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_E802Ref1003->SetLineColor(ci);
   Graph_E802Ref1003->GetXaxis()->SetLabelFont(42);
   Graph_E802Ref1003->GetXaxis()->SetLabelSize(0.035);
   Graph_E802Ref1003->GetXaxis()->SetTitleSize(0.035);
   Graph_E802Ref1003->GetXaxis()->SetTitleFont(42);
   Graph_E802Ref1003->GetYaxis()->SetLabelFont(42);
   Graph_E802Ref1003->GetYaxis()->SetLabelSize(0.035);
   Graph_E802Ref1003->GetYaxis()->SetTitleSize(0.035);
   Graph_E802Ref1003->GetYaxis()->SetTitleOffset(0);
   Graph_E802Ref1003->GetYaxis()->SetTitleFont(42);
   Graph_E802Ref1003->GetZaxis()->SetLabelFont(42);
   Graph_E802Ref1003->GetZaxis()->SetLabelSize(0.035);
   Graph_E802Ref1003->GetZaxis()->SetTitleSize(0.035);
   Graph_E802Ref1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_E802Ref1003);
   
   gre->Draw(" pz");
   
   Double_t E877_fx1004[7] = {
   1.4,
   1.5,
   1.6,
   1.7,
   1.8,
   1.9,
   1.9};
   Double_t E877_fy1004[7] = {
   23,
   20,
   15,
   12,
   10,
   7,
   7};
   Double_t E877_fex1004[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t E877_fey1004[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   gre = new TGraphErrors(7,E877_fx1004,E877_fy1004,E877_fex1004,E877_fey1004);
   gre->SetName("E877");
   gre->SetTitle("");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_E8771004 = new TH1F("Graph_E8771004","",100,1.35,1.95);
   Graph_E8771004->SetMinimum(4.2);
   Graph_E8771004->SetMaximum(25.8);
   Graph_E8771004->SetDirectory(0);
   Graph_E8771004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_E8771004->SetLineColor(ci);
   Graph_E8771004->GetXaxis()->SetLabelFont(42);
   Graph_E8771004->GetXaxis()->SetLabelSize(0.035);
   Graph_E8771004->GetXaxis()->SetTitleSize(0.035);
   Graph_E8771004->GetXaxis()->SetTitleFont(42);
   Graph_E8771004->GetYaxis()->SetLabelFont(42);
   Graph_E8771004->GetYaxis()->SetLabelSize(0.035);
   Graph_E8771004->GetYaxis()->SetTitleSize(0.035);
   Graph_E8771004->GetYaxis()->SetTitleOffset(0);
   Graph_E8771004->GetYaxis()->SetTitleFont(42);
   Graph_E8771004->GetZaxis()->SetLabelFont(42);
   Graph_E8771004->GetZaxis()->SetLabelSize(0.035);
   Graph_E8771004->GetZaxis()->SetTitleSize(0.035);
   Graph_E8771004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_E8771004);
   
   gre->Draw(" pz");
   
   Double_t E877Ref_fx1005[7] = {
   -1.4,
   -1.5,
   -1.6,
   -1.7,
   -1.8,
   -1.9,
   -1.9};
   Double_t E877Ref_fy1005[7] = {
   23,
   20,
   15,
   12,
   10,
   7,
   7};
   Double_t E877Ref_fex1005[7] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t E877Ref_fey1005[7] = {
   1,
   1,
   1,
   1,
   1,
   1,
   1};
   gre = new TGraphErrors(7,E877Ref_fx1005,E877Ref_fy1005,E877Ref_fex1005,E877Ref_fey1005);
   gre->SetName("E877Ref");
   gre->SetTitle("");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_E877Ref1005 = new TH1F("Graph_E877Ref1005","",100,-1.95,-1.35);
   Graph_E877Ref1005->SetMinimum(4.2);
   Graph_E877Ref1005->SetMaximum(25.8);
   Graph_E877Ref1005->SetDirectory(0);
   Graph_E877Ref1005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_E877Ref1005->SetLineColor(ci);
   Graph_E877Ref1005->GetXaxis()->SetLabelFont(42);
   Graph_E877Ref1005->GetXaxis()->SetLabelSize(0.035);
   Graph_E877Ref1005->GetXaxis()->SetTitleSize(0.035);
   Graph_E877Ref1005->GetXaxis()->SetTitleFont(42);
   Graph_E877Ref1005->GetYaxis()->SetLabelFont(42);
   Graph_E877Ref1005->GetYaxis()->SetLabelSize(0.035);
   Graph_E877Ref1005->GetYaxis()->SetTitleSize(0.035);
   Graph_E877Ref1005->GetYaxis()->SetTitleOffset(0);
   Graph_E877Ref1005->GetYaxis()->SetTitleFont(42);
   Graph_E877Ref1005->GetZaxis()->SetLabelFont(42);
   Graph_E877Ref1005->GetZaxis()->SetLabelSize(0.035);
   Graph_E877Ref1005->GetZaxis()->SetTitleSize(0.035);
   Graph_E877Ref1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_E877Ref1005);
   
   gre->Draw(" pz");
   
   Double_t dNdy_fx1006[17] = {
   -0.28,
   -0.18,
   -0.08,
   0.02,
   0.12,
   0.22,
   0.32,
   0.42,
   0.52,
   0.62,
   0.72,
   0.82,
   0.92,
   1.02,
   1.12,
   1.22,
   1.32};
   Double_t dNdy_fy1006[17] = {
   59.55394,
   62.14294,
   63.4345,
   64.98626,
   64.76317,
   63.90757,
   61.07911,
   57.95785,
   54.95168,
   52.47702,
   48.4227,
   43.97067,
   39.9699,
   34.98558,
   29.80961,
   24.92865,
   20.34879};
   Double_t dNdy_fex1006[17] = {
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02,
   0.02};
   Double_t dNdy_fey1006[17] = {
   7.948697,
   8.09506,
   8.250643,
   8.451945,
   8.421631,
   8.312231,
   7.942503,
   7.536059,
   7.146268,
   6.825933,
   6.300152,
   5.722741,
   5.200635,
   4.551912,
   3.877779,
   3.244377,
   2.649959};
   gre = new TGraphErrors(17,dNdy_fx1006,dNdy_fy1006,dNdy_fex1006,dNdy_fey1006);
   gre->SetName("dNdy");
   gre->SetTitle("");

   ci = 1434;
   color = new TColor(ci, 1, 0, 0, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_dNdy1006 = new TH1F("Graph_dNdy1006","",100,-0.464,1.504);
   Graph_dNdy1006->SetMinimum(12.1249);
   Graph_dNdy1006->SetMaximum(79.01214);
   Graph_dNdy1006->SetDirectory(0);
   Graph_dNdy1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_dNdy1006->SetLineColor(ci);
   Graph_dNdy1006->GetXaxis()->SetLabelFont(42);
   Graph_dNdy1006->GetXaxis()->SetLabelSize(0.035);
   Graph_dNdy1006->GetXaxis()->SetTitleSize(0.035);
   Graph_dNdy1006->GetXaxis()->SetTitleFont(42);
   Graph_dNdy1006->GetYaxis()->SetLabelFont(42);
   Graph_dNdy1006->GetYaxis()->SetLabelSize(0.035);
   Graph_dNdy1006->GetYaxis()->SetTitleSize(0.035);
   Graph_dNdy1006->GetYaxis()->SetTitleOffset(0);
   Graph_dNdy1006->GetYaxis()->SetTitleFont(42);
   Graph_dNdy1006->GetZaxis()->SetLabelFont(42);
   Graph_dNdy1006->GetZaxis()->SetLabelSize(0.035);
   Graph_dNdy1006->GetZaxis()->SetTitleSize(0.035);
   Graph_dNdy1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_dNdy1006);
   
   gre->Draw(" pe2");
   
   Double_t reflected_fx1007[17] = {
   0.28,
   0.18,
   0.08,
   -0.02,
   -0.12,
   -0.22,
   -0.32,
   -0.42,
   -0.52,
   -0.62,
   -0.72,
   -0.82,
   -0.92,
   -1.02,
   -1.12,
   -1.22,
   -1.32};
   Double_t reflected_fy1007[17] = {
   59.55394,
   62.14294,
   63.4345,
   64.98626,
   64.76317,
   63.90757,
   61.07911,
   57.95785,
   54.95168,
   52.47702,
   48.4227,
   43.97067,
   39.9699,
   34.98558,
   29.80961,
   24.92865,
   20.34879};
   Double_t reflected_fex1007[17] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t reflected_fey1007[17] = {
   1.80084,
   0.5162562,
   0.2619161,
   0.251097,
   0.201872,
   0.2656595,
   0.1877111,
   0.1522585,
   0.1908437,
   0.2313102,
   0.2559287,
   0.2738016,
   0.2174516,
   0.1856272,
   0.1400528,
   0.1538969,
   0.1563386};
   gre = new TGraphErrors(17,reflected_fx1007,reflected_fy1007,reflected_fex1007,reflected_fey1007);
   gre->SetName("reflected");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_reflected1007 = new TH1F("Graph_reflected1007","Graph",100,-1.48,0.44);
   Graph_reflected1007->SetMinimum(15.68796);
   Graph_reflected1007->SetMaximum(69.74185);
   Graph_reflected1007->SetDirectory(0);
   Graph_reflected1007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_reflected1007->SetLineColor(ci);
   Graph_reflected1007->GetXaxis()->SetLabelFont(42);
   Graph_reflected1007->GetXaxis()->SetLabelSize(0.035);
   Graph_reflected1007->GetXaxis()->SetTitleSize(0.035);
   Graph_reflected1007->GetXaxis()->SetTitleFont(42);
   Graph_reflected1007->GetYaxis()->SetLabelFont(42);
   Graph_reflected1007->GetYaxis()->SetLabelSize(0.035);
   Graph_reflected1007->GetYaxis()->SetTitleSize(0.035);
   Graph_reflected1007->GetYaxis()->SetTitleOffset(0);
   Graph_reflected1007->GetYaxis()->SetTitleFont(42);
   Graph_reflected1007->GetZaxis()->SetLabelFont(42);
   Graph_reflected1007->GetZaxis()->SetLabelSize(0.035);
   Graph_reflected1007->GetZaxis()->SetTitleSize(0.035);
   Graph_reflected1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_reflected1007);
   
   gre->Draw(" p");
   TLatex *   tex = new TLatex(0.25,0.2,"Open symbols are reflected");
tex->SetNDC();
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.17,0.89,"#pi^{#font[122]{-} } Rapidity Density");
tex->SetNDC();
   tex->SetTextSize(0.06666667);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.13,0.72,0.93,0.87,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/dNdy","STAR FXT #sqrt{s_{NN} } = 4.5 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/E895","E895 #sqrt{s_{NN} } = 4.3 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/E802","E802 #sqrt{s_{NN} } = 4.9 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/E877","E877 #sqrt{s_{NN} } = 4.9 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
