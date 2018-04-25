#include "fit.C"
void doProjections(TH3D* num, TH3D* fitNum, TH3D* den, TH1D** projCF, TH1D** projFitCF, const Double_t normalization, const Double_t projRange);
void projectHistogram(TH3D* fullHist, TH1D** projHist, Float_t projRange);
void readData(TH3D* &num, TH3D* &den, TH3D* &coul, const TString inFile, const Int_t pm, const Int_t ktBin, const Int_t phiBin);
void writeTGraphs(TMinuit* minuit, const Int_t binNumber, const Float_t xValue);
TH3D* histCopy(TH3* hist, TString nameTitle);

void fitManager(
    const TString inputfile = "bin0.root",  //input file
    const TString outFileName = "testOut.root",  //output file
    const Int_t pm = 1,
    const Int_t ktBin = 0,
    const Int_t multBin = 0,
    const Double_t fitRange = 0.149,
    const Double_t projRange = 0.03,
    const Double_t initNorm = 0.1689, 
    const Double_t initLambda = 0.5, 
    const Double_t initRo = 38.1, 
    const Double_t initRs = 27.0, 
    const Double_t initRl = 49.9, 
    const Double_t initRos = -0.259, 
    const Double_t initRol = 0, 
    const Double_t initRsl = 0 
    )
{

    TH3D* num;
    TH3D* den;
    TH3D* coul;
    TH3D* fitNum;

    readData(num,den,coul,inputfile.Data(),pm,ktBin,0);
    coul->Divide(den);


    Int_t nFitPars = 8;
    Double_t fitPars[8] = {0.};
    Double_t fitParErrors[8] = {0.};
	TMinuit* minuit = new TMinuit(nFitPars);

    //Do the fit
    // gROOT->LoadMacro("fit.C");
    TStopwatch* fitTimer = new TStopwatch();
    fit(num, den, coul, nFitPars, fitRange, minuit, initNorm, initLambda, initRo, initRs, initRl, initRos, initRol, initRsl);
    cout << "\nFit took " << fitTimer->RealTime() << " seconds to finish.\n\n";

    for (Int_t i = 0; i <= 7; ++i) { minuit->GetParameter(i, fitPars[i], fitParErrors[i]); }

    //Project histograms
    fitNum = histCopy(den, "Theoretical Numerator");
    makeFitNumerator(fitNum, den, coul, fitPars);

    TH1D* projectedCF[3];
    TH1D* projectedFitCF[3];

    TFile* outFile = new TFile(outFileName.Data(),"UPDATE");
    outFile->mkdir(TString::Format("%d",multBin));
    outFile->cd(TString::Format("%d",multBin));

    doProjections(num, fitNum, den, projectedCF, projectedFitCF, fitPars[0], projRange);

    // Save fit parameters to TGraphs
    // const Float_t multCut[7] = {47.5, 60.5, 76.5, 96.5, 120.5, 153.5, 1000}; // Official cut values
    const Float_t multCut[7] = {54, 67, 87, 109, 137, 160}; // Super unofficial bin averages
    const Float_t ktCut[4] = {0.173,0.215,0.263,0.341};
    gDirectory->cd("..");
    // writeTGraphs(minuit, ktBin, ktCut[ktBin]);
    writeTGraphs(minuit, multBin, multCut[multBin]);

    outFile->Close();
}

TH3D* histCopy(TH3* hist, TString nameTitle)
{

    Int_t nBins = hist->GetNbinsX();   
    Double_t lo = hist->GetXaxis()->GetXmin();
    Double_t hi = hist->GetXaxis()->GetXmax();

    TH3D* rHist = new TH3D(nameTitle.Data(),nameTitle.Data(),nBins,lo,hi,nBins,lo,hi,nBins,lo,hi);

    return rHist;

}

