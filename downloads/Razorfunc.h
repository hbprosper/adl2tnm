// Razor recipe taken from the RazorBoost gurus: N. Strobbe, S. Sekmen
// also info here:
//   https://twiki.cern.ch/twiki/bin/view/CMSPublic/RazorLikelihoodHowTo
#include "TLorentzVector.h"

namespace Razor {

  // deltaPhi:
  double dPhi(double phi1, double phi2) {
    double deltaphi = fabs(phi2 - phi1);
    if ( deltaphi > M_PI ) deltaphi = 2 * M_PI - deltaphi;
      return deltaphi;
    }
  double dPhi(TLorentzVector& p1, TLorentzVector& p2) {
    return fabs(p1.DeltaPhi(p2));
  }

  // deltaR:
  double dR(double eta1, double phi1, double eta2, double phi2) {
    double deltaeta = eta1 - eta2;
    double deltaphi = dPhi(phi1, phi2);
    return sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  }
  double dR(TLorentzVector& p1, TLorentzVector& p2) {
    return p1.DeltaR(p2);
  }

  // Hemispheres:
  std::vector<TLorentzVector> fmegajets(std::vector<TLorentzVector>& myjets) {
    std::vector<TLorentzVector> mynewjets;
    TLorentzVector j1, j2;
    //bool foundGood = false;
    int N_comb = 1;
    for(unsigned int i = 0; i < myjets.size(); i++){
      N_comb *= 2;
    }
    double M_min = 9999999999.0;
    int j_count;
    for(int i = 1; i < N_comb-1; i++){
      TLorentzVector j_temp1, j_temp2;
      int itemp = i;
      j_count = N_comb/2;
      int count = 0;
      while(j_count > 0){
        if(itemp/j_count == 1){
          j_temp1 += myjets[count];
        } else {
          j_temp2 += myjets[count];
        }
        itemp -= j_count*(itemp/j_count);
        j_count /= 2;
        count++;
      }
      double M_temp = j_temp1.M2()+j_temp2.M2();
      // smallest mass
      if(M_temp < M_min){
        M_min = M_temp;
        j1 = j_temp1;
        j2 = j_temp2;
      }
    }
    if(j2.Pt() > j1.Pt()){
      TLorentzVector temp = j1;
      j1 = j2;
      j2 = temp;
    }
    mynewjets.push_back(j1);
    mynewjets.push_back(j2);
    return mynewjets;
  }
  
  // MR
  double fMR(std::vector<TLorentzVector>& j){
    TLorentzVector ja = j[0];
    TLorentzVector jb = j[1];
    double A = ja.P();
    double B = jb.P();
    double az = ja.Pz();
    double bz = jb.Pz();
    TVector3 jaT, jbT;
    jaT.SetXYZ(ja.Px(),ja.Py(),0.0);
    jbT.SetXYZ(jb.Px(),jb.Py(),0.0);
    double ATBT = (jaT+jbT).Mag2();
    double temp = sqrt((A+B)*(A+B)-(az+bz)*(az+bz)-
      		 (jbT.Dot(jbT)-jaT.Dot(jaT))*(jbT.Dot(jbT)-jaT.Dot(jaT))/(jaT+jbT).Mag2());
    double mybeta = (jbT.Dot(jbT)-jaT.Dot(jaT))/sqrt(ATBT*((A+B)*(A+B)-(az+bz)*(az+bz)));
    double mygamma = 1./sqrt(1.-mybeta*mybeta);
    //gamma times MRstar
    temp *= mygamma;
    return temp;
  }
  
  // MTR
  double fMTR(std::vector<TLorentzVector>& j, TLorentzVector& met_){
    TLorentzVector ja = j[0];
    TLorentzVector jb = j[1];
    TVector3       met= met_.Vect();
    double temp = met.Mag()*(ja.Pt()+jb.Pt()) - met.Dot(ja.Vect()+jb.Vect());
    temp /= 2.;
    temp = sqrt(temp);
    return temp;
  }
  
  // MT
  double fMT(TLorentzVector& lepton, TLorentzVector& pfmet){
    return sqrt( 2 * lepton.Pt() * pfmet.Pt() * ( 1 - cos( pfmet.Phi() - lepton.Phi() ) ) );
  }

  // Mll
  double fMll(TLorentzVector& lep1, TLorentzVector& lep2){
    TLorentzVector Z = lep1 + lep2;
    return fabs(Z.M() - 91.187);
  }
  
}
