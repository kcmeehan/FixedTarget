//Implementation of spectra and ratio fit functions.
#include <utility>

#include <TString.h>
#include <TMath.h>
#include <TF1.h>

#include "utilityFunctions.h"
#include "ParticleInfo.h"

#include "SpectraFitFunctions.h"

/******************************************************************
   PION RATIO COULOMB FIT AND FIT RESULT PRINT FUNCTIONS
******************************************************************/
//_________________________________________________________
Double_t PionRatioFit(Double_t *x, Double_t *par){

  //NOTE: Parameters 2,3,and 4 should be FIXED in the following ways:
  //      Par2 = FIXED to the PION slope parameter from spectra fit
  //      Par3 = FIXED to the PROTON slope parameter from spectra fit
  //      Par4 = FIXED to the recentered rapidity, y-yMid

  ParticleInfo particleInfo;
  
  Double_t mTm0 = x[0];

  //Fit Parameters
  Double_t initialRatio = par[0];
  Double_t coulombV = par[1]/1000.0;
  Double_t pionTemp = par[2];  //This Should be Fixed the pion Spectra Fit
  Double_t protonTemp = par[3];//This Should be Fixed from the proton Spectra Fit
  Double_t y = par[4];         //This Should be Fixed (y-yMid)

  //Additional Variables for -->Pion<--
  Double_t m0 = particleInfo.GetParticleMass(PION);
  Double_t mT = mTm0 + m0;
  Double_t energy = mT*cosh(y);
  Double_t p = sqrt(energy*energy - m0*m0);
  Double_t betaGamma = p / m0;

  //Additional Variables for -->Proton<--
  Double_t mP = particleInfo.GetParticleMass(PROTON);

  //Compute the Effective Coulomb Potential
  Double_t eMax = sqrt(pow(mP*betaGamma,2) + pow(mP,2)) - mP;
  Double_t effCoulombV = coulombV * (1.0 - exp(-eMax/protonTemp));


  //Compute the Transformation Jacobian
  Double_t num = sqrt(pow(energy - effCoulombV,2) - pow(m0,2));
  Double_t denom = sqrt(pow(energy + effCoulombV,2) - pow(m0,2));
  Double_t Jacobian = (energy - effCoulombV) / (energy + effCoulombV);
  Jacobian = Jacobian * ( num/denom );

  //Compute the Emmision Factor for Bose Einstein
  Double_t emmisionFactor = exp( (energy + effCoulombV)/pionTemp ) - 1.0;
  emmisionFactor = emmisionFactor / (exp( (energy - effCoulombV)/pionTemp) - 1.0);

  //Assemble it all Together
  return initialRatio * emmisionFactor * Jacobian;


}

//________________________________________________________
TString PrintPionRatioFitResults(TF1 *fitFunc){
  
  Double_t initialPionRatio     = fitFunc->GetParameter(0);
  Double_t initialPionRatioErr = fitFunc->GetParError(0);

  Double_t coulombPotential    = fitFunc->GetParameter(1);
  Double_t coulombPotentialErr = fitFunc->GetParError(1);

  Double_t chi2 = fitFunc->GetChisquare();
  Double_t ndf = fitFunc->GetNDF();

  return TString::Format("%.04f +- %.04f\t%.04f +- %.04f\t%.04f",
                         coulombPotential,coulombPotentialErr,
			 initialPionRatio,initialPionRatioErr,
			 chi2/ndf);

}

/******************************************************************
   COUNT THE DNDY IN THE MEASURED REGION OF THE SPECTRUM
/******************************************************************/
//__________________________________________________________
std::pair<double,double> CountdNdyOfSpectrum(TGraphErrors *spectrum, Int_t pid,
					     Double_t minRange, Double_t maxRange){

  //Count the dNdy of a measured spectrum by numerically integrating
  //its points in the range from minRange to maxRange. Return a pair
  //corresponding to the dNdy and its error.
  
  Double_t dNdy(0);
  Double_t dNdyErr(0);
  Double_t errSum(0);
    
  ParticleInfo particleInfo;
  Double_t pMass = particleInfo.GetParticleMass(pid);

  for (Int_t iPoint=0; iPoint<spectrum->GetN(); iPoint++){

    Double_t mTm0 = spectrum->GetX()[iPoint];
    if (mTm0 < minRange || mTm0 > maxRange)
      continue;

    Double_t mT = mTm0 + pMass;
    Double_t yield = spectrum->GetY()[iPoint];
    Double_t yieldErr = spectrum->GetEY()[iPoint];
    Double_t binWidth = spectrum->GetEX()[iPoint]*2.0; //Error is half of bin width
    
    dNdy += yield * binWidth * mT;
    errSum += pow(yieldErr * binWidth * mT,2);
    
  }

  //Compute the Error Before the 2Pi Normalization
  dNdyErr = sqrt(errSum);

  //Apply the Normalization  
  dNdy = dNdy * 2.0 * TMath::Pi();
  dNdyErr = dNdyErr * 2.0 * TMath::Pi();

  return std::make_pair(dNdy,dNdyErr);

}

