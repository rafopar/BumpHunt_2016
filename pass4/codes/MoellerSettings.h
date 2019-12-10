/* 
 * File:   MoellerSettings.h
 * Author: rafopar
 *
 * Created on October 31, 2019, 2:13 PM
 */


#ifndef MOELLERSETTINGS_H
#define MOELLERSETTINGS_H

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

const double pos_d0_cut = 1.1;
const double Psum_min = 1.51; // GeV

const double chi2NDFTighCut_Data = 2;
const double chi2NDFTighCut_MC = 2;
double chi2NDFTighCut;

const double Pem_MaxTight_Data = 1.9;
const double cl_dTCut_Tight_Data = 0.8;

bool isData;
bool isMC;


bool HasTopL1 = false;
bool HasBotL1 = false;

double Pem_MaxTight;
double cl_dTCut_Tight;


double topChi2, botChi2;

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
double GetMagnitude(vector<double> );

#endif /* MOELLERSETTINGS_H */

