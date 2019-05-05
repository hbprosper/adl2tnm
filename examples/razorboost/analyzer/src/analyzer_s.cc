//------------------------------------------------------------------
// File:        analyzer_s.cc
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
vector<TNMObject> Tau;
vector<TNMObject> Jet;
vector<TNMObject> Muon;
vector<TNMObject> Photon;

TNMObject MET;

vector<TNMObject> Electron;
vector<TNMObject> FatJet;

// internal objects
vector<TNMObject> taus_veto;
vector<TNMObject> electrons_sel;
vector<TNMObject> AK8jets;
vector<TNMObject> muons_sel;

TNMObject met;

vector<TNMObject> AK4jets;
vector<TNMObject> electrons_veto;
vector<TNMObject> muons_veto;
vector<TNMObject> photons;
vector<TNMObject> megajets;
vector<TNMObject> bjets_loose;
vector<TNMObject> topjets_masstag;
vector<TNMObject> bjets_medium;
vector<TNMObject> jets_0pho;
vector<TNMObject> leptons_veto;
vector<TNMObject> leptons_sel;
vector<TNMObject> bjets_tight;
vector<TNMObject> Wjets_masstag;
vector<TNMObject> Wjets_antitag;
vector<TNMObject> topjets;
vector<TNMObject> topjets_antitag;
vector<TNMObject> topjets_masstag_0b;
vector<TNMObject> Wjets;


// object definitions
struct object_taus_veto_s : public TNMThing
{
  object_taus_veto_s() : TNMThing() {}
  ~object_taus_veto_s() {}
  bool create()
  {
    taus_veto.clear();

    // note: o and Tau are the same object
    vector<TNMObject>& o = Tau;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 18) ) continue;
        if ( !(p("|eta|") < 2.5) ) continue;
        if ( !(p("idMVAnewDM2017v2") >= 4) ) continue;
        taus_veto.push_back(p);
      }
  return true;
  };
} object_taus_veto;

struct object_electrons_sel_s : public TNMThing
{
  object_electrons_sel_s() : TNMThing() {}
  ~object_electrons_sel_s() {}
  bool create()
  {
    electrons_sel.clear();

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
        electrons_sel.push_back(p);
      }
  return true;
  };
} object_electrons_sel;

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

struct object_muons_sel_s : public TNMThing
{
  object_muons_sel_s() : TNMThing() {}
  ~object_muons_sel_s() {}
  bool create()
  {
    muons_sel.clear();

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
        muons_sel.push_back(p);
      }
  return true;
  };
} object_muons_sel;

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

struct object_electrons_veto_s : public TNMThing
{
  object_electrons_veto_s() : TNMThing() {}
  ~object_electrons_veto_s() {}
  bool create()
  {
    electrons_veto.clear();

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
        electrons_veto.push_back(p);
      }
  return true;
  };
} object_electrons_veto;

struct object_muons_veto_s : public TNMThing
{
  object_muons_veto_s() : TNMThing() {}
  ~object_muons_veto_s() {}
  bool create()
  {
    muons_veto.clear();

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
        muons_veto.push_back(p);
      }
  return true;
  };
} object_muons_veto;

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

struct object_bjets_loose_s : public TNMThing
{
  object_bjets_loose_s() : TNMThing() {}
  ~object_bjets_loose_s() {}
  bool create()
  {
    bjets_loose.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.152) ) continue;
        bjets_loose.push_back(p);
      }
  return true;
  };
} object_bjets_loose;

struct object_topjets_masstag_s : public TNMThing
{
  object_topjets_masstag_s() : TNMThing() {}
  ~object_topjets_masstag_s() {}
  bool create()
  {
    topjets_masstag.clear();

    // note: o and AK8jets are the same object
    vector<TNMObject>& o = AK8jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("pt") > 400) ) continue;
        if ( !((p("msoftdrop") >= 105) &&
		 (p("msoftdrop") <= 210)) ) continue;
        topjets_masstag.push_back(p);
      }
  return true;
  };
} object_topjets_masstag;

