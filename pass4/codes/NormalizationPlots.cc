/* 
 * File:   NormalizationPlots.cc
 * Author: rafopar
 *
 * Created on November 25, 2019, 11:21 AM
 */

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLine.h>
#include <TFile.h>
#include <cstdlib>
#include <fstream>
#include <TMath.h>
#include <iostream>
#include <TLatex.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TRatioPlot.h>
#include <TGraphErrors.h>
//#include "setting_2016_pass1.h"

using namespace std;


void DrawDatMCComparisonSingleHist(TFile** files, std::string histNameBase, std::string Title, int nDim);
void DrawDatMCComparison(TFile** files, std::string histNameBase, std::string Title, int nDim);
void AddErrorAllBins(TH1D* h, double RelErr);

void Draw2DCuts(std::string histAllBut, std::string histCut, std::string Title);

void DrawAntiFEECut(TFile** files);
void DrawPV0MaxCut(TFile** files);

void Drawd0Cut(TFile** files);
void DrawfRad(TFile** files);

void DrawLarged0hists(TFile** files, std::string histNameBase, std::string Title);

void WriteSingleV0CutFractins(TFile** files);

// ===== This function should return the Radiative fraction /
// ===== It should take the "CutEffect" histograms, and calculate the 
// ===== Rad Fraction as the Rad_Hist/(Wab+Tri)
double GetfRad(TFile** files, std::string histNameBase, double &fRad_Err);

const double tritrig_SigmaGen = 1.416e-3;
const double tritrig_SigmError = 0.00431e-3;
const double NGen_tritrig = 985. * 50000.; /* 200 recon files, and each recon has 50K Gen events*/

//const double Rad_SigmaGen = 81.e-6; // This was used till Tongong found that wrong alpha was used for Rad
//const double Rad_SigmError = 0.834e-6;
const double Rad_SigmaGen = 66.36e-6;
const double Rad_SigmError = 0.6678e-6;
const double NGen_Rad = 9959 * 10000.;
//const double NGen_Rad = 4989 * 10000.;

const double Wab_SigmaGen = 0.1985;
const double Wab_SigmError = 0.01973;
const double NGen_Wab = 9965. * 100000.;

const double Lumin8099 = 237.e9; // inverse barn

const double Pem_MaxTight_Data = 1.75;
const double Pem_Max_Data = 1.8;
const double Pem_Max_MC = 1.72;