/******************************************************************
   BOSE-EINSTEIN SPECTRAL FIT FUNCTION AND NUMERICAL INTEGRATION
/******************************************************************/
//__________________________________________________________
Double_t InvertBoseEinstein(Double_t Slope, Double_t pMass,
			    Double_t minRange, Double_t maxRange){

  //Returns the dN/dy of the Spectra Fits by numerically inverting the
  //Bose-Einstein Function.  Here we integrate the fitting function over dmT
  //from minRange to maxRange GeV in .01 GeV Steps

  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange; //mT-m0

  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){

    sum += ( (x + pMass)/(exp((x+pMass)/Slope)-1.0) ) * stepWidth;
		//cosh(rapidity)/Slope

    //Increment x
    x += stepWidth;

  } 

  return sum;
}

//_______________________________________________________
Double_t BoseEinsteinFitFunc(Double_t *x, Double_t *par){

  //This is the Bose Einstein Function which is used to fit the spectra
  //It consists of the normalized part which contains the dNdy and the 
  //BE Functional Form

  //NOTE: par2 corresponding to the particle mass should be fixed!
  //NOTE: par3 corresponding to the rapidity should be fixed!
  
  //Get the Independent Variable
  Double_t xx = x[0];

  //Get the Parameters
  Double_t dNdy = par[0];
  Double_t tSlope = par[1];
  Double_t pMass = par[2];    //This Should be FIXED!

  return (1.0/(2.0*TMath::Pi())) * (dNdy/InvertBoseEinstein(tSlope,pMass)) *
    (1.0/(exp((xx+pMass)/tSlope) - 1.0));

}

//__________________________________________________________
Double_t InvertCoulombModifiedBoseEinsteinFitFunc(Double_t tSlopePi, Double_t piMass,
					Double_t rapidity, Double_t Vcoulomb, Double_t proMass, Double_t tSlopePro,
					Double_t minRange, Double_t maxRange){
  //Returns the dN/dy of the Spectra Fits by numerically inverting the
  //Coulomb-Modified Bose-Einstein Function.  Here we integrate the fitting function over dmT
  //from minRange to maxRange GeV in .01 GeV Steps

  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange; //mT-m0

  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){

		Double_t mT = x + piMass;
		Double_t Ef = mT*TMath::CosH(rapidity);
		Double_t pz = mT*TMath::SinH(rapidity);
		Double_t pT = sqrt(mT*mT - piMass*piMass);  
		Double_t p = sqrt(pz*pz + pT*pT);
		Double_t Emax = sqrt(proMass*proMass*p*p/(piMass*piMass)+proMass*proMass) - proMass;
		Double_t Veff = Vcoulomb * (1.0 - exp(-1.0*Emax/tSlopePro));

    sum += ((x + piMass)*(Ef - Veff)*sqrt((Ef-Veff)*(Ef-Veff)-piMass*piMass)/(exp((Ef-Veff)/tSlopePi)-1.0)) * stepWidth;

    //Increment x
    x += stepWidth;

  } 

  return sum;

}

