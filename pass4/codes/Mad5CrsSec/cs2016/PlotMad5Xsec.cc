/* 
 * File:   PlotMad5Xsec.cc
 * Author: rafopar
 *
 * Created on July 1, 2020, 10:31 PM
 */

#include <cstdlib>

using namespace std;

void Plot1DHist(std::string fname, std::string histname, std::string title, std::string keyname);

/*
 * 
 */
void PlotMad5Xsec() {

   Plot1DHist("hist_rad.root", "Integrated cross section", " ; Cross section [pb]; ", "RadXsecMad5");
   Plot1DHist("hist_wab.root", "Integrated cross section", " ; Cross section [pb]; ", "WABXsecMad5");
   Plot1DHist("hist_tritrig.root", "Integrated cross section", " ; Cross section [pb]; ", "TriXsecMad5");
    
}

void Plot1DHist(std::string fname, std::string histname, std::string title, std::string keyname){

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);
    c1->SetTopMargin(0.01);
    c1->SetRightMargin(0.12);
    c1->SetBottomMargin(0.12);
    c1->SetLeftMargin(0.13);
    
    TFile *file_in = new TFile(fname.c_str(), "Read");
    
    TH1D *h = (TH1D*)file_in->Get(histname.c_str());
    h->SetTitleSize(0.06, "X");
    h->SetLabelSize(0.06, "X");
    h->SetTitleSize(0.06, "Y");
    h->SetLabelSize(0.06, "Y");
    h->SetTitle(title.c_str());
    h->SetStats(0);
    h->GetXaxis()->SetNdivisions(502);
    h->Draw();
    
    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextFont(42);
    lat1->DrawLatex(0.15, 0.9, "#it{HPS} Preliminary");
    lat1->SetTextSize(0.038);
    lat1->DrawLatex(0.15, 0.8, Form("RMS = %1.2e pb", h->GetRMS() ));
    
    c1->Print(Form("Figs/%s.eps", keyname.c_str()));
    c1->Print(Form("Figs/%s.pdf", keyname.c_str()));
    c1->Print(Form("Figs/%s.png", keyname.c_str()));
    
    
    
    delete c1;
}
