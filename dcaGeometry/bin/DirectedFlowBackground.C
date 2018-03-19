//
//  DirectedFlowLambda.c
//  FixedTarget
//
//  Created by DavidTlustyRice on 22/11/17.
//
//

#include <iostream>

void CalcCholesky(int NP, double* fCov, double* fCovSqrt)
{
  double *C = fCovSqrt;
  double *V = fCov;
  // calculate sqrt(V) as lower diagonal matrix
  for( int i = 0; i < NP; ++i )
  {
    for( int j = 0; j < NP; ++j )
    {
      C[i*NP+j] = 0;
    }
  }
  for( int j = 0; j < NP; ++j )
  {
    // diagonal terms first
    double Ck = 0;
    for( int k = 0; k < j; ++k )
    {
      Ck += C[j*NP+k] * C[j*NP+k];
    } // k
    C[j*NP+j] = sqrt( fabs( V[j*NP+j] - Ck ) );
    
    // off-diagonal terms
    for( int i = j+1; i < NP; ++i )
    {
      Ck = 0;
      for( int k = 0; k < j; ++k )
      {
        Ck += C[i*NP+k] * C[j*NP+k];
      } //k
      if(C[j*NP+j]!=0 ) C[i*NP+j] = ( V[i*NP+j] - Ck ) / C[j*NP+j];
      else C[i*NP+j] = 0;
    }// i
  } // j
}
double RANDOM(double xx, TF1* F, int NP, double* fCovSqrt)
{
  
  double * z = new double[NP];
  double * x = new double[NP];
  double * p = new double[NP];
  
  for( int i = 0; i < NP; ++i )
  {
    z[i] = gRandom->Gaus( 0.0, 1.0 );
    p[i] = F->GetParameter(i);
  }
  
  for( int i = 0; i < NP; ++i )
  {
    x[i] = 0;
    for( int j = 0; j <= i; ++j )
    {
      x[i] += fCovSqrt[i*NP+j] * z[j];
    } // j
  }
  
  for( int i = 0; i < NP; ++i )
  {
    F->SetParameter(i,x[i]+p[i]);
  }
  double value = F->Eval(xx);
  for( int i = 0; i < NP; ++i )
  {
    F->SetParameter(i,p[i]);
  }
  
  delete [] z;
  delete [] x;
  delete [] p;
  return value;
  
}



double Pearson(double *x, double *par)
{
  //  return par[0]*TMath::Power(1+(x[0]-par[1])*(x[0]-par[1])/par[2],par[3])*TMath::Power(1+(x[0]-par[1])*(x[0]-par[1])/par[4],par[5]);
  return par[4]+par[0]*2*TMath::Sqrt(TMath::Power(2,1/par[3])-1)/(par[2]*TMath::Beta(par[3]-0.5,0.5))*
  TMath::Power(1+4*TMath::Power((x[0]-par[1])/par[2],2)*(TMath::Power(2,1/par[3])-1),-par[3]);
}

void DirectedFlowBackground(char *filename = "test.root", int rebin = 1, double EventPlaneResolution = 0.404, char *histogram = "V1vsM", int linear=0, float sigma = 0.5)
{
  
  gROOT->Reset();
  TGaxis::SetMaxDigits(3);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);
  gStyle->SetTitleFontSize(0.03);
  
  TFile *inputfile = new TFile(filename);
  TH3D *hV1 = (TH3D*)inputfile->Get(histogram);

  hV1->Sumw2();
  
  TH2D *hUnlikeSign = (TH2D*)inputfile->Get("UnlikeSignVsY");
  TH2D *hCombinatorial = (TH2D*)inputfile->Get("RotatedVsY");
  TH2D *hCombinatorialToPlot = (TH2D*)hCombinatorial->Clone("CombinatorialToPlot"); // will not be Sumw2 so it can be plot as a line
  hUnlikeSign->Sumw2();
  hCombinatorial->Sumw2();
  TCanvas *c1 = new TCanvas("c1");
  c1->Print("LambdaMassVsY.pdf[");
  
