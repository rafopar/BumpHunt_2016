#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLine.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TGraph.h>
#include "setting_2016_pass1.h"

#include "/Work/Soft/root_funcs/funcs1.C"

void Fit_Calo_dt() {
    //gStyle->SetOptFit(1);

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);
    std::string data_type = "Data";

    TLatex *lat1 = new TLatex();
    lat1->SetNDC();
    lat1->SetTextSize(0.04);

    TLine *line1 = new TLine();
    line1->SetLineColor(1);

    TFile *file_in = new TFile("EventSelection.root");

    TH2D *h_dtCorr_Esum2 = (TH2D*) file_in->Get("h_dtCorr_Esum2");
    h_dtCorr_Esum2->SetTitle("; E_{sum} [GeV]; t_{tpp} - t_{bot} [ns]");

    TH1D *h_Proj_cl_dt2 = (TH1D*) h_dtCorr_Esum2->ProjectionY("h_Proj_cl_dt2", h_dtCorr_Esum2->GetXaxis()->FindBin(Psum_min), h_dtCorr_Esum2->GetXaxis()->FindBin(2.4));
    h_Proj_cl_dt2->Draw();

    const int n_Peak = 15;
    const int n_Gaus = 2 * n_Peak;
    const int npar_14 = 3 * n_Gaus + 2; // 44 = 3*14 + 2
    const int npar = 5 * n_Peak + 3; // 38 = 7*5 + 3
    TF1 *f_MultiGauss_14 = new TF1("f_MultiGauss_14", MultiGauss, -9., 9., npar_14);

    f_MultiGauss_14->SetNpx(4500);

    TF1 *f_MultiPeak_7 = new TF1("f_MultiPeak_7", MultiGauss2, -9., 9., npar);
    f_MultiPeak_7->SetNpx(4500);

    double pars7_Peaks[npar] = {n_Gaus, -1, 0.15, 0.9 * h_Proj_cl_dt2->GetMaximum(), 0., 0.3, 0., 1., 30., -14., 0.3, -14., 1., 35, -12., 0.3, -12., 1.,
        40., -10., 0.3, -10., 1., 45, -8., 0.3, -8., 1., 30, -6., 0.3, -6., 1., 60., -4., 0.3, -4., 1., 160., -2., 0.3, -2., 1., 160., 2., 0.3, 2., 1.,
        60., 4., 0.3, 4., 1., 30., 6., 0.3, 6., 1., 45., 8., 0.3, 8., 1., 40., 10., 0.3, 10., 1., 35., 12., 0.3, 12., 1., 30., 14., 0.3, 14., 1.};

    double pars14_Gaus[npar_14] = {n_Gaus, -1, h_Proj_cl_dt2->GetMaximum(), 0., 0.3, 0.1 * h_Proj_cl_dt2->GetMaximum(), 0., 1., 40, -6., 0.3, 4, -6., 1., 65, -4., 0.3, 6.5, -4., 1.,
        180, -2., 0.3, 18., -2., 1., 120, 2., 0.3, 12., 2., 1., 65, 4., 0.3, 6.5, 4., 1., 40, 6., 0.3, 4, 6., 1.};

    double mean_min[n_Gaus] = {-0.5, -0.5 , -14.5 , -14.5 , -12.5 , -12.5, -10.5 , -10.5 , -8.5 , -8.5 , -6.5 , -6.5 , -4.5 , -4.5 , -2.5 , -2.5 , 1.5 , 1.5 , 3.5 , 3.5 ,
        5.5 , 5.5 , 7.5 , 7.5 , 9.5 , 9.5 , 11.5 , 11.5 , 13.5 , 13.5 };
    double mean_max[n_Gaus] = {0.5 , 0.5 , -13.5 , -13.5 , -11.5 , -11.5 , -9.5 , -9.5 , -7.5 , -7.5 , -5.5 , -5.5 , -3.5 , -3.5 , -1.5 , -1.5 ,
        2.5 , 2.5 , 4.5 , 4.5 , 6.5 , 6.5 , 8.5 , 8.5 , 10.5 , 10.5 , 12.5 , 12.5 , 14.5 , 14.5 };
    double sigm_max[n_Gaus] = {0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1, 0.5,
        1.1, 0.5, 1.1, 0.5, 1.1, 0.5, 1.1};
    double sigm_min[n_Gaus] = {0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4, 0.1, 0.4,
        0.1, 0.4, 0.1, 0.4, 0.1, 0.4};

    f_MultiGauss_14->SetParameters(pars14_Gaus);
    f_MultiGauss_14->FixParameter(0, n_Gaus);
    f_MultiGauss_14->FixParameter(1, -1);


    f_MultiPeak_7->SetParameters(pars7_Peaks);
    f_MultiPeak_7->FixParameter(0, n_Peak);
    f_MultiPeak_7->FixParameter(1, -1);
    //f_MultiPeak_7->SetParLimits(2, 0., 0.2);

    for (int i = 0; i < n_Gaus; i++) {
        f_MultiGauss_14->SetParLimits(3 * i + 2, 0., 30000.);

        f_MultiGauss_14->SetParLimits(3 * i + 3, mean_min[i], mean_max[i]);
        f_MultiGauss_14->SetParLimits(3 * i + 4, sigm_min[i], sigm_max[i]);
    }

    //h_Proj_cl_dt2->Fit(f_MultiGauss_14, "MeV", "", -7., -1.);

    //f_MultiGauss_14->GetParameters(pars14_Gaus);

    //TF1 *f_MultiGauss_14_components[n_Gaus];

    // for( int i = 0; i < n_Gaus; i++ ){

    //   f_MultiGauss_14_components[i] = new TF1(Form("f_MultiGauss_14_%d", i), MultiGauss, -9., 9., npar_14);

    //   f_MultiGauss_14_components[i]->SetParameters(pars14_Gaus);
    //   f_MultiGauss_14_components[i]->SetParameter(1, i);
    //   f_MultiGauss_14_components[i]->SetLineColor(i+1);
    //   f_MultiGauss_14_components[i]->SetNpx(4500);
    //   f_MultiGauss_14_components[i]->Draw("Same");
    // }

    for (int i = 0; i < n_Peak; i++) {
        f_MultiPeak_7->SetParLimits(5 * i + 3, 0., 30000.);
        f_MultiPeak_7->SetParLimits(5 * i + 4, mean_min[2 * i], mean_max[2 * i]);
        f_MultiPeak_7->SetParLimits(5 * i + 6, mean_min[2 * i + 1], mean_max[2 * i + 1]);
        f_MultiPeak_7->SetParLimits(5 * i + 5, sigm_min[2 * i], sigm_max[2 * i]);
        f_MultiPeak_7->SetParLimits(5 * i + 7, sigm_min[2 * i + 1], sigm_max[2 * i + 1]);
    }

    h_Proj_cl_dt2->Fit(f_MultiPeak_7, "MeV", "", -15., 15.);

    f_MultiPeak_7->GetParameters(pars7_Peaks);

    TF1 * f_MultiPeak_7_components[n_Peak];
    TF1 *f_Gaus1 = new TF1("f_Gaus1", "[0]*TMath::Gaus(x, [1], [2])", -15., 15.);
    f_Gaus1->SetNpx(4500);
    f_Gaus1->SetLineColor(1);

    TGraph *gr_components = new TGraph();
    gr_components->SetTitle("; t_{bot} - t_{top} [ns]");


    for (int i = 0; i < n_Peak; i++) {
        f_MultiPeak_7_components[i] = new TF1("f_MultiPeak_7", MultiGauss2, -15., 15., npar);
        f_MultiPeak_7_components[i]->SetParameters(pars7_Peaks);
        f_MultiPeak_7_components[i]->SetParameter(1, i);
        f_MultiPeak_7_components[i]->SetLineColor(i + 1);
        f_MultiPeak_7_components[i]->SetNpx(4500);
        //f_MultiPeak_7_components[i]->Draw("Same");

        // Let's define the mean value as the avarge of means of sharp and wide Gaussian's of the corresponding peak
        double peak_mean = 0.5 * (pars7_Peaks[5 * i + 4] + pars7_Peaks[5 * i + 6]);
        gr_components->SetPoint(i, peak_mean, f_MultiPeak_7_components[i]->Integral(-15., 15.));

        f_Gaus1->SetParameters(pars7_Peaks[5 * i + 3], pars7_Peaks[5 * i + 4], pars7_Peaks[5 * i + 5]);
        f_Gaus1->SetLineColor(i + 1);
        f_Gaus1->SetLineStyle(1);
        f_Gaus1->DrawCopy("Same");
        f_Gaus1->SetParameters(pars7_Peaks[2] * pars7_Peaks[5 * i + 3], pars7_Peaks[5 * i + 6], pars7_Peaks[5 * i + 7]);
        f_Gaus1->SetLineColor(i + 1); 
        f_Gaus1->SetLineStyle(4);
        f_Gaus1->DrawCopy("Same");
    }
    double chi2 = f_MultiPeak_7->GetChisquare();
    double ndf = f_MultiPeak_7->GetNDF();
    double Gauss_ratio = f_MultiPeak_7->GetParameter(2);

    lat1->DrawLatex(0.12, 0.8, Form("#chi^{2}/NDF = %1.2f", chi2 / ndf));
    lat1->DrawLatex(0.12, 0.7, Form("#frac{Gaus(Narrow)}{Gaus(wide)} = %1.2f", 1. / Gauss_ratio));

    c1->Print("Figs/Calo_dt_Fit_lin1.eps");
    c1->Print("Figs/Calo_dt_Fit_lin1.pdf");
    c1->Print("Figs/Calo_dt_Fit_lin1.png");

    c1->SetLogy();
    c1->Update();
    c1->Print("Figs/Calo_dt_Fit_log1.eps");
    c1->Print("Figs/Calo_dt_Fit_log1.pdf");
    c1->Print("Figs/Calo_dt_Fit_log1.png");


    h_Proj_cl_dt2->SetMaximum(1.4 * f_MultiPeak_7_components[7]->GetMaximum(-15., 15.));
    c1->SetLogy(0);
    c1->Update();
    c1->Print("Figs/Calo_dt_Fit_zoom1.eps");
    c1->Print("Figs/Calo_dt_Fit_zoom1.pdf");
    c1->Print("Figs/Calo_dt_Fit_zoom1.png");



    c1->Clear();
    gr_components->SetMarkerColor(2);
    gr_components->SetMarkerSize(2);
    gr_components->SetMarkerStyle(21);


    TF1 *f_lin1 = new TF1("f_lin1", "[0] + [1]*x", -9., 9.);

    double *gr_y_points = gr_components->GetY();
    double *gr_x_points = gr_components->GetX();

    gr_components->SetMaximum(1.1 * gr_y_points[3]);
    gr_components->Draw("AP");
    f_lin1->SetLineColor(4);
    gr_components->Fit(f_lin1, "MeV", "", -7., -3.);
    f_lin1->DrawCopy("Same");
    f_lin1->SetLineColor(96);
    gr_components->Fit(f_lin1, "MeV", "", 0.5, 6.5);
    f_lin1->DrawCopy("Same");
    line1->DrawLine(0., gr_y_points[1], 0., gr_y_points[3]);
    line1->DrawLine(gr_x_points[1], 0.5 * (gr_y_points[1] + gr_y_points[n_Peak - 1]), gr_x_points[n_Peak - 1], 0.5 * (gr_y_points[1] + gr_y_points[n_Peak - 1]));
    line1->DrawLine(gr_x_points[2], 0.5 * (gr_y_points[2] + gr_y_points[n_Peak - 2]), gr_x_points[n_Peak - 2], 0.5 * (gr_y_points[2] + gr_y_points[n_Peak - 2]));

    c1->Print("Figs/cl_dt_fit_summary.eps");
    c1->Print("Figs/cl_dt_fit_summary.pdf");
    c1->Print("Figs/cl_dt_fit_summary.png");


    f_MultiPeak_7->Draw();
    TH1D *h_tmp = (TH1D*) f_MultiPeak_7->GetHistogram();

    TH1D *h_MultiPeak_7 = (TH1D*) h_tmp->Clone("h_MultiPeak_7");

    h_MultiPeak_7->Draw();

    f_MultiPeak_7_components[0]->Draw();
    h_tmp = (TH1D*) f_MultiPeak_7_components[0]->GetHistogram();
    TH1D *h_MultiPeak_core = (TH1D*) h_tmp->Clone("h_MultiPeak_core");
    h_MultiPeak_core->Draw();

    const int n_dt_cut_bins = 200;
    TH1D *h_dt_cut1 = new TH1D("h_dtcut1", "", n_dt_cut_bins, 0., 4);

    for (int i = 0; i < n_dt_cut_bins; i++) {

        double dt_cut = h_dt_cut1->GetBinCenter(i + 1);

        double t_min_bin_tot = h_MultiPeak_7->FindBin(-dt_cut);
        double t_max_bin_tot = h_MultiPeak_7->FindBin(dt_cut);
        double tot_integr = h_MultiPeak_7->Integral(t_min_bin_tot, t_max_bin_tot);

        double t_min_bin_core = h_MultiPeak_core->FindBin(-dt_cut);
        double t_max_bin_core = h_MultiPeak_core->FindBin(dt_cut);
        double sign_integr = h_MultiPeak_core->Integral(t_min_bin_core, t_max_bin_core);

        h_dt_cut1->SetBinContent(i + 1, sign_integr / sqrt(tot_integr));

    }


    h_dt_cut1->Draw();
    double max_val = h_dt_cut1->GetMaximum();
    double dt_cut_val = h_dt_cut1->GetBinCenter(h_dt_cut1->GetMaximumBin());
    h_dt_cut1->SetMinimum(0);
    line1->DrawLine(dt_cut_val, 0, dt_cut_val, 1.02 * max_val);
    lat1->DrawLatex(0.5, 0.65, Form("|#Delta t| = %1.2f ns", dt_cut_val));
    c1->Print("Figs/dt_cur_optimize1.eps");
    c1->Print("Figs/dt_cur_optimize1.pdf");
    c1->Print("Figs/dt_cur_optimize1.png");

    h_dt_cut1->SetMinimum(0.96 * max_val);
    lat1->DrawLatex(0.5, 0.65, Form("|#Delta t| = %1.2f ns", dt_cut_val));
    c1->Print("Figs/dt_cur_optimize1_zoom.eps");
    c1->Print("Figs/dt_cur_optimize1_zoom.pdf");
    c1->Print("Figs/dt_cur_optimize1_zoom.png");

}
