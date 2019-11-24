#ifndef __SETTING_2016_PASS__
#define __SETTING_2016_PASS__

#include <set>
#include <map>
#include <TF1.h>
#include <TH2D.h>
#include <hps_event/EcalCluster.h>

using namespace std;


// =========================================================================
// =====   Const Variables 
// =========================================================================

const double radian = 57.29578;
const double Eb = 2.306;
const double CL_trk_time_Offset_Data = 55.;
const double CL_trk_time_Offset_tri = 43.5;
const double CL_trk_time_Offset_WAB = 51.2517;
double CL_trk_time_Offset;
//const double cl_t_max = 80.;
//const double cl_t_min = 20.;
double cl_t_max = 63.;
double cl_t_min = 50.;

const double pos_d0_cut = 1.1;

const double chi2NDFTighCut_Data = 2;
const double chi2NDFTighCut_MC = 2;
double chi2NDFTighCut;

const double ep_d0TightCutMax_Data = 0.5;
const double ep_d0TightCutMin_Data = -0.7;
const double ep_d0TightCutMax_MC = 0.4;
const double ep_d0TightCutMin_MC = -0.5;

const double em_d0TightCutMax_Data = 0.7;
const double em_d0TightCutMin_Data = -0.7;
const double em_d0TightCutMax_MC = 0.7;
const double em_d0TightCutMin_MC = -0.7;

const double cl_dTCut_Tight_Data = 0.7;
const double cl_dTCut_Tight_MC = 0.4;

const int nSVTLayers = 6;

const double Pem_MaxTight_Data = 1.75;
const double Pem_MaxTight_MC = 1.75;
const double Pem_MaxCut_Data = 1.75;
const double Pem_MaxCut_MC = 1.75;

const double cl_dTcut_Data = 1.43;
const double PsumCutMax_Data = 2.4;
const double PsumCutMax_MC = 2.4;
const double PsumCutMin_Data = 1.51; // GeV
const double PsumCutMin_MC = 1.51; // GeV

const double d0_cut_Data = 1.18; // From pass1 Data and MC, will be revised with new MC
const double d0_cut_MC = 0.7; // Needs to be verified

// =========================================================================
// =====  Definition of Non-Const Variables
// =========================================================================

// ==== ============================
// ==== Boolean variables
// ==== ============================

bool isData;
bool isMC;
bool isTri;
bool isRad;
bool isWab;
bool isAp;

// =========================================================================
// ========== Flags for Tight cuts on different variables =========
// =========================================================================

bool IsTightcldT;
bool IsTightemClTrkdT;
bool IsTightepClTrkdT;
bool IsTightemTrkClMatch;
bool IsTightepTrkClMatch;
bool IsTightemtrkChi2;
bool IsTighteptrkChi2;
bool IsTightPem;
bool IsTightD0ep;
bool IsTightD0em;


// =========================================================================
// ==== Flags for cuts on different variables (Those are Non-Tight cut flags)
// =========================================================================

bool IscldT;
bool IsemClTrkdT;
bool IsepClTrkdT;
bool IsemTrkClMatch;
bool IsepTrkClMatch;
bool IsemtrkChi2;
bool IseptrkChi2;
bool IsPem;
bool IsD0ep;
bool IsD0em;
bool IsPsumMax;
bool IsPsumMin;


// ========================================================================
// === Bool variables defining which program is running
// ========================================================================
bool isEventSelection = false;
bool isTrkClusterMatching = false;
bool isECalTimeStudies = false;

// ==== ============================
// ==== Int variables
// ==== ============================

int ApMass = 0;

std::set<int> ApMassSet;

double Pem_MaxTight;
double cl_dTCut_Tight;

// ====== Track quality cuts ======
double ep_d0TightCutMax;
double ep_d0TightCutMin;

double em_d0TightCutMax;
double em_d0TightCutMin;

double Pem_MaxCut;

double cl_dTcut;

double PsumCutMax;
double PsumCutMin;
double d0_cut;

