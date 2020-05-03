/* 
 * File:   FEEStudy.cc
 * Author: rafopar
 *
 * Created on March 10, 2020, 1:37 PM
 */

#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TFile.h>
#include <TRandom.h>

#include <hps_event/HpsEvent.h>
#include <hps_event/EcalCluster.h>

#include <cstdlib>

using namespace std;

/*
 * 
 */
double GetMagnitude(vector<double> v);
bool ECalFEECut(GblTrack*);

int main(int argc, char** argv) {

    std::string dataSet;

    bool isData = false;
    if (argc >= 2) {

        dataSet = argv[1];

    } else {
        cout << "No argument is provided " << endl;
        cout << "Rus as follows: Eg  ./EventSelection.exe Data" << endl;
        cout << "Exiting" << endl;

        exit(1);
    }

    TRandom *rand1 = new TRandom();

    const int n_X_Regions = 8;
    const double Eb = 2.306;
    //const double sigm_smear = 0.11;

    double sigm_smear_Top = 0.9 * 4.98966 / 100.; // factor 0.9 is empirical, seems it is overexpanding a little bit
    double sigm_smear_Bot = 0.9 * 4.96235 / 100.; // factor 0.9 is empirical, seems it is overexpanding a little bit

    double scaleTop_Data = 1.01225;
    double scaleBot_Data = 1.01825;
    //    double scaleTop_MC = 1.02343;  // factor 2 is kind of empirical without this it deson't go to the right place
    //    double scaleBot_MC = 1.0210;   // factor 2 is kind of empirical without this it deson't go to the right place
    double scaleTop_MC = 1. + 1.5 * (1.02343 - 1.); // factor 2 is kind of empirical without this it deson't go to the right place
    double scaleBot_MC = 1. + 1.5 * (1.0210 - 1.); // factor 2 is kind of empirical without this it deson't go to the right place


    std::string inpFile;
    if (dataSet.compare("Data") == 0) {
        inpFile = "../Data/skim_Singles_8099.root";
        isData = true;
    } else if (dataSet.compare("Mlr") == 0) {
        inpFile = "../Data/skim_Moeller_beam_All.root";
    }

    TFile *file_smearPars = new TFile("MomSmearScale.root", "Read");
    TTree *trSmear = (TTree*) file_smearPars->Get("tr1");

    //TFile *file_in = new TFile("../Data/hps_008099.145_dst_4.2.root");
    TFile *file_in = new TFile(inpFile.c_str());
    TFile *file_out = new TFile(Form("FEE_Studies_%s.root", dataSet.c_str()), "Recreate");

    TH1D *h_nOtherElectrons1 = new TH1D("h_nOtherElectrons1", "", 11, -0., 10.5);
    TH1D *h_nFSP1 = new TH1D("h_nFSP1", "", 11, -0., 10.5);
    TH1D *h_nAllelectrons1 = new TH1D("h_nAllElectrons1", "", 11, -0., 10.5);

    TH1D *h_Pem1 = new TH1D("h_Pem1", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2 = new TH1D("h_Pem2", "", 400, 0., 1.35 * Eb);

    TH2D *tr_P_X_Top6hits = new TH2D("tr_P_X_Top6hits", "", 200, -300, 220., 200, 0., 1.35 * Eb);
    TH2D *tr_P_X_Top5hits = new TH2D("tr_P_X_Top5hits", "", 200, -300, 220., 200, 0., 1.35 * Eb);
    TH2D *tr_P_X_Bot6hits = new TH2D("tr_P_X_Bot6hits", "", 200, -300, 220., 200, 0., 1.35 * Eb);
    TH2D *tr_P_X_Bot5hits = new TH2D("tr_P_X_Bot5hits", "", 200, -300, 220., 200, 0., 1.35 * Eb);

    TH1D *h_Pem2_Top = new TH1D("h_Pem2_Top", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Top5hits = new TH1D("h_Pem2_Top5hits", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Top6hits = new TH1D("h_Pem2_Top6hits", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Bot = new TH1D("h_Pem2_Bot", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Bot5hits = new TH1D("h_Pem2_Bot5hits", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Bot6hits = new TH1D("h_Pem2_Bot6hits", "", 400, 0., 1.35 * Eb);
    TH1D *h_chi2NDF1 = new TH1D("h_chi2NDF1", "", 200, 0., 25.);

    TH1D *h_Pem2Smear_Top = new TH1D("h_Pem2Smear_Top", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2Smear_Bot = new TH1D("h_Pem2Smear_Bot", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2ScaledSmear_Top = new TH1D("h_Pem2ScaledSmear_Top", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2ScaledSmear_Bot = new TH1D("h_Pem2ScaledSmear_Bot", "", 400, 0., 1.35 * Eb);

    TH1D * h_Pem2_[n_X_Regions];
    TH1D * h_Pem2_Top6hits_[n_X_Regions];
    TH1D * h_Pem2_Top5hits_[n_X_Regions];
    TH1D * h_Pem2_Bot6hits_[n_X_Regions];
    TH1D * h_Pem2_Bot5hits_[n_X_Regions];

    for (int i = 0; i < n_X_Regions; i++) {
        h_Pem2_[i] = new TH1D(Form("h_Pem2_%d", i), "", 200, 0., 1.35 * Eb);
        h_Pem2_Top6hits_[i] = new TH1D(Form("h_Pem2_Top6hits_%d", i), "", 200, 0., 1.35 * Eb);
        h_Pem2_Top5hits_[i] = new TH1D(Form("h_Pem2_Top5hits_%d", i), "", 200, 0., 1.35 * Eb);
        h_Pem2_Bot6hits_[i] = new TH1D(Form("h_Pem2_Bot6hits_%d", i), "", 200, 0., 1.35 * Eb);
        h_Pem2_Bot5hits_[i] = new TH1D(Form("h_Pem2_Bot5hits_%d", i), "", 200, 0., 1.35 * Eb);
    }

    // ====================== Sc means "Scaled", Sm means "Smeared"
    TH1D *h_Pem2_Top5hitsScSm = new TH1D("h_Pem2_Top5hitsScSm", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Top6hitsScSm = new TH1D("h_Pem2_Top6hitsScSm", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Bot5hitsScSm = new TH1D("h_Pem2_Bot5hitsScSm", "", 400, 0., 1.35 * Eb);
    TH1D *h_Pem2_Bot6hitsScSm = new TH1D("h_Pem2_Bot6hitsScSm", "", 400, 0., 1.35 * Eb);

    // ======= ============== Reading smearing parameters from the tree =================
    double mean_Data_Top5hits;
    double sigm_Data_Top5hits;
    double scale_Data_Top5hits;
    double mean_Data_Top6hits;
    double sigm_Data_Top6hits;
    double scale_Data_Top6hits;
    double mean_Data_Bot5hits;
    double sigm_Data_Bot5hits;
    double scale_Data_Bot5hits;
    double mean_Data_Bot6hits;
    double sigm_Data_Bot6hits;
    double scale_Data_Bot6hits;
    double mean_MC_Top5hits;
    double sigm_MC_Top5hits;
    double scale_MC_Top5hits;
    double mean_MC_Top6hits;
    double sigm_MC_Top6hits;
    double scale_MC_Top6hits;
    double mean_MC_Bot5hits;
    double sigm_MC_Bot5hits;
    double scale_MC_Bot5hits;
    double mean_MC_Bot6hits;
    double sigm_MC_Bot6hits;
    double scale_MC_Bot6hits;
    double smear_Top5hits;
    double smear_Top6hits;
    double smear_Bot5hits;
    double smear_Bot6hits;

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

    cout << "mean_Data_Top5hits = " << mean_Data_Top5hits << endl;

    TH2D *h_tr_YXc1 = new TH2D("h_tr_YXc1", "", 200, -300, 390, 200, -100, 100.);
    TH2D *h_tr_YXc_6hit1 = new TH2D("h_tr_YXc_6hit1", "", 200, -300, 390, 200, -100, 100.);
    TH2D *h_tr_YXc_5hit1 = new TH2D("h_tr_YXc_5hit1", "", 200, -300, 390, 200, -100, 100.);

    TTree *tr1 = (TTree*) file_in->Get("HPS_Event");

    HpsEvent *ev = new HpsEvent();

    TBranch *b_hps_event = tr1->GetBranch("Event");
    b_hps_event->SetAddress(&ev);

    HpsParticle* part = 0;

    vector<HpsParticle *> v_Electrons;

    int nev = tr1->GetEntries();

    //nev = 200000;
    cout << "nev = " << nev << endl;

    for (int ientry = 0; ientry < nev; ientry++) {

        tr1->GetEntry(ientry);

        if ((ientry + 1) % 50000 == 0) {
            cout.flush() << "Processed " << ientry << "\r";
        }

        v_Electrons.clear();
        v_Electrons.shrink_to_fit();

        int nOtherElectrons = ev->getNumberOfParticles(HpsParticle::OTHER_ELECTRONS);
        //cout<<ev->getNumberOfParticles(HpsParticle::OTHER_ELECTRONS)<<endl;

        h_nOtherElectrons1->Fill(nOtherElectrons);

        for (int iother = 0; iother < nOtherElectrons; iother++) {
            v_Electrons.push_back(ev->getParticle(HpsParticle::OTHER_ELECTRONS, iother));
        }

        bool singletrg = ev->isSingle0Trigger() || ev->isSingle1Trigger();

        if (isData && !singletrg) {
            continue;
        }

        int nFSP = ev->getNumberOfParticles(HpsParticle::FINAL_STATE_PARTICLE);

        h_nFSP1->Fill(nFSP);

        for (int iFSP = 0; iFSP < nFSP; iFSP++) {

            HpsParticle *curPart = ev->getParticle(HpsParticle::FINAL_STATE_PARTICLE, iFSP);

            if (curPart->getPDG() == 11) {
                v_Electrons.push_back(curPart);
            }
        }

        h_nAllelectrons1->Fill(v_Electrons.size());

        for (int iel = 0; iel < v_Electrons.size(); iel++) {

            HpsParticle *em = v_Electrons.at(iel);
            GblTrack *em_trk = (GblTrack*) em->getTracks()->At(0);
            double chi2 = em_trk->getChi2();
            int nHits = em_trk->getSvtHits()->GetSize();
            double NDF = 2 * nHits - 5;

            double y_tr = em_trk->getPositionAtEcal().at(1);
            double x_tr = em_trk->getPositionAtEcal().at(0);

            bool isTop = (y_tr > 0.);

            double Pem = GetMagnitude(em->getMomentum());

            h_Pem1->Fill(Pem);
            h_chi2NDF1->Fill(chi2 / NDF);

            h_tr_YXc1->Fill(x_tr, y_tr);
            if (nHits == 5) {
                h_tr_YXc_5hit1->Fill(x_tr, y_tr);
            } else if (nHits == 6) {
                h_tr_YXc_6hit1->Fill(x_tr, y_tr);
            }


            double scaleMom;
            if (isData) {
                // scaleMom = isTop ? scaleTop_Data : scaleBot_Data;

                if (isTop) {
                    if (nHits == 5) {
                        scaleMom = scale_Data_Top5hits;
                    } else if (nHits == 6) {
                        scaleMom = scale_Data_Top6hits;
                    }
                } else {
                    if (nHits == 5) {
                        scaleMom = scale_Data_Bot5hits;
                    } else if (nHits == 6) {
                        scaleMom = scale_Data_Bot6hits;
                    }
                }

            } else {
                // scaleMom = isTop ? scaleTop_MC : scaleBot_MC;

                if (isTop) {
                    if (nHits == 5) {
                        scaleMom = scale_MC_Top5hits;
                    } else if (nHits == 6) {
                        scaleMom = scale_MC_Top6hits;
                    }
                } else {
                    if (nHits == 5) {
                        scaleMom = scale_MC_Bot5hits;
                    } else if (nHits == 6) {
                        scaleMom = scale_MC_Bot6hits;
                    }
                }

            }
            double PemScaled = scaleMom*Pem;


            double sigm_smear;
            double sigm_smearScaled;
            if (isTop) {

                if (nHits == 5) {
                    sigm_smear = smear_Top5hits;
                } else if (nHits == 6) {
                    sigm_smear = smear_Top6hits;
                }

            } else {

                if (nHits == 5) {
                    sigm_smear = smear_Bot5hits;
                } else if (nHits == 6) {
                    sigm_smear = smear_Bot6hits;
                }

            }
            sigm_smearScaled = PemScaled*sigm_smear;

            //            double sigm_smear = isTop ? Pem * sigm_smear_Top : Pem*sigm_smear_Bot;
            //            double sigm_smearScaled = isTop ? PemScaled * sigm_smear_Top : PemScaled*sigm_smear_Bot;


            double PemSmear = rand1->Gaus(Pem, sigm_smear);
            double PemScaledSmear = rand1->Gaus(PemScaled, sigm_smearScaled);
            if (isData) {
                PemSmear = Pem;
                PemScaledSmear = PemScaled;
            }


            //cout<<Pem<<"    "<<PemScaled<<"    "<<PemScaledSmear<<endl;

            if (isnan(x_tr)) {
                continue;
            }

            if (x_tr > -5.) {
                continue;
            }

            int tr_x_region = int(TMath::Abs((x_tr + 25.)) / 10.);

            if (tr_x_region < n_X_Regions) {
                //cout<<x_tr <<"   "<<tr_x_region<<endl;
                h_Pem2_[tr_x_region]->Fill(Pem);

                if (y_tr > 0) {

                    if (nHits == 6) {
                        h_Pem2_Top6hits_[tr_x_region]->Fill(Pem);
                    } else if (nHits == 5) {
                        h_Pem2_Top5hits_[tr_x_region]->Fill(Pem);
                    }

                } else if (y_tr < 0.) {
                    if (nHits == 6) {
                        h_Pem2_Bot6hits_[tr_x_region]->Fill(Pem);
                    } else if (nHits == 5) {
                        h_Pem2_Bot5hits_[tr_x_region]->Fill(Pem);
                    }

                }
            }

            if (y_tr > 0) {

                if (nHits == 6) {
                    tr_P_X_Top6hits->Fill(x_tr, Pem);
                }else if ( nHits == 5 ){
                    tr_P_X_Top5hits->Fill(x_tr, Pem);
                }

            }else if( y_tr < 0. ){
                if (nHits == 6) {
                    tr_P_X_Bot6hits->Fill(x_tr, Pem);
                }else if ( nHits == 5 ){
                    tr_P_X_Bot5hits->Fill(x_tr, Pem);
                }
            }

            if (ECalFEECut(em_trk)) {
                h_Pem2->Fill(Pem);

                if (y_tr > 0) {
                    h_Pem2_Top->Fill(Pem);
                    h_Pem2Smear_Top->Fill(PemSmear);
                    h_Pem2ScaledSmear_Top->Fill(PemScaledSmear);


                    if (nHits == 5) {
                        h_Pem2_Top5hits->Fill(Pem);
                        h_Pem2_Top5hitsScSm->Fill(PemScaledSmear);
                    } else if (nHits == 6) {
                        h_Pem2_Top6hits->Fill(Pem);
                        h_Pem2_Top6hitsScSm->Fill(PemScaledSmear);
                    }

                } else if (y_tr < 0) {
                    h_Pem2_Bot->Fill(Pem);
                    h_Pem2Smear_Bot->Fill(PemSmear);
                    h_Pem2ScaledSmear_Bot->Fill(PemScaledSmear);
                    if (nHits == 5) {
                        h_Pem2_Bot5hits->Fill(Pem);
                        h_Pem2_Bot5hitsScSm->Fill(PemScaledSmear);
                    } else if (nHits == 6) {
                        h_Pem2_Bot6hits->Fill(Pem);
                        h_Pem2_Bot6hitsScSm->Fill(PemScaledSmear);
                    }
                }
            }
        }



    }

    gDirectory->Write();
    file_out->Close();

    return 0;
}

double GetMagnitude(vector<double> v) {

    double magn2 = 0;

    for (int i = 0; i < v.size(); i++) {

        magn2 = magn2 + v.at(i) * v.at(i);
    }

    return sqrt(magn2);
}

bool ECalFEECut(GblTrack* trk) {

    double y_tr = trk->getPositionAtEcal().at(1);
    double x_tr = trk->getPositionAtEcal().at(0);

    //return x_tr > -120. && x_tr < 40.;
    return x_tr > -140. && x_tr < 40.;
    //return x_tr > -140. && x_tr < -120.;
}