/* 
 * File:   MassParametrization.cc
 * Author: rafopar
 *
 * Created on March 17, 2020, 7:14 PM
 */

#include <TF1.h>
#include <TH1D.h>
#include <TFile.h>
#include <TMath.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>

#include <cstdlib>

using namespace std;

template <typename T>
void MakeHistStyle(T *hist);

void WriteMlrResol(TGraphErrors *gr_MlrData, TGraphErrors *gr_MlrMC, TGraphErrors *gr_MlrMCScSm);
void WriteApResol(TGraphErrors *gr_Ap, std::string keyword, int* mass_Arr);

/*
 * 
 */
void MassParametrization() {

    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParLimits(2, 0., 9.);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextSize(0.04);
    lat1->SetTextFont(42);


    TCanvas *c0 = new TCanvas("c0", "", 1900, 950);
    //TCanvas *c0 = new TCanvas("c0", "", 1583, 792);
    c0->SetTopMargin(0.015);
    c0->SetRightMargin(0.005);
    c0->SetLeftMargin(0.1);
    c0->SetBottomMargin(0.13);
    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.02);
    c1->SetLeftMargin(0.13);
    c1->SetBottomMargin(0.13);
    TCanvas *c2 = new TCanvas("c2", "", 950, 950);
    c2->SetTopMargin(0.02);
    c2->SetRightMargin(0.02);
    c2->SetLeftMargin(0.13);
    c2->SetBottomMargin(0.13);
    
    TGraphErrors *gr_sigmRecon = new TGraphErrors();
    TGraphErrors *gr_sigmScSmRecon = new TGraphErrors();
    TGraphErrors *gr_sigmReconSimpleScale = new TGraphErrors();

    TGraphErrors *gr_sigmReconLowMass = new TGraphErrors();
    TGraphErrors *gr_sigmScSmReconLowMass = new TGraphErrors();
    TGraphErrors *gr_sigmReconSimpleScaleLowMass = new TGraphErrors();

    // =======================================================================
    // ===== Getting Moeller Resolutions
    // =======================================================================

    TFile *file_Mlr_MC = new TFile("MoellerAnalyze_MC.root", "Read");
    TH1D *h_Moeller_M_Recon = (TH1D*) file_Mlr_MC->Get("h_TCM4");
    h_Moeller_M_Recon->SetTitle("; M(ee) [GeV]");

    c1->cd();
    h_Moeller_M_Recon->Draw();
    double meanMlrMC = h_Moeller_M_Recon->GetMean();
    double rmsMlrMC = h_Moeller_M_Recon->GetRMS();
    f_Gaus->SetParameters(h_Moeller_M_Recon->GetMaximum(), 0.0488, 0.001);

    h_Moeller_M_Recon->Fit(f_Gaus, "MeV", "", meanMlrMC - 1.2 * rmsMlrMC, meanMlrMC + 1.5 * rmsMlrMC);
    meanMlrMC = f_Gaus->GetParameter(1);
    double meanErrMlrMC = f_Gaus->GetParError(1);
    double sigmMlrMC = f_Gaus->GetParameter(2);
    double sigmMlrMC_Err = f_Gaus->GetParError(2);
    double chi2Mlr_MC = f_Gaus->GetChisquare();
    double ndfMlr_MC = f_Gaus->GetNDF();

    lat1->DrawLatex(0.6, 0.85, Form("#mu = %1.3f #pm %1.4f MeV", 1000. * meanMlrMC, 1000. * meanErrMlrMC));
    lat1->DrawLatex(0.6, 0.8, Form("#sigma = %1.3f #pm %1.4f MeV", 1000. * sigmMlrMC, 1000. * sigmMlrMC_Err));
    lat1->DrawLatex(0.6, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2Mlr_MC / ndfMlr_MC));

    c1->Print("Figs/Mlr_RecMassFit_MC.eps");
    c1->Print("Figs/Mlr_RecMassFit_MC.pdf");
    c1->Print("Figs/Mlr_RecMassFit_MC.png");

    TGraphErrors *gr_Mlr_MC_Rec = new TGraphErrors();
    gr_Mlr_MC_Rec->SetPoint(0, meanMlrMC, sigmMlrMC);
    gr_Mlr_MC_Rec->SetPointError(0, meanErrMlrMC, sigmMlrMC_Err);
    gr_Mlr_MC_Rec->SetMarkerColor(95);
    gr_Mlr_MC_Rec->SetMarkerStyle(29);
    gr_Mlr_MC_Rec->SetMarkerSize(3.5);

    TH1D *h_Moeller_MCScSm_Recon = (TH1D*) file_Mlr_MC->Get("h_TCM_ScSm4");
    h_Moeller_MCScSm_Recon->SetTitle("; M(ee) [GeV]");

    MakeHistStyle(h_Moeller_MCScSm_Recon);
    h_Moeller_MCScSm_Recon->Draw();
    double meanMlrMCScSm = h_Moeller_MCScSm_Recon->GetMean();
    double rmsMlrMCScSm = h_Moeller_MCScSm_Recon->GetRMS();
    f_Gaus->SetParameters(h_Moeller_MCScSm_Recon->GetMaximum(), 0.0488, 0.002);
    h_Moeller_MCScSm_Recon->Fit(f_Gaus, "MeV", "", meanMlrMCScSm - 4. * rmsMlrMCScSm, meanMlrMCScSm + 4 * rmsMlrMCScSm);
    meanMlrMCScSm = f_Gaus->GetParameter(1);
    double meanErrMlrMCScSm = f_Gaus->GetParError(1);
    double sigmMlrMCScSm = f_Gaus->GetParameter(2);
    double sigmMlrMCScSm_Err = f_Gaus->GetParError(2);
    double chi2Mlr_MCScSm = f_Gaus->GetChisquare();
    double ndfMlr_MCScSm = f_Gaus->GetNDF();
    lat1->DrawLatex(0.7, 0.92, "#bf{#it{HPS} internal}");
    lat1->DrawLatex(0.58, 0.85, Form("#mu = %1.3f #pm %1.3f MeV", 1000. * meanMlrMCScSm, 1000. * meanErrMlrMCScSm));
    lat1->DrawLatex(0.58, 0.8, Form("#sigma = %1.3f #pm %1.3f MeV", 1000. * sigmMlrMCScSm, 1000. * sigmMlrMCScSm_Err));
    lat1->DrawLatex(0.58, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2Mlr_MCScSm / ndfMlr_MCScSm));

    c1->Print("Figs/Mlr_RecMassScSmFit_MC.eps");
    c1->Print("Figs/Mlr_RecMassScSmFit_MC.pdf");
    c1->Print("Figs/Mlr_RecMassScSmFit_MC.png");

    TGraphErrors *gr_Mlr_MC_RecScSm = new TGraphErrors();
    gr_Mlr_MC_RecScSm->SetPoint(0, meanMlrMCScSm, sigmMlrMCScSm);
    gr_Mlr_MC_RecScSm->SetPointError(0, meanErrMlrMCScSm, sigmMlrMCScSm_Err);
    gr_Mlr_MC_RecScSm->SetMarkerColor(95);
    gr_Mlr_MC_RecScSm->SetMarkerStyle(30);
    gr_Mlr_MC_RecScSm->SetMarkerSize(3.5);



    TFile *file_Mlr_Data = new TFile("MoellerAnalyze_Data.root", "Read");
    TH1D *h_Moeller_DataScSm_Recon = (TH1D*) file_Mlr_Data->Get("h_TCM_ScSm4");
    h_Moeller_DataScSm_Recon->SetTitle("; M(ee) [GeV]");
    MakeHistStyle(h_Moeller_DataScSm_Recon);
    h_Moeller_DataScSm_Recon->Draw();
    double meanMlrDataScSm = h_Moeller_DataScSm_Recon->GetMean();
    double rmsMlrDataScSm = h_Moeller_DataScSm_Recon->GetRMS();
    f_Gaus->SetParameters(h_Moeller_DataScSm_Recon->GetMaximum(), 0.0488, 0.002);

    h_Moeller_DataScSm_Recon->Fit(f_Gaus, "MeV", "", meanMlrDataScSm - 1.5 * rmsMlrDataScSm, meanMlrDataScSm + 1.25 * rmsMlrDataScSm);
    meanMlrDataScSm = f_Gaus->GetParameter(1);
    double meanErrMlrDataScSm = f_Gaus->GetParError(1);
    double sigmMlrDataScSm = f_Gaus->GetParameter(2);
    double sigmMlrDataScSm_Err = f_Gaus->GetParError(2);
    double chi2Mlr_DataScSm = f_Gaus->GetChisquare();
    double ndfMlr_DataScSm = f_Gaus->GetNDF();
    lat1->DrawLatex(0.7, 0.92, "#bf{#it{HPS} internal}");
    lat1->DrawLatex(0.58, 0.85, Form("#mu = %1.3f #pm %1.3f MeV", 1000. * meanMlrDataScSm, 1000. * meanErrMlrDataScSm));
    lat1->DrawLatex(0.58, 0.8, Form("#sigma = %1.3f #pm %1.3f MeV", 1000. * sigmMlrDataScSm, 1000. * sigmMlrDataScSm_Err));
    lat1->DrawLatex(0.58, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2Mlr_DataScSm / ndfMlr_DataScSm));

    c1->Print("Figs/Mlr_RecMassScSmFit_Data.eps");
    c1->Print("Figs/Mlr_RecMassScSmFit_Data.pdf");
    c1->Print("Figs/Mlr_RecMassScSmFit_Data.png");

    double MCMlrRatio = sigmMlrDataScSm / sigmMlrMC;


    TGraphErrors *gr_Mlr_Data_Rec = new TGraphErrors();
    gr_Mlr_Data_Rec->SetPoint(0, meanMlrDataScSm, sigmMlrDataScSm);
    gr_Mlr_Data_Rec->SetPointError(0, meanErrMlrDataScSm, sigmMlrDataScSm_Err);
    gr_Mlr_Data_Rec->SetMarkerColor(38);
    gr_Mlr_Data_Rec->SetMarkerStyle(33);
    gr_Mlr_Data_Rec->SetMarkerSize(3.5);


    const int nMasses = 20;
    int masses[nMasses] = {50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 120, 125, 130, 135, 140, 145, 175};

    const int nLowMass = 4;
    const double lowMassLim = 49.5;
    int lowmassesp[nLowMass] = {30, 35, 40, 45};

    c1->SetLeftMargin(0.15);
    c2->SetLeftMargin(0.15);
    c1->Print("Figs/RecMassFits.pdf[");
    c2->Print("Figs/RecMassScSmFits.pdf[");
    double histMax = 0;
    for (int im = 0; im < nMasses; im++) {
        TFile *curFile = new TFile(Form("EventSelection_Ap_%d_MeV.root", masses[im]), "Read");

        TH1D *h_ReconMass = (TH1D*) curFile->Get("h_Minv_GeneralLargeBins_Final_1");
        MakeHistStyle(h_ReconMass);
        h_ReconMass->SetTitle("; M(e^{-}e^{+}) [GeV]");
        h_ReconMass->SetTitle("; M(ee) [GeV]");

        histMax = TMath::Max(histMax, h_ReconMass->GetMaximum());

        h_ReconMass->SetLineColor(2);
        TH1D *h_ReconMassScSm = (TH1D*) curFile->Get("h_MinvScSm_GeneralLargeBins_Final_1");
        h_ReconMassScSm->SetTitle("; M(ee) [GeV]");
        MakeHistStyle(h_ReconMassScSm);
        c0->cd();
        if (im % 2 == 0) {
            if (im == 0) {
                h_ReconMass->SetMaximum(2.3 * h_ReconMass->GetMaximum());
                h_ReconMass->SetAxisRange(0.03, 0.19);
                h_ReconMass->DrawCopy("");
            } else {
                h_ReconMass->DrawCopy("Same");
            }
            h_ReconMassScSm->DrawCopy("Same");
        }


        c1->cd();

        double RmsRec = h_ReconMass->GetRMS();
        double xMax = h_ReconMass->GetBinCenter(h_ReconMass->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMass->GetBinContent(h_ReconMass->GetMaximumBin()), xMax, RmsRec);

        //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
        h_ReconMass->SetAxisRange(xMax - 0.03, xMax + 0.03);

        h_ReconMass->Fit(f_Gaus, "MeV", "", xMax - 1.2 * RmsRec, xMax + 1.6 * RmsRec);
        double mean = f_Gaus->GetParameter(1);
        double sigm = f_Gaus->GetParameter(2);
        double sigmErr = f_Gaus->GetParError(2);
        double chi2 = f_Gaus->GetChisquare();
        double ndf = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(masses[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * mean));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigm));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2 / ndf));

        gr_sigmRecon->SetPoint(im, mean, sigm);
        gr_sigmRecon->SetPointError(im, 0., sigmErr);
        gr_sigmReconSimpleScale->SetPoint(im, mean, sigm * MCMlrRatio);
        gr_sigmReconSimpleScale->SetPointError(im, 0., sigmErr * MCMlrRatio);

        c1->Print("Figs/RecMassFits.pdf");

        c2->cd();

        h_ReconMassScSm->Draw();

        RmsRec = h_ReconMassScSm->GetRMS();
        xMax = h_ReconMassScSm->GetBinCenter(h_ReconMassScSm->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMassScSm->GetMaximum(), xMax, RmsRec);

        //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
        h_ReconMassScSm->SetAxisRange(xMax - 0.03, xMax + 0.03);

        h_ReconMassScSm->Fit(f_Gaus, "MeV", "", xMax - 2.2 * RmsRec, xMax + 2.6 * RmsRec);
        double meanScSm = f_Gaus->GetParameter(1);
        double sigmScSm = f_Gaus->GetParameter(2);
        double sigmScSmErr = f_Gaus->GetParError(2);
        double chi2ScSm = f_Gaus->GetChisquare();
        double ndfScSm = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(masses[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * meanScSm));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigmScSm));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2ScSm / ndfScSm));
        c2->Print("Figs/RecMassScSmFits.pdf");

        gr_sigmScSmRecon->SetPoint(im, meanScSm, sigmScSm);
        gr_sigmScSmRecon->SetPointError(im, 0., sigmScSmErr);

        curFile->Close();
    }

    c1->Print("Figs/RecMassFits.pdf]");
    c2->Print("Figs/RecMassScSmFits.pdf]");

    c0->Print("Figs/MassesTogether.eps");
    c0->Print("Figs/MassesTogether.pdf");
    c0->Print("Figs/MassesTogether.png");


    c1->Print("Figs/RecLowMassFits.pdf[");
    c2->Print("Figs/RecLowMassScSmFits.pdf[");

    for (int im = 0; im < nLowMass; im++) {
        TFile *curFile = new TFile(Form("EventSelection_Ap_%d_MeV.root", lowmassesp[im]), "Read");

        TH1D *h_ReconMass = (TH1D*) curFile->Get("h_Minv_GeneralLargeBins_Final_1");
        h_ReconMass->SetTitle("; M(e^{-}e^{+}) [GeV]");
        h_ReconMass->SetTitle("; M(ee) [GeV]");

        histMax = TMath::Max(histMax, h_ReconMass->GetMaximum());

        h_ReconMass->SetLineColor(2);
        TH1D *h_ReconMassScSm = (TH1D*) curFile->Get("h_MinvScSm_GeneralLargeBins_Final_1");
        h_ReconMassScSm->SetTitle("; M(ee) [GeV]");

        c1->cd();

        double RmsRec = h_ReconMass->GetRMS();
        double xMax = h_ReconMass->GetBinCenter(h_ReconMass->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMass->GetBinContent(h_ReconMass->GetMaximumBin()), xMax, 0.5 * RmsRec);

        //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
        h_ReconMass->SetAxisRange(xMax - 0.03, xMax + 0.03);
        h_ReconMass->Draw();
        h_ReconMass->Fit(f_Gaus, "MeV", "", xMax - 1.2 * RmsRec, xMax + 1.6 * RmsRec);
        double mean = f_Gaus->GetParameter(1);
        double sigm = f_Gaus->GetParameter(2);
        double sigmErr = f_Gaus->GetParError(2);
        double chi2 = f_Gaus->GetChisquare();
        double ndf = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(lowmassesp[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * mean));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigm));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2 / ndf));

        gr_sigmReconLowMass->SetPoint(im, mean, sigm);
        gr_sigmReconLowMass->SetPointError(im, 0., sigmErr);
        gr_sigmReconSimpleScaleLowMass->SetPoint(im, mean, sigm * MCMlrRatio);
        gr_sigmReconSimpleScaleLowMass->SetPointError(im, 0., sigmErr * MCMlrRatio);

        c1->Print("Figs/RecLowMassFits.pdf");

        //

        c2->cd();
        h_ReconMassScSm->Draw();

        RmsRec = h_ReconMassScSm->GetRMS();
        xMax = h_ReconMassScSm->GetBinCenter(h_ReconMassScSm->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMassScSm->GetMaximum(), xMax, 0.5 * RmsRec);

        //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
        h_ReconMassScSm->SetAxisRange(xMax - 0.03, xMax + 0.03);

        h_ReconMassScSm->Fit(f_Gaus, "MeV", "", xMax - 2.2 * RmsRec, xMax + 2.6 * RmsRec);
        double meanScSm = f_Gaus->GetParameter(1);
        double sigmScSm = f_Gaus->GetParameter(2);
        double sigmScSmErr = f_Gaus->GetParError(2);
        double chi2ScSm = f_Gaus->GetChisquare();
        double ndfScSm = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(lowmassesp[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * meanScSm));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigmScSm));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2ScSm / ndfScSm));
        c2->Print("Figs/RecLowMassScSmFits.pdf");

        gr_sigmScSmReconLowMass->SetPoint(im, meanScSm, sigmScSm);
        gr_sigmScSmReconLowMass->SetPointError(im, 0., sigmScSmErr);

        curFile->Close();


    }

    c1->Print("Figs/RecLowMassFits.pdf]");
    c2->Print("Figs/RecLowMassScSmFits.pdf]");

    c0->Clear();
    c0->SetRightMargin(0.01);
    c0->SetBottomMargin(0.12);

    gr_sigmRecon->SetMarkerColor(2);
    gr_sigmRecon->SetMarkerStyle(20);
    gr_sigmRecon->SetMarkerSize(3.1);
    gr_sigmReconSimpleScale->SetMarkerColor(2);
    gr_sigmReconSimpleScale->SetMarkerStyle(24);
    gr_sigmReconSimpleScale->SetMarkerSize(3.1);
    gr_sigmScSmRecon->SetMarkerColor(4);
    gr_sigmScSmRecon->SetMarkerStyle(21);
    gr_sigmScSmRecon->SetMarkerSize(3.1);

    gr_sigmReconLowMass->SetMarkerColor(2);
    gr_sigmReconLowMass->SetMarkerStyle(34);
    gr_sigmReconLowMass->SetMarkerSize(3.1);
    gr_sigmReconSimpleScaleLowMass->SetMarkerColor(2);
    gr_sigmReconSimpleScaleLowMass->SetMarkerStyle(28);
    gr_sigmReconSimpleScaleLowMass->SetMarkerSize(3.1);

    gr_sigmScSmReconLowMass->SetMarkerColor(4);
    gr_sigmScSmReconLowMass->SetMarkerStyle(41);
    gr_sigmScSmReconLowMass->SetMarkerSize(3.1);

    TF1 *f_Pol4 = new TF1("f_Pol4", "pol4", 0., 0.25);
    f_Pol4->SetNpx(4500);

    TLegend *leg1 = new TLegend(0.11, 0.52, 0.42, 0.98);
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->AddEntry(gr_sigmRecon, "A'");
    leg1->AddEntry(gr_sigmScSmRecon, "A' Smeared");
    leg1->AddEntry(gr_sigmReconSimpleScale, "A' Scaled by M#oslashller Ratio");
    leg1->AddEntry(gr_Mlr_Data_Rec, "Moeller: Data");
    leg1->AddEntry(gr_Mlr_MC_Rec, "Moeller: MC");
    leg1->AddEntry(gr_Mlr_MC_RecScSm, "Moeller: MC Smeared");
    leg1->AddEntry(gr_sigmReconLowMass, "low mass A'");
    leg1->AddEntry(gr_sigmReconSimpleScaleLowMass, "Low mass A': scaled by M#oslashller Ratio");
    leg1->AddEntry(gr_sigmScSmReconLowMass, "low mass A': smeared");

    TMultiGraph *mtgr1 = new TMultiGraph();
    mtgr1->Add(gr_sigmRecon);
    mtgr1->Add(gr_sigmScSmRecon);
    mtgr1->Add(gr_sigmReconSimpleScale);
    mtgr1->Add(gr_Mlr_Data_Rec);
    mtgr1->Add(gr_Mlr_MC_Rec);
    mtgr1->Add(gr_Mlr_MC_RecScSm);
    mtgr1->Add(gr_sigmReconLowMass);
    mtgr1->Add(gr_sigmReconSimpleScaleLowMass);
    mtgr1->Add(gr_sigmScSmReconLowMass);

    mtgr1->Draw("AP");
    mtgr1->SetTitle("; M(ee) [GeV]; #sigma [GeV]");
    mtgr1->SetMinimum(0.);
    mtgr1->GetYaxis()->SetTitleOffset(1.);
    mtgr1->GetYaxis()->SetTitleSize(0.05);
    mtgr1->GetYaxis()->SetLabelSize(0.05);
    mtgr1->GetXaxis()->SetTitleSize(0.05);
    mtgr1->GetXaxis()->SetLabelSize(0.05);
    gr_sigmScSmRecon->Fit(f_Pol4, "MeV", "", 0.045, 0.18);
    f_Pol4->DrawCopy("Same");
    double masspars[5];
    f_Pol4->GetParameters(masspars);

    gr_sigmRecon->Fit(f_Pol4, "MeV", "", 0.045, 0.18);
    double masspars_nonsmear[5];
    f_Pol4->GetParameters(masspars_nonsmear);
    f_Pol4->DrawCopy("Same");
    leg1->Draw();
    lat1->DrawLatex(0.5, 0.9, "#it{HPS} Preliminary");
    c0->Print("Figs/MassResolVSMass.eps");
    c0->Print("Figs/MassResolVSMass.pdf");
    c0->Print("Figs/MassResolVSMass.png");

    ofstream outMassparam("MassParam.dat");

    outMassparam << "\t & \t $\\mathrm{P0\\; [GeV]}$ \t & $\\mathrm{P1}$ \t & $\\mathrm{P2\\; [GeV^{-1}]}$ \t & $\\mathrm{P3\\; [GeV^{-2}]}$ \t & $\\mathrm{P4\\; [GeV^{-3}]}$ \\\\ \\hline" << endl;
    outMassparam << "smear value & " << masspars[0] << " & " << masspars[1] << " & " << masspars[2] << " & " << masspars[3] << " & " << masspars[4] << " \\\\ \\hline " << endl;
    outMassparam << "Nonsmear & " << masspars_nonsmear[0] << " & " << masspars_nonsmear[1] << " & " << masspars_nonsmear[2] << " & " << masspars_nonsmear[3]
            << " & " << masspars_nonsmear[4] << " \\\\ \\hline " << endl;


    WriteMlrResol(gr_Mlr_Data_Rec, gr_Mlr_MC_Rec, gr_Mlr_MC_RecScSm);
    WriteApResol(gr_sigmScSmRecon, "ScSm", masses);
    WriteApResol(gr_sigmRecon, "NoSmear", masses);
    WriteApResol(gr_sigmReconSimpleScale, "SimpleScale", masses);
    WriteApResol(gr_sigmReconLowMass, "NoSmearLowMass", lowmassesp);
    WriteApResol(gr_sigmReconSimpleScaleLowMass, "SimpleScaleLowMass", lowmassesp);
    WriteApResol(gr_sigmScSmReconLowMass, "ScSmLowMass", lowmassesp);
    /*
        c0->Clear();

        gr_sigmScSmRecon->Draw("AP");

        for (int i = 0; i < 6; i++) {

            TF1 *ftmp = new TF1(Form("f_Pol%d", i + 1), Form("pol%d", i + 1), 0.03, 0.18);

            int col = i + 1;
            ftmp->SetLineColor(col);
            gr_sigmScSmRecon->Fit(ftmp, "MeV", "", 0.045, 0.178);
            ftmp->DrawCopy("Same");
            double chi2 = ftmp->GetChisquare();
            double ndf = ftmp->GetNDF();
            lat1->SetTextColor(col);
            lat1->DrawLatex(0.18, 0.9 - 0.05 * i, Form("Pol%d #chi^{2}/NDF = %1.3f", i + 1, chi2 / ndf));
        }
        f_Gaus->SetParameters(8.92555e-03, 2.32513e-01, 1.08321e-01);
        f_Gaus->SetLineColor(7);
        gr_sigmScSmRecon->Fit(f_Gaus, "MeV", "", 0.045, 0.178);
        double chi2 = f_Gaus->GetChisquare();
        double ndf = f_Gaus->GetNDF();
        lat1->SetTextColor(7);
        lat1->DrawLatex(0.18, 0.6, Form("Gaus #chi^{2}/NDF = %1.3f",  chi2 / ndf));
     */
    return 0;
}

