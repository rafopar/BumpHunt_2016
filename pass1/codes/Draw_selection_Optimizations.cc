#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TGraph.h>
#include <Slice_Fitter.h>
#include "setting_2016_pass1.h"
#include "/Work/Soft/root_funcs/funcs1.C"

#include <fstream>

using namespace std;

void Draw_2Hists_Ontop(TH1D*, TH1D*, TCanvas*);
TF1 *SumTF1s(TF1*, TF1*, const char*, double, double, double, double);

TF1 *f_aa;
TF1 *f_bb;

double Sum2Funcs(double *, double *);

void Draw_selection_Optimizations(){

  gSystem->Load("libtoollibs.so");
  
  TCanvas *c1 = new TCanvas("c1", "", 750, 750);

  ofstream out_file("cut_parameters.dat");

  std::string data_type = "Data";
  
  //TFile *file_in = new TFile("Event_Selection_Data.root");
  //TFile *file_in = new TFile("Event_Selection_Tritrig.root");

  TFile *file_in = new TFile(Form("Event_Selection_%s.root", data_type.c_str()));

  TH1D *h_Nsigma_ele_top1 = (TH1D*)file_in->Get("h_Nsigma_ele_top1");
  TH1D *h_Nsigma_ele_top_Tight1 = (TH1D*)file_in->Get("h_Nsigma_ele_top_Tight1");

  h_Nsigma_ele_top1->SetTitle("Electrons: Top; N#sigma");
  Draw_2Hists_Ontop(h_Nsigma_ele_top1, h_Nsigma_ele_top_Tight1, c1);
  c1->Print(Form("Figs/%s_Nsigma_ele_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_ele_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_ele_top_optimize.png", data_type.c_str()));


  TH1D *h_Nsigma_ele_bot1 = (TH1D*)file_in->Get("h_Nsigma_ele_bot1");
  TH1D *h_Nsigma_ele_bot_Tight1 = (TH1D*)file_in->Get("h_Nsigma_ele_bot_Tight1");

  h_Nsigma_ele_bot1->SetTitle("Electrons: Bot; N#sigma");
  Draw_2Hists_Ontop(h_Nsigma_ele_bot1, h_Nsigma_ele_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_Nsigma_ele_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_ele_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_ele_bot_optimize.png", data_type.c_str()));


  TH1D *h_Nsigma_pos_top1 = (TH1D*)file_in->Get("h_Nsigma_pos_top1");
  TH1D *h_Nsigma_pos_top_Tight1 = (TH1D*)file_in->Get("h_Nsigma_pos_top_Tight1");

  h_Nsigma_pos_top1->SetTitle("Positrons: Top; N#sigma");
  Draw_2Hists_Ontop(h_Nsigma_pos_top1, h_Nsigma_pos_top_Tight1, c1);
  c1->Print(Form("Figs/%s_Nsigma_pos_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_pos_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_pos_top_optimize.png", data_type.c_str()));


  TH1D *h_Nsigma_pos_bot1 = (TH1D*)file_in->Get("h_Nsigma_pos_bot1");
  TH1D *h_Nsigma_pos_bot_Tight1 = (TH1D*)file_in->Get("h_Nsigma_pos_bot_Tight1");

  h_Nsigma_pos_bot1->SetTitle("Positrons: Bot; N#sigma");
  Draw_2Hists_Ontop(h_Nsigma_pos_bot1, h_Nsigma_pos_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_Nsigma_pos_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_pos_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_Nsigma_pos_bot_optimize.png", data_type.c_str()));


  TH1D *h_chi2NDF_ele_6hits_top1 = (TH1D*)file_in->Get("h_chi2NDF_ele_6hits_top1");
  TH1D *h_chi2NDF_ele_6hits_top_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_ele_6hits_top_Tight1");
  h_chi2NDF_ele_6hits_top1->SetTitle("Electrons: 6 hits: Top; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_ele_6hits_top1, h_chi2NDF_ele_6hits_top_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_top_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_ele_6hits_bot1 = (TH1D*)file_in->Get("h_chi2NDF_ele_6hits_bot1");
  TH1D *h_chi2NDF_ele_6hits_bot_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_ele_6hits_bot_Tight1");
  h_chi2NDF_ele_6hits_bot1->SetTitle("Electrons: 6 hits: Bot; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_ele_6hits_bot1, h_chi2NDF_ele_6hits_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_6hits_bot_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_ele_5hits_top1 = (TH1D*)file_in->Get("h_chi2NDF_ele_5hits_top1");
  TH1D *h_chi2NDF_ele_5hits_top_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_ele_5hits_top_Tight1");
  h_chi2NDF_ele_5hits_top1->SetTitle("Electrons: 5 hits: Top; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_ele_5hits_top1, h_chi2NDF_ele_5hits_top_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_top_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_ele_5hits_bot1 = (TH1D*)file_in->Get("h_chi2NDF_ele_5hits_bot1");
  TH1D *h_chi2NDF_ele_5hits_bot_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_ele_5hits_bot_Tight1");
  h_chi2NDF_ele_5hits_bot1->SetTitle("Electrons: 5 hits: Bot; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_ele_5hits_bot1, h_chi2NDF_ele_5hits_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_ele_5hits_bot_optimize.png", data_type.c_str()));

  
  TH1D *h_chi2NDF_pos_6hits_top1 = (TH1D*)file_in->Get("h_chi2NDF_pos_6hits_top1");
  TH1D *h_chi2NDF_pos_6hits_top_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_pos_6hits_top_Tight1");
  h_chi2NDF_pos_6hits_top1->SetTitle("Positrons: 6 hits: Top; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_pos_6hits_top1, h_chi2NDF_pos_6hits_top_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_top_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_pos_6hits_bot1 = (TH1D*)file_in->Get("h_chi2NDF_pos_6hits_bot1");
  TH1D *h_chi2NDF_pos_6hits_bot_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_pos_6hits_bot_Tight1");
  h_chi2NDF_pos_6hits_bot1->SetTitle("Positrons: 6 hits: Bot; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_pos_6hits_bot1, h_chi2NDF_pos_6hits_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_6hits_bot_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_pos_5hits_top1 = (TH1D*)file_in->Get("h_chi2NDF_pos_5hits_top1");
  TH1D *h_chi2NDF_pos_5hits_top_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_pos_5hits_top_Tight1");
  h_chi2NDF_pos_5hits_top1->SetTitle("Positrons: 5 hits: Top; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_pos_5hits_top1, h_chi2NDF_pos_5hits_top_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_top_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_top_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_top_optimize.png", data_type.c_str()));
  
  TH1D *h_chi2NDF_pos_5hits_bot1 = (TH1D*)file_in->Get("h_chi2NDF_pos_5hits_bot1");
  TH1D *h_chi2NDF_pos_5hits_bot_Tight1 = (TH1D*)file_in->Get("h_chi2NDF_pos_5hits_bot_Tight1");
  h_chi2NDF_pos_5hits_bot1->SetTitle("Positrons: 5 hits: Bot; #chi^{2}/NDF");
  Draw_2Hists_Ontop(h_chi2NDF_pos_5hits_bot1, h_chi2NDF_pos_5hits_bot_Tight1, c1);
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_bot_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_bot_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_chi2NDF_pos_5hits_bot_optimize.png", data_type.c_str()));

  //========================== Track Cluster Delta T: Electrons Top ======================

  TH2D *h_trk_clust_dt_P_ele_top1 = (TH2D*)file_in->Get("h_trk_clust_dt_P_ele_top1");
  h_trk_clust_dt_P_ele_top1->SetTitle("Electrons: Top; P[GeV];  #Delta t(trk - clust) [ns]");
  h_trk_clust_dt_P_ele_top1->Draw("colz");
  c1->Print(Form("Figs/%s_trk_clust_dt_P_ele_top_loose.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_clust_dt_P_ele_top_loose.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_clust_dt_P_ele_top_loose.png", data_type.c_str()));

  
  TH1D *h_trk_clust_dt_ele_top1 = (TH1D*)file_in->Get("h_trk_clust_dt_ele_top1");
  TH1D *h_trk_clust_dt_ele_top_Tight1 = (TH1D*)file_in->Get("h_trk_clust_dt_ele_top_Tight1");
  h_trk_clust_dt_ele_top1->SetTitle("Electrons: Top; #Delta t(trk - clust) [ns]");
  Draw_2Hists_Ontop(h_trk_clust_dt_ele_top1, h_trk_clust_dt_ele_top_Tight1, c1);

  TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", -10., 10.);
  f_Gaus->SetParLimits(2, 0., 5.);
  f_Gaus->SetNpx(4500);

  TF1 *f_Pol3 = new TF1("f_Pol3", "[0] + x*([1] + x*([2] + x*[3] ) )", 0., 2.5);
  f_Pol3->SetNpx(4500);

  TF1 *f_Pol4 = new TF1("f_Pol4", "[0] + x*([1] + x*([2] + x*([3] + x*[4]) ) )", 0., 2.5);
  f_Pol4->SetNpx(4500);

  TH2D *h_trk_clust_dt_P_ele_top_Tight1 = (TH2D*)file_in->Get("h_trk_clust_dt_P_ele_top_Tight1");
  h_trk_clust_dt_P_ele_top_Tight1->SetTitle("Electrons: Top; P[GeV];  #Delta t(trk - clust) [ns]");
  TSlice_Fitter sl_fit(h_trk_clust_dt_P_ele_top_Tight1, "trk_cl_dt_ele_Top", f_Gaus, 12, 0.4, 1.8);
  sl_fit.Do_SliceFit(2.2);

  TGraph *gr_mean = sl_fit.GetGrMean();
  gr_mean->SetMarkerColor(2);
  gr_mean->SetMarkerStyle(20);
  TGraph *gr_sigm = sl_fit.GetGrSigm();
  gr_sigm->SetMarkerColor(2);
  gr_sigm->SetMarkerStyle(21);

  gr_mean->Draw("AP");
  gr_mean->Fit(f_Pol3, "MeV", "", 0.4, 1.7);

  out_file<<" ===============  Track Cluster Delta T: Electrons Top ============= "<<endl;
  out_file<<" ===== mean ===== "<<endl;
  out_file<<f_Pol3->GetParameter(0)<<" + x*("<<f_Pol3->GetParameter(1)<<") + x*x*("<<f_Pol3->GetParameter(2)<<") + x*x*x*("<<f_Pol3->GetParameter(3)<<")"<<endl;

  c1->Clear();
  gr_sigm->Draw("AP");
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.4, 1.7);
  out_file<<" ===== sigm ===== "<<endl;
  out_file<<f_Pol4->GetParameter(0)<<" + x*("<<f_Pol4->GetParameter(1)<<") + x*x*("<<f_Pol4->GetParameter(2)<<") + x*x*x*("<<
    f_Pol4->GetParameter(3)<<") + x*x*x*x*("<<f_Pol4->GetParameter(4)<<")"<<endl;
  
  TF1 *f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_UP_ele_top", 0.4, 1.6, 1., 3.);
  TF1 *f_low_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_LOW_ele_top", 0.4, 1.6, 1., -3.);
  TF1 *f_mean = (TF1*)f_Pol3->Clone("f_mean");
  f_mean->SetRange(0.4, 1.6);
  
  h_trk_clust_dt_P_ele_top_Tight1->Draw("colz");
  
  f_up_lim->Draw("Same");
  f_mean->Draw("Same");
  f_low_lim->Draw("Same");
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_top.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_top.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_top.png", data_type.c_str()));


  //========================== Track Cluster Delta T: Electrons Bottom ======================
  
  TH1D *h_trk_clust_dt_ele_bot1 = (TH1D*)file_in->Get("h_trk_clust_dt_ele_bot1");
  TH1D *h_trk_clust_dt_ele_bot_Tight1 = (TH1D*)file_in->Get("h_trk_clust_dt_ele_bot_Tight1");
  h_trk_clust_dt_ele_bot1->SetTitle("Electrons: Bot ; #Delta t(trk - clust) [ns]");

  TH2D *h_trk_clust_dt_P_ele_bot_Tight1 = (TH2D*)file_in->Get("h_trk_clust_dt_P_ele_bot_Tight1");
  h_trk_clust_dt_P_ele_bot_Tight1->SetTitle("Electrons: Bot; P[GeV];  #Delta t(trk - clust) [ns]");
  h_trk_clust_dt_P_ele_bot_Tight1->Draw("colz");
  sl_fit.SetAll(h_trk_clust_dt_P_ele_bot_Tight1, "trk_cl_dt_ele_Bot", f_Gaus, 12, 0.4, 1.8);
  sl_fit.Do_SliceFit(2.2);

  gr_mean = sl_fit.GetGrMean();
  gr_sigm = sl_fit.GetGrSigm();

  gr_mean->Fit(f_Pol3, "MeV", "", 0.4, 1.7);
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.4, 1.7);

  out_file<<endl<<endl<<endl;
  out_file<<" ===============  Track Cluster Delta T: Electrons Bottom ============= "<<endl;
  out_file<<" ===== mean ===== "<<endl;
  out_file<<f_Pol3->GetParameter(0)<<" + x*("<<f_Pol3->GetParameter(1)<<") + x*x*("<<f_Pol3->GetParameter(2)<<") + x*x*x*("<<f_Pol3->GetParameter(3)<<")"<<endl;
  out_file<<" ===== sigm ===== "<<endl;
  out_file<<f_Pol4->GetParameter(0)<<" + x*("<<f_Pol4->GetParameter(1)<<") + x*x*("<<f_Pol4->GetParameter(2)<<") + x*x*x*("<<
    f_Pol4->GetParameter(3)<<") + x*x*x*x*("<<f_Pol4->GetParameter(4)<<")"<<endl;

  
  f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_UP_ele_top", 0.4, 1.6, 1., 3.);
  f_low_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_LOW_ele_top", 0.4, 1.6, 1., -3.);
  f_mean = (TF1*)f_Pol3->Clone("f_mean_trk_cl_dt_UP_ele_top");
  f_mean->SetRange(0.4, 1.6);
  
  h_trk_clust_dt_P_ele_bot_Tight1->Draw("colz");
  
  f_up_lim->Draw("Same");
  f_mean->Draw("Same");
  f_low_lim->Draw("Same");
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_bot.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_bot.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_ele_bot.png", data_type.c_str()));

  //========================== Track Cluster Delta T: Positrons Top ======================
  
  TH1D *h_trk_clust_dt_pos_top1 = (TH1D*)file_in->Get("h_trk_clust_dt_pos_top1");
  TH1D *h_trk_clust_dt_pos_top_Tight1 = (TH1D*)file_in->Get("h_trk_clust_dt_pos_top_Tight1");
  h_trk_clust_dt_pos_top1->SetTitle("Positrons: Top ; #Delta t(trk - clust) [ns]");

  TH2D *h_trk_clust_dt_P_pos_top_Tight1 = (TH2D*)file_in->Get("h_trk_clust_dt_P_pos_top_Tight1");
  h_trk_clust_dt_P_pos_top_Tight1->SetTitle("Positrons: Top; P[GeV];  #Delta t(trk - clust) [ns]");
  h_trk_clust_dt_P_pos_top_Tight1->Draw("colz");
  sl_fit.SetAll(h_trk_clust_dt_P_pos_top_Tight1, "trk_cl_dt_pos_Top", f_Gaus, 12, 0.4, 1.8);
  sl_fit.Do_SliceFit(2.2);

  gr_mean = sl_fit.GetGrMean();
  gr_sigm = sl_fit.GetGrSigm();

  gr_mean->Fit(f_Pol3, "MeV", "", 0.4, 1.7);
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.4, 1.7);

  out_file<<endl<<endl<<endl;
  out_file<<" ===============  Track Cluster Delta T: Positrons Top ============= "<<endl;
  out_file<<" ===== mean ===== "<<endl;
  out_file<<f_Pol3->GetParameter(0)<<" + x*("<<f_Pol3->GetParameter(1)<<") + x*x*("<<f_Pol3->GetParameter(2)<<") + x*x*x*("<<f_Pol3->GetParameter(3)<<")"<<endl;
  out_file<<" ===== sigm ===== "<<endl;
  out_file<<f_Pol4->GetParameter(0)<<" + x*("<<f_Pol4->GetParameter(1)<<") + x*x*("<<f_Pol4->GetParameter(2)<<") + x*x*x*("<<
    f_Pol4->GetParameter(3)<<") + x*x*x*x*("<<f_Pol4->GetParameter(4)<<")"<<endl;

  
  f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_UP_pos_top", 0.4, 1.6, 1., 3.);
  f_low_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_LOW_pos_top", 0.4, 1.6, 1., -3.);
  f_mean = (TF1*)f_Pol3->Clone("f_mean_trk_cl_dt_UP_pos_top");
  f_mean->SetRange(0.4, 1.6);
  
  h_trk_clust_dt_P_pos_top_Tight1->Draw("colz");
  
  f_up_lim->Draw("Same");
  f_mean->Draw("Same");
  f_low_lim->Draw("Same");
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_top.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_top.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_top.png", data_type.c_str()));

  //========================== Track Cluster Delta T: Positrons Bot ======================
  
  TH1D *h_trk_clust_dt_pos_bot1 = (TH1D*)file_in->Get("h_trk_clust_dt_pos_bot1");
  TH1D *h_trk_clust_dt_pos_bot_Tight1 = (TH1D*)file_in->Get("h_trk_clust_dt_pos_bot_Tight1");
  h_trk_clust_dt_pos_bot1->SetTitle("Positrons: Bot ; #Delta t(trk - clust) [ns]");

  TH2D *h_trk_clust_dt_P_pos_bot_Tight1 = (TH2D*)file_in->Get("h_trk_clust_dt_P_pos_bot_Tight1");
  h_trk_clust_dt_P_pos_bot_Tight1->SetTitle("Positrons: Bot; P[GeV];  #Delta t(trk - clust) [ns]");
  h_trk_clust_dt_P_pos_bot_Tight1->Draw("colz");
  sl_fit.SetAll(h_trk_clust_dt_P_pos_bot_Tight1, "trk_cl_dt_pos_Bot", f_Gaus, 12, 0.4, 1.8);
  sl_fit.Do_SliceFit(2.2);

  gr_mean = sl_fit.GetGrMean();
  gr_sigm = sl_fit.GetGrSigm();

  gr_mean->Fit(f_Pol3, "MeV", "", 0.4, 1.7);
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.4, 1.7);

  out_file<<endl<<endl<<endl;
  out_file<<" ===============  Track Cluster Delta T: Positrons Bot ============= "<<endl;
  out_file<<" ===== mean ===== "<<endl;
  out_file<<f_Pol3->GetParameter(0)<<" + x*("<<f_Pol3->GetParameter(1)<<") + x*x*("<<f_Pol3->GetParameter(2)<<") + x*x*x*("<<f_Pol3->GetParameter(3)<<")"<<endl;
  out_file<<" ===== sigm ===== "<<endl;
  out_file<<f_Pol4->GetParameter(0)<<" + x*("<<f_Pol4->GetParameter(1)<<") + x*x*("<<f_Pol4->GetParameter(2)<<") + x*x*x*("<<
    f_Pol4->GetParameter(3)<<") + x*x*x*x*("<<f_Pol4->GetParameter(4)<<")"<<endl;


  
  f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_UP_pos_bot", 0.4, 1.6, 1., 3.);
  f_low_lim = SumTF1s(f_Pol3, f_Pol4, "f_trk_cl_dt_LOW_pos_bot", 0.4, 1.6, 1., -3.);
  f_mean = (TF1*)f_Pol3->Clone("f_mean_trk_cl_dt_UP_pos_bot");
  f_mean->SetRange(0.4, 1.6);
  
  h_trk_clust_dt_P_pos_bot_Tight1->Draw("colz");
  
  f_up_lim->Draw("Same");
  f_mean->Draw("Same");
  f_low_lim->Draw("Same");
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_bot.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_bot.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_trk_cl_dt_P_pos_bot.png", data_type.c_str()));


  // ===================== ele_pos cluster Delta_t ========================
  TH1D *h_cl_dt1 = (TH1D*)file_in->Get("h_cl_dt1");
  h_cl_dt1->SetTitle("; #Delta t_{cl} (ele. - pos.) [ns]");
  TH1D *h_cl_dt_Tight1 = (TH1D*)file_in->Get("h_cl_dt_Tight1");
  c1->SetLogy();
  
  Draw_2Hists_Ontop(h_cl_dt1, h_cl_dt_Tight1, c1);
  h_cl_dt_Tight1->Fit(f_Gaus, "MeV", "Same", -1.5, 1.5);
  
  c1->Print(Form("Figs/%s_cl_Dt_optimize.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_Dt_optimize.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_Dt_optimize.png", data_type.c_str()));
  c1->SetLogy(0);




  // ====================== As a function of ESum ===================
  TH2D *h_cl_dt_Esum1 = (TH2D*)file_in->Get("h_cl_dt_Esum1");
  h_cl_dt_Esum1->SetTitle("; E_{sum} [GeV]; t_{ele} - e_{pos} [ns]");
  h_cl_dt_Esum1->SetAxisRange(-4., 4., "Y");
  h_cl_dt_Esum1->Draw("colz");
  c1->Print(Form("Figs/%s_cl_dt_ESum1.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_ESum1.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_ESum1.png", data_type.c_str()));

  
  TH2D *h_cl_dt_Esum_Tight1 = (TH2D*)file_in->Get("h_cl_dt_Esum_Tight1");
  h_cl_dt_Esum_Tight1->SetTitle("; E_{sum} [GeV]; t_{ele} - e_{pos} [ns]");
  h_cl_dt_Esum_Tight1->SetAxisRange(-4., 4., "Y");

  sl_fit.SetAll(h_cl_dt_Esum_Tight1, "cl_dt_ESum", f_Gaus, 12, 0.9, 2.4);
  sl_fit.Do_SliceFit(2.2);

  gr_mean = sl_fit.GetGrMean();
  gr_sigm = sl_fit.GetGrSigm();

  gr_mean->Fit(f_Pol3, "MeV", "", 0.9, 2.4);
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.9, 2.4);

  f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_cl_dt_UP_Esum", 0.9, 2.4, 1., 3.);
  f_low_lim = SumTF1s(f_Pol3, f_Pol4, "fcl_dt_LOW_Esum", 0.9, 2.4, 1., -3.);
  f_mean = (TF1*)f_Pol3->Clone("f_mean_cl_dt_Esum");
  f_mean->SetRange(0.9, 2.4);

  h_cl_dt_Esum_Tight1->Draw("colz");
  f_up_lim->Draw("Same");
  f_low_lim->Draw("Same");
  f_mean->Draw("Same");
  
  out_file<<endl<<endl<<endl;
  out_file<<" =============== Ele Pos clust dt ============= "<<endl;
  out_file<<" ===== mean ===== "<<endl;
  out_file<<f_Pol3->GetParameter(0)<<" + x*("<<f_Pol3->GetParameter(1)<<") + x*x*("<<f_Pol3->GetParameter(2)<<") + x*x*x*("<<f_Pol3->GetParameter(3)<<")"<<endl;
  out_file<<" ===== sigm ===== "<<endl;
  out_file<<f_Pol4->GetParameter(0)<<" + x*("<<f_Pol4->GetParameter(1)<<") + x*x*("<<f_Pol4->GetParameter(2)<<") + x*x*x*("<<
    f_Pol4->GetParameter(3)<<") + x*x*x*x*("<<f_Pol4->GetParameter(4)<<")"<<endl;


  c1->Print(Form("Figs/%s_cl_dt_ESum_Tight1.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_ESum_Tight1.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_ESum_Tight1.png", data_type.c_str()));


  TH2D *h_cl_dt_Esum2 = (TH2D*)file_in->Get("h_cl_dt_Esum2");
  h_cl_dt_Esum2->SetTitle("; E_{sum} [GeV]; t_{ele} - e_{pos} [ns]");
  h_cl_dt_Esum2->Draw("colz");
  f_up_lim->Draw("Same");
  f_low_lim->Draw("Same");
  f_mean->Draw("Same");
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_fromTight.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_fromTight.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_fromTight.png", data_type.c_str()));


  sl_fit.SetAll(h_cl_dt_Esum2, "cl_dt_Esum2", f_Gaus, 12, 0.9, 2.4);
  sl_fit.Do_SliceFit(2.2);

  gr_mean = sl_fit.GetGrMean();
  gr_sigm = sl_fit.GetGrSigm();

  gr_mean->Fit(f_Pol3, "MeV", "", 0.9, 2.4);
  gr_sigm->Fit(f_Pol4, "MeV", "", 0.9, 2.4);

  f_up_lim = SumTF1s(f_Pol3, f_Pol4, "f_cl_dt_UP_Esum2", 0.9, 2.4, 1., 3.);
  f_low_lim = SumTF1s(f_Pol3, f_Pol4, "fcl_dt_LOW_Esum2", 0.9, 2.4, 1., -3.);
  f_mean = (TF1*)f_Pol3->Clone("f_mean_cl_dt_Esum2");
  f_mean->SetRange(0.9, 2.4);

  h_cl_dt_Esum2->Draw("colz");
  f_up_lim->Draw("Same");
  f_low_lim->Draw("Same");
  f_mean->Draw("Same");
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_slFIt.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_slFIt.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_Esum2_cuts_slFIt.png", data_type.c_str()));

  TH1D *h_Proj_cl_dt2 = (TH1D*)h_cl_dt_Esum2->ProjectionY("h_Proj_cl_dt2", h_cl_dt_Esum2->GetXaxis()->FindBin(Psum_min), h_cl_dt_Esum2->GetXaxis()->FindBin(2.4));
  h_Proj_cl_dt2->Draw();

  const int npar_14 = 44; // 44 = 3*14 + 2
  TF1 *f_MultiGauss_14 = new TF1("f_MultiGauss_14", MultiGauss, -9., 9., npar_14);  

  double pars14_Gaus[npar_14] = { 14, 0, h_Proj_cl_dt2->GetMaximum(), 0., 0.3,  0.1*h_Proj_cl_dt2->GetMaximum(), 0., 1., 40, -6., 0.3, 4, -6., 1., 65, -4., 0.3, 6.5, -4., 1., 180, -2., 0.3, 18., -2., 1.,
				  120, 2., 0.3, 12., 2., 1.,  65, 4., 0.3, 6.5, 4., 1., 40, 6., 0.3, 4, 6., 1.}

  f_MultiGauss_14->SetParameters(pars14_Gaus);
  
  f_MultiGauss_14->SetParameters(14, -1, h_Proj_cl_dt2->GetMaximum(), 0., 0.3, );
  
  TF1 *f_8Gaus = new TF1("f_8Gaus", "[0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Gaus(x, [4], [5]) + [6]*TMath::Gaus(x, [7], [8]) + [9]*TMath::Gaus(x, [10], [11]) + [12]*TMath::Gaus(x, [13], [14]) + [15]*TMath::Gaus(x, [16], [17]) + [18]*TMath::Gaus(x, [19], [20]) + [21]*TMath::Gaus(x, [22], [23])", -7., 7.);
  double pars8_Gaus[24] = {h_Proj_cl_dt2->GetMaximum(), 0., 0.3, 40, -6., 0.3, 60., -4., 0.3, 120., -2., 0.3, 180, 0., 0.3, 120., 2., 0.3, 60, 4., 0.3, 40, 6., 0.3};
  f_8Gaus->SetParameters(pars8_Gaus);

  for( int ii = 0; ii < 8; ii++ ){
    if( ii > 0 ){
      // f_8Gaus->SetParLimits(3*ii, 0,  500);
      // f_8Gaus->SetParLimits(3*ii + 1,  2*ii - 8 - 0.5,  2*ii - 8 + 0.5);
      // f_8Gaus->SetParLimits(3*ii + 2,  0., 0.8);
    }

  }
  
  h_Proj_cl_dt2->Fit(f_8Gaus, "MeV", "", -7., 7.);
  TF1 *f_7Gaus = new TF1("f_8Gaus", "[0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Gaus(x, [4], [5]) + [6]*TMath::Gaus(x, [7], [8]) + [9]*TMath::Gaus(x, [10], [11]) + [12]*TMath::Gaus(x, [13], [14]) + [15]*TMath::Gaus(x, [16], [17]) + [18]*TMath::Gaus(x, [19], [20])", -7., 7.);
  
  f_8Gaus->GetParameters(pars8_Gaus);
  TF1 *f_Gaus_arr[8];
  for( int ii = 0; ii < 8; ii++ ){
    f_Gaus_arr[ii] = new TF1(Form("f_Gaus_arr%d", ii), "[0]*TMath::Gaus(x, [1], [2])", -7., 7.);
    f_Gaus_arr[ii]->SetParameters(&pars8_Gaus[3*ii]);
    f_Gaus_arr[ii]->SetLineColor(ii+1);
    f_Gaus_arr[ii]->Draw("Same");
  }
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1.png", data_type.c_str()));
  c1->SetLogy();
  c1->Update();
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1_LogY.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1_LogY.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_cl_dt_fit_withBr1_LogY.png", data_type.c_str()));

  c1->SetLogy(0);
  f_7Gaus->SetParameters(&pars8_Gaus[3]);
  f_7Gaus->SetLineColor(4); 
  h_Proj_cl_dt2->Draw();
  f_8Gaus->Draw("Same");
  f_7Gaus->Draw("Same");
  c1->Print(Form("Figs/%s_Bgr_Estimation_of_cl_dt2.eps", data_type.c_str()));
  c1->Print(Form("Figs/%s_Bgr_Estimation_of_cl_dt2.pdf", data_type.c_str()));
  c1->Print(Form("Figs/%s_Bgr_Estimation_of_cl_dt2.png", data_type.c_str()));

  out_file<<endl;
  out_file<<endl;
  out_file<<" ======= How much bgr is reduced going from 2ns to 1.2 ns ========"<<endl;
  out_file<<" Bgr in the -2 ns to 2 ns region is "<<f_7Gaus->Integral(-2., 2.)<<endl;
  out_file<<" Bgr in the -1.16 ns to 1.16 ns region is "<<f_7Gaus->Integral(-1.16, 1.16)<<endl;
  out_file<<" Reduction is region is "<<f_7Gaus->Integral(-2., 2.)/f_7Gaus->Integral(-1.16, 1.16)<<endl;
  out_file<<" Tot Signal is "<<f_8Gaus->Integral(-1.16, .16)<<endl;
  

  //f_8Gaus->Draw("Same");
  
}

