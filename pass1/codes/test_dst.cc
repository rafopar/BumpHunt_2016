#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include "setting_2016_pass1.h"

#include <iostream>

using namespace std;

int main() {

    //gSystem->Load("/Work/apps/hps-dst/hps-dst/build/lib/libHpsEvent.so");

    TFile *file_in = new TFile("../Data/hps_007796_All_v0_3.11.1.root");

    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");
    //tr1->SetBranchAddress("HPS_Event", ev);

    TFile *file_out = new TFile("test_dst.root", "Recreate");

    TH1D *h_Ecl1 = new TH1D("h_Ecl1", "", 200, 0., 2.5);

    TH1D *h_n_svt_hits1 = new TH1D("h_n_svt_hits1", "", 81, -0.5, 80.5);
    TH1D *h_svt_hitY1 = new TH1D("h_svt_hitY1", "", 200, -50., 50.);
    TH1D *h_n_svt_tophits1 = new TH1D("h_n_svt_tophits1", "", 41, -0.5, 40.5);
    TH1D *h_n_svt_bothits1 = new TH1D("h_n_svt_bothits1", "", 41, -0.5, 40.5);
    TH2D *h_n_svTtopbot_hit2 = new TH2D("h_n_svTtopbot_hit2", "", 41, -0.5, 40.5, 41, -0.5, 40.5);
    TH2D *h_n_svTtopbot_hit3 = new TH2D("h_n_svTtopbot_hit3", "", 41, -0.5, 40.5, 41, -0.5, 40.5);

    TH1D *h_chi2ndf1 = new TH1D("h_chi2ndf1", "", 200, 0., 20);
    TH2D *h_tr_yx1 = new TH2D("h_tr_yx1", "", 200, -400., 400, 200, -90., 90);
    TH2D *h_n_top_bot_tracks1 = new TH2D("h_n_top_bot_tracks1", "", 11, -0.5, 10.5, 11, -0.5, 10.5);

    TH1D *h_goodNessofPID1 = new TH1D("h_goodNessofPID1", "", 200, 0., 45);
    TH2D *h_goodNessofPID_charge1 = new TH2D("h_goodNessofPID_charge1", "", 3, -1.5, 1.5, 200, 0., 45.);

    TH1D *h_n_fs_part1 = new TH1D("h_n_fs_part1", "", 41, -0.5, 40.5);

    TH2D *h_top_trkhits_allhits1 = new TH2D("h_top_trkhits_allhits1", "", 21, -0.5, 20.5, 21, -0.5, 20.5);
    TH2D *h_bot_trkhits_allhits1 = new TH2D("h_bot_trkhits_allhits1", "", 21, -0.5, 20.5, 21, -0.5, 20.5);

    TH1D *h_pos_chiDNF_clean1 = new TH1D("h_pos_chiDNF_clean1", "", 200, 0., 25.);
    TH1D *h_neg_chiDNF_clean1 = new TH1D("h_neg_chiDNF_clean1", "", 200, 0., 25.);

    TH1D *h_pos_chiDNF5hits_clean1 = new TH1D("h_pos_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_pos_chiDNF6hits_clean1 = new TH1D("h_pos_chiDNF6hits_clean1", "", 200, 0., 25.);
    TH1D *h_neg_chiDNF5hits_clean1 = new TH1D("h_neg_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_neg_chiDNF6hits_clean1 = new TH1D("h_neg_chiDNF6hits_clean1", "", 200, 0., 25.);

    TH1D *h_top_pos_chiDNF5hits_clean1 = new TH1D("h_top_pos_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_top_pos_chiDNF6hits_clean1 = new TH1D("h_top_pos_chiDNF6hits_clean1", "", 200, 0., 25.);
    TH1D *h_top_neg_chiDNF5hits_clean1 = new TH1D("h_top_neg_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_top_neg_chiDNF6hits_clean1 = new TH1D("h_top_neg_chiDNF6hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_pos_chiDNF5hits_clean1 = new TH1D("h_bot_pos_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_pos_chiDNF6hits_clean1 = new TH1D("h_bot_pos_chiDNF6hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_neg_chiDNF5hits_clean1 = new TH1D("h_bot_neg_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_neg_chiDNF6hits_clean1 = new TH1D("h_bot_neg_chiDNF6hits_clean1", "", 200, 0., 25.);

    TH2D *h_top_pos_chiDNF5hits_P_clean1 = new TH2D("h_top_pos_chiDNF5hits_P_clean1", "", 200, 0.4, 2.5, 200, 0., 25);
    
    TH1D *h_top_chiDNF5hits_clean1 = new TH1D("h_top_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_top_chiDNF6hits_clean1 = new TH1D("h_top_chiDNF6hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_chiDNF5hits_clean1 = new TH1D("h_bot_chiDNF5hits_clean1", "", 200, 0., 25.);
    TH1D *h_bot_chiDNF6hits_clean1 = new TH1D("h_bot_chiDNF6hits_clean1", "", 200, 0., 25.);

    TH1D *h_pos_chiDNF_clean2 = new TH1D("h_pos_chiDNF_clean2", "", 200, 0., 25.);
    TH1D *h_neg_chiDNF_clean2 = new TH1D("h_neg_chiDNF_clean2", "", 200, 0., 25.);



    TH2D *h_cl_t_E1 = new TH2D("h_cl_t_E1", "", 200, 0., 2.5, 200, 25., 95.);
    TH2D *h_cl_dt_Esum1 = new TH2D("h_cl_dt_Esum1", "", 200, 0.5, 2.5, 200, -7., 7);
    TH2D *h_cl_dt_Esum2 = new TH2D("h_cl_dt_Esum2", "", 200, 0.5, 2.5, 200, -7., 7);

    HpsEvent *ev = new HpsEvent();

    TBranch *b_hos_event = tr1->GetBranch("Event");
    b_hos_event->SetAddress(&ev);

    SvtTrack *SVTtrack = 0;
    GblTrack *GBLtrack = 0;
    EcalCluster* cl = 0;
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

    //nev = 100000;
    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }


        int n_cl = ev->getNumberOfEcalClusters();

        bool is_pair1 = ev->isPair1Trigger();

        if (!is_pair1) {
            continue;
        }

        //cout<<"n_cl = "<<n_cl<<endl;

        // ================================================================        
        // ================================================================        
        // ==================== Loop over ECal clusters====================
        // ==================== Loop over ECal clusters====================
        // ================================================================        
        // ================================================================        

        for (int i_cl = 0; i_cl < n_cl; i_cl++) {

            cl = ev->getEcalCluster(i_cl);

            double E_cl = cl->getEnergy();

            h_Ecl1->Fill(E_cl);
        }


        // ================================================================        
        // ================================================================        
        // ===================== Loop over SVT hits =======================
        // ===================== Loop over SVT hits =======================
        // ================================================================        
        // ================================================================        

        int n_svt_hits = ev->getNumberOfSvtHits();

        h_n_svt_hits1->Fill(n_svt_hits);

        int n_top_hits = 0;
        int n_bot_hits = 0;
        for (int ihit = 0; ihit < n_svt_hits; ihit++) {
            svt_hit = ev->getSvtHit(ihit);

            std::vector<double> hit_pos = svt_hit->getPosition();

            h_svt_hitY1->Fill(hit_pos[1]);

            if (hit_pos[1] > 0) {
                n_top_hits = n_top_hits + 1;
            } else {
                n_bot_hits = n_bot_hits + 1;
            }
        }

        h_n_svt_tophits1->Fill(n_top_hits);
        h_n_svt_bothits1->Fill(n_bot_hits);

        // ================================================================        
        // ================================================================        
        // ===================== Loop over GBL tracks =====================
        // ===================== Loop over GBL tracks =====================
        // ================================================================
        // ================================================================

        int n_tracks = ev->getNumberOfGblTracks();
        int n_top_trk = 0;
        int n_bot_trk = 0;
        int n_pos_trk = 0;
        int n_neg_trk = 0;


        for (int itr = 0; itr < n_tracks; itr++) {

            GBLtrack = ev->getGblTrack(itr);

            double chi2 = GBLtrack->getChi2();
            int nhits = (GBLtrack->getSvtHits())->GetSize();
            int ndf = (2 * nhits - 5);
            int q = GBLtrack->getCharge();
            double chi2ndf = chi2 / double(ndf);

            vector<double> pos_ec = GBLtrack->getPositionAtEcal();

            h_tr_yx1->Fill(pos_ec[0], pos_ec[1]);
            h_chi2ndf1->Fill(chi2ndf);

            if (pos_ec[1] > 0) {
                n_top_trk = n_top_trk + 1;
            } else {
                n_bot_trk = n_bot_trk + 1;
            }


            if (q > 0) {
                n_pos_trk = n_pos_trk + 1;
            } else {
                n_neg_trk = n_neg_trk + 1;
            }
        }

        h_n_top_bot_tracks1->Fill(n_bot_trk, n_top_trk);

        int n_fs_part = ev->getNumberOfParticles(HpsParticle::FINAL_STATE_PARTICLE);
        h_n_fs_part1->Fill(n_fs_part);


        int n_pos_part = 0;
        int n_neg_part = 0;
        int n_neut_part = 0;

        int n_top_part = 0;
        int n_bot_part = 0;

        for (int ipart = 0; ipart < n_fs_part; ipart++) {

            part = ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ipart);


            double goodness_pid = part->getGoodnessOfPID();
            double q = part->getCharge();

            int n_cl = part->getClusters()->GetSize();


            // We don't want to look into particles that don't have clusters associated, nor tracks associated
            if (n_cl > 0 && q != 0) {
                std::vector<double> cl_pos = ((EcalCluster*) part->getClusters()->At(0))->getPosition();

                double cl_E = ((EcalCluster*) part->getClusters()->At(0))->getEnergy();
                double cl_t = ((EcalCluster*) part->getClusters()->At(0))->getClusterTime();

                h_cl_t_E1->Fill(cl_E, cl_t);

                if (cl_pos[1] > 0) {
                    ind_top_fs_part[n_top_part] = ipart;
                    n_top_part = n_top_part + 1;
                } else {
                    ind_bot_fs_part[n_bot_part] = ipart;
                    n_bot_part = n_bot_part + 1;
                }

                h_goodNessofPID1->Fill(goodness_pid);

                h_goodNessofPID_charge1->Fill(q, goodness_pid);

                if (q > 0) {
                    ind_pos_fs_part[n_pos_part] = ipart;
                    n_pos_part = n_pos_part + 1;
                } else if (q < 0) {
                    ind_neg_fs_part[n_neg_part] = ipart;
                    n_neg_part = n_neg_part + 1;
                } else {
                    ind_neut_fs_part[n_neut_part] = ipart;
                    n_neut_part = n_neg_part + 1;
                }
            }

        }



        bool clean_event_sample = (n_pos_part == 1 && n_neg_part == 1 && n_top_part && n_bot_part == 1);
        //bool clean_event_sample = (n_bot_trk == 1 && n_top_trk == 1 && n_pos_trk == 1 && n_bot_trk == 1);


        if (n_bot_trk == 1 && n_top_trk == 1) {
            h_n_svTtopbot_hit2->Fill(n_bot_hits, n_top_hits);
        }

        if (clean_event_sample) {
            h_n_svTtopbot_hit3->Fill(n_bot_hits, n_top_hits);

            //  GBLtrack* cur_trk = (GBLtrack*)(ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ind_top_fs_part[0])->getTracks())->At(0);

            GblTrack *top_tr = (GblTrack*) ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ind_top_fs_part[0])->getTracks()->At(0);
            GblTrack *bot_tr = (GblTrack*) ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ind_bot_fs_part[0])->getTracks()->At(0);

            EcalCluster *top_cl = (EcalCluster*) ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ind_top_fs_part[0])->getClusters()->At(0);
            EcalCluster *bot_cl = (EcalCluster*) ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, ind_bot_fs_part[0])->getClusters()->At(0);

            double Esum = top_cl->getEnergy() + bot_cl->getEnergy();
            double dt = top_cl->getClusterTime() - bot_cl->getClusterTime();

            h_cl_dt_Esum1->Fill(Esum, dt);

            int n_top_hit_of_track = top_tr->getSvtHits()->GetSize();
            int n_bot_hit_of_track = bot_tr->getSvtHits()->GetSize();

            h_top_trkhits_allhits1->Fill(n_top_hit_of_track, n_top_hits);
            h_bot_trkhits_allhits1->Fill(n_bot_hit_of_track, n_bot_hits);


            if (n_top_hit_of_track == n_top_hits && n_bot_hit_of_track && n_bot_hits) {

                h_cl_dt_Esum2->Fill(Esum, dt);

                double top_q = top_tr->getCharge();
                double top_chi2 = top_tr->getChi2();
                double top_chi2NDF = top_chi2 / (2 * double(n_top_hit_of_track) - 5);
                double bot_q = bot_tr->getCharge();
                double bot_chi2 = bot_tr->getChi2();
                double bot_chi2NDF = bot_chi2 / (2 * double(n_bot_hit_of_track) - 5);

                vector<double> P3_top = top_tr->getMomentum();
                double P_top = sqrt(P3_top[0] * P3_top[0] + P3_top[1] * P3_top[1] + P3_top[2] * P3_top[2]);

                
                double pos_chi2_ndf = (top_q > 0) ? top_chi2NDF : bot_chi2NDF;
                double neg_chi2_ndf = (top_q < 0) ? top_chi2NDF : bot_chi2NDF;
                int pos_ndf = (top_q > 0) ? 2 * n_top_hit_of_track - 5 : 2 * n_bot_hit_of_track - 5;
                int neg_ndf = (top_q < 0) ? 2 * n_top_hit_of_track - 5 : 2 * n_bot_hit_of_track - 5;

                h_pos_chiDNF_clean1->Fill(pos_chi2_ndf);
                h_neg_chiDNF_clean1->Fill(neg_chi2_ndf);


                if (n_top_hit_of_track == 5) {
                    h_top_chiDNF5hits_clean1->Fill(top_chi2NDF);

                    if (top_q > 0) {
                        h_top_pos_chiDNF5hits_clean1->Fill(top_chi2NDF);
                        h_top_pos_chiDNF5hits_P_clean1->Fill(P_top,top_chi2NDF );
                    } else {
                        h_top_neg_chiDNF5hits_clean1->Fill(top_chi2NDF);
                    }

                } else {
                    if (top_q > 0) {
                        h_top_pos_chiDNF6hits_clean1->Fill(top_chi2NDF);
                    } else {
                        h_top_neg_chiDNF6hits_clean1->Fill(top_chi2NDF);
                    }
                    h_top_chiDNF6hits_clean1->Fill(top_chi2NDF);
                }

                if (n_bot_hit_of_track == 5) {
                    h_bot_chiDNF5hits_clean1->Fill(bot_chi2NDF);

                    if (bot_q > 0) {
                        h_bot_pos_chiDNF5hits_clean1->Fill(bot_chi2NDF);
                    } else {
                        h_bot_neg_chiDNF5hits_clean1->Fill(top_chi2NDF);
                    }

                } else {
                    if (bot_q > 0) {
                        h_bot_pos_chiDNF6hits_clean1->Fill(bot_chi2NDF);
                    } else {
                        h_bot_neg_chiDNF6hits_clean1->Fill(top_chi2NDF);
                    }
                    h_bot_chiDNF6hits_clean1->Fill(bot_chi2NDF);
                }




                if (pos_ndf == 5) {
                    h_pos_chiDNF5hits_clean1->Fill(pos_chi2_ndf);
                } else {
                    h_pos_chiDNF6hits_clean1->Fill(pos_chi2_ndf);
                }

                if (neg_ndf == 5) {
                    h_neg_chiDNF5hits_clean1->Fill(neg_chi2_ndf);
                } else {
                    h_neg_chiDNF6hits_clean1->Fill(neg_chi2_ndf);
                }


                if (Esum > Psum_min && TMath::Abs(dt) < 1) {
                    h_pos_chiDNF_clean2->Fill(pos_chi2_ndf);
                    h_neg_chiDNF_clean2->Fill(neg_chi2_ndf);

                }
            }
        }

    }


    gDirectory->Write();
    return 0;
}
