void figure_11()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 16:52:17 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-0.003649251,-5.61353,1.788582,3.13647);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogx();
   c->SetLogy();
   c->SetLeftMargin(0.17);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {2, 2.48, 2.96, 3.44, 3.92, 4.4, 4.88, 5.36, 5.84, 6.32, 6.8, 7.28, 7.76, 8.24, 8.72, 9.2, 9.68, 10.16, 10.64, 11.12, 11.6, 12.08, 12.56, 13.04, 13.52, 14, 14.48, 14.96, 15.44, 15.92, 16.4, 16.88, 17.36, 17.84, 18.32, 18.8, 19.28, 19.76, 20.24, 20.72, 21.2, 21.68, 22.16, 22.64, 23.12, 23.6, 24.08, 24.56, 25.04, 25.52, 26, 26.48, 26.96, 27.44, 27.92, 28.4, 28.88, 29.36, 29.84, 30.32, 30.8, 31.28, 31.76, 32.24, 32.72, 33.2, 33.68, 34.16, 34.64, 35.12, 35.6, 36.08, 36.56, 37.04, 37.52, 38, 38.48, 38.96, 39.44, 39.92, 40.4, 40.88, 41.36, 41.84, 42.32, 42.8, 43.28, 43.76, 44.24, 44.72, 45.2, 45.68, 46.16, 46.64, 47.12, 47.6, 48.08, 48.56, 49.04, 49.52, 50}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(5e-05);
   frame_5PN2__1->SetMaximum(500);
   frame_5PN2__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetTitle("#sqrt{s_{NN} } (GeV)");
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.06111111);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.07777778);
   frame_5PN2__1->GetXaxis()->SetTitleOffset(0.75);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("(dN/dy)_{y=0} / #LT N_{part} #GT");
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.06111111);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.07777778);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t gE895_pim_fx1001[4] = {
   2.68,
   3.31,
   3.83,
   4.29};
   Double_t gE895_pim_fy1001[4] = {
   0.0635,
   0.115,
   0.147,
   0.182};
   Double_t gE895_pim_fex1001[4] = {
   0,
   0,
   0,
   0};
   Double_t gE895_pim_fey1001[4] = {
   0.006,
   0.011,
   0.015,
   0.018};
   TGraphErrors *gre = new TGraphErrors(4,gE895_pim_fx1001,gE895_pim_fy1001,gE895_pim_fex1001,gE895_pim_fey1001);
   gre->SetName("gE895_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE895_pim1001 = new TH1F("Graph_gE895_pim1001","Graph",100,2.519,4.451);
   Graph_gE895_pim1001->SetMinimum(0.04325);
   Graph_gE895_pim1001->SetMaximum(0.21425);
   Graph_gE895_pim1001->SetDirectory(0);
   Graph_gE895_pim1001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE895_pim1001->SetLineColor(ci);
   Graph_gE895_pim1001->GetXaxis()->SetLabelFont(42);
   Graph_gE895_pim1001->GetXaxis()->SetLabelSize(0.035);
   Graph_gE895_pim1001->GetXaxis()->SetTitleSize(0.035);
   Graph_gE895_pim1001->GetXaxis()->SetTitleFont(42);
   Graph_gE895_pim1001->GetYaxis()->SetLabelFont(42);
   Graph_gE895_pim1001->GetYaxis()->SetLabelSize(0.035);
   Graph_gE895_pim1001->GetYaxis()->SetTitleSize(0.035);
   Graph_gE895_pim1001->GetYaxis()->SetTitleOffset(0);
   Graph_gE895_pim1001->GetYaxis()->SetTitleFont(42);
   Graph_gE895_pim1001->GetZaxis()->SetLabelFont(42);
   Graph_gE895_pim1001->GetZaxis()->SetLabelSize(0.035);
   Graph_gE895_pim1001->GetZaxis()->SetTitleSize(0.035);
   Graph_gE895_pim1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE895_pim1001);
   
   gre->Draw(" pe");
   
   Double_t gE895_lam_fx1002[4] = {
   2.68,
   3.31,
   3.83,
   4.29};
   Double_t gE895_lam_fy1002[4] = {
   0.0021,
   0.0122,
   0.02,
   0.0274};
   Double_t gE895_lam_fex1002[4] = {
   0,
   0,
   0,
   0};
   Double_t gE895_lam_fey1002[4] = {
   0.0002,
   0.0012,
   0.002,
   0.0027};
   gre = new TGraphErrors(4,gE895_lam_fx1002,gE895_lam_fy1002,gE895_lam_fex1002,gE895_lam_fey1002);
   gre->SetName("gE895_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE895_lam1002 = new TH1F("Graph_gE895_lam1002","Graph",100,2.519,4.451);
   Graph_gE895_lam1002->SetMinimum(0.00171);
   Graph_gE895_lam1002->SetMaximum(0.03292);
   Graph_gE895_lam1002->SetDirectory(0);
   Graph_gE895_lam1002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE895_lam1002->SetLineColor(ci);
   Graph_gE895_lam1002->GetXaxis()->SetLabelFont(42);
   Graph_gE895_lam1002->GetXaxis()->SetLabelSize(0.035);
   Graph_gE895_lam1002->GetXaxis()->SetTitleSize(0.035);
   Graph_gE895_lam1002->GetXaxis()->SetTitleFont(42);
   Graph_gE895_lam1002->GetYaxis()->SetLabelFont(42);
   Graph_gE895_lam1002->GetYaxis()->SetLabelSize(0.035);
   Graph_gE895_lam1002->GetYaxis()->SetTitleSize(0.035);
   Graph_gE895_lam1002->GetYaxis()->SetTitleOffset(0);
   Graph_gE895_lam1002->GetYaxis()->SetTitleFont(42);
   Graph_gE895_lam1002->GetZaxis()->SetLabelFont(42);
   Graph_gE895_lam1002->GetZaxis()->SetLabelSize(0.035);
   Graph_gE895_lam1002->GetZaxis()->SetTitleSize(0.035);
   Graph_gE895_lam1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE895_lam1002);
   
   gre->Draw(" pe");
   
   Double_t gE895_k0s_fx1003[3] = {
   2.68,
   3.31,
   3.83};
   Double_t gE895_k0s_fy1003[3] = {
   0.0001,
   0.00052,
   0.00115};
   Double_t gE895_k0s_fex1003[3] = {
   0,
   0,
   0};
   Double_t gE895_k0s_fey1003[3] = {
   1e-05,
   5e-05,
   0.00011};
   gre = new TGraphErrors(3,gE895_k0s_fx1003,gE895_k0s_fy1003,gE895_k0s_fex1003,gE895_k0s_fey1003);
   gre->SetName("gE895_k0s");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE895_k0s1003 = new TH1F("Graph_gE895_k0s1003","Graph",100,2.565,3.945);
   Graph_gE895_k0s1003->SetMinimum(8.1e-05);
   Graph_gE895_k0s1003->SetMaximum(0.001377);
   Graph_gE895_k0s1003->SetDirectory(0);
   Graph_gE895_k0s1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE895_k0s1003->SetLineColor(ci);
   Graph_gE895_k0s1003->GetXaxis()->SetLabelFont(42);
   Graph_gE895_k0s1003->GetXaxis()->SetLabelSize(0.035);
   Graph_gE895_k0s1003->GetXaxis()->SetTitleSize(0.035);
   Graph_gE895_k0s1003->GetXaxis()->SetTitleFont(42);
   Graph_gE895_k0s1003->GetYaxis()->SetLabelFont(42);
   Graph_gE895_k0s1003->GetYaxis()->SetLabelSize(0.035);
   Graph_gE895_k0s1003->GetYaxis()->SetTitleSize(0.035);
   Graph_gE895_k0s1003->GetYaxis()->SetTitleOffset(0);
   Graph_gE895_k0s1003->GetYaxis()->SetTitleFont(42);
   Graph_gE895_k0s1003->GetZaxis()->SetLabelFont(42);
   Graph_gE895_k0s1003->GetZaxis()->SetLabelSize(0.035);
   Graph_gE895_k0s1003->GetZaxis()->SetTitleSize(0.035);
   Graph_gE895_k0s1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE895_k0s1003);
   
   gre->Draw(" pe");
   
   Double_t gE895_p_fx1004[4] = {
   2.68,
   3.31,
   3.83,
   4.29};
   Double_t gE895_p_fy1004[4] = {
   4.84,
   4.28,
   3.7,
   3.76};
   Double_t gE895_p_fex1004[4] = {
   0,
   0,
   0,
   0};
   Double_t gE895_p_fey1004[4] = {
   0.48,
   0.42,
   0.3,
   0.36};
   gre = new TGraphErrors(4,gE895_p_fx1004,gE895_p_fy1004,gE895_p_fex1004,gE895_p_fey1004);
   gre->SetName("gE895_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE895_p1004 = new TH1F("Graph_gE895_p1004","Graph",100,2.519,4.451);
   Graph_gE895_p1004->SetMinimum(3.208);
   Graph_gE895_p1004->SetMaximum(5.512);
   Graph_gE895_p1004->SetDirectory(0);
   Graph_gE895_p1004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE895_p1004->SetLineColor(ci);
   Graph_gE895_p1004->GetXaxis()->SetLabelFont(42);
   Graph_gE895_p1004->GetXaxis()->SetLabelSize(0.035);
   Graph_gE895_p1004->GetXaxis()->SetTitleSize(0.035);
   Graph_gE895_p1004->GetXaxis()->SetTitleFont(42);
   Graph_gE895_p1004->GetYaxis()->SetLabelFont(42);
   Graph_gE895_p1004->GetYaxis()->SetLabelSize(0.035);
   Graph_gE895_p1004->GetYaxis()->SetTitleSize(0.035);
   Graph_gE895_p1004->GetYaxis()->SetTitleOffset(0);
   Graph_gE895_p1004->GetYaxis()->SetTitleFont(42);
   Graph_gE895_p1004->GetZaxis()->SetLabelFont(42);
   Graph_gE895_p1004->GetZaxis()->SetLabelSize(0.035);
   Graph_gE895_p1004->GetZaxis()->SetTitleSize(0.035);
   Graph_gE895_p1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE895_p1004);
   
   gre->Draw(" pe");
   
   Double_t gE802_pim_fx1005[1] = {
   4.86};
   Double_t gE802_pim_fy1005[1] = {
   0.208};
   Double_t gE802_pim_fex1005[1] = {
   0};
   Double_t gE802_pim_fey1005[1] = {
   0.021};
   gre = new TGraphErrors(1,gE802_pim_fx1005,gE802_pim_fy1005,gE802_pim_fex1005,gE802_pim_fey1005);
   gre->SetName("gE802_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE802_pim1005 = new TH1F("Graph_gE802_pim1005","Graph",100,4.76,5.96);
   Graph_gE802_pim1005->SetMinimum(0.1828);
   Graph_gE802_pim1005->SetMaximum(0.2332);
   Graph_gE802_pim1005->SetDirectory(0);
   Graph_gE802_pim1005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE802_pim1005->SetLineColor(ci);
   Graph_gE802_pim1005->GetXaxis()->SetLabelFont(42);
   Graph_gE802_pim1005->GetXaxis()->SetLabelSize(0.035);
   Graph_gE802_pim1005->GetXaxis()->SetTitleSize(0.035);
   Graph_gE802_pim1005->GetXaxis()->SetTitleFont(42);
   Graph_gE802_pim1005->GetYaxis()->SetLabelFont(42);
   Graph_gE802_pim1005->GetYaxis()->SetLabelSize(0.035);
   Graph_gE802_pim1005->GetYaxis()->SetTitleSize(0.035);
   Graph_gE802_pim1005->GetYaxis()->SetTitleOffset(0);
   Graph_gE802_pim1005->GetYaxis()->SetTitleFont(42);
   Graph_gE802_pim1005->GetZaxis()->SetLabelFont(42);
   Graph_gE802_pim1005->GetZaxis()->SetLabelSize(0.035);
   Graph_gE802_pim1005->GetZaxis()->SetTitleSize(0.035);
   Graph_gE802_pim1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE802_pim1005);
   
   gre->Draw(" pe");
   
   Double_t gE802_p_fx1006[1] = {
   4.86};
   Double_t gE802_p_fy1006[1] = {
   3.62};
   Double_t gE802_p_fex1006[1] = {
   0};
   Double_t gE802_p_fey1006[1] = {
   0.12};
   gre = new TGraphErrors(1,gE802_p_fx1006,gE802_p_fy1006,gE802_p_fex1006,gE802_p_fey1006);
   gre->SetName("gE802_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gE802_p1006 = new TH1F("Graph_gE802_p1006","Graph",100,4.76,5.96);
   Graph_gE802_p1006->SetMinimum(3.476);
   Graph_gE802_p1006->SetMaximum(3.764);
   Graph_gE802_p1006->SetDirectory(0);
   Graph_gE802_p1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gE802_p1006->SetLineColor(ci);
   Graph_gE802_p1006->GetXaxis()->SetLabelFont(42);
   Graph_gE802_p1006->GetXaxis()->SetLabelSize(0.035);
   Graph_gE802_p1006->GetXaxis()->SetTitleSize(0.035);
   Graph_gE802_p1006->GetXaxis()->SetTitleFont(42);
   Graph_gE802_p1006->GetYaxis()->SetLabelFont(42);
   Graph_gE802_p1006->GetYaxis()->SetLabelSize(0.035);
   Graph_gE802_p1006->GetYaxis()->SetTitleSize(0.035);
   Graph_gE802_p1006->GetYaxis()->SetTitleOffset(0);
   Graph_gE802_p1006->GetYaxis()->SetTitleFont(42);
   Graph_gE802_p1006->GetZaxis()->SetLabelFont(42);
   Graph_gE802_p1006->GetZaxis()->SetLabelSize(0.035);
   Graph_gE802_p1006->GetZaxis()->SetTitleSize(0.035);
   Graph_gE802_p1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gE802_p1006);
   
   gre->Draw(" pe");
   
   Double_t g877_lam_fx1007[1] = {
   4.9};
   Double_t g877_lam_fy1007[1] = {
   0.0283};
   Double_t g877_lam_fex1007[1] = {
   0};
   Double_t g877_lam_fey1007[1] = {
   0.003};
   gre = new TGraphErrors(1,g877_lam_fx1007,g877_lam_fy1007,g877_lam_fex1007,g877_lam_fey1007);
   gre->SetName("g877_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_g877_lam1007 = new TH1F("Graph_g877_lam1007","Graph",100,4.8,6);
   Graph_g877_lam1007->SetMinimum(0.0247);
   Graph_g877_lam1007->SetMaximum(0.0319);
   Graph_g877_lam1007->SetDirectory(0);
   Graph_g877_lam1007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g877_lam1007->SetLineColor(ci);
   Graph_g877_lam1007->GetXaxis()->SetLabelFont(42);
   Graph_g877_lam1007->GetXaxis()->SetLabelSize(0.035);
   Graph_g877_lam1007->GetXaxis()->SetTitleSize(0.035);
   Graph_g877_lam1007->GetXaxis()->SetTitleFont(42);
   Graph_g877_lam1007->GetYaxis()->SetLabelFont(42);
   Graph_g877_lam1007->GetYaxis()->SetLabelSize(0.035);
   Graph_g877_lam1007->GetYaxis()->SetTitleSize(0.035);
   Graph_g877_lam1007->GetYaxis()->SetTitleOffset(0);
   Graph_g877_lam1007->GetYaxis()->SetTitleFont(42);
   Graph_g877_lam1007->GetZaxis()->SetLabelFont(42);
   Graph_g877_lam1007->GetZaxis()->SetLabelSize(0.035);
   Graph_g877_lam1007->GetZaxis()->SetTitleSize(0.035);
   Graph_g877_lam1007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g877_lam1007);
   
   gre->Draw(" pe");
   
   Double_t g891_lam_fx1008[1] = {
   4.9};
   Double_t g891_lam_fy1008[1] = {
   0.025};
   Double_t g891_lam_fex1008[1] = {
   0};
   Double_t g891_lam_fey1008[1] = {
   0.003};
   gre = new TGraphErrors(1,g891_lam_fx1008,g891_lam_fy1008,g891_lam_fex1008,g891_lam_fey1008);
   gre->SetName("g891_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(23);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_g891_lam1008 = new TH1F("Graph_g891_lam1008","Graph",100,4.8,6);
   Graph_g891_lam1008->SetMinimum(0.0214);
   Graph_g891_lam1008->SetMaximum(0.0286);
   Graph_g891_lam1008->SetDirectory(0);
   Graph_g891_lam1008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g891_lam1008->SetLineColor(ci);
   Graph_g891_lam1008->GetXaxis()->SetLabelFont(42);
   Graph_g891_lam1008->GetXaxis()->SetLabelSize(0.035);
   Graph_g891_lam1008->GetXaxis()->SetTitleSize(0.035);
   Graph_g891_lam1008->GetXaxis()->SetTitleFont(42);
   Graph_g891_lam1008->GetYaxis()->SetLabelFont(42);
   Graph_g891_lam1008->GetYaxis()->SetLabelSize(0.035);
   Graph_g891_lam1008->GetYaxis()->SetTitleSize(0.035);
   Graph_g891_lam1008->GetYaxis()->SetTitleOffset(0);
   Graph_g891_lam1008->GetYaxis()->SetTitleFont(42);
   Graph_g891_lam1008->GetZaxis()->SetLabelFont(42);
   Graph_g891_lam1008->GetZaxis()->SetLabelSize(0.035);
   Graph_g891_lam1008->GetZaxis()->SetTitleSize(0.035);
   Graph_g891_lam1008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g891_lam1008);
   
   gre->Draw(" pe");
   
   Double_t g896_lam_fx1009[1] = {
   4.9};
   Double_t g896_lam_fy1009[1] = {
   0.0368};
   Double_t g896_lam_fex1009[1] = {
   0};
   Double_t g896_lam_fey1009[1] = {
   0.005};
   gre = new TGraphErrors(1,g896_lam_fx1009,g896_lam_fy1009,g896_lam_fex1009,g896_lam_fey1009);
   gre->SetName("g896_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_g896_lam1009 = new TH1F("Graph_g896_lam1009","Graph",100,4.8,6);
   Graph_g896_lam1009->SetMinimum(0.0308);
   Graph_g896_lam1009->SetMaximum(0.0428);
   Graph_g896_lam1009->SetDirectory(0);
   Graph_g896_lam1009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_g896_lam1009->SetLineColor(ci);
   Graph_g896_lam1009->GetXaxis()->SetLabelFont(42);
   Graph_g896_lam1009->GetXaxis()->SetLabelSize(0.035);
   Graph_g896_lam1009->GetXaxis()->SetTitleSize(0.035);
   Graph_g896_lam1009->GetXaxis()->SetTitleFont(42);
   Graph_g896_lam1009->GetYaxis()->SetLabelFont(42);
   Graph_g896_lam1009->GetYaxis()->SetLabelSize(0.035);
   Graph_g896_lam1009->GetYaxis()->SetTitleSize(0.035);
   Graph_g896_lam1009->GetYaxis()->SetTitleOffset(0);
   Graph_g896_lam1009->GetYaxis()->SetTitleFont(42);
   Graph_g896_lam1009->GetZaxis()->SetLabelFont(42);
   Graph_g896_lam1009->GetZaxis()->SetLabelSize(0.035);
   Graph_g896_lam1009->GetZaxis()->SetTitleSize(0.035);
   Graph_g896_lam1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_g896_lam1009);
   
   gre->Draw(" pe");
   
   Double_t gNA44_pim_fx1010[1] = {
   17.26};
   Double_t gNA44_pim_fy1010[1] = {
   0.476};
   Double_t gNA44_pim_fex1010[1] = {
   0};
   Double_t gNA44_pim_fey1010[1] = {
   0.048};
   gre = new TGraphErrors(1,gNA44_pim_fx1010,gNA44_pim_fy1010,gNA44_pim_fex1010,gNA44_pim_fey1010);
   gre->SetName("gNA44_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(31);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA44_pim1010 = new TH1F("Graph_gNA44_pim1010","Graph",100,17.16,18.36);
   Graph_gNA44_pim1010->SetMinimum(0.4184);
   Graph_gNA44_pim1010->SetMaximum(0.5336);
   Graph_gNA44_pim1010->SetDirectory(0);
   Graph_gNA44_pim1010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA44_pim1010->SetLineColor(ci);
   Graph_gNA44_pim1010->GetXaxis()->SetLabelFont(42);
   Graph_gNA44_pim1010->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA44_pim1010->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA44_pim1010->GetXaxis()->SetTitleFont(42);
   Graph_gNA44_pim1010->GetYaxis()->SetLabelFont(42);
   Graph_gNA44_pim1010->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA44_pim1010->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA44_pim1010->GetYaxis()->SetTitleOffset(0);
   Graph_gNA44_pim1010->GetYaxis()->SetTitleFont(42);
   Graph_gNA44_pim1010->GetZaxis()->SetLabelFont(42);
   Graph_gNA44_pim1010->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA44_pim1010->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA44_pim1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA44_pim1010);
   
   gre->Draw(" pe");
   
   Double_t gNA44_p_fx1011[1] = {
   17.26};
   Double_t gNA44_p_fy1011[1] = {
   2.04};
   Double_t gNA44_p_fex1011[1] = {
   0};
   Double_t gNA44_p_fey1011[1] = {
   0.2};
   gre = new TGraphErrors(1,gNA44_p_fx1011,gNA44_p_fy1011,gNA44_p_fex1011,gNA44_p_fey1011);
   gre->SetName("gNA44_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(31);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA44_p1011 = new TH1F("Graph_gNA44_p1011","Graph",100,17.16,18.36);
   Graph_gNA44_p1011->SetMinimum(1.8);
   Graph_gNA44_p1011->SetMaximum(2.28);
   Graph_gNA44_p1011->SetDirectory(0);
   Graph_gNA44_p1011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA44_p1011->SetLineColor(ci);
   Graph_gNA44_p1011->GetXaxis()->SetLabelFont(42);
   Graph_gNA44_p1011->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA44_p1011->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA44_p1011->GetXaxis()->SetTitleFont(42);
   Graph_gNA44_p1011->GetYaxis()->SetLabelFont(42);
   Graph_gNA44_p1011->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA44_p1011->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA44_p1011->GetYaxis()->SetTitleOffset(0);
   Graph_gNA44_p1011->GetYaxis()->SetTitleFont(42);
   Graph_gNA44_p1011->GetZaxis()->SetLabelFont(42);
   Graph_gNA44_p1011->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA44_p1011->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA44_p1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA44_p1011);
   
   gre->Draw(" pe");
   
   Double_t gNA49_pim_fx1012[5] = {
   6.38,
   7.71,
   8.83,
   12.35,
   17.26};
   Double_t gNA49_pim_fy1012[5] = {
   0.251,
   0.268,
   0.29,
   0.383,
   0.478};
   Double_t gNA49_pim_fex1012[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gNA49_pim_fey1012[5] = {
   0.025,
   0.026,
   0.029,
   0.038,
   0.048};
   gre = new TGraphErrors(5,gNA49_pim_fx1012,gNA49_pim_fy1012,gNA49_pim_fex1012,gNA49_pim_fey1012);
   gre->SetName("gNA49_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA49_pim1012 = new TH1F("Graph_gNA49_pim1012","Graph",100,5.292,18.348);
   Graph_gNA49_pim1012->SetMinimum(0.196);
   Graph_gNA49_pim1012->SetMaximum(0.556);
   Graph_gNA49_pim1012->SetDirectory(0);
   Graph_gNA49_pim1012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA49_pim1012->SetLineColor(ci);
   Graph_gNA49_pim1012->GetXaxis()->SetLabelFont(42);
   Graph_gNA49_pim1012->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA49_pim1012->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA49_pim1012->GetXaxis()->SetTitleFont(42);
   Graph_gNA49_pim1012->GetYaxis()->SetLabelFont(42);
   Graph_gNA49_pim1012->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA49_pim1012->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA49_pim1012->GetYaxis()->SetTitleOffset(0);
   Graph_gNA49_pim1012->GetYaxis()->SetTitleFont(42);
   Graph_gNA49_pim1012->GetZaxis()->SetLabelFont(42);
   Graph_gNA49_pim1012->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA49_pim1012->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA49_pim1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA49_pim1012);
   
   gre->Draw(" pe");
   
   Double_t gNA49_lam_fx1013[5] = {
   6.38,
   7.71,
   8.83,
   12.35,
   17.26};
   Double_t gNA49_lam_fy1013[5] = {
   0.041,
   0.0464,
   0.0437,
   0.0342,
   0.03};
   Double_t gNA49_lam_fex1013[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gNA49_lam_fey1013[5] = {
   0.004,
   0.002,
   0.002,
   0.002,
   0.002};
   gre = new TGraphErrors(5,gNA49_lam_fx1013,gNA49_lam_fy1013,gNA49_lam_fex1013,gNA49_lam_fey1013);
   gre->SetName("gNA49_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA49_lam1013 = new TH1F("Graph_gNA49_lam1013","Graph",100,5.292,18.348);
   Graph_gNA49_lam1013->SetMinimum(0.02596);
   Graph_gNA49_lam1013->SetMaximum(0.05044);
   Graph_gNA49_lam1013->SetDirectory(0);
   Graph_gNA49_lam1013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA49_lam1013->SetLineColor(ci);
   Graph_gNA49_lam1013->GetXaxis()->SetLabelFont(42);
   Graph_gNA49_lam1013->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA49_lam1013->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA49_lam1013->GetXaxis()->SetTitleFont(42);
   Graph_gNA49_lam1013->GetYaxis()->SetLabelFont(42);
   Graph_gNA49_lam1013->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA49_lam1013->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA49_lam1013->GetYaxis()->SetTitleOffset(0);
   Graph_gNA49_lam1013->GetYaxis()->SetTitleFont(42);
   Graph_gNA49_lam1013->GetZaxis()->SetLabelFont(42);
   Graph_gNA49_lam1013->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA49_lam1013->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA49_lam1013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA49_lam1013);
   
   gre->Draw(" pe");
   
   Double_t gNA49_p_fx1014[5] = {
   6.38,
   7.71,
   8.83,
   12.35,
   17.26};
   Double_t gNA49_p_fy1014[5] = {
   2.52,
   2.3,
   2.26,
   1.644,
   2.022};
   Double_t gNA49_p_fex1014[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gNA49_p_fey1014[5] = {
   0.24,
   0.22,
   0.22,
   0.16,
   0.2};
   gre = new TGraphErrors(5,gNA49_p_fx1014,gNA49_p_fy1014,gNA49_p_fex1014,gNA49_p_fey1014);
   gre->SetName("gNA49_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA49_p1014 = new TH1F("Graph_gNA49_p1014","Graph",100,5.292,18.348);
   Graph_gNA49_p1014->SetMinimum(1.3564);
   Graph_gNA49_p1014->SetMaximum(2.8876);
   Graph_gNA49_p1014->SetDirectory(0);
   Graph_gNA49_p1014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA49_p1014->SetLineColor(ci);
   Graph_gNA49_p1014->GetXaxis()->SetLabelFont(42);
   Graph_gNA49_p1014->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA49_p1014->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA49_p1014->GetXaxis()->SetTitleFont(42);
   Graph_gNA49_p1014->GetYaxis()->SetLabelFont(42);
   Graph_gNA49_p1014->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA49_p1014->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA49_p1014->GetYaxis()->SetTitleOffset(0);
   Graph_gNA49_p1014->GetYaxis()->SetTitleFont(42);
   Graph_gNA49_p1014->GetZaxis()->SetLabelFont(42);
   Graph_gNA49_p1014->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA49_p1014->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA49_p1014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA49_p1014);
   
   gre->Draw(" pe");
   
   Double_t gNA57_k0s_fx1015[1] = {
   8.8};
   Double_t gNA57_k0s_fy1015[1] = {
   0.0051};
   Double_t gNA57_k0s_fex1015[1] = {
   0};
   Double_t gNA57_k0s_fey1015[1] = {
   0.00025};
   gre = new TGraphErrors(1,gNA57_k0s_fx1015,gNA57_k0s_fy1015,gNA57_k0s_fex1015,gNA57_k0s_fey1015);
   gre->SetName("gNA57_k0s");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA57_k0s1015 = new TH1F("Graph_gNA57_k0s1015","Graph",100,8.7,9.9);
   Graph_gNA57_k0s1015->SetMinimum(0.0048);
   Graph_gNA57_k0s1015->SetMaximum(0.0054);
   Graph_gNA57_k0s1015->SetDirectory(0);
   Graph_gNA57_k0s1015->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA57_k0s1015->SetLineColor(ci);
   Graph_gNA57_k0s1015->GetXaxis()->SetLabelFont(42);
   Graph_gNA57_k0s1015->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA57_k0s1015->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA57_k0s1015->GetXaxis()->SetTitleFont(42);
   Graph_gNA57_k0s1015->GetYaxis()->SetLabelFont(42);
   Graph_gNA57_k0s1015->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA57_k0s1015->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA57_k0s1015->GetYaxis()->SetTitleOffset(0);
   Graph_gNA57_k0s1015->GetYaxis()->SetTitleFont(42);
   Graph_gNA57_k0s1015->GetZaxis()->SetLabelFont(42);
   Graph_gNA57_k0s1015->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA57_k0s1015->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA57_k0s1015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA57_k0s1015);
   
   gre->Draw(" pe");
   
   Double_t gNA57_lam_fx1016[2] = {
   8.8,
   17.3};
   Double_t gNA57_lam_fy1016[2] = {
   0.0574,
   0.0492};
   Double_t gNA57_lam_fex1016[2] = {
   0,
   0};
   Double_t gNA57_lam_fey1016[2] = {
   0.005,
   0.005};
   gre = new TGraphErrors(2,gNA57_lam_fx1016,gNA57_lam_fy1016,gNA57_lam_fex1016,gNA57_lam_fey1016);
   gre->SetName("gNA57_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gNA57_lam1016 = new TH1F("Graph_gNA57_lam1016","Graph",100,7.95,18.15);
   Graph_gNA57_lam1016->SetMinimum(0.04238);
   Graph_gNA57_lam1016->SetMaximum(0.06422);
   Graph_gNA57_lam1016->SetDirectory(0);
   Graph_gNA57_lam1016->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gNA57_lam1016->SetLineColor(ci);
   Graph_gNA57_lam1016->GetXaxis()->SetLabelFont(42);
   Graph_gNA57_lam1016->GetXaxis()->SetLabelSize(0.035);
   Graph_gNA57_lam1016->GetXaxis()->SetTitleSize(0.035);
   Graph_gNA57_lam1016->GetXaxis()->SetTitleFont(42);
   Graph_gNA57_lam1016->GetYaxis()->SetLabelFont(42);
   Graph_gNA57_lam1016->GetYaxis()->SetLabelSize(0.035);
   Graph_gNA57_lam1016->GetYaxis()->SetTitleSize(0.035);
   Graph_gNA57_lam1016->GetYaxis()->SetTitleOffset(0);
   Graph_gNA57_lam1016->GetYaxis()->SetTitleFont(42);
   Graph_gNA57_lam1016->GetZaxis()->SetLabelFont(42);
   Graph_gNA57_lam1016->GetZaxis()->SetLabelSize(0.035);
   Graph_gNA57_lam1016->GetZaxis()->SetTitleSize(0.035);
   Graph_gNA57_lam1016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gNA57_lam1016);
   
   gre->Draw(" pe");
   
   Double_t gWA98_pim_fx1017[1] = {
   17.26};
   Double_t gWA98_pim_fy1017[1] = {
   0.489};
   Double_t gWA98_pim_fex1017[1] = {
   0};
   Double_t gWA98_pim_fey1017[1] = {
   0.048};
   gre = new TGraphErrors(1,gWA98_pim_fx1017,gWA98_pim_fy1017,gWA98_pim_fex1017,gWA98_pim_fey1017);
   gre->SetName("gWA98_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gWA98_pim1017 = new TH1F("Graph_gWA98_pim1017","Graph",100,17.16,18.36);
   Graph_gWA98_pim1017->SetMinimum(0.4314);
   Graph_gWA98_pim1017->SetMaximum(0.5466);
   Graph_gWA98_pim1017->SetDirectory(0);
   Graph_gWA98_pim1017->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gWA98_pim1017->SetLineColor(ci);
   Graph_gWA98_pim1017->GetXaxis()->SetLabelFont(42);
   Graph_gWA98_pim1017->GetXaxis()->SetLabelSize(0.035);
   Graph_gWA98_pim1017->GetXaxis()->SetTitleSize(0.035);
   Graph_gWA98_pim1017->GetXaxis()->SetTitleFont(42);
   Graph_gWA98_pim1017->GetYaxis()->SetLabelFont(42);
   Graph_gWA98_pim1017->GetYaxis()->SetLabelSize(0.035);
   Graph_gWA98_pim1017->GetYaxis()->SetTitleSize(0.035);
   Graph_gWA98_pim1017->GetYaxis()->SetTitleOffset(0);
   Graph_gWA98_pim1017->GetYaxis()->SetTitleFont(42);
   Graph_gWA98_pim1017->GetZaxis()->SetLabelFont(42);
   Graph_gWA98_pim1017->GetZaxis()->SetLabelSize(0.035);
   Graph_gWA98_pim1017->GetZaxis()->SetTitleSize(0.035);
   Graph_gWA98_pim1017->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gWA98_pim1017);
   
   gre->Draw(" pe");
   
   Double_t gSTARBES_pim_fx1018[5] = {
   7.7,
   11.5,
   19.6,
   27,
   39};
   Double_t gSTARBES_pim_fy1018[5] = {
   0.2965,
   0.3835,
   0.4905,
   0.5157,
   0.4536};
   Double_t gSTARBES_pim_fex1018[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gSTARBES_pim_fey1018[5] = {
   0.027,
   0.039,
   0.054,
   0.057,
   0.06};
   gre = new TGraphErrors(5,gSTARBES_pim_fx1018,gSTARBES_pim_fy1018,gSTARBES_pim_fex1018,gSTARBES_pim_fey1018);
   gre->SetName("gSTARBES_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#32424a");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gSTARBES_pim1018 = new TH1F("Graph_gSTARBES_pim1018","Graph",100,4.57,42.13);
   Graph_gSTARBES_pim1018->SetMinimum(0.23918);
   Graph_gSTARBES_pim1018->SetMaximum(0.60302);
   Graph_gSTARBES_pim1018->SetDirectory(0);
   Graph_gSTARBES_pim1018->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARBES_pim1018->SetLineColor(ci);
   Graph_gSTARBES_pim1018->GetXaxis()->SetLabelFont(42);
   Graph_gSTARBES_pim1018->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_pim1018->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_pim1018->GetXaxis()->SetTitleFont(42);
   Graph_gSTARBES_pim1018->GetYaxis()->SetLabelFont(42);
   Graph_gSTARBES_pim1018->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_pim1018->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_pim1018->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARBES_pim1018->GetYaxis()->SetTitleFont(42);
   Graph_gSTARBES_pim1018->GetZaxis()->SetLabelFont(42);
   Graph_gSTARBES_pim1018->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_pim1018->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_pim1018->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARBES_pim1018);
   
   gre->Draw(" pe");
   
   Double_t gSTARBES_k0s_fx1019[5] = {
   7.7,
   11.5,
   19.6,
   27,
   39};
   Double_t gSTARBES_k0s_fy1019[5] = {
   0.00348,
   0.00448,
   0.00581,
   0.00646,
   0.00686};
   Double_t gSTARBES_k0s_fex1019[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gSTARBES_k0s_fey1019[5] = {
   0.0002,
   0.0002,
   0.0002,
   0.0002,
   0.0005};
   gre = new TGraphErrors(5,gSTARBES_k0s_fx1019,gSTARBES_k0s_fy1019,gSTARBES_k0s_fex1019,gSTARBES_k0s_fey1019);
   gre->SetName("gSTARBES_k0s");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(4);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gSTARBES_k0s1019 = new TH1F("Graph_gSTARBES_k0s1019","Graph",100,4.57,42.13);
   Graph_gSTARBES_k0s1019->SetMinimum(0.002872);
   Graph_gSTARBES_k0s1019->SetMaximum(0.007768);
   Graph_gSTARBES_k0s1019->SetDirectory(0);
   Graph_gSTARBES_k0s1019->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARBES_k0s1019->SetLineColor(ci);
   Graph_gSTARBES_k0s1019->GetXaxis()->SetLabelFont(42);
   Graph_gSTARBES_k0s1019->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_k0s1019->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_k0s1019->GetXaxis()->SetTitleFont(42);
   Graph_gSTARBES_k0s1019->GetYaxis()->SetLabelFont(42);
   Graph_gSTARBES_k0s1019->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_k0s1019->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_k0s1019->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARBES_k0s1019->GetYaxis()->SetTitleFont(42);
   Graph_gSTARBES_k0s1019->GetZaxis()->SetLabelFont(42);
   Graph_gSTARBES_k0s1019->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_k0s1019->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_k0s1019->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARBES_k0s1019);
   
   gre->Draw(" pe");
   
   Double_t gSTARBES_lam_fx1020[5] = {
   7.7,
   11.5,
   19.6,
   27,
   39};
   Double_t gSTARBES_lam_fy1020[5] = {
   0.0425,
   0.0397,
   0.0368,
   0.034,
   0.0312};
   Double_t gSTARBES_lam_fex1020[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gSTARBES_lam_fey1020[5] = {
   0.004,
   0.003,
   0.002,
   0.002,
   0.003};
   gre = new TGraphErrors(5,gSTARBES_lam_fx1020,gSTARBES_lam_fy1020,gSTARBES_lam_fex1020,gSTARBES_lam_fey1020);
   gre->SetName("gSTARBES_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gSTARBES_lam1020 = new TH1F("Graph_gSTARBES_lam1020","Graph",100,4.57,42.13);
   Graph_gSTARBES_lam1020->SetMinimum(0.02637);
   Graph_gSTARBES_lam1020->SetMaximum(0.04833);
   Graph_gSTARBES_lam1020->SetDirectory(0);
   Graph_gSTARBES_lam1020->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARBES_lam1020->SetLineColor(ci);
   Graph_gSTARBES_lam1020->GetXaxis()->SetLabelFont(42);
   Graph_gSTARBES_lam1020->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_lam1020->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_lam1020->GetXaxis()->SetTitleFont(42);
   Graph_gSTARBES_lam1020->GetYaxis()->SetLabelFont(42);
   Graph_gSTARBES_lam1020->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_lam1020->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_lam1020->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARBES_lam1020->GetYaxis()->SetTitleFont(42);
   Graph_gSTARBES_lam1020->GetZaxis()->SetLabelFont(42);
   Graph_gSTARBES_lam1020->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_lam1020->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_lam1020->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARBES_lam1020);
   
   gre->Draw(" pe");
   
   Double_t gSTARBES_p_fx1021[5] = {
   7.7,
   11.5,
   19.6,
   27,
   39};
   Double_t gSTARBES_p_fy1021[5] = {
   3.258,
   2.602,
   2.025,
   1.849,
   1.551};
   Double_t gSTARBES_p_fex1021[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t gSTARBES_p_fey1021[5] = {
   0.36,
   0.314,
   0.264,
   0.0222,
   0.171};
   gre = new TGraphErrors(5,gSTARBES_p_fx1021,gSTARBES_p_fy1021,gSTARBES_p_fex1021,gSTARBES_p_fey1021);
   gre->SetName("gSTARBES_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6600");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gSTARBES_p1021 = new TH1F("Graph_gSTARBES_p1021","Graph",100,4.57,42.13);
   Graph_gSTARBES_p1021->SetMinimum(1.1562);
   Graph_gSTARBES_p1021->SetMaximum(3.8418);
   Graph_gSTARBES_p1021->SetDirectory(0);
   Graph_gSTARBES_p1021->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARBES_p1021->SetLineColor(ci);
   Graph_gSTARBES_p1021->GetXaxis()->SetLabelFont(42);
   Graph_gSTARBES_p1021->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_p1021->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_p1021->GetXaxis()->SetTitleFont(42);
   Graph_gSTARBES_p1021->GetYaxis()->SetLabelFont(42);
   Graph_gSTARBES_p1021->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_p1021->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_p1021->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARBES_p1021->GetYaxis()->SetTitleFont(42);
   Graph_gSTARBES_p1021->GetZaxis()->SetLabelFont(42);
   Graph_gSTARBES_p1021->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARBES_p1021->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARBES_p1021->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARBES_p1021);
   
   gre->Draw(" pe");
   
   Double_t gSTARFXT_pim_fx1022[1] = {
   4.5};
   Double_t gSTARFXT_pim_fy1022[1] = {
   0.184};
   Double_t gSTARFXT_pim_fex1022[1] = {
   0};
   Double_t gSTARFXT_pim_fey1022[1] = {
   0.018};
   gre = new TGraphErrors(1,gSTARFXT_pim_fx1022,gSTARFXT_pim_fy1022,gSTARFXT_pim_fex1022,gSTARFXT_pim_fey1022);
   gre->SetName("gSTARFXT_pim");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_gSTARFXT_pim1022 = new TH1F("Graph_gSTARFXT_pim1022","Graph",100,4.4,5.6);
   Graph_gSTARFXT_pim1022->SetMinimum(0.1624);
   Graph_gSTARFXT_pim1022->SetMaximum(0.2056);
   Graph_gSTARFXT_pim1022->SetDirectory(0);
   Graph_gSTARFXT_pim1022->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARFXT_pim1022->SetLineColor(ci);
   Graph_gSTARFXT_pim1022->GetXaxis()->SetLabelFont(42);
   Graph_gSTARFXT_pim1022->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_pim1022->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_pim1022->GetXaxis()->SetTitleFont(42);
   Graph_gSTARFXT_pim1022->GetYaxis()->SetLabelFont(42);
   Graph_gSTARFXT_pim1022->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_pim1022->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_pim1022->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARFXT_pim1022->GetYaxis()->SetTitleFont(42);
   Graph_gSTARFXT_pim1022->GetZaxis()->SetLabelFont(42);
   Graph_gSTARFXT_pim1022->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_pim1022->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_pim1022->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARFXT_pim1022);
   
   gre->Draw(" pe");
   
   Double_t gSTARFXT_k0s_fx1023[1] = {
   4.5};
   Double_t gSTARFXT_k0s_fy1023[1] = {
   0.00122};
   Double_t gSTARFXT_k0s_fex1023[1] = {
   0};
   Double_t gSTARFXT_k0s_fey1023[1] = {
   0.0001};
   gre = new TGraphErrors(1,gSTARFXT_k0s_fx1023,gSTARFXT_k0s_fy1023,gSTARFXT_k0s_fex1023,gSTARFXT_k0s_fey1023);
   gre->SetName("gSTARFXT_k0s");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_gSTARFXT_k0s1023 = new TH1F("Graph_gSTARFXT_k0s1023","Graph",100,4.4,5.6);
   Graph_gSTARFXT_k0s1023->SetMinimum(0.0011);
   Graph_gSTARFXT_k0s1023->SetMaximum(0.00134);
   Graph_gSTARFXT_k0s1023->SetDirectory(0);
   Graph_gSTARFXT_k0s1023->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARFXT_k0s1023->SetLineColor(ci);
   Graph_gSTARFXT_k0s1023->GetXaxis()->SetLabelFont(42);
   Graph_gSTARFXT_k0s1023->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_k0s1023->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_k0s1023->GetXaxis()->SetTitleFont(42);
   Graph_gSTARFXT_k0s1023->GetYaxis()->SetLabelFont(42);
   Graph_gSTARFXT_k0s1023->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_k0s1023->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_k0s1023->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARFXT_k0s1023->GetYaxis()->SetTitleFont(42);
   Graph_gSTARFXT_k0s1023->GetZaxis()->SetLabelFont(42);
   Graph_gSTARFXT_k0s1023->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_k0s1023->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_k0s1023->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARFXT_k0s1023);
   
   gre->Draw(" pe");
   
   Double_t gSTARFXT_lam_fx1024[1] = {
   4.5};
   Double_t gSTARFXT_lam_fy1024[1] = {
   0.0277};
   Double_t gSTARFXT_lam_fex1024[1] = {
   0};
   Double_t gSTARFXT_lam_fey1024[1] = {
   0.003};
   gre = new TGraphErrors(1,gSTARFXT_lam_fx1024,gSTARFXT_lam_fy1024,gSTARFXT_lam_fex1024,gSTARFXT_lam_fey1024);
   gre->SetName("gSTARFXT_lam");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_gSTARFXT_lam1024 = new TH1F("Graph_gSTARFXT_lam1024","Graph",100,4.4,5.6);
   Graph_gSTARFXT_lam1024->SetMinimum(0.0241);
   Graph_gSTARFXT_lam1024->SetMaximum(0.0313);
   Graph_gSTARFXT_lam1024->SetDirectory(0);
   Graph_gSTARFXT_lam1024->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARFXT_lam1024->SetLineColor(ci);
   Graph_gSTARFXT_lam1024->GetXaxis()->SetLabelFont(42);
   Graph_gSTARFXT_lam1024->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_lam1024->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_lam1024->GetXaxis()->SetTitleFont(42);
   Graph_gSTARFXT_lam1024->GetYaxis()->SetLabelFont(42);
   Graph_gSTARFXT_lam1024->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_lam1024->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_lam1024->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARFXT_lam1024->GetYaxis()->SetTitleFont(42);
   Graph_gSTARFXT_lam1024->GetZaxis()->SetLabelFont(42);
   Graph_gSTARFXT_lam1024->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_lam1024->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_lam1024->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARFXT_lam1024);
   
   gre->Draw(" pe");
   
   Double_t gSTARFXT_p_fx1025[1] = {
   4.5};
   Double_t gSTARFXT_p_fy1025[1] = {
   3.58};
   Double_t gSTARFXT_p_fex1025[1] = {
   0};
   Double_t gSTARFXT_p_fey1025[1] = {
   0.3};
   gre = new TGraphErrors(1,gSTARFXT_p_fx1025,gSTARFXT_p_fy1025,gSTARFXT_p_fex1025,gSTARFXT_p_fey1025);
   gre->SetName("gSTARFXT_p");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(5);
   
   TH1F *Graph_gSTARFXT_p1025 = new TH1F("Graph_gSTARFXT_p1025","Graph",100,4.4,5.6);
   Graph_gSTARFXT_p1025->SetMinimum(3.22);
   Graph_gSTARFXT_p1025->SetMaximum(3.94);
   Graph_gSTARFXT_p1025->SetDirectory(0);
   Graph_gSTARFXT_p1025->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gSTARFXT_p1025->SetLineColor(ci);
   Graph_gSTARFXT_p1025->GetXaxis()->SetLabelFont(42);
   Graph_gSTARFXT_p1025->GetXaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_p1025->GetXaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_p1025->GetXaxis()->SetTitleFont(42);
   Graph_gSTARFXT_p1025->GetYaxis()->SetLabelFont(42);
   Graph_gSTARFXT_p1025->GetYaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_p1025->GetYaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_p1025->GetYaxis()->SetTitleOffset(0);
   Graph_gSTARFXT_p1025->GetYaxis()->SetTitleFont(42);
   Graph_gSTARFXT_p1025->GetZaxis()->SetLabelFont(42);
   Graph_gSTARFXT_p1025->GetZaxis()->SetLabelSize(0.035);
   Graph_gSTARFXT_p1025->GetZaxis()->SetTitleSize(0.035);
   Graph_gSTARFXT_p1025->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gSTARFXT_p1025);
   
   gre->Draw(" pe");
   TLatex *   tex = new TLatex(21,3,"p #times 20");
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(20,0.2,"#pi^{#font[122]{-} }");
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(20,0.02,"#Lambda");
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(20,0.002,"K^{0}_{S} #times 0.1");
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.2,0.75,0.95,0.95,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/gE895_pim","E895","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(24);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gE802_pim","E802","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/g891_lam","E891","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/g896_lam","E896","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/g877_lam","E877","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gNA57_lam","NA57","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gNA44_pim","NA44","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(31);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gNA49_pim","NA49","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(28);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gWA98_pim","WA98","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gSTARBES_pim","STAR BES","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(30);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/gSTARFXT_pim","STAR FXT","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(5);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
