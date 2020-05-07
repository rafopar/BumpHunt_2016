/* 
 * File:   FitMoellerMass.cc
 * Author: rafopar
 *
 * Created on November 13, 2019, 5:05 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>

#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>

using namespace std;

/*
 * 
 */

void DrawMoellerFiducial();
void DrawMoellerFiducial(std::string);
void DrawPSumDeltatCuts(TFile *, std::string);
void DrawdXCuts(TFile *, std::string);
void OutlineECalEdges();
//void FitMass(TFile *, std::string);

int main(int argc, char** argv) {

    gStyle->SetOptFit(1);

    std::string dataSet;

    if (argc >= 2) {

        dataSet = argv[1];

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./FitMoellerMass.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }


    std::string inpFileName;

    if (dataSet.compare("Data") == 0) {
        //inpFileName = "MoellerAnalyze_Data_All.root";
        inpFileName = "MoellerAnalyze_Data.root";
    } else if (dataSet.compare("MC") == 0) {
        inpFileName = "MoellerAnalyze_MC.root";
        //inpFileName = "MoellerAnalyze_MC_All.root";
    } else {
        cout << "Wrong Argument is provided." << endl;
        cout << "Exiting" << endl;
        exit(1);
    }


    // ==========================================================
    //   This is not a nice way to declare same variables, but I can not just 
    //   include the MoellerSetting.h. It has many dependencies.
    // ==========================================================
    const double PSumMax = 2.4;
    const double PSumMin = 2.2;

    const double PDiffHighMax = 0.35;
    const double PDiffHighMin = 0.05;
    const double PDiffLowMax = -0.15;
    const double PDiffLowMin = -0.55;


    TLatex *lat1 = new TLatex();
    lat1->SetNDC();

    TLine *line1 = new TLine();
    line1->SetLineColor(2);

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetLeftMargin(0.15);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.07);
    f_Gaus->SetNpx(4500);

    TFile *file_in = new TFile(inpFileName.c_str(), "Read");

    TH2D *h_PsumPdiff3 = (TH2D*) file_in->Get("h_PsumPdiff3");
    h_PsumPdiff3->SetTitle("; P_{Sum} [GeV]; P_{Diff} [GeV]");
    h_PsumPdiff3->Draw("colz");
    line1->DrawLine(PSumMin, PDiffLowMin, PSumMax, PDiffLowMin);
    line1->DrawLine(PSumMax, PDiffLowMin, PSumMax, PDiffLowMax);
    line1->DrawLine(PSumMin, PDiffLowMin, PSumMin, PDiffLowMax);
    line1->DrawLine(PSumMin, PDiffLowMax, PSumMax, PDiffLowMax);
    line1->DrawLine(PSumMin, PDiffHighMin, PSumMax, PDiffHighMin);
    line1->DrawLine(PSumMax, PDiffHighMin, PSumMax, PDiffHighMax);
    line1->DrawLine(PSumMin, PDiffHighMin, PSumMin, PDiffHighMax);
    line1->DrawLine(PSumMin, PDiffHighMax, PSumMax, PDiffHighMax);
    c1->Print(Form("Figs/PSumDiff3_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/PSumDiff3_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/PSumDiff3_%s.png", dataSet.c_str()));


    TH2D *h_Trk_dT_Psum5 = (TH2D*) file_in->Get("h_Trk_dT_Psum5");
    h_Trk_dT_Psum5->SetTitle("; P_{Sum} [GeV]; #Delta t_{trk} [ns]");
    h_Trk_dT_Psum5->Draw("colz");

    c1->Print(Form("Figs/Trk_dT_Psum5_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Trk_dT_Psum5_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Trk_dT_Psum5_%s.png", dataSet.c_str()));

    TH1D *h_dT_tr5 = (TH1D*) h_Trk_dT_Psum5->ProjectionY("h_dT_tr5", h_Trk_dT_Psum5->GetXaxis()->FindBin(PSumMin), h_Trk_dT_Psum5->GetXaxis()->FindBin(PSumMax));
    f_Gaus->SetParameters(h_dT_tr5->GetMaximum(), h_dT_tr5->GetMean(), h_dT_tr5->GetRMS());
    h_dT_tr5->Fit(f_Gaus, "MeV", "", -3., 1.5);
    double mean_trDt = f_Gaus->GetParameter(1);
    double sigm_trDt = f_Gaus->GetParameter(2);
    line1->DrawLine(mean_trDt - 1.5 * sigm_trDt, 0., mean_trDt - 1.5 * sigm_trDt, h_dT_tr5->GetMaximum());
    line1->DrawLine(mean_trDt + 1.5 * sigm_trDt, 0., mean_trDt + 1.5 * sigm_trDt, h_dT_tr5->GetMaximum());
    c1->Print(Form("Figs/dT_tr5_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/dT_tr5_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/dT_tr5_%s.png", dataSet.c_str()));

    TH2D *h_chi2Minv = (TH2D*) file_in->Get("h_Chi2NDF_TCM6");

    h_chi2Minv->SetTitle("; M(e^{-}e^{-}) [GeV]; #chi^{2}/MDF");
    h_chi2Minv->Draw("colz");
    c1->Print(Form("Figs/Chi2NDF_Mass_Moeller_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Chi2NDF_Mass_Moeller_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Chi2NDF_Mass_Moeller_%s.png", dataSet.c_str()));

    TH1D *h_Chi2Proj1 = (TH1D*) h_chi2Minv->ProjectionY("h_Chi2Proj1", 1, h_chi2Minv->GetXaxis()->FindBin(0.055));

    TGraphErrors *grSigma = new TGraphErrors();
    grSigma->SetTitle("; #chi^{2}/NDF cut; #sigma [GeV]");
    grSigma->SetMarkerStyle(20);
    grSigma->SetMarkerColor(2);

    TGraph *grNMoeller = new TGraph();
    grNMoeller->SetTitle("; #chi^{2}/NDF cut; #sqrt{N}");
    grNMoeller->SetMarkerStyle(20);
    grNMoeller->SetMarkerColor(2);

    TGraph *grFigOfMerit = new TGraph();
    grFigOfMerit->SetTitle("; #chi^{2}/NDF cut; #sqrt{N}/#sigma");
    grFigOfMerit->SetMarkerStyle(20);
    grFigOfMerit->SetMarkerColor(2);
    /*
        int ind_chi2 = 0;
        f_Gaus->SetParLimits(2, 0., 0.02);
        c1->Print(Form("Figs/MoellerMassFits_%s.pdf[", dataSet.c_str()));
        for (int i = 0; i < h_chi2Minv->GetNbinsY(); i++) {

            TH1D *htmp = (TH1D*) h_chi2Minv->ProjectionX("tmp", 1, i + 1);
            cout << "Kuku" << endl;

            double chi2Cut = h_chi2Minv->GetYaxis()->GetBinCenter(i + 1);
            double NMoeller = h_Chi2Proj1->Integral(1, i + 1);

            if (htmp->GetEntries() > 250) {

                if (ind_chi2 == 0) {
                    f_Gaus->SetParameters(htmp->GetMaximum(), 0.048, 0.002);
                }

                htmp->Fit(f_Gaus, "MeV", "", 0.03, 0.052);
                c1->Print(Form("Figs/MoellerMassFits_%s.pdf", dataSet.c_str()));

                double sigm = f_Gaus->GetParameter(2);
                double sigmErr = f_Gaus->GetParError(2);

                grSigma->SetPoint(ind_chi2, chi2Cut, sigm);
                grSigma->SetPointError(ind_chi2, 0, sigmErr);
                grNMoeller->SetPoint(ind_chi2, chi2Cut, sqrt(NMoeller));

                grFigOfMerit->SetPoint(ind_chi2, chi2Cut, sqrt(NMoeller) / sigm);

                ind_chi2 = ind_chi2 + 1;
            }

        }
        c1->Print(Form("Figs/MoellerMassFits_%s.pdf]", dataSet.c_str()));

        c1->Clear();
        grSigma->GetYaxis()->SetTitleOffset(2.);
        grSigma->Draw("AP");
        c1->Print(Form("Figs/MassSigmaChi2Cut_%s.eps", dataSet.c_str()));
        c1->Print(Form("Figs/MassSigmaChi2Cut_%s.pdf", dataSet.c_str()));
        c1->Print(Form("Figs/MassSigmaChi2Cut_%s.png", dataSet.c_str()));

        c1->Clear();
        grNMoeller->Draw("AP");
        c1->Print(Form("Figs/Sqrt_NMoeller_%s.eps", dataSet.c_str()));
        c1->Print(Form("Figs/Sqrt_NMoeller_%s.pdf", dataSet.c_str()));
        c1->Print(Form("Figs/Sqrt_NMoeller_%s.png", dataSet.c_str()));

        c1->Clear();
        grFigOfMerit->Draw("AP");
        c1->Print(Form("Figs/MoellerFigOfMerit_%s.eps", dataSet.c_str()));
        c1->Print(Form("Figs/MoellerFigOfMerit_%s.pdf", dataSet.c_str()));
        c1->Print(Form("Figs/MoellerFigOfMerit_%s.png", dataSet.c_str()));
     */
    //c1->SetLogz();

    
    TH2D *h_tr_yxc_1 = (TH2D*) file_in->Get("h_tr_yxc_3");
    h_tr_yxc_1->SetTitle("; X_{tr} [mm]; Y_{tr} [mm]");
    h_tr_yxc_1->SetAxisRange(-160., -30., "X");
    h_tr_yxc_1->SetAxisRange(-50., 50., "Y");
    h_tr_yxc_1->SetMarkerColor(4);
    h_tr_yxc_1->SetMarkerStyle(20);
    h_tr_yxc_1->SetMarkerSize(0.12);
    h_tr_yxc_1->Draw("colz");
    //DrawMoellerFiducial();
    DrawMoellerFiducial(dataSet.c_str());
    
    c1->Print(Form("Figs/tr_yxc_1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/tr_yxc_1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/tr_yxc_1_%s.png", dataSet.c_str()));

    TH2D *h_cl_yxc_1 = (TH2D*) file_in->Get("h_cl_yxc_3");
    h_cl_yxc_1->SetTitle("; X_{cl} [mm]; Y_{cl} [mm]");
    h_cl_yxc_1->SetAxisRange(-160., -30., "X");
    h_cl_yxc_1->SetAxisRange(-50., 50., "Y");
    h_cl_yxc_1->SetMarkerColor(2);
    h_cl_yxc_1->SetMarkerStyle(20);
    h_cl_yxc_1->SetMarkerSize(0.12);
    h_cl_yxc_1->Draw("colz");
    c1->Print(Form("Figs/cl_yxc_1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/cl_yxc_1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/cl_yxc_1_%s.png", dataSet.c_str()));

    c1->SetLogz(0);
    h_cl_yxc_1->SetStats(0);
    h_tr_yxc_1->SetStats(0);
    h_cl_yxc_1->Draw("");
    h_tr_yxc_1->Draw("Same");
    //DrawMoellerFiducial();
    DrawMoellerFiducial(dataSet.c_str());
    OutlineECalEdges();
    c1->Print(Form("Figs/ClTrk_yxc1_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/ClTrk_yxc1_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/ClTrk_yxc1_%s.png", dataSet.c_str()));
    

    DrawPSumDeltatCuts(file_in, dataSet.c_str());
    DrawdXCuts(file_in, dataSet.c_str());

    return 0;
}

