/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoellerAnalysis.cc
 * Author: rafopar
 *
 * Created on October 31, 2019, 2:06 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include "MoellerSettings.h"
#include "MoellerSettings.C"

#include <iostream>

#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {


    if (argc >= 2) {

        dataSet = argv[1];

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./EventSelection.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }

    InitSettings(dataSet);


    TH1D *h_nTCMoellers = new TH1D("h_NTCMoellers", "", 11, -0.5, 10.5);
    TH1D *h_MTCMoeller1 = new TH1D("h_MTCMoeller1", "", 200, 0.02, 0.12);
    TH1D *h_MTCMoeller2 = new TH1D("h_MTCMoeller2", "", 200, 0.02, 0.12);
    TH1D *h_MTCMoeller3 = new TH1D("h_MTCMoeller3", "", 200, 0.02, 0.12);
    TH1D *h_MTCMoeller4 = new TH1D("h_MTCMoeller4", "", 200, 0.02, 0.12);
    TH1D *h_MoellerQualifyStat1 = new TH1D("h_MoellerQualifyStat", "", 121, -0.5, 120.5);
    TH1D *h_vz_Moeller1 = new TH1D("h_vz_Moeller1", "", 200, -5., -3.5);
    TH1D *h_vz_Moeller2 = new TH1D("h_vz_Moeller2", "", 200, -5., -3.5);
    TH1D *h_tvM_charge1 = new TH1D("h_tvM_charge1", "", 7, -3.5, 3.5);
    TH1D *h_tvM_charge2 = new TH1D("h_tvM_charge2", "", 7, -3.5, 3.5);

    TH1D *h_VertChi2_1 = new TH1D("h_VertChi2_1", "", 200, 0., 100.);
    TH1D *h_VertChi2_2 = new TH1D("h_VertChi2_2", "", 200, 0., 100.);
    TH1D *h_VertChi2_3 = new TH1D("h_VertChi2_3", "", 200, 0., 100.);
    TH1D *h_VertChi2_4 = new TH1D("h_VertChi2_4", "", 200, 0., 100.);

    TH1D *h_ToptrkChiNDF1 = new TH1D("h_ToptrkChiNDF1", "", 200, 0., 14.);
    TH1D *h_BottrkChiNDF1 = new TH1D("h_BottrkChiNDF1", "", 200, 0., 14.);

    TH2D *h_phi_TopBot1 = new TH2D("h_phi_TopBot1", "", 200, -180., 0., 200, 0., 180.);
    TH2D *h_phi_TopBot2 = new TH2D("h_phi_TopBot2", "", 200, -180., 0., 200, 0., 180.);
    TH2D *h_phi_TopBot3 = new TH2D("h_phi_TopBot3", "", 200, -180., 0., 200, 0., 180.);
    TH2D *h_phi_TopBot4 = new TH2D("h_phi_TopBot4", "", 200, -180., 0., 200, 0., 180.);
    TH2D *h_phi_TopBot5 = new TH2D("h_phi_TopBot5", "", 200, -180., 0., 200, 0., 180.);

    TH1D *h_dPhi1 = new TH1D("h_dPhi1", "", 200, 140., 220.);
    TH1D *h_dPhi2 = new TH1D("h_dPhi2", "", 200, 140., 220.);
    TH1D *h_dPhi3 = new TH1D("h_dPhi3", "", 200, 140., 220.);
    TH1D *h_dPhi4 = new TH1D("h_dPhi4", "", 200, 140., 220.);
    TH1D *h_dPhi5 = new TH1D("h_dPhi5", "", 200, 140., 220.);

    TH2D *h_cl_dT_Psum1 = new TH2D("h_cl_dT_Psum1", "", 200, 0.5, 1.3 * Eb, 200, -5.5, 5.5);
    TH2D *h_cl_dT_Psum2 = new TH2D("h_cl_dT_Psum2", "", 200, 0.5, 1.3 * Eb, 200, -5.5, 5.5);
    TH2D *h_P_TopBot1 = new TH2D("h_P_TopBot1", "", 200, 0.1, 1.2 * Eb, 200, 0.1, 1.2 * Eb);
    TH2D *h_P_TopBot2 = new TH2D("h_P_TopBot2", "", 200, 0.1, 1.2 * Eb, 200, 0.1, 1.2 * Eb);
    TH2D *h_Top_TrCldT1 = new TH2D("h_Top_TrCldT1", "", 200, 0.2, 1.2 * Eb, 200, -5.5, 5.5);
    TH2D *h_Bot_TrCldT1 = new TH2D("h_Bot_TrCldT1", "", 200, 0.2, 1.2 * Eb, 200, -5.5, 5.5);

    TH2D *h_PsumPdiff1 = new TH2D("h_PsumPdiff1", "", 200, 1.8, 2.8, 200, -2., 2.);
    TH2D *h_PsumPdiff2 = new TH2D("h_PsumPdiff2", "", 200, 1.8, 2.8, 200, -2., 2.);
    TH2D *h_PsumPdiff3 = new TH2D("h_PsumPdiff3", "", 200, 1.8, 2.8, 200, -2., 2.);
    TH2D *h_PsumPdiff4 = new TH2D("h_PsumPdiff4", "", 200, 1.8, 2.8, 200, -2., 2.);

    TH2D *h_Trk_dT_Psum1 = new TH2D("h_Trk_dT_Psum1", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);
    TH2D *h_Trk_dT_Psum2 = new TH2D("h_Trk_dT_Psum2", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);
    TH2D *h_Trk_dT_Psum3 = new TH2D("h_Trk_dT_Psum3", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);
    TH2D *h_Trk_dT_Psum4 = new TH2D("h_Trk_dT_Psum4", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);
    TH2D *h_Trk_dT_Psum5 = new TH2D("h_Trk_dT_Psum5", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);
    TH2D *h_Trk_dT_Psum6 = new TH2D("h_Trk_dT_Psum6", "", 200, 0.5, 1.3 * Eb, 200, -9., 9.);

    TH2D *h_dX_P_Top1 = new TH2D("h_dX_P_Top1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_Top2 = new TH2D("h_dX_P_Top2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_Top3 = new TH2D("h_dX_P_Top3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_Bot1 = new TH2D("h_dX_P_Bot1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_Bot2 = new TH2D("h_dX_P_Bot2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_Bot3 = new TH2D("h_dX_P_Bot3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);

    TH2D *h_dX_P_InHole_Top1 = new TH2D("h_dX_P_InHole_Top1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InHole_Top2 = new TH2D("h_dX_P_InHole_Top2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InHole_Top3 = new TH2D("h_dX_P_InHole_Top3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InHole_Bot1 = new TH2D("h_dX_P_InHole_Bot1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InHole_Bot2 = new TH2D("h_dX_P_InHole_Bot2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InHole_Bot3 = new TH2D("h_dX_P_InHole_Bot3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);

    TH2D *h_dX_P_InECal_Top1 = new TH2D("h_dX_P_InECal_Top1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InECal_Top2 = new TH2D("h_dX_P_InECal_Top2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InECal_Top3 = new TH2D("h_dX_P_InECal_Top3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InECal_Bot1 = new TH2D("h_dX_P_InECal_Bot1", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InECal_Bot2 = new TH2D("h_dX_P_InECal_Bot2", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);
    TH2D *h_dX_P_InECal_Bot3 = new TH2D("h_dX_P_InECal_Bot3", "", 200, 0.2, 0.95 * Eb, 200, -50., 50.);

    TH1D *h_TopMatchChi2_1 = new TH1D("h_TopMatchChi2_1", "", 200, 0., 14.);
    TH1D *h_TopMatchChi2_2 = new TH1D("h_TopMatchChi2_2", "", 200, 0., 14.);
    TH1D *h_TopMatchChi2_3 = new TH1D("h_TopMatchChi2_3", "", 200, 0., 14.);
    TH1D *h_TopMatchChi2_4 = new TH1D("h_TopMatchChi2_4", "", 200, 0., 14.);
    TH1D *h_BotMatchChi2_1 = new TH1D("h_BotMatchChi2_1", "", 200, 0., 14.);
    TH1D *h_BotMatchChi2_2 = new TH1D("h_BotMatchChi2_2", "", 200, 0., 14.);
    TH1D *h_BotMatchChi2_3 = new TH1D("h_BotMatchChi2_3", "", 200, 0., 14.);
    TH1D *h_BotMatchChi2_4 = new TH1D("h_BotMatchChi2_4", "", 200, 0., 14.);

    TH2D *h_TopBotMatchCh2_3 = new TH2D("h_TopBotMatchCh2_3", "", 200, 0., 15., 200, 0., 15.);

    TH2D *h_X_TopBot1 = new TH2D("h_X_TopBot1", "", 200, -150., 0., 200, -150., 0.);
    TH2D *h_X_TopBot2 = new TH2D("h_X_TopBot2", "", 200, -150., 0., 200, -150., 0.);
    TH2D *h_X_TopBot3 = new TH2D("h_X_TopBot3", "", 200, -150., 0., 200, -150., 0.);
    TH2D *h_X_TopBot4 = new TH2D("h_X_TopBot4", "", 200, -150., 0., 200, -150., 0.);

    TH2D *h_Y_TopBot1 = new TH2D("h_Y_TopBot1", "", 200, -90., 0., 200, 0., 90.);
    TH2D *h_Y_TopBot2 = new TH2D("h_Y_TopBot2", "", 200, -90., 0., 200, 0., 90.);
    TH2D *h_Y_TopBot3 = new TH2D("h_Y_TopBot3", "", 200, -90., 0., 200, 0., 90.);
    TH2D *h_Y_TopBot4 = new TH2D("h_Y_TopBot4", "", 200, -90., 0., 200, 0., 90.);

    TH2D *h_Chi2NDF_TCM1 = new TH2D("h_Chi2NDF_TCM1", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM2 = new TH2D("h_Chi2NDF_TCM2", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM3 = new TH2D("h_Chi2NDF_TCM3", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM4 = new TH2D("h_Chi2NDF_TCM4", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM5 = new TH2D("h_Chi2NDF_TCM5", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM6 = new TH2D("h_Chi2NDF_TCM6", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM_Top6 = new TH2D("h_Chi2NDF_TCM_Top6", "", 200, 0.02, 0.12, 200, 0., 12.);
    TH2D *h_Chi2NDF_TCM_Bot6 = new TH2D("h_Chi2NDF_TCM_Bot6", "", 200, 0.02, 0.12, 200, 0., 12.);

    TH2D *h_tr_yxc_1 = new TH2D("h_tr_yxc_1", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_tr_yxc_2 = new TH2D("h_tr_yxc_2", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_tr_yxc_3 = new TH2D("h_tr_yxc_3", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_tr_yxc_4 = new TH2D("h_tr_yxc_4", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_tr_yxc_5 = new TH2D("h_tr_yxc_5", "", 200, -300., 270, 200, -90., 90.);

    TH2D *h_cl_yxc_1 = new TH2D("h_cl_yxc_1", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_cl_yxc_2 = new TH2D("h_cl_yxc_2", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_cl_yxc_3 = new TH2D("h_cl_yxc_3", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_cl_yxc_4 = new TH2D("h_cl_yxc_4", "", 200, -300., 270, 200, -90., 90.);
    TH2D *h_cl_yxc_5 = new TH2D("h_cl_yxc_5", "", 200, -300., 270, 200, -90., 90.);

    int nev = tr1->GetEntries();
    //nev = 1000000;

    cout << "Number of events is " << nev << endl;

    for (int ientry = 0; ientry < nev; ientry++) {
        tr1->GetEntry(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }

        ResetEventFlags();


        HpsParticle::ParticleType MlrPart = HpsParticle::TC_MOLLER_CANDIDATE;
        
        int nTCMoellers = ev->getNumberOfParticles(MlrPart);

        h_nTCMoellers->Fill(nTCMoellers);


        for (int iTCM = 0; iTCM < nTCMoellers; iTCM++) {

            ResetConstrainedMollerFlags();

            HpsParticle *cur_tcM = ev->getParticle(MlrPart, iTCM);

            int qualifyStat = DoesQualifyMoeller(cur_tcM);

            if (qualifyStat != 0) {
                continue;
            }


            h_MoellerQualifyStat1->Fill(qualifyStat);


            double M_TCM = cur_tcM->getMass();
            double vz_TCM = cur_tcM->getVertexPosition().at(2);

            double VertexChi2 = cur_tcM->getVertexFitChi2();

            h_VertChi2_1->Fill(VertexChi2);

            h_MTCMoeller1->Fill(M_TCM);

            h_vz_Moeller1->Fill(vz_TCM);


            if (((GblTrack*) ((HpsParticle*) cur_tcM->getParticles()->At(0))->getTracks()->At(0))->getPositionAtEcal().at(1) > 0) {
                Topem = (HpsParticle*) cur_tcM->getParticles()->At(0);
                Botem = (HpsParticle*) cur_tcM->getParticles()->At(1);

            } else {
                Topem = (HpsParticle*) cur_tcM->getParticles()->At(1);
                Botem = (HpsParticle*) cur_tcM->getParticles()->At(0);
            }

            topChi2 = ((GblTrack*) Topem->getTracks()->At(0))->getChi2();
            botChi2 = ((GblTrack*) Botem->getTracks()->At(0))->getChi2();

            int NHitsTop = ((GblTrack*) Topem->getTracks()->At(0))->getSvtHits()->GetSize();
            int NHitsBot = ((GblTrack*) Botem->getTracks()->At(0))->getSvtHits()->GetSize();

            double topChi2NDF = topChi2 / (2 * NHitsTop - 5.);
            double botChi2NDF = botChi2 / (2 * NHitsBot - 5.);

            double chi2NDF_Sum = (topChi2 + botChi2) / (2 * (NHitsTop + NHitsBot) - 10.);

            HasTopL1 = HasL1Hit((GblTrack*) Topem->getTracks()->At(0));
            HasBotL1 = HasL1Hit((GblTrack*) Botem->getTracks()->At(0));


            h_Chi2NDF_TCM1->Fill(M_TCM, chi2NDF_Sum);

            h_ToptrkChiNDF1->Fill(topChi2NDF);
            h_BottrkChiNDF1->Fill(botChi2NDF);

            double tTopCl = 9999.;
            double tBotCl = 9999.;
            if (Topem->getClusters()->GetSize() > 0) {
                tTopCl = ((EcalCluster*) Topem->getClusters()->At(0))->getClusterTime();
            }
            if (Botem->getClusters()->GetSize() > 0) {
                tBotCl = ((EcalCluster*) Botem->getClusters()->At(0))->getClusterTime();
            }

            double MatchingChi2Top = Topem->getGoodnessOfPID();
            double MatchingChi2Bot = Botem->getGoodnessOfPID();
            double cl_dT = tTopCl - tBotCl;
            double P_TCM = GetMagnitude(cur_tcM->getMomentum());
            double tTopTr = ((GblTrack*) Topem->getTracks()->At(0))->getTrackTime();
            double tBotTr = ((GblTrack*) Botem->getTracks()->At(0))->getTrackTime();
            double dT_ClTrk_Top = tTopCl - tTopTr - CL_trk_time_Offset;
            double dT_ClTrk_Bot = tBotCl - tBotTr - CL_trk_time_Offset;

            vector<double> P_Top_emVect = ((GblTrack*) Topem->getTracks()->At(0))->getMomentum();
            vector<double> P_Bot_emVect = ((GblTrack*) Botem->getTracks()->At(0))->getMomentum();

            double Px_TopRot = P_Top_emVect.at(0) * cos(phi_rot) - P_Top_emVect.at(2) * sin(phi_rot);
            double Px_BotRot = P_Bot_emVect.at(0) * cos(phi_rot) - P_Bot_emVect.at(2) * sin(phi_rot);

            double phiTop = atan2(P_Top_emVect.at(1), Px_TopRot) * TMath::RadToDeg();
            double phiBot = atan2(P_Bot_emVect.at(1), Px_BotRot) * TMath::RadToDeg();
            //            double phiTop = atan2(P_Top_emVect.at(1), P_Top_emVect.at(0)) * TMath::RadToDeg();
            //            double phiBot = atan2(P_Bot_emVect.at(1), P_Bot_emVect.at(0)) * TMath::RadToDeg();

            h_phi_TopBot1->Fill(phiBot, phiTop);
            h_dPhi1->Fill(phiTop - phiBot);

            double P_Top = GetMagnitude(P_Top_emVect);
            double P_Bot = GetMagnitude(P_Bot_emVect);
            double P_Diff = P_Top - P_Bot;

            // ====================================================================================
            //    In 2016 data, It is quite rare to have both Moeller electrons to hit the ECal
            //    That is why we will not require cluster to be matched with track
            // ====================================================================================

            vector<double> pos_TopCl{9999., 9999., 9999.};
            vector<double> pos_BotCl{9999., 9999., 9999.};

            if (Topem->getClusters()->GetSize() > 0) {
                pos_TopCl = ((EcalCluster*) Topem->getClusters()->At(0))->getPosition();
            }

            if (Botem->getClusters()->GetSize() > 0) {
                pos_BotCl = ((EcalCluster*) Botem->getClusters()->At(0))->getPosition();
            }

            //cout<<Topem->getClusters()->GetSize()<<"     "<<Botem->getClusters()->GetSize()<<endl;

            double xTopCl = pos_TopCl.at(0);
            double xBotCl = pos_BotCl.at(0);
            double yTopCl = pos_TopCl.at(1);
            double yBotCl = pos_BotCl.at(1);

            vector<double> pos_TopTrk = ((GblTrack*) Topem->getTracks()->At(0))->getPositionAtEcal();
            vector<double> pos_BotTrk = ((GblTrack*) Botem->getTracks()->At(0))->getPositionAtEcal();

            double yTopTr = pos_TopTrk.at(1);
            double xTopTr = pos_TopTrk.at(0);
            double yBotTr = pos_BotTrk.at(1);
            double xBotTr = pos_BotTrk.at(0);

            TopTrkFiducial = TrackFiducial(xTopTr, yTopTr);
            BotTrkFiducial = TrackFiducial(xBotTr, yBotTr);

            TopTrkInHole = TrackInHole(xTopTr, yTopTr);
            BotTrkInHole = TrackInHole(xBotTr, yBotTr);

            double tr_dT = tTopTr - tBotTr;

            double dX_Top = pos_TopCl.at(0) - pos_TopTrk.at(0);
            double dX_Bot = pos_BotCl.at(0) - pos_BotTrk.at(0);

            h_tr_yxc_1->Fill(xTopTr, yTopTr);
            h_tr_yxc_1->Fill(xBotTr, yBotTr);
            h_cl_yxc_1->Fill(xTopCl, yTopCl);
            h_cl_yxc_1->Fill(xBotCl, yBotCl);


            if (TopTrkInHole) {
                h_dX_P_InHole_Top1->Fill(P_Top, dX_Top);
            } else {
                h_dX_P_InECal_Top1->Fill(P_Top, dX_Top);
            }

            if (BotTrkInHole) {
                h_dX_P_InHole_Bot1->Fill(P_Bot, dX_Bot);
            } else {
                h_dX_P_InECal_Bot1->Fill(P_Bot, dX_Bot);
            }

            h_cl_dT_Psum1->Fill(P_TCM, cl_dT);
            h_P_TopBot1->Fill(P_Bot, P_Top);

            h_Trk_dT_Psum1->Fill(P_TCM, tr_dT);

            h_Top_TrCldT1->Fill(P_Top, dT_ClTrk_Top);
            h_Bot_TrCldT1->Fill(P_Bot, dT_ClTrk_Bot);


            h_dX_P_Top1->Fill(P_Top, dX_Top);
            h_dX_P_Bot1->Fill(P_Bot, dX_Bot);

            h_X_TopBot1->Fill(xBotCl, xTopCl);
            h_Y_TopBot1->Fill(yBotCl, yTopCl);

            h_TopMatchChi2_1->Fill(MatchingChi2Top);
            h_BotMatchChi2_1->Fill(MatchingChi2Bot);

            h_PsumPdiff1->Fill(P_TCM, P_Top - P_Bot);


            if ((MatchingChi2Top - MatchingChi2Median) * (MatchingChi2Bot - MatchingChi2Median) < 0.
                    && TMath::Min(MatchingChi2Top, MatchingChi2Bot) < MatchingChi2Best) {

                h_PsumPdiff2->Fill(P_TCM, P_Top - P_Bot);

                if ((P_Diff > PDiffLowMin && P_Diff < PDiffLowMax) || (P_Diff > PDiffHighMin && P_Diff < PDiffHighMax)) {
                    h_Trk_dT_Psum5->Fill(P_TCM, tr_dT);
                }

                if (tr_dT > tr_dT_Min && tr_dT < tr_dT_Max) {

                    h_PsumPdiff3->Fill(P_TCM, P_Top - P_Bot);
                    if ((P_Diff > PDiffLowMin && P_Diff < PDiffLowMax) || (P_Diff > PDiffHighMin && P_Diff < PDiffHighMax)) {
                        h_cl_dT_Psum2->Fill(P_TCM, cl_dT);
                        h_Trk_dT_Psum6->Fill(P_TCM, tr_dT);
                    }
                }
            }


            if (P_TCM > PSumMin && P_TCM < PSumMax /*&& cl_dT > -1.5 && cl_dT < 1.5 */) {

                //cout<<"xBotCl = "<<xBotCl<<"      xTopCl = "<<xTopCl<<endl;

                h_MTCMoeller2->Fill(M_TCM);
                h_P_TopBot2->Fill(P_Bot, P_Top);
                h_dX_P_Top2->Fill(P_Top, dX_Top);
                h_dX_P_Bot2->Fill(P_Bot, dX_Bot);
                if (TopTrkInHole) {
                    h_dX_P_InHole_Top2->Fill(P_Top, dX_Top);
                } else {
                    h_dX_P_InECal_Top2->Fill(P_Top, dX_Top);
                }
                if (BotTrkInHole) {
                    h_dX_P_InHole_Bot2->Fill(P_Bot, dX_Bot);
                } else {
                    h_dX_P_InECal_Bot2->Fill(P_Bot, dX_Bot);
                }
                h_X_TopBot2->Fill(xBotCl, xTopCl);
                h_Y_TopBot2->Fill(yBotCl, yTopCl);
                h_phi_TopBot2->Fill(phiBot, phiTop);
                h_dPhi2->Fill(phiTop - phiBot);
                h_VertChi2_2->Fill(VertexChi2);
                h_Trk_dT_Psum2->Fill(P_TCM, tr_dT);
                h_TopMatchChi2_2->Fill(MatchingChi2Top);
                h_BotMatchChi2_2->Fill(MatchingChi2Bot);
                h_Chi2NDF_TCM2->Fill(M_TCM, chi2NDF_Sum);
                h_tr_yxc_2->Fill(xTopTr, yTopTr);
                h_tr_yxc_2->Fill(xBotTr, yBotTr);
                h_cl_yxc_2->Fill(xTopCl, yTopCl);
                h_cl_yxc_2->Fill(xBotCl, yBotCl);


                //if (P_Bot > 0.8 && P_Bot < 1.5 && P_Top > 0.8 && P_Top < 1.5) {
                if ((P_Diff > PDiffLowMin && P_Diff < PDiffLowMax) || (P_Diff > PDiffHighMin && P_Diff < PDiffHighMax)) {
                    h_MTCMoeller3->Fill(M_TCM);
                    h_dX_P_Top3->Fill(P_Top, dX_Top);
                    h_dX_P_Bot3->Fill(P_Bot, dX_Bot);
                    if (TopTrkInHole) {
                        h_dX_P_InHole_Top3->Fill(P_Top, dX_Top);
                    } else {
                        h_dX_P_InECal_Top3->Fill(P_Top, dX_Top);
                    }
                    if (BotTrkInHole) {
                        h_dX_P_InHole_Bot3->Fill(P_Bot, dX_Bot);
                    } else {
                        h_dX_P_InECal_Bot3->Fill(P_Bot, dX_Bot);
                    }
                    h_X_TopBot3->Fill(xBotCl, xTopCl);
                    h_Y_TopBot3->Fill(yBotCl, yTopCl);
                    h_phi_TopBot3->Fill(phiBot, phiTop);
                    h_dPhi3->Fill(phiTop - phiBot);
                    h_VertChi2_3->Fill(VertexChi2);
                    h_Trk_dT_Psum3->Fill(P_TCM, tr_dT);
                    h_TopMatchChi2_3->Fill(MatchingChi2Top);
                    h_BotMatchChi2_3->Fill(MatchingChi2Bot);
                    h_Chi2NDF_TCM3->Fill(M_TCM, chi2NDF_Sum);
                    h_tr_yxc_3->Fill(xTopTr, yTopTr);
                    h_tr_yxc_3->Fill(xBotTr, yBotTr);
                    h_cl_yxc_3->Fill(xTopCl, yTopCl);
                    h_cl_yxc_3->Fill(xBotCl, yBotCl);

                    bool testTopMatchingCut = false;
                    bool testBotMatchingCut = false;

                    if (TopTrkInHole) {
                        testTopMatchingCut = TMath::Abs(dX_Top) > 50.;
                    } else {
                        testTopMatchingCut = P_Top < 1.1 && dX_Top > -5 && dX_Top < 6;
                    }

                    if (BotTrkInHole) {
                        testBotMatchingCut = TMath::Abs(dX_Bot) > 50.;
                    } else {
                        testBotMatchingCut = P_Bot < 1.15 && dX_Bot > -8 && dX_Bot < 3;
                    }

                    if (!(TopTrkFiducial && BotTrkFiducial)) {
                        continue;
                    }

                    if (testTopMatchingCut && testBotMatchingCut && tr_dT > tr_dT_Min && tr_dT < tr_dT_Max) {
                        h_Chi2NDF_TCM6->Fill(M_TCM, chi2NDF_Sum);
                        h_PsumPdiff4->Fill(P_TCM, P_Top - P_Bot);

                        if (P_Top > P_Bot) {
                            h_Chi2NDF_TCM_Top6->Fill(M_TCM, chi2NDF_Sum);
                        } else {
                            h_Chi2NDF_TCM_Bot6->Fill(M_TCM, chi2NDF_Sum);
                        }
                    }



                    if ((MatchingChi2Top - MatchingChi2Median) * (MatchingChi2Bot - MatchingChi2Median) < 0.
                            && TMath::Min(MatchingChi2Top, MatchingChi2Bot) < MatchingChi2Best && tr_dT > tr_dT_Min && tr_dT < tr_dT_Max
                            /* && (phiTop > phiBot + 165) && (phiTop < phiBot + 190.  )*/) {
                        h_MTCMoeller4->Fill(M_TCM);
                        h_dPhi4->Fill(phiTop - phiBot);
                        h_phi_TopBot4->Fill(phiBot, phiTop);
                        h_VertChi2_4->Fill(VertexChi2);
                        h_X_TopBot4->Fill(xBotCl, xTopCl);
                        h_Y_TopBot4->Fill(yBotCl, yTopCl);
                        h_Trk_dT_Psum4->Fill(P_TCM, tr_dT);
                        h_TopMatchChi2_4->Fill(MatchingChi2Top);
                        h_BotMatchChi2_4->Fill(MatchingChi2Bot);
                        h_TopBotMatchCh2_3->Fill(MatchingChi2Bot, MatchingChi2Top);
                        h_Chi2NDF_TCM4->Fill(M_TCM, chi2NDF_Sum);
                        h_tr_yxc_4->Fill(xTopTr, yTopTr);
                        h_tr_yxc_4->Fill(xBotTr, yBotTr);
                        h_cl_yxc_4->Fill(xTopCl, yTopCl);
                        h_cl_yxc_4->Fill(xBotCl, yBotCl);

                        if (HasTopL1 && HasBotL1) {

                            h_phi_TopBot5->Fill(phiBot, phiTop);
                            h_dPhi5->Fill(phiTop - phiBot);
                            h_Chi2NDF_TCM5->Fill(M_TCM, chi2NDF_Sum);
                            h_tr_yxc_5->Fill(xTopTr, yTopTr);
                            h_tr_yxc_5->Fill(xBotTr, yBotTr);
                            h_cl_yxc_5->Fill(xTopCl, yTopCl);
                            h_cl_yxc_5->Fill(xBotCl, yBotCl);
                        }

                    }
                }

            }

        }

    }

    gDirectory->Write();
    return 0;
}