const int nMinvBins = 12; // # of Minv bins, We want to study PV0 for different Minv Bins
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
    //TFile *file_EvSelection_Data = new TFile("EventSelection_Data_10Percent.root", "Read");
    TH1D *h_PV03_Data = (TH1D*) file_EvSelection_Data->Get("h_PV03");
    double bwPV03 = h_PV03_Data->GetBinWidth(10);
    h_PV03_Data->SetLineColor(1);

    TFile *file_EvSelection_Wab = new TFile("EventSelection_WAB.root", "Read");

    TH1D *h_PV03_Wab = (TH1D*) file_EvSelection_Wab->Get("h_PV03");
    h_PV03_Wab->SetTitle("; P_{Sum} [GeV]");
    h_PV03_Wab->Scale(Wab_SigmaGen / (bwPV03 * NGen_Wab));
    h_PV03_Wab->SetLineColor(45);

    TFile *file_EvSelection_Rad = new TFile("EventSelection_Rad.root", "Read");

    TH1D *h_PV03_Rad = (TH1D*) file_EvSelection_Rad->Get("h_PV03");
    h_PV03_Rad->SetTitle("; P_{Sum} [GeV]");
    h_PV03_Rad->Scale(Rad_SigmaGen / (bwPV03 * NGen_Rad));
    h_PV03_Rad->SetLineColor(2);


    TFile *file_EvSelection_Tri = new TFile("EventSelection_Tri.root", "Read");

    TH1D *h_PV03_Tri = (TH1D*) file_EvSelection_Tri->Get("h_PV03");
    h_PV03_Tri->SetTitle("; P_{Sum} [GeV]; d#sigma/d P_{Sum} [bn/GeV]");
    h_PV03_Tri->Scale(tritrig_SigmaGen / (bwPV03 * NGen_tritrig));
    h_PV03_Tri->SetLineColor(4);

    h_PV03_Tri->Draw();
    h_PV03_Rad->Draw("Same");
    h_PV03_Wab->Draw("Same");

    TH1D *h_PV03_WabPlusTri = (TH1D*) h_PV03_Tri->Clone("h_PV03_WabPlusTri");
    h_PV03_WabPlusTri->Add(h_PV03_Wab);
    h_PV03_WabPlusTri->SetLineColor(95);
    h_PV03_WabPlusTri->Draw();
    h_PV03_Tri->Draw("Same");
    h_PV03_Rad->Draw("Same");
    h_PV03_Wab->Draw("Same");
    const double DataScale = 1.32;
    h_PV03_Data->Scale(1 / (bwPV03 * Lumin8099));
    //h_PV03_Data->Draw("Same");
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
    c1->Print("Figs/PV03_MC_Components.eps");
    c1->Print("Figs/PV03_MC_Components.pdf");
    c1->Print("Figs/PV03_MC_Components.png");

    TH1D *h_PV03_Rad_Cumulative = (TH1D*) h_PV03_Rad->GetCumulative(0);
    h_PV03_Rad_Cumulative->Draw();

    TH1D *h_PV03_WabPlusTrid_Cumulative = (TH1D*) h_PV03_WabPlusTri->GetCumulative(0);
    h_PV03_WabPlusTrid_Cumulative->Draw();


    for (int i = 0; i < h_PV03_WabPlusTrid_Cumulative->GetNbinsX(); i++) {
        h_PV03_WabPlusTrid_Cumulative->SetBinContent(i + 1, sqrt(h_PV03_WabPlusTrid_Cumulative->GetBinContent(i + 1)));
    }

    TH1D *h_PV03_FOM = (TH1D*) h_PV03_Rad_Cumulative->Clone("h_PV03_FOM");
    h_PV03_FOM->Divide(h_PV03_WabPlusTrid_Cumulative);

    h_PV03_FOM->Draw();
    double PV0Cut = h_PV03_FOM->GetBinCenter(h_PV03_FOM->GetMaximumBin());
    cout << "PV0Cut = " << PV0Cut << endl;
    line1->DrawLine(PV0Cut, 0., PV0Cut, h_PV03_FOM->GetMaximum());
    lat1->DrawLatex(0.15, 0.4, Form("P_{V0} > %1.2f", PV0Cut));
    c1->Print("Figs/PV03_FOM.eps");
    c1->Print("Figs/PV03_FOM.pdf");
    c1->Print("Figs/PV03_FOM.png");

    TFile * files_EvSelection[5] = {file_EvSelection_Data, file_EvSelection_Tri, file_EvSelection_Rad, file_EvSelection_Wab};

    CutFractions.open("CutPowers.dat", ios::out);

    const int nMinvBins = 12;


    DrawDatMCComparisonSingleHist(files_EvSelection, "Minv_GeneralLargeBins_Final_1", "; M_{ee} [GeV]; d#sigma/dM_{ee} [bn/GeV] ", 5);
    DrawDatMCComparisonSingleHist(files_EvSelection, "MinvScSm_GeneralLargeBins_Final_1", "; M_{ee} [GeV]; d#sigma/dM_{ee} [bn/GeV] ", 5);
    DrawDatMCComparisonSingleHist(files_EvSelection, "PV0ScSm_GeneralLargeBins_Final_1", "; P(V_{0}) [GeV]; d#sigma/dP(e^{-}e^{+}) [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PV0Max", "; P_{V0} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);

    DrawDatMCComparison(files_EvSelection, "PV0Min", "; P_{V0} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PV0ScSmMin", "; P_{V0} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PSumMin", "; P_{e^{-}} + P_{e^{+}} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PV0ScSmMin", "; P_{V_{0}} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PSumScSmMin", "; P_{e^{-}} + P_{e^{+}} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PV0Min", "; P_{V0} [GeV]; d#sigma/dP_{V0} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "clDt", "; Cluster #Delta t [ns]; d#sigma/d #Delta t [bn/ns] ", 1);
    WriteSingleV0CutFractins(files_EvSelection);
    /*
    DrawDatMCComparison(files_EvSelection, "Pem", "; P_{e^{-}} [GeV]; d#sigma/d P_{e^{-}} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "d0_ep", "; d_{0}(e^{+}) [mm]; d#sigma/d d_{0}(e^{+}) [bn/mm] ", 1);


    DrawDatMCComparison(files_EvSelection, "em_cl_trk_dT", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "ep_cl_trk_dT", "; P_{e^{+}} [GeV]; t_{cl} - t_{trk} [ns]", 2);

    DrawDatMCComparison(files_EvSelection, "em_cl_trk_dT_Top", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "em_cl_trk_dT_Bot", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "ep_cl_trk_dT_Top", "; P_{e^{+}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "ep_cl_trk_dT_Bot", "; P_{e^{+}} [GeV]; t_{cl} - t_{trk} [ns]", 2);

    DrawDatMCComparison(files_EvSelection, "dX_em", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_ep", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);

    DrawDatMCComparison(files_EvSelection, "dX_emTopWithL6", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_emTopNoL6", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_emBotWithL6", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_emBotNoL6", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);

    DrawDatMCComparison(files_EvSelection, "dX_epTopWithL6", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_epTopNoL6", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_epBotWithL6", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_epBotNoL6", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]", 2);
     */
    double MinvBins[nMinvBins + 1] = {0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24};

    //    for (int i = 0; i < nMinvBins; i++) {
    //        DrawDatMCComparison(files_EvSelection, Form("PV0Min_MinvBin_%d", i),
    //                Form("%1.3f GeV < M(ee) < %1.3f GeV; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV]", MinvBins[i], MinvBins[i + 1]), 1);
    //    }
    /*
        Draw2DCuts("em_cl_trk_dT_Top", "h_trkCl_dt_P_Top_Cut", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]");
        Draw2DCuts("em_cl_trk_dT_Bot", "h_trkCl_dt_P_Bot_Cut", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]");

        Draw2DCuts("dX_emTopWithL6", "h_dX_Top_NegWithL6_Cut", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_emTopNoL6", "h_dX_Top_NegNoL6_Cut", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_emBotWithL6", "h_dX_Bot_NegWithL6_Cut", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_emBotNoL6", "h_dX_Bot_NegNoL6_Cut", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]");

        Draw2DCuts("dX_epTopWithL6", "h_dX_Top_PosWithL6_Cut", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_epTopNoL6", "h_dX_Top_PosNoL6_Cut", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_epBotWithL6", "h_dX_Bot_PosWithL6_Cut", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]");
        Draw2DCuts("dX_epBotNoL6", "h_dX_Bot_PosNoL6_Cut", "; P_{e^{+}} [GeV]; X_{cl} - X_{trk} [mm]");

    DrawAntiFEECut(files_EvSelection);
        Drawd0Cut(files_EvSelection);
     */
    // ========== Getting the Rad Fraction ===========
    DrawPV0MaxCut(files_EvSelection);

    c1->Clear();
    TGraphErrors *gr_fRad = new TGraphErrors();
    gr_fRad->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");

    for (int i = 0; i < nMinvBins; i++) {
        double fRadErr;
        double fRad = TMath::Max(0., GetfRad(files_EvSelection, Form("PV0Min_MinvBin_%d", i), fRadErr));

        cout << "fRad = " << fRad << endl;

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


    DrawfRad(files_EvSelection);

    /*
    DrawLarged0hists(files_EvSelection, "Pem_BigD0_1", ";P_{e^{-}} [GeV]; d#sigma/dP_{e^{-}} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "Pem_BigD0_2", ";P_{e^{-}} [GeV]; d#sigma/dP_{e^{-}} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "Pep_BigD0_1", ";P_{e^{+}} [GeV]; d#sigma/dP_{e^{+}} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "Pep_BigD0_2", ";P_{e^{+}} [GeV]; d#sigma/dP_{e^{+}} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "PV0_BigD0_1", ";P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "PV0_BigD0_2", ";P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV]");
    DrawLarged0hists(files_EvSelection, "Minv_BidD0_1", ";M(e^{-}e^{+}) [GeV]; d#sigma/dM [bn/GeV]");
     */
}

void Draw2DCuts(std::string histnminusbase, std::string histCut, std::string Title) {

    TCanvas *ctmp = new TCanvas("ctmp", "", 950, 950);
    ctmp->SetLeftMargin(0.15);
    ctmp->SetRightMargin(0.14);
    ctmp->SetLogz();

    TFile *file_Data = new TFile("EventSelection_Data.root", "Read");
    TH2D *h_Data_AllBut = (TH2D*) file_Data->Get(Form("h_%s_AllBut", histnminusbase.c_str()));
    h_Data_AllBut->SetTitle(Title.c_str());
    TFile *file_DataCut = new TFile("EvSelectionCutHists_Data.root", "Read");
    TH2D *h_Data_Cut = (TH2D*) file_DataCut->Get(Form("%s", histCut.c_str()));
    h_Data_Cut->SetTitle(Title.c_str());
    h_Data_Cut->SetLineColor(2);
    h_Data_Cut->Scale(10000);
    h_Data_Cut->SetMarkerColor(2);
    h_Data_Cut->SetMarkerSize(0.9);
    h_Data_Cut->SetMarkerStyle(20);

    h_Data_AllBut->Draw("colz");
    h_Data_Cut->Draw("box same0");
    ctmp->Print(Form("Figs/Cuts2D_%s_Data.eps", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Data.pdf", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Data.png", histnminusbase.c_str()));


    TFile *file_Tri = new TFile("EventSelection_Tri.root", "Read");
    TH2D *h_Tri_AllBut = (TH2D*) file_Tri->Get(Form("h_%s_AllBut", histnminusbase.c_str()));
    h_Tri_AllBut->SetTitle(Title.c_str());
    TFile *file_TriCut = new TFile("EvSelectionCutHists_Tri.root", "Read");
    TH2D *h_Tri_Cut = (TH2D*) file_TriCut->Get(Form("%s", histCut.c_str()));
    h_Tri_Cut->SetTitle(Title.c_str());
    h_Tri_Cut->SetLineColor(2);
    h_Tri_Cut->Scale(10000);
    h_Tri_Cut->SetMarkerColor(2);
    h_Tri_Cut->SetMarkerSize(0.9);
    h_Tri_Cut->SetMarkerStyle(20);

    h_Tri_AllBut->Draw("colz");
    h_Tri_Cut->Draw("box same0");
    ctmp->Print(Form("Figs/Cuts2D_%s_Tri.eps", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Tri.pdf", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Tri.png", histnminusbase.c_str()));


    TFile *file_Rad = new TFile("EventSelection_Rad.root", "Read");
    TH2D *h_Rad_AllBut = (TH2D*) file_Rad->Get(Form("h_%s_AllBut", histnminusbase.c_str()));
    h_Rad_AllBut->SetTitle(Title.c_str());
    TFile *file_RadCut = new TFile("EvSelectionCutHists_Rad.root", "Read");
    TH2D *h_Rad_Cut = (TH2D*) file_RadCut->Get(Form("%s", histCut.c_str()));
    h_Rad_Cut->SetTitle(Title.c_str());
    h_Rad_Cut->SetLineColor(2);
    h_Rad_Cut->Scale(10000);
    h_Rad_Cut->SetMarkerColor(2);
    h_Rad_Cut->SetMarkerSize(0.9);
    h_Rad_Cut->SetMarkerStyle(20);

    h_Rad_AllBut->Draw("colz");
    h_Rad_Cut->Draw("box same0");
    ctmp->Print(Form("Figs/Cuts2D_%s_Rad.eps", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Rad.pdf", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_Rad.png", histnminusbase.c_str()));


    TFile *file_WAB = new TFile("EventSelection_WAB.root", "Read");
    TH2D *h_WAB_AllBut = (TH2D*) file_WAB->Get(Form("h_%s_AllBut", histnminusbase.c_str()));
    h_WAB_AllBut->SetTitle(Title.c_str());
    TFile *file_WABCut = new TFile("EvSelectionCutHists_WAB.root", "Read");
    TH2D *h_WAB_Cut = (TH2D*) file_WABCut->Get(Form("%s", histCut.c_str()));
    h_WAB_Cut->SetTitle(Title.c_str());
    h_WAB_Cut->Scale(10000);
    h_WAB_Cut->SetLineColor(2);
    h_WAB_Cut->SetMarkerColor(2);
    h_WAB_Cut->SetMarkerSize(0.9);
    h_WAB_Cut->SetMarkerStyle(20);

    h_WAB_AllBut->Draw("colz");
    h_WAB_Cut->Draw("box same0");
    ctmp->Print(Form("Figs/Cuts2D_%s_WAB.eps", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_WAB.pdf", histnminusbase.c_str()));
    ctmp->Print(Form("Figs/Cuts2D_%s_WAB.png", histnminusbase.c_str()));

    delete ctmp;
}

void DrawDatMCComparisonSingleHist(TFile** files, std::string histNameBase, std::string Title, int Rb) {
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

    TCanvas *c1 = new TCanvas("c", "", 950, 950);
    c1->SetLeftMargin(0.15);
    c1->SetRightMargin(0.02);

    TH1D *h_Data = (TH1D*) file_Data->Get(Form("h_%s", histNameBase.c_str()));

    h_Data = (TH1D*) h_Data->Rebin(Rb, "h_Data");
    double bw = h_Data->GetBinWidth(10);
    h_Data->Sumw2();
    h_Data->SetLineColor(1);
    h_Data->SetTitle(Title.c_str());
    h_Data->Scale(1. / (bw * Lumin8099));

    TH1D *h_Tri = (TH1D*) file_Tri->Get(Form("h_%s", histNameBase.c_str()));
    h_Tri = (TH1D*) h_Tri->Rebin(Rb, "h_Tri");
    bw = h_Tri->GetBinWidth(10);
    h_Tri->Sumw2();
    h_Tri->SetLineColor(4);
    h_Tri->SetTitle(Title.c_str());
    h_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));


    TH1D *h_Rad = (TH1D*) file_Rad->Get(Form("h_%s", histNameBase.c_str()));
    h_Rad = (TH1D*) h_Rad->Rebin(Rb, "h_Rad");

    bw = h_Rad->GetBinWidth(10);
    h_Rad->Sumw2();
    h_Rad->SetLineColor(2);
    h_Rad->SetTitle(Title.c_str());
    h_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));

    TH1D *h_WAB = (TH1D*) file_WAB->Get(Form("h_%s", histNameBase.c_str()));
    h_WAB = (TH1D*) h_WAB->Rebin(Rb, "h_WAB");

    bw = h_WAB->GetBinWidth(10);
    h_WAB->Sumw2();
    h_WAB->SetLineColor(45);
    h_WAB->SetTitle(Title.c_str());
    h_WAB->Scale(Wab_SigmaGen / (bw * NGen_Wab));

    TH1D *h_Tot = (TH1D*) h_Tri->Clone("h_Tot");
    h_Tot->Add(h_WAB);

    h_Tot->SetLineColor(95);

    if (histNameBase.find("PV0") == 0) {
        h_Tot->SetAxisRange(1.85, 2.5);
        h_Data->SetAxisRange(1.85, 2.5);
        h_Tri->SetAxisRange(1.85, 2.5);
        h_WAB->SetAxisRange(1.85, 2.5);
        h_Rad->SetAxisRange(1.85, 2.5);


        // ======= Calculated the contribution from WAB and writes in a text file
        ofstream wab_Ratio("WabRatio.dat");

        wab_Ratio << "Wab contribution is " << 100. * h_WAB->Integral() / h_Tot->Integral() << "%" << endl;
        wab_Ratio.close();
    }

    TRatioPlot *rp = new TRatioPlot(h_Data, h_Tot, "divsym");
    rp->SetLeftMargin(0.15);
    rp->GetUpperPad()->SetBottomMargin(0);
    rp->GetLowerPad()->SetTopMargin(0);
    h_Data->SetMaximum(1.05 * h_Tot->GetMaximum());
    rp->Draw();
    rp->GetUpperPad()->cd();
    h_Tri->Draw("Same");
    h_Rad->Draw("Same");
    h_WAB->Draw("Same");
    rp->GetLowerRefGraph()->SetMaximum(1.1);
    rp->GetLowerRefGraph()->SetMinimum(0.5);
    c1->Update();

    c1->Print(Form("Figs/%s.eps", histNameBase.c_str()));
    c1->Print(Form("Figs/%s.pdf", histNameBase.c_str()));
    c1->Print(Form("Figs/%s.png", histNameBase.c_str()));

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
        double dataAll = h_Data_All->Integral();

        double bw = h_Data_All->GetBinWidth(10);
        h_Data_All->Sumw2();
        h_Data_All->SetLineColor(1);
        h_Data_All->SetTitle(Title.c_str());
        h_Data_All->Scale(1. / (bw * Lumin8099));
        TH1D *h_Data_AllBut = (TH1D*) file_Data->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        double dataAllBut = h_Data_AllBut->Integral();
        h_Data_AllBut->Sumw2();
        h_Data_AllBut->SetLineColor(1);
        h_Data_AllBut->SetTitle(Title.c_str());
        h_Data_AllBut->Scale(1. / (bw * Lumin8099));
        TH1D *h_Data_CutEffect = (TH1D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Data_CutEffect->Sumw2();
        h_Data_CutEffect->SetLineColor(1);
        h_Data_CutEffect->SetTitle(Title.c_str());
        h_Data_CutEffect->Scale(1. / (bw * Lumin8099));

        double dataFraction = h_Data_CutEffect->Integral() / h_Data_AllBut->Integral();



        TH1D *h_Tri_All = (TH1D*) file_Tri->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Tri_All->Sumw2();
        h_Tri_All->SetLineColor(4);
        h_Tri_All->SetTitle(Title.c_str());
        h_Tri_All->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
        AddErrorAllBins(h_Tri_All, tritrig_SigmError / tritrig_SigmaGen);
        TH1D *h_Tri_AllBut = (TH1D*) file_Tri->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Tri_AllBut->SetLineColor(4);
        h_Tri_AllBut->Sumw2();
        h_Tri_AllBut->SetTitle(Title.c_str());
        h_Tri_AllBut->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
        AddErrorAllBins(h_Tri_AllBut, tritrig_SigmError / tritrig_SigmaGen);
        TH1D *h_Tri_CutEffect = (TH1D*) file_Tri->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Tri_CutEffect->SetLineColor(4);
        h_Tri_CutEffect->Sumw2();
        h_Tri_CutEffect->SetTitle(Title.c_str());
        h_Tri_CutEffect->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
        AddErrorAllBins(h_Tri_CutEffect, tritrig_SigmError / tritrig_SigmaGen);

        double triFraction = h_Tri_CutEffect->Integral() / h_Tri_AllBut->Integral();

        TH1D *h_Rad_All = (TH1D*) file_Rad->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Rad_All->SetLineColor(2);
        h_Rad_All->Sumw2();
        h_Rad_All->SetTitle(Title.c_str());
        h_Rad_All->Scale(Rad_SigmaGen / (bw * NGen_Rad));
        AddErrorAllBins(h_Rad_All, Rad_SigmError / Rad_SigmaGen);
        TH1D *h_Rad_AllBut = (TH1D*) file_Rad->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Rad_AllBut->SetLineColor(2);
        h_Rad_AllBut->Sumw2();
        h_Rad_AllBut->SetTitle(Title.c_str());
        h_Rad_AllBut->Scale(Rad_SigmaGen / (bw * NGen_Rad));
        AddErrorAllBins(h_Rad_AllBut, Rad_SigmError / Rad_SigmaGen);
        TH1D *h_Rad_CutEffect = (TH1D*) file_Rad->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Rad_CutEffect->SetLineColor(2);
        h_Rad_CutEffect->Sumw2();
        h_Rad_CutEffect->SetTitle(Title.c_str());
        h_Rad_CutEffect->Scale(Rad_SigmaGen / (bw * NGen_Rad));
        AddErrorAllBins(h_Rad_CutEffect, Rad_SigmError / Rad_SigmaGen);

        double radFraction = h_Rad_CutEffect->Integral() / h_Rad_AllBut->Integral();

        TH1D *h_WAB_All = (TH1D*) file_WAB->Get(Form("h_%s_All", histNameBase.c_str()));
        h_WAB_All->SetLineColor(45);
        h_WAB_All->Sumw2();
        h_WAB_All->SetTitle(Title.c_str());
        h_WAB_All->Scale(Wab_SigmaGen / (bw * NGen_Wab));
        AddErrorAllBins(h_WAB_All, Wab_SigmError / Wab_SigmaGen);
        TH1D *h_WAB_AllBut = (TH1D*) file_WAB->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_WAB_AllBut->SetLineColor(45);
        h_WAB_AllBut->Sumw2();
        h_WAB_AllBut->SetTitle(Title.c_str());
        h_WAB_AllBut->Scale(Wab_SigmaGen / (bw * NGen_Wab));
        AddErrorAllBins(h_WAB_AllBut, Wab_SigmError / Wab_SigmaGen);
        TH1D *h_WAB_CutEffect = (TH1D*) file_WAB->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_WAB_CutEffect->SetLineColor(45);
        h_WAB_CutEffect->Sumw2();
        h_WAB_CutEffect->SetTitle(Title.c_str());
        h_WAB_CutEffect->Scale(Wab_SigmaGen / (bw * NGen_Wab));
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
        rp->GetLowerRefGraph()->SetMaximum(1.5);
        rp->GetLowerRefGraph()->SetMinimum(0.5);
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
        rp2->GetLowerRefGraph()->SetMaximum(1.5);
        rp2->GetLowerRefGraph()->SetMinimum(0.5);
        c1D->Update();
        c1D->Print(Form("Figs/%s_AllBut.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.png", histNameBase.c_str()));

        c1D->Clear();
        delete rp2;

        if (histNameBase.compare("PV0Min") == 0 || histNameBase.compare("PV0ScSmMin") == 0) {
            h_Data_CutEffect->SetAxisRange(1.6, 2.6);
        }

        h_Data_CutEffect->SetMaximum(1.05 * Max_AllBut);
        TRatioPlot *rp3 = new TRatioPlot(h_Data_CutEffect, hTriPlusWab_CutEffect, "divsym");
        rp3->GetUpperPad()->SetBottomMargin(0);
        rp3->GetLowerPad()->SetTopMargin(0);
        rp3->Draw();
        rp3->GetUpperPad()->cd();
        h_Tri_CutEffect->Draw("Same");
        h_Rad_CutEffect->Draw("Same");
        h_WAB_CutEffect->Draw("Same");
        rp2->GetLowerRefGraph()->SetMaximum(1.5);
        rp2->GetLowerRefGraph()->SetMinimum(0.5);
        c1D->Update();
        c1D->Print(Form("Figs/%s_CutEffect.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.png", histNameBase.c_str()));

        c1D->Clear();
        delete rp3;

        CutFractions << setw(25) << histNameBase << setw(12) << " & " << Form("%1.3e", dataAllBut) << " & " << dataFraction << setw(12) << " & " << triFraction << setw(12)
                << " & " << radFraction << setw(12) << " & " << wabFraction << setw(12) << " & " << wabTriFraction << " \\\\ \\hline" << endl;


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
        c2D->SetRightMargin(0.14);
        c2D->SetLogz();

        TH2D *h_Data_All = (TH2D*) file_Data->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Data_All->Sumw2();
        h_Data_All->SetTitle(Title.c_str());
        //h_Data_All->Scale(1 / Lumin8099);
        h_Data_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_All.png", histNameBase.c_str()));

        TH2D *h_Data_AllBut = (TH2D*) file_Data->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Data_AllBut->Sumw2();
        h_Data_AllBut->SetTitle(Title.c_str());
        //h_Data_AllBut->Scale(1 / Lumin8099);
        h_Data_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_AllBut.png", histNameBase.c_str()));

        TH2D *h_Data_CutEffect = (TH2D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Data_CutEffect->Sumw2();
        h_Data_CutEffect->SetTitle(Title.c_str());
        //h_Data_CutEffect->Scale(1 / Lumin8099);
        h_Data_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Data_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Data_CutEffect.png", histNameBase.c_str()));

        double dataFraction = h_Data_CutEffect->Integral() / h_Data_AllBut->Integral();

        TH2D *h_Tri_All = (TH2D*) file_Tri->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Tri_All->Sumw2();
        h_Tri_All->SetTitle(Title.c_str());
        //h_Tri_All->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_All.png", histNameBase.c_str()));

        TH2D *h_Tri_AllBut = (TH2D*) file_Tri->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Tri_AllBut->Sumw2();
        h_Tri_AllBut->SetTitle(Title.c_str());
        //h_Tri_AllBut->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_AllBut.png", histNameBase.c_str()));

        TH2D *h_Tri_CutEffect = (TH2D*) file_Tri->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Tri_CutEffect->Sumw2();
        h_Tri_CutEffect->SetTitle(Title.c_str());
        //h_Tri_CutEffect->Scale(tritrig_SigmaGen / NGen_tritrig);
        h_Tri_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Tri_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Tri_CutEffect.png", histNameBase.c_str()));

        double triFraction = h_Tri_CutEffect->Integral() / h_Tri_AllBut->Integral();

        TH2D *h_Rad_All = (TH2D*) file_Rad->Get(Form("h_%s_All", histNameBase.c_str()));
        h_Rad_All->Sumw2();
        h_Rad_All->SetTitle(Title.c_str());
        //h_Rad_All->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_All->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_All.png", histNameBase.c_str()));

        TH2D *h_Rad_AllBut = (TH2D*) file_Rad->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Rad_AllBut->Sumw2();
        h_Rad_AllBut->SetTitle(Title.c_str());
        //h_Rad_AllBut->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_AllBut.png", histNameBase.c_str()));

        TH2D *h_Rad_CutEffect = (TH2D*) file_Rad->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Rad_CutEffect->Sumw2();
        h_Rad_CutEffect->SetTitle(Title.c_str());
        //h_Rad_CutEffect->Scale(Rad_SigmaGen / NGen_Rad);
        h_Rad_CutEffect->Draw("colz");
        c2D->Print(Form("Figs/%s_Rad_CutEffect.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_CutEffect.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_Rad_CutEffect.png", histNameBase.c_str()));

        double radFraction = h_Rad_CutEffect->Integral() / h_Rad_AllBut->Integral();

        TH2D *h_WAB_All = (TH2D*) file_WAB->Get(Form("h_%s_All", histNameBase.c_str()));
        h_WAB_All->Sumw2();
        h_WAB_All->SetTitle(Title.c_str());
        //h_WAB_All->Scale(Wab_SigmaGen / NGen_Wab);
        h_WAB_All->Draw("colz");
        c2D->Print(Form("Figs/%s_WAB_All.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_All.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_All.png", histNameBase.c_str()));

        TH2D *h_WAB_AllBut = (TH2D*) file_WAB->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_WAB_AllBut->Sumw2();
        h_WAB_AllBut->SetTitle(Title.c_str());
        //h_WAB_AllBut->Scale(Wab_SigmaGen / NGen_Wab);
        h_WAB_AllBut->Draw("colz");
        c2D->Print(Form("Figs/%s_WAB_AllBut.eps", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_AllBut.pdf", histNameBase.c_str()));
        c2D->Print(Form("Figs/%s_WAB_AllBut.png", histNameBase.c_str()));

        TH2D *h_WAB_CutEffect = (TH2D*) file_WAB->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_WAB_CutEffect->Sumw2();
        h_WAB_CutEffect->SetTitle(Title.c_str());
        //h_WAB_CutEffect->Scale(Wab_SigmaGen / NGen_Wab);
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
    if (Integr_TriWAB == 0) {
        return 0.;
    }


    double fRad = Integr_Rad / Integr_TriWAB;

    fRad_Err = fRad * sqrt((err_Rad / Integr_Rad)*(err_Rad / Integr_Rad) + (err_TriWAB / Integr_TriWAB)*(err_TriWAB / Integr_TriWAB));


    if (isnan(fRad)) {
        fRad = 0.;
        fRad_Err = 0.;
    }


    return fRad;

}

void DrawfRad(TFile** files) {

    TCanvas *ctmp = new TCanvas("ctmp", "", 950, 950);
    ctmp->SetRightMargin(0.02);
    ctmp->SetLeftMargin(0.12);

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];

    TFile *file_fRad_Output = new TFile("fRadHists.root", "Recreate");


    //TH1D *h_Memep_True1_Rad = (TH1D*) file_Rad->Get("h_Memep_True1");
    TH1D *h_Memep_True1_Rad = (TH1D*) file_Rad->Get("h_Minv_GeneralTrue_Final_1");
    h_Memep_True1_Rad->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep_True1_Rad->Sumw2();
    h_Memep_True1_Rad->SetLineColor(2);
    h_Memep_True1_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    //AddErrorAllBins(h_Memep_True1_Rad, Rad_SigmError / Rad_SigmaGen);

    //TH1D *h_Memep1_Rad = (TH1D*) file_Rad->Get("h_Memep1");
    TH1D *h_Memep1_Rad = (TH1D*) file_Rad->Get("h_MinvScSm_General_Final_1");
    h_Memep1_Rad->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep1_Rad->Sumw2();
    h_Memep1_Rad->SetLineColor(2);
    h_Memep1_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    // AddErrorAllBins(h_Memep1_Rad, Rad_SigmError / Rad_SigmaGen);

    TH1D *h_Memep1_Tri = (TH1D*) file_Tri->Get("h_MinvScSm_General_Final_1");
    //TH1D *h_Memep1_Tri = (TH1D*) file_Tri->Get("h_Memep1");
    h_Memep1_Tri->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep1_Tri->Sumw2();
    h_Memep1_Tri->SetLineColor(4);
    h_Memep1_Tri->Scale(tritrig_SigmaGen / NGen_tritrig);
    //AddErrorAllBins(h_Memep1_Tri, tritrig_SigmError / tritrig_SigmaGen);


    //    TH1D *h_Memep1_WAB = (TH1D*) file_WAB->Get("h_Memep1");
    TH1D *h_Memep1_WAB = (TH1D*) file_WAB->Get("h_MinvScSm_General_Final_1");
    h_Memep1_WAB->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep1_WAB->Sumw2();
    h_Memep1_WAB->SetLineColor(45);
    h_Memep1_WAB->Scale(Wab_SigmaGen / NGen_Wab);
    //AddErrorAllBins(h_Memep1_WAB, Wab_SigmError / Wab_SigmaGen);


    TH1D *h_Memep1_Tot = (TH1D*) h_Memep1_Tri->Clone("Memep_Tot");
    h_Memep1_Tot->Add(h_Memep1_WAB);
    h_Memep1_Tot->SetLineColor(45);

    TH1D *h_Memep1_Tri_RB = (TH1D*) h_Memep1_Tri->Rebin(20, "h_Memep_Tri_RB");
    TH1D *h_Memep1_WAB_RB = (TH1D*) h_Memep1_WAB->Rebin(20, "h_Memep_WAB_RB");
    TH1D *h_Memep1_Rad_RB = (TH1D*) h_Memep1_Rad->Rebin(20, "h_Memep_Rad_RB");
    TH1D *h_Memep_True1_Rad_RB = (TH1D*) h_Memep_True1_Rad->Rebin(20, "h_Memep_True1_Rad_RB");
    TH1D *h_Memep1_Tot_RB = (TH1D*) h_Memep1_Tot->Rebin(20, "h_Memep_Tot_RB");

    h_Memep1_Tot_RB->SetLineColor(95);
    h_Memep1_WAB_RB->SetLineColor(45);
    h_Memep1_Tri_RB->SetLineColor(4);
    h_Memep1_Rad_RB->SetLineColor(2);
    h_Memep_True1_Rad_RB->SetLineColor(2);

    TLegend *leg1 = new TLegend(0.25, 0.2, 0.45, 0.4);
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->AddEntry(h_Memep1_Tot_RB, "Tri + WAB");
    leg1->AddEntry(h_Memep1_Tri_RB, "Tri");
    leg1->AddEntry(h_Memep1_WAB_RB, "WAB");
    leg1->AddEntry(h_Memep1_Rad_RB, "Rad");


    ctmp->SetLogy();
    h_Memep1_Tot_RB->SetMinimum(1.e-6 * h_Memep1_Tot_RB->GetMaximum());
    h_Memep1_Tot_RB->Draw("hist e");
    h_Memep1_WAB_RB->Draw("hist Same e");
    h_Memep1_Tri_RB->Draw("hist Same e");
    h_Memep1_Rad_RB->Draw("hist Same e");
    leg1->Draw();
    ctmp->Print("Figs/Mass_MCComponets_RB.eps");
    ctmp->Print("Figs/Mass_MCComponets_RB.pdf");
    ctmp->Print("Figs/Mass_MCComponets_RB.png");

    TH1D *h_fRad = (TH1D*) h_Memep1_Rad_RB->Clone("h_fRad");

    h_fRad->Divide(h_Memep1_Tot_RB);
    h_fRad->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");

    ctmp->SetLogy(0);
    h_fRad->SetAxisRange(0., 0.12, "Y");
    h_fRad->SetLineColor(2);
    h_fRad->Draw();

    ctmp->Print("Figs/fRadWithTruts.eps");
    ctmp->Print("Figs/fRadWithTruts.pdf");
    ctmp->Print("Figs/fRadWithTruts.png");


    TH1D *h_fRadTrue = (TH1D*) h_Memep_True1_Rad_RB->Clone("h_Memep_True1_Rad_RB");
    h_fRadTrue->Divide(h_Memep1_Tot_RB);
    h_fRadTrue->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");
    h_fRadTrue->GetXaxis()->SetNdivisions(506);
    h_fRadTrue->SetLineColor(4);
    h_fRadTrue->SetAxisRange(0.03, 0.09, "Y");
    h_fRadTrue->SetAxisRange(0.04, 0.18, "X");
    h_fRadTrue->Draw();
    ctmp->Print("Figs/fRadWithTrutsTrueMass.eps");
    ctmp->Print("Figs/fRadWithTrutsTrueMass.pdf");
    ctmp->Print("Figs/fRadWithTrutsTrueMass.png");


    TF1 *f_Pol6 = new TF1("f_Pol6", "pol6", 0., 0.2);
    f_Pol6->SetNpx(4500);
    f_Pol6->SetLineColor(95);
    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);
    TLegend *legfRad1 = new TLegend(0.35, 0.75, 0.65, 0.88);
    legfRad1->SetBorderSize(0.);
    legfRad1->SetFillColor(0);
    legfRad1->AddEntry(h_fRadTrue, "True Mass");
    legfRad1->AddEntry(h_fRad, "Rec Mass");
    TCanvas *cfRad = new TCanvas("cfRad", "", 950, 950);
    cfRad->cd();
    cfRad->SetTopMargin(0.02);
    cfRad->SetRightMargin(0.02);
    cfRad->SetLeftMargin(0.19);
    cfRad->SetBottomMargin(0.14);
    h_fRad->SetStats(0);
    h_fRadTrue->SetStats(0);
    h_fRadTrue->GetXaxis()->SetTitleSize(0.06);
    h_fRadTrue->GetYaxis()->SetTitleSize(0.06);
    h_fRadTrue->GetXaxis()->SetLabelSize(0.06);
    h_fRadTrue->GetYaxis()->SetLabelSize(0.06);
    h_fRadTrue->Draw();
    h_fRadTrue->Fit(f_Pol6, "MeV", "", 0.04, 0.18);
    h_fRad->Draw("Same");
    legfRad1->Draw();
    double chi2 = f_Pol6->GetChisquare();
    double NDF = f_Pol6->GetNDF();
    lat1->DrawLatex(0.3, 0.32, Form("#chi^{2}/NDF = %1.2f", chi2 / NDF));
    cfRad->Print("Figs/fRad_Fit.eps");
    cfRad->Print("Figs/fRad_Fit.pdf");
    cfRad->Print("Figs/fRad_Fit.png");

    const int nPar = 7;
    double parsPol[nPar];

    f_Pol6->GetParameters(parsPol);
    ofstream outfRadFit("fRadFitPars.dat");
    outfRadFit << "Par(0)  & Par(1) & Par(2) & Par(3) & Par(4) & Par(5) & Par(6)" << endl;
    outfRadFit.precision(10);
    for (int i = 0; i < nPar; i++) {
        outfRadFit << parsPol[i] << " & \t";
    }
    outfRadFit << endl;

    delete cfRad;


    TH1D *h_Memep_True_VarBins1_Rad = (TH1D*) file_Rad->Get("h_MinvTrue_GeneralVarBins_Final_1");
    h_Memep_True_VarBins1_Rad->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep_True_VarBins1_Rad->Sumw2();
    h_Memep_True_VarBins1_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    //AddErrorAllBins(h_Memep_True_VarBins1_Rad, Rad_SigmError / Rad_SigmaGen);

    TH1D *h_Memep_VarBins1_Rad = (TH1D*) file_Rad->Get("h_MinvScSm_GeneralVarBins_Final_1");
    h_Memep_VarBins1_Rad->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep_VarBins1_Rad->Sumw2();
    h_Memep_VarBins1_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    // AddErrorAllBins(h_Memep_VarBins1_Rad, Rad_SigmError / Rad_SigmaGen);

    TH1D *h_Memep_VarBins1_Tri = (TH1D*) file_Tri->Get("h_MinvScSm_GeneralVarBins_Final_1");
    h_Memep_VarBins1_Tri->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep_VarBins1_Tri->Sumw2();
    h_Memep_VarBins1_Tri->Scale(tritrig_SigmaGen / NGen_tritrig);
    // AddErrorAllBins(h_Memep_VarBins1_Tri, tritrig_SigmError / tritrig_SigmaGen);


    TH1D *h_Memep_VarBins1_WAB = (TH1D*) file_WAB->Get("h_MinvScSm_GeneralVarBins_Final_1");
    h_Memep_VarBins1_WAB->SetTitle("; M(e^{-}e^{+}) [ GeV]; d#sigma/dm [bn*GeV^{-1}]");
    h_Memep_VarBins1_WAB->Sumw2();
    h_Memep_VarBins1_WAB->Scale(Wab_SigmaGen / NGen_Wab);
    //AddErrorAllBins(h_Memep_VarBins1_WAB, Wab_SigmError / Wab_SigmaGen);


    TH1D *h_Memep_VarBins1_Tot = (TH1D*) h_Memep_VarBins1_Tri->Clone("Memep_VarBins_Tot");
    h_Memep_VarBins1_Tot->Add(h_Memep_VarBins1_WAB);


    h_Memep_VarBins1_Tot->SetLineColor(95);
    h_Memep_VarBins1_WAB->SetLineColor(45);
    h_Memep_VarBins1_Tri->SetLineColor(4);
    h_Memep_VarBins1_Rad->SetLineColor(2);

    TLegend *leg2 = new TLegend(0.25, 0.2, 0.45, 0.4);
    leg2->SetBorderSize(0);
    leg2->SetFillColor(0);
    leg2->AddEntry(h_Memep_VarBins1_Tot, "Tri + WAB");
    leg2->AddEntry(h_Memep_VarBins1_Tri, "Tri");
    leg2->AddEntry(h_Memep_VarBins1_WAB, "WAB");
    leg2->AddEntry(h_Memep_VarBins1_Rad, "Rad");

    ctmp->SetLogy();
    h_Memep_VarBins1_Tot->SetMinimum(1.e-6 * h_Memep_VarBins1_Tot->GetMaximum());
    h_Memep_VarBins1_Tot->Draw("hist e");
    h_Memep_VarBins1_WAB->Draw("hist Same e");
    h_Memep_VarBins1_Tri->Draw("hist Same e");
    h_Memep_VarBins1_Rad->Draw("hist Same e");

    leg2->Draw();
    ctmp->Print("Figs/Mass_MCComponets_VarBins.eps");
    ctmp->Print("Figs/Mass_MCComponets_VarBIns.pdf");
    ctmp->Print("Figs/Mass_MCComponets_VarBIns.png");

    TH1D *h_fRad_VarBins = (TH1D*) h_Memep_VarBins1_Rad->Clone("h_fRad_VarBins");

    h_fRad_VarBins->Divide(h_Memep_VarBins1_Tot);
    h_fRad_VarBins->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");

    ctmp->SetLogy(0);
    h_fRad_VarBins->SetAxisRange(0., 0.12, "Y");
    h_fRad_VarBins->Draw();

    ctmp->Print("Figs/fRadWithTruts_VarBins.eps");
    ctmp->Print("Figs/fRadWithTruts_VarBins.pdf");
    ctmp->Print("Figs/fRadWithTruts_VarBins.png");

    TH1D *h_fRad_TrueMass_VarBins = (TH1D*) h_Memep_True_VarBins1_Rad->Clone("h_fRad_TrueMass_VarBins");
    h_fRad_TrueMass_VarBins->Divide(h_Memep_VarBins1_Tot);
    h_fRad_TrueMass_VarBins->SetTitle("; M(e^{-}e^{+}) [GeV]; f_{Rad}");
    h_fRad_TrueMass_VarBins->SetLineColor(4);
    h_fRad_TrueMass_VarBins->Draw("Same");
    ctmp->Print("Figs/fRadVarBins_TrueAndRecMass.eps");
    ctmp->Print("Figs/fRadVarBins_TrueAndRecMass.pdf");
    ctmp->Print("Figs/fRadVarBins_TrueAndRecMass.png");

    h_fRad_TrueMass_VarBins->SetAxisRange(0., 0.12, "Y");
    h_fRad_TrueMass_VarBins->Draw();
    ctmp->Print("Figs/fRadVarBins_TrueMass.eps");
    ctmp->Print("Figs/fRadVarBins_TrueMass.pdf");
    ctmp->Print("Figs/fRadVarBins_TrueMass.png");

    h_Memep_True1_Rad->Write("h_Memep_True1_Rad");
    h_Memep1_Rad->Write("h_Memep1_Rad");
    h_Memep1_Tri->Write("h_Memep1_Tri");
    h_Memep1_WAB->Write("h_Memep1_WAB");
    h_Memep1_Tot->Write("h_Memep1_Tot");

    h_Memep1_Tot_RB->Write("h_Memep1_Tot_RB");
    h_Memep1_Rad_RB->Write("h_Memep1_Rad_RB");
    h_Memep_True1_Rad_RB->Write("h_Memep_True1_Rad_RB");
    h_Memep1_Tri_RB->Write("h_Memep1_Tri_RB");
    h_Memep1_WAB_RB->Write("h_Memep1_WAB_RB");

    h_fRad->Write("h_fRad");
    h_fRadTrue->Write("h_fRadTrue");

    h_Memep_True_VarBins1_Rad->Write("h_Memep_True_VarBins1_Rad");
    h_Memep_VarBins1_Rad->Write("h_Memep_VarBins1_Rad");
    h_Memep_VarBins1_WAB->Write("h_Memep_VarBins1_WAB");
    h_Memep_VarBins1_Tri->Write("h_Memep_VarBins1_Tri");
    h_Memep_VarBins1_Tot->Write("h_Memep_VarBins1_Tot");
    h_fRad_VarBins->Write("h_fRad_VarBins");
    h_fRad_TrueMass_VarBins->Write("h_fRad_TrueMass_VarBins");


    file_fRad_Output->Close();
    delete file_fRad_Output;
    delete ctmp;
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
    ctmp->SetLeftMargin(0.14);

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
    line1->SetLineColor(1);
    TLine *tmpLineData = line1->DrawLine(Pem_Max_Data, 0., Pem_Max_Data, 0.25 * h_Pem_All_Tri->GetMaximum());
    line1->SetLineColor(2);
    TLine *tmpLine = line1->DrawLine(Pem_Max_MC, 0., Pem_Max_MC, 0.25 * h_Pem_All_Tri->GetMaximum());
    //TLine *tmpLine = line1->DrawLine(Pem_MaxTight_Data, 0., Pem_MaxTight_Data, 0.25 * h_Pem_All_Tri->GetMaximum());

    int binCutData = h_Pem_All_Tri->FindBin(Pem_Max_Data);
    int binCutMC = h_Pem_All_Tri->FindBin(Pem_Max_MC);
    double TotData = h_Pem_All_Data->Integral();
    double CutData = h_Pem_All_Data->Integral(binCutData + 1, h_Pem_All_Data->GetNbinsX());
    double TotTri = h_Pem_All_Tri->Integral();
    double CutTri = h_Pem_All_Tri->Integral(binCutMC + 1, h_Pem_All_Tri->GetNbinsX());
    double TotRad = h_Pem_All_Rad->Integral();
    double CutRad = h_Pem_All_Rad->Integral(binCutMC + 1, h_Pem_All_Rad->GetNbinsX());
    lat1->SetTextColor(1);
    TLatex *tmpLat1 = lat1->DrawLatex(0.5, 0.72, Form("Data Cut = %1.2f %%", 100. * CutData / TotData));
    lat1->SetTextColor(2);
    TLatex *tmpLat2 = lat1->DrawLatex(0.5, 0.67, Form("Tri Cut = %1.2f %%", 100. * CutTri / TotTri));
    lat1->SetTextColor(4);
    TLatex *tmpLat3 = lat1->DrawLatex(0.5, 0.62, Form("Rad Cut = %1.2f %%", 100. * CutRad / TotRad));
    ctmp->Print("Figs/FEE_Cut.eps");
    ctmp->Print("Figs/FEE_Cut.pdf");
    ctmp->Print("Figs/FEE_Cut.png");

    delete tmpLineData;
    delete tmpLine;
    delete tmpLat1;
    delete tmpLat2;
    delete tmpLat3;

    h_Pem_All_Tri->SetAxisRange(0., 0.02 * h_Pem_All_Tri->GetMaximum(), "Y");
    ctmp->Update();
    line1->SetLineColor(1);
    TLine *tmpLine2 = line1->DrawLine(Pem_Max_Data, 0., Pem_Max_Data, 0.95 * h_Pem_All_Tri->GetMaximum());
    line1->SetLineColor(2);
    TLine *tmpLine2MC = line1->DrawLine(Pem_Max_MC, 0., Pem_Max_MC, 0.95 * h_Pem_All_Tri->GetMaximum());
    ctmp->Print("Figs/FEE_CutZoom.eps");
    ctmp->Print("Figs/FEE_CutZoom.pdf");
    ctmp->Print("Figs/FEE_CutZoom.png");


    TH1D *h_Pem_AllBut_Data = (TH1D*) file_Data->Get("h_Pem_AllBut");
    TH1D *h_Pem_AllBut_Tri = (TH1D*) file_Tri->Get("h_Pem_AllBut");
    TH1D *h_Pem_AllBut_Rad = (TH1D*) file_Rad->Get("h_Pem_AllBut");
    TH1D *h_Pem_AllBut_WAB = (TH1D*) file_WAB->Get("h_Pem_AllBut");

    h_Pem_AllBut_Data->Scale(1 / (bw * Lumin8099));
    h_Pem_AllBut_Data->SetLineColor(1);
    h_Pem_AllBut_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
    h_Pem_AllBut_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));

    h_Pem_AllBut_Tri->SetTitle("; P_{e^{-}} [GeV]; d#sigma/d P_{e^{-}} [bn/GeV] ");
    h_Pem_AllBut_Tri->SetLineColor(2);
    h_Pem_AllBut_Tri->Draw();
    h_Pem_AllBut_Data->Draw("Same");
    h_Pem_AllBut_Rad->Draw("Same");
    line1->SetLineColor(1);
    TLine *tmpLineData2 = line1->DrawLine(Pem_Max_Data, 0., Pem_Max_Data, 0.25 * h_Pem_AllBut_Tri->GetMaximum());
    line1->SetLineColor(2);
    TLine *tmpLine3 = line1->DrawLine(Pem_Max_MC, 0., Pem_Max_MC, 0.25 * h_Pem_AllBut_Tri->GetMaximum());

    int binCutAllBut = h_Pem_AllBut_Tri->FindBin(Pem_MaxTight_Data);
    double TotDataAllBut = h_Pem_AllBut_Data->Integral();
    double CutDataAllBut = h_Pem_AllBut_Data->Integral(binCutData + 1, h_Pem_AllBut_Data->GetNbinsX());
    double TotTriAllBut = h_Pem_AllBut_Tri->Integral();
    double CutTriAllBut = h_Pem_AllBut_Tri->Integral(binCutMC + 1, h_Pem_AllBut_Tri->GetNbinsX());
    double TotRadAllBut = h_Pem_AllBut_Rad->Integral();
    double CutRadAllBut = h_Pem_AllBut_Rad->Integral(binCutMC + 1, h_Pem_AllBut_Rad->GetNbinsX());
    lat1->SetTextColor(1);
    TLatex *tmpLat21 = lat1->DrawLatex(0.55, 0.72, Form("Data Cut = %1.2f %%", 100. * CutDataAllBut / TotDataAllBut));
    lat1->SetTextColor(2);
    TLatex *tmpLat22 = lat1->DrawLatex(0.55, 0.67, Form("Tri Cut = %1.2f %%", 100. * CutTriAllBut / TotTriAllBut));
    lat1->SetTextColor(4);
    TLatex *tmpLat23 = lat1->DrawLatex(0.55, 0.62, Form("Rad Cut = %1.2f %%", 100. * CutRadAllBut / TotRadAllBut));

    ctmp->Print("Figs/FEE_Cut_AllBut.eps");
    ctmp->Print("Figs/FEE_Cut_AllBut.pdf");
    ctmp->Print("Figs/FEE_Cut_AllBut.png");

    delete tmpLat21;
    delete tmpLat22;
    delete tmpLat23;
    delete tmpLine3;
    delete tmpLineData2;

    h_Pem_AllBut_Tri->SetAxisRange(0., 0.02 * h_Pem_AllBut_Tri->GetMaximum(), "Y");
    ctmp->Update();
    line1->SetLineColor(1);
    TLine *tmpLine2Data = line1->DrawLine(Pem_Max_Data, 0., Pem_Max_Data, 0.95 * h_Pem_AllBut_Tri->GetMaximum());
    line1->SetLineColor(2);
    line1->DrawLine(Pem_Max_MC, 0., Pem_Max_MC, 0.95 * h_Pem_AllBut_Tri->GetMaximum());

    //TLine *tmpLine4 = line1->DrawLine(Pem_MaxTight_Data, 0., Pem_MaxTight_Data, 0.95 * h_Pem_AllBut_Tri->GetMaximum());
    ctmp->Print("Figs/FEE_CutAllButZoom.eps");
    ctmp->Print("Figs/FEE_CutAllButZoom.pdf");
    ctmp->Print("Figs/FEE_CutAllButZoom.png");


    delete ctmp;
}

