#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TCanvas.h>

#include "setting_2016_pass1.h"

void Compare_Data_MC(){

  TCanvas *c1 = new TCanvas("c1", "", 750, 750);

  TLatex *lat1 = new TLatex();
  lat1->SetNDC();

  TLine *line1 = new TLine();
  line1->SetLineColor(2);
  line1->SetLineWidth(2);

  map<std::string, int> cols;
  cols["Data"] = 1;
  cols["Trid"] = 2;
  cols["WAB"] = 3;
  cols["MCTot"] = 4;
  
  TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", -5., 5.);
  
  TFile *file_Data = new TFile("Event_Selection_Data.root");
  TFile *file_Trid = new TFile("Event_Selection_Tritrig.root");
  TFile *file_WAB = new TFile("Event_Selection_WAB.root");
  TFile *file_RAD = new TFile("Event_Selection_RAD.root");


  TH1D *h_tarP_Data = (TH1D*)file_Data->Get("h_tarP1");
  h_tarP_Data->SetName("h_tarP_Data");
  h_tarP_Data->SetLineColor(1);
  h_tarP_Data->Scale(1./tri_data_lumi);

  cout<<"tri_data_lumi = "<<tri_data_lumi<<endl;
  
  TH1D *h_tarP_Trid = (TH1D*)file_Trid->Get("h_tarP1");
  h_tarP_Trid->SetName("h_tarP_Data");
  h_tarP_Trid->SetLineColor(2);
  h_tarP_Trid->Scale(1./tritrig_mc_lumi);

  TH1D *h_tarP_WAB = (TH1D*)file_WAB->Get("h_tarP1");
  h_tarP_WAB->SetName("h_tarP_Data");
  h_tarP_WAB->SetLineColor(3);
  h_tarP_WAB->Scale(1./wab_mc_lumi);

  TH1D *h_tarP_trid_plus_WAB = (TH1D*)h_tarP_Trid->Clone("h_tarP_trid_plus_WAB");
  h_tarP_trid_plus_WAB->Add(h_tarP_WAB);
  h_tarP_trid_plus_WAB->SetLineColor(4);

  int cut_bin1 = h_tarP_Trid->FindBin(Psum_min);
  int cut_bin2 = h_tarP_Trid->FindBin(1.2*Eb);

  double scale = h_tarP_Data->Integral(cut_bin1, cut_bin2)/h_tarP_trid_plus_WAB->Integral(cut_bin1, cut_bin2);
  h_tarP_trid_plus_WAB->Scale(scale);
  cout<<"Scale = "<<scale<<endl;
  
  h_tarP_Data->Draw("hist");
  h_tarP_trid_plus_WAB->Draw("Same hist");
  h_tarP_Trid->Draw("Same hist");
  lat1->DrawLatex(0.7, 0.5, Form("Scale = %1.2f", scale));
  c1->Print("Figs/tarP_compare.eps");
  c1->Print("Figs/tarP_compare.pdf");
  c1->Print("Figs/tarP_compare.png");

  
  TH1D *h_d0_pos_Data3 = (TH1D*)file_Data->Get("h_d0_pos3");
  h_d0_pos_Data3->SetTitle("; d_{0} [mm]");
  h_d0_pos_Data3->SetName("h_d0_pos_Data3");
  h_d0_pos_Data3->SetLineColor(1);
  h_d0_pos_Data3->SetFillColor(1);
  h_d0_pos_Data3->Scale(1./tri_data_lumi);

  
  TH1D *h_d0_pos_Trid3 = (TH1D*)file_Trid->Get("h_d0_pos3");
  h_d0_pos_Trid3->SetName("h_d0_pos_Trid3");
  h_d0_pos_Trid3->SetTitle("; d_{0} [mm]");
  h_d0_pos_Trid3->SetLineColor(2);
  h_d0_pos_Trid3->SetFillColor(2);
  h_d0_pos_Trid3->SetFillStyle(3001);
  h_d0_pos_Trid3->Scale(1./tritrig_mc_lumi);

  TH1D *h_d0_pos_WAB3 = (TH1D*)file_WAB->Get("h_d0_pos3");
  h_d0_pos_WAB3->SetName("h_d0_pos_WAB3");
  h_d0_pos_WAB3->SetLineColor(3);
  h_d0_pos_WAB3->SetFillColor(3);
  h_d0_pos_WAB3->SetFillStyle(3001);
  h_d0_pos_WAB3->Scale(1./wab_mc_lumi);
  

  TH1D *h_d0_pos_RAD3 = (TH1D*)file_RAD->Get("h_d0_pos3");
  h_d0_pos_RAD3->SetName("h_d0_pos_WAB3");
  h_d0_pos_RAD3->SetLineColor(25);
  h_d0_pos_RAD3->SetFillColor(25);
  h_d0_pos_RAD3->SetFillStyle(3001);
  h_d0_pos_RAD3->Scale(1./rad_mc_lumi);


  
  TH1D *h_d0_trid_plus_WAB3 = (TH1D*)h_d0_pos_Trid3->Clone("h_d0_trid_plus_WAB3");
  h_d0_trid_plus_WAB3->Add(h_d0_pos_WAB3);
  TH1D *h_cum_d0_trid_plus_WAB3 = (TH1D*)h_d0_trid_plus_WAB3->GetCumulative();

  for( int i = 0; i < h_cum_d0_trid_plus_WAB3->GetNbinsX(); i++ ){
    h_cum_d0_trid_plus_WAB3->SetBinContent(i + 1, sqrt(h_cum_d0_trid_plus_WAB3->GetBinContent(i+1)));
  }
  
  TH1D *h_cum_d0_rad3 = (TH1D*)h_d0_pos_RAD3->GetCumulative();

  TH1D *h_ratio_rad3_cum_tot3 = (TH1D*)h_cum_d0_rad3->Clone("h_ratio_rad3_cum_tot3");
  h_ratio_rad3_cum_tot3->Divide(h_cum_d0_trid_plus_WAB3);
  

  h_cum_d0_trid_plus_WAB3->Draw();
  h_cum_d0_rad3->Draw("Same");
  

  h_ratio_rad3_cum_tot3->Draw();
  double d0_cut = h_ratio_rad3_cum_tot3->GetBinCenter(h_ratio_rad3_cum_tot3->GetMaximumBin());
  c1->Print("Figs/Optimize_ratio_d0_cut.eps");
  c1->Print("Figs/Optimize_ratio_d0_cut.pdf");
  c1->Print("Figs/Optimize_ratio_d0_cut.png");

  h_d0_pos_Trid3->Draw("hist");
  h_d0_pos_WAB3->Draw("hist Same");
  h_d0_pos_RAD3->Draw("hist same");
  line1->DrawLine(d0_cut, 0, d0_cut, h_d0_pos_Trid3->GetMaximum());
  c1->Print("Figs/MC_d0_distributions.eps");
  c1->Print("Figs/MC_d0_distributions.pdf");
  c1->Print("Figs/MC_d0_distributions.png");


  h_d0_pos_Data3->Draw();
  f_Gaus->SetParameters(h_d0_pos_Data3->GetMaximum(), 0., 0.5);
  h_d0_pos_Data3->Fit(f_Gaus, "MeV", "", -1.2, 0.75);
  double mean_d0_data = f_Gaus->GetParameter(1);
  double sigm_d0_data = f_Gaus->GetParameter(2);
  lat1->DrawLatex(0.55, 0.7, Form("#sigma = %1.2f mm", sigm_d0_data));
  c1->Print("Figs/d0_fit_Data.eps");
  c1->Print("Figs/d0_fit_Data.pdf");
  c1->Print("Figs/d0_fit_Data.png");

  
  h_d0_trid_plus_WAB3->Draw();
  //f_Gaus->SetParameters(h_d0_pos_Data3->GetMaximum(), 0., 0.5);
  h_d0_trid_plus_WAB3->Fit(f_Gaus, "MeV", "", -1.2, 0.75);
  mean_d0_data = f_Gaus->GetParameter(1);
  sigm_d0_data = f_Gaus->GetParameter(2);
  lat1->DrawLatex(0.55, 0.7, Form("#sigma = %1.2f mm", sigm_d0_data));
  c1->Print("Figs/d0_fit_Trid_plus_WAB.eps");
  c1->Print("Figs/d0_fit_Trid_plus_WAB.pdf");
  c1->Print("Figs/d0_fit_Trid_plus_WAB.png");

  double mean_d0_trid = f_Gaus->GetParameter(1);
  double sigm_d0_trid = f_Gaus->GetParameter(2);

  double d0_data_cut = mean_d0_data + (d0_cut - mean_d0_trid)*sigm_d0_data/sigm_d0_trid;
  
  h_d0_pos_Data3->Draw("hist");
  h_d0_trid_plus_WAB3->Draw("hist same");
  //  h_d0_pos_Trid3->Draw("hist same");
  h_d0_pos_WAB3->Draw("hist Same");
  h_d0_pos_RAD3->Draw("hist same");
  line1->DrawLine(d0_cut, 0, d0_cut, h_d0_pos_Trid3->GetMaximum());
  line1->SetLineColor(4);
  line1->DrawLine(d0_data_cut, 0, d0_data_cut, h_d0_pos_Trid3->GetMaximum());
  c1->Print("Figs/d0_compare.eps");
  c1->Print("Figs/d0_compare.pdf");
  c1->Print("Figs/d0_compare.png");

  

  TH1D *h_P_ele_final_data = (TH1D*)file_Data->Get("h_P_ele_final");
  h_P_ele_final_data->SetTitle("; P_{e^{+}} [GeV]");
  h_P_ele_final_data->Scale(1./tri_data_lumi);
  h_P_ele_final_data->SetLineColor(cols["Data"]);

  TH1D *h_P_ele_final_trid = (TH1D*)file_Trid->Get("h_P_ele_final");
  h_P_ele_final_trid->Scale(1./tritrig_mc_lumi);
  h_P_ele_final_trid->SetLineColor(cols["Trid"]);

  TH1D *h_P_ele_final_WAB = (TH1D*)file_WAB->Get("h_P_ele_final");
  h_P_ele_final_WAB->SetLineColor(cols["WAB"]);
  h_P_ele_final_WAB->Scale(1./wab_mc_lumi);

  
  TH1D *h_h_P_ele_final_trid_plus_wab = (TH1D*)h_P_ele_final_trid->Clone("h_h_P_ele_final_trid_plus_wab");
  h_h_P_ele_final_trid_plus_wab->Add(h_P_ele_final_WAB);
  h_h_P_ele_final_trid_plus_wab->SetLineColor(cols["MCTot"]);
  
  
  h_P_ele_final_data->Draw();
  h_h_P_ele_final_trid_plus_wab->Draw("Same hist");
  h_P_ele_final_trid->Draw("Same hist");
  h_P_ele_final_WAB->Draw("Same hist");
  
  
}

