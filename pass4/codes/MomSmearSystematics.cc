/* 
 * File:   MomSmearSystematics.cc
 * Author: rafopar
 *
 * Created on April 22, 2020, 2:05 PM
 */

#include <cstdlib>
#include <list>
#include <vector>

using namespace std;

typedef struct {
    double mean_0; // Mean obtained from data Originally
    double sigm_0; // Sigma obtained from data Originally

    TFile *file_in; // The input file
    std::string histBaseName; // 
    std::string dataSet; // 

    TGraphErrors *gr_mean;
    TGraphErrors *gr_sigm;
    TGraph *gr_chi2;

    double rangeMin; // minimum range for the fit in terms of sigma0
    double rangeMax; // maximum range for the fit in terms of sigma0
    double sigmStep; // Step for the fit in terms of sigma0

    double upLim; // Above this point chi2/NDF grows fast. These values are determined by the user
    double downLim; // Below this point chi2/NDF grows fast. These values are determined by the user

} SmearObj;

void FitPeak(SmearObj);

vector<double> GetSigmas(TH1D *h, double step, double lowlim_min, double lowlim_max, double uplim_min, double uplim_max, double mean_0, double sigm_0);

TH1D* GetSmearCombinatoricHist(vector<double> sigmData, vector<double> sigmMC);


