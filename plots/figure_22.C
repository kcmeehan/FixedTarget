void figure_22()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 15:58:25 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,900,1200);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: Pad_out
   TPad *Pad_out = new TPad("Pad_out", "c",0,0.6666667,1,1);
   Pad_out->Draw();
   Pad_out->cd();
   Pad_out->Range(0.05352941,3.5,0.6182353,7.382353);
   Pad_out->SetFillColor(0);
   Pad_out->SetFillStyle(4000);
   Pad_out->SetBorderMode(0);
   Pad_out->SetBorderSize(2);
   Pad_out->SetRightMargin(0.05);
   Pad_out->SetTopMargin(0.15);
   Pad_out->SetBottomMargin(0);
   Pad_out->SetFrameFillStyle(0);
   Pad_out->SetFrameBorderMode(0);
   Pad_out->SetFrameFillStyle(0);
   Pad_out->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {0.11, 0.1148, 0.1196, 0.1244, 0.1292, 0.134, 0.1388, 0.1436, 0.1484, 0.1532, 0.158, 0.1628, 0.1676, 0.1724, 0.1772, 0.182, 0.1868, 0.1916, 0.1964, 0.2012, 0.206, 0.2108, 0.2156, 0.2204, 0.2252, 0.23, 0.2348, 0.2396, 0.2444, 0.2492, 0.254, 0.2588, 0.2636, 0.2684, 0.2732, 0.278, 0.2828, 0.2876, 0.2924, 0.2972, 0.302, 0.3068, 0.3116, 0.3164, 0.3212, 0.326, 0.3308, 0.3356, 0.3404, 0.3452, 0.35, 0.3548, 0.3596, 0.3644, 0.3692, 0.374, 0.3788, 0.3836, 0.3884, 0.3932, 0.398, 0.4028, 0.4076, 0.4124, 0.4172, 0.422, 0.4268, 0.4316, 0.4364, 0.4412, 0.446, 0.4508, 0.4556, 0.4604, 0.4652, 0.47, 0.4748, 0.4796, 0.4844, 0.4892, 0.494, 0.4988, 0.5036, 0.5084, 0.5132, 0.518, 0.5228, 0.5276, 0.5324, 0.5372, 0.542, 0.5468, 0.5516, 0.5564, 0.5612, 0.566, 0.5708, 0.5756, 0.5804, 0.5852, 0.59}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(3.5);
   frame_5PN2__1->SetMaximum(6.8);
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
   frame_5PN2__1->GetYaxis()->SetTitle("R_{out} (fm)");
   frame_5PN2__1->GetYaxis()->SetNdivisions(206);
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.08888889);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.1055556);
   frame_5PN2__1->GetYaxis()->SetTitleOffset(0.4);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t Graph_1_fx1001[3] = {
   0.294,
   0.4,
   0.539};
   Double_t Graph_1_fy1001[3] = {
   5.57,
   4.39,
   4.21};
   Double_t Graph_1_fex1001[3] = {
   0,
   0,
   0};
   Double_t Graph_1_fey1001[3] = {
   0.41,
   0.44,
   0.54};
   TGraphErrors *gre = new TGraphErrors(3,Graph_1_fx1001,Graph_1_fy1001,Graph_1_fex1001,Graph_1_fey1001);
   gre->SetName("Graph_1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_11001 = new TH1F("Graph_Graph_11001","Graph",100,0.2695,0.5635);
   Graph_Graph_11001->SetMinimum(3.439);
   Graph_Graph_11001->SetMaximum(6.211);
   Graph_Graph_11001->SetDirectory(0);
   Graph_Graph_11001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_11001->SetLineColor(ci);
   Graph_Graph_11001->GetXaxis()->SetLabelFont(42);
   Graph_Graph_11001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_11001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_11001->GetXaxis()->SetTitleFont(42);
   Graph_Graph_11001->GetYaxis()->SetLabelFont(42);
   Graph_Graph_11001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_11001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_11001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_11001->GetYaxis()->SetTitleFont(42);
   Graph_Graph_11001->GetZaxis()->SetLabelFont(42);
   Graph_Graph_11001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_11001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_11001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_11001);
   
   gre->Draw("pe1");
   
   Double_t Graph_2_fx1002[3] = {
   0.155,
   0.202,
   0.319};
   Double_t Graph_2_fy1002[3] = {
   5.236,
   6.206,
   4.609};
   Double_t Graph_2_fex1002[3] = {
   0,
   0,
   0};
   Double_t Graph_2_fey1002[3] = {
   0.35,
   0.378,
   0.424};
   gre = new TGraphErrors(3,Graph_2_fx1002,Graph_2_fy1002,Graph_2_fex1002,Graph_2_fey1002);
   gre->SetName("Graph_2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_21002 = new TH1F("Graph_Graph_21002","Graph",100,0.1386,0.3354);
   Graph_Graph_21002->SetMinimum(3.9451);
   Graph_Graph_21002->SetMaximum(6.8239);
   Graph_Graph_21002->SetDirectory(0);
   Graph_Graph_21002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_21002->SetLineColor(ci);
   Graph_Graph_21002->GetXaxis()->SetLabelFont(42);
   Graph_Graph_21002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_21002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_21002->GetXaxis()->SetTitleFont(42);
   Graph_Graph_21002->GetYaxis()->SetLabelFont(42);
   Graph_Graph_21002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_21002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_21002->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_21002->GetYaxis()->SetTitleFont(42);
   Graph_Graph_21002->GetZaxis()->SetLabelFont(42);
   Graph_Graph_21002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_21002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_21002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_21002);
   
   gre->Draw("pe1");
   
   Double_t Ro_fx1003[4] = {
   0.225,
   0.264,
   0.307,
   0.388};
   Double_t Ro_fy1003[4] = {
   4.880405,
   4.831791,
   4.451635,
   4.148311};
   Double_t Ro_fex1003[4] = {
   0,
   0,
   0,
   0};
   Double_t Ro_fey1003[4] = {
   0.09251815,
   0.06535344,
   0.07330122,
   0.06418585};
   gre = new TGraphErrors(4,Ro_fx1003,Ro_fy1003,Ro_fex1003,Ro_fey1003);
   gre->SetName("Ro");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Ro1003 = new TH1F("Graph_Ro1003","Graph",100,0.2087,0.4043);
   Graph_Ro1003->SetMinimum(3.995245);
   Graph_Ro1003->SetMaximum(5.061803);
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
   
   TLegend *leg = new TLegend(0.44,0.54,0.94,0.84,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/Ro","STAR FXT #sqrt{s_{NN} } = 4.5 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph_1","E895 #sqrt{s_{NN} } = 4.3 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph_2","E866 #sqrt{s_{NN} } = 4.9 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00aa00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   leg->Draw();
   Pad_out->Modified();
   c->cd();
  
// ------------>Primitives in pad: Pad_side
   TPad *Pad_side = new TPad("Pad_side", "c",0,0.3809524,1,0.6666667);
   Pad_side->Draw();
   Pad_side->cd();
   Pad_side->Range(0.05352941,2.4,0.6182353,5.9);
   Pad_side->SetFillColor(0);
   Pad_side->SetFillStyle(4000);
   Pad_side->SetBorderMode(0);
   Pad_side->SetBorderSize(2);
   Pad_side->SetRightMargin(0.05);
   Pad_side->SetTopMargin(0);
   Pad_side->SetBottomMargin(0);
   Pad_side->SetFrameFillStyle(0);
   Pad_side->SetFrameBorderMode(0);
   Pad_side->SetFrameFillStyle(0);
   Pad_side->SetFrameBorderMode(0);
   Double_t xAxis2[101] = {0.11, 0.1148, 0.1196, 0.1244, 0.1292, 0.134, 0.1388, 0.1436, 0.1484, 0.1532, 0.158, 0.1628, 0.1676, 0.1724, 0.1772, 0.182, 0.1868, 0.1916, 0.1964, 0.2012, 0.206, 0.2108, 0.2156, 0.2204, 0.2252, 0.23, 0.2348, 0.2396, 0.2444, 0.2492, 0.254, 0.2588, 0.2636, 0.2684, 0.2732, 0.278, 0.2828, 0.2876, 0.2924, 0.2972, 0.302, 0.3068, 0.3116, 0.3164, 0.3212, 0.326, 0.3308, 0.3356, 0.3404, 0.3452, 0.35, 0.3548, 0.3596, 0.3644, 0.3692, 0.374, 0.3788, 0.3836, 0.3884, 0.3932, 0.398, 0.4028, 0.4076, 0.4124, 0.4172, 0.422, 0.4268, 0.4316, 0.4364, 0.4412, 0.446, 0.4508, 0.4556, 0.4604, 0.4652, 0.47, 0.4748, 0.4796, 0.4844, 0.4892, 0.494, 0.4988, 0.5036, 0.5084, 0.5132, 0.518, 0.5228, 0.5276, 0.5324, 0.5372, 0.542, 0.5468, 0.5516, 0.5564, 0.5612, 0.566, 0.5708, 0.5756, 0.5804, 0.5852, 0.59}; 
   
   TH1C *frame_qmWq__2 = new TH1C("frame_qmWq__2","",100, xAxis2);
   frame_qmWq__2->SetMinimum(2.4);
   frame_qmWq__2->SetMaximum(5.9);
   frame_qmWq__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_qmWq__2->SetLineColor(ci);
   frame_qmWq__2->SetMarkerStyle(8);
   frame_qmWq__2->SetMarkerSize(0);
   frame_qmWq__2->GetXaxis()->SetNdivisions(206);
   frame_qmWq__2->GetXaxis()->SetLabelFont(42);
   frame_qmWq__2->GetXaxis()->SetLabelSize(0.035);
   frame_qmWq__2->GetXaxis()->SetTitleSize(0.035);
   frame_qmWq__2->GetXaxis()->SetTitleFont(42);
   frame_qmWq__2->GetYaxis()->SetTitle("R_{side} (fm)");
   frame_qmWq__2->GetYaxis()->SetNdivisions(206);
   frame_qmWq__2->GetYaxis()->SetLabelFont(42);
   frame_qmWq__2->GetYaxis()->SetLabelSize(0.1);
   frame_qmWq__2->GetYaxis()->SetTitleSize(0.125);
   frame_qmWq__2->GetYaxis()->SetTitleOffset(0.35);
   frame_qmWq__2->GetYaxis()->SetTitleFont(42);
   frame_qmWq__2->GetZaxis()->SetLabelFont(42);
   frame_qmWq__2->GetZaxis()->SetLabelSize(0.035);
   frame_qmWq__2->GetZaxis()->SetTitleSize(0.035);
   frame_qmWq__2->GetZaxis()->SetTitleFont(42);
   frame_qmWq__2->Draw("p");
   
   Double_t Graph_3_fx1004[3] = {
   0.294,
   0.4,
   0.539};
   Double_t Graph_3_fy1004[3] = {
   4.9,
   3.11,
   3.73};
   Double_t Graph_3_fex1004[3] = {
   0,
   0,
   0};
   Double_t Graph_3_fey1004[3] = {
   0.51,
   0.54,
   0.57};
   gre = new TGraphErrors(3,Graph_3_fx1004,Graph_3_fy1004,Graph_3_fex1004,Graph_3_fey1004);
   gre->SetName("Graph_3");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_31004 = new TH1F("Graph_Graph_31004","Graph",100,0.2695,0.5635);
   Graph_Graph_31004->SetMinimum(2.286);
   Graph_Graph_31004->SetMaximum(5.694);
   Graph_Graph_31004->SetDirectory(0);
   Graph_Graph_31004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_31004->SetLineColor(ci);
   Graph_Graph_31004->GetXaxis()->SetLabelFont(42);
   Graph_Graph_31004->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_31004->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_31004->GetXaxis()->SetTitleFont(42);
   Graph_Graph_31004->GetYaxis()->SetLabelFont(42);
   Graph_Graph_31004->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_31004->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_31004->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_31004->GetYaxis()->SetTitleFont(42);
   Graph_Graph_31004->GetZaxis()->SetLabelFont(42);
   Graph_Graph_31004->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_31004->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_31004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_31004);
   
   gre->Draw("pe1");
   
   Double_t Graph_4_fx1005[3] = {
   0.155,
   0.202,
   0.319};
   Double_t Graph_4_fy1005[3] = {
   5.412,
   5.03,
   4.136};
   Double_t Graph_4_fex1005[3] = {
   0,
   0,
   0};
   Double_t Graph_4_fey1005[3] = {
   0.347,
   0.223,
   0.304};
   gre = new TGraphErrors(3,Graph_4_fx1005,Graph_4_fy1005,Graph_4_fex1005,Graph_4_fey1005);
   gre->SetName("Graph_4");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_41005 = new TH1F("Graph_Graph_41005","Graph",100,0.1386,0.3354);
   Graph_Graph_41005->SetMinimum(3.6393);
   Graph_Graph_41005->SetMaximum(5.9517);
   Graph_Graph_41005->SetDirectory(0);
   Graph_Graph_41005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_41005->SetLineColor(ci);
   Graph_Graph_41005->GetXaxis()->SetLabelFont(42);
   Graph_Graph_41005->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_41005->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_41005->GetXaxis()->SetTitleFont(42);
   Graph_Graph_41005->GetYaxis()->SetLabelFont(42);
   Graph_Graph_41005->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_41005->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_41005->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_41005->GetYaxis()->SetTitleFont(42);
   Graph_Graph_41005->GetZaxis()->SetLabelFont(42);
   Graph_Graph_41005->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_41005->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_41005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_41005);
   
   gre->Draw("pe1");
   
   Double_t Rs_fx1006[4] = {
   0.225,
   0.264,
   0.307,
   0.388};
   Double_t Rs_fy1006[4] = {
   4.400845,
   4.257112,
   3.976096,
   3.641773};
   Double_t Rs_fex1006[4] = {
   0,
   0,
   0,
   0};
   Double_t Rs_fey1006[4] = {
   0.0653408,
   0.05804913,
   0.06604535,
   0.05622263};
   gre = new TGraphErrors(4,Rs_fx1006,Rs_fy1006,Rs_fex1006,Rs_fey1006);
   gre->SetName("Rs");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rs1006 = new TH1F("Graph_Rs1006","Graph",100,0.2087,0.4043);
   Graph_Rs1006->SetMinimum(3.497487);
   Graph_Rs1006->SetMaximum(4.554249);
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
   Pad_side->Modified();
   c->cd();
  
