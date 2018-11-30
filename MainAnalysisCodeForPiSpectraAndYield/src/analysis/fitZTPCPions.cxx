//Extracts the yield of pion minus and pion plus mesons.

#include <iostream>
#include <vector>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH3D.h>
#include <TF1.h>
#include <TClonesArray.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TLine.h>
#include <TGraphErrors.h>
#include <TPaveText.h>
#include <TPaveStats.h>
#include <TLegend.h>
#include <TVirtualFitter.h>
#include <TLatex.h>

#include "globalDefinitions.h"
#include "ParticleInfo.h"
#include "TrackInfo.h"
#include "PrimaryVertexInfo.h"
#include "EventInfo.h"

#include "utilityFunctions.h"
#include "fitZTPCUtilities.h"

//-------FUNCTIONS DEFINED BELOW MAIN ------
void FitPionMinus();
void DrawPredictionLines(TCanvas *canvas);
void ComputeBinKinematics(Int_t mTm0Index, Double_t y, Int_t PID);
Bool_t AddPointToSpectra(TH1D *yieldHisto, TF1 *yieldFit, TGraphErrors *rawSpectra, Int_t yIndex,
			 Int_t mTm0Index, Int_t PID, Int_t CHARGE, TString IMAGEDIR="");

//-------GLOBALS--------

//Save?
Bool_t SAVEOBJ = true;
Bool_t SAVEIMG = true;
Bool_t DEBUG   = false;

//Canvases
TCanvas *fittingCanvas, *fitParCanvas, *fitParCanvas2, *spectraCanvas, *confCanvas;

//Particle Parameterizations and predictions
ParticleInfo *particleInfo;
ParticlePars *pion, *kaon, *proton, *electron;
TLine *pionLine, *kaonLine,*protonLine, *electronLine;
Double_t rapidity, mTm0, mT, pZ, pT, pTotal;
Double_t pionPredict, kaonPredict, protonPredict, electronPredict, deuteronPredict;
Double_t lineHeight;

//ZTPC Variable Histograms
std::vector<std::vector<TH1D *> > tpcPionMinusHisto(nRapidityBins,std::vector<TH1D *>(nmTm0Bins,(TH1D *)NULL));
std::vector<std::vector<TH1D *> > tpcPionPlusHisto(nRapidityBins,std::vector<TH1D *>(nmTm0Bins,(TH1D *)NULL));

//Fit Functions
std::vector<std::vector<TF1 *> > tpcPionMinusFit(nRapidityBins,std::vector<TF1 *>(nmTm0Bins,(TF1 *)NULL));
std::vector<std::vector<TF1 *> > tpcPionPlusFit(nRapidityBins,std::vector<TF1 *>(nmTm0Bins,(TF1 *)NULL));

//Raw Spectra
std::vector<TGraphErrors *> rawSpectraMinus(nRapidityBins,(TGraphErrors *)NULL);
std::vector<TGraphErrors *> rawSpectraPlus(nRapidityBins,(TGraphErrors *)NULL);

//Number of Events Histogram
TH1D *nEventsHisto;

//Species Controls
Bool_t killElectron;

//Spectra

//User Specified Indices
Int_t rapidityIndex;
Int_t centralityIndex;

