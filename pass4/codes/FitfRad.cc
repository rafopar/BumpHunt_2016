/* 
 * File:   FitfRad.cc
 * Author: rafopar
 *
 * Created on March 10, 2020, 11:06 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
void FitfRad() {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetRightMargin(0.02);
    c1->SetLeftMargin(0.2);
    c1->SetTopMargin(0.02);
    c1->SetBottomMargin(0.12);

    TFile *file_in = new TFile("fRadHists.root", "Read");

    TH1D *h_fRadTrue = (TH1D*) file_in->Get("h_fRadTrue");
    h_fRadTrue->Draw();

    const int nPol = 10;

    TF1 * f_Pol_[nPol];

    TLegend *leg1 = new TLegend(0.3, 0.7, 0.6, 0.96);
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);

    for (int i = 0; i < nPol; i++) {
        f_Pol_[i] = new TF1(Form("f_Pol_%d", i), Form("pol%d", i), 0., 0.25);
        f_Pol_[i]->SetNpx(4500);
        
        int col = i;
        f_Pol_[i]->SetLineColor(col);
        

        h_fRadTrue->Fit(f_Pol_[i], "MeV", "", 0.04, 0.18);

        double chi2 = f_Pol_[i]->GetChisquare();
        double NDF = f_Pol_[i]->GetNDF();
        if (i > 3) {
            leg1->AddEntry(f_Pol_[i], Form("pol_%d  #chi^{2}.NDF = %1.2f", i, chi2/NDF));
            f_Pol_[i]->DrawCopy("Same");
        }
    }

    leg1->Draw();

    return 0;
}