//_______________________________________________________
Double_t CoulombModifiedBoseEinsteinFitFunc(Double_t *x, Double_t *par){

	//This is the Coulomb-Modified Bose Einstein Function which is used to
	//fit the pion spectra.
	
	//Get the Independent Variable
	Double_t xx = x[0];

	//Get the parameters
	Double_t dNdy      = par[0];
	Double_t tSlopePi  = par[1];
	Double_t piMass    = par[2]; //This should be FIXED!
	Double_t tSlopePro = par[3];
	Double_t proMass   = par[4]; //This should be FIXED!
	Double_t rapidity  = par[5]; //This should be FIXED!
	Double_t Vcoulomb  = par[6]; 

	Double_t mT = xx + piMass;
	Double_t Ef = mT*TMath::CosH(rapidity);
	Double_t pz = mT*TMath::SinH(rapidity);
	Double_t pT = sqrt(mT*mT - piMass*piMass);  
	Double_t p = sqrt(pz*pz + pT*pT);
	Double_t Emax = sqrt(proMass*proMass*p*p/(piMass*piMass)+proMass*proMass) - proMass;
	Double_t Veff = Vcoulomb * (1.0 - exp(-1.0*Emax/tSlopePro));

	return (1.0/(2.0*TMath::Pi())) * 
	  (dNdy/InvertCoulombModifiedBoseEinsteinFitFunc(tSlopePi,piMass,rapidity,Vcoulomb,proMass,tSlopePro)) *
    (Ef - Veff) * sqrt((Ef - Veff)*(Ef - Veff) - piMass*piMass)/(exp((Ef-Veff)/tSlopePi) - 1.0);

}

//_______________________________________________________
Double_t BoseEinsteinFitFuncNoInversion(Double_t *x, Double_t *par){

  //This is the Bose Einstein Function which is used to fit the spectra
  //It consists of the normalized part which contains the dNdy and the 
  //BE Functional Form

  //NOTE: Here the zeroeth parameter is an overall constant and
  //      NOT the dNdy!

  //NOTE: par2 corresponding to the particle mass should be fixed!
  //NOTE: par3 corresponding to the rapidity should be fixed!
  
  //Get the Independent Variable
  Double_t xx = x[0];

  //Get the Parameters
  Double_t A = par[0];
  Double_t tSlope = par[1];
  Double_t pMass = par[2];    //This Should be FIXED!
  Double_t rapidity = par[3]; //This Should be FIXED!

  return A * (1.0/(exp((xx+pMass)*cosh(rapidity)/tSlope) - 1.0));

}

/******************************************************************
   MT-EXPONENTIAL SPECTRAL FIT FUNCTION AND NUMERICAL INTEGRATION
/******************************************************************/
//___________________________________________________________
Double_t InvertmTExponential(Double_t Slope, Double_t pMass, 
			     Double_t minRange, Double_t maxRange){

  //Returns the integral of the mTExponential fit by numerically
  //inverting the function in the specified range.

  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange; //mT-m0

  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){
    
    sum += ( (x + pMass)/(exp((x+pMass)/Slope)) ) * stepWidth;
    
    //Increment x
    x += stepWidth;
    
  } 

  return sum;
  
  
}

//____________________________________________________________
Double_t mTExponentialFitFunc(Double_t *x, Double_t *par){

  //The mTExponential funtion. The zeroth parameter is the dNdy,
  //from mT-m0=0 to "infinity". See inversion routine above

  Double_t xx=x[0]; //mT-m0
  
  //Get the Parameters
  Double_t dNdy = par[0];
  Double_t tSlope = par[1];   
  Double_t pMass = par[2];    //This should be FIXED

  return (1.0/(2.0*TMath::Pi())) * (dNdy/InvertmTExponential(tSlope,pMass)) *
    (1.0/(exp((xx+pMass)/tSlope)));
  
}


/******************************************************************
   THERMAL SPECTRAL FIT FUNCTION (MAXWELL-BOLTZMANN
   Note: See Jen Klay's Thesis Eqn 7.5
/******************************************************************/
//___________________________________________________________________________
Double_t ThermalFitFunc(Double_t *x, Double_t *par){

  //NOTE: par2 corresponding to the particle mass should be fixed
  
  Double_t xx =x[0];

  Double_t dNdy = par[0];
  Double_t tSlope = par[1];
  Double_t pMass = par[2];  //This Should be Fixed

  return (1.0/(2.0*TMath::Pi())) * (dNdy/tSlope) *(xx+pMass) *(1.0/(2.0*tSlope*tSlope + 2.0*tSlope*pMass + pMass*pMass)) * exp(-(xx)/tSlope);

}

