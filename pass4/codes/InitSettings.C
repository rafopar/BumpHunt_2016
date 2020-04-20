#include "setting_2016_pass1.h"
#include <TF1.h>
#include <set>
#include <vector>

void InitVariables(std::string dataSet) {


    rnd1 = new TRandom();

    // Defing available values for Ap simulation
    ApMassSet.insert(30);
    ApMassSet.insert(35);
    ApMassSet.insert(40);
    ApMassSet.insert(45);
    ApMassSet.insert(50);
    ApMassSet.insert(55);
    ApMassSet.insert(60);
    ApMassSet.insert(65);
    ApMassSet.insert(70);
    ApMassSet.insert(75);
    ApMassSet.insert(80);
    ApMassSet.insert(85);
    ApMassSet.insert(90);
    ApMassSet.insert(95);
    ApMassSet.insert(100);
    ApMassSet.insert(105);
    ApMassSet.insert(110);
    ApMassSet.insert(115);
    ApMassSet.insert(120);
    ApMassSet.insert(125);
    ApMassSet.insert(130);
    ApMassSet.insert(135);
    ApMassSet.insert(140);
    ApMassSet.insert(145);
    ApMassSet.insert(150);
    ApMassSet.insert(155);
    ApMassSet.insert(160);
    ApMassSet.insert(165);
    ApMassSet.insert(170);
    ApMassSet.insert(175);


    // =================== Initialize map of vectors of invariant mass
    m_v_ee[0] = {};
    m_v_ee[1] = {};
    m_v_ee[2] = {};
    m_v_ee[3] = {};

    m_v_PSum[0] = {};
    m_v_PSum[1] = {};
    m_v_PSum[2] = {};
    m_v_PSum[3] = {};

    m_v_Minv_General[0] = {};
    m_v_Minv_General[1] = {};
    m_v_Minv_General[2] = {};
    m_v_Minv_General[3] = {};

    m_v_MinvScSm_General[0] = {};
    m_v_MinvScSm_General[1] = {};
    m_v_MinvScSm_General[2] = {};
    m_v_MinvScSm_General[3] = {};

    m_v_MinvTrue_General[0] = {};
    m_v_MinvTrue_General[1] = {};
    m_v_MinvTrue_General[2] = {};
    m_v_MinvTrue_General[3] = {};

    m_v_PSum_General[0] = {};
    m_v_PSum_General[1] = {};
    m_v_PSum_General[2] = {};
    m_v_PSum_General[3] = {};

    m_v_PSumScSm_General[0] = {};
    m_v_PSumScSm_General[1] = {};
    m_v_PSumScSm_General[2] = {};
    m_v_PSumScSm_General[3] = {};

    // ========== Initialize the vector of CutKeys
    v_CutsKeys = {};

    // ======= We want to study PSum distributions for different Minv ranges, below are defined ranges for these bins
    double MinvBins[nMinvBins + 1] = {0., 0.02, 0.04, 0.06, 0.08, 0.1, 0.12, 0.14, 0.16, 0.18, 0.2, 0.22, 0.24};
    h_MinvBins1 = new TH1D("h_MinvBins1", "", nMinvBins, MinvBins);

    InitSmearPars();

    // ========================================================================
    // ========= Let's figure it out which data source will be analyzed Rad, Tri, Date etc
    // ========================================================================

    isData = false;
    isTri = false;
    isRad = false;
    isWab = false;
    isMC = false;

    if (dataSet.compare("Data") == 0) {
        isData = true;
        //inpFileName = "../Data/hps_008099.All_dst_4.2.root";
        inpFileName = "../Data/hps_008099_All_v0_4.2.root";
        //inpFileName = "../Data/V0_Blinded_7803.root";

        if (isEventSelection) {
            outFileName = "EventSelection_Data.root";
        } else if (isTrkClusterMatching) {
            outFileName = "TrkClustMatching_Data.root";
        } else if (isECalTimeStudies) {
            outFileName = "ECalTimingStudies_Data.root";
        }


        trkClustMatchFileName = "TrkClustMatching_Data.root";
        cutHistFileName = "EvSelectionCuts_Data.root";
        cutHistFileName2 = "EvSelectionCutHists_Data.root";
    } else {

        isMC = true;

        InitTrkKillingHist();

        cutHistFileName = "EvSelectionCuts_Data.root";

        if (dataSet.compare("WAB") == 0) {
            isWab = true;
            inpFileName = "../Data/wab_beam_pass4.root";
            //inpFileName = "../Data/WABBT_Pass4_pairs1.root";
            //inpFileName = "../Data/WABBT_Pass4_pairs1.root";

            if (isEventSelection) {
                outFileName = "EventSelection_WAB.root";
            } else if (isTrkClusterMatching) {
                outFileName = "TrkClustMatching_WAB.root";
            } else if (isECalTimeStudies) {
                outFileName = "ECalTimingStudies_WAB.root";
            }

            trkClustMatchFileName = "TrkClustMatching_WAB.root";
            cutHistFileName = "EvSelectionCuts_WAB.root";
            cutHistFileName2 = "EvSelectionCutHists_WAB.root";

        } else if (dataSet.compare("Rad") == 0) {
            isRad = true;
            //inpFileName = "../Data/RAD_Beam_pass4.root";
            //inpFileName = "../Data/Rad_Beam_pass4.root";
            inpFileName = "../Data/RadBeamWithTruth.root";

            if (isEventSelection) {
                outFileName = "EventSelection_Rad.root";
            } else if (isTrkClusterMatching) {
                outFileName = "TrkClustMatching_Rad.root";
            } else if (isECalTimeStudies) {
                outFileName = "ECalTimingStudies_Rad.root";
            }

            trkClustMatchFileName = "TrkClustMatching_Rad.root";
            cutHistFileName = "EvSelectionCuts_Rad.root";
            cutHistFileName2 = "EvSelectionCutHists_Rad.root";

        } else if (dataSet.compare("Tri") == 0) {
            isTri = true;
            inpFileName = "../Data/tritrig_pass4.root";
            //inpFileName = "../Data/tritrig_Pass4_iss640.root";
            //inpFileName = "../Data/tritrig_Pass4_Files1To200.root";

            if (isEventSelection) {
                outFileName = "EventSelection_Tri.root";
            } else if (isTrkClusterMatching) {
                outFileName = "TrkClustMatching_Tri.root";
            } else if (isECalTimeStudies) {
                outFileName = "ECalTimingStudies_Tri.root";
            }

            trkClustMatchFileName = "TrkClustMatching_Tri.root";
            cutHistFileName = "EvSelectionCuts_Tri.root";
            cutHistFileName2 = "EvSelectionCutHists_Tri.root";


        } else if (dataSet.compare("Ap") == 0) {
            isAp = true;
            if (ApMassSet.count(ApMass) > 0) {

                //inpFileName = Form("../Data/Ap_%dMeV.root", ApMass);
                //inpFileName = Form("../Data/AP_TargNominal_%d_MeV.root", ApMass);
                inpFileName = Form("../Data/AP_TargM0p5mm_%d_MeV.root", ApMass);
                //inpFileName = Form("../Data/AP_TargP0p5mm_%d_MeV.root", ApMass);
                //inpFileName = Form("../Data/Ap_%dMeV_Dec11_2019.root", ApMass);
                outFileName = Form("EventSelection_Ap_%dMeV.root", ApMass);


                if (isEventSelection) {
                    outFileName = Form("EventSelection_Ap_%d_MeV.root", ApMass);
                } else if (isTrkClusterMatching) {
                    outFileName = Form("TrkClustMatching_Ap_%d_MeV.root", ApMass);
                } else if (isECalTimeStudies) {
                    outFileName = Form("ECalTimingStudies_Ap_%d_MeV.root", ApMass);
                }

                trkClustMatchFileName = Form("TrkClustMatching_Ap_%d_MeV.root", ApMass);
                cutHistFileName = Form("EvSelectionCuts_Ap_%d_MeV.root", ApMass);
                cutHistFileName2 = Form("EvSelectionCutHists_Ap_%d_MeV.root", ApMass);


            } else {
                cout << "Wrong, or No Ap mass is provided. The mass is " << ApMass << endl;
                cout << "Exiting" << endl;
                exit(1);
            }
        } else {

            cout << "As a data set you provided " << dataSet << endl;
            cout << "This is not a correct dataset. Exiting" << endl;
            exit(1);
        }
    }


    file_in = new TFile(inpFileName.c_str());

    if (isEventSelection) {
        file_trkClustMatch = new TFile(trkClustMatchFileName.c_str(), "Read");
        file_CutHists = new TFile(cutHistFileName.c_str(), "Read");
        file_CutHists2 = new TFile(cutHistFileName2.c_str(), "Recreate");
    }

    f_clTBotUpLim = new TF1("f_clTBotUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTBotLowLim = new TF1("f_clTBotLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopUpLim = new TF1("f_clTTopUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopLowLim = new TF1("f_clTTopLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);


    f_fRad_Mass = new TF1("f_fRad_Mass", "[0] + x*( [1] + x*([2] +  x*([3] + x*([4] + x*([5] + x*([6] + x*([7] + x*([8] + x*[9])))))) ) ) ", 0., 0.25);
    f_fRad_Mass->SetParameters(-853094.35571679403074085712432861328125, 54359868.78713452816009521484375, -1289945815.2204229831695556640625,
            15968338273.346767425537109375, -114890347220.0277557373046875, 486617910661.73077392578125, -1105011911726.684814453125, 762692693207.0887451171875,
            1678645670596.710205078125, -2734109241360.267578125);


    // ============== =============================== ====================
    // ============== Track-Cluster Matchin functions ====================
    // ============== =============================== ====================

    // ==== Postitive tracks ====
    f_dXTopWithL6Pos_TightUpperLim = new TF1("f_dXTopWithL6Pos_TightUpperLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_dXTopWithL6Pos_TightLowerLim = new TF1("f_dXTopWithL6Pos_TightLowerLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);

    f_dXTopNoL6Pos_TightUpperLim = new TF1("f_dXTopNoL6Pos_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXTopNoL6Pos_TightLowerLim = new TF1("f_dXTopNoL6Pos_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);


    f_dXBotWithL6Pos_TightUpperLim = new TF1("f_dXBotWithL6Pos_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXBotWithL6Pos_TightLowerLim = new TF1("f_dXBotWithL6Pos_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);

    f_dXBotNoL6Pos_TightUpperLim = new TF1("f_dXBotNoL6Pos_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXBotNoL6Pos_TightLowerLim = new TF1("f_dXBotNoL6Pos_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);


    // ==== Postitive tracks ====
    f_dXTopWithL6Neg_TightUpperLim = new TF1("f_dXTopWithL6Neg_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXTopWithL6Neg_TightLowerLim = new TF1("f_dXTopWithL6Neg_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);

    f_dXTopNoL6Neg_TightUpperLim = new TF1("f_dXTopNoL6Neg_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXTopNoL6Neg_TightLowerLim = new TF1("f_dXTopNoL6Neg_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);


    f_dXBotWithL6Neg_TightUpperLim = new TF1("f_dXBotWithL6Neg_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXBotWithL6Neg_TightLowerLim = new TF1("f_dXBotWithL6Neg_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);

    f_dXBotNoL6Neg_TightUpperLim = new TF1("f_dXBotNoL6Neg_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_dXBotNoL6Neg_TightLowerLim = new TF1("f_dXBotNoL6Neg_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);


    // === ================ ===
    // === Time matching 
    // === ================ ===

    f_trkCl_dt_Top_TightUpperLim = new TF1("f_trkCl_dt_Top_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_trkCl_dt_Top_TightLowerLim = new TF1("f_trkCl_dt_Top_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_trkCl_dt_Bot_TightUpperLim = new TF1("f_trkCl_dt_Bot_TightUpperLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);
    f_trkCl_dt_Bot_TightLowerLim = new TF1("f_trkCl_dt_Bot_TightLowerLim", "[0] + x*( [1] + x*([2] + x*[3]) )", 0., 2.5);


    // === ============= ====
    // === Other Functions ====
    // === ============= ====
    f_TrashUp_dX_Top_PosWithL6 = new TF1("f_TrashUp_dX_Top_PosWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Top_PosWithL6 = new TF1("f_TrashLow_dX_Top_PosWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Top_PosNoL6 = new TF1("f_TrashUp_dX_Top_PosNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Top_PosNoL6 = new TF1("f_TrashLow_dX_Top_PosNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Bot_PosWithL6 = new TF1("f_TrashUp_dX_Bot_PosWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Bot_PosWithL6 = new TF1("f_TrashLow_dX_Bot_PosWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Bot_PosNoL6 = new TF1("f_TrashUp_dX_Bot_PosNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Bot_PosNoL6 = new TF1("f_TrashLow_dX_Bot_PosNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Top_NegWithL6 = new TF1("f_TrashUp_dX_Top_NegWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Top_NegWithL6 = new TF1("f_TrashLow_dX_Top_NegWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Top_NegNoL6 = new TF1("f_TrashUp_dX_Top_NegNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Top_NegNoL6 = new TF1("f_TrashLow_dX_Top_NegNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Bot_NegWithL6 = new TF1("f_TrashUP_dX_Bot_NegWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Bot_NegWithL6 = new TF1("f_TrashLow_dX_Bot_NegWithL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashUp_dX_Bot_NegNoL6 = new TF1("f_TrashUP_dX_Bot_NegNoL6", "[0] + [1]/(x - [2])", 0., 2.2);
    f_TrashLow_dX_Bot_NegNoL6 = new TF1("f_TrashLow_dX_Bot_NegNoL6", "[0] + [1]/(x - [2])", 0., 2.2);

    if (isData) {


        CL_trk_time_Offset = CL_trk_time_Offset_Data;

        chi2NDFTighCut = chi2NDFTighCut_Data;

        ep_d0TightCutMax = ep_d0TightCutMax_Data;
        ep_d0TightCutMin = ep_d0TightCutMin_Data;

        em_d0TightCutMax = em_d0TightCutMax_Data;
        em_d0TightCutMin = em_d0TightCutMin_Data;

        cl_dTCut_Tight = cl_dTCut_Tight_Data;
        cl_dTcut = cl_dTcut_Data;

        Pem_MaxTight = Pem_MaxTight_Data;

        Pem_MaxCut = Pem_MaxCut_Data;
        PsumCutMax = PsumCutMax_Data;
        PsumCutMin = PsumCutMin_Data;
        d0_cut = d0_cut_Data;
        largeD0Cut = largeD0Cut_Data;

        f_clTBotUpLim->SetParameters(58.5, 3.40282, -1.00306);
        f_clTBotLowLim->SetParameters(45.51, 7.55268, -1.89745);
        f_clTTopUpLim->SetParameters(58.4842, 6.33371, -3.54136);
        f_clTTopLowLim->SetParameters(49.9385, 1.38759, 0.0484333);

        f_dXTopWithL6Pos_TightUpperLim->SetParameters(-5.98409, 26.061, -11.688);
        f_dXTopWithL6Pos_TightLowerLim->SetParameters(-13.1351, 13.1293, -2.22706);

        f_dXTopNoL6Pos_TightUpperLim->SetParameters(-39.666, 224.024, -290.323, 111.805);
        f_dXTopNoL6Pos_TightLowerLim->SetParameters(-80.858, 160.212, -89.0708, 9.70467);

        f_dXBotWithL6Pos_TightUpperLim->SetParameters(-12.2105, 53.4947, -47.773, 12.7416);
        f_dXBotWithL6Pos_TightLowerLim->SetParameters(-4.78296, -23.0808, 25.5697, -6.67282);

        f_dXBotNoL6Pos_TightUpperLim->SetParameters(-61.102, 277.35, -330.309, 117.842);
        f_dXBotNoL6Pos_TightLowerLim->SetParameters(-91.7703, 208.185, -162.909, 41.4299);


        f_dXTopWithL6Neg_TightUpperLim->SetParameters(-17.1488, 73.6343, -62.0659, 15.5421);
        f_dXTopWithL6Neg_TightLowerLim->SetParameters(13.9718, -64.9545, 59.9272, -15.7356);

        f_dXTopNoL6Neg_TightUpperLim->SetParameters(67.1155, -135.967, 102.147, -25.9778);
        f_dXTopNoL6Neg_TightLowerLim->SetParameters(12.7772, -95.4775, 119.617, -41.3284);

        f_dXBotWithL6Neg_TightUpperLim->SetParameters(-1.77583, 21.8994, -20.4999, 5.22121);
        f_dXBotWithL6Neg_TightLowerLim->SetParameters(14.5461, -62.4698, 53.6471, -13.6255);

        f_dXBotNoL6Neg_TightUpperLim->SetParameters(44.0713, -58.8599, 3.79157, 10.3651);
        f_dXBotNoL6Neg_TightLowerLim->SetParameters(-1.81492, -55.8293, 84.5025, -34.4477);

        f_trkCl_dt_Top_TightUpperLim->SetParameters(-6.56042, 27.9583, -25.605, 6.9747);
        f_trkCl_dt_Top_TightLowerLim->SetParameters(-1.55686, -3.51391, 4.19438, -1.08659);

        f_trkCl_dt_Bot_TightUpperLim->SetParameters(-6.15725, 25.4919, -22.3805, 5.73573);
        f_trkCl_dt_Bot_TightLowerLim->SetParameters(-3.33916, -0.537733, 2.06764, -0.629115);


        //        f_TrashUp_dX_Top_PosWithL6->SetParameters(7., 20., -0.5);
        //        f_TrashLow_dX_Top_PosWithL6->SetParameters(7., -25., 0.);
        //        f_TrashUp_dX_Top_PosNoL6->SetParameters(0., 16., 0.24);
        //        f_TrashLow_dX_Top_PosNoL6->SetParameters(5., -15., 0.24);
        //        f_TrashUp_dX_Bot_PosWithL6->SetParameters(-1., 25., -0.25);
        //        f_TrashLow_dX_Bot_PosWithL6->SetParameters(1., -25., -0.25);
        //        f_TrashUp_dX_Bot_PosNoL6->SetParameters(0., 16., 0.24);
        //        f_TrashLow_dX_Bot_PosNoL6->SetParameters(5., -18., 0.18);
        //        f_TrashUp_dX_Top_NegWithL6->SetParameters(4., 25., -0.45);
        //        f_TrashLow_dX_Top_NegWithL6->SetParameters(-4., -25., -0.45);
        //        f_TrashUp_dX_Top_NegNoL6->SetParameters(2., 15., 0.24);
        //        f_TrashLow_dX_Top_NegNoL6->SetParameters(0., -16., 0.24);
        //        f_TrashUp_dX_Bot_NegWithL6->SetParameters(11., 25., -1.95);
        //        f_TrashLow_dX_Bot_NegWithL6->SetParameters(-11., -25., -1.95);
        //        f_TrashUp_dX_Bot_NegNoL6->SetParameters(3., 10., 0.25);
        //        f_TrashLow_dX_Bot_NegNoL6->SetParameters(0., -16., 0.24);

        f_TrashUp_dX_Top_PosWithL6->SetParameters(7., 25., 0.);
        f_TrashLow_dX_Top_PosWithL6->SetParameters(4., -25., 0.);
        f_TrashUp_dX_Top_PosNoL6->SetParameters(-5., 45., -0.4);
        f_TrashLow_dX_Top_PosNoL6->SetParameters(7., -22., 0.1);
        f_TrashUp_dX_Bot_PosWithL6->SetParameters(5., 25., -0.25);
        f_TrashLow_dX_Bot_PosWithL6->SetParameters(-4., -25., -0.25);
        f_TrashUp_dX_Bot_PosNoL6->SetParameters(-10., 46., -0.2);
        f_TrashLow_dX_Bot_PosNoL6->SetParameters(5., -25., 0.01);

        f_TrashLow_dX_Top_NegWithL6->SetParameters(10., -50., -0.4);
        f_TrashUp_dX_Top_NegWithL6->SetParameters(5., 35., -0.65);
        f_TrashUp_dX_Top_NegNoL6->SetParameters(-10., 37., -0.1);
        f_TrashLow_dX_Top_NegNoL6->SetParameters(12., -40., -0.1);
        f_TrashUp_dX_Bot_NegWithL6->SetParameters(0., 65., -1.95);
        f_TrashLow_dX_Bot_NegWithL6->SetParameters(10., -105., -1.95);
        f_TrashUp_dX_Bot_NegNoL6->SetParameters(-15., 40., -0.2);
        f_TrashLow_dX_Bot_NegNoL6->SetParameters(-3., -25., -0.01);

        if (isEventSelection) {
            InitCutHistograms();
        }

    } else if (isMC) {

        CL_trk_time_Offset = CL_trk_time_Offset_tri;

        if (isWab) {
            CL_trk_time_Offset = CL_trk_time_Offset_WAB;
        } else if (isRad) {
            CL_trk_time_Offset = CL_trk_time_Offset_Rad;
        }

        chi2NDFTighCut = chi2NDFTighCut_MC;

        cl_dTCut_Tight = cl_dTCut_Tight_MC;

        Pem_MaxTight = Pem_MaxTight_MC;


        ep_d0TightCutMax = ep_d0TightCutMax_MC;
        ep_d0TightCutMin = ep_d0TightCutMin_MC;

        em_d0TightCutMax = em_d0TightCutMax_MC;
        em_d0TightCutMin = em_d0TightCutMin_MC;

        cl_dTcut = cl_dTcut_Data;

        Pem_MaxTight = Pem_MaxTight_Data;

        Pem_MaxCut = Pem_MaxCut_MC;
        PsumCutMax = PsumCutMax_MC;
        PsumCutMin = PsumCutMin_MC;
        d0_cut = d0_cut_MC;
        largeD0Cut = largeD0Cut_MC;

        f_clTBotUpLim->SetParameters(48., 0., 0.);
        f_clTBotLowLim->SetParameters(38, 0., 0.);
        f_clTTopUpLim->SetParameters(60., 0., 0.);
        f_clTTopLowLim->SetParameters(30., 0., 0.);


        // ==================================================================
        // ==================================================================
        // ======= As a temporary solution I will init functions with data
        // ======= values, but later these values should be adjusted for MC.
        // ==================================================================
        // ==================================================================

        f_dXTopWithL6Pos_TightUpperLim->SetParameters(-5.98409, 26.061, -11.688);
        f_dXTopWithL6Pos_TightLowerLim->SetParameters(-13.1351, 13.1293, -2.22706);

        f_dXTopNoL6Pos_TightUpperLim->SetParameters(-39.666, 224.024, -290.323, 111.805);
        f_dXTopNoL6Pos_TightLowerLim->SetParameters(-80.858, 160.212, -89.0708, 9.70467);

        f_dXBotWithL6Pos_TightUpperLim->SetParameters(-12.2105, 53.4947, -47.773, 12.7416);
        f_dXBotWithL6Pos_TightLowerLim->SetParameters(-4.78296, -23.0808, 25.5697, -6.67282);

        f_dXBotNoL6Pos_TightUpperLim->SetParameters(-61.102, 277.35, -330.309, 117.842);
        f_dXBotNoL6Pos_TightLowerLim->SetParameters(-91.7703, 208.185, -162.909, 41.4299);


        f_dXTopWithL6Neg_TightUpperLim->SetParameters(-17.1488, 73.6343, -62.0659, 15.5421);
        f_dXTopWithL6Neg_TightLowerLim->SetParameters(13.9718, -64.9545, 59.9272, -15.7356);

        f_dXTopNoL6Neg_TightUpperLim->SetParameters(67.1155, -135.967, 102.147, -25.9778);
        f_dXTopNoL6Neg_TightLowerLim->SetParameters(12.7772, -95.4775, 119.617, -41.3284);

        f_dXBotWithL6Neg_TightUpperLim->SetParameters(-1.77583, 21.8994, -20.4999, 5.22121);
        f_dXBotWithL6Neg_TightLowerLim->SetParameters(14.5461, -62.4698, 53.6471, -13.6255);

        f_dXBotNoL6Neg_TightUpperLim->SetParameters(44.0713, -58.8599, 3.79157, 10.3651);
        f_dXBotNoL6Neg_TightLowerLim->SetParameters(-1.81492, -55.8293, 84.5025, -34.4477);

        f_trkCl_dt_Top_TightUpperLim->SetParameters(-6.56042, 27.9583, -25.605, 6.9747);
        f_trkCl_dt_Top_TightLowerLim->SetParameters(-1.55686, -3.51391, 4.19438, -1.08659);

        f_trkCl_dt_Bot_TightUpperLim->SetParameters(-6.15725, 25.4919, -22.3805, 5.73573);
        f_trkCl_dt_Bot_TightLowerLim->SetParameters(-3.33916, -0.537733, 2.06764, -0.629115);


        f_TrashUp_dX_Top_PosWithL6->SetParameters(4., 20., -0.5);
        f_TrashLow_dX_Top_PosWithL6->SetParameters(-2., -25., -0.75);
        f_TrashUp_dX_Top_PosNoL6->SetParameters(2., 16., 0.);
        f_TrashLow_dX_Top_PosNoL6->SetParameters(1., -15., 0.);
        f_TrashUp_dX_Bot_PosWithL6->SetParameters(-1., 25., -0.25);
        f_TrashLow_dX_Bot_PosWithL6->SetParameters(1., -25., -0.25);
        f_TrashUp_dX_Bot_PosNoL6->SetParameters(0., 16., 0.04);
        f_TrashLow_dX_Bot_PosNoL6->SetParameters(5., -18., 0.);
        f_TrashUp_dX_Top_NegWithL6->SetParameters(4., 25., -0.75);
        f_TrashLow_dX_Top_NegWithL6->SetParameters(-3., -25., -1.);
        f_TrashUp_dX_Top_NegNoL6->SetParameters(2., 15., -0.05);
        f_TrashLow_dX_Top_NegNoL6->SetParameters(4., -16., 0.24);
        f_TrashUp_dX_Bot_NegWithL6->SetParameters(8., 25., -1.95);
        f_TrashLow_dX_Bot_NegWithL6->SetParameters(0., -25., -0.5);
        f_TrashUp_dX_Bot_NegNoL6->SetParameters(0., 20., -0.12);
        f_TrashLow_dX_Bot_NegNoL6->SetParameters(12., -46., -0.54);

        if (isEventSelection) {
            InitCutHistograms();
        }

    }

    TFile *file_ECalTimeCorrections = new TFile("ECalTimeCorrections.root", "Read");

    h_time_Corrections = (TH2D*) file_ECalTimeCorrections->Get("h_cl_dtMeans1");


    h_SVTLayerBinning = new TH1D("h_SVTLayerBinning", "", nSVTLayers, SVTLayerBinnings);


    IsTightcldT = false;
    IsTightemClTrkdT = false;
    IsTightepClTrkdT = false;
    IsTightemTrkClMatch = false;
    IsTightepTrkClMatch = false;
    IsTightemtrkChi2 = false;
    IsTighteptrkChi2 = false;
    IsTightPem = false;
    IsTightD0ep = false;
    IsTightD0em = false;

    // ==== We want to open it at the end, that gDirectory->Write will try to save histos in this file ===
    file_out = new TFile(outFileName.c_str(), "Recreate");

    // =================== Initialize map of histograms with differ Cut conditions

    for (int ii = 0; ii < TMath::Power(2, NCutInQuestion); ii++) {
        m_h_Minv[ii] = new TH1D(Form("h_Minv_Final_%d", ii), "", 6000, 0., 0.3);
        m_h_Psum[ii] = new TH1D(Form("h_PSum_Final_%d", ii), "", 600, 0.7, 1.2 * Eb);

        m_h_Minv_General[ii] = new TH1D(Form("h_Minv_General_Final_%d", ii), "", 6000, 0., 0.3);
        m_h_MinvScSm_General[ii] = new TH1D(Form("h_MinvScSm_General_Final_%d", ii), "", 6000, 0., 0.3);
        m_h_Psum_General[ii] = new TH1D(Form("h_PSum_General_Final_%d", ii), "", 600, 0.7, 1.2 * Eb);
        m_h_Minv_GeneralLargeBins[ii] = new TH1D(Form("h_Minv_GeneralLargeBins_Final_%d", ii), "", 400, 0., 0.25);
        m_h_MinvTrue_GeneralLargeBins[ii] = new TH1D(Form("h_MinvTrue_GeneralLargeBins_Final_%d", ii), "", 400, 0., 0.25);
        m_h_Psum_GeneralLargeBins[ii] = new TH1D(Form("h_Psum_GeneralLargeBins_Final_%d", ii), "", 40, 1.6, 1.2 * Eb);
        m_h_PsumScSm_GeneralLargeBins[ii] = new TH1D(Form("h_PsumScSm_GeneralLargeBins_Final_%d", ii), "", 40, 1.6, 1.2 * Eb);
        m_h_MinvScSm_GeneralLargeBins[ii] = new TH1D(Form("h_MinvScSm_GeneralLargeBins_Final_%d", ii), "", 400, 0., 0.25);
    }

    if (isEventSelection) {
        InitGeneralHistograms();

    }
}

void ResetEventFlags() {

}

void ResetV0Flags() {
    IsTightcldT = false;
    IsTightemClTrkdT = false;
    IsTightepClTrkdT = false;
    IsTightemTrkClMatch = false;
    IsTightepTrkClMatch = false;
    IsTightemtrkChi2 = false;
    IsTighteptrkChi2 = false;
    IsTightPem = false;
    IsTightD0ep = false;
    IsTightD0em = false;

    IscldT = false;
    IsemClTrkdT = false;
    IsepClTrkdT = false;
    IsemTrkClMatch = false;
    IsepTrkClMatch = false;
    IsemtrkChi2 = false;
    IseptrkChi2 = false;
    IsPem = false;
    IsD0ep = false;
    IsD0em = false;
    IsPsumMax = false;
    IsPsumMin = false;
    isLarged0ep = false;

    isRadAndRecoil = false;

    MinvBin = 0;
    cl_ep = nullptr;
    cl_em = nullptr;

    CutsKey = 0;

    v_CutsKeys.clear();
    v_CutsKeys.shrink_to_fit();

    true_em_match = false;
    trueMass = 0.;
}

void CorrectClusterTime(EcalCluster* cl) {

    // ==== Just in case, we should make sure, the input data source is Data, not MC

    if (isData) {
        int y_ind = cl->getSeed()->getYCrystalIndex();
        int x_ind = cl->getSeed()->getXCrystalIndex();

        double t_corr = h_time_Corrections->GetBinContent(h_time_Corrections->FindBin(x_ind, y_ind));
        cl->setClusterTime(cl->getClusterTime() - t_corr);
    }
}

int GetCutsKey() {

    if (IsD0ep) {
        CutsKey = CutsKey | 1;
    }

    if (hasepL1) {
        CutsKey = CutsKey | 2;
    }

    return CutsKey;
}

void FillVectorOfCutsKeys() {

    // make sure the v_CutsKeys is empty
    if (v_CutsKeys.size() > 0) {
        v_CutsKeys.clear();
        v_CutsKeys.shrink_to_fit();
    }

    if (hasepL1 && IsD0ep) {
        v_CutsKeys.push_back(3); // 1 1
        v_CutsKeys.push_back(2); // 1 0
        v_CutsKeys.push_back(1); // 0 1
        v_CutsKeys.push_back(0); // 0 0
    } else if (!hasepL1 && IsD0ep) {
        v_CutsKeys.push_back(1); // 0 1
        v_CutsKeys.push_back(0); // 0 0
    } else if (hasepL1 && !IsD0ep) {
        v_CutsKeys.push_back(2); // 1 0
        v_CutsKeys.push_back(0); // 0 0
    } else {
        v_CutsKeys.push_back(0); // 0 0
    }
}

std::set<int> GetVerticalCrystalls(EcalCluster* cl) {
    std::set<int> vert_crystals;
    for (int i = 0; i < cl->getEcalHits()->GetSize(); i++) {
        vert_crystals.insert(((EcalHit*) cl->getEcalHits()->At(i))->getYCrystalIndex());
    }
    return vert_crystals;
}

bool CheckAllOtherCuts(std::string astr) {
    bool Stat = false;

    // ======= In the analysis workshop it was decided to drop the d0 cut
    // ======= So here we will manually set the "IsD0ep" as true;
    // ======= CORRECTION!!  Now it is not quite clear whether we should not cut on d0
    // ======= So we might want to put this cut again

    IsD0ep = true;
    IsepClTrkdT = true;
    IsemClTrkdT = true;
    IsepTrkClMatch = true;
    IsemTrkClMatch = true;
    IsPem = true;
    //===============================

    if (astr.compare("cldT") == 0) {
        Stat = IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsPem && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("emClTrkdT") == 0) {
        Stat = IscldT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("epClTrkdT") == 0) {
        Stat = IscldT && IsemClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("emClTrkMatch") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsepTrkClMatch && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("epClTrkMatch") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("Pem") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsD0ep && IsPsumMin && IsPsumMax;
    } else if (astr.compare("d0ep") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsPem && IsPsumMin && IsPsumMax;
    } else if (astr.compare("PsumMax") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsPem && IsD0ep && IsPsumMin;
    } else if (astr.compare("PsumMin") == 0) {
        Stat = IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch && IsPem && IsD0ep && IsPsumMax;
    } else {
        cout << "Wrong Argument is provided in the CheckTighCuts function.  Your argument is " << astr.c_str() << endl;
        cout << " The list of possible arguments are" << endl;
        cout << "\"cldT\"             Applies cuts to all other variables except the cluster time difference cut" << endl;
        cout << "\"emClTrkdT\"        Applies cuts to all other variables except the trk-cluster time diff cut for e-" << endl;
        cout << "\"epClTrkdT\"        Applies cuts to all other variables except the trk-cluster time diff cut for e+" << endl;
        cout << "\"emClTrkMatch\"     Applies cuts to all other variables except the trk-cluster Matching cut for e-" << endl;
        cout << "\"epClTrkMatch\"     Applies cuts to all other variables except the trk-cluster Matching cut for e+" << endl;
        cout << "\"Pem\"              Applies cuts to all other variables except the Electron momentum upper cut" << endl;
        cout << "\"d0ep\"             Applies cuts to all other variables except the d0 of e+ track" << endl;
        cout << "\"PsumMax\"             Applies cuts to all other variables except Psum max cut" << endl;
        cout << "\"PsumMin\"             Applies cuts to all other variables except Psum min cut" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return Stat;
}

bool CheckTightCuts(std::string astr) {

    bool CheckStatus = false;

    if (astr.compare("cldT") == 0) {
        CheckStatus = IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
        //cout<<IsTightemClTrkdT<<"   "<<IsTightepClTrkdT<<"   "<<IsTightemTrkClMatch<<"   "<<IsTightepTrkClMatch<<"   "<<IsTightemtrkChi2
        //        <<"   "<<IsTighteptrkChi2<<"   "<<IsTightPem<<endl;
    } else if (astr.compare("emClTrkdT") == 0) {
        CheckStatus = IsTightcldT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else if (astr.compare("epClTrkdT") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else if (astr.compare("emClTrkMatch") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else if (astr.compare("epClTrkMatch") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else if (astr.compare("emTrkChi2") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("epTrkChi2") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTightPem;
    } else if (astr.compare("Pem") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else {
        cout << "Wrong Argument is provided in the CheckTighCuts function.  Your argument is " << astr.c_str() << endl;
        cout << " The list of possible arguments are" << endl;
        cout << "\"cldT\"             Applies strong cuts to all other variables except the cluster time difference cut" << endl;
        cout << "\"emClTrkdT\"        Applies strong cuts to all other variables except the trk-cluster time diff cut for e-" << endl;
        cout << "\"epClTrkdT\"        Applies strong cuts to all other variables except the trk-cluster time diff cut for e+" << endl;
        cout << "\"emClTrkMatch\"     Applies strong cuts to all other variables except the trk-cluster Matching cut for e-" << endl;
        cout << "\"epClTrkMatch\"     Applies strong cuts to all other variables except the trk-cluster Matching cut for e+" << endl;
        cout << "\"emTrkChi2\"        Applies strong cuts to all other variables except the e- track chi2 cut" << endl;
        cout << "\"epTrkChi2\"        Applies strong cuts to all other variables except the e+ track chi2 cut" << endl;
        cout << "\"Pem\"              Applies strong cuts to all other variables except the Electron momentum upper cut" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return CheckStatus;
}

bool IsCldtTightCutPass(EcalCluster* cl1, EcalCluster* cl2) {

    if (cl1->getPosition().at(1) * cl2->getPosition().at(1) > 0) {
        cout << "In function IsCldtTightCutPass clusters should be in opposite half" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return (TMath::Abs(cl1->getClusterTime() - cl2->getClusterTime()) < cl_dTCut_Tight);
}

bool IsTightChi2NdfCutPassed(GblTrack* trk) {

    bool checkStatus = false;

    // For the "Tight" chi2/NDF we didn't see any significant difference
    // wrt 5/6 hits tracks, and whether the track is in the Bottom or Top



    if (trk->getChi2() / (2. * (trk->getSvtHits()->GetSize()) - 5.) < chi2NDFTighCut) {
        checkStatus = true;
    }

    return checkStatus;
}

bool IsTightTrkClust_dtCutPassed(GblTrack *trk, EcalCluster *cl) {
    bool timeMatch = false;

    if (!(trk->getPositionAtEcal().at(1) * cl->getPosition().at(1) > 0)) {
        cout << "Track and cluster are not in the same half " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    double P = GetMagnitude(trk->getMomentum());
    double dt = cl->getClusterTime() - CL_trk_time_Offset - trk->getTrackTime();

    if (cl->getPosition().at(1) > 0) {
        timeMatch = (dt > f_trkCl_dt_Top_TightLowerLim->Eval(P)) && (dt < f_trkCl_dt_Top_TightUpperLim->Eval(P));
    } else {
        timeMatch = (dt > f_trkCl_dt_Bot_TightLowerLim->Eval(P)) && (dt < f_trkCl_dt_Bot_TightUpperLim->Eval(P));
    }

    return timeMatch;
}

bool IsTightTrkClust_dXCutPassed(GblTrack *trk, EcalCluster *cl) {
    bool posMatch = false;

    // ==== 1st check whether if the trk and cluster are in the same detector hals

    if (!(trk->getPositionAtEcal().at(1) * cl->getPosition().at(1) > 0)) {
        cout << "Track and cluster are not in the same half " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    double P = GetMagnitude(trk->getMomentum());


    double dX = cl->getPosition().at(0) - trk->getPositionAtEcal().at(0);
    bool HasHitInL6 = HasL6Hit(trk);
    int charge = trk->getCharge();

    if (cl->getPosition().at(1) > 0) {

        if (charge > 0) {
            if (HasHitInL6) {
                posMatch = (dX > f_dXTopWithL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXTopWithL6Pos_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXTopNoL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXTopNoL6Pos_TightUpperLim->Eval(P));
            }
        } else {
            if (HasHitInL6) {
                posMatch = (dX > f_dXTopWithL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXTopWithL6Neg_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXTopNoL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXTopNoL6Neg_TightUpperLim->Eval(P));
            }
        }

    } else {
        if (charge > 0) {
            if (HasHitInL6) {
                posMatch = (dX > f_dXBotWithL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXBotWithL6Pos_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXBotNoL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXBotNoL6Pos_TightUpperLim->Eval(P));
            }
        } else {
            if (HasHitInL6) {
                posMatch = (dX > f_dXBotWithL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXBotWithL6Neg_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXBotNoL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXBotNoL6Neg_TightUpperLim->Eval(P));
            }
        }
    }

    return posMatch;
}

bool IsTightTrkClustCutPassed(GblTrack *trk, EcalCluster *cl) {

    bool checkStatus = false;
    bool timeMatch = false;
    bool posMatch = false;

    // ===== ========================================= ======
    // ===== First, let's check track cluster time difference ======
    // ===== ========================================= ======

    // ==== 1st check whether if the trk and cluster are in the same detector hals

    if (!(trk->getPositionAtEcal().at(1) * cl->getPosition().at(1) > 0)) {
        cout << "Track and cluster are not in the same half " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    double P = GetMagnitude(trk->getMomentum());
    double dt = cl->getClusterTime() - CL_trk_time_Offset - trk->getTrackTime();

    if (cl->getPosition().at(1) > 0) {
        timeMatch = (dt > f_trkCl_dt_Top_TightLowerLim->Eval(P)) && (dt < f_trkCl_dt_Top_TightUpperLim->Eval(P));
    } else {
        timeMatch = (dt > f_trkCl_dt_Bot_TightLowerLim->Eval(P)) && (dt < f_trkCl_dt_Bot_TightUpperLim->Eval(P));
    }


    // ===== ========================================= ======
    // ===== Second, let's check track cluster position difference ======
    // ===== ========================================= ======
    double dX = cl->getPosition().at(0) - trk->getPositionAtEcal().at(0);
    bool HasHitInL6 = HasL6Hit(trk);
    int charge = trk->getCharge();

    if (cl->getPosition().at(1) > 0) {

        if (charge > 0) {
            if (HasHitInL6) {
                posMatch = (dX > f_dXTopWithL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXTopWithL6Pos_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXTopNoL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXTopNoL6Pos_TightUpperLim->Eval(P));
            }
        } else {
            if (HasHitInL6) {
                posMatch = (dX > f_dXTopWithL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXTopWithL6Neg_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXTopNoL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXTopNoL6Neg_TightUpperLim->Eval(P));
            }
        }

    } else {
        if (charge > 0) {
            if (HasHitInL6) {
                posMatch = (dX > f_dXBotWithL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXBotWithL6Pos_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXBotNoL6Pos_TightLowerLim->Eval(P)) && (dX < f_dXBotNoL6Pos_TightUpperLim->Eval(P));
            }
        } else {
            if (HasHitInL6) {
                posMatch = (dX > f_dXBotWithL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXBotWithL6Neg_TightUpperLim->Eval(P));
            } else {
                posMatch = (dX > f_dXBotNoL6Neg_TightLowerLim->Eval(P)) && (dX < f_dXBotNoL6Neg_TightUpperLim->Eval(P));
            }
        }
    }
    return timeMatch*posMatch;
}

bool IscldTCut(EcalCluster* cl1, EcalCluster* cl2) {

    if (cl1->getPosition().at(1) * cl2->getPosition().at(1) > 0) {
        cout << "In function IsCldtTightCutPass clusters should be in opposite half" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    return (TMath::Abs(cl1->getClusterTime() - cl2->getClusterTime()) < cl_dTcut);
}

bool IsTrkClusterdXMatch(GblTrack* trk, EcalCluster* cl) {


    // ===== ========================================= ======
    // ===== First, let's check track cluster time difference ======
    // ===== ========================================= ======

    // ==== 1st check whether if the trk and cluster are in the same detector hals

    if (!(trk->getPositionAtEcal().at(1) * cl->getPosition().at(1) > 0)) {
        cout << "Track and cluster are not in the same half " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    bool dXMatch = false;

    double P = GetMagnitude(trk->getMomentum());
    double dX = cl->getPosition().at(0) - trk->getPositionAtEcal().at(0);

    if (trk->getCharge() > 0) {

        if (cl->getPosition().at(1) > 0) {

            if (HasL6Hit(trk)) {
                int bin = h_dX_Top_PosWithL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Top_PosWithL6_Cut->GetBinContent(bin));
            } else {
                int bin = h_dX_Top_PosNoL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Top_PosNoL6_Cut->GetBinContent(bin));
            }

        } else {
            if (HasL6Hit(trk)) {
                int bin = h_dX_Bot_PosWithL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Bot_PosWithL6_Cut->GetBinContent(bin));
            } else {
                int bin = h_dX_Bot_PosNoL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Bot_PosNoL6_Cut->GetBinContent(bin));
            }
        }
    } else {
        if (cl->getPosition().at(1) > 0) {

            if (HasL6Hit(trk)) {
                int bin = h_dX_Top_NegWithL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Top_NegWithL6_Cut->GetBinContent(bin));
            } else {
                int bin = h_dX_Top_NegNoL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Top_NegNoL6_Cut->GetBinContent(bin));
            }

        } else {
            if (HasL6Hit(trk)) {
                int bin = h_dX_Bot_NegWithL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Bot_NegWithL6_Cut->GetBinContent(bin));
            } else {
                int bin = h_dX_Bot_NegNoL6_Cut->FindBin(P, dX);
                dXMatch = bool(h_dX_Bot_NegNoL6_Cut->GetBinContent(bin));
            }
        }
    }

    return dXMatch;
}

bool IsTrkClusterdTMatch(GblTrack* trk, EcalCluster* cl) {

    // ===== ========================================= ======
    // ===== First, let's check track cluster time difference ======
    // ===== ========================================= ======

    // ==== 1st check whether if the trk and cluster are in the same detector hals

    if (!(trk->getPositionAtEcal().at(1) * cl->getPosition().at(1) > 0)) {
        cout << "Track and cluster are not in the same half " << endl;
        cout << "Exiting" << endl;
        exit(1);
    }
    bool timeMatch = false;

    double P = GetMagnitude(trk->getMomentum());
    double dt = cl->getClusterTime() - CL_trk_time_Offset - trk->getTrackTime();

    if (cl->getPosition().at(1) > 0) {
        int bin = h_trkCl_dt_P_Top_Cut->FindBin(P, dt);
        timeMatch = bool( h_trkCl_dt_P_Top_Cut->GetBinContent(bin));
    } else {
        int bin = h_trkCl_dt_P_Bot_Cut->FindBin(P, dt);
        timeMatch = bool( h_trkCl_dt_P_Bot_Cut->GetBinContent(bin));
    }

    return timeMatch;
}

bool IsTrkClusterMatch(GblTrack *trk, EcalCluster *cl) {

    bool checkStatus = false;
    bool timeMatch = false;
    bool posMatch = false;

    timeMatch = IsTrkClusterdTMatch(trk, cl);
    posMatch = IsTrkClusterdXMatch(trk, cl);

    checkStatus = timeMatch*posMatch;

    return checkStatus;
}

bool IsTightemMaxMomCut(double P) {

    return (P < Pem_MaxTight);
}

bool IsTightD0CutPassed(GblTrack* trk) {
    bool checkStatus = false;

    if (isData) {

        if (trk->getOmega() < 0) {

            if (trk->getD0() > ep_d0TightCutMin && trk->getD0() < ep_d0TightCutMax) {
                checkStatus = true;
            }

        } else if (trk->getOmega() > 0) {

            if (trk->getD0() > em_d0TightCutMin && trk->getD0() < em_d0TightCutMax) {

                checkStatus = true;
            }

        }

    }

    return checkStatus;
}

void FillLargeD0Hists(double mV0, double Pem, double Pep) {

    if (isLarged0ep && IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch) {
        h_Pem_BigD0_1->Fill(Pem);
        h_Pep_BigD0_1->Fill(Pep);
        h_PSum_BigD0_1->Fill(Pem + Pep);
        h_Minv_BidD0_1->Fill(mV0);

        if (mV0 > 0.05) {
            h_Pem_BigD0_2->Fill(Pem);
            h_Pep_BigD0_2->Fill(Pep);
            h_PSum_BigD0_2->Fill(Pem + Pep);
        }

    }

}

bool HasL1Hit(GblTrack *trk) {
    bool hasL1 = false;
    for (int ii = 0; ii < trk->getSvtHits()->GetSize(); ii++) {
        if (((SvtHit*) trk->getSvtHits()->At(ii))->getPosition().at(2) < 120.) {
            hasL1 = true;

            return hasL1;
        }
    }
    return hasL1;
}

bool HasL6Hit(GblTrack *trk) {
    bool hasL6 = false;
    for (int ii = 0; ii < trk->getSvtHits()->GetSize(); ii++) {
        if (((SvtHit*) trk->getSvtHits()->At(ii))->getPosition().at(2) > 850.) {
            hasL6 = true;

            return hasL6;
        }
    }
    return hasL6;
}

bool IsEmMaxMomCut(double P) {
    if (P < Pem_MaxCut) {
        return true;
    } else {

        return false;
    }
}

bool IsPsumMaxCut(double P) {
    return (P < PsumCutMax);
}

bool IsPsumMinCut(double P) {
    return (P > PsumCutMin);
}

bool IsD0Cut(double d0) {

    //return (d0 > 2.25);
    return (d0 < d0_cut);
}

bool IsLargeD0(double d0) {

    return (d0 > largeD0Cut);
}

bool IsClInFid(HpsParticle* part) {

    EcalCluster *cl = (EcalCluster*) part->getClusters()->At(0);
    double y_cl = cl->getPosition().at(1);
    double x_cl = cl->getPosition().at(0);

    bool inFid = true;

    // Excluding regions step by step

    if (x_cl < -270 || x_cl > 350. || TMath::Abs(y_cl) > 78 || TMath::Abs(y_cl) < 36) {
        inFid = false;
    } else if (
            x_cl > -112 && x_cl < 40. && TMath::Abs(y_cl) < 49.) {
        inFid == false;
    }

    return inFid;
}

bool IsClInDeepFid(HpsParticle* part) {

    EcalCluster *cl = (EcalCluster*) part->getClusters()->At(0);
    double y_cl = cl->getPosition().at(1);
    double x_cl = cl->getPosition().at(0);

    bool inFid = true;

    // Excluding regions step by step

    if (x_cl < -260 || x_cl > 340. || TMath::Abs(y_cl) > 70. || TMath::Abs(y_cl) < 43.5) {
        inFid = false;
    } else if (
            x_cl > -120 && x_cl < 50. && TMath::Abs(y_cl) < 58.) {
        inFid == false;
    }

    return inFid;
}

vector<double> GetHitCoordAtLayer(GblTrack* trk, int layer) {

    // ==== =Check if legal layer is provided
    if (!(layer >= 1 && layer <= 6)) {
        cout << "In the function GetHitCoordAtLayer, wrong layer is provided" << endl;
        cout << "The layer should be one of following values, 1, 2, 3, 4 5 or 6" << endl;
        cout << "Exiting" << endl;
        exit(1);
    }

    bool found = false;

    for (int i = 0; i < trk->getSvtHits()->GetSize(); i++) {

        if (h_SVTLayerBinning->FindBin(((SvtHit*) trk->getSvtHits()->At(i))->getPosition().at(2)) == layer) {
            found = true;
            return ((SvtHit*) trk->getSvtHits()->At(i))->getPosition();
        }
    }

    if (found == false) {

        return vector<double>{0., 0., 0.};
    }

}

bool IsIntimeClusterCandidate(EcalCluster* cl) {
    vector<double> cl_pos = cl->getPosition();

    bool intime = false;


    if (cl_pos.at(1) > 0) {
        cl_t_max = 70.;
        cl_t_min = 30.;
    } else {
        cl_t_max = f_clTBotUpLim->Eval(cl->getEnergy());
        cl_t_min = f_clTBotLowLim->Eval(cl->getEnergy());
    }


    if (cl->getClusterTime() > cl_t_min && cl->getClusterTime() < cl_t_max) {

        intime = true;
    }

    return intime;
}


// ===== ============================================== ======
// ===== This is a generic function theat will return the magnitude of the vector
// ===== In this case the magnitude is defined as the square root of the sums of element squares
// ===== ============================================== ======

double GetMagnitude(vector<double> v) {

    double magn2 = 0;

    for (int i = 0; i < v.size(); i++) {

        magn2 = magn2 + v.at(i) * v.at(i);
    }

    return sqrt(magn2);
}

vector<double> GetMassBins() {

    vector<double> massBins;

    TF1 *f_Pol9 = new TF1("f_Pol9", "pol9", 0.02, 0.25);

    //======== These parameters are just empirical parameters obtained by fitting the Tri mass spectrum with pol9 function
    double pars[10] = {-153346.6270154149387963116168975830078125, 11201974.94080074690282344818115234375, -304941970.057447373867034912109375,
        4447333216.984340667724609375, -39577578066.1367340087890625, 226243975671.709014892578125, -837152757876.4150390625, 1941315061381.22021484375,
        -2565233441882.16552734375, 1472607538595.3955078125};
    f_Pol9->SetParameters(pars);

    double xMax = 0.25;
    double x0 = 0.032;
    //double cur_x = x0;
    double cur_x = 0;
    const double bw = 0.25 / 200;
    const double desiredCont = 4000.; // The number that we want eah bin of the histo to have

    massBins.push_back(cur_x);
    while (cur_x < xMax) {

        double f = f_Pol9->Eval(cur_x);

        double delta_x = 0.0005;
        if (cur_x > x0) {
            delta_x = TMath::Min(0.01, desiredCont * bw / f);
        }
        if (delta_x < 0.0005) {
            delta_x = 0.0005;
        }

        cur_x = cur_x + delta_x;

        massBins.push_back(cur_x);

    }

    //    for (int i = 0; i < massBins.size(); i++) {
    //        cout << massBins.at(i) << ", ";
    //    }
    //    cout << endl;

    return massBins;
}

void DefineCutGeneral(TH2D *h_inp, TH2D *h_cut, double acutFraction) {

    // Just in case reset the h_cut before filling
    h_cut->Reset();

    for (int i = 0; i < h_inp->GetNbinsX(); i++) {


        TH1D *h1D = (TH1D*) h_inp->ProjectionY("h_inp", i + 1, i + 1);

        int NbinsY = h1D->GetNbinsX();

        double N_All = h1D->Integral();

        double cutFraction = acutFraction;

        // ===== We would like to have not very poor statistics, otherwise
        // ===== We will skip all bins that that column

        // *** Seems it will be better if we don't skip any momentum value
        //        if (N_All < 45) {
        //            continue;
        //        }


        if (N_All < 10) {
            cutFraction = 30. * acutFraction;
        } else if (N_All < 30) {
            cutFraction = 15. * acutFraction;
        } else if (N_All < 60) {
            cutFraction = 10. * acutFraction;
        } else if (N_All < 100) {
            cutFraction = 5. * acutFraction;
        } else if (N_All < 200) {
            cutFraction = 4. * acutFraction;
        } else if (N_All < 500) {
            cutFraction = 2. * acutFraction;
        }


        for (int iy = 0; iy < NbinsY; iy++) {


            if (h1D->Integral(1, iy + 1) > N_All * (1 - 0.5 * cutFraction)) {
                break;
            }

            if (h1D->Integral(1, iy + 1) > 0.5 * cutFraction * N_All) {

                h_cut->SetBinContent(i + 1, iy + 1, 1);
            }

        }


        delete h1D;
    }
}

void FilldXP_ep(HpsParticle *V0, HpsParticle *ep, double P, double dX) {

    bool top = (((GblTrack*) (ep->getTracks()->At(0)))->getMomentum().at(1) > 0);

    bool hasL6 = HasL6Hit((GblTrack*) ep->getTracks()->At(0));

    bool isAllButCuts = CheckAllOtherCuts("epClTrkMatch");

    h_dX_ep_All->Fill(P, dX);

    if (top) {

        if (hasL6) {
            h_dX_epTopWithL6_All->Fill(P, dX);
        } else {
            h_dX_epTopNoL6_All->Fill(P, dX);
        }
    } else {
        if (hasL6) {
            h_dX_epBotWithL6_All->Fill(P, dX);
        } else {
            h_dX_epBotNoL6_All->Fill(P, dX);
        }
    }

    if (isAllButCuts) {
        h_dX_ep_AllBut->Fill(P, dX);
        h_Minv_epClTrkMatch_Final1->Fill(V0->getMass());

        if (top) {

            if (hasL6) {
                h_dX_epTopWithL6_AllBut->Fill(P, dX);
            } else {
                h_dX_epTopNoL6_AllBut->Fill(P, dX);
            }
        } else {
            if (hasL6) {
                h_dX_epBotWithL6_AllBut->Fill(P, dX);
            } else {
                h_dX_epBotNoL6_AllBut->Fill(P, dX);
            }
        }

        if (IsepTrkClMatch) {
            h_dX_ep_CutEffect->Fill(P, dX);

            if (top) {

                if (hasL6) {
                    h_dX_epTopWithL6_CutEffect->Fill(P, dX);
                } else {
                    h_dX_epTopNoL6_CutEffect->Fill(P, dX);
                }
            } else {
                if (hasL6) {
                    h_dX_epBotWithL6_CutEffect->Fill(P, dX);
                } else {
                    h_dX_epBotNoL6_CutEffect->Fill(P, dX);
                }
            }
        }

    }

}

void FilldXP_em(HpsParticle *V0, HpsParticle *em, double P, double dX) {

    bool top = (((GblTrack*) (em->getTracks()->At(0)))->getMomentum().at(1) > 0);

    bool hasL6 = HasL6Hit((GblTrack*) em->getTracks()->At(0));

    bool isAllButCuts = CheckAllOtherCuts("emClTrkMatch");

    h_dX_em_All->Fill(P, dX);

    if (top) {

        if (hasL6) {
            h_dX_emTopWithL6_All->Fill(P, dX);
        } else {
            h_dX_emTopNoL6_All->Fill(P, dX);
        }
    } else {
        if (hasL6) {
            h_dX_emBotWithL6_All->Fill(P, dX);
        } else {
            h_dX_emBotNoL6_All->Fill(P, dX);
        }
    }

    if (isAllButCuts) {
        h_dX_em_AllBut->Fill(P, dX);
        h_Minv_emClTrkMatch_Final1->Fill(V0->getMass());

        if (top) {

            if (hasL6) {
                h_dX_emTopWithL6_AllBut->Fill(P, dX);
            } else {
                h_dX_emTopNoL6_AllBut->Fill(P, dX);
            }
        } else {
            if (hasL6) {
                h_dX_emBotWithL6_AllBut->Fill(P, dX);
            } else {
                h_dX_emBotNoL6_AllBut->Fill(P, dX);
            }
        }

        if (IsemTrkClMatch) {
            h_dX_em_CutEffect->Fill(P, dX);

            if (top) {

                if (hasL6) {
                    h_dX_emTopWithL6_CutEffect->Fill(P, dX);
                } else {
                    h_dX_emTopNoL6_CutEffect->Fill(P, dX);
                }
            } else {
                if (hasL6) {
                    h_dX_emBotWithL6_CutEffect->Fill(P, dX);
                } else {
                    h_dX_emBotNoL6_CutEffect->Fill(P, dX);
                }
            }
        }

    }

}

void FilldtP_ep(HpsParticle *V0, HpsParticle *ep, double P, double dt) {

    bool top = (((GblTrack*) (ep->getTracks()->At(0)))->getMomentum().at(1) > 0);

    bool isAllButCuts = CheckAllOtherCuts("epClTrkdT");

    h_ep_cl_trk_dT_All->Fill(P, dt);

    if (top) {
        h_ep_cl_trk_dT_Top_All->Fill(P, dt);
        h_cl_trk_dT_Top_All->Fill(P, dt);
    } else {
        h_ep_cl_trk_dT_Bot_All->Fill(P, dt);
        h_cl_trk_dT_Bot_All->Fill(P, dt);
    }

    if (isAllButCuts) {
        h_Minv_epClTrkdT_Final1->Fill(V0->getMass());
        h_ep_cl_trk_dT_AllBut->Fill(P, dt);

        if (top) {
            h_ep_cl_trk_dT_Top_AllBut->Fill(P, dt);
            h_cl_trk_dT_Top_AllBut->Fill(P, dt);
        } else {
            h_ep_cl_trk_dT_Bot_AllBut->Fill(P, dt);
            h_cl_trk_dT_Bot_AllBut->Fill(P, dt);
        }

        if (IsepClTrkdT) {

            h_ep_cl_trk_dT_CutEffect->Fill(P, dt);

            if (top) {
                h_ep_cl_trk_dT_Top_CutEffect->Fill(P, dt);
                h_cl_trk_dT_Top_CutEffect->Fill(P, dt);
            } else {
                h_ep_cl_trk_dT_Bot_CutEffect->Fill(P, dt);
                h_cl_trk_dT_Bot_CutEffect->Fill(P, dt);
            }
        }

    }
}

void FilldtP_em(HpsParticle *V0, HpsParticle *em, double P, double dt) {

    bool top = (((GblTrack*) (em->getTracks()->At(0)))->getMomentum().at(1) > 0);

    bool isAllButCuts = CheckAllOtherCuts("emClTrkdT");

    h_em_cl_trk_dT_All->Fill(P, dt);

    if (top) {
        h_em_cl_trk_dT_Top_All->Fill(P, dt);
        h_cl_trk_dT_Top_All->Fill(P, dt);
    } else {
        h_em_cl_trk_dT_Bot_All->Fill(P, dt);
        h_cl_trk_dT_Bot_All->Fill(P, dt);
    }

    if (isAllButCuts) {
        h_Minv_emClTrkdT_Final1->Fill(V0->getMass());
        h_em_cl_trk_dT_AllBut->Fill(P, dt);

        if (top) {
            h_em_cl_trk_dT_Top_AllBut->Fill(P, dt);
            h_cl_trk_dT_Top_AllBut->Fill(P, dt);
        } else {
            h_em_cl_trk_dT_Bot_AllBut->Fill(P, dt);
            h_cl_trk_dT_Bot_AllBut->Fill(P, dt);
        }

        if (IsemClTrkdT) {

            h_em_cl_trk_dT_CutEffect->Fill(P, dt);

            if (top) {
                h_em_cl_trk_dT_Top_CutEffect->Fill(P, dt);
                h_cl_trk_dT_Top_CutEffect->Fill(P, dt);
            } else {
                h_em_cl_trk_dT_Bot_CutEffect->Fill(P, dt);
                h_cl_trk_dT_Bot_CutEffect->Fill(P, dt);
            }
        }

    }
}

void FillMCHists(HpsEvent *ev, HpsParticle *em, HpsParticle *ep) {

    if (isMC && IscldT && IsemClTrkdT && IsepClTrkdT && IsemTrkClMatch && IsepTrkClMatch) {
        int nMCParticles = ev->getNumberOfMCParticles();

        double Pem_Rec = 0;
        double Pep_Rec = 0;

        double Pem_MC = 0;
        double Pep_MC = 0;

        bool epHasL1 = false;
        for (int iMC = 0; iMC < nMCParticles; iMC++) {
            MCParticle *mcpart = ev->getMCParticle(iMC);

            if (mcpart->getParentCount() > 0 && mcpart->getParent(0)->getPdgID() == 622 || mcpart->getParentCount() == 0 ||
                    (mcpart->getParentCount() > 0 && mcpart->getParent(0)->getPdgID() == 22 && mcpart->getParent(0)->getParentCount() == 0)) {

                if (mcpart->getPdgID() == 11) {

                    Pem_MC = GetMagnitude(mcpart->getMomentum());
                    Pem_Rec = GetMagnitude(em->getMomentum());

                    double hasL1 = HasL1Hit((GblTrack*) em->getTracks()->At(0));

                    if (hasL1) {
                        h_dP_P_em_WithL1_1->Fill(Pem_MC, (Pem_Rec - Pem_MC) / Pem_MC);
                    } else {
                        h_dP_P_em_NoL1_1->Fill(Pem_MC, (Pem_Rec - Pem_MC) / Pem_MC);
                    }

                } else if (mcpart->getPdgID() == -11) {

                    Pep_MC = GetMagnitude(mcpart->getMomentum());
                    Pep_Rec = GetMagnitude(ep->getMomentum());

                    double hasL1 = HasL1Hit((GblTrack*) ep->getTracks()->At(0));

                    if (hasL1) {
                        h_dP_P_ep_WithL1_1->Fill(Pep_MC, (Pep_Rec - Pep_MC) / Pep_MC);
                        epHasL1 = true;
                    } else {
                        h_dP_P_ep_NoL1_1->Fill(Pep_MC, (Pep_Rec - Pep_MC) / Pep_MC);
                        epHasL1 = false;
                    }
                }
            }

        }

        if (epHasL1) {
            h_PSum_RecMC_WithL1_1->Fill(Pem_MC + Pep_MC, Pem_Rec + Pep_Rec);
        } else {
            h_PSum_RecMC_NoL1_1->Fill(Pem_MC + Pep_MC, Pem_Rec + Pep_Rec);
        }

    }
}

// ===== ==============================================     ======

void FillfRadHists(HpsEvent *ev, HpsParticle *v0) {

    if (!isMC) {
        return;
    }


    double m_v0 = v0->getMass();
    int nMCParticles = ev->getNumberOfMCParticles();

    // =========== Studies with Rad samples =========
    if (isRad || isAp) {

        isRadAndRecoil = true; // As soon we know this sample is Rad we set it "true", BUT
        // below, if it failed to match the truth then it will be reset back to false
        double P_RecoilTrue = 0;
        double P_em_True = 0;

        for (int ii = 0; ii < nMCParticles; ii++) {
            MCParticle *mcpart = ev->getMCParticle(ii);

            if (mcpart->getPdgID() == 622) {
                double m_gg = mcpart->getMass();
                double P_gg = GetMagnitude(mcpart->getMomentum());

                HpsParticle *em;
                if (((HpsParticle*) v0->getParticles()->At(0))->getCharge() < 0) {
                    em = (HpsParticle*) v0->getParticles()->At(0);
                } else {
                    em = (HpsParticle*) v0->getParticles()->At(1);
                }

                double P_em_Rec = GetMagnitude(em->getMomentum());
                TVector3 v3_em_Rec(em->getMomentum().at(0), em->getMomentum().at(1), em->getMomentum().at(2));

                //            const int nfRadMassBins = 20;
                //double fRadMassCenters[nfRadMassBins] = {0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23};




                int n_Daught = mcpart->getDaughterCount();

                //                if (n_Daught == 1) {
                //                    cout << mcpart->getDaughter(0)->getPdgID() << "      " << GetMagnitude(mcpart->getDaughter(0)->getMomentum()) << "     " << m_gg << "     " << P_gg << endl;
                //
                //                }

                true_em_match = false;
                for (int iD = 0; iD < n_Daught; iD++) {

                    MCParticle *curDaught = mcpart->getDaughter(iD);



                    if (curDaught->getCharge() < 0) {

                        P_em_True = GetMagnitude(curDaught->getMomentum());
                        h_dP_PTrue_em1->Fill(P_em_True, P_em_Rec / P_em_True);

                        TVector3 v3_em_True(curDaught->getMomentum().at(0), curDaught->getMomentum().at(1), curDaught->getMomentum().at(2));
                        double angle_RecTrue = v3_em_True.Angle(v3_em_Rec) * TMath::RadToDeg();

                        h_dThetaTrue_Minv1->Fill(m_gg, angle_RecTrue);

                        h_dP_dTh_True1->Fill(P_em_Rec / P_em_True, angle_RecTrue);

                        if (m_gg > 0.04) {
                            h_dP_dTh_True2->Fill(P_em_Rec / P_em_True, angle_RecTrue);
                        }

                        if (angle_RecTrue < 1.) {
                            h_dP_PTrue_em2->Fill(P_em_True, P_em_Rec / P_em_True);
                        }

                        if (P_em_Rec / P_em_True > 0.8 && P_em_Rec / P_em_True < 1.1) {
                            h_dThetaTrue_Minv2->Fill(m_gg, angle_RecTrue);

                            if (angle_RecTrue < 1.) {
                                true_em_match = true;
                                isRadAndRecoil = false;
                            }
                        }
                    }
                }


                for (int imass = 0; imass < nfRadMassBins; imass++) {
                    if (TMath::Abs(m_gg - fRadMassCenters[imass]) < TMath::Min(0.01, 2000. * massHistBinWidth / MassFunc[imass])) {
                        h_Rad_MinvPSum1_[imass]->Fill(GetMagnitude(v0->getMomentum()), m_v0);
                        h_Rad_MinvPSumTrue_[imass]->Fill(GetMagnitude(mcpart->getMomentum()), m_gg);

                        if (true_em_match)
                            h_Rad_MinvPSum2_[imass]->Fill(GetMagnitude(v0->getMomentum()), m_v0);
                    }
                }


                if (true_em_match && IsPsumMin) {
                    h_Memep1->Fill(m_v0);
                    h_Memep_True1->Fill(m_gg);
                    h_Memep_VarBins1->Fill(m_v0);
                    h_Memep_True_VarBins1->Fill(m_gg);
                    trueMass = m_gg;
                }


                //break;
            } else if (mcpart->getPdgID() == 623 && mcpart->getDaughterCount() == 1 && mcpart->getDaughter(0)->getCharge() == -1) {

                P_RecoilTrue = GetMagnitude(mcpart->getDaughter(0)->getMomentum());
            }


        }



        //        double P_RecoilTrue = 0;
        //        double P_em_True = 0;

        h_P_DecayRecoil->Fill(P_em_True, P_RecoilTrue);

    } else if (isTri || isWab) {

        if (IsPsumMin) {
            h_Memep1->Fill(m_v0);
            h_Memep_VarBins1->Fill(m_v0);
        }
    }

}

void InitCutHistograms() {

    TH2D *h_dX_Top_PosWithL6 = (TH2D*) file_CutHists->Get("h_dX_epTopWithL6_AllBut");
    h_dX_Top_PosWithL6->SetName("h_dX_Top_PosWithL6");
    h_dX_Top_PosWithL6_Cut = (TH2D*) h_dX_Top_PosWithL6->Clone("h_dX_Top_PosWithL6_Cut");
    for (int ix = 0; ix < h_dX_Top_PosWithL6->GetNbinsY(); ix++) {
        for (int iy = 0; iy < h_dX_Top_PosWithL6->GetNbinsX(); iy++) {
            double x = h_dX_Top_PosWithL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Top_PosWithL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y < f_TrashLow_dX_Top_PosWithL6->Eval(x) || y > f_TrashUp_dX_Top_PosWithL6->Eval(x)) {
                h_dX_Top_PosWithL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Top_PosWithL6, h_dX_Top_PosWithL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Top_PosWithL6);
    file_CutHists2->Add(h_dX_Top_PosWithL6_Cut);

    TH2D *h_dX_Top_PosNoL6 = (TH2D*) file_CutHists->Get("h_dX_epTopNoL6_AllBut");
    h_dX_Top_PosNoL6->SetName("h_dX_Top_PosNoL6");
    h_dX_Top_PosNoL6_Cut = (TH2D*) h_dX_Top_PosNoL6->Clone("h_dX_Top_PosNoL6_Cut");

    for (int ix = 0; ix < h_dX_Top_PosNoL6->GetNbinsX(); ix++) {
        for (int iy = 0; iy < h_dX_Top_PosNoL6->GetNbinsY(); iy++) {
            double x = h_dX_Top_PosNoL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Top_PosNoL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y < f_TrashLow_dX_Top_PosNoL6->Eval(x) || y > f_TrashUp_dX_Top_PosNoL6->Eval(x)) {
                h_dX_Top_PosNoL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Top_PosNoL6, h_dX_Top_PosNoL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Top_PosNoL6);
    file_CutHists2->Add(h_dX_Top_PosNoL6_Cut);



    TH2D *h_dX_Bot_PosWithL6 = (TH2D*) file_CutHists->Get("h_dX_epBotWithL6_AllBut");
    h_dX_Bot_PosWithL6->SetName("h_dX_Bot_PosWithL6");
    h_dX_Bot_PosWithL6_Cut = (TH2D*) h_dX_Bot_PosWithL6->Clone("h_dX_Bot_PosWithL6_Cut");
    for (int ix = 0; ix < h_dX_Bot_PosWithL6->GetNbinsY(); ix++) {
        for (int iy = 0; iy < h_dX_Bot_PosWithL6->GetNbinsX(); iy++) {
            double x = h_dX_Bot_PosWithL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Bot_PosWithL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y < f_TrashLow_dX_Bot_PosWithL6->Eval(x) || y > f_TrashUp_dX_Bot_PosWithL6->Eval(x)) {
                h_dX_Bot_PosWithL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Bot_PosWithL6, h_dX_Bot_PosWithL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Bot_PosWithL6);
    file_CutHists2->Add(h_dX_Bot_PosWithL6_Cut);

    TH2D *h_dX_Bot_PosNoL6 = (TH2D*) file_CutHists->Get("h_dX_epBotNoL6_AllBut");
    h_dX_Bot_PosNoL6->SetName("h_dX_Bot_PosNoL6");
    h_dX_Bot_PosNoL6_Cut = (TH2D*) h_dX_Bot_PosNoL6->Clone("h_dX_Bot_PosNoL6_Cut");

    for (int ix = 0; ix < h_dX_Bot_PosNoL6->GetNbinsX(); ix++) {
        for (int iy = 0; iy < h_dX_Bot_PosNoL6->GetNbinsY(); iy++) {
            double x = h_dX_Bot_PosNoL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Bot_PosNoL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y < f_TrashLow_dX_Bot_PosNoL6->Eval(x) || y > f_TrashUp_dX_Bot_PosNoL6->Eval(x)) {
                h_dX_Bot_PosNoL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Bot_PosNoL6, h_dX_Bot_PosNoL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Bot_PosNoL6);
    file_CutHists2->Add(h_dX_Bot_PosNoL6_Cut);




    TH2D *h_dX_Top_NegWithL6 = (TH2D*) file_CutHists->Get("h_dX_emTopWithL6_AllBut");
    h_dX_Top_NegWithL6->SetName("h_dX_Top_NegWithL6");
    h_dX_Top_NegWithL6_Cut = (TH2D*) h_dX_Top_NegWithL6->Clone("h_dX_Top_NegWithL6_Cut");
    for (int ix = 0; ix < h_dX_Top_NegWithL6->GetNbinsX(); ix++) {
        for (int iy = 0; iy < h_dX_Top_NegWithL6->GetNbinsY(); iy++) {
            double x = h_dX_Top_NegWithL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Top_NegWithL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y > f_TrashUp_dX_Top_NegWithL6->Eval(x) || y < f_TrashLow_dX_Top_NegWithL6->Eval(x)) {
                h_dX_Top_NegWithL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Top_NegWithL6, h_dX_Top_NegWithL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Top_NegWithL6);
    file_CutHists2->Add(h_dX_Top_NegWithL6_Cut);

    TH2D *h_dX_Top_NegNoL6 = (TH2D*) file_CutHists->Get("h_dX_emTopNoL6_AllBut");
    h_dX_Top_NegNoL6->SetName("h_dX_Top_NegNoL6");
    h_dX_Top_NegNoL6_Cut = (TH2D*) h_dX_Top_NegNoL6->Clone("h_dX_Top_NegNoL6_Cut");

    for (int ix = 0; ix < h_dX_Top_NegNoL6->GetNbinsX(); ix++) {
        for (int iy = 0; iy < h_dX_Top_NegNoL6->GetNbinsY(); iy++) {
            double x = h_dX_Top_NegNoL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Top_NegNoL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y > f_TrashUp_dX_Top_NegNoL6->Eval(x) || y < f_TrashLow_dX_Top_NegNoL6->Eval(x)) {
                h_dX_Top_NegNoL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Top_NegNoL6, h_dX_Top_NegNoL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Top_NegNoL6);
    file_CutHists2->Add(h_dX_Top_NegNoL6_Cut);



    TH2D *h_dX_Bot_NegWithL6 = (TH2D*) file_CutHists->Get("h_dX_emBotWithL6_AllBut");
    h_dX_Bot_NegWithL6->SetName("h_dX_Bot_NegWithL6");
    h_dX_Bot_NegWithL6_Cut = (TH2D*) h_dX_Bot_NegWithL6->Clone("h_dX_Bot_NegWithL6_Cut");
    for (int ix = 0; ix < h_dX_Bot_NegWithL6->GetNbinsY(); ix++) {
        for (int iy = 0; iy < h_dX_Bot_NegWithL6->GetNbinsX(); iy++) {
            double x = h_dX_Bot_NegWithL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Bot_NegWithL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y > f_TrashUp_dX_Bot_NegWithL6->Eval(x) || y < f_TrashLow_dX_Bot_NegWithL6->Eval(x)) {
                h_dX_Bot_NegWithL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Bot_NegWithL6, h_dX_Bot_NegWithL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Bot_NegWithL6);
    file_CutHists2->Add(h_dX_Bot_NegWithL6_Cut);

    TH2D *h_dX_Bot_NegNoL6 = (TH2D*) file_CutHists->Get("h_dX_emBotNoL6_AllBut");
    h_dX_Bot_NegNoL6->SetName("h_dX_Bot_NegNoL6");
    h_dX_Bot_NegNoL6_Cut = (TH2D*) h_dX_Bot_NegNoL6->Clone("h_dX_Bot_NegNoL6_Cut");

    for (int ix = 0; ix < h_dX_Bot_NegNoL6->GetNbinsX(); ix++) {
        for (int iy = 0; iy < h_dX_Bot_NegNoL6->GetNbinsY(); iy++) {
            double x = h_dX_Bot_NegNoL6_Cut->GetXaxis()->GetBinCenter(ix + 1);
            double y = h_dX_Bot_NegNoL6_Cut->GetYaxis()->GetBinCenter(iy + 1);
            if (y > f_TrashUp_dX_Bot_NegNoL6->Eval(x) || y < f_TrashLow_dX_Bot_NegNoL6->Eval(x)) {
                h_dX_Bot_NegNoL6->SetBinContent(ix + 1, iy + 1, 0.);
            }
        }
    }

    DefineCutGeneral(h_dX_Bot_NegNoL6, h_dX_Bot_NegNoL6_Cut, 0.01);
    file_CutHists2->Add(h_dX_Bot_NegNoL6);
    file_CutHists2->Add(h_dX_Bot_NegNoL6_Cut);

    //TH2D *h_trkCl_dt_P_Top = (TH2D*) file_trkClustMatch->Get("h_trkCl_dt_P_Top");
    TH2D *h_trkCl_dt_P_Top = (TH2D*) file_CutHists->Get("h_cl_trk_dT_Top_AllBut");
    h_trkCl_dt_P_Top->SetName("h_trkCl_dt_P_Top");
    h_trkCl_dt_P_Top_Cut = (TH2D*) h_trkCl_dt_P_Top->Clone("h_trkCl_dt_P_Top_Cut");
    DefineCutGeneral(h_trkCl_dt_P_Top, h_trkCl_dt_P_Top_Cut, 0.01);
    file_CutHists2->Add(h_trkCl_dt_P_Top);
    file_CutHists2->Add(h_trkCl_dt_P_Top_Cut);

    //    TH2D *h_trkCl_dt_P_Bot = (TH2D*) file_trkClustMatch->Get("h_trkCl_dt_P_Bot");
    TH2D *h_trkCl_dt_P_Bot = (TH2D*) file_CutHists->Get("h_cl_trk_dT_Bot_AllBut");
    h_trkCl_dt_P_Bot->SetName("h_trkCl_dt_P_Bot");
    h_trkCl_dt_P_Bot_Cut = (TH2D*) h_trkCl_dt_P_Bot->Clone("h_trkCl_dt_P_Bot_Cut");
    DefineCutGeneral(h_trkCl_dt_P_Bot, h_trkCl_dt_P_Bot_Cut, 0.01);
    file_CutHists2->Add(h_trkCl_dt_P_Bot);
    file_CutHists2->Add(h_trkCl_dt_P_Bot_Cut);


    file_CutHists2->Write();
    //file_CutHists2->Close();

}

void InitGeneralHistograms() {

    h_clDt_All = new TH1D("h_clDt_All", "", 70, -3., 3.);
    h_clDt_AllBut = new TH1D("h_clDt_AllBut", "", 70, -3., 3.);
    h_clDt_CutEffect = new TH1D("h_clDt_CutEffect", "", 70, -3., 3.);

    h_PsumMax_All = new TH1D("h_PsumMax_All", "", 70, 0.7, 1.2 * Eb);
    h_PsumMax_AllBut = new TH1D("h_PsumMax_AllBut", "", 70, 0.7, 1.2 * Eb);
    h_PsumMax_CutEffect = new TH1D("h_PsumMax_CutEffect", "", 70, 0.7, 1.2 * Eb);

    h_PsumScSmMax_All = new TH1D("h_PsumScSmMax_All", "", 70, 0.7, 1.2 * Eb);
    h_PsumScSmMax_AllBut = new TH1D("h_PsumScSmMax_AllBut", "", 70, 0.7, 1.2 * Eb);
    h_PsumScSmMax_CutEffect = new TH1D("h_PsumScSmMax_CutEffect", "", 70, 0.7, 1.2 * Eb);

    h_PsumMin_All = new TH1D("h_PsumMin_All", "", 70, 0.7, 1.2 * Eb);
    h_PsumMin_AllBut = new TH1D("h_PsumMin_AllBut", "", 70, 0.7, 1.2 * Eb);
    h_PsumMin_CutEffect = new TH1D("h_PsumMin_CutEffect", "", 70, 0.7, 1.2 * Eb);

    h_PsumScSmMin_All = new TH1D("h_PsumScSmMin_All", "", 70, 0.7, 1.2 * Eb);
    h_PsumScSmMin_AllBut = new TH1D("h_PsumScSmMin_AllBut", "", 70, 0.7, 1.2 * Eb);
    h_PsumScSmMin_CutEffect = new TH1D("h_PsumScSmMin_CutEffect", "", 70, 0.7, 1.2 * Eb);

    h_cl_trk_dT_All = new TH2D("h_cl_trk_dT_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_AllBut = new TH2D("h_cl_trk_dT_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_CutEffect = new TH2D("h_cl_trk_dT_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);

    h_cl_trk_dT_Top_All = new TH2D("h_cl_trk_dT_Top_All", "", 40, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_Top_AllBut = new TH2D("h_cl_trk_dT_Top_AllBut", "", 40, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_Top_CutEffect = new TH2D("h_cl_trk_dT_Top_CutEffect", "", 40, 0., 2.5, 200, -8., 8.);

    h_cl_trk_dT_Bot_All = new TH2D("h_cl_trk_dT_Bot_All", "", 40, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_Bot_AllBut = new TH2D("h_cl_trk_dT_Bot_AllBut", "", 40, 0., 2.5, 200, -8., 8.);
    h_cl_trk_dT_Bot_CutEffect = new TH2D("h_cl_trk_dT_Bot_CutEffect", "", 40, 0., 2.5, 200, -8., 8.);


    h_em_cl_trk_dT_All = new TH2D("h_em_cl_trk_dT_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_AllBut = new TH2D("h_em_cl_trk_dT_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_CutEffect = new TH2D("h_em_cl_trk_dT_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);

    h_em_cl_trk_dT_Top_All = new TH2D("h_em_cl_trk_dT_Top_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_Top_AllBut = new TH2D("h_em_cl_trk_dT_Top_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_Top_CutEffect = new TH2D("h_em_cl_trk_dT_Top_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);

    h_em_cl_trk_dT_Bot_All = new TH2D("h_em_cl_trk_dT_Bot_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_Bot_AllBut = new TH2D("h_em_cl_trk_dT_Bot_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_em_cl_trk_dT_Bot_CutEffect = new TH2D("h_em_cl_trk_dT_Bot_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);


    h_ep_cl_trk_dT_All = new TH2D("h_ep_cl_trk_dT_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_AllBut = new TH2D("h_ep_cl_trk_dT_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_CutEffect = new TH2D("h_ep_cl_trk_dT_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);

    h_ep_cl_trk_dT_Top_All = new TH2D("h_ep_cl_trk_dT_Top_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_Top_AllBut = new TH2D("h_ep_cl_trk_dT_Top_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_Top_CutEffect = new TH2D("h_ep_cl_trk_dT_Top_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);

    h_ep_cl_trk_dT_Bot_All = new TH2D("h_ep_cl_trk_dT_Bot_All", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_Bot_AllBut = new TH2D("h_ep_cl_trk_dT_Bot_AllBut", "", 200, 0., 2.5, 200, -8., 8.);
    h_ep_cl_trk_dT_Bot_CutEffect = new TH2D("h_ep_cl_trk_dT_Bot_CutEffect", "", 200, 0., 2.5, 200, -8., 8.);


    h_dX_em_All = new TH2D("h_dX_em_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_em_AllBut = new TH2D("h_dX_em_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_em_CutEffect = new TH2D("h_dX_em_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);

    h_dX_emTopWithL6_All = new TH2D("h_dX_emTopWithL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emTopWithL6_AllBut = new TH2D("h_dX_emTopWithL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emTopWithL6_CutEffect = new TH2D("h_dX_emTopWithL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emTopNoL6_All = new TH2D("h_dX_emTopNoL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emTopNoL6_AllBut = new TH2D("h_dX_emTopNoL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emTopNoL6_CutEffect = new TH2D("h_dX_emTopNoL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotWithL6_All = new TH2D("h_dX_emBotWithL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotWithL6_AllBut = new TH2D("h_dX_emBotWithL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotWithL6_CutEffect = new TH2D("h_dX_emBotWithL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotNoL6_All = new TH2D("h_dX_emBotNoL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotNoL6_AllBut = new TH2D("h_dX_emBotNoL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_emBotNoL6_CutEffect = new TH2D("h_dX_emBotNoL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);

    h_dX_ep_All = new TH2D("h_dX_ep_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_ep_AllBut = new TH2D("h_dX_ep_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_ep_CutEffect = new TH2D("h_dX_ep_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);


    h_dX_epTopWithL6_All = new TH2D("h_dX_epTopWithL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epTopWithL6_AllBut = new TH2D("h_dX_epTopWithL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epTopWithL6_CutEffect = new TH2D("h_dX_epTopWithL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epTopNoL6_All = new TH2D("h_dX_epTopNoL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epTopNoL6_AllBut = new TH2D("h_dX_epTopNoL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epTopNoL6_CutEffect = new TH2D("h_dX_epTopNoL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotWithL6_All = new TH2D("h_dX_epBotWithL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotWithL6_AllBut = new TH2D("h_dX_epBotWithL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotWithL6_CutEffect = new TH2D("h_dX_epBotWithL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotNoL6_All = new TH2D("h_dX_epBotNoL6_All", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotNoL6_AllBut = new TH2D("h_dX_epBotNoL6_AllBut", "", 60, 0., 2.5, 200, -50., 50.);
    h_dX_epBotNoL6_CutEffect = new TH2D("h_dX_epBotNoL6_CutEffect", "", 60, 0., 2.5, 200, -50., 50.);

    // =============== Final Event Selection Cuts Cuts ==========
    h_Minv_Final1 = new TH1D("h_Minv_Final1", "", 200, 0., 0.24);
    h_Minv_PMax_Final1 = new TH1D("h_Minv_PMax_Final1", "", 200, 0., 0.24);
    h_Minv_PMin_Final1 = new TH1D("h_Minv_PMin_Final1", "", 200, 0., 0.24);
    h_Minv_cldT_Final1 = new TH1D("h_Minv_cldT_Final1", "", 200, 0., 0.24);
    h_Minv_epClTrkdT_Final1 = new TH1D("h_Minv_epClTrkdT_Final1", "", 200, 0., 0.24);
    h_Minv_emClTrkdT_Final1 = new TH1D("h_Minv_emClTrkdT_Final1", "", 200, 0., 0.24);
    h_Minv_epClTrkMatch_Final1 = new TH1D("h_Minv_epClTrkMatch_Final1", "", 200, 0., 0.24);
    h_Minv_emClTrkMatch_Final1 = new TH1D("h_Minv_emClTrkMatch_Final1", "", 200, 0., 0.24);
    h_Minv_Pem_Final1 = new TH1D("h_Minv_Pem_Final1", "", 200, 0., 0.24);
    h_Minv_d0ep_Final1 = new TH1D("h_Minv_d0ep_Final1", "", 200, 0., 0.24);


    // =============== Histograms with Large d0 ======================

    h_Pem_BigD0_1 = new TH1D("h_Pem_BigD0_1", "", 70, 0., 2.2);
    h_Pem_BigD0_2 = new TH1D("h_Pem_BigD0_2", "", 70, 0., 2.2);
    h_Pep_BigD0_1 = new TH1D("h_Pep_BigD0_1", "", 70, 0., 2.2);
    h_Pep_BigD0_2 = new TH1D("h_Pep_BigD0_2", "", 70, 0., 2.2);
    h_PSum_BigD0_1 = new TH1D("h_PSum_BigD0_1", "", 70, 0., 1.2 * Eb);
    h_PSum_BigD0_2 = new TH1D("h_PSum_BigD0_2", "", 70, 0., 1.2 * Eb);
    h_Minv_BidD0_1 = new TH1D("h_Minv_BidD0_1", "", 70, 0., 0.24);


    h_dP_P_ep_WithL1_1 = new TH2D("h_dP_P_ep_WithL1_1", "", 100, 0., Eb, 100, -0.2, 0.2);
    h_dP_P_ep_NoL1_1 = new TH2D("h_dP_P_ep_NoL1_1", "", 100, 0., Eb, 100, -0.2, 0.2);
    h_dP_P_em_WithL1_1 = new TH2D("h_dP_P_em_WithL1_1", "", 100, 0., Eb, 100, -0.2, 0.2);
    h_dP_P_em_NoL1_1 = new TH2D("h_dP_P_em_NoL1_1", "", 100, 0., Eb, 100, -0.2, 0.2);

    h_PSum_RecMC_WithL1_1 = new TH2D("h_PSum_RecMC_WithL1_1", "", 100, 0., 1.2 * Eb, 100, 0., 1.2 * Eb);
    h_PSum_RecMC_NoL1_1 = new TH2D("h_PSum_RecMC_NoL1_1", "", 100, 0., 1.2 * Eb, 100, 0., 1.2 * Eb);


    for (int ii = 0; ii < nfRadMassBins; ii++) {
        h_Rad_MinvPSum1_[ii] = new TH2D(Form("h_Rad_MinvPSum1_%d", ii), "", 200, 0.7, 1.2 * Eb, 200., 0., 0.3);
        h_Rad_MinvPSum2_[ii] = new TH2D(Form("h_Rad_MinvPSum2_%d", ii), "", 200, 0.7, 1.2 * Eb, 200., 0., 0.3);
        h_Rad_MinvPSumTrue_[ii] = new TH2D(Form("h_Rad_MinvPSumTrue_%d", ii), "", 200, 0.7, 1.2 * Eb, 200., 0., 0.3);
    }

    h_dP_PTrue_em1 = new TH2D("h_dP_PTrue_em1", "", 200, 0., 1.2 * Eb, 200, 0., 1.5);
    h_dP_PTrue_em2 = new TH2D("h_dP_PTrue_em2", "", 200, 0., 1.2 * Eb, 200, 0., 1.5);
    h_dThetaTrue_Minv1 = new TH2D("h_dThetaTrue_Minv1", "", 200, 0., 0.25, 200, 0., 12.);
    h_dThetaTrue_Minv2 = new TH2D("h_dThetaTrue_Minv2", "", 200, 0., 0.25, 200, 0., 12.);

    h_dP_dTh_True1 = new TH2D("h_dP_dTh_True1", "", 200, 0., 1.5, 200, 0., 12);
    h_dP_dTh_True2 = new TH2D("h_dP_dTh_True2", "", 200, 0., 1.5, 200, 0., 12);

    h_Memep1 = new TH1D("h_Memep1", "", 400, 0., 0.25);
    h_Memep_True1 = new TH1D("h_Memep_True1", "", 400, 0., 0.25);

    h_P_DecayRecoil = new TH2D("h_P_DecayRecoil", "", 200, 0., 1.05 * Eb, 200, 0., 1.05 * Eb);

    vector<double> v_massBins = GetMassBins();
    int nMassBins = v_massBins.size() - 1;

    double massBinEdges[nMassBins + 1];
    std::copy(v_massBins.begin(), v_massBins.end(), massBinEdges);

    h_Memep_VarBins1 = new TH1D("h_Memep_VarBins1", "", nMassBins, massBinEdges);
    h_Memep_True_VarBins1 = new TH1D("h_Memep_True_VarBins1", "", nMassBins, massBinEdges);

    h_Pemep_Final = new TH2D("h_Pemep_Final", "", 200, 0., Eb, 200, 0., Eb);

    h_Pep_Fid1 = new TH1D("h_Pep_Fid1", "", 400, 0., 1.2 * Eb);
    h_Pep_DeepFid1 = new TH1D("h_DeepPep_Fid1", "", 400, 0., 1.2 * Eb);

    for (int ii = 0; ii < n_MomRange; ii++) {
        h_E_P_ep_Fid1_[ii] = new TH1D(Form("h_E_P_ep_Fid1_%d", ii), "", 400, 0., 2.);
        h_E_P_ep_DeepFid1_[ii] = new TH1D(Form("h_E_P_ep_DeepFid1_%d", ii), "", 400, 0., 2.);
    }
}

void InitTrkKillingHist() {

    TFile *fileTrkKiller = new TFile("../Data/dualPlaneTest.root", "Read");


    gr_TrkKiller = (TGraphAsymmErrors*) fileTrkKiller->Get("p2slopehps_007963.1GamEm_L1HitInefficiency");

    double x, y;
    int nPoints = gr_TrkKiller->GetN();
    gr_TrkKiller->GetPoint(nPoints - 1, x, y);
    double xMax = x;
    gr_TrkKiller->GetPoint(0, x, y);
    double xMin = x;
    double bw = (xMax - xMin) / double(nPoints - 1);

    //    double xMax = gr_TrkKiller->GetXaxis()->GetXmax();
    //    double xMin = gr_TrkKiller->GetXaxis()->GetXmin();

    //cout << "xMin is " << xMin << "    xMax is " << xMax << "    nBin is " << nPoints << endl;

    h_TrkKiller = new TH1D("h_TrkKiller", "", nPoints, xMin - bw / 2., xMax + bw / 2.);

    //cout<<"h_TrkKiller = "<<h_TrkKiller<<endl;

    for (int ipoint = 0; ipoint < nPoints; ipoint++) {

        gr_TrkKiller->GetPoint(ipoint, x, y);

        int ibin = h_TrkKiller->FindBin(x);
        //cout << "ipoint = " << ipoint << "   x = " << x << "    y = " << y << "    ibin = " << ibin << endl;
        h_TrkKiller->SetBinContent(ibin, y);
    }

    //fileTrkKiller->Close();

}

bool IsParticleKilled(HpsParticle * part) {

    if (!isMC) {
        return false;
    }

    GblTrack *trk = (GblTrack*) part->getTracks()->At(0);

    double slp = trk->getTanLambda();

    int nHits = trk->getSvtHits()->GetSize();

    //cout << "nHits = " << nHits << "     slp = " << slp << endl;

    if (nHits == 6) {
        return false;
    } else if (nHits == 5) {

        int ibin = h_TrkKiller->FindBin(slp);

        //cout<<"xMin = "<<h_TrkKiller->GetXaxis()->GetXmin()<<"     xMax = "<<h_TrkKiller->GetXaxis()->GetXmax()<<endl;

        double eff = 1 - h_TrkKiller->GetBinContent(ibin);

        double randNumber = rnd1->Uniform(0., 1.);

        //cout<<"ibin = "<<ibin << "     Eff = " << eff << "      randNumber is " << randNumber << endl;

        if (randNumber > eff) {
            return true;
        } else {
            return false;
        }

    }

}

vector<double> GetSmearKine(HpsParticle* v0) {

    HpsParticle *top = ((HpsParticle*) v0->getParticles()->At(0))->getMomentum().at(1) > 0 ? ((HpsParticle*) v0->getParticles()->At(0)) : ((HpsParticle*) v0->getParticles()->At(1));
    HpsParticle *bot = ((HpsParticle*) v0->getParticles()->At(0))->getMomentum().at(1) < 0 ? ((HpsParticle*) v0->getParticles()->At(0)) : ((HpsParticle*) v0->getParticles()->At(1));

    double M_V0 = v0->getMass();
    double P_V0 = GetMagnitude(v0->getMomentum());

    double P_Top = GetMagnitude(top->getMomentum());
    double P_Bot = GetMagnitude(bot->getMomentum());
    int nTopHits = ((GblTrack*) top->getTracks()->At(0))->getSvtHits()->GetSize();
    int nBotHits = ((GblTrack*) bot->getTracks()->At(0))->getSvtHits()->GetSize();

    double scaleMomTop;
    double scaleMomBot;

    if (isData) {
        scaleMomTop = nTopHits == 5 ? scale_Data_Top5hits : scale_Data_Top6hits;
        scaleMomBot = nBotHits == 5 ? scale_Data_Bot5hits : scale_Data_Bot6hits;
    } else {
        scaleMomTop = nTopHits == 5 ? scale_MC_Top5hits : scale_MC_Top6hits;
        scaleMomBot = nBotHits == 5 ? scale_MC_Bot5hits : scale_MC_Bot6hits;
    }

    double P_TopScaled = scaleMomTop*P_Top;
    double P_BotScaled = scaleMomBot*P_Bot;

    double smearTop = nTopHits == 5 ? smear_Top5hits : smear_Top6hits;
    double smearBot = nBotHits == 5 ? smear_Bot5hits : smear_Bot6hits;

    double P_TopSmSc = rnd1->Gaus(P_TopScaled, P_TopScaled * smearTop);
    double P_BotSmSc = rnd1->Gaus(P_BotScaled, P_BotScaled * smearBot);

    if (isData) {
        P_TopSmSc = P_TopScaled;
        P_BotSmSc = P_BotScaled;
    }

    double P_emScSm = top->getCharge() < 0 ? P_TopSmSc : P_BotSmSc;
    double P_epScSm = top->getCharge() > 0 ? P_TopSmSc : P_BotSmSc;

    double PV0ScSm = P_V0 * (P_TopSmSc + P_BotSmSc) / (P_Top + P_Bot);

    double MinvScSmfactor = sqrt((P_TopSmSc / P_Top)*(P_BotSmSc / P_Bot));
    double M_V0_ScSm = MinvScSmfactor*M_V0;

    //cout<<"MV_0 = "<<M_V0<<"    M_V0_ScSm = "<<M_V0_ScSm<<endl;

    vector<double> smearKine = {M_V0_ScSm, P_emScSm, P_epScSm, PV0ScSm};
    return smearKine;
}

void InitSmearPars() {

    file_smearPars = new TFile("MomSmearScale.root", "Read");
    trSmear = (TTree*) file_smearPars->Get("tr1");

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
}

void FillPositDistributions(HpsParticle* ep) {

    double P = GetMagnitude(((GblTrack*) ep->getTracks()->At(0))->getMomentum());
    double cl_E = ((EcalCluster*) ep->getClusters()->At(0))->getEnergy();

    if (IsClInFid(ep)) {
        h_Pep_Fid1->Fill(P);
    }
    if (IsClInDeepFid(ep)) {
        h_Pep_DeepFid1->Fill(P);
    }

    if (P < 0.4 || P > 1.8) {
        return;
    }


    int iMomBin;
    if (P > 0.4 && P < 0.8) {
        iMomBin = 0;
    } else if (P > 0.8 && P < 1.2) {
        iMomBin = 1;
    } else {
        iMomBin = 2;
    }


    if (IsClInFid(ep)) {
        h_E_P_ep_Fid1_[iMomBin]->Fill(cl_E / P);
    }

    if (IsClInDeepFid(ep)) {
        h_E_P_ep_DeepFid1_[iMomBin]->Fill(cl_E / P);
    }
}