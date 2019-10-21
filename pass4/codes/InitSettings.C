#include "setting_2016_pass1.h"
#include <TF1.h>
#include <set>

void InitVariables(std::string dataSet) {


    f_clTBotUpLim = new TF1("f_clTBotUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTBotLowLim = new TF1("f_clTBotLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopUpLim = new TF1("f_clTTopUpLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);
    f_clTTopLowLim = new TF1("f_clTTopLowLim", "[0] + x*( [1] + x*[2] )", 0., 2.5);


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



    if (dataSet.compare("Data") == 0) {

        CL_trk_time_Offset = CL_trk_time_Offset_Data;

        ep_d0TightCutMax = ep_d0TightCutMax_Data;
        ep_d0TightCutMin = ep_d0TightCutMin_Data;

        em_d0TightCutMax = em_d0TightCutMax_Data;
        em_d0TightCutMin = em_d0TightCutMin_Data;

        cl_dTCut_Tight = cl_dTCut_Tight_Data;
        
        Pem_MaxTight = Pem_MaxTight_Data;

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


    } else if (dataSet.compare("MC") == 0) {

        CL_trk_time_Offset = CL_trk_time_Offset_tri;

        f_clTBotUpLim->SetParameters(47.5, 0., 0.);
        f_clTBotLowLim->SetParameters(39, 0., 0.);
        f_clTTopUpLim->SetParameters(60., 0., 0.);
        f_clTTopLowLim->SetParameters(30., 0., 0.);
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

    cl_ep = nullptr;
    cl_em = nullptr;
}

void CorrectClusterTime(EcalCluster* cl) {

    int y_ind = cl->getSeed()->getYCrystalIndex();
    int x_ind = cl->getSeed()->getXCrystalIndex();

    double t_corr = h_time_Corrections->GetBinContent(h_time_Corrections->FindBin(x_ind, y_ind));
    cl->setClusterTime(cl->getClusterTime() - t_corr);
}

std::set<int> GetVerticalCrystalls(EcalCluster* cl) {
    std::set<int> vert_crystals;
    for (int i = 0; i < cl->getEcalHits()->GetSize(); i++) {
        vert_crystals.insert(((EcalHit*) cl->getEcalHits()->At(i))->getYCrystalIndex());
    }
    return vert_crystals;
}

bool CheckTightCuts(std::string astr) {

    bool CheckStatus = false;

    if (astr.compare("cldT") == 0) {
        CheckStatus = IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
        //cout<<IsTightemClTrkdT<<"   "<<IsTightepClTrkdT<<"   "<<IsTightemTrkClMatch<<"   "<<IsTightepTrkClMatch<<"   "<<IsTightemtrkChi2
        //        <<"   "<<IsTighteptrkChi2<<"   "<<IsTightPem<<endl;
    } else if (astr.compare("emClTrkdT") == 0) {
        CheckStatus = IsTightcldT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("epClTrkdT") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("emClTrkMatch") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("epClTrkMatch") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("emTrkChi2") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTighteptrkChi2 && IsTightPem;
    } else if (astr.compare("epTrkChi2") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTightPem;
    } else if (astr.compare("Pem") == 0) {
        CheckStatus = IsTightcldT && IsTightemClTrkdT && IsTightepClTrkdT && IsTightemTrkClMatch && IsTightepTrkClMatch && IsTightemtrkChi2 && IsTighteptrkChi2;
    } else {
        cout << "Wrong Argument is provided in the CheckTighCuts function.  Your argument is "<<astr.c_str()<<endl;
        cout<<" The list of possible arguments are" << endl;
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

    return (TMath::Abs(cl1->getClusterTime() - cl1->getClusterTime()) < cl_dTCut_Tight);
}

bool IsTightChi2NdfCutPassed(GblTrack* trk) {

    bool checkStatus = false;

    // For the "Tight" chi2/NDF we didn't see any significant difference
    // wrt 5/6 hits tracks, and whether the track is in the Bottom or Top

    if (isData) {

        if (trk->getChi2() / (2. * (trk->getSvtHits()->GetSize()) - 5.) < chi2NDFTighCut_tData) {
            checkStatus = true;
        }

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

bool IsTightemMaxMomCut(double P){
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