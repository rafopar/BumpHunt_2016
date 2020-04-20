#include "MoellerSettings.h"

#include <TFile.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include <iostream>

using namespace std;

void InitSettings(std::string dataSet) {


    isData = false;
    isMC = false;

    rand1 = new TRandom();

    if (dataSet.compare("Data") == 0) {

        isData = true;
        //inpFileName = "../Data/hps_008099_All_Moller_4.2.root";
        //inpFileName = "../Data/hps_007796_All_Moller_4.2.root";
        //inpFileName = "../Data/hps_007966_All_Moller_4.2.root";
        //inpFileName = "../Data/hps_008096_All_Moller_4.2.root";

        //inpFileName = "../Data/hps_Moeller_Data_All.root";
        //inpFileName = "../Data/Moeller_8099.root";
        inpFileName = "../Data/Moeller_7966.root";
        outFileName = "MoellerAnalyze_Data.root";

    } else if (dataSet.compare("MC") == 0) {
        isMC = true;

        //inpFileName = "../Data/olv3_HPS-PhysicsRun2016-Nominal-v4-4-fieldmap_3.8-fix_noTrigger_All.root";
        //inpFileName = "../Data/skim_Moeller_ClTimeFixed.root";
        inpFileName = "../Data/skim_Moeller_beam_All.root";
        //inpFileName = "../Data/skim_Moeller.root";
        outFileName = "MoellerAnalyze_MC.root";
    }

    InitSmearPars();

    file_in = new TFile(inpFileName.c_str(), "Read");

    tr1 = (TTree*) file_in->Get("HPS_Event");

    ev = new HpsEvent();

    b_hps_event = tr1->GetBranch("Event");
    b_hps_event->SetAddress(&ev);

    SVTtrack = nullptr;
    trk = nullptr;
    cl = nullptr;
    clTop = nullptr;
    clBot = nullptr;
    ec_hit = nullptr;
    svt_hit = nullptr;
    part = nullptr;

    Topem = nullptr;
    Botem = nullptr;

    if (isData) {
        CL_trk_time_Offset = CL_trk_time_Offset_Data;
        tr_dT_Max = tr_dT_Max_Data;
        tr_dT_Min = tr_dT_Min_Data;
        PSumMax = PSumMax_Data;
        PSumMin = PSumMin_Data;
    }


    if (isMC) {
        CL_trk_time_Offset = CL_trk_time_Offset_tri;
        tr_dT_Max = tr_dT_Max_MC;
        tr_dT_Min = tr_dT_Min_MC;
        PSumMax = PSumMax_MC;
        PSumMin = PSumMin_MC;
    }


    // ==== We want to open it at the end, that gDirectory->Write will try to save histos in this file ===
    file_out = new TFile(outFileName.c_str(), "Recreate");
}

void ResetEventFlags() {
}

void ResetConstrainedMollerFlags() {
    Topem = nullptr;
    Botem = nullptr;

    topChi2 = 0;
    botChi2 = 0;

    HasTopL1 = false;
    HasBotL1 = false;
}

