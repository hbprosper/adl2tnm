//------------------------------------------------------------------
// File:        analyzer_s.cc
// Description: Analyzer for ADL-based analysis:
//
// ADL file: razorboost_adl2tnm.adl
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
// Created:     Sun May  5 21:48:25 2019 by adl2tnm.py v2.0.0
//------------------------------------------------------------------
#include <algorithm>
#include "analyzer_s.h"
#include "ATLASSUSY1605.03814_functions.h"
#include "ATLASEXOT1704.0384_functions.h"
#include "Razorfunc.h"

using namespace atlas;
using namespace Razor;

using namespace std;
//------------------------------------------------------------------
// The following functions, objects, and variables are globally visible
// within this programming unit.
//------------------------------------------------------------------
//
// functions
inline
double	_fMT(TLorentzVector& lepton, TLorentzVector& pfmet)
{
  return fMT(lepton, pfmet);
};

inline
double	_fMR(vector<TNMObject>& j)
{
  vector<TLorentzVector> j_(j.size());
  copy(j.begin(), j.end(), j_.begin());
  return fMR(j_);
};

inline
double	_fMTR(vector<TNMObject>& j, TLorentzVector& met_)
{
  vector<TLorentzVector> j_(j.size());
  copy(j.begin(), j.end(), j_.begin());
  return fMTR(j_, met_);
};

inline
std::vector<TNMObject>	_fmegajets(vector<TNMObject>& myjets)
{
  vector<TLorentzVector> myjets_(myjets.size());
  copy(myjets.begin(), myjets.end(), myjets_.begin());

  vector<TLorentzVector> t = fmegajets(myjets_);
  vector<TNMObject> o(t.size());
  copy(t.begin(), t.end(), o.begin());
  return o;
};

inline
double	_dPhi(double phi1, double phi2)
{
  return dPhi(phi1, phi2);
};

inline
double	_dPhi(TLorentzVector& p1, TLorentzVector& p2)
{
  return dPhi(p1, p2);
};

inline
double	_fMll(TLorentzVector& lep1, TLorentzVector& lep2)
{
  return fMll(lep1, lep2);
};

inline
double	_dR(double eta1, double phi1, double eta2, double phi2)
{
  return dR(eta1, phi1, eta2, phi2);
};

inline
double	_dR(TLorentzVector& p1, TLorentzVector& p2)
{
  return dR(p1, p2);
};


//------------------------------------------------------------------
// proxies for external objects
vector<TNMObject> Muon;
vector<TNMObject> Jet;
vector<TNMObject> Tau;
vector<TNMObject> Photon;

TNMObject MET;

vector<TNMObject> Electron;
vector<TNMObject> FatJet;

// internal objects
vector<TNMObject> photons;
vector<TNMObject> AK8jets;
vector<TNMObject> tausVeto;
vector<TNMObject> electronsVeto;
vector<TNMObject> muonsVeto;
vector<TNMObject> muonsSel;
vector<TNMObject> AK4jets;

TNMObject met;

vector<TNMObject> electronsSel;
vector<TNMObject> AK4jetsNopho;
vector<TNMObject> megajets;
vector<TNMObject> WjetsMasstag;
vector<TNMObject> WjetsAntitag;
vector<TNMObject> bjetsTight;
vector<TNMObject> megajetsNopho;
vector<TNMObject> bjetsMedium;
vector<TNMObject> Wjets;
vector<TNMObject> bjetsLoose;
vector<TNMObject> leptonsVeto;
vector<TNMObject> topjetsMasstag;
vector<TNMObject> leptonsSel;
vector<TNMObject> topjetsMasstag0b;
vector<TNMObject> topjetsAntitag;
vector<TNMObject> topjets;


// object definitions
struct object_photons_s : public TNMThing
{
  object_photons_s() : TNMThing() {}
  ~object_photons_s() {}
  bool create()
  {
    photons.clear();

    // note: o and Photon are the same object
    vector<TNMObject>& o = Photon;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 80) ) continue;
        if ( !(p("|eta|") < 2.5) ) continue;
        photons.push_back(p);
      }
  return true;
  };
} object_photons;

struct object_AK8jets_s : public TNMThing
{
  object_AK8jets_s() : TNMThing() {}
  ~object_AK8jets_s() {}
  bool create()
  {
    AK8jets.clear();

    // note: o and FatJet are the same object
    vector<TNMObject>& o = FatJet;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 200) ) continue;
        if ( !(p("|eta|") < 2.4) ) continue;
        AK8jets.push_back(p);
      }
  return true;
  };
} object_AK8jets;

