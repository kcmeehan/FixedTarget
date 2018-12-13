{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Dec 13 00:43:58 2018) by ROOT version5.34/36
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,1200,900);
   c1->Range(-1.702381,-2.166667,1.392857,14.5);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLeftMargin(0.13);
   c1->SetRightMargin(0.03);
   c1->SetTopMargin(0.03);
   c1->SetBottomMargin(0.13);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1F *hframe__1 = new TH1F("hframe__1","",1000,-1.3,1.3);
   hframe__1->SetMinimum(0);
   hframe__1->SetMaximum(14);
   hframe__1->SetDirectory(0);
   hframe__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hframe__1->SetLineColor(ci);
   hframe__1->GetXaxis()->SetTitle("y - y_{cms}");
   hframe__1->GetXaxis()->SetLabelFont(42);
   hframe__1->GetXaxis()->SetLabelSize(0.04444445);
   hframe__1->GetXaxis()->SetTitleSize(0.05555556);
   hframe__1->GetXaxis()->SetTitleFont(42);
   hframe__1->GetYaxis()->SetTitle("dN/dy");
   hframe__1->GetYaxis()->SetLabelFont(42);
   hframe__1->GetYaxis()->SetLabelSize(0.04444445);
   hframe__1->GetYaxis()->SetTitleSize(0.05555556);
   hframe__1->GetYaxis()->SetTitleFont(42);
   hframe__1->GetZaxis()->SetLabelFont(42);
   hframe__1->GetZaxis()->SetLabelSize(0.035);
   hframe__1->GetZaxis()->SetTitleSize(0.035);
   hframe__1->GetZaxis()->SetTitleFont(42);
   hframe__1->Draw(" ");
   
   TGraphErrors *gre = new TGraphErrors(5);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(8);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(5);
   gre->SetPoint(0,0.145,3.74013);
   gre->SetPointError(0,0,0.226277);
   gre->SetPoint(1,0.395,3.73098);
   gre->SetPointError(1,0,0.141396);
   gre->SetPoint(2,0.645,3.44624);
   gre->SetPointError(2,0,0.0980417);
   gre->SetPoint(3,0.895,2.6921);
   gre->SetPointError(3,0,0.0709756);
   gre->SetPoint(4,1.145,1.70831);
   gre->SetPointError(4,0,0.061831);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0.045,1.245);
   Graph_Graph1->SetMinimum(1.414486);
   Graph_Graph1->SetMaximum(4.1984);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);
   
   gre->Draw("pe1");
   
   gre = new TGraphErrors(5);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(4);
   gre->SetPoint(0,-0.145,3.74013);
   gre->SetPointError(0,0,0.136026);
   gre->SetPoint(1,-0.395,3.73098);
   gre->SetPointError(1,0,0.0928218);
   gre->SetPoint(2,-0.645,3.44624);
   gre->SetPointError(2,0,0.0604473);
   gre->SetPoint(3,-0.895,2.6921);
   gre->SetPointError(3,0,0.0468494);
   gre->SetPoint(4,-1.145,1.70831);
   gre->SetPointError(4,0,0.0443368);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Graph",100,-1.245,-0.045);
   Graph_Graph2->SetMinimum(1.442755);
   Graph_Graph2->SetMaximum(4.097374);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph2);
   
   gre->Draw("pe1 ");
   
   gre = new TGraphErrors(10);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(4);
   gre->SetPoint(0,0.145,3.74013);
   gre->SetPointError(0,0,0.136026);
   gre->SetPoint(1,0.395,3.73098);
   gre->SetPointError(1,0,0.0928218);
   gre->SetPoint(2,0.645,3.44624);
   gre->SetPointError(2,0,0.0604473);
   gre->SetPoint(3,0.895,2.6921);
   gre->SetPointError(3,0,0.0468494);
   gre->SetPoint(4,1.145,1.70831);
   gre->SetPointError(4,0,0.0443368);
   gre->SetPoint(5,-0.145,3.74013);
   gre->SetPointError(5,0,0.136026);
   gre->SetPoint(6,-0.395,3.73098);
   gre->SetPointError(6,0,0.0928218);
   gre->SetPoint(7,-0.645,3.44624);
   gre->SetPointError(7,0,0.0604473);
   gre->SetPoint(8,-0.895,2.6921);
   gre->SetPointError(8,0,0.0468494);
   gre->SetPoint(9,-1.145,1.70831);
   gre->SetPointError(9,0,0.0443368);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Graph",100,-1.374,1.374);
   Graph_Graph3->SetMinimum(1.442755);
   Graph_Graph3->SetMaximum(4.097374);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3->SetLineColor(ci);
   Graph_Graph3->GetXaxis()->SetLabelFont(42);
   Graph_Graph3->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetXaxis()->SetTitleFont(42);
   Graph_Graph3->GetYaxis()->SetLabelFont(42);
   Graph_Graph3->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetYaxis()->SetTitleFont(42);
   Graph_Graph3->GetZaxis()->SetLabelFont(42);
   Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph3);
   
   gre->Draw("pe1 ");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,0.1142,7.7778);
   gre->SetPointError(0,0,0.4378);
   gre->SetPoint(1,0.3059,7.8177);
   gre->SetPointError(1,0,0.2792);
   gre->SetPoint(2,0.5251,7.1396);
   gre->SetPointError(2,0,0.2393);
   gre->SetPoint(3,0.7169,6.2621);
   gre->SetPointError(3,0,0.2792);
   
   TH1F *Graph_Graph4 = new TH1F("Graph_Graph4","Graph",100,0.05393,0.77717);
   Graph_Graph4->SetMinimum(5.75963);
   Graph_Graph4->SetMaximum(8.43887);
   Graph_Graph4->SetDirectory(0);
   Graph_Graph4->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph4->SetLineColor(ci);
   Graph_Graph4->GetXaxis()->SetLabelFont(42);
   Graph_Graph4->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetXaxis()->SetTitleFont(42);
   Graph_Graph4->GetYaxis()->SetLabelFont(42);
   Graph_Graph4->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetYaxis()->SetTitleFont(42);
   Graph_Graph4->GetZaxis()->SetLabelFont(42);
   Graph_Graph4->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph4->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph4);
   
   gre->Draw("pe1");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph4");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,-0.1142,7.7778);
   gre->SetPointError(0,0,0.4378);
   gre->SetPoint(1,-0.3059,7.8177);
   gre->SetPointError(1,0,0.2792);
   gre->SetPoint(2,-0.5251,7.1396);
   gre->SetPointError(2,0,0.2393);
   gre->SetPoint(3,-0.7169,6.2621);
   gre->SetPointError(3,0,0.2792);
   
   TH1F *Graph_Graph5 = new TH1F("Graph_Graph5","Graph",100,-0.77717,-0.05393);
   Graph_Graph5->SetMinimum(5.75963);
   Graph_Graph5->SetMaximum(8.43887);
   Graph_Graph5->SetDirectory(0);
   Graph_Graph5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph5->SetLineColor(ci);
   Graph_Graph5->GetXaxis()->SetLabelFont(42);
   Graph_Graph5->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetXaxis()->SetTitleFont(42);
   Graph_Graph5->GetYaxis()->SetLabelFont(42);
   Graph_Graph5->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetYaxis()->SetTitleFont(42);
   Graph_Graph5->GetZaxis()->SetLabelFont(42);
   Graph_Graph5->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph5->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph5);
   
   gre->Draw("pe1 ");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,0.1101,1.3029);
   gre->SetPointError(0,0,0.5378);
   gre->SetPoint(1,0.3028,1.2225);
   gre->SetPointError(1,0,0.2792);
   gre->SetPoint(2,0.4954,1.0777);
   gre->SetPointError(2,0,0.4393);
   gre->SetPoint(3,0.7064,0.8123);
   gre->SetPointError(3,0,0.3792);
   
   TH1F *Graph_Graph6 = new TH1F("Graph_Graph6","Graph",100,0.05047,0.76603);
   Graph_Graph6->SetMinimum(0.29234);
   Graph_Graph6->SetMaximum(1.98146);
   Graph_Graph6->SetDirectory(0);
   Graph_Graph6->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph6->SetLineColor(ci);
   Graph_Graph6->GetXaxis()->SetLabelFont(42);
   Graph_Graph6->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetXaxis()->SetTitleFont(42);
   Graph_Graph6->GetYaxis()->SetLabelFont(42);
   Graph_Graph6->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetYaxis()->SetTitleFont(42);
   Graph_Graph6->GetZaxis()->SetLabelFont(42);
   Graph_Graph6->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph6->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph6);
   
   gre->Draw("pe1");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph6");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,-0.1101,1.3029);
   gre->SetPointError(0,0,0.5378);
   gre->SetPoint(1,-0.3028,1.2225);
   gre->SetPointError(1,0,0.2792);
   gre->SetPoint(2,-0.4954,1.0777);
   gre->SetPointError(2,0,0.4393);
   gre->SetPoint(3,-0.7064,0.8123);
   gre->SetPointError(3,0,0.3792);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","Graph",100,-0.76603,-0.05047);
   Graph_Graph7->SetMinimum(0.29234);
   Graph_Graph7->SetMaximum(1.98146);
   Graph_Graph7->SetDirectory(0);
   Graph_Graph7->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph7->SetLineColor(ci);
   Graph_Graph7->GetXaxis()->SetLabelFont(42);
   Graph_Graph7->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetXaxis()->SetTitleFont(42);
   Graph_Graph7->GetYaxis()->SetLabelFont(42);
   Graph_Graph7->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetYaxis()->SetTitleFont(42);
   Graph_Graph7->GetZaxis()->SetLabelFont(42);
   Graph_Graph7->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph7->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph7);
   
   gre->Draw("pe1 ");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph7");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,0.11215,4.54035);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,0.30435,4.5201);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,0.51025,4.10865);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,0.71165,3.5372);
   gre->SetPointError(3,0,0);
   
   TH1F *Graph_Graph8 = new TH1F("Graph_Graph8","Graph",100,0.0522,0.7716);
   Graph_Graph8->SetMinimum(3.436885);
   Graph_Graph8->SetMaximum(4.640665);
   Graph_Graph8->SetDirectory(0);
   Graph_Graph8->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph8->SetLineColor(ci);
   Graph_Graph8->GetXaxis()->SetLabelFont(42);
   Graph_Graph8->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetXaxis()->SetTitleFont(42);
   Graph_Graph8->GetYaxis()->SetLabelFont(42);
   Graph_Graph8->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetYaxis()->SetTitleFont(42);
   Graph_Graph8->GetZaxis()->SetLabelFont(42);
   Graph_Graph8->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph8->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph8->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph8);
   
   gre->Draw("pe1 ");
   
   gre = new TGraphErrors(4);
   gre->SetName("Graph8");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(4);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,-0.11215,4.54035);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,-0.30435,4.5201);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,-0.51025,4.10865);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,-0.71165,3.5372);
   gre->SetPointError(3,0,0);
   
   TH1F *Graph_Graph9 = new TH1F("Graph_Graph9","Graph",100,-0.7716,-0.0522);
   Graph_Graph9->SetMinimum(3.436885);
   Graph_Graph9->SetMaximum(4.640665);
   Graph_Graph9->SetDirectory(0);
   Graph_Graph9->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph9->SetLineColor(ci);
   Graph_Graph9->GetXaxis()->SetLabelFont(42);
   Graph_Graph9->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetXaxis()->SetTitleFont(42);
   Graph_Graph9->GetYaxis()->SetLabelFont(42);
   Graph_Graph9->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetYaxis()->SetTitleFont(42);
   Graph_Graph9->GetZaxis()->SetLabelFont(42);
   Graph_Graph9->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph9->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph9);
   
   gre->Draw("pe1 ");
   
   TLegend *leg = new TLegend(0.12,0.65,0.92,0.96,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.055);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("NULL","K^{0}_{S} STAR FXT #sqrt{s_{NN}} = 4.5 GeV","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(22);
   entry=leg->AddEntry("NULL","K^{+} E917 #sqrt{s_{NN}} = 4.3 GeV","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(3);
   entry->SetTextFont(22);
   entry=leg->AddEntry("NULL","K^{-} E917 #sqrt{s_{NN}} = 4.3 GeV","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(3);
   entry->SetTextFont(22);
   entry=leg->AddEntry("NULL","(K^{+}+K^{-})/2 E917 #sqrt{s_{NN}} = 4.3 GeV","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(3);
   entry->SetTextFont(22);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