void readData(TH3D* &num, TH3D* &den, TH3D* &coul, const TString inFile, const Int_t pm, const Int_t ktBin, const Int_t phiBin)
{

    // Create histogram names
    Int_t phiLabels[8] = {0,22,45,67,90,112,135,157};
//    Int_t phiLabels[4] = {0,45,90,135};
    Float_t ktLabels[4] = {0.22,0.33,0.42,0.52};
    TString histNames[6] = { "NumPiPlus" , "DenPiPlus" , "CoulPiPlus" , "NumPiMinus" , "DenPiMinus" , "CoulPiMinus" };


    for(Int_t i = 0; i <= 5; i++)
    {
        if(phiBin >= 0) {histNames[i] += "_phi"; histNames[i] += phiLabels[phiBin];}

        histNames[i] += "_kt";
        histNames[i] += ktBin;

    }

    // Get histograms from input file
	TFile* file = new TFile(inFile.Data());
    TH3S* pNum = (TH3S*)file->Get(histNames[0].Data());
    TH3S* pDen = (TH3S*)file->Get(histNames[1].Data());
    TH3D* pCoul = (TH3D*)file->Get(histNames[2].Data());
    TH3S* mNum = (TH3S*)file->Get(histNames[3].Data());
    TH3S* mDen = (TH3S*)file->Get(histNames[4].Data());
    TH3D* mCoul = (TH3D*)file->Get(histNames[5].Data());

    num = histCopy(pNum, "Numerator");
    den = histCopy(pDen, "Denominator");
    coul = histCopy(pCoul, "Coulomb");

	if( pm != -1 )
	{
		num->Add(pNum);
		den->Add(pDen);
		coul->Add(pCoul);
	}

	if( pm != 1 )
	{
		num->Add(mNum);
		den->Add(mDen);
		coul->Add(mCoul);
	}

    cout << num->GetEntries() << endl;
}

void projectHistogram(TH3D* fullHist, TH1D** projHist, Float_t projRange)
{
    Double_t fullMin = fullHist->GetXaxis()->GetXmin();
    Double_t fullMax = fullHist->GetXaxis()->GetXmax();

    // Do x-projection
    fullHist->SetAxisRange(fullMin, fullMax, "x");
    fullHist->SetAxisRange(-1.*projRange, projRange, "y");
    fullHist->SetAxisRange(-1.*projRange, projRange, "z");
    projHist[0] = (TH1D*)fullHist->Project3D("xeNOFNUF");

    // Do y-projection
    fullHist->SetAxisRange(fullMin, fullMax, "y");
    fullHist->SetAxisRange(-1.*projRange, projRange, "x");
    fullHist->SetAxisRange(-1.*projRange, projRange, "z");
    projHist[1] = (TH1D*)fullHist->Project3D("yeNOFNUF");

    // Do z-projection
    fullHist->SetAxisRange(fullMin, fullMax, "z");
    fullHist->SetAxisRange(-1.*projRange, projRange, "x");
    fullHist->SetAxisRange(-1.*projRange, projRange, "y");
    projHist[2] = (TH1D*)fullHist->Project3D("zeNOFNUF");
}

void doProjections(TH3D* num, TH3D* fitNum, TH3D* den, TH1D** projCF, TH1D** projFitCF, const Double_t normalization, const Double_t projRange)
{
    TH1D* projectedNum[3];
    TH1D* projectedFitNum[3];
    TH1D* projectedDen[3];

    projectHistogram(num, projectedNum, projRange);
    projectHistogram(fitNum, projectedFitNum, projRange);
    projectHistogram(den, projectedDen, projRange);

    TString histNames[3] = {"qOut", "qSide", "qLong"};

    for (Int_t i = 0; i <= 2; ++i)
    {
        projCF[i] = new TH1D(*projectedNum[i]);
        projCF[i]->Divide(projectedDen[i]);
        projCF[i]->Scale(1.0/normalization);
        projCF[i]->SetNameTitle(histNames[i].Data(), histNames[i].Data());
        
        projFitCF[i] = new TH1D(*projectedFitNum[i]);
        projFitCF[i]->Divide(projectedDen[i]);
        histNames[i] += "Fit";
        projFitCF[i]->SetNameTitle(histNames[i].Data(), histNames[i].Data());

        // Some basic graphics options
        projCF[i]->SetMarkerStyle(kFullTriangleUp);
        projCF[i]->SetMarkerColor(kBlue);
        projCF[i]->SetMaximum(1.4);
        projCF[i]->SetMinimum(0.9);
        
        projFitCF[i]->SetMarkerColor(kRed);
        projFitCF[i]->SetLineColor(kRed);
        projFitCF[i]->SetLineWidth(2);
        projFitCF[i]->SetMaximum(1.4);
        projFitCF[i]->SetMinimum(0.9);

        //Write the histograms
        projCF[i]->Write();
        projFitCF[i]->Write();

        delete projCF[i];
        delete projFitCF[i];
        
    }

}

