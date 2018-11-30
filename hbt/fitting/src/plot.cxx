#ifndef PLOT_CXX
#define PLOT_CXX

namespace plot{

    void setPadMargins(TCanvas* canvas, Int_t nRows, Int_t nColumns, 
                        Float_t leftMargin, Float_t bottomMargin,
                        Float_t topMargin = 0.1, Float_t rightMargin = 0.1);

}

void plot::setPadMargins(TCanvas* canvas, Int_t nRows, Int_t nColumns, 
                        Float_t leftMargin, Float_t bottomMargin,
                        Float_t topMargin, Float_t rightMargin)
{

    Float_t dx = (1 - leftMargin - rightMargin) / Float_t(nColumns);
    Float_t dy = (1 - bottomMargin - topMargin) / Float_t(nRows);
    Float_t padBottomMargin = bottomMargin / (dy + bottomMargin);
    Float_t padLeftMargin = leftMargin / (dx + leftMargin);

    for (Int_t i = 0; i <= (nRows-1); i++) {
        Float_t yLow = -1, yHigh = -1;
        if( i == (nRows-1) ) {
            yLow = 0;
            yHigh = dy + bottomMargin;
        } else {
            yHigh = 1 - i*dy - topMargin;
            yLow = yHigh - dy;
            // yLow = (i+1)*dy + bottomMargin;
            // yHigh = yLow + dy;
        }

        for (Int_t j = 0; j <= (nColumns-1); j++) {
            Float_t xLow = -1, xHigh = -1;
            if(j == 0) {
                xLow = 0;
                xHigh = dx + leftMargin;
            } else {
                xLow = j*dx + leftMargin;
                xHigh = xLow + dx;
            }


            Int_t padNumber = i*nColumns + (j+1);
            canvas->cd(padNumber);
            gPad->SetPad(xLow, yLow, xHigh, yHigh);
            if( i == (nRows-1) )  {gPad->SetBottomMargin(padBottomMargin);} 
            if( j == 0 )  {gPad->SetLeftMargin(padLeftMargin);} 

            // This is a fudge factor to make the right portion of the frame
            // visible in the pad.
            if(j == (nColumns-1) ) { gPad->SetRightMargin(0.01); }
        }
    }
}

#endif