void DrawMoellerFiducial() {

    TLine *line1 = new TLine();
    line1->SetLineColor(1);
    line1->SetLineWidth(2);
    line1->DrawLine(-125, 26., -125, 40.);
    line1->DrawLine(-125, 26., -97, 26.);
    line1->DrawLine(-97, 26., -97, 40.);
    line1->DrawLine(-97, 40., -125, 40.);

    line1->DrawLine(-85, 23., -85, 31.);
    line1->DrawLine(-85, 23., -60, 23.);
    line1->DrawLine(-60, 23., -60, 31.);
    line1->DrawLine(-60, 31., -85, 31.);

    line1->DrawLine(-112, -27., -112, -40.);
    line1->DrawLine(-112, -27., -95, -27.);
    line1->DrawLine(-95, -27., -95, -40.);
    line1->DrawLine(-95, -40., -112, -40.);

    line1->DrawLine(-95, -33., -95, -39.);
    line1->DrawLine(-95, -33., -85, -33.);
    line1->DrawLine(-85, -33., -85, -39.);
    line1->DrawLine(-85, -39., -95, -39.);

    line1->DrawLine(-70, -23., -70, -30.);
    line1->DrawLine(-70, -23., -48, -23.);
    line1->DrawLine(-48, -23., -48, -30.);
    line1->DrawLine(-48, -30., -70, -30.);

    delete line1;
}

