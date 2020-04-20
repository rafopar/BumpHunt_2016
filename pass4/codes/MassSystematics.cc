/* 
 * File:   MassSystematics.cc
 * Author: rafopar
 *
 * Created on April 17, 2020, 10:16 AM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
void MassSystematics() {

    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 0., 0.2);
    f_Gaus->SetNpx(4500);
    f_Gaus->SetParLimits(2, 0., 9.);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);

    // This code will fit masses of Ap from different target positions, and will check how
    // much the target resolution changes depending on the target position

    const int nTargPos = 3;

    const int nMasses = 20;
    int masses[nMasses] = {50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 120, 125, 130, 135, 140, 145, 175};

    TGraphErrors * gr_sigmRecon_[nTargPos];
    TGraphErrors * gr_sigmScSmRecon_[nTargPos];
    TMultiGraph *mtgr_ApRecMass = new TMultiGraph();
    TMultiGraph *mtgr_ApRecMassScSm = new TMultiGraph();

    for (int i = 0; i < nTargPos; i++) {
        gr_sigmRecon_[i] = new TGraphErrors();
        gr_sigmScSmRecon_[i] = new TGraphErrors();
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
            h_ReconMass->SetTitle("; M(ee) [GeV]");

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

            curFile->Close();


        }

        gr_sigmRecon_[it]->SetMarkerColor(grCols[it]);
        gr_sigmRecon_[it]->SetMarkerStyle(grStyles[it]);
        gr_sigmRecon_[it]->SetMarkerSize(3.1);

        gr_sigmScSmRecon_[it]->SetMarkerColor(grScSmCols[it]);
        gr_sigmScSmRecon_[it]->SetMarkerStyle(grScSmStyles[it]);
        gr_sigmScSmRecon_[it]->SetMarkerSize(3.1);

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
    c0->SetTopMargin(0.01);
    c0->SetRightMargin(0.02);
    mtgr_ApRecMass->Draw("AP");
    mtgr_ApRecMass->SetMinimum(0.);
    leg1->Draw();
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
    mtgr_ApRecMassScSm->SetMinimum(0.);
    leg2->Draw();
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.eps");
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.pdf");
    c0->Print("Figs/MassResolScSmVsMass_TargDependence.png");



    return 0;
}