void MomSmearSystematics() {

    TCanvas *c1 = new TCanvas("c1", "", 950, 950);

    TLine *line1 = new TLine();
    line1->SetLineColor(2);

    TFile *file_Data = new TFile("FEE_Studies_Data.root", "Read");
    TFile *file_MC = new TFile("FEE_Studies_Mlr.root", "Read");

    double mean_Data_Top5hits;
    double sigm_Data_Top5hits;
    double scale_Data_Top5hits;
    double mean_Data_Top6hits;
    double sigm_Data_Top6hits;
    double scale_Data_Top6hits;
    double mean_Data_Bot5hits;
    double sigm_Data_Bot5hits;
    double scale_Data_Bot5hits;
    double mean_Data_Bot6hits;
    double sigm_Data_Bot6hits;
    double scale_Data_Bot6hits;

    double mean_MC_Top5hits;
    double sigm_MC_Top5hits;
    double scale_MC_Top5hits;
    double mean_MC_Top6hits;
    double sigm_MC_Top6hits;
    double scale_MC_Top6hits;
    double mean_MC_Bot5hits;
    double sigm_MC_Bot5hits;
    double scale_MC_Bot5hits;
    double mean_MC_Bot6hits;
    double sigm_MC_Bot6hits;
    double scale_MC_Bot6hits;

    double smear_Top5hits;
    double smear_Top6hits;
    double smear_Bot5hits;
    double smear_Bot6hits;

    TFile *file_smearPars = new TFile("MomSmearScale.root", "Read");
    TTree *trSmear = (TTree*) file_smearPars->Get("tr1");

    trSmear->SetBranchAddress("mean_Data_Top5hits", &mean_Data_Top5hits);
    trSmear->SetBranchAddress("sigm_Data_Top5hits", &sigm_Data_Top5hits);
    trSmear->SetBranchAddress("scale_Data_Top5hits", &scale_Data_Top5hits);
    trSmear->SetBranchAddress("mean_Data_Top6hits", &mean_Data_Top6hits);
    trSmear->SetBranchAddress("sigm_Data_Top6hits", &sigm_Data_Top6hits);
    trSmear->SetBranchAddress("scale_Data_Top6hits", &scale_Data_Top6hits);
    trSmear->SetBranchAddress("mean_Data_Bot5hits", &mean_Data_Bot5hits);
    trSmear->SetBranchAddress("sigm_Data_Bot5hits", &sigm_Data_Bot5hits);
    trSmear->SetBranchAddress("scale_Data_Bot5hits", &scale_Data_Bot5hits);
    trSmear->SetBranchAddress("mean_Data_Bot6hits", &mean_Data_Bot6hits);
    trSmear->SetBranchAddress("sigm_Data_Bot6hits", &sigm_Data_Bot6hits);
    trSmear->SetBranchAddress("scale_Data_Bot6hits", &scale_Data_Bot6hits);

    trSmear->SetBranchAddress("mean_MC_Top5hits", &mean_MC_Top5hits);
    trSmear->SetBranchAddress("sigm_MC_Top5hits", &sigm_MC_Top5hits);
    trSmear->SetBranchAddress("scale_MC_Top5hits", &scale_MC_Top5hits);
    trSmear->SetBranchAddress("mean_MC_Top6hits", &mean_MC_Top6hits);
    trSmear->SetBranchAddress("sigm_MC_Top6hits", &sigm_MC_Top6hits);
    trSmear->SetBranchAddress("scale_MC_Top6hits", &scale_MC_Top6hits);
    trSmear->SetBranchAddress("mean_MC_Bot5hits", &mean_MC_Bot5hits);
    trSmear->SetBranchAddress("sigm_MC_Bot5hits", &sigm_MC_Bot5hits);
    trSmear->SetBranchAddress("scale_MC_Bot5hits", &scale_MC_Bot5hits);
    trSmear->SetBranchAddress("mean_MC_Bot6hits", &mean_MC_Bot6hits);
    trSmear->SetBranchAddress("sigm_MC_Bot6hits", &sigm_MC_Bot6hits);
    trSmear->SetBranchAddress("scale_MC_Bot6hits", &scale_MC_Bot6hits);

    trSmear->SetBranchAddress("smear_Top5hits", &smear_Top5hits);
    trSmear->SetBranchAddress("smear_Top6hits", &smear_Top6hits);
    trSmear->SetBranchAddress("smear_Bot5hits", &smear_Bot5hits);
    trSmear->SetBranchAddress("smear_Bot6hits", &smear_Bot6hits);

    trSmear->GetEntry(0);
    file_smearPars->Close();

    double rangeMax = 2.1;
    double rangeMin = 0.5;
    double sigmStep = 0.06;

    const map<std::string, double> upLims = {
        {"Top5hitsData", 1.6},
        {"Top6hitsData", 1.55},
        {"Bot5hitsData", 1.4},
        {"Bot6hitsData", 1.7},
        {"Top5hitsMC", 2.7},
        {"Top6hitsMC", 2.7},
        {"Bot5hitsMC", 2.7},
        {"Bot6hitsMC", 2.7}
    };
    const map<std::string, double> downLims = {
        {"Top5hitsData", 1.7},
        {"Top6hitsData", 1.45},
        {"Bot5hitsData", 1.45},
        {"Bot6hitsData", 1.55},
        {"Top5hitsMC", 1.5},
        {"Top6hitsMC", 1.6},
        {"Bot5hitsMC", 1.9},
        {"Bot6hitsMC", 1.5}
    };


    TH1D *h_Pem2_Top5hits_Data = (TH1D*) file_Data->Get("h_Pem2_Top5hits");
    h_Pem2_Top5hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Top5hits_Data->SetAxisRange(1.7, 3.);
    TH1D *h_Pem2_Top6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_Data->SetAxisRange(1.7, 3.);
    
    TH1D *h_Pem2_Bot5hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_Data->SetAxisRange(1.7, 3.);
    TH1D *h_Pem2_Bot6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_Data->SetAxisRange(1.7, 3.);
    
    TH1D *h_Pem2_Top5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top5hits");
    h_Pem2_Top5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top5hits_MC->SetAxisRange(1.7, 3.);
    TH1D *h_Pem2_Top6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_MC->SetAxisRange(1.7, 3.);
    
    TH1D *h_Pem2_Bot5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_MC->SetAxisRange(1.7, 3.);
    TH1D *h_Pem2_Bot6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_MC->SetAxisRange(1.7, 3.);
    
    TGraphErrors *gr_mean_Top5hits_Data = new TGraphErrors();
    TGraphErrors *gr_sigm_Top5hits_Data = new TGraphErrors();
    TGraphErrors *gr_chi2_Top5hits_Data = new TGraphErrors();

    /*
    SmearObj sm_Top5hits_Data{mean_Data_Top5hits, sigm_Data_Top5hits, file_Data, "Top5hits", "Data",
        gr_mean_Top5hits_Data, gr_sigm_Top5hits_Data, gr_chi2_Top5hits_Data, rangeMin, rangeMax, sigmStep,
        upLims.at("Top5hitsData"), downLims.at("Top5hitsData")};

    FitPeak(sm_Top5hits_Data);

    c1->SetTopMargin(0.05);
    c1->SetRightMargin(0.03);
    c1->Divide(1, 2, 0., 2);
    c1->cd(1);
    gr_chi2_Top5hits_Data->Draw("AP");
    c1->cd(2);
    gr_sigm_Top5hits_Data->Draw("AP");
    line1->DrawLine(0.4, sigm_Data_Top5hits, 2, sigm_Data_Top5hits);
    c1->Print("Figs/MomSmearSys_Top5HitsData.eps");
    c1->Print("Figs/MomSmearSys_Top5HitsData.pdf");
    c1->Print("Figs/MomSmearSys_Top5HitsData.png");


    TH1D *h_Pem2_Top6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_Data->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Top6hits_Data = new TGraphErrors();
    TGraphErrors *gr_sigm_Top6hits_Data = new TGraphErrors();
    TGraphErrors *gr_chi2_Top6hits_Data = new TGraphErrors();

    SmearObj sm_Top6hits_Data{mean_Data_Top6hits, sigm_Data_Top6hits, file_Data, "Top6hits", "Data",
        gr_mean_Top6hits_Data, gr_sigm_Top6hits_Data, gr_chi2_Top6hits_Data, rangeMin, rangeMax, sigmStep,
        upLims.at("Top6hitsData"), downLims.at("Top6hitsData")};

    FitPeak(sm_Top6hits_Data);

    c1->cd(1)->Clear();
    gr_chi2_Top6hits_Data->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Top6hits_Data->Draw("AP");
    line1->DrawLine(0.4, sigm_Data_Top6hits, 2, sigm_Data_Top6hits);
    c1->Print("Figs/MomSmearSys_Top6HitsData.eps");
    c1->Print("Figs/MomSmearSys_Top6HitsData.pdf");
    c1->Print("Figs/MomSmearSys_Top6HitsData.png");


    TH1D *h_Pem2_Bot5hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_Data->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Bot5hits_Data = new TGraphErrors();
    TGraphErrors *gr_sigm_Bot5hits_Data = new TGraphErrors();
    TGraphErrors *gr_chi2_Bot5hits_Data = new TGraphErrors();

    SmearObj sm_Bot5hits_Data{mean_Data_Bot5hits, sigm_Data_Bot5hits, file_Data, "Bot5hits", "Data",
        gr_mean_Bot5hits_Data, gr_sigm_Bot5hits_Data, gr_chi2_Bot5hits_Data, rangeMin, rangeMax, sigmStep,
        upLims.at("Bot5hitsData"), downLims.at("Bot5hitsData")};

    FitPeak(sm_Bot5hits_Data);

    c1->cd(1)->Clear();
    gr_chi2_Bot5hits_Data->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Bot5hits_Data->Draw("AP");
    line1->DrawLine(0.4, sigm_Data_Bot5hits, 2, sigm_Data_Bot5hits);
    c1->Print("Figs/MomSmearSys_Bot5HitsData.eps");
    c1->Print("Figs/MomSmearSys_Bot5HitsData.pdf");
    c1->Print("Figs/MomSmearSys_Bot5HitsData.png");


    TH1D *h_Pem2_Bot6hits_Data = (TH1D*) file_Data->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_Data->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_Data->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Bot6hits_Data = new TGraphErrors();
    TGraphErrors *gr_sigm_Bot6hits_Data = new TGraphErrors();
    TGraphErrors *gr_chi2_Bot6hits_Data = new TGraphErrors();

    SmearObj sm_Bot6hits_Data{mean_Data_Bot6hits, sigm_Data_Bot6hits, file_Data, "Bot6hits", "Data",
        gr_mean_Bot6hits_Data, gr_sigm_Bot6hits_Data, gr_chi2_Bot6hits_Data, rangeMin, rangeMax, sigmStep,
        upLims.at("Bot6hitsData"), downLims.at("Bot6hitsData")};

    FitPeak(sm_Bot6hits_Data);

    c1->cd(1)->Clear();
    gr_chi2_Bot6hits_Data->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Bot6hits_Data->Draw("AP");
    line1->DrawLine(0.4, sigm_Data_Bot6hits, 2, sigm_Data_Bot6hits);
    c1->Print("Figs/MomSmearSys_Bot6HitsData.eps");
    c1->Print("Figs/MomSmearSys_Bot6HitsData.pdf");
    c1->Print("Figs/MomSmearSys_Bot6HitsData.png");




    TH1D *h_Pem2_Top5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top5hits");
    h_Pem2_Top5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top5hits_MC->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Top5hits_MC = new TGraphErrors();
    TGraphErrors *gr_sigm_Top5hits_MC = new TGraphErrors();
    TGraphErrors *gr_chi2_Top5hits_MC = new TGraphErrors();

    SmearObj sm_Top5hits_MC{mean_MC_Top5hits, sigm_MC_Top5hits, file_MC, "Top5hits", "MC",
        gr_mean_Top5hits_MC, gr_sigm_Top5hits_MC, gr_chi2_Top5hits_MC, rangeMin, rangeMax, sigmStep,
        upLims.at("Top5hitsMC"), downLims.at("Top5hitsMC")};

    FitPeak(sm_Top5hits_MC);

    c1->cd(1)->Clear();
    gr_chi2_Top5hits_MC->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Top5hits_MC->Draw("AP");
    line1->DrawLine(0.4, sigm_MC_Top5hits, 2, sigm_MC_Top5hits);
    c1->Print("Figs/MomSmearSys_Top5HitsMC.eps");
    c1->Print("Figs/MomSmearSys_Top5HitsMC.pdf");
    c1->Print("Figs/MomSmearSys_Top5HitsMC.png");


    TH1D *h_Pem2_Top6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Top6hits");
    h_Pem2_Top6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Top6hits_MC->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Top6hits_MC = new TGraphErrors();
    TGraphErrors *gr_sigm_Top6hits_MC = new TGraphErrors();
    TGraphErrors *gr_chi2_Top6hits_MC = new TGraphErrors();

    SmearObj sm_Top6hits_MC{mean_MC_Top6hits, sigm_MC_Top6hits, file_MC, "Top6hits", "MC",
        gr_mean_Top6hits_MC, gr_sigm_Top6hits_MC, gr_chi2_Top6hits_MC, rangeMin, rangeMax, sigmStep,
        upLims.at("Top6hitsMC"), downLims.at("Top6hitsMC")};

    FitPeak(sm_Top6hits_MC);

    c1->cd(1)->Clear();
    gr_chi2_Top6hits_MC->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Top6hits_MC->Draw("AP");
    line1->DrawLine(0.4, sigm_MC_Top6hits, 2, sigm_MC_Top6hits);
    c1->Print("Figs/MomSmearSys_Top6HitsMC.eps");
    c1->Print("Figs/MomSmearSys_Top6HitsMC.pdf");
    c1->Print("Figs/MomSmearSys_Top6HitsMC.png");


    TH1D *h_Pem2_Bot5hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot5hits");
    h_Pem2_Bot5hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot5hits_MC->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Bot5hits_MC = new TGraphErrors();
    TGraphErrors *gr_sigm_Bot5hits_MC = new TGraphErrors();
    TGraphErrors *gr_chi2_Bot5hits_MC = new TGraphErrors();

    SmearObj sm_Bot5hits_MC{mean_MC_Bot5hits, sigm_MC_Bot5hits, file_MC, "Bot5hits", "MC",
        gr_mean_Bot5hits_MC, gr_sigm_Bot5hits_MC, gr_chi2_Bot5hits_MC, rangeMin, rangeMax, sigmStep,
        upLims.at("Bot5hitsMC"), downLims.at("Bot5hitsMC")};

    FitPeak(sm_Bot5hits_MC);

    c1->cd(1)->Clear();
    gr_chi2_Bot5hits_MC->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Bot5hits_MC->Draw("AP");
    line1->DrawLine(0.4, sigm_MC_Bot5hits, 2, sigm_MC_Bot5hits);
    c1->Print("Figs/MomSmearSys_Bot5HitsMC.eps");
    c1->Print("Figs/MomSmearSys_Bot5HitsMC.pdf");
    c1->Print("Figs/MomSmearSys_Bot5HitsMC.png");


    TH1D *h_Pem2_Bot6hits_MC = (TH1D*) file_MC->Get("h_Pem2_Bot6hits");
    h_Pem2_Bot6hits_MC->SetTitle("; P [GeV]");
    h_Pem2_Bot6hits_MC->SetAxisRange(1.7, 3.);
    TGraphErrors *gr_mean_Bot6hits_MC = new TGraphErrors();
    TGraphErrors *gr_sigm_Bot6hits_MC = new TGraphErrors();
    TGraphErrors *gr_chi2_Bot6hits_MC = new TGraphErrors();

    SmearObj sm_Bot6hits_MC{mean_MC_Bot6hits, sigm_MC_Bot6hits, file_MC, "Bot6hits", "MC",
        gr_mean_Bot6hits_MC, gr_sigm_Bot6hits_MC, gr_chi2_Bot6hits_MC, rangeMin, rangeMax, sigmStep,
        upLims.at("Bot6hitsMC"), downLims.at("Bot6hitsMC")};

    FitPeak(sm_Bot6hits_MC);

    c1->cd(1)->Clear();
    gr_chi2_Bot6hits_MC->Draw("AP");
    c1->cd(2)->Clear();
    gr_sigm_Bot6hits_MC->Draw("AP");
    line1->DrawLine(0.4, sigm_MC_Bot6hits, 2, sigm_MC_Bot6hits);
    c1->Print("Figs/MomSmearSys_Bot6HitsMC.eps");
    c1->Print("Figs/MomSmearSys_Bot6HitsMC.pdf");
    c1->Print("Figs/MomSmearSys_Bot6HitsMC.png");

*/

    // ======================== Getting Sigmas ========================
    
    vector<double> sigmas_top5HitsData = GetSigmas(h_Pem2_Top5hits_Data, sigmStep, downLims.at("Top5hitsData"), 0.85, 0.85, upLims.at("Top5hitsData"), 
            mean_Data_Top5hits, sigm_Data_Top5hits);

    vector<double> sigmas_top5HitsMC = GetSigmas(h_Pem2_Top5hits_MC, sigmStep, downLims.at("Top5hitsMC"), 0.85, 0.85, upLims.at("Top5hitsMC"), 
            mean_MC_Top5hits, sigm_MC_Top5hits);
    
    cout<<"Size of sigmas_top5HitsMC is "<<sigmas_top5HitsMC.size()<<endl;

    TH1D *h_Smear_Top5HitsData = GetSmearCombinatoricHist(sigmas_top5HitsData, sigmas_top5HitsMC);
    h_Smear_Top5HitsData->SetName("h_Smear_Top5HitsData");
    h_Smear_Top5HitsData->Draw();
    line1->DrawLine(smear_Top5hits, 0., smear_Top5hits, h_Smear_Top5HitsData->GetMaximum());
    c1->Print("Figs/SmeaySystematics_Top5Hits.eps");
    c1->Print("Figs/SmeaySystematics_Top5Hits.pdf");
    c1->Print("Figs/SmeaySystematics_Top5Hits.png");
    
    vector<double> sigmas_top6HitsData = GetSigmas(h_Pem2_Top6hits_Data, sigmStep, downLims.at("Top6hitsData"), 0.85, 0.85, upLims.at("Top6hitsData"), 
            mean_Data_Top6hits, sigm_Data_Top6hits);

    vector<double> sigmas_top6HitsMC = GetSigmas(h_Pem2_Top6hits_MC, sigmStep, downLims.at("Top6hitsMC"), 0.85, 0.85, upLims.at("Top6hitsMC"), 
            mean_MC_Top6hits, sigm_MC_Top6hits);
    
    cout<<"Size of sigmas_top6HitsMC is "<<sigmas_top6HitsMC.size()<<endl;

    TH1D *h_Smear_Top6HitsData = GetSmearCombinatoricHist(sigmas_top6HitsData, sigmas_top6HitsMC);
    h_Smear_Top6HitsData->SetName("h_Smear_Top6HitsData");
    h_Smear_Top6HitsData->Draw();
    line1->DrawLine(smear_Top6hits, 0., smear_Top6hits, h_Smear_Top6HitsData->GetMaximum());
    c1->Print("Figs/SmeaySystematics_Top6Hits.eps");
    c1->Print("Figs/SmeaySystematics_Top6Hits.pdf");
    c1->Print("Figs/SmeaySystematics_Top6Hits.png");
    
    
    
    vector<double> sigmas_bot5HitsData = GetSigmas(h_Pem2_Bot5hits_Data, sigmStep, downLims.at("Bot5hitsData"), 0.85, 0.85, upLims.at("Bot5hitsData"), 
            mean_Data_Bot5hits, sigm_Data_Bot5hits);

    vector<double> sigmas_bot5HitsMC = GetSigmas(h_Pem2_Bot5hits_MC, sigmStep, downLims.at("Bot5hitsMC"), 0.85, 0.85, upLims.at("Bot5hitsMC"), 
            mean_MC_Bot5hits, sigm_MC_Bot5hits);
    
    cout<<"Size of sigmas_bot5HitsMC is "<<sigmas_bot5HitsMC.size()<<endl;

    TH1D *h_Smear_Bot5HitsData = GetSmearCombinatoricHist(sigmas_bot5HitsData, sigmas_bot5HitsMC);
    h_Smear_Bot5HitsData->SetName("h_Smear_Bot5HitsData");
    h_Smear_Bot5HitsData->Draw();
    line1->DrawLine(smear_Bot5hits, 0., smear_Bot5hits, h_Smear_Bot5HitsData->GetMaximum());
    c1->Print("Figs/SmeaySystematics_Bot5Hits.eps");
    c1->Print("Figs/SmeaySystematics_Bot5Hits.pdf");
    c1->Print("Figs/SmeaySystematics_Bot5Hits.png");
    
    vector<double> sigmas_bot6HitsData = GetSigmas(h_Pem2_Bot6hits_Data, sigmStep, downLims.at("Bot6hitsData"), 0.85, 0.85, upLims.at("Bot6hitsData"), 
            mean_Data_Bot6hits, sigm_Data_Bot6hits);

    vector<double> sigmas_bot6HitsMC = GetSigmas(h_Pem2_Bot6hits_MC, sigmStep, downLims.at("Bot6hitsMC"), 0.85, 0.85, upLims.at("Bot6hitsMC"), 
            mean_MC_Bot6hits, sigm_MC_Bot6hits);
    
    cout<<"Size of sigmas_bot6HitsMC is "<<sigmas_bot6HitsMC.size()<<endl;

    TH1D *h_Smear_Bot6HitsData = GetSmearCombinatoricHist(sigmas_bot6HitsData, sigmas_bot6HitsMC);
    h_Smear_Bot6HitsData->SetName("h_Smear_Bot6HitsData");
    h_Smear_Bot6HitsData->Draw();
    line1->DrawLine(smear_Bot6hits, 0., smear_Bot6hits, h_Smear_Bot6HitsData->GetMaximum());
    c1->Print("Figs/SmeaySystematics_Bot6Hits.eps");
    c1->Print("Figs/SmeaySystematics_Bot6Hits.pdf");
    c1->Print("Figs/SmeaySystematics_Bot6Hits.png");   
    
    
    return 0;
}