struct object_tausVeto_s : public TNMThing
{
  object_tausVeto_s() : TNMThing() {}
  ~object_tausVeto_s() {}
  bool create()
  {
    tausVeto.clear();

    // note: o and Tau are the same object
    vector<TNMObject>& o = Tau;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 18) ) continue;
        if ( !(p("|eta|") < 2.5) ) continue;
        if ( !(p("idMVAnewDM2017v2") >= 4) ) continue;
        tausVeto.push_back(p);
      }
  return true;
  };
} object_tausVeto;

struct object_electronsVeto_s : public TNMThing
{
  object_electronsVeto_s() : TNMThing() {}
  ~object_electronsVeto_s() {}
  bool create()
  {
    electronsVeto.clear();

    // note: o and Electron are the same object
    vector<TNMObject>& o = Electron;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 5) ) continue;
        if ( !(p("|eta|") < 2.5) ) continue;
        if ( !(p("miniPFRelIso_all") < 0.1) ) continue;
        if ( !(p("|dxy|") < 0.05) ) continue;
        if ( !(p("|dz|") < 0.1) ) continue;
        electronsVeto.push_back(p);
      }
  return true;
  };
} object_electronsVeto;

struct object_muonsVeto_s : public TNMThing
{
  object_muonsVeto_s() : TNMThing() {}
  ~object_muonsVeto_s() {}
  bool create()
  {
    muonsVeto.clear();

    // note: o and Muon are the same object
    vector<TNMObject>& o = Muon;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 5) ) continue;
        if ( !(p("|eta|") < 2.4) ) continue;
        if ( !(p("softId") == 1) ) continue;
        if ( !(p("miniPFRelIso_all") < 0.2) ) continue;
        if ( !(p("|dxy|") < 0.2) ) continue;
        if ( !(p("|dz|") < 0.5) ) continue;
        muonsVeto.push_back(p);
      }
  return true;
  };
} object_muonsVeto;

struct object_muonsSel_s : public TNMThing
{
  object_muonsSel_s() : TNMThing() {}
  ~object_muonsSel_s() {}
  bool create()
  {
    muonsSel.clear();

    // note: o and Muon are the same object
    vector<TNMObject>& o = Muon;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 10) ) continue;
        if ( !(p("|eta|") < 2.4) ) continue;
        if ( !(p("miniPFRelIso_all") < 0.15) ) continue;
        if ( !(p("|dxy|") < 0.05) ) continue;
        if ( !(p("|dz|") < 0.1) ) continue;
        muonsSel.push_back(p);
      }
  return true;
  };
} object_muonsSel;

struct object_AK4jets_s : public TNMThing
{
  object_AK4jets_s() : TNMThing() {}
  ~object_AK4jets_s() {}
  bool create()
  {
    AK4jets.clear();

    // note: o and Jet are the same object
    vector<TNMObject>& o = Jet;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 30) ) continue;
        if ( !(p("|eta|") < 2.4) ) continue;
        AK4jets.push_back(p);
      }
  return true;
  };
} object_AK4jets;

struct object_met_s : public TNMThing
{
  object_met_s() : TNMThing() {}
  ~object_met_s() {}
  bool create()
  {
    // singleton object
    met = MET;
  return true;
  };
} object_met;

struct object_electronsSel_s : public TNMThing
{
  object_electronsSel_s() : TNMThing() {}
  ~object_electronsSel_s() {}
  bool create()
  {
    electronsSel.clear();

    // note: o and Electron are the same object
    vector<TNMObject>& o = Electron;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 10) ) continue;
        if ( !(p("|eta|") < 2.5) ) continue;
        if ( !((p("|eta|") <= 1.442) ||
		 (p("|eta|") >= 1.556)) ) continue;
        if ( !(p("miniPFRelIso_all") < 0.1) ) continue;
        if ( !(p("|dxy|") < 0.05) ) continue;
        if ( !(p("|dz|") < 0.1) ) continue;
        electronsSel.push_back(p);
      }
  return true;
  };
} object_electronsSel;

struct object_AK4jetsNopho_s : public TNMThing
{
  object_AK4jetsNopho_s() : TNMThing() {}
  ~object_AK4jetsNopho_s() {}
  bool create()
  {
    AK4jetsNopho.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        TNMObject& j = p;
        TNMBool cut1(photons.size());
        for(size_t n=0; n < photons.size(); n++)
          {
            cut1[n] = _dR(j, photons[n]) < 0.4  &&
		 (photons[n]("pt")/j("pt") >= 0.5) &&
		 (photons[n]("pt")/j("pt") <= 2.0);
          }
        if ( (cut1.OR()) ) continue;
        AK4jetsNopho.push_back(p);
      }
  return true;
  };
} object_AK4jetsNopho;

