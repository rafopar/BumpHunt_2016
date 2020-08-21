/* 
 * File:   DrawPsumCutEffect.cc
 * Author: rafopar
 *
 * Created on August 11, 2020, 11:34 AM
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
void DrawPsumCutEffect() {

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);



    const int nSamples = 3;

    double xsec[nSamples] = {1.647e-3, 1.416e-3, 1.249e-3};

    int eltotsp[nSamples] = {900, 1000, 1100};
    int Ngen[nSamples] = {987 * 50000, 985 * 50000, 989 * 50000};

    TFile * file_in[nSamples];
    TH1D * h_Mass[nSamples];

    for (int i = 0; i < nSamples; i++) {
        file_in[i] = new TFile(Form("EventSelection_Tri_eltotsp%d.root", eltotsp[i]), "Read");
        TH1D *h_tmp = (TH1D*) file_in[i]->Get("h_MinvScSm_General_Final_1");
        h_Mass[i] = (TH1D*) h_tmp->Rebin(60, Form("h_Mass_%d", eltotsp[i]));
        h_Mass[i]->SetLineWidth(2);
        h_Mass[i]->SetTitle("; M [GeV]; d#sigma/dM [mb GeV^{-1}]");
        h_Mass[i]->Scale(xsec[i] / (Ngen[i] * h_Mass[i]->GetBinWidth(15)));
        h_Mass[i]->SetLineColor(i + 1);
    }

    h_Mass[0]->SetAxisRange(0.02, 0.18, "X");
    h_Mass[1]->SetAxisRange(0.02, 0.18, "X");
    h_Mass[2]->SetAxisRange(0.02, 0.18, "X");
    h_Mass[2]->Draw();
    h_Mass[1]->Draw("Same");
    h_Mass[0]->Draw("Same");

    TLegend *leg1 = new TLegend(0.25, 0.05, 0.7, 0.45);
    leg1->SetBorderSize(0.);
    leg1->AddEntry(h_Mass[0], Form("eltotsp = %d MeV", eltotsp[0]));
    leg1->AddEntry(h_Mass[1], Form("eltotsp = %d MeV", eltotsp[1]));
    leg1->AddEntry(h_Mass[2], Form("eltotsp = %d MeV", eltotsp[2]));

    TRatioPlot *rp1 = new TRatioPlot(h_Mass[2], h_Mass[0]);
    rp1->Draw();
    rp1->GetUpperPad()->cd()->SetLeftMargin(0.14);
    rp1->GetUpperPad()->SetBottomMargin(0.);
    rp1->GetUpperPad()->cd()->SetLogy();
    leg1->Draw();
    rp1->GetLowerPad()->SetTopMargin(0.);
    rp1->GetLowerPad()->SetGridx();
    rp1->GetLowerRefGraph()->SetMaximum(1.2);
    rp1->GetLowerRefGraph()->SetMinimum(0.8);
    h_Mass[1]->Draw("Same");
    lat1->DrawLatex(0.55, 0.75, Form("ratio = #frac{eltotsp = %d}{eltotsp = %d}", eltotsp[2], eltotsp[0]));
    c1->Print("Figs/eltotsp_Test_Mass.eps");
    c1->Print("Figs/eltotsp_Test_Mass.pdf");
    c1->Print("Figs/eltotsp_Test_Mass.png");

    /**
     * Now we will make plot of Out of time vs intime mass comparison plots
     */

    TFile *file_orig = new TFile("EventSelection_Data_Orig.root", "Read");
    TH1D *h_Mass_Orig = (TH1D*) ((TH1D*) file_orig->Get("h_Minv_General_Final_1"))->Rebin(40);
    h_Mass_Orig->SetLineWidth(2);
    h_Mass_Orig->SetTitle("; M [GeV]");

    TFile *file_outOfTime = new TFile("EventSelection_Data_OutOfTime.root", "Read");
    TH1D *h_Mass_outOfTime = (TH1D*) ((TH1D*) file_outOfTime->Get("h_Minv_General_Final_1"))->Rebin(40);
    h_Mass_outOfTime->SetLineWidth(2);
    h_Mass_outOfTime->SetMaximum(1.05 * h_Mass_Orig->GetMaximum());
    h_Mass_outOfTime->SetTitle("; M [GeV]");
    h_Mass_outOfTime->SetLineColor(2);

    c1->Clear();

    TLegend *leg2 = new TLegend(0.55, 0.6, 0.9, 0.89);
    leg2->SetBorderSize(0.);
    leg2->AddEntry(h_Mass_Orig, "Intime");
    leg2->AddEntry(h_Mass_outOfTime, "Out of time");

    TRatioPlot *rp2 = new TRatioPlot(h_Mass_outOfTime, h_Mass_Orig);
    rp2->Draw();
    rp2->GetUpperPad()->cd()->SetLogy();
    leg2->Draw();
    rp2->GetLowerRefGraph()->SetMaximum(0.06);
    rp2->GetLowerRefGraph()->SetMinimum(0.);
    rp2->GetLowerRefGraph()->GetYaxis()->SetNdivisions(502);
    c1->Print("Figs/OutOfTimeContamination.eps");
    c1->Print("Figs/OutOfTimeContamination.pdf");
    c1->Print("Figs/OutOfTimeContamination.png");
    
    
    c1->Clear();
    c1->SetLogz();
    const double cl_dTcut_Data = 1.43;
    TLine *line1 = new TLine();
    line1->SetLineColor(2);
    line1->SetLineWidth(2);
        
    TH2D *h_cl_dt_Esum_posneg1 = (TH2D*)file_orig->Get("h_cl_dt_Esum_posneg1");
    h_cl_dt_Esum_posneg1->SetTitle("; P_{e^{-}} + P_{e^{+}} [GeV]; #Delta t [ns]");
    h_cl_dt_Esum_posneg1->SetAxisRange(-5., 5., "Y");
    h_cl_dt_Esum_posneg1->Draw("colz");
    line1->DrawLine(0., +cl_dTcut_Data, 2.8, +cl_dTcut_Data);
    line1->DrawLine(0., -cl_dTcut_Data, 2.8, -cl_dTcut_Data);
    c1->Print("Figs/PosNeg_cldt_PSum.eps");
    c1->Print("Figs/PosNeg_cldt_PSum.pdf");
    c1->Print("Figs/PosNeg_cldt_PSum.png");
    
}