int DoesQualifyMoeller(HpsParticle *part) {

    int stat = 0;

    int stat_Size = 0;
    int stat_charges = 0;
    int stat_oppositeHalves = 0;
    int stat_ClusterPresence = 0;

    if (part->getParticles()->GetSize() != 2) {
        //cout << "# of v0 is " << part->getParticles()->GetSize() << endl;
        //cout << "# of v0 daughters is not 2!" << endl;
        stat_Size = 1;

        // ===== Next two steps can not be checked, if it failes this step
        stat = stat_Size;
        return stat;
    }


    if (!(((HpsParticle*) part->getParticles()->At(0))->getCharge() < 0 && ((HpsParticle*) part->getParticles()->At(1))->getCharge() < 0)) {

        cout << "Charges are    " << ((HpsParticle*) part->getParticles()->At(0)) << "   and   " << ((HpsParticle*) part->getParticles()->At(1)) << endl;
        cout << "Moeller pairs should both have Negative charges" << endl;
        stat_charges = 10;
    }


    double y_pos0 = ((GblTrack*) ((HpsParticle*) part->getParticles()->At(0))->getTracks()->At(0))->getPositionAtEcal().at(1);
    double y_pos1 = ((GblTrack*) ((HpsParticle*) part->getParticles()->At(1))->getTracks()->At(0))->getPositionAtEcal().at(1);

    if (y_pos0 * y_pos1 >= 0) {
        cout << "Tracks are not in opposite halves." << endl;
        stat_oppositeHalves = 100;
    }


    if (!(((HpsParticle*) part->getParticles()->At(0))->getClusters()->GetSize() >= 1 &&
            ((HpsParticle*) part->getParticles()->At(1))->getClusters()->GetSize() >= 1)) {
        //cout << "One of Moeller particles doesn't have a cluster!"<<endl;
        stat_ClusterPresence = 0;
        //stat_ClusterPresence = 500;
    }

    stat = stat_Size + stat_charges + stat_oppositeHalves + stat_ClusterPresence;

    return stat;

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

double GetMagnitude(vector<double> v) {

    double magn2 = 0;

    for (int i = 0; i < v.size(); i++) {
        magn2 = magn2 + v.at(i) * v.at(i);
    }

    return sqrt(magn2);
}

bool TrackFiducial(double tr_x, double tr_y) {

    bool fiducial = false;

    if (isData) {

        if (tr_y > 0) {
            if (tr_y < 42. && tr_y < 13 - 0.26 * tr_x && tr_y > 18 - 0.08 * tr_x && ((tr_x > -125. && tr_x < -95.) || (tr_x > -85 && tr_x < -55.))) {
                fiducial = true;
            }
        } else if (tr_y < 0) {
            if (tr_y < -23. && tr_y < -15. + 0.08 * tr_x && tr_y > -18. + 0.22 * tr_x && ((tr_x > -75. && tr_x < -45) || (tr_x > -110. && tr_x < -95.))) {
                fiducial = true;
            }
        }

    } else if (isMC) {

        if (tr_y > 0) {

            if (tr_y > 23. && tr_y > 15 - 0.1 * tr_x && tr_y < 12 - 0.3 * tr_x && ((tr_x > -75. && tr_x < -50.) || (tr_x > -130. && tr_x < -95))) {
                fiducial = true;
            }

        } else if (tr_y < 0) {

            if (tr_y < -22 && tr_y < -15 + 0.1 * tr_x && tr_y > -15 + 0.25 * tr_x && ((tr_x > -120. && tr_x < -94) || (tr_x > -75 && tr_x < -50.))) {
                fiducial = true;
            }

        }

    }


    return fiducial;

    // if (tr_y > 0) {

    /*
     * 
     * ********** DATA ***********
     TOP:
     * tr_y > 18 - 0.08 * tr_x
     * tr_y < 13 - 0.26 * tr_x
     * tr_y < 42.
     * tr_x > -125. && tr_x < -90. || tr_x > -85 && tr_x < -52.
     * 
     * 
         
     *BOT:
     * tr_y < -20.
     * tr_y < -15. + 0.08 * tr_x
     * tr_y > -18. + 0.22 * tr_x
     * tr_x > -70. && tr_x < -40
     * tr_x > -110. && tr_x < -95.
         
     * 
     * 
     * ************ MC ************
     * 
     * TOP
     * 
     * tr_y > 23
     * 
     * tr_x > - 75. && tr_x < -50.
     * tr_x > -130. && tr_x < -95
     * tr_y > 15 - 0.1*tr_x
     * tr_y < 12 - 0.3*tr_x
     * 
     * 
     * BOT
     * 
     * tr_y < -22
     * tr_y < -15 + 0.1*tr_x
     * tr_y > -15 + 0..25*tr_x
     * tr_x > -120. && tr_x < -94
     * tr_x > -80 && tr_x < -50.
     * 
     */





    //        if (tr_x > -125 && tr_x < -97.) {
    //
    //            if (tr_y > 26. && tr_y < 40.) {
    //                fiducial = true;
    //            }
    //        } else if (tr_x > -85. && tr_x < -60.) {
    //            if (tr_y > 23. && tr_y < 31.) {
    //                fiducial = true;
    //            }
    //
    //        }
    //    } else {
    //        if (tr_x > -112. && tr_x < -95.) {
    //            if (tr_y > -40 && tr_y < -27.) {
    //                fiducial = true;
    //            }
    //        } else if (tr_x > -95. && tr_x < -85) {
    //            if (tr_y > -39. && tr_y < -33.) {
    //                fiducial = true;
    //            }
    //
    //        } else if (tr_x > -70. && tr_x < -48.) {
    //            if (tr_y > -30. && tr_y < -23.) {
    //                fiducial = true;
    //            }
    //
    //        }
    //    }
    //
    //    return fiducial;
}

bool TrackInHole(double tr_x, double tr_y) {

    bool InHole = (tr_x > -95 && tr_x < -20. && TMath::Abs(tr_y) < 35);

    return InHole;
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
