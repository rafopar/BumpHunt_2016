/* 
 * File:   NormalizationPlots.cc
 * Author: rafopar
 *
 * Created on November 25, 2019, 11:21 AM
 */

#include <TH1D.h>
#include <TFile.h>
#include <cstdlib>
#include <TLatex.h>
//#include "setting_2016_pass1.h"

using namespace std;

void DrawDatMCComparison(TFile** files, std::string histNameBase, std::string Title, int nDim);
void AddErrorAllBins(TH1D* h, double RelErr);

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
    h_Psum3_Data->SetLineColor(1);

    TFile *file_EvSelection_Wab = new TFile("EventSelection_WAB.root", "Read");

    TH1D *h_Psum3_Wab = (TH1D*) file_EvSelection_Wab->Get("h_Psum3");
    h_Psum3_Wab->SetTitle("; P_{Sum} [GeV]");
    h_Psum3_Wab->Scale(Wab_SigmaGen / NGen_Wab);
    h_Psum3_Wab->SetLineColor(45);

    TFile *file_EvSelection_Rad = new TFile("EventSelection_Rad.root", "Read");

    TH1D *h_Psum3_Rad = (TH1D*) file_EvSelection_Rad->Get("h_Psum3");
    h_Psum3_Rad->SetTitle("; P_{Sum} [GeV]");
    h_Psum3_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    h_Psum3_Rad->SetLineColor(2);


    TFile *file_EvSelection_Tri = new TFile("EventSelection_Tri.root", "Read");

    TH1D *h_Psum3_Tri = (TH1D*) file_EvSelection_Tri->Get("h_Psum3");
    h_Psum3_Tri->SetTitle("; P_{Sum} [GeV]");
    h_Psum3_Tri->Scale(tritrig_SigmaGen / NGen_tritrig);
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
    h_Psum3_Data->Scale(1 / Lumin8099);
    h_Psum3_Data->Draw("Same");
    lat1->SetTextColor(1);
    lat1->DrawLatex(0.3, 0.5, "Data");
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

    DrawDatMCComparison(files_EvSelection, "PsumMax", "; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "PsumMin", "; P_{Sum} [GeV]; d#sigma/dP_{Sum} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "clDt", "; Cluster #Delta t [ns]; d#sigma/d #Delta t [bn/ns] ", 1);
    DrawDatMCComparison(files_EvSelection, "Pem", "; P_{e^{-}} [GeV]; d#sigma/d P_{e^{-}} [bn/GeV] ", 1);
    DrawDatMCComparison(files_EvSelection, "d0_ep", "; d_{0}(e^{+}) [m]; d#sigma/d d_{0}(e^{+}) [bn/mm] ", 1);
    DrawDatMCComparison(files_EvSelection, "em_cl_trk_dT", "; P_{e^{-}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "ep_cl_trk_dT", "; P_{e^{+}} [GeV]; t_{cl} - t_{trk} [ns]", 2);
    DrawDatMCComparison(files_EvSelection, "dX_em", "; P_{e^{-}} [GeV]; X_{cl} - X_{trk} [mm]", 2);

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
        h_Data_All->Scale(1 / Lumin8099);
        TH1D *h_Data_AllBut = (TH1D*) file_Data->Get(Form("h_%s_AllBut", histNameBase.c_str()));
        h_Data_AllBut->Sumw2();
        h_Data_AllBut->SetLineColor(1);
        h_Data_AllBut->SetTitle(Title.c_str());
        h_Data_AllBut->Scale(1 / Lumin8099);
        TH1D *h_Data_CutEffect = (TH1D*) file_Data->Get(Form("h_%s_CutEffect", histNameBase.c_str()));
        h_Data_CutEffect->Sumw2();
        h_Data_CutEffect->SetLineColor(1);
        h_Data_CutEffect->SetTitle(Title.c_str());
        h_Data_CutEffect->Scale(1 / Lumin8099);

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

        TH1D *hTriPlusWab_All = (TH1D*) h_Tri_All->Clone("hTriPlusWab_All");
        hTriPlusWab_All->Add(h_WAB_All);
        hTriPlusWab_All->SetLineColor(95);
        TH1D *hTriPlusWab_AllBut = (TH1D*) h_Tri_AllBut->Clone("hTriPlusWab_AllBut");
        hTriPlusWab_AllBut->Add(h_WAB_AllBut);
        hTriPlusWab_AllBut->SetLineColor(95);
        TH1D *hTriPlusWab_CutEffect = (TH1D*) h_Tri_CutEffect->Clone("hTriPlusWab_CutEffect");
        hTriPlusWab_CutEffect->Add(h_WAB_CutEffect);
        hTriPlusWab_CutEffect->SetLineColor(95);

        double MaxArray_All[5] = {h_Data_All->GetMaximum(), h_Tri_All->GetMaximum(), h_Rad_All->GetMaximum(), h_WAB_All->GetMaximum(), hTriPlusWab_All->GetMaximum()};
        double Max_All = TMath::MaxElement<double>(5, MaxArray_All);

        double MaxArray_AllBut[5] = {h_Data_AllBut->GetMaximum(), h_Tri_AllBut->GetMaximum(), h_Rad_AllBut->GetMaximum(), h_WAB_AllBut->GetMaximum(),
            hTriPlusWab_AllBut->GetMaximum()};
        double Max_AllBut = TMath::MaxElement<double>(5, MaxArray_AllBut);

        double MaxArray_CutEffect[5] = {h_Data_CutEffect->GetMaximum(), h_Tri_CutEffect->GetMaximum(), h_Rad_CutEffect->GetMaximum(), h_WAB_CutEffect->GetMaximum(),
            hTriPlusWab_CutEffect->GetMaximum()};
        double Max_CutEffect = TMath::MaxElement<double>(5, MaxArray_CutEffect);


        h_Data_All->SetMaximum(1.05 * Max_All);
        h_Data_All->Draw();
        h_Tri_All->Draw("Same");
        h_Rad_All->Draw("Same");
        h_WAB_All->Draw("Same");
        hTriPlusWab_All->Draw("Same");
        c1D->Print(Form("Figs/%s_All.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_All.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_All.png", histNameBase.c_str()));

        h_Data_AllBut->SetMaximum(1.05 * Max_AllBut);
        h_Data_AllBut->Draw();
        h_Tri_AllBut->Draw("Same");
        h_Rad_AllBut->Draw("Same");
        h_WAB_AllBut->Draw("Same");
        hTriPlusWab_AllBut->Draw("Same");
        c1D->Print(Form("Figs/%s_AllBut.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_AllBut.png", histNameBase.c_str()));

        h_Data_CutEffect->SetMaximum(1.05 * Max_AllBut);
        h_Data_CutEffect->Draw();
        h_Tri_CutEffect->Draw("Same");
        h_Rad_CutEffect->Draw("Same");
        h_WAB_CutEffect->Draw("Same");
        hTriPlusWab_CutEffect->Draw("Same");
        c1D->Print(Form("Figs/%s_CutEffect.eps", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.pdf", histNameBase.c_str()));
        c1D->Print(Form("Figs/%s_CutEffect.png", histNameBase.c_str()));


    } else if (nDim == 2) {

        TCanvas *c2D = new TCanvas("c1D", "", 950, 950);
        c2D->SetLeftMargin(0.15);

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

    }

}

void AddErrorAllBins(TH1D* h, double RelErr) {

    for (int i = 0; i < h->GetNbinsX(); i++) {

        double cur_err = h->GetBinError(i + 1);
        double binCont = h->GetBinContent(i + 1);
        h->SetBinError(i + 1, sqrt(cur_err * cur_err + binCont * binCont * RelErr * RelErr));
    }

}