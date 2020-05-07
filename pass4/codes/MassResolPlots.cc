/* 
 * File:   MassResolPlots.cc
 * Author: rafopar
 *
 * Created on March 12, 2020, 8:10 PM
 */

#include <cstdlib>

using namespace std;

void DrawFEEPlots();

const double Eb = 2.306;

/*
 * 
 */
void MassResolPlots() {

    DrawFEEPlots();


}

void DrawFEEPlots() {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.02);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    const double tr_xMaxFEE = 40.;
    const double tr_xMinFEE = -140.;
    //const double tr_xMinFEE = -120.;
    
    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(2);
    
    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0.9, 2.9);
    f_Gaus->SetNpx(4500);

    TFile *file_Data = new TFile("FEE_Studies_Data.root", "Read");
    
    TH2D *h_tr_YXc1 = (TH2D*)file_Data->Get("h_tr_YXc1");
    h_tr_YXc1->SetTitle("; X_{tr} [mm]; Y_{tr} [mm]");
    h_tr_YXc1->GetYaxis()->SetTitleOffset(1.2);
    h_tr_YXc1->Draw("colz");
    line1->DrawLine(tr_xMaxFEE, -100, tr_xMaxFEE, 100.);
    line1->DrawLine(tr_xMinFEE, -100, tr_xMinFEE, 100.);
    c1->Print("Figs/FEE_tr_yxc1_Data.eps");
    c1->Print("Figs/FEE_tr_yxc1_Data.pdf");
    c1->Print("Figs/FEE_tr_yxc1_Data.png");
    
    TH1D *h_Pem1 = (TH1D*)file_Data->Get("h_Pem1");
    h_Pem1->SetTitle("; P_{e^{-}} [GeV]");
    TH1D *h_Pem2 = (TH1D*)file_Data->Get("h_Pem2");
    h_Pem2->SetTitle("; P_{e^{-}} [GeV]");
    h_Pem2->SetLineColor(2);
    h_Pem1->Draw();
    h_Pem2->Scale(h_Pem1->GetMaximum()/h_Pem2->GetMaximum());
    h_Pem2->Draw("hist Same");
    c1->Print("Figs/FEE_Pem_12_Data.eps");
    c1->Print("Figs/FEE_Pem_12_Data.pdf");
    c1->Print("Figs/FEE_Pem_12_Data.png");

    TH1D *h_Pem2_Top_Data = (TH1D*) file_Data->Get("h_Pem2_Top");
    h_Pem2_Top_Data->SetTitle("; P [GeV]");
    h_Pem2_Top_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Top_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Top_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Top_Data->Fit(f_Gaus, "MeV", "", 2.1, 2.5);
    double mean_Data_Top = f_Gaus->GetParameter(1);
    double sigm_Data_Top = f_Gaus->GetParameter(2);
    lat1->DrawLatex(0.17, 0.89, Form("#mu = %1.3f GeV", mean_Data_Top));
    lat1->DrawLatex(0.17, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Top));
    lat1->DrawLatex(0.17, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top_MomFit_Data.eps");
    c1->Print("Figs/FEE_Top_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Top_MomFit_Data.png");

    TH1D *h_Pem2_Bot_Data = (TH1D*) file_Data->Get("h_Pem2_Bot");
    h_Pem2_Bot_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Bot_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Bot_Data->Fit(f_Gaus, "MeV", "", 2.08, 2.48);
    double mean_Data_Bot = f_Gaus->GetParameter(1);
    double sigm_Data_Bot = f_Gaus->GetParameter(2);
    lat1->DrawLatex(0.17, 0.89, Form("#mu = %1.3f GeV", mean_Data_Bot));
    lat1->DrawLatex(0.17, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Bot));
    lat1->DrawLatex(0.17, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot_MomFit_Data.eps");
    c1->Print("Figs/FEE_Bot_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Bot_MomFit_Data.png");

    TFile *file_MC = new TFile("FEE_Studies_Mlr.root", "Read");

    TH1D *h_Pem2_Top_MC = (TH1D*) file_MC->Get("h_Pem2_Top");
    h_Pem2_Top_MC->SetTitle("; P [GeV]");
    h_Pem2_Top_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Top_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Top_MC->GetMaximum(), Eb, 0.09);
    h_Pem2_Top_MC->Fit(f_Gaus, "MeV", "", 2.15, 2.55);
    double mean_MC_Top = f_Gaus->GetParameter(1);
    double sigm_MC_Top = f_Gaus->GetParameter(2);
    lat1->DrawLatex(0.17, 0.89, Form("#mu = %1.3f GeV", mean_MC_Top));
    lat1->DrawLatex(0.17, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Top));
    lat1->DrawLatex(0.17, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top_MomFit_MC.eps");
    c1->Print("Figs/FEE_Top_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Top_MomFit_MC.png");

    TH1D *h_Pem2_Bot_MC = (TH1D*) file_MC->Get("h_Pem2_Bot");
    h_Pem2_Bot_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Bot_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot_MC->GetMaximum(), Eb, 0.09);
    h_Pem2_Bot_MC->Fit(f_Gaus, "MeV", "", 2.16, 2.5);
    double mean_MC_Bot = f_Gaus->GetParameter(1);
    double sigm_MC_Bot = f_Gaus->GetParameter(2);
    lat1->DrawLatex(0.17, 0.89, Form("#mu = %1.3f GeV", mean_MC_Bot));
    lat1->DrawLatex(0.17, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Bot));
    lat1->DrawLatex(0.17, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot_MomFit_MC.eps");
    c1->Print("Figs/FEE_Bot_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Bot_MomFit_MC.png");


    double sigm_smear_Top = sqrt(sigm_Data_Top * sigm_Data_Top - sigm_MC_Top * sigm_MC_Top);
    double sigm_smear_Bot = sqrt(sigm_Data_Bot * sigm_Data_Bot - sigm_MC_Bot * sigm_MC_Bot);
    double DataScale_Top = Eb / mean_Data_Top;
    double DataScale_Bot = Eb / mean_Data_Bot;
    double MCScale_Top = Eb / mean_MC_Top;
    double MCScale_Bot = Eb / mean_MC_Bot;



    TH1D *h_Pem2_Top5hits_Data = (TH1D*) file_Data->Get("h_Pem2_Top5hits");
    h_Pem2_Top5hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Top5hits_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Top5hits_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Top5hits_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Top5hits_Data->Fit(f_Gaus, "MeV", "", 2.1, 2.5);
    double mean_Data_Top5hits = f_Gaus->GetParameter(1);
    double sigm_Data_Top5hits = f_Gaus->GetParameter(2);
    double sigmErr_Data_Top5hits = f_Gaus->GetParError(2);
    //double scale_Data_Top5hits = Eb / mean_Data_Top5hits;
    double scale_Data_Top5hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_Data_Top5hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Top5hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top5hits_MomFit_Data.eps");
    c1->Print("Figs/FEE_Top5hits_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Top5hits_MomFit_Data.png");

    TH1D *h_Pem2_Top6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Top6hits_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Top6hits_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Top6hits_Data->Fit(f_Gaus, "MeV", "", 2.1, 2.5);
    double mean_Data_Top6hits = f_Gaus->GetParameter(1);
    double sigm_Data_Top6hits = f_Gaus->GetParameter(2);
    double sigmErr_Data_Top6hits = f_Gaus->GetParError(2);
    //double scale_Data_Top6hits = Eb / mean_Data_Top6hits;
    double scale_Data_Top6hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_Data_Top6hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Top6hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top6hits_MomFit_Data.eps");
    c1->Print("Figs/FEE_Top6hits_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Top6hits_MomFit_Data.png");

    TH1D *h_Pem2_Bot5hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Bot5hits_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot5hits_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Bot5hits_Data->Fit(f_Gaus, "MeV", "", 2.1, 2.5);
    double mean_Data_Bot5hits = f_Gaus->GetParameter(1);
    double sigm_Data_Bot5hits = f_Gaus->GetParameter(2);
    double sigmErr_Data_Bot5hits = f_Gaus->GetParError(2);
    //double scale_Data_Bot5hits = Eb / mean_Data_Bot5hits;
    double scale_Data_Bot5hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_Data_Bot5hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Bot5hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot5hits_MomFit_Data.eps");
    c1->Print("Figs/FEE_Bot5hits_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Bot5hits_MomFit_Data.png");

    TH1D *h_Pem2_Bot6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_Data->SetAxisRange(1.7, 3.);
    h_Pem2_Bot6hits_Data->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot6hits_Data->GetMaximum(), Eb, 0.14);
    h_Pem2_Bot6hits_Data->Fit(f_Gaus, "MeV", "", 2.1, 2.5);
    double mean_Data_Bot6hits = f_Gaus->GetParameter(1);
    double sigm_Data_Bot6hits = f_Gaus->GetParameter(2);
    double sigmErr_Data_Bot6hits = f_Gaus->GetParError(2);
    //double scale_Data_Bot6hits = Eb / mean_Data_Bot6hits;
    double scale_Data_Bot6hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_Data_Bot6hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_Data_Bot6hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot6hits_MomFit_Data.eps");
    c1->Print("Figs/FEE_Bot6hits_MomFit_Data.pdf");
    c1->Print("Figs/FEE_Bot6hits_MomFit_Data.png");

    //const double scaleCorr = 0.98;
    const double scaleCorr = 1.01;
    
    TH1D *h_Pem2_Top5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top5hits");
    h_Pem2_Top5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top5hits_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Top5hits_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Top5hits_MC->GetMaximum(), Eb, 0.14);
    h_Pem2_Top5hits_MC->Fit(f_Gaus, "MeV", "", 2.15, 2.55);
    double mean_MC_Top5hits = f_Gaus->GetParameter(1);
    double sigm_MC_Top5hits = f_Gaus->GetParameter(2);
    double sigmErr_MC_Top5hits = f_Gaus->GetParError(2);
    //double scale_MC_Top5hits = scaleCorr*Eb / mean_MC_Top5hits;
    double scale_MC_Top5hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_MC_Top5hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Top5hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top5hits_MomFit_MC.eps");
    c1->Print("Figs/FEE_Top5hits_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Top5hits_MomFit_MC.png");

    TH1D *h_Pem2_Top6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Top6hits_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Top6hits_MC->GetMaximum(), Eb, 0.14);
    h_Pem2_Top6hits_MC->Fit(f_Gaus, "MeV", "", 2.15, 2.55);
    double mean_MC_Top6hits = f_Gaus->GetParameter(1);
    double sigm_MC_Top6hits = f_Gaus->GetParameter(2);
    double sigmErr_MC_Top6hits = f_Gaus->GetParError(2);
    //double scale_MC_Top6hits = scaleCorr*Eb / mean_MC_Top6hits;
    double scale_MC_Top6hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_MC_Top6hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Top6hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Top6hits_MomFit_MC.eps");
    c1->Print("Figs/FEE_Top6hits_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Top6hits_MomFit_MC.png");

    TH1D *h_Pem2_Bot5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Bot5hits_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot5hits_MC->GetMaximum(), Eb, 0.14);
    h_Pem2_Bot5hits_MC->Fit(f_Gaus, "MeV", "", 2.15, 2.55);
    double mean_MC_Bot5hits = f_Gaus->GetParameter(1);
    double sigm_MC_Bot5hits = f_Gaus->GetParameter(2);
    double sigmErr_MC_Bot5hits = f_Gaus->GetParError(2);
    //double scale_MC_Bot5hits = scaleCorr*Eb / mean_MC_Bot5hits;
    double scale_MC_Bot5hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_MC_Bot5hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Bot5hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot5hits_MomFit_MC.eps");
    c1->Print("Figs/FEE_Bot5hits_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Bot5hits_MomFit_MC.png");

    TH1D *h_Pem2_Bot6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_MC->SetAxisRange(1.7, 3.);
    h_Pem2_Bot6hits_MC->Draw();
    f_Gaus->SetParameters(h_Pem2_Bot6hits_MC->GetMaximum(), Eb, 0.14);
    h_Pem2_Bot6hits_MC->Fit(f_Gaus, "MeV", "", 2.15, 2.55);
    double mean_MC_Bot6hits = f_Gaus->GetParameter(1);
    double sigm_MC_Bot6hits = f_Gaus->GetParameter(2);
    double sigmErr_MC_Bot6hits = f_Gaus->GetParError(2);
    //double scale_MC_Bot6hits = scaleCorr*Eb / mean_MC_Bot6hits;
    double scale_MC_Bot6hits = 1;
    lat1->DrawLatex(0.11, 0.89, Form("#mu = %1.3f GeV", mean_MC_Bot6hits));
    lat1->DrawLatex(0.11, 0.84, Form("#sigma = %1.4f GeV", sigm_MC_Bot6hits));
    lat1->DrawLatex(0.11, 0.79, Form("#chi^{2}/NDF = %1.2f", f_Gaus->GetChisquare() / f_Gaus->GetNDF()));
    c1->Print("Figs/FEE_Bot6hits_MomFit_MC.eps");
    c1->Print("Figs/FEE_Bot6hits_MomFit_MC.pdf");
    c1->Print("Figs/FEE_Bot6hits_MomFit_MC.png");


    double smear_Top5hits = sqrt(TMath::Power(sigm_Data_Top5hits / mean_Data_Top5hits, 2) - TMath::Power(sigm_MC_Top5hits / mean_MC_Top5hits, 2));
    double smearErr_Top5hits = sqrt(TMath::Power(sigmErr_Data_Top5hits / mean_Data_Top5hits, 2) + TMath::Power(sigmErr_MC_Top5hits / mean_MC_Top5hits, 2));
    double smear_Top6hits = sqrt(TMath::Power(sigm_Data_Top6hits / mean_Data_Top6hits, 2) - TMath::Power(sigm_MC_Top6hits / mean_MC_Top6hits, 2));
    double smearErr_Top6hits = sqrt(TMath::Power(sigmErr_Data_Top6hits / mean_Data_Top6hits, 2) + TMath::Power(sigmErr_MC_Top6hits / mean_MC_Top6hits, 2));
    double smear_Bot5hits = sqrt(TMath::Power(sigm_Data_Bot5hits / mean_Data_Bot5hits, 2) - TMath::Power(sigm_MC_Bot5hits / mean_MC_Bot5hits, 2));
    double smearErr_Bot5hits = sqrt(TMath::Power(sigmErr_Data_Bot5hits / mean_Data_Bot5hits, 2) + TMath::Power(sigmErr_MC_Bot5hits / mean_MC_Bot5hits, 2));
    double smear_Bot6hits = sqrt(TMath::Power(sigm_Data_Bot6hits / mean_Data_Bot6hits, 2) - TMath::Power(sigm_MC_Bot6hits / mean_MC_Bot6hits, 2));
    double smearErr_Bot6hits = sqrt(TMath::Power(sigmErr_Data_Bot6hits / mean_Data_Bot6hits, 2) + TMath::Power(sigmErr_MC_Bot6hits / mean_MC_Bot6hits, 2));

    TFile *file_out = new TFile("MomSmearScale.root", "Recreate");
    TTree *tr1 = new TTree("tr1", "Momentum resolution Parameters");
    tr1->Branch("mean_Data_Top5hits", &mean_Data_Top5hits, "mean_Data_Top5hits/D");
    tr1->Branch("sigm_Data_Top5hits", &sigm_Data_Top5hits, "sigm_Data_Top5hits/D");
    tr1->Branch("sigmErr_Data_Top5hits", &sigmErr_Data_Top5hits, "sigmErr_Data_Top5hits/D");
    tr1->Branch("scale_Data_Top5hits", &scale_Data_Top5hits, "scale_Data_Top5hits/D");
    tr1->Branch("mean_Data_Top6hits", &mean_Data_Top6hits, "mean_Data_Top6hits/D");
    tr1->Branch("sigm_Data_Top6hits", &sigm_Data_Top6hits, "sigm_Data_Top6hits/D");
    tr1->Branch("sigmErr_Data_Top6hits", &sigmErr_Data_Top6hits, "sigmErr_Data_Top6hits/D");
    tr1->Branch("scale_Data_Top6hits", &scale_Data_Top6hits, "scale_Data_Top6hits/D");
    tr1->Branch("mean_Data_Bot5hits", &mean_Data_Bot5hits, "mean_Data_Bot5hits/D");
    tr1->Branch("sigm_Data_Bot5hits", &sigm_Data_Bot5hits, "sigm_Data_Bot5hits/D");
    tr1->Branch("sigmErr_Data_Bot5hits", &sigmErr_Data_Bot5hits, "sigmErr_Data_Bot5hits/D");
    tr1->Branch("scale_Data_Bot5hits", &scale_Data_Bot5hits, "scale_Data_Bot5hits/D");
    tr1->Branch("mean_Data_Bot6hits", &mean_Data_Bot6hits, "mean_Data_Bot6hits/D");
    tr1->Branch("sigm_Data_Bot6hits", &sigm_Data_Bot6hits, "sigm_Data_Bot6hits/D");
    tr1->Branch("sigmErr_Data_Bot6hits", &sigmErr_Data_Bot6hits, "sigmErr_Data_Bot6hits/D");
    tr1->Branch("scale_Data_Bot6hits", &scale_Data_Bot6hits, "scale_Data_Bot6hits/D");

    tr1->Branch("mean_MC_Top5hits", &mean_MC_Top5hits, "mean_MC_Top5hits/D");
    tr1->Branch("sigm_MC_Top5hits", &sigm_MC_Top5hits, "sigm_MC_Top5hits/D");
    tr1->Branch("scale_MC_Top5hits", &scale_MC_Top5hits, "scale_MC_Top5hits/D");
    tr1->Branch("mean_MC_Top6hits", &mean_MC_Top6hits, "mean_MC_Top6hits/D");
    tr1->Branch("sigm_MC_Top6hits", &sigm_MC_Top6hits, "sigm_MC_Top6hits/D");
    tr1->Branch("scale_MC_Top6hits", &scale_MC_Top6hits, "scale_MC_Top6hits/D");
    tr1->Branch("mean_MC_Bot5hits", &mean_MC_Bot5hits, "mean_MC_Bot5hits/D");
    tr1->Branch("sigm_MC_Bot5hits", &sigm_MC_Bot5hits, "sigm_MC_Bot5hits/D");
    tr1->Branch("scale_MC_Bot5hits", &scale_MC_Bot5hits, "scale_MC_Bot5hits/D");
    tr1->Branch("mean_MC_Bot6hits", &mean_MC_Bot6hits, "mean_MC_Bot6hits/D");
    tr1->Branch("sigm_MC_Bot6hits", &sigm_MC_Bot6hits, "sigm_MC_Bot6hits/D");
    tr1->Branch("scale_MC_Bot6hits", &scale_MC_Bot6hits, "scale_MC_Bot6hits/D");

    tr1->Branch("smear_Top5hits", &smear_Top5hits, "smear_Top5hits/D");
    tr1->Branch("smearErr_Top5hits", &smearErr_Top5hits, "smearErr_Top5hits/D");
    tr1->Branch("smear_Top6hits", &smear_Top6hits, "smear_Top6hits/D");
    tr1->Branch("smearErr_Top6hits", &smearErr_Top6hits, "smearErr_Top6hits/D");
    tr1->Branch("smear_Bot5hits", &smear_Bot5hits, "smear_Bot5hits/D");
    tr1->Branch("smearErr_Bot5hits", &smearErr_Bot5hits, "smearErr_Bot5hits/D");
    tr1->Branch("smear_Bot6hits", &smear_Bot6hits, "smear_Bot6hits/D");
    tr1->Branch("smearErr_Bot6hits", &smearErr_Bot6hits, "smearErr_Bot6hits/D");

    tr1->Fill();
    tr1->Write();


    ofstream out_smear("MomSmearing.dat");
    //    out_smear<<"        &       $\\mathrm{\\mu_{Top}}$   &  $\\mathrm{\\mu_{Bot}}$   &     $\\mathrm{\\sigma_{Top}}$   &  $\\mathrm{\\sigma_{Bot}}$  \\\\ \\hline "<<endl;
    //    out_smear<<"Data    &  "<<mean_Data_Top<<"    &    "<<mean_Data_Bot<<"    &    "<<sigm_Data_Top<<"    &    "<<sigm_Data_Bot<<"   \\ \\hline"<<endl;
    //    out_smear<<"MC      &  "<<mean_MC_Top<<"    &    "<<mean_MC_Bot<<"    &    "<<sigm_MC_Top<<"    &    "<<sigm_MC_Bot<<"   \\ \\hline"<<endl;