void DrawMoellerFiducial(std::string dataSet) {

    TLine *line1 = new TLine();
    line1->SetLineColor(1);
    line1->SetLineWidth(2);

    if (dataSet.compare("Data") == 0) {

        double x1t = -55;
        double x2t = -85;
        double x3t = -95;
        double x4t = -125;
        double yHigh = 42.;
        double y12t = 13 - 0.26 * x1t;
        double y22t = 13 - 0.26 * x2t;
        double y32t = 13 - 0.26 * x3t;
        double y42t = 13 - 0.26 * x4t;
        double y11t = 18 - 0.08 * x1t;
        double y21t = 18 - 0.08 * x2t;
        double y31t = 18 - 0.08 * x3t;
        double y41t = 18 - 0.08 * x4t;

        line1->DrawLine(x4t, y42t, -110., yHigh);
        line1->DrawLine(x1t, y12t, x2t, y22t);
        line1->DrawLine(x3t, y32t, -110, yHigh);
        line1->DrawLine(x1t, y11t, x2t, y21t);
        line1->DrawLine(x3t, y31t, x4t, y41t);
        line1->DrawLine(x1t, y11t, x1t, y12t);
        line1->DrawLine(x2t, y21t, x2t, y22t);
        line1->DrawLine(x3t, y31t, x3t, y32t);
        line1->DrawLine(x4t, y41t, x4t, y42t);


        double x1b = -45;
        double x2b = -75;
        double x3b = -95;
        double x4b = -110;
        double yLowb = -23.;

        double y11b = -15. + 0.08 * x1b;
        double y21b = -15. + 0.08 * x2b;
        double y31b = -15. + 0.08 * x3b;
        double y41b = -15. + 0.08 * x4b;
        double y12b = -18. + 0.22 * x1b;
        double y22b = -18. + 0.22 * x2b;
        double y32b = -18. + 0.22 * x3b;
        double y42b = -18. + 0.22 * x4b;

        line1->DrawLine(x1b, yLowb, x2b, yLowb);
        line1->DrawLine(x3b, y31b, x4b, y41b);
        line1->DrawLine(x1b, y12b, x2b, y22b);
        line1->DrawLine(x3b, y32b, x4b, y42b);
        line1->DrawLine(x1b, yLowb, x1b, y12b);
        line1->DrawLine(x2b, yLowb, x2b, y22b);
        line1->DrawLine(x3b, y31b, x3b, y32b);
        line1->DrawLine(x4b, y41b, x4b, y42b);

    } else if (dataSet.compare("MC") == 0) {

        double x1t = -50;
        double x2t = -75;
        double x3t = -95;
        double x4t = -130;
        double yLowt = 23.;


        double y11t = 15. - 0.1 * x1t;
        double y21t = 15. - 0.1 * x2t;
        double y31t = 15. - 0.1 * x3t;
        double y41t = 15. - 0.1 * x4t;
        double y12t = 12. - 0.3 * x1t;
        double y22t = 12. - 0.3 * x2t;
        double y32t = 12. - 0.3 * x3t;
        double y42t = 12. - 0.3 * x4t;

        line1->DrawLine(x1t, yLowt, x2t, yLowt);
        line1->DrawLine(x3t, y31t, x4t, y41t);
        line1->DrawLine(x1t, y12t, x2t, y22t);
        line1->DrawLine(x3t, y32t, x4t, y42t);
        line1->DrawLine(x1t, yLowt, x1t, y12t);
        line1->DrawLine(x2t, yLowt, x2t, y22t);
        line1->DrawLine(x3t, y31t, x3t, y32t);
        line1->DrawLine(x4t, y41t, x4t, y42t);


        double x1b = -50;
        double x2b = -75;
        double x3b = -94;
        double x4b = -120;
        double yLowb = -22.;

        double y11b = -15. + 0.1 * x1b;
        double y21b = -15. + 0.1 * x2b;
        double y31b = -15. + 0.1 * x3b;
        double y41b = -15. + 0.1 * x4b;
        double y12b = -15. + 0.25 * x1b;
        double y22b = -15. + 0.25 * x2b;
        double y32b = -15. + 0.25 * x3b;
        double y42b = -15. + 0.25 * x4b;

        line1->DrawLine(x1b, yLowb, x2b, yLowb);
        line1->DrawLine(x3b, y31b, x4b, y41b);
        line1->DrawLine(x1b, y12b, x2b, y22b);
        line1->DrawLine(x3b, y32b, x4b, y42b);
        line1->DrawLine(x1b, yLowb, x1b, y12b);
        line1->DrawLine(x2b, yLowb, x2b, y22b);
        line1->DrawLine(x3b, y31b, x3b, y32b);
        line1->DrawLine(x4b, y41b, x4b, y42b);

    }
}

