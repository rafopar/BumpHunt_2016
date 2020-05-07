

void ReportApStats(){

  ofstream out("Ap_Stats.dat");

  const int n_masses = 29;
  
  int masses[n_masses] = {30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 155, 160, 165, 170, 175};

  for( int i = 0; i < n_masses; i++ ){

    cout<<masses[i]<<endl;
    TFile *cur_file = new TFile(Form("EventSelection_Ap_%d_MeV.root", masses[i]), "Read");

    TH1D *h_Minv_General_Final_1 = (TH1D*)cur_file->Get("h_Minv_General_Final_1");

    int entries =h_Minv_General_Final_1 ->GetEntries();

    out<<setw(5)<<masses[i]<<setw(10)<<entries<<endl;
    
  }

}
