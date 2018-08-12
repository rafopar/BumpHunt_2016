#include <TChain.h>

void make_class()
{
  TChain *ch1 = new TChain("Event_Selection");
  ch1->Add("../Data/hps_007796_nt_tri_3.11.1.root/ntuple");
  ch1->MakeClass("Event_Selection");
}