double SVTLayerBinnings[nSVTLayers + 1] = {50., 150., 250., 400., 600., 800., 950.};

// ========= ================================ ============
// ========= Normalizatin factors from Sebouh ============
// ========= ================================ ============

// (# of recon files)*(generated/readout)*(events per generated file)/(sigma in barns) = lumi in inverse barns
double wab_mc_lumi = (9898 * 1 * 10000) / 220.6e-3;
double tritrig_mc_lumi = (900 * 1 * 10000) / 1.1416e-3;
double rad_mc_lumi = (100 * 1 * 10000) / .0667e-3;

// (mass per area of target (g/cm^2))/(molar mass/Avagadro's number)*(10^-24 cm^2/barn)/(electron charge)
double lumi_per_C = 0.00782 / (183.8 / 6.023E+23)*1e-24 / 1.602E-19;
double charge = 827975.643e-9 / 10; // divide by 10 for blinding
double tri_data_lumi = charge*lumi_per_C;


// =========================================================================
// ===== String variables
// =========================================================================
// ====== Data Set, it should be either "Data" or "MC"
std::string dataSet;

std::string inpFileName;
std::string outFileName;
std::string trkClustMatchFileName;
std::string cutHistFileName;
std::string cutHistFileName2;



// =========================================================================
// ===== Root standard type variables, e.g. TH1, TF1, TFile etc...
// =========================================================================

TH1D *h_SVTLayerBinning;

// ====== This histogram should have time corrections for each crystal ======
TH2D *h_time_Corrections;


// =========================================================================
// ====== The input and output files. They will be initianalized inside the InitVariables function
// ====== Depending it is data or MC, it will read a different file
// =========================================================================
TFile *file_in;
TFile *file_out;
/*The file that contains trk-cluster Matching histograms*/
TFile *file_trkClustMatch;
/* Histograms from this file will be used for determining cut limits e.g. keeping 99% of events */
TFile *file_CutHists;
/* This file will contain same histograms for cut determination, and also actual histograms that
 * were determined, i.e. if the variable is acceptable, then the corresponding bin content is 1, otherwise it is 0
 */
TFile *file_CutHists2;


// =========================================================================
// ===== Cluster time custs as a function of Energy
// =========================================================================
TF1 *f_clTBotUpLim;
TF1 *f_clTBotLowLim;
TF1 *f_clTTopUpLim;
TF1 *f_clTTopLowLim;

// ======= ================================ ========
// ======= Track-Cluster Matching Functions
// ======= ================================ ========

// === ================ ===
// === Spatial matching 
// === ================ ===

// ====== Positives =====
TF1 *f_dXTopWithL6Pos_TightUpperLim;
TF1 *f_dXTopWithL6Pos_TightLowerLim;

TF1 *f_dXTopNoL6Pos_TightUpperLim;
TF1 *f_dXTopNoL6Pos_TightLowerLim;

TF1 *f_dXBotWithL6Pos_TightUpperLim;
TF1 *f_dXBotWithL6Pos_TightLowerLim;

TF1 *f_dXBotNoL6Pos_TightUpperLim;
TF1 *f_dXBotNoL6Pos_TightLowerLim;

// ====== Negatives =====
TF1 *f_dXTopWithL6Neg_TightUpperLim;
TF1 *f_dXTopWithL6Neg_TightLowerLim;

TF1 *f_dXTopNoL6Neg_TightUpperLim;
TF1 *f_dXTopNoL6Neg_TightLowerLim;

TF1 *f_dXBotWithL6Neg_TightUpperLim;
TF1 *f_dXBotWithL6Neg_TightLowerLim;

TF1 *f_dXBotNoL6Neg_TightUpperLim;
TF1 *f_dXBotNoL6Neg_TightLowerLim;

// === ================ ===
// === Time matching 
// === ================ ===

TF1 *f_trkCl_dt_Top_TightUpperLim;
TF1 *f_trkCl_dt_Top_TightLowerLim;
TF1 *f_trkCl_dt_Bot_TightUpperLim;
TF1 *f_trkCl_dt_Bot_TightLowerLim;


