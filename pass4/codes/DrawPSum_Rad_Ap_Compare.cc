/* 
 * File:   DrawPSum_Rad_Ap_Compare.cc
 * Author: rafopar
 *
 * Created on January 15, 2020, 10:01 AM
 */

#include <cstdlib>
#include <vector>

using namespace std;

/*
 * 
 */
void DrawPSum_Rad_Ap_Compare() {

    TCanvas *c1 = new TCanvas("c1", "", 900, 900);
    vector<int> ApMasses = {50, 100, 175};

    TFile *file_Rad = new TFile("EventSelection_Rad.root", "Read");
    TH2D *h_Mass_Psum_Rad = (TH2D*) file_Rad->Get("h_Minv_PSumMin_AllBut");
    h_Mass_Psum_Rad->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Mass_Psum_Rad->Draw("colz");
    c1->Print("Figs/Minv_Psum_Rad.eps");
    c1->Print("Figs/Minv_Psum_Rad.pdf");
    c1->Print("Figs/Minv_Psum_Rad.png");

    for (int i = 0; i < ApMasses.size(); i++) {

        int mass = ApMasses.at(i);
        TFile *file_Ap = new TFile(Form("EventSelection_Ap_%d_MeV.root", mass), "Read");

        TH2D *h_Mass_Psum_Ap = (TH2D*) file_Ap->Get("h_Minv_PSumMin_AllBut");
        h_Mass_Psum_Ap->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
        h_Mass_Psum_Ap->Draw("colz");
        c1->Print(Form("Figs/Minv_Psum_Ap_%d_Mev.eps", mass));
        c1->Print(Form("Figs/Minv_Psum_Ap_%d_Mev.pdf", mass));
        c1->Print(Form("Figs/Minv_Psum_Ap_%d_Mev.png", mass));
        
        int meanBin = h_Mass_Psum_Rad->GetYaxis()->FindBin(double(mass)*0.001);
        TH1D *h_PSumRad = (TH1D*)h_Mass_Psum_Rad->ProjectionX(Form("h_PSumRad_%d_MeV", mass), meanBin - 3*mass/50, meanBin + 3*mass/50);
        
        
        TH1D *h_PSum_Ap = (TH1D*)h_Mass_Psum_Ap->ProjectionX(Form("h_PSum_Ap_%d_MeV", mass), meanBin - 3*mass/50, meanBin + 3*mass/50);

        
        h_PSum_Ap->Scale(h_PSumRad->GetMaximum()/h_PSum_Ap->GetMaximum());
        
        h_PSumRad->SetLineColor(2);
        h_PSum_Ap->SetLineColor(4);
        
        h_PSumRad->Draw("hist");
        h_PSum_Ap->Draw("hist Same");
        c1->Print(Form("Figs/PSum_Rad_Ap_Compare_%d_MeV.eps", mass));
        c1->Print(Form("Figs/PSum_Rad_Ap_Compare_%d_MeV.pdf", mass));
        c1->Print(Form("Figs/PSum_Rad_Ap_Compare_%d_MeV.png", mass));
    }

    return 0;
}

