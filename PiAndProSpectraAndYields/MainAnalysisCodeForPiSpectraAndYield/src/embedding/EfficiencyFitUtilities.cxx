#include <iostream>

#include <TMath.h>
#include <TF1.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include <TMatrixD.h>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TMatrixDSym.h>
#include <TDecompChol.h>
#include <TRandom3.h>
#include <TFormula.h>

#include <EfficiencyFitUtilities.h>

//__________________________________________________________________
Double_t GetOneSigmaEfficiencyDeviateAt(TGraphAsymmErrors *gr, Double_t xVal){

  Int_t iPoint = TMath::BinarySearch(gr->GetN(),gr->GetX(),xVal);
  
  Double_t errHigh = gr->GetEYhigh()[iPoint];
  Double_t errLow  = gr->GetEYlow()[iPoint];
  Double_t total = errHigh+errLow;

  Double_t frac = errHigh/total;

  TRandom3 rand(0);
  Double_t sampleWidth = errHigh;
  if (rand.Uniform(0,1) < frac)
    sampleWidth = errLow;

  Double_t deviate = -1;
  while (deviate <= 0 || deviate >= 1){
    deviate = rand.Gaus(gr->GetY()[iPoint],sampleWidth);
  }

  return deviate;
  
}

//__________________________________________________________________
Int_t CountNAbove(Int_t n, Double_t *vec, Double_t threshold){

  Int_t count(0);
  for (int i=0; i<n; i++){
    if (vec[i] > threshold)
      count++;
  }

  return count;
}

//_________________________________________________________________
Int_t CountNBelow(Int_t n, Double_t *vec, Double_t threshold){

  Int_t count(0);
  for (int i=0; i<n; i++){

    if (vec[i] < threshold)
      count++;

  }
  return count;
}

//__________________________________________________________________
Double_t FindFractionalCut(Int_t n, Double_t *vec, Double_t desiredFrac,
			   bool forward, const int nTrials){


  if (n == 0)
    return 0;

  Double_t min = TMath::MinElement(n,vec);
  Double_t max = TMath::MaxElement(n,vec);
  Double_t step = (max-min)/(double)nTrials;

  if (forward){
    for (Double_t x=min; x<max; x+=step){

      Double_t fraction = CountNBelow(n,vec,x)/(double)n;

      if (fraction >= desiredFrac){
	return x;
      }

    }
  }

  else{
    for (Double_t x=max; x>min; x-=step){

      Double_t fraction = CountNAbove(n,vec,x)/(double)n;

      if (fraction >= desiredFrac){
	return x;
      }

    }
  }

}


//______________________________________________________________________________
TMatrixD GetRandomDeviateVector(TF1 *func, TFitResultPtr fitResult){

  //Suppose we want to construct an efficiency function of the same form as our
  //fit, but whose parameters are random deviates distributed according to
  //the errors on the fit parameters. This is useful when we are trying to characterize
  //the error associated with the efficiency corrections.

  //************************************************************************
  //However, we must be careful to consider any covariance between the fit
  //parameters. We need to be especially careful with efficiency functions because
  //the error on the efficiency is often the largest source of systematic error in
  //spectra analyses. So it pays high divideds to make sure you control this error
  //by properly considering all the covariances that can constrain it.
  //************************************************************************

  //Cholesky Decomposition
  //WARNING: This particular method works for positive definite Covariance Matrices and each
  //dimension must originate as a Normal Distribution (which is a good assumption
  //for most fits). If your covariance matrix is not positive definite you likely have
  //a fit minimum which is not singular/unique. This typically means your parameters
  //have some linear dependence. If this is the case you can either control the dependence
  //or try to do an eigen value decomposition which is more computationally intensive.

  //Find Documentation for the CholeskyDecomp. method here:
  //http://en.wikipedia.org/wiki/Multivariate_normal_distribution#Drawing_values_from_the_distribution

  //Determin the Dimensionality
  Int_t dim = func->GetNpar();

  //Get the Covariance Maxtrix
  TMatrixDSym covMatrix = fitResult->GetCovarianceMatrix();

  //Do the Cholesky Decomposition
  TDecompChol decompMatrix(covMatrix);
  decompMatrix.Decompose();

  //Get the Upper Trianglular Matrix
  TMatrixD upper = decompMatrix.GetU();

  TMatrixD A(dim,dim);
  A.Transpose(upper);

  //Generate a Vector of the parameter's means
  TMatrixD meanVector(dim,1);
  for (Int_t iDim=0; iDim<dim; iDim++)
    meanVector[iDim][0] = func->GetParameter(iDim);

  //Generate a Column Vector of Independent normal deviates
  TMatrixD indepDeviates(dim,1);
  TRandom3 rand(0);
  for (Int_t iDim=0; iDim<dim; iDim++)
    indepDeviates[iDim][0] = rand.Gaus(0,1);

  //Create the Random Deviate Vector
  TMatrixD deviateVector(dim,1);
  deviateVector = meanVector + A*indepDeviates;

  return deviateVector;

}


