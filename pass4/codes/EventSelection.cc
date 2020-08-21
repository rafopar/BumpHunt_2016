/* 
 * File:   EventSelection.cc
 * Author: rafopar
 *
 * Created on September 18, 2019, 9:27 AM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>
#include "setting_2016_pass1.h"
#include "InitSettings.C"

#include <fstream>
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

    isEventSelection = true;
    InitVariables(dataSet);

    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");

    TH1D *h_nV0_1 = new TH1D("h_nV0_1", "", 11, -0.5, 10.5);
    TH1D *h_nV0_2 = new TH1D("h_nV0_2", "", 11, -0.5, 10.5);

    TH1D *h_n_c1l = new TH1D("h_n_cl1", "", 15, -0.5, 14.5);
    TH1D *h_clE1 = new TH1D("h_clE1", "", 200, 0., 1.2 * Eb);
    TH2D *h_cl_E_t1 = new TH2D("h_cl_E_t1", "", 200, 0., 1.2 * Eb, 200, 0., 180.);
    TH2D *h_cl_E_tTop1 = new TH2D("h_cl_E_tTop1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_cl_E_tBot1 = new TH2D("h_cl_E_tBot1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_dt_Esum1 = new TH2D("h_dt_Esum1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dt_Esum2 = new TH2D("h_dt_Esum2", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dt_EsumHighPSum1 = new TH2D("h_dt_EsumHighPSum1", "", 200, 0.8 * Eb, 3.2 * Eb, 200, -15., 15.);
    TH2D *h_dt_EsumHighPSum2 = new TH2D("h_dt_EsumHighPSum2", "", 200, 0.8 * Eb, 3.2 * Eb, 200, -15., 15.);
    TH2D *h_dtCorr_Esum1 = new TH2D("h_dtCorr_Esum1", "", 200, 0.8, 1.2 * Eb, 200, -15., 15.);
    TH2D *h_dtCorr_Esum2 = new TH2D("h_dtCorr_Esum2", "", 200, 0.8, 1.2 * Eb, 200, -15., 15.);

    TH2D *h_cl_yxc1 = new TH2D("h_cl_yxc1", "", 200, -300., 370, 200, -90., 90.);
    TH2D *h_cl_yxc_TEST1 = new TH2D("h_cl_yxc_TEST1", "", 200, -300., 370, 200, -90., 90.);

    TH1D *h_tr_P_pos1 = new TH1D("h_tr_P_pos1", "", 200, 0., 1.2 * Eb);
    TH1D *h_tr_P_neg1 = new TH1D("h_tr_P_neg1", "", 200, 0., 1.2 * Eb);

    TH1D *h_n_tr1 = new TH1D("h_n_tr1", "", 21, -0.5, 20.5);

    TH2D *h_n_trk_crash1 = new TH2D("h_n_trk_crash1", "", 21, -0.5, 20.5, 15, -7.5, 7.5);

    TH2D *h_cl_dtMeans1 = new TH2D("h_cl_dtMeans1", "", 47, -23.5, 23.5, 11, -5.5, 5.5);

    TH2D *h_em_cl_EvsT_top1 = new TH2D("h_em_cl_EvsT_top1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_em_cl_EvsT_top2 = new TH2D("h_em_cl_EvsT_top2", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_em_cl_EvsT_bot1 = new TH2D("h_em_cl_EvsT_bot1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_em_cl_EvsT_bot2 = new TH2D("h_em_cl_EvsT_bot2", "", 200, 0., 1.2 * Eb, 200, 30., 75.);

    TH2D *h_ep_cl_EvsT_top1 = new TH2D("h_ep_cl_EvsT_top1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_ep_cl_EvsT_top2 = new TH2D("h_ep_cl_EvsT_top2", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_ep_cl_EvsT_bot1 = new TH2D("h_ep_cl_EvsT_bot1", "", 200, 0., 1.2 * Eb, 200, 30., 75.);
    TH2D *h_ep_cl_EvsT_bot2 = new TH2D("h_ep_cl_EvsT_bot2", "", 200, 0., 1.2 * Eb, 200, 30., 75.);

    TH2D *h_cl_dt_Esum_posneg1 = new TH2D("h_cl_dt_Esum_posneg1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);
    TH2D *h_cl_dt_Esum_posnegTight1 = new TH2D("h_cl_dt_Esum_posnegTight1", "", 200, 0., 1.2 * Eb, 200, -15., 15.);

    TH1D *h_chi2NDF_em_top_5hits_1 = new TH1D("h_chi2NDF_em_top_5hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_em_top_6hits_1 = new TH1D("h_chi2NDF_em_top_6hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_em_bot_5hits_1 = new TH1D("h_chi2NDF_em_bot_5hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_em_bot_6hits_1 = new TH1D("h_chi2NDF_em_bot_6hits_1", "", 200, 0., 13.);

    TH1D *h_chi2NDF_ep_top_5hits_1 = new TH1D("h_chi2NDF_ep_top_5hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_ep_top_6hits_1 = new TH1D("h_chi2NDF_ep_top_6hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_ep_bot_5hits_1 = new TH1D("h_chi2NDF_ep_bot_5hits_1", "", 200, 0., 13.);
    TH1D *h_chi2NDF_ep_bot_6hits_1 = new TH1D("h_chi2NDF_ep_bot_6hits_1", "", 200, 0., 13.);

    TH1D *h_d0_em_top_5hits_1 = new TH1D("h_d0_em_top_5hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_top_6hits_1 = new TH1D("h_d0_em_top_6hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_bot_5hits_1 = new TH1D("h_d0_em_bot_5hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_bot_6hits_1 = new TH1D("h_d0_em_bot_6hits_1", "", 200, -3.5, 3.5);

    TH1D *h_d0_em_topWithL1 = new TH1D("h_d0_em_topWithL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_topNoL1 = new TH1D("h_d0_em_topNoL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_botWithL1 = new TH1D("h_d0_em_botWithL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_em_botNoL1 = new TH1D("h_d0_em_botNoL1", "", 200, -3.5, 3.5);
    TH1D *h_Mv0_WithL1 = new TH1D("h_Mv0_emWithL1", "", 200, 0.02, 0.2);
    TH1D *h_Mv0_NoL1 = new TH1D("h_Mv0_emNoL1", "", 200, 0.02, 0.2);

    TH1D *h_d0_ep_top_5hits_1 = new TH1D("h_d0_ep_top_5hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_top_6hits_1 = new TH1D("h_d0_ep_top_6hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_bot_5hits_1 = new TH1D("h_d0_ep_bot_5hits_1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_bot_6hits_1 = new TH1D("h_d0_ep_bot_6hits_1", "", 200, -3.5, 3.5);

    TH1D *h_d0_ep_topWithL1 = new TH1D("h_d0_ep_topWithL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_topNoL1 = new TH1D("h_d0_ep_topNoL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_botWithL1 = new TH1D("h_d0_ep_botWithL1", "", 200, -3.5, 3.5);
    TH1D *h_d0_ep_botNoL1 = new TH1D("h_d0_ep_botNoL1", "", 200, -3.5, 3.5);

    TH1D *h_pos_Chi2PID1 = new TH1D("h_pos_Chi2PID1", "", 200, 0., 10);
    TH1D *h_pos_Chi2PID2 = new TH1D("h_pos_Chi2PID2", "", 200, 0., 10);
    TH1D *h_pos_Chi2PID3 = new TH1D("h_pos_Chi2PID3", "", 200, 0., 10);

    TH1D *h_PV01 = new TH1D("h_PV01", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV02 = new TH1D("h_PV02", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV03 = new TH1D("h_PV03", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV04 = new TH1D("h_PV04", "", 200, 0.7, 1.2 * Eb);

    TH1D *h_PV0_Test1 = new TH1D("h_PV0_Test1", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test2 = new TH1D("h_PV0_Test2", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test3 = new TH1D("h_PV0_Test3", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test4 = new TH1D("h_PV0_Test4", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test5 = new TH1D("h_PV0_Test5", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test6 = new TH1D("h_PV0_Test6", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test7 = new TH1D("h_PV0_Test7", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test8 = new TH1D("h_PV0_Test8", "", 200, 0.7, 1.2 * Eb);
    TH1D *h_PV0_Test9 = new TH1D("h_PV0_Test9", "", 200, 0.7, 1.2 * Eb);

    TH1D *h_Pem_TightCut1 = new TH1D("h_Pem_TightCut1", "", 200, 0., Eb);

    TH1D *h_em_Chi2Ndf1 = new TH1D("h_em_Chi2Ndf1", "", 200, 0., 13.);
    TH1D *h_ep_Chi2Ndf1 = new TH1D("h_ep_Chi2Ndf1", "", 200, 0., 13.);

    TH2D *h_dX_Top_PosWithL6 = new TH2D("h_dX_Top_PosWithL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Top_PosNoL6 = new TH2D("h_dX_Top_PosNoL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Bot_PosWithL6 = new TH2D("h_dX_Bot_PosWithL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Bot_PosNoL6 = new TH2D("h_dX_Bot_PosNoL6", "", 50, 0., Eb, 100, -50., 50.);

    TH2D *h_dX_Top_NegWithL6 = new TH2D("h_dX_Top_NegWithL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Top_NegNoL6 = new TH2D("h_dX_Top_NegNoL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Bot_NegWithL6 = new TH2D("h_dX_Bot_NegWithL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Bot_NegNoL6 = new TH2D("h_dX_Bot_NegNoL6", "", 50, 0., Eb, 100, -50., 50.);
    TH2D *h_dX_Bot_NegNoL6_Test1 = new TH2D("h_dX_Bot_NegNoL6_Test1", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dX_Bot_NegNoL6_Test2 = new TH2D("h_dX_Bot_NegNoL6_Test2", "", 200, 0., Eb, 200, -50., 50.);

    TH2D *h_dY_Top_PosWithL6 = new TH2D("h_dY_Top_PosWithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Top_PosNoL6 = new TH2D("h_dY_Top_PosNoL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Bot_PosWithL6 = new TH2D("h_dY_Bot_PosWithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Bot_PosNoL6 = new TH2D("h_dY_Bot_PosNoL6", "", 200, 0., Eb, 200, -50., 50.);

    TH2D *h_dY_Top_NegWithL6 = new TH2D("h_dY_Top_NegWithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Top_NegNoL6 = new TH2D("h_dY_Top_NegNoL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Bot_NegWithL6 = new TH2D("h_dY_Bot_NegWithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dY_Bot_NegNoL6 = new TH2D("h_dY_Bot_NegNoL6", "", 200, 0., Eb, 200, -50., 50.);

    TH2D *h_dX_Top_TEST_WithL6 = new TH2D("h_dX_Top_TEST_WithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dX_Top_TEST_NoL6 = new TH2D("h_dX_Top_TEST_NoL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dX_Bot_TEST_WithL6 = new TH2D("h_dX_Bot_TEST_WithL6", "", 200, 0., Eb, 200, -50., 50.);
    TH2D *h_dX_Bot_TEST_NoL6 = new TH2D("h_dX_Bot_TEST_NoL6", "", 200, 0., Eb, 200, -50., 50.);


    TH2D *h_PemPep1 = new TH2D("h_PemPep1", "", 200, 0., 1.05 * Eb, 200, 0., 1.05 * Eb);

    TH2D *h_cl_E_Xc_ep1 = new TH2D("h_cl_E_Xc_ep1", "", 200, -300., 370, 200, 0., Eb);
    TH2D *h_cl_E_Xc_em1 = new TH2D("h_cl_E_Xc_em1", "", 200, -300., 370, 200, 0., Eb);



    // =============== n-1 histograms, i.e. these histograms are filled when cuts on the rest of variables are applied

    TH1D *h_d0_ep_Nminus1 = new TH1D("h_d0_ep_Nminus1", "", 200, -3.5, 3.5);
    TH1D *h_Pem_Nminus1 = new TH1D("h_Pem_Nminus1", "", 200, 0., Eb);
    TH1D *h_cl_dt_Nminus1 = new TH1D("h_cl_dt_Nminus1", "", 200, -5., 5.);


    // ============================= Three stages of histograms ==================================
    // == 1. Histograms With extension "All" represent the distribution of a variable when no cut is applied
    // == 2. Histograms With extension "AllBut" represent the distribution of a variable when, all
    // ==    event selection cuts are applied, except the one of that variable
    // == 3. Histograms With extension "CutEffect" represents the distribution of a given variable, 
    // ==    when all cuts (including the given variable) are applied
    // ============================= Three stages of histograms ==================================

    //    TH1D *h_PV0Max_All = new TH1D("h_PV0Max_All", "", 70, 0.7, 1.2 * Eb);
    //    TH1D *h_PV0Max_AllBut = new TH1D("h_PV0Max_AllBut", "", 70, 0.7, 1.2 * Eb);
    //    TH1D *h_PV0Max_CutEffect = new TH1D("h_PV0Max_CutEffect", "", 70, 0.7, 1.2 * Eb);

    TH2D *h_Minv_PV0Max_All = new TH2D("h_Minv_PV0Max_All", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH2D *h_Minv_PV0Max_AllBut = new TH2D("h_Minv_PV0Max_AllBut", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH2D *h_Minv_PV0Max_CutEffect = new TH2D("h_Minv_PV0Max_CutEffect", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);

    TH2D *h_Minv_PV0Min_All = new TH2D("h_Minv_PV0Min_All", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH2D *h_Minv_PV0Min_AllBut = new TH2D("h_Minv_PV0Min_AllBut", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH2D *h_Minv_PV0Min_CutEffect = new TH2D("h_Minv_PV0Min_CutEffect", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);

    TH1D * h_PV0Min_MinvBin_All[nMinvBins + 1];
    TH1D * h_PV0Min_MinvBin_AllBut[nMinvBins + 1];
    TH1D * h_PV0Min_MinvBin_CutEffect[nMinvBins + 1];

    for (int i = 0; i < nMinvBins + 1; i++) {
        h_PV0Min_MinvBin_All[i] = new TH1D(Form("h_PV0Min_MinvBin_%d_All", i), "", 70, 0.7, 1.2 * Eb);
        h_PV0Min_MinvBin_AllBut[i] = new TH1D(Form("h_PV0Min_MinvBin_%d_AllBut", i), "", 70, 0.7, 1.2 * Eb);
        h_PV0Min_MinvBin_CutEffect[i] = new TH1D(Form("h_PV0Min_MinvBin_%d_CutEffect", i), "", 70, 0.7, 1.2 * Eb);
    }


    TH1D *h_Pem_All = new TH1D("h_Pem_All", "", 70, 0., 2.2);
    TH1D *h_Pem_AllBut = new TH1D("h_Pem_AllBut", "", 70, 0., 2.2);
    TH1D *h_Pem_CutEffect = new TH1D("h_Pem_CutEffect", "", 70, 0., 2.2);

    TH1D *h_d0_ep_All = new TH1D("h_d0_ep_All", "", 120, -3.5, 9.);
    TH1D *h_d0_ep_AllBut = new TH1D("h_d0_ep_AllBut", "", 120, -3.5, 9.);
    TH1D *h_d0_ep_CutEffect = new TH1D("h_d0_ep_CutEffect", "", 120, -3.5, 9.);


    TH2D *h_Minv_PV0_MCParticle = new TH2D("h_Minv_PV0_MCParticle", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH2D *h_Minv_P622_MCParticle = new TH2D("h_Minv_P622_MCParticle", "", 200, 0.7, 1.2 * Eb, 200, 0., 0.25);
    TH1D *h_N_MCDaughters1 = new TH1D("h_N_MCDaughters1", "", 6, -0.5, 5.5);

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

    //nev = 200000;
    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);
        //tr1->GetEvent(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }

        // This needs to be called at the beginning of every event
        ResetEventFlags();


        int n_cl = ev->getNumberOfEcalClusters();

        if (!ev->isPair1Trigger() && isData) {
            continue;
        }
        h_n_c1l->Fill(n_cl);

        int n_top_cl = 0;
        int n_bot_cl = 0;
        for (int i_cl = 0; i_cl < n_cl; i_cl++) {
            cl = ev->getEcalCluster(i_cl);

            // ===== Correct the cluster time at the earliest stage =====
            // ===== The correction is needed only for Data, so, we =====
            // ===== will check, if it is data, and then only will  =====
            // ===== apply the correction                           =====
            if (isData) {
                CorrectClusterTime(cl);
            }

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

        h_n_pos_trk1->Fill(n_pos);
        h_n_neg_trk1->Fill(n_neg);

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

                //                double t_top_corrected = clTop->getClusterTime() - topTimeCorrection;
                //                double t_bot_corrected = clBot->getClusterTime() - botTimeCorrection;

                //                double dtCorr = t_top_corrected - t_bot_corrected;

                h_dt_Esum1->Fill(Esum, dt);
                h_dt_EsumHighPSum1->Fill(Esum, dt);

                if (clTop->getEnergy() > 2. && clBot->getEnergy() > 2.) {
                    h_dt_EsumHighPSum2->Fill(Esum, dt);
                }

                //h_dtCorr_Esum1->Fill(Esum, dtCorr);

                if (n_pos == 1 && n_neg == 1) {
                    h_dt_Esum2->Fill(Esum, dt);
                    //                    h_dtCorr_Esum2->Fill(Esum, dtCorr);
                }

            }

        }


        int nTC_V0 = ev->getNumberOfParticles(HpsParticle::TC_V0_CANDIDATE);

        h_nV0_1->Fill(nTC_V0);
        int n_realV0 = 0;

        for (int iv0 = 0; iv0 < nTC_V0; iv0++) {

            ResetV0Flags();

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

            double PV0 = GetMagnitude(cur_v0->getMomentum());
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
            //cout<<part0->getCharge()<<endl;


            if (IsParticleKilled(em, "Up") || IsParticleKilled(ep, "Up")) {
                continue;
            }



            double mV0 = cur_v0->getMass();
            vector<double> smearKine = GetSmearKine(cur_v0);
            double M_TCSmSc = smearKine.at(0);
            double PemScSm = smearKine.at(1);
            double PepScSm = smearKine.at(2);
            double PV0ScSm = smearKine.at(3);
            double PSumScSm = PemScSm + PepScSm;
            double M_TCSmScErrPos = smearKine.at(4);
            double M_TCSmScErrNeg = smearKine.at(5);


            //            cout << "# of em clusters     " << em->getClusters()->GetSize() << endl;
            //            cout << "# of ep clusters " << ep->getClusters()->GetSize() << endl;

            // ======== Getting Electron related variables ========
            bool emHasCl = false;
            vector<double> pos_cl_em{-9999, -9999, -9999};
            double t_cl_em = -9999;
            bool is_neg_ClustIntime = false;
            double E_cl_em = -9999;

            if (em->getClusters()->GetSize() > 0) {
                cl_em = (EcalCluster*) em->getClusters()->At(0);
                pos_cl_em = cl_em->getPosition();
                t_cl_em = cl_em->getClusterTime();

                t_cl_em = cl_em->getClusterTime();

                E_cl_em = cl_em->getEnergy();

                is_neg_ClustIntime = IsIntimeClusterCandidate(cl_em);

                if (pos_cl_em.at(1) > 0) {
                    h_em_cl_EvsT_top1->Fill(cl_em->getEnergy(), t_cl_em);
                    if (is_neg_ClustIntime) {
                        h_em_cl_EvsT_top2->Fill(cl_em->getEnergy(), t_cl_em);
                    }
                } else {
                    h_em_cl_EvsT_bot1->Fill(cl_em->getEnergy(), t_cl_em);
                    if (is_neg_ClustIntime) {
                        h_em_cl_EvsT_bot2->Fill(cl_em->getEnergy(), t_cl_em);
                    }
                }

                emHasCl = true;
            } else {
                cout << "Rare event didn't give a cluster" << endl;
                continue;
            }

            GblTrack *trk_em = (GblTrack*) em->getTracks()->At(0);
            vector<double> pos_trk_em = trk_em->getPositionAtEcal();
            vector<double> P_trk_em = trk_em->getMomentum();
            double P_em = sqrt(P_trk_em.at(0) * P_trk_em.at(0) + P_trk_em.at(1) * P_trk_em.at(1) + P_trk_em.at(2) * P_trk_em.at(2));
            bool hasemL1 = HasL1Hit(trk_em);
            bool hasemL6 = HasL6Hit(trk_em);

            double chi2_em = trk_em->getChi2();
            int n_emHits = trk_em->getSvtHits()->GetSize();
            int NDF_em = 2 * n_emHits - 5;
            double d0_em = trk_em->getD0();
            double dY_em = pos_cl_em.at(1) - pos_trk_em.at(1);
            double dX_em = pos_cl_em.at(0) - pos_trk_em.at(0);

            if (!(pos_trk_em.at(1) * cl_em->getPosition().at(1) > 0)) {
                cout << "               =============================================== " << endl;
                cout << " A rare event, when cluster and track positions are not in the same half" << endl;
                cout << "Electron Cluster Y positions is " << cl_em->getPosition().at(1) << endl;
                cout << "Electron Track Y positions at ECal is " << pos_trk_em.at(1) << endl;
                cout << "               =============================================== " << endl;
                continue;
            }

            double ClTrkDt_em = cl_em->getClusterTime() - CL_trk_time_Offset - trk_em->getTrackTime();

            if (pos_trk_em.at(1) > 0) {

                if (HasL1Hit(trk_em)) {
                    h_d0_em_topWithL1->Fill(d0_em);
                } else {
                    h_d0_em_topNoL1->Fill(d0_em);
                }
            } else {
                if (HasL1Hit(trk_em)) {
                    h_d0_em_botWithL1->Fill(d0_em);
                } else {
                    h_d0_em_botNoL1->Fill(d0_em);
                }
            }




            if (n_emHits == 5) {
                if (pos_trk_em.at(1) > 0) {
                    h_chi2NDF_em_top_5hits_1->Fill(chi2_em / double(NDF_em));
                    h_d0_em_top_5hits_1->Fill(d0_em);
                } else {
                    h_chi2NDF_em_bot_5hits_1->Fill(chi2_em / double(NDF_em));
                    h_d0_em_bot_5hits_1->Fill(d0_em);
                }
            } else if (n_emHits == 6) {
                if (pos_trk_em.at(1) > 0) {
                    h_chi2NDF_em_top_6hits_1->Fill(chi2_em / double(NDF_em));
                    h_d0_em_top_6hits_1->Fill(d0_em);
                } else {
                    h_chi2NDF_em_bot_6hits_1->Fill(chi2_em / double(NDF_em));
                    h_d0_em_bot_6hits_1->Fill(d0_em);
                }
            } else {
                cout << "Number of hits is " << n_emHits << endl;
                cout << "This is strange: Number of hits should be either 5 or 6" << endl;
                cout << "Exiting" << endl;
                exit(1);
            }

            // ======== Getting Positron related variables ========
            vector<double> pos_cl_ep{-9999, -9999, -9999, -9999};
            bool epHasCl = false;
            double t_cl_ep = -9999;
            bool is_pos_ClustIntime = false;
            double E_cl_ep = -9999;

            if (ep->getClusters()->GetSize() > 0) {
                cl_ep = (EcalCluster*) ep->getClusters()->At(0);
                pos_cl_ep = cl_ep->getPosition();
                t_cl_ep = cl_ep->getClusterTime();
                E_cl_ep = cl_ep->getEnergy();
                is_pos_ClustIntime = IsIntimeClusterCandidate(cl_ep);

                double posChi2 = ep->getGoodnessOfPID();

                h_pos_Chi2PID1->Fill(posChi2);

                if (pos_cl_ep.at(1) > 0) {
                    h_ep_cl_EvsT_top1->Fill(cl_ep->getEnergy(), t_cl_ep);
                    if (is_pos_ClustIntime) {
                        h_ep_cl_EvsT_top2->Fill(cl_ep->getEnergy(), t_cl_ep);
                        h_pos_Chi2PID2->Fill(posChi2);
                    }
                } else {
                    h_ep_cl_EvsT_bot1->Fill(cl_ep->getEnergy(), t_cl_ep);
                    if (is_pos_ClustIntime) {
                        h_pos_Chi2PID3->Fill(posChi2);
                        h_ep_cl_EvsT_bot2->Fill(cl_ep->getEnergy(), t_cl_ep);
                    }
                }


                epHasCl = true;
            } else {
                cout << "Rare event didn't give a cluster" << endl;
                continue;
            }


            if (!(is_neg_ClustIntime && is_pos_ClustIntime)) {
                continue;
            }

            if (cl_em->getPosition().at(1) * cl_ep->getPosition().at(1) > 0) {
                cout << "A rare event when e- and e+ in V0 are in the same detector half " << endl;
                continue;
            }


            h_cl_dt_Esum_posneg1->Fill(E_cl_ep + E_cl_em, t_cl_ep - t_cl_em);

            GblTrack *trk_ep = (GblTrack*) ep->getTracks()->At(0);
            vector<double> pos_trk_ep = trk_ep->getPositionAtEcal();
            vector<double> P_trk_ep = trk_ep->getMomentum();
            double P_ep = sqrt(P_trk_ep.at(0) * P_trk_ep.at(0) + P_trk_ep.at(1) * P_trk_ep.at(1) + P_trk_ep.at(2) * P_trk_ep.at(2));
            hasepL1 = HasL1Hit(trk_ep);
            bool hasepL6 = HasL6Hit(trk_ep);



            if (!(pos_trk_ep.at(1) * cl_ep->getPosition().at(1) > 0)) {
                cout << "               =============================================== " << endl;
                cout << " A rare event, when cluster and track positions are not in the same half" << endl;
                cout << "PositCluster Y positions is " << cl_ep->getPosition().at(1) << endl;
                cout << "PositCluster Track Y positions at ECal is " << pos_trk_ep.at(1) << endl;
                cout << "               =============================================== " << endl;
                continue;
            }

            double ClTrkDt_ep = cl_ep->getClusterTime() - CL_trk_time_Offset - trk_ep->getTrackTime();

            double chi2_ep = trk_ep->getChi2();
            int n_epHits = trk_ep->getSvtHits()->GetSize();
            int NDF_ep = 2 * n_epHits - 5;
            double d0_ep = trk_ep->getD0();
            double dY_ep = pos_cl_ep.at(1) - pos_trk_ep.at(1);
            double dX_ep = pos_cl_ep.at(0) - pos_trk_ep.at(0);


            if (pos_trk_ep.at(1) > 0) {

                if (HasL1Hit(trk_ep)) {
                    h_d0_ep_topWithL1->Fill(d0_ep);
                } else {
                    h_d0_ep_topNoL1->Fill(d0_ep);
                }
            } else {
                if (HasL1Hit(trk_ep)) {
                    h_d0_ep_botWithL1->Fill(d0_ep);
                } else {
                    h_d0_ep_botNoL1->Fill(d0_ep);
                }
            }



            if (n_epHits == 5) {
                if (pos_trk_ep.at(1) > 0) {
                    h_chi2NDF_ep_top_5hits_1->Fill(chi2_ep / double(NDF_ep));
                    h_d0_ep_top_5hits_1->Fill(d0_ep);
                } else {
                    h_chi2NDF_ep_bot_5hits_1->Fill(chi2_ep / double(NDF_ep));
                    h_d0_ep_bot_5hits_1->Fill(d0_ep);
                }
            } else if (n_epHits == 6) {
                if (pos_trk_ep.at(1) > 0) {
                    h_chi2NDF_ep_top_6hits_1->Fill(chi2_ep / double(NDF_ep));
                    h_d0_ep_top_6hits_1->Fill(d0_ep);
                } else {
                    h_chi2NDF_ep_bot_6hits_1->Fill(chi2_ep / double(NDF_ep));
                    h_d0_ep_bot_6hits_1->Fill(d0_ep);
                }
            } else {
                cout << "Number of hits is " << n_epHits << endl;
                cout << "This is strange: Number of hits should be either 5 or 6" << endl;
                cout << "Exiting" << endl;
                exit(1);
            }




            if (HasL1Hit(trk_ep) && HasL1Hit(trk_em)) {
                h_Mv0_WithL1->Fill(mV0);
            } else {
                h_Mv0_NoL1->Fill(mV0);
            }


            double PSum = P_em + P_ep;

            h_PV01->Fill(PV0);

            IsTightcldT = IsCldtTightCutPass(cl_em, cl_ep);
            IsTightepClTrkdT = IsTightTrkClust_dtCutPassed(trk_ep, cl_ep);
            IsTightemClTrkdT = IsTightTrkClust_dtCutPassed(trk_em, cl_em);
            IsTightemTrkClMatch = IsTightTrkClust_dXCutPassed(trk_em, cl_em);
            IsTightepTrkClMatch = IsTightTrkClust_dXCutPassed(trk_ep, cl_ep);
            IsTighteptrkChi2 = IsTightChi2NdfCutPassed(trk_ep);
            IsTightemtrkChi2 = IsTightChi2NdfCutPassed(trk_em);
            IsTightPem = IsTightemMaxMomCut(P_em);


            //            cout << IsTightcldT << "   " << IsTightepClTrkdT << "   " << IsTightemClTrkdT << "   " << IsTightemTrkClMatch << "   " << IsTightepTrkClMatch << "   "
            //                    << IsTighteptrkChi2 << "   " << IsTightemtrkChi2 << "   " << IsTightPem << endl;

            // =========================================================
            // We don't need tracks that don't have hit lin L1
            // =========================================================

            //if (!(hasemL1 && hasepL1)) {
            // ===================== At the Analysis Workshop in Jan 2020, it was decided to drop the L1 requirement
            // ===================== It requires significant studies in order the data and MC track efficiencies to agree
            // ===================== Without it the Data-MC agreement is better
            //            if (!hasepL1) {
            //                continue;
            //            }

            if (IsTightcldT && IsTightPem && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightepTrkClMatch && IsTightemTrkClMatch && IsTightemClTrkdT && IsTightepClTrkdT
                    && IsTightcldT) {
                h_PV02->Fill(PV0);
            }

            if (CheckTightCuts("cldT")) {
                h_cl_dt_Esum_posnegTight1->Fill(E_cl_ep + E_cl_em, t_cl_ep - t_cl_em);
            }

            if (CheckTightCuts("Pem")) {
                h_Pem_TightCut1->Fill(P_em);
            }

            if (CheckTightCuts("emTrkChi2")) {
                h_em_Chi2Ndf1->Fill(chi2_em / double(NDF_em));
            }

            if (CheckTightCuts("epTrkChi2")) {
                h_ep_Chi2Ndf1->Fill(chi2_ep / double(NDF_ep));
            }

            if (CheckTightCuts("emClTrkMatch")) {

                if (pos_trk_em.at(1) > 0.) {
                    if (hasemL6) {
                        h_dX_Top_NegWithL6->Fill(P_em, dX_em);
                        h_dY_Top_NegWithL6->Fill(P_em, dY_em);
                    } else {
                        h_dX_Top_NegNoL6->Fill(P_em, dX_em);
                        h_dY_Top_NegNoL6->Fill(P_em, dY_em);
                    }

                } else {
                    if (hasemL6) {
                        h_dX_Bot_NegWithL6->Fill(P_em, dX_em);
                        h_dY_Bot_NegWithL6->Fill(P_em, dY_em);
                    } else {
                        h_dX_Bot_NegNoL6->Fill(P_em, dX_em);
                        h_dY_Bot_NegNoL6->Fill(P_em, dY_em);

                        if (pos_cl_em.at(0) < -260.) {
                            h_dX_Bot_NegNoL6_Test1->Fill(P_em, dX_em);
                        } else {
                            h_dX_Bot_NegNoL6_Test2->Fill(P_em, dX_em);
                        }

                        if (dX_em > -7 - 18. / (0.2 - P_em)) {
                            h_cl_yxc_TEST1->Fill(pos_cl_em.at(0), pos_cl_em.at(1));
                        }

                    }

                }

            }


            if (CheckTightCuts("epClTrkMatch")) {
                if (pos_trk_ep.at(1) > 0.) {
                    if (hasepL6) {
                        h_dX_Top_PosWithL6->Fill(P_ep, dX_ep);
                        h_dY_Top_PosWithL6->Fill(P_ep, dY_ep);
                    } else {
                        h_dX_Top_PosNoL6->Fill(P_ep, dX_ep);
                        h_dY_Top_PosNoL6->Fill(P_ep, dY_ep);
                    }
                } else {
                    if (hasepL6) {
                        h_dX_Bot_PosWithL6->Fill(P_ep, dX_ep);
                        h_dY_Bot_PosWithL6->Fill(P_ep, dY_ep);
                    } else {
                        h_dX_Bot_PosNoL6->Fill(P_ep, dX_ep);
                        h_dY_Bot_PosNoL6->Fill(P_ep, dY_ep);
                    }
                }

            }


            // ==========================
            // Temporary studies with MCParticles

            int nMCParticles = ev->getNumberOfMCParticles();

            bool MCStat1 = false;
            for (int iMC = 0; iMC < nMCParticles; iMC++) {
                MCParticle *mcpart = ev->getMCParticle(iMC);

                //                cout<<mcpart->getPdgID()<<"     "<<mcpart->getEnergy()<<"     "<<mcpart->getMass()<<"    "<<mcpart->getMomentum().at(0)<<"     "
                //                        <<mcpart->getMomentum().at(1)<<"     "<<mcpart->getMomentum().at(2)<<"     "<<endl;



                if (mcpart->getPdgID() == 622) {


                    h_N_MCDaughters1->Fill(mcpart->getDaughterCount());

                    if (mcpart->getDaughterCount() < 2) {
                        continue;
                    }
                    //cout << mcpart->getDaughterCount() << endl;

                    //                    if (mcpart->getDaughterCount() > 2) {
                    //                        for (int iD = 0; iD < mcpart->getDaughterCount(); iD++) {
                    //                            cout << "Daughter " << iD << "     Status is " << mcpart->getDaughter(iD)->getGenStatus() <<"    PID = "<<
                    //                                    mcpart->getDaughter(iD)->getPdgID()<< endl;
                    //                        }
                    //                    }

                    double P622 = GetMagnitude(mcpart->getMomentum());
                    double P0 = GetMagnitude(mcpart->getDaughter(0)->getMomentum());
                    double P1 = GetMagnitude(mcpart->getDaughter(1)->getMomentum());

                    //                    cout << " = = = = = = = = = " << endl;
                    //                    cout<<"Endpoint of 622         " << mcpart->getEndPoint().at(0) << "     " << mcpart->getEndPoint().at(1) << "    " << mcpart->getEndPoint().at(2) << endl;
                    //                    for (int iD = 0; iD < mcpart->getDaughterCount(); iD++) {
                    //                        cout<<"Vertex of particle #"<<iD<<"   " << mcpart->getDaughter(iD)->getVertex().at(0) << "     " << mcpart->getDaughter(iD)->getVertex().at(1) << "    " 
                    //                                << mcpart->getDaughter(iD)->getVertex().at(2) << endl;
                    //                    }

                    TLorentzVector L0, L1;
                    L0.SetPxPyPzE(mcpart->getDaughter(0)->getMomentum().at(0), mcpart->getDaughter(0)->getMomentum().at(1),
                            mcpart->getDaughter(0)->getMomentum().at(2), P0);
                    L1.SetPxPyPzE(mcpart->getDaughter(1)->getMomentum().at(0), mcpart->getDaughter(1)->getMomentum().at(1),
                            mcpart->getDaughter(1)->getMomentum().at(2), P1);

                    double Minv = TLorentzVector(L0 + L1).M();

                    //cout<<mcpart->getMass()<<"       "<<Minv<<endl;

                    //cout<<mcpart->getDaughterCount()<<"        "<<P0 + P1<<"      "<<Minv<<endl;


                    if (mcpart->getDaughterCount() == 2) {
                        h_Minv_PV0_MCParticle->Fill(P0 + P1, Minv);
                        h_Minv_P622_MCParticle->Fill(P622, Minv);
                        if (Minv < 0.048 || Minv > 0.052) {
                            MCStat1 = true;
                        }
                    }
                }

            }

            // ==========================


            h_cl_E_Xc_ep1->Fill(((EcalCluster*) ep->getClusters()->At(0))->getPosition().at(0), ((EcalCluster*) ep->getClusters()->At(0))->getEnergy());
            h_cl_E_Xc_em1->Fill(((EcalCluster*) em->getClusters()->At(0))->getPosition().at(0), ((EcalCluster*) em->getClusters()->At(0))->getEnergy());


            // ===============================================================================================
            // ====== Selecting Final V0 candidates
            // ===============================================================================================

            //            IsPV0Max = IsPV0MaxCut(PV0);
            //            IsPV0Min = IsPV0MinCut(PV0);
            IsPV0Max = IsPV0MaxCut(PV0ScSm);
            IsPV0Min = IsPV0MinCut(PV0ScSm);
            IscldT = IscldTCut(cl_em, cl_ep);
            IsemClTrkdT = IsTrkClusterdTMatch(trk_em, cl_em);
            IsepClTrkdT = IsTrkClusterdTMatch(trk_ep, cl_ep);
            IsemTrkClMatch = IsTrkClusterdXMatch(trk_em, cl_em);
            IsepTrkClMatch = IsTrkClusterdXMatch(trk_ep, cl_ep);
            IsPem = IsEmMaxMomCut(P_em);
            IsD0ep = IsD0Cut(d0_ep);


            FillMCHists(ev, em, ep);
            if (IsPV0Max && IscldT) {
                FillfRadHists(ev, cur_v0);
            }


            //cout<<P_em<<"    "<<PemScSm<<"                         "<<P_ep<<"    "<<PepScSm<<endl;
            //cout<<PV0<<"     "<<P_em + P_ep<<"    "<<PV0ScSm<<endl;

            // ===== This checks if the sample is Rad, and if yes then the electron from the current v0 should be
            // ===== matched to the gen electron, otherwise we don't want to use this v0, for other samples
            // ===== we don't care, and the v0 should be used.
            if (isRadAndRecoil) {
                continue;
            }

            h_PV0Max_All->Fill(PV0);
            h_PV0ScSmMax_All->Fill(PV0ScSm);
            h_Minv_PV0Max_All->Fill(PV0, mV0);
            if (CheckAllOtherCuts("PV0Max")) {
                h_Minv_PMax_Final1->Fill(mV0);
                h_PV0_Test1->Fill(PV0);
                h_PV0Max_AllBut->Fill(PV0);
                h_PV0ScSmMax_AllBut->Fill(PV0ScSm);
                h_Minv_PV0Max_AllBut->Fill(PV0, mV0);

                if (IsPV0Max) {
                    h_PV0Max_CutEffect->Fill(PV0);
                    h_PV0ScSmMax_CutEffect->Fill(PV0ScSm);
                    h_Minv_PV0Max_CutEffect->Fill(PV0, mV0);
                }
            }

            MinvBin = h_MinvBins1->FindBin(mV0) - 1;
            h_PV0Min_MinvBin_All[MinvBin]->Fill(PV0);
            h_PV0Min_All->Fill(PV0);
            h_PSumMin_All->Fill(PSum);
            h_PSumScSmMin_All->Fill(PSumScSm);
            h_PV0ScSmMin_All->Fill(PV0ScSm);
            h_Minv_PV0Min_All->Fill(PV0, mV0);

            if (CheckAllOtherCuts("PV0Min")) {
                h_Minv_PMin_Final1->Fill(mV0);
                h_PV03->Fill(PV0);
                h_PV0_Test2->Fill(PV0);
                h_PV0Min_AllBut->Fill(PV0);
                h_PSumMin_AllBut->Fill(PSum);
                h_PSumScSmMin_AllBut->Fill(PSumScSm);
                h_PV0ScSmMin_AllBut->Fill(PV0ScSm);

                h_Minv_PV0Min_AllBut->Fill(PV0, mV0);

                h_PemPep1->Fill(P_em, P_ep);
                h_PV0Min_MinvBin_AllBut[MinvBin]->Fill(PV0);

                if (IsPV0Min) {
                    h_PV0Min_CutEffect->Fill(PV0);
                    h_PSumMin_CutEffect->Fill(PSum);
                    h_PSumScSmMin_CutEffect->Fill(PSumScSm);
                    h_PV0ScSmMin_CutEffect->Fill(PV0ScSm);
                    h_Minv_PV0Min_CutEffect->Fill(PV0, mV0);
                    h_PV0Min_MinvBin_CutEffect[MinvBin]->Fill(PV0);
                }
            }


            h_clDt_All->Fill(t_cl_ep - t_cl_em);
            if (CheckAllOtherCuts("cldT")) {
                h_Minv_cldT_Final1->Fill(mV0);
                h_PV0_Test3->Fill(PV0);

                h_cl_dt_Nminus1->Fill(t_cl_ep - t_cl_em);
                h_clDt_AllBut->Fill(t_cl_ep - t_cl_em);

                if (IscldT) {
                    h_clDt_CutEffect->Fill(t_cl_ep - t_cl_em);
                }
            }


            FilldtP_ep(cur_v0, ep, P_ep, ClTrkDt_ep);
            FilldtP_em(cur_v0, em, P_em, ClTrkDt_em);


            FilldXP_ep(cur_v0, ep, P_ep, dX_ep);
            FilldXP_em(cur_v0, em, P_em, dX_em);


            h_Pem_All->Fill(P_em);
            if (CheckAllOtherCuts("Pem")) {
                h_Minv_Pem_Final1->Fill(mV0);
                h_PV0_Test8->Fill(PV0);

                h_Pem_Nminus1->Fill(P_em);
                h_Pem_AllBut->Fill(P_em);

                if (IsPem) {
                    h_Pem_CutEffect->Fill(P_em);
                }
            }

            h_d0_ep_All->Fill(d0_ep);
            if (CheckAllOtherCuts("d0ep")) {
                h_Minv_d0ep_Final1->Fill(mV0);
                h_PV0_Test9->Fill(PV0);

                h_d0_ep_Nminus1->Fill(d0_ep);
                h_d0_ep_AllBut->Fill(d0_ep);

                if (IsD0ep) {
                    h_Minv_Final1->Fill(mV0);
                    h_PV04->Fill(PV0);
                    h_d0_ep_CutEffect->Fill(d0_ep);


                    n_realV0 = n_realV0 + 1;
                }
            }



            // =============================== Do Not Remove the following line ============================            
            IsD0ep = IsD0Cut(d0_ep);
            isLarged0ep = IsLargeD0(d0_ep);
            // =============================== Do Not Remove the   above line   ============================ 

            FillLargeD0Hists(mV0, P_em, P_ep);


            if (IsPV0Max && IsPV0Min && IscldT /*&& IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsPem */) {
                CutsKey = GetCutsKey();

                FillPositDistributions(ep);

                h_Pemep_Final->Fill(P_em, P_ep);

                m_v_ee[CutsKey].push_back(mV0);
                m_v_PV0[CutsKey].push_back(PV0);

                FillVectorOfCutsKeys();

                for (int iCut = 0; iCut < v_CutsKeys.size(); iCut++) {
                    m_v_Minv_General[v_CutsKeys.at(iCut)].push_back(mV0);
                    m_v_PV0_General[v_CutsKeys.at(iCut)].push_back(PV0);
                    m_v_PV0ScSm_General[v_CutsKeys.at(iCut)].push_back(PV0ScSm);
                    m_v_MinvScSm_General[v_CutsKeys.at(iCut)].push_back(M_TCSmSc);
                    m_v_MinvScSmErrPos_General[v_CutsKeys.at(iCut)].push_back(M_TCSmScErrPos);
                    m_v_MinvScSmErrNeg_General[v_CutsKeys.at(iCut)].push_back(M_TCSmScErrNeg);

                    m_v_ep_General[v_CutsKeys.at(iCut)].push_back(ep);
                    m_v_em_General[v_CutsKeys.at(iCut)].push_back(em);

                    if (true_em_match) {
                        m_v_MinvTrue_General[v_CutsKeys.at(iCut)].push_back(trueMass);
                    }
                }

            }


        }
        h_nV0_2->Fill(n_realV0);


        for (map<int, vector<double> >::iterator it = m_v_ee.begin(); it != m_v_ee.end(); it++) {

            int CurCutKey = it->first;
            int nCurV0 = it->second.size();
            bool SingleV0 = (nCurV0 == 1);

            int HistKey = SingleV0 | CurCutKey << 1;
            //            cout << nCurV0 << endl;
            //            cout << SingleV0 << "    " << CurCutKey << "    " << HistKey << endl;

            for (int iV0 = 0; iV0 < nCurV0; iV0++) {
                m_h_Minv[HistKey]->Fill((it->second).at(iV0));
                m_h_PV0[HistKey]->Fill((m_v_PV0[CurCutKey]).at(iV0));
            }

        }
        // ============= When everything is done with the vector masses and PV0, we can rest it again
        m_v_ee.clear();
        m_v_PV0.clear();


        for (map<int, vector<double> >::iterator it = m_v_Minv_General.begin(); it != m_v_Minv_General.end(); it++) {
            int CurCutKey = it->first;
            int nCurV0 = it->second.size();
            bool SingleV0 = (nCurV0 == 1);



            int HistKey = SingleV0 | CurCutKey << 1;

            //            cout << nCurV0 << endl;
            //            cout << SingleV0 << "    " << CurCutKey << "    " << HistKey << endl;

            std::sort(m_v_ep_General[CurCutKey].begin(), m_v_ep_General[CurCutKey].end());
            int uniqueepCount = std::unique(m_v_ep_General[CurCutKey].begin(), m_v_ep_General[CurCutKey].end()) - m_v_ep_General[CurCutKey].begin();

            std::sort(m_v_em_General[CurCutKey].begin(), m_v_em_General[CurCutKey].end());
            int uniqueemCount = std::unique(m_v_em_General[CurCutKey].begin(), m_v_em_General[CurCutKey].end()) - m_v_em_General[CurCutKey].begin();



            for (int iV0 = 0; iV0 < nCurV0; iV0++) {
                m_h_Minv_General[HistKey]->Fill((it->second).at(iV0));
                m_h_MinvScSm_General[HistKey]->Fill(m_v_MinvScSm_General[CurCutKey].at(iV0));
                m_h_PV0_General[HistKey]->Fill(m_v_PV0_General[CurCutKey].at(iV0));

                //m_h_Minv_GeneralLargeBins[HistKey]->Fill( m_v_MinvTrue_General[CurCutKey].at(iV0) );
                m_h_Minv_GeneralLargeBins[HistKey]->Fill((it->second).at(iV0));
                m_h_PV0_GeneralLargeBins[HistKey]->Fill(m_v_PV0_General[CurCutKey].at(iV0));
                m_h_PV0ScSm_GeneralLargeBins[HistKey]->Fill(m_v_PV0ScSm_General[CurCutKey].at(iV0));

                m_h_MinvScSm_GeneralLargeBins[HistKey]->Fill(m_v_MinvScSm_General[CurCutKey].at(iV0));
                m_h_MinvScSm_GeneralVarBins[HistKey]->Fill(m_v_MinvScSm_General[CurCutKey].at(iV0));
                m_h_MinvScSmErrPos_GeneralLargeBins[HistKey]->Fill(m_v_MinvScSmErrPos_General[CurCutKey].at(iV0));
                m_h_MinvScSmErrNeg_GeneralLargeBins[HistKey]->Fill(m_v_MinvScSmErrNeg_General[CurCutKey].at(iV0));

                m_h_unique_ep_General[HistKey]->Fill(nCurV0, uniqueepCount);
                m_h_unique_em_General[HistKey]->Fill(nCurV0, uniqueemCount);

                if (isRad || isAp) {

                    if (m_v_MinvTrue_General[CurCutKey].size() > 0) {

                        m_h_Minv_GeneralTrue[HistKey]->Fill(m_v_MinvTrue_General[CurCutKey].at(iV0));
                        m_h_MinvTrue_GeneralLargeBins[HistKey]->Fill(m_v_MinvTrue_General[CurCutKey].at(iV0));
                        m_h_MinvTrue_GeneralVarBins[HistKey]->Fill(m_v_MinvTrue_General[CurCutKey].at(iV0));
                    }
                }
            }

            //            it->second.clear();
            //            it->second.shrink_to_fit();
            //
            //            m_v_PV0_General[CurCutKey].clear();
            //            m_v_PV0_General[CurCutKey].shrink_to_fit();
        }

        m_v_MinvScSmErrPos_General.clear();
        m_v_MinvScSmErrNeg_General.clear();
        m_v_MinvScSm_General.clear();
        m_v_Minv_General.clear();
        m_v_PV0_General.clear();
        m_v_PV0ScSm_General.clear();
        m_v_MinvTrue_General.clear();
        m_v_ep_General.clear();
        m_v_em_General.clear();

        //cout<<m_v_ee[0].size()<<"    "<<m_v_ee[1].size()<<endl;


    }

    gDirectory->Write();
    return 0;
}