struct object_bjets_medium_s : public TNMThing
{
  object_bjets_medium_s() : TNMThing() {}
  ~object_bjets_medium_s() {}
  bool create()
  {
    bjets_medium.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.4941) ) continue;
        bjets_medium.push_back(p);
      }
  return true;
  };
} object_bjets_medium;

struct object_jets_0pho_s : public TNMThing
{
  object_jets_0pho_s() : TNMThing() {}
  ~object_jets_0pho_s() {}
  bool create()
  {
    jets_0pho.clear();

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
        jets_0pho.push_back(p);
      }
  return true;
  };
} object_jets_0pho;

struct object_leptons_veto_s : public TNMThing
{
  object_leptons_veto_s() : TNMThing() {}
  ~object_leptons_veto_s() {}
  bool create()
  {

    // concatenate vectors
    vector<TNMObject> o; size_t n = 0;

    n = o.size();
    o.resize(n + electrons_veto.size());
    copy(electrons_veto.begin(), electrons_veto.end(), o.begin() + n);

    n = o.size();
    o.resize(n + muons_veto.size());
    copy(muons_veto.begin(), muons_veto.end(), o.begin() + n);

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        leptons_veto.push_back(p);
      }
    sort(leptons_veto.begin(), leptons_veto.end());
  return true;
  };
} object_leptons_veto;

struct object_leptons_sel_s : public TNMThing
{
  object_leptons_sel_s() : TNMThing() {}
  ~object_leptons_sel_s() {}
  bool create()
  {

    // concatenate vectors
    vector<TNMObject> o; size_t n = 0;

    n = o.size();
    o.resize(n + electrons_sel.size());
    copy(electrons_sel.begin(), electrons_sel.end(), o.begin() + n);

    n = o.size();
    o.resize(n + muons_sel.size());
    copy(muons_sel.begin(), muons_sel.end(), o.begin() + n);

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        leptons_sel.push_back(p);
      }
    sort(leptons_sel.begin(), leptons_sel.end());
  return true;
  };
} object_leptons_sel;

struct object_bjets_tight_s : public TNMThing
{
  object_bjets_tight_s() : TNMThing() {}
  ~object_bjets_tight_s() {}
  bool create()
  {
    bjets_tight.clear();

    // note: o and AK4jets are the same object
    vector<TNMObject>& o = AK4jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") > 0.8001) ) continue;
        bjets_tight.push_back(p);
      }
  return true;
  };
} object_bjets_tight;

struct object_Wjets_masstag_s : public TNMThing
{
  object_Wjets_masstag_s() : TNMThing() {}
  ~object_Wjets_masstag_s() {}
  bool create()
  {
    Wjets_masstag.clear();

    // note: o and AK8jets are the same object
    vector<TNMObject>& o = AK8jets;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !((p("msoftdrop") >= 65) &&
		 (p("msoftdrop") <= 105)) ) continue;
        Wjets_masstag.push_back(p);
      }
  return true;
  };
} object_Wjets_masstag;

struct object_Wjets_antitag_s : public TNMThing
{
  object_Wjets_antitag_s() : TNMThing() {}
  ~object_Wjets_antitag_s() {}
  bool create()
  {
    Wjets_antitag.clear();

    // note: o and Wjets_masstag are the same object
    vector<TNMObject>& o = Wjets_masstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("tau2") / p("tau1") > 0.4) ) continue;
        Wjets_antitag.push_back(p);
      }
  return true;
  };
} object_Wjets_antitag;