void WriteMlrResol(TGraphErrors *gr_MlrData, TGraphErrors *gr_MlrMC, TGraphErrors *gr_MlrMCScSm) {

    ofstream out("Mlr_MassResol.dat");

    double x_Data, y_Data, x_err_Data, y_err_Data;
    double x_MC, y_MC, x_err_MC, y_err_MC;
    double x_MCScSm, y_MCScSm, x_err_MCScSm, y_err_MCScSm;

    gr_MlrData->GetPoint(0, x_Data, y_Data);
    y_err_Data = gr_MlrData->GetErrorY(0);
    gr_MlrMC->GetPoint(0, x_MC, y_MC);
    y_err_MC = gr_MlrMC->GetErrorY(0);
    gr_MlrMCScSm->GetPoint(0, x_MCScSm, y_MCScSm);
    y_err_MCScSm = gr_MlrMCScSm->GetErrorY(0);

    out << "  & $\\mathrm{ \\mu \\;[MeV] } $ & $\\mathrm{ \\sigma\\; [MeV] } $ & $\\mathrm{ \\sigma err \\;[MeV] } $ \\\\ \\hline " << endl;
    out << " Data  & " << x_Data * 1000. << "   &   " << y_Data * 1000. << "   &   " << y_err_Data * 1000. << "  \\\\ \\hline" << endl;
    out << " MC unsmeared  & " << x_MC * 1000. << "   &   " << y_MC * 1000. << "   &   " << y_err_MC * 1000. << "  \\\\ \\hline" << endl;
    out << " MC smeared  & " << x_MCScSm * 1000. << "   &   " << y_MCScSm * 1000. << "   &   " << y_err_MCScSm * 1000. << "  \\\\ \\hline" << endl;

}

