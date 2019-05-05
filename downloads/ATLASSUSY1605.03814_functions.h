#ifndef ATLASSUSY1605_03814_functions_H
#define ATLASSUSY1605_03814_functions_H
#include <vector>
#include <iostream>
#include <cmath>
#include "TLorentzVector.h"

namespace atlas
{
  double Meff(std::vector<TLorentzVector>& jets, TLorentzVector& MET) {
    double meff = MET.Pt();
    for (size_t i=0; i<jets.size(); i++) {
      meff += jets[i].Pt();
    }
    return meff;
  }
  
  double dphijNjle3METmin(std::vector<TLorentzVector>& jets, TLorentzVector& MET) {
    if (jets.size() < 2)
      return 0;
    int njets = jets.size();
    if ( njets > 3 ) njets = 3;
    double dphimin = 999;
    for (int i=0; i<njets; i++) {
      double dphi = fabs(MET.DeltaPhi(jets[i]));
      if (dphi < dphimin) dphimin = dphi;
    }
    return dphimin;
  }

  double dphijNjgt3METmin(std::vector<TLorentzVector>& jets, TLorentzVector& MET) {
    double dphimin = 999;
    if (jets.size() <= (size_t)3) 
      return 0;
    for (size_t i=0; i<jets.size(); i++) {
      double dphi = fabs(MET.DeltaPhi(jets[i]));
      if (dphi < dphimin) dphimin = dphi;
    }
    return dphimin;
  }
  
  double METovermeffNJ(std::vector<TLorentzVector>& jets,
		       int njets, TLorentzVector& MET) {
    if (jets.size() < (size_t)njets) {
      //std::cout << "Not enough jets" << std::endl;
      return 0;
    }
    double meff = MET.Pt();
    for (int i=0; i<njets; i++) {
      meff += jets[i].Pt();
    }
    return MET.Pt() / meff;
  }

  double METoversqrtHT(std::vector<TLorentzVector>& jets, TLorentzVector& MET) {
    double HT = 0;
    for (size_t i=0; i<jets.size(); i++) {
      HT += jets[i].Pt();
    }
    return MET.Pt() / sqrt(HT);
  }

  double aplanarity(std::vector<TLorentzVector>& jets) {
    // to be filled in
    return 0;
  }
  
  inline
    double dPhi(double phi1, double phi2)
  {
    double deltaphi = fabs(phi2 - phi1);
    if ( deltaphi > M_PI ) deltaphi = 2 * M_PI - deltaphi;
    return deltaphi;
  }

  double dR(double eta1, double phi1, double eta2, double phi2)
  {
    double deltaeta = eta1 - eta2;
    double deltaphi = dPhi(phi1, phi2);
    return sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  }

  inline
    double dR(TLorentzVector& p1, TLorentzVector& p2)
  {
    return p1.DeltaR(p2);
  }

 inline
    double dPhi(TLorentzVector& p1, TLorentzVector& p2)
  {
    return p1.DeltaPhi(p2);
  }  
};
#endif
