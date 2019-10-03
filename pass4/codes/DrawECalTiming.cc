/* 
 * File:   DrawECalTiming.cc
 * Author: rafopar
 *
 * Created on October 3, 2019, 1:38 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>

#include <cstdlib>

#include "InitSettings.C"

using namespace std;

/*
 * 
 */
void DrawECalTiming() {

    InitVariables();

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);
    c1->SetLogz();
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.11);
    TFile *file_in = new TFile("EventSelection.root", "Read");

    TH2D *h_cl_E_tTop1 = (TH2D*) file_in->Get("h_cl_E_tTop1");
    h_cl_E_tTop1->SetTitle("; E_{cl} [GeV]; t_{cl} ns");
    h_cl_E_tTop1->SetStats(0);
    h_cl_E_tTop1->Draw("colz");
    c1->Print("Figs/cl_t_E_Top.eps");
    c1->Print("Figs/cl_t_E_Top.pdf");
    c1->Print("Figs/cl_t_E_Top.png");

    TH2D *h_cl_E_tBot1 = (TH2D*) file_in->Get("h_cl_E_tBot1");
    h_cl_E_tBot1->SetTitle("; E_{cl} [GeV]; t_{cl} ns");
    h_cl_E_tBot1->SetStats(0);
    h_cl_E_tBot1->Draw("colz");
    f_clTBotUpLim->Draw("Same");
    f_clTBotLowLim->Draw("Same");
    c1->Print("Figs/cl_t_E_Bot.eps");
    c1->Print("Figs/cl_t_E_Bot.pdf");
    c1->Print("Figs/cl_t_E_Bot.png");

    TFile *file_ECalTimeCorr = new TFile("ECalTimeCorrections.root", "Read");

    TCanvas *c_ECal = new TCanvas("c_ECal", "", 1400, 400);
    c_ECal->SetLeftMargin(0.05);
    c_ECal->SetRightMargin(0.09);
    c_ECal->SetTopMargin(0.012);

    TH2D *h_cl_dtMeans1 = (TH2D*) file_ECalTimeCorr->Get("h_cl_dtMeans1");
    h_cl_dtMeans1->SetTitle("; X_{Crystal}; Y_{Crystal}");
    h_cl_dtMeans1->SetStats(0);
    h_cl_dtMeans1->SetLabelSize(0.06, "Z");
    h_cl_dtMeans1->SetLabelSize(0.06, "Y");
    h_cl_dtMeans1->SetLabelSize(0.06, "X");
    h_cl_dtMeans1->SetTitleOffset(0.3, "Y");
    h_cl_dtMeans1->SetTitleOffset(0.6, "X");
    h_cl_dtMeans1->SetTitleSize(0.06, "Y");
    h_cl_dtMeans1->SetTitleSize(0.06, "X");
    h_cl_dtMeans1->Draw("colz");
    c_ECal->Print("Figs/ECal_YX_timeCorr.eps");
    c_ECal->Print("Figs/ECal_YX_timeCorr.pdf");
    c_ECal->Print("Figs/ECal_YX_timeCorr.png");

    const int nECalrow = 5;
    int gr_Styles[nECalrow] = {20, 21, 22, 29, 33};
    int gr_Colors[nECalrow] = {1, 2, 4, 35, 96};

    TGraphErrors * gr_TopTCorr[nECalrow];
    TGraphErrors * gr_BotTCorr[nECalrow];
    TMultiGraph *mtgrTopCorr = new TMultiGraph();
    TMultiGraph *mtgrBotCorr = new TMultiGraph();

    TLegend *leg_TopCorr = new TLegend(0.92, 0.5, 0.999, 0.99);
    leg_TopCorr->SetBorderSize(0);

    TLegend *leg_BotCorr = new TLegend(0.92, 0.5, 0.999, 0.99);
    leg_BotCorr->SetBorderSize(0);

    for (int i = 0; i < 5; i++) {
        gr_TopTCorr[i] = (TGraphErrors*) file_ECalTimeCorr->Get(Form("gr_mean_dt_%d", i + 6));
        gr_TopTCorr[i]->SetMarkerSize(1.5);
        gr_TopTCorr[i]->SetMarkerColor(gr_Colors[i]);
        gr_TopTCorr[i]->SetMarkerStyle(gr_Styles[i]);
        mtgrTopCorr->Add(gr_TopTCorr[i]);
        leg_TopCorr->AddEntry(gr_TopTCorr[i], Form("Y=%d", i + 1), "lep");

        gr_BotTCorr[i] = (TGraphErrors*) file_ECalTimeCorr->Get(Form("gr_mean_dt_%d", i));
        gr_BotTCorr[i]->SetMarkerColor(gr_Colors[i]);
        gr_BotTCorr[i]->SetMarkerStyle(gr_Styles[i]);
        mtgrBotCorr->Add(gr_BotTCorr[i]);
        mtgrBotCorr->Add(gr_TopTCorr[i]);
        leg_BotCorr->AddEntry(gr_BotTCorr[i], Form("Y=%d", -5 + i), "lep");
    }

    mtgrTopCorr->Draw("AP");
    mtgrTopCorr->SetTitle("; X ; Time Corr [ns]");
    mtgrTopCorr->GetXaxis()->SetTitleSize(0.06);
    mtgrTopCorr->GetXaxis()->SetLabelSize(0.06);
    mtgrTopCorr->GetXaxis()->SetTitleOffset(0.6);
    mtgrTopCorr->GetYaxis()->SetTitleSize(0.06);
    mtgrTopCorr->GetYaxis()->SetLabelSize(0.06);
    mtgrTopCorr->GetYaxis()->SetTitleOffset(0.4);
    leg_TopCorr->Draw();
    c_ECal->Print("Figs/gr_TopCorrections.eps");
    c_ECal->Print("Figs/gr_TopCorrections.pdf");
    c_ECal->Print("Figs/gr_TopCorrections.png");

    c_ECal->Clear();
    mtgrBotCorr->Draw("AP");
    mtgrBotCorr->SetTitle("; X ; Time Corr [ns]");
    mtgrBotCorr->GetXaxis()->SetTitleSize(0.06);
    mtgrBotCorr->GetXaxis()->SetLabelSize(0.06);
    mtgrBotCorr->GetXaxis()->SetTitleOffset(0.6);
    mtgrBotCorr->GetYaxis()->SetTitleSize(0.06);
    mtgrBotCorr->GetYaxis()->SetLabelSize(0.06);
    mtgrBotCorr->GetYaxis()->SetTitleOffset(0.4);
    leg_BotCorr->Draw();
    c_ECal->Print("Figs/gr_BotCorrections.eps");
    c_ECal->Print("Figs/gr_BotCorrections.pdf");
    c_ECal->Print("Figs/gr_BotCorrections.png");

}

