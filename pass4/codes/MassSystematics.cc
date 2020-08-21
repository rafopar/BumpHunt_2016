/* 
 * File:   MassSystematics.cc
 * Author: rafopar
 *
 * Created on April 17, 2020, 10:16 AM
 */

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

/*
 * 
 */
double SmearStatPosDiff(double *xx, double *par);
double SmearStatNegDiff(double *xx, double *par);
double SmearStatMaxDiff(double *xx, double *par);

double SmearSysPosDiff(double *xx, double *par);
double SmearSysNegDiff(double *xx, double *par);
double SmearSysMaxDiff(double *xx, double *par);

double SmearTotErr(double *xx, double *par);

TF1 *f_SmearSysErrPos;
TF1 *f_SmearSysErrNeg;
TF1 *f_SmearStatErrPos;
TF1 *f_SmearStatErrNeg;
TF1 *f_SmearCentral;



TF1 *f_SmearStatPosDiff;
TF1 *f_SmearStatNegDiff;
TF1 *f_SmearStatMaxDiff;

TF1 *f_SmearSysPosDiff;
TF1 *f_SmearSysNegDiff;
TF1 *f_SmearSysMaxDiff;


template <typename T>
void MakeStyle1(T*);

void MassSystematics() {

    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParLimits(2, 0., 9.);

    f_SmearStatErrPos = new TF1("f_SmearStatErrPos", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);
    f_SmearStatErrNeg = new TF1("f_SmearStatErrNeg", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);
    f_SmearCentral = new TF1("f_SmearCentral", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    // This code will fit masses of Ap from different target positions, and will check how
    // much the target resolution changes depending on the target position

    ofstream out_dat("MassUncertParam.dat");
    out_dat << "\\bf Function Description &\\bm{ $\\mathrm{p_{0}\\; [GeV]}$} & \\bm{ $\\mathrm{p_{1} }$} & \\bm{ $\\mathrm{p_{2}\\; [GeV^{-1}]}$} & \\bm{ $\\mathrm{p_{3}\\; [GeV^{-2}]}$ }& \\bm{ $\\mathrm{p_{4}\\; [GeV^{-3}]}$} \\\\ \\hline " << endl;

    TF1 *f_Pol4 = new TF1("f_Pol4", "[0] + x*( [1] + x*([2] + x*([3] + x*[4])))", 0., 0.3);
    const int nTargPos = 3;

    const int nMasses = 20;
    int masses[nMasses] = {50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 120, 125, 130, 135, 140, 145, 175};

    TGraphErrors * gr_sigmRecon_[nTargPos];
    TGraphErrors * gr_sigmScSmRecon_[nTargPos];
    
    TGraphErrors * gr_MassScaleScSmRecon_[nTargPos];
    
    
    TMultiGraph *mtgr_ApRecMass = new TMultiGraph();
    TMultiGraph *mtgr_ApRecMassScSm = new TMultiGraph();

    for (int i = 0; i < nTargPos; i++) {
        gr_sigmRecon_[i] = new TGraphErrors();
        gr_sigmScSmRecon_[i] = new TGraphErrors();
        gr_MassScaleScSmRecon_[i] = new TGraphErrors();
    }

    std::string targPosDirName[nTargPos] = {"ApTargNominal", "ApTargP0p5", "ApTargM0p5"};
    std::string targPosName[nTargPos] = {"t0", "tp0p5", "tm0p5"};

    int grCols[nTargPos] = {4, 2, 6};
    int grStyles[nTargPos] = {25, 24, 26};
    int grScSmCols[nTargPos] = {4, 2, 6};
    int grScSmStyles[nTargPos] = {21, 20, 22};

    for (int it = 0; it < nTargPos; it++) {

        TCanvas *c1 = new TCanvas("c1", "", 950, 950);
        TCanvas *c2 = new TCanvas("c2", "", 950, 950);

        c1->Print(Form("Figs/RecMassFits_%s.pdf[", targPosName[it].c_str()));
        c2->Print(Form("Figs/RecMassScSmFits_%s.pdf[", targPosName[it].c_str()));

        for (int im = 0; im < nMasses; im++) {

            TFile *curFile = new TFile(Form("%s/EventSelection_%s_Ap_%d_MeV.root", targPosDirName[it].c_str(), targPosName[it].c_str(), masses[im]), "Read");

            TH1D *h_ReconMass = (TH1D*) curFile->Get("h_Minv_GeneralLargeBins_Final_1");
            h_ReconMass->SetTitle("; M(e^{-}e^{+}) [GeV]");

            h_ReconMass->SetLineColor(2);
            TH1D *h_ReconMassScSm = (TH1D*) curFile->Get("h_MinvScSm_GeneralLargeBins_Final_1");
            h_ReconMassScSm->SetTitle("; M(ee) [GeV]");


            double RmsRec = h_ReconMass->GetRMS();
            double xMax = h_ReconMass->GetBinCenter(h_ReconMass->GetMaximumBin());
            f_Gaus->SetParameters(h_ReconMass->GetBinContent(h_ReconMass->GetMaximumBin()), xMax, RmsRec);

            //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
            h_ReconMass->SetAxisRange(xMax - 0.03, xMax + 0.03);
            c1->cd();
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
            c1->Print(Form("Figs/RecMassFits_%s.pdf", targPosName[it].c_str()));

            gr_sigmRecon_[it]->SetPoint(im, mean, sigm);
            gr_sigmRecon_[it]->SetPointError(im, 0., sigmErr);


            c2->cd();
            h_ReconMassScSm->Draw();

            RmsRec = h_ReconMassScSm->GetRMS();
            xMax = h_ReconMassScSm->GetBinCenter(h_ReconMassScSm->GetMaximumBin());
            f_Gaus->SetParameters(h_ReconMassScSm->GetMaximum(), xMax, RmsRec);

            //h_ReconMass->SetAxisRange(xMax - 9 * RmsRec, xMax + 9 * RmsRec);
            h_ReconMassScSm->SetAxisRange(xMax - 0.03, xMax + 0.03);

            h_ReconMassScSm->Fit(f_Gaus, "MeV", "", xMax - 2.2 * RmsRec, xMax + 2.6 * RmsRec);
            double meanScSm = f_Gaus->GetParameter(1);
            double meanErrScSm = f_Gaus->GetParError(1);
            double sigmScSm = f_Gaus->GetParameter(2);
            double sigmScSmErr = f_Gaus->GetParError(2);
            double chi2ScSm = f_Gaus->GetChisquare();
            double ndfScSm = f_Gaus->GetNDF();
            lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(masses[im])));
            lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * meanScSm));
            lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigmScSm));
            lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2ScSm / ndfScSm));

            c2->Print(Form("Figs/RecMassScSmFits_%s.pdf", targPosName[it].c_str()));

            gr_sigmScSmRecon_[it]->SetPoint(im, meanScSm, sigmScSm);
            gr_sigmScSmRecon_[it]->SetPointError(im, 0., sigmScSmErr);

            
            gr_MassScaleScSmRecon_[it]->SetPoint(im, masses[im], 100.*(1000.*meanScSm - masses[im])/masses[im]);
            gr_MassScaleScSmRecon_[it]->SetPointError(im, 0, 100.*(1000.*meanErrScSm)/masses[im]);
            
            curFile->Close();


        }

        gr_sigmRecon_[it]->SetMarkerColor(grCols[it]);
        gr_sigmRecon_[it]->SetMarkerStyle(grStyles[it]);
        gr_sigmRecon_[it]->SetMarkerSize(2.);

        gr_sigmScSmRecon_[it]->SetMarkerColor(grScSmCols[it]);
        gr_sigmScSmRecon_[it]->SetMarkerStyle(grScSmStyles[it]);
        gr_sigmScSmRecon_[it]->SetMarkerSize(2.);
        
        gr_MassScaleScSmRecon_[it]->SetMarkerColor(grScSmCols[it]);
        gr_MassScaleScSmRecon_[it]->SetMarkerStyle(grScSmStyles[it]);
        gr_MassScaleScSmRecon_[it]->SetMarkerSize(2);
        
        mtgr_ApRecMass->Add(gr_sigmRecon_[it]);
        mtgr_ApRecMassScSm->Add(gr_sigmScSmRecon_[it]);
        c1->Print(Form("Figs/RecMassFits_%s.pdf]", targPosName[it].c_str()));
        c2->Print(Form("Figs/RecMassScSmFits_%s.pdf]", targPosName[it].c_str()));

        delete c1;
        delete c2;

    }

    TLegend *leg1 = new TLegend(0.11, 0.72, 0.42, 0.98);
    leg1->SetBorderSize(0);
    leg1->SetFillColor(0);
    leg1->AddEntry(gr_sigmRecon_[0], "Targ Nominal");
    leg1->AddEntry(gr_sigmRecon_[1], "Targ +0.5 mm");
    leg1->AddEntry(gr_sigmRecon_[2], "Targ -0.5 mm");

    TCanvas *c0 = new TCanvas("c0", "", 1900, 950);
    c0->SetGridx();
    c0->SetGridy();
    c0->SetTopMargin(0.015);
    c0->SetRightMargin(0.023);
    mtgr_ApRecMass->Draw("AP");
    mtgr_ApRecMass->SetMinimum(0.);
    leg1->Draw();
    mtgr_ApRecMass->SetTitle("; m(e^{-}e^{+}) [GeV]; #sigma_{m} [GeV]");
    c0->Print("Figs/MassResolVsMass_TargDependence.eps");
    c0->Print("Figs/MassResolVsMass_TargDependence.pdf");
    c0->Print("Figs/MassResolVsMass_TargDependence.png");

    TLegend *leg2 = new TLegend(0.11, 0.72, 0.42, 0.98);
    leg2->SetBorderSize(0);
    leg2->SetFillColor(0);
    leg2->AddEntry(gr_sigmScSmRecon_[0], "Smeared Targ Nominal");
    leg2->AddEntry(gr_sigmScSmRecon_[1], "Smeared Targ +0.5 mm");
    leg2->AddEntry(gr_sigmScSmRecon_[2], "Smeared Targ -0.5 mm");
    c0->Clear();
    mtgr_ApRecMassScSm->Draw("AP");
    f_Pol4->SetLineColor(4);
    gr_sigmScSmRecon_[0]->Fit(f_Pol4, "MeV", "", 0.45, 0.18);
    f_SmearCentral = (TF1*) f_Pol4->Clone("f_SmearCentral");
    f_Pol4->DrawCopy("Same");
    f_Pol4->SetLineColor(2);
    gr_sigmScSmRecon_[1]->Fit(f_Pol4, "MeV", "", 0.45, 0.18);
    double parsTargPos[5];
    double parsTargNeg[5];

    f_Pol4->GetParameters(parsTargPos);
    out_dat << " target at 0.5 mm & " << parsTargPos[0] << " & " << parsTargPos[1] << " & " << parsTargPos[2] << " & " << parsTargPos[3] << " & " << parsTargPos[4] << "  \\\\ \\hline" << endl;
    f_SmearSysErrNeg = (TF1*) f_Pol4->Clone("f_SmearSysErrPos");
    f_Pol4->DrawCopy("Same");
    f_Pol4->SetLineColor(6);
    gr_sigmScSmRecon_[2]->Fit(f_Pol4, "MeV", "", 0.45, 0.18);
    f_Pol4->GetParameters(parsTargNeg);
    out_dat << " target at -0.5 mm & " << parsTargNeg[0] << " & " << parsTargNeg[1] << " & " << parsTargNeg[2] << " & " << parsTargNeg[3] << " & " << parsTargNeg[4] << "  \\\\ \\hline" << endl;
    f_SmearSysErrPos = (TF1*) f_Pol4->Clone("f_SmearSysErrPos");
    f_Pol4->DrawCopy("Same");
    mtgr_ApRecMassScSm->SetTitle("; m(e^{-}e^{+}) [GeV]; #sigma_{m} [GeV]");
    MakeStyle1(mtgr_ApRecMassScSm);
    //mtgr_ApRecMassScSm->SetMinimum(0.);
    leg2->Draw();
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.eps");
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.pdf");
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.png");

    c0->Clear();
    TLegend *legSmearSysErr = new TLegend(0.14, 0.75, 0.5, 0.93);
    legSmearSysErr->SetBorderSize(0);

    f_SmearSysPosDiff = new TF1("f_SmearSysPosDiff", SmearSysPosDiff, 0.037, 0.178);
    f_SmearSysNegDiff = new TF1("f_SmearSysNegDiff", SmearSysNegDiff, 0.037, 0.178);
    f_SmearSysPosDiff->SetMaximum(2.5);
    f_SmearSysPosDiff->SetMinimum(-2.5);
    f_SmearSysPosDiff->SetLineColor(2);
    f_SmearSysPosDiff->SetTitle("; m(e^{-}e^{+}) [GeV]; sys. errors on mass resolution [%]");
    MakeStyle1(f_SmearSysPosDiff);

    //    f_SmearSysPosDiff->GetYaxis()->SetLabelSize(0.051);
    //    f_SmearSysPosDiff->GetXaxis()->SetLabelSize(0.051);
    //    f_SmearSysPosDiff->GetYaxis()->SetTitleOffset(0.8);
    //    f_SmearSysPosDiff->GetXaxis()->SetTitleOffset(0.9);
    //    f_SmearSysPosDiff->GetYaxis()->SetTitleSize(0.051);
    //    f_SmearSysPosDiff->GetXaxis()->SetTitleSize(0.051);
    //    f_SmearSysPosDiff->GetXaxis()->SetNdivisions(520);
    f_SmearSysPosDiff->Draw();
    f_SmearSysNegDiff->SetLineColor(4);
    f_SmearSysNegDiff->SetLineStyle(2);
    f_SmearSysNegDiff->Draw("Same");
    legSmearSysErr->AddEntry(f_SmearSysPosDiff, "sys. error: targ at -0.5 mm");
    legSmearSysErr->AddEntry(f_SmearSysNegDiff, "sys. error: targ at +0.5 mm");
    legSmearSysErr->Draw();
    c0->Print("Figs/MassSmearSysErr.eps");
    c0->Print("Figs/MassSmearSysErr.pdf");
    c0->Print("Figs/MassSmearSysErr.png");


    f_SmearSysMaxDiff = new TF1("f_SmearSysMaxDiff", SmearSysMaxDiff, 0.037, 0.178, 0);
    f_SmearSysMaxDiff->SetTitle("; m(e^{-}e^{+}) [GeV]; sys. errors on mass resolution [%]");
    f_SmearSysMaxDiff->SetNpx(4500);
    f_SmearSysMaxDiff->Draw();
    c0->Print("Figs/MassSmearSysMaxErr.eps");
    c0->Print("Figs/MassSmearSysMaxErr.pdf");
    c0->Print("Figs/MassSmearSysMaxErr.png");

    c0->Clear();
    MakeStyle1(gr_MassScaleScSmRecon_[0]);
    MakeStyle1(gr_MassScaleScSmRecon_[1]);
    MakeStyle1(gr_MassScaleScSmRecon_[2]);
    
    TMultiGraph *mtgr_massScale_targPos = new TMultiGraph();
    mtgr_massScale_targPos->Add(gr_MassScaleScSmRecon_[0]);
    mtgr_massScale_targPos->Add(gr_MassScaleScSmRecon_[1]);
    mtgr_massScale_targPos->Add(gr_MassScaleScSmRecon_[2]);
    mtgr_massScale_targPos->Draw("AP");
    mtgr_massScale_targPos->SetTitle("; m(e^{-}e^{+}) [GeV]; Mass scale difference [%]");
    MakeStyle1(mtgr_massScale_targPos);
    c0->Print("Figs/MassScaleTargPos.eps");
    c0->Print("Figs/MassScaleTargPos.pdf");
    c0->Print("Figs/MassScaleTargPos.png");
    
    // ===================================== Mass resolution Uncertainty ===============================
    TGraphErrors *gr_sigmScSmErrPosRecon = new TGraphErrors();
    TGraphErrors *gr_sigmScSmErrNegRecon = new TGraphErrors();

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    TCanvas *c2 = new TCanvas("c2", "", 950, 950);

    c1->Print("Figs/RecMassScSmErrPosFits.pdf[");
    c1->Print("Figs/RecMassScSmErrNegFits.pdf[");
    for (int im = 0; im < nMasses; im++) {

        TFile *curFile = new TFile(Form("EventSelection_Ap_%d_MeV.root", masses[im]), "Read");


        c1->cd();
        TH1D *h_ReconMassScSmErrPos = (TH1D*) curFile->Get("h_MinvScSmErrPos_GeneralLargeBins_Final_1");
        h_ReconMassScSmErrPos->SetTitle("; M(ee) [GeV]");

        h_ReconMassScSmErrPos->Draw();

        double RmsRecScSmErrPos = h_ReconMassScSmErrPos->GetRMS();
        double xMax = h_ReconMassScSmErrPos->GetBinCenter(h_ReconMassScSmErrPos->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMassScSmErrPos->GetMaximum(), xMax, RmsRecScSmErrPos);
        h_ReconMassScSmErrPos->SetAxisRange(xMax - 0.03, xMax + 0.03);

        h_ReconMassScSmErrPos->Fit(f_Gaus, "MeV", "", xMax - 2.2 * RmsRecScSmErrPos, xMax + 2.6 * RmsRecScSmErrPos);
        double meanScSmErrPos = f_Gaus->GetParameter(1);
        double sigmScSmErrPos = f_Gaus->GetParameter(2);
        double sigmScSmErrPosErr = f_Gaus->GetParError(2);
        double chi2ScSmErrPos = f_Gaus->GetChisquare();
        double ndfScSmErrPos = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(masses[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * meanScSmErrPos));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigmScSmErrPos));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2ScSmErrPos / ndfScSmErrPos));
        c1->Print("Figs/RecMassScSmErrPosFits.pdf");
        c1->Print("Figs/RecMassScSmErrNegFits.pdf");
        gr_sigmScSmErrPosRecon->SetPoint(im, meanScSmErrPos, sigmScSmErrPos);
        gr_sigmScSmErrPosRecon->SetPointError(im, 0., sigmScSmErrPosErr);

        c2->cd();
        TH1D *h_ReconMassScSmErrNeg = (TH1D*) curFile->Get("h_MinvScSmErrNeg_GeneralLargeBins_Final_1");
        h_ReconMassScSmErrNeg->SetTitle("; M(ee) [GeV]");

        h_ReconMassScSmErrNeg->Draw();

        double RmsRecScSmErrNeg = h_ReconMassScSmErrNeg->GetRMS();
        xMax = h_ReconMassScSmErrNeg->GetBinCenter(h_ReconMassScSmErrNeg->GetMaximumBin());
        f_Gaus->SetParameters(h_ReconMassScSmErrNeg->GetMaximum(), xMax, RmsRecScSmErrNeg);
        h_ReconMassScSmErrNeg->SetAxisRange(xMax - 0.03, xMax + 0.03);

        h_ReconMassScSmErrNeg->Fit(f_Gaus, "MeV", "", xMax - 2.2 * RmsRecScSmErrNeg, xMax + 2.6 * RmsRecScSmErrNeg);
        double meanScSmErrNeg = f_Gaus->GetParameter(1);
        double sigmScSmErrNeg = f_Gaus->GetParameter(2);
        double sigmScSmErrNegErr = f_Gaus->GetParError(2);
        double chi2ScSmErrNeg = f_Gaus->GetChisquare();
        double ndfScSmErrNeg = f_Gaus->GetNDF();
        lat1->DrawLatex(0.35, 0.94, Form("Mass: %1.2f MeV", double(masses[im])));
        lat1->DrawLatex(0.64, 0.85, Form("#mu = %1.3f MeV", 1000. * meanScSmErrNeg));
        lat1->DrawLatex(0.64, 0.80, Form("#sigma = %1.3f MeV", 1000. * sigmScSmErrNeg));
        lat1->DrawLatex(0.64, 0.75, Form("#chi^{2}/NDF = %1.3f ", chi2ScSmErrNeg / ndfScSmErrNeg));
        c2->Print("Figs/RecMassScSmErrNegFits.pdf");
        c2->Print("Figs/RecMassScSmErrNegFits.pdf");
        gr_sigmScSmErrNegRecon->SetPoint(im, meanScSmErrNeg, sigmScSmErrNeg);
        gr_sigmScSmErrNegRecon->SetPointError(im, 0., sigmScSmErrNegErr);


    }
    c1->Print("Figs/RecMassScSmErrPosFits.pdf]");
    c2->Print("Figs/RecMassScSmErrNegFits.pdf]");


    // ========================================================================================
    // ======= As the central Mass parametrization, the upper and lower stat limits also will
    // ======= will be fit with 4th order polynomial function
    // ========================================================================================

    ofstream outSmearStat("SmearStat.dat");

    //f_Pol4->SetNpx(4500);

    gr_sigmScSmErrPosRecon->SetMarkerStyle(22);
    gr_sigmScSmErrPosRecon->SetMarkerColor(6);
    gr_sigmScSmErrPosRecon->SetMarkerSize(2);
    gr_sigmScSmErrNegRecon->SetMarkerStyle(20);
    gr_sigmScSmErrNegRecon->SetMarkerColor(2);
    gr_sigmScSmErrNegRecon->SetMarkerSize(2);
    gr_sigmScSmRecon_[0]->SetMarkerSize(2);

    c0->Clear();
    c0->cd();
    TMultiGraph *mtgr_smearErr = new TMultiGraph();
    mtgr_smearErr->Add(gr_sigmScSmErrPosRecon);
    mtgr_smearErr->Add(gr_sigmScSmErrNegRecon);
    mtgr_smearErr->Add(gr_sigmScSmRecon_[0]); // 0 corresponds to the target position at 0
    mtgr_smearErr->Draw("AP");
    mtgr_smearErr->SetTitle("; m [GeV]; #sigma (m) [GeV]");
    MakeStyle1(mtgr_smearErr);
    //f_Pol4->SetLineWidth(4);
    f_Pol4->SetLineColor(6);
    f_Pol4->SetLineStyle(4);
    gr_sigmScSmErrPosRecon->Fit(f_Pol4, "MeV", "", 0.045, 0.18);
    f_SmearStatErrPos = (TF1*) f_Pol4->Clone("f_SmearStatErrPos");
    double pars[5];
    double parsPos[5];
    double parsNeg[5];
    double parsCentral[5];
    f_Pol4->GetParameters(pars);
    f_Pol4->GetParameters(parsPos);

    //outSmearStat << " & p_{0} [GeV] & p_{1} & p_{2} [GeV^{-1}] & p_{3} [GeV^{-2}] & p_{4} [GeV^{-3}] \\\\ \\hline " << endl;
    out_dat << "1 $\\sigma$ upper function & " << pars[0] << " & " << pars[1] << " & " << pars[2] << " & " << pars[3] << " & " << pars[4] << " \\\\ \\hline " << endl;
    f_Pol4->SetLineColor(2);
    f_Pol4->SetLineStyle(2);
    gr_sigmScSmErrNegRecon->Fit(f_Pol4, "MeV", "", 0.045, 0.18);
    f_SmearStatErrNeg = (TF1*) f_Pol4->Clone("f_SmearStatErrNeg");
    f_Pol4->GetParameters(pars);
    f_Pol4->GetParameters(parsNeg);
    out_dat << "1 $\\sigma$ lower function & " << pars[0] << " & " << pars[1] << " & " << pars[2] << " & " << pars[3] << " & " << pars[4] << " \\\\ \\hline " << endl;

    f_Pol4->SetLineColor(4);
    f_Pol4->SetLineStyle(1);
    gr_sigmScSmRecon_[0]->Fit(f_Pol4, "MeV", "", 0.045, 0.18);
    f_SmearCentral = (TF1*) f_Pol4->Clone("f_SmearCentral");
    f_Pol4->GetParameters(parsCentral);
    TLegend *legSmearStat = new TLegend(0.12, 0.65, 0.45, 0.98);
    legSmearStat->SetBorderSize(0);
    legSmearStat->AddEntry(gr_sigmScSmErrPosRecon, "1 #sigma upper function");
    legSmearStat->AddEntry(gr_sigmScSmErrNegRecon, "1 #sigma lower function");
    legSmearStat->AddEntry(gr_sigmScSmRecon_[0], "Central function");
    legSmearStat->Draw("Same");
    c0->Print("Figs/MassResolStatParametrize.eps");
    c0->Print("Figs/MassResolStatParametrize.pdf");
    c0->Print("Figs/MassResolStatParametrize.png");

    f_SmearStatPosDiff = new TF1("f_SmearStatPosDiff", SmearStatPosDiff, 0.035, 0.18);
    f_SmearStatPosDiff->SetNpx(4500);
    f_SmearStatPosDiff->SetTitle("; m(e^{-}e^{+}) [GeV]; 1#sigma stat error on mass resolution %");
    f_SmearStatPosDiff->GetXaxis()->SetNdivisions(520);
    f_SmearStatPosDiff->Draw();
    MakeStyle1(f_SmearStatPosDiff);

    TLegend *legSmearStatErr = new TLegend(0.15, 0.75, 0.5, 0.93);
    legSmearStatErr->SetBorderSize(0);
    f_SmearStatNegDiff = new TF1("f_SmearStatPosDiff", SmearStatNegDiff, 0.035, 0.18);
    f_SmearStatNegDiff->SetNpx(4500);
    f_SmearStatNegDiff->SetTitle("; m(e^{-}e^{+}) [GeV]; 1#sigma stat errors on mass resolution %");
    f_SmearStatNegDiff->SetLineColor(4);
    f_SmearStatNegDiff->SetLineStyle(2);

    legSmearStatErr->AddEntry(f_SmearStatPosDiff, "1#sigma upper stat. error");
    legSmearStatErr->AddEntry(f_SmearStatNegDiff, "1#sigma lower stat. error");
    f_SmearStatNegDiff->Draw("Same");
    legSmearStatErr->Draw();
    c0->Print("Figs/MassSmearStatErr.eps");
    c0->Print("Figs/MassSmearStatErr.pdf");
    c0->Print("Figs/MassSmearStatErr.png");


    f_SmearStatMaxDiff = new TF1("f_SmearStatMaxDiff", SmearStatMaxDiff, 0.035, 0.18, 0);
    f_SmearStatMaxDiff->SetNpx(4500);
    f_SmearStatMaxDiff->SetTitle("; m(e^{-}e^{+}) [GeV]; 1#sigma stat error on mass resolution %");
    f_SmearStatMaxDiff->Draw();
    c0->Print("Figs/MassSmearStatMaxErr.eps");
    c0->Print("Figs/MassSmearStatMaxErr.pdf");
    c0->Print("Figs/MassSmearStatMaxErr.png");

    TLegend *legTot = new TLegend(0.18, 0.7, 0.65, 0.89);
    legTot->SetBorderSize(0);
    TF1 *f_SmearTotErr = new TF1("f_SmearTotErr", SmearTotErr, 0.035, 0.18, 0);
    f_SmearTotErr->SetNpx(4500);
    f_SmearTotErr->SetMinimum(0);
    f_SmearTotErr->SetTitle("; m(e^{-}e^{+}) [GeV]; Total uncertainty on mass resolution %");
    f_SmearTotErr->SetLineColor(4);
    legTot->AddEntry(f_SmearTotErr, "Total");
    legTot->AddEntry(f_SmearSysMaxDiff, "Target position related");
    legTot->AddEntry(f_SmearStatMaxDiff, "Smearing coefficient related");

    MakeStyle1(f_SmearTotErr);
    f_SmearTotErr->Draw();
    f_SmearSysMaxDiff->SetLineStyle(2);
    f_SmearSysMaxDiff->SetLineColor(2);
    f_SmearStatMaxDiff->SetLineColor(6);
    f_SmearStatMaxDiff->SetLineStyle(3);
    f_SmearSysMaxDiff->Draw("Same");
    f_SmearStatMaxDiff->Draw("Same");
    legTot->Draw();
    c0->Print("Figs/MassSmearTotErr.eps");
    c0->Print("Figs/MassSmearTotErr.pdf");
    c0->Print("Figs/MassSmearTotErr.png");

    TFile *file_massResolUncertainty = new TFile("massResolUncertainty.root", "Recreate");
    f_SmearSysMaxDiff->Write();
    f_SmearStatMaxDiff->Write();
    f_SmearTotErr->Write();
    file_massResolUncertainty->Close();
    delete file_massResolUncertainty;
}

