/* 
 * File:   DrawRunByRunNormalizations.cc
 * Author: rafopar
 *
 * Created on January 30, 2020, 9:05 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <TFile.h>
#include <TH1D.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>

using namespace std;

/*
 * 
 */
void DrawRunByRunNormalizations() {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetLeftMargin(0.12);

    fstream runList("../lists/GoldenRunsLumin10Percent.dat");

    map<int, double> m_charge;

    int n_Combinations = 8; // 2^{3}

    TH1D * h_Minv_General_Final_[n_Combinations];
    TGraphErrors * gr_MinvInegral_equalFileNumbers[n_Combinations];
    TGraphErrors * gr_MinvInegral_FilesDiffer[n_Combinations];
    TMultiGraph *mtgr_MinvIntegral[n_Combinations];
    TFile *file_all = new TFile("../BlindedOutputs/EventSelection_Data_1000.root", "Read");

    c1->SetLogy();
    for (int i = 0; i < n_Combinations; i++) {
        gr_MinvInegral_equalFileNumbers[i] = new TGraphErrors();
        gr_MinvInegral_FilesDiffer[i] = new TGraphErrors();
        mtgr_MinvIntegral[i] = new TMultiGraph();
        h_Minv_General_Final_[i] = (TH1D*) file_all->Get(Form("h_Minv_General_Final_%d", i));
        h_Minv_General_Final_[i]->SetTitle(Form("Cut Category %d; M(ee) [GeV]; # of events/0.05 MeV", i));
        h_Minv_General_Final_[i]->Draw();
        c1->Print(Form("Figs/Minv_General_Final_Cut_%d.eps", i));
        c1->Print(Form("Figs/Minv_General_Final_Cut_%d.pdf", i));
        c1->Print(Form("Figs/Minv_General_Final_Cut_%d.png", i));
    }


    int ind_point_equalFileNumbers = 0;
    int ind_point_FilesDiffer = 0;
    while (!runList.eof()) {

        int run;
        double charge;
        double nfilesSpredsheet;
        double nfilesRecon;

        runList>>run;
        runList>>nfilesSpredsheet;
        runList>>charge;
        runList>>nfilesRecon;

        //if( nfilesSpredsheet != nfilesRecon ){continue;}

        TFile *cur_file = new TFile(Form("../BlindedOutputs/EventSelection_Data_%d.root", run), "Read");

        for (int ii = 0; ii < n_Combinations; ii++) {
            TH1D *h_cur_hist = (TH1D*) cur_file->Get(Form("h_Minv_General_Final_%d", ii));
            double IntegrError;
            double MinvIntegr = h_cur_hist->IntegralAndError(1, h_cur_hist->GetNbinsX(), IntegrError);
            MinvIntegr = MinvIntegr / ((nfilesRecon / nfilesSpredsheet) * charge);
            IntegrError = IntegrError / ((nfilesRecon / nfilesSpredsheet) * charge);


            if (nfilesSpredsheet == nfilesRecon) {
                gr_MinvInegral_equalFileNumbers[ii]->SetPoint(ind_point_equalFileNumbers, run, MinvIntegr);
                gr_MinvInegral_equalFileNumbers[ii]->SetPointError(ind_point_equalFileNumbers, 0., IntegrError);
            } else {
                gr_MinvInegral_FilesDiffer[ii]->SetPoint(ind_point_FilesDiffer, run, MinvIntegr);
                gr_MinvInegral_FilesDiffer[ii]->SetPointError(ind_point_FilesDiffer, 0., IntegrError);
            }
        }

        delete cur_file;
        if (nfilesSpredsheet == nfilesRecon) {
            ind_point_equalFileNumbers = ind_point_equalFileNumbers + 1;
        } else {
            ind_point_FilesDiffer = ind_point_FilesDiffer + 1;
        }
    }


    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    
    c1->SetLogy(0);
    for (int ii = 0; ii < n_Combinations; ii++) {
        gr_MinvInegral_equalFileNumbers[ii]->SetMarkerColor(4);
        gr_MinvInegral_equalFileNumbers[ii]->SetMarkerStyle(20);
        //gr_MinvInegral_equalFileNumbers[ii]->SetTitle("; Run; #of events/charge");
        //gr_MinvInegral_equalFileNumbers[ii]->GetXaxis()->SetLimits(7600, 8121);

        gr_MinvInegral_FilesDiffer[ii]->SetMarkerColor(2);
        gr_MinvInegral_FilesDiffer[ii]->SetMarkerStyle(22);
        //gr_MinvInegral_equalFileNumbers[ii]->SetTitle("; Run; #of events/charge");
        //gr_MinvInegral_equalFileNumbers[ii]->GetXaxis()->SetLimits(7600, 8121);
        
        //gr_MinvInegral[ii]->SetMinimum(0);
        
        mtgr_MinvIntegral[ii]->Add(gr_MinvInegral_equalFileNumbers[ii]);
        mtgr_MinvIntegral[ii]->Add(gr_MinvInegral_FilesDiffer[ii]);
        
        mtgr_MinvIntegral[ii]->Draw("AP");
        mtgr_MinvIntegral[ii]->SetTitle("; Run; #of events/charge");
        mtgr_MinvIntegral[ii]->GetXaxis()->SetLimits(7600, 8121);
        lat1->DrawLatex(0.35, 0.92, Form("Cut Category %d", ii));
        c1->Print(Form("Figs/RuntoRumMinvIntegral_Category_%d.eps", ii));
        c1->Print(Form("Figs/RuntoRumMinvIntegral_Category_%d.pdf", ii));
        c1->Print(Form("Figs/RuntoRumMinvIntegral_Category_%d.png", ii));
    }
}

