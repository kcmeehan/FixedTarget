void figure_21()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 15:57:51 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: Pad_out
   TPad *Pad_out = new TPad("Pad_out", "c",0,0,0.3809524,1);
   Pad_out->Draw();
   Pad_out->cd();
   Pad_out->Range(0.8898306,1.9,5.5,7.9);
   Pad_out->SetFillColor(0);
   Pad_out->SetFillStyle(4000);
   Pad_out->SetBorderMode(0);
   Pad_out->SetBorderSize(2);
   Pad_out->SetLeftMargin(0.2625);
   Pad_out->SetRightMargin(0);
   Pad_out->SetTopMargin(0.05);
   Pad_out->SetBottomMargin(0.15);
   Pad_out->SetFrameFillStyle(0);
   Pad_out->SetFrameBorderMode(0);
   Pad_out->SetFrameFillStyle(0);
   Pad_out->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {2.1, 2.134, 2.168, 2.202, 2.236, 2.27, 2.304, 2.338, 2.372, 2.406, 2.44, 2.474, 2.508, 2.542, 2.576, 2.61, 2.644, 2.678, 2.712, 2.746, 2.78, 2.814, 2.848, 2.882, 2.916, 2.95, 2.984, 3.018, 3.052, 3.086, 3.12, 3.154, 3.188, 3.222, 3.256, 3.29, 3.324, 3.358, 3.392, 3.426, 3.46, 3.494, 3.528, 3.562, 3.596, 3.63, 3.664, 3.698, 3.732, 3.766, 3.8, 3.834, 3.868, 3.902, 3.936, 3.97, 4.004, 4.038, 4.072, 4.106, 4.14, 4.174, 4.208, 4.242, 4.276, 4.31, 4.344, 4.378, 4.412, 4.446, 4.48, 4.514, 4.548, 4.582, 4.616, 4.65, 4.684, 4.718, 4.752, 4.786, 4.82, 4.854, 4.888, 4.922, 4.956, 4.99, 5.024, 5.058, 5.092, 5.126, 5.16, 5.194, 5.228, 5.262, 5.296, 5.33, 5.364, 5.398, 5.432, 5.466, 5.5}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(2.8);
   frame_5PN2__1->SetMaximum(7.6);
   frame_5PN2__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetNdivisions(206);
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelOffset(-0.015);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.07777778);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("R (fm)");
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelOffset(0.01);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.07777778);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.125);
   frame_5PN2__1->GetYaxis()->SetTitleOffset(0.85);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t Graph1_fx1001[4] = {
   2.7,
   3.32,
   3.86,
   4.3};
   Double_t Graph1_fy1001[4] = {
   6.22,
   5.79,
   5.76,
   5.48};
   Double_t Graph1_fex1001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph1_fey1001[4] = {
   0.26,
   0.16,
   0.23,
   0.31};
   TGraphErrors *gre = new TGraphErrors(4,Graph1_fx1001,Graph1_fy1001,Graph1_fex1001,Graph1_fey1001);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph11001 = new TH1F("Graph_Graph11001","Graph",100,2.54,4.46);
   Graph_Graph11001->SetMinimum(5.039);
   Graph_Graph11001->SetMaximum(6.611);
   Graph_Graph11001->SetDirectory(0);
   Graph_Graph11001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11001->SetLineColor(ci);
   Graph_Graph11001->GetXaxis()->SetLabelFont(42);
   Graph_Graph11001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph11001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph11001->GetXaxis()->SetTitleFont(42);
   Graph_Graph11001->GetYaxis()->SetLabelFont(42);
   Graph_Graph11001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph11001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph11001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph11001->GetYaxis()->SetTitleFont(42);
   Graph_Graph11001->GetZaxis()->SetLabelFont(42);
   Graph_Graph11001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph11001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph11001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11001);
   
   gre->Draw("pe1");
   
   Double_t Graph2_fx1002[1] = {
   5.03};
   Double_t Graph2_fy1002[1] = {
   5.41};
   Double_t Graph2_fex1002[1] = {
   0};
   Double_t Graph2_fey1002[1] = {
   0.33};
   gre = new TGraphErrors(1,Graph2_fx1002,Graph2_fy1002,Graph2_fex1002,Graph2_fey1002);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph21002 = new TH1F("Graph_Graph21002","Graph",100,4.93,6.13);
   Graph_Graph21002->SetMinimum(5.014);
   Graph_Graph21002->SetMaximum(5.806);
   Graph_Graph21002->SetDirectory(0);
   Graph_Graph21002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21002->SetLineColor(ci);
   Graph_Graph21002->GetXaxis()->SetLabelFont(42);
   Graph_Graph21002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph21002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph21002->GetXaxis()->SetTitleFont(42);
   Graph_Graph21002->GetYaxis()->SetLabelFont(42);
   Graph_Graph21002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph21002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph21002->GetYaxis()->SetTitleOffset(0);
   Graph_Graph21002->GetYaxis()->SetTitleFont(42);
   Graph_Graph21002->GetZaxis()->SetLabelFont(42);
   Graph_Graph21002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph21002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph21002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21002);
   
   gre->Draw("pe1");
   
   Double_t Ro_fx1003[6] = {
   4.5,
   0,
   0,
   0,
   0,
   0};
   Double_t Ro_fy1003[6] = {
   4.966162,
   0,
   0,
   0,
   0,
   0};
   Double_t Ro_fex1003[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Ro_fey1003[6] = {
   0.4717853,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(6,Ro_fx1003,Ro_fy1003,Ro_fex1003,Ro_fey1003);
   gre->SetName("Ro");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Ro1003 = new TH1F("Graph_Ro1003","Graph",100,0,4.95);
   Graph_Ro1003->SetMinimum(0);
   Graph_Ro1003->SetMaximum(5.981742);
   Graph_Ro1003->SetDirectory(0);
   Graph_Ro1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Ro1003->SetLineColor(ci);
   Graph_Ro1003->GetXaxis()->SetLabelFont(42);
   Graph_Ro1003->GetXaxis()->SetLabelSize(0.035);
   Graph_Ro1003->GetXaxis()->SetTitleSize(0.035);
   Graph_Ro1003->GetXaxis()->SetTitleFont(42);
   Graph_Ro1003->GetYaxis()->SetLabelFont(42);
   Graph_Ro1003->GetYaxis()->SetLabelSize(0.035);
   Graph_Ro1003->GetYaxis()->SetTitleSize(0.035);
   Graph_Ro1003->GetYaxis()->SetTitleOffset(0);
   Graph_Ro1003->GetYaxis()->SetTitleFont(42);
   Graph_Ro1003->GetZaxis()->SetLabelFont(42);
   Graph_Ro1003->GetZaxis()->SetLabelSize(0.035);
   Graph_Ro1003->GetZaxis()->SetTitleSize(0.035);
   Graph_Ro1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Ro1003);
   
   gre->Draw("pe1");
   TLatex *   tex = new TLatex(0.5,0.85,"Out");
tex->SetNDC();
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.2625,0.18,1.2625,0.48,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05555556);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/Graph1","#splitline{E895 }{#sqrt{s_{NN} } = 4.3 GeV}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00aa00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Ro","#splitline{STAR FXT }{#sqrt{s_{NN} } = 4.5 GeV}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph2","#splitline{E866 }{#sqrt{s_{NN} } = 4.9 GeV}","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   leg->Draw();
   Pad_out->Modified();
   c->cd();
  