void writeTGraphs(TMinuit* minuit, const Int_t binNumber, const Float_t xValue)
{

    const Int_t nMultBins = 6;
    Double_t fitParameters[8] = {0.};
    Double_t fitParameterErrors[8] = {0.};

    for (Int_t i = 0; i <= 7; ++i) { minuit->GetParameter(i, fitParameters[i], fitParameterErrors[i]); }

    TGraphErrors* graphs[13];
    TString graphNames[13] = {"norm", "lam", "Ro^2", "Rs^2", "Rl^2", "Ros^2", "Rol^2", "Rsl^2", "Ro", "Rs", "Rl", "RoOverRs", "Ro2MinusRs2"};
    TString graphTitles[13] = {"Normalization", "#lambda", "R_{o}^{2}", "R_{s}^{2}", "R_{l}^{2}", "R_{os}^{2}", "R_{ol}^{2}", "R_{sl}^{2}", "R_{o}", "R_{s}", "R_{l}", "R_{o} / R_{s}", "R_{o}^{2} - R_{s}^{2}"};
    for (Int_t i = 0; i <= 12; ++i)
    {

        graphs[i] = (TGraphErrors*)gDirectory->Get(graphNames[i].Data());

        // If the TGraphErrors's don't already exist, create them
        if(!graphs[i]) 
        {
            graphs[i] = new TGraphErrors(nMultBins);
            graphs[i]->SetNameTitle(graphNames[i].Data(), graphTitles[i].Data());

        } else { // If they *do* exist, delete the old copies so we don't get a bunch of duplicates
            TString nameCycle = graphNames[i];
            nameCycle += ";1";
            gDirectory->Delete(nameCycle.Data());
        }
        
    }

    // The first 8 TGraphErrors correspond directly to fit parameters. Just copy them over
    for (Int_t i = 0; i <= 7; ++i)
    {
        graphs[i]->SetPoint(binNumber, xValue, fitParameters[i]);
        graphs[i]->SetPointError(binNumber, 0, fitParameterErrors[i]);
    }

    // For Ro/Rs/Rl, we just take the square roots of the values
    for (Int_t i = 8; i <= 10; ++i)
    {
        Double_t yValue = sqrt(fitParameters[i-6]);
        Double_t yValueError = fitParameterErrors[i-6] / (2*yValue);
        graphs[i]->SetPoint(binNumber, xValue, yValue);
        graphs[i]->SetPointError(binNumber, 0, yValueError);
    }

    // (Ro^2 - Rs^2) and (Ro/Rs) are a little trickier
    Double_t Ro2MinusRs2 = fitParameters[2] - fitParameters[3];
    Double_t Ro2MinusRs2Error = sqrt(fitParameters[2]*fitParameters[2] + fitParameters[3]*fitParameters[3]);
    graphs[11]->SetPoint(binNumber, xValue, Ro2MinusRs2);
    graphs[11]->SetPointError(binNumber, 0, Ro2MinusRs2Error);

    Double_t Ro = sqrt(fitParameters[2]);
    Double_t RoErr = fitParameterErrors[2] / (2*Ro);
    Double_t Rs = sqrt(fitParameters[3]);
    Double_t RsErr = fitParameterErrors[3] / (2*Rs);
    Double_t RoOverRs = Ro / Rs;
    Double_t RoOverRsErr = (Ro/Rs) * sqrt( (RoErr/Ro)*(RoErr/Ro) + (RsErr/Rs)*(RsErr/Rs) );
    graphs[12]->SetPoint(binNumber, xValue, RoOverRs);
    graphs[12]->SetPointError(binNumber, 0, RoOverRsErr);


    for (Int_t i = 0; i <= 12; ++i)
    {
        graphs[i]->Write(graphs[i]->GetName(), 2);
        delete graphs[i];
        
    }

}
