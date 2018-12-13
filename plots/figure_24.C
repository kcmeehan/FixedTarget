void figure_24()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 15:58:30 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,1200);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(2.048333,2.071429,9.215,9.214286);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLeftMargin(0.13);
   c->SetRightMargin(0.03);
   c->SetTopMargin(0.03);
   c->SetBottomMargin(0.13);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {2, 2.07, 2.14, 2.21, 2.28, 2.35, 2.42, 2.49, 2.56, 2.63, 2.7, 2.77, 2.84, 2.91, 2.98, 3.05, 3.12, 3.19, 3.26, 3.33, 3.4, 3.47, 3.54, 3.61, 3.68, 3.75, 3.82, 3.89, 3.96, 4.03, 4.1, 4.17, 4.24, 4.31, 4.38, 4.45, 4.52, 4.59, 4.66, 4.73, 4.8, 4.87, 4.94, 5.01, 5.08, 5.15, 5.22, 5.29, 5.36, 5.43, 5.5, 5.57, 5.64, 5.71, 5.78, 5.85, 5.92, 5.99, 6.06, 6.13, 6.2, 6.27, 6.34, 6.41, 6.48, 6.55, 6.62, 6.69, 6.76, 6.83, 6.9, 6.97, 7.04, 7.11, 7.18, 7.25, 7.32, 7.39, 7.46, 7.53, 7.6, 7.67, 7.74, 7.81, 7.88, 7.95, 8.02, 8.09, 8.16, 8.23, 8.3, 8.37, 8.44, 8.51, 8.58, 8.65, 8.72, 8.79, 8.86, 8.93, 9}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",100, xAxis1);
   frame_5PN2__1->SetMinimum(3);
   frame_5PN2__1->SetMaximum(9);
   frame_5PN2__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetTitle("R_{long} (fm)");
   frame_5PN2__1->GetXaxis()->SetRange(15,100);
   frame_5PN2__1->GetXaxis()->SetNdivisions(1710);
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.05);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.06111111);
   frame_5PN2__1->GetXaxis()->SetTitleOffset(0.9);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("R_{side} (fm)");
   frame_5PN2__1->GetYaxis()->SetNdivisions(1710);
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.05);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.06111111);
   frame_5PN2__1->GetYaxis()->SetTitleOffset(0.8);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t Graph1_fx1001[4] = {
   5.15,
   5.15,
   4.72,
   4.64};
   Double_t Graph1_fy1001[4] = {
   6.28,
   5.37,
   5.05,
   4.83};
   Double_t Graph1_fex1001[4] = {
   0.19,
   0.14,
   0.18,
   0.24};
   Double_t Graph1_fey1001[4] = {
   0.2,
   0.11,
   0.12,
   0.21};
   TGraphErrors *gre = new TGraphErrors(4,Graph1_fx1001,Graph1_fy1001,Graph1_fex1001,Graph1_fey1001);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#149718");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#149718");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph11001 = new TH1F("Graph_Graph11001","Graph",100,4.306,5.434);
   Graph_Graph11001->SetMinimum(4.434);
   Graph_Graph11001->SetMaximum(6.666);
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
   
   gre->Draw(" pe");
   
   Double_t Graph2_fx1002[1] = {
   3.61};
   Double_t Graph2_fy1002[1] = {
   4.55};
   Double_t Graph2_fex1002[1] = {
   0.3};
   Double_t Graph2_fey1002[1] = {
   0.42};
   gre = new TGraphErrors(1,Graph2_fx1002,Graph2_fy1002,Graph2_fex1002,Graph2_fey1002);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(22);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph21002 = new TH1F("Graph_Graph21002","Graph",100,3.25,3.97);
   Graph_Graph21002->SetMinimum(4.046);
   Graph_Graph21002->SetMaximum(5.054);
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
   
   gre->Draw(" pe");
   
   Double_t Graph3_fx1003[1] = {
   4.488739};
   Double_t Graph3_fy1003[1] = {
   4.61359};
   Double_t Graph3_fex1003[1] = {
   0.09784946};
   Double_t Graph3_fey1003[1] = {
   0.09210153};
   gre = new TGraphErrors(1,Graph3_fx1003,Graph3_fy1003,Graph3_fex1003,Graph3_fey1003);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph31003 = new TH1F("Graph_Graph31003","Graph",100,4.37132,4.606158);
   Graph_Graph31003->SetMinimum(4.503068);
   Graph_Graph31003->SetMaximum(4.724112);
   Graph_Graph31003->SetDirectory(0);
   Graph_Graph31003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31003->SetLineColor(ci);
   Graph_Graph31003->GetXaxis()->SetLabelFont(42);
   Graph_Graph31003->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph31003->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph31003->GetXaxis()->SetTitleFont(42);
   Graph_Graph31003->GetYaxis()->SetLabelFont(42);
   Graph_Graph31003->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph31003->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph31003->GetYaxis()->SetTitleOffset(0);
   Graph_Graph31003->GetYaxis()->SetTitleFont(42);
   Graph_Graph31003->GetZaxis()->SetLabelFont(42);
   Graph_Graph31003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph31003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph31003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31003);
   
   gre->Draw(" pe");
   
   Double_t Graph4_fx1004[7] = {
   5.01443,
   5.42759,
   5.7974,
   5.98998,
   6.18026,
   6.32953,
   6.64397};
   Double_t Graph4_fy1004[7] = {
   4.93449,
   4.78635,
   4.83625,
   4.8907,
   4.96732,
   5.00157,
   5.20713};
   Double_t Graph4_fex1004[7] = {
   0.113695,
   0.0701463,
   0.0472674,
   0.0350745,
   0.0780461,
   0.0662081,
   0.0688818};
   Double_t Graph4_fey1004[7] = {
   0.0966063,
   0.0507441,
   0.0332015,
   0.0242054,
   0.0496485,
   0.041259,
   0.042596};
   gre = new TGraphErrors(7,Graph4_fx1004,Graph4_fy1004,Graph4_fex1004,Graph4_fey1004);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph41004 = new TH1F("Graph_Graph41004","Graph",100,4.719523,6.894063);
   Graph_Graph41004->SetMinimum(4.684194);
   Graph_Graph41004->SetMaximum(5.301138);
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
   
   gre->Draw(" pe");
   
   Double_t Graph5_fx1005[1] = {
   8.03};
   Double_t Graph5_fy1005[1] = {
   6.36};
   Double_t Graph5_fex1005[1] = {
   0.57};
   Double_t Graph5_fey1005[1] = {
   0.66};
   gre = new TGraphErrors(1,Graph5_fx1005,Graph5_fy1005,Graph5_fex1005,Graph5_fey1005);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(33);
   gre->SetMarkerSize(4);
   
   TH1F *Graph_Graph51005 = new TH1F("Graph_Graph51005","Graph",100,7.346,8.714);
   Graph_Graph51005->SetMinimum(5.568);
   Graph_Graph51005->SetMaximum(7.152);
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
   
   gre->Draw(" pe");
   TLatex *   tex = new TLatex(5.5,4.4,"7.7 - 200");
   tex->SetTextAlign(13);
   tex->SetTextSize(0.03888889);
   tex->SetTextAngle(12);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(3.2,5.2,"4.9");
   tex->SetTextAlign(13);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(4.5,4.5,"4.5");
   tex->SetTextAlign(13);
   tex->SetTextColor(2);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(8.25,6.8,"2760");
   tex->SetTextAlign(13);
   tex->SetTextColor(4);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(3.9,5.3,"2.7 - 4.3");
   tex->SetTextAlign(13);

   ci = TColor::GetColor("#149718");
   tex->SetTextColor(ci);
   tex->SetTextSize(0.03888889);
   tex->SetTextAngle(65);
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(3,3,9,9);
   line->SetLineColor(4);
   line->SetLineStyle(2);
   line->SetLineWidth(3);
   line->Draw();
   
   TLegend *leg = new TLegend(0.15,0.66,0.45,0.96,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04444445);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1000);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/Graph1","E895","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#149718");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph2","E866","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(22);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph3","STAR FXT","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph4","STAR BES","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/Graph5","ALICE","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(33);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