//  const int nYBins = 7;
//  double y_bins[nYBins] = {-1.5,-1.3,-1.1,-0.9,-0.7,-0.5,-0.3};
  const int nYBins = 16;
  double y_bins[nYBins] = {-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2};
//  const int nYBins = 20;
//  double y_bins[nYBins] = {-1.7,-1.6,-1.52,-1.46,-1.42,-1.36,-1.3,-1.24,-1.18,-1.12,-1.06,-1,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2};
//  const int nYBins = 37;
//  double y_bins[nYBins] = {-1.7,-1.6,-1.56,-1.52,-1.48,-1.46,-1.44,-1.42,-1.4,-1.38,-1.36,-1.34,-1.32,-1.3,-1.28,-1.26,-1.24,-1.22,-1.2,-1.18,-1.16,-1.14,-1.12,-1.1,-1.08,-1.06,-1.04,-1.02,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2};
  double y_bins_cms[nYBins] = {0};
  double Yield[nYBins] = {0};
  double newy[nYBins] = {0};
  double newy2[nYBins] = {0};
  double newy3[nYBins] = {0};
  double newy4[nYBins] = {0};
  double YieldError[nYBins] = {0};
  double ypos[nYBins]={0};
  double yposreflected[nYBins]={0};
  double BgYield[nYBins] = {0};
  double BgYieldError[nYBins] = {0};
  double FlowReflected[nYBins] = {0};
  double Flow[nYBins] = {0};
  double FlowError[nYBins] = {0};
  
  
  for (int h = 0; h < nYBins-1; h++){
    double FitLim1 = 1.095;
    double FitLim2 = 1.14;
    int Bin1 = hUnlikeSign->GetXaxis()->FindBin(y_bins[h]+0.001);
    int Bin2 = hUnlikeSign->GetXaxis()->FindBin(y_bins[h+1]-0.00001);

    
    c1->cd();
    TH1D *hInvMass = hUnlikeSign->ProjectionY("InvMass",Bin1,Bin2);
    TH1D *hInvMassBg = hCombinatorial->ProjectionY("InvMassBg",Bin1,Bin2);
    TH1D *hInvMassBgToPlot = hCombinatorialToPlot->ProjectionY("InvMassBgToPlot",Bin1,Bin2);
    hInvMass->Rebin(rebin);
    hInvMassBg->Rebin(rebin);
    hInvMassBgToPlot->Rebin(rebin);
    hInvMassBg->Scale(0.95);
    hInvMassBgToPlot->Scale(0.95);
    char ProjTitle[100];
    sprintf(ProjTitle, "%.2f < y(p#pi^{#minus}) < %.2f, centrality 10 - 30", y_bins[h], y_bins[h+1]);
    hInvMass->SetTitle(ProjTitle);
    hInvMass->GetXaxis()->SetTitle("M_{p#pi^{#minus}} [GeV/c^{2}]");
    hInvMass->GetYaxis()->SetTitle(Form("Counts/%f",hInvMass->GetBinWidth(1)));
    hInvMass->GetXaxis()->SetTitleSize(0.043);
    hInvMass->GetXaxis()->SetLabelSize(0.043);
    hInvMass->GetYaxis()->SetTitleSize(0.043);
    hInvMass->GetYaxis()->SetLabelSize(0.043);
    hInvMass->GetXaxis()->SetRangeUser(1.08,1.18);
    hInvMassBgToPlot->SetLineColor(2);
    TH1D *hSig = (TH1D*)hInvMass->Clone("Sig");
    hSig->Add(hInvMassBg,-1);
    TF1 *fPearson = new TF1("Pearson",Pearson,FitLim1,FitLim2,5);
    fPearson->SetNpx(1000);
    fPearson->SetParameter(0,hSig->Integral()*hSig->GetBinWidth(1));
    fPearson->SetParameter(1,1.115);
    fPearson->SetParameter(2,0.01);
    fPearson->SetParameter(3,2);
    fPearson->SetParLimits(2,0,10);
    fPearson->SetParLimits(1,1.114,1.118);
//    fPearson->SetParLimits(0,1000,10000);
    hSig->Fit(fPearson,"REM0","");
    hSig->Fit(fPearson,"REM0","");

    hInvMass->GetYaxis()->SetRangeUser(hSig->GetMinimum(),hSig->GetMaximum()+hInvMassBg->GetMaximum());
    hInvMass->Draw();
    hInvMassBgToPlot->Draw("lsame");

    
    
    fPearson->SetLineColor(kGreen+2);
    fPearson->Draw("same");
    hSig->SetMarkerStyle(24);
    hSig->SetMarkerColor(kMagenta);
    hSig->SetLineColor(kMagenta);
    hSig->Draw("same");
    TLegend *mLegend = new TLegend(0.6,0.5,0.95,0.89);
    mLegend->AddEntry(hInvMass,"Unlike Sign","pl");
    mLegend->AddEntry(hCombinatorialToPlot,"Combinatorial Bg","l");
    mLegend->AddEntry(hSig,"Signal (Unlike #minus Bg)","pl");
    mLegend->AddEntry(fPearson,"Pearson VII fit to Signal","l");
    mLegend->SetBorderSize(0);
    mLegend->Draw();
    
//    double sig1 = fPearson->GetParameter(1) - sigma*fPearson->GetParameter(2);
//    double sig2 = fPearson->GetParameter(1) + sigma*fPearson->GetParameter(2);
//    double sig1 = fPearson->GetParameter(1) - 0.007;
//    double sig2 = fPearson->GetParameter(1) + 0.007;
    double sig1 = 1.113;
    double sig2 = 1.119;
    
    double bg1 = 1.09;
    double bg2 = fPearson->GetParameter(1) - 3*fPearson->GetParameter(2);
    double bg3 = fPearson->GetParameter(1) + 3*fPearson->GetParameter(2);
    double bg4 = 1.15;
    TLine *cutLine1 = new TLine(sig1,0,sig1,hInvMass->GetMaximum());
    TLine *cutLine2 = new TLine(sig2,0,sig2,hInvMass->GetMaximum());
    cutLine1->SetLineStyle(3);
    cutLine2->SetLineStyle(3);
    cutLine1->Draw();
    cutLine2->Draw();
    
    TLine *bgLine1 = new TLine(bg1,0,bg1,hInvMassBg->GetMaximum());
    TLine *bgLine2 = new TLine(bg2,0,bg2,hInvMassBg->GetMaximum());
    TLine *bgLine3 = new TLine(bg3,0,bg3,hInvMassBg->GetMaximum());
    TLine *bgLine4 = new TLine(bg4,0,bg4,hInvMassBg->GetMaximum());
//    bgLine1->SetLineStyle(4);
//    bgLine2->SetLineStyle(4);
//    bgLine3->SetLineStyle(4);
//    bgLine4->SetLineStyle(4);
    bgLine1->Draw();
    bgLine2->Draw();
    bgLine3->Draw();
    bgLine4->Draw();
    
    
    c1->Print("LambdaMassVsY.pdf");


    int Bin1forV1 = hV1->GetZaxis()->FindBin(y_bins[h]+0.00001);
    int Bin2forV1 = hV1->GetZaxis()->FindBin(y_bins[h+1]-0.00001);
    
    hV1->GetZaxis()->SetRange(Bin1forV1,Bin2forV1);
    TH2D *hV1yx = (TH2D*)hV1->Project3D("yx");
    int MassBin1 = hV1->GetXaxis()->FindBin(sig1+0.0001);
    int MassBin2 = hV1->GetXaxis()->FindBin(sig2-0.00001);
    TH1D *hV1proj = hV1yx->ProjectionY("V1proj",MassBin1,MassBin2);
    

    int BgBin1 = hV1->GetXaxis()->FindBin(bg1+0.0001);
    int BgBin2 = hV1->GetXaxis()->FindBin(bg2-0.00001);
    int BgBin3 = hV1->GetXaxis()->FindBin(bg3+0.0001);
    int BgBin4 = hV1->GetXaxis()->FindBin(bg4-0.00001);
    TH1D *hV1Bgproj = hV1yx->ProjectionY("V1Bgproj",BgBin1,BgBin2);
    TH1D *hV1Bgproj2 = hV1yx->ProjectionY("V1Bgproj2",BgBin3,BgBin4);
    hV1Bgproj->Add(hV1Bgproj2,1);
    
    
    int bgMassBin1 = hInvMassBg->FindBin(sig1+0.0001);
    int bgMassBin2 = hInvMassBg->FindBin(sig2-0.0001);
    Double_t eB, eS;
    
    
//    double S = fPearson->GetParameter(0)/hSig->GetBinWidth(1);
//    eS = fPearson->GetParError(0)/hSig->GetBinWidth(1);
//    double S = fPearson->Integral(sig1,sig2)/hSig->GetBinWidth(1);
//    eS = (fPearson->Integral(sig1,sig2)/fPearson->GetParameter(0))*fPearson->GetParError(0)/hSig->GetBinWidth(1);
    double S = hInvMass->Integral(bgMassBin1,bgMassBin2);
    hInvMass->IntegralAndError(bgMassBin1,bgMassBin2,eS);
    double B = hInvMassBg->IntegralAndError(bgMassBin1,bgMassBin2,eB);
    
    cout<<eS/S<<"   "<<eB/B<<endl;
    
    Yield[h] = S/(y_bins[h+1]-y_bins[h]);
    YieldError[h] = eS/(y_bins[h+1]-y_bins[h]);
    double V1 = hV1proj->GetMean();
    double V1B = hV1Bgproj->GetMean();
    double eV1 = hV1proj->GetMeanError();
    double eV1B = hV1Bgproj->GetMeanError();
    
    cout<<S<<"   "<<B<<endl;
    cout<<V1<<" "<<eV1<<"   "<<V1B<<" "<<eV1B<<endl;
  
    double V1S = 1/S*((S+B)*V1 - B*V1B);
    double eV1S = 1/S*TMath::Sqrt((S+B)*(S+B)*eV1*eV1+B*B*eV1B*eV1B);
    cout<<V1S<<" "<<eV1S<<endl;

    Flow[h] = V1/EventPlaneResolution;
    FlowReflected[h] = -V1/EventPlaneResolution;
    FlowError[h] = eV1/EventPlaneResolution/*+V1S*0.03/EventPlaneResolution*/;
    ypos[h] = (y_bins[h] + y_bins[h+1])/2. + 1.52;
    cout<<"Ypos: "<<ypos[h]<<endl;
    
    
    hV1proj->Delete();
    hV1Bgproj->Delete();
    hV1Bgproj2->Delete();
    hSig->Delete();
    mLegend->Delete();
    fPearson->Delete();
    hV1yx->Delete();
    bgLine1->Delete();
    bgLine2->Delete();
    bgLine3->Delete();
    bgLine4->Delete();
    cutLine1->Delete();
    cutLine2->Delete();
  
  }
  for (int i=0; i<nYBins; i++) y_bins_cms[i] = y_bins[i] + 1.52;

  
  c1->Print("LambdaMassVsY.pdf]");

  
  //**************************  Directed Flow Calculation ****************************
  
  TCanvas *c2 = new TCanvas("c2");
  TGraphErrors *gYield = new TGraphErrors(nYBins-1,ypos,Yield,0,YieldError);
  gYield->Draw("AP");
  TF1 *fYield = new TF1("fYield","[0] +[1]*x+[2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x + [6]*x*x*x*x*x + [7]*x*x*x*x*x*x",-2,2);
  gYield->Fit(fYield,"","",-0.5,2);
  c2->Print("LambdaYield.pdf");
  
  for (int i=0; i<nYBins-1; i++) {
//    cout<<fYield->Integral(y_bins_cms[i],y_bins_cms[i+1])/(y_bins_cms[i+1]-y_bins_cms[i])<<endl;
    cout<<y_bins_cms[i]<<"   "<<y_bins_cms[i+1]<<endl;
    cout<<fYield->Mean(y_bins_cms[i],y_bins_cms[i+1])<<endl;
  }

  TCanvas *c3 = new TCanvas("c3");
  TH2D *hTemp = new TH2D("Temp","",10,-1.5,1.5,1000,-0.3,0.3);
  hTemp->GetXaxis()->SetTitle("y_{LAB} #minus y_{c.m.}");
  hTemp->GetYaxis()->SetTitle("v_{1}");
  hTemp->Draw();
  
  TGraphErrors *gFlow = new TGraphErrors(nYBins-1,ypos,Flow,0,FlowError);
  TF1 *g = new TF1("g","[0]*x+[1]*x*x*x",-2,2);
  g->SetParName(0,"F");
  g->SetParName(1,"F_{3}");
  
  if(linear) g->FixParameter(1,0);
  gFlow->Fit("g","0","",-0.5,2);
  TF1 *fConv = new TF1("fConv","fYield*g",-2,2);
  double par[9];
  fYield->GetParameters(par);
  par[8] = g->GetParameter(0);
  par[9] = g->GetParameter(1);
  fConv->SetParameters(par);
  double newpos[nYBins-1];
  for (int i=0; i<nYBins-1; i++) {
    newpos[i] = g->GetX(fConv->Integral(y_bins_cms[i],y_bins_cms[i+1])/fYield->Integral(y_bins_cms[i],y_bins_cms[i+1]), y_bins_cms[i],y_bins_cms[i+1]);
  }
  TGraphErrors *gFlow2 = new TGraphErrors(nYBins-1,newpos,Flow,0,FlowError);
  gFlow2->Fit("g","0","",-0.5,2);
  par[8] = g->GetParameter(0);
  par[9] = g->GetParameter(1);
  fConv->SetParameters(par);
  double newpos2[nYBins-1];
  for (int i=0; i<nYBins-1; i++) {
    newpos2[i] = g->GetX(fConv->Integral(y_bins_cms[i],y_bins_cms[i+1])/fYield->Integral(y_bins_cms[i],y_bins_cms[i+1]), y_bins_cms[i],y_bins_cms[i+1]);
  }
  TGraphErrors *gFlow3 = new TGraphErrors(nYBins-1,newpos2,Flow,0,FlowError);
  gFlow3->Fit("g","0","",-0.5,2);
  par[8] = g->GetParameter(0);
  par[9] = g->GetParameter(1);
  fConv->SetParameters(par);
  double newpos3[nYBins-1];
  for (int i=0; i<nYBins-1; i++) {
    newpos3[i] = g->GetX(fConv->Integral(y_bins_cms[i],y_bins_cms[i+1])/fYield->Integral(y_bins_cms[i],y_bins_cms[i+1]), y_bins_cms[i],y_bins_cms[i+1]);
  }
  TGraphErrors *gFlow4 = new TGraphErrors(nYBins-1,newpos3,Flow,0,FlowError);
  gFlow4->SetMarkerStyle(8);
  gFlow4->Draw("Psame");
  
  TFitResultPtr fitPointer = gFlow4->Fit("g","0VS","",-0.5,2);
  TF1 *f2 = new TF1("f1","[0]*x+[1]*x*x*x",-2,2);
  TF1 *f3 = new TF1("f2","[0]*x+[1]*x*x*x",-2,2);
  TMatrixDSym cov = fitPointer->GetCovarianceMatrix();
  int NP = 2; //define number of parameters
  double *covArray = new double[NP*NP]; // number of parameters x number of parameters
  covArray = cov.GetMatrixArray();
  double* fCov = new double[NP*NP];
  fCov = cov.GetMatrixArray();
  double* fCovSqrt = new double[NP*NP];
  CalcCholesky(NP, fCov, fCovSqrt);
  Double_t yup[100];
  Double_t ydown[100];
  for (int i=0; i<nYBins-1; i++) {
    TH1D *hDistributionAtX = new TH1D("hDistributionAtX","",1000,-0.5,0.5);
    for (int j=0; j<10000; j++) {
      hDistributionAtX->Fill(RANDOM(newpos3[i],g,NP,fCovSqrt));
    }
    yup[i] = g->Eval(newpos3[i]) + hDistributionAtX->GetRMS();
    ydown[i] = g->Eval(newpos3[i]) - hDistributionAtX->GetRMS();
    hDistributionAtX->Delete();
//    cout<<yup[i]<<"  "<<g->Eval(x[i])<<"  "<<ydown[i]<<endl;

  }
  TGraph *gUp = new TGraph(nYBins-1,newpos3,yup);
  TGraph *gDown = new TGraph(nYBins-1,newpos3,ydown);
  gUp->SetMarkerStyle(2);
  gDown->SetMarkerStyle(2);
