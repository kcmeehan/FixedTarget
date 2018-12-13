//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Dec 25 18:51:48 2013 by ROOT version 5.22/00
// from TTree V0PicoDst/V0PicoDst from StV0Maker
// found on file: ../output.k0s/324502266C711EE7CD7F6FF5070C116A_2920.ks.picodst.root
//////////////////////////////////////////////////////////

#ifndef v0dst_h
#define v0dst_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class v0dst {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           evtnumber;
   Int_t           trgmode;
   Int_t           nrefmult;
   Int_t           nrefmultftpceast;
   Int_t           bbcadcsumeast;
   Float_t         zdcadc0;
   Double_t        bbccirate;
   Double_t        zdccirate;
   Int_t           ntofmatched;
   Float_t         primvertexX;
   Float_t         primvertexY;
   Float_t         primvertexZ;
   Float_t         magn;
   Int_t           nv0;
   Float_t         v0mass[30000];   //[nv0]
   Float_t         v0pt[30000];   //[nv0]
   Float_t         v0rapidity[30000];   //[nv0]
   Float_t         v0eta[30000];   //[nv0]
   Float_t         v0x[30000];   //[nv0]
   Float_t         v0y[30000];   //[nv0]
   Float_t         v0z[30000];   //[nv0]
   Float_t         v0px[30000];   //[nv0]
   Float_t         v0py[30000];   //[nv0]
   Float_t         v0pz[30000];   //[nv0]
   Float_t         v0declen[30000];   //[nv0]
   Float_t         v0dca[30000];   //[nv0]
   Float_t         v0dca2d[30000];   //[nv0]
   Float_t         v0pathlen[30000];   //[nv0]
   Int_t           dau1id[30000];   //[nv0]
   Float_t         dau1dca[30000];   //[nv0]
   Float_t         dau1dca2d[30000];   //[nv0]
   Int_t           dau1nhits[30000];   //[nv0]
   Int_t           dau1nhitsdedx[30000];   //[nv0]
   Int_t           dau1nhitsposs[30000];   //[nv0]
   Float_t         dau1dedx[30000];   //[nv0]
   Float_t         dau1nsigma[30000];   //[nv0]
   Float_t         dau1eta[30000];   //[nv0]
   Float_t         dau1pt[30000];   //[nv0]
   Float_t         dau1px[30000];   //[nv0]
   Float_t         dau1py[30000];   //[nv0]
   Float_t         dau1pz[30000];   //[nv0]
   Int_t           dau1tpc[30000];   //[nv0]
   Int_t           dau1ssd[30000];   //[nv0]
   Int_t           dau1svt[30000];   //[nv0]
   Int_t           dau1tofflag[30000];   //[nv0]
   Float_t         dau1tof[30000];   //[nv0]
   Float_t         dau1pathlen[30000];   //[nv0]
   Float_t         dau1firstx[30000];   //[nv0]
   Float_t         dau1firsty[30000];   //[nv0]
   Float_t         dau1firstz[30000];   //[nv0]
   Float_t         dau1lastx[30000];   //[nv0]
   Float_t         dau1lasty[30000];   //[nv0]
   Float_t         dau1lastz[30000];   //[nv0]
   Int_t           dau2id[30000];   //[nv0]
   Float_t         dau2dca[30000];   //[nv0]
   Float_t         dau2dca2d[30000];   //[nv0]
   Int_t           dau2nhits[30000];   //[nv0]
   Int_t           dau2nhitsdedx[30000];   //[nv0]
   Int_t           dau2nhitsposs[30000];   //[nv0]
   Float_t         dau2dedx[30000];   //[nv0]
   Float_t         dau2nsigma[30000];   //[nv0]
   Float_t         dau2eta[30000];   //[nv0]
   Float_t         dau2pt[30000];   //[nv0]
   Float_t         dau2px[30000];   //[nv0]
   Float_t         dau2py[30000];   //[nv0]
   Float_t         dau2pz[30000];   //[nv0]
   Int_t           dau2tpc[30000];   //[nv0]
   Int_t           dau2ssd[30000];   //[nv0]
   Int_t           dau2svt[30000];   //[nv0]
   Int_t           dau2tofflag[30000];   //[nv0]
   Float_t         dau2tof[30000];   //[nv0]
   Float_t         dau2pathlen[30000];   //[nv0]
   Float_t         dau2firstx[30000];   //[nv0]
   Float_t         dau2firsty[30000];   //[nv0]
   Float_t         dau2firstz[30000];   //[nv0]
   Float_t         dau2lastx[30000];   //[nv0]
   Float_t         dau2lasty[30000];   //[nv0]
   Float_t         dau2lastz[30000];   //[nv0]
   Float_t         dca1to2[30000];   //[nv0]

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_evtnumber;   //!
   TBranch        *b_trgmode;   //!
   TBranch        *b_nrefmult;   //!
   TBranch        *b_nrefmultftpceast;   //!
   TBranch        *b_bbcadcsumeast;   //!
   TBranch        *b_zdcadc0;   //!
   TBranch        *b_bbccirate;   //!
   TBranch        *b_zdccirate;   //!
   TBranch        *b_ntofmatched;   //!
   TBranch        *b_primvertexX;   //!
   TBranch        *b_primvertexY;   //!
   TBranch        *b_primvertexZ;   //!
   TBranch        *b_magn;   //!
   TBranch        *b_nv0;   //!
   TBranch        *b_v0mass;   //!
   TBranch        *b_v0pt;   //!
   TBranch        *b_v0rapidity;   //!
   TBranch        *b_v0eta;   //!
   TBranch        *b_v0x;   //!
   TBranch        *b_v0y;   //!
   TBranch        *b_v0z;   //!
   TBranch        *b_v0px;   //!
   TBranch        *b_v0py;   //!
   TBranch        *b_v0pz;   //!
   TBranch        *b_v0declen;   //!
   TBranch        *b_v0dca;   //!
   TBranch        *b_v0dca2d;   //!
   TBranch        *b_v0pathlen;   //!
   TBranch        *b_dau1id;   //!
   TBranch        *b_dau1dca;   //!
   TBranch        *b_dau1dca2d;   //!
   TBranch        *b_dau1nhits;   //!
   TBranch        *b_dau1nhitsdedx;   //!
   TBranch        *b_dau1nhitsposs;   //!
   TBranch        *b_dau1dedx;   //!
   TBranch        *b_dau1nsigma;   //!
   TBranch        *b_dau1eta;   //!
   TBranch        *b_dau1pt;   //!
   TBranch        *b_dau1px;   //!
   TBranch        *b_dau1py;   //!
   TBranch        *b_dau1pz;   //!
   TBranch        *b_dau1tpc;   //!
   TBranch        *b_dau1ssd;   //!
   TBranch        *b_dau1svt;   //!
   TBranch        *b_dau1tofflag;   //!
   TBranch        *b_dau1tof;   //!
   TBranch        *b_dau1pathlen;   //!
   TBranch        *b_dau1firstx;   //!
   TBranch        *b_dau1firsty;   //!
   TBranch        *b_dau1firstz;   //!
   TBranch        *b_dau1lastx;   //!
   TBranch        *b_dau1lasty;   //!
   TBranch        *b_dau1lastz;   //!
   TBranch        *b_dau2id;   //!
   TBranch        *b_dau2dca;   //!
   TBranch        *b_dau2dca2d;   //!
   TBranch        *b_dau2nhits;   //!
   TBranch        *b_dau2nhitsdedx;   //!
   TBranch        *b_dau2nhitsposs;   //!
   TBranch        *b_dau2dedx;   //!
   TBranch        *b_dau2nsigma;   //!
   TBranch        *b_dau2eta;   //!
   TBranch        *b_dau2pt;   //!
   TBranch        *b_dau2px;   //!
   TBranch        *b_dau2py;   //!
   TBranch        *b_dau2pz;   //!
   TBranch        *b_dau2tpc;   //!
   TBranch        *b_dau2ssd;   //!
   TBranch        *b_dau2svt;   //!
   TBranch        *b_dau2tofflag;   //!
   TBranch        *b_dau2tof;   //!
   TBranch        *b_dau2pathlen;   //!
   TBranch        *b_dau2firstx;   //!
   TBranch        *b_dau2firsty;   //!
   TBranch        *b_dau2firstz;   //!
   TBranch        *b_dau2lastx;   //!
   TBranch        *b_dau2lasty;   //!
   TBranch        *b_dau2lastz;   //!
   TBranch        *b_dca1to2;   //!

   v0dst(TTree *tree=0);
   virtual ~v0dst();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef v0dst_cxx