// ------------>Primitives in pad: Pad_long
   TPad *Pad_long = new TPad("Pad_long", "c",0,0,1,0.3809524);
   Pad_long->Draw();
   Pad_long->cd();
   Pad_long->Range(0.05352941,0.340678,0.6182353,5.9);
   Pad_long->SetFillColor(0);
   Pad_long->SetFillStyle(4000);
   Pad_long->SetBorderMode(0);
   Pad_long->SetBorderSize(2);
   Pad_long->SetRightMargin(0.05);
   Pad_long->SetTopMargin(0);
   Pad_long->SetBottomMargin(0.2625);
   Pad_long->SetFrameFillStyle(0);
   Pad_long->SetFrameBorderMode(0);
   Pad_long->SetFrameFillStyle(0);
   Pad_long->SetFrameBorderMode(0);
   Double_t xAxis3[101] = {0.11, 0.1148, 0.1196, 0.1244, 0.1292, 0.134, 0.1388, 0.1436, 0.1484, 0.1532, 0.158, 0.1628, 0.1676, 0.1724, 0.1772, 0.182, 0.1868, 0.1916, 0.1964, 0.2012, 0.206, 0.2108, 0.2156, 0.2204, 0.2252, 0.23, 0.2348, 0.2396, 0.2444, 0.2492, 0.254, 0.2588, 0.2636, 0.2684, 0.2732, 0.278, 0.2828, 0.2876, 0.2924, 0.2972, 0.302, 0.3068, 0.3116, 0.3164, 0.3212, 0.326, 0.3308, 0.3356, 0.3404, 0.3452, 0.35, 0.3548, 0.3596, 0.3644, 0.3692, 0.374, 0.3788, 0.3836, 0.3884, 0.3932, 0.398, 0.4028, 0.4076, 0.4124, 0.4172, 0.422, 0.4268, 0.4316, 0.4364, 0.4412, 0.446, 0.4508, 0.4556, 0.4604, 0.4652, 0.47, 0.4748, 0.4796, 0.4844, 0.4892, 0.494, 0.4988, 0.5036, 0.5084, 0.5132, 0.518, 0.5228, 0.5276, 0.5324, 0.5372, 0.542, 0.5468, 0.5516, 0.5564, 0.5612, 0.566, 0.5708, 0.5756, 0.5804, 0.5852, 0.59}; 
   
   TH1C *frame_BlQ9__3 = new TH1C("frame_BlQ9__3","",100, xAxis3);
   frame_BlQ9__3->SetMinimum(1.8);
   frame_BlQ9__3->SetMaximum(5.9);
   frame_BlQ9__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_BlQ9__3->SetLineColor(ci);
   frame_BlQ9__3->SetMarkerStyle(8);
   frame_BlQ9__3->SetMarkerSize(0);
   frame_BlQ9__3->GetXaxis()->SetTitle("m_{T} (GeV)");
   frame_BlQ9__3->GetXaxis()->SetNdivisions(206);
   frame_BlQ9__3->GetXaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetXaxis()->SetLabelOffset(0.015);
   frame_BlQ9__3->GetXaxis()->SetLabelSize(0.07777778);
   frame_BlQ9__3->GetXaxis()->SetTitleSize(0.1);
   frame_BlQ9__3->GetXaxis()->SetTitleFont(42);
   frame_BlQ9__3->GetYaxis()->SetTitle("R_{long} (fm)");
   frame_BlQ9__3->GetYaxis()->SetNdivisions(206);
   frame_BlQ9__3->GetYaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetYaxis()->SetLabelOffset(0.01);
   frame_BlQ9__3->GetYaxis()->SetLabelSize(0.07777778);
   frame_BlQ9__3->GetYaxis()->SetTitleSize(0.08888889);
   frame_BlQ9__3->GetYaxis()->SetTitleOffset(0.5);
   frame_BlQ9__3->GetYaxis()->SetTitleFont(42);
   frame_BlQ9__3->GetZaxis()->SetLabelFont(42);
   frame_BlQ9__3->GetZaxis()->SetLabelSize(0.035);
   frame_BlQ9__3->GetZaxis()->SetTitleSize(0.035);
   frame_BlQ9__3->GetZaxis()->SetTitleFont(42);
   frame_BlQ9__3->Draw("p");
   
   Double_t Graph_5_fx1007[3] = {
   0.294,
   0.4,
   0.539};
   Double_t Graph_5_fy1007[3] = {
   3.62,
   3.05,
   2.36};
   Double_t Graph_5_fex1007[3] = {
   0,
   0,
   0};
   Double_t Graph_5_fey1007[3] = {
   0.38,
   0.42,
   0.34};
   gre = new TGraphErrors(3,Graph_5_fx1007,Graph_5_fy1007,Graph_5_fex1007,Graph_5_fey1007);
   gre->SetName("Graph_5");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_51007 = new TH1F("Graph_Graph_51007","Graph",100,0.2695,0.5635);
   Graph_Graph_51007->SetMinimum(1.822);
   Graph_Graph_51007->SetMaximum(4.198);
   Graph_Graph_51007->SetDirectory(0);
   Graph_Graph_51007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_51007->SetLineColor(ci);
   Graph_Graph_51007->GetXaxis()->SetLabelFont(42);
   Graph_Graph_51007->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_51007->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_51007->GetXaxis()->SetTitleFont(42);
   Graph_Graph_51007->GetYaxis()->SetLabelFont(42);
   Graph_Graph_51007->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_51007->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_51007->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_51007->GetYaxis()->SetTitleFont(42);
   Graph_Graph_51007->GetZaxis()->SetLabelFont(42);
   Graph_Graph_51007->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_51007->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_51007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_51007);
   
   gre->Draw("pe1");
   
   Double_t Graph_6_fx1008[3] = {
   0.155,
   0.202,
   0.319};
   Double_t Graph_6_fy1008[3] = {
   5.17,
   5.299,
   3.247};
   Double_t Graph_6_fex1008[3] = {
   0,
   0,
   0};
   Double_t Graph_6_fey1008[3] = {
   0.344,
   0.213,
   0.26};
   gre = new TGraphErrors(3,Graph_6_fx1008,Graph_6_fy1008,Graph_6_fex1008,Graph_6_fey1008);
   gre->SetName("Graph_6");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_Graph_61008 = new TH1F("Graph_Graph_61008","Graph",100,0.1386,0.3354);
   Graph_Graph_61008->SetMinimum(2.7343);
   Graph_Graph_61008->SetMaximum(5.7667);
   Graph_Graph_61008->SetDirectory(0);
   Graph_Graph_61008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_61008->SetLineColor(ci);
   Graph_Graph_61008->GetXaxis()->SetLabelFont(42);
   Graph_Graph_61008->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_61008->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_61008->GetXaxis()->SetTitleFont(42);
   Graph_Graph_61008->GetYaxis()->SetLabelFont(42);
   Graph_Graph_61008->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_61008->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_61008->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_61008->GetYaxis()->SetTitleFont(42);
   Graph_Graph_61008->GetZaxis()->SetLabelFont(42);
   Graph_Graph_61008->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_61008->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_61008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_61008);
   
   gre->Draw("pe1");
   
   Double_t Rl_fx1009[4] = {
   0.225,
   0.264,
   0.307,
   0.388};
   Double_t Rl_fy1009[4] = {
   4.322747,
   3.851506,
   3.427452,
   3.159415};
   Double_t Rl_fex1009[4] = {
   0,
   0,
   0,
   0};
   Double_t Rl_fey1009[4] = {
   0.07376452,
   0.05835374,
   0.06343272,
   0.05426006};
   gre = new TGraphErrors(4,Rl_fx1009,Rl_fy1009,Rl_fex1009,Rl_fey1009);
   gre->SetName("Rl");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rl1009 = new TH1F("Graph_Rl1009","Graph",100,0.2087,0.4043);
   Graph_Rl1009->SetMinimum(2.976019);
   Graph_Rl1009->SetMaximum(4.525647);
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
   Pad_long->Modified();
   c->cd();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
