double CalculateEventPlaneResolution(float mult = 10, float v1=0.1)
{
	TF1 *fCalcRes = new TF1("fCalcRes","TMath::Sqrt(TMath::Pi())/2*x*TMath::Exp(-x*x/2)*(TMath::BesselI0(x*x/2)+TMath::BesselI1(x*x/2))",0,10);
	float X = v1*TMath::Sqrt(mult);
	return fCalcRes->Eval(X);
}