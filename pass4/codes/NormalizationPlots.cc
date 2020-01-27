/* 
 * File:   NormalizationPlots.cc
 * Author: rafopar
 *
 * Created on November 25, 2019, 11:21 AM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TLine.h>
#include <TFile.h>
#include <cstdlib>
#include <fstream>
#include <TMath.h>
#include <iostream>
#include <TLatex.h>
#include <TCanvas.h>
#include <TRatioPlot.h>
#include <TGraphErrors.h>
//#include "setting_2016_pass1.h"

using namespace std;


void DrawDatMCComparison(TFile** files, std::string histNameBase, std::string Title, int nDim);
void AddErrorAllBins(TH1D* h, double RelErr);

void DrawAntiFEECut(TFile** files);

void Drawd0Cut(TFile** files);

// ===== This function should return the Radiative fraction /
// ===== It should take the "CutEffect" histograms, and calculate the 
// ===== Rad Fraction as the Rad_Hist/(Wab+Tri)
double GetfRad(TFile** files, std::string histNameBase, double &fRad_Err);

const double tritrig_SigmaGen = 1.416e-3;
const double tritrig_SigmError = 0.00431e-3;
const double NGen_tritrig = 985. * 50000.; /* 200 recon files, and each recon has 50K Gen events*/

const double Rad_SigmaGen = 81.e-6;
const double Rad_SigmError = 0.834e-6;
const double NGen_Rad = 4989 * 10000.;

const double Wab_SigmaGen = 0.1985;
const double Wab_SigmError = 0.01973;
const double NGen_Wab = 9965. * 100000.;

const double Lumin8099 = 237.e9; // inverse barn

const double Pem_MaxTight_Data = 1.75;

const int nMinvBins = 12; // # of Minv bins, We want to study Psum for different Minv Bins
double MinvBins[nMinvBins + 1] = {0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24};

ofstream CutFractions;

/*
 * 
 */