// === ================== ===
// === Some histograms need some regions to be trashed before
// === creating Cut histograms. Below TF1 functions will 
// ==== determine these regions
// === ================== ===

TF1 *f_TrashUp_dX_Top_PosWithL6;
TF1 *f_TrashLow_dX_Top_PosWithL6;
TF1 *f_TrashUp_dX_Top_PosNoL6;
TF1 *f_TrashLow_dX_Top_PosNoL6;
TF1 *f_TrashUp_dX_Bot_PosWithL6;
TF1 *f_TrashLow_dX_Bot_PosWithL6;
TF1 *f_TrashUp_dX_Bot_PosNoL6;
TF1 *f_TrashLow_dX_Bot_PosNoL6;

TF1 *f_TrashUp_dX_Top_NegWithL6;
TF1 *f_TrashLow_dX_Top_NegWithL6;
TF1 *f_TrashUp_dX_Top_NegNoL6;
TF1 *f_TrashLow_dX_Top_NegNoL6;
TF1 *f_TrashUp_dX_Bot_NegWithL6;
TF1 *f_TrashLow_dX_Bot_NegWithL6;
TF1 *f_TrashUp_dX_Bot_NegNoL6;
TF1 *f_TrashLow_dX_Bot_NegNoL6;



// ========= ========================================================================= ========
// ========= Histograms  ========
// ========= ========================================================================= ========
TH2D *h_dX_Top_PosWithL6_Cut;
TH2D *h_dX_Top_PosNoL6_Cut;
TH2D *h_dX_Bot_PosWithL6_Cut;
TH2D *h_dX_Bot_PosNoL6_Cut;

TH2D *h_dX_Top_NegWithL6_Cut;
TH2D *h_dX_Top_NegNoL6_Cut;
TH2D *h_dX_Bot_NegWithL6_Cut;
TH2D *h_dX_Bot_NegNoL6_Cut;

TH2D *h_trkCl_dt_P_Top_Cut;
TH2D *h_trkCl_dt_P_Bot_Cut;

// ========= ========================================================================= ========
// ========= DST HPS type variables
// ========= ========================================================================= ========

EcalCluster *cl_ep;
EcalCluster *cl_em;

// ========= ========================================================================= ========
// ========= Definition of functions
// ========= ========================================================================= ========

// ======== Initialize Any constants or function that are needed ======

void InitVariables(std::string);

// ========= ========================================================================= ========
// ========= This function resets variables/flags, usually this needs to be called
// ========= at the beginning of every event
// ========= ========================================================================= ========
void ResetEventFlags();


// ========= ========================================================================= ========
// ========= This function resets variables/flags, usually this needs to be called
// ========= at the beginning of every V0 candidate
// ========= ========================================================================= ========
void ResetV0Flags();

// ====== This function cuts clusters that have cluster time far from the the expected 
// ====== signal time
bool IsIntimeClusterCandidate(EcalCluster*);

// ======= This function should implement cluster time corrections
void CorrectClusterTime(EcalCluster*);

// ======= This function returns number of rows the given crystal cover.
std::set<int> GetVerticalCrystalls(EcalCluster*);


// ========= ============================================================= ============
// ========= This check if all other variables (Except the given) passed cuts
// ========= ============================================================= ============

bool CheckAllOtherCuts(std::string);


// ========= ============================================================= ============
// ========= The function below Checks if all tight cuts except the given, are passed
// ========= ============================================================= ============
bool CheckTightCuts(std::string);

// ========= ============================================================= ============
// ========= This function check whether two clusters are satisfy top-bot 
// ========= tight cut
// ========= ============================================================= ============

bool IsCldtTightCutPass(EcalCluster*, EcalCluster*);


// ========= ============================================================= ============
// ========= This function checks if the track passed the "Tight" chi2/NDF cut
// ========= ============================================================= ============
bool IsTightChi2NdfCutPassed(GblTrack*);