void WriteApResol(TGraphErrors *gr_Ap, std::string keyword, int* mass_Arr) {

    ofstream out(Form("Ap_Param_%s.dat", keyword.c_str()));


    out << "  & $\\mathrm{ \\mu \\;[MeV] } $ & $\\mathrm{ \\sigma\\; [MeV] } $ & $\\mathrm{ \\sigma err \\;[MeV] } $ \\\\ \\hline " << endl;

    for (int i = 0; i < gr_Ap->GetN(); i++) {
        double mean, sigm, mean_err, sigm_err;
        gr_Ap->GetPoint(i, mean, sigm);
        sigm_err = gr_Ap->GetErrorY(i);

//        out << Form("Ap %d MeV & ", mass_Arr[i]) << mean * 1000. << "   &   " << sigm * 1000. << "   &   " << sigm_err * 1000. << "\\\\ \\hline" << endl;
	out << Form("Ap %d MeV & ", mass_Arr[i]) << Form("%1.2f", mean * 1000.) << "   &   " << Form("%1.2f", sigm * 1000.) << "   &   " << Form("%1.4f",sigm_err * 1000.) << "\\\\ \\hline" << endl;
    }
}

template <typename T>
void MakeHistStyle(T *hist) {

    hist->SetTitleSize(0.05, "Y");
    hist->SetLabelSize(0.05, "Y");
    hist->SetTitleSize(0.05, "X");
    hist->SetLabelSize(0.05, "X");
}