void NormalizationPlots() {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);

    TFile *file_EvSelection_Data = new TFile("EventSelection_Data.root", "Read");
    TH1D *h_Psum3_Data = (TH1D*) file_EvSelection_Data->Get("h_Psum3");
    double bwPSum3 = h_Psum3_Data->GetBinWidth(10);
    h_Psum3_Data->SetLineColor(1);

    TFile *file_EvSelection_Wab = new TFile("EventSelection_WAB.root", "Read");

    TH1D *h_Psum3_Wab = (TH1D*) file_EvSelection_Wab->Get("h_Psum3");
    h_Psum3_Wab->SetTitle("; P_{Sum} [GeV]");
    h_Psum3_Wab->Scale(Wab_SigmaGen / (bwPSum3 * NGen_Wab));
    h_Psum3_Wab->SetLineColor(45);

    TFile *file_EvSelection_Rad = new TFile("EventSelection_Rad.root", "Read");

    TH1D *h_Psum3_Rad = (TH1D*) file_EvSelection_Rad->Get("h_Psum3");
    h_Psum3_Rad->SetTitle("; P_{Sum} [GeV]");
    h_Psum3_Rad->Scale(Rad_SigmaGen / (bwPSum3 * NGen_Rad));
    h_Psum3_Rad->SetLineColor(2);


    TFile *file_EvSelection_Tri = new TFile("EventSelection_Tri.root", "Read");

    TH1D *h_Psum3_Tri = (TH1D*) file_EvSelection_Tri->Get("h_Psum3");
    h_Psum3_Tri->SetTitle("; P_{Sum} [GeV]; d#sigma/d P_{Sum} [bn/GeV]");
    h_Psum3_Tri->Scale(tritrig_SigmaGen / (bwPSum3 * NGen_tritrig));
    h_Psum3_Tri->SetLineColor(4);

    h_Psum3_Tri->Draw();
    h_Psum3_Rad->Draw("Same");
    h_Psum3_Wab->Draw("Same");

    TH1D *h_PSum3_WabPlusTri = (TH1D*) h_Psum3_Tri->Clone("h_PSum3_WabPlusTri");
    h_PSum3_WabPlusTri->Add(h_Psum3_Wab);
    h_PSum3_WabPlusTri->SetLineColor(95);
    h_PSum3_WabPlusTri->Draw();
    h_Psum3_Tri->Draw("Same");
    h_Psum3_Rad->Draw("Same");
    h_Psum3_Wab->Draw("Same");
    const double DataScale = 1.32;
    h_Psum3_Data->Scale(1 / (bwPSum3 * Lumin8099));
    //h_Psum3_Data->Draw("Same");
    lat1->SetTextColor(1);
    //lat1->DrawLatex(0.3, 0.5, "Data");
    lat1->SetTextColor(95);
    lat1->DrawLatex(0.3, 0.45, "WAB + Tri");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.3, 0.4, "Tri");
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.3, 0.35, "Rad");
    lat1->SetTextColor(45);
    lat1->DrawLatex(0.3, 0.3, "Wab");
    c1->Print("Figs/PSum3_MC_Components.eps");
    c1->Print("Figs/PSum3_MC_Components.pdf");
    c1->Print("Figs/PSum3_MC_Components.png");

    TH1D *h_Psum3_Rad_Cumulative = (TH1D*) h_Psum3_Rad->GetCumulative(0);
    h_Psum3_Rad_Cumulative->Draw();

    TH1D *h_Psum3_WabPlusTrid_Cumulative = (TH1D*) h_PSum3_WabPlusTri->GetCumulative(0);
    h_Psum3_WabPlusTrid_Cumulative->Draw();


    for (int i = 0; i < h_Psum3_WabPlusTrid_Cumulative->GetNbinsX(); i++) {
        h_Psum3_WabPlusTrid_Cumulative->SetBinContent(i + 1, sqrt(h_Psum3_WabPlusTrid_Cumulative->GetBinContent(i + 1)));
    }

    TH1D *h_Psum3_FOM = (TH1D*) h_Psum3_Rad_Cumulative->Clone("h_Psum3_FOM");
    h_Psum3_FOM->Divide(h_Psum3_WabPlusTrid_Cumulative);

    h_Psum3_FOM->Draw();
    double PsumCut = h_Psum3_FOM->GetBinCenter(h_Psum3_FOM->GetMaximumBin());
    cout << "PsumCut = " << PsumCut << endl;
    line1->DrawLine(PsumCut, 0., PsumCut, h_Psum3_FOM->GetMaximum());
    lat1->DrawLatex(0.15, 0.4, Form("P_{sum} > %1.2f", PsumCut));
    c1->Print("Figs/PSum3_FOM.eps");
    c1->Print("Figs/PSum3_FOM.pdf");
    c1->Print("Figs/PSum3_FOM.png");

    TFile * files_EvSelection[5] = {file_EvSelection_Data, file_EvSelection_Tri, file_EvSelection_Rad, file_EvSelection_Wab};

    CutFractions.open("CutPowers.dat", ios::out);

    const int nMinvBins = 12;

    DrawDatMCComparison(files_EvSelection, "PsumMax", "; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PsumMin", "; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "clDt", "; Cluster #Delta t [ns]; d#sigma/d #Delta t [bn/ns] ", 1);
    DrawDatMCComparison(files_EvSelection, "Pem", "; P_{e^{-}} [GeV]; d#sigma/d P_{e^{-}} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "d0_ep", "; d_{0}(e^{+}) [mm]; d#sigma/d d_{0}(e^{+}) [bn/mm] ", 1);
    DrawDatMCComparison(files_EvSelection, "em_cl_trk_dT", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "ep_cl_trk_dT", "; P_{e^{+}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_em", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_ep", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);

    double MinvBins[nMinvBins + 1] = {0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24};
    for (int i = 0; i < nMinvBins; i++) {
        DrawDatMCComparison(files_EvSelection, Form("PSumMin_MinvBin_%d", i),
                Form("%1.3f GeV < M(ee) < %1.3f GeV; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV]", MinvBins[i], MinvBins[i + 1]), 1);
    }



    DrawAntiFEECut(files_EvSelection);
    Drawd0Cut(files_EvSelection);
    // ========== Getting the Rad Fraction ===========

    TGraphErrors *gr_fRad = new TGraphErrors();
    gr_fRad->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");

    for (int i = 0; i < nMinvBins; i++) {
        double fRadErr;
        double fRad = GetfRad(files_EvSelection, Form("PSumMin_MinvBin_%d", i), fRadErr);

        double MinvVal = (MinvBins[i] + MinvBins[i + 1]) / 2.;
        gr_fRad->SetPoint(i, MinvVal, fRad);
        gr_fRad->SetPointError(i, 0., fRadErr);
    }

    c1->cd()->SetLeftMargin(0.12);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.03);
    gr_fRad->SetMarkerColor(4);
    gr_fRad->SetMarkerStyle(29);
    gr_fRad->Draw("AP");
    c1->Print("Figs/fRad_MassBins.eps");
    c1->Print("Figs/fRad_MassBins.pdf");
    c1->Print("Figs/fRad_MassBins.png");

}

void DrawDatMCComparison(TFile** files, std::string histNameBase, std::string Title, int nDim) {

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TFile *file_Data = files[0];
    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];


    if (nDim == 1) {
        TCanvas *c1D = new TCanvas("c1D", "", 950, 950);
        c1D->SetLeftMargin(0.15);
        c1D->SetRightMargin(0.02);

        TH1D *h_Data_All = (TH1D*) file_Data->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Data_All->Sumw2();
        h_Data_All->SetLineColor(1);
        h_Data_All->SetTitle(Title.c_str());
        h_Data_All->Scale(1. / Lumin8099);
        TH1D *h_Data_AllBut = (TH1D*) file_Data->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Data_AllBut->Sumw2();
        h_Data_AllBut->SetLineColor(1);
        h_Data_AllBut->SetTitle(Title.c_str());
        h_Data_AllBut->Scale(1. / Lumin8099);
        TH1D *h_Data_CutEffect = (TH1D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Data_CutEffect->Sumw2();
        h_Data_CutEffect->SetLineColor(1);
        h_Data_CutEffect->SetTitle(Title.c_str());
        h_Data_CutEffect->Scale(1. / Lumin8099);

        double dataFraction = h_Data_CutEffect->Integral() / h_Data_AllBut->Integral();


        TH1D *h_Tri_All = (TH1D*) file_Tri->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Tri_All->Sumw2();
        h_Tri_All->SetLineColor(4);
        h_Tri_All->SetTitle(Title.c_str());
        h_Tri_All->Scale(tritrig_SigmaGen / NGen_tritrig);
        AddErrorAllBins(h_Tri_All, tritrig_SigmError / tritrig_SigmaGen);
        TH1D *h_Tri_AllBut = (TH1D*) file_Tri->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Tri_AllBut->SetLineColor(4);
        h_Tri_AllBut->Sumw2();
        h_Tri_AllBut->SetTitle(Title.c_str());
        h_Tri_AllBut->Scale(tritrig_SigmaGen / NGen_tritrig);
        AddErrorAllBins(h_Tri_AllBut, tritrig_SigmError / tritrig_SigmaGen);
        TH1D *h_Tri_CutEffect = (TH1D*) file_Tri->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Tri_CutEffect->SetLineColor(4);
        h_Tri_CutEffect->Sumw2();
        h_Tri_CutEffect->SetTitle(Title.c_str());
        h_Tri_CutEffect->Scale(tritrig_SigmaGen / NGen_tritrig);
        AddErrorAllBins(h_Tri_CutEffect, tritrig_SigmError / tritrig_SigmaGen);

        double triFraction = h_Tri_CutEffect->Integral() / h_Tri_AllBut->Integral();

        TH1D *h_Rad_All = (TH1D*) file_Rad->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Rad_All->SetLineColor(2);
        h_Rad_All->Sumw2();
        h_Rad_All->SetTitle(Title.c_str());
        h_Rad_All->Scale(Rad_SigmaGen / NGen_Rad);
        AddErrorAllBins(h_Rad_All, Rad_SigmError / Rad_SigmaGen);
        TH1D *h_Rad_AllBut = (TH1D*) file_Rad->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Rad_AllBut->SetLineColor(2);
        h_Rad_AllBut->Sumw2();
        h_Rad_AllBut->SetTitle(Title.c_str());
        h_Rad_AllBut->Scale(Rad_SigmaGen / NGen_Rad);
        AddErrorAllBins(h_Rad_AllBut, Rad_SigmError / Rad_SigmaGen);
        TH1D *h_Rad_CutEffect = (TH1D*) file_Rad->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Rad_CutEffect->SetLineColor(2);
        h_Rad_CutEffect->Sumw2();
        h_Rad_CutEffect->SetTitle(Title.c_str());
        h_Rad_CutEffect->Scale(Rad_SigmaGen / NGen_Rad);
        AddErrorAllBins(h_Rad_CutEffect, Rad_SigmError / Rad_SigmaGen);

        double radFraction = h_Rad_CutEffect->Integral() / h_Rad_AllBut->Integral();

        TH1D *h_WAB_All = (TH1D*) file_WAB->Get(Form("h_%s_All", histNameBase.c_str()));
        h_WAB_All->SetLineColor(45);
        h_WAB_All->Sumw2();
        h_WAB_All->SetTitle(Title.c_str());
        h_WAB_All->Scale(Wab_SigmaGen / NGen_Wab);
        AddErrorAllBins(h_WAB_All, Wab_SigmError / Wab_SigmaGen);
        TH1D *h_WAB_AllBut = (TH1D*) file_WAB->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_WAB_AllBut->SetLineColor(45);
        h_WAB_AllBut->Sumw2();
        h_WAB_AllBut->SetTitle(Title.c_str());
        h_WAB_AllBut->Scale(Wab_SigmaGen / NGen_Wab);
        AddErrorAllBins(h_WAB_AllBut, Wab_SigmError / Wab_SigmaGen);
        TH1D *h_WAB_CutEffect = (TH1D*) file_WAB->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_WAB_CutEffect->SetLineColor(45);
        h_WAB_CutEffect->Sumw2();
        h_WAB_CutEffect->SetTitle(Title.c_str());
        h_WAB_CutEffect->Scale(Wab_SigmaGen / NGen_Wab);
        AddErrorAllBins(h_WAB_CutEffect, Wab_SigmError / Wab_SigmaGen);

        double wabFraction = h_WAB_CutEffect->Integral() / h_WAB_AllBut->Integral();

        TH1D *hTriPlusWab_All = (TH1D*) h_Tri_All->Clone("hTriPlusWab_All");
        hTriPlusWab_All->Add(h_WAB_All);
        hTriPlusWab_All->SetLineColor(95);
        TH1D *hTriPlusWab_AllBut = (TH1D*) h_Tri_AllBut->Clone("hTriPlusWab_AllBut");
        hTriPlusWab_AllBut->Add(h_WAB_AllBut);
        hTriPlusWab_AllBut->SetLineColor(95);
        TH1D *hTriPlusWab_CutEffect = (TH1D*) h_Tri_CutEffect->Clone("hTriPlusWab_CutEffect");
        hTriPlusWab_CutEffect->Add(h_WAB_CutEffect);
        hTriPlusWab_CutEffect->SetLineColor(95);

        double wabTriFraction = hTriPlusWab_CutEffect->Integral() / hTriPlusWab_AllBut->Integral();

        double MaxArray_All[5] = {h_Data_All->GetMaximum(), h_Tri_All->GetMaximum(), h_Rad_All->GetMaximum(), h_WAB_All->GetMaximum(), hTriPlusWab_All->GetMaximum()};
        double Max_All = TMath::MaxElement<double>(5, MaxArray_All);

        double MaxArray_AllBut[5] = {h_Data_AllBut->GetMaximum(), h_Tri_AllBut->GetMaximum(), h_Rad_AllBut->GetMaximum(), h_WAB_AllBut->GetMaximum(),
            hTriPlusWab_AllBut->GetMaximum()};
        double Max_AllBut = TMath::MaxElement<double>(5, MaxArray_AllBut);

        double MaxArray_CutEffect[5] = {h_Data_CutEffect->GetMaximum(), h_Tri_CutEffect->GetMaximum(), h_Rad_CutEffect->GetMaximum(), h_WAB_CutEffect->GetMaximum(),
            hTriPlusWab_CutEffect->GetMaximum()};
        double Max_CutEffect = TMath::MaxElement<double>(5, MaxArray_CutEffect);


        h_Data_All->SetMaximum(1.05 * Max_All);

        TRatioPlot *rp = new TRatioPlot(h_Data_All, hTriPlusWab_All, "divsym");
        rp->GetUpperPad()->SetBottomMargin(0);
        rp->GetLowerPad()->SetTopMargin(0);
        rp->Draw();
        rp->GetUpperPad()->cd();
        h_Tri_All->Draw("Same");
        h_Rad_All->Draw("Same");
        h_WAB_All->Draw("Same");
        rp->GetLowerRefGraph()->SetMaximum(1.6);
        rp->GetLowerRefGraph()->SetMinimum(0.4);
        c1D->Update();
        c1D->Print(Form("Figs/%s_All.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_All.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_All.png", histNameBase.c_str()));

        c1D->Clear();
        delete rp;

        h_Data_AllBut->SetMaximum(1.05 * Max_AllBut);
        TRatioPlot *rp2 = new TRatioPlot(h_Data_AllBut, hTriPlusWab_AllBut, "divsym");
        rp2->GetUpperPad()->SetBottomMargin(0);
        rp2->GetLowerPad()->SetTopMargin(0);
        rp2->Draw();
        rp2->GetUpperPad()->cd();
        h_Tri_AllBut->Draw("Same");
        h_Rad_AllBut->Draw("Same");
        h_WAB_AllBut->Draw("Same");
        rp2->GetLowerRefGraph()->SetMaximum(1.6);
        rp2->GetLowerRefGraph()->SetMinimum(0.4);
        c1D->Update();
        c1D->Print(Form("Figs/%s_AllBut.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.png", histNameBase.c_str()));

        c1D->Clear();
        delete rp2;

        h_Data_CutEffect->SetMaximum(1.05 * Max_AllBut);
        TRatioPlot *rp3 = new TRatioPlot(h_Data_CutEffect, hTriPlusWab_CutEffect, "divsym");
        rp3->GetUpperPad()->SetBottomMargin(0);
        rp3->GetLowerPad()->SetTopMargin(0);
        rp3->Draw();
        rp3->GetUpperPad()->cd();
        h_Tri_CutEffect->Draw("Same");
        h_Rad_CutEffect->Draw("Same");
        h_WAB_CutEffect->Draw("Same");
        rp2->GetLowerRefGraph()->SetMaximum(1.6);
        rp2->GetLowerRefGraph()->SetMinimum(0.4);
        c1D->Update();
        c1D->Print(Form("Figs/%s_CutEffect.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.png", histNameBase.c_str()));

        c1D->Clear();
        delete rp3;

        CutFractions << setw(25) << histNameBase << setw(12) << " & " << dataFraction << setw(12) << " & " << triFraction << setw(12) << " & " << radFraction << setw(12) << " & " << wabFraction
                << setw(12) << " & " << wabTriFraction << " \\\\ \\hline" << endl;


        delete h_Data_All;
        delete h_Data_AllBut;
        delete h_Data_CutEffect;
        delete h_Tri_All;
        delete h_Tri_AllBut;
        delete h_Tri_CutEffect;
        delete h_Rad_All;
        delete h_Rad_AllBut;
        delete h_Rad_CutEffect;
        delete h_WAB_All;
        delete h_WAB_AllBut;
        delete h_WAB_CutEffect;
        delete hTriPlusWab_All;
        delete hTriPlusWab_AllBut;
        delete hTriPlusWab_CutEffect;

    } else if (nDim == 2) {

        TCanvas *c2D = new TCanvas("c1D", "", 950, 950);
        c2D->SetLeftMargin(0.15);
        c2D->SetLogz();

        TH2D *h_Data_All = (TH2D*) file_Data->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Data_All->Sumw2();
        h_Data_All->SetTitle(Title.c_str());
        h_Data_All->Scale(1 / Lumin8099);
        h_Data_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_All.png", histNameBase.c_str()));

        TH2D *h_Data_AllBut = (TH2D*) file_Data->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Data_AllBut->Sumw2();
        h_Data_AllBut->SetTitle(Title.c_str());
        h_Data_AllBut->Scale(1 / Lumin8099);
        h_Data_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_AllBut.png", histNameBase.c_str()));

        TH2D *h_Data_CutEffect = (TH2D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Data_CutEffect->Sumw2();
        h_Data_CutEffect->SetTitle(Title.c_str());
        h_Data_CutEffect->Scale(1 / Lumin8099);
        h_Data_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_CutEffect.png", histNameBase.c_str()));

        double dataFraction = h_Data_CutEffect->Integral() / h_Data_AllBut->Integral();

        TH2D *h_Tri_All = (TH2D*) file_Tri->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Tri_All->Sumw2();
        h_Tri_All->SetTitle(Title.c_str());
        h_Tri_All->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_All.png", histNameBase.c_str()));

        TH2D *h_Tri_AllBut = (TH2D*) file_Tri->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Tri_AllBut->Sumw2();
        h_Tri_AllBut->SetTitle(Title.c_str());
        h_Tri_AllBut->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_AllBut.png", histNameBase.c_str()));

        TH2D *h_Tri_CutEffect = (TH2D*) file_Tri->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Tri_CutEffect->Sumw2();
        h_Tri_CutEffect->SetTitle(Title.c_str());
        h_Tri_CutEffect->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_CutEffect.png", histNameBase.c_str()));

        double triFraction = h_Tri_CutEffect->Integral() / h_Tri_AllBut->Integral();

        TH2D *h_Rad_All = (TH2D*) file_Rad->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Rad_All->Sumw2();
        h_Rad_All->SetTitle(Title.c_str());
        h_Rad_All->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_All.png", histNameBase.c_str()));

        TH2D *h_Rad_AllBut = (TH2D*) file_Rad->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Rad_AllBut->Sumw2();
        h_Rad_AllBut->SetTitle(Title.c_str());
        h_Rad_AllBut->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_AllBut.png", histNameBase.c_str()));

        TH2D *h_Rad_CutEffect = (TH2D*) file_Rad->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Rad_CutEffect->Sumw2();
        h_Rad_CutEffect->SetTitle(Title.c_str());
        h_Rad_CutEffect->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_CutEffect.png", histNameBase.c_str()));

        double radFraction = h_Rad_CutEffect->Integral() / h_Rad_AllBut->Integral();

        TH2D *h_WAB_All = (TH2D*) file_WAB->Get(Form("h_%s_All", histNameBase.c_str()));
        h_WAB_All->Sumw2();
        h_WAB_All->SetTitle(Title.c_str());
        h_WAB_All->Scale(Wab_SigmaGen / NGen_Wab);
        h_WAB_All->Draw("colz");
        c2D->Print(Form("Figs/%s_WAB_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_All.png", histNameBase.c_str()));

        TH2D *h_WAB_AllBut = (TH2D*) file_WAB->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_WAB_AllBut->Sumw2();
        h_WAB_AllBut->SetTitle(Title.c_str());
        h_WAB_AllBut->Scale(Wab_SigmaGen / NGen_Wab);
        h_WAB_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_WAB_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_AllBut.png", histNameBase.c_str()));

        TH2D *h_WAB_CutEffect = (TH2D*) file_WAB->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_WAB_CutEffect->Sumw2();
        h_WAB_CutEffect->SetTitle(Title.c_str());
        h_WAB_CutEffect->Scale(Wab_SigmaGen / NGen_Wab);
        h_WAB_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_WAB_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_CutEffect.png", histNameBase.c_str()));

        double wabFraction = h_WAB_CutEffect->Integral() / h_WAB_AllBut->Integral();

        TH2D *hTriPlusWab_All = (TH2D*) h_Tri_All->Clone("hTriPlusWab_All");
        hTriPlusWab_All->Add(h_WAB_All);
        TH2D *hTriPlusWab_AllBut = (TH2D*) h_Tri_AllBut->Clone("hTriPlusWab_AllBut");
        hTriPlusWab_AllBut->Add(h_WAB_AllBut);
        TH2D *hTriPlusWab_CutEffect = (TH2D*) h_Tri_CutEffect->Clone("hTriPlusWab_CutEffect");
        hTriPlusWab_CutEffect->Add(h_WAB_CutEffect);

        double wabTriFraction = hTriPlusWab_CutEffect->Integral() / hTriPlusWab_AllBut->Integral();

        CutFractions << setw(25) << histNameBase << setw(12) << " & " << dataFraction << setw(12) << " & " << triFraction << setw(12) << " & " << radFraction << setw(12) << " & " << wabFraction
                << setw(12) << " & " << wabTriFraction << " \\\\ \\hline" << endl;


        delete h_Data_All;
        delete h_Data_AllBut;
        delete h_Data_CutEffect;
        delete h_Tri_All;
        delete h_Tri_AllBut;
        delete h_Tri_CutEffect;
        delete h_Rad_All;
        delete h_Rad_AllBut;
        delete h_Rad_CutEffect;
        delete h_WAB_All;
        delete h_WAB_AllBut;
        delete h_WAB_CutEffect;
        delete hTriPlusWab_All;
        delete hTriPlusWab_AllBut;
        delete hTriPlusWab_CutEffect;
    }



}

void AddErrorAllBins(TH1D* h, double RelErr) {

    for (int i = 0; i < h->GetNbinsX(); i++) {

        double cur_err = h->GetBinError(i + 1);
        double binCont = h->GetBinContent(i + 1);
        h->SetBinError(i + 1, sqrt(cur_err * cur_err + binCont * binCont * RelErr * RelErr));
    }

}

double GetfRad(TFile** files, std::string histNameBase, double &fRad_Err) {

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TFile *file_Data = files[0];
    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];


    TH1D *h_Data_CutEffect = (TH1D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
    h_Data_CutEffect->Sumw2();
    h_Data_CutEffect->Scale(1 / Lumin8099);

    TH1D *h_Tri_CutEffect = (TH1D*) file_Tri->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
    h_Tri_CutEffect->Sumw2();
    h_Tri_CutEffect->Scale(tritrig_SigmaGen / NGen_tritrig);
    AddErrorAllBins(h_Tri_CutEffect, tritrig_SigmError / tritrig_SigmaGen);

    TH1D *h_Rad_CutEffect = (TH1D*) file_Rad->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
    h_Rad_CutEffect->Sumw2();
    h_Rad_CutEffect->Scale(Rad_SigmaGen / NGen_Rad);
    AddErrorAllBins(h_Rad_CutEffect, Rad_SigmError / Rad_SigmaGen);

    TH1D *h_WAB_CutEffect = (TH1D*) file_WAB->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
    h_WAB_CutEffect->Sumw2();
    h_WAB_CutEffect->Scale(Wab_SigmaGen / NGen_Wab);
    AddErrorAllBins(h_WAB_CutEffect, Wab_SigmError / Wab_SigmaGen);

    TH1D *hTriPlusWab_CutEffect = (TH1D*) h_Tri_CutEffect->Clone("hTriPlusWab_CutEffect");
    hTriPlusWab_CutEffect->Add(h_WAB_CutEffect);

    double err_Rad;
    double err_TriWAB;

    double Integr_Rad = h_Rad_CutEffect->IntegralAndError(1, h_Rad_CutEffect->GetNbinsX(), err_Rad);
    double Integr_TriWAB = hTriPlusWab_CutEffect->IntegralAndError(1, hTriPlusWab_CutEffect->GetNbinsX(), err_TriWAB);

    double fRad = Integr_Rad / Integr_TriWAB;

    fRad_Err = fRad * sqrt((err_Rad / Integr_Rad)*(err_Rad / Integr_Rad) + (err_TriWAB / Integr_TriWAB)*(err_TriWAB / Integr_TriWAB));


    if (isnan(fRad)) {
        fRad = 0.;
        fRad_Err = 0.;
    }


    return fRad;

}

void DrawAntiFEECut(TFile** files) {

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TCanvas *ctmp = new TCanvas("ctmp", "", 950, 950);

    TFile *file_Data = files[0];
    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];

    TH1D *h_Pem_All_Data = (TH1D*) file_Data->Get("h_Pem_All");
    TH1D *h_Pem_All_Tri = (TH1D*) file_Tri->Get("h_Pem_All");
    TH1D *h_Pem_All_Rad = (TH1D*) file_Rad->Get("h_Pem_All");
    TH1D *h_Pem_All_WAB = (TH1D*) file_WAB->Get("h_Pem_All");

    double bw = h_Pem_All_Data->GetBinWidth(10);

    h_Pem_All_Data->Scale(1 / (bw * Lumin8099));
    h_Pem_All_Data->SetLineColor(1);
    h_Pem_All_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
    h_Pem_All_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));

    TLine *line1 = new TLine();
    line1->SetLineColor(2);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    h_Pem_All_Tri->SetTitle("; P_{e^{-}} [GeV]; d#sigma/d P_{e^{-}} [bn/GeV] ");
    h_Pem_All_Tri->SetLineColor(2);
    h_Pem_All_Tri->Draw();
    h_Pem_All_Data->Draw("Same");
    h_Pem_All_Rad->Draw("Same");
    TLine *tmpLine = line1->DrawLine(Pem_MaxTight_Data, 0., Pem_MaxTight_Data, 0.25 * h_Pem_All_Tri->GetMaximum());
    int binCut = h_Pem_All_Tri->FindBin(Pem_MaxTight_Data);
    double TotData = h_Pem_All_Data->Integral();
    double CutData = h_Pem_All_Data->Integral(binCut, h_Pem_All_Data->GetNbinsX());
    double TotTri = h_Pem_All_Tri->Integral();
    double CutTri = h_Pem_All_Tri->Integral(binCut, h_Pem_All_Tri->GetNbinsX());
    double TotRad = h_Pem_All_Rad->Integral();
    double CutRad = h_Pem_All_Rad->Integral(binCut, h_Pem_All_Rad->GetNbinsX());
    lat1->SetTextColor(1);
    TLatex *tmpLat1 = lat1->DrawLatex(0.5, 0.72, Form("Data Cut = %1.2f %%", 100. * CutData / TotData));
    lat1->SetTextColor(2);
    TLatex *tmpLat2 = lat1->DrawLatex(0.5, 0.67, Form("Tri Cut = %1.2f %%", 100. * CutTri / TotTri));
    lat1->SetTextColor(4);
    TLatex *tmpLat3 = lat1->DrawLatex(0.5, 0.62, Form("Rad Cut = %1.2f %%", 100. * CutRad / TotRad));
    ctmp->Print("Figs/FEE_Cut.eps");
    ctmp->Print("Figs/FEE_Cut.pdf");
    ctmp->Print("Figs/FEE_Cut.png");

    delete tmpLine;
    delete tmpLat1;
    delete tmpLat2;
    delete tmpLat3;

    h_Pem_All_Tri->SetAxisRange(0., 0.02 * h_Pem_All_Tri->GetMaximum(), "Y");
    ctmp->Update();
    TLine *tmpLine2 = line1->DrawLine(Pem_MaxTight_Data, 0., Pem_MaxTight_Data, 0.95 * h_Pem_All_Tri->GetMaximum());
    ctmp->Print("Figs/FEE_CutZoom.eps");
    ctmp->Print("Figs/FEE_CutZoom.pdf");
    ctmp->Print("Figs/FEE_CutZoom.png");


    delete ctmp;
}