void FitPeak(SmearObj sm) {

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 1.5, 3.);
    f_Gaus->SetNpx(4500);

    TH1D *h_Peak = (TH1D*) sm.file_in->Get(Form("h_Pem2_%s", sm.histBaseName.c_str()));
    h_Peak->SetAxisRange(1.7, 3.);

    double cursigmRange = sm.rangeMin;

    TCanvas *c0 = new TCanvas("c0", "", 950, 950);
    c0->Print(Form("Figs/SmearFits_%s_%s.pdf[", sm.histBaseName.c_str(), sm.dataSet.c_str()));

    int index = 0;
    while (cursigmRange <= sm.rangeMax) {

        f_Gaus->SetParameters(h_Peak->GetMaximum(), sm.mean_0, sm.sigm_0);

        //h_Peak->Fit(f_Gaus, "MeV", "", sm.mean_0 - 0.75*cursigmRange * sm.sigm_0, sm.mean_0 + 1.25*cursigmRange * sm.sigm_0);
        //h_Peak->Fit(f_Gaus, "MeV", "", 2.15, sm.mean_0 + cursigmRange * sm.sigm_0);
        h_Peak->Fit(f_Gaus, "MeV", "", sm.mean_0 - cursigmRange * sm.sigm_0, 2.5);
        //h_Peak->Fit(f_Gaus, "MeV", "", sm.mean_0 - sm.downLim*sm.sigm_0, sm.mean_0 + cursigmRange * sm.sigm_0 );
        //h_Peak->Fit(f_Gaus, "MeV", "", sm.mean_0 - cursigmRange * sm.sigm_0, sm.mean_0 + sm.upLim*sm.sigm_0 );

        double chi2 = f_Gaus->GetNDF() >= 1 ? f_Gaus->GetChisquare() / f_Gaus->GetNDF() : 0;
        double mean = f_Gaus->GetParameter(1);
        double meanErr = f_Gaus->GetParError(1);
        double sigm = f_Gaus->GetParameter(2);
        double sigmErr = f_Gaus->GetParError(2);

        sm.gr_mean->SetPoint(index, cursigmRange, mean);
        sm.gr_mean->SetPointError(index, 0., meanErr);
        sm.gr_sigm->SetPoint(index, cursigmRange, sigm);
        sm.gr_sigm->SetPointError(index, 0., sigmErr);
        sm.gr_chi2->SetPoint(index, cursigmRange, chi2);

        c0->Print(Form("Figs/SmearFits_%s_%s.pdf", sm.histBaseName.c_str(), sm.dataSet.c_str()));
        index = index + 1;
        cursigmRange = cursigmRange + sm.sigmStep;
    }
    c0->Print(Form("Figs/SmearFits_%s_%s.pdf]", sm.histBaseName.c_str(), sm.dataSet.c_str()));

    sm.gr_mean->SetMarkerColor(3);
    sm.gr_sigm->SetMarkerColor(2);
    sm.gr_sigm->SetMarkerStyle(20);
    sm.gr_chi2->SetMarkerColor(4);
    sm.gr_chi2->SetMarkerStyle(21);

    delete c0;
}