struct object_topjets_s : public TNMThing
{
  object_topjets_s() : TNMThing() {}
  ~object_topjets_s() {}
  bool create()
  {
    topjets.clear();

    // note: o and topjets_masstag are the same object
    vector<TNMObject>& o = topjets_masstag;

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

struct object_topjets_antitag_s : public TNMThing
{
  object_topjets_antitag_s() : TNMThing() {}
  ~object_topjets_antitag_s() {}
  bool create()
  {
    topjets_antitag.clear();

    // note: o and topjets_masstag are the same object
    vector<TNMObject>& o = topjets_masstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") < 0.1522) ) continue;
        if ( !(p("tau3") / p("tau2") >= 0.46) ) continue;
        topjets_antitag.push_back(p);
      }
  return true;
  };
} object_topjets_antitag;

struct object_topjets_masstag_0b_s : public TNMThing
{
  object_topjets_masstag_0b_s() : TNMThing() {}
  ~object_topjets_masstag_0b_s() {}
  bool create()
  {
    topjets_masstag_0b.clear();

    // note: o and topjets_masstag are the same object
    vector<TNMObject>& o = topjets_masstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("btagDeepB") < 0.1522) ) continue;
        topjets_masstag_0b.push_back(p);
      }
  return true;
  };
} object_topjets_masstag_0b;

struct object_Wjets_s : public TNMThing
{
  object_Wjets_s() : TNMThing() {}
  ~object_Wjets_s() {}
  bool create()
  {
    Wjets.clear();

    // note: o and Wjets_masstag are the same object
    vector<TNMObject>& o = Wjets_masstag;

    for(size_t c=0; c < o.size(); c++)
      {
        TNMObject& p = o[c];
        if ( !(p("tau2") / p("tau1") <= 0.4) ) continue;
        Wjets.push_back(p);
      }
  return true;
  };
} object_Wjets;


//------------------------------------------------------------------
// defines (aliases)

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
        value = met + leptons_veto[0];
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
        value = met + leptons_veto[0] + leptons_veto[1];
        return value;
      }
  }
  bool done;
  TNMObject value;
} METll;

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
        value = _fMll(leptons_sel[0], leptons_sel[1]);
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
        value = _fMT(leptons_veto[0], met);
        return value;
      }
  }
  bool done;
  float value;
} MT;

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

struct R2ll_s : public TNMThing
{
  R2ll_s() : TNMThing(), done(false) {}
  ~R2ll_s() {}
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
} R2ll;

struct R2_s : public TNMThing
{
  R2_s() : TNMThing(), done(false) {}
  ~R2_s() {}
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
} R2;

struct R2l_s : public TNMThing
{
  R2l_s() : TNMThing(), done(false) {}
  ~R2l_s() {}
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
} R2l;

