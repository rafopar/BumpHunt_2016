/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DrawBunchStructure.cc
 * Author: rafopar
 *
 * Created on August 18, 2020, 7:57 PM
 */

#include <cstdlib>

using namespace std;

template <typename T>
void MakeStyle1(T*);

/*
 * 
 */
void DrawBunchStructure() {

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "", 900, 900);
    c1->SetLeftMargin(0.14);
    c1->SetTopMargin(0.02);
    c1->SetBottomMargin(0.14);
    c1->SetRightMargin(0.02);
    c1->SetGridx();

    TFile *file_in = new TFile("EventSelection_Data_BunchStructure.root", "Read");

    TH2D *h_dt_EsumHighPSum1 = (TH2D*) file_in->Get("h_dt_EsumHighPSum1");
    h_dt_EsumHighPSum1->SetTitle("; E_{Bot} + E_{Top} [GeV]; #delta t [ns]");
    MakeStyle1(h_dt_EsumHighPSum1);
    h_dt_EsumHighPSum1->Draw("col");
    c1->Print("Figs/cl_dt_Esum_Accidentals.eps");
    c1->Print("Figs/cl_dt_Esum_Accidentals.pdf");
    c1->Print("Figs/cl_dt_Esum_Accidentals.png");

    const double ESumCut = 2.9;
    int EsumCutBin = h_dt_EsumHighPSum1->GetXaxis()->FindBin(ESumCut);

    TH1D *h_dt_Accidentals = (TH1D*) h_dt_EsumHighPSum1->ProjectionY("h_dt_Accidentals", EsumCutBin, h_dt_EsumHighPSum1->GetNbinsX());
    h_dt_Accidentals->SetTitle("; #delta t [ns]");
    h_dt_Accidentals->Draw();
    c1->Print("Figs/cl_dt_Accidentals.eps");
    c1->Print("Figs/cl_dt_Accidentals.pdf");
    c1->Print("Figs/cl_dt_Accidentals.png");

    TGraphErrors *gr_AccCounts = new TGraphErrors();

    double dt = -14.99;
    const double binStr = 2.;
    
    int ind = 0;
    while (dt < 15.) {
        
        int bin1 = h_dt_Accidentals->FindBin(dt);
        int bin2 = h_dt_Accidentals->FindBin(dt + binStr);
        
        double counts = h_dt_Accidentals->Integral(bin1, bin2 - 1);
        
        gr_AccCounts->SetPoint(ind, dt + binStr/2., counts);
        gr_AccCounts->SetPointError(ind, 0., sqrt(counts));
        
        ind = ind + 1;
        dt = dt + binStr;
    }

    MakeStyle1(gr_AccCounts);
    
    gr_AccCounts->SetTitle("; bunch time difference [ns]; counts #pm 1 ns");
    gr_AccCounts->SetMarkerColor(4);
    gr_AccCounts->SetMarkerStyle(20);
    gr_AccCounts->SetMinimum(0.);
    gr_AccCounts->Draw("AP");

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