//  gUp->Draw("lsame");
//  gDown->Draw("lsame");
  
  gUp->Fit(f2,"R","");
  gDown->Fit(f3,"R","");
  f2->SetLineColor(kBlue);
  f3->SetLineColor(kOrange+2);
  f2->SetLineWidth(1);
  f3->SetLineWidth(1);
  f2->Draw("same");
  f3->Draw("same");
  
  
  
  for (int h=0; h<nYBins-1; h++) yposreflected[h] = -newpos3[h];
  TGraphErrors *gFlowReflected = new TGraphErrors(nYBins-1,yposreflected,FlowReflected,0,FlowError);
  gFlowReflected->SetMarkerStyle(4);
  gFlowReflected->Draw("Psame");
  
  
//  TF1 *f = new TF1("f","[0]*x+[1]",-2,2);
//  gFlow->Fit("f","","",0,2);
//  TF1 *ftodraw = new TF1("ftodraw","[0]*x",0,2);
//  ftodraw->SetParameter(0,f->GetParameter(0));
//  TF1 *ftodrawreflected = new TF1("ftodrawreflected","[0]*x",-2,0);
//  ftodrawreflected->SetParameter(0,f->GetParameter(0));
//  ftodrawreflected->SetLineStyle(2);

  TF1 *gtodraw = new TF1("gtodraw","[0]*x+[1]*x*x*x",0,2);
  gtodraw->SetLineColor(kGreen+2);
  gtodraw->SetLineWidth(1);
  gtodraw->SetParameter(0,g->GetParameter(0));
  gtodraw->SetParameter(1,g->GetParameter(1));
  TF1 *gtodrawreflected = new TF1("gtodrawreflected","[0]*x+[1]*x*x*x",-2,0);
  gtodrawreflected->SetLineColor(kGreen+2);
  gtodrawreflected->SetLineWidth(1);
  gtodrawreflected->SetParameter(0,g->GetParameter(0));
  gtodrawreflected->SetParameter(1,g->GetParameter(1));
  gtodrawreflected->SetLineStyle(2);

