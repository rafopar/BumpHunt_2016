/* 
 * File:   ParametrizeCBPars.cc
 * Author: rafopar
 *
 * Created on July 17, 2020, 3:00 PM
 */

#include <cstdlib>
#include <TF1.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TFile.h>

using namespace std;

/*
 * This code runs over all Masses, fits them with a Crystal-Ball function, and
 * then will parametrize all parameters of CB function as a function of mass
 */

TH1D* FitApMass(std::string, TF1*);

void ParametrizeCBPars() {

    vector<int> v_masses = {40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130,
        135, 140, 145, 155, 160, 165, 170, 175};


    TFile *file_out = new TFile("AP_CrystalBallFits.root", "Recreate");

    TF1 *f_CB = new TF1("f_CB", "crystalball", 0.03, 0.22);
    f_CB->SetNpx(4500);
    //f_CB->SetParLimits(4, 0., 200);
    f_CB->FixParameter(4, 10.);

    TGraphErrors *gr_mean = new TGraphErrors();
    TGraphErrors *gr_sigm = new TGraphErrors();
    TGraphErrors *gr_alpha = new TGraphErrors();
    TGraphErrors *gr_n = new TGraphErrors();

    int ind = 0;
    for (int mass : v_masses) {

        std::string fname = Form("EventSelection_Ap_%d_MeV.root", mass);

        TH1D *h_tmp = FitApMass(fname, f_CB);
        file_out->cd();


        TH1D *h_cur = (TH1D*) h_tmp->Clone(Form("Ap_ScSm_%d", mass));
        h_cur->SetName(Form("Ap_ScSm_%d", mass));

        double mean = f_CB->GetParameter(1);
        double sigm = f_CB->GetParameter(2);
        double alpha = f_CB->GetParameter(3);
        double n = f_CB->GetParameter(4);

        gr_mean->SetPoint(ind, mass, mean);
        gr_sigm->SetPoint(ind, mass, sigm);
        gr_n->SetPoint(ind, mass, n);
        gr_alpha->SetPoint(ind, mass, alpha);

        ind = ind + 1;
    }

    file_out->cd();
    TF1 *f_mean = new TF1("f_mean", "0 + [1]*x", 0., 200.);
    f_mean->SetNpx(4500);
    gr_mean->Draw("AP");
    gr_mean->Fit(f_mean, "MeV", "", 30., 190.);

    TF1 *f_sigm = new TF1("f_sigm", "pol4", 0., 200.);
    f_sigm->SetParameters(0.000130018, 4.74687e-05, -2.98764e-07, 3.26166e-09, -9.89314e-12);
    f_sigm->SetNpx(4500);
    gr_sigm->Draw("AP");
    gr_sigm->Fit(f_sigm, "MeV", "", 30., 190.);


    TF1 *f_alpha = new TF1("f_alpha", "pol9", 0., 200.);
    f_alpha->SetParameters(37.1181, -3.32656, 0.13699, -0.00322371, 4.75482e-05, -4.54681e-07, 2.81361e-09,
            -1.08431e-11, 2.35569e-14, -2.19113e-17);
    f_alpha->SetNpx(4500);
    gr_alpha->Draw("AP");
    gr_alpha->Fit(f_alpha, "MeV", "", 30., 190.);

    TF1 *f_n = new TF1("f_n", "pol0", 0., 200.);
    f_n->SetNpx(4500);
    gr_n->Draw("AP");
    gr_n->Fit(f_n, "MeV", "", 30., 190.);
    
    
    gDirectory->Write();
    f_mean->Write();
    f_sigm->Write();
    f_alpha->Write();
    f_n->Write();
    gr_mean->Write("gr_mean");
    gr_sigm->Write("gr_sigm");
    gr_alpha->Write("gr_alpha");
    gr_n->Write("gr_n");


    return 0;
}

TH1D *FitApMass(std::string fname, TF1* f) {
    TFile *file_in = new TFile(fname.c_str(), "Read");

    TH1D *h = (TH1D*) file_in->Get("h_MinvScSm_General_Final_1");
    double rms = h->GetRMS();
    double max = h->GetMaximum();
    double mean = h->GetBinCenter(h->GetMaximumBin());

    f->SetParameters(max, mean, rms, 1.6, 30);

    h->Fit(f, "MeV", "", mean - 5 * rms, mean + 5 * rms);

    return h;
}