/******************************************************************
   DOUBLE EXPONENTIAL FIT FUNCTION 
   Note: See Lokesh's Mid Rapidity Spectra Paper
/******************************************************************/
//___________________________________________________________________
Double_t InvertDoubleExponential(Double_t A1, Double_t T1, Double_t A2, Double_t T2,
				 Double_t pMass,Double_t minRange, Double_t maxRange){

  //Returns the integral of the Double Exponential fit by numerically
  //inverting the function in the specified range.

  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange; //mT-m0

  //Integrals for each term

  //Term 1
  Double_t term1(0);
  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){
    
    term1 += ( (x+pMass)*exp(-(x+pMass)/T1) ) * stepWidth;
    
    //Increment x
    x += stepWidth;
    
  } 

  term1 = A1 * term1;

  //Term 2
  x=minRange;
  Double_t term2(0);
  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){
    
    term2 += ( (x+pMass)*exp(-(x+pMass)/T2) ) * stepWidth;
    
    //Increment x
    x += stepWidth;
    
  } 

  term2 = A2 * term2;

  sum = term1 + term2;
  
  return sum;

}

//_________________________________________________________________
Double_t DoubleExponential(Double_t *x, Double_t *par){

  Double_t xx=x[0]; //mT-m0

  Double_t dNdy  = par[0];
  Double_t A1    = par[1];
  Double_t T1    = par[2];
  Double_t A2    = par[3];
  Double_t T2    = par[4];
  Double_t pMass = par[5]; //This should be fixed

  return (1.0/(2.0*TMath::Pi()))*(dNdy)*( (A1*exp(-(xx+pMass)/T1)+A2*exp(-(xx+pMass)/T2)) / InvertDoubleExponential(A1,T1,A2,T2,pMass));


}

//_________________________________________________________________
Double_t InvertExponential(Double_t T, Double_t pMass, Double_t minRange, Double_t maxRange){

  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange; //mT-m0

  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){
    
    sum += ( (x+pMass)*exp(-(x+pMass)/T) ) * stepWidth;
    
    //Increment x
    x += stepWidth;
    
  } 

	return sum;
}

//_________________________________________________________________
Double_t JCDoubleExponential(Double_t *x, Double_t *par){

  Double_t xx=x[0]; //mT-m0

  Double_t dNdy1 = par[0];
	Double_t T1    = par[1];
  Double_t dNdy2 = par[2];
	Double_t T2    = par[3];
	Double_t pMass = par[4];
	
	return (1.0/(2.0*TMath::Pi()))*(dNdy1*exp(-(xx+pMass)/T1)/InvertExponential(T1, pMass) + dNdy2*exp(-(xx+pMass)/T2)/InvertExponential(T2, pMass));


}

/******************************************************************
   SIEMENS AND RASMUSSEN MODEL
   See: Phys rev 42,880 (1979)

   Original Implementation in Fortran by Mike Heffner
   Modified by Daniel Cebra to use mT
   Converted into ROOT/C++ here
/******************************************************************/
//___________________________________________________________________
Double_t InvertSiemensRasmussen(Double_t T, Double_t beta, 
				Double_t pMass,Double_t minRange, Double_t maxRange){

  //Returns the integral of the Siemens Rasmussen Function in
  //the specified range
  
  Double_t stepWidth = .01;
  Int_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum = 0.0;
  Double_t x = minRange+0.00001; //mT-m0

  for (Int_t stepIndex=0; stepIndex < nSteps; stepIndex++){

    Double_t mt = x+pMass;
    Double_t E = mt;
    Double_t p = sqrt(pow(E,2)-pow(pMass,2));
    Double_t gamma = 1.0/sqrt(1.0-pow(beta,2));
    Double_t alpha = (gamma*beta*p) / T;

    Double_t A = exp(-gamma*E/T);
    Double_t B = (sinh(alpha)/alpha)*(gamma+(T/E));
    Double_t C = (T/E)*cosh(alpha);

    sum += ( E * A * (B-C) ) * stepWidth;
    
    //Increment x
    x += stepWidth;
    
  } 

  return sum;

  
}

//___________________________________________________________________
Double_t SiemensRasmussen(Double_t *x, Double_t *par){

  Double_t xx=x[0]; //mT-m0

  Double_t dNdy  = par[0];
  Double_t T     = par[1];
  Double_t beta  = par[2];
  Double_t pMass = par[3]; //This should be fixed

  Double_t mt = xx+pMass;
  Double_t E  = mt;
  Double_t p  = sqrt(pow(E,2)-pow(pMass,2));
  Double_t gamma = 1.0/sqrt(1.0-pow(beta,2));
  Double_t alpha = (gamma*beta*p) / T;

  Double_t A = exp(-gamma*E/T);
  Double_t B = (sinh(alpha)/alpha)*(gamma+(T/E));
  Double_t C = (T/E)*cosh(alpha);

  //In the Limit that beta->0 (no radial flow) the SiemensRassmussen
  //Function should go to a Boltzmann Distribution (Thermal Function Above)
  if (beta < 0.001){
    Double_t thermalPars[3] = {dNdy,T,pMass};
    return ThermalFitFunc(x,thermalPars);
  }
  
  return (1.0/(2.0*TMath::Pi())) * dNdy * A * (B - C) / InvertSiemensRasmussen(T,beta,pMass);
}

