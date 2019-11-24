/* 
 * File:   TrkClustMatchingStudies.cc
 * Author: rafopar
 *
 * Created on October 17, 2019, 3:45 PM
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
    
    if (argc >= 2) {

        dataSet = argv[1];

        if (argc == 3) {
            ApMass = atoi(argv[2]);
        }

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./EventSelection.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }
    
    isTrkClusterMatching = true;
    InitVariables(dataSet);


    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");

    TFile *file_out = new TFile(Form("TrkClustMatching_%s.root", dataSet.c_str()), "Recreate");

    TH2D *h_dX_P_TopPos1 = new TH2D("h_dX_P_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_BotPos1 = new TH2D("h_dX_P_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_TopNeg1 = new TH2D("h_dX_P_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_BotNeg1 = new TH2D("h_dX_P_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);

    TH2D *h_dY_P_TopPos1 = new TH2D("h_dY_P_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_BotPos1 = new TH2D("h_dY_P_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_TopNeg1 = new TH2D("h_dY_P_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_BotNeg1 = new TH2D("h_dY_P_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);

    TH2D *h_dX_P_WithL6_TopPos1 = new TH2D("h_dX_P_WithL6_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_WithL6_BotPos1 = new TH2D("h_dX_P_WithL6_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_NoL6_TopPos1 = new TH2D("h_dX_P_NoL6_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_NoL6_BotPos1 = new TH2D("h_dX_P_NoL6_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_WithL6_TopNeg1 = new TH2D("h_dX_P_WithL6_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_WithL6_BotNeg1 = new TH2D("h_dX_P_WithL6_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_NoL6_TopNeg1 = new TH2D("h_dX_P_NoL6_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_NoL6_BotNeg1 = new TH2D("h_dX_P_NoL6_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);

    TH2D *h_dY_P_WithL6_TopPos1 = new TH2D("h_dY_P_WithL6_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_WithL6_BotPos1 = new TH2D("h_dY_P_WithL6_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_NoL6_TopPos1 = new TH2D("h_dY_P_NoL6_TopPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_NoL6_BotPos1 = new TH2D("h_dY_P_NoL6_BotPos1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_WithL6_TopNeg1 = new TH2D("h_dY_P_WithL6_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_WithL6_BotNeg1 = new TH2D("h_dY_P_WithL6_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_NoL6_TopNeg1 = new TH2D("h_dY_P_NoL6_TopNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);
    TH2D *h_dY_P_NoL6_BotNeg1 = new TH2D("h_dY_P_NoL6_BotNeg1", "", 200, 0., 1.2 * Eb, 200, -50., 50.);

    TH2D *h_dY_Y_WithL6_TopPos1 = new TH2D("h_dY_Y_WithL6_TopPos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_WithL6_BotPos1 = new TH2D("h_dY_Y_WithL6_BotPos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_NoL6_TopPos1 = new TH2D("h_dY_Y_NoL6_TopPos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_NoL6_BotPos1 = new TH2D("h_dY_Y_NoL6_BotPos1", "", 200, -100., 100., 200, -50., 50.);

    TH2D *h_dY_Y_WithL6_SinglePos1 = new TH2D("h_dY_Y_WithL6_SinglePos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_WithL6_MultiHitPos1 = new TH2D("h_dY_Y_WithL6_MultiHitPos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_NoL6_SinglePos1 = new TH2D("h_dY_Y_NoL6_SinglePos1", "", 200, -100., 100., 200, -50., 50.);
    TH2D *h_dY_Y_NoL6_MultiHitPos1 = new TH2D("h_dY_Y_NoL6_MultiHitPos1", "", 200, -100., 100., 200, -50., 50.);

    TH2D *h_tmp_cl_YXc1 = new TH2D("h_tmp_cl_YXc1", "", 200, -300, 370., 200, -90., 90.);
    TH2D *h_tmp_cl_YXc2 = new TH2D("h_tmp_cl_YXc2", "", 200, -300, 370., 200, -90., 90.);

    TH2D *h_L6_Yxc_pos1 = new TH2D("h_L6_Yxc_pos1", "", 200, -150., 150., 200, -80., 80.);
    TH2D *h_L5_Yxc_pos1 = new TH2D("h_L5_Yxc_pos1", "", 200, -150., 150., 200, -80., 80.);


    TH1D * h_dY_Top_pos_Single1_WithL6_[5];
    TH1D * h_dY_Top_pos_MultiHit1_WithL6_[5];
    TH1D * h_dY_Bot_pos_Single1_WithL6_[5];
    TH1D * h_dY_Bot_pos_MultiHit1_WithL6_[5];
    TH1D * h_dY_Top_pos_Single1_NoL6_[5];
    TH1D * h_dY_Top_pos_MultiHit1_NoL6_[5];
    TH1D * h_dY_Bot_pos_Single1_NoL6_[5];
    TH1D * h_dY_Bot_pos_MultiHit1_NoL6_[5];

    TH1D * h_dY_Top_pos1_WithL6_[5];
    TH1D * h_dY_Bot_pos1_WithL6_[5];
    TH1D * h_dY_Top_pos1_NoL6_[5];
    TH1D * h_dY_Bot_pos1_NoL6_[5];

    for (int i = 0; i < 5; i++) {
        h_dY_Top_pos1_WithL6_[i] = new TH1D(Form("h_dY_Top_pos1_WithL6_%d", i), "", 200, -25., 25.);
        h_dY_Bot_pos1_WithL6_[i] = new TH1D(Form("h_dY_Bot_pos1_WithL6_%d", i), "", 200, -25., 25.);
        h_dY_Top_pos1_NoL6_[i] = new TH1D(Form("h_dY_Top_pos1_NoL6_%d", i), "", 200, -25., 25.);
        h_dY_Bot_pos1_NoL6_[i] = new TH1D(Form("h_dY_Bot_pos1_NoL6_%d", i), "", 200, -25., 25.);

        h_dY_Top_pos_Single1_WithL6_[i] = new TH1D(Form("h_dY_Top_pos_Single1_WithL6_%d", i), "", 200, -25, 25.);
        h_dY_Top_pos_MultiHit1_WithL6_[i] = new TH1D(Form("h_dY_Top_pos_MultiHit1_WithL6_%d", i), "", 200, -25, 25.);
        h_dY_Bot_pos_Single1_WithL6_[i] = new TH1D(Form("h_dY_Bot_pos_Single1_WithL6_%d", i), "", 200, -25, 25.);
        h_dY_Bot_pos_MultiHit1_WithL6_[i] = new TH1D(Form("h_dY_Bot_pos_MultiHit1_WithL6_%d", i), "", 200, -25, 25.);
        h_dY_Top_pos_Single1_NoL6_[i] = new TH1D(Form("h_dY_Top_pos_Single1_NoL6_%d", i), "", 200, -25, 25.);
        h_dY_Top_pos_MultiHit1_NoL6_[i] = new TH1D(Form("h_dY_Top_pos_MultiHit1_NoL6_%d", i), "", 200, -25, 25.);
        h_dY_Bot_pos_Single1_NoL6_[i] = new TH1D(Form("h_dY_Bot_pos_Single1_NoL6_%d", i), "", 200, -25, 25.);
        h_dY_Bot_pos_MultiHit1_NoL6_[i] = new TH1D(Form("h_dY_Bot_pos_MultiHit1_NoL6_%d", i), "", 200, -25, 25.);
    }


    TH2D *h_trkCl_dt_P_Top_Pos_6hit = new TH2D("h_trkCl_dt_P_Top_Pos_6hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Top_Pos_5hit = new TH2D("h_trkCl_dt_P_Top_Pos_5hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Bot_Pos_6hit = new TH2D("h_trkCl_dt_P_Bot_Pos_6hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Bot_Pos_5hit = new TH2D("h_trkCl_dt_P_Bot_Pos_5hit", "", 200, 0., 2.5, 200, -15., 15.);

    TH2D *h_trkCl_dt_P_Top_Neg_6hit = new TH2D("h_trkCl_dt_P_Top_Neg_6hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Top_Neg_5hit = new TH2D("h_trkCl_dt_P_Top_Neg_5hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Bot_Neg_6hit = new TH2D("h_trkCl_dt_P_Bot_Neg_6hit", "", 200, 0., 2.5, 200, -15., 15.);
    TH2D *h_trkCl_dt_P_Bot_Neg_5hit = new TH2D("h_trkCl_dt_P_Bot_Neg_5hit", "", 200, 0., 2.5, 200, -15., 15.);


    TH2D *h_trkCl_dt_P_Top = new TH2D("h_trkCl_dt_P_Top", "", 100, 0., 2.5, 100, -10., 10.);
    TH2D *h_trkCl_dt_P_Bot = new TH2D("h_trkCl_dt_P_Bot", "", 100, 0., 2.5, 100, -10., 10.);
    
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


    int nev = tr1->GetEntries();

    cout << "Number of events is " << nev << endl;

    nev = 2000;
    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }

        // This needs to be called at the beginning of every event
        ResetEventFlags();

        int n_cl = ev->getNumberOfEcalClusters();

        if (!ev->isPair1Trigger() && isData) {
            continue;
        }


        int nTC_V0 = ev->getNumberOfParticles(HpsParticle::TC_V0_CANDIDATE);


        for (int iv0 = 0; iv0 < nTC_V0; iv0++) {

            HpsParticle *cur_v0 = ev->getParticle(HpsParticle::TC_V0_CANDIDATE, iv0);

            if (cur_v0->getParticles()->GetSize() != 2) {
                cout << "# of v0 is " << cur_v0->getParticles()->GetSize() << endl;
                cout << "# of v0 daughters is not 2.    Exiting!" << endl;
                exit(1);
            }

            if (((HpsParticle*) cur_v0->getParticles()->At(0))->getCharge()*((HpsParticle*) cur_v0->getParticles()->At(1))->getCharge() >= 0) {

                cout << "Charges are    " << ((HpsParticle*) cur_v0->getParticles()->At(0)) << "   and   " << ((HpsParticle*) cur_v0->getParticles()->At(1)) << endl;
                cout << "v0 pairs should have opposite sign charges.    Exiting" << endl;
                exit(1);
            }


            HpsParticle *em;
            HpsParticle *ep;
            //HpsParticle *part0 = ((HpsParticle*)cur_v0->getParticles()->At(0)) ;

            if (((HpsParticle*) cur_v0->getParticles()->At(0))->getCharge() < 0) {
                em = (HpsParticle*) cur_v0->getParticles()->At(0);
                ep = (HpsParticle*) cur_v0->getParticles()->At(1);
            } else if (((HpsParticle*) cur_v0->getParticles()->At(0))->getCharge() > 0) {
                em = (HpsParticle*) cur_v0->getParticles()->At(1);
                ep = (HpsParticle*) cur_v0->getParticles()->At(0);
            }


            // ======== Getting Electron related variables ========
            bool emHasCl = false;
            vector<double> pos_cl_em{-9999, -9999, -9999};
            double t_cl_em = -9999;
            bool is_neg_ClustIntime = false;
            double E_cl_em = -9999;

            if (em->getClusters()->GetSize() > 0) {
                EcalCluster* cl_em = (EcalCluster*) em->getClusters()->At(0);
                pos_cl_em = cl_em->getPosition();
                t_cl_em = cl_em->getClusterTime();

                E_cl_em = cl_em->getEnergy();

                is_neg_ClustIntime = IsIntimeClusterCandidate(cl_em);

                emHasCl = true;
            }

            GblTrack *trk_em = (GblTrack*) em->getTracks()->At(0);
            vector<double> pos_trk_em = trk_em->getPositionAtEcal();
            vector<double> P_trk_em = trk_em->getMomentum();
            double P_em = sqrt(P_trk_em.at(0) * P_trk_em.at(0) + P_trk_em.at(1) * P_trk_em.at(1) + P_trk_em.at(2) * P_trk_em.at(2));

            double chi2_em = trk_em->getChi2();
            int n_emHits = trk_em->getSvtHits()->GetSize();
            int NDF_em = 2 * n_emHits - 5;
            double d0_em = trk_em->getD0();




            // ======== Getting Positron related variables ========
            vector<double> pos_cl_ep{-9999, -9999, -9999, -9999};
            bool epHasCl = false;
            double t_cl_ep = -9999;
            bool is_pos_ClustIntime = false;
            double E_cl_ep = -9999;

            if (ep->getClusters()->GetSize() > 0) {
                EcalCluster *cl_ep = (EcalCluster*) ep->getClusters()->At(0);
                pos_cl_ep = cl_ep->getPosition();
                t_cl_ep = cl_ep->getClusterTime();
                E_cl_ep = cl_ep->getEnergy();
                is_pos_ClustIntime = IsIntimeClusterCandidate(cl_ep);
                epHasCl = true;
            }

            if (!(is_neg_ClustIntime && is_pos_ClustIntime)) {
                continue;
            }

            GblTrack *trk_ep = (GblTrack*) ep->getTracks()->At(0);
            vector<double> pos_trk_ep = trk_ep->getPositionAtEcal();
            vector<double> P_trk_ep = trk_ep->getMomentum();
            double P_ep = sqrt(P_trk_ep.at(0) * P_trk_ep.at(0) + P_trk_ep.at(1) * P_trk_ep.at(1) + P_trk_ep.at(2) * P_trk_ep.at(2));

            double chi2_ep = trk_ep->getChi2();
            int n_epHits = trk_ep->getSvtHits()->GetSize();
            int NDF_ep = 2 * n_epHits - 5;
            double d0_ep = trk_ep->getD0();

            if (pos_cl_em.at(1) > 0) {

                h_dX_P_TopNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                h_dX_P_BotPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                h_dY_P_TopNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                h_dY_P_BotPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));

                int seedY = ((EcalCluster*) ep->getClusters()->At(0))->getSeed()->getYCrystalIndex();
                
                h_trkCl_dt_P_Top->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                h_trkCl_dt_P_Bot->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);

                if (trk_ep->getSvtHits()->GetSize() == 6) {
                    h_trkCl_dt_P_Bot_Pos_6hit->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);
                }else{
                    h_trkCl_dt_P_Bot_Pos_5hit->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);
                }

                if (trk_em->getSvtHits()->GetSize() == 6) {
                    h_trkCl_dt_P_Top_Neg_6hit->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                }else{
                    h_trkCl_dt_P_Top_Neg_5hit->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                }


                if (HasL6Hit(trk_ep)) {
                    h_dX_P_WithL6_BotPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                    h_dY_P_WithL6_BotPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    h_dY_Y_WithL6_BotPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    h_L6_Yxc_pos1->Fill(GetHitCoordAtLayer(trk_ep, 6).at(0), GetHitCoordAtLayer(trk_ep, 6).at(1));

                    h_dY_Bot_pos1_WithL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));


                    if (GetVerticalCrystalls((EcalCluster*) ep->getClusters()->At(0)).size() > 1) {
                        h_dY_Y_WithL6_MultiHitPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Bot_pos_MultiHit1_WithL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    } else {
                        h_dY_Bot_pos_Single1_WithL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Y_WithL6_SinglePos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    }

                } else {
                    h_dX_P_NoL6_BotPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                    h_dY_P_NoL6_BotPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    h_dY_Y_NoL6_BotPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    h_L5_Yxc_pos1->Fill(GetHitCoordAtLayer(trk_ep, 5).at(0), GetHitCoordAtLayer(trk_ep, 5).at(1));
                    h_dY_Bot_pos1_NoL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    if (GetVerticalCrystalls((EcalCluster*) ep->getClusters()->At(0)).size() > 1) {
                        h_dY_Y_NoL6_MultiHitPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Bot_pos_MultiHit1_NoL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    } else {
                        h_dY_Y_NoL6_SinglePos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Bot_pos_Single1_NoL6_[-seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    }

                    if ((pos_cl_ep.at(1) - pos_trk_ep.at(1) > -10.) && (pos_cl_ep.at(1) - pos_trk_ep.at(1) < -8.) && P_ep > 0.9) {
                        h_tmp_cl_YXc1->Fill(pos_cl_ep.at(0), pos_cl_ep.at(1));
                    } else {
                        h_tmp_cl_YXc2->Fill(pos_cl_ep.at(0), pos_cl_ep.at(1));
                    }
                }

                if (HasL6Hit(trk_em)) {
                    h_dX_P_WithL6_TopNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                    h_dY_P_WithL6_TopNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                } else {
                    h_dX_P_NoL6_TopNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                    h_dY_P_NoL6_TopNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                }

            } else {
                h_dX_P_BotNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                h_dX_P_TopPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                h_dY_P_BotNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                h_dY_P_TopPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));

                int seedY = ((EcalCluster*) ep->getClusters()->At(0))->getSeed()->getYCrystalIndex();


                h_trkCl_dt_P_Top->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);
                h_trkCl_dt_P_Bot->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                                
                if (trk_ep->getSvtHits()->GetSize() == 6) {
                    h_trkCl_dt_P_Top_Pos_6hit->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);
                }else{
                    h_trkCl_dt_P_Top_Pos_5hit->Fill(P_ep, t_cl_ep - trk_ep->getTrackTime() - CL_trk_time_Offset);
                }

                if (trk_em->getSvtHits()->GetSize() == 6) {
                    h_trkCl_dt_P_Bot_Neg_6hit->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                }else{
                    h_trkCl_dt_P_Bot_Neg_5hit->Fill(P_em, t_cl_em - trk_em->getTrackTime() - CL_trk_time_Offset);
                }
                
                
                
                if (HasL6Hit(trk_ep)) {
                    h_dX_P_WithL6_TopPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                    h_dY_P_WithL6_TopPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    h_dY_Y_WithL6_TopPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    GetHitCoordAtLayer(trk_ep, 6);

                    h_dY_Top_pos1_WithL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    h_L6_Yxc_pos1->Fill(GetHitCoordAtLayer(trk_ep, 6).at(0), GetHitCoordAtLayer(trk_ep, 6).at(1));

                    if (GetVerticalCrystalls((EcalCluster*) ep->getClusters()->At(0)).size() > 1) {
                        h_dY_Y_WithL6_MultiHitPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Top_pos_MultiHit1_WithL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    } else {
                        h_dY_Y_WithL6_SinglePos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Top_pos_Single1_WithL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    }


                } else {
                    h_dX_P_NoL6_TopPos1->Fill(P_ep, pos_cl_ep.at(0) - pos_trk_ep.at(0));
                    h_dY_P_NoL6_TopPos1->Fill(P_ep, pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    h_dY_Y_NoL6_TopPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    h_L5_Yxc_pos1->Fill(GetHitCoordAtLayer(trk_ep, 5).at(0), GetHitCoordAtLayer(trk_ep, 5).at(1));
                    h_dY_Top_pos1_NoL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));

                    if (GetVerticalCrystalls((EcalCluster*) ep->getClusters()->At(0)).size() > 1) {
                        h_dY_Y_NoL6_MultiHitPos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Top_pos_MultiHit1_NoL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    } else {
                        h_dY_Y_NoL6_SinglePos1->Fill(pos_trk_ep.at(1), pos_cl_ep.at(1) - pos_trk_ep.at(1));
                        h_dY_Top_pos_Single1_NoL6_[seedY - 1]->Fill(pos_cl_ep.at(1) - pos_trk_ep.at(1));
                    }
                }

                if (HasL6Hit(trk_em)) {
                    h_dX_P_WithL6_BotNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                    h_dY_P_WithL6_BotNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                } else {
                    h_dX_P_NoL6_BotNeg1->Fill(P_em, pos_cl_em.at(0) - pos_trk_em.at(0));
                    h_dY_P_NoL6_BotNeg1->Fill(P_em, pos_cl_em.at(1) - pos_trk_em.at(1));
                }


            }




        }


    }



    gDirectory->Write();

    return 0;
}