//------------------------------------------------------------------
// File: TNMAdapter.cc
// Description: map input objects to TNMObjects
// Created:     Sun May  5 21:48:25 2019 by adl2tnm.py v2.0.0
//------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <stdlib.h>
#include "TString.h"
#include "TNMAdapter.h"

using namespace std;

TNMAdapter::TNMAdapter()
{
}

TNMAdapter::~TNMAdapter()
{
}

void TNMAdapter::operator()(eventBuffer& ev, 
          std::string name, std::vector<TNMObject>& p)
{
  p.clear();

  if ( name == string("Jet") )
    {
      for (size_t c=0; c < ev.Jet_area.size(); c++)
        {
          p.push_back(TNMObject("Jet", 
                                ev.Jet_pt[c], 
                                ev.Jet_eta[c],
                                ev.Jet_phi[c],
                                ev.Jet_mass[c]));
          p.back().Value["btagDeepB"] 	= ev.Jet_btagDeepB[c];
          p.back().Value["eta"] 	= ev.Jet_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.Jet_eta[c]);
          p.back().Value["pt"] 	= ev.Jet_pt[c];
        }
      return;
    }

  if ( name == string("Photon") )
    {
      for (size_t c=0; c < ev.Photon_charge.size(); c++)
        {
          p.push_back(TNMObject("Photon", 
                                ev.Photon_pt[c], 
                                ev.Photon_eta[c],
                                ev.Photon_phi[c],
                                ev.Photon_mass[c]));
          p.back().Value["charge"] 	= ev.Photon_charge[c];
          p.back().Value["eta"] 	= ev.Photon_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.Photon_eta[c]);
          p.back().Value["pt"] 	= ev.Photon_pt[c];
        }
      return;
    }

  if ( name == string("Tau") )
    {
      for (size_t c=0; c < ev.Tau_charge.size(); c++)
        {
          p.push_back(TNMObject("Tau", 
                                ev.Tau_pt[c], 
                                ev.Tau_eta[c],
                                ev.Tau_phi[c],
                                ev.Tau_mass[c]));
          p.back().Value["charge"] 	= ev.Tau_charge[c];
          p.back().Value["dxy"] 	= ev.Tau_dxy[c];
          p.back().Value["|dxy|"] 	= abs(ev.Tau_dxy[c]);
          p.back().Value["dz"] 	= ev.Tau_dz[c];
          p.back().Value["|dz|"] 	= abs(ev.Tau_dz[c]);
          p.back().Value["eta"] 	= ev.Tau_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.Tau_eta[c]);
          p.back().Value["idMVAnewDM2017v2"] 	= ev.Tau_idMVAnewDM2017v2[c];
          p.back().Value["pt"] 	= ev.Tau_pt[c];
        }
      return;
    }

  if ( name == string("Muon") )
    {
      for (size_t c=0; c < ev.Muon_charge.size(); c++)
        {
          p.push_back(TNMObject("Muon", 
                                ev.Muon_pt[c], 
                                ev.Muon_eta[c],
                                ev.Muon_phi[c],
                                ev.Muon_mass[c]));
          p.back().Value["charge"] 	= ev.Muon_charge[c];
          p.back().Value["dxy"] 	= ev.Muon_dxy[c];
          p.back().Value["|dxy|"] 	= abs(ev.Muon_dxy[c]);
          p.back().Value["dz"] 	= ev.Muon_dz[c];
          p.back().Value["|dz|"] 	= abs(ev.Muon_dz[c]);
          p.back().Value["eta"] 	= ev.Muon_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.Muon_eta[c]);
          p.back().Value["miniPFRelIso_all"] 	= ev.Muon_miniPFRelIso_all[c];
          p.back().Value["pt"] 	= ev.Muon_pt[c];
          p.back().Value["softId"] 	= ev.Muon_softId[c];
        }
      return;
    }

  if ( name == string("Electron") )
    {
      for (size_t c=0; c < ev.Electron_charge.size(); c++)
        {
          p.push_back(TNMObject("Electron", 
                                ev.Electron_pt[c], 
                                ev.Electron_eta[c],
                                ev.Electron_phi[c],
                                ev.Electron_mass[c]));
          p.back().Value["charge"] 	= ev.Electron_charge[c];
          p.back().Value["dxy"] 	= ev.Electron_dxy[c];
          p.back().Value["|dxy|"] 	= abs(ev.Electron_dxy[c]);
          p.back().Value["dz"] 	= ev.Electron_dz[c];
          p.back().Value["|dz|"] 	= abs(ev.Electron_dz[c]);
          p.back().Value["eta"] 	= ev.Electron_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.Electron_eta[c]);
          p.back().Value["miniPFRelIso_all"] 	= ev.Electron_miniPFRelIso_all[c];
          p.back().Value["pt"] 	= ev.Electron_pt[c];
        }
      return;
    }

  if ( name == string("FatJet") )
    {
      for (size_t c=0; c < ev.FatJet_area.size(); c++)
        {
          p.push_back(TNMObject("FatJet", 
                                ev.FatJet_pt[c], 
                                ev.FatJet_eta[c],
                                ev.FatJet_phi[c],
                                ev.FatJet_mass[c]));
          p.back().Value["btagDeepB"] 	= ev.FatJet_btagDeepB[c];
          p.back().Value["eta"] 	= ev.FatJet_eta[c];
          p.back().Value["|eta|"] 	= abs(ev.FatJet_eta[c]);
          p.back().Value["msoftdrop"] 	= ev.FatJet_msoftdrop[c];
          p.back().Value["pt"] 	= ev.FatJet_pt[c];
          p.back().Value["tau1"] 	= ev.FatJet_tau1[c];
          p.back().Value["tau2"] 	= ev.FatJet_tau2[c];
          p.back().Value["tau3"] 	= ev.FatJet_tau3[c];
        }
      return;
    }

}

void TNMAdapter::operator()(eventBuffer& ev, 
          std::string name, TNMObject& p)
{

  if ( name == string("MET") )
    {
      TNMObject q("MET", 
                  ev.MET_pt, 
                  0,
                  ev.MET_phi,
                  0);
      q.Value["pt"] 	= ev.MET_pt;

      p = q;
      return;
    }
}
