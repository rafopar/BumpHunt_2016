/* 
 * File:   DrawEvSelectionCutPlots.cc
 * Author: rafopar
 *
 * Created on November 17, 2019, 1:20 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TCanvas.h>

#include <cstdlib>

using namespace std;

/*
 * 
 */
void DrawEvSelectionCutPlots() {


    TCanvas *c1 = new TCanvas("c1", "", 900, 900);

    std::string dataType = "Data";
    
    TFile *file_EvSelectionHists = new TFile(Form("EvSelectionCutHists_%s.root", dataType.c_str()), "Read");

    TH2D *h_trkCl_dt_P_Top = (TH2D*) file_EvSelectionHists->Get("h_trkCl_dt_P_Top");
    h_trkCl_dt_P_Top->SetTitle("; P [GeV]; t_{cl} - t_{tr} [ns]");

    TH2D *h_trkCl_dt_P_Top_Cut = (TH2D*) file_EvSelectionHists->Get("h_trkCl_dt_P_Top_Cut");
    h_trkCl_dt_P_Top_Cut->SetTitle("; P [GeV]; t_{cl} - t_{tr} [ns]");
    h_trkCl_dt_P_Top_Cut->SetMarkerColor(2);
    h_trkCl_dt_P_Top_Cut->SetMarkerStyle(20);
    h_trkCl_dt_P_Top_Cut->SetMarkerSize(0.8);

    h_trkCl_dt_P_Top->Draw("colz");
    h_trkCl_dt_P_Top_Cut->Draw("Same");
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Top_%s.eps", dataType.c_str()));
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Top_%s.pdf", dataType.c_str()));
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Top_%s.png", dataType.c_str()));


    TH2D *h_trkCl_dt_P_Bot = (TH2D*) file_EvSelectionHists->Get("h_trkCl_dt_P_Bot");
    h_trkCl_dt_P_Bot->SetTitle("; P [GeV]; t_{cl} - t_{tr} [ns]");

    TH2D *h_trkCl_dt_P_Bot_Cut = (TH2D*) file_EvSelectionHists->Get("h_trkCl_dt_P_Bot_Cut");
    h_trkCl_dt_P_Bot_Cut->SetTitle("; P [GeV]; t_{cl} - t_{tr} [ns]");
    h_trkCl_dt_P_Bot_Cut->SetMarkerColor(2);
    h_trkCl_dt_P_Bot_Cut->SetMarkerStyle(20);
    h_trkCl_dt_P_Bot_Cut->SetMarkerSize(0.8);

    h_trkCl_dt_P_Bot->Draw("colz");
    h_trkCl_dt_P_Bot_Cut->Draw("Same");
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Bot_%s.eps", dataType.c_str()));
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Bot_%s.pdf", dataType.c_str()));
    c1->Print(Form("Figs/trk_cl_timeDiffCut_Bot_%s.png", dataType.c_str()));


    TFile *file_DataEvSelection = new TFile(Form("EventSelection_%s.root", dataType.c_str()), "Read");

    TH2D *h_dX_Bot_NegNoL6_Test = (TH2D*) file_DataEvSelection->Get("h_dX_Bot_NegNoL6");
    h_dX_Bot_NegNoL6_Test->SetTitle("; P [GeV]; X_{cl} - X_{tr} [mm]");
    h_dX_Bot_NegNoL6_Test->Draw("colz");
    c1->Print("Figs/dX_Bot_NegNoL6_Data_TEST.eps");
    c1->Print("Figs/dX_Bot_NegNoL6_Data_TEST.pdf");
    c1->Print("Figs/dX_Bot_NegNoL6_Data_TEST.png");

    TH2D *h_cl_yxc_TEST1 = (TH2D*) file_DataEvSelection->Get("h_cl_yxc_TEST1");
    h_cl_yxc_TEST1->SetTitle("; X_{cl} [mm]; Y_{cl} [mm]");
    h_cl_yxc_TEST1->Draw("colz");
    c1->Print("Figs/cl_yxc_OutsidedTrkClMatching.eps");
    c1->Print("Figs/cl_yxc_OutsidedTrkClMatching.pdf");
    c1->Print("Figs/cl_yxc_OutsidedTrkClMatching.png");

    TH2D *h_dX_Top_PosWithL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_PosWithL6");
    h_dX_Top_PosWithL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_PosWithL6->Draw("colz");

    TH2D *h_dX_Top_PosWithL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_PosWithL6_Cut");
    h_dX_Top_PosWithL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_PosWithL6_Cut->SetMarkerColor(2);
    h_dX_Top_PosWithL6_Cut->SetMarkerStyle(20);
    h_dX_Top_PosWithL6_Cut->SetMarkerSize(0.7);
    h_dX_Top_PosWithL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Top_PosWithL6_Cut.eps");
    c1->Print("Figs/dX_Top_PosWithL6_Cut.pdf");
    c1->Print("Figs/dX_Top_PosWithL6_Cut.png");

    TH2D *h_dX_Top_PosNoL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_PosNoL6");
    h_dX_Top_PosNoL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_PosNoL6->Draw("colz");

    TH2D *h_dX_Top_PosNoL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_PosNoL6_Cut");
    h_dX_Top_PosNoL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_PosNoL6_Cut->SetMarkerColor(2);
    h_dX_Top_PosNoL6_Cut->SetMarkerStyle(20);
    h_dX_Top_PosNoL6_Cut->SetMarkerSize(0.7);
    h_dX_Top_PosNoL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Top_PosNoL6_Cut.eps");
    c1->Print("Figs/dX_Top_PosNoL6_Cut.pdf");
    c1->Print("Figs/dX_Top_PosNoL6_Cut.png");

    TH2D *h_dX_Bot_PosWithL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_PosWithL6");
    h_dX_Bot_PosWithL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_PosWithL6->Draw("colz");
    TH2D *h_dX_Bot_PosWithL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_PosWithL6_Cut");
    h_dX_Bot_PosWithL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_PosWithL6_Cut->SetMarkerColor(2);
    h_dX_Bot_PosWithL6_Cut->SetMarkerStyle(20);
    h_dX_Bot_PosWithL6_Cut->SetMarkerSize(0.7);
    h_dX_Bot_PosWithL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Bot_PosWithL6_Cut.eps");
    c1->Print("Figs/dX_Bot_PosWithL6_Cut.pdf");
    c1->Print("Figs/dX_Bot_PosWithL6_Cut.png");

    TH2D *h_dX_Bot_PosNoL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_PosNoL6");
    h_dX_Bot_PosNoL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_PosNoL6->Draw("colz");

    TH2D *h_dX_Bot_PosNoL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_PosNoL6_Cut");
    h_dX_Bot_PosNoL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_PosNoL6_Cut->SetMarkerColor(2);
    h_dX_Bot_PosNoL6_Cut->SetMarkerStyle(20);
    h_dX_Bot_PosNoL6_Cut->SetMarkerSize(0.7);
    h_dX_Bot_PosNoL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Bot_PosNoL6_Cut.eps");
    c1->Print("Figs/dX_Bot_PosNoL6_Cut.pdf");
    c1->Print("Figs/dX_Bot_PosNoL6_Cut.png");


    TH2D *h_dX_Top_NegWithL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_NegWithL6");
    h_dX_Top_NegWithL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_NegWithL6->Draw("colz");

    TH2D *h_dX_Top_NegWithL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_NegWithL6_Cut");
    h_dX_Top_NegWithL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_NegWithL6_Cut->SetMarkerColor(2);
    h_dX_Top_NegWithL6_Cut->SetMarkerStyle(20);
    h_dX_Top_NegWithL6_Cut->SetMarkerSize(0.7);
    h_dX_Top_NegWithL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Top_NegWithL6_Cut.eps");
    c1->Print("Figs/dX_Top_NegWithL6_Cut.pdf");
    c1->Print("Figs/dX_Top_NegWithL6_Cut.png");

    TH2D *h_dX_Top_NegNoL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_NegNoL6");
    h_dX_Top_NegNoL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_NegNoL6->Draw("colz");

    TH2D *h_dX_Top_NegNoL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Top_NegNoL6_Cut");
    h_dX_Top_NegNoL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Top_NegNoL6_Cut->SetMarkerColor(2);
    h_dX_Top_NegNoL6_Cut->SetMarkerStyle(20);
    h_dX_Top_NegNoL6_Cut->SetMarkerSize(0.7);
    h_dX_Top_NegNoL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Top_NegNoL6_Cut.eps");
    c1->Print("Figs/dX_Top_NegNoL6_Cut.pdf");
    c1->Print("Figs/dX_Top_NegNoL6_Cut.png");

    TH2D *h_dX_Bot_NegWithL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_NegWithL6");
    h_dX_Bot_NegWithL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_NegWithL6->Draw("colz");
    TH2D *h_dX_Bot_NegWithL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_NegWithL6_Cut");
    h_dX_Bot_NegWithL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_NegWithL6_Cut->SetMarkerColor(2);
    h_dX_Bot_NegWithL6_Cut->SetMarkerStyle(20);
    h_dX_Bot_NegWithL6_Cut->SetMarkerSize(0.7);
    h_dX_Bot_NegWithL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Bot_NegWithL6_Cut.eps");
    c1->Print("Figs/dX_Bot_NegWithL6_Cut.pdf");
    c1->Print("Figs/dX_Bot_NegWithL6_Cut.png");

    TH2D *h_dX_Bot_NegNoL6 = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_NegNoL6");
    h_dX_Bot_NegNoL6->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_NegNoL6->Draw("colz");

    TH2D *h_dX_Bot_NegNoL6_Cut = (TH2D*) file_EvSelectionHists->Get("h_dX_Bot_NegNoL6_Cut");
    h_dX_Bot_NegNoL6_Cut->SetTitle("; P [GeV]; X_cl - X_{tr} [mm]");
    h_dX_Bot_NegNoL6_Cut->SetMarkerColor(2);
    h_dX_Bot_NegNoL6_Cut->SetMarkerStyle(20);
    h_dX_Bot_NegNoL6_Cut->SetMarkerSize(0.7);
    h_dX_Bot_NegNoL6_Cut->Draw("Same");
    c1->Print("Figs/dX_Bot_NegNoL6_Cut.eps");
    c1->Print("Figs/dX_Bot_NegNoL6_Cut.pdf");
    c1->Print("Figs/dX_Bot_NegNoL6_Cut.png");
    
    
    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    
    TH1D *h_Pem_TightCut1 =  (TH1D*)file_DataEvSelection->Get("h_Pem_TightCut1");
    h_Pem_TightCut1->SetTitle("; P [GeV]");
    h_Pem_TightCut1->Draw();
    c1->Print("Figs/Pem_TightCuts.eps");
    c1->Print("Figs/Pem_TightCuts.pdf");
    c1->Print("Figs/Pem_TightCuts.png");
    
    h_Pem_TightCut1->SetAxisRange(0., 0.025*h_Pem_TightCut1->GetMaximum(), "Y");
    line1->DrawLine(1.75, 0., 1.75, h_Pem_TightCut1->GetMaximum());
    c1->Print("Figs/Pem_TightCutsZoom.eps");
    c1->Print("Figs/Pem_TightCutsZoom.pdf");
    c1->Print("Figs/Pem_TightCutsZoom.png");
    
    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    
    TH1D *h_d0_em_botWithL1 = (TH1D*)file_DataEvSelection->Get("h_d0_em_botWithL1");
    h_d0_em_botWithL1->SetTitle("; Electron d_{0} [mm]");
    h_d0_em_botWithL1->Draw();

    TH1D *h_d0_em_botNoL1 = (TH1D*)file_DataEvSelection->Get("h_d0_em_botNoL1");
    h_d0_em_botNoL1->SetTitle("; Electron d_{0} [mm]");
    h_d0_em_botNoL1->SetLineColor(2);
    h_d0_em_botNoL1->Scale(h_d0_em_botWithL1->GetMaximum()/h_d0_em_botNoL1->GetMaximum());
    h_d0_em_botNoL1->Draw("hist Same");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.6, "With L1");
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.55, "No L1");
    c1->Print("Figs/d0_em_WIthAndWithL1.eps");
    c1->Print("Figs/d0_em_WIthAndWithL1.pdf");
    c1->Print("Figs/d0_em_WIthAndWithL1.png");
    
    
    TH1D *h_Minv_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_Final1");
    h_Minv_Final1->SetLineColor(2);
    h_Minv_Final1->SetTitle("; M(e^{-}e^{+}) [GeV]");
    h_Minv_Final1->Draw();
    c1->Print("Figs/Minv_Final_Data.eps");
    c1->Print("Figs/Minv_Final_Data.pdf");
    c1->Print("Figs/Minv_Final_Data.png");
    
    c1->SetLogy();
    c1->Print("Figs/Minv_FinalLog_Data.eps");
    c1->Print("Figs/Minv_FinalLog_Data.pdf");
    c1->Print("Figs/Minv_FinalLog_Data.png");
    
    c1->SetLogy(0);
    
    lat1->SetTextFont(42);
    TH1D *h_Minv_PMax_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_PMax_Final1");
    h_Minv_PMax_Final1->SetTitle("P_{sum} Max; M(e^{-}e^{+}) [GeV]");
    h_Minv_PMax_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_PMax_Final1->Integral()));
    c1->Print("Figs/Minv_PsumMax_Data.eps");
    c1->Print("Figs/Minv_PsumMax_Data.pdf");
    c1->Print("Figs/Minv_PsumMax_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_PsumMaxLog_Data.eps");
    c1->Print("Figs/Minv_PsumMaxLog_Data.pdf");
    c1->Print("Figs/Minv_PsumMaxLog_Data.png");
    c1->SetLogy(0);


    TH1D *h_Minv_PMin_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_PMin_Final1");
    h_Minv_PMin_Final1->SetTitle("P_{sum} Min; M(e^{-}e^{+}) [GeV]");
    h_Minv_PMin_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_PMin_Final1->Integral()));
    c1->Print("Figs/Minv_PsumMin_Data.eps");
    c1->Print("Figs/Minv_PsumMin_Data.pdf");
    c1->Print("Figs/Minv_PsumMin_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_PsumMinLog_Data.eps");
    c1->Print("Figs/Minv_PsumMinLog_Data.pdf");
    c1->Print("Figs/Minv_PsumMinLog_Data.png");
    c1->SetLogy(0);
    
    TH1D *h_Minv_cldT_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_cldT_Final1");
    h_Minv_cldT_Final1->SetTitle("cluster time diff; M(e^{-}e^{+}) [GeV]");
    h_Minv_cldT_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_cldT_Final1->Integral()));
    c1->Print("Figs/Minv_cldT_Data.eps");
    c1->Print("Figs/Minv_cldT_Data.pdf");
    c1->Print("Figs/Minv_cldT_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_cldTLog_Data.eps");
    c1->Print("Figs/Minv_cldTLog_Data.pdf");
    c1->Print("Figs/Minv_cldTLog_Data.png");
    c1->SetLogy(0);
    
    
    TH1D *h_Minv_epClTrkdT_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_epClTrkdT_Final1");
    h_Minv_epClTrkdT_Final1->SetTitle("e^{+} cl trk time diff; M(e^{-}e^{+}) [GeV]");
    h_Minv_epClTrkdT_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_epClTrkdT_Final1->Integral()));
    c1->Print("Figs/Minv_epClTrkdT_Data.eps");
    c1->Print("Figs/Minv_epClTrkdT_Data.pdf");
    c1->Print("Figs/Minv_epClTrkdT_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_epClTrkdTLog_Data.eps");
    c1->Print("Figs/Minv_epClTrkdTLog_Data.pdf");
    c1->Print("Figs/Minv_epClTrkdTLog_Data.png");
    c1->SetLogy(0);
    
    
    TH1D *h_Minv_emClTrkdT_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_emClTrkdT_Final1");
    h_Minv_emClTrkdT_Final1->SetTitle("e^{-} cl trk time diff; M(e^{-}e^{+}) [GeV]");
    h_Minv_emClTrkdT_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_emClTrkdT_Final1->Integral()));
    c1->Print("Figs/Minv_emClTrkdT_Data.eps");
    c1->Print("Figs/Minv_emClTrkdT_Data.pdf");
    c1->Print("Figs/Minv_emClTrkdT_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_emClTrkdTLog_Data.eps");
    c1->Print("Figs/Minv_emClTrkdTLog_Data.pdf");
    c1->Print("Figs/Minv_emClTrkdTLog_Data.png");
    c1->SetLogy(0);
    
    
    TH1D *h_Minv_epClTrkMatch_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_epClTrkMatch_Final1");
    h_Minv_epClTrkMatch_Final1->SetTitle("e^{+} cl trk Matching; M(e^{-}e^{+}) [GeV]");
    h_Minv_epClTrkMatch_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_epClTrkMatch_Final1->Integral()));
    c1->Print("Figs/Minv_epClTrkMatch_Data.eps");
    c1->Print("Figs/Minv_epClTrkMatch_Data.pdf");
    c1->Print("Figs/Minv_epClTrkMatch_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_epClTrkMatchLog_Data.eps");
    c1->Print("Figs/Minv_epClTrkMatchLog_Data.pdf");
    c1->Print("Figs/Minv_epClTrkMatchLog_Data.png");
    c1->SetLogy(0);
    
    TH1D *h_Minv_emClTrkMatch_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_emClTrkMatch_Final1");
    h_Minv_emClTrkMatch_Final1->SetTitle("e^{-} cl trk Matching; M(e^{-}e^{+}) [GeV]");
    h_Minv_emClTrkMatch_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_emClTrkMatch_Final1->Integral()));
    c1->Print("Figs/Minv_emClTrkMatch_Data.eps");
    c1->Print("Figs/Minv_emClTrkMatch_Data.pdf");
    c1->Print("Figs/Minv_emClTrkMatch_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_emClTrkMatchLog_Data.eps");
    c1->Print("Figs/Minv_emClTrkMatchLog_Data.pdf");
    c1->Print("Figs/Minv_emClTrkMatchLog_Data.png");
    c1->SetLogy(0);


    TH1D *h_Minv_Pem_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_Pem_Final1");
    h_Minv_Pem_Final1->SetTitle("e^{-} P_{Max} (anti FEE) cut; M(e^{-}e^{+}) [GeV]");
    h_Minv_Pem_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_Pem_Final1->Integral()));
    c1->Print("Figs/Minv_Pem_Data.eps");
    c1->Print("Figs/Minv_Pem_Data.pdf");
    c1->Print("Figs/Minv_Pem_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_PemLog_Data.eps");
    c1->Print("Figs/Minv_PemLog_Data.pdf");
    c1->Print("Figs/Minv_PemLog_Data.png");
    c1->SetLogy(0);

    TH1D *h_Minv_d0ep_Final1 = (TH1D*)file_DataEvSelection->Get("h_Minv_d0ep_Final1");
    h_Minv_d0ep_Final1->SetTitle("e^{+} d_{0} cut; M(e^{-}e^{+}) [GeV]");
    h_Minv_d0ep_Final1->Draw();
    h_Minv_Final1->Draw("Same");
    lat1->DrawLatex(0.55, 0.65, Form("Ratio = %1.4f", h_Minv_Final1->Integral()/h_Minv_d0ep_Final1->Integral()));
    c1->Print("Figs/Minv_d0ep_Data.eps");
    c1->Print("Figs/Minv_d0ep_Data.pdf");
    c1->Print("Figs/Minv_d0ep_Data.png");
    c1->SetLogy();
    c1->Print("Figs/Minv_d0epLog_Data.eps");
    c1->Print("Figs/Minv_d0epLog_Data.pdf");
    c1->Print("Figs/Minv_d0epLog_Data.png");
    c1->SetLogy(0);
}
