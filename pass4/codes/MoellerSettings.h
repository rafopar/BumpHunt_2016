/* 
 * File:   MoellerSettings.h
 * Author: rafopar
 *
 * Created on October 31, 2019, 2:13 PM
 */


#ifndef MOELLERSETTINGS_H
#define MOELLERSETTINGS_H



#include <TRandom.h>

#include <vector>

using namespace std;

const double radian = 57.29578;
const double Eb = 2.306;
const double CL_trk_time_Offset_Data = 55.;
const double CL_trk_time_Offset_tri = 43.5;
const double phi_rot = 0.03; // The 30 mrad rotation
double CL_trk_time_Offset;
double cl_t_max = 63.;
double cl_t_min = 50.;

const double Mlr_PSmear_MC = 0.11 / Eb;


double sigm_smear_Top = 0.9 * 4.98966 / 100.; // factor 0.9 is empirical, seems it is overexpanding a little bit
double sigm_smear_Bot = 0.9 * 4.96235 / 100.; // factor 0.9 is empirical, seems it is overexpanding a little bit

double scaleTop_Data = 1.01225;
double scaleBot_Data = 1.01825;
//    double scaleTop_MC = 1.02343;  // factor 2 is kind of empirical without this it deson't go to the right place
//    double scaleBot_MC = 1.0210;   // factor 2 is kind of empirical without this it deson't go to the right place
double scaleTop_MC = 1. + 1.5 * (1.02343 - 1.); // factor 2 is kind of empirical without this it deson't go to the right place
double scaleBot_MC = 1. + 1.5 * (1.0210 - 1.); // factor 2 is kind of empirical without this it deson't go to the right place


const double tr_dT_Max_Data = 1.6916;
const double tr_dT_Min_Data = -2.94388;
const double tr_dT_Max_MC = 1.54025;
const double tr_dT_Min_MC = -1.44324;
double tr_dT_Max;
double tr_dT_Min;

const double PSumMax_Data = 2.45775;
const double PSumMin_Data = 2.09719;
const double PSumMax_MC = 2.41889;
const double PSumMin_MC = 2.15221;
double PSumMax;
double PSumMin;

const double PDiffHighMax = 0.35;
const double PDiffHighMin = 0.05;
const double PDiffLowMax = -0.15;
const double PDiffLowMin = -0.55;

const double MatchingChi2Median = 5.;
const double MatchingChi2Best = 3.5;

const double pos_d0_cut = 1.1;
const double Psum_min = 1.51; // GeV

const double chi2NDFTighCut_Data = 2;
const double chi2NDFTighCut_MC = 2;
double chi2NDFTighCut;

const double Pem_MaxTight_Data = 1.9;
const double cl_dTCut_Tight_Data = 0.8;

bool isData;
bool isMC;

/* Here the fiducial is not related to the detector volume, but rather it is a region determined by MC
 representing the Moeller acceptance*/
bool TopTrkFiducial = false;
bool BotTrkFiducial = false;

bool TopTrkInHole = false; // A flag telling whether the Top track went through the ECal hole
bool BotTrkInHole = false; // A flag telling whether the Bottom track went through the ECal hole

bool HasTopL1 = false;
bool HasBotL1 = false;

double Pem_MaxTight;
double cl_dTCut_Tight;


double topChi2, botChi2;



// =========================================================================
// ===== Smearing related variables
// =========================================================================
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

TFile *file_smearPars;
TTree *trSmear;


// =========================================================================
// ===== String variables
// =========================================================================
// ====== Data Set, it should be either "Data" or "MC"
std::string dataSet;

std::string inpFileName;
std::string outFileName;


// =========================================================================
// ====== The input and output files. they will be initialized inside the InitVariables function
// ====== Depending it is data or MC, it will read a different file
// =========================================================================
TFile *file_in;
TFile *file_out;


// =========================================================================
// ====== 
// ====== The Tree which will read the HPS_Event 
// =========================================================================

TTree *tr1;


// =========================================================================
// ====== 

// ====================================================
// ====== Random generator for smearing momenta
// ====================================================

TRandom *rand1;


HpsEvent *ev;

TBranch *b_hps_event;
//b_hps_event->SetAddress(&ev);

SvtTrack *SVTtrack;
GblTrack *trk;
EcalCluster* cl;
EcalCluster* clTop;
EcalCluster* clBot;
EcalHit* ec_hit;
SvtHit *svt_hit;
HpsParticle* part;

HpsParticle *Topem;
HpsParticle *Botem;


void InitSettings(std::string);

void ResetEventFlags();

//========================================================
// ====== Resets some variables/flags that are initialized
// ====== for every candidate Moeller Vertex
//========================================================
void ResetConstrainedMollerFlags();

int DoesQualifyMoeller(HpsParticle*);

// ========= ============================================================= ============
// ========= This function checks whether the track has a hit in L1
// ========= ============================================================= ============
bool HasL1Hit(GblTrack*);

//========================================================
//===== Returns square root of the sum of elements
//========================================================
double GetMagnitude(vector<double>);


// =======================================================
// ===== Init smearing parameters
// =======================================================
void InitSmearPars();

#endif /* MOELLERSETTINGS_H */