void DrawPV0MaxCut(TFile** files) {

    //==========================================================
    //===== Order of files in the pointer "files" is the following
    //===== 1-st: Data
    //===== 2-nd: TriTrig
    //===== 3-3d: Radiatives
    //===== 4-th: Converted Wabs
    //==========================================================

    TCanvas *ctmp = new TCanvas("ctmp", "", 950, 950);
    ctmp->SetLeftMargin(0.14);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    TFile *file_Data = files[0];
    TFile *file_Tri = files[1];
    TFile *file_Rad = files[2];
    TFile *file_WAB = files[3];

    TH1D *h_PV0Max_AllBut_Data = (TH1D*) file_Data->Get("h_PV0ScSmMax_AllBut");
    h_PV0Max_AllBut_Data->SetTitle("; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn * GeV^{-1}]");
    TH1D *h_PV0Max_AllBut_Tri = (TH1D*) file_Tri->Get("h_PV0ScSmMax_AllBut");
    TH1D *h_PV0Max_AllBut_Rad = (TH1D*) file_Rad->Get("h_PV0ScSmMax_AllBut");
    TH1D *h_PV0Max_AllBut_WAB = (TH1D*) file_WAB->Get("h_PV0ScSmMax_AllBut");

    double bw = h_PV0Max_AllBut_Data->GetBinWidth(10);

    h_PV0Max_AllBut_Data->Scale(1 / (bw * Lumin8099));
    h_PV0Max_AllBut_Data->SetLineColor(1);
    h_PV0Max_AllBut_Tri->SetLineColor(4);
    h_PV0Max_AllBut_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));
    h_PV0Max_AllBut_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));
    h_PV0Max_AllBut_Rad->SetLineColor(2);
    h_PV0Max_AllBut_WAB->Scale(Wab_SigmaGen / (bw * NGen_Wab));
    h_PV0Max_AllBut_WAB->SetLineColor(45);


    h_PV0Max_AllBut_Data->Draw();
    h_PV0Max_AllBut_Tri->Draw("hist same");
    h_PV0Max_AllBut_Rad->Draw("hist same");
    h_PV0Max_AllBut_WAB->Draw("hist same");
    lat1->SetTextColor(1);
    lat1->DrawLatex(0.18, 0.8, "Data");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.18, 0.75, "Tri");
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.18, 0.7, "Rad");
    lat1->SetTextColor(45);
    lat1->DrawLatex(0.18, 0.65, "WAB");
    ctmp->Print("Figs/PV0ScSmMuxCut_AllBut.eps");
    ctmp->Print("Figs/PV0ScSmMuxCut_AllBut.pdf");
    ctmp->Print("Figs/PV0ScSmMuxCut_AllBut.png");

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
    h_d0_AllBut_Tri->SetLineWidth(2);

    TH1D *h_d0_AllBut_Rad = (TH1D*) file_Rad->Get("h_d0_ep_AllBut");
    h_d0_AllBut_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));
    h_d0_AllBut_Rad->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_Rad->SetLineColor(2);
    h_d0_AllBut_Rad->SetLineWidth(2);

    TH1D *h_d0_AllBut_WAB = (TH1D*) file_WAB->Get("h_d0_ep_AllBut");
    h_d0_AllBut_WAB->Scale(Wab_SigmaGen / (bw * NGen_Wab));
    h_d0_AllBut_WAB->SetTitle("; d_{0} [mm]; d#sigma/d d_{0} [bn/mm]");
    h_d0_AllBut_WAB->SetLineColor(45);
    h_d0_AllBut_WAB->SetLineWidth(2);

    TH1D *h_d0_AllBut_TriPlusWAB = (TH1D*) h_d0_AllBut_Tri->Clone("h_d0_AllBut_TriPlusWAB");
    h_d0_AllBut_TriPlusWAB->SetLineColor(95);
    h_d0_AllBut_TriPlusWAB->SetLineWidth(2);
    h_d0_AllBut_TriPlusWAB->Add(h_d0_AllBut_WAB);

    TLegend *leg1 = new TLegend(0.5, 0.35, 0.85, 0.7);
    leg1->SetBorderSize(0);
    leg1->AddEntry(h_d0_AllBut_TriPlusWAB, "TriTrig + WAB", "lg");
    leg1->AddEntry(h_d0_AllBut_Tri, "TriTrig", "lg");
    leg1->AddEntry(h_d0_AllBut_Rad, "Rad", "lg");
    leg1->AddEntry(h_d0_AllBut_WAB, "WAB", "lg");

    h_d0_AllBut_TriPlusWAB->Draw("hist");
    //h_d0_AllBut_Data->Draw("Same");
    h_d0_AllBut_Tri->Draw("hist Same");
    h_d0_AllBut_Rad->Draw("hist Same");
    h_d0_AllBut_WAB->Draw("hist Same");
    leg1->Draw();
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
    lat1->DrawLatex(0.4, 0.35, Form("Max FOM is at d_{0} = %1.2f mm", d0_FOM_MC));
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
    lat1->DrawLatex(0.42, 0.7, Form("#mu = %1.3f mm", mean_MC));
    lat1->DrawLatex(0.42, 0.65, Form("#sigma = %1.3f mm", sigm_MC));
    lat1->DrawLatex(0.42, 0.45, Form("d_{0}(MC) < %1.3f mm", d0_FOM_MC));
    line1->DrawLine(d0_FOM_MC, 0., d0_FOM_MC, 0.9 * h_d0_AllBut_TriPlusWAB->GetMaximum());
    ctmp->Print("Figs/d0_MC_Fit.eps");
    ctmp->Print("Figs/d0_MC_Fit.pdf");
    ctmp->Print("Figs/d0_MC_Fit.png");

    h_d0_AllBut_Data->Draw();
    f_Gaus->SetParameters(h_d0_AllBut_Data->GetMaximum(), 0, h_d0_AllBut_Data->GetRMS());
    h_d0_AllBut_Data->Fit(f_Gaus, "MeV", "", -0.7, 0.8);
    double mean_Data = f_Gaus->GetParameter(1);
    double sigm_Data = f_Gaus->GetParameter(2);
    double d0_FOM_Data = mean_Data + sigm_Data * (d0_FOM_MC - mean_MC) / sigm_MC;
    lat1->DrawLatex(0.42, 0.7, Form("#mu = %1.3f mm", mean_Data));
    lat1->DrawLatex(0.42, 0.65, Form("#sigma = %1.3f mm", sigm_Data));
    lat1->DrawLatex(0.42, 0.45, Form("d_{0}(Data) < %1.3f mm", d0_FOM_Data));
    line1->DrawLine(d0_FOM_Data, 0., d0_FOM_Data, 0.9 * h_d0_AllBut_Data->GetMaximum());
    ctmp->Print("Figs/d0_Data_Fit.eps");
    ctmp->Print("Figs/d0_Data_Fit.pdf");
    ctmp->Print("Figs/d0_Data_Fit.png");

    delete ctmp;
}

