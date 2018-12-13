{
//=========Macro generated from canvas: c/c
//=========  (Thu Dec 13 00:49:09 2018) by ROOT version5.34/36
   TCanvas *c = new TCanvas("c", "c",35,45,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-0.4496138,-0.1375,2.547811,0.1125);
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
   
   TH1F *hist_Plot1 = new TH1F("hist_Plot1","",10,1,250);
   hist_Plot1->SetMinimum(-0.1);
   hist_Plot1->SetMaximum(0.1);
   hist_Plot1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hist_Plot1->SetLineColor(ci);
   hist_Plot1->GetXaxis()->SetTitle("#sqrt{s_{NN}} (GeV)");
   hist_Plot1->GetXaxis()->CenterTitle(true);
   hist_Plot1->GetXaxis()->SetMoreLogLabels();
   hist_Plot1->GetXaxis()->SetNoExponent();
   hist_Plot1->GetXaxis()->SetNdivisions(1404);
   hist_Plot1->GetXaxis()->SetLabelFont(42);
   hist_Plot1->GetXaxis()->SetLabelSize(0.06);
   hist_Plot1->GetXaxis()->SetTitleSize(0.07);
   hist_Plot1->GetXaxis()->SetTitleOffset(0.9);
   hist_Plot1->GetXaxis()->SetTitleFont(42);
   hist_Plot1->GetYaxis()->SetTitle("v_{2}");
   hist_Plot1->GetYaxis()->CenterTitle(true);
   hist_Plot1->GetYaxis()->SetNdivisions(204);
   hist_Plot1->GetYaxis()->SetLabelFont(42);
   hist_Plot1->GetYaxis()->SetLabelOffset(0.01);
   hist_Plot1->GetYaxis()->SetLabelSize(0.06);
   hist_Plot1->GetYaxis()->SetTitleSize(0.07);
   hist_Plot1->GetYaxis()->SetTitleOffset(0.8);
   hist_Plot1->GetYaxis()->SetTitleFont(42);
   hist_Plot1->GetZaxis()->SetLabelFont(42);
   hist_Plot1->GetZaxis()->SetLabelSize(0.035);
   hist_Plot1->GetZaxis()->SetTitleSize(0.035);
   hist_Plot1->GetZaxis()->SetTitleFont(42);
   hist_Plot1->Draw("P9");
   
   TGraphErrors *gre = new TGraphErrors(10);
   gre->SetName("FOPI");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(32);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,1.907,0.071);
   gre->SetPointError(0,0,0.008);
   gre->SetPoint(1,1.922,0.03);
   gre->SetPointError(1,0,0.005);
   gre->SetPoint(2,1.936,-0.01);
   gre->SetPointError(2,0,0.004);
   gre->SetPoint(3,1.984,-0.058);
   gre->SetPointError(3,0,0.007);
   gre->SetPoint(4,2.053,-0.08);
   gre->SetPointError(4,0,0.012);
   gre->SetPoint(5,2.142,-0.062);
   gre->SetPointError(5,0,0.007);
   gre->SetPoint(6,2.227,-0.061);
   gre->SetPointError(6,0,0.007);
   gre->SetPoint(7,2.309,-0.057);
   gre->SetPointError(7,0,0.007);
   gre->SetPoint(8,2.389,-0.052);
   gre->SetPointError(8,0,0.007);
   gre->SetPoint(9,2.503,-0.041);
   gre->SetPointError(9,0,0.007);
   
   TH1F *Graph_FOPI1 = new TH1F("Graph_FOPI1","Graph",100,1.8474,2.5626);
   Graph_FOPI1->SetMinimum(-0.1091);
   Graph_FOPI1->SetMaximum(0.0961);
   Graph_FOPI1->SetDirectory(0);
   Graph_FOPI1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_FOPI1->SetLineColor(ci);
   Graph_FOPI1->GetXaxis()->SetLabelFont(42);
   Graph_FOPI1->GetXaxis()->SetLabelSize(0.035);
   Graph_FOPI1->GetXaxis()->SetTitleSize(0.035);
   Graph_FOPI1->GetXaxis()->SetTitleFont(42);
   Graph_FOPI1->GetYaxis()->SetLabelFont(42);
   Graph_FOPI1->GetYaxis()->SetLabelSize(0.035);
   Graph_FOPI1->GetYaxis()->SetTitleSize(0.035);
   Graph_FOPI1->GetYaxis()->SetTitleFont(42);
   Graph_FOPI1->GetZaxis()->SetLabelFont(42);
   Graph_FOPI1->GetZaxis()->SetLabelSize(0.035);
   Graph_FOPI1->GetZaxis()->SetTitleSize(0.035);
   Graph_FOPI1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_FOPI1);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(10);
   gre->SetName("EOS");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,2.369,-0.065);
   gre->SetPointError(0,0,0.007);
   gre->SetPoint(1,2.683,-0.047);
   gre->SetPointError(1,0,0.005);
   gre->SetPoint(2,3.305,-0.002);
   gre->SetPointError(2,0,0.004);
   gre->SetPoint(3,3.827,0.016);
   gre->SetPointError(3,0,0.003);
   gre->SetPoint(4,4.287,0.019);
   gre->SetPointError(4,0,0.006);
   gre->SetPoint(5,4.857,0.022);
   gre->SetPointError(5,0,0.005);
   gre->SetPoint(6,1.907,0);
   gre->SetPointError(6,0,4.172013e-308);
   gre->SetPoint(7,1.922,4.940656e-324);
   gre->SetPointError(7,0,6.932234e-310);
   gre->SetPoint(8,1.936,6.932236e-310);
   gre->SetPointError(8,0,1.253198e-319);
   gre->SetPoint(9,1.984,2.959453e-321);
   gre->SetPointError(9,0,6.95327e-310);
   
   TH1F *Graph_EOS2 = new TH1F("Graph_EOS2","Graph",100,1.612,5.152);
   Graph_EOS2->SetMinimum(-0.0819);
   Graph_EOS2->SetMaximum(0.0369);
   Graph_EOS2->SetDirectory(0);
   Graph_EOS2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_EOS2->SetLineColor(ci);
   Graph_EOS2->GetXaxis()->SetLabelFont(42);
   Graph_EOS2->GetXaxis()->SetLabelSize(0.035);
   Graph_EOS2->GetXaxis()->SetTitleSize(0.035);
   Graph_EOS2->GetXaxis()->SetTitleFont(42);
   Graph_EOS2->GetYaxis()->SetLabelFont(42);
   Graph_EOS2->GetYaxis()->SetLabelSize(0.035);
   Graph_EOS2->GetYaxis()->SetTitleSize(0.035);
   Graph_EOS2->GetYaxis()->SetTitleFont(42);
   Graph_EOS2->GetZaxis()->SetLabelFont(42);
   Graph_EOS2->GetZaxis()->SetLabelSize(0.035);
   Graph_EOS2->GetZaxis()->SetTitleSize(0.035);
   Graph_EOS2->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_EOS2);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(3);
   gre->SetName("CERES");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(27);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,8.84,0.028);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,12.36,0.037);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,17.26,0.043);
   gre->SetPointError(2,0,0);
   
   TH1F *Graph_CERES3 = new TH1F("Graph_CERES3","Graph",100,7.998,18.102);
   Graph_CERES3->SetMinimum(0.0265);
   Graph_CERES3->SetMaximum(0.0445);
   Graph_CERES3->SetDirectory(0);
   Graph_CERES3->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_CERES3->SetLineColor(ci);
   Graph_CERES3->GetXaxis()->SetLabelFont(42);
   Graph_CERES3->GetXaxis()->SetLabelSize(0.035);
   Graph_CERES3->GetXaxis()->SetTitleSize(0.035);
   Graph_CERES3->GetXaxis()->SetTitleFont(42);
   Graph_CERES3->GetYaxis()->SetLabelFont(42);
   Graph_CERES3->GetYaxis()->SetLabelSize(0.035);
   Graph_CERES3->GetYaxis()->SetTitleSize(0.035);
   Graph_CERES3->GetYaxis()->SetTitleFont(42);
   Graph_CERES3->GetZaxis()->SetLabelFont(42);
   Graph_CERES3->GetZaxis()->SetLabelSize(0.035);
   Graph_CERES3->GetZaxis()->SetTitleSize(0.035);
   Graph_CERES3->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_CERES3);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("NA49");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(28);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,8.84,0.024);
   gre->SetPointError(0,0,0.003);
   gre->SetPoint(1,17.26,0.034);
   gre->SetPointError(1,0,0.001);
   
   TH1F *Graph_NA494 = new TH1F("Graph_NA494","Graph",100,7.998,18.102);
   Graph_NA494->SetMinimum(0.0196);
   Graph_NA494->SetMaximum(0.0364);
   Graph_NA494->SetDirectory(0);
   Graph_NA494->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_NA494->SetLineColor(ci);
   Graph_NA494->GetXaxis()->SetLabelFont(42);
   Graph_NA494->GetXaxis()->SetLabelSize(0.035);
   Graph_NA494->GetXaxis()->SetTitleSize(0.035);
   Graph_NA494->GetXaxis()->SetTitleFont(42);
   Graph_NA494->GetYaxis()->SetLabelFont(42);
   Graph_NA494->GetYaxis()->SetLabelSize(0.035);
   Graph_NA494->GetYaxis()->SetTitleSize(0.035);
   Graph_NA494->GetYaxis()->SetTitleFont(42);
   Graph_NA494->GetZaxis()->SetLabelFont(42);
   Graph_NA494->GetZaxis()->SetLabelSize(0.035);
   Graph_NA494->GetZaxis()->SetTitleSize(0.035);
   Graph_NA494->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_NA494);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(9);
   gre->SetName("STARp");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,7.7,0.0357);
   gre->SetPointError(0,0,0.0009);
   gre->SetPoint(1,11.5,0.0402);
   gre->SetPointError(1,0,0.0005);
   gre->SetPoint(2,14.5,0.0412);
   gre->SetPointError(2,0,0.0005);
   gre->SetPoint(3,19.6,0.0412);
   gre->SetPointError(3,0,0.0003);
   gre->SetPoint(4,27,0.0412);
   gre->SetPointError(4,0,0.0002);
   gre->SetPoint(5,39,0.0431);
   gre->SetPointError(5,0,0.0002);
   gre->SetPoint(6,62.4,0.0527);
   gre->SetPointError(6,0,0.0002);
   gre->SetPoint(7,125,0.0395);
   gre->SetPointError(7,0,0.006);
   gre->SetPoint(8,6.932236e-310,0.0009);
   gre->SetPointError(8,0,-2.315842e+77);
   
   TH1F *Graph_STARp5 = new TH1F("Graph_STARp5","Graph",100,6.239012e-310,137.5);
   Graph_STARp5->SetMinimum(0);
   Graph_STARp5->SetMaximum(0.0581);
   Graph_STARp5->SetDirectory(0);
   Graph_STARp5->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_STARp5->SetLineColor(ci);
   Graph_STARp5->GetXaxis()->SetLabelFont(42);
   Graph_STARp5->GetXaxis()->SetLabelSize(0.035);
   Graph_STARp5->GetXaxis()->SetTitleSize(0.035);
   Graph_STARp5->GetXaxis()->SetTitleFont(42);
   Graph_STARp5->GetYaxis()->SetLabelFont(42);
   Graph_STARp5->GetYaxis()->SetLabelSize(0.035);
   Graph_STARp5->GetYaxis()->SetTitleSize(0.035);
   Graph_STARp5->GetYaxis()->SetTitleFont(42);
   Graph_STARp5->GetZaxis()->SetLabelFont(42);
   Graph_STARp5->GetZaxis()->SetLabelSize(0.035);
   Graph_STARp5->GetZaxis()->SetTitleSize(0.035);
   Graph_STARp5->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_STARp5);
   
   gre->Draw("p9");
   
   gre = new TGraphErrors(9);
   gre->SetName("STAR");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff00ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,7.7,0.0334);
   gre->SetPointError(0,0,0.0005);
   gre->SetPoint(1,11.5,0.0348);
   gre->SetPointError(1,0,0.0002);
   gre->SetPoint(2,14.5,0.0365);
   gre->SetPointError(2,0,0.0002);
   gre->SetPoint(3,19.6,0.0355);
   gre->SetPointError(3,0,0.0001);
   gre->SetPoint(4,27,0.0366);
   gre->SetPointError(4,0,0.0001);
   gre->SetPoint(5,39,0.0381);
   gre->SetPointError(5,0,0.0001);
   gre->SetPoint(6,62.4,0.0387);
   gre->SetPointError(6,0,0.0001);
   gre->SetPoint(7,135,0.03985);
   gre->SetPointError(7,0,0.001);
   gre->SetPoint(8,0.0334,0.0005);
   gre->SetPointError(8,0,2.239095e-314);
   
   TH1F *Graph_STAR6 = new TH1F("Graph_STAR6","Graph",100,0.03006,148.4967);
   Graph_STAR6->SetMinimum(0);
   Graph_STAR6->SetMaximum(0.044885);
   Graph_STAR6->SetDirectory(0);
   Graph_STAR6->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_STAR6->SetLineColor(ci);
   Graph_STAR6->GetXaxis()->SetLabelFont(42);
   Graph_STAR6->GetXaxis()->SetLabelSize(0.035);
   Graph_STAR6->GetXaxis()->SetTitleSize(0.035);
   Graph_STAR6->GetXaxis()->SetTitleFont(42);
   Graph_STAR6->GetYaxis()->SetLabelFont(42);
   Graph_STAR6->GetYaxis()->SetLabelSize(0.035);
   Graph_STAR6->GetYaxis()->SetTitleSize(0.035);
   Graph_STAR6->GetYaxis()->SetTitleFont(42);
   Graph_STAR6->GetZaxis()->SetLabelFont(42);
   Graph_STAR6->GetZaxis()->SetLabelSize(0.035);
   Graph_STAR6->GetZaxis()->SetTitleSize(0.035);
   Graph_STAR6->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_STAR6);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("PHENIXp");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,64.4,0.045);
   gre->SetPointError(0,0,0.005);
   gre->SetPoint(1,200,0.06);
   gre->SetPointError(1,0,0.008);
   
   TH1F *Graph_PHENIXp7 = new TH1F("Graph_PHENIXp7","Graph",100,50.84,213.56);
   Graph_PHENIXp7->SetMinimum(0.0372);
   Graph_PHENIXp7->SetMaximum(0.0708);
   Graph_PHENIXp7->SetDirectory(0);
   Graph_PHENIXp7->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PHENIXp7->SetLineColor(ci);
   Graph_PHENIXp7->GetXaxis()->SetLabelFont(42);
   Graph_PHENIXp7->GetXaxis()->SetLabelSize(0.035);
   Graph_PHENIXp7->GetXaxis()->SetTitleSize(0.035);
   Graph_PHENIXp7->GetXaxis()->SetTitleFont(42);
   Graph_PHENIXp7->GetYaxis()->SetLabelFont(42);
   Graph_PHENIXp7->GetYaxis()->SetLabelSize(0.035);
   Graph_PHENIXp7->GetYaxis()->SetTitleSize(0.035);
   Graph_PHENIXp7->GetYaxis()->SetTitleFont(42);
   Graph_PHENIXp7->GetZaxis()->SetLabelFont(42);
   Graph_PHENIXp7->GetZaxis()->SetLabelSize(0.035);
   Graph_PHENIXp7->GetZaxis()->SetTitleSize(0.035);
   Graph_PHENIXp7->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_PHENIXp7);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("PHENIXpi");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(4);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,60.4,0.04);
   gre->SetPointError(0,0,0.002);
   gre->SetPoint(1,200,0.04);
   gre->SetPointError(1,0,0.002);
   
   TH1F *Graph_PHENIXpi8 = new TH1F("Graph_PHENIXpi8","Graph",100,46.44,213.96);
   Graph_PHENIXpi8->SetMinimum(0.0376);
   Graph_PHENIXpi8->SetMaximum(0.0424);
   Graph_PHENIXpi8->SetDirectory(0);
   Graph_PHENIXpi8->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PHENIXpi8->SetLineColor(ci);
   Graph_PHENIXpi8->GetXaxis()->SetLabelFont(42);
   Graph_PHENIXpi8->GetXaxis()->SetLabelSize(0.035);
   Graph_PHENIXpi8->GetXaxis()->SetTitleSize(0.035);
   Graph_PHENIXpi8->GetXaxis()->SetTitleFont(42);
   Graph_PHENIXpi8->GetYaxis()->SetLabelFont(42);
   Graph_PHENIXpi8->GetYaxis()->SetLabelSize(0.035);
   Graph_PHENIXpi8->GetYaxis()->SetTitleSize(0.035);
   Graph_PHENIXpi8->GetYaxis()->SetTitleFont(42);
   Graph_PHENIXpi8->GetZaxis()->SetLabelFont(42);
   Graph_PHENIXpi8->GetZaxis()->SetLabelSize(0.035);
   Graph_PHENIXpi8->GetZaxis()->SetTitleSize(0.035);
   Graph_PHENIXpi8->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_PHENIXpi8);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(4);
   gre->SetName("PHOBOS");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(26);
   gre->SetMarkerSize(3);
   gre->SetPoint(0,19.6,0.033);
   gre->SetPointError(0,0,0.005);
   gre->SetPoint(1,58.4,0.044);
   gre->SetPointError(1,0,0.003);
   gre->SetPoint(2,130,0.048);
   gre->SetPointError(2,0,0.003);
   gre->SetPoint(3,200,0.052);
   gre->SetPointError(3,0,0.003);
   
   TH1F *Graph_PHOBOS9 = new TH1F("Graph_PHOBOS9","Graph",100,1.56,218.04);
   Graph_PHOBOS9->SetMinimum(0.0253);
   Graph_PHOBOS9->SetMaximum(0.0577);
   Graph_PHOBOS9->SetDirectory(0);
   Graph_PHOBOS9->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_PHOBOS9->SetLineColor(ci);
   Graph_PHOBOS9->GetXaxis()->SetLabelFont(42);
   Graph_PHOBOS9->GetXaxis()->SetLabelSize(0.035);
   Graph_PHOBOS9->GetXaxis()->SetTitleSize(0.035);
   Graph_PHOBOS9->GetXaxis()->SetTitleFont(42);
   Graph_PHOBOS9->GetYaxis()->SetLabelFont(42);
   Graph_PHOBOS9->GetYaxis()->SetLabelSize(0.035);
   Graph_PHOBOS9->GetYaxis()->SetTitleSize(0.035);
   Graph_PHOBOS9->GetYaxis()->SetTitleFont(42);
   Graph_PHOBOS9->GetZaxis()->SetLabelFont(42);
   Graph_PHOBOS9->GetZaxis()->SetLabelSize(0.035);
   Graph_PHOBOS9->GetZaxis()->SetTitleSize(0.035);
   Graph_PHOBOS9->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_PHOBOS9);
   
   gre->Draw(" p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("FXT _p");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,4.6,0.02831);
   gre->SetPointError(1,0,0.006);
   
   TH1F *Graph_FXT _p10 = new TH1F("Graph_FXT _p10","Graph",100,0.00506,5.06);
   Graph_FXT _p10->SetMinimum(0);
   Graph_FXT _p10->SetMaximum(0.037741);
   Graph_FXT _p10->SetDirectory(0);
   Graph_FXT _p10->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_FXT _p10->SetLineColor(ci);
   Graph_FXT _p10->GetXaxis()->SetLabelFont(42);
   Graph_FXT _p10->GetXaxis()->SetLabelSize(0.035);
   Graph_FXT _p10->GetXaxis()->SetTitleSize(0.035);
   Graph_FXT _p10->GetXaxis()->SetTitleFont(42);
   Graph_FXT _p10->GetYaxis()->SetLabelFont(42);
   Graph_FXT _p10->GetYaxis()->SetLabelSize(0.035);
   Graph_FXT _p10->GetYaxis()->SetTitleSize(0.035);
   Graph_FXT _p10->GetYaxis()->SetTitleFont(42);
   Graph_FXT _p10->GetZaxis()->SetLabelFont(42);
   Graph_FXT _p10->GetZaxis()->SetLabelSize(0.035);
   Graph_FXT _p10->GetZaxis()->SetTitleSize(0.035);
   Graph_FXT _p10->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_FXT _p10);
   
   gre->Draw("p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("FXT_pi");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#009900");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(4);
   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,4.4,0.02355);
   gre->SetPointError(1,0,0.00388);
   
   TH1F *Graph_FXT_pi11 = new TH1F("Graph_FXT_pi11","Graph",100,0.00484,4.84);
   Graph_FXT_pi11->SetMinimum(0);
   Graph_FXT_pi11->SetMaximum(0.030173);
   Graph_FXT_pi11->SetDirectory(0);
   Graph_FXT_pi11->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_FXT_pi11->SetLineColor(ci);
   Graph_FXT_pi11->GetXaxis()->SetLabelFont(42);
   Graph_FXT_pi11->GetXaxis()->SetLabelSize(0.035);
   Graph_FXT_pi11->GetXaxis()->SetTitleSize(0.035);
   Graph_FXT_pi11->GetXaxis()->SetTitleFont(42);
   Graph_FXT_pi11->GetYaxis()->SetLabelFont(42);
   Graph_FXT_pi11->GetYaxis()->SetLabelSize(0.035);
   Graph_FXT_pi11->GetYaxis()->SetTitleSize(0.035);
   Graph_FXT_pi11->GetYaxis()->SetTitleFont(42);
   Graph_FXT_pi11->GetZaxis()->SetLabelFont(42);
   Graph_FXT_pi11->GetZaxis()->SetLabelSize(0.035);
   Graph_FXT_pi11->GetZaxis()->SetTitleSize(0.035);
   Graph_FXT_pi11->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_FXT_pi11);
   
   gre->Draw("p9");
   
   gre = new TGraphErrors(2);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = 924;
   color = new TColor(ci, 0, 0.6, 0, " ", 0.4);
   gre->SetLineColor(ci);
   gre->SetLineWidth(30);
   gre->SetPoint(0,0,0);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,4.4,0.02355);
   gre->SetPointError(1,0,0.00056);
   gre->Draw("z");
   
   TLegend *leg = new TLegend(0.42,0.18,0.94,0.62,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("FOPI","FOPI (Ch)  0.25<b_{0}<0.45","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("EOS","EOS, E895, E877 (p)  5-7 fm","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("CERES","CERES (Ch) ","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NA49","NA49 (Ch)  12-34%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(28);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("STARp","STAR (p)  10-40%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(30);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("STAR","STAR (#pi) 10-40%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff00ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(30);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("PHENIXp","PHENIX (p) 20-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(8);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("PHENIXpi","PHENIX (#pi) 20-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   entry=leg->AddEntry("PHOBOS","PHOBOS (Ch) 0-40%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(26);
   entry->SetMarkerSize(3);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.42,0.8,0.94,0.92,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   entry=leg->AddEntry("FXT _p","STAR FXT (p) 0-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   entry=leg->AddEntry("FXT_pi","STAR FXT (#pi) 0-30%","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(29);
   entry->SetMarkerSize(4);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