struct object_megajets_s : public TNMThing
{
  object_megajets_s() : TNMThing() {}
  ~object_megajets_s() {}
  bool create()
  {
    megajets.clear();
    vector<TNMObject> o = _fmegajets(AK4jets);

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        megajets.push_back(p);
      }
  return true;
  };
} object_megajets;

struct object_WjetsMasstag_s : public TNMThing
{
  object_WjetsMasstag_s() : TNMThing() {}
  ~object_WjetsMasstag_s() {}
  bool create()
  {
    WjetsMasstag.clear();

    // note: o and AK8jets are the same object
    vector<TNMObject>& o = AK8jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !((p("msoftdrop") >= 65) &&
		 (p("msoftdrop") <= 105)) ) continue;
        WjetsMasstag.push_back(p);
      }
  return true;
  };
} object_WjetsMasstag;

struct object_WjetsAntitag_s : public TNMThing
{
  object_WjetsAntitag_s() : TNMThing() {}
  ~object_WjetsAntitag_s() {}
  bool create()
  {
    WjetsAntitag.clear();

    // note: o and WjetsMasstag are the same object
    vector<TNMObject>& o = WjetsMasstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("tau2") / p("tau1") > 0.4) ) continue;
        WjetsAntitag.push_back(p);
      }
  return true;
  };
} object_WjetsAntitag;

struct object_bjetsTight_s : public TNMThing
{
  object_bjetsTight_s() : TNMThing() {}
  ~object_bjetsTight_s() {}
  bool create()
  {
    bjetsTight.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.8001) ) continue;
        bjetsTight.push_back(p);
      }
  return true;
  };
} object_bjetsTight;

struct object_megajetsNopho_s : public TNMThing
{
  object_megajetsNopho_s() : TNMThing() {}
  ~object_megajetsNopho_s() {}
  bool create()
  {
    megajetsNopho.clear();
    vector<TNMObject> o = _fmegajets(AK4jetsNopho);

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        megajetsNopho.push_back(p);
      }
  return true;
  };
} object_megajetsNopho;

struct object_bjetsMedium_s : public TNMThing
{
  object_bjetsMedium_s() : TNMThing() {}
  ~object_bjetsMedium_s() {}
  bool create()
  {
    bjetsMedium.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.4941) ) continue;
        bjetsMedium.push_back(p);
      }
  return true;
  };
} object_bjetsMedium;

struct object_Wjets_s : public TNMThing
{
  object_Wjets_s() : TNMThing() {}
  ~object_Wjets_s() {}
  bool create()
  {
    Wjets.clear();

    // note: o and WjetsMasstag are the same object
    vector<TNMObject>& o = WjetsMasstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("tau2") / p("tau1") <= 0.4) ) continue;
        Wjets.push_back(p);
      }
  return true;
  };
} object_Wjets;

struct object_bjetsLoose_s : public TNMThing
{
  object_bjetsLoose_s() : TNMThing() {}
  ~object_bjetsLoose_s() {}
  bool create()
  {
    bjetsLoose.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.152) ) continue;
        bjetsLoose.push_back(p);
      }
  return true;
  };
} object_bjetsLoose;

struct object_leptonsVeto_s : public TNMThing
{
  object_leptonsVeto_s() : TNMThing() {}
  ~object_leptonsVeto_s() {}
  bool create()
  {
    leptonsVeto.clear();
    // concatenate vectors
    vector<TNMObject> o;
    for(size_t n=0; n < electronsVeto.size(); n++)
      {
        o.push_back(electronsVeto[n]);
      }
    for(size_t n=0; n < muonsVeto.size(); n++)
      {
        o.push_back(muonsVeto[n]);
      }
    
    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        leptonsVeto.push_back(p);
      }
    sort(leptonsVeto.begin(), leptonsVeto.end());
  return true;
  };
} object_leptonsVeto;

struct object_topjetsMasstag_s : public TNMThing
{
  object_topjetsMasstag_s() : TNMThing() {}
  ~object_topjetsMasstag_s() {}
  bool create()
  {
    topjetsMasstag.clear();

    // note: o and AK8jets are the same object
    vector<TNMObject>& o = AK8jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 400) ) continue;
        if ( !((p("msoftdrop") >= 105) &&
		 (p("msoftdrop") <= 210)) ) continue;
        topjetsMasstag.push_back(p);
      }
  return true;
  };
} object_topjetsMasstag;