void DrawLarged0hists(TFile** files, std::string histNameBase, std::string Title) {

    TCanvas *c1D = new TCanvas("c1D", "", 950, 950);

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

    double Max_All = 0;
    TH1D *h_Data = (TH1D*) file_Data->Get(Form("h_%s", histNameBase.c_str()));
    h_Data->SetTitle(Title.c_str());
    double bw = h_Data->GetBinWidth(10);
    h_Data->Sumw2();
    h_Data->SetLineColor(1);
    h_Data->Scale(1. / (bw * Lumin8099));
    Max_All = TMath::Max(Max_All, h_Data->GetMaximum());

    TH1D *h_Tri = (TH1D*) file_Tri->Get(Form("h_%s", histNameBase.c_str()));
    h_Tri->SetTitle(Title.c_str());
    h_Tri->Sumw2();
    h_Tri->SetLineColor(4);
    h_Tri->Scale(tritrig_SigmaGen / (bw * NGen_tritrig));

    TH1D *h_Rad = (TH1D*) file_Rad->Get(Form("h_%s", histNameBase.c_str()));
    h_Rad->SetTitle(Title.c_str());
    h_Rad->Sumw2();
    h_Rad->SetLineColor(2);
    h_Rad->Scale(Rad_SigmaGen / (bw * NGen_Rad));

    TH1D *h_WAB = (TH1D*) file_WAB->Get(Form("h_%s", histNameBase.c_str()));
    h_WAB->SetTitle(Title.c_str());
    h_WAB->Sumw2();
    h_WAB->SetLineColor(42);
    h_WAB->Scale(Wab_SigmaGen / (bw * NGen_Wab));


    TH1D *h_TriPlusWab = (TH1D*) h_Tri->Clone("h_TriPlusWab");
    h_TriPlusWab->Add(h_WAB);
    h_TriPlusWab->SetLineColor(95);
    Max_All = TMath::Max(Max_All, h_TriPlusWab->GetMaximum());


    h_Data->SetMaximum(1.05 * Max_All);

    TRatioPlot *rp = new TRatioPlot(h_Data, h_TriPlusWab, "divsym");
    rp->GetUpperPad()->SetBottomMargin(0);
    rp->GetLowerPad()->SetTopMargin(0);
    rp->Draw();
    rp->GetUpperPad()->cd();
    h_Tri->Draw("Same");
    h_Rad->Draw("Same");
    h_WAB->Draw("Same");
    rp->GetLowerRefGraph()->SetMaximum(1.35);
    rp->GetLowerRefGraph()->SetMinimum(0.65);
    c1D->Update();
    c1D->Print(Form("Figs/%s_All.eps", histNameBase.c_str()));
    c1D->Print(Form("Figs/%s_All.pdf", histNameBase.c_str()));
    c1D->Print(Form("Figs/%s_All.png", histNameBase.c_str()));

    c1D->Clear();

    c1D->Print(Form("WABStudy_%s.eps", histNameBase.c_str()));
    c1D->Print(Form("WABStudy_%s.pdf", histNameBase.c_str()));
    c1D->Print(Form("WABStudy_%s.png", histNameBase.c_str()));

    delete rp;

}