void Draw_2Hists_Ontop(TH1D *h_orig, TH1D *h_tight, TCanvas *c){

  c->Clear();
  TLatex *lat1 = new TLatex();
  lat1->SetNDC();
  lat1->SetTextSize(0.04);
  lat1->SetTextFont(11);
  
  c->cd();
  h_orig->SetFillColor(45);
  h_tight->SetFillColor(95);

  h_orig->SetStats(0);
  h_tight->SetStats(0);  
  
  double Scale = h_orig->GetMaximum()/h_tight->GetMaximum();
 
  h_orig->Draw();
  h_tight->Scale(Scale);
  h_tight->Draw("hist Same");
  lat1->DrawLatex(0.7, 0.8, Form("Scale = %1.2f", Scale));
}

TF1 *SumTF1s(TF1* f_a, TF1* f_b, const char* func_name, double x_min, double x_max, double scale_a, double scale_b){
  f_aa = f_a;
  f_bb = f_b;

  TF1 *f_sum = new TF1(func_name, Sum2Funcs, x_min, x_max, 2);
  f_sum->SetParameter(0, scale_a);
  f_sum->SetParameter(1, scale_b);
  return f_sum;
}

double Sum2Funcs(double *x, double *par){
  return par[0]*f_aa->Eval(x[0]) + par[1]*f_bb->Eval(x[0]);
}
