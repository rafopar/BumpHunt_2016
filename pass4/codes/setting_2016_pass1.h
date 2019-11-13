#ifndef __SETTING_2016_PASS__
#define __SETTING_2016_PASS__

#include <set>
#include <map>
#include <TF1.h>
#include <hps_event/EcalCluster.h>

using namespace std;


// =========================================================================
// =====   Const Variables 
// =========================================================================

const double radian = 57.29578;
const double Eb = 2.306;
const double CL_trk_time_Offset_Data = 55.;
const double CL_trk_time_Offset_tri = 43.5;
//const double CL_trk_time_Offset_tri = 51.64;
double CL_trk_time_Offset;
//const double cl_t_max = 80.;
//const double cl_t_min = 20.;
double cl_t_max = 63.;
double cl_t_min = 50.;

const double pos_d0_cut = 1.1;
const double Psum_min = 1.51; // GeV

const double chi2NDFTighCut_Data = 2;
const double chi2NDFTighCut_MC = 2;
double chi2NDFTighCut;

const double ep_d0TightCutMax_Data = 0.5;
const double ep_d0TightCutMin_Data = -0.7;

const double em_d0TightCutMax_Data = 0.7;
const double em_d0TightCutMin_Data = -0.7;

const double cl_dTCut_Tight_Data = 0.7;

const int nSVTLayers = 6;

const double Pem_MaxTight_Data = 1.7;

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
// ========= This function returns the position of the hit associated to the track
// ========= in the given layer
// ========= ============================================================= ============
vector<double> GetHitCoordAtLayer(GblTrack*, int);


// ===== ============================================== ======
// ===== This is a generic function that will return the magnitude of the vector
// ===== In this case the magnitude is defined as the square root of the sums of element squares
// ===== ============================================== ======

double GetMagnitude(vector<double>);







#endif