/******************************************************************
   BLAST WAVE MODEL
  


/******************************************************************/
//___________________________________________________________________
Double_t RadialIntegralBW(Double_t betaS, Double_t n, Double_t T, Double_t mTm0,
			  Double_t mass, Double_t R){

  //Radial Integral for the Blast Wave Model

  //Integration Variable
  Double_t r(0.0); //The lower limit of integration is 0.0

  //Integration Steps
  Double_t sum(0.0);
  Double_t stepWidth(0.01);
  Int_t    nSteps = (Int_t)(fabs(R)/stepWidth);

  //Compute mT and pT
  Double_t mT = mTm0 + mass;
  Double_t pT = ConvertmTm0ToPt(mTm0,mass);

  //Do the numerical integral
  for (int iStep=0; iStep<nSteps; iStep++){

    Double_t betaT = betaS * pow(r/R,n);
    Double_t rho   = TMath::ATanH(betaT);

    Double_t BesselI0 = TMath::BesselI0((pT/T)*TMath::SinH(rho));
    Double_t BesselK1 = TMath::BesselK1((mT/T)*TMath::CosH(rho));

    //Increment the Sum
    sum += r * mT * BesselI0 * BesselK1 * stepWidth;

    //Increment the integration variable
    r += stepWidth;
    
  }//End Loop Over iStep

  return sum;
  
}

//___________________________________________________________________
Double_t InvertBlastWaveFit(Double_t betaS, Double_t n, Double_t T,
			    Double_t mass, Double_t R, Double_t minRange, Double_t maxRange){

  //Integrate the Blast Wave Fit in range from minRange to maxRange

  Double_t stepWidth(0.01);
  Double_t nSteps = (Int_t)(fabs(maxRange-minRange)/stepWidth);
  Double_t sum(0.0);
  Double_t x(minRange); //Integration variable (mT-m0)

  for (int iStep=0; iStep<nSteps; iStep++){

    Double_t mT = x+mass;
    
    //Increment the Sum
    sum += mT * RadialIntegralBW(betaS,n,T,x,mass,R) * stepWidth;
    
    //Increment the Integration Variable
    x += stepWidth;
    
  }
  
  return sum;
  
}

//___________________________________________________________________
Double_t BlastWaveModelFit(Double_t *x, Double_t *par){

  Double_t xx=x[0]; //mT-m0

  Double_t norm  = par[0]; //Yield
  Double_t T     = par[1]; //Tkin
  Double_t betaS = par[2]; //Surface Velocity
  Double_t n     = par[3]; //Power in the Tranverse Velocity factor (betaT)
  Double_t R     = par[4]; //Upper Limit of Radial Integral (SHOULD BE FIXED)
  Double_t mass  = par[5]; //Should be FIXED

  return (1.0/(2.0*TMath::Pi())) * norm * RadialIntegralBW(betaS,n,T,xx,mass,R);// / InvertBlastWaveFit(betaS,n,T,mass,R);

}

//___________________________________________________________________
//
// Double Maxwell-Boltzmann thermal function used by Jenn Klay in her arxiv paper 
//  arXiv:nucl-ex/0306033v2  26 Sep 2003
//___________________________________________________________________
Double_t DoubleThermalFit(Double_t *x, Double_t *par){

	Double_t xx = x[0]; //mt-m0

	Double_t dNdy1 = par[0];
	Double_t T1 = par[1];
	Double_t dNdy2 = par[2];
	Double_t T2 = par[3];
	Double_t mass = par[4];//Should be FIXED

	return (xx + mass)/(2 * TMath::Pi()) * (dNdy1 * exp(-1. * xx / T1) / (mass*mass*T1 + 2*mass*T1*T1 + 2*pow(T1, 3)) + 
			dNdy2 * exp(-1. * xx / T2) / (mass*mass*T2 + 2*mass*T2*T2 + 2*pow(T2, 3)));

}
