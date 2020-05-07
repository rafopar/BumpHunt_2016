/* 
 * File:   FEECutStudies.cc
 * Author: rafopar
 *
 * Created on April 27, 2020, 5:32 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
void FEECutStudies() {

    TFile *file_Data = new TFile("FEE_Studies_Data.root");

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 1.1, 3.);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParLimits(2, 0., 0.3);

    const int n_X_Regions = 8;
    const double xMax6HitData = 2.5;
    const double xMin6HitData = 2.15;

    const double xMax5HitData = 2.55;
    const double xMin5HitData = 2.05;

    const double xMaxBot6HitData = 2.45;
    const double xMinBot6HitData = 2.1;

    TGraphErrors *gr_SigmTop6HitsData = new TGraphErrors();
    TGraph *gr_chiTop6HitsData = new TGraph();
    TGraphErrors *gr_SigmTop5HitsData = new TGraphErrors();
    TGraph *gr_chiTop5HitsData = new TGraph();
    TGraphErrors *gr_SigmBot6HitsData = new TGraphErrors();
    TGraph *gr_chiBot6HitsData = new TGraph();
    TGraphErrors *gr_SigmBot5HitsData = new TGraphErrors();
    TGraph *gr_chiBot5HitsData = new TGraph();

    TH1D * h_P_em_Top6hits_Data_[n_X_Regions];
    TH1D * h_P_em_Top5hits_Data_[n_X_Regions];
    TH1D * h_P_em_Bot6hits_Data_[n_X_Regions];
    TH1D * h_P_em_Bot5hits_Data_[n_X_Regions];

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    TCanvas *c2 = new TCanvas("c2", "", 950, 950);
    TCanvas *c3 = new TCanvas("c3", "", 950, 950);
    TCanvas *c4 = new TCanvas("c4", "", 950, 950);

    c1->Print("Figs/FEE_PeakFit_Xregions_DataTop6hits.pdf[");
    c2->Print("Figs/FEE_PeakFit_Xregions_DataTop5hits.pdf[");
    c3->Print("Figs/FEE_PeakFit_Xregions_DataBot6hits.pdf[");
    c4->Print("Figs/FEE_PeakFit_Xregions_DataBot5hits.pdf[");
    for (int i = 0; i < n_X_Regions; i++) {
        c1->cd();
        h_P_em_Top6hits_Data_[i] = (TH1D*) file_Data->Get(Form("h_Pem2_Top6hits_%d", i));
        h_P_em_Top6hits_Data_[i]->SetAxisRange(1.5, 3., "X");
        f_Gaus->SetParameters(h_P_em_Top6hits_Data_[i]->GetMaximum(), 2.28, 0.15);
        h_P_em_Top6hits_Data_[i]->Fit(f_Gaus, "MeV", "", xMin6HitData, xMax6HitData);
        double mean = f_Gaus->GetParameter(1);
        double sigm = f_Gaus->GetParameter(2);
        double sigmErr = f_Gaus->GetParError(2);
        double chi2 = f_Gaus->GetChisquare();
        double ndf = f_Gaus->GetNDF();
        gr_chiTop6HitsData->SetPoint(i, i + 1, chi2 / ndf);
        gr_SigmTop6HitsData->SetPoint(i, i + 1, sigm);
        gr_SigmTop6HitsData->SetPointError(i, 0., sigmErr);
        lat1->DrawLatex(0.15, 0.92, "Data Top 6 hits");
        lat1->DrawLatex(0.65, 0.7, Form("#sigma = %1.3f", sigm));

        c1->Print("Figs/FEE_PeakFit_Xregions_DataTop6hits.pdf");

        c2->cd();
        h_P_em_Top5hits_Data_[i] = (TH1D*) file_Data->Get(Form("h_Pem2_Top5hits_%d", i));
        h_P_em_Top5hits_Data_[i]->SetAxisRange(1.5, 3., "X");
        f_Gaus->SetParameters(h_P_em_Top5hits_Data_[i]->GetMaximum(), 2.28, 0.15);
        h_P_em_Top5hits_Data_[i]->Fit(f_Gaus, "MeV", "", xMin5HitData, xMax5HitData);
        mean = f_Gaus->GetParameter(1);
        sigm = f_Gaus->GetParameter(2);
        sigmErr = f_Gaus->GetParError(2);
        chi2 = f_Gaus->GetChisquare();
        ndf = f_Gaus->GetNDF();
        gr_chiTop5HitsData->SetPoint(i, i + 1, chi2 / ndf);
        gr_SigmTop5HitsData->SetPoint(i, i + 1, sigm);
        gr_SigmTop5HitsData->SetPointError(i, 0., sigmErr);
        lat1->DrawLatex(0.15, 0.92, "Data Top 5 hits");
        lat1->DrawLatex(0.65, 0.7, Form("#sigma = %1.3f", sigm));

        c2->Print("Figs/FEE_PeakFit_Xregions_DataTop5hits.pdf");


        c3->cd();
        h_P_em_Bot6hits_Data_[i] = (TH1D*) file_Data->Get(Form("h_Pem2_Bot6hits_%d", i));
        h_P_em_Bot6hits_Data_[i]->SetAxisRange(1.5, 3., "X");
        f_Gaus->SetParameters(h_P_em_Bot6hits_Data_[i]->GetMaximum(), 2.28, 0.15);
        h_P_em_Bot6hits_Data_[i]->Fit(f_Gaus, "MeV", "", xMinBot6HitData, xMaxBot6HitData);
        mean = f_Gaus->GetParameter(1);
        sigm = f_Gaus->GetParameter(2);
        sigmErr = f_Gaus->GetParError(2);
        chi2 = f_Gaus->GetChisquare();
        ndf = f_Gaus->GetNDF();
        gr_chiBot6HitsData->SetPoint(i, i + 1, chi2 / ndf);
        gr_SigmBot6HitsData->SetPoint(i, i + 1, sigm);
        gr_SigmBot6HitsData->SetPointError(i, 0., sigmErr);
        lat1->DrawLatex(0.15, 0.92, "Data Bot 6 hits");
        lat1->DrawLatex(0.65, 0.7, Form("#sigma = %1.3f", sigm));

        c3->Print("Figs/FEE_PeakFit_Xregions_DataBot6hits.pdf");
        
        
        c4->cd();
        h_P_em_Bot5hits_Data_[i] = (TH1D*) file_Data->Get(Form("h_Pem2_Bot5hits_%d", i));
        h_P_em_Bot5hits_Data_[i]->SetAxisRange(1.5, 3., "X");
        f_Gaus->SetParameters(h_P_em_Bot5hits_Data_[i]->GetMaximum(), 2.28, 0.15);
        h_P_em_Bot5hits_Data_[i]->Fit(f_Gaus, "MeV", "", xMin5HitData, xMax5HitData);
        mean = f_Gaus->GetParameter(1);
        sigm = f_Gaus->GetParameter(2);
        sigmErr = f_Gaus->GetParError(2);
        chi2 = f_Gaus->GetChisquare();
        ndf = f_Gaus->GetNDF();
        gr_chiBot5HitsData->SetPoint(i, i + 1, chi2 / ndf);
        gr_SigmBot5HitsData->SetPoint(i, i + 1, sigm);
        gr_SigmBot5HitsData->SetPointError(i, 0., sigmErr);
        lat1->DrawLatex(0.15, 0.92, "Data Bot 5 hits");
        lat1->DrawLatex(0.65, 0.7, Form("#sigma = %1.3f", sigm));

        c4->Print("Figs/FEE_PeakFit_Xregions_DataBot5hits.pdf");
        
    }
    c1->Print("Figs/FEE_PeakFit_Xregions_DataTop6hits.pdf]");
    c2->Print("Figs/FEE_PeakFit_Xregions_DataTop5hits.pdf]");
    c3->Print("Figs/FEE_PeakFit_Xregions_DataBot6hits.pdf]");
    c4->Print("Figs/FEE_PeakFit_Xregions_DataBot5hits.pdf]");


    c1->cd();
    TF1 *f_Pol0 = new TF1("f_Pol0", "[0]", 1.1, 3.);

    gr_SigmTop6HitsData->SetMarkerStyle(20);
    gr_SigmTop6HitsData->SetMarkerColor(2);
    gr_SigmTop6HitsData->Draw("AP");
    gr_SigmTop6HitsData->Fit(f_Pol0, "MeV", "", 0., 6.5);
    c1->Print("Figs/FeePeakXcutDep_Top6HitsData.eps");
    c1->Print("Figs/FeePeakXcutDep_Top6HitsData.pdf");
    c1->Print("Figs/FeePeakXcutDep_Top6HitsData.png");

    gr_chiTop6HitsData->SetMarkerStyle(20);
    gr_chiTop6HitsData->SetMarkerColor(2);
    gr_chiTop6HitsData->Draw("AP");


    gr_SigmTop5HitsData->SetMarkerStyle(20);
    gr_SigmTop5HitsData->SetMarkerColor(2);
    gr_SigmTop5HitsData->Draw("AP");
    gr_SigmTop5HitsData->Fit(f_Pol0, "MeV", "", 0., 6.5);
    c1->Print("Figs/FeePeakXcutDep_Top5HitsData.eps");
    c1->Print("Figs/FeePeakXcutDep_Top5HitsData.pdf");
    c1->Print("Figs/FeePeakXcutDep_Top5HitsData.png");
    
    
    gr_SigmBot6HitsData->SetMarkerStyle(20);
    gr_SigmBot6HitsData->SetMarkerColor(2);
    gr_SigmBot6HitsData->Draw("AP");
    gr_SigmBot6HitsData->Fit(f_Pol0, "MeV", "", 0., 6.5);
    c1->Print("Figs/FeePeakXcutDep_Bot6HitsData.eps");
    c1->Print("Figs/FeePeakXcutDep_Bot6HitsData.pdf");
    c1->Print("Figs/FeePeakXcutDep_Bot6HitsData.png");    

    gr_SigmBot5HitsData->SetMarkerStyle(20);
    gr_SigmBot5HitsData->SetMarkerColor(2);
    gr_SigmBot5HitsData->Draw("AP");
    gr_SigmBot5HitsData->Fit(f_Pol0, "MeV", "", 0., 6.5);
    c1->Print("Figs/FeePeakXcutDep_Bot5HitsData.eps");
    c1->Print("Figs/FeePeakXcutDep_Bot5HitsData.pdf");
    c1->Print("Figs/FeePeakXcutDep_Bot5HitsData.png");    

}