struct object_leptonsSel_s : public TNMThing
{
  object_leptonsSel_s() : TNMThing() {}
  ~object_leptonsSel_s() {}
  bool create()
  {
    leptonsSel.clear();
    // concatenate vectors
    vector<TNMObject> o;
    for(size_t n=0; n < electronsSel.size(); n++)
      {
        o.push_back(electronsSel[n]);
      }
    for(size_t n=0; n < muonsSel.size(); n++)
      {
        o.push_back(muonsSel[n]);
      }
    
    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        leptonsSel.push_back(p);
      }
    sort(leptonsSel.begin(), leptonsSel.end());
  return true;
  };
} object_leptonsSel;

struct object_topjetsMasstag0b_s : public TNMThing
{
  object_topjetsMasstag0b_s() : TNMThing() {}
  ~object_topjetsMasstag0b_s() {}
  bool create()
  {
    topjetsMasstag0b.clear();

    // note: o and topjetsMasstag are the same object
    vector<TNMObject>& o = topjetsMasstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") < 0.1522) ) continue;
        topjetsMasstag0b.push_back(p);
      }
  return true;
  };
} object_topjetsMasstag0b;

struct object_topjetsAntitag_s : public TNMThing
{
  object_topjetsAntitag_s() : TNMThing() {}
  ~object_topjetsAntitag_s() {}
  bool create()
  {
    topjetsAntitag.clear();

    // note: o and topjetsMasstag are the same object
    vector<TNMObject>& o = topjetsMasstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") < 0.1522) ) continue;
        if ( !(p("tau3") / p("tau2") >= 0.46) ) continue;
        topjetsAntitag.push_back(p);
      }
  return true;
  };
} object_topjetsAntitag;

struct object_topjets_s : public TNMThing
{
  object_topjets_s() : TNMThing() {}
  ~object_topjets_s() {}
  bool create()
  {
    topjets.clear();

    // note: o and topjetsMasstag are the same object
    vector<TNMObject>& o = topjetsMasstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") >= 0.1522) ) continue;
        if ( !(p("tau3") / p("tau2") < 0.46) ) continue;
        topjets.push_back(p);
      }
  return true;
  };
} object_topjets;


//------------------------------------------------------------------
// defines (aliases)

struct MRNopho_s : public TNMThing
{
  MRNopho_s() : TNMThing(), done(false) {}
  ~MRNopho_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _fMR(megajetsNopho);
        return value;
      }
  }
  bool done;
  float value;
} MRNopho;

struct METpho_s : public TNMThing
{
  METpho_s() : TNMThing(), done(false) {}
  ~METpho_s() {}
  void reset() { done = false; }
  operator TNMObject()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = met + photons[0];
        return value;
      }
  }
  bool done;
  TNMObject value;
} METpho;

struct dphimegajetsNopho_s : public TNMThing
{
  dphimegajetsNopho_s() : TNMThing(), done(false) {}
  ~dphimegajetsNopho_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _dPhi(megajetsNopho[0], megajetsNopho[1]);
        return value;
      }
  }
  bool done;
  float value;
} dphimegajetsNopho;

struct METl_s : public TNMThing
{
  METl_s() : TNMThing(), done(false) {}
  ~METl_s() {}
  void reset() { done = false; }
  operator TNMObject()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = met + leptonsVeto[0];
        return value;
      }
  }
  bool done;
  TNMObject value;
} METl;

struct METll_s : public TNMThing
{
  METll_s() : TNMThing(), done(false) {}
  ~METll_s() {}
  void reset() { done = false; }
  operator TNMObject()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = met + leptonsVeto[0] + leptonsVeto[1];
        return value;
      }
  }
  bool done;
  TNMObject value;
} METll;

struct MR_s : public TNMThing
{
  MR_s() : TNMThing(), done(false) {}
  ~MR_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _fMR(megajets);
        return value;
      }
  }
  bool done;
  float value;
} MR;

struct Mll_s : public TNMThing
{
  Mll_s() : TNMThing(), done(false) {}
  ~Mll_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _fMll(leptonsSel[0], leptonsSel[1]);
        return value;
      }
  }
  bool done;
  float value;
} Mll;

struct MT_s : public TNMThing
{
  MT_s() : TNMThing(), done(false) {}
  ~MT_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _fMT(leptonsVeto[0], met);
        return value;
      }
  }
  bool done;
  float value;
} MT;

