/* 
 * File:   DrawCutSystematics.cc
 * Author: rafopar
 *
 * Created on May 1, 2020, 10:12 PM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */

const double tritrig_SigmaGen = 1.416e-3;
const double tritrig_SigmError = 0.00431e-3;
const double NGen_tritrig = 985. * 50000.; /* 200 recon files, and each recon has 50K Gen events*/

const double Rad_SigmaGen = 81.e-6;
const double Rad_SigmError = 0.834e-6;
const double NGen_Rad = 9959 * 10000.;
//const double NGen_Rad = 4989 * 10000.;

const double Wab_SigmaGen = 0.1985;
const double Wab_SigmError = 0.01973;
const double NGen_Wab = 9965. * 100000.;

const double Lumin8099 = 237.e9; // inverse barn


void DrawClBotTimeCutSystematics();
void DrawClTrkKillingSystematics();
void DrawMlrFidSystematics();

void DrawCutSystematics() {

    //DrawClBotTimeCutSystematics();
    //DrawClTrkKillingSystematics();
    DrawMlrFidSystematics();
}

void DrawClBotTimeCutSystematics() {

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();

    TCanvas *c1 = new TCanvas("c1", "", 1700., 950);
    c1->SetRightMargin(0.05);
    c1->SetTopMargin(0.05);

    const double um = 1.e-6;

    TFile *file_Data_orig = new TFile("EventSelection_Data.root", "Read");
    TH1D *h_MinvDataOrig = (TH1D*) ((TH1D*) file_Data_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvDataOrig");
    double bw = h_MinvDataOrig->GetBinWidth(10);
    h_MinvDataOrig->SetStats(0);
    h_MinvDataOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvDataOrig->Scale(1. / (bw * Lumin8099 * um));
    h_MinvDataOrig->SetLineColor(4);

    TFile *file_Data_loose = new TFile("EventSelection_Data_LooseTbotClCut.root", "Read");
    TH1D *h_MinvDataLoose = (TH1D*) ((TH1D*) file_Data_loose->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvDataOrig");
    h_MinvDataLoose->SetStats(0);
    h_MinvDataLoose->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvDataLoose->Scale(1. / (bw * Lumin8099 * um));
    h_MinvDataLoose->SetLineColor(2);

    TRatioPlot *rpMinvData = new TRatioPlot(h_MinvDataOrig, h_MinvDataLoose);
    rpMinvData->Draw();
    rpMinvData->GetUpperPad()->SetLogy();
    rpMinvData->GetUpperPad()->SetGridy();
    rpMinvData->GetUpperPad()->SetTopMargin(0.02);
    rpMinvData->GetUpperPad()->SetBottomMargin(0.);
    rpMinvData->GetLowerPad()->cd()->SetTopMargin(0.);
    rpMinvData->GetLowerRefGraph()->SetMaximum(1.002);
    rpMinvData->GetLowerRefGraph()->SetMinimum(0.99);
    rpMinvData->GetUpperPad()->cd();
    c1->SetRightMargin(0);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "Looser time cut");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "Original time cut");
    c1->Print("Figs/Minv_Data_clBottimeSys.eps");
    c1->Print("Figs/Minv_Data_clBottimeSys.pdf");
    c1->Print("Figs/Minv_Data_clBottimeSys.png");


    c1->Clear();
    TFile *file_Tri_orig = new TFile("EventSelection_Tri.root", "Read");
    TH1D *h_MinvTriOrig = (TH1D*) ((TH1D*) file_Tri_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvTriOrig");
    h_MinvTriOrig->SetStats(0);
    h_MinvTriOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvTriOrig->Scale(tritrig_SigmaGen / (bw * NGen_tritrig * um));
    h_MinvTriOrig->SetLineColor(4);

    TFile *file_Tri_loose = new TFile("EventSelection_Tri_LooseTbotClCut.root", "Read");
    TH1D *h_MinvTriLoose = (TH1D*) ((TH1D*) file_Tri_loose->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvTriOrig");
    h_MinvTriLoose->SetStats(0);
    h_MinvTriLoose->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvTriLoose->Scale(tritrig_SigmaGen / (bw * NGen_tritrig * um));
    h_MinvTriLoose->SetLineColor(2);

    TRatioPlot *rpMinvTri = new TRatioPlot(h_MinvTriOrig, h_MinvTriLoose);
    rpMinvTri->Draw();
    rpMinvTri->GetUpperPad()->SetLogy();
    rpMinvTri->GetUpperPad()->SetGridy();
    rpMinvTri->GetUpperPad()->SetTopMargin(0.02);
    rpMinvTri->GetUpperPad()->SetBottomMargin(0.);
    rpMinvTri->GetLowerPad()->cd()->SetTopMargin(0.);
    rpMinvTri->GetLowerRefGraph()->SetMaximum(1.002);
    rpMinvTri->GetLowerRefGraph()->SetMinimum(0.97);
    rpMinvTri->GetUpperPad()->cd();
    c1->SetRightMargin(0);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "Looser time cut");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "Original time cut");
    c1->Print("Figs/Minv_Tri_clBottimeSys.eps");
    c1->Print("Figs/Minv_Tri_clBottimeSys.pdf");
    c1->Print("Figs/Minv_Tri_clBottimeSys.png");

    c1->Clear();
    TFile *file_Rad_orig = new TFile("EventSelection_Rad.root", "Read");
    TH1D *h_MinvRadOrig = (TH1D*) ((TH1D*) file_Rad_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvRadOrig");
    h_MinvRadOrig->SetStats(0);
    h_MinvRadOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvRadOrig->Scale(Rad_SigmaGen / (bw * NGen_Rad * um));
    h_MinvRadOrig->SetLineColor(4);

    TFile *file_Rad_loose = new TFile("EventSelection_Rad_LooseTbotClCut.root", "Read");
    TH1D *h_MinvRadLoose = (TH1D*) ((TH1D*) file_Rad_loose->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvRadOrig");
    h_MinvRadLoose->SetStats(0);
    h_MinvRadLoose->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvRadLoose->Scale(Rad_SigmaGen / (bw * NGen_Rad * um));
    h_MinvRadLoose->SetLineColor(2);

    TRatioPlot *rpMinvRad = new TRatioPlot(h_MinvRadOrig, h_MinvRadLoose);
    rpMinvRad->Draw();
    rpMinvRad->GetUpperPad()->SetLogy();
    rpMinvRad->GetUpperPad()->SetGridy();
    rpMinvRad->GetUpperPad()->SetTopMargin(0.02);
    rpMinvRad->GetUpperPad()->SetBottomMargin(0.);
    rpMinvRad->GetLowerPad()->cd()->SetTopMargin(0.);
    rpMinvRad->GetLowerRefGraph()->SetMaximum(1.002);
    rpMinvRad->GetLowerRefGraph()->SetMinimum(0.99);
    rpMinvRad->GetUpperPad()->cd();
    c1->SetRightMargin(0);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "Looser time cut");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "Original time cut");
    c1->Print("Figs/Minv_Rad_clBottimeSys.eps");
    c1->Print("Figs/Minv_Rad_clBottimeSys.pdf");
    c1->Print("Figs/Minv_Rad_clBottimeSys.png");

    c1->Clear();
    TFile *file_WAB_orig = new TFile("EventSelection_WAB.root", "Read");
    TH1D *h_MinvWABOrig = (TH1D*) ((TH1D*) file_WAB_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvWABOrig");
    h_MinvWABOrig->SetStats(0);
    h_MinvWABOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvWABOrig->Scale(Wab_SigmaGen / (bw * NGen_Wab * um));
    h_MinvWABOrig->SetLineColor(4);

    TFile *file_WAB_loose = new TFile("EventSelection_WAB_LooseTbotClCut.root", "Read");
    TH1D *h_MinvWABLoose = (TH1D*) ((TH1D*) file_WAB_loose->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvWABOrig");
    h_MinvWABLoose->SetStats(0);
    h_MinvWABLoose->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvWABLoose->Scale(Wab_SigmaGen / (bw * NGen_Wab * um));
    h_MinvWABLoose->SetLineColor(2);

    TRatioPlot *rpMinvWAB = new TRatioPlot(h_MinvWABOrig, h_MinvWABLoose);
    rpMinvWAB->Draw();
    rpMinvWAB->GetUpperPad()->SetLogy();
    rpMinvWAB->GetUpperPad()->SetGridy();
    rpMinvWAB->GetUpperPad()->SetTopMargin(0.02);
    rpMinvWAB->GetUpperPad()->SetBottomMargin(0.);
    rpMinvWAB->GetLowerPad()->cd()->SetTopMargin(0.);
    rpMinvWAB->GetLowerRefGraph()->SetMaximum(1.002);
    rpMinvWAB->GetLowerRefGraph()->SetMinimum(0.93);
    rpMinvWAB->GetUpperPad()->cd();
    c1->SetRightMargin(0);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "Looser time cut");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "Original time cut");
    c1->Print("Figs/Minv_WAB_clBottimeSys.eps");
    c1->Print("Figs/Minv_WAB_clBottimeSys.pdf");
    c1->Print("Figs/Minv_WAB_clBottimeSys.png");

    c1->Clear();
    TH1D *h_MinvTriPlusWabOrig = (TH1D*) h_MinvTriOrig->Clone("h_MinvTriPlusWabOrig");
    h_MinvTriPlusWabOrig->Add(h_MinvWABOrig);
    TH1D *h_fRadOrig = (TH1D*) h_MinvRadOrig->Clone("h_fRadOrig");
    h_fRadOrig->SetTitle("; m(e^{-}e^{+}) [GeV];");
    h_fRadOrig->Divide(h_MinvTriPlusWabOrig);
    h_fRadOrig->SetAxisRange(0.02, 0.1, "Y");
    h_fRadOrig->SetAxisRange(0.035, 0.18, "X");

    TH1D *h_MinvTriPlusWabLoose = (TH1D*) h_MinvTriLoose->Clone("h_MinvTriPlusWabLoose");
    h_MinvTriPlusWabLoose->Add(h_MinvWABLoose);
    TH1D *h_fRadLoose = (TH1D*) h_MinvRadLoose->Clone("h_fRadLoose");
    h_fRadLoose->SetTitle("; m(e^{-}e^{+}) [GeV];");
    h_fRadLoose->Divide(h_MinvTriPlusWabLoose);
    h_fRadLoose->SetAxisRange(0.02, 0.1, "Y");
    h_fRadLoose->SetAxisRange(0.035, 0.18, "X");


    TRatioPlot *rpfRad = new TRatioPlot(h_fRadOrig, h_fRadLoose);
    rpfRad->Draw();
    rpfRad->GetUpperPad()->SetGridy();
    rpfRad->GetUpperPad()->SetTopMargin(0.02);
    rpfRad->GetUpperPad()->SetBottomMargin(0.);
    rpfRad->GetLowerPad()->cd()->SetTopMargin(0.);
    rpfRad->GetLowerRefGraph()->SetMaximum(1.002);
    rpfRad->GetLowerRefGraph()->SetMinimum(0.998);
    rpfRad->GetLowerRefGraph()->SetMarkerStyle(20);
    rpfRad->GetUpperPad()->cd();
    c1->SetRightMargin(0);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "Looser time cut");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "Original time cut");
    c1->Print("Figs/fRad_clBottimeSys.eps");
    c1->Print("Figs/fRad_clBottimeSys.pdf");
    c1->Print("Figs/fRad_clBottimeSys.png");

}

