/* 
 * File:   EventSelection.cc
 * Author: rafopar
 *
 * Created on September 18, 2019, 9:27 AM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include "setting_2016_pass1.h"
#include "InitSettings.C"

#include <iostream>

#include <cstdlib>

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    
    InitVariables();
    
    TFile *file_in = new TFile("../Data/hps_008099.All_dst_4.2.root");
    //TFile *file_in = new TFile("../Data/hps_008099.11_dst_4.2.root");
    //TFile *file_in = new TFile("../../pass1/Data/hps_007800.190_dst_3.11.1.root");

    TFile *file_ECalTimeCorrections = new TFile("ECalTimeCorrections.root", "Read");

    TH2D *h_time_Corrections = (TH2D*) file_ECalTimeCorrections->Get("h_cl_dtMeans1");


    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");
    //TChain *tr1 =  new TChain("HPS_Event");
    //tr1->Add("../Data/hps_008099.*_dst_4.2.root");

    TFile *file_out = new TFile("EventSelection.root", "Recreate");

    TH1D *h_n_c1l = new TH1D("h_n_cl1", "", 15, -0.5, 14.5);
    TH1D *h_clE1 = new TH1D("h_clE1", "", 200, 0., 1.2 * Eb);
    TH2D *h_cl_E_t1 = new TH2D("h_cl_E_t1", "", 200, 0., 1.2 * Eb, 200, 0., 180.);
    TH2D *h_cl_E_tTop1 = new TH2D("h_cl_E_tTop1", "", 200, 0., 1.2 * Eb, 200, 20., 80.);
    TH2D *h_cl_E_tBot1 = new TH2D("h_cl_E_tBot1", "", 200, 0., 1.2 * Eb, 200, 20., 80.);
    TH2D *h_dt_Esum1 = new TH2D("h_dt_Esum1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dt_Esum2 = new TH2D("h_dt_Esum2", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dtCorr_Esum1 = new TH2D("h_dtCorr_Esum1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dtCorr_Esum2 = new TH2D("h_dtCorr_Esum2", "", 200, 0., 1.2 * Eb, 200, -15., 15.);

    TH2D *h_cl_yxc1 = new TH2D("h_cl_yxc1", "", 200, -300., 370, 200, -90., 90.);

    TH1D *h_tr_P_pos1 = new TH1D("h_tr_P_pos1", "", 200, 0., 1.2 * Eb);
    TH1D *h_tr_P_neg1 = new TH1D("h_tr_P_neg1", "", 200, 0., 1.2 * Eb);

    TH1D *h_n_tr1 = new TH1D("h_n_tr1", "", 21, -0.5, 20.5);

    TH2D *h_n_trk_crash1 = new TH2D("h_n_trk_crash1", "", 21, -0.5, 20.5, 15, -7.5, 7.5);

    TH2D *h_cl_dtMeans1 = new TH2D("h_cl_dtMeans1", "", 47, -23.5, 23.5, 11, -5.5, 5.5);

    HpsEvent *ev = new HpsEvent();
    //tr1->SetBranchAddress("HPS_Event", ev);

    TBranch *b_hps_event = tr1->GetBranch("Event");
    b_hps_event->SetAddress(&ev);

    SvtTrack *SVTtrack = 0;
    GblTrack *trk = 0;
    EcalCluster* cl = 0;
    EcalCluster* clTop = 0;
    EcalCluster* clBot = 0;
    EcalHit* ec_hit = 0;
    SvtHit *svt_hit = 0;
    HpsParticle* part = 0;

    const int n_max_cl = 100;
    const int n_max_top_cl = 100;
    const int n_max_bot_cl = 100;
    const int n_max_trk = 100;
    const int n_max_top_trk = 100;
    const int n_max_bot_trk = 100;
    const int n_max_pos_trk = 100;
    const int n_max_neg_trk = 100;
    const int n_max_part = 100;

    int ind_top_cl[n_max_cl];
    int ind_bot_cl[n_max_cl];

    int ind_top_fs_part[n_max_part];
    int ind_bot_fs_part[n_max_part];
    int ind_pos_fs_part[n_max_part];
    int ind_neg_fs_part[n_max_part];
    int ind_neut_fs_part[n_max_part];

    int nev = tr1->GetEntries();

    cout << "Number of events is " << nev << endl;

    //nev = 500000;
    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);
        //tr1->GetEvent(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }

        int n_cl = ev->getNumberOfEcalClusters();


        if (!ev->isPair1Trigger()) {
            continue;
        }
        h_n_c1l->Fill(n_cl);

        int n_top_cl = 0;
        int n_bot_cl = 0;
        for (int i_cl = 0; i_cl < n_cl; i_cl++) {
            cl = ev->getEcalCluster(i_cl);

            double cl_E = cl->getEnergy();
            double cl_t = cl->getClusterTime();
            vector<double> cl_pos = cl->getPosition();
            h_clE1->Fill(cl_E);
            h_cl_E_t1->Fill(cl_E, cl_t);

            if (cl_pos.at(1) > 0) {
                h_cl_E_tTop1->Fill(cl_E, cl_t);
                cl_t_max = 70.;
                cl_t_min = 30.;
//                cl_t_max = f_clTTopUpLim->Eval(cl_E);
//                cl_t_min = f_clTTopLowLim->Eval(cl_E);
            } else {
                h_cl_E_tBot1->Fill(cl_E, cl_t);
                cl_t_max = f_clTBotUpLim->Eval(cl_E);
                cl_t_min = f_clTBotLowLim->Eval(cl_E);
            }
            

            if (!(cl_t > cl_t_min && cl_t < cl_t_max)) {
                continue;
            }
            
            

            h_cl_yxc1->Fill(cl_pos.at(0), cl_pos.at(1));

            if (cl_pos.at(1) > 0) {
                ind_top_cl[n_top_cl] = i_cl;
                n_top_cl = n_top_cl + 1;
            } else {
                ind_bot_cl[n_bot_cl] = i_cl;
                n_bot_cl = n_bot_cl + 1;
            }
        }


        //ev->getNumberOfParticles(HpsParticle::)

        int n_tr = ev->getNumberOfGblTracks();
        h_n_tr1->Fill(n_tr);
        //cout<<" =============== n_tr = "<<n_tr<<" ================"<<endl;
        if (n_tr > 6) {
            //cout << "n_tr = " << n_tr << "   continuing ...." << endl;
            //continue;
            //cout << "Event number is " << ev->getEventNumber() << endl;
        }

        int n_pos = 0;
        int n_neg = 0;

        for (int i_tr = 0; i_tr < n_tr; i_tr++) {

            trk = (GblTrack*) ev->getGblTrack(i_tr);
            //            cout<<trk->getType()<<endl;
            //            cout<<trk->getZ0()<<endl;
            //            cout<<trk->getOmega()<<endl;
            h_n_trk_crash1->Fill(n_tr, trk->getCharge());
            //cout<<"trk = "<<trk<<endl;
            vector<double> mom3 = trk->getMomentum();
            double px = mom3.at(0);
            double py = mom3.at(1);
            double pz = mom3.at(2);
            double trP = sqrt(px * px + py * py + pz * pz);

            if (trk->getCharge() > 0 && trk->getCharge() < 2.) {
                h_tr_P_pos1->Fill(trP);
                n_pos = n_pos + 1;
            } else if (trk->getCharge() < 0 && trk->getCharge() > -2) {
                h_tr_P_neg1->Fill(trP);
                n_neg = n_neg + 1;
            }

        }


        for (int iTopCl = 0; iTopCl < n_top_cl; iTopCl++) {
            for (int iBotCl = 0; iBotCl < n_bot_cl; iBotCl++) {

                clTop = ev->getEcalCluster(ind_top_cl[iTopCl]);
                clBot = ev->getEcalCluster(ind_bot_cl[iBotCl]);
                int ix_top = clTop->getSeed()->getXCrystalIndex();
                int iy_top = clTop->getSeed()->getYCrystalIndex();
                int ix_bot = clBot->getSeed()->getXCrystalIndex();
                int iy_bot = clBot->getSeed()->getYCrystalIndex();

                double dt = clTop->getClusterTime() - clBot->getClusterTime();
                double Esum = clTop->getEnergy() + clBot->getEnergy();

                double topTimeCorrection = h_time_Corrections->GetBinContent(h_time_Corrections->FindBin(ix_top, iy_top));
                double botTimeCorrection = h_time_Corrections->GetBinContent(h_time_Corrections->FindBin(ix_bot, iy_bot));

                double t_top_corrected = clTop->getClusterTime() - topTimeCorrection;
                double t_bot_corrected = clBot->getClusterTime() - botTimeCorrection;

                double dtCorr = t_top_corrected - t_bot_corrected;

                h_dt_Esum1->Fill(Esum, dt);
                h_dtCorr_Esum1->Fill(Esum, dtCorr);

                if (n_pos == 1 && n_neg == 1) {
                    h_dt_Esum2->Fill(Esum, dt);
                    h_dtCorr_Esum2->Fill(Esum, dtCorr);
                }

            }

        }

    }

    gDirectory->Write();
    return 0;
}