struct dphimegajets_s : public TNMThing
{
  dphimegajets_s() : TNMThing(), done(false) {}
  ~dphimegajets_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = _dPhi(megajets[0], megajets[1]);
        return value;
      }
  }
  bool done;
  float value;
} dphimegajets;

struct Rsq_s : public TNMThing
{
  Rsq_s() : TNMThing(), done(false) {}
  ~Rsq_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = sqrt(_fMTR(megajets, met) / MR);
        return value;
      }
  }
  bool done;
  float value;
} Rsq;

struct Rsqpho_s : public TNMThing
{
  Rsqpho_s() : TNMThing(), done(false) {}
  ~Rsqpho_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = sqrt(_fMTR(megajetsNopho, (TNMObject&)METpho) / MRNopho);
        return value;
      }
  }
  bool done;
  float value;
} Rsqpho;

struct Rsqll_s : public TNMThing
{
  Rsqll_s() : TNMThing(), done(false) {}
  ~Rsqll_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = sqrt(_fMTR(megajets, (TNMObject&)METll) / MR);
        return value;
      }
  }
  bool done;
  float value;
} Rsqll;

struct Rsql_s : public TNMThing
{
  Rsql_s() : TNMThing(), done(false) {}
  ~Rsql_s() {}
  void reset() { done = false; }
  operator float()
  {
    if ( done )
      {
        return value;
      }
    else
      {
        done  = true;
        value = sqrt(_fMTR(megajets, (TNMObject&)METl) / MR);
        return value;
      }
  }
  bool done;
  float value;
} Rsql;

