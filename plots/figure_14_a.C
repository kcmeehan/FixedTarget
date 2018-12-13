{
//=========Macro generated from canvas: c/c
//=========  (Wed Feb 28 09:50:26 2018) by ROOT version5.34/36
   TCanvas *c = new TCanvas("c", "c",0,0,1200,900);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(-1.976471,-0.9464286,1.788235,0.8392857);
   c->SetFillColor(0);
   c->SetFillStyle(4000);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[101] = {-1.6, -1.568, -1.536, -1.504, -1.472, -1.44, -1.408, -1.376, -1.344, -1.312, -1.28, -1.248, -1.216, -1.184, -1.152, -1.12, -1.088, -1.056, -1.024, -0.992, -0.96, -0.928, -0.896, -0.864, -0.832, -0.8, -0.768, -0.736, -0.704, -0.672, -0.64, -0.608, -0.576, -0.544, -0.512, -0.48, -0.448, -0.416, -0.384, -0.352, -0.32, -0.288, -0.256, -0.224, -0.192, -0.16, -0.128, -0.096, -0.064, -0.032, 1.110223e-15, 0.032, 0.064, 0.096, 0.128, 0.16, 0.192, 0.224, 0.256, 0.288, 0.32, 0.352, 0.384, 0.416, 0.448, 0.48, 0.512, 0.544, 0.576, 0.608, 0.64, 0.672, 0.704, 0.736, 0.768, 0.8, 0.832, 0.864, 0.896, 0.928, 0.96, 0.992, 1.024, 1.056, 1.088, 1.12, 1.152, 1.184, 1.216, 1.248, 1.28, 1.312, 1.344, 1.376, 1.408, 1.44, 1.472, 1.504, 1.536, 1.568, 1.6}; 
   
   TH1C *frame = new TH1C("frame","",100, xAxis1);
   frame->SetMinimum(-0.75);
   frame->SetMaximum(0.75);
   frame->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame->SetLineColor(ci);
   frame->SetMarkerStyle(8);
   frame->SetMarkerSize(0);
   frame->GetXaxis()->SetTitle("y_{cm}");
   frame->GetXaxis()->SetLabelFont(42);
   frame->GetXaxis()->SetLabelSize(0.05);
   frame->GetXaxis()->SetTitleSize(0.06111111);
   frame->GetXaxis()->SetTitleOffset(0.8);
   frame->GetXaxis()->SetTitleFont(42);
   frame->GetYaxis()->SetTitle("v_{1}");
   frame->GetYaxis()->SetLabelFont(42);
   frame->GetYaxis()->SetLabelSize(0.05);
   frame->GetYaxis()->SetTitleSize(0.06111111);
   frame->GetYaxis()->SetTitleOffset(0.7);
   frame->GetYaxis()->SetTitleFont(42);
   frame->GetZaxis()->SetLabelFont(42);
   frame->GetZaxis()->SetLabelSize(0.035);
   frame->GetZaxis()->SetTitleSize(0.035);
   frame->GetZaxis()->SetTitleFont(42);
   frame->Draw("p");
   TLatex *   tex = new TLatex(0.15,0.89,"#Lambda 10-30%");
tex->SetNDC();
   tex->SetTextSize(0.07777778);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.55,0.45,"slope near mid-rapidity:");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.63,0.37,"0.094 #pm 0.014");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.15,0.75,"STAR Preliminary");
tex->SetNDC();
   tex->SetTextSize(0.06111111);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.15,0.7,"Statistical Errors Only");
tex->SetNDC();
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.15,0.66,"Open symbols are reflected");
tex->SetNDC();
   tex->SetTextSize(0.03888889);
   tex->SetLineWidth(2);
   tex->Draw();
   TLine *line = new TLine(-1.6,0,1.6,0);
   line->SetLineStyle(0);
   line->SetLineWidth(2);
   line->Draw();
   line = new TLine(0,-0.75,0,0.75);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   
   TLegend *leg = new TLegend(0.54,0.17,0.94,0.32,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
