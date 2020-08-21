/* 
 * File:   fRadStudy.cc
 * Author: rafopar
 *
 * Created on January 13, 2020, 5:05 PM
 */

#include <cstdlib>

using namespace std;


TH1D *getFOM(TH1D *h_Sig, TH1D *h_Tot);

/*
 * 
 */
void fRadStudy() {

    const double tritrig_SigmaGen = 1.416e-3;
    const double tritrig_SigmError = 0.00431e-3;
    const double NGen_tritrig = 985. * 50000.; /* 200 recon files, and each recon has 50K Gen events*/

//    const double Rad_SigmaGen = 81.e-6;
//    const double Rad_SigmError = 0.834e-6;
    const double Rad_SigmaGen = 66.36e-6;
    const double Rad_SigmError = 0.6678e-6;
    const double NGen_Rad = 4989 * 10000.;

    const double Wab_SigmaGen = 0.1985;
    const double Wab_SigmError = 0.01973;
    const double NGen_Wab = 9965. * 100000.;

    const double Lumin8099 = 237.e9; // inverse barn

    const int RebinY = 16;

    TLatex *lat1 = new TLatex();
    lat1->SetTextFont(42);
    lat1->SetTextSize(0.04);
    lat1->SetNDC();

    TFile *file_Data = new TFile("EventSelection_Data.root");
    TFile *file_Rad = new TFile("EventSelection_Rad.root");
    TFile *file_WAB = new TFile("EventSelection_WAB.root");
    TFile *file_Tri = new TFile("EventSelection_Tri.root");


    TH2D *h_Minv_PSumMin_AllBut_Data = (TH2D*) file_Data->Get("h_Minv_PSumMin_AllBut");
    h_Minv_PSumMin_AllBut_Data->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Minv_PSumMin_AllBut_Data->Scale(1 / Lumin8099);
    TH2D *h_Minv_PSumMin_AllBut_Data_RB = (TH2D*) h_Minv_PSumMin_AllBut_Data->RebinY(RebinY, "h_Minv_PSumMin_AllBut_Data_RB");

    TH2D *h_Minv_PSumMin_AllBut_Rad = (TH2D*) file_Rad->Get("h_Minv_PSumMin_AllBut");
    h_Minv_PSumMin_AllBut_Rad->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Minv_PSumMin_AllBut_Rad->Scale(Rad_SigmaGen / NGen_Rad);
    TH2D *h_Minv_PSumMin_AllBut_Rad_RB = (TH2D*) h_Minv_PSumMin_AllBut_Rad->RebinY(RebinY, "h_Minv_PSumMin_AllBut_Rad_RB");

    TH2D *h_Minv_PSumMin_AllBut_WAB = (TH2D*) file_WAB->Get("h_Minv_PSumMin_AllBut");
    h_Minv_PSumMin_AllBut_WAB->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Minv_PSumMin_AllBut_WAB->Scale(Wab_SigmaGen / NGen_Wab);
    TH2D *h_Minv_PSumMin_AllBut_WAB_RB = (TH2D*) h_Minv_PSumMin_AllBut_WAB->RebinY(RebinY, "h_Minv_PSumMin_AllBut_WAB_RB");

    TH2D *h_Minv_PSumMin_AllBut_Tri = (TH2D*) file_Tri->Get("h_Minv_PSumMin_AllBut");
    h_Minv_PSumMin_AllBut_Tri->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Minv_PSumMin_AllBut_Tri->Scale(tritrig_SigmaGen / NGen_tritrig);
    TH2D *h_Minv_PSumMin_AllBut_Tri_RB = (TH2D*) h_Minv_PSumMin_AllBut_Tri->RebinY(RebinY, "h_Minv_PSumMin_AllBut_Tri_RB");

    TH2D *h_Minv_PSumMin_AllBut_WABTri = (TH2D*) h_Minv_PSumMin_AllBut_WAB->Clone("h_Minv_PSumMin_AllBut_WABTri");
    h_Minv_PSumMin_AllBut_WABTri->SetTitle("; P_{Sum} [GeV]; M(ee) [GeV]");
    h_Minv_PSumMin_AllBut_WABTri->Add(h_Minv_PSumMin_AllBut_Tri);
    TH2D *h_Minv_PSumMin_AllBut_WABTri_RB = (TH2D*) h_Minv_PSumMin_AllBut_WABTri->RebinY(RebinY, "h_Minv_PSumMin_AllBut_WABTri_RB");

    int NBinsY = h_Minv_PSumMin_AllBut_WABTri_RB->GetNbinsY();
    cout << "NBinsY = " << NBinsY << endl;

    TGraph *gr_PSumMin = new TGraph();
    gr_PSumMin->SetMarkerStyle(29);
    gr_PSumMin->SetMarkerSize(2);
    gr_PSumMin->SetMarkerColor(2);

    TCanvas *c1 = new TCanvas("c1", "", 900, 900);
    TCanvas *c2 = new TCanvas("c2", "", 900, 900);

    c1->Print("Figs/PSum_FOM_Minv.pdf[");
    c2->Print("Figs/PSum_Compare_Minv.pdf[");

    for (int i = 0; i < NBinsY; i++) {

        TH1D *h_Sig_tmp = (TH1D*) h_Minv_PSumMin_AllBut_Rad_RB->ProjectionX(Form("h_Sig_%d", i), i + 1, i + 1);
        TH1D *h_Sig = (TH1D*) h_Sig_tmp->RebinX(2, "h_Sig");
        double Minv = h_Minv_PSumMin_AllBut_Rad_RB->GetYaxis()->GetBinCenter(i + 1);
        double BinWidthY = h_Minv_PSumMin_AllBut_Rad_RB->GetYaxis()->GetBinWidth(i + 1);

        TH1D *h_Bgr_tmp = (TH1D*) h_Minv_PSumMin_AllBut_WABTri_RB->ProjectionX(Form("h_Bgr_%d", i), i + 1, i + 1);
        TH1D *h_Bgr = (TH1D*) h_Bgr_tmp->RebinX(2, "h_Bgr");

        TH1D *h_FOM = getFOM(h_Sig, h_Bgr);

        c2->cd();
        h_Bgr->SetLineColor(95);
        h_Sig->SetLineColor(2);
        h_Bgr->SetAxisRange(0, 1.05 * TMath::Max(h_Bgr->GetMaximum(), h_Sig->GetMaximum()), "Y");
        h_Bgr->Draw();
        h_Sig->Draw("Same");
        lat1->DrawLatex(0.25, 0.92, Form("M(ee) #in ( %1.3f - %1.3f ) GeV", Minv - BinWidthY / 2., Minv + BinWidthY / 2.));
        c2->Print("Figs/PSum_Compare_Minv.pdf");

        c1->cd();
        h_FOM->Draw();
        lat1->DrawLatex(0.25, 0.92, Form("M(ee) #in ( %1.3f - %1.3f ) GeV", Minv - BinWidthY / 2., Minv + BinWidthY / 2.));
        c1->Print("Figs/PSum_FOM_Minv.pdf");

        double PSumMin = h_FOM->GetBinCenter(h_FOM->GetMaximumBin());

        gr_PSumMin->SetPoint(i, PSumMin, Minv);
    }
    c2->Print("Figs/PSum_Compare_Minv.pdf]");
    c1->Print("Figs/PSum_FOM_Minv.pdf]");


    c1->cd()->SetLeftMargin(0.14);
    h_Minv_PSumMin_AllBut_Data->Draw("colz");
    gr_PSumMin->Draw("Same P");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_Data.eps");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_Data.pdf");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_Data.png");


    h_Minv_PSumMin_AllBut_WABTri->Draw("colz");
    gr_PSumMin->Draw("Same P");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_WABTri.eps");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_WABTri.pdf");
    c1->Print("Figs/MinvPsum_WitmPSumMinCut_WABTri.png");


    return 0;
}

TH1D *getFOM(TH1D *h_Sig, TH1D *h_Tot) {

    TH1D *h_SqrtTotCum = (TH1D*) h_Tot->Clone("h_SqrtTotCum");

    TH1D *h_TotCum = (TH1D*) h_Tot->GetCumulative(0, "Cum");
    h_SqrtTotCum->Reset();

    for (int i = 0; i < h_Tot->GetNbinsX(); i++) {
        h_SqrtTotCum->SetBinContent(i + 1, sqrt(h_TotCum->GetBinContent(i + 1)));
    }


    TH1D *h_SigCum = (TH1D*) h_Sig->GetCumulative(0, "Cum");

    TH1D *h_FOM = (TH1D*) h_SigCum->Clone("h_FOM");

    h_FOM->Divide(h_SqrtTotCum);

    return h_FOM;
}