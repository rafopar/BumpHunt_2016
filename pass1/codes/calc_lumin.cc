#include <iostream>

using namespace std;

double calc_lumin(double ); // charge in Nano Coulomsbs

int main(){
  const double nano = 1.e-9;
  //const double I = 200; // 200 nA
  const double qq = 87905; // 200 nA

  //cout<<"Lumin at 200 nA = "<<calc_lumin(I)<<"cm^{-2} s^{-1}"<<endl;
  cout<<"Lumin for charge" <<qq<<" = "<<calc_lumin( qq )<<" cm^{-2}"<<endl;

  return 0;
}


double calc_lumin(double q_tot) // charge in Nano Coulomsbs
{
  const double rho=19.6; // g/cm3
  const double A=183.84; // g/mole
  const double t=100*4.05e-6; // cm (thickness)
  const double qe=1.6e-19;// coulumbs
  const double Na=6.022e23;  // atoms/mole
  const double nanoto1 = 1.e-9;
  double N_e = q_tot*nanoto1/qe;
  double Lumin = N_e*rho*t*Na/A;

  cout<<"Lumin = "<<Lumin<<endl;
  return Lumin;
}
