void figure_17()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 16:10:27 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-0.3170732,-0.02969512,2.121951,0.09103659);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLeftMargin(0.13);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.13);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[201] = {0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.7, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.4, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.6, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.9, 1.91, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2}; 
   
   TH1C *frame_5PN2__1 = new TH1C("frame_5PN2__1","",200, xAxis1);
   frame_5PN2__1->SetMinimum(-0.014);
   frame_5PN2__1->SetMaximum(0.085);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_5PN2__1->SetLineColor(ci);
   frame_5PN2__1->SetMarkerStyle(8);
   frame_5PN2__1->SetMarkerSize(0);
   frame_5PN2__1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   frame_5PN2__1->GetXaxis()->SetLabelFont(42);
   frame_5PN2__1->GetXaxis()->SetLabelSize(0.05555556);
   frame_5PN2__1->GetXaxis()->SetTitleSize(0.06111111);
   frame_5PN2__1->GetXaxis()->SetTitleOffset(0.9);
   frame_5PN2__1->GetXaxis()->SetTitleFont(42);
   frame_5PN2__1->GetYaxis()->SetTitle("v_{2}");
   frame_5PN2__1->GetYaxis()->SetLabelFont(42);
   frame_5PN2__1->GetYaxis()->SetLabelSize(0.05);
   frame_5PN2__1->GetYaxis()->SetTitleSize(0.06666667);
   frame_5PN2__1->GetYaxis()->SetTitleFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelFont(42);
   frame_5PN2__1->GetZaxis()->SetLabelSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleSize(0.035);
   frame_5PN2__1->GetZaxis()->SetTitleFont(42);
   frame_5PN2__1->Draw("p");
   
   Double_t E895_proton_v2_fx1001[5] = {
   0.497,
   0.83,
   1.169,
   1.841,
   1.508};
   Double_t E895_proton_v2_fy1001[5] = {
   0.00421,
   0.01288,
   0.02814,
   0.05372,
   0.04779};
   Double_t E895_proton_v2_fex1001[5] = {
   0,
   0,
   0,
   0,
   0};
   Double_t E895_proton_v2_fey1001[5] = {
   0.0085,
   0.0085,
   0.0085,
   0.022,
   0.01345};
   TGraphErrors *gre = new TGraphErrors(5,E895_proton_v2_fx1001,E895_proton_v2_fy1001,E895_proton_v2_fex1001,E895_proton_v2_fey1001);
   gre->SetName("E895_proton_v2");
   gre->SetTitle("Graph");

   ci = TColor::GetColor("#00aa00");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#00aa00");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(34);
   gre->SetMarkerSize(3.5);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","Graph",100,0.3626,1.9754);
   Graph_Graph1001->SetMinimum(-0.012291);
   Graph_Graph1001->SetMaximum(0.083721);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1001->SetLineColor(ci);
   Graph_Graph1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1001);
   
   gre->Draw("pe1");
   
   TH1D *hist_STAR_proton_v2__2 = new TH1D("hist_STAR_proton_v2__2","v2POIPT",6,0.35,2.3);
   hist_STAR_proton_v2__2->SetBinContent(1,0.009179362);
   hist_STAR_proton_v2__2->SetBinContent(2,0.0179024);
   hist_STAR_proton_v2__2->SetBinContent(3,0.03174829);
   hist_STAR_proton_v2__2->SetBinContent(4,0.05321014);
   hist_STAR_proton_v2__2->SetBinContent(5,0.05938818);
   hist_STAR_proton_v2__2->SetBinError(1,0.002608662);
   hist_STAR_proton_v2__2->SetBinError(2,0.003222192);
   hist_STAR_proton_v2__2->SetBinError(3,0.0051863);
   hist_STAR_proton_v2__2->SetBinError(4,0.009302766);
   hist_STAR_proton_v2__2->SetBinError(5,0.01852211);
   hist_STAR_proton_v2__2->SetMinimum(-0.01);
   hist_STAR_proton_v2__2->SetMaximum(0.12);
   hist_STAR_proton_v2__2->SetEntries(5);
   hist_STAR_proton_v2__2->SetStats(0);
   hist_STAR_proton_v2__2->SetContour(20);
   hist_STAR_proton_v2__2->SetContourLevel(0,-0.01);
   hist_STAR_proton_v2__2->SetContourLevel(1,-0.0035);
   hist_STAR_proton_v2__2->SetContourLevel(2,0.003);
   hist_STAR_proton_v2__2->SetContourLevel(3,0.0095);
   hist_STAR_proton_v2__2->SetContourLevel(4,0.016);
   hist_STAR_proton_v2__2->SetContourLevel(5,0.0225);
   hist_STAR_proton_v2__2->SetContourLevel(6,0.029);
   hist_STAR_proton_v2__2->SetContourLevel(7,0.0355);
   hist_STAR_proton_v2__2->SetContourLevel(8,0.042);
   hist_STAR_proton_v2__2->SetContourLevel(9,0.0485);
   hist_STAR_proton_v2__2->SetContourLevel(10,0.055);
   hist_STAR_proton_v2__2->SetContourLevel(11,0.0615);
   hist_STAR_proton_v2__2->SetContourLevel(12,0.068);
   hist_STAR_proton_v2__2->SetContourLevel(13,0.0745);
   hist_STAR_proton_v2__2->SetContourLevel(14,0.081);
   hist_STAR_proton_v2__2->SetContourLevel(15,0.0875);
   hist_STAR_proton_v2__2->SetContourLevel(16,0.094);
   hist_STAR_proton_v2__2->SetContourLevel(17,0.1005);
   hist_STAR_proton_v2__2->SetContourLevel(18,0.107);
   hist_STAR_proton_v2__2->SetContourLevel(19,0.1135);
   hist_STAR_proton_v2__2->SetFillStyle(0);
   hist_STAR_proton_v2__2->SetLineColor(4);
   hist_STAR_proton_v2__2->SetLineWidth(2);
   hist_STAR_proton_v2__2->SetMarkerColor(4);
   hist_STAR_proton_v2__2->SetMarkerStyle(29);
   hist_STAR_proton_v2__2->SetMarkerSize(4);
   hist_STAR_proton_v2__2->GetXaxis()->SetTitle("p_{T}[GeV/c]");
   hist_STAR_proton_v2__2->GetXaxis()->SetRange(1,6);
   hist_STAR_proton_v2__2->GetXaxis()->SetLabelFont(42);
   hist_STAR_proton_v2__2->GetXaxis()->SetLabelSize(0.055);
   hist_STAR_proton_v2__2->GetXaxis()->SetTitleSize(0.05);
   hist_STAR_proton_v2__2->GetXaxis()->SetTitleFont(42);
   hist_STAR_proton_v2__2->GetYaxis()->SetTitle("v_{2}");
   hist_STAR_proton_v2__2->GetYaxis()->SetLabelFont(42);
   hist_STAR_proton_v2__2->GetYaxis()->SetLabelSize(0.055);
   hist_STAR_proton_v2__2->GetYaxis()->SetTitleSize(0.055);
   hist_STAR_proton_v2__2->GetYaxis()->SetTitleFont(42);
   hist_STAR_proton_v2__2->GetZaxis()->SetLabelFont(42);
   hist_STAR_proton_v2__2->GetZaxis()->SetLabelSize(0.035);
   hist_STAR_proton_v2__2->GetZaxis()->SetTitleSize(0.035);
   hist_STAR_proton_v2__2->GetZaxis()->SetTitleFont(42);
   hist_STAR_proton_v2__2->Draw("same pE1X0");
   TLatex *   tex = new TLatex(0.2,0.89,"p 0-30%");
tex->SetNDC();
   tex->SetTextSize(0.07777778);
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(0,0,2,0);
   line->SetLineStyle(2);
   line->SetLineWidth(3);
   line->Draw();
   
   TLegend *leg = new TLegend(0.14,0.7,0.69,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hist_legend_d/STAR_proton_v2","0-30% STAR FXT #sqrt{s_{NN} } = 4.5 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("graph_legend_d/E895_proton_v2","12-25% E895 #sqrt{ s_{NN} } = 4.3 GeV","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00aa00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(3.5);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