//______________________________________________________________________________
TGraphAsymmErrors *ConstructErrorFuncConfidenceBand(TF1 *fitFunc, TFitResultPtr *fitResult, Double_t percenttile){

  //This function constructs an nth sigma error band using the fit function and
  //the fit results. By default a one sigma band will be created.

  //Note this was written for a TF1 that has three functions, but can be easily
  //generalized to any number.

  TGraphAsymmErrors *errorBand = new TGraphAsymmErrors();

  Double_t minRange(0), maxRange(0);
  fitFunc->GetRange(minRange,maxRange);

  const Int_t nIterations(1000);
  const Int_t nPoints(1000);
  Double_t stepSize = fabs(maxRange-minRange)/(Double_t)nPoints;

  //For each iteration we construct a new efficiency function with parameters
  //that are random deviates from a multi-variate normal distribution defined
  //by the fit function's parameters, errors, and covariance. We then evaluate
  //that function at various values of pT or mTm0.  The spread in the efficiency
  //values at any given pT or mTm0 will give us the uncertainty.
  std::vector<double> temp;
  std::vector< std::vector <double> > effValsHigh(nPoints,std::vector <double> (0));
  std::vector< std::vector <double> > effValsLow(nPoints, std::vector <double> (0));

  for (Int_t iIter=0; iIter<nIterations; iIter++){

    //Gerate the Vector of Random Deviates
    Bool_t accept = false;
    Double_t pars[3];
    while (!accept){

      TMatrixD tempRandomDeviates = GetRandomDeviateVector(fitFunc,*fitResult);

      if (tempRandomDeviates[1][0] > 0 && tempRandomDeviates[2][0] > 0){
	accept = true;
	pars[0] = tempRandomDeviates[0][0];
	pars[1] = tempRandomDeviates[1][0];
	pars[2] = tempRandomDeviates[2][0];
      }

    }

    //Use the deviates to define a new efficiency function
    TF1 effFunc("",fitFunc->GetExpFormula(),minRange,maxRange);
    effFunc.FixParameter(0,pars[0]);
    effFunc.FixParameter(1,pars[1]);
    effFunc.FixParameter(2,pars[2]);

    for (Int_t iPoint=0; iPoint<nPoints; iPoint++){

      Double_t funcVal = fitFunc->Eval(iPoint * stepSize);
      Double_t tempEffVal = effFunc.Eval(iPoint * stepSize);
      if (tempEffVal > funcVal){
	effValsHigh.at(iPoint).push_back(tempEffVal);

      }
      else if (tempEffVal < funcVal){
	effValsLow.at(iPoint).push_back(tempEffVal);;

      }


    }//End Loop Over iPoint

  }//End Loop Over iIter

  //For each point along the efficiency curve find the uncertainty in the efficiency
  //and pass the value to the error band graph
  for (Int_t iPoint=0; iPoint<nPoints-1; iPoint++){

    Double_t fractionalCutHigh(0);
    Double_t fractionalCutLow(0);

    if (effValsHigh.at(iPoint).size() > 0)
      fractionalCutHigh = FindFractionalCut(effValsHigh.at(iPoint).size(),&effValsHigh.at(iPoint).at(0),percenttile/2.0);
    if (effValsLow.at(iPoint).size() > 0)
      fractionalCutLow = FindFractionalCut(effValsLow.at(iPoint).size(),&effValsLow.at(iPoint).at(0),percenttile/2.0,false);


    double funcVal = fitFunc->Eval(iPoint*stepSize);
    errorBand->SetPoint(errorBand->GetN(),iPoint*stepSize,funcVal);
    errorBand->SetPointError(errorBand->GetN()-1,stepSize/2.0,stepSize/2.0,
			     fabs(funcVal - fractionalCutLow),
			     fabs(funcVal - fractionalCutHigh));


  }

  return errorBand;

}