//------------------------------------------------------------------
// regions
struct region_TopcategoryCRL_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRL_s()
    : TNMThing(),
      name("TopcategoryCRL"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_TopcategoryCRL", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("Rsql > 0.08", 0);
    hcount->Fill("topjetsMasstag0b.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
  }

  ~region_TopcategoryCRL_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(AK4jets.size() >= 3) ) return false;
    count("AK4jets.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(MR > 800) ) return false;
    count("MR > 800");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(Rsql > 0.08) ) return false;
    count("Rsql > 0.08");

    if ( !(topjetsMasstag0b.size() >= 1) ) return false;
    count("topjetsMasstag0b.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRL;

struct region_WcategoryCRZ_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRZ_s()
    : TNMThing(),
      name("WcategoryCRZ"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_WcategoryCRZ", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("(muonsSel.size == 2 and electronsVeto.size == 0) or (electronsSel.size == 2 and muonsVeto.size == 0)", 0);
    hcount->Fill("leptonsSel[0].charge + leptonsSel[1].charge == 0", 0);
    hcount->Fill("fMll(leptonsSel[0], leptonsSel[1]) < 10", 0);
    hcount->Fill("Rsqll > 0.08", 0);
    hcount->Fill("WjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_WcategoryCRZ_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(AK4jets.size() >= 3) ) return false;
    count("AK4jets.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(MR > 800) ) return false;
    count("MR > 800");

    if ( !((muonsSel.size() == 2  &&
		  electronsVeto.size() == 0)  ||
		  (electronsSel.size() == 2  &&
		  muonsVeto.size() == 0)) ) return false;
    count("(muonsSel.size == 2 and electronsVeto.size == 0) or (electronsSel.size == 2 and muonsVeto.size == 0)");

    if ( !(leptonsSel[0]("charge") + leptonsSel[1]("charge") == 0) ) return false;
    count("leptonsSel[0].charge + leptonsSel[1].charge == 0");

    if ( !(_fMll(leptonsSel[0], leptonsSel[1]) < 10) ) return false;
    count("fMll(leptonsSel[0], leptonsSel[1]) < 10");

    if ( !(Rsqll > 0.08) ) return false;
    count("Rsqll > 0.08");

    if ( !(WjetsMasstag.size() >= 1) ) return false;
    count("WjetsMasstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRZ;

struct region_TopcategoryCRZ_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRZ_s()
    : TNMThing(),
      name("TopcategoryCRZ"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_TopcategoryCRZ", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("(muonsSel.size == 2 and electronsVeto.size == 0) or (electronsSel.size == 2 and muonsVeto.size == 0)", 0);
    hcount->Fill("leptonsSel[0].charge + leptonsSel[1].charge == 0", 0);
    hcount->Fill("fMll(leptonsSel[0], leptonsSel[1]) < 10", 0);
    hcount->Fill("Rsqll > 0.08", 0);
    hcount->Fill("topjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_TopcategoryCRZ_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(AK4jets.size() >= 3) ) return false;
    count("AK4jets.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(MR > 800) ) return false;
    count("MR > 800");

    if ( !((muonsSel.size() == 2  &&
		  electronsVeto.size() == 0)  ||
		  (electronsSel.size() == 2  &&
		  muonsVeto.size() == 0)) ) return false;
    count("(muonsSel.size == 2 and electronsVeto.size == 0) or (electronsSel.size == 2 and muonsVeto.size == 0)");

    if ( !(leptonsSel[0]("charge") + leptonsSel[1]("charge") == 0) ) return false;
    count("leptonsSel[0].charge + leptonsSel[1].charge == 0");

    if ( !(_fMll(leptonsSel[0], leptonsSel[1]) < 10) ) return false;
    count("fMll(leptonsSel[0], leptonsSel[1]) < 10");

    if ( !(Rsqll > 0.08) ) return false;
    count("Rsqll > 0.08");

    if ( !(topjetsMasstag.size() >= 1) ) return false;
    count("topjetsMasstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRZ;

struct region_WcategoryCRG_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRG_s()
    : TNMThing(),
      name("WcategoryCRG"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_WcategoryCRG", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("photons.size == 1", 0);
    hcount->Fill("AK4jetsNopho.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("MRNopho > 800", 0);
    hcount->Fill("Rsqpho > 0.08", 0);
    hcount->Fill("WjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajetsNopho < 2.8", 0);
  }

  ~region_WcategoryCRG_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(photons.size() == 1) ) return false;
    count("photons.size == 1");

    if ( !(AK4jetsNopho.size() >= 3) ) return false;
    count("AK4jetsNopho.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(MRNopho > 800) ) return false;
    count("MRNopho > 800");

    if ( !(Rsqpho > 0.08) ) return false;
    count("Rsqpho > 0.08");

    if ( !(WjetsMasstag.size() >= 1) ) return false;
    count("WjetsMasstag.size >= 1");

    if ( !(dphimegajetsNopho < 2.8) ) return false;
    count("dphimegajetsNopho < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRG;

struct region_WcategoryCRL_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRL_s()
    : TNMThing(),
      name("WcategoryCRL"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_WcategoryCRL", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("Rsql > 0.08", 0);
    hcount->Fill("WjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
  }

  ~region_WcategoryCRL_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(AK4jets.size() >= 3) ) return false;
    count("AK4jets.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(MR > 800) ) return false;
    count("MR > 800");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(Rsql > 0.08) ) return false;
    count("Rsql > 0.08");

    if ( !(WjetsMasstag.size() >= 1) ) return false;
    count("WjetsMasstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRL;

struct region_preselection_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_preselection_s()
    : TNMThing(),
      name("preselection"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(4)
  {
    hcount = new TH1F("cutflow_preselection", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("Rsq > 0.08", 0);
  }

  ~region_preselection_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(AK4jets.size() >= 3) ) return false;
    count("AK4jets.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(MR > 800) ) return false;
    count("MR > 800");

    if ( !(Rsq > 0.08) ) return false;
    count("Rsq > 0.08");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_preselection;

struct region_TopcategoryCRG_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRG_s()
    : TNMThing(),
      name("TopcategoryCRG"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_TopcategoryCRG", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("photons.size == 1", 0);
    hcount->Fill("AK4jetsNopho.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("MRNopho > 800", 0);
    hcount->Fill("Rsqpho > 0.08", 0);
    hcount->Fill("topjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajetsNopho < 2.8", 0);
  }

  ~region_TopcategoryCRG_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(photons.size() == 1) ) return false;
    count("photons.size == 1");

    if ( !(AK4jetsNopho.size() >= 3) ) return false;
    count("AK4jetsNopho.size >= 3");

    if ( !(AK8jets.size() >= 1) ) return false;
    count("AK8jets.size >= 1");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(MRNopho > 800) ) return false;
    count("MRNopho > 800");

    if ( !(Rsqpho > 0.08) ) return false;
    count("Rsqpho > 0.08");

    if ( !(topjetsMasstag.size() >= 1) ) return false;
    count("topjetsMasstag.size >= 1");

    if ( !(dphimegajetsNopho < 2.8) ) return false;
    count("dphimegajetsNopho < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRG;

struct region_TopcategoryCRW_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRW_s()
    : TNMThing(),
      name("TopcategoryCRW"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_TopcategoryCRW", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("topjetsMasstag0b.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
  }

  ~region_TopcategoryCRW_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(topjetsMasstag0b.size() >= 1) ) return false;
    count("topjetsMasstag0b.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRW;

struct region_TopcategorySR_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategorySR_s()
    : TNMThing(),
      name("TopcategorySR"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(5)
  {
    hcount = new TH1F("cutflow_TopcategorySR", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("topjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_TopcategorySR_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(topjets.size() >= 1) ) return false;
    count("topjets.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategorySR;

struct region_TopcategoryCRT_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRT_s()
    : TNMThing(),
      name("TopcategoryCRT"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(5)
  {
    hcount = new TH1F("cutflow_TopcategoryCRT", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("topjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT < 100", 0);
  }

  ~region_TopcategoryCRT_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(topjets.size() >= 1) ) return false;
    count("topjets.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !(MT < 100) ) return false;
    count("MT < 100");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRT;

struct region_TopcategoryCRQ_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_TopcategoryCRQ_s()
    : TNMThing(),
      name("TopcategoryCRQ"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_TopcategoryCRQ", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("topjetsAntitag.size >= 1", 0);
    hcount->Fill("dphimegajets >= 2.8", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
  }

  ~region_TopcategoryCRQ_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(topjetsAntitag.size() >= 1) ) return false;
    count("topjetsAntitag.size >= 1");

    if ( !(dphimegajets >= 2.8) ) return false;
    count("dphimegajets >= 2.8");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_TopcategoryCRQ;

struct region_WcategorySR_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategorySR_s()
    : TNMThing(),
      name("WcategorySR"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_WcategorySR", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("bjetsMedium.size >= 1", 0);
    hcount->Fill("Wjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_WcategorySR_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(bjetsMedium.size() >= 1) ) return false;
    count("bjetsMedium.size >= 1");

    if ( !(Wjets.size() >= 1) ) return false;
    count("Wjets.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategorySR;

struct region_WcategoryCRQ_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRQ_s()
    : TNMThing(),
      name("WcategoryCRQ"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_WcategoryCRQ", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 0", 0);
    hcount->Fill("tausVeto.size == 0", 0);
    hcount->Fill("WjetsAntitag.size >= 1", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
    hcount->Fill("dphimegajets >= 2.8", 0);
  }

  ~region_WcategoryCRQ_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 0) ) return false;
    count("leptonsVeto.size == 0");

    if ( !(tausVeto.size() == 0) ) return false;
    count("tausVeto.size == 0");

    if ( !(WjetsAntitag.size() >= 1) ) return false;
    count("WjetsAntitag.size >= 1");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    if ( !(dphimegajets >= 2.8) ) return false;
    count("dphimegajets >= 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRQ;

struct region_WcategoryCRW_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRW_s()
    : TNMThing(),
      name("WcategoryCRW"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_WcategoryCRW", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("WjetsMasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
    hcount->Fill("bjetsLoose.size == 0", 0);
  }

  ~region_WcategoryCRW_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(WjetsMasstag.size() >= 1) ) return false;
    count("WjetsMasstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    if ( !(bjetsLoose.size() == 0) ) return false;
    count("bjetsLoose.size == 0");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRW;

struct region_WcategoryCRT_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_WcategoryCRT_s()
    : TNMThing(),
      name("WcategoryCRT"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_WcategoryCRT", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsVeto.size == 1", 0);
    hcount->Fill("Wjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT < 100", 0);
    hcount->Fill("bjetsMedium.size >= 1", 0);
  }

  ~region_WcategoryCRT_s() {}

  void summary(std::ostream& os)
  {
    os << name << std::endl;
    double gtotal = hcount->GetBinContent(1);
    for(int c=0; c <= ncuts; c++)
      {
        double value(hcount->GetBinContent(c+1));
        double error(hcount->GetBinError(c+1));
        double efficiency=0;
        if ( gtotal > 0 ) efficiency = value/gtotal;
        char record[1024];
        sprintf(record, 
                " %2d %-45s:"
                " %9.2f +/- %5.1f %6.3f",
                c+1, hcount->GetXaxis()->GetBinLabel(c+1), 
                value, error, efficiency);
        os << record << std::endl;
      }
    os << std::endl;
  }
  void count(string c)		{ hcount->Fill(c.c_str(), weight); }
  void write(TFile* fout)	{ fout->cd(); hcount->Write(); }
  void reset()			{ done = false; result = false; }
  bool operator()()		{ return create(); }

  bool create()
  {
    if ( done ) return result;
    done   = true;
    result = false;
    count("none");

    if ( !(region_preselection()) ) return false;
    count("preselection");

    if ( !(leptonsVeto.size() == 1) ) return false;
    count("leptonsVeto.size == 1");

    if ( !(Wjets.size() >= 1) ) return false;
    count("Wjets.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !(MT < 100) ) return false;
    count("MT < 100");

    if ( !(bjetsMedium.size() >= 1) ) return false;
    count("bjetsMedium.size >= 1");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_WcategoryCRT;


//------------------------------------------------------------------
analyzer_s::analyzer_s()
{
  // cache pointers to defines
  defines.clear();
  defines.push_back(&MRNopho);
  defines.push_back(&METpho);
  defines.push_back(&dphimegajetsNopho);
  defines.push_back(&Rsq);
  defines.push_back(&METl);
  defines.push_back(&Rsqpho);
  defines.push_back(&METll);
  defines.push_back(&MR);
  defines.push_back(&Mll);
  defines.push_back(&Rsqll);
  defines.push_back(&Rsql);
  defines.push_back(&MT);
  defines.push_back(&dphimegajets);

  // cache pointers to filtered objects
  objects.clear();
  objects.push_back(&object_photons);
  objects.push_back(&object_AK8jets);
  objects.push_back(&object_tausVeto);
  objects.push_back(&object_electronsVeto);
  objects.push_back(&object_muonsVeto);
  objects.push_back(&object_muonsSel);
  objects.push_back(&object_AK4jets);
  objects.push_back(&object_met);
  objects.push_back(&object_electronsSel);
  objects.push_back(&object_AK4jetsNopho);
  objects.push_back(&object_megajets);
  objects.push_back(&object_WjetsMasstag);
  objects.push_back(&object_WjetsAntitag);
  objects.push_back(&object_bjetsTight);
  objects.push_back(&object_megajetsNopho);
  objects.push_back(&object_bjetsMedium);
  objects.push_back(&object_Wjets);
  objects.push_back(&object_bjetsLoose);
  objects.push_back(&object_leptonsVeto);
  objects.push_back(&object_topjetsMasstag);
  objects.push_back(&object_leptonsSel);
  objects.push_back(&object_topjetsMasstag0b);
  objects.push_back(&object_topjetsAntitag);
  objects.push_back(&object_topjets);

  // cache pointers to regions
  regions.clear();
  regions.push_back(&region_TopcategoryCRL);
  regions.push_back(&region_WcategoryCRZ);
  regions.push_back(&region_TopcategoryCRZ);
  regions.push_back(&region_WcategoryCRG);
  regions.push_back(&region_WcategoryCRL);
  regions.push_back(&region_preselection);
  regions.push_back(&region_TopcategoryCRG);
  regions.push_back(&region_TopcategoryCRW);
  regions.push_back(&region_TopcategorySR);
  regions.push_back(&region_TopcategoryCRT);
  regions.push_back(&region_TopcategoryCRQ);
  regions.push_back(&region_WcategorySR);
  regions.push_back(&region_WcategoryCRQ);
  regions.push_back(&region_WcategoryCRW);
  regions.push_back(&region_WcategoryCRT);
 }

analyzer_s::~analyzer_s() {}

void analyzer_s::run(std::vector<TNMObject>& Muon_,
                     std::vector<TNMObject>& Jet_,
                     std::vector<TNMObject>& Tau_,
                     std::vector<TNMObject>& Photon_,
                     TNMObject& MET_,
                     std::vector<TNMObject>& Electron_,
                     std::vector<TNMObject>& FatJet_)

{
  // copy to internal buffers
  Muon	= Muon_;
  Jet	= Jet_;
  Tau	= Tau_;
  Photon	= Photon_;
  MET	= MET_;
  Electron	= Electron_;
  FatJet	= FatJet_;

  // reset all objects
  for(size_t c=0; c < defines.size(); c++) defines[c]->reset();
  for(size_t c=0; c < objects.size(); c++) objects[c]->reset();
  for(size_t c=0; c < regions.size(); c++) regions[c]->reset();

  // create objects by applying selection criteria
  for(size_t c=0; c < objects.size(); c++) objects[c]->create();

  // create regions by applying selection criteria
  for(size_t c=0; c < regions.size(); c++) regions[c]->create();
}

void analyzer_s::summary(TFile* fout, ostream& os)
{
  os << std::endl << "Summary" << std::endl << std::endl;
  for(size_t c=0; c < regions.size(); c++)
    {
      regions[c]->summary(os);
      regions[c]->write(fout);
    }
}