//    out_smear << "   & Data & MC \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\mu_{Top}\\; [GeV]}$  &  " << mean_Data_Top << "   &   " << mean_MC_Top << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\mu_{Bot}\\; [GeV]}$  &  " << mean_Data_Bot << "   &   " << mean_MC_Bot << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\sigma_{Top}\\; [GeV]}$  &  " << sigm_Data_Top << "   &   " << sigm_MC_Top << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\sigma_{Bot}\\; [GeV]}$  &  " << sigm_Data_Bot << "   &   " << sigm_MC_Bot << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{Scale_{Top}\\; [GeV]}$  &  " << DataScale_Top << "   &   " << MCScale_Top << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{Scale_{Bot}\\; [GeV]}$  &  " << DataScale_Bot << "   &   " << MCScale_Bot << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\sigma_{Top}^{Smear} [\\%]}$  &  " << " N/A " << "   &   " << 100. * sigm_smear_Top / mean_MC_Top << " \\\\ \\hline " << endl;
//    out_smear << "$\\mathrm{\\sigma_{Bot}^{Smear} [\\%]}$  &  " << " N/A " << "   &   " << 100. * sigm_smear_Bot / mean_MC_Bot << " \\\\ \\hline " << endl;

    out_smear << "   & Data & MC \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\mu_{Top} 5 hits\\; [GeV]}$  &  " << mean_Data_Top5hits << "   &   " << mean_MC_Top5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\mu_{Top} 6 hits\\; [GeV]}$  &  " << mean_Data_Top6hits << "   &   " << mean_MC_Top6hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\mu_{Bot} 5 hits\\; [GeV]}$  &  " << mean_Data_Bot5hits << "   &   " << mean_MC_Bot5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\mu_{Bot} 6 hits\\; [GeV]}$  &  " << mean_Data_Bot6hits << "   &   " << mean_MC_Bot6hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\sigma_{Top} 5 hits\\; [GeV]}$  &  " << sigm_Data_Top5hits << "   &   " << sigm_MC_Top5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\sigma_{Top} 6 hits\\; [GeV]}$  &  " << sigm_Data_Top6hits << "   &   " << sigm_MC_Top6hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\sigma_{Bot} 5 hits\\; [GeV]}$  &  " << sigm_Data_Bot5hits << "   &   " << sigm_MC_Bot5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\sigma_{Bot} 6 hits\\; [GeV]}$  &  " << sigm_Data_Bot6hits << "   &   " << sigm_MC_Bot6hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\Sigma_{Top}^{smear} 5 hits\\; [\\%] }$  &  N/A  &   " << 100.*smear_Top5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\Sigma_{Top}^{smear} 6 hits\\; [\\%]}$  &  N/A  &   " << 100.*smear_Top6hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\Sigma_{Bot}^{smear} 5 hits\\; [\\%]}$  &  N/A  &   " << 100.*smear_Bot5hits << " \\\\ \\hline " << endl;
    out_smear << "$\\mathrm{\\Sigma_{Bot}^{smear} 6 hits\\; [\\%]}$  &  N/A  &   " << 100.*smear_Bot5hits << " \\\\ \\hline " << endl;
    

    TH1D *h_Pem2ScaledSmear_Top_MC = (TH1D*) file_MC->Get("h_Pem2ScaledSmear_Top");
    h_Pem2ScaledSmear_Top_MC->SetTitle("; P [GeV]");
    h_Pem2ScaledSmear_Top_MC->SetLineColor(2);
    h_Pem2ScaledSmear_Top_MC->SetAxisRange(1.8, 3.);

    TH1D *h_Pem2ScaledSmear_Bot_MC = (TH1D*) file_MC->Get("h_Pem2ScaledSmear_Bot");
    h_Pem2ScaledSmear_Bot_MC->SetTitle("; P [GeV]");
    h_Pem2ScaledSmear_Bot_MC->SetLineColor(2);
    h_Pem2ScaledSmear_Bot_MC->SetAxisRange(1.8, 3.);

    TH1D *h_Pem2ScaledSmear_Top_Data = (TH1D*) file_Data->Get("h_Pem2ScaledSmear_Top");
    h_Pem2ScaledSmear_Top_Data->SetTitle("; P [GeV]");
    h_Pem2ScaledSmear_Top_Data->SetAxisRange(1.8, 3.);

    TH1D *h_Pem2ScaledSmear_Bot_Data = (TH1D*) file_Data->Get("h_Pem2ScaledSmear_Bot");
    h_Pem2ScaledSmear_Bot_Data->SetTitle("; P [GeV]");
    h_Pem2ScaledSmear_Bot_Data->SetAxisRange(1.8, 3.);


    h_Pem2ScaledSmear_Bot_MC->Draw();
    //f_Gaus->SetParameters(h_Pem2ScaledSmear_Bot_MC->SetMaximum(), Eb, )
    h_Pem2ScaledSmear_Bot_Data->Scale(1.04 * h_Pem2ScaledSmear_Bot_MC->GetMaximum() / h_Pem2ScaledSmear_Bot_Data->GetMaximum());
    h_Pem2ScaledSmear_Bot_Data->Draw("Same");







    TH1D *h_Pem2_Top5hitsScSm_Data = (TH1D*) file_Data->Get("h_Pem2_Top5hitsScSm");
    int bin1 = h_Pem2_Top5hitsScSm_Data->FindBin(2.15);
    int bin2 = h_Pem2_Top5hitsScSm_Data->FindBin(2.55);
    h_Pem2_Top5hitsScSm_Data->SetAxisRange(1.7, 3., "X");
    h_Pem2_Top5hitsScSm_Data->SetLineWidth(2);
    h_Pem2_Top5hitsScSm_Data->SetTitle("; P[GeV]");
    TH1D *h_Pem2_Top5hitsScSm_MC = (TH1D*) file_MC->Get("h_Pem2_Top5hitsScSm");
    h_Pem2_Top5hitsScSm_MC->SetAxisRange(1.7, 3., "X");
    h_Pem2_Top5hitsScSm_MC->SetLineColor(2);
    h_Pem2_Top5hitsScSm_MC->SetLineWidth(2);
    h_Pem2_Top5hitsScSm_MC->Scale(h_Pem2_Top5hitsScSm_Data->Integral(bin1, bin2) / h_Pem2_Top5hitsScSm_MC->Integral(bin1, bin2));
    h_Pem2_Top5hitsScSm_Data->Draw();
    h_Pem2_Top5hitsScSm_MC->Draw("hist Same");
    c1->Print("Figs/Pem2_Top5hits_DataMC.eps");
    c1->Print("Figs/Pem2_Top5hits_DataMC.pdf");
    c1->Print("Figs/Pem2_Top5hits_DataMC.png");

    TH1D *h_Pem2_Top6hitsScSm_Data = (TH1D*) file_Data->Get("h_Pem2_Top6hitsScSm");
    bin1 = h_Pem2_Top6hitsScSm_Data->FindBin(2.15);
    bin2 = h_Pem2_Top6hitsScSm_Data->FindBin(2.55);
    h_Pem2_Top6hitsScSm_Data->SetAxisRange(1.7, 3., "X");
    h_Pem2_Top6hitsScSm_Data->SetLineWidth(2);
    h_Pem2_Top6hitsScSm_Data->SetTitle("; P[GeV]");
    TH1D *h_Pem2_Top6hitsScSm_MC = (TH1D*) file_MC->Get("h_Pem2_Top6hitsScSm");
    h_Pem2_Top6hitsScSm_MC->SetAxisRange(1.7, 3., "X");
    h_Pem2_Top6hitsScSm_MC->SetLineColor(2);
    h_Pem2_Top6hitsScSm_MC->SetLineWidth(2);
    h_Pem2_Top6hitsScSm_MC->Scale(h_Pem2_Top6hitsScSm_Data->Integral(bin1, bin2) / h_Pem2_Top6hitsScSm_MC->Integral(bin1, bin2));
    h_Pem2_Top6hitsScSm_Data->Draw();
    h_Pem2_Top6hitsScSm_MC->Draw("hist Same");
    c1->Print("Figs/Pem2_Top6hits_DataMC.eps");
    c1->Print("Figs/Pem2_Top6hits_DataMC.pdf");
    c1->Print("Figs/Pem2_Top6hits_DataMC.png");

    TH1D *h_Pem2_Bot5hitsScSm_Data = (TH1D*) file_Data->Get("h_Pem2_Bot5hitsScSm");
    bin1 = h_Pem2_Bot5hitsScSm_Data->FindBin(2.15);
    bin2 = h_Pem2_Bot5hitsScSm_Data->FindBin(2.55);
    h_Pem2_Bot5hitsScSm_Data->SetAxisRange(1.7, 3., "X");
    h_Pem2_Bot5hitsScSm_Data->SetLineWidth(2);
    h_Pem2_Bot5hitsScSm_Data->SetTitle("; P[GeV]");
    TH1D *h_Pem2_Bot5hitsScSm_MC = (TH1D*) file_MC->Get("h_Pem2_Bot5hitsScSm");
    h_Pem2_Bot5hitsScSm_MC->SetAxisRange(1.7, 3., "X");
    h_Pem2_Bot5hitsScSm_MC->SetLineColor(2);
    h_Pem2_Bot5hitsScSm_MC->SetLineWidth(2);
    h_Pem2_Bot5hitsScSm_MC->Scale(h_Pem2_Bot5hitsScSm_Data->Integral(bin1, bin2) / h_Pem2_Bot5hitsScSm_MC->Integral(bin1, bin2));
    h_Pem2_Bot5hitsScSm_Data->Draw();
    h_Pem2_Bot5hitsScSm_MC->Draw("hist Same");
    c1->Print("Figs/Pem2_Bot5hits_DataMC.eps");
    c1->Print("Figs/Pem2_Bot5hits_DataMC.pdf");
    c1->Print("Figs/Pem2_Bot5hits_DataMC.png");

    TH1D *h_Pem2_Bot6hitsScSm_Data = (TH1D*) file_Data->Get("h_Pem2_Bot6hitsScSm");
    bin1 = h_Pem2_Bot6hitsScSm_Data->FindBin(2.15);
    bin2 = h_Pem2_Bot6hitsScSm_Data->FindBin(2.55);
    h_Pem2_Bot6hitsScSm_Data->SetAxisRange(1.7, 3., "X");
    h_Pem2_Bot6hitsScSm_Data->SetLineWidth(2);
    h_Pem2_Bot6hitsScSm_Data->SetTitle("; P[GeV]");
    TH1D *h_Pem2_Bot6hitsScSm_MC = (TH1D*) file_MC->Get("h_Pem2_Bot6hitsScSm");
    h_Pem2_Bot6hitsScSm_MC->SetAxisRange(1.7, 3., "X");
    h_Pem2_Bot6hitsScSm_MC->SetLineColor(2);
    h_Pem2_Bot6hitsScSm_MC->SetLineWidth(2);
    h_Pem2_Bot6hitsScSm_MC->Scale(h_Pem2_Bot6hitsScSm_Data->Integral(bin1, bin2) / h_Pem2_Bot6hitsScSm_MC->Integral(bin1, bin2));
    h_Pem2_Bot6hitsScSm_Data->Draw();
    h_Pem2_Bot6hitsScSm_MC->Draw("hist Same");
    c1->Print("Figs/Pem2_Bot6hits_DataMC.eps");
    c1->Print("Figs/Pem2_Bot6hits_DataMC.pdf");
    c1->Print("Figs/Pem2_Bot6hits_DataMC.png");



    file_out->Close();
}