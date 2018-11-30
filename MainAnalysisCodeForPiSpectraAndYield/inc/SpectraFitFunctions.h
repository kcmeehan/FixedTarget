//Header file for spectra and ratio fit functions and routines
//See src/analysis/SpectraFitFunctions.cxx for implementations

//Pion Ratio Coulomb Fit___________________________________________
Double_t PionRatioFit(Double_t *x, Double_t *par);
TString PrintPionRatioFitResults(TF1 *fitFunc);

//Compute the dNdy in the measured range by counting_______________
std::pair<double,double> CountdNdyOfSpectrum(TGraphErrors *spectrum, Int_t pid,
					     Double_t minRange=0.0, Double_t maxRange=100.0);

//Bose-Einstein fit_________________________________________________
Double_t InvertBoseEinstein(Double_t slope, Double_t particleMass,
			    Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t BoseEinsteinFitFunc(Double_t *x, Double_t *par); //This calls InvertBoseEinstein
Double_t InvertCoulombModifiedBoseEinsteinFitFunc(Double_t tSlopePi, Double_t piMass,
          Double_t rapidity, Double_t Vcoulomb, Double_t proMass, Double_t tSlopePro,
					Double_t minRange=0.0, Double_t maxRange=100.0);
Double_t CoulombModifiedBoseEinsteinFitFunc(Double_t *x, Double_t *par);//This calls InvertCoulombModifiedBE
Double_t BoseEinsteinFitFuncNoInversion(Double_t *x, Double_t *par); 

//MT-Exponential fit_________________________________________________
Double_t InvertmTExponential(Double_t slope, Double_t particleMass, 
			     Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t mTExponentialFitFunc(Double_t *x, Double_t *par); //This calls InvertmTExponential

//Thermal (Maxwell-Boltzmann) fit__________________________________
Double_t ThermalFitFunc(Double_t *x, Double_t *par);
Double_t DoubleThermalFit(Double_t *x, Double_t *par);

//Double Exponential
Double_t InvertDoubleExponential(Double_t A1, Double_t T1, Double_t A2, Double_t T2,
				 Double_t pMass,Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t DoubleExponential(Double_t *x, Double_t *par);

//Jenn Klay's Double Exponential
Double_t InvertExponential(Double_t T, Double_t pMass, Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t JCDoubleExponential(Double_t *x, Double_t *par);

//Siemens and Rasmussen Model______________________________________
Double_t InvertSiemensRasmussen(Double_t T, Double_t beta,
				Double_t pMass,Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t SiemensRasmussen(Double_t *x, Double_t *par);

//Blast Wave Model_________________________________________________
Double_t RadialIntegralBW(Double_t betaS, Double_t n, Double_t T, Double_t mTm0,
			  Double_t mass, Double_t R);
Double_t InvertBlastWaveFit(Double_t betaS, Double_t n, Double_t T, Double_t mass,
			    Double_t R, Double_t minRange=0.0, Double_t maxRange=10.0);
Double_t BlastWaveModelFit(Double_t *x, Double_t *par);