void DrawPSumDeltatCuts(TFile *file_in, std::string dataSet) {

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", -3., 5.);
    f_Gaus->SetNpx(4500);

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    TH2D *h_Trk_dT_Psum5 = (TH2D*) file_in->Get("h_Trk_dT_Psum5");

    h_Trk_dT_Psum5->SetTitle("; P_{Sum} [GeV]; Track #Delta t [ns]");
    h_Trk_dT_Psum5->Draw("colz");
    h_Trk_dT_Psum5->SetAxisRange(1.8, 2.8, "X");

    h_Trk_dT_Psum5->Draw("colz");

    int binX1 = h_Trk_dT_Psum5->GetXaxis()->FindBin(2.18);
    int binX2 = h_Trk_dT_Psum5->GetXaxis()->FindBin(2.4);

    TH1D *h_dT = (TH1D*) h_Trk_dT_Psum5->ProjectionY("h_dT", binX1, binX2);

    f_Gaus->SetParameters(h_dT->GetMaximum(), 0., 1.);

    h_dT->Draw();
    double maxBinCenter = h_dT->GetBinCenter(h_dT->GetMaximumBin());
    double rms = h_dT->GetRMS();
    h_dT->Fit(f_Gaus, "MeV", "", maxBinCenter - 1.5 * rms, maxBinCenter + 1.5 * rms);

    double mean_dT = f_Gaus->GetParameter(1);
    double sigm_dT = f_Gaus->GetParameter(2);

    double dT1 = mean_dT - 2 * sigm_dT;
    double dT2 = mean_dT + 2 * sigm_dT;
    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(2);
    line1->DrawLine(dT1, 0., dT1, f_Gaus->GetMaximum());
    line1->DrawLine(dT2, 0., dT2, f_Gaus->GetMaximum());
    c1->Print(Form("Figs/Mlr_Trk_dT5_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_Trk_dT5_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_Trk_dT5_%s.png", dataSet.c_str()));

    double binY1 = h_Trk_dT_Psum5->GetYaxis()->FindBin(dT1);
    double binY2 = h_Trk_dT_Psum5->GetYaxis()->FindBin(dT2);

    TH1D *h_PSum = (TH1D*) h_Trk_dT_Psum5->ProjectionX("h_PSum", binY1, binY2);

    maxBinCenter = h_PSum->GetBinCenter(h_PSum->GetMaximumBin());
    rms = h_PSum->GetRMS();

    f_Gaus->SetParameters(h_PSum->GetMaximum(), maxBinCenter, rms);
    h_PSum->Draw();
    h_PSum->Fit(f_Gaus, "MeV", "", maxBinCenter - 0.5 * rms, maxBinCenter + rms);
    cout << "asdasd " << maxBinCenter << "    " << rms << endl;

    double meanPSum = f_Gaus->GetParameter(1);
    double sigmPSum = f_Gaus->GetParameter(2);

    double PSumMax = meanPSum + 3 * sigmPSum;
    double PSumMin = meanPSum - 3.5 * sigmPSum;


    line1->DrawLine(PSumMax, 0., PSumMax, f_Gaus->GetMaximum());
    line1->DrawLine(PSumMin, 0., PSumMin, f_Gaus->GetMaximum());

    c1->Print(Form("Figs/Mlr_Psum5_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_Psum5_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_Psum5_%s.png", dataSet.c_str()));

    ofstream outDat(Form("Mlr_DtPsuCuts_%s.dat", dataSet.c_str()));
    //ofstream outDat("test.dat");

    outDat << " & $\\mathrm{\\Delta t min}$ & $\\mathrm{\\Delta t max}$ & $\\mathrm{\\P_{Sum} min}$ &  $\\mathrm{\\P_{Sum} max}$ \\\\ \\hline  " << endl;
    outDat << dataSet.c_str() << " & " << dT1 << " & " << dT2 << " & " << PSumMin << " & " << PSumMax << "\\\\ \\hline" << endl;


    h_Trk_dT_Psum5->Draw("colz");
    line1->DrawLine(PSumMin, dT1, PSumMax, dT1);
    line1->DrawLine(PSumMax, dT1, PSumMax, dT2);
    line1->DrawLine(PSumMax, dT2, PSumMin, dT2);
    line1->DrawLine(PSumMin, dT2, PSumMin, dT1);

    c1->Print(Form("Figs/Trk_dT_Psum5_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Trk_dT_Psum5_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Trk_dT_Psum5_%s.png", dataSet.c_str()));



    delete c1;
}