vector<double> GetSigmas(TH1D *h, double step, double lowlim_min, double lowlim_max, double uplim_min, double uplim_max, double mean_0, double sigm_0) {

    TF1 *f_Gaus = new TF1("f_Gaus", "[0]*TMath::Gaus(x, [1], [2])", 1.2, 3.);
    f_Gaus->SetNpx(4500);
    
    vector<double> sigmas;

    double cur_lowlim = lowlim_min;

    while (cur_lowlim >= lowlim_max) {

        double cur_uplim = uplim_min;
        while (cur_uplim <= uplim_max) {

            f_Gaus->SetParameters(h->GetMaximum(), mean_0, sigm_0);
            
            double ll = mean_0 - cur_lowlim*sigm_0;
            double rr = mean_0 + cur_uplim*sigm_0;
            
            h->Fit(f_Gaus, "M", "", ll, rr);
            
            cout<<"ll = "<<ll <<"    rr = "<<rr<<endl;
            
            double sigm = f_Gaus->GetParameter(2);
            
            sigmas.push_back(sigm/mean_0);
            
            
            cur_uplim = cur_uplim + step;
        }

        cur_lowlim = cur_lowlim - step;
    }

    return sigmas;
}

TH1D* GetSmearCombinatoricHist(vector<double> sigmData, vector<double> sigmMC){

    TH1D *h_Smear = new TH1D("h_Smear", "", 400, 0.02, 0.08);
    
    for( auto curSigmData : sigmData ){
        for( auto curSigmMC : sigmMC ){
            double curSmearSigm = sqrt( curSigmData*curSigmData - curSigmMC*curSigmMC );
            
            h_Smear->Fill(curSmearSigm);
        }
    }
    
    
    return h_Smear;
}