// ------------>Primitives in pad: Pad_side
   TPad *Pad_side = new TPad("Pad_side", "c",0.3809524,0,0.6666667,1);
   Pad_side->Draw();
   Pad_side->cd();
   Pad_side->Range(2.1,1.9,5.5,7.9);
   Pad_side->SetFillColor(0);
   Pad_side->SetFillStyle(4000);
   Pad_side->SetBorderMode(0);
   Pad_side->SetBorderSize(2);
   Pad_side->SetLeftMargin(0);
   Pad_side->SetRightMargin(0);
   Pad_side->SetTopMargin(0.05);
   Pad_side->SetBottomMargin(0.15);
   Pad_side->SetFrameFillStyle(0);
   Pad_side->SetFrameBorderMode(0);
   Pad_side->SetFrameFillStyle(0);
   Pad_side->SetFrameBorderMode(0);
   Double_t xAxis2[101] = {2.1, 2.134, 2.168, 2.202, 2.236, 2.27, 2.304, 2.338, 2.372, 2.406, 2.44, 2.474, 2.508, 2.542, 2.576, 2.61, 2.644, 2.678, 2.712, 2.746, 2.78, 2.814, 2.848, 2.882, 2.916, 2.95, 2.984, 3.018, 3.052, 3.086, 3.12, 3.154, 3.188, 3.222, 3.256, 3.29, 3.324, 3.358, 3.392, 3.426, 3.46, 3.494, 3.528, 3.562, 3.596, 3.63, 3.664, 3.698, 3.732, 3.766, 3.8, 3.834, 3.868, 3.902, 3.936, 3.97, 4.004, 4.038, 4.072, 4.106, 4.14, 4.174, 4.208, 4.242, 4.276, 4.31, 4.344, 4.378, 4.412, 4.446, 4.48, 4.514, 4.548, 4.582, 4.616, 4.65, 4.684, 4.718, 4.752, 4.786, 4.82, 4.854, 4.888, 4.922, 4.956, 4.99, 5.024, 5.058, 5.092, 5.126, 5.16, 5.194, 5.228, 5.262, 5.296, 5.33, 5.364, 5.398, 5.432, 5.466, 5.5}; 
   
   TH1C *frame_qmWq__2 = new TH1C("frame_qmWq__2","",100, xAxis2);
   frame_qmWq__2->SetMinimum(2.8);
   frame_qmWq__2->SetMaximum(7.6);
   frame_qmWq__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_qmWq__2->SetLineColor(ci);
   frame_qmWq__2->SetMarkerStyle(8);
   frame_qmWq__2->SetMarkerSize(0);
   frame_qmWq__2->GetXaxis()->SetNdivisions(206);
   frame_qmWq__2->GetXaxis()->SetLabelFont(42);
   frame_qmWq__2->GetXaxis()->SetLabelOffset(-0.03);
   frame_qmWq__2->GetXaxis()->SetLabelSize(0.09722222);
   frame_qmWq__2->GetXaxis()->SetTitleSize(0.035);
   frame_qmWq__2->GetXaxis()->SetTitleFont(42);
   frame_qmWq__2->GetYaxis()->SetLabelFont(42);
   frame_qmWq__2->GetYaxis()->SetLabelSize(0.035);
   frame_qmWq__2->GetYaxis()->SetTitleSize(0.035);
   frame_qmWq__2->GetYaxis()->SetTitleOffset(0);
   frame_qmWq__2->GetYaxis()->SetTitleFont(42);
   frame_qmWq__2->GetZaxis()->SetLabelFont(42);
   frame_qmWq__2->GetZaxis()->SetLabelSize(0.035);
   frame_qmWq__2->GetZaxis()->SetTitleSize(0.035);
   frame_qmWq__2->GetZaxis()->SetTitleFont(42);
   frame_qmWq__2->Draw("p");
   
   Double_t Graph4_fx1004[4] = {
   2.7,
   3.32,
   3.86,
   4.3};
   Double_t Graph4_fy1004[4] = {
   6.28,
   5.37,
   5.05,
   4.83};
   Double_t Graph4_fex1004[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph4_fey1004[4] = {
   0.2,
   0.11,
   0.12,
   0.21};
   gre = new TGraphErrors(4,Graph4_fx1004,Graph4_fy1004,Graph4_fex1004,Graph4_fey1004);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph41004 = new TH1F("Graph_Graph41004","Graph",100,2.54,4.46);
   Graph_Graph41004->SetMinimum(4.434);
   Graph_Graph41004->SetMaximum(6.666);
   Graph_Graph41004->SetDirectory(0);
   Graph_Graph41004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41004->SetLineColor(ci);
   Graph_Graph41004->GetXaxis()->SetLabelFont(42);
   Graph_Graph41004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph41004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph41004->GetXaxis()->SetTitleFont(42);
   Graph_Graph41004->GetYaxis()->SetLabelFont(42);
   Graph_Graph41004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph41004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph41004->GetYaxis()->SetTitleOffset(0);
   Graph_Graph41004->GetYaxis()->SetTitleFont(42);
   Graph_Graph41004->GetZaxis()->SetLabelFont(42);
   Graph_Graph41004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph41004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph41004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41004);
   
   gre->Draw("pe1");
   
   Double_t Graph5_fx1005[1] = {
   5.03};
   Double_t Graph5_fy1005[1] = {
   4.55};
   Double_t Graph5_fex1005[1] = {
   0};
   Double_t Graph5_fey1005[1] = {
   0.42};
   gre = new TGraphErrors(1,Graph5_fx1005,Graph5_fy1005,Graph5_fex1005,Graph5_fey1005);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph51005 = new TH1F("Graph_Graph51005","Graph",100,4.93,6.13);
   Graph_Graph51005->SetMinimum(4.046);
   Graph_Graph51005->SetMaximum(5.054);
   Graph_Graph51005->SetDirectory(0);
   Graph_Graph51005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51005->SetLineColor(ci);
   Graph_Graph51005->GetXaxis()->SetLabelFont(42);
   Graph_Graph51005->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph51005->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph51005->GetXaxis()->SetTitleFont(42);
   Graph_Graph51005->GetYaxis()->SetLabelFont(42);
   Graph_Graph51005->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph51005->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph51005->GetYaxis()->SetTitleOffset(0);
   Graph_Graph51005->GetYaxis()->SetTitleFont(42);
   Graph_Graph51005->GetZaxis()->SetLabelFont(42);
   Graph_Graph51005->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph51005->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph51005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51005);
   
   gre->Draw("pe1");
   
   Double_t Rs_fx1006[6] = {
   4.5,
   0,
   0,
   0,
   0,
   0};
   Double_t Rs_fy1006[6] = {
   4.330889,
   0,
   0,
   0,
   0,
   0};
   Double_t Rs_fex1006[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Rs_fey1006[6] = {
   0.2815078,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(6,Rs_fx1006,Rs_fy1006,Rs_fex1006,Rs_fey1006);
   gre->SetName("Rs");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rs1006 = new TH1F("Graph_Rs1006","Graph",100,0,4.95);
   Graph_Rs1006->SetMinimum(0);
   Graph_Rs1006->SetMaximum(5.073636);
   Graph_Rs1006->SetDirectory(0);
   Graph_Rs1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rs1006->SetLineColor(ci);
   Graph_Rs1006->GetXaxis()->SetLabelFont(42);
   Graph_Rs1006->GetXaxis()->SetLabelSize(0.035);
   Graph_Rs1006->GetXaxis()->SetTitleSize(0.035);
   Graph_Rs1006->GetXaxis()->SetTitleFont(42);
   Graph_Rs1006->GetYaxis()->SetLabelFont(42);
   Graph_Rs1006->GetYaxis()->SetLabelSize(0.035);
   Graph_Rs1006->GetYaxis()->SetTitleSize(0.035);
   Graph_Rs1006->GetYaxis()->SetTitleOffset(0);
   Graph_Rs1006->GetYaxis()->SetTitleFont(42);
   Graph_Rs1006->GetZaxis()->SetLabelFont(42);
   Graph_Rs1006->GetZaxis()->SetLabelSize(0.035);
   Graph_Rs1006->GetZaxis()->SetTitleSize(0.035);
   Graph_Rs1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rs1006);
   
   gre->Draw("pe1");
      tex = new TLatex(0.35,0.85,"Side");
tex->SetNDC();
   tex->SetTextSize(0.1888889);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_side->Modified();
   c->cd();
  
// ------------>Primitives in pad: Pad_long
   TPad *Pad_long = new TPad("Pad_long", "c",0.6666667,0,1,1);
   Pad_long->Draw();
   Pad_long->cd();
   Pad_long->Range(2.1,1.9,6.1,7.9);
   Pad_long->SetFillColor(0);
   Pad_long->SetFillStyle(4000);
   Pad_long->SetBorderMode(0);
   Pad_long->SetBorderSize(2);
   Pad_long->SetLeftMargin(0);
   Pad_long->SetRightMargin(0.15);
   Pad_long->SetTopMargin(0.05);
   Pad_long->SetBottomMargin(0.15);
   Pad_long->SetFrameFillStyle(0);
   Pad_long->SetFrameBorderMode(0);
   Pad_long->SetFrameFillStyle(0);
   Pad_long->SetFrameBorderMode(0);
   Double_t xAxis3[101] = {2.1, 2.134, 2.168, 2.202, 2.236, 2.27, 2.304, 2.338, 2.372, 2.406, 2.44, 2.474, 2.508, 2.542, 2.576, 2.61, 2.644, 2.678, 2.712, 2.746, 2.78, 2.814, 2.848, 2.882, 2.916, 2.95, 2.984, 3.018, 3.052, 3.086, 3.12, 3.154, 3.188, 3.222, 3.256, 3.29, 3.324, 3.358, 3.392, 3.426, 3.46, 3.494, 3.528, 3.562, 3.596, 3.63, 3.664, 3.698, 3.732, 3.766, 3.8, 3.834, 3.868, 3.902, 3.936, 3.97, 4.004, 4.038, 4.072, 4.106, 4.14, 4.174, 4.208, 4.242, 4.276, 4.31, 4.344, 4.378, 4.412, 4.446, 4.48, 4.514, 4.548, 4.582, 4.616, 4.65, 4.684, 4.718, 4.752, 4.786, 4.82, 4.854, 4.888, 4.922, 4.956, 4.99, 5.024, 5.058, 5.092, 5.126, 5.16, 5.194, 5.228, 5.262, 5.296, 5.33, 5.364, 5.398, 5.432, 5.466, 5.5}; 
   
   TH1C *frame_BlQ9__3 = new TH1C("frame_BlQ9__3","",100, xAxis3);
   frame_BlQ9__3->SetMinimum(2.8);
   frame_BlQ9__3->SetMaximum(7.6);
   frame_BlQ9__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_BlQ9__3->SetLineColor(ci);
   frame_BlQ9__3->SetMarkerStyle(8);
   frame_BlQ9__3->SetMarkerSize(0);
   frame_BlQ9__3->GetXaxis()->SetTitle("#sqrt{s_{NN} } (GeV/c)");
   frame_BlQ9__3->GetXaxis()->SetNdivisions(206);
   frame_BlQ9__3->GetXaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetXaxis()->SetLabelOffset(-0.015);
   frame_BlQ9__3->GetXaxis()->SetLabelSize(0.07777778);
   frame_BlQ9__3->GetXaxis()->SetTitleSize(0.1166667);
   frame_BlQ9__3->GetXaxis()->SetTitleOffset(0.5);
   frame_BlQ9__3->GetXaxis()->SetTitleFont(42);
   frame_BlQ9__3->GetYaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetYaxis()->SetLabelSize(0.07777778);
   frame_BlQ9__3->GetYaxis()->SetTitleSize(0.035);
   frame_BlQ9__3->GetYaxis()->SetTitleOffset(0);
   frame_BlQ9__3->GetYaxis()->SetTitleFont(42);
   frame_BlQ9__3->GetZaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetZaxis()->SetLabelSize(0.035);
   frame_BlQ9__3->GetZaxis()->SetTitleSize(0.035);
   frame_BlQ9__3->GetZaxis()->SetTitleFont(42);
   frame_BlQ9__3->Draw("p");
   
   Double_t Graph7_fx1007[4] = {
   2.7,
   3.32,
   3.86,
   4.3};
   Double_t Graph7_fy1007[4] = {
   5.15,
   5.15,
   4.72,
   4.64};
   Double_t Graph7_fex1007[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph7_fey1007[4] = {
   0.19,
   0.14,
   0.18,
   0.24};
   gre = new TGraphErrors(4,Graph7_fx1007,Graph7_fy1007,Graph7_fex1007,Graph7_fey1007);
   gre->SetName("Graph7");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph71007 = new TH1F("Graph_Graph71007","Graph",100,2.54,4.46);
   Graph_Graph71007->SetMinimum(4.306);
   Graph_Graph71007->SetMaximum(5.434);
   Graph_Graph71007->SetDirectory(0);
   Graph_Graph71007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph71007->SetLineColor(ci);
   Graph_Graph71007->GetXaxis()->SetLabelFont(42);
   Graph_Graph71007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph71007->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph71007->GetXaxis()->SetTitleFont(42);
   Graph_Graph71007->GetYaxis()->SetLabelFont(42);
   Graph_Graph71007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph71007->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph71007->GetYaxis()->SetTitleOffset(0);
   Graph_Graph71007->GetYaxis()->SetTitleFont(42);
   Graph_Graph71007->GetZaxis()->SetLabelFont(42);
   Graph_Graph71007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph71007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph71007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph71007);
   
   gre->Draw("pe1");
   
   Double_t Graph8_fx1008[1] = {
   5.03};
   Double_t Graph8_fy1008[1] = {
   3.61};
   Double_t Graph8_fex1008[1] = {
   0};
   Double_t Graph8_fey1008[1] = {
   0.3};
   gre = new TGraphErrors(1,Graph8_fx1008,Graph8_fy1008,Graph8_fex1008,Graph8_fey1008);
   gre->SetName("Graph8");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph81008 = new TH1F("Graph_Graph81008","Graph",100,4.93,6.13);
   Graph_Graph81008->SetMinimum(3.25);
   Graph_Graph81008->SetMaximum(3.97);
   Graph_Graph81008->SetDirectory(0);
   Graph_Graph81008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph81008->SetLineColor(ci);
   Graph_Graph81008->GetXaxis()->SetLabelFont(42);
   Graph_Graph81008->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph81008->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph81008->GetXaxis()->SetTitleFont(42);
   Graph_Graph81008->GetYaxis()->SetLabelFont(42);
   Graph_Graph81008->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph81008->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph81008->GetYaxis()->SetTitleOffset(0);
   Graph_Graph81008->GetYaxis()->SetTitleFont(42);
   Graph_Graph81008->GetZaxis()->SetLabelFont(42);
   Graph_Graph81008->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph81008->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph81008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph81008);
   
   gre->Draw("pe1");
   
   Double_t Rl_fx1009[6] = {
   4.5,
   0,
   0,
   0,
   0,
   0};
   Double_t Rl_fy1009[6] = {
   3.984382,
   0,
   0,
   0,
   0,
   0};
   Double_t Rl_fex1009[6] = {
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Rl_fey1009[6] = {
   0.2589849,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(6,Rl_fx1009,Rl_fy1009,Rl_fex1009,Rl_fey1009);
   gre->SetName("Rl");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rl1009 = new TH1F("Graph_Rl1009","Graph",100,0,4.95);
   Graph_Rl1009->SetMinimum(0);
   Graph_Rl1009->SetMaximum(4.667704);
   Graph_Rl1009->SetDirectory(0);
   Graph_Rl1009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rl1009->SetLineColor(ci);
   Graph_Rl1009->GetXaxis()->SetLabelFont(42);
   Graph_Rl1009->GetXaxis()->SetLabelSize(0.035);
   Graph_Rl1009->GetXaxis()->SetTitleSize(0.035);
   Graph_Rl1009->GetXaxis()->SetTitleFont(42);
   Graph_Rl1009->GetYaxis()->SetLabelFont(42);
   Graph_Rl1009->GetYaxis()->SetLabelSize(0.035);
   Graph_Rl1009->GetYaxis()->SetTitleSize(0.035);
   Graph_Rl1009->GetYaxis()->SetTitleOffset(0);
   Graph_Rl1009->GetYaxis()->SetTitleFont(42);
   Graph_Rl1009->GetZaxis()->SetLabelFont(42);
   Graph_Rl1009->GetZaxis()->SetLabelSize(0.035);
   Graph_Rl1009->GetZaxis()->SetTitleSize(0.035);
   Graph_Rl1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rl1009);
   
   gre->Draw("pe1");
      tex = new TLatex(0.25,0.85,"Long");
tex->SetNDC();
   tex->SetTextSize(0.15);
   tex->SetLineWidth(2);
   tex->Draw();
   Pad_long->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