void Drawd0Cut(TFile** files) {

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TFile *file_Data = files[0];
    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];

    TLatex *lat1 = new TLatex();
    lat1->SetTextFont(42);
    lat1->SetNDC();
    lat1->SetTextSize(0.03);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);

    TCanvas *ctmp = new TCanvas("ctmp", "", 950, 950);

    TH1D *h_d0_AllBut_Data = (TH1D*) file_Data->Get("h_d0_ep_AllBut");
    double bw = h_d0_AllBut_Data->GetBinWidth(10);
    h_d0_AllBut_Data->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_Data->Scale(1 / (bw * Lumin8099));
    h_d0_AllBut_Data->SetLineColor(1);

    TH1D *h_d0_AllBut_Tri = (TH1D*) file_Tri->Get("h_d0_ep_AllBut");
    h_d0_AllBut_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
    h_d0_AllBut_Tri->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_Tri->SetLineColor(4);

    TH1D *h_d0_AllBut_Rad = (TH1D*) file_Rad->Get("h_d0_ep_AllBut");
    h_d0_AllBut_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));
    h_d0_AllBut_Rad->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_Rad->SetLineColor(2);

    TH1D *h_d0_AllBut_WAB = (TH1D*) file_WAB->Get("h_d0_ep_AllBut");
    h_d0_AllBut_WAB->Scale(Wab_SigmaGen / (bw * NGen_Wab));
    h_d0_AllBut_WAB->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_WAB->SetLineColor(45);

    TH1D *h_d0_AllBut_TriPlusWAB = (TH1D*) h_d0_AllBut_Tri->Clone("h_d0_AllBut_TriPlusWAB");
    h_d0_AllBut_TriPlusWAB->SetLineColor(95);
    h_d0_AllBut_TriPlusWAB->Add(h_d0_AllBut_WAB);

    h_d0_AllBut_TriPlusWAB->Draw();
    h_d0_AllBut_Data->Draw("Same");
    h_d0_AllBut_Tri->Draw("Same");
    h_d0_AllBut_Rad->Draw("Same");
    h_d0_AllBut_WAB->Draw("Same");
    ctmp->Print("Figs/d0_MC_Components.eps");
    ctmp->Print("Figs/d0_MC_Components.pdf");
    ctmp->Print("Figs/d0_MC_Components.png");

    TH1D *h_cum_d0_AllBut_TriPlusWAB = (TH1D*) h_d0_AllBut_TriPlusWAB->GetCumulative(true, "cum");
    TH1D *h_cum_d0_AllBut_Rad = (TH1D*) h_d0_AllBut_Rad->GetCumulative(true, "cum");

    for (int i = 0; i < h_cum_d0_AllBut_TriPlusWAB->GetNbinsX(); i++) {
        double tmp = h_cum_d0_AllBut_TriPlusWAB->GetBinContent(i + 1);
        h_cum_d0_AllBut_TriPlusWAB->SetBinContent(i + 1, sqrt(tmp));
    }


    TH1D *h_d0_FOM = (TH1D*) h_cum_d0_AllBut_Rad->Clone("h_d0_FOM");
    h_d0_FOM->Divide(h_cum_d0_AllBut_TriPlusWAB);

    h_d0_FOM->SetStats(false);
    h_d0_FOM->Draw();
    double d0_FOM_MC = h_d0_FOM->GetBinCenter(h_d0_FOM->GetMaximumBin());
    ctmp->Print("Figs/d0_FOM_MC.eps");
    ctmp->Print("Figs/d0_FOM_MC.pdf");
    ctmp->Print("Figs/d0_FOM_MC.png");

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", -3., 3.);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParameters(h_d0_AllBut_TriPlusWAB->GetMaximum(), 0, h_d0_AllBut_TriPlusWAB->GetRMS());
    f_Gaus->SetParLimits(2, 0., 2.);

    h_d0_AllBut_TriPlusWAB->Draw();
    h_d0_AllBut_TriPlusWAB->Fit(f_Gaus, "MeV", "", -0.7, 0.5);
    double mean_MC = f_Gaus->GetParameter(1);
    double sigm_MC = f_Gaus->GetParameter(2);
    lat1->DrawLatex(0.12, 0.7, Form("#mu = %1.3f mm", mean_MC));
    lat1->DrawLatex(0.12, 0.65, Form("#sigma = %1.3f mm", sigm_MC));
    lat1->DrawLatex(0.12, 0.45, Form("d_{0}(MC) < %1.3f mm", d0_FOM_MC));
    line1->DrawLine(d0_FOM_MC, 0., d0_FOM_MC, 0.9 * h_d0_AllBut_TriPlusWAB->GetMaximum());
    ctmp->Print("Figs/d0_MC_Fit.eps");
    ctmp->Print("Figs/d0_MC_Fit.pdf");
    ctmp->Print("Figs/d0_MC_Fit.png");

    h_d0_AllBut_Data->Draw();
    f_Gaus->SetParameters(h_d0_AllBut_Data->GetMaximum(), 0, h_d0_AllBut_Data->GetRMS());
    h_d0_AllBut_Data->Fit(f_Gaus, "MeV", "", -0.7, 0.7);
    double mean_Data = f_Gaus->GetParameter(1);
    double sigm_Data = f_Gaus->GetParameter(2);
    double d0_FOM_Data = mean_Data + sigm_Data * (d0_FOM_MC - mean_MC) / sigm_MC;
    lat1->DrawLatex(0.12, 0.7, Form("#mu = %1.3f mm", mean_Data));
    lat1->DrawLatex(0.12, 0.65, Form("#sigma = %1.3f mm", sigm_Data));
    lat1->DrawLatex(0.12, 0.45, Form("d_{0}(Data) < %1.3f mm", d0_FOM_Data));
    line1->DrawLine(d0_FOM_Data, 0., d0_FOM_Data, 0.9 * h_d0_AllBut_Data->GetMaximum());
    ctmp->Print("Figs/d0_Data_Fit.eps");
    ctmp->Print("Figs/d0_Data_Fit.pdf");
    ctmp->Print("Figs/d0_Data_Fit.png");

    delete ctmp;
}