#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TLine.h>
#include <TLatex.h>
#include <TCanvas.h>

#include "setting_2016_pass1.h"

void Draw_Data_MC_hists(TH1D *h_Data, TH1D *h_Trid, TH1D *h_WAB, double scale, std::string title, std::string var_name);

TH1D* Calc_RadFrac(TH1D* h_RAD, TH1D *h_Trid, TH1D *h_WAB);

void Compare_Data_MC(){

  TCanvas *c1 = new TCanvas("c1", "", 750, 750);

  TLatex *lat1 = new TLatex();
  lat1->SetNDC();

  TLine *line1 = new TLine();
  line1->SetLineColor(2);
  line1->SetLineWidth(2);


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
  TH1D *h_tarP_Data_tmp = (TH1D*)h_tarP_Data->Clone("h_tarP_Data_tmp");
  h_tarP_Data_tmp->Scale(1./tri_data_lumi);

  cout<<"tri_data_lumi = "<<tri_data_lumi<<endl;
  
  TH1D *h_tarP_Trid = (TH1D*)file_Trid->Get("h_tarP1");
  TH1D *h_tarP_Trid_tmp = (TH1D*)h_tarP_Trid->Clone("h_tarP_Trid_tmp");
  h_tarP_Trid->SetName("h_tarP_Data");
  h_tarP_Trid->SetLineColor(2);
  h_tarP_Trid_tmp->Scale(1./tritrig_mc_lumi);

  TH1D *h_tarP_WAB = (TH1D*)file_WAB->Get("h_tarP1");
  TH1D *h_tarP_WAB_tmp = (TH1D*)h_tarP_WAB->Clone("h_tarP_WAB_tmp");
  h_tarP_WAB->SetName("h_tarP_Data");
  h_tarP_WAB->SetLineColor(3);
  h_tarP_WAB_tmp->Scale(1./wab_mc_lumi);

  TH1D *h_tarP_trid_plus_WAB = (TH1D*)h_tarP_Trid_tmp->Clone("h_tarP_trid_plus_WAB");
  h_tarP_trid_plus_WAB->Add(h_tarP_WAB_tmp);
  h_tarP_trid_plus_WAB->SetLineColor(4);

  int cut_bin1 = h_tarP_Trid_tmp->FindBin(Psum_min);
  int cut_bin2 = h_tarP_Trid_tmp->FindBin(1.2*Eb);

  double scale = h_tarP_Data_tmp->Integral(cut_bin1, cut_bin2)/h_tarP_trid_plus_WAB->Integral(cut_bin1, cut_bin2);
  h_tarP_trid_plus_WAB->Scale(scale);
  cout<<"Scale = "<<scale<<endl;
  
  h_tarP_Data->Draw("hist");
  h_tarP_trid_plus_WAB->Draw("Same hist");
  h_tarP_Trid->Draw("Same hist");
  lat1->DrawLatex(0.7, 0.5, Form("Scale = %1.2f", scale));
  c1->Print("Figs/tarP_scale.eps");
  c1->Print("Figs/tarP_scale.pdf");
  c1->Print("Figs/tarP_scale.png");

  
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
  TH1D *h_P_ele_final_trid = (TH1D*)file_Trid->Get("h_P_ele_final");
  TH1D *h_P_ele_final_WAB = (TH1D*)file_WAB->Get("h_P_ele_final");
  Draw_Data_MC_hists(h_P_ele_final_data, h_P_ele_final_trid, h_P_ele_final_WAB, scale, "; P_{e^{-}} [GeV]; #sigma b/GeV", "eleP_final");
  c1->Print("Figs/ele_P_compare.eps");
  c1->Print("Figs/ele_P_compare.pdf");
  c1->Print("Figs/ele_P_compare.png");
  
  TH1D *h_P_pos_final_data = (TH1D*)file_Data->Get("h_P_pos_final");
  TH1D *h_P_pos_final_trid = (TH1D*)file_Trid->Get("h_P_pos_final");
  TH1D *h_P_pos_final_WAB = (TH1D*)file_WAB->Get("h_P_pos_final");
  Draw_Data_MC_hists(h_P_pos_final_data, h_P_pos_final_trid, h_P_pos_final_WAB, scale, "; P_{e^{+}} [GeV]; #sigma b/GeV", "posP_final");
  c1->Print("Figs/pos_P_compare.eps");
  c1->Print("Figs/pos_P_compare.pdf");
  c1->Print("Figs/pos_P_compare.png");

  TH1D *h_phi0_ele_final_data = (TH1D*)file_Data->Get("h_phi0_ele_final");
  TH1D *h_phi0_ele_final_trid = (TH1D*)file_Trid->Get("h_phi0_ele_final");
  TH1D *h_phi0_ele_final_WAB = (TH1D*)file_WAB->Get("h_phi0_ele_final");
  Draw_Data_MC_hists(h_phi0_ele_final_data, h_phi0_ele_final_trid, h_phi0_ele_final_WAB, scale, "; #phi_{0}^{e^{-}} [GeV]; #sigma [b/deg]", "ele_phi0_final");
  c1->Print("Figs/phi0_ele_compare.eps");
  c1->Print("Figs/phi0_ele_compare.pdf");
  c1->Print("Figs/phi0_ele_compare.png");
  
  TH1D *h_phi0_pos_final_data = (TH1D*)file_Data->Get("h_phi0_pos_final");
  TH1D *h_phi0_pos_final_trid = (TH1D*)file_Trid->Get("h_phi0_pos_final");
  TH1D *h_phi0_pos_final_WAB = (TH1D*)file_WAB->Get("h_phi0_pos_final");
  Draw_Data_MC_hists(h_phi0_pos_final_data, h_phi0_pos_final_trid, h_phi0_pos_final_WAB, scale, "; #phi_{0}^{e^{+}} [GeV]; #sigma [b/deg]", "pos_phi0_final");
  c1->Print("Figs/phi0_pos_compare.eps");
  c1->Print("Figs/phi0_pos_compare.pdf");
  c1->Print("Figs/phi0_pos_compare.png");
  
  TH1D *h_tanLambda_ele_final_data = (TH1D*)file_Data->Get("h_tanLambda_ele_final");
  TH1D *h_tanLambda_ele_final_trid = (TH1D*)file_Trid->Get("h_tanLambda_ele_final");
  TH1D *h_tanLambda_ele_final_WAB = (TH1D*)file_WAB->Get("h_tanLambda_ele_final");
  Draw_Data_MC_hists(h_tanLambda_ele_final_data, h_tanLambda_ele_final_trid, h_tanLambda_ele_final_WAB, scale, "; #lambda(e^{-}) [deg]; #signa [b/deg]", "ele_tanLambda_final");
  c1->Print("Figs/tanLambda_ele_compare.eps");
  c1->Print("Figs/tanLambda_ele_compare.pdf");
  c1->Print("Figs/tanLambda_ele_compare.png");

  TH1D *h_tanLambda_pos_final_data = (TH1D*)file_Data->Get("h_tanLambda_pos_final");
  TH1D *h_tanLambda_pos_final_trid = (TH1D*)file_Trid->Get("h_tanLambda_pos_final");
  TH1D *h_tanLambda_pos_final_WAB = (TH1D*)file_WAB->Get("h_tanLambda_pos_final");
  Draw_Data_MC_hists(h_tanLambda_pos_final_data, h_tanLambda_pos_final_trid, h_tanLambda_pos_final_WAB, scale, "; #lambda(e^{+}) [deg]; #signa [b/deg]", "pos_tanLambda_final");
  c1->Print("Figs/tanLambda_pos_compare.eps");
  c1->Print("Figs/tanLambda_pos_compare.pdf");
  c1->Print("Figs/tanLambda_pos_compare.png");


  TH1D *h_tarM_final_data = (TH1D*)file_Data->Get("h_tarM6");
  TH1D *h_tarM_final_Trid = (TH1D*)file_Trid->Get("h_tarM6");
  TH1D *h_tarM_final_WAB = (TH1D*)file_WAB->Get("h_tarM6");

  Draw_Data_MC_hists(h_tarM_final_data, h_tarM_final_Trid, h_tarM_final_WAB, scale, "; M(e^{-}e^{+}); #sigma [GeV^{-1}]", "tarM_final");
  c1->Print("Figs/tarM_compare.eps");
  c1->Print("Figs/tarM_compare.pdf");
  c1->Print("Figs/tarM_compare.png");


  
  Draw_Data_MC_hists(h_tarP_Data, h_tarP_Trid, h_tarP_WAB, scale, "; P_{sum} [GeV]; #sigma [b/GeV]", "tarP_final" );
  c1->Print("Figs/tarP_compare.eps");
  c1->Print("Figs/tarP_compare.pdf");
  c1->Print("Figs/tarP_compare.png");
  
  // =================================                                    ==============================
  // =================================            RAD FRACTION            ==============================
  // =================================                                    ==============================

  TF1 *f_RadFrac = new TF1("f_RadFrac", "[0] + [1]*exp(-x/[2])", 0., 2.5);
  
  TH1D *h_tarM_final_largebins_data = (TH1D*)file_Data->Get("h_tarM_largebins");
  TH1D *h_tarM_final_largebins_Trid = (TH1D*)file_Trid->Get("h_tarM_largebins");
  TH1D *h_tarM_final_largebins_WAB = (TH1D*)file_WAB->Get("h_tarM_largebins");
  TH1D *h_tarM_final_largebins_RAD = (TH1D*)file_RAD->Get("h_tarM_largebins");

   
  TH1D *h_RadFeac = (TH1D*)Calc_RadFrac(h_tarM_final_largebins_RAD, h_tarM_final_largebins_Trid, h_tarM_final_largebins_WAB);
  h_RadFeac->SetTitle("; M(e^{-}e^{+}) [GeV]; rad.frac.");
  h_RadFeac->SetTitleOffset(1.4, "Y");
  h_RadFeac->Draw();
  f_RadFrac->SetParameters(0.1549, -0.2473, 0.0276); // Setting Sebouh's parameters
  f_RadFrac->SetLineColor(4);
  f_RadFrac->DrawCopy("Same");
  f_RadFrac->SetLineColor(2);
  h_RadFeac->Fit(f_RadFrac, "MeV", "", 0.01, 0.19);
  lat1->SetTextColor(4);
  lat1->DrawLatex(0.2, 0.8, "Sebouh's function");
  lat1->SetTextColor(2);
  lat1->DrawLatex(0.2, 0.75, "New fit");
  c1->Print("Figs/Rad_Frac.eps");
  c1->Print("Figs/Rad_Frac.pdf");
  c1->Print("Figs/Rad_Frac.png");
  
}


