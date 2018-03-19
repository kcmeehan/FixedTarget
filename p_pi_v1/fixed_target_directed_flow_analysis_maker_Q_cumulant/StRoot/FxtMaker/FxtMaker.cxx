#include "FxtMaker.h"    // Class header file

ClassImp(FxtMaker)    // Class implementation in CINT

FxtMaker::FxtMaker(StMuDstMaker* Maker, TString JobId, Int_t EventsNumber, Double_t inputParameter) : StMaker()    // Constructor
  {
    mMuDstMaker = Maker; JobIdName = JobId; cutTest = inputParameter;
    JobIdName.Append(".root");    // Name output file by assigned Job ID
    StProton    * Aproton =    StProton::instance(); Mass_Proton = Aproton->mass();
    StPionMinus *   Apion = StPionMinus::instance();   Mass_Pion =   Apion->mass();
    StKaonMinus *   Akaon = StKaonMinus::instance();   Mass_Kaon =   Akaon->mass();
    Low = -2.; High = 0.;    // Set rapidity/pseudorapidity range
    //Low = 0.0; High = 3.0;    // Set transverse momentum range
    midrapidity = -1.52;
    // Initialize variables for Q cumulant method
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            if(icent == 0) multCounter[itrack] = 0;
            sumS11[itrack][icent] = 0.0;
            sumM11[itrack][icent] = 0.0;
            sumM111[itrack][icent] = 0.0;
            sumM1111[itrack][icent] = 0.0;
            sumCorr2[itrack][icent] = 0.0;
            sumCorr4[itrack][icent] = 0.0;
            sumAddon1[itrack][icent] = 0.0;
            sumAddon2[itrack][icent] = 0.0;
            sumAddon5[itrack][icent] = 0.0;
            sumAddon6[itrack][icent] = 0.0;
            sumAddon7[itrack][icent] = 0.0;
            sumAddon8[itrack][icent] = 0.0;
            sumS11Squared[itrack][icent] = 0.0;
            sumM11Squared[itrack][icent] = 0.0;
            sumM111Squared[itrack][icent] = 0.0;
            sumM1111Squared[itrack][icent] = 0.0;
            sumCorr2Squared[itrack][icent] = 0.0;
            sumCorr4Squared[itrack][icent] = 0.0;
            sumAddon1Squared[itrack][icent] = 0.0;
            sumAddon2Squared[itrack][icent] = 0.0;
            sumAddon5Squared[itrack][icent] = 0.0;
            sumAddon6Squared[itrack][icent] = 0.0;
            sumAddon7Squared[itrack][icent] = 0.0;
            sumAddon8Squared[itrack][icent] = 0.0;
            sumM11M1111[itrack][icent] = 0.0;
            sumCorr2Corr4[itrack][icent] = 0.0;
            sumM11S11[itrack][icent] = 0.0;
            sumCorr2C1[itrack][icent] = 0.0;
            sumCorr2C2[itrack][icent] = 0.0;
            sumCorr2C5[itrack][icent] = 0.0;
            sumCorr2C6[itrack][icent] = 0.0;
            sumM11M111[itrack][icent] = 0.0;
            sumCorr2C7[itrack][icent] = 0.0;
            sumCorr2C8[itrack][icent] = 0.0;
            sumM1111S11[itrack][icent] = 0.0;
            sumCorr4C1[itrack][icent] = 0.0;
            sumCorr4C2[itrack][icent] = 0.0;
            sumCorr4C5[itrack][icent] = 0.0;
            sumCorr4C6[itrack][icent] = 0.0;
            sumM111M1111[itrack][icent] = 0.0;
            sumCorr4C7[itrack][icent] = 0.0;
            sumCorr4C8[itrack][icent] = 0.0;
            sumC1C2[itrack][icent] = 0.0;
            sumC1C5[itrack][icent] = 0.0;
            sumC1C6[itrack][icent] = 0.0;
            sumM111S11[itrack][icent] = 0.0;
            sumC1C7[itrack][icent] = 0.0;
            sumC1C8[itrack][icent] = 0.0;
            sumC2C5[itrack][icent] = 0.0;
            sumC2C6[itrack][icent] = 0.0;
            sumC2C7[itrack][icent] = 0.0;
            sumC2C8[itrack][icent] = 0.0;
            sumC5C6[itrack][icent] = 0.0;
            sumC5C7[itrack][icent] = 0.0;
            sumC5C8[itrack][icent] = 0.0;
            sumC6C7[itrack][icent] = 0.0;
            sumC6C8[itrack][icent] = 0.0;
            sumC7C8[itrack][icent] = 0.0;
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                sumMp[ibin][itrack][icent] = 0.0;
                sumM01[ibin][itrack][icent] = 0.0;
                sumM011[ibin][itrack][icent] = 0.0;
                sumM0111[ibin][itrack][icent] = 0.0;
                sumCorr2Reduced[ibin][itrack][icent] = 0.0;
                sumCorr4Reduced[ibin][itrack][icent] = 0.0;
                sumAddon3[ibin][itrack][icent] = 0.0;
                sumAddon4[ibin][itrack][icent] = 0.0;
                sumAddon9[ibin][itrack][icent] = 0.0;
                sumAddon10[ibin][itrack][icent] = 0.0;
                sumAddon11[ibin][itrack][icent] = 0.0;
                sumAddon12[ibin][itrack][icent] = 0.0;
                sumAddon13[ibin][itrack][icent] = 0.0;
                sumAddon14[ibin][itrack][icent] = 0.0;
                sumAddon15[ibin][itrack][icent] = 0.0;
                sumMpSquared[ibin][itrack][icent] = 0.0;
                sumM01Squared[ibin][itrack][icent] = 0.0;
                sumM011Squared[ibin][itrack][icent] = 0.0;
                sumM0111Squared[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedSquared[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedSquared[ibin][itrack][icent] = 0.0;
                sumAddon3Squared[ibin][itrack][icent] = 0.0;
                sumAddon4Squared[ibin][itrack][icent] = 0.0;
                sumAddon9Squared[ibin][itrack][icent] = 0.0;
                sumAddon10Squared[ibin][itrack][icent] = 0.0;
                sumAddon11Squared[ibin][itrack][icent] = 0.0;
                sumAddon12Squared[ibin][itrack][icent] = 0.0;
                sumAddon13Squared[ibin][itrack][icent] = 0.0;
                sumAddon14Squared[ibin][itrack][icent] = 0.0;
                sumAddon15Squared[ibin][itrack][icent] = 0.0;
                sumM11M01[ibin][itrack][icent] = 0.0;
                sumCorr2Corr2Reduced[ibin][itrack][icent] = 0.0;
                sumM11M0111[ibin][itrack][icent] = 0.0;
                sumCorr2Corr4Reduced[ibin][itrack][icent] = 0.0;
                sumM1111M01[ibin][itrack][icent] = 0.0;
                sumCorr4Corr2Reduced[ibin][itrack][icent] = 0.0;
                sumM1111M0111[ibin][itrack][icent] = 0.0;
                sumCorr4Corr4Reduced[ibin][itrack][icent] = 0.0;
                sumM01M0111[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedCorr4Reduced[ibin][itrack][icent] = 0.0;
                sumM11mp[ibin][itrack][icent] = 0.0;
                sumCorr2C3[ibin][itrack][icent] = 0.0;
                sumCorr2C4[ibin][itrack][icent] = 0.0;
                sumM11M011[ibin][itrack][icent] = 0.0;
                sumCorr2C9[ibin][itrack][icent] = 0.0;
                sumCorr2C10[ibin][itrack][icent] = 0.0;
                sumCorr2C11[ibin][itrack][icent] = 0.0;
                sumCorr2C12[ibin][itrack][icent] = 0.0;
                sumCorr2C13[ibin][itrack][icent] = 0.0;
                sumCorr2C14[ibin][itrack][icent] = 0.0;
                sumM01S11[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC1[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC2[ibin][itrack][icent] = 0.0;
                sumM01mp[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC3[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC4[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC5[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC6[ibin][itrack][icent] = 0.0;
                sumM111M01[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC7[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC8[ibin][itrack][icent] = 0.0;
                sumM01M011[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC9[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC10[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC11[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC12[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC13[ibin][itrack][icent] = 0.0;
                sumCorr2ReducedC14[ibin][itrack][icent] = 0.0;
                sumM1111mp[ibin][itrack][icent] = 0.0;
                sumCorr4C3[ibin][itrack][icent] = 0.0;
                sumCorr4C4[ibin][itrack][icent] = 0.0;
                sumM1111M011[ibin][itrack][icent] = 0.0;
                sumCorr4C9[ibin][itrack][icent] = 0.0;
                sumCorr4C10[ibin][itrack][icent] = 0.0;
                sumCorr4C11[ibin][itrack][icent] = 0.0;
                sumCorr4C12[ibin][itrack][icent] = 0.0;
                sumCorr4C13[ibin][itrack][icent] = 0.0;
                sumCorr4C14[ibin][itrack][icent] = 0.0;
                sumM0111S11[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC1[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC2[ibin][itrack][icent] = 0.0;
                sumM0111mp[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC3[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC4[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC5[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC6[ibin][itrack][icent] = 0.0;
                sumM111M0111[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC7[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC8[ibin][itrack][icent] = 0.0;
                sumM011M0111[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC9[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC10[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC11[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC12[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC13[ibin][itrack][icent] = 0.0;
                sumCorr4ReducedC14[ibin][itrack][icent] = 0.0;
                sumS11mp[ibin][itrack][icent] = 0.0;
                sumC1C3[ibin][itrack][icent] = 0.0;
                sumC1C4[ibin][itrack][icent] = 0.0;
                sumM011S11[ibin][itrack][icent] = 0.0;
                sumC1C9[ibin][itrack][icent] = 0.0;
                sumC1C10[ibin][itrack][icent] = 0.0;
                sumC1C11[ibin][itrack][icent] = 0.0;
                sumC1C12[ibin][itrack][icent] = 0.0;
                sumC1C13[ibin][itrack][icent] = 0.0;
                sumC1C14[ibin][itrack][icent] = 0.0;
                sumC2C3[ibin][itrack][icent] = 0.0;
                sumC2C4[ibin][itrack][icent] = 0.0;
                sumC2C9[ibin][itrack][icent] = 0.0;
                sumC2C10[ibin][itrack][icent] = 0.0;
                sumC2C11[ibin][itrack][icent] = 0.0;
                sumC2C12[ibin][itrack][icent] = 0.0;
                sumC2C13[ibin][itrack][icent] = 0.0;
                sumC2C14[ibin][itrack][icent] = 0.0;
                sumC3C4[ibin][itrack][icent] = 0.0;
                sumC3C5[ibin][itrack][icent] = 0.0;
                sumC3C6[ibin][itrack][icent] = 0.0;
                sumM111mp[ibin][itrack][icent] = 0.0;
                sumC3C7[ibin][itrack][icent] = 0.0;
                sumC3C8[ibin][itrack][icent] = 0.0;
                sumM011mp[ibin][itrack][icent] = 0.0;
                sumC3C9[ibin][itrack][icent] = 0.0;
                sumC3C10[ibin][itrack][icent] = 0.0;
                sumC3C11[ibin][itrack][icent] = 0.0;
                sumC3C12[ibin][itrack][icent] = 0.0;
                sumC3C13[ibin][itrack][icent] = 0.0;
                sumC3C14[ibin][itrack][icent] = 0.0;
                sumC4C5[ibin][itrack][icent] = 0.0;
                sumC4C6[ibin][itrack][icent] = 0.0;
                sumC4C7[ibin][itrack][icent] = 0.0;
                sumC4C8[ibin][itrack][icent] = 0.0;
                sumC4C9[ibin][itrack][icent] = 0.0;
                sumC4C10[ibin][itrack][icent] = 0.0;
                sumC4C11[ibin][itrack][icent] = 0.0;
                sumC4C12[ibin][itrack][icent] = 0.0;
                sumC4C13[ibin][itrack][icent] = 0.0;
                sumC4C14[ibin][itrack][icent] = 0.0;
                sumC5C9[ibin][itrack][icent] = 0.0;
                sumC5C10[ibin][itrack][icent] = 0.0;
                sumC5C11[ibin][itrack][icent] = 0.0;
                sumC5C12[ibin][itrack][icent] = 0.0;
                sumC5C13[ibin][itrack][icent] = 0.0;
                sumC5C14[ibin][itrack][icent] = 0.0;
                sumC6C9[ibin][itrack][icent] = 0.0;
                sumC6C10[ibin][itrack][icent] = 0.0;
                sumC6C11[ibin][itrack][icent] = 0.0;
                sumC6C12[ibin][itrack][icent] = 0.0;
                sumC6C13[ibin][itrack][icent] = 0.0;
                sumC6C14[ibin][itrack][icent] = 0.0;
                sumM111M011[ibin][itrack][icent] = 0.0;
                sumC7C9[ibin][itrack][icent] = 0.0;
                sumC7C10[ibin][itrack][icent] = 0.0;
                sumC7C11[ibin][itrack][icent] = 0.0;
                sumC7C12[ibin][itrack][icent] = 0.0;
                sumC7C13[ibin][itrack][icent] = 0.0;
                sumC7C14[ibin][itrack][icent] = 0.0;
                sumC8C9[ibin][itrack][icent] = 0.0;
                sumC8C10[ibin][itrack][icent] = 0.0;
                sumC8C11[ibin][itrack][icent] = 0.0;
                sumC8C12[ibin][itrack][icent] = 0.0;
                sumC8C13[ibin][itrack][icent] = 0.0;
                sumC8C14[ibin][itrack][icent] = 0.0;
                sumC9C10[ibin][itrack][icent] = 0.0;
                sumC9C11[ibin][itrack][icent] = 0.0;
                sumC9C12[ibin][itrack][icent] = 0.0;
                sumC9C13[ibin][itrack][icent] = 0.0;
                sumC9C14[ibin][itrack][icent] = 0.0;
                sumC10C11[ibin][itrack][icent] = 0.0;
                sumC10C12[ibin][itrack][icent] = 0.0;
                sumC10C13[ibin][itrack][icent] = 0.0;
                sumC10C14[ibin][itrack][icent] = 0.0;
                sumC11C12[ibin][itrack][icent] = 0.0;
                sumC11C13[ibin][itrack][icent] = 0.0;
                sumC11C14[ibin][itrack][icent] = 0.0;
                sumC12C13[ibin][itrack][icent] = 0.0;
                sumC12C14[ibin][itrack][icent] = 0.0;
                sumC13C14[ibin][itrack][icent] = 0.0;
              }
          }
      }
    // Read Phi TProfile from file
    /*phi_total = 0.0;
    for(Int_t ibin = 0; ibin < 500; ibin++) {phi_weight[ibin] = 0.0;}
    phi_input = new TFile("/star/data01/scratch/ywu27/Fxt/results/phi_profile.root","READ");
     if( !phi_input->IsOpen() ) std::cout<<"No Phi histogram!"<<std::endl;
     if(  phi_input->IsOpen() )
     {
       std::cout<<"Phi histogram loaded successfully!"<<std::endl;
       Hist_Phi = (TH1D*)phi_input->Get("Phi");
       for(Int_t ibin = 0; ibin < 500; ibin++) {phi_weight[ibin] = Hist_Phi->GetBinContent(ibin+1);phi_total += phi_weight[ibin];}
       phi_total *= 1.0/500.0;
     }*/
  }

FxtMaker::~FxtMaker() {}    // Destructor

Int_t FxtMaker::Init()
  {
    outputFile = new TFile(JobIdName,"RECREATE");
    // QA plots
    hist_pt_eta = new TH2D("hist_pt_eta","hist_pt_eta",20,-2,0,50,0,5);
    
    histogram1D[0] = new TH1D("Vz","V_{Z}",500,200.0,220.0);
    histogram1D[0]->GetXaxis()->SetTitle("V_{Z} (cm)");
    histogram1D[0]->GetYaxis()->SetTitle("# of Vertices");
    histogram2D[0] = new TH2D("VyVx","V_{Y} vs V_{X} Distribution",500,-3.0,3.0,500,-3.0,3.0);
    histogram2D[0]->GetXaxis()->SetTitle("V_{X} (cm)");
    histogram2D[0]->GetYaxis()->SetTitle("V_{Y} (cm)");
    histogram1D[1] = new TH1D("vertMult","Vertices Multiplicity",400,0.0,400.0);
    histogram1D[1]->GetXaxis()->SetTitle("# of Vertices in Event");
    histogram1D[1]->GetYaxis()->SetTitle("# of Events");
    histogram1D[2] = new TH1D("refMult","Reference Multiplicity",N_track,0.0,N_track);
    histogram1D[2]->GetXaxis()->SetTitle("RefMult");
    histogram1D[2]->GetYaxis()->SetTitle("# of Events");
    histogram1D[3] = new TH1D("trackMult","Tracks Multiplicity",N_track,0.0,N_track);
    histogram1D[3]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[3]->GetYaxis()->SetTitle("# of Events");
    histogram1D[4] = new TH1D("TofMatchMult","# of Tracks Having Positive TofMatch Flag Distribution",N_track,0.0,N_track);
    histogram1D[4]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[4]->GetYaxis()->SetTitle("# of Events");
    histogram1D[5] = new TH1D("eventCuts","# of Selected Events after Each Cut",8,0.5,8.5);
    histogram1D[5]->GetXaxis()->SetBinLabel(1,"Before Cuts");
    histogram1D[5]->GetXaxis()->SetBinLabel(2,"Run Number Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(3,"At Least One Vertex Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(4,"Trigger ID Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(5,"V_{Z} Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(6,"Vertex Index Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(7,"V_{X} Cut");
    histogram1D[5]->GetXaxis()->SetBinLabel(8,"V_{Y} Cut");
    histogram1D[5]->GetYaxis()->SetTitle("# of Events");
    histogram1D[6] = new TH1D("Eta","Pseudorapidity",500,-2.5,0.0);
    histogram1D[6]->GetXaxis()->SetTitle("#eta");
    histogram1D[6]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[7] = new TH1D("Phi","Azimuth Angle",500,-TMath::Pi(),TMath::Pi());
    histogram1D[7]->GetXaxis()->SetTitle("#phi");
    histogram1D[7]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[8] = new TH1D("pT","Transverse Momentum",500,0.0,10.0);
    histogram1D[8]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    //histogram1D[8]->GetYaxis()->SetTitle("(1/p_{T})dN/dRapidity y^{-2}");
    histogram1D[8]->GetYaxis()->SetTitle("# of Tracks");
	histogram1D[9] = new TH1D("nHits","nHits Distribution",400,0.0,400.0);
    histogram1D[9]->GetXaxis()->SetTitle("nHits");
    histogram1D[9]->GetYaxis()->SetTitle("# of Tracks");
    // PID plots
    histogram2D[1] = new TH2D("dEdx","dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    histogram2D[1]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[1]->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    histogram2D[2] = new TH2D("beta","1/#beta vs q*|p|",500,-3.0,3.0,500,0.0,5.0);
    histogram2D[2]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[2]->GetYaxis()->SetTitle("1/#beta");
    histogram2D[3] = new TH2D("mass","m^{2} vs q*|p|",500,-3.0,3.0,500,-0.6,5.0);
    histogram2D[3]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[3]->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    // Test probability PID
    histogram2D[4] = new TH2D("dEdx_Proton","Proton dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    histogram2D[4]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[4]->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    histogram2D[7] = new TH2D("dEdx_Pion","Pion dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    histogram2D[7]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[7]->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    histogram2D[8] = new TH2D("dEdx_Kaon","Kaon dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    histogram2D[8]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[8]->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    histogram2D[9] = new TH2D("dEdx_Electron","Electron dE/dx vs q*|p|",500,-3.0,3.0,500,0.0,10.0);
    histogram2D[9]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[9]->GetYaxis()->SetTitle("dE/dx (keV/cm)");
    histogram2D[10] = new TH2D("beta_Proton","Proton 1/#beta vs q*|p|",500,-3.0,3.0,500,0.0,5.0);
    histogram2D[10]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[10]->GetYaxis()->SetTitle("1/#beta");
    histogram2D[11] = new TH2D("mass_Proton","Proton m^{2} vs q*|p|",500,-3.0,3.0,500,-0.6,1.2);
    histogram2D[11]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[11]->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    histogram2D[12] = new TH2D("beta_Kaon","Kaon 1/#beta vs q*|p|",500,-3.0,3.0,500,0.0,5.0);
    histogram2D[12]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[12]->GetYaxis()->SetTitle("1/#beta");
    histogram2D[13] = new TH2D("mass_Kaon","Kaon m^{2} vs q*|p|",500,-3.0,3.0,500,-0.6,1.2);
    histogram2D[13]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[13]->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    // Test probability PID ends
    histogram2D[5] = new TH2D("beta_Pion","Pion 1/#beta vs q*|p|",500,-3.0,3.0,500,0.0,5.0);
    histogram2D[5]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[5]->GetYaxis()->SetTitle("1/#beta");
    histogram2D[6] = new TH2D("mass_Pion","Pion m^{2} vs q*|p|",500,-3.0,3.0,500,-0.6,1.2);
    histogram2D[6]->GetXaxis()->SetTitle("q*|p| (GeV/c)");
    histogram2D[6]->GetYaxis()->SetTitle("m^{2} (GeV/c^{2})^{2}");
    histogram1D[10] = new TH1D("Mult_Pion","Pion Multiplicity",N_track,0.0,N_track);
    histogram1D[10]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[10]->GetYaxis()->SetTitle("# of Events");
    histogram1D[11] = new TH1D("Eta_Pion","Pion Pseudorapidity",500,-2.5,0.0);
    histogram1D[11]->GetXaxis()->SetTitle("#eta");
    histogram1D[11]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[12] = new TH1D("Phi_Pion","Pion Azimuth Angle",500,-TMath::Pi(),TMath::Pi());
    histogram1D[12]->GetXaxis()->SetTitle("#phi");
    histogram1D[12]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[13] = new TH1D("pT_Pion","Pion Transverse Momentum",500,0.0,10.0);
    histogram1D[13]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    //histogram1D[13]->GetYaxis()->SetTitle("(1/p_{T})dN/dRapidity y^{-2}");
	histogram1D[13]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[14] = new TH1D("y_Pion","Pion Rapidity",500,-2.5,0.0);
    histogram1D[14]->GetXaxis()->SetTitle("y");
    histogram1D[14]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 124] = new TH1D("Mult_Proton","Proton Multiplicity",N_track,0.0,N_track);
    histogram1D[17 + 3*Ncentralities + 124]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[17 + 3*Ncentralities + 124]->GetYaxis()->SetTitle("# of Events");
    histogram1D[17 + 3*Ncentralities + 125] = new TH1D("Eta_Proton","Proton Pseudorapidity",500,-2.5,0.0);
    histogram1D[17 + 3*Ncentralities + 125]->GetXaxis()->SetTitle("#eta");
    histogram1D[17 + 3*Ncentralities + 125]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 126] = new TH1D("Phi_Proton","Proton Azimuth Angle",500,-TMath::Pi(),TMath::Pi());
    histogram1D[17 + 3*Ncentralities + 126]->GetXaxis()->SetTitle("#phi");
    histogram1D[17 + 3*Ncentralities + 126]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 127] = new TH1D("pT_Proton","Proton Transverse Momentum",500,0.0,10.0);
    histogram1D[17 + 3*Ncentralities + 127]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    //histogram1D[17 + 3*Ncentralities + 127]->GetYaxis()->SetTitle("(1/p_{T})dN/dRapidity y^{-2}");
    histogram1D[17 + 3*Ncentralities + 127]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 128] = new TH1D("y_Proton","Proton Rapidity",500,-2.5,0.0);
    histogram1D[17 + 3*Ncentralities + 128]->GetXaxis()->SetTitle("y");
    histogram1D[17 + 3*Ncentralities + 128]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 129] = new TH1D("Mult_Kaon","Kaon Multiplicity",N_track,0.0,N_track);
    histogram1D[17 + 3*Ncentralities + 129]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[17 + 3*Ncentralities + 129]->GetYaxis()->SetTitle("# of Events");
    histogram1D[17 + 3*Ncentralities + 130] = new TH1D("Eta_Kaon","Kaon Pseudorapidity",500,-2.5,0.0);
    histogram1D[17 + 3*Ncentralities + 130]->GetXaxis()->SetTitle("#eta");
    histogram1D[17 + 3*Ncentralities + 130]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 131] = new TH1D("Phi_Kaon","Kaon Azimuth Angle",500,-TMath::Pi(),TMath::Pi());
    histogram1D[17 + 3*Ncentralities + 131]->GetXaxis()->SetTitle("#phi");
    histogram1D[17 + 3*Ncentralities + 131]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 132] = new TH1D("pT_Kaon","Kaon Transverse Momentum",500,0.0,10.0);
    histogram1D[17 + 3*Ncentralities + 132]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    //histogram1D[17 + 3*Ncentralities + 132]->GetYaxis()->SetTitle("(1/p_{T})dN/dRapidity y^{-2}");
    histogram1D[17 + 3*Ncentralities + 132]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 133] = new TH1D("y_Kaon","Kaon Rapidity",500,-2.5,0.0);
    histogram1D[17 + 3*Ncentralities + 133]->GetXaxis()->SetTitle("y");
    histogram1D[17 + 3*Ncentralities + 133]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 134] = new TH1D("Mult_POI","POI Multiplicity",N_track,0.0,N_track);
    histogram1D[17 + 3*Ncentralities + 134]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[17 + 3*Ncentralities + 134]->GetYaxis()->SetTitle("# of Events");
    histogram1D[17 + 3*Ncentralities + 135] = new TH1D("Mult_RFP","RFP Multiplicity",N_track,0.0,N_track);
    histogram1D[17 + 3*Ncentralities + 135]->GetXaxis()->SetTitle("# of Tracks in Event");
    histogram1D[17 + 3*Ncentralities + 135]->GetYaxis()->SetTitle("# of Events");
    // Flow plots
    char name[60], description[60];
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        sprintf(name,"v1_2_Proton_%d",icent+1);
        //sprintf(description,"(%d - %d)%% proton v_{1}(y)",80-5*(icent+1),80-5*icent);
        if( icent >  0 ) sprintf(description,"(%d-%d)%% proton v_{1}(y)",30-5*icent,30-5*(icent-1));
        if( icent == 0 ) sprintf(description,">30%% proton v_{1}(y)");
        histogram1D[15+3*icent] = new TH1D(name,description,Nbins,Low,High);
        histogram1D[15+3*icent]->GetXaxis()->SetTitle("Rapidity y");
        histogram1D[15+3*icent]->GetYaxis()->SetTitle("v_{1}");
        sprintf(name,"v1_4_Proton_%d",icent+1);
        histogram1D[16+3*icent] = new TH1D(name,description,Nbins,Low,High);
        histogram1D[16+3*icent]->GetXaxis()->SetTitle("Rapidity y");
        histogram1D[16+3*icent]->GetYaxis()->SetTitle("v_{1}");
		sprintf(name,"trackMult_%d",icent+1);
        //sprintf(description,"(%d - %d)%% Track Multiplicity",80-5*(icent+1),80-5*icent);
        if( icent >  0 ) sprintf(description,"(%d-%d)%% Track Multiplicity",30-5*icent,30-5*(icent-1));
        if( icent == 0 ) sprintf(description,">30%% Track Multiplicity");
		histogram1D[17+3*icent] = new TH1D(name,description,N_track,0.0,N_track);
		histogram1D[17+3*icent]->GetXaxis()->SetTitle("# of Tracks in Event");
		histogram1D[17+3*icent]->GetYaxis()->SetTitle("# of Events");
      }
    histogram1D[15+3*Ncentralities] = new TH1D("v1_2_Proton","(10-25)% proton v_{1}(y)",Nbins,Low,High);
    histogram1D[15+3*Ncentralities]->GetXaxis()->SetTitle("Rapidity y");
    histogram1D[15+3*Ncentralities]->GetYaxis()->SetTitle("v_{1}");
    histogram1D[15+3*Ncentralities]->SetMarkerStyle(20);histogram1D[15+3*Ncentralities]->SetMarkerColor(2);histogram1D[15+3*Ncentralities]->SetLineColor(2);
    histogram1D[16+3*Ncentralities] = new TH1D("v1_4_Proton","(10-25)% proton v_{1}(y)",Nbins,Low,High);
    histogram1D[16+3*Ncentralities]->GetXaxis()->SetTitle("Rapidity y");
    histogram1D[16+3*Ncentralities]->GetYaxis()->SetTitle("v_{1}");
    histogram1D[16+3*Ncentralities]->SetMarkerStyle(24);histogram1D[16+3*Ncentralities]->SetMarkerColor(4);histogram1D[16+3*Ncentralities]->SetLineColor(4);
    // nSigmaPion distribution
    char hist_description[200];
    for(Int_t i=0;i<30;i++)
      {
        sprintf(name,"nSigmaProton_hist_%d",i+1);
        sprintf(hist_description,"n#sigma{p^{+}} distribution for %f (GeV/c) < |p| < %f (GeV/c)",0.0+0.1*i,0.1+0.1*i);
        histogram1D[17+3*Ncentralities+i] = new TH1D(name,hist_description,400,-20.0,20.0);
        histogram1D[17+3*Ncentralities+i]->GetXaxis()->SetTitle("n#sigma{p^{+}}");
        histogram1D[17+3*Ncentralities+i]->GetYaxis()->SetTitle("# of Tracks");
        sprintf(name,"nSigmaPion_hist_%d",i+1);
        sprintf(hist_description,"n#sigma{#pi^{+}} distribution for %f (GeV/c) < |p| < %f (GeV/c)",0.0+0.1*i,0.1+0.1*i);
        histogram1D[17+3*Ncentralities+i+30] = new TH1D(name,hist_description,400,-20.0,20.0);
        histogram1D[17+3*Ncentralities+i+30]->GetXaxis()->SetTitle("n#sigma{#pi^{+}}");
        histogram1D[17+3*Ncentralities+i+30]->GetYaxis()->SetTitle("# of Tracks");
		sprintf(name,"nSigmaKaon_hist_%d",i+1);
        sprintf(hist_description,"n#sigma{K^{+}} distribution for %f (GeV/c) < |p| < %f (GeV/c)",0.0+0.1*i,0.1+0.1*i);
        histogram1D[17+3*Ncentralities+i+60] = new TH1D(name,hist_description,400,-20.0,20.0);
        histogram1D[17+3*Ncentralities+i+60]->GetXaxis()->SetTitle("n#sigma{K^{+}}");
        histogram1D[17+3*Ncentralities+i+60]->GetYaxis()->SetTitle("# of Tracks");
        sprintf(name,"nSigmaElectron_hist_%d",i+1);
        sprintf(hist_description,"n#sigma{e^{+}} distribution for %f (GeV/c) < |p| < %f (GeV/c)",0.0+0.1*i,0.1+0.1*i);
        histogram1D[17+3*Ncentralities+i+90] = new TH1D(name,hist_description,400,-20.0,20.0);
        histogram1D[17+3*Ncentralities+i+90]->GetXaxis()->SetTitle("n#sigma{e^{+}}");
        histogram1D[17+3*Ncentralities+i+90]->GetYaxis()->SetTitle("# of Tracks");
      }
    histogram1D[17 + 3*Ncentralities + 120] = new TH1D("PIDStat","# of Identified Particles from dE/dx within Possible Protons",4,0.5,4.5);
    histogram1D[17 + 3*Ncentralities + 120]->GetXaxis()->SetBinLabel(1,"Protons");
    histogram1D[17 + 3*Ncentralities + 120]->GetXaxis()->SetBinLabel(2,"Pions");
    histogram1D[17 + 3*Ncentralities + 120]->GetXaxis()->SetBinLabel(3,"Kaons");
    histogram1D[17 + 3*Ncentralities + 120]->GetXaxis()->SetBinLabel(4,"Electrons");
    histogram1D[17 + 3*Ncentralities + 120]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 121] = new TH1D("DCA","DCA to Primary Vertices",100,0.0,0.1);
    histogram1D[17 + 3*Ncentralities + 121]->GetXaxis()->SetTitle("DCA (cm)");
    histogram1D[17 + 3*Ncentralities + 121]->GetYaxis()->SetTitle("# of Tracks");
    histogram1D[17 + 3*Ncentralities + 122] = new TH1D("Phi_flatten","Flatten Azimuth Angle",500,-TMath::Pi(),TMath::Pi());
    histogram1D[17 + 3*Ncentralities + 122]->GetXaxis()->SetTitle("#phi");
    histogram1D[17 + 3*Ncentralities + 122]->GetYaxis()->SetTitle("# of Tracks");
    // Reference flows and corrections
    histogram2D[14] = new TH2D("Reference2","Q cumulant 2nd order Reference Flow",Ncentralities,0.5,Ncentralities+0.5,N_track,0.5,N_track+0.5);
    histogram2D[14]->GetXaxis()->SetTitle("Centrality Bin");
    histogram2D[14]->GetYaxis()->SetTitle("Multiplicity");
    histogram2D[15] = new TH2D("Reference4","Q cumulant 4th order Reference Flow",Ncentralities,0.5,Ncentralities+0.5,N_track,0.5,N_track+0.5);
    histogram2D[15]->GetXaxis()->SetTitle("Centrality Bin");
    histogram2D[15]->GetYaxis()->SetTitle("Multiplicity");
    histogram2D[16] = new TH2D("Correction1","<<TMath::Cos2#phi>>",Ncentralities,0.5,Ncentralities+0.5,N_track,0.5,N_track+0.5);
    histogram2D[16]->GetXaxis()->SetTitle("Centrality Bin");
    histogram2D[16]->GetYaxis()->SetTitle("Multiplicity");
    histogram2D[17] = new TH2D("Correction2","<<TMath::Sin2#phi>>",Ncentralities,0.5,Ncentralities+0.5,N_track,0.5,N_track+0.5);
    histogram2D[17]->GetXaxis()->SetTitle("Centrality Bin");
    histogram2D[17]->GetYaxis()->SetTitle("Multiplicity");
    // Cosmetic Setup
    /*for( Int_t iHist = 0; iHist < Nhistograms; iHist++ )
      {
        histogram1D[iHist]->GetXaxis()->SetTitleSize(0.05);
        histogram1D[iHist]->GetXaxis()->SetTitleOffset(0.9);
        histogram1D[iHist]->GetYaxis()->SetTitleSize(0.05);
        histogram1D[iHist]->GetYaxis()->SetTitleOffset(0.9);
        if( iHist < 21 )
          {
            histogram2D[iHist]->GetXaxis()->SetTitleSize(0.05);
            histogram2D[iHist]->GetXaxis()->SetTitleOffset(0.9);
            histogram2D[iHist]->GetYaxis()->SetTitleSize(0.05);
            histogram2D[iHist]->GetYaxis()->SetTitleOffset(0.9);
          }
      }*/
    // TArrayD to Save flow variables
    flowArray     = new TArrayD( (24 + 30*Nbins)*N_track*Ncentralities );
    flowArray2    = new TArrayD( N_track );
    flowArrayCOV1 = new TArrayD( ( 8 + 34*Nbins)*N_track*Ncentralities );
    flowArrayCOV2 = new TArrayD( ( 8 + 34*Nbins)*N_track*Ncentralities );
    flowArrayCOV3 = new TArrayD( ( 8 + 34*Nbins)*N_track*Ncentralities );
    flowArrayCOV4 = new TArrayD( ( 8 + 35*Nbins)*N_track*Ncentralities );
    return kStOK;
  }

Int_t FxtMaker::Finish()
{
    // Save flow variables to TArrayD
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
		for ( Int_t itrack = 0; itrack < N_track; itrack++ )
		  {
            flowArray->AddAt(           sumS11[itrack][icent],  0 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(           sumM11[itrack][icent],  1 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(          sumM111[itrack][icent],  2 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(         sumM1111[itrack][icent],  3 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(         sumCorr2[itrack][icent],  4 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(         sumCorr4[itrack][icent],  5 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon1[itrack][icent],  6 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon2[itrack][icent],  7 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon5[itrack][icent],  8 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon6[itrack][icent],  9 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon7[itrack][icent], 10 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(        sumAddon8[itrack][icent], 11 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(    sumS11Squared[itrack][icent], 12 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(    sumM11Squared[itrack][icent], 13 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(   sumM111Squared[itrack][icent], 14 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(  sumM1111Squared[itrack][icent], 15 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(  sumCorr2Squared[itrack][icent], 16 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt(  sumCorr4Squared[itrack][icent], 17 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon1Squared[itrack][icent], 18 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon2Squared[itrack][icent], 19 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon5Squared[itrack][icent], 20 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon6Squared[itrack][icent], 21 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon7Squared[itrack][icent], 22 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
            flowArray->AddAt( sumAddon8Squared[itrack][icent], 23 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
			for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
			  {
                flowArray->AddAt(                  sumMp[ibin][itrack][icent], 24 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(                 sumM01[ibin][itrack][icent], 25 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(                sumM011[ibin][itrack][icent], 26 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(               sumM0111[ibin][itrack][icent], 27 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(        sumCorr2Reduced[ibin][itrack][icent], 28 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(        sumCorr4Reduced[ibin][itrack][icent], 29 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(              sumAddon3[ibin][itrack][icent], 30 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(              sumAddon4[ibin][itrack][icent], 31 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(              sumAddon9[ibin][itrack][icent], 32 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon10[ibin][itrack][icent], 33 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon11[ibin][itrack][icent], 34 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon12[ibin][itrack][icent], 35 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon13[ibin][itrack][icent], 36 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon14[ibin][itrack][icent], 37 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(             sumAddon15[ibin][itrack][icent], 38 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(           sumMpSquared[ibin][itrack][icent], 39 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(          sumM01Squared[ibin][itrack][icent], 40 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(         sumM011Squared[ibin][itrack][icent], 41 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(        sumM0111Squared[ibin][itrack][icent], 42 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt( sumCorr2ReducedSquared[ibin][itrack][icent], 43 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt( sumCorr4ReducedSquared[ibin][itrack][icent], 44 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(       sumAddon3Squared[ibin][itrack][icent], 45 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(       sumAddon4Squared[ibin][itrack][icent], 46 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(       sumAddon9Squared[ibin][itrack][icent], 47 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon10Squared[ibin][itrack][icent], 48 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon11Squared[ibin][itrack][icent], 49 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon12Squared[ibin][itrack][icent], 50 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon13Squared[ibin][itrack][icent], 51 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon14Squared[ibin][itrack][icent], 52 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
                flowArray->AddAt(      sumAddon15Squared[ibin][itrack][icent], 53 + ibin*30 + (24 + 30*Nbins)*itrack + (24 + 30*Nbins)*N_track*icent );
			  }
		  }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV1->AddAt(  sumM11S11[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C1[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C2[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C5[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C6[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumM11M111[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C7[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV1->AddAt( sumCorr2C8[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV1->AddAt(            sumM11mp[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(          sumCorr2C3[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumCorr2C4[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumM11M011[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumCorr2C9[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(        sumCorr2C10[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(        sumCorr2C11[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(        sumCorr2C12[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(        sumCorr2C13[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(        sumCorr2C14[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(          sumM01S11[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC1[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC2[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(           sumM01mp[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC3[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC4[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC5[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC6[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumM111M01[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC7[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC8[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumM01M011[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(  sumCorr2ReducedC9[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt( sumCorr2ReducedC10[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt( sumCorr2ReducedC11[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt( sumCorr2ReducedC12[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt( sumCorr2ReducedC13[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt( sumCorr2ReducedC14[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumM1111mp[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumCorr4C3[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumCorr4C4[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(       sumM1111M011[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(         sumCorr4C9[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV1->AddAt(          sumC13C14[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV2->AddAt(  sumM1111S11[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C1[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C2[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C5[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C6[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt( sumM111M1111[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C7[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV2->AddAt(   sumCorr4C8[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV2->AddAt(         sumCorr4C10[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(         sumCorr4C11[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(        sumCorr4C12[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(        sumCorr4C13[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(        sumCorr4C14[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(        sumM0111S11[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC1[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC2[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(         sumM0111mp[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC3[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC4[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC5[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC6[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(       sumM111M0111[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC7[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC8[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(       sumM011M0111[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(  sumCorr4ReducedC9[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt( sumCorr4ReducedC10[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt( sumCorr4ReducedC11[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt( sumCorr4ReducedC12[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt( sumCorr4ReducedC13[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt( sumCorr4ReducedC14[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumS11mp[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(            sumC1C3[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(            sumC1C4[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(         sumM011S11[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(            sumC1C9[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumC1C10[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumC1C11[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumC1C12[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumC1C13[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(           sumC1C14[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV2->AddAt(            sumC2C3[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV3->AddAt(    sumC1C2[itrack][icent], 0 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC1C5[itrack][icent], 1 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC1C6[itrack][icent], 2 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt( sumM111S11[itrack][icent], 3 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC1C7[itrack][icent], 4 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC1C8[itrack][icent], 5 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC2C5[itrack][icent], 6 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            flowArrayCOV3->AddAt(    sumC2C6[itrack][icent], 7 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV3->AddAt(    sumC2C4[ibin][itrack][icent], 8 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(    sumC2C9[ibin][itrack][icent], 9 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC2C10[ibin][itrack][icent], 10 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC2C11[ibin][itrack][icent], 11 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC2C12[ibin][itrack][icent], 12 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC2C13[ibin][itrack][icent], 13 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC2C14[ibin][itrack][icent], 14 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C4[ibin][itrack][icent], 15 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C5[ibin][itrack][icent], 16 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C6[ibin][itrack][icent], 17 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt( sumM111mp[ibin][itrack][icent], 18 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C7[ibin][itrack][icent], 19 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C8[ibin][itrack][icent], 20 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt( sumM011mp[ibin][itrack][icent], 21 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC3C9[ibin][itrack][icent], 22 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC3C10[ibin][itrack][icent], 23 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC3C11[ibin][itrack][icent], 24 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC3C12[ibin][itrack][icent], 25 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC3C13[ibin][itrack][icent], 26 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC3C14[ibin][itrack][icent], 27 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC4C5[ibin][itrack][icent], 28 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC4C6[ibin][itrack][icent], 29 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC4C7[ibin][itrack][icent], 30 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC4C8[ibin][itrack][icent], 31 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC4C9[ibin][itrack][icent], 32 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC4C10[ibin][itrack][icent], 33 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC4C11[ibin][itrack][icent], 34 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC4C12[ibin][itrack][icent], 35 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC4C13[ibin][itrack][icent], 36 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC4C14[ibin][itrack][icent], 37 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(   sumC5C9[ibin][itrack][icent], 38 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC5C10[ibin][itrack][icent], 39 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC5C11[ibin][itrack][icent], 40 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
                flowArrayCOV3->AddAt(  sumC5C12[ibin][itrack][icent], 41 + ibin*34 + (8 + 34*Nbins)*itrack + (8 + 34*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            flowArrayCOV4->AddAt( sumC2C7[itrack][icent], 0 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC2C8[itrack][icent], 1 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC5C6[itrack][icent], 2 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC5C7[itrack][icent], 3 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC5C8[itrack][icent], 4 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC6C7[itrack][icent], 5 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC6C8[itrack][icent], 6 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            flowArrayCOV4->AddAt( sumC7C8[itrack][icent], 7 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                flowArrayCOV4->AddAt(     sumC5C13[ibin][itrack][icent], 8 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(     sumC5C14[ibin][itrack][icent], 9 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(     sumC6C9[ibin][itrack][icent], 10 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC6C10[ibin][itrack][icent], 11 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC6C11[ibin][itrack][icent], 12 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC6C12[ibin][itrack][icent], 13 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC6C13[ibin][itrack][icent], 14 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC6C14[ibin][itrack][icent], 15 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt( sumM111M011[ibin][itrack][icent], 16 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(     sumC7C9[ibin][itrack][icent], 17 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC7C10[ibin][itrack][icent], 18 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC7C11[ibin][itrack][icent], 19 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC7C12[ibin][itrack][icent], 20 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC7C13[ibin][itrack][icent], 21 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC7C14[ibin][itrack][icent], 22 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(     sumC8C9[ibin][itrack][icent], 23 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC8C10[ibin][itrack][icent], 24 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC8C11[ibin][itrack][icent], 25 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC8C12[ibin][itrack][icent], 26 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC8C13[ibin][itrack][icent], 27 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC8C14[ibin][itrack][icent], 28 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC9C10[ibin][itrack][icent], 29 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC9C11[ibin][itrack][icent], 30 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC9C12[ibin][itrack][icent], 31 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC9C13[ibin][itrack][icent], 32 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(    sumC9C14[ibin][itrack][icent], 33 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC10C11[ibin][itrack][icent], 34 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC10C12[ibin][itrack][icent], 35 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC10C13[ibin][itrack][icent], 36 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC10C14[ibin][itrack][icent], 37 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC11C12[ibin][itrack][icent], 38 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC11C13[ibin][itrack][icent], 39 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC11C14[ibin][itrack][icent], 40 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC12C13[ibin][itrack][icent], 41 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
                flowArrayCOV4->AddAt(   sumC12C14[ibin][itrack][icent], 42 + ibin*35 + (8 + 35*Nbins)*itrack + (8 + 35*Nbins)*N_track*icent );
              }
          }
      }
    for ( Int_t itrack = 0; itrack < N_track; itrack++ )
      {
        flowArray2->AddAt(multCounter[itrack],itrack);
      }
    // Reference Flows and their correction terms
    Double_t      v1_2[Nbins][N_track][Ncentralities],
    v1_4[Nbins][N_track][Ncentralities],
    v1_2Error[Nbins][N_track][Ncentralities],
    v1_4Error[Nbins][N_track][Ncentralities],
    reference2_1,
    reference2_2,
    reference2_3,
    reference4_1,
    reference4_2,
    reference4_3,
    reference4_4,
    correction1,
    correction2,
    correction5,
    correction6,
    correction7,
    correction8,
    reference2Error1,
    //reference2Error2,
    reference2Error3,
    reference4Error1,
    //reference4Error2,
    reference4Error3,
    correction1Error,
    correction2Error,
    correction5Error,
    correction6Error,
    correction7Error,
    correction8Error,
    covRef2Ref4,
    covRef2C1,
    covRef2C2,
    covRef2C5,
    covRef2C6,
    covRef2C7,
    covRef2C8,
    covRef4C1,
    covRef4C2,
    covRef4C5,
    covRef4C6,
    covRef4C7,
    covRef4C8,
    covC1C2,
    covC1C5,
    covC1C6,
    covC1C7,
    covC1C8,
    covC2C5,
    covC2C6,
    covC2C7,
    covC2C8,
    covC5C6,
    covC5C7,
    covC5C8,
    covC6C7,
    covC6C8,
    covC7C8,
    sign2,
    sign4,
    dr23r2,
    dr23c1,
    dr23c2,
    dr43r4,
    dr43r2,
    dr43c1,
    dr43c2,
    dr43c5,
    dr43c6,
    dr43c7,
    dr43c8;
    Double_t  differential2_1,
    differential2_2,
    differential4_1,
    differential4_2,
    correction3,
    correction4,
    correction9,
    correction10,
    correction11,
    correction12,
    correction13,
    correction14,
    differential2Error1,
    //differential2Error2,
    differential4Error1,
    //differential4Error2,
    correction3Error,
    correction4Error,
    correction9Error,
    correction10Error,
    correction11Error,
    correction12Error,
    correction13Error,
    correction14Error,
    covRef2Def2,
    covRef2Def4,
    covRef4Def2,
    covRef4Def4,
    covDef2Def4,
    covRef2C3,
    covRef2C4,
    covRef2C9,
    covRef2C10,
    covRef2C11,
    covRef2C12,
    covRef2C13,
    covRef2C14,
    covDef2C1,
    covDef2C2,
    covDef2C3,
    covDef2C4,
    covDef2C5,
    covDef2C6,
    covDef2C7,
    covDef2C8,
    covDef2C9,
    covDef2C10,
    covDef2C11,
    covDef2C12,
    covDef2C13,
    covDef2C14,
    covRef4C3,
    covRef4C4,
    covRef4C9,
    covRef4C10,
    covRef4C11,
    covRef4C12,
    covRef4C13,
    covRef4C14,
    covDef4C1,
    covDef4C2,
    covDef4C3,
    covDef4C4,
    covDef4C5,
    covDef4C6,
    covDef4C7,
    covDef4C8,
    covDef4C9,
    covDef4C10,
    covDef4C11,
    covDef4C12,
    covDef4C13,
    covDef4C14;
    Double_t   covC1C3,
    covC1C4,
    covC1C9,
    covC1C10,
    covC1C11,
    covC1C12,
    covC1C13,
    covC1C14,
    covC2C3,
    covC2C4,
    covC2C9,
    covC2C10,
    covC2C11,
    covC2C12,
    covC2C13,
    covC2C14,
    covC3C4,
    covC3C5,
    covC3C6,
    covC3C7,
    covC3C8,
    covC3C9,
    covC3C10,
    covC3C11,
    covC3C12,
    covC3C13,
    covC3C14,
    covC4C5,
    covC4C6,
    covC4C7,
    covC4C8,
    covC4C9,
    covC4C10,
    covC4C11,
    covC4C12,
    covC4C13,
    covC4C14,
    covC5C9,
    covC5C10,
    covC5C11,
    covC5C12,
    covC5C13,
    covC5C14,
    covC6C9,
    covC6C10,
    covC6C11,
    covC6C12,
    covC6C13,
    covC6C14,
    covC7C9,
    covC7C10,
    covC7C11,
    covC7C12,
    covC7C13,
    covC7C14,
    covC8C9,
    covC8C10,
    covC8C11,
    covC8C12,
    covC8C13,
    covC8C14,
    covC9C10,
    covC9C11,
    covC9C12,
    covC9C13,
    covC9C14,
    covC10C11,
    covC10C12,
    covC10C13,
    covC10C14,
    covC11C12,
    covC11C13,
    covC11C14,
    covC12C13,
    covC12C14,
    covC13C14,
    df2dr2,
    df2dd2,
    df2dc1,
    df2dc2,
    df2dc3,
    df2dc4,
    df4dr2,
    df4dd2,
    df4dr4,
    df4dd4,
    df4dc1,
    df4dc2,
    df4dc3,
    df4dc4,
    df4dc5,
    df4dc6,
    df4dc7,
    df4dc8,
    df4dc9,
    df4dc10,
    df4dc11,
    df4dc12,
    df4dc13,
    df4dc14;
    for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
        for ( Int_t itrack = 0; itrack < N_track; itrack++ )
          {
            if(multCounter[itrack] < 5) continue;
            reference2_1 = 0.;
            reference2_2 = 0.;
            reference2_3 = 0.;
            reference4_1 = 0.;
            reference4_2 = 0.;
            reference4_3 = 0.;
            reference4_4 = 0.;
            correction1 = 0.;
            correction2 = 0.;
            correction5 = 0.;
            correction6 = 0.;
            correction7 = 0.;
            correction8 = 0.;
            reference2Error1 = 0.;
            //reference2Error2 = 0.;
            reference2Error3 = 0.;
            reference4Error1 = 0.;
            //reference4Error2 = 0.;
            reference4Error3 = 0.;
            correction1Error = 0.;
            correction2Error = 0.;
            correction5Error = 0.;
            correction6Error = 0.;
            correction7Error = 0.;
            correction8Error = 0.;
            covRef2Ref4 = 0.;
            covRef2C1 = 0.;
            covRef2C2 = 0.;
            covRef2C5 = 0.;
            covRef2C6 = 0.;
            covRef2C7 = 0.;
            covRef2C8 = 0.;
            covRef4C1 = 0.;
            covRef4C2 = 0.;
            covRef4C5 = 0.;
            covRef4C6 = 0.;
            covRef4C7 = 0.;
            covRef4C8 = 0.;
            covC1C2 = 0.;
            covC1C5 = 0.;
            covC1C6 = 0.;
            covC1C7 = 0.;
            covC1C8 = 0.;
            covC2C5 = 0.;
            covC2C6 = 0.;
            covC2C7 = 0.;
            covC2C8 = 0.;
            covC5C6 = 0.;
            covC5C7 = 0.;
            covC5C8 = 0.;
            covC6C7 = 0.;
            covC6C8 = 0.;
            covC7C8 = 0.;
            sign2 = 0.;
            sign4 = 0.;
            dr23r2 = 0.;
            dr23c1 = 0.;
            dr23c2 = 0.;
            dr43r4 = 0.;
            dr43r2 = 0.;
            dr43c1 = 0.;
            dr43c2 = 0.;
            dr43c5 = 0.;
            dr43c6 = 0.;
            dr43c7 = 0.;
            dr43c8 = 0.;
            // get mean
            reference2_1 = (   sumM11[itrack][icent] != 0.0 ) ?  sumCorr2[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(reference2_1)) reference2_1 = 0.0;
            reference4_1 = ( sumM1111[itrack][icent] != 0.0 ) ?  sumCorr4[itrack][icent] / sumM1111[itrack][icent] : 0.0;
            if(!TMath::Finite(reference4_1)) reference4_1 = 0.0; if(reference2_1 == 0. || reference4_1 == 0.) continue;
            correction1 = (   sumS11[itrack][icent] != 0.0 ) ? sumAddon1[itrack][icent] /   sumS11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction1)) correction1 = 0.0;
            correction2 = (   sumS11[itrack][icent] != 0.0 ) ? sumAddon2[itrack][icent] /   sumS11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction2)) correction2 = 0.0;
            correction5 = (   sumM11[itrack][icent] != 0.0 ) ? sumAddon5[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction5)) correction5 = 0.0;
            correction6 = (   sumM11[itrack][icent] != 0.0 ) ? sumAddon6[itrack][icent] /   sumM11[itrack][icent] : 0.0;
            if(!TMath::Finite(correction6)) correction6 = 0.0;
            correction7 = (  sumM111[itrack][icent] != 0.0 ) ? sumAddon7[itrack][icent] /  sumM111[itrack][icent] : 0.0;
            if(!TMath::Finite(correction7)) correction7 = 0.0;
            correction8 = (  sumM111[itrack][icent] != 0.0 ) ? sumAddon8[itrack][icent] /  sumM111[itrack][icent] : 0.0;
            if(!TMath::Finite(correction8)) correction8 = 0.0;
            // get error on mean
            reference2Error1 = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumCorr2[itrack][icent],sumCorr2Squared[itrack][icent]);
            reference4Error1 = GetError(sumM1111[itrack][icent],sumM1111Squared[itrack][icent],sumCorr4[itrack][icent],sumCorr4Squared[itrack][icent]);
            if(reference2Error1 == 0. || reference4Error1 == 0.) continue;
            correction1Error = GetError(sumS11[itrack][icent],sumS11Squared[itrack][icent],sumAddon1[itrack][icent],sumAddon1Squared[itrack][icent]);
            correction2Error = GetError(sumS11[itrack][icent],sumS11Squared[itrack][icent],sumAddon2[itrack][icent],sumAddon2Squared[itrack][icent]);
            correction5Error = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumAddon5[itrack][icent],sumAddon5Squared[itrack][icent]);
            correction6Error = GetError(sumM11[itrack][icent],sumM11Squared[itrack][icent],sumAddon6[itrack][icent],sumAddon6Squared[itrack][icent]);
            correction7Error = GetError(sumM111[itrack][icent],sumM111Squared[itrack][icent],sumAddon7[itrack][icent],sumAddon7Squared[itrack][icent]);
            correction8Error = GetError(sumM111[itrack][icent],sumM111Squared[itrack][icent],sumAddon8[itrack][icent],sumAddon8Squared[itrack][icent]);
            // Covariance terms
            covRef2Ref4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM1111[itrack][icent],sumCorr4[itrack][icent],
                                        sumM11M1111[itrack][icent],sumCorr2Corr4[itrack][icent]);
            covRef2C1 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                      sumM11S11[itrack][icent],sumCorr2C1[itrack][icent]);
            covRef2C2 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                      sumM11S11[itrack][icent],sumCorr2C2[itrack][icent]);
            covRef2C5 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                      sumM11Squared[itrack][icent],sumCorr2C5[itrack][icent]);
            covRef2C6 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                      sumM11Squared[itrack][icent],sumCorr2C6[itrack][icent]);
            covRef2C7 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                      sumM11M111[itrack][icent],sumCorr2C7[itrack][icent]);
            covRef2C8 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                      sumM11M111[itrack][icent],sumCorr2C8[itrack][icent]);
            covRef4C1 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                      sumM1111S11[itrack][icent],sumCorr4C1[itrack][icent]);
            covRef4C2 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                      sumM1111S11[itrack][icent],sumCorr4C2[itrack][icent]);
            covRef4C5 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                      sumM11M1111[itrack][icent],sumCorr4C5[itrack][icent]);
            covRef4C6 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                      sumM11M1111[itrack][icent],sumCorr4C6[itrack][icent]);
            covRef4C7 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                      sumM111M1111[itrack][icent],sumCorr4C7[itrack][icent]);
            covRef4C8 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                      sumM111M1111[itrack][icent],sumCorr4C8[itrack][icent]);
            covC1C2 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                    sumS11Squared[itrack][icent],sumC1C2[itrack][icent]);
            covC1C5 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                    sumM11S11[itrack][icent],sumC1C5[itrack][icent]);
            covC1C6 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11S11[itrack][icent],sumC1C6[itrack][icent]);
            covC1C7 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM111S11[itrack][icent],sumC1C7[itrack][icent]);
            covC1C8 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111S11[itrack][icent],sumC1C8[itrack][icent]);
            covC2C5 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                    sumM11S11[itrack][icent],sumC2C5[itrack][icent]);
            covC2C6 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11S11[itrack][icent],sumC2C6[itrack][icent]);
            covC2C7 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM111S11[itrack][icent],sumC2C7[itrack][icent]);
            covC2C8 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111S11[itrack][icent],sumC2C8[itrack][icent]);
            covC5C6 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                    sumM11Squared[itrack][icent],sumC5C6[itrack][icent]);
            covC5C7 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM11M111[itrack][icent],sumC5C7[itrack][icent]);
            covC5C8 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM11M111[itrack][icent],sumC5C8[itrack][icent]);
            covC6C7 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                    sumM11M111[itrack][icent],sumC6C7[itrack][icent]);
            covC6C8 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM11M111[itrack][icent],sumC6C8[itrack][icent]);
            covC7C8 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                    sumM111Squared[itrack][icent],sumC7C8[itrack][icent]);
            // Corrected Reference Flows
            reference2_2 = reference2_1 - correction1*correction1 - correction2*correction2;
            if(!TMath::Finite(reference2_2)) reference2_2 = 0.0;
            reference4_2 = reference4_1 - 2.0*reference2_1*reference2_1
            - 4.0*correction1*correction7
            + 4.0*correction2*correction8
            - correction5*correction5 - correction6*correction6
            + 4.0*correction5*( correction1*correction1 - correction2*correction2 )
            + 8.0*correction6*correction2*correction1
            + 8.0*reference2_1*( correction1*correction1 + correction2*correction2 )
            - 6.0*TMath::Power( correction1*correction1 + correction2*correction2, 2.0 );
            if(!TMath::Finite(reference4_2)) reference4_2 = 0.0;
            // prepare reference flow to be divided
            //sign2 = (reference2_2 > 0.)? 1.:-1.; sign4 = (reference4_2 > 0.)? 1.:-1.;
            sign2 = 1.; sign4 = -1.;
            reference2_3 = TMath::Sqrt( sign2*reference2_2 );
            if(!TMath::Finite(reference2_3)) reference2_3 = 0.0;
            reference4_3 =  TMath::Power( sign4*reference4_2, 3.0/4.0 );
            if(!TMath::Finite(reference4_3)) reference4_3 = 0.0; //if(reference2_3 == 0. || reference4_3 == 0.) continue;
            // differentiate QC2 reference flow
            dr23r2 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*1.;
            if(!TMath::Finite(dr23r2)) dr23r2 = 0.0;
            dr23c1 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*(-2.*correction1);
            if(!TMath::Finite(dr23c1)) dr23c1 = 0.0;
            dr23c2 = 0.5*TMath::Power(sign2*reference2_2,-0.5)*sign2*(-2.*correction2);
            if(!TMath::Finite(dr23c2)) dr23c2 = 0.0;
            // error propagation
            reference2Error3 = TMath::Sqrt(TMath::Power(dr23r2,2.)*reference2Error1
                                           +TMath::Power(dr23c1,2.)*correction1Error
                                           +TMath::Power(dr23c2,2.)*correction2Error
                                           +2.*dr23r2*dr23c1*covRef2C1
                                           +2.*dr23r2*dr23c2*covRef2C2
                                           +2.*dr23c1*dr23c2*covC1C2
                                           );
            if(!TMath::Finite(reference2Error3) || reference2_3 == 0.) reference2Error3 = 0.0;
            // differentiate QC4 reference flow
            dr43r4 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*1.;
            if(!TMath::Finite(dr43r4)) dr43r4 = 0.0;
            dr43r2 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*reference2_1+8.*( correction1*correction1 + correction2*correction2 ));
            if(!TMath::Finite(dr43r2)) dr43r2 = 0.0;
            dr43c1 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*correction7+8.*correction5*correction1+8.*correction6*correction2+16.*reference2_1*correction1
                                                                        -24.*correction1*(correction1*correction1 + correction2*correction2));
            if(!TMath::Finite(dr43c1)) dr43c1 = 0.0;
            dr43c2 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(4.*correction8-8.*correction5*correction2+8.*correction6*correction1+16.*reference2_1*correction2
                                                                        -24.*correction2*(correction1*correction1 + correction2*correction2));
            if(!TMath::Finite(dr43c2)) dr43c2 = 0.0;
            dr43c5 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-2.*correction5+4.*( correction1*correction1 - correction2*correction2 ));
            if(!TMath::Finite(dr43c5)) dr43c5 = 0.0;
            dr43c6 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-2.*correction6+8.*correction2*correction1);
            if(!TMath::Finite(dr43c6)) dr43c6 = 0.0;
            dr43c7 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(-4.*correction1);
            if(!TMath::Finite(dr43c7)) dr43c7 = 0.0;
            dr43c8 = 0.25*TMath::Power(sign4*reference4_2,-0.75)*sign4*(4.*correction2);
            if(!TMath::Finite(dr43c8)) dr43c8 = 0.0;
            // error propagation
            reference4Error3 = TMath::Sqrt(TMath::Power(dr43r4,2.)*reference4Error1
                                           +TMath::Power(dr43r2,2.)*reference2Error1
                                           +TMath::Power(dr43c1,2.)*correction1Error
                                           +TMath::Power(dr43c2,2.)*correction2Error
                                           +TMath::Power(dr43c5,2.)*correction5Error
                                           +TMath::Power(dr43c6,2.)*correction6Error
                                           +TMath::Power(dr43c7,2.)*correction7Error
                                           +TMath::Power(dr43c8,2.)*correction8Error
                                           
                                           +2.*dr43r4*dr43r2*covRef2Ref4
                                           +2.*dr43r4*dr43c1*covRef4C1
                                           +2.*dr43r4*dr43c2*covRef4C2
                                           +2.*dr43r4*dr43c5*covRef4C5
                                           +2.*dr43r4*dr43c6*covRef4C6
                                           +2.*dr43r4*dr43c7*covRef4C7
                                           +2.*dr43r4*dr43c8*covRef4C8
                                           
                                           +2.*dr43r2*dr43c1*covRef2C1
                                           +2.*dr43r2*dr43c2*covRef2C2
                                           +2.*dr43r2*dr43c5*covRef2C5
                                           +2.*dr43r2*dr43c6*covRef2C6
                                           +2.*dr43r2*dr43c7*covRef2C7
                                           +2.*dr43r2*dr43c8*covRef2C8
                                           
                                           +2.*dr43c1*dr43c2*covC1C2
                                           +2.*dr43c1*dr43c5*covC1C5
                                           +2.*dr43c1*dr43c6*covC1C6
                                           +2.*dr43c1*dr43c7*covC1C7
                                           +2.*dr43c1*dr43c8*covC1C8
                                           
                                           +2.*dr43c2*dr43c5*covC2C5
                                           +2.*dr43c2*dr43c6*covC2C6
                                           +2.*dr43c2*dr43c7*covC2C7
                                           +2.*dr43c2*dr43c8*covC2C8
                                           
                                           +2.*dr43c5*dr43c6*covC5C6
                                           +2.*dr43c5*dr43c7*covC5C7
                                           +2.*dr43c5*dr43c8*covC5C8
                                           
                                           +2.*dr43c6*dr43c7*covC6C7
                                           +2.*dr43c6*dr43c8*covC6C8
                                           
                                           +2.*dr43c7*dr43c8*covC7C8
                                           );
            if(!TMath::Finite(reference4Error3) || reference4_3 == 0.) reference4Error3 = 0.0;
            //hr2->SetBinContent(itrack+1,reference2_3);hr2->SetBinError(itrack+1,reference2Error3);
            // QC4 reference flow
            reference4_4 = TMath::Power( sign4*reference4_2, 1.0/4.0 );
            if(!TMath::Finite(reference4_4)) reference4_4 = 0.0;
            //hr4->SetBinContent(itrack+1,reference4_4);hr2->SetBinError(itrack+1,reference4Error3);
            // compute differential flows
            for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
              {
                v1_2[ibin][itrack][icent] = 0.;
                v1_2Error[ibin][itrack][icent] = 0.;
                v1_4[ibin][itrack][icent] = 0.;
                v1_4Error[ibin][itrack][icent] = 0.;
                differential2_1 = 0.;
                differential2_2 = 0.;
                differential4_1 = 0.;
                differential4_2 = 0.;
                correction3 = 0.;
                correction4 = 0.;
                correction9 = 0.;
                correction10 = 0.;
                correction11 = 0.;
                correction12 = 0.;
                correction13 = 0.;
                correction14 = 0.;
                differential2Error1 = 0.;
                //differential2Error2 = 0.;
                differential4Error1 = 0.;
                //differential4Error2 = 0.;
                correction3Error = 0.;
                correction4Error = 0.;
                correction9Error = 0.;
                correction10Error = 0.;
                correction11Error = 0.;
                correction12Error = 0.;
                correction13Error = 0.;
                correction14Error = 0.;
                covRef2Def2 = 0.;
                covRef2Def4 = 0.;
                covRef4Def2 = 0.;
                covRef4Def4 = 0.;
                covDef2Def4 = 0.;
                covRef2C3 = 0.;
                covRef2C4 = 0.;
                covRef2C9 = 0.;
                covRef2C10 = 0.;
                covRef2C11 = 0.;
                covRef2C12 = 0.;
                covRef2C13 = 0.;
                covRef2C14 = 0.;
                covDef2C1 = 0.;
                covDef2C2 = 0.;
                covDef2C3 = 0.;
                covDef2C4 = 0.;
                covDef2C5 = 0.;
                covDef2C6 = 0.;
                covDef2C7 = 0.;
                covDef2C8 = 0.;
                covDef2C9 = 0.;
                covDef2C10 = 0.;
                covDef2C11 = 0.;
                covDef2C12 = 0.;
                covDef2C13 = 0.;
                covDef2C14 = 0.;
                covRef4C3 = 0.;
                covRef4C4 = 0.;
                covRef4C9 = 0.;
                covRef4C10 = 0.;
                covRef4C11 = 0.;
                covRef4C12 = 0.;
                covRef4C13 = 0.;
                covRef4C14 = 0.;
                covDef4C1 = 0.;
                covDef4C2 = 0.;
                covDef4C3 = 0.;
                covDef4C4 = 0.;
                covDef4C5 = 0.;
                covDef4C6 = 0.;
                covDef4C7 = 0.;
                covDef4C8 = 0.;
                covDef4C9 = 0.;
                covDef4C10 = 0.;
                covDef4C11 = 0.;
                covDef4C12 = 0.;
                covDef4C13 = 0.;
                covDef4C14 = 0.;
                covC1C3 = 0.;
                covC1C4 = 0.;
                covC1C9 = 0.;
                covC1C10 = 0.;
                covC1C11 = 0.;
                covC1C12 = 0.;
                covC1C13 = 0.;
                covC1C14 = 0.;
                covC2C3 = 0.;
                covC2C4 = 0.;
                covC2C9 = 0.;
                covC2C10 = 0.;
                covC2C11 = 0.;
                covC2C12 = 0.;
                covC2C13 = 0.;
                covC2C14 = 0.;
                covC3C4 = 0.;
                covC3C5 = 0.;
                covC3C6 = 0.;
                covC3C7 = 0.;
                covC3C8 = 0.;
                covC3C9 = 0.;
                covC3C10 = 0.;
                covC3C11 = 0.;
                covC3C12 = 0.;
                covC3C13 = 0.;
                covC3C14 = 0.;
                covC4C5 = 0.;
                covC4C6 = 0.;
                covC4C7 = 0.;
                covC4C8 = 0.;
                covC4C9 = 0.;
                covC4C10 = 0.;
                covC4C11 = 0.;
                covC4C12 = 0.;
                covC4C13 = 0.;
                covC4C14 = 0.;
                covC5C9 = 0.;
                covC5C10 = 0.;
                covC5C11 = 0.;
                covC5C12 = 0.;
                covC5C13 = 0.;
                covC5C14 = 0.;
                covC6C9 = 0.;
                covC6C10 = 0.;
                covC6C11 = 0.;
                covC6C12 = 0.;
                covC6C13 = 0.;
                covC6C14 = 0.;
                covC7C9 = 0.;
                covC7C10 = 0.;
                covC7C11 = 0.;
                covC7C12 = 0.;
                covC7C13 = 0.;
                covC7C14 = 0.;
                covC8C9 = 0.;
                covC8C10 = 0.;
                covC8C11 = 0.;
                covC8C12 = 0.;
                covC8C13 = 0.;
                covC8C14 = 0.;
                covC9C10 = 0.;
                covC9C11 = 0.;
                covC9C12 = 0.;
                covC9C13 = 0.;
                covC9C14 = 0.;
                covC10C11 = 0.;
                covC10C12 = 0.;
                covC10C13 = 0.;
                covC10C14 = 0.;
                covC11C12 = 0.;
                covC11C13 = 0.;
                covC11C14 = 0.;
                covC12C13 = 0.;
                covC12C14 = 0.;
                covC13C14 = 0.;
                df2dr2 = 0.;
                df2dd2 = 0.;
                df2dc1 = 0.;
                df2dc2 = 0.;
                df2dc3 = 0.;
                df2dc4 = 0.;
                df4dr2 = 0.;
                df4dd2 = 0.;
                df4dr4 = 0.;
                df4dd4 = 0.;
                df4dc1 = 0.;
                df4dc2 = 0.;
                df4dc3 = 0.;
                df4dc4 = 0.;
                df4dc5 = 0.;
                df4dc6 = 0.;
                df4dc7 = 0.;
                df4dc8 = 0.;
                df4dc9 = 0.;
                df4dc10 = 0.;
                df4dc11 = 0.;
                df4dc12 = 0.;
                df4dc13 = 0.;
                df4dc14= 0.;
                // Differential Flows and their correction terms
                differential2_1 = (   sumM01[ibin][itrack][icent] != 0.0 ) ? sumCorr2Reduced[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(differential2_1)) differential2_1 = 0.0;
                differential4_1 = ( sumM0111[ibin][itrack][icent] != 0.0 ) ? sumCorr4Reduced[ibin][itrack][icent] / sumM0111[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(differential4_1)) differential4_1 = 0.0; if(differential2_1 == 0. || differential4_1 == 0.) continue;
                correction3 = (    sumMp[ibin][itrack][icent] != 0.0 ) ?       sumAddon3[ibin][itrack][icent] /    sumMp[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction3)) correction3 = 0.0;
                correction4 = (    sumMp[ibin][itrack][icent] != 0.0 ) ?       sumAddon4[ibin][itrack][icent] /    sumMp[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction4)) correction4 = 0.0;
                correction9 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?       sumAddon9[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction9)) correction9 = 0.0;
                correction10 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon10[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction10)) correction10 = 0.0;
                correction11 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon11[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction11)) correction11 = 0.0;
                correction12 = (  sumM011[ibin][itrack][icent] != 0.0 ) ?      sumAddon12[ibin][itrack][icent] /  sumM011[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction12)) correction12 = 0.0;
                correction13 = (   sumM01[ibin][itrack][icent] != 0.0 ) ?      sumAddon13[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction13)) correction13 = 0.0;
                correction14 = (   sumM01[ibin][itrack][icent] != 0.0 ) ?      sumAddon14[ibin][itrack][icent] /   sumM01[ibin][itrack][icent] : 0.0;
                if(!TMath::Finite(correction14)) correction14 = 0.0;
                // error on mean
                differential2Error1 = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],
                                               sumCorr2Reduced[ibin][itrack][icent],sumCorr2ReducedSquared[ibin][itrack][icent]);
                differential4Error1 = GetError(sumM0111[ibin][itrack][icent],sumM0111Squared[ibin][itrack][icent],
                                               sumCorr4Reduced[ibin][itrack][icent],sumCorr4ReducedSquared[ibin][itrack][icent]);
                if(differential2Error1 == 0. || differential4Error1 == 0.) continue;
                correction3Error = GetError(sumMp[ibin][itrack][icent],sumMpSquared[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumAddon3Squared[ibin][itrack][icent]);
                correction4Error = GetError(sumMp[ibin][itrack][icent],sumMpSquared[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumAddon4Squared[ibin][itrack][icent]);
                correction9Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumAddon9Squared[ibin][itrack][icent]);
                correction10Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumAddon10Squared[ibin][itrack][icent]);
                correction11Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumAddon11Squared[ibin][itrack][icent]);
                correction12Error = GetError(sumM011[ibin][itrack][icent],sumM011Squared[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumAddon12Squared[ibin][itrack][icent]);
                correction13Error = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],sumAddon13Squared[ibin][itrack][icent]);
                correction14Error = GetError(sumM01[ibin][itrack][icent],sumM01Squared[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],sumAddon14Squared[ibin][itrack][icent]);
                // Covariance terms
                covRef2Def2 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],
                                            sumM11M01[ibin][itrack][icent],sumCorr2Corr2Reduced[ibin][itrack][icent]);
                covRef2Def4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM11M0111[ibin][itrack][icent],sumCorr2Corr4Reduced[ibin][itrack][icent]);
                covRef4Def2 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],
                                            sumM1111M01[ibin][itrack][icent],sumCorr4Corr2Reduced[ibin][itrack][icent]);
                covRef4Def4 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM1111M0111[ibin][itrack][icent],sumCorr4Corr4Reduced[ibin][itrack][icent]);
                covDef2Def4 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],
                                            sumM01M0111[ibin][itrack][icent],sumCorr2ReducedCorr4Reduced[ibin][itrack][icent]);
                
                covRef2C3 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM11mp[ibin][itrack][icent],sumCorr2C3[ibin][itrack][icent]);
                covRef2C4 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM11mp[ibin][itrack][icent],sumCorr2C4[ibin][itrack][icent]);
                covRef2C9 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM11M011[ibin][itrack][icent],sumCorr2C9[ibin][itrack][icent]);
                covRef2C10 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C10[ibin][itrack][icent]);
                covRef2C11 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C11[ibin][itrack][icent]);
                covRef2C12 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM11M011[ibin][itrack][icent],sumCorr2C12[ibin][itrack][icent]);
                covRef2C13 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM11M01[ibin][itrack][icent],sumCorr2C13[ibin][itrack][icent]);
                covRef2C14 = GetCovariance(sumM11[itrack][icent],sumCorr2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM11M01[ibin][itrack][icent],sumCorr2C14[ibin][itrack][icent]);
                
                covRef4C3 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM1111mp[ibin][itrack][icent],sumCorr4C3[ibin][itrack][icent]);
                covRef4C4 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM1111mp[ibin][itrack][icent],sumCorr4C4[ibin][itrack][icent]);
                covRef4C9 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM1111M011[ibin][itrack][icent],sumCorr4C9[ibin][itrack][icent]);
                covRef4C10 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C10[ibin][itrack][icent]);
                covRef4C11 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C11[ibin][itrack][icent]);
                covRef4C12 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM1111M011[ibin][itrack][icent],sumCorr4C12[ibin][itrack][icent]);
                covRef4C13 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM1111M01[ibin][itrack][icent],sumCorr4C13[ibin][itrack][icent]);
                covRef4C14 = GetCovariance(sumM1111[itrack][icent],sumCorr4[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM1111M01[ibin][itrack][icent],sumCorr4C14[ibin][itrack][icent]);
                
                covDef2C1 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                          sumM01S11[ibin][itrack][icent],sumCorr2ReducedC1[ibin][itrack][icent]);
                covDef2C2 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                          sumM01S11[ibin][itrack][icent],sumCorr2ReducedC2[ibin][itrack][icent]);
                covDef2C3 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM01mp[ibin][itrack][icent],sumCorr2ReducedC3[ibin][itrack][icent]);
                covDef2C4 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM01mp[ibin][itrack][icent],sumCorr2ReducedC4[ibin][itrack][icent]);
                covDef2C5 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                          sumM11M01[ibin][itrack][icent],sumCorr2ReducedC5[ibin][itrack][icent]);
                covDef2C6 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                          sumM11M01[ibin][itrack][icent],sumCorr2ReducedC6[ibin][itrack][icent]);
                covDef2C7 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                          sumM111M01[ibin][itrack][icent],sumCorr2ReducedC7[ibin][itrack][icent]);
                covDef2C8 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                          sumM111M01[ibin][itrack][icent],sumCorr2ReducedC8[ibin][itrack][icent]);
                covDef2C9 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumCorr2ReducedC9[ibin][itrack][icent]);
                covDef2C10 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC10[ibin][itrack][icent]);
                covDef2C11 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC11[ibin][itrack][icent]);
                covDef2C12 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM01M011[ibin][itrack][icent],sumCorr2ReducedC12[ibin][itrack][icent]);
                covDef2C13 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM01Squared[ibin][itrack][icent],sumCorr2ReducedC13[ibin][itrack][icent]);
                covDef2C14 = GetCovariance(sumM01[ibin][itrack][icent],sumCorr2Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM01Squared[ibin][itrack][icent],sumCorr2ReducedC14[ibin][itrack][icent]);
                
                covDef4C1 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon1[itrack][icent],
                                          sumM0111S11[ibin][itrack][icent],sumCorr4ReducedC1[ibin][itrack][icent]);
                covDef4C2 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumS11[itrack][icent],sumAddon2[itrack][icent],
                                          sumM0111S11[ibin][itrack][icent],sumCorr4ReducedC2[ibin][itrack][icent]);
                covDef4C3 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                          sumM0111mp[ibin][itrack][icent],sumCorr4ReducedC3[ibin][itrack][icent]);
                covDef4C4 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                          sumM0111mp[ibin][itrack][icent],sumCorr4ReducedC4[ibin][itrack][icent]);
                covDef4C5 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                          sumM11M0111[ibin][itrack][icent],sumCorr4ReducedC5[ibin][itrack][icent]);
                covDef4C6 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                          sumM11M0111[ibin][itrack][icent],sumCorr4ReducedC6[ibin][itrack][icent]);
                covDef4C7 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                          sumM111M0111[ibin][itrack][icent],sumCorr4ReducedC7[ibin][itrack][icent]);
                covDef4C8 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                          sumM111M0111[ibin][itrack][icent],sumCorr4ReducedC8[ibin][itrack][icent]);
                covDef4C9 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                          sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC9[ibin][itrack][icent]);
                covDef4C10 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC10[ibin][itrack][icent]);
                covDef4C11 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC11[ibin][itrack][icent]);
                covDef4C12 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                           sumM011M0111[ibin][itrack][icent],sumCorr4ReducedC12[ibin][itrack][icent]);
                covDef4C13 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                           sumM01M0111[ibin][itrack][icent],sumCorr4ReducedC13[ibin][itrack][icent]);
                covDef4C14 = GetCovariance(sumM0111[ibin][itrack][icent],sumCorr4Reduced[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                           sumM01M0111[ibin][itrack][icent],sumCorr4ReducedC14[ibin][itrack][icent]);
                
                covC1C3 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC1C3[ibin][itrack][icent]);
                covC1C4 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC1C4[ibin][itrack][icent]);
                covC1C9 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011S11[ibin][itrack][icent],sumC1C9[ibin][itrack][icent]);
                covC1C10 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C10[ibin][itrack][icent]);
                covC1C11 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C11[ibin][itrack][icent]);
                covC1C12 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC1C12[ibin][itrack][icent]);
                covC1C13 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC1C13[ibin][itrack][icent]);
                covC1C14 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC1C14[ibin][itrack][icent]);
                
                covC2C3 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC2C3[ibin][itrack][icent]);
                covC2C4 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumS11mp[ibin][itrack][icent],sumC2C4[ibin][itrack][icent]);
                covC2C9 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011S11[ibin][itrack][icent],sumC2C9[ibin][itrack][icent]);
                covC2C10 = GetCovariance(sumS11[itrack][icent],sumAddon1[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C10[ibin][itrack][icent]);
                covC2C11 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C11[ibin][itrack][icent]);
                covC2C12 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011S11[ibin][itrack][icent],sumC2C12[ibin][itrack][icent]);
                covC2C13 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC2C13[ibin][itrack][icent]);
                covC2C14 = GetCovariance(sumS11[itrack][icent],sumAddon2[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01S11[ibin][itrack][icent],sumC2C14[ibin][itrack][icent]);
                
                covC3C4 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],
                                        sumMpSquared[ibin][itrack][icent],sumC3C4[ibin][itrack][icent]);
                covC3C5 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC3C5[ibin][itrack][icent]);
                covC3C6 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC3C6[ibin][itrack][icent]);
                covC3C7 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC3C7[ibin][itrack][icent]);
                covC3C8 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC3C8[ibin][itrack][icent]);
                covC3C9 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011mp[ibin][itrack][icent],sumC3C9[ibin][itrack][icent]);
                covC3C10 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C10[ibin][itrack][icent]);
                covC3C11 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C11[ibin][itrack][icent]);
                covC3C12 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC3C12[ibin][itrack][icent]);
                covC3C13 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC3C13[ibin][itrack][icent]);
                covC3C14 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon3[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC3C14[ibin][itrack][icent]);
                
                covC4C5 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM11[itrack][icent],sumAddon5[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC4C5[ibin][itrack][icent]);
                covC4C6 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM11[itrack][icent],sumAddon6[itrack][icent],
                                        sumM11mp[ibin][itrack][icent],sumC4C6[ibin][itrack][icent]);
                covC4C7 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM111[itrack][icent],sumAddon7[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC4C7[ibin][itrack][icent]);
                covC4C8 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM111[itrack][icent],sumAddon8[itrack][icent],
                                        sumM111mp[ibin][itrack][icent],sumC4C8[ibin][itrack][icent]);
                covC4C9 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM011mp[ibin][itrack][icent],sumC4C9[ibin][itrack][icent]);
                covC4C10 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C10[ibin][itrack][icent]);
                covC4C11 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C11[ibin][itrack][icent]);
                covC4C12 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011mp[ibin][itrack][icent],sumC4C12[ibin][itrack][icent]);
                covC4C13 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC4C13[ibin][itrack][icent]);
                covC4C14 = GetCovariance(sumMp[ibin][itrack][icent],sumAddon4[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01mp[ibin][itrack][icent],sumC4C14[ibin][itrack][icent]);
                
                covC5C9 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM11M011[ibin][itrack][icent],sumC5C9[ibin][itrack][icent]);
                covC5C10 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C10[ibin][itrack][icent]);
                covC5C11 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C11[ibin][itrack][icent]);
                covC5C12 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC5C12[ibin][itrack][icent]);
                covC5C13 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC5C13[ibin][itrack][icent]);
                covC5C14 = GetCovariance(sumM11[itrack][icent],sumAddon5[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC5C14[ibin][itrack][icent]);
                
                covC6C9 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM11M011[ibin][itrack][icent],sumC6C9[ibin][itrack][icent]);
                covC6C10 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C10[ibin][itrack][icent]);
                covC6C11 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C11[ibin][itrack][icent]);
                covC6C12 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM11M011[ibin][itrack][icent],sumC6C12[ibin][itrack][icent]);
                covC6C13 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC6C13[ibin][itrack][icent]);
                covC6C14 = GetCovariance(sumM11[itrack][icent],sumAddon6[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM11M01[ibin][itrack][icent],sumC6C14[ibin][itrack][icent]);
                
                covC7C9 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM111M011[ibin][itrack][icent],sumC7C9[ibin][itrack][icent]);
                covC7C10 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C10[ibin][itrack][icent]);
                covC7C11 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C11[ibin][itrack][icent]);
                covC7C12 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC7C12[ibin][itrack][icent]);
                covC7C13 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC7C13[ibin][itrack][icent]);
                covC7C14 = GetCovariance(sumM111[itrack][icent],sumAddon7[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC7C14[ibin][itrack][icent]);
                
                covC8C9 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],
                                        sumM111M011[ibin][itrack][icent],sumC8C9[ibin][itrack][icent]);
                covC8C10 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C10[ibin][itrack][icent]);
                covC8C11 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C11[ibin][itrack][icent]);
                covC8C12 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM111M011[ibin][itrack][icent],sumC8C12[ibin][itrack][icent]);
                covC8C13 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC8C13[ibin][itrack][icent]);
                covC8C14 = GetCovariance(sumM111[itrack][icent],sumAddon8[itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM111M01[ibin][itrack][icent],sumC8C14[ibin][itrack][icent]);
                
                covC9C10 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C10[ibin][itrack][icent]);
                covC9C11 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C11[ibin][itrack][icent]);
                covC9C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                         sumM011Squared[ibin][itrack][icent],sumC9C12[ibin][itrack][icent]);
                covC9C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                         sumM01M011[ibin][itrack][icent],sumC9C13[ibin][itrack][icent]);
                covC9C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon9[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                         sumM01M011[ibin][itrack][icent],sumC9C14[ibin][itrack][icent]);
                
                covC10C11 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC10C11[ibin][itrack][icent]);
                covC10C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC10C12[ibin][itrack][icent]);
                covC10C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC10C13[ibin][itrack][icent]);
                covC10C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon10[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC10C14[ibin][itrack][icent]);
                
                covC11C12 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],
                                          sumM011Squared[ibin][itrack][icent],sumC11C12[ibin][itrack][icent]);
                covC11C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC11C13[ibin][itrack][icent]);
                covC11C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon11[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC11C14[ibin][itrack][icent]);
                
                covC12C13 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC12C13[ibin][itrack][icent]);
                covC12C14 = GetCovariance(sumM011[ibin][itrack][icent],sumAddon12[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01M011[ibin][itrack][icent],sumC12C14[ibin][itrack][icent]);
                
                covC13C14 = GetCovariance(sumM01[ibin][itrack][icent],sumAddon13[ibin][itrack][icent],sumM01[ibin][itrack][icent],sumAddon14[ibin][itrack][icent],
                                          sumM01Squared[ibin][itrack][icent],sumC13C14[ibin][itrack][icent]);
                // Corrected Differential Flows
                differential2_2 = differential2_1 - correction3*correction1 - correction4*correction2;
                if(!TMath::Finite(differential2_2)) differential2_2 = 0.0;
                differential4_2 = differential4_1 - 2.0*differential2_1*reference2_1
                - correction3*correction7
                + correction4*correction8
                - correction1*correction9
                + correction2*correction10
                - 2.0*correction1*correction11
                - 2.0*correction2*correction12
                - correction13*correction5
                - correction14*correction6
                + 2.0*correction5*( correction3*correction1 - correction4*correction2 )
                + 2.0*correction6*( correction3*correction2 + correction4*correction1 )
                + 4.0*reference2_1*( correction3*correction1 + correction4*correction2 )
                + 2.0*correction13*( correction1*correction1 - correction2*correction2 )
                + 4.0*correction14*correction1*correction2
                + 4.0*differential2_1*( correction1*correction1 + correction2*correction2 )
                - 6.0*( correction1*correction1 - correction2*correction2 )*( correction3*correction1
                                                                             - correction4*correction2 )
                - 12.0*correction1*correction2*( correction4*correction1 + correction3*correction2 );
                if(!TMath::Finite(differential4_2)) differential4_2 = 0.0;
                // Final flows
                v1_2[ibin][itrack][icent] = ( reference2_3 > 0.0 ) ? sign2*differential2_2 / reference2_3 : 0.0;
                if(!TMath::Finite(v1_2[ibin][itrack][icent])) v1_2[ibin][itrack][icent] = 0.0;
                v1_4[ibin][itrack][icent] = ( reference4_3 > 0.0 ) ? sign4*differential4_2 / reference4_3 : 0.0;
                if(!TMath::Finite(v1_4[ibin][itrack][icent])) v1_4[ibin][itrack][icent] = 0.0;
                // differentiate QC2 differential flow
                df2dr2 = 1.0/(sign2*reference2_2)*(- (sign2*differential2_2)*(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0) ) );
                if(!TMath::Finite(df2dr2)) df2dr2 = 0.0;
                df2dd2 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0) );
                if(!TMath::Finite(df2dd2)) df2dd2 = 0.0;
                df2dc1 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction3) - (sign2*differential2_2)
                                                   *(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0)*(-2.0*correction1) ) );
                if(!TMath::Finite(df2dc1)) df2dc1 = 0.0;
                df2dc2 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction4) - (sign2*differential2_2)
                                                   *(sign2*1.0/2.0*TMath::Power(sign2*reference2_2,-1.0/2.0)*(-2.0*correction2) ) );
                if(!TMath::Finite(df2dc2)) df2dc2 = 0.0;
                df2dc3 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction1) );
                if(!TMath::Finite(df2dc3)) df2dc3 = 0.0;
                df2dc4 = 1.0/(sign2*reference2_2)*(sign2*TMath::Power(sign2*reference2_2,1.0/2.0)*(-correction2) );
                if(!TMath::Finite(df2dc4)) df2dc4 = 0.0;
                // error propagation
                v1_2Error[ibin][itrack][icent] = TMath::Sqrt( TMath::Power(df2dr2,2.0)*reference2Error1
                                                             + TMath::Power(df2dd2,2.0)*differential2Error1
                                                             + TMath::Power(df2dc1,2.0)*correction1Error
                                                             + TMath::Power(df2dc2,2.0)*correction2Error
                                                             + TMath::Power(df2dc3,2.0)*correction3Error
                                                             + TMath::Power(df2dc4,2.0)*correction4Error
                                                             
                                                             + 2.0*df2dr2*df2dd2*covRef2Def2
                                                             + 2.0*df2dr2*df2dc1*covRef2C1
                                                             + 2.0*df2dr2*df2dc2*covRef2C2
                                                             + 2.0*df2dr2*df2dc3*covRef2C3
                                                             + 2.0*df2dr2*df2dc4*covRef2C4
                                                             
                                                             + 2.0*df2dd2*df2dc1*covDef2C1
                                                             + 2.0*df2dd2*df2dc2*covDef2C2
                                                             + 2.0*df2dd2*df2dc3*covDef2C3
                                                             + 2.0*df2dd2*df2dc4*covDef2C4
                                                             
                                                             + 2.0*df2dc1*df2dc2*covC1C2
                                                             + 2.0*df2dc1*df2dc3*covC1C3
                                                             + 2.0*df2dc1*df2dc4*covC1C4
                                                             
                                                             + 2.0*df2dc2*df2dc3*covC2C3
                                                             + 2.0*df2dc2*df2dc4*covC2C4
                                                             
                                                             + 2.0*df2dc3*df2dc4*covC3C4
                                                             );
                if(!TMath::Finite(v1_2Error[ibin][itrack][icent]) || df2dr2*reference2Error1 == 0. || df2dd2*differential2Error1 == 0. || v1_2[ibin][itrack][icent] == 0.)
                    v1_2Error[ibin][itrack][icent] = 0.0;
                // differentiate QC4 differential flow
                df4dr2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*differential2_1
                                                                                                                     + 4.0*(correction3*correction1 + correction4*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*reference2_1
                                                                                                                                                      + 8.0*(correction1*correction1
                                                                                                                                                             + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dr2)) df4dr2 = 0.0;
                df4dd2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*reference2_1
                                                                                                                     + 4.0*(correction1*correction1 + correction2*correction2) ) );
                if(!TMath::Finite(df4dd2)) df4dd2 = 0.0;
                df4dr4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0) ) );
                if(!TMath::Finite(df4dr4)) df4dr4 = 0.0;
                df4dd4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( sign4*TMath::Power(sign4*reference4_2,3.0/4.0) );
                if(!TMath::Finite(df4dd4)) df4dd4 = 0.0;
                df4dc1 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction9 - 2.0*correction11
                                                                                                                     + 2.0*correction3*correction5
                                                                                                                     + 2.0*correction4*correction6 + 4.0*correction3*reference2_1
                                                                                                                     + 4.0*correction13*correction1 + 4.0*correction14*correction2
                                                                                                                     + 8.0*differential2_1*correction1
                                                                                                                     - 12.0*correction1*(correction3*correction1 - correction4*correction2)
                                                                                                                     - 6.0*correction3*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*(2.0*correction1*correction2*correction4
                                                                                                                             + correction3*correction2*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*correction7
                                                                                                                                                      + 8.0*correction1*correction5
                                                                                                                                                      + 8.0*correction6*correction2
                                                                                                                                                      + 16.0*reference2_1*correction1
                                                                                                                                                      - 24.0*correction1*
                                                                                                                                                      (correction1*correction1
                                                                                                                                                       + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc1)) df4dc1 = 0.0;
                df4dc2 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(correction10 - 2.0*correction12
                                                                                                                     - 2.0*correction4*correction5
                                                                                                                     + 2.0*correction3*correction6 + 4.0*correction4*reference2_1
                                                                                                                     - 4.0*correction13*correction2 + 4.0*correction14*correction1
                                                                                                                     + 8.0*differential2_1*correction2
                                                                                                                     + 12.0*correction2*(correction3*correction1 - correction4*correction2)
                                                                                                                     + 6.0*correction4*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*(2.0*correction2*correction1*correction3
                                                                                                                             + correction4*correction1*correction1) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(4.0*correction8
                                                                                                                                                      - 8.0*correction2*correction5
                                                                                                                                                      + 8.0*correction6*correction1
                                                                                                                                                      + 16.0*reference2_1*correction2
                                                                                                                                                      - 24.0*correction2*
                                                                                                                                                      (correction1*correction1
                                                                                                                                                       + correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc2)) df4dc2 = 0.0;
                df4dc3 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction7 + 2.0*correction5*correction1 + 2.0*correction6*correction2
                                                                                                                     + 4.0*correction1*reference2_1
                                                                                                                     - 6.0*correction1*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*correction1*correction2*correction2) );
                if(!TMath::Finite(df4dc3)) df4dc3 = 0.0;
                df4dc4 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(correction8 - 2.0*correction5*correction2 + 2.0*correction6*correction1
                                                                                                                     + 4.0*correction2*reference2_1
                                                                                                                     + 6.0*correction2*(correction1*correction1 - correction2*correction2)
                                                                                                                     - 12.0*correction1*correction1*correction2) );
                if(!TMath::Finite(df4dc4)) df4dc4 = 0.0;
                df4dc5 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction13 + 2.0*(correction3*correction1
                                                                                                                                          - correction4*correction2) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-2.0*correction5
                                                                                                                                                      + 4.0*(correction1*correction1
                                                                                                                                                             - correction2*correction2) ) ) );
                if(!TMath::Finite(df4dc5)) df4dc5 = 0.0;
                df4dc6 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction14 + 2.0*(correction3*correction2
                                                                                                                                          + correction4*correction1) )
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-2.0*correction6
                                                                                                                                                      +8.0*correction1*correction2 ) ) );
                if(!TMath::Finite(df4dc6)) df4dc6 = 0.0;
                df4dc7 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction3)
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*(-4.0*correction1) ) );
                if(!TMath::Finite(df4dc7)) df4dc7 = 0.0;
                df4dc8 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*correction4
                                                                    - sign4*differential4_2*(sign4*3.0/4.0*TMath::Power(sign4*reference4_2,-1.0/4.0)*4.0*correction2 ) );
                if(!TMath::Finite(df4dc8)) df4dc8 = 0.0;
                df4dc9 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction1) );
                if(!TMath::Finite(df4dc9)) df4dc9 = 0.0;
                df4dc10 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*correction2 );
                if(!TMath::Finite(df4dc10)) df4dc10 = 0.0;
                df4dc11 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*correction1) );
                if(!TMath::Finite(df4dc11)) df4dc11 = 0.0;
                df4dc12 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-2.0*correction2) );
                if(!TMath::Finite(df4dc12)) df4dc12 = 0.0;
                df4dc13 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction5 + 2.0*(correction1*correction1
                                                                                                                                          - correction2*correction2) ) );
                if(!TMath::Finite(df4dc13)) df4dc13 = 0.0;
                df4dc14 = TMath::Power(sign4*reference4_2,-3.0/2.0)*( TMath::Power(sign4*reference4_2,3.0/4.0)*sign4*(-correction6 + 4.0*correction1*correction2 ) );
                if(!TMath::Finite(df4dc14)) df4dc14 = 0.0;
                // error propagation
                v1_4Error[ibin][itrack][icent] = TMath::Sqrt( TMath::Power(df4dr2,2.0)*reference2Error1
                                                             + TMath::Power(df4dd2,2.0)*differential2Error1
                                                             + TMath::Power(df4dr4,2.0)*reference4Error1
                                                             + TMath::Power(df4dd4,2.0)*differential4Error1
                                                             + TMath::Power(df4dc1,2.0)*correction1Error
                                                             + TMath::Power(df4dc2,2.0)*correction2Error
                                                             + TMath::Power(df4dc3,2.0)*correction3Error
                                                             + TMath::Power(df4dc4,2.0)*correction4Error
                                                             + TMath::Power(df4dc5,2.0)*correction5Error
                                                             + TMath::Power(df4dc6,2.0)*correction6Error
                                                             + TMath::Power(df4dc7,2.0)*correction7Error
                                                             + TMath::Power(df4dc8,2.0)*correction8Error
                                                             + TMath::Power(df4dc9,2.0)*correction9Error
                                                             + TMath::Power(df4dc10,2.0)*correction10Error
                                                             + TMath::Power(df4dc11,2.0)*correction11Error
                                                             + TMath::Power(df4dc12,2.0)*correction12Error
                                                             + TMath::Power(df4dc13,2.0)*correction13Error
                                                             + TMath::Power(df4dc14,2.0)*correction14Error
                                                             
                                                             + 2.0*df4dr2*df4dd2*covRef2Def2
                                                             + 2.0*df4dr2*df4dr4*covRef2Ref4
                                                             + 2.0*df4dr2*df4dd4*covRef2Def4
                                                             + 2.0*df4dr2*df4dc1*covRef2C1
                                                             + 2.0*df4dr2*df4dc2*covRef2C2
                                                             + 2.0*df4dr2*df4dc3*covRef2C3
                                                             + 2.0*df4dr2*df4dc4*covRef2C4
                                                             + 2.0*df4dr2*df4dc5*covRef2C5
                                                             + 2.0*df4dr2*df4dc6*covRef2C6
                                                             + 2.0*df4dr2*df4dc7*covRef2C7
                                                             + 2.0*df4dr2*df4dc8*covRef2C8
                                                             + 2.0*df4dr2*df4dc9*covRef2C9
                                                             + 2.0*df4dr2*df4dc10*covRef2C10
                                                             + 2.0*df4dr2*df4dc11*covRef2C11
                                                             + 2.0*df4dr2*df4dc12*covRef2C12
                                                             + 2.0*df4dr2*df4dc13*covRef2C13
                                                             + 2.0*df4dr2*df4dc14*covRef2C14
                                                             
                                                             + 2.0*df4dd2*df4dr4*covRef4Def2
                                                             + 2.0*df4dd2*df4dd4*covDef2Def4
                                                             + 2.0*df4dd2*df4dc1*covDef2C1
                                                             + 2.0*df4dd2*df4dc2*covDef2C2
                                                             + 2.0*df4dd2*df4dc3*covDef2C3
                                                             + 2.0*df4dd2*df4dc4*covDef2C4
                                                             + 2.0*df4dd2*df4dc5*covDef2C5
                                                             + 2.0*df4dd2*df4dc6*covDef2C6
                                                             + 2.0*df4dd2*df4dc7*covDef2C7
                                                             + 2.0*df4dd2*df4dc8*covDef2C8
                                                             + 2.0*df4dd2*df4dc9*covDef2C9
                                                             + 2.0*df4dd2*df4dc10*covDef2C10
                                                             + 2.0*df4dd2*df4dc11*covDef2C11
                                                             + 2.0*df4dd2*df4dc12*covDef2C12
                                                             + 2.0*df4dd2*df4dc13*covDef2C13
                                                             + 2.0*df4dd2*df4dc14*covDef2C14
                                                             
                                                             + 2.0*df4dr4*df4dd4*covRef4Def4
                                                             + 2.0*df4dr4*df4dc1*covRef4C1
                                                             + 2.0*df4dr4*df4dc2*covRef4C2
                                                             + 2.0*df4dr4*df4dc3*covRef4C3
                                                             + 2.0*df4dr4*df4dc4*covRef4C4
                                                             + 2.0*df4dr4*df4dc5*covRef4C5
                                                             + 2.0*df4dr4*df4dc6*covRef4C6
                                                             + 2.0*df4dr4*df4dc7*covRef4C7
                                                             + 2.0*df4dr4*df4dc8*covRef4C8
                                                             + 2.0*df4dr4*df4dc9*covRef4C9
                                                             + 2.0*df4dr4*df4dc10*covRef4C10
                                                             + 2.0*df4dr4*df4dc11*covRef4C11
                                                             + 2.0*df4dr4*df4dc12*covRef4C12
                                                             + 2.0*df4dr4*df4dc13*covRef4C13
                                                             + 2.0*df4dr4*df4dc14*covRef4C14
                                                             
                                                             + 2.0*df4dd4*df4dc1*covDef4C1
                                                             + 2.0*df4dd4*df4dc2*covDef4C2
                                                             + 2.0*df4dd4*df4dc3*covDef4C3
                                                             + 2.0*df4dd4*df4dc4*covDef4C4
                                                             + 2.0*df4dd4*df4dc5*covDef4C5
                                                             + 2.0*df4dd4*df4dc6*covDef4C6
                                                             + 2.0*df4dd4*df4dc7*covDef4C7
                                                             + 2.0*df4dd4*df4dc8*covDef4C8
                                                             + 2.0*df4dd4*df4dc9*covDef4C9
                                                             + 2.0*df4dd4*df4dc10*covDef4C10
                                                             + 2.0*df4dd4*df4dc11*covDef4C11
                                                             + 2.0*df4dd4*df4dc12*covDef4C12
                                                             + 2.0*df4dd4*df4dc13*covDef4C13
                                                             + 2.0*df4dd4*df4dc14*covDef4C14
                                                             
                                                             + 2.0*df4dc1*df4dc2*covC1C2
                                                             + 2.0*df4dc1*df4dc3*covC1C3
                                                             + 2.0*df4dc1*df4dc4*covC1C4
                                                             + 2.0*df4dc1*df4dc5*covC1C5
                                                             + 2.0*df4dc1*df4dc6*covC1C6
                                                             + 2.0*df4dc1*df4dc7*covC1C7
                                                             + 2.0*df4dc1*df4dc8*covC1C8
                                                             + 2.0*df4dc1*df4dc9*covC1C9
                                                             + 2.0*df4dc1*df4dc10*covC1C10
                                                             + 2.0*df4dc1*df4dc11*covC1C11
                                                             + 2.0*df4dc1*df4dc12*covC1C12
                                                             + 2.0*df4dc1*df4dc13*covC1C13
                                                             + 2.0*df4dc1*df4dc14*covC1C14
                                                             
                                                             + 2.0*df4dc2*df4dc3*covC2C3
                                                             + 2.0*df4dc2*df4dc4*covC2C4
                                                             + 2.0*df4dc2*df4dc5*covC2C5
                                                             + 2.0*df4dc2*df4dc6*covC2C6
                                                             + 2.0*df4dc2*df4dc7*covC2C7
                                                             + 2.0*df4dc2*df4dc8*covC2C8
                                                             + 2.0*df4dc2*df4dc9*covC2C9
                                                             + 2.0*df4dc2*df4dc10*covC2C10
                                                             + 2.0*df4dc2*df4dc11*covC2C11
                                                             + 2.0*df4dc2*df4dc12*covC2C12
                                                             + 2.0*df4dc2*df4dc13*covC2C13
                                                             + 2.0*df4dc2*df4dc14*covC2C14
                                                             
                                                             + 2.0*df4dc3*df4dc4*covC3C4
                                                             + 2.0*df4dc3*df4dc5*covC3C5
                                                             + 2.0*df4dc3*df4dc6*covC3C6
                                                             + 2.0*df4dc3*df4dc7*covC3C7
                                                             + 2.0*df4dc3*df4dc8*covC3C8
                                                             + 2.0*df4dc3*df4dc9*covC3C9
                                                             + 2.0*df4dc3*df4dc10*covC3C10
                                                             + 2.0*df4dc3*df4dc11*covC3C11
                                                             + 2.0*df4dc3*df4dc12*covC3C12
                                                             + 2.0*df4dc3*df4dc13*covC3C13
                                                             + 2.0*df4dc3*df4dc14*covC3C14
                                                             
                                                             + 2.0*df4dc4*df4dc5*covC4C5
                                                             + 2.0*df4dc4*df4dc6*covC4C6
                                                             + 2.0*df4dc4*df4dc7*covC4C7
                                                             + 2.0*df4dc4*df4dc8*covC4C8
                                                             + 2.0*df4dc4*df4dc9*covC4C9
                                                             + 2.0*df4dc4*df4dc10*covC4C10
                                                             + 2.0*df4dc4*df4dc11*covC4C11
                                                             + 2.0*df4dc4*df4dc12*covC4C12
                                                             + 2.0*df4dc4*df4dc13*covC4C13
                                                             + 2.0*df4dc4*df4dc14*covC4C14
                                                             
                                                             + 2.0*df4dc5*df4dc6*covC5C6
                                                             + 2.0*df4dc5*df4dc7*covC5C7
                                                             + 2.0*df4dc5*df4dc8*covC5C8
                                                             + 2.0*df4dc5*df4dc9*covC5C9
                                                             + 2.0*df4dc5*df4dc10*covC5C10
                                                             + 2.0*df4dc5*df4dc11*covC5C11
                                                             + 2.0*df4dc5*df4dc12*covC5C12
                                                             + 2.0*df4dc5*df4dc13*covC5C13
                                                             + 2.0*df4dc5*df4dc14*covC5C14
                                                             
                                                             + 2.0*df4dc6*df4dc7*covC6C7
                                                             + 2.0*df4dc6*df4dc8*covC6C8
                                                             + 2.0*df4dc6*df4dc9*covC6C9
                                                             + 2.0*df4dc6*df4dc10*covC6C10
                                                             + 2.0*df4dc6*df4dc11*covC6C11
                                                             + 2.0*df4dc6*df4dc12*covC6C12
                                                             + 2.0*df4dc6*df4dc13*covC6C13
                                                             + 2.0*df4dc6*df4dc14*covC6C14
                                                             
                                                             + 2.0*df4dc7*df4dc8*covC7C8
                                                             + 2.0*df4dc7*df4dc9*covC7C9
                                                             + 2.0*df4dc7*df4dc10*covC7C10
                                                             + 2.0*df4dc7*df4dc11*covC7C11
                                                             + 2.0*df4dc7*df4dc12*covC7C12
                                                             + 2.0*df4dc7*df4dc13*covC7C13
                                                             + 2.0*df4dc7*df4dc14*covC7C14
                                                             
                                                             + 2.0*df4dc8*df4dc9*covC8C9
                                                             + 2.0*df4dc8*df4dc10*covC8C10
                                                             + 2.0*df4dc8*df4dc11*covC8C11
                                                             + 2.0*df4dc8*df4dc12*covC8C12
                                                             + 2.0*df4dc8*df4dc13*covC8C13
                                                             + 2.0*df4dc8*df4dc14*covC8C14
                                                             
                                                             + 2.0*df4dc9*df4dc10*covC9C10
                                                             + 2.0*df4dc9*df4dc11*covC9C11
                                                             + 2.0*df4dc9*df4dc12*covC9C12
                                                             + 2.0*df4dc9*df4dc13*covC9C13
                                                             + 2.0*df4dc9*df4dc14*covC9C14
                                                             
                                                             + 2.0*df4dc10*df4dc11*covC10C11
                                                             + 2.0*df4dc10*df4dc12*covC10C12
                                                             + 2.0*df4dc10*df4dc13*covC10C13
                                                             + 2.0*df4dc10*df4dc14*covC10C14
                                                             
                                                             + 2.0*df4dc11*df4dc12*covC11C12
                                                             + 2.0*df4dc11*df4dc13*covC11C13
                                                             + 2.0*df4dc11*df4dc14*covC11C14
                                                             
                                                             + 2.0*df4dc12*df4dc13*covC12C13
                                                             + 2.0*df4dc12*df4dc14*covC12C14
                                                             
                                                             + 2.0*df4dc13*df4dc14*covC13C14
                                                             );
                if(!TMath::Finite(v1_4Error[ibin][itrack][icent]) || df4dr2*reference2Error1 == 0. || df4dd2*differential2Error1 == 0.
                   || df4dr4*reference4Error1 == 0. || df4dd4*differential4Error1 == 0. || v1_4[ibin][itrack][icent] == 0.)
                    v1_4Error[ibin][itrack][icent] = 0.0;
                /*std::cout<<icent<<"  "<<itrack<<"  "<<ibin<<"  "<<reference2_1<<"  "<<sign2*reference2_2<<"  "<<reference2_3<<"  "
                 <<differential2_1<<"  "<<sign2*differential2_2<<"  "<<v1_2[ibin][itrack][icent]<<"  "<<v1_2Error[ibin][itrack][icent]<<std::endl
                 <<icent<<"  "<<itrack<<"  "<<ibin<<"  "<<reference4_1<<"  "<<sign4*reference4_2<<"  "<<reference4_3<<"  "
                 <<differential4_1<<"  "<<sign4*differential4_2<<"  "<<v1_4[ibin][itrack][icent]<<"  "<<v1_4Error[ibin][itrack][icent]<<std::endl
                 <<std::endl;*/
              }
          }
      }
    Double_t content2[ Nbins ], error2[ Nbins ], content4[ Nbins ], error4[ Nbins ];
    for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
      {
        content2[ibin] = 0.0; error2[ibin] = 0.0; content4[ibin] = 0.0; error4[ibin] = 0.0;
        //for ( Int_t icent = 0; icent < Ncentralities; icent++ )    // (0-80)%
        for ( Int_t icent = 2; icent < 5; icent++ )    // (10-25)%
          {
			for ( Int_t itrack = 0; itrack < N_track; itrack++ )
			  {
                content2[ibin] += ( v1_2[ibin][itrack][icent] != 0. && v1_2Error[ibin][itrack][icent] > 0.0 ) ?
                v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error2[ibin] += ( v1_2[ibin][itrack][icent] != 0. && v1_2Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                content4[ibin] += ( v1_4[ibin][itrack][icent] != 0. && v1_4Error[ibin][itrack][icent] > 0.0 ) ?
                v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error4[ibin] += ( v1_4[ibin][itrack][icent] != 0. && v1_4Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
			  }
          }
        content2[ibin] *= ( error2[ibin] > 0.0 ) ? 1.0 / error2[ibin] : 0.0;
        if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
        error2[ibin]  = ( error2[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error2[ibin] ) : 0.0;
        if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;
        content4[ibin] *= ( error4[ibin] > 0.0 ) ? 1.0 / error4[ibin] : 0.0;
        if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
        error4[ibin]  = ( error4[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error4[ibin] ) : 0.0;
        if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;
        histogram1D[15+3*Ncentralities]->SetBinContent(ibin+1,content2[ibin]); histogram1D[15+3*Ncentralities]->SetBinError(ibin+1,error2[ibin]);
        histogram1D[16+3*Ncentralities]->SetBinContent(ibin+1,content4[ibin]); histogram1D[16+3*Ncentralities]->SetBinError(ibin+1,error4[ibin]);
      }
	for ( Int_t icent = 0; icent < Ncentralities; icent++ )
      {
		for ( Int_t ibin = 0; ibin < Nbins; ibin++ )
		  {
			content2[ibin] = 0.0; error2[ibin] = 0.0; content4[ibin] = 0.0; error4[ibin] = 0.0;
			for ( Int_t itrack = 0; itrack < N_track; itrack++ )
			  {
                content2[ibin] += ( v1_2[ibin][itrack][icent] != 0. && v1_2Error[ibin][itrack][icent] > 0.0 ) ?
                v1_2[ibin][itrack][icent] / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error2[ibin] += ( v1_2[ibin][itrack][icent] != 0. && v1_2Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_2Error[ibin][itrack][icent], 2.0 ) : 0.0;
                content4[ibin] += ( v1_4[ibin][itrack][icent] != 0. && v1_4Error[ibin][itrack][icent] > 0.0 ) ?
                v1_4[ibin][itrack][icent] / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
                error4[ibin] += ( v1_4[ibin][itrack][icent] != 0. && v1_4Error[ibin][itrack][icent] > 0.0 ) ? 1.0 / TMath::Power( v1_4Error[ibin][itrack][icent], 2.0 ) : 0.0;
			  }
            content2[ibin] *= ( error2[ibin] > 0.0 ) ? 1.0 / error2[ibin] : 0.0;
            if(!TMath::Finite(content2[ibin])) content2[ibin] = 0.0;
            error2[ibin]  = ( error2[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error2[ibin] ) : 0.0;
            if(!TMath::Finite(error2[ibin])) error2[ibin] = 0.0;
            content4[ibin] *= ( error4[ibin] > 0.0 ) ? 1.0 / error4[ibin] : 0.0;
            if(!TMath::Finite(content4[ibin])) content4[ibin] = 0.0;
            error4[ibin]  = ( error4[ibin] > 0.0 ) ? TMath::Sqrt( 1.0 / error4[ibin] ) : 0.0;
            if(!TMath::Finite(error4[ibin])) error4[ibin] = 0.0;
			histogram1D[15+3*icent]->SetBinContent(ibin+1,content2[ibin]); histogram1D[15+3*icent]->SetBinError(ibin+1,error2[ibin]);
			histogram1D[16+3*icent]->SetBinContent(ibin+1,content4[ibin]); histogram1D[16+3*icent]->SetBinError(ibin+1,error4[ibin]);
		  }  
	  }
    // Save histograms and close output file
    outputFile->WriteObject(flowArray    , "flowArray"    );
    outputFile->WriteObject(flowArray2   , "flowArray2"   );
    outputFile->WriteObject(flowArrayCOV1, "flowArrayCOV1");
    outputFile->WriteObject(flowArrayCOV2, "flowArrayCOV2");
    outputFile->WriteObject(flowArrayCOV3, "flowArrayCOV3");
    outputFile->WriteObject(flowArrayCOV4, "flowArrayCOV4");
    outputFile->Write(); //outputFile->Close();
    return kStOK;
  }

Int_t FxtMaker::Make()
  {
    histogram1D[5]->Fill(1);    // Count # of events before any cuts
    StMuEvent* muEvent = NULL;
    muEvent = mMuDstMaker->muDst()->event();    // Get Event pointer
    Int_t verticesNumber = 0;
    verticesNumber = mMuDstMaker->muDst()->numberOfPrimaryVertices();    // Get the number of Primary Vertices associated with current event
    histogram1D[1]->Fill(verticesNumber);
    if( muEvent )    // Ensure event pointer is not NULL
      {
        if( muEvent->runId() >= 16140033 && muEvent->runId() <= 16140038
            //( muEvent->runId() >= 15046095 && muEvent->runId() <= 15049033 ) || ( muEvent->runId() >= 15049037 && muEvent->runId() <= 15070021 )
           )    // Event run number cut
          {
            histogram1D[5]->Fill(2);    // Count # of events after run number cut
            if( verticesNumber > 0
                //muEvent->refMult() > 5
               )    // Having at least one primary vertex cut
              {
                histogram1D[5]->Fill(3);    // Count # of events before any cuts
                Int_t maxTriggerIds = 0, flag = 0;
                maxTriggerIds = muEvent->triggerIdCollection().nominal().maxTriggerIds();
                for( Int_t iTrig = 0; iTrig < maxTriggerIds; iTrig++ )
                  {
                    if( muEvent->triggerIdCollection().nominal().triggerId(iTrig) == 1
                        //muEvent->triggerIdCollection().nominal().triggerId(iTrig) == 440005 || muEvent->triggerIdCollection().nominal().triggerId(iTrig) == 440015
                       ) flag++;
                  }
                if( flag > 0 )    // Trigger id cut
                  {
                    histogram1D[5]->Fill(4);    // Count # of events after trigger id cut
                    // Vertices loop starts
                    //for ( Int_t iv = 0; iv < verticesNumber; iv++ )
                      {
                        StMuPrimaryVertex* V = NULL;
                        //V = mMuDstMaker->muDst()->primaryVertex(iv);    // Get the ith Primary Vertex
                        V = mMuDstMaker->muDst()->primaryVertex(); StThreeVectorF r;
                        //mMuDstMaker->muDst()->setVertexIndex(iv);    // Set the ith Primary Vertex as current
						Int_t  centrality = Ncentralities;
                        Int_t tracknumber = N_track;
                        if( V )    // Ensure primary vertex pointer is not NULL
                          {
                            r = V->position();
                            histogram1D[0]->Fill(r.z()); histogram2D[0]->Fill(r.x(),r.y());
                            if( r.z() > 210.0 && r.z() < 212.0
                                //r.z() > -70.0 && r.z() < 70.0
                                //TMath::Abs(r.z() - 211.0) < cutTest
							   )    // Vz cut
                              {
                                histogram1D[5]->Fill(5);    // Count # of events after Vz cut
                                //std::cout<<mMuDstMaker->muDst()->currentVertexIndex()<<std::endl;
                                if( mMuDstMaker->muDst()->currentVertexIndex() == 0 )    // Require current primary vertex index == 0
                                  {
                                    histogram1D[5]->Fill(6);    // Count # of events after vertex index cut
                                    if( r.x() > -1.5 && r.x() < 1.0
                                        //TMath::Power(r.x(),2.0) + TMath::Power(r.y()+0.89,2.0) < 1.0
                                        //TMath::Abs(r.x() - -0.25) < cutTest
                                       )    // Vx cut
                                      {
                                        histogram1D[5]->Fill(7);    // Count # of events after Vx cut
                                        if( r.y() > -2.5 && r.y() < -1.0
                                            //TMath::Abs(r.y() - -1.75) < cutTest
                                           )    // Vy cut
                                          {
                                            histogram1D[5]->Fill(8);    // Count # of events after Vy cut
                                            // Reset Q vectors variables
                                            Double_t n = 1.,
                                            Q_n_1_r,  Q_n_1_i,    // track-wise variables
                                            Q_n_3_r,  Q_n_3_i,
                                            Q_2n_2_r, Q_2n_2_i,
                                            S11,
                                            S12,
                                            S13,
                                            S14,
                                            S21,
                                            S22,
                                            S31,
                                            S41,
                                            M11,
                                            M111,
                                            M1111,
                                            corr2,
                                            corr4,
                                            addon1,
                                            addon2,
                                            addon5,
                                            addon6,
                                            addon7,
                                            addon8,
                                            p_n_0_r[Nbins],  p_n_0_i[Nbins],
                                            q_n_2_r[Nbins],  q_n_2_i[Nbins],
                                            q_2n_1_r[Nbins], q_2n_1_i[Nbins],
                                            s11[Nbins],
                                            s12[Nbins],
                                            s13[Nbins],
                                            mp[Nbins],
                                            M01,
                                            M011,
                                            M0111,
                                            corr2Reduced,
                                            corr4Reduced,
                                            addon3,
                                            addon4,
                                            addon9,
                                            addon10,
                                            addon11,
                                            addon12,
                                            addon13,
                                            addon14;
                                            Q_n_1_r = 0.0;  Q_n_1_i = 0.0;    // track-wise variables
                                            Q_n_3_r = 0.0;  Q_n_3_i = 0.0;
                                            Q_2n_2_r = 0.0; Q_2n_2_i = 0.0;
                                            S11 = 0.0;
                                            S12 = 0.0;
                                            S13 = 0.0;
                                            S14 = 0.0;
                                            for(Int_t ibin=0;ibin<Nbins;ibin++){
                                                p_n_0_r[ibin] = 0.0;  p_n_0_i[ibin] = 0.0;
                                                q_n_2_r[ibin] = 0.0;  q_n_2_i[ibin] = 0.0;
                                                q_2n_1_r[ibin] = 0.0; q_2n_1_i[ibin] = 0.0;
                                                s11[ibin] = 0.0;
                                                s12[ibin] = 0.0;
                                                s13[ibin] = 0.0;
                                                mp[ibin] = 0.0;
                                            }
                                            Int_t tracksNumber = mMuDstMaker->muDst()->numberOfPrimaryTracks();    // Get the number of Primary Tracks
                                            Int_t Ntracks = 0, N_POI = 0, N_RFP = 0, N_Pion = 0, N_Proton = 0, N_Kaon = 0;
                                            // Primary Tracks loop starts
                                            for( Int_t itr = 0; itr < tracksNumber; itr++ )
                                              {
                                                StMuTrack* track = NULL;
                                                track = mMuDstMaker->muDst()->primaryTracks(itr);    // Get Track pointer
                                                histogram1D[9]->Fill(track->nHits());
                                                if( /*track && track->charge() != 0
                                                    &&*/ track->nHitsDedx() > 0
                                                    && (Double_t)track->nHitsFit(kTpcId)/track->nHitsPoss(kTpcId) >= 0.52
                                                    //&& TMath::Abs( track->eta() ) < 1.0
                                                    //&& track->pt() > 0.4 && track->pt() < 2.0
                                                    //&& track->dcaGlobal().mag() < 2.0
                                                    //&& track->nHits() > 15 //&& track->nHitsFit() > 15
                                                   )    // Track cuts
                                                  {
                                                    Ntracks++;
                                                  }    // Track cuts end
                                              }    // Primary tracks loop ends
                                            // Get centrality
                                            if( Ntracks >=   5 && Ntracks <  48 ) centrality =  0;
                                            if( Ntracks >=  48 && Ntracks <  61 ) centrality =  1;
                                            if( Ntracks >=  61 && Ntracks <  77 ) centrality =  2;
                                            if( Ntracks >=  77 && Ntracks <  97 ) centrality =  3;
                                            if( Ntracks >=  97 && Ntracks < 121 ) centrality =  4;
                                            if( Ntracks >= 121 && Ntracks < 153 ) centrality =  5;
                                            if( Ntracks >= 153 && Ntracks < 240 ) centrality =  6;
                                            // Get multiplicity
                                            if( Ntracks <= N_track ) tracknumber = Ntracks - 1; if(tracknumber < N_track) multCounter[tracknumber]++;
                                            //tracknumber = 0;
                                            // Ntracks selection
                                            if( tracknumber != N_track
												&& centrality != Ncentralities
                                               )
                                              {
                                                histogram1D[2]->Fill(muEvent->refMult());
                                                histogram1D[3]->Fill(Ntracks);
                                                // Loop through tracks again to fill histograms
                                                for( Int_t itr = 0; itr < tracksNumber; itr++ )
                                                  {
                                                    StMuTrack* track = NULL;
                                                    track = mMuDstMaker->muDst()->primaryTracks(itr);    // Get Track pointer
                                                    if( /*track && track->charge() != 0
                                                        &&*/ track->nHitsDedx() > 0
                                                        && (Double_t)track->nHitsFit(kTpcId)/track->nHitsPoss(kTpcId) >= 0.52
                                                        //&& TMath::Abs( track->eta() ) < 1.0
                                                        //&& track->eta() > -2.0 && track->eta() < -0.0
                                                        //&& track->pt() > 0.2 && track->pt() < 2.0
                                                        //&& track->dcaGlobal().mag() < 2.0
                                                        //&& track->nHits() > 15 //&& track->nHitsFit() > 15
                                                       )    // Track cuts
                                                      {
                                                        Double_t pt = track->pt(), eta = track->eta(), phi = track->phi();
                                                        histogram1D[7]->Fill(phi); histogram1D[6]->Fill(eta); histogram1D[8]->Fill(pt);
                                                        histogram2D[1]->Fill(track->charge()*track->p().mag(),track->dEdx()*1.0e6);
                                                        Double_t   Beta = track->btofPidTraits().beta(),
                                                                 trackP = track->p().mag(),
                                                                  mass2 = 0.0;
                                                        if( Beta != -999.0 /*&& TMath::Abs(Beta) < 1.0*/ )
                                                          {
                                                            mass2 = trackP*trackP * ( ( 1.0 / ( Beta*Beta ) ) - 1.0 );
                                                            histogram2D[2]->Fill(track->charge()*track->p().mag(),1.0/Beta);
                                                            histogram2D[3]->Fill(track->charge()*track->p().mag(),mass2);
                                                          }
                                                        // Pion contamination test
                                                        if( Beta == -999.0
                                                            && track->charge() > 0
                                                            && pt > 0.4 && pt < 2.0
                                                            //&& track->p().mag() < 1.6
                                                           )
                                                          {
                                                            for(Int_t i=0;i<30;i++)
                                                              {
                                                                if(track->p().mag() > 0.0+0.1*i && track->p().mag() < 0.1+0.1*i)
                                                                  {
                                                                    histogram1D[17+3*Ncentralities+i]->Fill(track->nSigmaProton());
                                                                    histogram1D[17+3*Ncentralities+i+30]->Fill(track->nSigmaPion());
																	histogram1D[17+3*Ncentralities+i+60]->Fill(track->nSigmaKaon());
                                                                    histogram1D[17+3*Ncentralities+i+90]->Fill(track->nSigmaElectron());
                                                                  }
                                                              }
                                                            if( TMath::Abs( track->nSigmaProton() ) < 2.0 ) histogram1D[17 + 3*Ncentralities + 120]->Fill(1);
                                                            if( TMath::Abs( track->nSigmaPion() ) < 2.0 ) histogram1D[17 + 3*Ncentralities + 120]->Fill(2);
                                                            if( TMath::Abs( track->nSigmaKaon() ) < 2.0 ) histogram1D[17 + 3*Ncentralities + 120]->Fill(3);
                                                            if( TMath::Abs( track->nSigmaElectron() ) < 2.0 ) histogram1D[17 + 3*Ncentralities + 120]->Fill(4);
                                                          }
                                                        // RFP rapidity (Proton)
                                                        /*Double_t rap_Proton = 0.5*std::log( ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                          + TMath::Power( Mass_Proton, 2.0 ) )
                                                                                             + pt*TMath::SinH( eta ) ) /
                                                                                           ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                         + TMath::Power( Mass_Proton, 2.0 ) )
                                                                                            - pt*TMath::SinH( eta ) ) );
                                                        // POI rapidity (Pion)
                                                        Double_t rap_Pion = 0.5*std::log( ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                        + TMath::Power( Mass_Pion, 2.0 ) )
                                                                                           + pt*TMath::SinH( eta ) ) /
                                                                                         ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                       + TMath::Power( Mass_Pion, 2.0 ) )
                                                                                          - pt*TMath::SinH( eta ) ) );
                                                        // Kaon rapidity
                                                        Double_t rap_Kaon = 0.5*std::log( ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                        + TMath::Power( Mass_Kaon, 2.0 ) )
                                                                                           + pt*TMath::SinH( eta ) ) /
                                                                                         ( TMath::Sqrt( TMath::Power( pt*TMath::CosH( eta ), 2.0 )
                                                                                                       + TMath::Power( Mass_Kaon, 2.0 ) )
                                                                                          - pt*TMath::SinH( eta ) ) );*/
                                                        Double_t energy_proton = TMath::Sqrt(track->p().mag2()+Mass_Proton*Mass_Proton);
                                                        Double_t energy_pion = TMath::Sqrt(track->p().mag2()+Mass_Pion*Mass_Pion);
                                                        Double_t energy_kaon = TMath::Sqrt(track->p().mag2()+Mass_Kaon*Mass_Kaon);
                                                        Double_t rap_Proton = 0.5*TMath::Log((energy_proton+track->p().z())/(energy_proton-track->p().z()));
                                                        Double_t rap_Pion = 0.5*TMath::Log((energy_pion+track->p().z())/(energy_pion-track->p().z()));
                                                        Double_t rap_Kaon = 0.5*TMath::Log((energy_kaon+track->p().z())/(energy_kaon-track->p().z()));
                                                        //if(Beta == -999.0)
                                                          {
                                                            if( TMath::Abs( track->nSigmaElectron() ) < 1.0 //&& TMath::Abs( track->btofPidTraits().sigmaElectron() ) < 1.0
                                                                //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                                //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                                //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                                && ( /*( Beta == -999.0 && TMath::Abs( track->nSigmaPion() ) > 2.0
                                                                                      && TMath::Abs( track->nSigmaKaon() ) > 2.0 && TMath::Abs( track->nSigmaProton() ) > 2.0
                                                                      )
                                                                     ||*/ ( Beta != -999.0 && TMath::Abs(mass2) < 0.005 )
                                                                    )
                                                                //&& Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12
                                                                //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0
                                                                //&& track->charge() > 0
                                                                //&& pt > 0.4 && pt < 2.0
                                                               )    // POI selection (Electrons)
                                                              {
                                                                histogram2D[9]->Fill(track->charge()*track->p().mag(),track->dEdx()*1.0e6);
                                                              }
                                                            if( TMath::Abs( track->nSigmaPion() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) < 1.0
                                                               //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                               //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                               //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                               && ( ( Beta == -999.0 //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                                     )
                                                                   || ( Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12 && ( ( track->p().mag() < 0.62 && TMath::Abs(mass2) > 0.005 )
                                                                                                                           || track->p().mag() > 0.62 ) )
                                                                   )
                                                               //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                               //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                               //&& track->charge() < 0
                                                               && pt > 0.2 //&& pt <= 1.6
                                                               && track->p().mag() < 1.6
                                                               )    // POI selection (Pions)
                                                              {
                                                                //if(track->charge() < 0)
                                                                  {
                                                                    N_Pion++;
                                                                    histogram1D[17 + 3*Ncentralities + 121]->Fill(track->dca(0).mag());
                                                                    histogram1D[11]->Fill(eta);
                                                                    histogram1D[12]->Fill(phi);
                                                                    histogram1D[13]->Fill(pt);
                                                                    histogram1D[14]->Fill(rap_Pion);
                                                                  }
                                                                histogram2D[7]->Fill(track->charge()*track->p().mag(),track->dEdx()*1.0e6);
                                                                if( Beta != -999.0 /*&& Beta < 1.0*/ )
                                                                  {
                                                                    histogram2D[5]->Fill(track->charge()*track->p().mag(),1.0/Beta);
                                                                    histogram2D[6]->Fill(track->charge()*track->p().mag(),mass2);
                                                                  }
                                                              }
															if( TMath::Abs( track->nSigmaKaon() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) < 1.0
                                                                //&& TMath::Abs( track->nSigmaElectron() ) > 1.0
                                                                //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                                //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                                && ( /*( Beta == -999.0 && TMath::Abs( track->nSigmaPion() ) > 1.0 && TMath::Abs( track->nSigmaProton() ) > 1.0
                                                                      )
																     ||*/ ( Beta != -999.0 && mass2 > 0.15 && mass2 < 0.34 )
                                                                    )
                                                                //&& Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12
                                                                //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                                //&& track->charge() > 0
                                                               && pt > 0.2 //&& pt <= 1.6
                                                               && track->p().mag() < 1.6
                                                               )    // POI selection (Kaons)
                                                              {
                                                                //if(track->charge() > 0)
                                                                  {
                                                                    N_Kaon++;
                                                                    histogram1D[17 + 3*Ncentralities + 130]->Fill(eta);
                                                                    histogram1D[17 + 3*Ncentralities + 131]->Fill(phi);
                                                                    histogram1D[17 + 3*Ncentralities + 132]->Fill(pt);
                                                                    histogram1D[17 + 3*Ncentralities + 133]->Fill(rap_Kaon);
                                                                  }
                                                                histogram2D[8]->Fill(track->charge()*track->p().mag(),track->dEdx()*1.0e6);
                                                                if( Beta != -999.0 /*&& Beta < 1.0*/ )
                                                                  {
                                                                    histogram2D[12]->Fill(track->charge()*track->p().mag(),1.0/Beta);
                                                                    histogram2D[13]->Fill(track->charge()*track->p().mag(),mass2);
                                                                  }
                                                              }
                                                            if( TMath::Abs( track->nSigmaProton() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaProton() ) < 1.0
                                                                //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                                //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                                //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                               && ( ( Beta == -999.0 //&& TMath::Abs( track->nSigmaPion() ) > 1.0
                                                                     )
                                                                     || ( Beta != -999.0 && mass2 > 0.6 && mass2 < 1.1 )
                                                                   )
                                                                //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                                //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0
                                                               //&& track->charge() > 0
                                                                && pt > 0.4 && pt < 2.0
                                                                //&& track->p().mag() < 2.8
                                                               )    // POI selection (Protons)
                                                              {
                                                                if(track->charge() > 0)
                                                                  {
                                                                    N_Proton++;
                                                                    histogram1D[17 + 3*Ncentralities + 125]->Fill(eta);
                                                                    histogram1D[17 + 3*Ncentralities + 126]->Fill(phi);
                                                                    histogram1D[17 + 3*Ncentralities + 127]->Fill(pt);
                                                                    histogram1D[17 + 3*Ncentralities + 128]->Fill(rap_Proton);
                                                                  }
                                                                histogram2D[4]->Fill(track->charge()*track->p().mag(),track->dEdx()*1.0e6);
                                                                if( Beta != -999.0 /*&& Beta < 1.0*/ )
                                                                  {
                                                                    histogram2D[10]->Fill(track->charge()*track->p().mag(),1.0/Beta);
                                                                    histogram2D[11]->Fill(track->charge()*track->p().mag(),mass2);
                                                                  }
                                                              }
                                                          }
														Double_t w = 1.0;    // Define weight
                                                        //w = (phi_weight[Hist_Phi->FindBin(phi)-1] > 0.0)? phi_total/phi_weight[Hist_Phi->FindBin(phi)-1]:0.0;
                                                        //histogram1D[17 + 3*Ncentralities + 122]->Fill(phi,w);
														// Compute RFP Q vectors
														//if( eta > 0.1 )
                                                        /*if( TMath::Abs( track->nSigmaProton() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaProton() ) < 1.0
                                                           //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                           && ( ( Beta == -999.0 //&& TMath::Abs( track->nSigmaKaon() ) > 1.0
                                                                 )
                                                               || ( Beta != -999.0 && mass2 > 0.6 && mass2 < 1.1 )
                                                               )
                                                           //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                           //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0
                                                           && track->charge() > 0
                                                           && pt > 0.4 && pt < 2.0
                                                           //&& track->p().mag() < 2.8
                                                           //&& rap_Proton >= -0.6
                                                           )*/    // RFP selection (Protons)
														  {
                                                            N_RFP++;
                                                            w = 1.0;
                                                            //w = pt;
                                                            //w *= rap_Proton - midrapidity;
															 Q_n_1_r +=     w * TMath::Cos(     n*phi );  Q_n_1_i +=     w * TMath::Sin(     n*phi );
															 Q_n_3_r += w*w*w * TMath::Cos(     n*phi );  Q_n_3_i += w*w*w * TMath::Sin(     n*phi );
															Q_2n_2_r +=   w*w * TMath::Cos( 2.0*n*phi ); Q_2n_2_i +=   w*w * TMath::Sin( 2.0*n*phi );
															S11 += w;
															S12 += w*w;
															S13 += w*w*w;
															S14 += w*w*w*w;
														  }
                                                        // Compute POI p vectors
                                                        /*if( TMath::Abs( track->nSigmaPion() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) < 1.0
                                                           //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                           && ( ( Beta == -999.0 //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                                 )
                                                               || ( Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12 && ( ( track->p().mag() < 0.62 && TMath::Abs(mass2) > 0.005 )
                                                                                                                       || track->p().mag() > 0.62 ) )
                                                               )
                                                           //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                           //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                           && track->charge() < 0
                                                           && pt > 0.2 //&& pt <= 1.6
                                                           && track->p().mag() < 1.6
                                                           //&& rap_Pion <= -0.7
                                                           )*/    // POI selection (Pions)
														/*if( TMath::Abs(track->nSigmaPion()) < 1.0
															&& TMath::Abs(track->btofPidTraits().sigmaPion()) < 1.0 
															&& TMath::Abs(track->btofPidTraits().sigmaKaon()) > 1.0 
															&& TMath::Abs(track->btofPidTraits().sigmaProton()) > 1.0 
															&& TMath::Abs(track->nSigmaElectron()) > 1.0
															&& track->charge() < 0
															&& pt > 0.2 //&& pt < 1.6
															&& track->p().mag() < 1.6
                                                            && rap_Pion < -0.7
														   )*/    // POI selection (Pion), Lukasz's cuts
                                                        /*if( TMath::Abs( track->nSigmaKaon() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) < 1.0
                                                           //&& TMath::Abs( track->nSigmaElectron() ) > 1.0
                                                           //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                           && ( ( Beta == -999.0 && TMath::Abs( track->nSigmaPion() ) > 1.0 && TMath::Abs( track->nSigmaProton() ) > 1.0
                                                                 )
                                                                 || ( Beta != -999.0 && mass2 > 0.15 && mass2 < 0.34 )
                                                               )
                                                           //&& Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12
                                                           //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                           && track->charge() > 0
                                                           && pt > 0.2 //&& pt < 1.6
                                                           && track->p().mag() < 1.6
                                                           //&& rap_Kaon > -1.52
                                                           )*/    // POI selection (Kaons)
                                                        //Double_t cutTest = 1.2;
                                                        if( TMath::Abs( track->nSigmaProton() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaProton() ) < 1.0
                                                            //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                            //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                            //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                            && ( ( Beta == -999.0
                                                                  )
                                                                 || ( Beta != -999.0 && mass2 > 0.6 && mass2 < 1.1 ) )
                                                            //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                            //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0
                                                            && track->charge() > 0
                                                            && pt > 0.4 && pt < 2.0
                                                            && eta > -2.0 && eta < cutTest
                                                            //&& track->p().mag() > 0.2
                                                           )    // POI selection (Protons)
                                                          {
                                                            Int_t bin = (Int_t)std::floor( ( rap_Proton - Low )*(Double_t)Nbins / ( High - Low ) );
                                                            //Int_t bin = (Int_t)std::floor( (  pt - Low )*(Double_t)Nbins / ( High - Low ) );
															//Int_t bin = (Int_t)std::floor( ( eta - Low )*(Double_t)Nbins / ( High - Low ) );
                                                            if( bin < 0 || bin >= Nbins ) continue; N_POI++;
                                                            hist_pt_eta->Fill(eta,pt);
															p_n_0_r[bin] += TMath::Cos( n*phi ); p_n_0_i[bin] += TMath::Sin( n*phi );
															     mp[bin]++;
                                                          }
                                                        // Compute tracks both labeled as POI & RFP q vectors
                                                        /*if( TMath::Abs( track->nSigmaPion() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) < 1.0
                                                           //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                           && ( ( Beta == -999.0 //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                                 )
                                                               || ( Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12 && ( ( track->p().mag() < 0.62 && TMath::Abs(mass2) > 0.005 )
                                                                                                                       || track->p().mag() > 0.62 ) )
                                                               )
                                                           //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                           //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                           && track->charge() > 0
                                                           && pt > 0.2 && pt < 0.0    // To void RFP & POI selection
                                                           && track->p().mag() < 1.6
                                                           //&& rap_Pion > -1.52
                                                           )*/    // both as RFP & POI selection (Pions)
                                                        /*if( TMath::Abs( track->nSigmaKaon() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) < 1.0
                                                           //&& TMath::Abs( track->nSigmaElectron() ) > 1.0
                                                           //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                           //&& TMath::Abs( track->nSigmaProton() ) > 2.0
                                                           && ( ( Beta == -999.0 && TMath::Abs( track->nSigmaPion() ) > 1.0 && TMath::Abs( track->nSigmaProton() ) > 1.0
                                                                 )
                                                                 || ( Beta != -999.0 && mass2 > 0.15 && mass2 < 0.34 )
                                                               )
                                                           //&& Beta != -999.0 && mass2 > -0.1 && mass2 < 0.12
                                                           //&& TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaProton() ) > 1.0
                                                           && track->charge() > 0
                                                           && pt > 0.2 && pt < 0.0    // To void RFP & POI selection
                                                           && track->p().mag() < 1.6
                                                           //&& rap_Kaon > -1.52
                                                            //&& pt > 0.4 && pt < 2.0
                                                           )*/    // both as RFP & POI selection (Kaons)
                                                        if( TMath::Abs( track->nSigmaProton() ) < 2.0 //&& TMath::Abs( track->btofPidTraits().sigmaProton() ) < 1.0
                                                            //&& TMath::Abs( track->nSigmaElectron() ) > 2.0
                                                            //&& TMath::Abs( track->nSigmaKaon() ) > 2.0
                                                            //&& TMath::Abs( track->nSigmaPion() ) > 2.0
                                                            && ( ( Beta == -999.0
                                                                  )
                                                                 || ( Beta != -999.0 && mass2 > 0.6 && mass2 < 1.1 ) )
                                                            //&& Beta != -999.0 && TMath::Abs(Beta) < 1.0 && mass2 > 0.005 && mass2 < 0.12
                                                            //&& TMath::Abs( track->btofPidTraits().sigmaKaon() ) > 1.0 && TMath::Abs( track->btofPidTraits().sigmaPion() ) > 1.0
                                                            && track->charge() > 0
                                                            && pt > 0.4 && pt < 2.0    // To void RFP & POI selection
                                                            && eta > -2.0 && eta < cutTest
                                                            //&& track->p().mag() < 2.8
                                                           )    // both as RFP & POI selection (Protons)
                                                          {
                                                            Int_t bin = (Int_t)std::floor( ( rap_Proton - Low )*(Double_t)Nbins / ( High - Low ) );
                                                            //Int_t bin = (Int_t)std::floor( (  pt - Low )*(Double_t)Nbins / ( High - Low ) );
															//Int_t bin = (Int_t)std::floor( ( eta - Low )*(Double_t)Nbins / ( High - Low ) );
															if( bin < 0 || bin >= Nbins ) continue; //N_POI++;
                                                            w = 1.0;
                                                            //w = pt;
                                                            //w *= rap_Proton - midrapidity;
															 q_n_2_r[bin] += w*w * TMath::Cos(     n*phi );  q_n_2_i[bin] += w*w * TMath::Sin(     n*phi );
															q_2n_1_r[bin] +=   w * TMath::Cos( 2.0*n*phi ); q_2n_1_i[bin] +=   w * TMath::Sin( 2.0*n*phi );
															     s11[bin] += w;
															     s12[bin] += w*w;
															     s13[bin] += w*w*w;
                                                          }
                                                      }
                                                  }    // Histogram loop ends
                                                histogram1D[10]->Fill(N_Pion);
                                                histogram1D[17 + 3*Ncentralities + 124]->Fill(N_Proton);
                                                histogram1D[17 + 3*Ncentralities + 129]->Fill(N_Kaon);
                                                histogram1D[17 + 3*Ncentralities + 134]->Fill(N_POI);
                                                histogram1D[17 + 3*Ncentralities + 135]->Fill(N_RFP);
                                                // Compute Reference Flows and corrections
                                                TComplex Q_n_1, Q_n_3, Q_2n_2, p_n_0, q_n_2, q_2n_1;
                                                Q_n_1 = TComplex( 0.0, 0.0 );
                                                Q_n_3 = TComplex( 0.0, 0.0 );
                                                Q_2n_2 = TComplex( 0.0, 0.0 );
                                                S21 = 0.0;
                                                S22 = 0.0;
                                                S31 = 0.0;
                                                S41 = 0.0;
                                                M11 = 0.0;
                                                M111 = 0.0;
                                                M1111 = 0.0;
                                                corr2 = 0.0;
                                                corr4 = 0.0;
                                                addon1 = 0.0;
                                                addon2 = 0.0;
                                                addon5 = 0.0;
                                                addon6 = 0.0;
                                                addon7 = 0.0;
                                                addon8 = 0.0;
                                                Q_n_1 = TComplex(  Q_n_1_r,  Q_n_1_i );
                                                Q_n_3 = TComplex(  Q_n_3_r,  Q_n_3_i );
                                                Q_2n_2 = TComplex( Q_2n_2_r, Q_2n_2_i );
                                                S21 = S11*S11;
                                                S22 = S12*S12;
                                                S31 = S11*S11*S11;
                                                S41 = S11*S11*S11*S11;
                                                M11 = S21 - S12;
                                                M111 = S31 - 3.0*S12*S11 + 2.0*S13;
                                                M1111 = S41 - 6.0*S12*S21 + 8.0*S13*S11 + 3.0*S22 - 6.0*S14;
                                                corr2 = TMath::Power(TComplex::Abs( Q_n_1 ),2.) - S12;
                                                corr4 = TMath::Power(TComplex::Abs( Q_n_1 ),4.) + TMath::Power(TComplex::Abs( Q_2n_2 ),2.)
                                                - 2.0*( Q_2n_2*TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 ) ).Re()
                                                + 8.0*( Q_n_3*TComplex::Conjugate( Q_n_1 ) ).Re() - 4.0*S12*TMath::Power(TComplex::Abs( Q_n_1 ),2.)
                                                - 6.0*S14 + 2.0*S22;
                                                addon1 = Q_n_1.Re();
                                                addon2 = Q_n_1.Im();
                                                addon5 = ( Q_n_1*Q_n_1 - Q_2n_2 ).Re();
                                                addon6 = ( Q_n_1*Q_n_1 - Q_2n_2 ).Im();
                                                addon7 = ( Q_n_1*TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 ) - Q_n_1*TComplex::Conjugate( Q_2n_2 )
                                                          - 2.0*S12*TComplex::Conjugate( Q_n_1 ) + 2.0*TComplex::Conjugate( Q_n_3 ) ).Re();
                                                addon8 = ( Q_n_1*TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 ) - Q_n_1*TComplex::Conjugate( Q_2n_2 )
                                                          - 2.0*S12*TComplex::Conjugate( Q_n_1 ) + 2.0*TComplex::Conjugate( Q_n_3 ) ).Im();
                                                // Collect variables for averaging Reference Flows over all events
                                                sumS11[tracknumber][centrality] +=    S11;
                                                sumM11[tracknumber][centrality] +=    M11;
                                                sumM111[tracknumber][centrality] +=   M111;
                                                sumM1111[tracknumber][centrality] +=  M1111;
                                                sumCorr2[tracknumber][centrality] +=  corr2;
                                                sumCorr4[tracknumber][centrality] +=  corr4;
                                                // Collect variables for statistical errors
                                                sumS11Squared[tracknumber][centrality] +=    S11*S11;
                                                sumM11Squared[tracknumber][centrality] +=    M11*M11;
                                                sumM111Squared[tracknumber][centrality] +=   M111*M111;
                                                sumM1111Squared[tracknumber][centrality] +=  M1111*M1111;
                                                if(M11 != 0.) sumCorr2Squared[tracknumber][centrality] +=  corr2*corr2 /   M11;
                                                if(M1111 != 0.) sumCorr4Squared[tracknumber][centrality] +=  corr4*corr4 / M1111;
                                                // Covariances
                                                sumM11M1111[tracknumber][centrality] +=   M11 * M1111;
                                                sumM11S11[tracknumber][centrality] +=   M11 *   S11;
                                                sumM11M111[tracknumber][centrality] +=   M11 *  M111;
                                                sumM1111S11[tracknumber][centrality] += M1111 *   S11;
                                                sumM111M1111[tracknumber][centrality] +=  M111 * M1111;
                                                sumM111S11[tracknumber][centrality] +=  M111 *   S11;
                                                sumCorr2Corr4[tracknumber][centrality] += corr2 * corr4;
                                                // detector inefficiency correction
                                                sumAddon1[tracknumber][centrality] += addon1;
                                                sumAddon2[tracknumber][centrality] += addon2;
                                                sumAddon5[tracknumber][centrality] += addon5;
                                                sumAddon6[tracknumber][centrality] += addon6;
                                                sumAddon7[tracknumber][centrality] += addon7;
                                                sumAddon8[tracknumber][centrality] += addon8;
                                                if(S11 != 0.) sumAddon1Squared[tracknumber][centrality] += addon1*addon1 /  S11;
                                                if(S11 != 0.) sumAddon2Squared[tracknumber][centrality] += addon2*addon2 /  S11;
                                                if(M11 != 0.) sumAddon5Squared[tracknumber][centrality] += addon5*addon5 /  M11;
                                                if(M11 != 0.) sumAddon6Squared[tracknumber][centrality] += addon6*addon6 /  M11;
                                                if(M111 != 0.) sumAddon7Squared[tracknumber][centrality] += addon7*addon7 / M111;
                                                if(M111 != 0.) sumAddon8Squared[tracknumber][centrality] += addon8*addon8 / M111;
                                                sumCorr2C1[tracknumber][centrality] += corr2 * addon1;
                                                sumCorr2C2[tracknumber][centrality] += corr2 * addon2;
                                                sumCorr2C5[tracknumber][centrality] += corr2 * addon5;
                                                sumCorr2C6[tracknumber][centrality] += corr2 * addon6;
                                                sumCorr2C7[tracknumber][centrality] += corr2 * addon7;
                                                sumCorr2C8[tracknumber][centrality] += corr2 * addon8;
                                                sumCorr4C1[tracknumber][centrality] += corr4 * addon1;
                                                sumCorr4C2[tracknumber][centrality] += corr4 * addon2;
                                                sumCorr4C5[tracknumber][centrality] += corr4 * addon5;
                                                sumCorr4C6[tracknumber][centrality] += corr4 * addon6;
                                                sumCorr4C7[tracknumber][centrality] += corr4 * addon7;
                                                sumCorr4C8[tracknumber][centrality] += corr4 * addon8;
                                                sumC1C2[tracknumber][centrality] += addon1 * addon2;
                                                sumC1C5[tracknumber][centrality] += addon1 * addon5;
                                                sumC1C6[tracknumber][centrality] += addon1 * addon6;
                                                sumC1C7[tracknumber][centrality] += addon1 * addon7;
                                                sumC1C8[tracknumber][centrality] += addon1 * addon8;
                                                sumC2C5[tracknumber][centrality] += addon2 * addon5;
                                                sumC2C6[tracknumber][centrality] += addon2 * addon6;
                                                sumC2C7[tracknumber][centrality] += addon2 * addon7;
                                                sumC2C8[tracknumber][centrality] += addon2 * addon8;
                                                sumC5C6[tracknumber][centrality] += addon5 * addon6;
                                                sumC5C7[tracknumber][centrality] += addon5 * addon7;
                                                sumC5C8[tracknumber][centrality] += addon5 * addon8;
                                                sumC6C7[tracknumber][centrality] += addon6 * addon7;
                                                sumC6C8[tracknumber][centrality] += addon6 * addon8;
                                                sumC7C8[tracknumber][centrality] += addon7 * addon8;
                                                // Compute Differential Flows and corrections
                                                // Loop through y/pT bins
                                                for(Int_t ibin = 0;ibin<Nbins;ibin++ ){
                                                    p_n_0 = TComplex( 0.0, 0.0 );
                                                    q_n_2 = TComplex( 0.0, 0.0 );
                                                    q_2n_1 = TComplex( 0.0, 0.0 );
                                                    M01 = 0.0;
                                                    M011 = 0.0;
                                                    M0111 = 0.0;
                                                    corr2Reduced = 0.0;
                                                    corr4Reduced = 0.0;
                                                    addon3 = 0.0;
                                                    addon4 = 0.0;
                                                    addon9 = 0.0;
                                                    addon10 = 0.0;
                                                    addon11 = 0.0;
                                                    addon12 = 0.0;
                                                    addon13 = 0.0;
                                                    addon14 = 0.0;
                                                    p_n_0 = TComplex(  p_n_0_r[ibin],  p_n_0_i[ibin] );
                                                    q_n_2 = TComplex(  q_n_2_r[ibin],  q_n_2_i[ibin] );
                                                    q_2n_1 = TComplex( q_2n_1_r[ibin], q_2n_1_i[ibin] );
                                                    M01 = mp[ibin]*S11 - s11[ibin];
                                                    M011 = mp[ibin]*( S21 - S12 ) - 2.0*( s11[ibin]*S11 - s12[ibin] );
                                                    M0111 = mp[ibin]*( S31 - 3.0*S11*S12 + 2.0*S13 ) - 3.0*( s11[ibin]*( S21 - S12 )
                                                                                                            + 2.0*( s13[ibin] - s12[ibin]*S11 ) );
                                                    corr2Reduced = ( p_n_0*TComplex::Conjugate( Q_n_1 ) - s11[ibin] ).Re();
                                                    corr4Reduced = ( p_n_0*Q_n_1*TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 )
                                                                    - q_2n_1*TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 )
                                                                    - p_n_0*Q_n_1*TComplex::Conjugate( Q_2n_2 )
                                                                    - 2.0*S12*p_n_0*TComplex::Conjugate( Q_n_1 )
                                                                    - 2.0*s11[ibin]*TMath::Power(TComplex::Abs( Q_n_1 ),2.)
                                                                    + 7.0*q_n_2*TComplex::Conjugate( Q_n_1 )
                                                                    - Q_n_1*TComplex::Conjugate( q_n_2 )
                                                                    + q_2n_1*TComplex::Conjugate( Q_2n_2 )
                                                                    + 2.0*p_n_0*TComplex::Conjugate( Q_n_3 )
                                                                    + 2.0*s11[ibin]*S12 - 6.0*s13[ibin] ).Re();
                                                    addon3 = p_n_0.Re();
                                                    addon4 = p_n_0.Im();
                                                    addon9 = ( p_n_0*( TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 )
                                                                      - TComplex::Conjugate( Q_2n_2 ) )
                                                              - 2.0*( s11[ibin]*TComplex::Conjugate( Q_n_1 )
                                                                     - TComplex::Conjugate( q_n_2 ) ) ).Re();
                                                    addon10 = ( p_n_0*( TComplex::Conjugate( Q_n_1 )*TComplex::Conjugate( Q_n_1 )
                                                                       - TComplex::Conjugate( Q_2n_2 ) )
                                                               - 2.0*( s11[ibin]*TComplex::Conjugate( Q_n_1 )
                                                                      - TComplex::Conjugate( q_n_2 ) ) ).Im();
                                                    addon11 = ( p_n_0*( TMath::Power(TComplex::Abs( Q_n_1 ),2.) - S12 )
                                                               - ( q_2n_1*TComplex::Conjugate( Q_n_1 )
                                                                  + s11[ibin]*Q_n_1 - 2.0*q_n_2 ) ).Re();
                                                    addon12 = ( p_n_0*( TMath::Power(TComplex::Abs( Q_n_1 ),2.) - S12 )
                                                               - ( q_2n_1*TComplex::Conjugate( Q_n_1 )
                                                                  + s11[ibin]*Q_n_1 - 2.0*q_n_2 ) ).Im();
                                                    addon13 = ( p_n_0*Q_n_1 - q_2n_1 ).Re();
                                                    addon14 = ( p_n_0*Q_n_1 - q_2n_1 ).Im();
                                                    // Collect variables for averaging Differential Flows over all events
                                                    sumMp[ibin][tracknumber][centrality] +=    mp[ibin];
                                                    sumM01[ibin][tracknumber][centrality] +=   M01;
                                                    sumM011[ibin][tracknumber][centrality] +=  M011;
                                                    sumM0111[ibin][tracknumber][centrality] += M0111;
                                                    sumCorr2Reduced[ibin][tracknumber][centrality] += corr2Reduced ;
                                                    sumCorr4Reduced[ibin][tracknumber][centrality] += corr4Reduced ;
                                                    // Collect variables for statistical errors
                                                    sumMpSquared[ibin][tracknumber][centrality] +=    mp[ibin]*mp[ibin];
                                                    sumM01Squared[ibin][tracknumber][centrality] +=   M01*M01;
                                                    sumM011Squared[ibin][tracknumber][centrality] +=  M011*M011;
                                                    sumM0111Squared[ibin][tracknumber][centrality] += M0111*M0111;
                                                    if(M01 != 0.) sumCorr2ReducedSquared[ibin][tracknumber][centrality] += corr2Reduced*corr2Reduced /   M01;
                                                    if(M0111 != 0.) sumCorr4ReducedSquared[ibin][tracknumber][centrality] += corr4Reduced*corr4Reduced / M0111;
                                                    // Covariances
                                                    sumM11M01[ibin][tracknumber][centrality] +=   M11 * M01;
                                                    sumM11M0111[ibin][tracknumber][centrality] +=   M11 * M0111;
                                                    sumM1111M01[ibin][tracknumber][centrality] += M1111 * M01;
                                                    sumM1111M0111[ibin][tracknumber][centrality] += M1111 * M0111;
                                                    sumM01M0111[ibin][tracknumber][centrality] +=   M01 * M0111;
                                                    sumM11mp[ibin][tracknumber][centrality] +=   M11 * mp[ibin];
                                                    sumM11M011[ibin][tracknumber][centrality] +=   M11 * M011;
                                                    sumM01S11[ibin][tracknumber][centrality] +=   S11 * M01;
                                                    sumM01mp[ibin][tracknumber][centrality] +=   M01 * mp[ibin];
                                                    sumM111M01[ibin][tracknumber][centrality] +=  M111 * M01;
                                                    sumM01M011[ibin][tracknumber][centrality] +=   M01 * M011;
                                                    sumM1111mp[ibin][tracknumber][centrality] += M1111 * mp[ibin];
                                                    sumM1111M011[ibin][tracknumber][centrality] += M1111 * M011;
                                                    sumM0111S11[ibin][tracknumber][centrality] +=   S11 * M0111;
                                                    sumM0111mp[ibin][tracknumber][centrality] += M0111 * mp[ibin];
                                                    sumM111M0111[ibin][tracknumber][centrality] +=  M111 * M0111;
                                                    sumM011M0111[ibin][tracknumber][centrality] +=  M011 * M0111;
                                                    sumS11mp[ibin][tracknumber][centrality] +=   S11 * mp[ibin];
                                                    sumM011S11[ibin][tracknumber][centrality] +=   S11 * M011;
                                                    sumM111mp[ibin][tracknumber][centrality] +=  M111 * mp[ibin];
                                                    sumM011mp[ibin][tracknumber][centrality] +=  M011 * mp[ibin];
                                                    sumM111M011[ibin][tracknumber][centrality] +=  M111 * M011;
                                                    sumCorr2Corr2Reduced[ibin][tracknumber][centrality] += corr2 * corr2Reduced;
                                                    sumCorr2Corr4Reduced[ibin][tracknumber][centrality] += corr2 * corr4Reduced;
                                                    sumCorr4Corr2Reduced[ibin][tracknumber][centrality] += corr4 * corr2Reduced;
                                                    sumCorr4Corr4Reduced[ibin][tracknumber][centrality] += corr4 * corr4Reduced;
                                                    sumCorr2ReducedCorr4Reduced[ibin][tracknumber][centrality] += corr2Reduced * corr4Reduced;
                                                    // detector inefficiency correction
                                                    sumAddon3[ibin][tracknumber][centrality] +=  addon3;
                                                    sumAddon4[ibin][tracknumber][centrality] +=  addon4;
                                                    sumAddon9[ibin][tracknumber][centrality] +=  addon9;
                                                    sumAddon10[ibin][tracknumber][centrality] += addon10;
                                                    sumAddon11[ibin][tracknumber][centrality] += addon11;
                                                    sumAddon12[ibin][tracknumber][centrality] += addon12;
                                                    sumAddon13[ibin][tracknumber][centrality] += addon13;
                                                    sumAddon14[ibin][tracknumber][centrality] += addon14;
                                                    if(mp[ibin] != 0.) sumAddon3Squared[ibin][tracknumber][centrality] +=  addon3*addon3  /   mp[ibin];
                                                    if(mp[ibin] != 0.) sumAddon4Squared[ibin][tracknumber][centrality] +=  addon4*addon4  /   mp[ibin];
                                                    if(M011 != 0.) sumAddon9Squared[ibin][tracknumber][centrality] +=  addon9*addon9  / M011;
                                                    if(M011 != 0.) sumAddon10Squared[ibin][tracknumber][centrality] += addon10*addon10 / M011;
                                                    if(M011 != 0.) sumAddon11Squared[ibin][tracknumber][centrality] += addon11*addon11 / M011;
                                                    if(M011 != 0.) sumAddon12Squared[ibin][tracknumber][centrality] += addon12*addon12 / M011;
                                                    if(M01 != 0.) sumAddon13Squared[ibin][tracknumber][centrality] += addon13*addon13 /  M01;
                                                    if(M01 != 0.) sumAddon14Squared[ibin][tracknumber][centrality] += addon14*addon14 /  M01;
                                                    sumCorr2C3[ibin][tracknumber][centrality] += corr2 * addon3;
                                                    sumCorr2C4[ibin][tracknumber][centrality] += corr2 * addon4;
                                                    sumCorr2C9[ibin][tracknumber][centrality] += corr2 * addon9;
                                                    sumCorr2C10[ibin][tracknumber][centrality] += corr2 * addon10;
                                                    sumCorr2C11[ibin][tracknumber][centrality] += corr2 * addon11;
                                                    sumCorr2C12[ibin][tracknumber][centrality] += corr2 * addon12;
                                                    sumCorr2C13[ibin][tracknumber][centrality] += corr2 * addon13;
                                                    sumCorr2C14[ibin][tracknumber][centrality] += corr2 * addon14;
                                                    sumCorr2ReducedC1[ibin][tracknumber][centrality] += corr2Reduced * addon1;
                                                    sumCorr2ReducedC2[ibin][tracknumber][centrality] += corr2Reduced * addon2;
                                                    sumCorr2ReducedC3[ibin][tracknumber][centrality] += corr2Reduced * addon3;
                                                    sumCorr2ReducedC4[ibin][tracknumber][centrality] += corr2Reduced * addon4;
                                                    sumCorr2ReducedC5[ibin][tracknumber][centrality] += corr2Reduced * addon5;
                                                    sumCorr2ReducedC6[ibin][tracknumber][centrality] += corr2Reduced * addon6;
                                                    sumCorr2ReducedC7[ibin][tracknumber][centrality] += corr2Reduced * addon7;
                                                    sumCorr2ReducedC8[ibin][tracknumber][centrality] += corr2Reduced * addon8;
                                                    sumCorr2ReducedC9[ibin][tracknumber][centrality] += corr2Reduced * addon9;
                                                    sumCorr2ReducedC10[ibin][tracknumber][centrality] += corr2Reduced * addon10;
                                                    sumCorr2ReducedC11[ibin][tracknumber][centrality] += corr2Reduced * addon11;
                                                    sumCorr2ReducedC12[ibin][tracknumber][centrality] += corr2Reduced * addon12;
                                                    sumCorr2ReducedC13[ibin][tracknumber][centrality] += corr2Reduced * addon13;
                                                    sumCorr2ReducedC14[ibin][tracknumber][centrality] += corr2Reduced * addon14;
                                                    sumCorr4C3[ibin][tracknumber][centrality] += corr4 * addon3;
                                                    sumCorr4C4[ibin][tracknumber][centrality] += corr4 * addon4;
                                                    sumCorr4C9[ibin][tracknumber][centrality] += corr4 * addon9;
                                                    sumCorr4C10[ibin][tracknumber][centrality] += corr4 * addon10;
                                                    sumCorr4C11[ibin][tracknumber][centrality] += corr4 * addon11;
                                                    sumCorr4C12[ibin][tracknumber][centrality] += corr4 * addon12;
                                                    sumCorr4C13[ibin][tracknumber][centrality] += corr4 * addon13;
                                                    sumCorr4C14[ibin][tracknumber][centrality] += corr4 * addon14;
                                                    sumCorr4ReducedC1[ibin][tracknumber][centrality] += corr4Reduced * addon1;
                                                    sumCorr4ReducedC2[ibin][tracknumber][centrality] += corr4Reduced * addon2;
                                                    sumCorr4ReducedC3[ibin][tracknumber][centrality] += corr4Reduced * addon3;
                                                    sumCorr4ReducedC4[ibin][tracknumber][centrality] += corr4Reduced * addon4;
                                                    sumCorr4ReducedC5[ibin][tracknumber][centrality] += corr4Reduced * addon5;
                                                    sumCorr4ReducedC6[ibin][tracknumber][centrality] += corr4Reduced * addon6;
                                                    sumCorr4ReducedC7[ibin][tracknumber][centrality] += corr4Reduced * addon7;
                                                    sumCorr4ReducedC8[ibin][tracknumber][centrality] += corr4Reduced * addon8;
                                                    sumCorr4ReducedC9[ibin][tracknumber][centrality] += corr4Reduced * addon9;
                                                    sumCorr4ReducedC10[ibin][tracknumber][centrality] += corr4Reduced * addon10;
                                                    sumCorr4ReducedC11[ibin][tracknumber][centrality] += corr4Reduced * addon11;
                                                    sumCorr4ReducedC12[ibin][tracknumber][centrality] += corr4Reduced * addon12;
                                                    sumCorr4ReducedC13[ibin][tracknumber][centrality] += corr4Reduced * addon13;
                                                    sumCorr4ReducedC14[ibin][tracknumber][centrality] += corr4Reduced * addon14;
                                                    sumC1C3[ibin][tracknumber][centrality] += addon1 * addon3;
                                                    sumC1C4[ibin][tracknumber][centrality] += addon1 * addon4;
                                                    sumC1C9[ibin][tracknumber][centrality] += addon1 * addon9;
                                                    sumC1C10[ibin][tracknumber][centrality] += addon1 * addon10;
                                                    sumC1C11[ibin][tracknumber][centrality] += addon1 * addon11;
                                                    sumC1C12[ibin][tracknumber][centrality] += addon1 * addon12;
                                                    sumC1C13[ibin][tracknumber][centrality] += addon1 * addon13;
                                                    sumC1C14[ibin][tracknumber][centrality] += addon1 * addon14;
                                                    sumC2C3[ibin][tracknumber][centrality] += addon2 * addon3;
                                                    sumC2C4[ibin][tracknumber][centrality] += addon2 * addon4;
                                                    sumC2C9[ibin][tracknumber][centrality] += addon2 * addon9;
                                                    sumC2C10[ibin][tracknumber][centrality] += addon2 * addon10;
                                                    sumC2C11[ibin][tracknumber][centrality] += addon2 * addon11;
                                                    sumC2C12[ibin][tracknumber][centrality] += addon2 * addon12;
                                                    sumC2C13[ibin][tracknumber][centrality] += addon2 * addon13;
                                                    sumC2C14[ibin][tracknumber][centrality] += addon2 * addon14;
                                                    sumC3C4[ibin][tracknumber][centrality] += addon3 * addon4;
                                                    sumC3C5[ibin][tracknumber][centrality] += addon3 * addon5;
                                                    sumC3C6[ibin][tracknumber][centrality] += addon3 * addon6;
                                                    sumC3C7[ibin][tracknumber][centrality] += addon3 * addon7;
                                                    sumC3C8[ibin][tracknumber][centrality] += addon3 * addon8;
                                                    sumC3C9[ibin][tracknumber][centrality] += addon3 * addon9;
                                                    sumC3C10[ibin][tracknumber][centrality] += addon3 * addon10;
                                                    sumC3C11[ibin][tracknumber][centrality] += addon3 * addon11;
                                                    sumC3C12[ibin][tracknumber][centrality] += addon3 * addon12;
                                                    sumC3C13[ibin][tracknumber][centrality] += addon3 * addon13;
                                                    sumC3C14[ibin][tracknumber][centrality] += addon3 * addon14;
                                                    sumC4C5[ibin][tracknumber][centrality] += addon4 * addon5;
                                                    sumC4C6[ibin][tracknumber][centrality] += addon4 * addon6;
                                                    sumC4C7[ibin][tracknumber][centrality] += addon4 * addon7;
                                                    sumC4C8[ibin][tracknumber][centrality] += addon4 * addon8;
                                                    sumC4C9[ibin][tracknumber][centrality] += addon4 * addon9;
                                                    sumC4C10[ibin][tracknumber][centrality] += addon4 * addon10;
                                                    sumC4C11[ibin][tracknumber][centrality] += addon4 * addon11;
                                                    sumC4C12[ibin][tracknumber][centrality] += addon4 * addon12;
                                                    sumC4C13[ibin][tracknumber][centrality] += addon4 * addon13;
                                                    sumC4C14[ibin][tracknumber][centrality] += addon4 * addon14;
                                                    sumC5C9[ibin][tracknumber][centrality] += addon5 * addon9;
                                                    sumC5C10[ibin][tracknumber][centrality] += addon5 * addon10;
                                                    sumC5C11[ibin][tracknumber][centrality] += addon5 * addon11;
                                                    sumC5C12[ibin][tracknumber][centrality] += addon5 * addon12;
                                                    sumC5C13[ibin][tracknumber][centrality] += addon5 * addon13;
                                                    sumC5C14[ibin][tracknumber][centrality] += addon5 * addon14;
                                                    sumC6C9[ibin][tracknumber][centrality] += addon6 * addon9;
                                                    sumC6C10[ibin][tracknumber][centrality] += addon6 * addon10;
                                                    sumC6C11[ibin][tracknumber][centrality] += addon6 * addon11;
                                                    sumC6C12[ibin][tracknumber][centrality] += addon6 * addon12;
                                                    sumC6C13[ibin][tracknumber][centrality] += addon6 * addon13;
                                                    sumC6C14[ibin][tracknumber][centrality] += addon6 * addon14;
                                                    sumC7C9[ibin][tracknumber][centrality] += addon7 * addon9;
                                                    sumC7C10[ibin][tracknumber][centrality] += addon7 * addon10;
                                                    sumC7C11[ibin][tracknumber][centrality] += addon7 * addon11;
                                                    sumC7C12[ibin][tracknumber][centrality] += addon7 * addon12;
                                                    sumC7C13[ibin][tracknumber][centrality] += addon7 * addon13;
                                                    sumC7C14[ibin][tracknumber][centrality] += addon7 * addon14;
                                                    sumC8C9[ibin][tracknumber][centrality] += addon8 * addon9;
                                                    sumC8C10[ibin][tracknumber][centrality] += addon8 * addon10;
                                                    sumC8C11[ibin][tracknumber][centrality] += addon8 * addon11;
                                                    sumC8C12[ibin][tracknumber][centrality] += addon8 * addon12;
                                                    sumC8C13[ibin][tracknumber][centrality] += addon8 * addon13;
                                                    sumC8C14[ibin][tracknumber][centrality] += addon8 * addon14;
                                                    sumC9C10[ibin][tracknumber][centrality] += addon9 * addon10;
                                                    sumC9C11[ibin][tracknumber][centrality] += addon9 * addon11;
                                                    sumC9C12[ibin][tracknumber][centrality] += addon9 * addon12;
                                                    sumC9C13[ibin][tracknumber][centrality] += addon9 * addon13;
                                                    sumC9C14[ibin][tracknumber][centrality] += addon9 * addon14;
                                                    sumC10C11[ibin][tracknumber][centrality] += addon10 * addon11;
                                                    sumC10C12[ibin][tracknumber][centrality] += addon10 * addon12;
                                                    sumC10C13[ibin][tracknumber][centrality] += addon10 * addon13;
                                                    sumC10C14[ibin][tracknumber][centrality] += addon10 * addon14;
                                                    sumC11C12[ibin][tracknumber][centrality] += addon11 * addon12;
                                                    sumC11C13[ibin][tracknumber][centrality] += addon11 * addon13;
                                                    sumC11C14[ibin][tracknumber][centrality] += addon11 * addon14;
                                                    sumC12C13[ibin][tracknumber][centrality] += addon12 * addon13;
                                                    sumC12C14[ibin][tracknumber][centrality] += addon12 * addon14;
                                                    sumC13C14[ibin][tracknumber][centrality] += addon13 * addon14;
                                                }    // y/pT bins loop ends
                                              }    // Event Ntracks selection ends
                                          }    // Vy cut ends
                                      }    // Vx cut ends
                                  }    // Primary vertex index cut ends
                              }    // Vz cut ends
                          }    // Primary vertex pointer not NULL cut ends
                      }    // Vertices loop ends
                  }    // Trigger id cut ends
              }    // At least one primary vertex cut ends
          }    // Event run number cut ends
      }    // Event pointer not NULL cut ends
    return kStOK;
  }

Double_t FxtMaker::GetCovariance(Double_t w1,Double_t w1v1,Double_t w2,Double_t w2v2,Double_t w1w2,Double_t w1w2v1v2){
    Double_t cov = ((w1w2v1v2/w1w2) - (w1v1/w1)*(w2v2/w2))/(w1*w2/w1w2 - 1.);
    if(!TMath::Finite(cov)) cov = 0.0;
    return cov;
}

Double_t FxtMaker::GetError(Double_t w1,Double_t w1square,Double_t w1v1,Double_t w1v1square){
    Double_t err = TMath::Abs(((w1v1square/w1) - (w1v1/w1)*(w1v1/w1))/(w1*w1/w1square - 1.));
    if(!TMath::Finite(err)) err = 0.0;
    return err;
}