//-------MAIN-------
void fitZTPCPions(TString ZTPCFILE, TString SPECTRAFILE, TString STARLIB, Int_t CENTRALITYINDEX,
                 Int_t RAPIDITYINDEX=-1, TString IMAGEDIR=""){

  //If the ImageDir argument is empty then turn off saving images                            
  if (!IMAGEDIR.CompareTo("") && SAVEIMG == true)
	    SAVEIMG = false;
 
  //If we are going to save images then create subdirectories                           
  if (SAVEIMG && !gSystem->OpenDirectory(IMAGEDIR+"/PionPlus/")){
    gSystem->mkdir(IMAGEDIR+"/PionPlus/");
  }
  if (SAVEIMG && !gSystem->OpenDirectory(IMAGEDIR+"PionMinus/")){
    gSystem->mkdir(IMAGEDIR+"/PionMinus/");
  }

  if (DEBUG && !gSystem->OpenDirectory(IMAGEDIR+"Debug/")) gSystem->mkdir(IMAGEDIR+"/Debug/");

  //Pass the Value of the user's input indices to the globals
  rapidityIndex = RAPIDITYINDEX;
  centralityIndex = CENTRALITYINDEX;

  killElectron = false;

  //Create the Particle Info Object which has all the Bichesl Curves
  particleInfo = new ParticleInfo(STARLIB,true);

  //Create the Output file and its directory structure
  TFile *outFile = new TFile(SPECTRAFILE,"RECREATE");
  if (SAVEOBJ){
    outFile->mkdir(Form("RawSpectra_%s",particleInfo->GetParticleName(PION,-1).Data()));
    outFile->mkdir(Form("RawSpectra_%s",particleInfo->GetParticleName(PION,1).Data()));
    outFile->mkdir("FitParameterizations");
  }
  
  //Create the Particle Parameterization Objects
  pion = new ParticlePars();
  kaon = new ParticlePars();
  proton = new ParticlePars();
  electron = new ParticlePars();
  
  DefineParticlePars(pion,"Pion");
  DefineParticlePars(kaon,"Kaon");
  DefineParticlePars(proton,"Proton");
  DefineParticlePars(electron,"Electron");

  //Particle ZTPC Prediction Lines
  pionLine = new TLine();
  kaonLine = new TLine();
  protonLine = new TLine();
  electronLine = new TLine();

  pionLine->SetLineColor(particleInfo->GetParticleColor(PION));
  kaonLine->SetLineColor(particleInfo->GetParticleColor(KAON));
  protonLine->SetLineColor(particleInfo->GetParticleColor(PROTON));
  electronLine->SetLineColor(particleInfo->GetParticleColor(ELECTRON));

  pionLine->SetLineWidth(2);
  kaonLine->SetLineWidth(2);
  protonLine->SetLineWidth(2);
  electronLine->SetLineWidth(2);

  //Get the Yield Histogram file and Get the 3D Z Histograms 
  TFile *inFile = new TFile(ZTPCFILE,"READ");
  TH3D *pionPlusZTPC3D = (TH3D *)inFile->Get(Form("PionPlus/zTPC_PionPlus_Cent%d",centralityIndex));
  TH3D *pionMinusZTPC3D = (TH3D *)inFile->Get(Form("PionMinus/zTPC_PionMinus_Cent%d",centralityIndex));
  LoadYieldHistograms(pionPlusZTPC3D,&tpcPionPlusHisto,"TPC",rapidityIndex);
  LoadYieldHistograms(pionMinusZTPC3D,&tpcPionMinusHisto,"TPC",rapidityIndex);
  nEventsHisto = (TH1D *)inFile->Get("nEvents");
     
  //Set Style Options
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(112);

  //Create Global Canvases
  fittingCanvas = new TCanvas("fittingCanvas","Fitting Canvas",20,20,800,600);
  fittingCanvas->SetLogy();
  fitParCanvas = new TCanvas("fitParCanvas","Fit Parameter Canvas",20,20,1000,1000);
  fitParCanvas->Divide(3,3);
  fitParCanvas2 = new TCanvas("fitParCanvas2","Fit Parameter Canvas 2",20,20,1000,1000);
  fitParCanvas2->Divide(3,3);
  spectraCanvas = new TCanvas("spectraCanvas","Spectra Canvas",20,850,800,600);
  spectraCanvas->SetLogy();
  confCanvas = new TCanvas("confCanvas","Width Confidence Interval Canvas",20,20,800,600);
  
  //Fit the Pion Minuses
  FitPionMinus();

  //Make the Pion Minus Spectra
  for (Int_t yIndex=2; yIndex<=18; yIndex++){
    
    //If the user has specified a rapidityIndex then only do that index
    if (rapidityIndex >= 0 && yIndex != rapidityIndex)
      continue;

    for (Int_t mTm0Index=2; mTm0Index<20; mTm0Index++){//56

      //If the spectra doesn't exist already then make it
      if (!rawSpectraMinus.at(yIndex)){
	
	rawSpectraMinus.at(yIndex) = new TGraphErrors();
	rawSpectraMinus.at(yIndex)->SetMarkerStyle(20);
	rawSpectraMinus.at(yIndex)->SetName(Form("rawSpectra_%s_Cent%02d_yIndex%02d",
						 particleInfo->GetParticleName(PION,-1).Data(),
						 centralityIndex,yIndex));
      }

      //Add the yield from this mT-m0 bin to the spectrum
			Bool_t success;
      if (!DEBUG) success = AddPointToSpectra(tpcPionMinusHisto.at(yIndex).at(mTm0Index),
					 tpcPionMinusFit.at(yIndex).at(mTm0Index),
					 rawSpectraMinus.at(yIndex),
					 yIndex,mTm0Index,PION,-1,IMAGEDIR);

      if (!DEBUG && !success)
	continue;
      
    }//End Loop Over mTm0Index

    //Save the Spectra
    if (!DEBUG && rawSpectraMinus.at(yIndex)->GetN() > 3 && SAVEOBJ){
      outFile->cd();
      outFile->cd(Form("RawSpectra_%s",particleInfo->GetParticleName(PION,-1).Data()));
      rawSpectraMinus.at(yIndex)->Write();
    }
    
  }//End Loop Over yIndex

	//Save fit parameterizations
  for (Int_t yIndex=2; yIndex<=18; yIndex++){

    //If the user has specified a rapidityIndex then only do that index
    if (rapidityIndex >= 0 && yIndex != rapidityIndex)
      continue;
		
    //Save the Parameterizations
    if (SAVEOBJ){
      outFile->cd();
      outFile->cd("FitParameterizations");
      pion->mean[yIndex]->Write();
      pion->width[yIndex]->Write();
      pion->widthConf[yIndex]->Write();
      electron->amp[yIndex]->Write();
      electron->mean[yIndex]->Write();
      electron->width[yIndex]->Write();
      electron->widthConf[yIndex]->Write();
    }
    
  }//End Loop Over yIndex
  
}