void Draw_Data_MC_hists(TH1D *h_Data_Orig, TH1D *h_Trid_Orig, TH1D *h_WAB_Orig, double scale, std::string title, std::string var_name){

  cols["Data"] = 1;
  cols["Trid"] = 2;
  cols["WAB"] = 3;
  cols["MCTot"] = 4;

  TH1D *h_Data = (TH1D*)h_Data_Orig->Clone(Form("h_%s_Data", var_name.c_str()));
  h_Data->SetTitle(title.c_str());
  //h_Data->SetName(Form("h_%s_Data", var_name.c_str()));
  h_Data->Scale(1./tri_data_lumi);
  h_Data->Scale(1./h_Data->GetBinWidth(1));
  h_Data->SetLineColor(cols["Data"]);

  TH1D *h_Trid = (TH1D*)h_Trid_Orig->Clone(Form("h_%s_Trid", var_name.c_str()));
  h_Trid->Scale(scale/tritrig_mc_lumi);
  h_Trid->Scale(1./h_Trid->GetBinWidth(1));
  //h_Trid->SetName(Form("h_%s_Trid", var_name.c_str()));
  h_Trid->SetLineColor(cols["Trid"]);

  TH1D *h_WAB = (TH1D*)h_WAB_Orig->Clone(Form("h_%s_WAB", var_name.c_str()));
  h_WAB->Scale(scale/wab_mc_lumi);
  h_WAB->Scale(1./h_WAB->GetBinWidth(1));
  //h_WAB->SetName(Form("h_%s_WAB", var_name.c_str()));
  h_WAB->SetLineColor(cols["WAB"]);

  TH1D *h_MCTot = (TH1D*)h_Trid->Clone(Form("h_%s_MCTot", var_name.c_str()));
  h_MCTot->Add(h_WAB);
  h_MCTot->SetLineColor(cols["MCTot"]);


  h_Data->SetAxisRange(0., 1.05*TMath::Max(h_Data->GetMaximum(), h_MCTot->GetMaximum()), "Y");

  h_Data->Draw("hist");
  h_MCTot->Draw("Same");

}


TH1D* Calc_RadFrac(TH1D* h_RAD_orig, TH1D *h_Trid_orig, TH1D *h_WAB_orig){


  TH1D *h_Trid = (TH1D*)h_Trid_orig->Clone("h_Trid_tarM");
  h_Trid->Scale(1./tritrig_mc_lumi);
  TH1D *h_WAB = (TH1D*)h_WAB_orig->Clone("h_WAB_tarM");
  h_WAB->Scale(1./wab_mc_lumi);
  TH1D *h_RAD = (TH1D*)h_RAD_orig->Clone("h_RAD_tarM");
  h_RAD->Scale(1./rad_mc_lumi);
  
  TH1D *h_MC_Tot = (TH1D*)h_Trid->Clone("h_MC_Tot");
  h_MC_Tot->Add(h_WAB);

  TH1D *h_RadFrac = (TH1D*)h_RAD->Clone("h_RadFrac");
  h_RadFrac->Divide(h_MC_Tot);

  return h_RadFrac;  
}