double SmearStatPosDiff(double *xx, double *par) {
    return 100. * (f_SmearStatErrPos->Eval(xx[0]) - f_SmearCentral->Eval(xx[0])) / f_SmearCentral->Eval(xx[0]);
}

double SmearStatNegDiff(double *xx, double *par) {
    return 100. * (f_SmearCentral->Eval(xx[0]) - f_SmearStatErrNeg->Eval(xx[0])) / f_SmearCentral->Eval(xx[0]);
}

double SmearSysMaxDiff(double *xx, double *par) {
    return TMath::Max(TMath::Abs(f_SmearSysPosDiff->Eval(xx[0])), TMath::Abs(f_SmearSysNegDiff->Eval(xx[0])));
}

double SmearSysPosDiff(double *xx, double *par) {
    return 100. * (f_SmearSysErrPos->Eval(xx[0]) - f_SmearCentral->Eval(xx[0])) / f_SmearCentral->Eval(xx[0]);
}

double SmearSysNegDiff(double *xx, double *par) {
    return 100. * (f_SmearCentral->Eval(xx[0]) - f_SmearSysErrNeg->Eval(xx[0])) / f_SmearCentral->Eval(xx[0]);
}

double SmearStatMaxDiff(double *xx, double *par) {
    return TMath::Max(TMath::Abs(f_SmearStatPosDiff->Eval(xx[0])), TMath::Abs(f_SmearStatNegDiff->Eval(xx[0])));
}

double SmearTotErr(double *xx, double *par) {
    return sqrt(f_SmearStatMaxDiff->Eval(xx[0]) * f_SmearStatMaxDiff->Eval(xx[0]) + f_SmearSysMaxDiff->Eval(xx[0]) * f_SmearSysMaxDiff->Eval(xx[0]));
}

template <typename T>
void MakeStyle1(T* drObj) {
    drObj->GetYaxis()->SetLabelSize(0.051);
    drObj->GetXaxis()->SetLabelSize(0.051);
    drObj->GetYaxis()->SetTitleOffset(1.);
    drObj->GetXaxis()->SetTitleOffset(0.9);
    drObj->GetYaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetTitleSize(0.051);
    drObj->GetXaxis()->SetNdivisions(520);
}