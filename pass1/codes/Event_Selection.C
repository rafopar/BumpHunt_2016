#define Event_Selection_cxx
#include "Event_Selection.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include "setting_2016_pass1.h"

//using namespace std;

void Init_Functions();

void Event_Selection::Loop()
{
  //   In a ROOT session, you can do:
  //      root> .L Event_Selection.C
  //      root> Event_Selection t
  //      root> t.GetEntry(12); // Fill t data members with entry number 12
  //      root> t.Show();       // Show values of entry 12
  //      root> t.Show(16);     // Read and show values of entry 16
  //      root> t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Init_Functions();

  TFile *file_out = new TFile("Event_Selection.root", "Recreate");

  TH1D *h_tarM1 = new TH1D("h_tarM1", "", 200, 0., 0.19);
  TH1D *h_tarM2 = new TH1D("h_tarM2", "", 200, 0., 0.19);
  TH1D *h_tarM3 = new TH1D("h_tarM3", "", 200, 0., 0.19);
  TH1D *h_tarM4 = new TH1D("h_tarM4", "", 200, 0., 0.19);
  TH1D *h_tarM5 = new TH1D("h_tarM5", "", 200, 0., 0.19);
  TH1D *h_tarM6 = new TH1D("h_tarM6", "", 200, 0., 0.19);

  TH1D *h_tarP1 = new TH1D("h_tarP1", "", 200, 0.5, 1.3*Eb);

  TH1D *h_P_ele_final = new TH1D("h_P_ele_final", "", 200, 0., 1.2*Eb);
  TH1D *h_P_pos_final = new TH1D("h_P_pos_final", "", 200, 0., 1.2*Eb);
  TH1D *h_phi0_ele_final = new TH1D("h_phi0_ele_final", "", 50, -6., 8.6);
  TH1D *h_phi0_pos_final = new TH1D("h_phi0_pos_final", "", 50, -6., 8.6);
  TH1D *h_tanLambda_ele_final = new TH1D("h_tanLambda_ele_final",  "", 50, -4.6, 4.6);
  TH1D *h_tanLambda_pos_final = new TH1D("h_tanLambda_pos_final",  "", 50, -4.6, 4.6);
  
  TH1D *h_n_ver_cands_in_ev1 = new TH1D("h_n_ver_cands_in_ev1", "",  10, -0.5, 9.5);

  TH1D *h_d0_pos1 = new TH1D("h_d0_pos1", "", 100, -5., 5.);
  TH1D *h_d0_pos2 = new TH1D("h_d0_pos2", "", 100, -5., 5.);
  TH1D *h_d0_pos3 = new TH1D("h_d0_pos3", "", 100, -5., 5.);
  
  TH1D *h_Nsigma_ele_top1 = new TH1D("h_Nsigma_ele_top1", "", 200, 0., 31.);
  TH1D *h_Nsigma_ele_bot1 = new TH1D("h_Nsigma_ele_bot1", "", 200, 0., 31.);
  TH1D *h_Nsigma_pos_top1 = new TH1D("h_Nsigma_pos_top1", "", 200, 0., 31.);
  TH1D *h_Nsigma_pos_bot1 = new TH1D("h_Nsigma_pos_bot1", "", 200, 0., 31.);

  TH1D *h_P_ele_top1 = new TH1D("h_P_ele_top1", "", 200, 0., 1.2*Eb);
  TH1D *h_P_ele_bot1 = new TH1D("h_P_ele_bot1", "", 200, 0., 1.2*Eb);

  TH1D *h_chi2NDF_ele_6hits_top1 = new TH1D("h_chi2NDF_ele_6hits_top1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_ele_6hits_bot1 = new TH1D("h_chi2NDF_ele_6hits_bot1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_ele_5hits_top1 = new TH1D("h_chi2NDF_ele_5hits_top1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_ele_5hits_bot1 = new TH1D("h_chi2NDF_ele_5hits_bot1", "", 200, 0., 20.);

  TH1D *h_chi2NDF_pos_6hits_top1 = new TH1D("h_chi2NDF_pos_6hits_top1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_pos_6hits_bot1 = new TH1D("h_chi2NDF_pos_6hits_bot1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_pos_5hits_top1 = new TH1D("h_chi2NDF_pos_5hits_top1", "", 200, 0., 20.);
  TH1D *h_chi2NDF_pos_5hits_bot1 = new TH1D("h_chi2NDF_pos_5hits_bot1", "", 200, 0., 20.);

  TH1D *h_trk_clust_dt_ele_top1 = new TH1D("h_trk_clust_dt_ele_top1", "", 200, -9., 9.);
  TH1D *h_trk_clust_dt_ele_bot1 = new TH1D("h_trk_clust_dt_ele_bot1", "", 200, -9., 9.);

  TH1D *h_trk_clust_dt_pos_top1 = new TH1D("h_trk_clust_dt_pos_top1", "", 200, -9., 9.);
  TH1D *h_trk_clust_dt_pos_bot1 = new TH1D("h_trk_clust_dt_pos_bot1", "", 200, -9., 9.);

  TH2D *h_trk_clust_dt_P_ele_top1 = new TH2D("h_trk_clust_dt_P_ele_top1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_ele_bot1 = new TH2D("h_trk_clust_dt_P_ele_bot1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_pos_top1 = new TH2D("h_trk_clust_dt_P_pos_top1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_pos_bot1 = new TH2D("h_trk_clust_dt_P_pos_bot1", "", 200, 0., 1.2*Eb, 200, -9., 9.);

  TH1D *h_cl_dt1 = new TH1D("h_cl_dt1", "", 200, -7., 7.);
  TH2D *h_cl_dt_Esum1 = new TH2D("h_cl_dt_Esum1", "", 200, 0., 1.2*Eb, 200, -7., 7.);


  //   ======== Histograms after tight cuts on other variables =======
  TH1D *h_Nsigma_ele_top_Tight1 = new TH1D("h_Nsigma_ele_top_Tight1", "", 200, 0., 31.);
  TH1D *h_Nsigma_ele_bot_Tight1 = new TH1D("h_Nsigma_ele_bot_Tight1", "", 200, 0., 31.);
  TH1D *h_Nsigma_pos_top_Tight1 = new TH1D("h_Nsigma_pos_top_Tight1", "", 200, 0., 31.);
  TH1D *h_Nsigma_pos_bot_Tight1 = new TH1D("h_Nsigma_pos_bot_Tight1", "", 200, 0., 31.);

  TH1D *h_chi2NDF_ele_6hits_top_Tight1 = new TH1D("h_chi2NDF_ele_6hits_top_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_ele_6hits_bot_Tight1 = new TH1D("h_chi2NDF_ele_6hits_bot_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_ele_5hits_top_Tight1 = new TH1D("h_chi2NDF_ele_5hits_top_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_ele_5hits_bot_Tight1 = new TH1D("h_chi2NDF_ele_5hits_bot_Tight1", "", 200, 0., 35.);
  
  TH1D *h_chi2NDF_pos_6hits_top_Tight1 = new TH1D("h_chi2NDF_pos_6hits_top_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_pos_6hits_bot_Tight1 = new TH1D("h_chi2NDF_pos_6hits_bot_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_pos_5hits_top_Tight1 = new TH1D("h_chi2NDF_pos_5hits_top_Tight1", "", 200, 0., 35.);
  TH1D *h_chi2NDF_pos_5hits_bot_Tight1 = new TH1D("h_chi2NDF_pos_5hits_bot_Tight1", "", 200, 0., 35.);

  TH1D *h_trk_clust_dt_ele_top_Tight1 = new TH1D("h_trk_clust_dt_ele_top_Tight1", "", 200, -9., 9.);
  TH1D *h_trk_clust_dt_ele_bot_Tight1 = new TH1D("h_trk_clust_dt_ele_bot_Tight1", "", 200, -9., 9.);

  TH1D *h_trk_clust_dt_pos_top_Tight1 = new TH1D("h_trk_clust_dt_pos_top_Tight1", "", 200, -9., 9.);
  TH1D *h_trk_clust_dt_pos_bot_Tight1 = new TH1D("h_trk_clust_dt_pos_bot_Tight1", "", 200, -9., 9.);

  TH2D *h_trk_clust_dt_P_ele_top_Tight1 = new TH2D("h_trk_clust_dt_P_ele_top_Tight1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_ele_bot_Tight1 = new TH2D("h_trk_clust_dt_P_ele_bot_Tight1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_pos_top_Tight1 = new TH2D("h_trk_clust_dt_P_pos_top_Tight1", "", 200, 0., 1.2*Eb, 200, -9., 9.);
  TH2D *h_trk_clust_dt_P_pos_bot_Tight1 = new TH2D("h_trk_clust_dt_P_pos_bot_Tight1", "", 200, 0., 1.2*Eb, 200, -9., 9.);

  TH1D *h_cl_dt_Tight1 = new TH1D("h_cl_dt_Tight1", "", 200, -7., 7.);
  TH2D *h_cl_dt_Esum_Tight1 = new TH2D("h_cl_dt_Esum_Tight1", "", 200, 0., 1.2*Eb, 200, -7., 7.);

  int cur_run = 0;
  int cur_ev = 0;

  int n_ev_sel_cuts = 1;

  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;


    if( jentry == 0 ){
      cur_run = run;
      cur_ev = event;
    }

    bool is_tri = true;       // Check is this is MC trident simulation
    bool is_data = !is_tri;   // the data flag is opposite of MC flag

    std::string data_type = "Trid" ; // It can be Data, Trid, WAB
    //std::string data_type = "Data" ; // It can be Data, Trid, WAB
    
    bool is_new_ev; // This variable tells whether the event number has changed, i.e. whether it is new a new evet
    
    if( cur_run == run && cur_ev == event ){
      is_new_ev = false;
    }else {
      is_new_ev = true;
    }
    
    // We want to analyze pair1 events
    if( !isPair1 ) {continue;}

    // ===== Opposite half cut =====
    if( eleClY*posClY > 0. ){continue; }

    // ===== Clusters should be in time clusters =====
    if( !(eleClT > cl_t_min && eleClT < cl_t_max) ) {continue;}
    if( !(posClT > cl_t_min && posClT < cl_t_max) ) {continue;}


    // ===== Cuts that are developed witm MC studies, will be applied now

    
    //if( !posHasL1 ){continue;}

    h_d0_pos1->Fill(posTrkD0);
    
    //if( !(posTrkD0 < pos_d0_cut) ) {continue;}

    h_tarM1->Fill(tarM);
    
    // ============ Some definitions, for the sake of not repeating a long expresion several times in the code ========
    double CL_trk_time_Offset; // The time offset between cluster time and track time, this is differet between data and MC
    if( is_tri ){
      CL_trk_time_Offset = CL_trk_time_Offset_tri;
    } else{
      CL_trk_time_Offset = CL_trk_time_Offset_Data;
    }
    
    double ele_trk_clus_dt = eleClT - eleTrkT - CL_trk_time_Offset;
    double pos_trk_clus_dt = posClT - posTrkT - CL_trk_time_Offset;
    double ele_pos_clust_dt = eleClT - posClT;
      
    // ============ Determining tight cuts for track cluster time difference =================
    double ele_trk_cl_dt_tigh_min;
    double ele_trk_cl_dt_tigh_max;

    double ele_trk_cl_dt_min;
    double ele_trk_cl_dt_max;
    
    if( eleClY > 0 ){
      ele_trk_cl_dt_tigh_min = mean_trk_clust_dt_ele_top - 0.8*sigm_trk_clust_dt_ele_top;
      ele_trk_cl_dt_tigh_max = mean_trk_clust_dt_ele_top + 0.8*sigm_trk_clust_dt_ele_top;

      double P_tmp = TMath::Min(eleP, P_max_trk_cl_dt);
      P_tmp = TMath::Max(P_tmp, P_min_trk_cl_dt);
      ele_trk_cl_dt_max = f_mean_cl_trk_dt_ele_top[data_type]->Eval(P_tmp) + 3.*f_sigm_cl_trk_dt_ele_top[data_type]->Eval(P_tmp);
      ele_trk_cl_dt_min = f_mean_cl_trk_dt_ele_top[data_type]->Eval(P_tmp) - 3.*f_sigm_cl_trk_dt_ele_top[data_type]->Eval(P_tmp);
     
    }else {
      ele_trk_cl_dt_tigh_min = mean_trk_clust_dt_ele_top - 0.8*sigm_trk_clust_dt_ele_top;
      ele_trk_cl_dt_tigh_max = mean_trk_clust_dt_ele_top + 0.8*sigm_trk_clust_dt_ele_top;

      double P_tmp = TMath::Min(eleP, P_max_trk_cl_dt);
      P_tmp = TMath::Max(P_tmp, P_min_trk_cl_dt);
      ele_trk_cl_dt_max = f_mean_cl_trk_dt_ele_bot[data_type]->Eval(P_tmp) + 3.*f_sigm_cl_trk_dt_ele_bot[data_type]->Eval(P_tmp);
      ele_trk_cl_dt_min = f_mean_cl_trk_dt_ele_bot[data_type]->Eval(P_tmp) - 3.*f_sigm_cl_trk_dt_ele_bot[data_type]->Eval(P_tmp);
    }


    double pos_trk_cl_dt_tigh_min;
    double pos_trk_cl_dt_tigh_max;

    double pos_trk_cl_dt_min;
    double pos_trk_cl_dt_max;
    if( posClY > 0 ){
      pos_trk_cl_dt_tigh_min = mean_trk_clust_dt_pos_top - 0.8*sigm_trk_clust_dt_pos_top;
      pos_trk_cl_dt_tigh_max = mean_trk_clust_dt_pos_top + 0.8*sigm_trk_clust_dt_pos_top;

      double P_tmp = TMath::Min(posP, P_max_trk_cl_dt);
      P_tmp = TMath::Max(P_tmp, P_min_trk_cl_dt);
      pos_trk_cl_dt_max = f_mean_cl_trk_dt_pos_top[data_type]->Eval(P_tmp) + 3.*f_sigm_cl_trk_dt_pos_top[data_type]->Eval(P_tmp);
      pos_trk_cl_dt_min = f_mean_cl_trk_dt_pos_top[data_type]->Eval(P_tmp) - 3.*f_sigm_cl_trk_dt_pos_top[data_type]->Eval(P_tmp);
      
    }else {
      pos_trk_cl_dt_tigh_min = mean_trk_clust_dt_pos_bot - 0.8*sigm_trk_clust_dt_pos_bot;
      pos_trk_cl_dt_tigh_max = mean_trk_clust_dt_pos_bot + 0.8*sigm_trk_clust_dt_pos_bot;

      double P_tmp = TMath::Min(posP, P_max_trk_cl_dt);
      P_tmp = TMath::Max(P_tmp, P_min_trk_cl_dt);
      pos_trk_cl_dt_max = f_mean_cl_trk_dt_pos_bot[data_type]->Eval(P_tmp) + 3.*f_sigm_cl_trk_dt_pos_bot[data_type]->Eval(P_tmp);
      pos_trk_cl_dt_min = f_mean_cl_trk_dt_pos_bot[data_type]->Eval(P_tmp) - 3.*f_sigm_cl_trk_dt_pos_bot[data_type]->Eval(P_tmp);
    }

      
    bool nsigma_tighcuts = eleP > 0.4 && eleP < 1.76 && tarP < 2.9 && eleTrkChisq/(2.*eleTrkHits - 5.) < 2.5 && posTrkChisq/(2.*posTrkHits - 5.) < 2.5 && ele_trk_clus_dt > ele_trk_cl_dt_tigh_min && ele_trk_clus_dt < ele_trk_cl_dt_tigh_max && pos_trk_clus_dt > pos_trk_cl_dt_tigh_min && pos_trk_clus_dt < pos_trk_cl_dt_tigh_max && ele_pos_clust_dt > cl_dt_min && ele_pos_clust_dt < cl_dt_max;
      

    bool trk_fit_tightcuts = eleP > 0.4 && eleP < 1.76 && tarP < 2.9 && ele_trk_clus_dt > ele_trk_cl_dt_tigh_min && ele_trk_clus_dt < ele_trk_cl_dt_tigh_max && pos_trk_clus_dt > pos_trk_cl_dt_tigh_min && pos_trk_clus_dt < pos_trk_cl_dt_tigh_max && ele_pos_clust_dt > cl_dt_min && ele_pos_clust_dt < cl_dt_max && eleMatchChisq < nsigma_tightcut && posMatchChisq < nsigma_tightcut;
    

    bool trk_clust_dt_tight = eleP > 0.4 && eleP < 1.76 && tarP < 2.9 && eleTrkChisq/(2.*eleTrkHits - 5.) < 2.5 && posTrkChisq/(2.*posTrkHits - 5.) < 2.5 && ele_pos_clust_dt > cl_dt_min && ele_pos_clust_dt < cl_dt_max && eleMatchChisq < nsigma_tightcut && posMatchChisq < nsigma_tightcut;


    bool clust_dt_tightcut = eleP > 0.4 && eleP < 1.76 && tarP < 2.9 && eleTrkChisq/(2.*eleTrkHits - 5.) < 2.5 && posTrkChisq/(2.*posTrkHits - 5.) < 2.5 && eleMatchChisq < nsigma_tightcut && posMatchChisq < nsigma_tightcut && ele_trk_clus_dt > ele_trk_cl_dt_tigh_min && ele_trk_clus_dt < ele_trk_cl_dt_tigh_max && pos_trk_clus_dt > pos_trk_cl_dt_tigh_min && pos_trk_clus_dt < pos_trk_cl_dt_tigh_max;


    bool ev_selection_cuts = eleTrkChisq/(2.*eleTrkHits - 5.) < 6. && posTrkChisq/(2.*posTrkHits - 5.) < 6. && eleMatchChisq < 5. && posMatchChisq < 5. && ele_pos_clust_dt > -1. && ele_pos_clust_dt < 1. && 	ele_trk_clus_dt > ele_trk_cl_dt_min && ele_trk_clus_dt < ele_trk_cl_dt_max && pos_trk_clus_dt > pos_trk_cl_dt_min && pos_trk_clus_dt < pos_trk_cl_dt_max;
																									
    
    
    if( eleClY > 0 ){
      h_Nsigma_ele_top1->Fill(eleMatchChisq);
      h_Nsigma_pos_bot1->Fill(posMatchChisq);

      if( nsigma_tighcuts){
	h_Nsigma_ele_top_Tight1->Fill(eleMatchChisq);
	h_Nsigma_pos_bot_Tight1->Fill(posMatchChisq);
      }

      

      h_P_ele_top1->Fill(eleP);

      if( eleTrkHits == 6 ){
	h_chi2NDF_ele_6hits_top1->Fill(eleTrkChisq/7.);
      } else {
	h_chi2NDF_ele_5hits_top1->Fill(eleTrkChisq/5.);
      }

      if( posTrkHits == 6 ){
	h_chi2NDF_pos_6hits_bot1->Fill(posTrkChisq/7.);
      } else {
	h_chi2NDF_pos_5hits_bot1->Fill(posTrkChisq/5.);
      }

      if( trk_fit_tightcuts ){
	if( eleTrkHits == 6 ){
	  h_chi2NDF_ele_6hits_top_Tight1->Fill(eleTrkChisq/7.);
	} else {
	  h_chi2NDF_ele_5hits_top_Tight1->Fill(eleTrkChisq/5.);
	}

	if( posTrkHits == 6 ){
	  h_chi2NDF_pos_6hits_bot_Tight1->Fill(posTrkChisq/7.);
	} else {
	  h_chi2NDF_pos_5hits_bot_Tight1->Fill(posTrkChisq/5.);
	}

      }


      h_trk_clust_dt_ele_top1->Fill(ele_trk_clus_dt);
      h_trk_clust_dt_pos_bot1->Fill(pos_trk_clus_dt);
      
      h_trk_clust_dt_P_ele_top1->Fill(eleP, ele_trk_clus_dt);
      h_trk_clust_dt_P_pos_bot1->Fill(posP, ele_trk_clus_dt);

      if( trk_clust_dt_tight ){
	h_trk_clust_dt_ele_top_Tight1->Fill(ele_trk_clus_dt);
	h_trk_clust_dt_pos_bot_Tight1->Fill(pos_trk_clus_dt);
      
	h_trk_clust_dt_P_ele_top_Tight1->Fill(eleP, ele_trk_clus_dt);
	h_trk_clust_dt_P_pos_bot_Tight1->Fill(posP, ele_trk_clus_dt);
      }
	
	
    } else {
      h_Nsigma_ele_bot1->Fill(eleMatchChisq);
      h_Nsigma_pos_top1->Fill(posMatchChisq);

      if( nsigma_tighcuts){
	h_Nsigma_ele_bot_Tight1->Fill(eleMatchChisq);
	h_Nsigma_pos_top_Tight1->Fill(posMatchChisq);
      }

      h_P_ele_bot1->Fill(eleP);

      if( eleTrkHits == 6 ){
	h_chi2NDF_ele_6hits_bot1->Fill(eleTrkChisq/7.);
      } else {
	h_chi2NDF_ele_5hits_bot1->Fill(eleTrkChisq/5.);
      }

      if( posTrkHits == 6 ){
	h_chi2NDF_pos_6hits_top1->Fill(posTrkChisq/7.);
      } else {
	h_chi2NDF_pos_5hits_top1->Fill(posTrkChisq/5.);
      }

      if( trk_fit_tightcuts ){
	if( eleTrkHits == 6 ){
	  h_chi2NDF_ele_6hits_bot_Tight1->Fill(eleTrkChisq/7.);
	} else {
	  h_chi2NDF_ele_5hits_bot_Tight1->Fill(eleTrkChisq/5.);
	}

	if( posTrkHits == 6 ){
	  h_chi2NDF_pos_6hits_top_Tight1->Fill(posTrkChisq/7.);
	} else {
	  h_chi2NDF_pos_5hits_top_Tight1->Fill(posTrkChisq/5.);
	}

      }

      h_trk_clust_dt_ele_bot1->Fill(ele_trk_clus_dt);
      h_trk_clust_dt_pos_top1->Fill(pos_trk_clus_dt);

      h_trk_clust_dt_P_ele_bot1->Fill(eleP, ele_trk_clus_dt);
      h_trk_clust_dt_P_pos_top1->Fill(posP, pos_trk_clus_dt);

      if( trk_clust_dt_tight ){
	h_trk_clust_dt_ele_bot_Tight1->Fill(ele_trk_clus_dt);
	h_trk_clust_dt_pos_top_Tight1->Fill(pos_trk_clus_dt);

	h_trk_clust_dt_P_ele_bot_Tight1->Fill(eleP, ele_trk_clus_dt);
	h_trk_clust_dt_P_pos_top_Tight1->Fill(posP, pos_trk_clus_dt);
      }
    }

    h_cl_dt1->Fill(ele_pos_clust_dt);
    h_cl_dt_Esum1->Fill(eleClE + posClE, ele_pos_clust_dt);

    if( clust_dt_tightcut ){
      h_cl_dt_Tight1->Fill(ele_pos_clust_dt);
      h_cl_dt_Esum_Tight1->Fill(eleClE + posClE, ele_pos_clust_dt); 
    }


    if( nsigma_tighcuts ){
      h_tarM2->Fill(tarM);
    }

    if( trk_fit_tightcuts ){
      h_tarM3->Fill(tarM);
    }

    if( trk_clust_dt_tight ){
      h_tarM4->Fill(tarM);
    }

    if( clust_dt_tightcut ){
      h_tarM5->Fill(tarM);
    }

      
    
    if( ev_selection_cuts ){

      h_d0_pos2->Fill(posTrkD0);

      if( !posHasL1 ){continue;}

      h_d0_pos3->Fill(posTrkD0);      
      if( !(posTrkD0 < pos_d0_cut) ) {continue;}
      
      h_tarM6->Fill(tarM);
      h_tarP1->Fill(tarP);

      h_P_pos_final->Fill(posP);
      h_P_ele_final->Fill(eleP);

      h_phi0_ele_final->Fill(eleTrkPhi*radian);
      h_phi0_pos_final->Fill(posTrkPhi*radian);

      h_tanLambda_ele_final->Fill(atan(eleTrkLambda)*radian);
      h_tanLambda_pos_final->Fill(atan(posTrkLambda)*radian);
      
      if( is_new_ev ){
	h_n_ver_cands_in_ev1->Fill(n_ev_sel_cuts);
	
	n_ev_sel_cuts = 1;
      }
      else{
	n_ev_sel_cuts = n_ev_sel_cuts + 1;
      }
      
    }
    //eleP
  }

  gDirectory->Write();
   
}

void Init_Functions(){
  f_mean_cl_trk_dt_ele_top["Data"] = new TF1("f_mean_cl_trk_dt_ele_top", "-0.463849 + x*(1.01109) + x*x*(0.0489378) + x*x*x*(-0.258737)", 0., 2.5);
  f_sigm_cl_trk_dt_ele_top["Data"] = new TF1("f_mean_cl_trk_dt_ele_top", "1.83648 + x*(-3.26601) + x*x*(6.07709) + x*x*x*(-4.88008) + x*x*x*x*(1.38874)", 0., 2.5);

  f_mean_cl_trk_dt_ele_bot["Data"] = new TF1("f_mean_cl_trk_dt_ele_bot", "-0.812765 + x*(0.878871) + x*x*(-0.319924) + x*x*x*(0.00307882)", 0., 2.5);
  f_sigm_cl_trk_dt_ele_bot["Data"] = new TF1("f_mean_cl_trk_dt_ele_bot", "1.34173 + x*(-0.704732) + x*x*(1.5466) + x*x*x*(-1.48625) + x*x*x*x*(0.486362)", 0., 2.5);

  f_mean_cl_trk_dt_pos_top["Data"] = new TF1("f_mean_cl_trk_dt_pos_top", "-0.860302 + x*(2.1808) + x*x*(-1.62851) + x*x*x*(0.388061)", 0., 2.5);
  f_sigm_cl_trk_dt_pos_top["Data"] = new TF1("f_mean_cl_trk_dt_pos_top", "2.79063 + x*(-7.3126) + x*x*(12.1243) + x*x*x*(-8.67505) + x*x*x*x*(2.23873)", 0., 2.5);

  f_mean_cl_trk_dt_pos_bot["Data"] = new TF1("f_mean_cl_trk_dt_pos_bot", "-1.00867 + x*(2.89172) + x*x*(-2.12403) + x*x*x*(0.529724)", 0., 2.5);
  f_sigm_cl_trk_dt_pos_bot["Data"] = new TF1("f_mean_cl_trk_dt_pos_bot", "0.067446 + x*(4.39018) + x*x*(-6.26695) + x*x*x*(3.86652) + x*x*x*x*(-0.881143)", 0., 2.5);



  f_mean_cl_trk_dt_ele_top["Trid"] = new TF1("f_mean_cl_trk_dt_ele_top", "0.0952942 + x*(-0.370083) + x*x*(0.587404) + x*x*x*(-0.258055)", 0., 2.5);
  f_sigm_cl_trk_dt_ele_top["Trid"] = new TF1("f_mean_cl_trk_dt_ele_top", "0.823454 + x*(-0.872126) + x*x*(0.839176) + x*x*x*(-0.360848) + x*x*x*x*(0.0506542)", 0., 2.5);

  f_mean_cl_trk_dt_ele_bot["Trid"] = new TF1("f_mean_cl_trk_dt_ele_bot", "0.199217 + x*(-0.704344) + x*x*(0.862869) + x*x*x*(-0.307677)", 0., 2.5);
  f_sigm_cl_trk_dt_ele_bot["Trid"] = new TF1("f_mean_cl_trk_dt_ele_bot", "0.74823 + x*(-0.897505) + x*x*(1.49219) + x*x*x*(-1.24496) + x*x*x*x*(0.380204)", 0., 2.5);

  f_mean_cl_trk_dt_pos_top["Trid"] = new TF1("f_mean_cl_trk_dt_pos_top", "0.32424 + x*(-0.949226) + x*x*(0.967374) + x*x*x*(-0.300816)", 0., 2.5);
  f_sigm_cl_trk_dt_pos_top["Trid"] = new TF1("f_mean_cl_trk_dt_pos_top", "0.057203 + x*(2.7954) + x*x*(-5.3646) + x*x*x*(4.05821) + x*x*x*x*(-1.06963)", 0., 2.5);

  f_mean_cl_trk_dt_pos_bot["Trid"] = new TF1("f_mean_cl_trk_dt_pos_bot", "0.0240929 + x*(-0.20681) + x*x*(0.453843) + x*x*x*(-0.210165)", 0., 2.5);
  f_sigm_cl_trk_dt_pos_bot["Trid"] = new TF1("f_mean_cl_trk_dt_pos_bot", "0.678652 + x*(-0.404917) + x*x*(0.279734) + x*x*x*(-0.0643174) + x*x*x*x*(0.00259185)", 0., 2.5);


}
