/* 
 * File:   DrawTruthMatching.cc
 * Author: rafopar
 *
 * Created on August 5, 2020, 1:00 AM
 */

#include <cstdlib>

using namespace std;

template <typename T>
void MakeStyle1(T*);

/*
 * 
 */
void DrawTruthMatching() {

    TCanvas *c1 = new TCanvas("c1", "", 800, 800);
    c1->SetLeftMargin(0.14);
    c1->SetRightMargin(0.02);
    c1->SetTopMargin(0.02);
    c1->SetBottomMargin(0.14);

    const int ApMass = 155;

    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    
    /*
     As an example we take one of high mass A's which will have
     * relatively clean samples, then we can dray d_p and d_theta distributions.
     */

    TFile *file_in = new TFile(Form("EventSelection_Ap_%d_MeV.root", ApMass));

    TH2D *h_dP_PTrue_em2 = (TH2D*) file_in->Get("h_dP_PTrue_em2");
    h_dP_PTrue_em2->SetTitle("; P [GeV]; (#Delta P)/P");
    MakeStyle1(h_dP_PTrue_em2);
    
    h_dP_PTrue_em2->Draw("col");
    c1->Print("Figs/TruthMatch_dP_P.eps");
    c1->Print("Figs/TruthMatch_dP_P.pdf");
    c1->Print("Figs/TruthMatch_dP_P.png");

    c1->SetLogy();
    TH2D *h_dThetaTrue_Minv2 = (TH2D*)file_in->Get("h_dThetaTrue_Minv2");
    TH1D *h_dth = (TH1D*)h_dThetaTrue_Minv2->ProjectionY("h_dth", 1, h_dThetaTrue_Minv2->GetNbinsX());
    h_dth->SetTitle("; #Delta #theta [deg]");
    h_dth->SetAxisRange(0., 4., "X");
    MakeStyle1(h_dth);
    h_dth->Draw();
    line1->DrawLine(1., 0., 1., h_dth->GetMaximum());
    c1->Print("Figs/TruthMatch_dTheta.eps");
    c1->Print("Figs/TruthMatch_dTheta.pdf");
    c1->Print("Figs/TruthMatch_dTheta.png");
}

template <typename T>
void MakeStyle1(T* drObj) {
    drObj->GetYaxis()->SetLabelSize(0.051);
    drObj->GetXaxis()->SetLabelSize(0.051);
    drObj->GetYaxis()->SetTitleOffset(1.2);
    drObj->GetXaxis()->SetTitleOffset(0.9);
    drObj->GetYaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetNdivisions(510);
}
