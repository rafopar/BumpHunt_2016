#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TMarker.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include "/Work/Soft/root_funcs/funcs1.C"

#include <iostream>

using namespace std;

TGraph* DefineGraph(double xval, double yval, int col, int style);

void Draw_chiNDF() {

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);

    TFile *file_in = new TFile("test_dst.root", "Read");

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextColor(2);

    TF1 *f_chi2_NDF1 = new TF1("f_chi2_NDF1", Chi2NDF_PDF, 0., 20, 2);

    TH1D *h_pos_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_pos_chiDNF5hits_clean1");
    h_pos_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    h_pos_chiDNF5hits_clean1->SetAxisRange(0., 10., "X");
    h_pos_chiDNF5hits_clean1->Draw();
    int cut_bin = h_pos_chiDNF5hits_clean1->FindBin(4.);
    double ratio = h_pos_chiDNF5hits_clean1->Integral(1, cut_bin) / h_pos_chiDNF5hits_clean1->Integral();
    lat1->DrawLatex(0.45, 0.5, Form("Keep %1.2f", ratio));
    f_chi2_NDF1->FixParameter(0, 5);
    h_pos_chiDNF5hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 6);
    c1->Print("Figs/chi2_NDF1_pos_5hits.eps");
    c1->Print("Figs/chi2_NDF1_pos_5hits.pdf");
    c1->Print("Figs/chi2_NDF1_pos_5hits.png");

    TH1D *h_pos_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_pos_chiDNF6hits_clean1");
    h_pos_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");
    h_pos_chiDNF6hits_clean1->SetAxisRange(0., 10., "X");
    h_pos_chiDNF6hits_clean1->Draw();
    cut_bin = h_pos_chiDNF6hits_clean1->FindBin(4.);
    ratio = h_pos_chiDNF6hits_clean1->Integral(1, cut_bin) / h_pos_chiDNF6hits_clean1->Integral();
    lat1->DrawLatex(0.45, 0.5, Form("Keep %1.2f", ratio));
    f_chi2_NDF1->FixParameter(0, 7);
    h_pos_chiDNF6hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 6);
    c1->Print("Figs/chi2_NDF1_pos_6hits.eps");
    c1->Print("Figs/chi2_NDF1_pos_6hits.pdf");
    c1->Print("Figs/chi2_NDF1_pos_6hits.png");


    TH1D *h_neg_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_neg_chiDNF5hits_clean1");
    h_neg_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    h_neg_chiDNF5hits_clean1->SetAxisRange(0., 10., "X");
    h_neg_chiDNF5hits_clean1->Draw();
    cut_bin = h_neg_chiDNF5hits_clean1->FindBin(4.);
    ratio = h_neg_chiDNF5hits_clean1->Integral(1, cut_bin) / h_neg_chiDNF5hits_clean1->Integral();
    lat1->DrawLatex(0.45, 0.5, Form("Keep %1.2f", ratio));
    f_chi2_NDF1->FixParameter(0, 5);
    h_neg_chiDNF5hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 6);
    c1->Print("Figs/chi2_NDF1_neg_5hits.eps");
    c1->Print("Figs/chi2_NDF1_neg_5hits.pdf");
    c1->Print("Figs/chi2_NDF1_neg_5hits.png");

    TH1D *h_neg_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_neg_chiDNF6hits_clean1");
    h_neg_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");
    h_neg_chiDNF6hits_clean1->SetAxisRange(0., 10., "X");
    h_neg_chiDNF6hits_clean1->Draw();
    cut_bin = h_neg_chiDNF6hits_clean1->FindBin(4.);
    ratio = h_neg_chiDNF6hits_clean1->Integral(1, cut_bin) / h_neg_chiDNF6hits_clean1->Integral();
    lat1->DrawLatex(0.45, 0.5, Form("Keep %1.2f", ratio));
    f_chi2_NDF1->FixParameter(0, 7);
    h_neg_chiDNF6hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 6);
    c1->Print("Figs/chi2_NDF1_neg_6hits.eps");
    c1->Print("Figs/chi2_NDF1_neg_6hits.pdf");
    c1->Print("Figs/chi2_NDF1_neg_6hits.png");

    TH1D *h_top_pos_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_top_pos_chiDNF5hits_clean1");
    h_top_pos_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_top_pos_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_top_pos_chiDNF6hits_clean1");
    h_top_pos_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_top_neg_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_top_neg_chiDNF5hits_clean1");
    h_top_neg_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_top_neg_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_top_neg_chiDNF6hits_clean1");
    h_top_neg_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_bot_pos_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_bot_pos_chiDNF5hits_clean1");
    h_bot_pos_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_bot_pos_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_bot_pos_chiDNF6hits_clean1");
    h_bot_pos_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_bot_neg_chiDNF5hits_clean1 = (TH1D*) file_in->Get("h_bot_neg_chiDNF5hits_clean1");
    h_bot_neg_chiDNF5hits_clean1->SetTitle("; #chi^{2}/NDF");
    TH1D *h_bot_neg_chiDNF6hits_clean1 = (TH1D*) file_in->Get("h_bot_neg_chiDNF6hits_clean1");
    h_bot_neg_chiDNF6hits_clean1->SetTitle("; #chi^{2}/NDF");

    vector<TGraph*> v_graphs;
    vector<std::string> gr_names;
    map<string, TH1D*> m_chi2_hists;

    h_top_pos_chiDNF5hits_clean1->Draw();
    h_top_pos_chiDNF5hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 6);
    m_chi2_hists["h_top_pos_chiDNF5hits_clean1"] = h_top_pos_chiDNF5hits_clean1;
    TGraph *gr = DefineGraph(h_top_pos_chiDNF5hits_clean1->GetMean(), 1, 4, 21);
    v_graphs.push_back(gr);
    gr_names.push_back("top pos 5 hits");
    c1->Print("Figs/chi2_top_pos_5hits_clean1.eps");
    c1->Print("Figs/chi2_top_pos_5hits_clean1.pdf");
    c1->Print("Figs/chi2_top_pos_5hits_clean1.png");

    h_top_pos_chiDNF6hits_clean1->Draw();
    m_chi2_hists["h_top_pos_chiDNF6hits_clean1"] = h_top_pos_chiDNF6hits_clean1;
    gr = DefineGraph(h_top_pos_chiDNF6hits_clean1->GetMean(), 2, 4, 22);
    v_graphs.push_back(gr);
    gr_names.push_back("top pos 6 hits");
    c1->Print("Figs/chi2_top_pos_6hits_clean1.eps");
    c1->Print("Figs/chi2_top_pos_6hits_clean1.pdf");
    c1->Print("Figs/chi2_top_pos_6hits_clean1.png");

    h_top_neg_chiDNF5hits_clean1->Draw();
    m_chi2_hists["h_top_neg_chiDNF5hits_clean1"] = h_top_neg_chiDNF5hits_clean1;
    gr = DefineGraph(h_top_neg_chiDNF5hits_clean1->GetMean(), 3, 2, 21);
    v_graphs.push_back(gr);
    gr_names.push_back("top neg 5 hits");
    c1->Print("Figs/chi2_top_neg_5hits_clean1.eps");
    c1->Print("Figs/chi2_top_neg_5hits_clean1.pdf");
    c1->Print("Figs/chi2_top_neg_5hits_clean1.png");

    h_top_neg_chiDNF6hits_clean1->Draw();
    m_chi2_hists["h_top_neg_chiDNF6hits_clean1"] = h_top_neg_chiDNF6hits_clean1;
    gr = DefineGraph(h_top_neg_chiDNF6hits_clean1->GetMean(), 4, 2, 22);
    v_graphs.push_back(gr);
    gr_names.push_back("top neg 6 hits");
    c1->Print("Figs/chi2_top_neg_6hits_clean1.eps");
    c1->Print("Figs/chi2_top_neg_6hits_clean1.pdf");
    c1->Print("Figs/chi2_top_neg_6hits_clean1.png");

    h_bot_pos_chiDNF5hits_clean1->Draw();
    m_chi2_hists["h_bot_pos_chiDNF5hits_clean1"] = h_bot_pos_chiDNF5hits_clean1;
    gr = DefineGraph(h_bot_pos_chiDNF5hits_clean1->GetMean(), 5, 4, 25);
    v_graphs.push_back(gr);
    gr_names.push_back("bot pos 5 hits");
    c1->Print("Figs/chi2_bot_pos_5hits_clean1.eps");
    c1->Print("Figs/chi2_bot_pos_5hits_clean1.pdf");
    c1->Print("Figs/chi2_bot_pos_5hits_clean1.png");

    h_bot_pos_chiDNF6hits_clean1->Draw();
    m_chi2_hists["h_bot_pos_chiDNF6hits_clean1"] = h_bot_pos_chiDNF6hits_clean1;
    gr = DefineGraph(h_bot_pos_chiDNF6hits_clean1->GetMean(), 6, 4, 26);
    v_graphs.push_back(gr);
    gr_names.push_back("bot pos 6 hits");
    c1->Print("Figs/chi2_bot_pos_6hits_clean1.eps");
    c1->Print("Figs/chi2_bot_pos_6hits_clean1.pdf");
    c1->Print("Figs/chi2_bot_pos_6hits_clean1.png");

    h_bot_neg_chiDNF5hits_clean1->Draw();
    m_chi2_hists["h_bot_neg_chiDNF5hits_clean1"] = h_bot_neg_chiDNF5hits_clean1;
    gr_names.push_back("bot neg 5 hits");
    gr = DefineGraph(h_bot_neg_chiDNF5hits_clean1->GetMean(), 7, 2, 25);
    v_graphs.push_back(gr);

    c1->Print("Figs/chi2_bot_neg_5hits_clean1.eps");
    c1->Print("Figs/chi2_bot_neg_5hits_clean1.pdf");
    c1->Print("Figs/chi2_bot_neg_5hits_clean1.png");

    h_bot_neg_chiDNF6hits_clean1->Draw();
    m_chi2_hists["h_bot_neg_chiDNF6hits_clean1"] = h_bot_neg_chiDNF6hits_clean1;
    gr = DefineGraph(h_bot_neg_chiDNF6hits_clean1->GetMean(), 8, 2, 26);
    v_graphs.push_back(gr);
    gr_names.push_back("bot neg 6 hits");
    c1->Print("Figs/chi2_bot_neg_6hits_clean1.eps");
    c1->Print("Figs/chi2_bot_neg_6hits_clean1.pdf");
    c1->Print("Figs/chi2_bot_neg_6hits_clean1.png");


    //    h_top_pos_chiDNF5hits_clean1->Draw();
    //    h_top_pos_chiDNF5hits_clean1->SetAxisRange(0., 10., "X");
    //    h_bot_pos_chiDNF5hits_clean1->Scale(h_top_pos_chiDNF5hits_clean1->GetMaximum() / h_bot_pos_chiDNF5hits_clean1->GetMaximum());
    //    h_bot_pos_chiDNF5hits_clean1->SetLineColor(2);
    //    h_bot_pos_chiDNF5hits_clean1->Draw("Same hist");
    //
    //
    //    h_bot_neg_chiDNF5hits_clean1->Draw();
    //    h_bot_neg_chiDNF5hits_clean1->SetAxisRange(0., 10., "X");
    //    h_bot_pos_chiDNF5hits_clean1->Scale(h_bot_neg_chiDNF5hits_clean1->GetMaximum() / h_bot_pos_chiDNF5hits_clean1->GetMaximum());
    //    h_bot_pos_chiDNF5hits_clean1->Draw("Same hist");

    TLegend *leg1 = new TLegend(0.45, 0.15, 0.75, 0.5);
    leg1->SetBorderSize(0);

    c1->Clear();
    TMultiGraph *mtgr1 = new TMultiGraph();
    for (int i = 0; i < v_graphs.size(); i++) {
        mtgr1->Add(v_graphs.at(i));
        leg1->AddEntry(v_graphs.at(i), gr_names.at(i).c_str());
    }

    mtgr1->Draw("AP");
    mtgr1->GetYaxis()->SetTickLength(0);
    mtgr1->GetXaxis()->SetTitle("mean of #chi^{2}/NDF");
    mtgr1->GetYaxis()->SetLabelOffset(9990);
    leg1->Draw();
    c1->Print("Figs/Chi2_NDF_means.eps");
    c1->Print("Figs/Chi2_NDF_means.pdf");
    c1->Print("Figs/Chi2_NDF_means.png");


    c1->Clear();
    h_bot_pos_chiDNF6hits_clean1->Draw("hist");
    h_bot_pos_chiDNF6hits_clean1->SetLineColor(2);
    h_bot_pos_chiDNF5hits_clean1->SetLineColor(3);

    double hist_max = h_bot_pos_chiDNF6hits_clean1->GetMaximum();
    for (map<string, TH1D*>::iterator it = m_chi2_hists.begin(); it != m_chi2_hists.end(); it++) {
        TH1D *h_cur = it->second;

        //h_cur->Rebin(4);
        h_cur->Scale(hist_max / h_cur->GetMaximum());
        cout << h_cur->GetMaximum() << "     " << it->first << endl;
        h_cur->Draw("Same hist");
    }
    f_chi2_NDF1->FixParameter(0, 7);
    h_bot_pos_chiDNF6hits_clean1->Fit(f_chi2_NDF1, "MeV", "", 0., 5.);

    c1->Print("Figs/All_chi2NDF_together.eps");
    c1->Print("Figs/All_chi2NDF_together.pdf");
    c1->Print("Figs/All_chi2NDF_together.png");
    
    

    hist_max = h_bot_pos_chiDNF6hits_clean1->GetMaximum();
    for (map<string, TH1D*>::iterator it = m_chi2_hists.begin(); it != m_chi2_hists.end(); it++) {
        TH1D *h_cur = it->second;

        h_cur->Rebin(4);
        h_cur->Scale(hist_max / h_cur->GetMaximum());
        cout << h_cur->GetMaximum() << "     " << it->first << endl;
        h_cur->Draw("Same hist");
        }

    h_bot_pos_chiDNF6hits_clean1->SetAxisRange(0, 0.045 * h_bot_pos_chiDNF6hits_clean1->GetMaximum(), "Y");
    c1->Print("Figs/All_chi2NDF_together_zoom.eps");
    c1->Print("Figs/All_chi2NDF_together_zoom.pdf");
    c1->Print("Figs/All_chi2NDF_together_zoom.png");


}

TGraph* DefineGraph(double xval, double yval, int col, int style) {

    TGraph *gr = new TGraph();
    gr->SetPoint(0, xval, yval);
    gr->SetMarkerSize(2);
    gr->SetMarkerColor(col);
    gr->SetMarkerStyle(style);

    return gr;
}