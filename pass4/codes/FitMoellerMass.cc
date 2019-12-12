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
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    gStyle->SetOptFit(1);
    
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

    h_chi2Minv->SetTitle("; M(e^{-}e^{-}) [GeV]; #chi^{2}/MDF");
    h_chi2Minv->Draw("colz");
    c1->Print("Figs/Chi2NDF_Mass_Moeller_Data.eps");
    c1->Print("Figs/Chi2NDF_Mass_Moeller_Data.pdf");
    c1->Print("Figs/Chi2NDF_Mass_Moeller_Data.png");
    
    TH1D *h_Chi2Proj1 = (TH1D*)h_chi2Minv->ProjectionY("h_Chi2Proj1", 1, h_chi2Minv->GetXaxis()->FindBin(0.055) );
    
    TGraphErrors *grSigma = new TGraphErrors();
    grSigma->SetTitle("; #chi^{2}/NDF cut; #sigma [GeV]");
    grSigma->SetMarkerStyle(20);
    grSigma->SetMarkerColor(2);

    TGraph *grNMoeller = new TGraph();
    grNMoeller->SetTitle("; #chi^{2}/NDF cut; #sqrt{N}");
    grNMoeller->SetMarkerStyle(20);
    grNMoeller->SetMarkerColor(2);

    TGraph *grFigOfMerit = new TGraph();
    grFigOfMerit->SetTitle("; #chi^{2}/NDF cut; #sqrt{N}/#sigma");
    grFigOfMerit->SetMarkerStyle(20);
    grFigOfMerit->SetMarkerColor(2);

    int ind_chi2 = 0;

    c1->Print("Figs/MoellerMassFits.pdf[");
    for (int i = 0; i < h_chi2Minv->GetNbinsY(); i++) {

        TH1D *htmp = (TH1D*) h_chi2Minv->ProjectionX("tmp", 1, i + 1);
        cout << "Kuku" << endl;

        double chi2Cut = h_chi2Minv->GetYaxis()->GetBinCenter(i + 1);
        double NMoeller = h_Chi2Proj1->Integral(1, i+1);

        if (htmp->GetEntries() > 250) {

            if (ind_chi2 == 0) {
                f_Gaus->SetParameters(htmp->GetMaximum(), 0.048, 0.002);
            }

            htmp->Fit(f_Gaus, "MeV", "", 0.03, 0.052);
            c1->Print("Figs/MoellerMassFits.pdf");

            double sigm = f_Gaus->GetParameter(2);
            double sigmErr = f_Gaus->GetParError(2);

            grSigma->SetPoint(ind_chi2, chi2Cut, sigm);
            grSigma->SetPointError(ind_chi2, 0, sigmErr);
            grNMoeller->SetPoint(ind_chi2, chi2Cut, sqrt(NMoeller));

            grFigOfMerit->SetPoint(ind_chi2, chi2Cut, sqrt(NMoeller)/sigm);
            
            ind_chi2 = ind_chi2 + 1;
        }

    }
    c1->Print("Figs/MoellerMassFits.pdf]");

    c1->Clear();
    grSigma->GetYaxis()->SetTitleOffset(2.);
    grSigma->Draw("AP");
    c1->Print("Figs/MassSigmaChi2Cut_Data.eps");
    c1->Print("Figs/MassSigmaChi2Cut_Data.pdf");
    c1->Print("Figs/MassSigmaChi2Cut_Data.png");
    
    c1->Clear();
    grNMoeller->Draw("AP");
    c1->Print("Figs/Sqrt_NMoeller_Data.eps");
    c1->Print("Figs/Sqrt_NMoeller_Data.pdf");
    c1->Print("Figs/Sqrt_NMoeller_Data.png");
    
    c1->Clear();
    grFigOfMerit->Draw("AP");
    c1->Print("Figs/MoellerFigOfMerit_Data.eps");
    c1->Print("Figs/MoellerFigOfMerit_Data.pdf");
    c1->Print("Figs/MoellerFigOfMerit_Data.png");

    return 0;
}

