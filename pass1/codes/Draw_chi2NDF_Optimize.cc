/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Draw_chi2NDF_Optimize.cc
 * Author: rafopar
 *
 * Created on October 14, 2018, 11:10 PM
 */

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <cstdlib>
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>

using namespace std;

/*
 * 
 */
void Draw_chi2NDF_Optimize() {

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0.02, 0.07);
    TF1 *f_Landau = new TF1("f_Landau", "[0]*TMath::Landau(x, [1], [2])", 0., 20.);
    f_Landau->SetNpx(4500);

    TFile *file_in = new TFile("chi2_mass_resol.root", "Read");

    TH2D *h_M_tcMol_chi2_4 = (TH2D*) file_in->Get("h_M_tcMol_chi2_4");

    h_M_tcMol_chi2_4->SetTitle("; M(e^{-}e^{-}) [GeV]; Tot #chi^{2}/NDF");
    h_M_tcMol_chi2_4->Draw("colz");
    c1->Print("Figs/Moeller_totchi2NDF_mass.eps");
    c1->Print("Figs/Moeller_totchi2NDF_mass.pdf");
    c1->Print("Figs/Moeller_totchi2NDF_mass.png");

    int n_binsY = h_M_tcMol_chi2_4->GetNbinsY();

    const double chi2_min = 1.;
    int bin1 = h_M_tcMol_chi2_4->GetYaxis()->FindBin(chi2_min);

    TGraph *gr_sigma_dep = new TGraph();

    int gr_point = 0;
    c1->Print("Figs/Moeller_Fits.pdf[");
    for (int i = bin1; i < n_binsY; i++) {

        TH1D *h_tmp = (TH1D*) h_M_tcMol_chi2_4->ProjectionX("h_tmp", 1, i + 1);

        f_Gaus->SetParameters(h_tmp->GetMaximum(), h_tmp->GetBinCenter(h_tmp->GetMaximumBin()), 0.0024);
        h_tmp->Fit(f_Gaus, "MeV", "", 0.044, 0.052);
    c1->Print("Figs/Moeller_Fits.pdf");

        double sigm = f_Gaus->GetParameter(2);
        double chi2_ndf_val = h_M_tcMol_chi2_4->GetYaxis()->GetBinCenter(i + 1);

        gr_sigma_dep->SetPoint(gr_point, chi2_ndf_val, sigm);

        gr_point = gr_point + 1;
    }
    c1->Print("Figs/Moeller_Fits.pdf]");


    c1->SetLeftMargin(0.16);
    c1->SetRightMargin(0.02);
    gr_sigma_dep->SetMarkerStyle(20);
    gr_sigma_dep->SetMarkerColor(4);
    gr_sigma_dep->SetMarkerSize(1);
    gr_sigma_dep->GetYaxis()->SetTitleOffset(2.2);
    gr_sigma_dep->SetTitle("; #chi^{2}/NDF cut; #sigma [GeV]");
    gr_sigma_dep->Draw("AP");
    c1->Print("Figs/Moeller_sigm_chi2NDF_dep.eps");
    c1->Print("Figs/Moeller_sigm_chi2NDF_dep.pdf");
    c1->Print("Figs/Moeller_sigm_chi2NDF_dep.png");
    c1->SetLeftMargin(1.45);

    TH1D *h_chi2NDF = (TH1D*) h_M_tcMol_chi2_4->ProjectionY("h_chi2NDF", 1, h_M_tcMol_chi2_4->GetNbinsX());
    f_Landau->SetParameters(h_chi2NDF->GetMaximum(), 1., 0.35);
    h_chi2NDF->Fit(f_Landau, "MeV", "", 0., 15);
    c1->Print("Figs/Chi2NDf_Fit.eps");
    c1->Print("Figs/Chi2NDf_Fit.pdf");
    c1->Print("Figs/Chi2NDf_Fit.png");
    
    
    int n_points = gr_sigma_dep->GetN();

    TGraph *gr_ratio = new TGraph();

    for (int i = 0; i < n_points; i++) {
        double chi2, sigma;
        gr_sigma_dep->GetPoint(i, chi2, sigma);

        double integral = f_Landau->Integral(0., chi2);
        double ratio = sqrt(integral)/sigma;

        gr_ratio->SetPoint(i, chi2, ratio);
    }

    gr_ratio->SetMarkerStyle(20);
    gr_ratio->SetMarkerColor(2);
    gr_ratio->GetYaxis()->SetTitleOffset(1.4);
    gr_ratio->SetTitle("; #chi^{2}/NDF; #sqrt{N_{pass}}/#sigma");
    gr_ratio->Draw("AP");
    c1->Print("Figs/Moeller_chi2NDF_sensitivity_ratio.eps");
    c1->Print("Figs/Moeller_chi2NDF_sensitivity_ratio.pdf");
    c1->Print("Figs/Moeller_chi2NDF_sensitivity_ratio.png");
    
}

