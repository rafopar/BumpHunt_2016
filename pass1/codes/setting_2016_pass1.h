#ifndef __SETTING_2016_PASS__
#define __SETTING_2016_PASS__

#include <map>
#include <TF1.h>

using namespace std;

const double radian = 57.29578;
const double Eb = 2.306;
const double CL_trk_time_Offset_Data = 55.;
const double CL_trk_time_Offset_tri = 51.64;
const double cl_t_max = 63.;
const double cl_t_min = 50.;
const double pos_d0_cut = 1.1;
const double Psum_min = 1.51; // GeV

//======= Tight cuts on trk-clust time diff =====
// These are dependent on track charge and also, they depend
// whether the track/cluster is in bot/top

const double mean_trk_clust_dt_ele_top = 0.05777;
const double sigm_trk_clust_dt_ele_top = 1.23;

const double mean_trk_clust_dt_ele_bot = -0.4263;
const double sigm_trk_clust_dt_ele_bot = 1.33;

const double mean_trk_clust_dt_pos_top = -8.61485e-02;
const double sigm_trk_clust_dt_pos_top = 1.2802;

const double mean_trk_clust_dt_pos_bot = -0.578381;
const double sigm_trk_clust_dt_pos_bot = 1.28636e+00;


// ========= ================================ ============
// ========= Normalizatin factors from Sebouh ============
// ========= Normalizatin factors from Sebouh ============
// ========= ================================ ============

// (# of recon files)*(generated/readout)*(events per generated file)/(sigma in barns) = lumi in inverse barns
double wab_mc_lumi =  (9898*1*10000)/220.6e-3;
double tritrig_mc_lumi = (900*1*10000)/1.1416e-3;
double rad_mc_lumi =  (100*1*10000)/.0667e-3;

// (mass per area of target (g/cm^2))/(molar mass/Avagadro's number)*(10^-24 cm^2/barn)/(electron charge)
double lumi_per_C = 0.00782/(183.8/6.023E+23)*1e-24/1.602E-19;
double charge = 827975.643e-9/10;  // divide by 10 for blinding
double tri_data_lumi = charge*lumi_per_C;


// ===== Tight cuts on ele-pos cluster time difference =====
const double cl_dt_max_tight = 0.45; // ns
const double cl_dt_min_tight = -0.45; // ns

// ===== Tight cut on nsigma =====
// ===== Distributions look quite slimilar for ele/pos/bot/top
const double nsigma_tightcut = 3.;


// ===== Minimum electron momentum 'tight cut' =====
const double ele_min_mom = 0.4;  // GeV
const double ele_max_mom = 1.76; // GeV
const double tarP_Max = 2.9; // GeV
const double ele_chi2_tightcut = 2.5; 
const double pos_chi2_tightcut = 2.5; 


 

map<std::string, TF1*> f_mean_cl_trk_dt_ele_top;
map<std::string, TF1*> f_sigm_cl_trk_dt_ele_top;

map<std::string, TF1*> f_mean_cl_trk_dt_ele_bot;
map<std::string, TF1*> f_sigm_cl_trk_dt_ele_bot;

map<std::string, TF1*> f_mean_cl_trk_dt_pos_top;
map<std::string, TF1*> f_sigm_cl_trk_dt_pos_top;

map<std::string, TF1*> f_mean_cl_trk_dt_pos_bot;
map<std::string, TF1*> f_sigm_cl_trk_dt_pos_bot;

map<std::string, TF1*> f_mean_ele_pos_clust_dt;
map<std::string, TF1*> f_sigm_ele_pos_clust_dt;

// P_max/P_min for trk-cluster matching functions, i.e. if the momentum is higher than this, then mean and sigma functions will be evaluated at these values
const double P_max_trk_cl_dt = 1.6;
const double P_min_trk_cl_dt = 0.4;


const double clust_dt_Esum_max = 2.4;
const double clust_dt_Esum_min = 0.9;
double cl_dt_max;
double cl_dt_min;


map<std::string, int> cols;


#endif
