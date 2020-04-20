#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>

#include <fstream>
#include <iostream>

using namespace std;

void DumpHistos(TH1D*, std::string);

void DumpHistos(){

  TFile *file_in = new TFile("EventSelection_Data.root", "Read");

  TH1D *h_Pep_Fid1 = (TH1D*)file_in->Get("h_Pep_Fid1");
  TH1D *h_DeepPep_Fid1 = (TH1D*)file_in->Get("h_DeepPep_Fid1");

  DumpHistos(h_Pep_Fid1, "PosMomInFid.dat");
  DumpHistos(h_DeepPep_Fid1, "PosMomInDeepFid.dat");
  
  const int n_MomRange = 3;
  TH1D *h_E_P_ep_Fid1_[n_MomRange];
  TH1D *h_E_P_ep_DeepFid1_[n_MomRange];

  for( int i = 0; i < n_MomRange; i++ ){
    h_E_P_ep_Fid1_[i] = (TH1D*)file_in->Get(Form("h_E_P_ep_Fid1_%d", i));
    DumpHistos(h_E_P_ep_Fid1_[i], Form("E_Over_P_MomRange_%d.dat", i));
    h_E_P_ep_DeepFid1_[i] = (TH1D*)file_in->Get(Form("h_E_P_ep_DeepFid1_%d", i));
    DumpHistos(h_E_P_ep_DeepFid1_[i], Form("E_Over_P_MomRange_DeepFid_%d.dat", i));
  }


  TFile *file_Tri = new TFile("EventSelection_Tri.root", "Read");

  TH1D *h_Pep_Fid1_Tri = (TH1D*)file_Tri->Get("h_Pep_Fid1");
  TH1D *h_DeepPep_Fid1_Tri = (TH1D*)file_Tri->Get("h_DeepPep_Fid1");

  DumpHistos(h_Pep_Fid1_Tri, "PosMomInFid_Tri.dat");
  DumpHistos(h_DeepPep_Fid1_Tri, "PosMomInDeepFid_Tri.dat");
  
  TH1D *h_E_P_ep_Fid1_Tri_[n_MomRange];
  TH1D *h_E_P_ep_DeepFid1_Tri_[n_MomRange];

  for( int i = 0; i < n_MomRange; i++ ){
    h_E_P_ep_Fid1_Tri_[i] = (TH1D*)file_Tri->Get(Form("h_E_P_ep_Fid1_%d", i));
    DumpHistos(h_E_P_ep_Fid1_Tri_[i], Form("E_Over_P_MomRange_Tri_%d.dat", i));
    h_E_P_ep_DeepFid1_Tri_[i] = (TH1D*)file_Tri->Get(Form("h_E_P_ep_DeepFid1_%d", i));
    DumpHistos(h_E_P_ep_DeepFid1_Tri_[i], Form("E_Over_P_MomRange_DeepFid_Tri_%d.dat", i));
  }

}

void DumpHistos(TH1D* h, std::string fname){

  ofstream out(fname.c_str());

  int n_bins = h->GetNbinsX();

  for( int i = 0; i < n_bins; i++ ){
    double x = h->GetBinCenter(i+1);
    double content = h->GetBinContent(i+1);
    out<<x<<setw(15)<<content<<endl;
  }

  out.close();

}
