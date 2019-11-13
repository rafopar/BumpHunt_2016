/* 
 * File:   DrawTrkClustCuts.cc
 * Author: rafopar
 *
 * Created on October 21, 2019, 3:50 PM
 */

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include "setting_2016_pass1.h"
#include "InitSettings.C"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    if (argc >= 2) {

        dataSet = argv[1];

        if (!(dataSet.compare("Data") == 0 || dataSet.compare("MC") == 0)) {
            cout << "The 1st argument should be data set, and it should be either \"Data\" or \"MC\" " << endl;
            cout << "Exiting" << endl;
            exit(1);
        }

        if (dataSet.compare("Data") == 0) {
            isData = true;
        } else {
            isData = false;
        }

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./EventSelection.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }

    InitVariables(dataSet);

    TCanvas *c1 = new TCanvas("c1", "", 900, 900);

    TFile *file_in = new TFile(Form("TrkClustMatching_%s.root", dataSet.c_str()), "Read");

    TH2D *h_dX_P_WithL6_TopPos1 = (TH2D*) file_in->Get("h_dX_P_WithL6_TopPos1");
    h_dX_P_WithL6_TopPos1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_NoL6_TopPos1 = (TH2D*) file_in->Get("h_dX_P_NoL6_TopPos1");
    h_dX_P_NoL6_TopPos1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_WithL6_BotPos1 = (TH2D*) file_in->Get("h_dX_P_WithL6_BotPos1");
    h_dX_P_WithL6_BotPos1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_NoL6_BotPos1 = (TH2D*) file_in->Get("h_dX_P_NoL6_BotPos1");
    h_dX_P_NoL6_BotPos1->SetTitle("; P [GeV] ; dX [mm]");

    c1->Divide(2, 2);

    c1->cd(1);
    h_dX_P_WithL6_TopPos1->SetAxisRange(0.3, 1.9);
    h_dX_P_WithL6_TopPos1->Draw("colz");
    f_dXTopWithL6Pos_TightUpperLim->Draw("Same");
    f_dXTopWithL6Pos_TightLowerLim->Draw("Same");

    c1->cd(2);
    h_dX_P_NoL6_TopPos1->SetAxisRange(0.3, 1.9);
    h_dX_P_NoL6_TopPos1->Draw("colz");
    f_dXTopNoL6Pos_TightUpperLim->Draw("Same");
    f_dXTopNoL6Pos_TightLowerLim->Draw("Same");

    c1->cd(3);
    h_dX_P_WithL6_BotPos1->SetAxisRange(0.3, 1.9);
    h_dX_P_WithL6_BotPos1->Draw("colz");
    f_dXBotWithL6Pos_TightUpperLim->Draw("Same");
    f_dXBotWithL6Pos_TightLowerLim->Draw("Same");

    c1->cd(4);
    h_dX_P_NoL6_BotPos1->SetAxisRange(0.3, 1.9);
    h_dX_P_NoL6_BotPos1->Draw("colz");
    f_dXBotNoL6Pos_TightUpperLim->Draw("Same");
    f_dXBotNoL6Pos_TightLowerLim->Draw("Same");

    c1->Print(Form("Figs/dX_P_cuts_pos1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_cuts_pos1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_cuts_pos1_%s.png", dataSet.c_str()));




    TH2D *h_dX_P_WithL6_TopNeg1 = (TH2D*) file_in->Get("h_dX_P_WithL6_TopNeg1");
    h_dX_P_WithL6_TopNeg1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_NoL6_TopNeg1 = (TH2D*) file_in->Get("h_dX_P_NoL6_TopNeg1");
    h_dX_P_NoL6_TopNeg1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_WithL6_BotNeg1 = (TH2D*) file_in->Get("h_dX_P_WithL6_BotNeg1");
    h_dX_P_WithL6_BotNeg1->SetTitle("; P [GeV] ; dX [mm]");
    TH2D *h_dX_P_NoL6_BotNeg1 = (TH2D*) file_in->Get("h_dX_P_NoL6_BotNeg1");
    h_dX_P_NoL6_BotNeg1->SetTitle("; P [GeV] ; dX [mm]");


    c1->Clear();
    c1->Divide(2, 2);

    c1->cd(1);
    h_dX_P_WithL6_TopNeg1->SetAxisRange(0.3, 1.9);
    h_dX_P_WithL6_TopNeg1->Draw("colz");
    f_dXTopWithL6Neg_TightUpperLim->Draw("Same");
    f_dXTopWithL6Neg_TightLowerLim->Draw("Same");

    c1->cd(2);
    h_dX_P_NoL6_TopNeg1->SetAxisRange(0.3, 1.9);
    h_dX_P_NoL6_TopNeg1->Draw("colz");
    f_dXTopNoL6Neg_TightUpperLim->Draw("Same");
    f_dXTopNoL6Neg_TightLowerLim->Draw("Same");

    c1->cd(3);
    h_dX_P_WithL6_BotNeg1->SetAxisRange(0.3, 1.9);
    h_dX_P_WithL6_BotNeg1->Draw("colz");
    f_dXBotWithL6Neg_TightUpperLim->Draw("Same");
    f_dXBotWithL6Neg_TightLowerLim->Draw("Same");

    c1->cd(4);
    h_dX_P_NoL6_BotNeg1->SetAxisRange(0.3, 1.9);
    h_dX_P_NoL6_BotNeg1->Draw("colz");
    f_dXBotNoL6Neg_TightUpperLim->Draw("Same");
    f_dXBotNoL6Neg_TightLowerLim->Draw("Same");

    c1->Print(Form("Figs/dX_P_cuts_neg1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_cuts_neg1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_cuts_neg1_%s.png", dataSet.c_str()));



    TH2D *h_dY_P_WithL6_TopPos1 = (TH2D*) file_in->Get("h_dY_P_WithL6_TopPos1");
    h_dY_P_WithL6_TopPos1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_NoL6_TopPos1 = (TH2D*) file_in->Get("h_dY_P_NoL6_TopPos1");
    h_dY_P_NoL6_TopPos1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_WithL6_BotPos1 = (TH2D*) file_in->Get("h_dY_P_WithL6_BotPos1");
    h_dY_P_WithL6_BotPos1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_NoL6_BotPos1 = (TH2D*) file_in->Get("h_dY_P_NoL6_BotPos1");
    h_dY_P_NoL6_BotPos1->SetTitle("; P [GeV] ; dY [mm]");

    c1->Clear();
    c1->Divide(2, 2);

    c1->cd(1);
    h_dY_P_WithL6_TopPos1->SetAxisRange(0.3, 1.9);
    h_dY_P_WithL6_TopPos1->Draw("colz");

    c1->cd(2);
    h_dY_P_NoL6_TopPos1->SetAxisRange(0.3, 1.9);
    h_dY_P_NoL6_TopPos1->Draw("colz");

    c1->cd(3);
    h_dY_P_WithL6_BotPos1->SetAxisRange(0.3, 1.9);
    h_dY_P_WithL6_BotPos1->Draw("colz");

    c1->cd(4);
    h_dY_P_NoL6_BotPos1->SetAxisRange(0.3, 1.9);
    h_dY_P_NoL6_BotPos1->Draw("colz");

    c1->Print(Form("Figs/dY_P_cuts_pos1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_cuts_pos1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_cuts_pos1_%s.png", dataSet.c_str()));


    TH2D *h_dY_P_WithL6_TopNeg1 = (TH2D*) file_in->Get("h_dY_P_WithL6_TopNeg1");
    h_dY_P_WithL6_TopNeg1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_NoL6_TopNeg1 = (TH2D*) file_in->Get("h_dY_P_NoL6_TopNeg1");
    h_dY_P_NoL6_TopNeg1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_WithL6_BotNeg1 = (TH2D*) file_in->Get("h_dY_P_WithL6_BotNeg1");
    h_dY_P_WithL6_BotNeg1->SetTitle("; P [GeV] ; dY [mm]");
    TH2D *h_dY_P_NoL6_BotNeg1 = (TH2D*) file_in->Get("h_dY_P_NoL6_BotNeg1");
    h_dY_P_NoL6_BotNeg1->SetTitle("; P [GeV] ; dY [mm]");


    c1->Clear();
    c1->Divide(2, 2);

    c1->cd(1);
    h_dY_P_WithL6_TopNeg1->SetAxisRange(0.3, 1.9);
    h_dY_P_WithL6_TopNeg1->Draw("colz");

    c1->cd(2);
    h_dY_P_NoL6_TopNeg1->SetAxisRange(0.3, 1.9);
    h_dY_P_NoL6_TopNeg1->Draw("colz");

    c1->cd(3);
    h_dY_P_WithL6_BotNeg1->SetAxisRange(0.3, 1.9);
    h_dY_P_WithL6_BotNeg1->Draw("colz");

    c1->cd(4);
    h_dY_P_NoL6_BotNeg1->SetAxisRange(0.3, 1.9);
    h_dY_P_NoL6_BotNeg1->Draw("colz");

    c1->Print(Form("Figs/dY_P_cuts_neg1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_cuts_neg1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_cuts_neg1_%s.png", dataSet.c_str()));

    c1->Clear();

    TH2D *h_L6_Yxc_pos1 = (TH2D*) file_in->Get("h_L5_Yxc_pos1");
    h_L6_Yxc_pos1->SetTitle("; Layer 5 X [mm]; Layer 5 Y [mm]");
    h_L6_Yxc_pos1->Draw("colz");
    c1->Print(Form("Figs/L5_YXc_pos1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/L5_YXc_pos1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/L5_YXc_pos1_%s.png", dataSet.c_str()));

    TH2D * h_trkCl_dt_P_Top = (TH2D*) file_in->Get("h_trkCl_dt_P_Top");
    h_trkCl_dt_P_Top->SetTitle("; P [GeV]; t_{cl} - t_{trk} [ns]");
    h_trkCl_dt_P_Top->Draw("colz");
    f_trkCl_dt_Top_TightUpperLim->Draw("Same");
    f_trkCl_dt_Top_TightLowerLim->Draw("Same");
    c1->Print(Form("Figs/cl_trk_dt_Top_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/cl_trk_dt_Top_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/cl_trk_dt_Top_%s.png", dataSet.c_str()));

    TH2D * h_trkCl_dt_P_Bot = (TH2D*) file_in->Get("h_trkCl_dt_P_Bot");
    h_trkCl_dt_P_Bot->SetTitle("; P [GeV]; t_{cl} - t_{trk} [ns]");
    h_trkCl_dt_P_Bot->Draw("colz");
    f_trkCl_dt_Bot_TightUpperLim->Draw("Same");
    f_trkCl_dt_Bot_TightLowerLim->Draw("Same");
    c1->Print(Form("Figs/cl_trk_dt_Bot_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/cl_trk_dt_Bot_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/cl_trk_dt_Bot_%s.png", dataSet.c_str()));


    TFile *file_EvSelection = new TFile(Form("EventSelection_%s.root", dataSet.c_str()));


    TH2D *h_dY_Top_PosWithL6 = (TH2D*) file_EvSelection->Get("h_dY_Top_PosWithL6");
    h_dY_Top_PosWithL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Top_PosNoL6 = (TH2D*) file_EvSelection->Get("h_dY_Top_PosNoL6");
    h_dY_Top_PosNoL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Bot_PosWithL6 = (TH2D*) file_EvSelection->Get("h_dY_Bot_PosWithL6");
    h_dY_Bot_PosWithL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Bot_PosNoL6 = (TH2D*) file_EvSelection->Get("h_dY_Bot_PosNoL6");
    h_dY_Bot_PosNoL6->SetTitle("; P [GeV]; dY [mm]");


    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    h_dY_Top_PosWithL6->Draw("colz");
    c1->cd(2);
    h_dY_Top_PosNoL6->Draw("colz");
    c1->cd(3);
    h_dY_Bot_PosWithL6->Draw("colz");
    c1->cd(4);
    h_dY_Bot_PosNoL6->Draw("colz");
    c1->Print(Form("Figs/dY_P_pos_AfterTightCuts_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_pos_AfterTightCuts_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_pos_AfterTightCuts_%s.png", dataSet.c_str()));


    TH2D *h_dY_Top_NegWithL6 = (TH2D*) file_EvSelection->Get("h_dY_Top_NegWithL6");
    h_dY_Top_NegWithL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Top_NegNoL6 = (TH2D*) file_EvSelection->Get("h_dY_Top_NegNoL6");
    h_dY_Top_NegNoL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Bot_NegWithL6 = (TH2D*) file_EvSelection->Get("h_dY_Bot_NegWithL6");
    h_dY_Bot_NegWithL6->SetTitle("; P [GeV]; dY [mm]");
    TH2D *h_dY_Bot_NegNoL6 = (TH2D*) file_EvSelection->Get("h_dY_Bot_NegNoL6");
    h_dY_Bot_NegNoL6->SetTitle("; P [GeV]; dY [mm]");


    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    h_dY_Top_NegWithL6->Draw("colz");
    c1->cd(2);
    h_dY_Top_NegNoL6->Draw("colz");
    c1->cd(3);
    h_dY_Bot_NegWithL6->Draw("colz");
    c1->cd(4);
    h_dY_Bot_NegNoL6->Draw("colz");
    c1->Print(Form("Figs/dY_P_neg_AfterTightCuts_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_neg_AfterTightCuts_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dY_P_neg_AfterTightCuts_%s.png", dataSet.c_str()));



    TH2D *h_dX_Top_PosWithL6 = (TH2D*) file_EvSelection->Get("h_dX_Top_PosWithL6");
    h_dX_Top_PosWithL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Top_PosNoL6 = (TH2D*) file_EvSelection->Get("h_dX_Top_PosNoL6");
    h_dX_Top_PosNoL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Bot_PosWithL6 = (TH2D*) file_EvSelection->Get("h_dX_Bot_PosWithL6");
    h_dX_Bot_PosWithL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Bot_PosNoL6 = (TH2D*) file_EvSelection->Get("h_dX_Bot_PosNoL6");
    h_dX_Bot_PosNoL6->SetTitle("; P [GeV]; dX [mm]");


    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    h_dX_Top_PosWithL6->Draw("colz");
    c1->cd(2);
    h_dX_Top_PosNoL6->Draw("colz");
    c1->cd(3);
    h_dX_Bot_PosWithL6->Draw("colz");
    c1->cd(4);
    h_dX_Bot_PosNoL6->Draw("colz");
    c1->Print(Form("Figs/dX_P_pos_AfterTightCuts_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_pos_AfterTightCuts_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_pos_AfterTightCuts_%s.png", dataSet.c_str()));


    TH2D *h_dX_Top_NegWithL6 = (TH2D*) file_EvSelection->Get("h_dX_Top_NegWithL6");
    h_dX_Top_NegWithL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Top_NegNoL6 = (TH2D*) file_EvSelection->Get("h_dX_Top_NegNoL6");
    h_dX_Top_NegNoL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Bot_NegWithL6 = (TH2D*) file_EvSelection->Get("h_dX_Bot_NegWithL6");
    h_dX_Bot_NegWithL6->SetTitle("; P [GeV]; dX [mm]");
    TH2D *h_dX_Bot_NegNoL6 = (TH2D*) file_EvSelection->Get("h_dX_Bot_NegNoL6");
    h_dX_Bot_NegNoL6->SetTitle("; P [GeV]; dX [mm]");


    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    h_dX_Top_NegWithL6->Draw("colz");
    c1->cd(2);
    h_dX_Top_NegNoL6->Draw("colz");
    c1->cd(3);
    h_dX_Bot_NegWithL6->Draw("colz");
    c1->cd(4);
    h_dX_Bot_NegNoL6->Draw("colz");
    c1->Print(Form("Figs/dX_P_neg_AfterTightCuts_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_neg_AfterTightCuts_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dX_P_neg_AfterTightCuts_%s.png", dataSet.c_str()));


    c1->Clear();
    TH1D *h_Pem_TightCut1 = (TH1D*) file_EvSelection->Get("h_Pem_TightCut1");
    h_Pem_TightCut1->SetTitle("; P [GeV]");
    h_Pem_TightCut1->Draw();
    c1->Print(Form("Figs/P_emAfterTighCuts_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/P_emAfterTighCuts_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/P_emAfterTighCuts_%s.png", dataSet.c_str()));

    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    TH1D *h_d0_ep_topWithL1 = (TH1D*) file_EvSelection->Get("h_d0_ep_topWithL1");
    h_d0_ep_topWithL1->SetTitle("; d_{0} [mm]");
    h_d0_ep_topWithL1->Draw();
    c1->cd(2);
    TH1D *h_d0_ep_topNoL1 = (TH1D*) file_EvSelection->Get("h_d0_ep_topNoL1");
    h_d0_ep_topNoL1->SetTitle("; d_{0} [mm]");
    h_d0_ep_topNoL1->Draw();
    c1->cd(3);
    TH1D *h_d0_ep_botWithL1 = (TH1D*) file_EvSelection->Get("h_d0_ep_botWithL1");
    h_d0_ep_botWithL1->SetTitle("; d_{0} [mm]");
    h_d0_ep_botWithL1->Draw();
    c1->cd(4);
    TH1D *h_d0_ep_botNoL1 = (TH1D*) file_EvSelection->Get("h_d0_ep_botNoL1");
    h_d0_ep_botNoL1->SetTitle("; d_{0} [mm]");
    h_d0_ep_botNoL1->Draw();
    c1->Print(Form("Figs/d0_cuts_Positives_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/d0_cuts_Positives_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/d0_cuts_Positives_%s.png", dataSet.c_str()));


    c1->Clear();
    c1->Divide(2, 2);
    c1->cd(1);
    TH1D *h_d0_em_topWithL1 = (TH1D*) file_EvSelection->Get("h_d0_em_topWithL1");
    h_d0_em_topWithL1->SetTitle("; d_{0} [mm]");
    h_d0_em_topWithL1->Draw();
    c1->cd(2);
    TH1D *h_d0_em_topNoL1 = (TH1D*) file_EvSelection->Get("h_d0_em_topNoL1");
    h_d0_em_topNoL1->SetTitle("; d_{0} [mm]");
    h_d0_em_topNoL1->Draw();
    c1->cd(3);
    TH1D *h_d0_em_botWithL1 = (TH1D*) file_EvSelection->Get("h_d0_em_botWithL1");
    h_d0_em_botWithL1->SetTitle("; d_{0} [mm]");
    h_d0_em_botWithL1->Draw();
    c1->cd(4);
    TH1D *h_d0_em_botNoL1 = (TH1D*) file_EvSelection->Get("h_d0_em_botNoL1");
    h_d0_em_botNoL1->SetTitle("; d_{0} [mm]");
    h_d0_em_botNoL1->Draw();
    c1->Print(Form("Figs/d0_cuts_Negatives_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/d0_cuts_Negatives_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/d0_cuts_Negatives_%s.png", dataSet.c_str()));

    return 0;
}