//------------------------------------------------------------------------
void FitPionMinus(){

  //Local Variables
  TH1D *yieldHisto = NULL;
  TF1 *yieldFit   = NULL;

  for (Int_t yIndex=2; yIndex<=18; yIndex++){

    //If the user has specified a rapidityIndex then only do that index
    if (rapidityIndex >= 0 && yIndex != rapidityIndex)
      continue;

    //Compute the Rapidity
    rapidity = GetRapidityRangeCenter(yIndex);
    
    cout <<"Working on Rapidity Index: " <<yIndex <<" Rapidity: " <<rapidity <<endl;

    //----- ROUND 1 - PARAMETERIZE THE PION WIDTH -----
    for (Int_t mTm0Index=2; mTm0Index<20; mTm0Index++){//56

      //Make sure the histogram exists
      if (!tpcPionMinusHisto.at(yIndex).at(mTm0Index))
	continue;

      //Pass the histogram to a local pointer
      yieldHisto = tpcPionMinusHisto.at(yIndex).at(mTm0Index);
      yieldHisto->SetAxisRange(-1,2.5);

      //Make sure it has enough entries
      if (yieldHisto->GetEntries() < 100)
	continue;

      //Compute the kinematics for this bin
      ComputeBinKinematics(mTm0Index,rapidity,PION);
       
      //Make the Predictions for the particle species
      pionPredict = particleInfo->PredictZTPC(pTotal,PION,PION);
      kaonPredict = particleInfo->PredictZTPC(pTotal,PION,KAON);
      protonPredict = particleInfo->PredictZTPC(pTotal,PION,PROTON);
      electronPredict = particleInfo->PredictZTPC(pTotal,PION,ELECTRON);


      //Stop if any of the confounding particles are overlapping
      if (electronPredict < pionPredict) continue;
			
      //Create the Fit and pass it to a local pointer
      if (!tpcPionMinusFit.at(yIndex).at(mTm0Index)){
	tpcPionMinusFit.at(yIndex).at(mTm0Index) = new TF1("","gaus(0)",-.2,.11);//.125
	yieldFit = tpcPionMinusFit.at(yIndex).at(mTm0Index);
      }

      //Draw the Histogram
      fittingCanvas->cd();
      tpcPionMinusHisto.at(yIndex).at(mTm0Index)->Draw("E");
      
      //Set the Parameters of the Fit Function
      yieldFit->SetParameter(0,yieldHisto->GetBinContent(yieldHisto->FindBin(0)));
      yieldFit->SetParameter(1,particleInfo->PredictZTPC(pTotal,PION,PION));
      yieldFit->SetParameter(2,.08);

      //Fit the Histogram
      yieldHisto->Fit(yieldFit,"RQ");

      //Draw the Prediction Lines
      lineHeight = yieldHisto->GetBinContent(yieldHisto->FindBin(pionPredict));
      if (!DEBUG) DrawPredictionLines(fittingCanvas);
      if (!DEBUG) fittingCanvas->Update();

      //Add the Mean and Width to their respective graphs
      AddPointToParGraph(pion->mean[yIndex],yieldFit,1,mTm0Index);
      AddPointToParGraph(pion->width[yIndex],yieldFit,2,mTm0Index);
      fitParCanvas->cd(2);
      pion->mean[yIndex]->Draw("APZ");
      fitParCanvas->cd(3);
      pion->width[yIndex]->Draw("APZ");
      if (!DEBUG) fitParCanvas->Update();

      //gSystem->Sleep(100);

    }//End Loop Over mTm0Index

    //Check to make sure there are entries in the parameter graphs
    if (pion->width[yIndex]->GetN() < 1){
      cout <<"fitZTPCPions.cxx:FitPionMinus() WARNING: No successful parameterizations for rapidity index: "
	   <<yIndex <<", rapidity = " <<rapidity <<endl;
      continue;
    }
    

    //Get the Maximum mTm0 from the graph and use it as a bound on the parameter
    Double_t max = pion->width[yIndex]->GetX()[pion->width[yIndex]->GetN()-1];

    //Fit the Pion Width as a function of mTm0
    pion->widthFit[yIndex] = new TF1(Form("pionMinus_WidthFit_%02d",yIndex),
                                     SwooshFunc,.05,max,4);
    pion->widthFit[yIndex]->SetParameters(0.071,0.8,0.2,0.1);
		if (yIndex == 5)  pion->widthFit[yIndex]->SetParLimits(2,0.2,0.4); //
		if (yIndex == 18) pion->widthFit[yIndex]->SetParLimits(2,0.5,0.8);
    pion->widthFit[yIndex]->SetParLimits(2,.0,1);
    pion->widthFit[yIndex]->SetParLimits(3,.0,2.0);
    pion->widthFit[yIndex]->SetNpx(10000);      
    
    fitParCanvas->cd(3);
    pion->width[yIndex]->Fit(pion->widthFit[yIndex],"RQ");

    pion->meanFit[yIndex] = new TF1(Form("pionMinus_MeanFit_%02d",yIndex),
                                     SwooshFunc,.05,max,4);
    pion->meanFit[yIndex]->SetParameters(0.02,0.7,0.4,-0.1);
    pion->meanFit[yIndex]->SetNpx(10000);      

    fitParCanvas->cd(2);
    pion->mean[yIndex]->Fit(pion->meanFit[yIndex],"RQ");

    fitParCanvas->Update();

    //Determine Confidence Interval 
    Double_t minRange = pion->width[yIndex]->GetX()[0];;
    Double_t maxRange = max;

    pion->widthConf[yIndex]->Set(pion->widthFit[yIndex]->GetNpx());  
    Double_t step = (maxRange-minRange)/(double)pion->widthConf[yIndex]->GetN();                                                                                   
    for (int i=0; i<pion->widthConf[yIndex]->GetN(); i++){                                                               
      pion->widthConf[yIndex]->SetPoint(i,minRange + i*step,0);                                                                 
    }                                                                                                                                                                 
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(pion->widthConf[yIndex],.95);//.68);
    pion->widthConf[yIndex]->SetFillColor(kOrange);                                                                                       
    pion->widthConf[yIndex]->SetFillStyle(3001); 

    //Graph Width Confidence Interval
    confCanvas->cd(); 
    pion->widthConf[yIndex]->Draw(); //A=>without axis. Not sure what Z is, P not applicable 
    if (!DEBUG) confCanvas->Update();
    
    cout <<"Finished Parameterizing the Pion Width!" <<endl;


    //----- ROUND 2 - PARAMETERIZE THE ELECTRON MEAN AND WIDTH -----
    for (Int_t mTm0Index=2; mTm0Index<20; mTm0Index++){//56

      //Make sure the histogram exists
      if (!tpcPionMinusHisto.at(yIndex).at(mTm0Index))
	continue;

      //Pass the histogram to a local pointer
      yieldHisto = tpcPionMinusHisto.at(yIndex).at(mTm0Index);
      yieldHisto->SetAxisRange(-1,2.5);

      //Make sure it has enough entries
      if (yieldHisto->GetEntries() < 100)
	continue;

      //Compute the kinematics for this bin
      ComputeBinKinematics(mTm0Index,rapidity,PION);
      
      //Make the Predictions for the particle species
      pionPredict = particleInfo->PredictZTPC(pTotal,PION,PION);
      kaonPredict = particleInfo->PredictZTPC(pTotal,PION,KAON);
      protonPredict = particleInfo->PredictZTPC(pTotal,PION,PROTON);
      electronPredict = particleInfo->PredictZTPC(pTotal,PION,ELECTRON);

      //Stop if any of the confounding particles are overlapping
      if (electronPredict < pionPredict) continue;
      if (fabs(electronPredict-kaonPredict) < 2*.08)
	continue;
      
      //Stop at this mTm0
      if (mTm0 > 0.5)
	break;

      //Get the Previous Pion Mean
      Double_t pionMeanPrev = pion->meanFit[yIndex]->Eval(mTm0);
      
      //Create the Fit and pass it to a local pointer
      if (tpcPionMinusFit.at(yIndex).at(mTm0Index))
	tpcPionMinusFit.at(yIndex).at(mTm0Index)->Delete();

      if (fabs(electronPredict-pionPredict) < 5*0.08) 
				tpcPionMinusFit.at(yIndex).at(mTm0Index) = new TF1("","gaus(0)+gaus(3)",-0.2,electronPredict+.15);

      else tpcPionMinusFit.at(yIndex).at(mTm0Index) = new TF1("","gaus(0)",electronPredict-0.1,electronPredict+.15);

      yieldFit = tpcPionMinusFit.at(yIndex).at(mTm0Index);

      //Electron Parameters
			Double_t eAmp = yieldHisto->GetBinContent(yieldHisto->FindBin(electronPredict));
			if (yIndex == 13) eAmp = yieldHisto->GetBinContent(yieldHisto->FindBin(electronPredict-0.06));
      yieldFit->SetParameter(0,eAmp);
      yieldFit->SetParameter(1,electronPredict);
      yieldFit->SetParameter(2,.08);
      yieldFit->SetParLimits(2,.06,.12);			     
      
      if (fabs(electronPredict-pionPredict) < 5*0.08){
			  yieldFit->SetParameter(3, yieldHisto->GetBinContent(yieldHisto->FindBin(pionMeanPrev)));
				yieldFit->FixParameter(4, pionMeanPrev);
				yieldFit->FixParameter(5, pion->widthFit[yIndex]->Eval(mTm0));
			}

      //Draw the Histogram
      fittingCanvas->cd();
      yieldHisto->Draw("E");

      //Fit the Yield Histogram
      yieldHisto->Fit(yieldFit,"RQ");

      //Draw the Prediction Lines
      lineHeight = yieldHisto->GetBinContent(yieldHisto->FindBin(pionPredict));
      if (!DEBUG) DrawPredictionLines(fittingCanvas);
      if (!DEBUG) fittingCanvas->Update();

      //Add the points to the fit par Graphs
      AddPointToParGraph(electron->mean[yIndex],yieldFit,1,mTm0Index);
      AddPointToParGraph(electron->width[yIndex],yieldFit,2,mTm0Index);

      //Draw the Parameter Graphs
      fitParCanvas->cd(5);
      electron->mean[yIndex]->Draw("APZ");
      fitParCanvas->cd(6);
      electron->width[yIndex]->Draw("APZ");
      if (!DEBUG) fitParCanvas->Update();

      //gSystem->Sleep(100);

    }//End Loop Over mTm0Index

    //Get the number of points in the electron mean graph and decide if it
    //should be killed or not
    if (electron->mean[yIndex]->GetN() < 5){
      killElectron = true;
      cout <<"INFO: fitZTPCPions.cxx:FitPionMinus(): The electron has ben killed due to too few points in the mean parameterization in rapidity index: " <<yIndex <<" rapidity = " <<rapidity <<endl;
    }

    //If the electron is not killed then fit its mean and width
    if (!killElectron){
      
      //Electron Mean
      max = electron->width[yIndex]->GetX()[electron->width[yIndex]->GetN()-1];
			
			if (yIndex == 13){
				electron->meanFit[yIndex] = new TF1(Form("electronMinus_MeanFit_%02d",yIndex),
							SwooshFunc,0.03,max,4);
				electron->meanFit[yIndex]->SetParameters(0.39,0.7,0.3,-0.1);
				electron->meanFit[yIndex]->SetNpx(10000);      
      }

      //Electron Width
      electron->widthFit[yIndex] = new TF1(Form("electronMinus_WidthFit_%02d",yIndex),
					   SwooshFunc,.05,1.0,4);
      electron->widthFit[yIndex]->SetParameters(.1,.5,.3,.1);
      electron->widthFit[yIndex]->SetParLimits(3,.0,3);
      electron->widthFit[yIndex]->SetNpx(10000);      

      //Get the Maximum mTm0 from the graph and use it as a bound on the parameter
      electron->widthFit[yIndex]->SetParLimits(2,.1,max);
    }
    else{
      if (yIndex == 13) electron->meanFit[yIndex] = NULL;
      electron->widthFit[yIndex] = NULL;
    }

    fitParCanvas->cd(5);
    if (yIndex == 13) electron->mean[yIndex]->Fit(electron->meanFit[yIndex],"R");
    fitParCanvas->cd(6);
    electron->width[yIndex]->Fit(electron->widthFit[yIndex],"R");
    fitParCanvas->Update();

    //Determine Confidence Interval
    minRange = electron->width[yIndex]->GetX()[0];
    maxRange = max;

    electron->widthConf[yIndex]->Set(electron->widthFit[yIndex]->GetNpx());  
    step = (maxRange-minRange)/(double)electron->widthConf[yIndex]->GetN();
    for (int i=0; i<electron->widthConf[yIndex]->GetN(); i++){
      electron->widthConf[yIndex]->SetPoint(i,minRange + i*step,0);
    }
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(electron->widthConf[yIndex],.68);
    electron->widthConf[yIndex]->SetFillColor(kOrange);
    electron->widthConf[yIndex]->SetFillStyle(3001);

    //Graph Width Confidence Interval
    confCanvas->cd();
    electron->widthConf[yIndex]->Draw(); //A=>without axis. Not sure what Z is, P not applicable
    if (!DEBUG) confCanvas->Update();
    
    cout <<"Finished Parameterizing the Electron mean and width!" <<endl;


    //----- ROUND 3: Final Fitting Loop
    for (Int_t mTm0Index=2; mTm0Index<20; mTm0Index++){//56

      //Make sure that the electron hasn't already been killed
      if (killElectron)
	continue;
   
      //Make sure the histogram exists
      if (!tpcPionMinusHisto.at(yIndex).at(mTm0Index))
	continue;

      //Pass the histogram to a local pointer
      yieldHisto = tpcPionMinusHisto.at(yIndex).at(mTm0Index);
 
      //Make sure it has enough entires
      if (yieldHisto->GetEntries() < 100)
	continue;

      //Compute the kinematics for this bin
      ComputeBinKinematics(mTm0Index,rapidity,PION);

      //Make the Predictions for the particle species
      pionPredict = particleInfo->PredictZTPC(pTotal,PION,PION);
      kaonPredict = particleInfo->PredictZTPC(pTotal,PION,KAON);
      protonPredict = particleInfo->PredictZTPC(pTotal,PION,PROTON);
      electronPredict = particleInfo->PredictZTPC(pTotal,PION,ELECTRON);

			if (electronPredict < pionPredict) continue;

      //Draw the Yield Histogram
      yieldHisto->SetAxisRange(-1,2.5);
      yieldHisto->SetMarkerStyle(kOpenCircle);
      fittingCanvas->cd();
      yieldHisto->Draw("E");
      
      //Create the Fit and pass it to a local pointer
      if (tpcPionMinusFit.at(yIndex).at(mTm0Index))
	tpcPionMinusFit.at(yIndex).at(mTm0Index)->Delete();
      
			//Get the Previous Pion Mean
			Int_t nPointsPiMean = pion->mean[yIndex]->GetN();
			Double_t pionMeanPrev;
			pionMeanPrev = pion->mean[yIndex]->Eval(mTm0);

      //The Final Fit depends on the status of the electron
      if (!killElectron && mTm0 < 0.5){
		
				tpcPionMinusFit.at(yIndex).at(mTm0Index) = new TF1("","gaus(0)+gaus(3)",-.2,electronPredict+.125);
				yieldFit = tpcPionMinusFit.at(yIndex).at(mTm0Index);

				//Set Parameter Names
				yieldFit->SetParNames(Form("%s_{Amp.}",particleInfo->GetParticleSymbol(PION).Data()),
									"#mu_{#pi}","#sigma_{#pi}","e_{Amp.}",
									"#mu_{e}","#sigma_{e}");
				
				//Pion Parameters
				yieldFit->SetParameter(0,yieldHisto->GetBinContent(yieldHisto->FindBin(pionMeanPrev)));
				if (mTm0 <= pion->mean[yIndex]->GetX()[nPointsPiMean-1]) yieldFit->FixParameter(1,pionMeanPrev);
				else yieldFit->SetParameter(1,pionPredict);
				yieldFit->FixParameter(2,pion->widthFit[yIndex]->Eval(mTm0));

				//Electron Parameters
				Double_t eAmpSeed = yieldHisto->GetBinContent(yieldHisto->FindBin(electronPredict));
			  Int_t nPointsEleMean = electron->mean[yIndex]->GetN();
				yieldFit->SetParameter(3,eAmpSeed);
				yieldFit->FixParameter(4,electron->mean[yIndex]->Eval(mTm0));
				yieldFit->FixParameter(5,electron->widthFit[yIndex]->Eval(mTm0));	

        AddPointToParGraph(electron->amp[yIndex],yieldFit,3,mTm0Index);
				fitParCanvas->cd(4);
				electron->amp[yIndex]->Draw("APZ");
				if (!DEBUG) fitParCanvas->Update();
      }//End if electron has NOT been killed

      else {

				tpcPionMinusFit.at(yIndex).at(mTm0Index) =
					new TF1("","gaus(0)",-1,pionMeanPrev+2*pion->widthFit[yIndex]->Eval(mTm0));
				yieldFit = tpcPionMinusFit.at(yIndex).at(mTm0Index);

				//Set Parameter Names
				yieldFit->SetParNames(Form("%s_{Amp.}",particleInfo->GetParticleSymbol(PION).Data()),
									"#mu_{#pi}","#sigma_{#pi}");
				
				//Pion Parameters
				yieldFit->SetParameter(0,yieldHisto->GetBinContent(yieldHisto->FindBin(pionMeanPrev)));
				if (mTm0 <= pion->mean[yIndex]->GetX()[nPointsPiMean-1]) yieldFit->FixParameter(1,pionMeanPrev);
				else yieldFit->SetParameter(1,pionPredict);
				yieldFit->FixParameter(2,pion->widthFit[yIndex]->Eval(mTm0));

      }//End if Electron has been killed

      //Fit the Yield Histogram
      yieldHisto->Fit(yieldFit,"RQ");
      if (!DEBUG) fittingCanvas->Update();      

    }//End Loop Over mTm0Index

    cout <<"Finished Final Loop of Pion Minus Fitting Procedure" <<endl;
    
  }//End Loop Over yIndex


}

