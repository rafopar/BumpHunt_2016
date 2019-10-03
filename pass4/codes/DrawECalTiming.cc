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
#include <cstdlib>

using namespace std;

/*
 * 
 */
void DrawECalTiming() {

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);
    c1->SetLogz();
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.11);
    TFile *file_in = new TFile("EventSelection.root", "Read");
    
    TH2D *h_cl_E_tTop1 = (TH2D*)file_in->Get("h_cl_E_tTop1");
    h_cl_E_tTop1->SetTitle("; E_{cl} [GeV]; t_{cl} ns");
    h_cl_E_tTop1->SetStats(0);
    h_cl_E_tTop1->Draw("colz");
    c1->Print("Figs/cl_t_E_Top.eps");
    c1->Print("Figs/cl_t_E_Top.pdf");
    c1->Print("Figs/cl_t_E_Top.png");
    
    TH2D *h_cl_E_tBot1 = (TH2D*)file_in->Get("h_cl_E_tBot1");
    h_cl_E_tBot1->SetTitle("; E_{cl} [GeV]; t_{cl} ns");
    h_cl_E_tBot1->SetStats(0);
    h_cl_E_tBot1->Draw("colz");
    c1->Print("Figs/cl_t_E_Bot.eps");
    c1->Print("Figs/cl_t_E_Bot.pdf");
    c1->Print("Figs/cl_t_E_Bot.png");    
}