//  ftodraw->Draw("same");
//  ftodrawreflected->Draw("same");
  gtodraw->Draw("same");
  gtodrawreflected->Draw("same");
  TLine *lx0 = new TLine(0,-0.3,0,0.3);
  lx0->SetLineStyle(2);
  
  TLine *ly0 = new TLine(-1.5,0,1.5,0);
  ly0->SetLineWidth(2);
  lx0->Draw();
  ly0->Draw();
  c3->Update();
  TPaveStats *st = (TPaveStats*)c3->GetPrimitive("stats");
  st->SetX1NDC(0.18);
  st->SetX2NDC(0.54);
  st->SetY1NDC(0.65);
  st->SetY2NDC(0.85);
  cout<<"Slope at 0 : "<<g->Derivative(0)<<endl;
  cout<<"Upper Limit: "<<f2->Derivative(0)<<endl;
  cout<<"Lower Limit: "<<f3->Derivative(0)<<endl;
  cout<<"Chi Square of the fit:"<<g->GetChisquare()/g->GetNDF()<<endl;

  TFile *output = new TFile("BackgroundFlowLambda.root","recreate");
  gFlow4->SetName("BgLambdaFlow");
  gFlow4->Write();
  gFlowReflected->SetName("BgLambdaFlowReflectedToDraw");
  gFlowReflected->Write();
  g->SetName("fitFunctionOfBgLambda");
  g->Write();
  f2->SetName("UpperLimit");
  f3->SetName("LowerLimit");
  f2->Write();
  f3->Write();
  c3->Write();
  output->Close();

//  TFitResultPtr fitPointer = gV1Cent1->Fit(f1,"RVS","");

  
  
  
  
  
  
  
  
}