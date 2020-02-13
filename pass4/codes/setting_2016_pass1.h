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
const double CL_trk_time_Offset_tri = 44.8;
const double CL_trk_time_Offset_WAB = 44.8;
const double CL_trk_time_Offset_Rad = 44.8;
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

const double Pem_MaxTight_Data = 1.8;
const double Pem_MaxTight_MC = 1.75;
const double Pem_MaxCut_Data = 1.75;
const double Pem_MaxCut_MC = 1.72;

const double cl_dTcut_Data = 1.43;
const double PsumCutMax_Data = 2.4;
const double PsumCutMax_MC = 2.4;
const double PsumCutMin_Data = 1.51; // GeV
const double PsumCutMin_MC = 1.51; // GeV

const double d0_cut_Data = 1.176; // From pass1 Data and MC, will be revised with new MC
const double d0_cut_MC = 0.65; // Needs to be verified

const int nMinvBins = 12; // # of Minv bins, We want to study Psum for different Minv Bins
const double MinvMin = 0.;
const double MinvMax = 0.24;

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
bool hasepL1;


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

// ==================================
// =====     The Cut Keyword
// =====             |-- L1 requirement for e+ (1: required, 0: Not required)
// =====             |
// =====             | - d0 cut (1: applied, 0: Not applied)
// =====             | | 
// ===== - - - - - - - - 
// ==================================
int CutsKey; // This should be determined for each V0 candidate

// ===== This vector will contain vector of CutsKeys, that the given V0 will satisfy
vector<int> v_CutsKeys;

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

int MinvBin;

// ========= ================================ ============
// ========= Normalizatin factors from Sebouh ============
// ========= ================================ ============

const double tritrig_SigmaGen = 1.416e-3;
const double NGen_tritrig = 985. * 50000.; /* 985 recon files, and each recon has 50K Gen events*/

const double Rad_SigmaGen = 81.61e-6;
const double NGen_Rad = 4989 * 10000.;

const double Wab_SigmaGen = 0.1985;
const double NGen_Wab = 9965. * 100000.;

const double Lumin8099 = 237.e9;

// =============================================================================
// === Old Pass1 Normalizations 
// =============================================================================

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
// ===== Map of vectors for Minv, Different Keys will represent
// ===== different set of cuts that the v0 candidate passed
// ===== This map will contain vector of Minv that pass the set of cuts
// ===== determined by the Key
// =========================================================================

map<int, vector<double> > m_v_ee;
map<int, vector<double> > m_v_PSum;


map<int, vector<double> > m_v_Minv_General;
map<int, vector<double> > m_v_PSum_General;



// =========================================================================
// ===== Map of histograms for for
// ===== different set of cuts that the v0 candidate passed
// =========================================================================

const int NCutInQuestion = 3;

// Events with one or more V0 candidates
// Require L1 hit from positron
// Place cut on d0?


// ==================================
// =====     The Cut Keyword
// =====             |------ L1 requirement for e+ (1: required, 0: Not required)
// =====             |
// =====             | ----- d0 cut (1: applied, 0: Not applied)
// =====             | | 
// =====             | | --- # of V0 candidates: (1: if # of V0s with a given conditions is one, 0: otherwise)
// =====             | | |
// =====             | | |
// = bit - - 6 5 4 3 2 1 0

map<int, TH1D*> m_h_Minv;
map<int, TH1D*> m_h_Psum;

// ========== Here the extension general refers to histograms that can be filled more often,
// ========== i.e. if the the V0 has ep_d0 cut passed, then both with/ and without d0 histograms will be filled

map<int, TH1D*> m_h_Minv_General;
map<int, TH1D*> m_h_Psum_General;

// ==================================

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

TH1D *h_MinvBins1;


// =================== Trk Cluster Matching histograms ============
// =================== These include All, AllBut, CutEffect =======

TH1D *h_clDt_All;
TH1D *h_clDt_AllBut;
TH1D *h_clDt_CutEffect;

TH2D *h_cl_trk_dT_All;
TH2D *h_cl_trk_dT_AllBut;
TH2D *h_cl_trk_dT_CutEffect;

TH2D *h_cl_trk_dT_Top_All;
TH2D *h_cl_trk_dT_Top_AllBut;
TH2D *h_cl_trk_dT_Top_CutEffect;

TH2D *h_cl_trk_dT_Bot_All;
TH2D *h_cl_trk_dT_Bot_AllBut;
TH2D *h_cl_trk_dT_Bot_CutEffect;

TH2D *h_em_cl_trk_dT_All;
TH2D *h_em_cl_trk_dT_AllBut;
TH2D *h_em_cl_trk_dT_CutEffect;