void DrawClTrkKillingSystematics() {

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();

    TCanvas *c1 = new TCanvas("c1", "", 1700., 950);
    c1->SetRightMargin(0.05);
    c1->SetTopMargin(0.05);

    const double um = 1.e-6;

    TFile *file_Tri_orig = new TFile("EventSelection_Tri.root", "Read");
    TH1D *h_MinvTriOrig = (TH1D*) ((TH1D*) file_Tri_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvTriOrig");
    double bw = h_MinvTriOrig->GetBinWidth(10);
    h_MinvTriOrig->SetStats(0);
    h_MinvTriOrig->Sumw2();
    h_MinvTriOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvTriOrig->Scale(tritrig_SigmaGen / (bw * NGen_tritrig * um));
    h_MinvTriOrig->SetLineColor(4);

    TFile *file_TriNoTrkKill = new TFile("EventSelection_Tri_NoTrkKilling.root", "Read");
    TH1D *h_MinvTriNoTrkKill = (TH1D*) ((TH1D*) file_TriNoTrkKill->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvTriOrig");
    h_MinvTriNoTrkKill->SetStats(0);
    h_MinvTriNoTrkKill->Sumw2();
    h_MinvTriNoTrkKill->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvTriNoTrkKill->Scale(tritrig_SigmaGen / (bw * NGen_tritrig * um));
    h_MinvTriNoTrkKill->SetLineColor(2);


    TFile *file_Rad_orig = new TFile("EventSelection_Rad.root", "Read");
    TH1D *h_MinvRadOrig = (TH1D*) ((TH1D*) file_Rad_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvRadOrig");
    h_MinvRadOrig->SetStats(0);
    h_MinvRadOrig->Sumw2();
    h_MinvRadOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvRadOrig->Scale(Rad_SigmaGen / (bw * NGen_Rad * um));
    h_MinvRadOrig->SetLineColor(4);

    TFile *file_RadNoTrkKill = new TFile("EventSelection_Rad_NoTrkKilling.root", "Read");
    TH1D *h_MinvRadNoTrkKill = (TH1D*) ((TH1D*) file_RadNoTrkKill->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvRadOrig");
    h_MinvRadNoTrkKill->SetStats(0);
    h_MinvRadNoTrkKill->Sumw2();
    h_MinvRadNoTrkKill->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvRadNoTrkKill->Scale(Rad_SigmaGen / (bw * NGen_Rad * um));
    h_MinvRadNoTrkKill->SetLineColor(2);

    TFile *file_Wab_orig = new TFile("EventSelection_WAB.root", "Read");
    TH1D *h_MinvWabOrig = (TH1D*) ((TH1D*) file_Wab_orig->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvWabOrig");
    h_MinvWabOrig->SetStats(0);
    h_MinvWabOrig->Sumw2();
    h_MinvWabOrig->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvWabOrig->Scale(Wab_SigmaGen / (bw * NGen_Wab * um));
    h_MinvWabOrig->SetLineColor(4);

    TFile *file_WabNoTrkKill = new TFile("EventSelection_WAB_NoTrkKilling.root", "Read");
    TH1D *h_MinvWabNoTrkKill = (TH1D*) ((TH1D*) file_WabNoTrkKill->Get("h_Minv_GeneralLargeBins_Final_1"))->Rebin(10, "h_MinvWabOrig");
    h_MinvWabNoTrkKill->SetStats(0);
    h_MinvWabNoTrkKill->Sumw2();
    h_MinvWabNoTrkKill->SetTitle("; m(e^{-}e^{+}) [GeV]; d#sigma/dm [#mu bn GeV^{-1}]");
    h_MinvWabNoTrkKill->Scale(Wab_SigmaGen / (bw * NGen_Wab * um));
    h_MinvWabNoTrkKill->SetLineColor(2);

    TH1D *h_Tot_orig = (TH1D*) h_MinvTriOrig->Clone("h_Tot_orig");
    h_Tot_orig->Add(h_MinvWabOrig);
    TH1D *h_fRadOrig = (TH1D*) h_MinvRadOrig->Clone("h_fRadOrig");
    h_fRadOrig->Divide(h_Tot_orig);
    h_fRadOrig->SetLineColor(4);
    h_fRadOrig->SetMarkerColor(4);
    h_fRadOrig->SetMarkerStyle(20);
    h_fRadOrig->SetAxisRange(0.02, 0.1, "Y");
    h_fRadOrig->SetAxisRange(0.035, 0.18);

    TH1D *h_Tot_NoTrkKill = (TH1D*) h_MinvTriNoTrkKill->Clone("h_Tot_NoTrkKill");
    h_Tot_NoTrkKill->Add(h_MinvWabNoTrkKill);


    TH1D *h_fRadNoTrkKill = (TH1D*) h_MinvRadNoTrkKill->Clone("h_fRadNoTrkKill");
    h_fRadNoTrkKill->Divide(h_Tot_NoTrkKill);
    h_fRadNoTrkKill->SetLineColor(2);
    h_fRadNoTrkKill->SetMarkerColor(2);
    h_fRadNoTrkKill->SetMarkerStyle(20);
    h_fRadNoTrkKill->SetAxisRange(0.035, 0.18);
    h_fRadNoTrkKill->SetAxisRange(0.02, 0.1, "Y");

    TF1 *f_pol0 = new TF1("f_pol0", "[0]", 0., 0.25);

    TRatioPlot *rpfRad = new TRatioPlot(h_fRadOrig, h_fRadNoTrkKill);
    rpfRad->Draw();
    rpfRad->GetUpperPad()->SetTopMargin(0.02);
    rpfRad->GetUpperPad()->SetBottomMargin(0.);
    rpfRad->GetLowerPad()->cd()->SetTopMargin(0.);
    rpfRad->GetLowerRefGraph()->SetMaximum(1.07);
    rpfRad->GetLowerRefGraph()->SetMinimum(0.95);
    rpfRad->GetLowerRefGraph()->SetMarkerStyle(20);

    TGraph *gr = (TGraph*) rpfRad->GetLowerRefGraph();
    gr->Fit(f_pol0, "MeV", "", 0.39, 0.174);
    double fRadratio = f_pol0->GetParameter(0);
    double fRadratioErr = f_pol0->GetParError(0);
    rpfRad->GetUpperPad()->cd();
    h_fRadOrig->Draw("Same E1");
    c1->SetRightMargin(0);
    lat1->SetTextFont(42);
    lat1->SetTextColor(2);
    lat1->DrawLatex(0.65, 0.8, "No Track killing");
    lat1->SetTextColor(4);
    lat1->DrawLatex(0.65, 0.75, "With Track Killing");
    lat1->SetTextColor(1);
    lat1->DrawLatex(0.2, 0.22, Form("Ratio Fit = %1.3f #pm %1.4f", fRadratio, fRadratioErr));

}

void DrawMlrFidSystematics() {

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);
    lat1->SetTextSize(0.03);

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.02);
    c1->SetRightMargin(0.06);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0.02, 0.06);

    TFile *fileDataOrig1stHalf = new TFile("MoellerAnalyze_Data_Orig1stHalf.root", "Read");

    TH1D *h_M_DataOrig1stHalf = (TH1D*) fileDataOrig1stHalf->Get("h_TCM4");
    h_M_DataOrig1stHalf->SetTitle("; m(e^{-}e^{-}) [GeV]");
    h_M_DataOrig1stHalf->SetStats(0);
    double mean_DataOrig1stHalf = h_M_DataOrig1stHalf->GetMean();
    double rms_DataOrig1stHalf = h_M_DataOrig1stHalf->GetRMS();
    f_Gaus->SetParameters(h_M_DataOrig1stHalf->GetMaximum(), mean_DataOrig1stHalf, rms_DataOrig1stHalf);
    h_M_DataOrig1stHalf->Fit(f_Gaus, "MeV", "", mean_DataOrig1stHalf - 1.5 * rms_DataOrig1stHalf, mean_DataOrig1stHalf + 1.25 * rms_DataOrig1stHalf);
    double meanErr_DataOrig1stHalf = f_Gaus->GetParError(1);
    mean_DataOrig1stHalf = f_Gaus->GetParameter(1);
    double sigm_DataOrig1stHalf = f_Gaus->GetParameter(2);
    double sigmErr_DataOrig1stHalf = f_Gaus->GetParError(2);
    double chi2_DataOrig1stHalf = f_Gaus->GetChisquare();
    double ndf_DataOrig1stHalf = f_Gaus->GetNDF();
    lat1->DrawLatex(0.6, 0.85, Form("#mu = %1.3f #pm %1.4f MeV", 1000. * mean_DataOrig1stHalf, 1000. * meanErr_DataOrig1stHalf));
    lat1->DrawLatex(0.6, 0.8, Form("#sigma = %1.3f #pm %1.4f MeV", 1000. * sigm_DataOrig1stHalf, 1000. * sigmErr_DataOrig1stHalf));
    lat1->DrawLatex(0.6, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2_DataOrig1stHalf / ndf_DataOrig1stHalf));
    c1->Print("Figs/M_MlrFitDataOrig1stHalf.eps");
    c1->Print("Figs/M_MlrFitDataOrig1stHalf.pdf");
    c1->Print("Figs/M_MlrFitDataOrig1stHalf.png");


    TFile *fileDataMCFid2ndHalf = new TFile("MoellerAnalyze_Data_MCFid2ndHalf.root", "Read");

    TH1D *h_M_DataMCFid2ndHalf = (TH1D*) fileDataMCFid2ndHalf->Get("h_TCM4");
    h_M_DataMCFid2ndHalf->SetTitle("; m(e^{-}e^{-}) [GeV]");
    h_M_DataMCFid2ndHalf->SetStats(0);
    double mean_DataMCFid2ndHalf = h_M_DataMCFid2ndHalf->GetMean();
    double rms_DataMCFid2ndHalf = h_M_DataMCFid2ndHalf->GetRMS();
    f_Gaus->SetParameters(h_M_DataMCFid2ndHalf->GetMaximum(), mean_DataMCFid2ndHalf, rms_DataMCFid2ndHalf);
    h_M_DataMCFid2ndHalf->Fit(f_Gaus, "MeV", "", mean_DataMCFid2ndHalf - 1.5 * rms_DataMCFid2ndHalf, mean_DataMCFid2ndHalf + 1.25 * rms_DataMCFid2ndHalf);
    mean_DataMCFid2ndHalf = f_Gaus->GetParameter(1);
    double meanErr_DataMCFid2ndHalf = f_Gaus->GetParError(1);
    double sigm_DataMCFid2ndHalf = f_Gaus->GetParameter(2);
    double sigmErr_DataMCFid2ndHalf = f_Gaus->GetParError(2);
    double chi2_DataMCFid2ndHalf = f_Gaus->GetChisquare();
    double ndf_DataMCFid2ndHalf = f_Gaus->GetNDF();
    lat1->DrawLatex(0.6, 0.85, Form("#mu = %1.3f #pm %1.4f MeV", 1000. * mean_DataMCFid2ndHalf, 1000.*meanErr_DataMCFid2ndHalf));
    lat1->DrawLatex(0.6, 0.8, Form("#sigma = %1.3f #pm %1.4f MeV", 1000. * sigm_DataMCFid2ndHalf, 1000. * sigmErr_DataMCFid2ndHalf));
    lat1->DrawLatex(0.6, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2_DataMCFid2ndHalf / ndf_DataMCFid2ndHalf));
    c1->Print("Figs/M_MlrFitDataMCFid2ndHalf.eps");
    c1->Print("Figs/M_MlrFitDataMCFid2ndHalf.pdf");
    c1->Print("Figs/M_MlrFitDataMCFid2ndHalf.png");




    TFile *fileMCOrig1stHalf = new TFile("MoellerAnalyze_MC_Orig1stHalf.root", "Read");

    TH1D *h_M_MCOrig1stHalf = (TH1D*) fileMCOrig1stHalf->Get("h_TCM4");
    h_M_MCOrig1stHalf->SetTitle("; m(e^{-}e^{-}) [GeV]");
    h_M_MCOrig1stHalf->SetStats(0);
    double mean_MCOrig1stHalf = h_M_MCOrig1stHalf->GetMean();
    double rms_MCOrig1stHalf = h_M_MCOrig1stHalf->GetRMS();
    f_Gaus->SetParameters(h_M_MCOrig1stHalf->GetMaximum(), mean_MCOrig1stHalf, rms_MCOrig1stHalf);
    h_M_MCOrig1stHalf->Fit(f_Gaus, "MeV", "", mean_MCOrig1stHalf - 1.5 * rms_MCOrig1stHalf, mean_MCOrig1stHalf + 1.25 * rms_MCOrig1stHalf);
    mean_MCOrig1stHalf = f_Gaus->GetParameter(1);
    double meanErr_MCOrig1stHalf = f_Gaus->GetParError(1);
    double sigm_MCOrig1stHalf = f_Gaus->GetParameter(2);
    double sigmErr_MCOrig1stHalf = f_Gaus->GetParError(2);
    double chi2_MCOrig1stHalf = f_Gaus->GetChisquare();
    double ndf_MCOrig1stHalf = f_Gaus->GetNDF();
    lat1->DrawLatex(0.6, 0.85, Form("#mu = %1.3f MeV #pm %1.4f ", 1000. * mean_MCOrig1stHalf, 1000.*meanErr_MCOrig1stHalf));
    lat1->DrawLatex(0.6, 0.8, Form("#sigma = %1.3f #pm %1.4f MeV", 1000. * sigm_MCOrig1stHalf, 1000. * sigmErr_MCOrig1stHalf));
    lat1->DrawLatex(0.6, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2_MCOrig1stHalf / ndf_MCOrig1stHalf));
    c1->Print("Figs/M_MlrFitMCOrig1stHalf.eps");
    c1->Print("Figs/M_MlrFitMCOrig1stHalf.pdf");
    c1->Print("Figs/M_MlrFitMCOrig1stHalf.png");



    TFile *fileMCDataFid2ndHalf = new TFile("MoellerAnalyze_MC_DataFid2ndHalf.root", "Read");

    TH1D *h_M_MCDataFid2ndHalf = (TH1D*) fileMCDataFid2ndHalf->Get("h_TCM4");
    h_M_MCDataFid2ndHalf->SetTitle("; m(e^{-}e^{-}) [GeV]");
    h_M_MCDataFid2ndHalf->SetStats(0);
    double mean_MCDataFid2ndHalf = h_M_MCDataFid2ndHalf->GetMean();
    double rms_MCDataFid2ndHalf = h_M_MCDataFid2ndHalf->GetRMS();
    f_Gaus->SetParameters(h_M_MCDataFid2ndHalf->GetMaximum(), mean_MCDataFid2ndHalf, rms_MCDataFid2ndHalf);
    h_M_MCDataFid2ndHalf->Fit(f_Gaus, "MeV", "", mean_MCDataFid2ndHalf - 1.5 * rms_MCDataFid2ndHalf, mean_MCDataFid2ndHalf + 1.25 * rms_MCDataFid2ndHalf);
    mean_MCDataFid2ndHalf = f_Gaus->GetParameter(1);
    double meanErr_MCDataFid2ndHalf = f_Gaus->GetParError(1);
    double sigm_MCDataFid2ndHalf = f_Gaus->GetParameter(2);
    double sigmErr_MCDataFid2ndHalf = f_Gaus->GetParError(2);
    double chi2_MCDataFid2ndHalf = f_Gaus->GetChisquare();
    double ndf_MCDataFid2ndHalf = f_Gaus->GetNDF();
    lat1->DrawLatex(0.6, 0.85, Form("#mu = %1.3f MeV #pm %1.4f", 1000. * mean_MCDataFid2ndHalf, 1000.*meanErr_MCDataFid2ndHalf));
    lat1->DrawLatex(0.6, 0.8, Form("#sigma = %1.3f #pm %1.4f MeV", 1000. * sigm_MCDataFid2ndHalf, 1000. * sigmErr_MCDataFid2ndHalf));
    lat1->DrawLatex(0.6, 0.75, Form("#chi^{2}/NDF = %1.3f", chi2_MCDataFid2ndHalf / ndf_MCDataFid2ndHalf));
    c1->Print("Figs/M_MlrFitMCDataFid2ndHalf.eps");
    c1->Print("Figs/M_MlrFitMCDataFid2ndHalf.pdf");
    c1->Print("Figs/M_MlrFitMCDataFid2ndHalf.png");

}