//------------------------------------------------------------------
// regions
struct region_W_L_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_L_s()
    : TNMThing(),
      name("W_L"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_W_L", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("R2l > 0.08", 0);
    hcount->Fill("bjetsloose.size == 0", 0);
    hcount->Fill("Wjetsmasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
  }

  ~region_W_L_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(R2l > 0.08) ) return false;
    count("R2l > 0.08");

    if ( !(bjets_loose.size() == 0) ) return false;
    count("bjets_loose.size == 0");

    if ( !(Wjets_masstag.size() >= 1) ) return false;
    count("Wjets_masstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_L;

struct region_W_G_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_G_s()
    : TNMThing(),
      name("W_G"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(7)
  {
    hcount = new TH1F("cutflow_W_G", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("photons.size == 1", 0);
    hcount->Fill("Wjetsmasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_W_G_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(photons.size() == 1) ) return false;
    count("photons.size == 1");

    if ( !(Wjets_masstag.size() >= 1) ) return false;
    count("Wjets_masstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_G;

struct region_W_Z_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_Z_s()
    : TNMThing(),
      name("W_Z"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_W_Z", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("(muonssel.size == 2 and electronsveto.size == 0) or (electronssel.size == 2 and muonsveto.size == 0)", 0);
    hcount->Fill("leptonssel[0].charge + leptonssel[1].charge == 0", 0);
    hcount->Fill("R2ll > 0.08", 0);
    hcount->Fill("Wjetsmasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("fMll(leptonssel[0], leptonssel[1]) < 10", 0);
  }

  ~region_W_Z_s() {}

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

    if ( !((muons_sel.size() == 2  &&
		  electrons_veto.size() == 0)  ||
		  (electrons_sel.size() == 2  &&
		  muons_veto.size() == 0)) ) return false;
    count("(muons_sel.size == 2 and electrons_veto.size == 0) or (electrons_sel.size == 2 and muons_veto.size == 0)");

    if ( !(leptons_sel[0]("charge") + leptons_sel[1]("charge") == 0) ) return false;
    count("leptons_sel[0].charge + leptons_sel[1].charge == 0");

    if ( !(R2ll > 0.08) ) return false;
    count("R2ll > 0.08");

    if ( !(Wjets_masstag.size() >= 1) ) return false;
    count("Wjets_masstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !(_fMll(leptons_sel[0], leptons_sel[1]) < 10) ) return false;
    count("fMll(leptons_sel[0], leptons_sel[1]) < 10");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_Z;

struct region_Top_L_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_L_s()
    : TNMThing(),
      name("Top_L"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_Top_L", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("R2l > 0.08", 0);
    hcount->Fill("bjetsloose.size == 0", 0);
    hcount->Fill("topjetsmasstag_0b.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
  }

  ~region_Top_L_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(R2l > 0.08) ) return false;
    count("R2l > 0.08");

    if ( !(bjets_loose.size() == 0) ) return false;
    count("bjets_loose.size == 0");

    if ( !(topjets_masstag_0b.size() >= 1) ) return false;
    count("topjets_masstag_0b.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_Top_L;

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
    hcount->Fill("R2 > 0.08", 0);
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

    if ( !(R2 > 0.08) ) return false;
    count("R2 > 0.08");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_preselection;

struct region_Top_G_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_G_s()
    : TNMThing(),
      name("Top_G"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(7)
  {
    hcount = new TH1F("cutflow_Top_G", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("photons.size == 1", 0);
    hcount->Fill("topjetsmasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_Top_G_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(photons.size() == 1) ) return false;
    count("photons.size == 1");

    if ( !(topjets_masstag.size() >= 1) ) return false;
    count("topjets_masstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_Top_G;

struct region_Top_Z_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_Z_s()
    : TNMThing(),
      name("Top_Z"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(9)
  {
    hcount = new TH1F("cutflow_Top_Z", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("AK4jets.size >= 3", 0);
    hcount->Fill("AK8jets.size >= 1", 0);
    hcount->Fill("MR > 800", 0);
    hcount->Fill("(muonssel.size == 2 and electronsveto.size == 0) or (electronssel.size == 2 and muonsveto.size == 0)", 0);
    hcount->Fill("leptonssel[0].charge + leptonssel[1].charge == 0", 0);
    hcount->Fill("R2ll > 0.08", 0);
    hcount->Fill("topjetsmasstag.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("fMll(leptonssel[0], leptonssel[1]) < 10", 0);
  }

  ~region_Top_Z_s() {}

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

    if ( !((muons_sel.size() == 2  &&
		  electrons_veto.size() == 0)  ||
		  (electrons_sel.size() == 2  &&
		  muons_veto.size() == 0)) ) return false;
    count("(muons_sel.size == 2 and electrons_veto.size == 0) or (electrons_sel.size == 2 and muons_veto.size == 0)");

    if ( !(leptons_sel[0]("charge") + leptons_sel[1]("charge") == 0) ) return false;
    count("leptons_sel[0].charge + leptons_sel[1].charge == 0");

    if ( !(R2ll > 0.08) ) return false;
    count("R2ll > 0.08");

    if ( !(topjets_masstag.size() >= 1) ) return false;
    count("topjets_masstag.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !(_fMll(leptons_sel[0], leptons_sel[1]) < 10) ) return false;
    count("fMll(leptons_sel[0], leptons_sel[1]) < 10");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_Top_Z;

struct region_W_T_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_T_s()
    : TNMThing(),
      name("W_T"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_W_T", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("bjetsloose.size >= 1", 0);
    hcount->Fill("Wjets.size >= 1", 0);
    hcount->Fill("MT < 100", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_W_T_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(bjets_loose.size() >= 1) ) return false;
    count("bjets_loose.size >= 1");

    if ( !(Wjets.size() >= 1) ) return false;
    count("Wjets.size >= 1");

    if ( !(MT < 100) ) return false;
    count("MT < 100");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_T;

struct region_W_W_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_W_s()
    : TNMThing(),
      name("W_W"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_W_W", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("bjetsloose.size > 0", 0);
    hcount->Fill("Wjetsmasstag.size >= 1", 0);
    hcount->Fill("MT [] 30 100", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_W_W_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(bjets_loose.size() > 0) ) return false;
    count("bjets_loose.size > 0");

    if ( !(Wjets_masstag.size() >= 1) ) return false;
    count("Wjets_masstag.size >= 1");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_W;

struct region_W_Q_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_Q_s()
    : TNMThing(),
      name("W_Q"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_W_Q", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("bjetsloose.size == 0", 0);
    hcount->Fill("Wjetsantitag.size >= 1", 0);
    hcount->Fill("dphimegajets >= 2.8", 0);
  }

  ~region_W_Q_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(bjets_loose.size() == 0) ) return false;
    count("bjets_loose.size == 0");

    if ( !(Wjets_antitag.size() >= 1) ) return false;
    count("Wjets_antitag.size >= 1");

    if ( !(dphimegajets >= 2.8) ) return false;
    count("dphimegajets >= 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_W_Q;

struct region_W_S_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_W_S_s()
    : TNMThing(),
      name("W_S"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_W_S", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("bjetsmedium.size >= 1", 0);
    hcount->Fill("Wjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_W_S_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(bjets_medium.size() >= 1) ) return false;
    count("bjets_medium.size >= 1");

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
} region_W_S;

struct region_Top_Q_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_Q_s()
    : TNMThing(),
      name("Top_Q"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_Top_Q", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("bjetsloose.size == 0", 0);
    hcount->Fill("topjetsantitag.size >= 1", 0);
    hcount->Fill("dphimegajets >= 2.8", 0);
  }

  ~region_Top_Q_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(bjets_loose.size() == 0) ) return false;
    count("bjets_loose.size == 0");

    if ( !(topjets_antitag.size() >= 1) ) return false;
    count("topjets_antitag.size >= 1");

    if ( !(dphimegajets >= 2.8) ) return false;
    count("dphimegajets >= 2.8");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_Top_Q;

struct region_Top_S_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_S_s()
    : TNMThing(),
      name("Top_S"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(5)
  {
    hcount = new TH1F("cutflow_Top_S", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 0", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("topjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
  }

  ~region_Top_S_s() {}

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

    if ( !(leptons_veto.size() == 0) ) return false;
    count("leptons_veto.size == 0");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

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
} region_Top_S;

struct region_Top_T_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_T_s()
    : TNMThing(),
      name("Top_T"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(6)
  {
    hcount = new TH1F("cutflow_Top_T", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("topjets.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT < 100", 0);
  }

  ~region_Top_T_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

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
} region_Top_T;

struct region_Top_W_s : public TNMThing
{
  std::string name;
  double total;
  double dtotal;
  TH1F*  hcount;
  bool   done;
  bool   result;
  double weight;

  int    ncuts;

  region_Top_W_s()
    : TNMThing(),
      name("Top_W"),
      total(0),
      dtotal(0),
      hcount(0),
      done(false),
      result(false),
      weight(1),
      ncuts(7)
  {
    hcount = new TH1F("cutflow_Top_W", "", 1, 0, 1);
    hcount->SetCanExtend(1);
    hcount->SetStats(0);
    hcount->Sumw2();

    hcount->Fill("none", 0);
    hcount->Fill("preselection", 0);
    hcount->Fill("leptonsveto.size == 1", 0);
    hcount->Fill("tausveto.size == 0", 0);
    hcount->Fill("bjetsloose.size == 0", 0);
    hcount->Fill("topjetsmasstag_0b.size >= 1", 0);
    hcount->Fill("dphimegajets < 2.8", 0);
    hcount->Fill("MT [] 30 100", 0);
  }

  ~region_Top_W_s() {}

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

    if ( !(leptons_veto.size() == 1) ) return false;
    count("leptons_veto.size == 1");

    if ( !(taus_veto.size() == 0) ) return false;
    count("taus_veto.size == 0");

    if ( !(bjets_loose.size() == 0) ) return false;
    count("bjets_loose.size == 0");

    if ( !(topjets_masstag_0b.size() >= 1) ) return false;
    count("topjets_masstag_0b.size >= 1");

    if ( !(dphimegajets < 2.8) ) return false;
    count("dphimegajets < 2.8");

    if ( !((MT >= 30) &&
		 (MT <= 100)) ) return false;
    count("MT [] 30 100");

    total  += weight;
    dtotal += weight * weight;

    // NB: remember to update result
    result  = true;
    return true;
  }
} region_Top_W;


//------------------------------------------------------------------
analyzer_s::analyzer_s()
{
  // cache pointers to defines
  defines.clear();
  defines.push_back(&R2ll);
  defines.push_back(&METpho);
  defines.push_back(&METl);
  defines.push_back(&R2);
  defines.push_back(&METll);
  defines.push_back(&Mll);
  defines.push_back(&R2l);
  defines.push_back(&MT);
  defines.push_back(&MR);
  defines.push_back(&dphimegajets);

  // cache pointers to filtered objects
  objects.clear();
  objects.push_back(&object_taus_veto);
  objects.push_back(&object_electrons_sel);
  objects.push_back(&object_AK8jets);
  objects.push_back(&object_muons_sel);
  objects.push_back(&object_met);
  objects.push_back(&object_AK4jets);
  objects.push_back(&object_electrons_veto);
  objects.push_back(&object_muons_veto);
  objects.push_back(&object_photons);
  objects.push_back(&object_megajets);
  objects.push_back(&object_bjets_loose);
  objects.push_back(&object_topjets_masstag);
  objects.push_back(&object_bjets_medium);
  objects.push_back(&object_jets_0pho);
  objects.push_back(&object_leptons_veto);
  objects.push_back(&object_leptons_sel);
  objects.push_back(&object_bjets_tight);
  objects.push_back(&object_Wjets_masstag);
  objects.push_back(&object_Wjets_antitag);
  objects.push_back(&object_topjets);
  objects.push_back(&object_topjets_antitag);
  objects.push_back(&object_topjets_masstag_0b);
  objects.push_back(&object_Wjets);

  // cache pointers to regions
  regions.clear();
  regions.push_back(&region_W_L);
  regions.push_back(&region_W_G);
  regions.push_back(&region_W_Z);
  regions.push_back(&region_Top_L);
  regions.push_back(&region_preselection);
  regions.push_back(&region_Top_G);
  regions.push_back(&region_Top_Z);
  regions.push_back(&region_W_T);
  regions.push_back(&region_W_W);
  regions.push_back(&region_W_Q);
  regions.push_back(&region_W_S);
  regions.push_back(&region_Top_Q);
  regions.push_back(&region_Top_S);
  regions.push_back(&region_Top_T);
  regions.push_back(&region_Top_W);
 }

analyzer_s::~analyzer_s() {}

void analyzer_s::run(std::vector<TNMObject>& Tau_,
                     std::vector<TNMObject>& Jet_,
                     std::vector<TNMObject>& Muon_,
                     std::vector<TNMObject>& Photon_,
                     TNMObject& MET_,
                     std::vector<TNMObject>& Electron_,
                     std::vector<TNMObject>& FatJet_)

{
  // copy to internal buffers
  Tau	= Tau_;
  Jet	= Jet_;
  Muon	= Muon_;
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