v0dst::v0dst(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../output.k0s/324502266C711EE7CD7F6FF5070C116A_2920.ks.picodst.root");
      if (!f) {
         f = new TFile("../output.k0s/324502266C711EE7CD7F6FF5070C116A_2920.ks.picodst.root");
      }
      tree = (TTree*)gDirectory->Get("V0PicoDst");

   }
   Init(tree);
}

v0dst::~v0dst()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t v0dst::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t v0dst::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void v0dst::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("evtnumber", &evtnumber, &b_evtnumber);
   fChain->SetBranchAddress("trgmode", &trgmode, &b_trgmode);
   fChain->SetBranchAddress("nrefmult", &nrefmult, &b_nrefmult);
   fChain->SetBranchAddress("nrefmultftpceast", &nrefmultftpceast, &b_nrefmultftpceast);
   fChain->SetBranchAddress("bbcadcsumeast", &bbcadcsumeast, &b_bbcadcsumeast);
   fChain->SetBranchAddress("zdcadc0", &zdcadc0, &b_zdcadc0);
   fChain->SetBranchAddress("bbccirate", &bbccirate, &b_bbccirate);
   fChain->SetBranchAddress("zdccirate", &zdccirate, &b_zdccirate);
   fChain->SetBranchAddress("ntofmatched", &ntofmatched, &b_ntofmatched);
   fChain->SetBranchAddress("primvertexX", &primvertexX, &b_primvertexX);
   fChain->SetBranchAddress("primvertexY", &primvertexY, &b_primvertexY);
   fChain->SetBranchAddress("primvertexZ", &primvertexZ, &b_primvertexZ);
   fChain->SetBranchAddress("magn", &magn, &b_magn);
   fChain->SetBranchAddress("nv0", &nv0, &b_nv0);
   fChain->SetBranchAddress("v0mass", v0mass, &b_v0mass);
   fChain->SetBranchAddress("v0pt", v0pt, &b_v0pt);
   fChain->SetBranchAddress("v0rapidity", v0rapidity, &b_v0rapidity);
   fChain->SetBranchAddress("v0eta", v0eta, &b_v0eta);
   fChain->SetBranchAddress("v0x", v0x, &b_v0x);
   fChain->SetBranchAddress("v0y", v0y, &b_v0y);
   fChain->SetBranchAddress("v0z", v0z, &b_v0z);
   fChain->SetBranchAddress("v0px", v0px, &b_v0px);
   fChain->SetBranchAddress("v0py", v0py, &b_v0py);
   fChain->SetBranchAddress("v0pz", v0pz, &b_v0pz);
   fChain->SetBranchAddress("v0declen", v0declen, &b_v0declen);
   fChain->SetBranchAddress("v0dca", v0dca, &b_v0dca);
   fChain->SetBranchAddress("v0dca2d", v0dca2d, &b_v0dca2d);
   fChain->SetBranchAddress("v0pathlen", v0pathlen, &b_v0pathlen);
   fChain->SetBranchAddress("dau1id", dau1id, &b_dau1id);
   fChain->SetBranchAddress("dau1dca", dau1dca, &b_dau1dca);
   fChain->SetBranchAddress("dau1dca2d", dau1dca2d, &b_dau1dca2d);
   fChain->SetBranchAddress("dau1nhits", dau1nhits, &b_dau1nhits);
   fChain->SetBranchAddress("dau1nhitsdedx", dau1nhitsdedx, &b_dau1nhitsdedx);
   fChain->SetBranchAddress("dau1nhitsposs", dau1nhitsposs, &b_dau1nhitsposs);
   fChain->SetBranchAddress("dau1dedx", dau1dedx, &b_dau1dedx);
   fChain->SetBranchAddress("dau1nsigma", dau1nsigma, &b_dau1nsigma);
   fChain->SetBranchAddress("dau1eta", dau1eta, &b_dau1eta);
   fChain->SetBranchAddress("dau1pt", dau1pt, &b_dau1pt);
   fChain->SetBranchAddress("dau1px", dau1px, &b_dau1px);
   fChain->SetBranchAddress("dau1py", dau1py, &b_dau1py);
   fChain->SetBranchAddress("dau1pz", dau1pz, &b_dau1pz);
   fChain->SetBranchAddress("dau1tpc", dau1tpc, &b_dau1tpc);
   fChain->SetBranchAddress("dau1ssd", dau1ssd, &b_dau1ssd);
   fChain->SetBranchAddress("dau1svt", dau1svt, &b_dau1svt);
   fChain->SetBranchAddress("dau1tofflag", dau1tofflag, &b_dau1tofflag);
   fChain->SetBranchAddress("dau1tof", dau1tof, &b_dau1tof);
   fChain->SetBranchAddress("dau1pathlen", dau1pathlen, &b_dau1pathlen);
   fChain->SetBranchAddress("dau1firstx", dau1firstx, &b_dau1firstx);
   fChain->SetBranchAddress("dau1firsty", dau1firsty, &b_dau1firsty);
   fChain->SetBranchAddress("dau1firstz", dau1firstz, &b_dau1firstz);
   fChain->SetBranchAddress("dau1lastx", dau1lastx, &b_dau1lastx);
   fChain->SetBranchAddress("dau1lasty", dau1lasty, &b_dau1lasty);
   fChain->SetBranchAddress("dau1lastz", dau1lastz, &b_dau1lastz);
   fChain->SetBranchAddress("dau2id", dau2id, &b_dau2id);
   fChain->SetBranchAddress("dau2dca", dau2dca, &b_dau2dca);
   fChain->SetBranchAddress("dau2dca2d", dau2dca2d, &b_dau2dca2d);
   fChain->SetBranchAddress("dau2nhits", dau2nhits, &b_dau2nhits);
   fChain->SetBranchAddress("dau2nhitsdedx", dau2nhitsdedx, &b_dau2nhitsdedx);
   fChain->SetBranchAddress("dau2nhitsposs", dau2nhitsposs, &b_dau2nhitsposs);
   fChain->SetBranchAddress("dau2dedx", dau2dedx, &b_dau2dedx);
   fChain->SetBranchAddress("dau2nsigma", dau2nsigma, &b_dau2nsigma);
   fChain->SetBranchAddress("dau2eta", dau2eta, &b_dau2eta);
   fChain->SetBranchAddress("dau2pt", dau2pt, &b_dau2pt);
   fChain->SetBranchAddress("dau2px", dau2px, &b_dau2px);
   fChain->SetBranchAddress("dau2py", dau2py, &b_dau2py);
   fChain->SetBranchAddress("dau2pz", dau2pz, &b_dau2pz);
   fChain->SetBranchAddress("dau2tpc", dau2tpc, &b_dau2tpc);
   fChain->SetBranchAddress("dau2ssd", dau2ssd, &b_dau2ssd);
   fChain->SetBranchAddress("dau2svt", dau2svt, &b_dau2svt);
   fChain->SetBranchAddress("dau2tofflag", dau2tofflag, &b_dau2tofflag);
   fChain->SetBranchAddress("dau2tof", dau2tof, &b_dau2tof);
   fChain->SetBranchAddress("dau2pathlen", dau2pathlen, &b_dau2pathlen);
   fChain->SetBranchAddress("dau2firstx", dau2firstx, &b_dau2firstx);
   fChain->SetBranchAddress("dau2firsty", dau2firsty, &b_dau2firsty);
   fChain->SetBranchAddress("dau2firstz", dau2firstz, &b_dau2firstz);
   fChain->SetBranchAddress("dau2lastx", dau2lastx, &b_dau2lastx);
   fChain->SetBranchAddress("dau2lasty", dau2lasty, &b_dau2lasty);
   fChain->SetBranchAddress("dau2lastz", dau2lastz, &b_dau2lastz);
   fChain->SetBranchAddress("dca1to2", dca1to2, &b_dca1to2);
   Notify();
}

Bool_t v0dst::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void v0dst::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t v0dst::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef v0dst_cxx
