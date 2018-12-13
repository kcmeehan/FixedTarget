void figure_15b()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Nov  8 16:39:33 2018) by ROOT version 6.14/04
   TCanvas *c = new TCanvas("c", "c",1,1,1200,876);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0.3309202,-0.04871795,1.722807,0.002564103);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogx();
   c->SetLeftMargin(0.15);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.17);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis2[1001] = {0, 0.045, 0.09, 0.135, 0.18, 0.225, 0.27, 0.315, 0.36, 0.405, 0.45, 0.495, 0.54, 0.585, 0.63, 0.675, 0.72, 0.765, 0.81, 0.855, 0.9, 0.945, 0.99, 1.035, 1.08, 1.125, 1.17, 1.215, 1.26, 1.305, 1.35, 1.395, 1.44, 1.485, 1.53, 1.575, 1.62, 1.665, 1.71, 1.755, 1.8, 1.845, 1.89, 1.935, 1.98, 2.025, 2.07, 2.115, 2.16, 2.205, 2.25, 2.295, 2.34, 2.385, 2.43, 2.475, 2.52, 2.565, 2.61, 2.655, 2.7, 2.745, 2.79, 2.835, 2.88, 2.925, 2.97, 3.015, 3.06, 3.105, 3.15, 3.195, 3.24, 3.285, 3.33, 3.375, 3.42, 3.465, 3.51, 3.555, 3.6, 3.645, 3.69, 3.735, 3.78, 3.825, 3.87, 3.915, 3.96, 4.005, 4.05, 4.095, 4.14, 4.185, 4.23, 4.275, 4.32, 4.365, 4.41, 4.455, 4.5, 4.545, 4.59, 4.635, 4.68, 4.725, 4.77, 4.815, 4.86, 4.905, 4.95, 4.995, 5.04, 5.085, 5.13, 5.175, 5.22, 5.265, 5.31, 5.355, 5.4, 5.445, 5.49, 5.535, 5.58, 5.625, 5.67, 5.715, 5.76, 5.805, 5.85, 5.895, 5.94, 5.985, 6.03, 6.075, 6.12, 6.165, 6.21, 6.255, 6.3, 6.345, 6.39, 6.435, 6.48, 6.525, 6.57, 6.615, 6.66, 6.705, 6.75, 6.795, 6.84, 6.885, 6.93, 6.975, 7.02, 7.065, 7.11, 7.155, 7.2, 7.245, 7.29, 7.335, 7.38, 7.425, 7.47, 7.515, 7.56, 7.605, 7.65, 7.695, 7.74, 7.785, 7.83, 7.875, 7.92, 7.965, 8.01, 8.055, 8.1, 8.145, 8.19, 8.235, 8.28, 8.325, 8.37, 8.415, 8.46, 8.505, 8.55, 8.595, 8.64, 8.685, 8.73, 8.775, 8.82, 8.865, 8.91, 8.955, 9, 9.045, 9.09, 9.135, 9.18, 9.225, 9.27, 9.315, 9.36, 9.405, 9.45, 9.495, 9.54, 9.585, 9.63, 9.675, 9.72, 9.765, 9.81, 9.855, 9.9, 9.945, 9.99, 10.035, 10.08, 10.125, 10.17, 10.215, 10.26, 10.305, 10.35, 10.395, 10.44, 10.485, 10.53, 10.575, 10.62, 10.665, 10.71, 10.755, 10.8, 10.845, 10.89, 10.935, 10.98, 11.025, 11.07, 11.115, 11.16, 11.205, 11.25, 11.295, 11.34, 11.385, 11.43, 11.475, 11.52, 11.565, 11.61, 11.655, 11.7, 11.745, 11.79, 11.835, 11.88, 11.925, 11.97, 12.015, 12.06, 12.105, 12.15, 12.195, 12.24, 12.285, 12.33, 12.375, 12.42, 12.465, 12.51, 12.555, 12.6, 12.645, 12.69, 12.735, 12.78, 12.825, 12.87, 12.915, 12.96, 13.005, 13.05, 13.095, 13.14, 13.185, 13.23, 13.275, 13.32, 13.365, 13.41, 13.455, 13.5, 13.545, 13.59, 13.635, 13.68, 13.725, 13.77, 13.815, 13.86, 13.905, 13.95, 13.995, 14.04, 14.085, 14.13, 14.175, 14.22, 14.265, 14.31, 14.355, 14.4, 14.445, 14.49, 14.535, 14.58, 14.625, 14.67, 14.715, 14.76, 14.805, 14.85, 14.895, 14.94, 14.985, 15.03, 15.075, 15.12, 15.165, 15.21, 15.255, 15.3, 15.345, 15.39, 15.435, 15.48, 15.525, 15.57, 15.615, 15.66, 15.705, 15.75, 15.795, 15.84, 15.885, 15.93, 15.975, 16.02, 16.065, 16.11, 16.155, 16.2, 16.245, 16.29, 16.335, 16.38, 16.425, 16.47, 16.515, 16.56, 16.605, 16.65, 16.695, 16.74, 16.785, 16.83, 16.875, 16.92, 16.965, 17.01, 17.055, 17.1, 17.145, 17.19, 17.235, 17.28, 17.325, 17.37, 17.415, 17.46, 17.505, 17.55, 17.595, 17.64, 17.685, 17.73, 17.775, 17.82, 17.865, 17.91, 17.955, 18, 18.045, 18.09, 18.135, 18.18, 18.225, 18.27, 18.315, 18.36, 18.405, 18.45, 18.495, 18.54, 18.585, 18.63, 18.675, 18.72, 18.765, 18.81, 18.855, 18.9, 18.945, 18.99, 19.035, 19.08, 19.125, 19.17, 19.215, 19.26, 19.305, 19.35, 19.395, 19.44, 19.485, 19.53, 19.575, 19.62, 19.665, 19.71, 19.755, 19.8, 19.845, 19.89, 19.935, 19.98, 20.025, 20.07, 20.115, 20.16, 20.205, 20.25, 20.295, 20.34, 20.385, 20.43, 20.475, 20.52, 20.565, 20.61, 20.655, 20.7, 20.745, 20.79, 20.835, 20.88, 20.925, 20.97, 21.015, 21.06, 21.105, 21.15, 21.195, 21.24, 21.285, 21.33, 21.375, 21.42, 21.465, 21.51, 21.555, 21.6, 21.645, 21.69, 21.735, 21.78, 21.825, 21.87, 21.915, 21.96, 22.005, 22.05, 22.095, 22.14, 22.185, 22.23, 22.275, 22.32, 22.365, 22.41, 22.455, 22.5, 22.545, 22.59, 22.635, 22.68, 22.725, 22.77, 22.815, 22.86, 22.905, 22.95, 22.995, 23.04, 23.085, 23.13, 23.175, 23.22, 23.265, 23.31, 23.355, 23.4, 23.445, 23.49, 23.535, 23.58, 23.625, 23.67, 23.715, 23.76, 23.805, 23.85, 23.895, 23.94, 23.985, 24.03, 24.075, 24.12, 24.165, 24.21, 24.255, 24.3, 24.345, 24.39, 24.435, 24.48, 24.525, 24.57, 24.615, 24.66, 24.705, 24.75, 24.795, 24.84, 24.885, 24.93, 24.975, 25.02, 25.065, 25.11, 25.155, 25.2, 25.245, 25.29, 25.335, 25.38, 25.425, 25.47, 25.515, 25.56, 25.605, 25.65, 25.695, 25.74, 25.785, 25.83, 25.875, 25.92, 25.965, 26.01, 26.055, 26.1, 26.145, 26.19, 26.235, 26.28, 26.325, 26.37, 26.415, 26.46, 26.505, 26.55, 26.595, 26.64, 26.685, 26.73, 26.775, 26.82, 26.865, 26.91, 26.955, 27, 27.045, 27.09, 27.135, 27.18, 27.225, 27.27, 27.315, 27.36, 27.405, 27.45, 27.495, 27.54, 27.585, 27.63, 27.675, 27.72, 27.765, 27.81, 27.855, 27.9, 27.945, 27.99, 28.035, 28.08, 28.125, 28.17, 28.215, 28.26, 28.305, 28.35, 28.395, 28.44, 28.485, 28.53, 28.575, 28.62, 28.665, 28.71, 28.755, 28.8, 28.845, 28.89, 28.935, 28.98, 29.025, 29.07, 29.115, 29.16, 29.205, 29.25, 29.295, 29.34, 29.385, 29.43, 29.475, 29.52, 29.565, 29.61, 29.655, 29.7, 29.745, 29.79, 29.835, 29.88, 29.925, 29.97, 30.015, 30.06, 30.105, 30.15, 30.195, 30.24, 30.285, 30.33, 30.375, 30.42, 30.465, 30.51, 30.555, 30.6, 30.645, 30.69, 30.735, 30.78, 30.825, 30.87, 30.915, 30.96, 31.005, 31.05, 31.095, 31.14, 31.185, 31.23, 31.275, 31.32, 31.365, 31.41, 31.455, 31.5, 31.545, 31.59, 31.635, 31.68, 31.725, 31.77, 31.815, 31.86, 31.905, 31.95, 31.995, 32.04, 32.085, 32.13, 32.175, 32.22, 32.265, 32.31, 32.355, 32.4, 32.445, 32.49, 32.535, 32.58, 32.625, 32.67, 32.715, 32.76, 32.805, 32.85, 32.895, 32.94, 32.985, 33.03, 33.075, 33.12, 33.165, 33.21, 33.255, 33.3, 33.345, 33.39, 33.435, 33.48, 33.525, 33.57, 33.615, 33.66, 33.705, 33.75, 33.795, 33.84, 33.885, 33.93, 33.975, 34.02, 34.065, 34.11, 34.155, 34.2, 34.245, 34.29, 34.335, 34.38, 34.425, 34.47, 34.515, 34.56, 34.605, 34.65, 34.695, 34.74, 34.785, 34.83, 34.875, 34.92, 34.965, 35.01, 35.055, 35.1, 35.145, 35.19, 35.235, 35.28, 35.325, 35.37, 35.415, 35.46, 35.505, 35.55, 35.595, 35.64, 35.685, 35.73, 35.775, 35.82, 35.865, 35.91, 35.955, 36, 36.045, 36.09, 36.135, 36.18, 36.225, 36.27, 36.315, 36.36, 36.405, 36.45, 36.495, 36.54, 36.585, 36.63, 36.675, 36.72, 36.765, 36.81, 36.855, 36.9, 36.945, 36.99, 37.035, 37.08, 37.125, 37.17, 37.215, 37.26, 37.305, 37.35, 37.395, 37.44, 37.485, 37.53, 37.575, 37.62, 37.665, 37.71, 37.755, 37.8, 37.845, 37.89, 37.935, 37.98, 38.025, 38.07, 38.115, 38.16, 38.205, 38.25, 38.295, 38.34, 38.385, 38.43, 38.475, 38.52, 38.565, 38.61, 38.655, 38.7, 38.745, 38.79, 38.835, 38.88, 38.925, 38.97, 39.015, 39.06, 39.105, 39.15, 39.195, 39.24, 39.285, 39.33, 39.375, 39.42, 39.465, 39.51, 39.555, 39.6, 39.645, 39.69, 39.735, 39.78, 39.825, 39.87, 39.915, 39.96, 40.005, 40.05, 40.095, 40.14, 40.185, 40.23, 40.275, 40.32, 40.365, 40.41, 40.455, 40.5, 40.545, 40.59, 40.635, 40.68, 40.725, 40.77, 40.815, 40.86, 40.905, 40.95, 40.995, 41.04, 41.085, 41.13, 41.175, 41.22, 41.265, 41.31, 41.355, 41.4, 41.445, 41.49, 41.535, 41.58, 41.625, 41.67, 41.715, 41.76, 41.805, 41.85, 41.895, 41.94, 41.985, 42.03, 42.075, 42.12, 42.165, 42.21, 42.255, 42.3, 42.345, 42.39, 42.435, 42.48, 42.525, 42.57, 42.615, 42.66, 42.705, 42.75, 42.795, 42.84, 42.885, 42.93, 42.975, 43.02, 43.065, 43.11, 43.155, 43.2, 43.245, 43.29, 43.335, 43.38, 43.425, 43.47, 43.515, 43.56, 43.605, 43.65, 43.695, 43.74, 43.785, 43.83, 43.875, 43.92, 43.965, 44.01, 44.055, 44.1, 44.145, 44.19, 44.235, 44.28, 44.325, 44.37, 44.415, 44.46, 44.505, 44.55, 44.595, 44.64, 44.685, 44.73, 44.775, 44.82, 44.865, 44.91, 44.955, 45}; 
   
   TH1C *frame_qmWq__3 = new TH1C("frame_qmWq__3","",1000, xAxis2);
   frame_qmWq__3->SetMinimum(-0.04);
   frame_qmWq__3->SetMaximum(0);
   frame_qmWq__3->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_qmWq__3->SetLineColor(ci);
   frame_qmWq__3->SetMarkerStyle(8);
   frame_qmWq__3->SetMarkerSize(0);
   frame_qmWq__3->GetXaxis()->SetTitle("#sqrt{ s_{NN} } GeV");
   frame_qmWq__3->GetXaxis()->SetRange(78,1000);
   frame_qmWq__3->GetXaxis()->SetMoreLogLabels();
   frame_qmWq__3->GetXaxis()->SetNdivisions(1404);
   frame_qmWq__3->GetXaxis()->SetLabelFont(42);
   frame_qmWq__3->GetXaxis()->SetLabelSize(0.05);
   frame_qmWq__3->GetXaxis()->SetTitleSize(0.07777778);
   frame_qmWq__3->GetXaxis()->SetTitleOffset(0.9);
   frame_qmWq__3->GetXaxis()->SetTitleFont(42);
   frame_qmWq__3->GetYaxis()->SetTitle("dv_{1} / dy #lbar_{ y=0}");
   frame_qmWq__3->GetYaxis()->SetNdivisions(10110);
   frame_qmWq__3->GetYaxis()->SetLabelFont(42);
   frame_qmWq__3->GetYaxis()->SetLabelSize(0.05);
   frame_qmWq__3->GetYaxis()->SetTitleSize(0.07777778);
   frame_qmWq__3->GetYaxis()->SetTitleOffset(0.9);
   frame_qmWq__3->GetYaxis()->SetTitleFont(42);
   frame_qmWq__3->GetZaxis()->SetLabelFont(42);
   frame_qmWq__3->GetZaxis()->SetLabelSize(0.035);
   frame_qmWq__3->GetZaxis()->SetTitleSize(0.035);
   frame_qmWq__3->GetZaxis()->SetTitleFont(42);
   frame_qmWq__3->Draw("p");
   
   Double_t gK0_fx1008[2] = {
   0,
   4.5};
   Double_t gK0_fy1008[2] = {
   0,
   -0.022};
   Double_t gK0_fex1008[2] = {
   0,
   0};
   Double_t gK0_fey1008[2] = {
   0,
   0.015};
   TGraphErrors *gre = new TGraphErrors(2,gK0_fx1008,gK0_fy1008,gK0_fex1008,gK0_fey1008);
   gre->SetName("gK0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(30);
   gre->SetMarkerSize(3);
   
   TH1F *Graph_gK01008 = new TH1F("Graph_gK01008","Graph",100,0.00495,4.95);
   Graph_gK01008->SetMinimum(-0.0407);
   Graph_gK01008->SetMaximum(0.0037);
   Graph_gK01008->SetDirectory(0);
   Graph_gK01008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gK01008->SetLineColor(ci);
   Graph_gK01008->GetXaxis()->SetLabelFont(42);
   Graph_gK01008->GetXaxis()->SetLabelSize(0.035);
   Graph_gK01008->GetXaxis()->SetTitleSize(0.035);
   Graph_gK01008->GetXaxis()->SetTitleFont(42);
   Graph_gK01008->GetYaxis()->SetLabelFont(42);
   Graph_gK01008->GetYaxis()->SetLabelSize(0.035);
   Graph_gK01008->GetYaxis()->SetTitleSize(0.035);
   Graph_gK01008->GetYaxis()->SetTitleOffset(0);
   Graph_gK01008->GetYaxis()->SetTitleFont(42);
   Graph_gK01008->GetZaxis()->SetLabelFont(42);
   Graph_gK01008->GetZaxis()->SetLabelSize(0.035);
   Graph_gK01008->GetZaxis()->SetTitleSize(0.035);
   Graph_gK01008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gK01008);
   
   gre->Draw(" p");
   
   Double_t gPiPlus_fx1009[2] = {
   0,
   4.5};
   Double_t gPiPlus_fy1009[2] = {
   0,
   -0.021};
   Double_t gPiPlus_fex1009[2] = {
   0,
   0};
   Double_t gPiPlus_fey1009[2] = {
   0,
   0.002};
   gre = new TGraphErrors(2,gPiPlus_fx1009,gPiPlus_fy1009,gPiPlus_fex1009,gPiPlus_fey1009);
   gre->SetName("gPiPlus");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_gPiPlus1009 = new TH1F("Graph_gPiPlus1009","Graph",100,0.00495,4.95);
   Graph_gPiPlus1009->SetMinimum(-0.0253);
   Graph_gPiPlus1009->SetMaximum(0.0023);
   Graph_gPiPlus1009->SetDirectory(0);
   Graph_gPiPlus1009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gPiPlus1009->SetLineColor(ci);
   Graph_gPiPlus1009->GetXaxis()->SetLabelFont(42);
   Graph_gPiPlus1009->GetXaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1009->GetXaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1009->GetXaxis()->SetTitleFont(42);
   Graph_gPiPlus1009->GetYaxis()->SetLabelFont(42);
   Graph_gPiPlus1009->GetYaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1009->GetYaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1009->GetYaxis()->SetTitleOffset(0);
   Graph_gPiPlus1009->GetYaxis()->SetTitleFont(42);
   Graph_gPiPlus1009->GetZaxis()->SetLabelFont(42);
   Graph_gPiPlus1009->GetZaxis()->SetLabelSize(0.035);
   Graph_gPiPlus1009->GetZaxis()->SetTitleSize(0.035);
   Graph_gPiPlus1009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gPiPlus1009);
   
   gre->Draw(" p");
   
   Double_t gPiMinus_fx1010[2] = {
   0,
   4.5};
   Double_t gPiMinus_fy1010[2] = {
   0,
   -0.01};
   Double_t gPiMinus_fex1010[2] = {
   0,
   0};
   Double_t gPiMinus_fey1010[2] = {
   0,
   0.003};
   gre = new TGraphErrors(2,gPiMinus_fx1010,gPiMinus_fy1010,gPiMinus_fex1010,gPiMinus_fey1010);
   gre->SetName("gPiMinus");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_gPiMinus1010 = new TH1F("Graph_gPiMinus1010","Graph",100,0.00495,4.95);
   Graph_gPiMinus1010->SetMinimum(-0.0143);
   Graph_gPiMinus1010->SetMaximum(0.0013);
   Graph_gPiMinus1010->SetDirectory(0);
   Graph_gPiMinus1010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_gPiMinus1010->SetLineColor(ci);
   Graph_gPiMinus1010->GetXaxis()->SetLabelFont(42);
   Graph_gPiMinus1010->GetXaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1010->GetXaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1010->GetXaxis()->SetTitleFont(42);
   Graph_gPiMinus1010->GetYaxis()->SetLabelFont(42);
   Graph_gPiMinus1010->GetYaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1010->GetYaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1010->GetYaxis()->SetTitleOffset(0);
   Graph_gPiMinus1010->GetYaxis()->SetTitleFont(42);
   Graph_gPiMinus1010->GetZaxis()->SetLabelFont(42);
   Graph_gPiMinus1010->GetZaxis()->SetLabelSize(0.035);
   Graph_gPiMinus1010->GetZaxis()->SetTitleSize(0.035);
   Graph_gPiMinus1010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_gPiMinus1010);
   
   gre->Draw(" p");
   
   Double_t bespipsys_fx1011[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   200};
   Double_t bespipsys_fy1011[8] = {
   -0.0249697,
   -0.0245736,
   -0.0189913,
   -0.0169655,
   -0.0136131,
   -0.0108059,
   -0.00587525,
   -0.00235619};
   Double_t bespipsys_fex1011[8] = {
   0.25,
   0.25,
   0.25,
   0.25,
   0.25,
   0.5,
   0,
   0};
   Double_t bespipsys_fey1011[8] = {
   0.00022904,
   0.001047249,
   0.001047249,
   7.63896e-05,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(8,bespipsys_fx1011,bespipsys_fy1011,bespipsys_fex1011,bespipsys_fey1011);
   gre->SetName("bespipsys");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetLineWidth(10);
   gre->SetMarkerStyle(25);
   
   TH1F *Graph_bespipsys1011 = new TH1F("Graph_bespipsys1011","Graph",100,6.705,219.255);
   Graph_bespipsys1011->SetMinimum(-0.02794731);
   Graph_bespipsys1011->SetMaximum(-2.97241e-05);
   Graph_bespipsys1011->SetDirectory(0);
   Graph_bespipsys1011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_bespipsys1011->SetLineColor(ci);
   Graph_bespipsys1011->GetXaxis()->SetLabelFont(42);
   Graph_bespipsys1011->GetXaxis()->SetLabelSize(0.035);
   Graph_bespipsys1011->GetXaxis()->SetTitleSize(0.035);
   Graph_bespipsys1011->GetXaxis()->SetTitleFont(42);
   Graph_bespipsys1011->GetYaxis()->SetLabelFont(42);
   Graph_bespipsys1011->GetYaxis()->SetLabelSize(0.035);
   Graph_bespipsys1011->GetYaxis()->SetTitleSize(0.035);
   Graph_bespipsys1011->GetYaxis()->SetTitleOffset(0);
   Graph_bespipsys1011->GetYaxis()->SetTitleFont(42);
   Graph_bespipsys1011->GetZaxis()->SetLabelFont(42);
   Graph_bespipsys1011->GetZaxis()->SetLabelSize(0.035);
   Graph_bespipsys1011->GetZaxis()->SetTitleSize(0.035);
   Graph_bespipsys1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_bespipsys1011);
   
   gre->Draw(" z9");
   
   Double_t bespip_fx1012[8] = {
   7.7,
   11.5,
   14.5,
   19.6,
   27,
   39,
   62.4,
   200};
   Double_t bespip_fy1012[8] = {
   -0.0249697,
   -0.0245736,
   -0.0189913,
   -0.0169655,
   -0.0136131,
   -0.0108059,
   -0.00587525,
   -0.00235619};
   Double_t bespip_fex1012[8] = {
   0.25,
   0.25,
   0.25,
   0.25,
   0.25,
   0.5,
   0,
   0};
   Double_t bespip_fey1012[8] = {
   0.000602224,
   0.000464752,
   0.000408242,
   0.000309662,
   0.000278147,
   0.000191003,
   0.00069624,
   5.23337e-05};
   gre = new TGraphErrors(8,bespip_fx1012,bespip_fy1012,bespip_fex1012,bespip_fey1012);
   gre->SetName("bespip");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);

   ci = TColor::GetColor("#cccccc");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_bespip1012 = new TH1F("Graph_bespip1012","Graph",100,6.705,219.255);
   Graph_bespip1012->SetMinimum(-0.02789873);
   Graph_bespip1012->SetMaximum(2.295047e-05);
   Graph_bespip1012->SetDirectory(0);
   Graph_bespip1012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_bespip1012->SetLineColor(ci);
   Graph_bespip1012->GetXaxis()->SetLabelFont(42);
   Graph_bespip1012->GetXaxis()->SetLabelSize(0.035);
   Graph_bespip1012->GetXaxis()->SetTitleSize(0.035);
   Graph_bespip1012->GetXaxis()->SetTitleFont(42);
   Graph_bespip1012->GetYaxis()->SetLabelFont(42);
   Graph_bespip1012->GetYaxis()->SetLabelSize(0.035);
   Graph_bespip1012->GetYaxis()->SetTitleSize(0.035);
   Graph_bespip1012->GetYaxis()->SetTitleOffset(0);
   Graph_bespip1012->GetYaxis()->SetTitleFont(42);
   Graph_bespip1012->GetZaxis()->SetLabelFont(42);
   Graph_bespip1012->GetZaxis()->SetLabelSize(0.035);
   Graph_bespip1012->GetZaxis()->SetTitleSize(0.035);
   Graph_bespip1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_bespip1012);
   
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
   0.25,
   0.25,
   0.25,
   0.25,
   0.25,
   0.5,
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
   
   TH1F *Graph_besk0sys1013 = new TH1F("Graph_besk0sys1013","Graph",100,6.885,219.235);
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
   0.25,
   0.25,
   0.25,
   0.25,
   0.25,
   0.5,
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
   
   TH1F *Graph_besk01014 = new TH1F("Graph_besk01014","Graph",100,6.885,219.235);
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
   TLine *line = new TLine(3.5,0,45,0);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   TLatex *   tex = new TLatex(10,0.04,"STAR BES 10-40%");
   tex->SetTextAlign(13);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(10,0.05,"STAR FXT 10-25%");
   tex->SetTextAlign(13);
   tex->SetTextColor(2);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(10,0.06,"E895 12-25%");
   tex->SetTextAlign(13);

   ci = TColor::GetColor("#5b9f1d");
   tex->SetTextColor(ci);
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.44,0.18,0.94,0.48,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("graph_legend_d/gPiPlus","#pi^{#font[122]{+} } (STAR FXT)","p");
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
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
