/* 
 * File:   InjectSignals.cc
 * Author: rafopar
 *
 * Created on May 21, 2020, 4:42 PM
 */

#include <cstdlib>

#include <fstream>
#include <iostream>

#include <TF1.h>
#include <TH1D.h>
#include <TFile.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TRandom2.h>

using namespace std;

typedef struct {
    int caseNo;
    double signalStrength; // wrt upper limit, i.e. N_Sig/N_Upper
    double mass;
    std::string MCFileName;
} SignalCase;


TH1D* FitApMass(std::string , TF1*);

/*
 * 
 */
int main(int argc, char** argv) {


    /*
     The Mass Parametrization
     */
    TF1 f_MassRes("f_MassRes", "pol4", 0., 0.3);
    f_MassRes.SetNpx(4500);
    f_MassRes.SetParameters(0.000379509, 0.0416842, -0.271364, 3.49537, -11.1153);


    TFile file_FullStat("EventSelection_pass4Full.root", "Read");

    TH1D *h_FullStatOrig = (TH1D*) file_FullStat.Get("h_Minv_General_Final_1");

    TFile file_UpLim("limitPlots_unblinded.root");
    TGraph *gr_limitN_g = (TGraph*) file_UpLim.Get("limitN_g");
    double *masses = gr_limitN_g->GetX();
    double *Limits = gr_limitN_g->GetY();
    int n_masses = gr_limitN_g->GetN();

    vector<double> v_masses(masses, masses + n_masses);
    vector<double> v_Limits(Limits, Limits + n_masses);

    TRandom2 *rand2 = new TRandom2();

    const int nCases = 7;

    SignalCase cases[nCases];

    cases[0] = {0, 1.5, 0.05, "EventSelection_Ap_50_MeV.root"};
    cases[1] = {1, 0.8, 0.1, "EventSelection_Ap_100_MeV.root"};
    cases[2] = {2, 1.2, 0.155, "EventSelection_Ap_155_MeV.root"};
    cases[3] = {3, 1.5, 0.09, "EventSelection_Ap_90_MeV.root"};
    cases[4] = {4, 0.5, 0.085, "EventSelection_Ap_85_MeV.root"};
    cases[5] = {5, 1.05, 0.065, "EventSelection_Ap_65_MeV.root"};
    cases[6] = {6, 0., 0.075, "EventSelection_Ap_75_MeV.root"};

    cout << cases[0].mass << endl;

    TFile *file_out_[nCases];
    TH1D * h_Signal_[nCases];
    
    auto f_CB = new TF1("f_CB", "crystalball", 0.03 , 0.22);
    f_CB->SetNpx(4500);

    ofstream out_dat("InjectedSignalInfo.dat");
    
    for (int icase = 0; icase < nCases; icase++) {

        double massRes = f_MassRes.Eval(cases[icase].mass);

        std::vector<double>::iterator low;
        low = std::lower_bound(v_masses.begin(), v_masses.end(), 1000. * cases[icase].mass);

        int mass_index = low - v_masses.begin();

        double UpLim = v_Limits.at(mass_index);

        int nGen = int(UpLim * cases[icase].signalStrength);
        
        TH1D *h_AP_Fit = (TH1D*) FitApMass( (cases[icase].MCFileName).c_str(), f_CB );
        h_AP_Fit->SetName(Form("Ap_Fit_%d", cases[icase].caseNo));

        out_dat << " ============================================== " << endl;
        out_dat << endl;
        out_dat << endl;
        out_dat << "   Generating Case # " << cases[icase].caseNo << endl;
        out_dat << "   mass is " << 1000. * cases[icase].mass << " MeV" << endl;
        //out_dat << "   Mass Resolution is " << 1000. * massRes << " MeV" << endl;
        out_dat << "   Upper Limit is " << UpLim << endl;
        out_dat << "   Signal Strength =  " << cases[icase].signalStrength << endl;
        out_dat << "   Injected Signal =  " << nGen << endl;
        out_dat<<" CB Parameters ";
        for( int ip = 0; ip < 5; ip++ ){
           out_dat<<f_CB->GetParameter(ip) <<"  ";
        }
        out_dat<<endl;

        file_out_[icase] = new TFile(Form("InjectedSignals_pass4Full_%d.root", icase), "Recreate");
        h_Signal_[icase] = (TH1D*) h_FullStatOrig->Clone(Form("h_Signal_%d", icase));
        h_Signal_[icase]->SetName(Form("h_Signal_%d", icase));
        

        for (int ii = 0; ii < nGen; ii++) {
            //h_Signal_[icase]->Fill(rand2->Gaus(cases[icase].mass, massRes));
            h_Signal_[icase]->Fill(f_CB->GetRandom() );
        }


        h_Signal_[icase]->SetEntries(0);
        h_Signal_[icase]->Write();
//        h_FullStatOrig->Write();
//        h_AP_Fit->Write();
        file_out_[icase]->Close();
        
    }

    return 0;
}

TH1D *FitApMass(std::string fname, TF1* f){
    TFile *file_in = new TFile(fname.c_str() , "Read");
    
    TH1D *h = (TH1D*)file_in->Get("h_MinvScSm_General_Final_1");
    double rms = h->GetRMS();
    double max = h->GetMaximum();
    double mean = h->GetBinCenter( h->GetMaximumBin());
    
    f->SetParameters(max, mean, rms, 1.6, 30);
    
    h->Fit(f, "MeV", "",  mean - 5*rms, mean + 5*rms);

    return h;
}