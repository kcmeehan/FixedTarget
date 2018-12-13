   const int kCentBin = 6;
   Float_t  centbd[kCentBin+1]={-0.5,0.5,1.5,2.5,3.5,4.5,5.5};
   const char* CentName[kCentBin] = {"25-30%","20-25%","15-20%","10-15%","5-10%","0-5%"};
   //const int kCentBin = 6;
   //Float_t  centbd[kCentBin+1]={-0.5,1.5,3.5,4.5,5.5,6.5,8.5};
   //const char* CentName[kCentBin] = {"60-80%","40-60%","30-40%","20-30%","10-20%","0-10%"};
   //const int kCentBin = 3;
   //Float_t  centbd[kCentBin+1]={-0.5,3.5,5.5,8.5};
   //const char* CentName[kCentBin] = {"40-80%","20-40%","0-20%"};

   //const int kPtBin = 16;
   //Float_t  ptbd[kPtBin+1]={0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.3,2.6,3.0,3.4,3.9,4.4,5.0,6.0};
   //const int kPtBin = 14;
   //Float_t  ptbd[kPtBin+1]={0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.3,2.6,3.0,3.4,3.9,4.4};
   const int kPtBin = 13;
   Float_t  ptbd[kPtBin+1]={0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0,2.3,2.6,3.0,3.4,3.9};

   int colorwheel[9] = {kGreen,kRed,kBlue,kCyan,kOrange,6,kBlack,30,38};