// ========= ============================================================= ============
// ========= This function check whether the given track and cluster pass 
// ========= time tight cuts
// ========= ============================================================= ============

bool IsTightTrkClust_dtCutPassed(GblTrack*, EcalCluster*);

// ========= ============================================================= ============
// ========= This function check whether the given track and cluster pass 
// ========= position tight cuts
// ========= ============================================================= ============
bool IsTightTrkClust_dXCutPassed(GblTrack*, EcalCluster*);


// ========= ============================================================= ============
// ========= This function check whether the given track and cluster pass 
// ========= position and time tight cuts
// ========= ============================================================= ============
bool IsTightTrkClustCutPassed(GblTrack*, EcalCluster*);



// ========= ============================================================= ============
// ========= This function checks if electron track momentum is below the
// ========= tight cut value;
// ========= ============================================================= ============

bool IsTightemMaxMomCut(double);


// ========= ============================================================= ============
// ========= This function checks if the track passed the "Tight" d0 cut
// ========= ============================================================= ============
bool IsTightD0CutPassed(GblTrack*);



// ========= ============================================================= ============
// ========= This function checks whether the track has a hit in L1
// ========= ============================================================= ============
bool HasL1Hit(GblTrack*);

// ========= ============================================================= ============
// ========= This function checks whether the track has a hit in L6
// ========= ============================================================= ============
bool HasL6Hit(GblTrack*);


// ========= ============================================================= ============
// ========= Cluster time difference cut
// ========= ============================================================= ============
bool IscldTCut(EcalCluster*, EcalCluster*);

// ========= ============================================================= ============
// ========= The Electron Momentum cut ============
// ========= ============================================================= ============
bool IsEmMaxMomCut(double);

// ========= ============================================================= ============
// ========= TrackClusterMatching ============
// ========= ============================================================= ============
bool IsTrkClusterMatch(GblTrack*, EcalCluster*);


// ========= ============================================================= ============
// ========= Track-Cluster dX Matching ============
// ========= ============================================================= ============
bool IsTrkClusterdXMatch(GblTrack*, EcalCluster*);

// ========= ============================================================= ============
// ========= Track-Cluster time difference Matching ============
// ========= ============================================================= ============
bool IsTrkClusterdTMatch(GblTrack*, EcalCluster*);


// ========= ============================================================= ============
// ========= Psum cut ============
// ========= ============================================================= ============
bool IsPsumMaxCut(double);

// ========= ============================================================= ============
// ========= Psum cut ============
// ========= ============================================================= ============
bool IsPsumMinCut(double);


// ========= ============================================================= ============
// ========= d0 cut ============
// ========= ============================================================= ============
bool IsD0Cut(double);

// ========= ============================================================= ============
// ========= This function returns the position of the hit associated to the track
// ========= in the given layer
// ========= ============================================================= ============
vector<double> GetHitCoordAtLayer(GblTrack*, int);


// ===== ============================================== ======
// ===== This is a generic function that will return the magnitude of the vector
// ===== In this case the magnitude is defined as the square root of the sums of element squares
// ===== ============================================== ======

double GetMagnitude(vector<double>);

// ===== ==============================================     ======
// ===== A function that you give as a 1st argument the     ======
// ===== input histogram, and for each xbin, it determines  ======
// ===== lbin, rbin, that events below lbin are less than   ======
// ===== a half of a given fraction (3rd argument), and     ======
// ===== and events above the rbin are similarly less       ======
// ===== than the half od a given fraction. The bin content ======
// ===== of all bins in between lbin and rbin are set to 1  ======
// ===== and the rest of bins are set to 0.                 ======
// ===== ==============================================     ======

void DefineCutGeneral(TH2D*, TH2D*, double);

// ===== ==============================================     ======
// ===== This function will go over all 2D Cut histograms   ======
// ===== and for each histo, will create and Initialize cut ======
// ===== histograms.                                        ======
// ===== ==============================================     ======
void InitCutHistograms();



#endif