TH2D *h_em_cl_trk_dT_Top_All;
TH2D *h_em_cl_trk_dT_Top_AllBut;
TH2D *h_em_cl_trk_dT_Top_CutEffect;

TH2D *h_em_cl_trk_dT_Bot_All;
TH2D *h_em_cl_trk_dT_Bot_AllBut;
TH2D *h_em_cl_trk_dT_Bot_CutEffect;


TH2D *h_ep_cl_trk_dT_All;
TH2D *h_ep_cl_trk_dT_AllBut;
TH2D *h_ep_cl_trk_dT_CutEffect;

TH2D *h_ep_cl_trk_dT_Top_All;
TH2D *h_ep_cl_trk_dT_Top_AllBut;
TH2D *h_ep_cl_trk_dT_Top_CutEffect;

TH2D *h_ep_cl_trk_dT_Bot_All;
TH2D *h_ep_cl_trk_dT_Bot_AllBut;
TH2D *h_ep_cl_trk_dT_Bot_CutEffect;


TH2D *h_dX_em_All;
TH2D *h_dX_em_AllBut;
TH2D *h_dX_em_CutEffect;

TH2D *h_dX_emTopWithL6_All;
TH2D *h_dX_emTopWithL6_AllBut;
TH2D *h_dX_emTopWithL6_CutEffect;
TH2D *h_dX_emTopNoL6_All;
TH2D *h_dX_emTopNoL6_AllBut;
TH2D *h_dX_emTopNoL6_CutEffect;
TH2D *h_dX_emBotWithL6_All;
TH2D *h_dX_emBotWithL6_AllBut;
TH2D *h_dX_emBotWithL6_CutEffect;
TH2D *h_dX_emBotNoL6_All;
TH2D *h_dX_emBotNoL6_AllBut;
TH2D *h_dX_emBotNoL6_CutEffect;

TH2D *h_dX_ep_All;
TH2D *h_dX_ep_AllBut;
TH2D *h_dX_ep_CutEffect;

TH2D *h_dX_epTopWithL6_All;
TH2D *h_dX_epTopWithL6_AllBut;
TH2D *h_dX_epTopWithL6_CutEffect;
TH2D *h_dX_epTopNoL6_All;
TH2D *h_dX_epTopNoL6_AllBut;
TH2D *h_dX_epTopNoL6_CutEffect;
TH2D *h_dX_epBotWithL6_All;
TH2D *h_dX_epBotWithL6_AllBut;
TH2D *h_dX_epBotWithL6_CutEffect;
TH2D *h_dX_epBotNoL6_All;
TH2D *h_dX_epBotNoL6_AllBut;
TH2D *h_dX_epBotNoL6_CutEffect;


// =============== Final Event Selection Cuts Cuts ==========
TH1D *h_Minv_Final1;
TH1D *h_Minv_PMax_Final1;
TH1D *h_Minv_PMin_Final1;
TH1D *h_Minv_cldT_Final1;
TH1D *h_Minv_epClTrkdT_Final1;
TH1D *h_Minv_emClTrkdT_Final1;
TH1D *h_Minv_epClTrkMatch_Final1;
TH1D *h_Minv_emClTrkMatch_Final1;
TH1D *h_Minv_Pem_Final1;
TH1D *h_Minv_d0ep_Final1;


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

// ======= This function returns the CutsKey for a given V0 candidate =======
int GetCutsKey();

// ======= This function Fills the vector of CutsKey for a given V0 candidate,  =======
// ======= that the current V0 will satisfy =======
void FillVectorOfCutsKeys();


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
// ===== Fill "dx VS P" histograms, it will figure out
// ===== which category it is, whether it is top/bot or
// ===== has L6 or has no L6 hit
// ===== ==============================================     ======
void FilldXP_ep(HpsParticle *V0, HpsParticle *Part, double P, double dX);
void FilldXP_em(HpsParticle *V0, HpsParticle *Part, double P, double dX);


// ===== ==============================================     ======
// ===== Fill "dt VS P" histograms, it will figure out
// ===== which category it is, whether it is top or bot
// ===== ==============================================     ======
void FilldtP_ep(HpsParticle *V0, HpsParticle *Part, double P, double dp);
void FilldtP_em(HpsParticle *V0, HpsParticle *Part, double P, double dp);


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


// ===== This function will go over  histograms   ======
// ===== and for each histo, will create and Initialize cut ======
// ===== histograms.                                        ======
// ===== ==============================================     ======
void InitGeneralHistograms();

#endif
