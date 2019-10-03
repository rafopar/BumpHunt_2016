/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mass_res_chi2.cc
 * Author: rafopar
 *
 * Created on September 16, 2018, 11:54 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TRefArray.h>
#include <cstdlib>
#include <TFileInfo.h>


#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include "setting_2016_pass1.h"

#include <iostream>


using namespace std;

/*
 * 
 */

// TESTING the code that Maurik provided

class my_notify : public TObject {
public:

    my_notify(TChain *chain, HpsEvent* hps_event) {
        fch = chain;
        fev = hps_event;
    };

    Bool_t Notify() {
        cout << "Yo, next file \n";
        auto branch = fch->GetBranch("Event");
        branch->SetAddress(&fev);
        return (true);
    };
private:
    TChain *fch;
    HpsEvent *fev;
};

int main(int argc, char** argv) {

    const int n_SVT_layer = 6;
    
    const double Py_P_mean = 3.1e-4;
    const double Py_P_sigm = 7.62e-4;
    const double Px_P_mean = 3.133e-2;
    const double Px_P_sigm = 1.19e-3;

    TCanvas *c1 = new TCanvas("c1", "", 750, 750);

    //    TFile *file_in = new TFile("../Data/hps_007796_All_Moller_3.11.1.root", "Read");
    // TFile *file_in = new TFile("../Data/hps_00*_All_Moller_3.11.1.root", "Read");


    TChain *tr1 = new TChain("HPS_Event");

    tr1->Add("../Data/hps_All_Moller_3.11.1.root");
    //    tr1->AddFile("../Data/hps_007796_All_Moller_3.11.1.root");
    //    tr1->AddFile("../Data/hps_007800_All_Moller_3.11.1.root");
    //    tr1->Add("../Data/hps_007966_All_Moller_3.11.1.root");
    //    tr1->Add("../Data/hps_007985_All_Moller_3.11.1.root");
    
    //tr1->Add("../Data/hps_007800.190_dst_3.11.1.root");
    //tr1->Add("../Data/hps_008054_All_Moller_3.11.1.root");
    //tr1->Add("../Data/hps_007*_All_Moller_3.11.1.root");
    HpsEvent *ev = new HpsEvent();


    auto my_no = new my_notify(tr1, ev);
    my_no->Notify();
    tr1->SetNotify(my_no);

    //TTree *tr1 = (TTree*) file_in->Get("HPS_Event");

    TFile *file_out = new TFile("chi2_mass_resol.root", "Recreate");

    TH1D *h_ECal_hits_raw = new TH1D("h_ECal_hits_raw", "", 51, -0.5, 50.5);
    
    TH1D *h_n_TC_Moellers1 = new TH1D("h_n_TC_Moellers1", "", 11, -0.5, 10.5);
    TH1D *h_M_tcMol1 = new TH1D("h_M_tcMol1", "", 200, 0.015, 0.09);
    TH1D *h_M_tcMol2 = new TH1D("h_M_tcMol2", "", 200, 0.015, 0.09);
    TH1D *h_M_tcMol3 = new TH1D("h_M_tcMol3", "", 200, 0.015, 0.09);
    TH1D *h_M_tcMol4 = new TH1D("h_M_tcMol4", "", 200, 0.015, 0.09);

    TH2D *h_M_tcMol_chi2_1 = new TH2D("h_M_tcMol_chi2_1", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_2 = new TH2D("h_M_tcMol_chi2_2", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_3 = new TH2D("h_M_tcMol_chi2_3", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_4 = new TH2D("h_M_tcMol_chi2_4", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_5 = new TH2D("h_M_tcMol_chi2_5", "", 200, 0.015, 0.09, 200, 0., 15);

    TH1D *h_tar_Y_angle1 = new TH1D("h_tar_Y_angle1", "", 200, -0.035, 0.035);
    TH1D *h_tar_Y_angle2 = new TH1D("h_tar_Y_angle2", "", 200, -0.035, 0.035);
    TH1D *h_tar_Y_angle3 = new TH1D("h_tar_Y_angle3", "", 200, -0.035, 0.035);
    TH1D *h_tar_Y_angle4 = new TH1D("h_tar_Y_angle4", "", 200, -0.035, 0.035);
    TH1D *h_tar_X_angle1 = new TH1D("h_tar_X_angle1", "", 200, -0.01, 0.06);
    TH1D *h_tar_X_angle2 = new TH1D("h_tar_X_angle2", "", 200, -0.01, 0.06);
    TH1D *h_tar_X_angle3 = new TH1D("h_tar_X_angle3", "", 200, -0.01, 0.06);
    TH1D *h_tar_X_angle4 = new TH1D("h_tar_X_angle4", "", 200, -0.01, 0.06);

    TH2D *h_M_tcMol_chi2_worse_1 = new TH2D("h_M_tcMol_chi2_worse_1", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_worse_2 = new TH2D("h_M_tcMol_chi2_worse_2", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_worse_3 = new TH2D("h_M_tcMol_chi2_worse_3", "", 200, 0.015, 0.09, 200, 0., 15);
    TH2D *h_M_tcMol_chi2_worse_4 = new TH2D("h_M_tcMol_chi2_worse_4", "", 200, 0.015, 0.09, 200, 0., 15);

    TH1D *h_match_nsigma1 = new TH1D("h_match_nsigma1", "", 200, 0., 32);
    TH1D *h_match_nsigma2 = new TH1D("h_match_nsigma2", "", 200, 0., 32);

    TH1D *h_svt_time_el1 = new TH1D("h_svt_time_el1", "", 200, -15., 15.);
    TH1D *h_svt_time_el2 = new TH1D("h_svt_time_el2", "", 200, -15., 15.);
    TH1D *h_tr_dt1 = new TH1D("h_tr_dt1", "", 200, -10., 10);
    TH1D *h_tr_dt2 = new TH1D("h_tr_dt2", "", 200, -10., 10);
    TH1D *h_tr_dt3 = new TH1D("h_tr_dt3", "", 200, -10., 10);
    TH2D *h_tr_el_times12_1 = new TH2D("h_tr_el_times12_1", "", 200, -15., 15., 200, -15., 15);
    TH2D *h_tr_el_times12_2 = new TH2D("h_tr_el_times12_2", "", 200, -15., 15., 200, -15., 15);
    TH2D *h_tr_P_12_1 = new TH2D("h_tr_P_12_1", "", 200, 0., 1.2 * Eb, 200, 0., 1.2 * Eb);
    TH2D *h_tr_Psum_Pdif1 = new TH2D("h_tr_Psum_Pdif1", "", 200, -1.5, 1.5, 200, 1.5, 3.1);

    TH2D *h_SVT_hit_vz_t1 = new TH2D("h_SVT_hit_vz_t1", "", 80, -12., 12., 80, 0., 950);
    h_SVT_hit_vz_t1->SetStats(0);
    TH1D *h_hit_rms1 = new TH1D("h_hit_rms1", "", 200, 0., 10.);
    TH1D *h_svt_hit_maxdt1 = new TH1D("h_svt_hit_maxdt1", "", 200, 0., 25.); // max_t - min_t between hits
    TH2D *h_chi2NDF_maxdt1 = new TH2D("h_chi2NDF_maxdt1", "", 200, 0., 25, 200, 0., 15);
    TH1D *h_dt_L1_1 = new TH1D("h_dt_L1_1", "", 200, -25., 25);
    TH1D *h_dt_L1_2 = new TH1D("h_dt_L1_2", "", 200, -25., 25);
    TH1D *h_dt_L1_3 = new TH1D("h_dt_L1_3", "", 200, -25., 25);

    TH1D * h_SVT_hit_time_top1_[n_SVT_layer];
    TH1D * h_SVT_hit_time_bot1_[n_SVT_layer];
    TH1D * h_SVT_hitdt_topbot1_[n_SVT_layer];

    for (int i = 0; i < n_SVT_layer; i++) {
        h_SVT_hit_time_top1_[i] = new TH1D(Form("h_SVT_hit_time_top1_%d", i), "", 200, -15., 15.);
        h_SVT_hit_time_bot1_[i] = new TH1D(Form("h_SVT_hit_time_bot1_%d", i), "", 200, -15., 15.);
        h_SVT_hitdt_topbot1_[i] = new TH1D(Form("h_SVT_hitdt_topbot1_%d", i), "", 200, -25., 25.);
    }



    TBranch *b_hps_event = tr1->GetBranch("Event");
    b_hps_event->SetAddress(&ev);

    SvtTrack *SVTtrack = 0;
    GblTrack *GBLtrack = 0;
    EcalCluster* cl = 0;
    EcalHit* ec_hit = 0;
    SvtHit *svt_hit = 0;
    HpsParticle* part = 0;

    int nev = tr1->GetEntries();

    //int nev = 450000;
    cout << "Number of events is " << nev << endl;

    //nev = 100000;
    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }
        
        int n_ECalHits = ev->getNumberOfEcalHits();
        
        
        h_ECal_hits_raw->Fill(n_ECalHits);

        //if (!(ev->isSingle0Trigger() || ev->isSingle1Trigger())) {
        if (!(ev->isSingle0Trigger())) {
            continue;
        }

        
        
        int n_part = ev->getNumberOfParticles(HpsParticle::TC_MOLLER_CANDIDATE);

        h_n_TC_Moellers1->Fill(n_part);

        vector<SvtHit*> top_hits[n_SVT_layer];
        vector<SvtHit*> bot_hits[n_SVT_layer];

        int n_SVT_hits = ev->getNumberOfSvtHits();


        for (int ihit = 0; ihit < n_SVT_hits; ihit++) {

            SvtHit* cur_hit = ev->getSvtHit(ihit);

            double t_hit = cur_hit->getTime();
            int layer_hit = cur_hit->getLayer() - 1;
            vector<double> hit_pos = cur_hit->getPosition();
            //cout<<layer_hit<<endl;

            if (hit_pos[1] > 0) {
                h_SVT_hit_time_top1_[layer_hit]->Fill(t_hit);
                top_hits[layer_hit].push_back(cur_hit);
            } else {
                h_SVT_hit_time_bot1_[layer_hit]->Fill(t_hit);
                bot_hits[layer_hit].push_back(cur_hit);
            }
        }


        for (int i_layer = 0; i_layer < n_SVT_layer; i_layer++) {

            for (int itop = 0; itop < top_hits[i_layer].size(); itop++) {
                for (int ibot = 0; ibot < bot_hits[i_layer].size(); ibot++) {

                    double dt = top_hits[i_layer].at(itop)->getTime() - bot_hits[i_layer].at(ibot)->getTime();

                    h_SVT_hitdt_topbot1_[i_layer]->Fill(dt);
                }

            }

            top_hits[i_layer].clear();
            top_hits[i_layer].shrink_to_fit();
            bot_hits[i_layer].clear();
            bot_hits[i_layer].shrink_to_fit();
        }

        for (int i_tcMol = 0; i_tcMol < n_part; i_tcMol++) {

            HpsParticle *tcMol_part = ev->getParticle(HpsParticle::TC_MOLLER_CANDIDATE, i_tcMol);

            double mass_tcMol = tcMol_part->getMass();
            h_M_tcMol1->Fill(mass_tcMol);

            int n_daught = tcMol_part->getParticles()->GetSize();

            HpsParticle * el_part[2];
            double p_el[2];
            double tr_time[2];
            double match_nsigma[2];
            double chi2[2];
            int n_hits[2];

            el_part[0] = (HpsParticle*) tcMol_part->getParticles()->At(0);
            el_part[1] = (HpsParticle*) tcMol_part->getParticles()->At(1);

            match_nsigma[0] = el_part[0]->getGoodnessOfPID();
            match_nsigma[1] = el_part[1]->getGoodnessOfPID();

            chi2[0] = ((GblTrack*) el_part[0]->getTracks()->At(0))->getChi2();
            n_hits[0] = ((GblTrack*) el_part[0]->getTracks()->At(0))->getSvtHits()->GetSize();


            chi2[1] = ((GblTrack*) el_part[1]->getTracks()->At(0))->getChi2();
            n_hits[1] = ((GblTrack*) el_part[1]->getTracks()->At(0))->getSvtHits()->GetSize();


            double chi2_ndf_worse = TMath::Max(chi2[0] / (2 * n_hits[0] - 5), chi2[1] / (2 * n_hits[1] - 5));
            double tot_chi2 = chi2[0] + chi2[1];
            double tot_ndf = double(2 * (n_hits[0] + n_hits[1]) - 10);

            h_match_nsigma1->Fill(match_nsigma[0]);
            h_match_nsigma1->Fill(match_nsigma[1]);

            vector<double> v3_P = tcMol_part->getMomentum();
            double tarP = sqrt(v3_P[0] * v3_P[0] + v3_P[1] * v3_P[1] + v3_P[2] * v3_P[2]);
            double tar_Xangle = v3_P[0] / tarP;
            double tar_Yangle = v3_P[1] / tarP;

            h_tar_Y_angle1->Fill(tar_Yangle);
            h_tar_X_angle1->Fill(tar_Xangle);

            vector<double> v3_el0 = el_part[0]->getMomentum();
            vector<double> v3_el1 = el_part[1]->getMomentum();
            p_el[0] = sqrt(v3_el0[0] * v3_el0[0] + v3_el0[1] * v3_el0[1] + v3_el0[2] * v3_el0[2]);
            p_el[1] = sqrt(v3_el1[0] * v3_el1[0] + v3_el1[1] * v3_el1[1] + v3_el1[2] * v3_el1[2]);


            // Seems there is no a direct method to get the track time, so I will get SVT hits,
            // and then calculate the track time as an average time of SVT hits
            TRefArray *el_1st_hits = ((GblTrack*) (el_part[0]->getTracks()->At(0)))->getSvtHits();
            TRefArray *el_2nd_hits = ((GblTrack*) (el_part[1]->getTracks()->At(0)))->getSvtHits();

            tr_time[0] = ((GblTrack*) el_part[0]->getTracks()->At(0))->getTrackTime();
            tr_time[1] = ((GblTrack*) el_part[1]->getTracks()->At(0))->getTrackTime();

            double hit_tmin = 1000.;
            double hit_tmax = -1000.;
            double him_time_mean0 = 0;
            double t_L1_top = 1000;
            double t_L1_bot = -1000;
            for (int ihit = 0; ihit < el_1st_hits->GetSize(); ihit++) {
                double cur_t = ((SvtHit*) el_1st_hits->At(ihit))->getTime();
                vector<double> hit_pos = ((SvtHit*) el_1st_hits->At(ihit))->getPosition();
                h_SVT_hit_vz_t1->Fill(cur_t, hit_pos[2], hit_pos[1] / abs(hit_pos[1]));

                him_time_mean0 = him_time_mean0 + ((SvtHit*) el_1st_hits->At(ihit))->getTime();

                if (cur_t < hit_tmin) {
                    hit_tmin = cur_t;
                }

                if (cur_t > hit_tmax) {
                    hit_tmax = cur_t;
                }

                if (((SvtHit*) el_1st_hits->At(ihit))->getLayer() == 3) {

                    if (hit_pos[1] > 0) {
                        t_L1_top = ((SvtHit*) el_1st_hits->At(ihit))->getTime();
                    } else {
                        t_L1_bot = ((SvtHit*) el_1st_hits->At(ihit))->getTime();
                    }
                }
            }
            him_time_mean0 = him_time_mean0 / el_1st_hits->GetSize();

            h_svt_hit_maxdt1->Fill(hit_tmax - hit_tmin);

            h_chi2NDF_maxdt1->Fill(hit_tmax - hit_tmin, chi2[0] / (2 * n_hits[0] - 5.));

            double hit_time_rms1 = 0;
            for (int ihit = 0; ihit < el_1st_hits->GetSize(); ihit++) {
                double cur_t = ((SvtHit*) el_1st_hits->At(ihit))->getTime();
                hit_time_rms1 = hit_time_rms1 + (cur_t - him_time_mean0)*(cur_t - him_time_mean0);
            }

            hit_time_rms1 = sqrt(hit_time_rms1 / el_1st_hits->GetSize());
            h_hit_rms1->Fill(hit_time_rms1);

            //
            //
            //            tr_time[1] = 0;
            for (int ihit = 0; ihit < el_2nd_hits->GetSize(); ihit++) {
                //tr_time[1] = tr_time[1] + ((SvtHit*) el_2nd_hits->At(ihit))->getTime();
                double cur_t = ((SvtHit*) el_2nd_hits->At(ihit))->getTime();
                vector<double> hit_pos = ((SvtHit*) el_2nd_hits->At(ihit))->getPosition();
                h_SVT_hit_vz_t1->Fill(cur_t, hit_pos[2], hit_pos[1] / abs(hit_pos[1]));

                if (((SvtHit*) el_2nd_hits->At(ihit))->getLayer() == 3) {

                    if (hit_pos[1] > 0) {
                        t_L1_top = ((SvtHit*) el_2nd_hits->At(ihit))->getTime();
                    } else {
                        t_L1_bot = ((SvtHit*) el_2nd_hits->At(ihit))->getTime();
                    }
                }


            }
            //            tr_time[1] = tr_time[1] / el_2nd_hits->GetSize();

            //            h_SVT_hit_vz_t1->Draw("colz");
            //            c1->Print("tmp.eps");
            //            cin.ignore();
            //            h_SVT_hit_vz_t1->Reset();


            h_svt_time_el1->Fill(tr_time[0]);
            h_svt_time_el2->Fill(tr_time[1]);
            h_tr_el_times12_1->Fill(tr_time[0], tr_time[1]);

            double tr_dt = tr_time[0] - tr_time[1];
            double tr_dt_L1 = t_L1_top - t_L1_bot;

            h_dt_L1_1->Fill(tr_dt_L1);

            h_tr_dt1->Fill(tr_dt);

            h_tr_P_12_1->Fill(p_el[0], p_el[1]);
            h_tr_Psum_Pdif1->Fill(p_el[1] - p_el[0], p_el[1] + p_el[0]);

            if (p_el[0] + p_el[1] > 1.8 && p_el[0] + p_el[1] < 2.5 && p_el[0] < 1.5 && p_el[1] < 1.5) {
            //if (tarP > 1.8 && tarP < 2.9 && p_el[0] < 1.75 && p_el[1] < 1.75) {
                h_tr_dt2->Fill(tr_dt);
                h_tr_el_times12_2->Fill(tr_time[0], tr_time[1]);
                h_M_tcMol2->Fill(mass_tcMol);

                h_match_nsigma2->Fill(match_nsigma[0]);
                h_match_nsigma2->Fill(match_nsigma[1]);

                h_tar_Y_angle2->Fill(tar_Yangle);
                h_tar_X_angle2->Fill(tar_Xangle);


                h_dt_L1_2->Fill(tr_dt_L1);

                                if ((match_nsigma[0] < 4. || match_nsigma[0] > 50.) && (match_nsigma[1] < 4. || match_nsigma[1] > 50.)) {
            //    if ((match_nsigma[0] - 15)*(match_nsigma[1] - 15.) < 0 && TMath::Min(match_nsigma[0], match_nsigma[1]) < 7) {
                    h_M_tcMol3->Fill(mass_tcMol);
                    h_tr_dt3->Fill(tr_dt);
                    h_M_tcMol_chi2_3->Fill(mass_tcMol, tot_chi2 / tot_ndf);
                    h_M_tcMol_chi2_worse_3->Fill(mass_tcMol, chi2_ndf_worse);

                    h_dt_L1_3->Fill(tr_dt_L1);


                    h_tar_Y_angle3->Fill(tar_Yangle);
                    h_tar_X_angle3->Fill(tar_Xangle);


                    if (tr_dt > -3. && tr_dt < 3.) {
                        h_M_tcMol4->Fill(mass_tcMol);
                        h_M_tcMol_chi2_4->Fill(mass_tcMol, tot_chi2 / tot_ndf);
                        h_M_tcMol_chi2_worse_4->Fill(mass_tcMol, chi2_ndf_worse);


                        h_tar_Y_angle4->Fill(tar_Yangle);
                        h_tar_X_angle4->Fill(tar_Xangle);

                        if( TMath::Abs(tar_Yangle - Py_P_mean) < 2*Py_P_sigm && TMath::Abs(tar_Xangle - Px_P_mean) < 2*Px_P_sigm){
                            h_M_tcMol_chi2_5->Fill(mass_tcMol, tot_chi2 / tot_ndf);
                        }
                        
                        
                    }

                }


            }


            //            SvtHit *el_1sthit_0 = ((GBLtrack*)(el_part[0]->getTracks()->At(0)))->getSvtHits()->At(0);
            //            SvtHit *el_1sthit_1 = ((GBLtrack*)(el_part[1]->getTracks()->At(0)))->getSvtHits()->At(0);

            //double trk

        }

    }


    gDirectory->Write();

    return 0;
}

