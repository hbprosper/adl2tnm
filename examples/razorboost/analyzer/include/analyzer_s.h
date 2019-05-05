#ifndef analyzer_s_HH
#define analyzer_s_HH
//------------------------------------------------------------------
// File:        analyzer_s.h
// Description: Analyzer for ADL-based analysis:
//
// ADL file: razorboost.adl
// info block
//	info        	analysis
//	experiment  	CMS
//	id          	SUS-16-050
//	publication 	Phys.Rev. D97 (2018) no.1, 012007
//	sqrtS       	13.0
//	lumi        	35.9
//	arXiv       	1710.11188
//	hepdata     	https://www.hepdata.net/record/ins1633588
//	doi         	10.1103/PhysRevD.97.012007
//
// Created:     Sun May  5 01:01:38 2019 by adl2tnm.py v2.0.0
//------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "TNMObject.h"
//------------------------------------------------------------------
struct TNMThing
{
  TNMThing() {}
  virtual ~TNMThing() {}
  virtual void reset() {}
  virtual bool create() { return true; }
  virtual void write(TFile* fout) {}
  virtual void summary(std::ostream& os) {}
};
    
struct analyzer_s
{
  std::vector<TNMThing*> defines;
  std::vector<TNMThing*> objects;
  std::vector<TNMThing*> regions;

  analyzer_s();
  ~analyzer_s();
  void run(std::vector<TNMObject>& Tau_,
           std::vector<TNMObject>& Jet_,
           std::vector<TNMObject>& Muon_,
           std::vector<TNMObject>& Photon_,
           TNMObject& MET_,
           std::vector<TNMObject>& Electron_,
           std::vector<TNMObject>& FatJet_);
  void summary(TFile* fout, std::ostream& os);
};

#endif
