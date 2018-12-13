void figure_23()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 15:58:28 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-3.529412,2.333333,31.76471,5.666667);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3, 3.3, 3.6, 3.9, 4.2, 4.5, 4.8, 5.1, 5.4, 5.7, 6, 6.3, 6.6, 6.9, 7.2, 7.5, 7.8, 8.1, 8.4, 8.7, 9, 9.3, 9.6, 9.9, 10.2, 10.5, 10.8, 11.1, 11.4, 11.7, 12, 12.3, 12.6, 12.9, 13.2, 13.5, 13.8, 14.1, 14.4, 14.7, 15, 15.3, 15.6, 15.9, 16.2, 16.5, 16.8, 17.1, 17.4, 17.7, 18, 18.3, 18.6, 18.9, 19.2, 19.5, 19.8, 20.1, 20.4, 20.7, 21, 21.3, 21.6, 21.9, 22.2, 22.5, 22.8, 23.1, 23.4, 23.7, 24, 24.3, 24.6, 24.9, 25.2, 25.5, 25.8, 26.1, 26.4, 26.7, 27, 27.3, 27.6, 27.9, 28.2, 28.5, 28.8, 29.1, 29.4, 29.7, 30}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(2.7);
   frame_5PN2__1->SetMaximum(5.5);
   frame_5PN2__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetTitle("% Central");
   frame_5PN2__1->GetXaxis()->SetNdivisions(506);
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.05);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.06111111);
   frame_5PN2__1->GetXaxis()->SetTitleOffset(0.8);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("R (fm)");
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.05);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.06111111);
   frame_5PN2__1->GetYaxis()->SetTitleOffset(0.75);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t Ro_Err_fx1001[6] = {
   27.75,
   22.75,
   17.75,
   12.75,
   7.75,
   2.75};
   Double_t Ro_Err_fy1001[6] = {
   3.628336,
   3.882034,
   4.032121,
   4.163384,
   4.526884,
   4.905428};
   Double_t Ro_Err_fex1001[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Ro_Err_fey1001[6] = {
   0.344692,
   0.3687932,
   0.3830515,
   0.3955214,
   0.430054,
   0.4660157};
   TGraphErrors *gre = new TGraphErrors(6,Ro_Err_fx1001,Ro_Err_fy1001,Ro_Err_fex1001,Ro_Err_fey1001);
   gre->SetName("Ro_Err");
   gre->SetTitle("Graph");

   ci = 1434;
   color = new TColor(ci, 1, 0, 0, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Ro_Err1001 = new TH1F("Graph_Ro_Err1001","Graph",100,0,30.85);
   Graph_Ro_Err1001->SetMinimum(3.074864);
   Graph_Ro_Err1001->SetMaximum(5.580224);
   Graph_Ro_Err1001->SetDirectory(0);
   Graph_Ro_Err1001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Ro_Err1001->SetLineColor(ci);
   Graph_Ro_Err1001->GetXaxis()->SetLabelFont(42);
   Graph_Ro_Err1001->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Ro_Err1001->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Ro_Err1001->GetXaxis()->SetTitleFont(42);
   Graph_Ro_Err1001->GetYaxis()->SetLabelFont(42);
   Graph_Ro_Err1001->GetYaxis()->SetLabelSize(0.05);
   Graph_Ro_Err1001->GetYaxis()->SetTitleSize(0.05);
   Graph_Ro_Err1001->GetYaxis()->SetTitleOffset(0);
   Graph_Ro_Err1001->GetYaxis()->SetTitleFont(42);
   Graph_Ro_Err1001->GetZaxis()->SetLabelFont(42);
   Graph_Ro_Err1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Ro_Err1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Ro_Err1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Ro_Err1001);
   
   gre->Draw("p e2");
   
   Double_t Ro_fx1002[6] = {
   27.75,
   22.75,
   17.75,
   12.75,
   7.75,
   2.75};
   Double_t Ro_fy1002[6] = {
   3.628336,
   3.882034,
   4.032121,
   4.163384,
   4.526884,
   4.905428};
   Double_t Ro_fex1002[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Ro_fey1002[6] = {
   0.1459377,
   0.09905922,
   0.0692106,
   0.05314,
   0.04455599,
   0.05167462};
   gre = new TGraphErrors(6,Ro_fx1002,Ro_fy1002,Ro_fex1002,Ro_fey1002);
   gre->SetName("Ro");
   gre->SetTitle("Graph");
   gre->SetFillColor(2);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Ro1002 = new TH1F("Graph_Ro1002","Graph",100,0,30.85);
   Graph_Ro1002->SetMinimum(3.334928);
   Graph_Ro1002->SetMaximum(5.104573);
   Graph_Ro1002->SetDirectory(0);
   Graph_Ro1002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Ro1002->SetLineColor(ci);
   Graph_Ro1002->GetXaxis()->SetLabelFont(42);
   Graph_Ro1002->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Ro1002->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Ro1002->GetXaxis()->SetTitleFont(42);
   Graph_Ro1002->GetYaxis()->SetLabelFont(42);
   Graph_Ro1002->GetYaxis()->SetLabelSize(0.05);
   Graph_Ro1002->GetYaxis()->SetTitleSize(0.05);
   Graph_Ro1002->GetYaxis()->SetTitleOffset(0);
   Graph_Ro1002->GetYaxis()->SetTitleFont(42);
   Graph_Ro1002->GetZaxis()->SetLabelFont(42);
   Graph_Ro1002->GetZaxis()->SetLabelSize(0.035);
   Graph_Ro1002->GetZaxis()->SetTitleSize(0.035);
   Graph_Ro1002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Ro1002);
   
   gre->Draw("e1");
   
   Double_t Rs_Err_fx1003[6] = {
   27.5,
   22.5,
   17.5,
   12.5,
   7.5,
   2.5};
   Double_t Rs_Err_fy1003[6] = {
   3.211626,
   3.313296,
   3.592466,
   3.762461,
   4.044462,
   4.305749};
   Double_t Rs_Err_fex1003[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Rs_Err_fey1003[6] = {
   0.2087557,
   0.2153642,
   0.2335103,
   0.24456,
   0.26289,
   0.2798737};
   gre = new TGraphErrors(6,Rs_Err_fx1003,Rs_Err_fy1003,Rs_Err_fex1003,Rs_Err_fey1003);
   gre->SetName("Rs_Err");
   gre->SetTitle("Graph");

   ci = 1435;
   color = new TColor(ci, 0, 0, 1, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rs_Err1003 = new TH1F("Graph_Rs_Err1003","Graph",100,0,30.6);
   Graph_Rs_Err1003->SetMinimum(2.844595);
   Graph_Rs_Err1003->SetMaximum(4.743898);
   Graph_Rs_Err1003->SetDirectory(0);
   Graph_Rs_Err1003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rs_Err1003->SetLineColor(ci);
   Graph_Rs_Err1003->GetXaxis()->SetLabelFont(42);
   Graph_Rs_Err1003->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Rs_Err1003->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Rs_Err1003->GetXaxis()->SetTitleFont(42);
   Graph_Rs_Err1003->GetYaxis()->SetLabelFont(42);
   Graph_Rs_Err1003->GetYaxis()->SetLabelSize(0.05);
   Graph_Rs_Err1003->GetYaxis()->SetTitleSize(0.05);
   Graph_Rs_Err1003->GetYaxis()->SetTitleOffset(0);
   Graph_Rs_Err1003->GetYaxis()->SetTitleFont(42);
   Graph_Rs_Err1003->GetZaxis()->SetLabelFont(42);
   Graph_Rs_Err1003->GetZaxis()->SetLabelSize(0.035);
   Graph_Rs_Err1003->GetZaxis()->SetTitleSize(0.035);
   Graph_Rs_Err1003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rs_Err1003);
   
   gre->Draw("pe2");
   
   Double_t Rs_fx1004[6] = {
   27.5,
   22.5,
   17.5,
   12.5,
   7.5,
   2.5};
   Double_t Rs_fy1004[6] = {
   3.211626,
   3.313296,
   3.592466,
   3.762461,
   4.044462,
   4.305749};
   Double_t Rs_fex1004[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Rs_fey1004[6] = {
   0.1229468,
   0.07196541,
   0.05402898,
   0.04315472,
   0.03660458,
   0.04292201};
   gre = new TGraphErrors(6,Rs_fx1004,Rs_fy1004,Rs_fex1004,Rs_fey1004);
   gre->SetName("Rs");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rs1004 = new TH1F("Graph_Rs1004","Graph",100,0,30.6);
   Graph_Rs1004->SetMinimum(2.96268);
   Graph_Rs1004->SetMaximum(4.47467);
   Graph_Rs1004->SetDirectory(0);
   Graph_Rs1004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rs1004->SetLineColor(ci);
   Graph_Rs1004->GetXaxis()->SetLabelFont(42);
   Graph_Rs1004->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Rs1004->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Rs1004->GetXaxis()->SetTitleFont(42);
   Graph_Rs1004->GetYaxis()->SetLabelFont(42);
   Graph_Rs1004->GetYaxis()->SetLabelSize(0.05);
   Graph_Rs1004->GetYaxis()->SetTitleSize(0.05);
   Graph_Rs1004->GetYaxis()->SetTitleOffset(0);
   Graph_Rs1004->GetYaxis()->SetTitleFont(42);
   Graph_Rs1004->GetZaxis()->SetLabelFont(42);
   Graph_Rs1004->GetZaxis()->SetLabelSize(0.035);
   Graph_Rs1004->GetZaxis()->SetTitleSize(0.035);
   Graph_Rs1004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rs1004);
   
   gre->Draw("e1");
   
   Double_t Rl_Err_fx1005[6] = {
   27.25,
   22.25,
   17.25,
   12.25,
   7.25,
   2.25};
   Double_t Rl_Err_fy1005[6] = {
   3.176281,
   3.093719,
   3.367489,
   3.496784,
   3.648267,
   3.855989};
   Double_t Rl_Err_fex1005[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Rl_Err_fey1005[6] = {
   0.2223397,
   0.2165604,
   0.2357242,
   0.2447749,
   0.2553787,
   0.2699193};
   gre = new TGraphErrors(6,Rl_Err_fx1005,Rl_Err_fy1005,Rl_Err_fex1005,Rl_Err_fey1005);
   gre->SetName("Rl_Err");
   gre->SetTitle("Graph");

   ci = 1436;
   color = new TColor(ci, 0, 0, 0, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rl_Err1005 = new TH1F("Graph_Rl_Err1005","Graph",100,0,30.35);
   Graph_Rl_Err1005->SetMinimum(2.752284);
   Graph_Rl_Err1005->SetMaximum(4.250783);
   Graph_Rl_Err1005->SetDirectory(0);
   Graph_Rl_Err1005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rl_Err1005->SetLineColor(ci);
   Graph_Rl_Err1005->GetXaxis()->SetLabelFont(42);
   Graph_Rl_Err1005->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Rl_Err1005->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Rl_Err1005->GetXaxis()->SetTitleFont(42);
   Graph_Rl_Err1005->GetYaxis()->SetLabelFont(42);
   Graph_Rl_Err1005->GetYaxis()->SetLabelSize(0.05);
   Graph_Rl_Err1005->GetYaxis()->SetTitleSize(0.05);
   Graph_Rl_Err1005->GetYaxis()->SetTitleOffset(0);
   Graph_Rl_Err1005->GetYaxis()->SetTitleFont(42);
   Graph_Rl_Err1005->GetZaxis()->SetLabelFont(42);
   Graph_Rl_Err1005->GetZaxis()->SetLabelSize(0.035);
   Graph_Rl_Err1005->GetZaxis()->SetTitleSize(0.035);
   Graph_Rl_Err1005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rl_Err1005);
   
   gre->Draw("pe2");
   
   Double_t Rl_fx1006[6] = {
   27.25,
   22.25,
   17.25,
   12.25,
   7.25,
   2.25};
   Double_t Rl_fy1006[6] = {
   3.176281,
   3.093719,
   3.367489,
   3.496784,
   3.648267,
   3.855989};
   Double_t Rl_fex1006[6] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Rl_fey1006[6] = {
   0.1292917,
   0.07732521,
   0.05726424,
   0.0462329,
   0.0373173,
   0.0429123};
   gre = new TGraphErrors(6,Rl_fx1006,Rl_fy1006,Rl_fex1006,Rl_fey1006);
   gre->SetName("Rl");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Rl1006 = new TH1F("Graph_Rl1006","Graph",100,0,30.35);
   Graph_Rl1006->SetMinimum(2.928143);
   Graph_Rl1006->SetMaximum(3.987152);
   Graph_Rl1006->SetDirectory(0);
   Graph_Rl1006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Rl1006->SetLineColor(ci);
   Graph_Rl1006->GetXaxis()->SetLabelFont(42);
   Graph_Rl1006->GetXaxis()->SetLabelSize(0.04444445);
   Graph_Rl1006->GetXaxis()->SetTitleSize(0.06111111);
   Graph_Rl1006->GetXaxis()->SetTitleFont(42);
   Graph_Rl1006->GetYaxis()->SetLabelFont(42);
   Graph_Rl1006->GetYaxis()->SetLabelSize(0.05);
   Graph_Rl1006->GetYaxis()->SetTitleSize(0.05);
   Graph_Rl1006->GetYaxis()->SetTitleOffset(0);
   Graph_Rl1006->GetYaxis()->SetTitleFont(42);
   Graph_Rl1006->GetZaxis()->SetLabelFont(42);
   Graph_Rl1006->GetZaxis()->SetLabelSize(0.035);
   Graph_Rl1006->GetZaxis()->SetTitleSize(0.035);
   Graph_Rl1006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Rl1006);
   
   gre->Draw("e1");
   TLatex *   tex = new TLatex(0.5,0.9,"STAR FXT #sqrt{s_{NN} } = 4.5 GeV");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.55,0.75,0.95,0.95,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/Ro","Out","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Rs","Side","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Rl","Long","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
