/* 
 * File:   PlotUnblindedMass.cc
 * Author: rafopar
 *
 * Created on May 13, 2020, 1:33 PM
 */

#include <cstdlib>

using namespace std;


template <typename T>
void MakeStyle1(T*);

/*
 * 
 */
void PlotUnblindedMass() {


    TCanvas *c1 = new TCanvas("c1", "", 1800, 900);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    TF1 *f_Pol0 = new TF1("f_Pol0", "[0]", 0., 0.45);

    const double mass_max = 0.299;
    const double mass_min = 0.02;

    TFile *file_10Percent = new TFile("EventSelection_Data_10Percent.root", "Read");

    TH1D *h_Mass_10Percent = (TH1D*)((TH1D*) file_10Percent->Get("h_Minv_General_Final_1"))->Rebin(10, "h_Mass_10Percent");
    h_Mass_10Percent->SetStats(0);
    double bw = h_Mass_10Percent->GetBinWidth(10)*1000; // to convert to MeV
    double scale2MeVBin = 1./bw;
    h_Mass_10Percent->Scale(scale2MeVBin);
    h_Mass_10Percent->SetTitle("; M(e^{-}e^{+}) [GeV]; dN/dM [MeV^{-1}]");
    h_Mass_10Percent->SetLineColor(2);
    h_Mass_10Percent->SetLineWidth(2);
    MakeStyle1(h_Mass_10Percent);
    double N_10Percent = h_Mass_10Percent->GetEntries();
    double Lumi10Percent = 1100.861649; // inverse nb
    
    TFile *file_FullStat = new TFile("EventSelection_pass4Full.root", "Read");
    TH1D *h_Mass_FullStat = (TH1D*)((TH1D*) file_FullStat->Get("h_Minv_General_Final_1"))->Rebin(10, "h_Mass_FullStat");
    h_Mass_FullStat->Scale(scale2MeVBin);
    h_Mass_FullStat->SetStats(0);
    h_Mass_FullStat->SetLineWidth(2);
    h_Mass_FullStat->SetTitle("; M(e^{-}e^{+}) [GeV]; dN/dM [MeV^{-1}]");
    h_Mass_FullStat->SetAxisRange(mass_min, mass_max);
    MakeStyle1(h_Mass_FullStat);
    double N_Full = h_Mass_FullStat->GetEntries();
    double LumiFull = 10753.2716; // inverse nb

    c1->SetLogy();

    h_Mass_10Percent->Draw("hist");
    lat1->DrawLatex(0.55, 0.8, "HPS Preliminary");
    c1->Print("Figs/10PercentMass.eps");
    c1->Print("Figs/10PercentMass.pdf");
    c1->Print("Figs/10PercentMass.png");

    h_Mass_FullStat->SetDrawOption("hist");
    h_Mass_10Percent->SetDrawOption("hist");
    TRatioPlot *rpMass = new TRatioPlot(h_Mass_FullStat, h_Mass_10Percent);
    rpMass->Draw();
    rpMass->GetUpperPad()->SetLogy();
    rpMass->GetUpperPad()->SetBottomMargin(0.);
    rpMass->GetLowerPad()->SetTopMargin(0.);
    rpMass->GetLowerRefGraph()->SetMaximum(11.1);
    rpMass->GetLowerRefGraph()->SetMinimum(8.9);
    TGraphErrors *grRatio = (TGraphErrors*) rpMass->GetLowerRefGraph();
    grRatio->Fit(f_Pol0, "MeV", "", mass_min, mass_max);
    MakeStyle1(grRatio);
    grRatio->GetYaxis()->SetNdivisions(102);
    rpMass->GetUpperPad()->cd();
    double ratio = f_Pol0->GetParameter(0);
    double ratioEntries = N_Full/N_10Percent;
    double ratioLumi = LumiFull/Lumi10Percent;
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.55, 0.75, "Full data set.");
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.55, 0.65, "Unblinded data set");
    lat1->SetTextColor(1);
    lat1->DrawLatex(0.7, 0.82, "HPS Preliminary");

    rpMass->GetUpperPad()->cd();
    lat1->DrawLatex(0.25, 0.25, Form("Ratio Lumi = %1.4f", ratioLumi));
    lat1->DrawLatex(0.25, 0.2, Form("Ratio Fit = %1.4f", ratio));
    lat1->DrawLatex(0.25, 0.15, Form("Ratio Entries = %1.4f", ratioEntries));
    c1->Print("Figs/Unblinded_MassRatio.eps");
    c1->Print("Figs/Unblinded_MassRatio.pdf");
    c1->Print("Figs/Unblinded_MassRatio.png");


    c1->cd();
    c1->Clear();
    c1->SetLogy();
    h_Mass_FullStat->SetAxisRange(0.02, 0.299);
    h_Mass_10Percent->Scale(ratio);
    h_Mass_10Percent->Draw("hist");
    h_Mass_FullStat->Draw("hist Same");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.5, 0.75, "Full data set");
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.5, 0.65, Form("Unblinded data set scaled by %1.2f", ratio));
    lat1->SetTextColor(1);
    lat1->DrawLatex(0.7, 0.82, "HPS Preliminary");
    c1->Print("Figs/UnblindedMassCompare.eps");
    c1->Print("Figs/UnblindedMassCompare.pdf");
    c1->Print("Figs/UnblindedMassCompare.png");


    return 0;
}

template <typename T>
void MakeStyle1(T* drObj) {
    drObj->GetYaxis()->SetLabelSize(0.051);
    drObj->GetXaxis()->SetLabelSize(0.051);
    drObj->GetYaxis()->SetTitleOffset(1.);
    drObj->GetXaxis()->SetTitleOffset(0.9);
    drObj->GetYaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetNdivisions(520);
}