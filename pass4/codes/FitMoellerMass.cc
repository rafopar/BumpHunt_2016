/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FitMoellerMass.cc
 * Author: rafopar
 *
 * Created on November 13, 2019, 5:05 PM
 */

#include <cstdlib>
#include <iostream>

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::string dataSet;

    if (argc >= 2) {

        dataSet = argv[1];

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./EventSelection.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }


    std::string inpFileName;

    if (dataSet.compare("Data") == 0) {
        inpFileName = "MoellerAnalyze_Data_All.root";
    } else {
        exit(1);
    }


    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetLeftMargin(0.15);
    
    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.07);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParLimits(2, 0., 0.02);

    TFile *file_in = new TFile(inpFileName.c_str(), "Read");

    TH2D *h_chi2Minv = (TH2D*) file_in->Get("h_Chi2NDF_TCM4");

    TGraph *gr1 = new TGraph();
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(2);

    int ind_chi2 = 0;

    for (int i = 0; i < h_chi2Minv->GetNbinsY(); i++) {

        TH1D *htmp = (TH1D*) h_chi2Minv->ProjectionX("tmp", 1, i + 1);
        cout << "Kuku" << endl;

        double chi2Cut = h_chi2Minv->GetYaxis()->GetBinCenter(i + 1);

        if (htmp->GetEntries() > 250) {

            if( ind_chi2 == 0 ){
                f_Gaus->SetParameters(htmp->GetMaximum(), 0.048, 0.002);
            }
            
            htmp->Fit(f_Gaus, "MeV", "", 0.03, 0.052);

            double sigm = f_Gaus->GetParameter(2);

            gr1->SetPoint(ind_chi2, chi2Cut, sigm);

            ind_chi2 = ind_chi2 + 1;
        }

    }

    gr1->Draw("AP");
    c1->Print("Figs/MassSigmaChi2Cut.eps");
    c1->Print("Figs/MassSigmaChi2Cut.pdf");
    c1->Print("Figs/MassSigmaChi2Cut.png");

    return 0;
}