//--------------------------------------------------------------------
void DrawPredictionLines(TCanvas *canvas){

  canvas->cd();
  
  PredictionLine(pionLine,pionPredict,lineHeight)->Draw("SAME");
  PredictionLine(kaonLine,kaonPredict,lineHeight)->Draw("SAME");
  PredictionLine(protonLine,protonPredict,lineHeight)->Draw("SAME");
  PredictionLine(electronLine,electronPredict,lineHeight)->Draw("SAME");

}

//--------------------------------------------------------------------
void ComputeBinKinematics(Int_t mTm0Index, Double_t y, Int_t PID){

  mTm0 = GetmTm0RangeCenter(mTm0Index);
  mT   = mTm0 + particleInfo->GetParticleMass(PID);
  pZ   = ComputepZ(mT,y);
  pT   = ConvertmTm0ToPt(mTm0,particleInfo->GetParticleMass(PID));
  pTotal = ComputepTotal(pT,pZ);
  
}

//--------------------------------------------------------------------
Bool_t AddPointToSpectra(TH1D *yieldHisto, TF1 *yieldFit, TGraphErrors *rawSpectra,
			 Int_t yIndex, Int_t mTm0Index, Int_t PID, Int_t CHARGE, TString IMAGEDIR){
  
  
  //Adds a point to the spectra
  //returns false on fail, true on success
	
  //Make sure both the histogram and fit exist
  if (!yieldHisto || ! yieldFit)
    return false;

  //Draw the Final Version of the Fit
  fittingCanvas->Clear();
  fittingCanvas->cd();
  fittingCanvas->SetTopMargin(.05);
  fittingCanvas->SetRightMargin(.05);
  yieldHisto->SetMarkerStyle(kOpenCircle);
  yieldHisto->SetTitle("");
  yieldHisto->SetAxisRange(-2.0,3.0);
  yieldHisto->Draw("E");

  //Draw the Fit
  yieldFit->SetLineWidth(3);
  yieldFit->SetLineColor(kBlack);
  yieldFit->SetNpx(10000);
  yieldFit->Draw("SAME");  

  //Create a Label
  TPaveText label(.12,.8,.35,.92,"BL NDC");
  label.SetTextAlign(11);
  label.AddText(Form("Z(%s) Yield Extraction Fit",particleInfo->GetParticleSymbol(PID,CHARGE).Data()));
  label.AddText(Form("  %.2f #leq y_{%s} < %.2f | %.2f #leq m_{T}-m_{%s} < %.2f",
                     GetRapidityRangeLow(yIndex),particleInfo->GetParticleSymbol(PID,CHARGE).Data(),
                     GetRapidityRangeHigh(yIndex),GetmTm0RangeLow(mTm0Index),
                     particleInfo->GetParticleSymbol(PID,CHARGE).Data(),GetmTm0RangeHigh(mTm0Index)));
  label.GetLine(0)->SetTextSize(.03);
  label.GetLine(1)->SetTextSize(.02);
  label.SetFillColor(kWhite);
  label.SetBorderSize(0);
  label.Draw("SAME");

  //Make A Function for Each of the Particles
  TF1 pionGaus("pion","gaus(0)",-20,20);
  pionGaus.FixParameter(0,yieldFit->GetParameter(0));
  pionGaus.FixParameter(1,yieldFit->GetParameter(1));
  pionGaus.FixParameter(2,yieldFit->GetParameter(2));
  pionGaus.SetParError(0,yieldFit->GetParError(0));
  pionGaus.SetParError(1,yieldFit->GetParError(1));
  pionGaus.SetParError(2,yieldFit->GetParError(2));
  pionGaus.SetLineColor(particleInfo->GetParticleColor(PID));
  pionGaus.SetLineWidth(3);
  pionGaus.SetLineStyle(7);
  pionGaus.SetNpx(10000);
  pionGaus.Draw("SAME");
  
  TF1 electronGaus("electron","gaus(0)",-20,20);
  if (!killElectron){
	  if (CHARGE==-1){
			electronGaus.FixParameter(0,yieldFit->GetParameter(3));
			electronGaus.FixParameter(1,yieldFit->GetParameter(4));
			electronGaus.FixParameter(2,yieldFit->GetParameter(5));
			electronGaus.SetParError(0,yieldFit->GetParError(3));
			electronGaus.SetParError(1,yieldFit->GetParError(4));
			electronGaus.SetParError(2,yieldFit->GetParError(5));
			electronGaus.SetLineColor(particleInfo->GetParticleColor(ELECTRON));
			electronGaus.SetLineWidth(3);
			electronGaus.SetLineStyle(7);
			electronGaus.SetNpx(10000);
			electronGaus.Draw("SAME");
		}
	  if (CHARGE==1){
			electronGaus.FixParameter(0,yieldFit->GetParameter(9));
			electronGaus.FixParameter(1,yieldFit->GetParameter(10));
			electronGaus.FixParameter(2,yieldFit->GetParameter(11));
			electronGaus.SetParError(0,yieldFit->GetParError(9));
			electronGaus.SetParError(1,yieldFit->GetParError(10));
			electronGaus.SetParError(2,yieldFit->GetParError(11));
			electronGaus.SetLineColor(particleInfo->GetParticleColor(ELECTRON));
			electronGaus.SetLineWidth(3);
			electronGaus.SetLineStyle(7);
			electronGaus.SetNpx(10000);
			electronGaus.Draw("SAME");
		}
  }

  TF1 kaonGaus("kaon","gaus(0)",-20,20);
  if (CHARGE==1){
		kaonGaus.FixParameter(0,yieldFit->GetParameter(3));
		kaonGaus.FixParameter(1,yieldFit->GetParameter(4));
		kaonGaus.FixParameter(2,yieldFit->GetParameter(5));
		kaonGaus.SetParError(0,yieldFit->GetParError(3));
		kaonGaus.SetParError(1,yieldFit->GetParError(4));
		kaonGaus.SetParError(2,yieldFit->GetParError(5));
		kaonGaus.SetLineColor(particleInfo->GetParticleColor(KAON));
		kaonGaus.SetLineWidth(3);
		kaonGaus.SetLineStyle(7);
		kaonGaus.SetNpx(10000);
		kaonGaus.Draw("SAME");

	}

  //Set NParameter Switch
  //Controls Whether protons will be drawn
  Bool_t parSwitch = false;
  if (yieldFit->GetNpar() > 6 && !killElectron)
    parSwitch = true;

  TF1 protonGaus("proton","gaus(0)",-20,20);
  if (parSwitch){
    protonGaus.FixParameter(0,yieldFit->GetParameter(6));
    protonGaus.FixParameter(1,yieldFit->GetParameter(7));
    protonGaus.FixParameter(2,yieldFit->GetParameter(8));
    protonGaus.SetParError(0,yieldFit->GetParError(6));
    protonGaus.SetParError(1,yieldFit->GetParError(7));
    protonGaus.SetParError(2,yieldFit->GetParError(8));
    protonGaus.SetLineColor(particleInfo->GetParticleColor(PROTON));
    protonGaus.SetLineWidth(3);
    protonGaus.SetLineStyle(7);
    protonGaus.SetNpx(10000);
    protonGaus.Draw("SAME");

  }

  gPad->Update();
  
  //Make A Legend
  TLegend leg;
  leg.SetOption("brNDC");
  leg.SetX1NDC(.65);
  leg.SetY1NDC(.59);
  leg.SetX2NDC(.92);
  leg.SetY2NDC(.64);
  leg.SetTextSize(.035);
  leg.SetNColumns(5);
  //leg.SetNColumns(parSwitch ? 5 : 1);
  leg.AddEntry(yieldFit,"Fit","L");
  leg.AddEntry("pion","#pi","L");
  if (!killElectron)
    leg.AddEntry("electron","e","L");
  if (parSwitch && !killElectron){
    leg.AddEntry("proton","p","L");
  }
  leg.SetFillColor(kWhite);
  leg.SetBorderSize(0);
  leg.Draw("SAME");

  fittingCanvas->Update();

  //Extract the Yield
  Double_t amp = pionGaus.GetParameter(0);
  Double_t ampError = pionGaus.GetParError(0);
  Double_t width = pionGaus.GetParameter(2);
  Double_t widthError = pion->widthConf[yIndex]->GetEY()[TMath::BinarySearch(pion->widthConf[yIndex]->GetN() , pion->widthConf[yIndex]->GetX() , pion->width[yIndex]->GetX()[mTm0Index] )];//pionGaus.GetParError(2);
  Double_t pi = 3.14159;

  Double_t zBinWidth = (Double_t)yieldHisto->GetBinWidth(2);
  Double_t mTm0BinCenter = GetmTm0RangeCenter(mTm0Index);
  Double_t nEvents = (Double_t)nEventsHisto->GetBinContent(nEventsHisto->FindBin(centralityIndex));

  //Set the Normalization Factor
  Double_t normFactor = (1.0/(mTm0BinCenter+particleInfo->GetParticleMass(PID))) * (1.0/mTm0BinWidth) * (1.0/rapidityBinWidth) *
    (1.0/nEvents) * (1.0/(2.0*pi));

  //Compute the Raw Yield
  Double_t rawYield, rawYieldError;
  rawYield = ( (amp * width * sqrt(2.0*pi)) / zBinWidth ) * normFactor;
  rawYieldError = ( (amp * width * sqrt(pow(ampError/amp,2)+pow(widthError/width,2)) *
		     sqrt(2.0*pi)) / zBinWidth) * normFactor;

                                                                                                  
  //If this is a Pion Plus Spectra Stop when the pion and proton peak are close together
  Double_t deltaMean = fabs(pionGaus.GetParameter(1)-protonGaus.GetParameter(1));
  Double_t sumWidths = pionGaus.GetParameter(2)+protonGaus.GetParameter(2);
  if (parSwitch && deltaMean < 1.5*sumWidths){
    return false;
  }

  //Add Point to Spectrum
  rawSpectra->SetPoint(rawSpectra->GetN(),GetmTm0RangeCenter(mTm0Index),rawYield);
  rawSpectra->SetPointError(rawSpectra->GetN()-1,0,rawYieldError);

  //Draw the Spectra
  spectraCanvas->cd();
  rawSpectra->Draw("APZ");
  spectraCanvas->Update();

  //Save the Fit Image
  if (SAVEIMG){
    TString fullImageDir = IMAGEDIR+"/"+particleInfo->GetParticleName(PID,CHARGE);
    TString imageName = TString::Format("zTPCFit_%s_%02d_%02d_%02d",
					particleInfo->GetParticleName(PID,CHARGE).Data(),
					centralityIndex,yIndex,mTm0Index);
    
    fittingCanvas->SaveAs(Form("%s/%s.eps",fullImageDir.Data(),imageName.Data()));
    
  }
  
  return true;

}