void WriteSingleV0CutFractins(TFile** files) {
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

    TH1D *h_PV00_Data = (TH1D*) file_Data->Get("h_PV0_General_Final_0");
    double NV0_Data_0 = h_PV00_Data->Integral();
    TH1D *h_PV01_Data = (TH1D*) file_Data->Get("h_PV0_General_Final_1");
    double NV0_Data_1 = h_PV01_Data->Integral();
    double beforeCut_Data = NV0_Data_0 + NV0_Data_1;
    double Ratio_Data = NV0_Data_1 / (NV0_Data_0 + NV0_Data_1);

    TH1D *h_PV00_Tri = (TH1D*) file_Tri->Get("h_PV0_General_Final_0");
    h_PV00_Tri->Scale(tritrig_SigmaGen / (NGen_tritrig));
    double NV0_Tri_0 = h_PV00_Tri->Integral();
    TH1D *h_PV01_Tri = (TH1D*) file_Tri->Get("h_PV0_General_Final_1");
    h_PV01_Tri->Scale(tritrig_SigmaGen / (NGen_tritrig));
    double NV0_Tri_1 = h_PV01_Tri->Integral();
    double Ratio_Tri = NV0_Tri_1 / (NV0_Tri_0 + NV0_Tri_1);

    TH1D *h_PV00_Rad = (TH1D*) file_Rad->Get("h_PV0_General_Final_0");
    double NV0_Rad_0 = h_PV00_Rad->Integral();
    TH1D *h_PV01_Rad = (TH1D*) file_Rad->Get("h_PV0_General_Final_1");
    double NV0_Rad_1 = h_PV01_Rad->Integral();
    double Ratio_Rad = NV0_Rad_1 / (NV0_Rad_0 + NV0_Rad_1);

    TH1D *h_PV00_WAB = (TH1D*) file_WAB->Get("h_PV0_General_Final_0");
    h_PV00_WAB->Scale(Wab_SigmaGen / NGen_Wab);
    double NV0_WAB_0 = h_PV00_WAB->Integral();
    TH1D *h_PV01_WAB = (TH1D*) file_WAB->Get("h_PV0_General_Final_1");
    h_PV01_WAB->Scale(Wab_SigmaGen / (NGen_Wab));
    double NV0_WAB_1 = h_PV01_WAB->Integral();
    double Ratio_WAB = NV0_WAB_1 / (NV0_WAB_0 + NV0_WAB_1);

    double NV0_TriPlusWAB_0 = NV0_Tri_0 + NV0_WAB_0;
    double NV0_TriPlusWAB_1 = NV0_Tri_1 + NV0_WAB_1;
    double Ratio_TriPlusWAB = NV0_TriPlusWAB_1 / (NV0_TriPlusWAB_0 + NV0_TriPlusWAB_1);


    CutFractions << setw(25) << "Single V0 " << setw(12) << " & " << Form("%1.3e", beforeCut_Data) << " & " << Ratio_Data << setw(12) << " & " << Ratio_Tri
            << setw(12) << " & " << Ratio_Rad << setw(12) << " & " << Ratio_WAB << setw(12) << " & " << Ratio_TriPlusWAB << " \\\\ \\hline" << endl;

}