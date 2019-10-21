/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECalTimingStudies.cc
 * Author: rafopar
 *
 * Created on September 27, 2019, 12:41 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TGraphErrors.h>

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

    TFile *file_ECalTimeCorrections = new TFile("ECalTimeCorrections.root", "Read");

    TH2D *h_time_Corrections = (TH2D*) file_ECalTimeCorrections->Get("h_cl_dtMeans1");

    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");

    TFile *file_out = new TFile("ECalTimingStudies.root", "Recreate");

    TH1D *h_clE1 = new TH1D("h_clE1", "", 200, 0., 1.2 * Eb);
    TH2D *h_cl_E_t1 = new TH2D("h_cl_E_t1", "", 200, 0., 1.2 * Eb, 200, 0., 180.);
    TH2D *h_cl_E_tTop1 = new TH2D("h_cl_E_tTop1", "", 200, 0., 1.2 * Eb, 200, 20., 80.);
    TH2D *h_cl_E_tBot1 = new TH2D("h_cl_E_tBot1", "", 200, 0., 1.2 * Eb, 200, 20., 80.);
    TH2D *h_dt_Esum1 = new TH2D("h_dt_Esum1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dt_Esum2 = new TH2D("h_dt_Esum2", "", 200, 0., 1.2 * Eb, 200, -15., 15.);

    TH2D *h_dtCorr_Esum1 = new TH2D("h_dtCorr_Esum1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);

    TH2D *h_cl_yxc1 = new TH2D("h_cl_yxc1", "", 200, -300., 370, 200, -90., 90.);

    const int n_ECalXregions = 13;
    TH2D * h_cl_dt_Esum_TopCut_[n_ECalXregions];
    TH2D * h_cl_dt_Esum_BotCut_[n_ECalXregions];

    for (int i = 0; i < n_ECalXregions; i++) {
        h_cl_dt_Esum_TopCut_[i] = new TH2D(Form("h_cl_dt_Esum_TopCut_%d", i), "", 200, 0., 1.2 * Eb, 200, -15., 15.);
        h_cl_dt_Esum_BotCut_[i] = new TH2D(Form("h_cl_dt_Esum_BotCut_%d", i), "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    }

    std::map< std::pair<int, int>, TH1D* > m_h_cl_dt_crystal;
    std::map< std::pair<int, int>, TH2D* > m_h_Esum_dt_crystal;

    for (int ix = -23; ix <= 23; ix++) {
        for (int iy = -5; iy <= 5; iy++) {
            m_h_cl_dt_crystal[std::pair<int, int>(ix, iy)] = new TH1D(Form("m_h_cl_dt_crystal_%d_%d", ix, iy), "", 200, -5., 5.);
            m_h_Esum_dt_crystal[std::pair<int, int>(ix, iy)] = new TH2D(Form("m_h_Esum_dt_crystal_%d_%d", ix, iy), "", 200, 0., 1.2*Eb, 200, -15., 15.);
        }
    }

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
                                
                double x_Top = clTop->getPosition().at(0);
                double x_Bot = clBot->getPosition().at(0);

                h_dt_Esum1->Fill(Esum, dt);
                h_dtCorr_Esum1->Fill(Esum, dtCorr);


                if (Esum > 0.75 * Eb) {
                    m_h_cl_dt_crystal[std::pair<int, int>(ix_top, iy_top)]->Fill(dt);
                    m_h_cl_dt_crystal[std::pair<int, int>(ix_bot, iy_bot)]->Fill(-dt);
                    
                }

                m_h_Esum_dt_crystal[std::pair<int, int>(ix_top, iy_top)]->Fill(Esum, dt);
                m_h_Esum_dt_crystal[std::pair<int, int>(ix_bot, iy_bot)]->Fill(Esum, -dt);

                for (int ii = 0; ii < n_ECalXregions; ii++) {

                    if ((x_Top > -280. + double(ii)*50. && x_Top < -280. + double(ii + 1)*50.)) {
                        h_cl_dt_Esum_TopCut_[ii]->Fill(Esum, dt);
                    }

                    if ((x_Bot > -280. + double(ii)*50. && x_Bot < -280. + double(ii + 1)*50.)) {
                        h_cl_dt_Esum_BotCut_[ii]->Fill(Esum, dt);
                    }


                }


                //                if (n_pos == 1 && n_neg == 1) {
                //                    h_dt_Esum2->Fill(Esum, dt);
                //                }

            }

        }


    }

    TGraphErrors * gr_mean_dt[11];

    for (int iy = -5; iy <= 5; iy++) {

        gr_mean_dt[iy + 5] = new TGraphErrors();
        int ind_x = 0;

        for (int ix = -23; ix <= 23; ix++) {

            if (m_h_cl_dt_crystal[std::pair<int, int>(ix, iy)]->GetEntries() > 50.) {
                double mean_dt = m_h_cl_dt_crystal[std::pair<int, int>(ix, iy)]->GetMean();
                double mean_dt_err = m_h_cl_dt_crystal[std::pair<int, int>(ix, iy)]->GetMeanError();
                h_cl_dtMeans1->Fill(ix, iy, mean_dt);

                gr_mean_dt[iy + 5]->SetPoint(ind_x, ix, mean_dt);
                gr_mean_dt[iy + 5]->SetPointError(ind_x, 0., mean_dt_err);

                ind_x = ind_x + 1;
            }
        }
    }


    for (int i = 0; i < 11; i++) {
        gr_mean_dt[i]->SetMarkerStyle(20 + i);
        gr_mean_dt[i]->SetMarkerColor(i + 1);
        gr_mean_dt[i]->Write(Form("gr_mean_dt_%d", i));
    }

    gDirectory->Write();

    return 0;
}