void DrawdXCuts(TFile *file_in, std::string dataSet) {


    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", -3., 5.);
    f_Gaus->SetNpx(4500);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(2);

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TH2D *h_dX_P_InECal_Top4 = (TH2D*) file_in->Get("h_dX_P_InECal_Top4");
    TH1D *h_dX_Top = (TH1D*) h_dX_P_InECal_Top4->ProjectionY("h_dX_Top", 1, h_dX_P_InECal_Top4->GetNbinsX());
    h_dX_Top->SetAxisRange(-30., 30.);
    h_dX_Top->SetTitle("; #Delta x [mm]");

    h_dX_Top->Draw();
    double rms = h_dX_Top->GetRMS();
    double maxBinX = h_dX_Top->GetBinCenter(h_dX_Top->GetMaximumBin());
    f_Gaus->SetParameters(h_dX_Top->GetMaximum(), maxBinX, rms);
    h_dX_Top->Fit(f_Gaus, "MeV", "", maxBinX - 1.5 * rms, maxBinX + 1.5 * rms);
    double mean = f_Gaus->GetParameter(1);
    double sigm = f_Gaus->GetParameter(2);
    double dx_maxTop = mean + 2 * sigm;
    double dx_minTop = mean - 2 * sigm;
    line1->DrawLine(dx_maxTop, 0, dx_maxTop, f_Gaus->GetMaximum());
    line1->DrawLine(dx_minTop, 0, dx_minTop, f_Gaus->GetMaximum());
    c1->Print(Form("Figs/Mlr_ClTr_dX_Top_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_ClTr_dX_Top_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_ClTr_dX_Top_%s.png", dataSet.c_str()));


    TH2D *h_dX_P_InECal_Bot4 = (TH2D*) file_in->Get("h_dX_P_InECal_Bot4");
    TH1D *h_dX_Bot = (TH1D*) h_dX_P_InECal_Bot4->ProjectionY("h_dX_Bot", 1, h_dX_P_InECal_Bot4->GetNbinsX());
    h_dX_Bot->SetAxisRange(-30., 30.);
    h_dX_Bot->SetTitle("; #Delta x [mm]");

    h_dX_Bot->Draw();
    rms = h_dX_Bot->GetRMS();
    maxBinX = h_dX_Bot->GetBinCenter(h_dX_Bot->GetMaximumBin());
    f_Gaus->SetParameters(h_dX_Bot->GetMaximum(), maxBinX, rms);
    h_dX_Bot->Fit(f_Gaus, "MeV", "", maxBinX - 1.5 * rms, maxBinX + 1.5 * rms);
    mean = f_Gaus->GetParameter(1);
    sigm = f_Gaus->GetParameter(2);
    double dx_maxBot = mean + 2 * sigm;
    double dx_minBot = mean - 2 * sigm;
    line1->DrawLine(dx_maxBot, 0, dx_maxBot, f_Gaus->GetMaximum());
    line1->DrawLine(dx_minBot, 0, dx_minBot, f_Gaus->GetMaximum());

    c1->Print(Form("Figs/Mlr_ClTr_dX_Bot_%s.eps", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_ClTr_dX_Bot_%s.pdf", dataSet.c_str()));
    c1->Print(Form("Figs/Mlr_ClTr_dX_Bot_%s.png", dataSet.c_str()));


    ofstream outdat(Form("Mlr_dXCuts_%s.dat", dataSet.c_str()));
    outdat << "  & $\\mathrm{\\Delta X_{min}^{Top}}$ & $\\mathrm{\\Delta X_{max}^{Top}}$ & $\\mathrm{\\Delta X_{min}^{Bot}}$ & $\\mathrm{\\Delta X_{max}^{Bot}}$ \\\\ \\hline" << endl;
    outdat << dataSet.c_str() << " & " << dx_minTop << " & " << dx_maxTop << " & " << dx_minBot << " & " << dx_maxBot << "  \\\\ \\hline " << endl;

    delete c1;
    delete f_Gaus;
    delete line1;
}


void OutlineECalEdges(){
    const double y1stRow = 21.5;
    const double y2ndRow = 34.5;
    const double xHoleNeg = -93.5;
    const double histNegLim = -160.;
    const double histPosLim = -30.;
    
    TLine *line1 = new TLine();
    line1->SetLineColor(6);
    line1->SetLineStyle(9);
    line1->SetLineWidth(3);
    // ============ Top Haf ===================
    line1->DrawLine(histNegLim, y1stRow, xHoleNeg, y1stRow);
    line1->DrawLine(xHoleNeg, y1stRow, xHoleNeg, y2ndRow);
    line1->DrawLine(xHoleNeg, y2ndRow, histPosLim, y2ndRow);

    // ============ Bottom Haf ===================
    line1->DrawLine(histNegLim, -y1stRow, xHoleNeg, -y1stRow);
    line1->DrawLine(xHoleNeg, -y1stRow, xHoleNeg, -y2ndRow);
    line1->DrawLine(xHoleNeg, -y2ndRow, histPosLim, -y2ndRow);
}