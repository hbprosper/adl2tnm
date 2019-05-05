//------------------------------------------------------------------
// File: TNMAdapter.cc
// Description: map input objects to TNMObjects
// Created:     Sun May  5 01:01:38 2019 by adl2tnm.py v2.0.0
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
  TString key(name.c_str());
  p.clear();

  if ( key.Contains("Jet") )
    {
      for (size_t c=0; c < ev.Jet_area.size(); c++)
        {
          p.push_back(TNMObject("Jet", 
                                ev.Jet_pt[c], 
                                ev.Jet_eta[c],
                                ev.Jet_phi[c],
                                ev.Jet_mass[c]));
          p.back().Value["area"] 	= ev.Jet_area[c];
          p.back().Value["bReg"] 	= ev.Jet_bReg[c];
          p.back().Value["btagCMVA"] 	= ev.Jet_btagCMVA[c];
          p.back().Value["btagCSVV2"] 	= ev.Jet_btagCSVV2[c];
          p.back().Value["btagDeepB"] 	= ev.Jet_btagDeepB[c];
          p.back().Value["btagDeepC"] 	= ev.Jet_btagDeepC[c];
          p.back().Value["btagDeepFlavB"] 	= ev.Jet_btagDeepFlavB[c];
          p.back().Value["chEmEF"] 	= ev.Jet_chEmEF[c];
          p.back().Value["chHEF"] 	= ev.Jet_chHEF[c];
          p.back().Value["cleanmask"] 	= ev.Jet_cleanmask[c];
          p.back().Value["electronIdx1"] 	= ev.Jet_electronIdx1[c];
          p.back().Value["electronIdx2"] 	= ev.Jet_electronIdx2[c];
          p.back().Value["eta"] 	= ev.Jet_eta[c];
          p.back().Value["genJetIdx"] 	= ev.Jet_genJetIdx[c];
          p.back().Value["hadronFlavour"] 	= ev.Jet_hadronFlavour[c];
          p.back().Value["jetId"] 	= ev.Jet_jetId[c];
          p.back().Value["mass"] 	= ev.Jet_mass[c];
          p.back().Value["muonIdx1"] 	= ev.Jet_muonIdx1[c];
          p.back().Value["muonIdx2"] 	= ev.Jet_muonIdx2[c];
          p.back().Value["nConstituents"] 	= ev.Jet_nConstituents[c];
          p.back().Value["nElectrons"] 	= ev.Jet_nElectrons[c];
          p.back().Value["nMuons"] 	= ev.Jet_nMuons[c];
          p.back().Value["neEmEF"] 	= ev.Jet_neEmEF[c];
          p.back().Value["neHEF"] 	= ev.Jet_neHEF[c];
          p.back().Value["partonFlavour"] 	= ev.Jet_partonFlavour[c];
          p.back().Value["phi"] 	= ev.Jet_phi[c];
          p.back().Value["pt"] 	= ev.Jet_pt[c];
          p.back().Value["puId"] 	= ev.Jet_puId[c];
          p.back().Value["qgl"] 	= ev.Jet_qgl[c];
          p.back().Value["rawFactor"] 	= ev.Jet_rawFactor[c];
        }
      return;
    }

  if ( key.Contains("Photon") )
    {
      for (size_t c=0; c < ev.Photon_charge.size(); c++)
        {
          p.push_back(TNMObject("Photon", 
                                ev.Photon_pt[c], 
                                ev.Photon_eta[c],
                                ev.Photon_phi[c],
                                ev.Photon_mass[c]));
          p.back().Value["charge"] 	= ev.Photon_charge[c];
          p.back().Value["cleanmask"] 	= ev.Photon_cleanmask[c];
          p.back().Value["cutBasedBitmap"] 	= ev.Photon_cutBasedBitmap[c];
          p.back().Value["eCorr"] 	= ev.Photon_eCorr[c];
          p.back().Value["electronIdx"] 	= ev.Photon_electronIdx[c];
          p.back().Value["electronVeto"] 	= ev.Photon_electronVeto[c];
          p.back().Value["energyErr"] 	= ev.Photon_energyErr[c];
          p.back().Value["eta"] 	= ev.Photon_eta[c];
          p.back().Value["genPartFlav"] 	= ev.Photon_genPartFlav[c];
          p.back().Value["genPartIdx"] 	= ev.Photon_genPartIdx[c];
          p.back().Value["hoe"] 	= ev.Photon_hoe[c];
          p.back().Value["isScEtaEB"] 	= ev.Photon_isScEtaEB[c];
          p.back().Value["isScEtaEE"] 	= ev.Photon_isScEtaEE[c];
          p.back().Value["jetIdx"] 	= ev.Photon_jetIdx[c];
          p.back().Value["mass"] 	= ev.Photon_mass[c];
          p.back().Value["mvaID"] 	= ev.Photon_mvaID[c];
          p.back().Value["mvaID_WP80"] 	= ev.Photon_mvaID_WP80[c];
          p.back().Value["mvaID_WP90"] 	= ev.Photon_mvaID_WP90[c];
          p.back().Value["pdgId"] 	= ev.Photon_pdgId[c];
          p.back().Value["pfRelIso03_all"] 	= ev.Photon_pfRelIso03_all[c];
          p.back().Value["pfRelIso03_chg"] 	= ev.Photon_pfRelIso03_chg[c];
          p.back().Value["phi"] 	= ev.Photon_phi[c];
          p.back().Value["pixelSeed"] 	= ev.Photon_pixelSeed[c];
          p.back().Value["pt"] 	= ev.Photon_pt[c];
          p.back().Value["r9"] 	= ev.Photon_r9[c];
          p.back().Value["sieie"] 	= ev.Photon_sieie[c];
          p.back().Value["vidNestedWPBitmap"] 	= ev.Photon_vidNestedWPBitmap[c];
        }
      return;
    }

  if ( key.Contains("GenJetAK8") )
    {
      for (size_t c=0; c < ev.GenJetAK8_eta.size(); c++)
        {
          p.push_back(TNMObject("GenJetAK8", 
                                ev.GenJetAK8_pt[c], 
                                ev.GenJetAK8_eta[c],
                                ev.GenJetAK8_phi[c],
                                ev.GenJetAK8_mass[c]));
          p.back().Value["eta"] 	= ev.GenJetAK8_eta[c];
          p.back().Value["hadronFlavour"] 	= ev.GenJetAK8_hadronFlavour[c];
          p.back().Value["mass"] 	= ev.GenJetAK8_mass[c];
          p.back().Value["partonFlavour"] 	= ev.GenJetAK8_partonFlavour[c];
          p.back().Value["phi"] 	= ev.GenJetAK8_phi[c];
          p.back().Value["pt"] 	= ev.GenJetAK8_pt[c];
        }
      return;
    }

  if ( key.Contains("GenVisTau") )
    {
      for (size_t c=0; c < ev.GenVisTau_charge.size(); c++)
        {
          p.push_back(TNMObject("GenVisTau", 
                                ev.GenVisTau_pt[c], 
                                ev.GenVisTau_eta[c],
                                ev.GenVisTau_phi[c],
                                ev.GenVisTau_mass[c]));
          p.back().Value["charge"] 	= ev.GenVisTau_charge[c];
          p.back().Value["eta"] 	= ev.GenVisTau_eta[c];
          p.back().Value["genPartIdxMother"] 	= ev.GenVisTau_genPartIdxMother[c];
          p.back().Value["mass"] 	= ev.GenVisTau_mass[c];
          p.back().Value["phi"] 	= ev.GenVisTau_phi[c];
          p.back().Value["pt"] 	= ev.GenVisTau_pt[c];
          p.back().Value["status"] 	= ev.GenVisTau_status[c];
        }
      return;
    }

  if ( key.Contains("GenDressedLepton") )
    {
      for (size_t c=0; c < ev.GenDressedLepton_eta.size(); c++)
        {
          p.push_back(TNMObject("GenDressedLepton", 
                                ev.GenDressedLepton_pt[c], 
                                ev.GenDressedLepton_eta[c],
                                ev.GenDressedLepton_phi[c],
                                ev.GenDressedLepton_mass[c]));
          p.back().Value["eta"] 	= ev.GenDressedLepton_eta[c];
          p.back().Value["mass"] 	= ev.GenDressedLepton_mass[c];
          p.back().Value["pdgId"] 	= ev.GenDressedLepton_pdgId[c];
          p.back().Value["phi"] 	= ev.GenDressedLepton_phi[c];
          p.back().Value["pt"] 	= ev.GenDressedLepton_pt[c];
        }
      return;
    }

  if ( key.Contains("LHEPart") )
    {
      for (size_t c=0; c < ev.LHEPart_eta.size(); c++)
        {
          p.push_back(TNMObject("LHEPart", 
                                ev.LHEPart_pt[c], 
                                ev.LHEPart_eta[c],
                                ev.LHEPart_phi[c],
                                ev.LHEPart_mass[c]));
          p.back().Value["eta"] 	= ev.LHEPart_eta[c];
          p.back().Value["mass"] 	= ev.LHEPart_mass[c];
          p.back().Value["pdgId"] 	= ev.LHEPart_pdgId[c];
          p.back().Value["phi"] 	= ev.LHEPart_phi[c];
          p.back().Value["pt"] 	= ev.LHEPart_pt[c];
        }
      return;
    }

  if ( key.Contains("LHEPdfWeight") )
    {
      for (size_t c=0; c < ev.LHEPdfWeight.size(); c++)
        {
          p.push_back(TNMObject("LHEPdfWeight", 
                                0, 
                                0,
                                0,
                                0));
          p.back().Value["LHEPdfWeight"] 	= ev.LHEPdfWeight[c];
        }
      return;
    }

  if ( key.Contains("TrigObj") )
    {
      for (size_t c=0; c < ev.TrigObj_eta.size(); c++)
        {
          p.push_back(TNMObject("TrigObj", 
                                ev.TrigObj_pt[c], 
                                ev.TrigObj_eta[c],
                                ev.TrigObj_phi[c],
                                0));
          p.back().Value["eta"] 	= ev.TrigObj_eta[c];
          p.back().Value["filterBits"] 	= ev.TrigObj_filterBits[c];
          p.back().Value["id"] 	= ev.TrigObj_id[c];
          p.back().Value["l1charge"] 	= ev.TrigObj_l1charge[c];
          p.back().Value["l1iso"] 	= ev.TrigObj_l1iso[c];
          p.back().Value["l1pt"] 	= ev.TrigObj_l1pt[c];
          p.back().Value["l1pt_2"] 	= ev.TrigObj_l1pt_2[c];
          p.back().Value["l2pt"] 	= ev.TrigObj_l2pt[c];
          p.back().Value["phi"] 	= ev.TrigObj_phi[c];
          p.back().Value["pt"] 	= ev.TrigObj_pt[c];
        }
      return;
    }

  if ( key.Contains("IsoTrack") )
    {
      for (size_t c=0; c < ev.IsoTrack_dxy.size(); c++)
        {
          p.push_back(TNMObject("IsoTrack", 
                                ev.IsoTrack_pt[c], 
                                ev.IsoTrack_eta[c],
                                ev.IsoTrack_phi[c],
                                0));
          p.back().Value["dxy"] 	= ev.IsoTrack_dxy[c];
          p.back().Value["dz"] 	= ev.IsoTrack_dz[c];
          p.back().Value["eta"] 	= ev.IsoTrack_eta[c];
          p.back().Value["isHighPurityTrack"] 	= ev.IsoTrack_isHighPurityTrack[c];
          p.back().Value["isPFcand"] 	= ev.IsoTrack_isPFcand[c];
          p.back().Value["miniPFRelIso_all"] 	= ev.IsoTrack_miniPFRelIso_all[c];
          p.back().Value["miniPFRelIso_chg"] 	= ev.IsoTrack_miniPFRelIso_chg[c];
          p.back().Value["pdgId"] 	= ev.IsoTrack_pdgId[c];
          p.back().Value["pfRelIso03_all"] 	= ev.IsoTrack_pfRelIso03_all[c];
          p.back().Value["pfRelIso03_chg"] 	= ev.IsoTrack_pfRelIso03_chg[c];
          p.back().Value["phi"] 	= ev.IsoTrack_phi[c];
          p.back().Value["pt"] 	= ev.IsoTrack_pt[c];
        }
      return;
    }

  if ( key.Contains("GenJet") )
    {
      for (size_t c=0; c < ev.GenJet_eta.size(); c++)
        {
          p.push_back(TNMObject("GenJet", 
                                ev.GenJet_pt[c], 
                                ev.GenJet_eta[c],
                                ev.GenJet_phi[c],
                                ev.GenJet_mass[c]));
          p.back().Value["eta"] 	= ev.GenJet_eta[c];
          p.back().Value["hadronFlavour"] 	= ev.GenJet_hadronFlavour[c];
          p.back().Value["mass"] 	= ev.GenJet_mass[c];
          p.back().Value["partonFlavour"] 	= ev.GenJet_partonFlavour[c];
          p.back().Value["phi"] 	= ev.GenJet_phi[c];
          p.back().Value["pt"] 	= ev.GenJet_pt[c];
        }
      return;
    }

  if ( key.Contains("SoftActivityJet") )
    {
      for (size_t c=0; c < ev.SoftActivityJet_eta.size(); c++)
        {
          p.push_back(TNMObject("SoftActivityJet", 
                                ev.SoftActivityJet_pt[c], 
                                ev.SoftActivityJet_eta[c],
                                ev.SoftActivityJet_phi[c],
                                0));
          p.back().Value["eta"] 	= ev.SoftActivityJet_eta[c];
          p.back().Value["phi"] 	= ev.SoftActivityJet_phi[c];
          p.back().Value["pt"] 	= ev.SoftActivityJet_pt[c];
        }
      return;
    }

  if ( key.Contains("GenPart") )
    {
      for (size_t c=0; c < ev.GenPart_eta.size(); c++)
        {
          p.push_back(TNMObject("GenPart", 
                                ev.GenPart_pt[c], 
                                ev.GenPart_eta[c],
                                ev.GenPart_phi[c],
                                ev.GenPart_mass[c]));
          p.back().Value["eta"] 	= ev.GenPart_eta[c];
          p.back().Value["genPartIdxMother"] 	= ev.GenPart_genPartIdxMother[c];
          p.back().Value["mass"] 	= ev.GenPart_mass[c];
          p.back().Value["pdgId"] 	= ev.GenPart_pdgId[c];
          p.back().Value["phi"] 	= ev.GenPart_phi[c];
          p.back().Value["pt"] 	= ev.GenPart_pt[c];
          p.back().Value["status"] 	= ev.GenPart_status[c];
          p.back().Value["statusFlags"] 	= ev.GenPart_statusFlags[c];
        }
      return;
    }

  if ( key.Contains("Tau") )
    {
      for (size_t c=0; c < ev.Tau_charge.size(); c++)
        {
          p.push_back(TNMObject("Tau", 
                                ev.Tau_pt[c], 
                                ev.Tau_eta[c],
                                ev.Tau_phi[c],
                                ev.Tau_mass[c]));
          p.back().Value["charge"] 	= ev.Tau_charge[c];
          p.back().Value["chargedIso"] 	= ev.Tau_chargedIso[c];
          p.back().Value["cleanmask"] 	= ev.Tau_cleanmask[c];
          p.back().Value["decayMode"] 	= ev.Tau_decayMode[c];
          p.back().Value["dxy"] 	= ev.Tau_dxy[c];
          p.back().Value["dz"] 	= ev.Tau_dz[c];
          p.back().Value["eta"] 	= ev.Tau_eta[c];
          p.back().Value["genPartFlav"] 	= ev.Tau_genPartFlav[c];
          p.back().Value["genPartIdx"] 	= ev.Tau_genPartIdx[c];
          p.back().Value["idAntiEle"] 	= ev.Tau_idAntiEle[c];
          p.back().Value["idAntiMu"] 	= ev.Tau_idAntiMu[c];
          p.back().Value["idDecayMode"] 	= ev.Tau_idDecayMode[c];
          p.back().Value["idDecayModeNewDMs"] 	= ev.Tau_idDecayModeNewDMs[c];
          p.back().Value["idMVAnewDM2017v2"] 	= ev.Tau_idMVAnewDM2017v2[c];
          p.back().Value["idMVAoldDM"] 	= ev.Tau_idMVAoldDM[c];
          p.back().Value["idMVAoldDM2017v1"] 	= ev.Tau_idMVAoldDM2017v1[c];
          p.back().Value["idMVAoldDM2017v2"] 	= ev.Tau_idMVAoldDM2017v2[c];
          p.back().Value["idMVAoldDMdR032017v2"] 	= ev.Tau_idMVAoldDMdR032017v2[c];
          p.back().Value["jetIdx"] 	= ev.Tau_jetIdx[c];
          p.back().Value["leadTkDeltaEta"] 	= ev.Tau_leadTkDeltaEta[c];
          p.back().Value["leadTkDeltaPhi"] 	= ev.Tau_leadTkDeltaPhi[c];
          p.back().Value["leadTkPtOverTauPt"] 	= ev.Tau_leadTkPtOverTauPt[c];
          p.back().Value["mass"] 	= ev.Tau_mass[c];
          p.back().Value["neutralIso"] 	= ev.Tau_neutralIso[c];
          p.back().Value["phi"] 	= ev.Tau_phi[c];
          p.back().Value["photonsOutsideSignalCone"] 	= ev.Tau_photonsOutsideSignalCone[c];
          p.back().Value["pt"] 	= ev.Tau_pt[c];
          p.back().Value["puCorr"] 	= ev.Tau_puCorr[c];
          p.back().Value["rawAntiEle"] 	= ev.Tau_rawAntiEle[c];
          p.back().Value["rawAntiEleCat"] 	= ev.Tau_rawAntiEleCat[c];
          p.back().Value["rawIso"] 	= ev.Tau_rawIso[c];
          p.back().Value["rawIsodR03"] 	= ev.Tau_rawIsodR03[c];
          p.back().Value["rawMVAnewDM2017v2"] 	= ev.Tau_rawMVAnewDM2017v2[c];
          p.back().Value["rawMVAoldDM"] 	= ev.Tau_rawMVAoldDM[c];
          p.back().Value["rawMVAoldDM2017v1"] 	= ev.Tau_rawMVAoldDM2017v1[c];
          p.back().Value["rawMVAoldDM2017v2"] 	= ev.Tau_rawMVAoldDM2017v2[c];
          p.back().Value["rawMVAoldDMdR032017v2"] 	= ev.Tau_rawMVAoldDMdR032017v2[c];
        }
      return;
    }

  if ( key.Contains("LHEScaleWeight") )
    {
      for (size_t c=0; c < ev.LHEScaleWeight.size(); c++)
        {
          p.push_back(TNMObject("LHEScaleWeight", 
                                0, 
                                0,
                                0,
                                0));
          p.back().Value["LHEScaleWeight"] 	= ev.LHEScaleWeight[c];
        }
      return;
    }

  if ( key.Contains("Muon") )
    {
      for (size_t c=0; c < ev.Muon_charge.size(); c++)
        {
          p.push_back(TNMObject("Muon", 
                                ev.Muon_pt[c], 
                                ev.Muon_eta[c],
                                ev.Muon_phi[c],
                                ev.Muon_mass[c]));
          p.back().Value["charge"] 	= ev.Muon_charge[c];
          p.back().Value["cleanmask"] 	= ev.Muon_cleanmask[c];
          p.back().Value["dxy"] 	= ev.Muon_dxy[c];
          p.back().Value["dxyErr"] 	= ev.Muon_dxyErr[c];
          p.back().Value["dz"] 	= ev.Muon_dz[c];
          p.back().Value["dzErr"] 	= ev.Muon_dzErr[c];
          p.back().Value["eta"] 	= ev.Muon_eta[c];
          p.back().Value["genPartFlav"] 	= ev.Muon_genPartFlav[c];
          p.back().Value["genPartIdx"] 	= ev.Muon_genPartIdx[c];
          p.back().Value["highPtId"] 	= ev.Muon_highPtId[c];
          p.back().Value["ip3d"] 	= ev.Muon_ip3d[c];
          p.back().Value["isPFcand"] 	= ev.Muon_isPFcand[c];
          p.back().Value["jetIdx"] 	= ev.Muon_jetIdx[c];
          p.back().Value["mass"] 	= ev.Muon_mass[c];
          p.back().Value["mediumId"] 	= ev.Muon_mediumId[c];
          p.back().Value["miniPFRelIso_all"] 	= ev.Muon_miniPFRelIso_all[c];
          p.back().Value["miniPFRelIso_chg"] 	= ev.Muon_miniPFRelIso_chg[c];
          p.back().Value["mvaTTH"] 	= ev.Muon_mvaTTH[c];
          p.back().Value["nStations"] 	= ev.Muon_nStations[c];
          p.back().Value["nTrackerLayers"] 	= ev.Muon_nTrackerLayers[c];
          p.back().Value["pdgId"] 	= ev.Muon_pdgId[c];
          p.back().Value["pfRelIso03_all"] 	= ev.Muon_pfRelIso03_all[c];
          p.back().Value["pfRelIso03_chg"] 	= ev.Muon_pfRelIso03_chg[c];
          p.back().Value["pfRelIso04_all"] 	= ev.Muon_pfRelIso04_all[c];
          p.back().Value["phi"] 	= ev.Muon_phi[c];
          p.back().Value["pt"] 	= ev.Muon_pt[c];
          p.back().Value["ptErr"] 	= ev.Muon_ptErr[c];
          p.back().Value["segmentComp"] 	= ev.Muon_segmentComp[c];
          p.back().Value["sip3d"] 	= ev.Muon_sip3d[c];
          p.back().Value["softId"] 	= ev.Muon_softId[c];
          p.back().Value["tightCharge"] 	= ev.Muon_tightCharge[c];
          p.back().Value["tightId"] 	= ev.Muon_tightId[c];
        }
      return;
    }

  if ( key.Contains("OtherPV") )
    {
      for (size_t c=0; c < ev.OtherPV_z.size(); c++)
        {
          p.push_back(TNMObject("OtherPV", 
                                0, 
                                0,
                                0,
                                0));
          p.back().Value["z"] 	= ev.OtherPV_z[c];
        }
      return;
    }

  if ( key.Contains("SV") )
    {
      for (size_t c=0; c < ev.SV_chi2.size(); c++)
        {
          p.push_back(TNMObject("SV", 
                                ev.SV_pt[c], 
                                ev.SV_eta[c],
                                ev.SV_phi[c],
                                ev.SV_mass[c]));
          p.back().Value["chi2"] 	= ev.SV_chi2[c];
          p.back().Value["dlen"] 	= ev.SV_dlen[c];
          p.back().Value["dlenSig"] 	= ev.SV_dlenSig[c];
          p.back().Value["eta"] 	= ev.SV_eta[c];
          p.back().Value["mass"] 	= ev.SV_mass[c];
          p.back().Value["ndof"] 	= ev.SV_ndof[c];
          p.back().Value["pAngle"] 	= ev.SV_pAngle[c];
          p.back().Value["phi"] 	= ev.SV_phi[c];
          p.back().Value["pt"] 	= ev.SV_pt[c];
          p.back().Value["x"] 	= ev.SV_x[c];
          p.back().Value["y"] 	= ev.SV_y[c];
          p.back().Value["z"] 	= ev.SV_z[c];
        }
      return;
    }

  if ( key.Contains("Electron") )
    {
      for (size_t c=0; c < ev.Electron_charge.size(); c++)
        {
          p.push_back(TNMObject("Electron", 
                                ev.Electron_pt[c], 
                                ev.Electron_eta[c],
                                ev.Electron_phi[c],
                                ev.Electron_mass[c]));
          p.back().Value["charge"] 	= ev.Electron_charge[c];
          p.back().Value["cleanmask"] 	= ev.Electron_cleanmask[c];
          p.back().Value["convVeto"] 	= ev.Electron_convVeto[c];
          p.back().Value["cutBased"] 	= ev.Electron_cutBased[c];
          p.back().Value["cutBased_HEEP"] 	= ev.Electron_cutBased_HEEP[c];
          p.back().Value["deltaEtaSC"] 	= ev.Electron_deltaEtaSC[c];
          p.back().Value["dr03EcalRecHitSumEt"] 	= ev.Electron_dr03EcalRecHitSumEt[c];
          p.back().Value["dr03HcalDepth1TowerSumEt"] 	= ev.Electron_dr03HcalDepth1TowerSumEt[c];
          p.back().Value["dr03TkSumPt"] 	= ev.Electron_dr03TkSumPt[c];
          p.back().Value["dxy"] 	= ev.Electron_dxy[c];
          p.back().Value["dxyErr"] 	= ev.Electron_dxyErr[c];
          p.back().Value["dz"] 	= ev.Electron_dz[c];
          p.back().Value["dzErr"] 	= ev.Electron_dzErr[c];
          p.back().Value["eCorr"] 	= ev.Electron_eCorr[c];
          p.back().Value["eInvMinusPInv"] 	= ev.Electron_eInvMinusPInv[c];
          p.back().Value["energyErr"] 	= ev.Electron_energyErr[c];
          p.back().Value["eta"] 	= ev.Electron_eta[c];
          p.back().Value["genPartFlav"] 	= ev.Electron_genPartFlav[c];
          p.back().Value["genPartIdx"] 	= ev.Electron_genPartIdx[c];
          p.back().Value["hoe"] 	= ev.Electron_hoe[c];
          p.back().Value["ip3d"] 	= ev.Electron_ip3d[c];
          p.back().Value["isPFcand"] 	= ev.Electron_isPFcand[c];
          p.back().Value["jetIdx"] 	= ev.Electron_jetIdx[c];
          p.back().Value["lostHits"] 	= ev.Electron_lostHits[c];
          p.back().Value["mass"] 	= ev.Electron_mass[c];
          p.back().Value["miniPFRelIso_all"] 	= ev.Electron_miniPFRelIso_all[c];
          p.back().Value["miniPFRelIso_chg"] 	= ev.Electron_miniPFRelIso_chg[c];
          p.back().Value["mvaFall17Iso"] 	= ev.Electron_mvaFall17Iso[c];
          p.back().Value["mvaFall17Iso_WP80"] 	= ev.Electron_mvaFall17Iso_WP80[c];
          p.back().Value["mvaFall17Iso_WP90"] 	= ev.Electron_mvaFall17Iso_WP90[c];
          p.back().Value["mvaFall17Iso_WPL"] 	= ev.Electron_mvaFall17Iso_WPL[c];
          p.back().Value["mvaFall17noIso"] 	= ev.Electron_mvaFall17noIso[c];
          p.back().Value["mvaFall17noIso_WP80"] 	= ev.Electron_mvaFall17noIso_WP80[c];
          p.back().Value["mvaFall17noIso_WP90"] 	= ev.Electron_mvaFall17noIso_WP90[c];
          p.back().Value["mvaFall17noIso_WPL"] 	= ev.Electron_mvaFall17noIso_WPL[c];
          p.back().Value["mvaTTH"] 	= ev.Electron_mvaTTH[c];
          p.back().Value["pdgId"] 	= ev.Electron_pdgId[c];
          p.back().Value["pfRelIso03_all"] 	= ev.Electron_pfRelIso03_all[c];
          p.back().Value["pfRelIso03_chg"] 	= ev.Electron_pfRelIso03_chg[c];
          p.back().Value["phi"] 	= ev.Electron_phi[c];
          p.back().Value["photonIdx"] 	= ev.Electron_photonIdx[c];
          p.back().Value["pt"] 	= ev.Electron_pt[c];
          p.back().Value["r9"] 	= ev.Electron_r9[c];
          p.back().Value["sieie"] 	= ev.Electron_sieie[c];
          p.back().Value["sip3d"] 	= ev.Electron_sip3d[c];
          p.back().Value["tightCharge"] 	= ev.Electron_tightCharge[c];
          p.back().Value["vidNestedWPBitmap"] 	= ev.Electron_vidNestedWPBitmap[c];
        }
      return;
    }

  if ( key.Contains("FatJet") )
    {
      for (size_t c=0; c < ev.FatJet_area.size(); c++)
        {
          p.push_back(TNMObject("FatJet", 
                                ev.FatJet_pt[c], 
                                ev.FatJet_eta[c],
                                ev.FatJet_phi[c],
                                ev.FatJet_mass[c]));
          p.back().Value["area"] 	= ev.FatJet_area[c];
          p.back().Value["btagCMVA"] 	= ev.FatJet_btagCMVA[c];
          p.back().Value["btagCSVV2"] 	= ev.FatJet_btagCSVV2[c];
          p.back().Value["btagDeepB"] 	= ev.FatJet_btagDeepB[c];
          p.back().Value["btagHbb"] 	= ev.FatJet_btagHbb[c];
          p.back().Value["eta"] 	= ev.FatJet_eta[c];
          p.back().Value["jetId"] 	= ev.FatJet_jetId[c];
          p.back().Value["mass"] 	= ev.FatJet_mass[c];
          p.back().Value["msoftdrop"] 	= ev.FatJet_msoftdrop[c];
          p.back().Value["n2b1"] 	= ev.FatJet_n2b1[c];
          p.back().Value["n3b1"] 	= ev.FatJet_n3b1[c];
          p.back().Value["phi"] 	= ev.FatJet_phi[c];
          p.back().Value["pt"] 	= ev.FatJet_pt[c];
          p.back().Value["subJetIdx1"] 	= ev.FatJet_subJetIdx1[c];
          p.back().Value["subJetIdx2"] 	= ev.FatJet_subJetIdx2[c];
          p.back().Value["tau1"] 	= ev.FatJet_tau1[c];
          p.back().Value["tau2"] 	= ev.FatJet_tau2[c];
          p.back().Value["tau3"] 	= ev.FatJet_tau3[c];
          p.back().Value["tau4"] 	= ev.FatJet_tau4[c];
        }
      return;
    }

  if ( key.Contains("SubJet") )
    {
      for (size_t c=0; c < ev.SubJet_btagCMVA.size(); c++)
        {
          p.push_back(TNMObject("SubJet", 
                                ev.SubJet_pt[c], 
                                ev.SubJet_eta[c],
                                ev.SubJet_phi[c],
                                ev.SubJet_mass[c]));
          p.back().Value["btagCMVA"] 	= ev.SubJet_btagCMVA[c];
          p.back().Value["btagCSVV2"] 	= ev.SubJet_btagCSVV2[c];
          p.back().Value["btagDeepB"] 	= ev.SubJet_btagDeepB[c];
          p.back().Value["eta"] 	= ev.SubJet_eta[c];
          p.back().Value["mass"] 	= ev.SubJet_mass[c];
          p.back().Value["n2b1"] 	= ev.SubJet_n2b1[c];
          p.back().Value["n3b1"] 	= ev.SubJet_n3b1[c];
          p.back().Value["phi"] 	= ev.SubJet_phi[c];
          p.back().Value["pt"] 	= ev.SubJet_pt[c];
          p.back().Value["tau1"] 	= ev.SubJet_tau1[c];
          p.back().Value["tau2"] 	= ev.SubJet_tau2[c];
          p.back().Value["tau3"] 	= ev.SubJet_tau3[c];
          p.back().Value["tau4"] 	= ev.SubJet_tau4[c];
        }
      return;
    }

  if ( key.Contains("SubGenJetAK8") )
    {
      for (size_t c=0; c < ev.SubGenJetAK8_eta.size(); c++)
        {
          p.push_back(TNMObject("SubGenJetAK8", 
                                ev.SubGenJetAK8_pt[c], 
                                ev.SubGenJetAK8_eta[c],
                                ev.SubGenJetAK8_phi[c],
                                ev.SubGenJetAK8_mass[c]));
          p.back().Value["eta"] 	= ev.SubGenJetAK8_eta[c];
          p.back().Value["mass"] 	= ev.SubGenJetAK8_mass[c];
          p.back().Value["phi"] 	= ev.SubGenJetAK8_phi[c];
          p.back().Value["pt"] 	= ev.SubGenJetAK8_pt[c];
        }
      return;
    }

}

void TNMAdapter::operator()(eventBuffer& ev, 
      std::string name, TNMObject& p)
{
  TString key(name.c_str());

  if ( key.Contains("CaloMET") )
    {
      TNMObject q("CaloMET", 
                  ev.CaloMET_pt, 
                  0,
                  ev.CaloMET_phi,
                  0);
      q.Value["phi"] 	= ev.CaloMET_phi;
      q.Value["pt"] 	= ev.CaloMET_pt;
      q.Value["sumEt"] 	= ev.CaloMET_sumEt;

      p = q;
      return;
    }
  if ( key.Contains("PV") )
    {
      TNMObject q("PV", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["chi2"] 	= ev.PV_chi2;
      q.Value["ndof"] 	= ev.PV_ndof;
      q.Value["npvs"] 	= ev.PV_npvs;
      q.Value["npvsGood"] 	= ev.PV_npvsGood;
      q.Value["score"] 	= ev.PV_score;
      q.Value["x"] 	= ev.PV_x;
      q.Value["y"] 	= ev.PV_y;
      q.Value["z"] 	= ev.PV_z;

      p = q;
      return;
    }
  if ( key.Contains("Generator") )
    {
      TNMObject q("Generator", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["binvar"] 	= ev.Generator_binvar;
      q.Value["id1"] 	= ev.Generator_id1;
      q.Value["id2"] 	= ev.Generator_id2;
      q.Value["scalePDF"] 	= ev.Generator_scalePDF;
      q.Value["weight"] 	= ev.Generator_weight;
      q.Value["x1"] 	= ev.Generator_x1;
      q.Value["x2"] 	= ev.Generator_x2;
      q.Value["xpdf1"] 	= ev.Generator_xpdf1;
      q.Value["xpdf2"] 	= ev.Generator_xpdf2;

      p = q;
      return;
    }
  if ( key.Contains("RawMET") )
    {
      TNMObject q("RawMET", 
                  ev.RawMET_pt, 
                  0,
                  ev.RawMET_phi,
                  0);
      q.Value["phi"] 	= ev.RawMET_phi;
      q.Value["pt"] 	= ev.RawMET_pt;
      q.Value["sumEt"] 	= ev.RawMET_sumEt;

      p = q;
      return;
    }
  if ( key.Contains("Flag") )
    {
      TNMObject q("Flag", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["BadChargedCandidateFilter"] 	= ev.Flag_BadChargedCandidateFilter;
      q.Value["BadChargedCandidateSummer16Filter"] 	= ev.Flag_BadChargedCandidateSummer16Filter;
      q.Value["BadPFMuonFilter"] 	= ev.Flag_BadPFMuonFilter;
      q.Value["BadPFMuonSummer16Filter"] 	= ev.Flag_BadPFMuonSummer16Filter;
      q.Value["CSCTightHalo2015Filter"] 	= ev.Flag_CSCTightHalo2015Filter;
      q.Value["CSCTightHaloFilter"] 	= ev.Flag_CSCTightHaloFilter;
      q.Value["CSCTightHaloTrkMuUnvetoFilter"] 	= ev.Flag_CSCTightHaloTrkMuUnvetoFilter;
      q.Value["EcalDeadCellBoundaryEnergyFilter"] 	= ev.Flag_EcalDeadCellBoundaryEnergyFilter;
      q.Value["EcalDeadCellTriggerPrimitiveFilter"] 	= ev.Flag_EcalDeadCellTriggerPrimitiveFilter;
      q.Value["HBHENoiseFilter"] 	= ev.Flag_HBHENoiseFilter;
      q.Value["HBHENoiseIsoFilter"] 	= ev.Flag_HBHENoiseIsoFilter;
      q.Value["HcalStripHaloFilter"] 	= ev.Flag_HcalStripHaloFilter;
      q.Value["METFilters"] 	= ev.Flag_METFilters;
      q.Value["chargedHadronTrackResolutionFilter"] 	= ev.Flag_chargedHadronTrackResolutionFilter;
      q.Value["ecalBadCalibFilter"] 	= ev.Flag_ecalBadCalibFilter;
      q.Value["ecalLaserCorrFilter"] 	= ev.Flag_ecalLaserCorrFilter;
      q.Value["eeBadScFilter"] 	= ev.Flag_eeBadScFilter;
      q.Value["globalSuperTightHalo2016Filter"] 	= ev.Flag_globalSuperTightHalo2016Filter;
      q.Value["globalTightHalo2016Filter"] 	= ev.Flag_globalTightHalo2016Filter;
      q.Value["goodVertices"] 	= ev.Flag_goodVertices;
      q.Value["hcalLaserEventFilter"] 	= ev.Flag_hcalLaserEventFilter;
      q.Value["muonBadTrackFilter"] 	= ev.Flag_muonBadTrackFilter;
      q.Value["trkPOGFilters"] 	= ev.Flag_trkPOGFilters;
      q.Value["trkPOG_logErrorTooManyClusters"] 	= ev.Flag_trkPOG_logErrorTooManyClusters;
      q.Value["trkPOG_manystripclus53X"] 	= ev.Flag_trkPOG_manystripclus53X;
      q.Value["trkPOG_toomanystripclus53X"] 	= ev.Flag_trkPOG_toomanystripclus53X;

      p = q;
      return;
    }
  if ( key.Contains("L1simulation") )
    {
      TNMObject q("L1simulation", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["step"] 	= ev.L1simulation_step;

      p = q;
      return;
    }
  if ( key.Contains("LHE") )
    {
      TNMObject q("LHE", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["HT"] 	= ev.LHE_HT;
      q.Value["HTIncoming"] 	= ev.LHE_HTIncoming;
      q.Value["Nb"] 	= ev.LHE_Nb;
      q.Value["Nc"] 	= ev.LHE_Nc;
      q.Value["Nglu"] 	= ev.LHE_Nglu;
      q.Value["Njets"] 	= ev.LHE_Njets;
      q.Value["NpLO"] 	= ev.LHE_NpLO;
      q.Value["NpNLO"] 	= ev.LHE_NpNLO;
      q.Value["Nuds"] 	= ev.LHE_Nuds;
      q.Value["Vpt"] 	= ev.LHE_Vpt;

      p = q;
      return;
    }
  if ( key.Contains("TkMET") )
    {
      TNMObject q("TkMET", 
                  ev.TkMET_pt, 
                  0,
                  ev.TkMET_phi,
                  0);
      q.Value["phi"] 	= ev.TkMET_phi;
      q.Value["pt"] 	= ev.TkMET_pt;
      q.Value["sumEt"] 	= ev.TkMET_sumEt;

      p = q;
      return;
    }
  if ( key.Contains("PuppiMET") )
    {
      TNMObject q("PuppiMET", 
                  ev.PuppiMET_pt, 
                  0,
                  ev.PuppiMET_phi,
                  0);
      q.Value["phi"] 	= ev.PuppiMET_phi;
      q.Value["pt"] 	= ev.PuppiMET_pt;
      q.Value["sumEt"] 	= ev.PuppiMET_sumEt;

      p = q;
      return;
    }
  if ( key.Contains("HLT") )
    {
      TNMObject q("HLT", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["AK4CaloJet100"] 	= ev.HLT_AK4CaloJet100;
      q.Value["AK4CaloJet120"] 	= ev.HLT_AK4CaloJet120;
      q.Value["AK4CaloJet30"] 	= ev.HLT_AK4CaloJet30;
      q.Value["AK4CaloJet40"] 	= ev.HLT_AK4CaloJet40;
      q.Value["AK4CaloJet50"] 	= ev.HLT_AK4CaloJet50;
      q.Value["AK4CaloJet80"] 	= ev.HLT_AK4CaloJet80;
      q.Value["AK4PFJet100"] 	= ev.HLT_AK4PFJet100;
      q.Value["AK4PFJet120"] 	= ev.HLT_AK4PFJet120;
      q.Value["AK4PFJet30"] 	= ev.HLT_AK4PFJet30;
      q.Value["AK4PFJet50"] 	= ev.HLT_AK4PFJet50;
      q.Value["AK4PFJet80"] 	= ev.HLT_AK4PFJet80;
      q.Value["AK8PFHT750_TrimMass50"] 	= ev.HLT_AK8PFHT750_TrimMass50;
      q.Value["AK8PFHT800_TrimMass50"] 	= ev.HLT_AK8PFHT800_TrimMass50;
      q.Value["AK8PFHT850_TrimMass50"] 	= ev.HLT_AK8PFHT850_TrimMass50;
      q.Value["AK8PFHT900_TrimMass50"] 	= ev.HLT_AK8PFHT900_TrimMass50;
      q.Value["AK8PFJet140"] 	= ev.HLT_AK8PFJet140;
      q.Value["AK8PFJet200"] 	= ev.HLT_AK8PFJet200;
      q.Value["AK8PFJet260"] 	= ev.HLT_AK8PFJet260;
      q.Value["AK8PFJet320"] 	= ev.HLT_AK8PFJet320;
      q.Value["AK8PFJet330_PFAK8BTagCSV_p1"] 	= ev.HLT_AK8PFJet330_PFAK8BTagCSV_p1;
      q.Value["AK8PFJet330_PFAK8BTagCSV_p17"] 	= ev.HLT_AK8PFJet330_PFAK8BTagCSV_p17;
      q.Value["AK8PFJet360_TrimMass30"] 	= ev.HLT_AK8PFJet360_TrimMass30;
      q.Value["AK8PFJet380_TrimMass30"] 	= ev.HLT_AK8PFJet380_TrimMass30;
      q.Value["AK8PFJet40"] 	= ev.HLT_AK8PFJet40;
      q.Value["AK8PFJet400"] 	= ev.HLT_AK8PFJet400;
      q.Value["AK8PFJet400_TrimMass30"] 	= ev.HLT_AK8PFJet400_TrimMass30;
      q.Value["AK8PFJet420_TrimMass30"] 	= ev.HLT_AK8PFJet420_TrimMass30;
      q.Value["AK8PFJet450"] 	= ev.HLT_AK8PFJet450;
      q.Value["AK8PFJet500"] 	= ev.HLT_AK8PFJet500;
      q.Value["AK8PFJet550"] 	= ev.HLT_AK8PFJet550;
      q.Value["AK8PFJet60"] 	= ev.HLT_AK8PFJet60;
      q.Value["AK8PFJet80"] 	= ev.HLT_AK8PFJet80;
      q.Value["AK8PFJetFwd140"] 	= ev.HLT_AK8PFJetFwd140;
      q.Value["AK8PFJetFwd200"] 	= ev.HLT_AK8PFJetFwd200;
      q.Value["AK8PFJetFwd260"] 	= ev.HLT_AK8PFJetFwd260;
      q.Value["AK8PFJetFwd320"] 	= ev.HLT_AK8PFJetFwd320;
      q.Value["AK8PFJetFwd40"] 	= ev.HLT_AK8PFJetFwd40;
      q.Value["AK8PFJetFwd400"] 	= ev.HLT_AK8PFJetFwd400;
      q.Value["AK8PFJetFwd450"] 	= ev.HLT_AK8PFJetFwd450;
      q.Value["AK8PFJetFwd500"] 	= ev.HLT_AK8PFJetFwd500;
      q.Value["AK8PFJetFwd60"] 	= ev.HLT_AK8PFJetFwd60;
      q.Value["AK8PFJetFwd80"] 	= ev.HLT_AK8PFJetFwd80;
      q.Value["BTagMu_AK4DiJet110_Mu5"] 	= ev.HLT_BTagMu_AK4DiJet110_Mu5;
      q.Value["BTagMu_AK4DiJet170_Mu5"] 	= ev.HLT_BTagMu_AK4DiJet170_Mu5;
      q.Value["BTagMu_AK4DiJet20_Mu5"] 	= ev.HLT_BTagMu_AK4DiJet20_Mu5;
      q.Value["BTagMu_AK4DiJet40_Mu5"] 	= ev.HLT_BTagMu_AK4DiJet40_Mu5;
      q.Value["BTagMu_AK4DiJet70_Mu5"] 	= ev.HLT_BTagMu_AK4DiJet70_Mu5;
      q.Value["BTagMu_AK4Jet300_Mu5"] 	= ev.HLT_BTagMu_AK4Jet300_Mu5;
      q.Value["BTagMu_AK8DiJet170_Mu5"] 	= ev.HLT_BTagMu_AK8DiJet170_Mu5;
      q.Value["BTagMu_AK8Jet300_Mu5"] 	= ev.HLT_BTagMu_AK8Jet300_Mu5;
      q.Value["CaloJet500_NoJetID"] 	= ev.HLT_CaloJet500_NoJetID;
      q.Value["CaloJet550_NoJetID"] 	= ev.HLT_CaloJet550_NoJetID;
      q.Value["CaloMET100_HBHECleaned"] 	= ev.HLT_CaloMET100_HBHECleaned;
      q.Value["CaloMET100_NotCleaned"] 	= ev.HLT_CaloMET100_NotCleaned;
      q.Value["CaloMET110_NotCleaned"] 	= ev.HLT_CaloMET110_NotCleaned;
      q.Value["CaloMET250_HBHECleaned"] 	= ev.HLT_CaloMET250_HBHECleaned;
      q.Value["CaloMET250_NotCleaned"] 	= ev.HLT_CaloMET250_NotCleaned;
      q.Value["CaloMET300_HBHECleaned"] 	= ev.HLT_CaloMET300_HBHECleaned;
      q.Value["CaloMET350_HBHECleaned"] 	= ev.HLT_CaloMET350_HBHECleaned;
      q.Value["CaloMET70_HBHECleaned"] 	= ev.HLT_CaloMET70_HBHECleaned;
      q.Value["CaloMET80_HBHECleaned"] 	= ev.HLT_CaloMET80_HBHECleaned;
      q.Value["CaloMET80_NotCleaned"] 	= ev.HLT_CaloMET80_NotCleaned;
      q.Value["CaloMET90_HBHECleaned"] 	= ev.HLT_CaloMET90_HBHECleaned;
      q.Value["CaloMET90_NotCleaned"] 	= ev.HLT_CaloMET90_NotCleaned;
      q.Value["CaloMHT90"] 	= ev.HLT_CaloMHT90;
      q.Value["DiEle27_WPTightCaloOnly_L1DoubleEG"] 	= ev.HLT_DiEle27_WPTightCaloOnly_L1DoubleEG;
      q.Value["DiJet110_35_Mjj650_PFMET110"] 	= ev.HLT_DiJet110_35_Mjj650_PFMET110;
      q.Value["DiJet110_35_Mjj650_PFMET120"] 	= ev.HLT_DiJet110_35_Mjj650_PFMET120;
      q.Value["DiJet110_35_Mjj650_PFMET130"] 	= ev.HLT_DiJet110_35_Mjj650_PFMET130;
      q.Value["DiMu9_Ele9_CaloIdL_TrackIdL"] 	= ev.HLT_DiMu9_Ele9_CaloIdL_TrackIdL;
      q.Value["DiMu9_Ele9_CaloIdL_TrackIdL_DZ"] 	= ev.HLT_DiMu9_Ele9_CaloIdL_TrackIdL_DZ;
      q.Value["DiPFJet15_FBEta3_NoCaloMatched"] 	= ev.HLT_DiPFJet15_FBEta3_NoCaloMatched;
      q.Value["DiPFJet15_NoCaloMatched"] 	= ev.HLT_DiPFJet15_NoCaloMatched;
      q.Value["DiPFJet25_FBEta3_NoCaloMatched"] 	= ev.HLT_DiPFJet25_FBEta3_NoCaloMatched;
      q.Value["DiPFJet25_NoCaloMatched"] 	= ev.HLT_DiPFJet25_NoCaloMatched;
      q.Value["DiPFJetAve100_HFJEC"] 	= ev.HLT_DiPFJetAve100_HFJEC;
      q.Value["DiPFJetAve140"] 	= ev.HLT_DiPFJetAve140;
      q.Value["DiPFJetAve15_HFJEC"] 	= ev.HLT_DiPFJetAve15_HFJEC;
      q.Value["DiPFJetAve160_HFJEC"] 	= ev.HLT_DiPFJetAve160_HFJEC;
      q.Value["DiPFJetAve200"] 	= ev.HLT_DiPFJetAve200;
      q.Value["DiPFJetAve220_HFJEC"] 	= ev.HLT_DiPFJetAve220_HFJEC;
      q.Value["DiPFJetAve25_HFJEC"] 	= ev.HLT_DiPFJetAve25_HFJEC;
      q.Value["DiPFJetAve260"] 	= ev.HLT_DiPFJetAve260;
      q.Value["DiPFJetAve300_HFJEC"] 	= ev.HLT_DiPFJetAve300_HFJEC;
      q.Value["DiPFJetAve320"] 	= ev.HLT_DiPFJetAve320;
      q.Value["DiPFJetAve35_HFJEC"] 	= ev.HLT_DiPFJetAve35_HFJEC;
      q.Value["DiPFJetAve40"] 	= ev.HLT_DiPFJetAve40;
      q.Value["DiPFJetAve400"] 	= ev.HLT_DiPFJetAve400;
      q.Value["DiPFJetAve500"] 	= ev.HLT_DiPFJetAve500;
      q.Value["DiPFJetAve60"] 	= ev.HLT_DiPFJetAve60;
      q.Value["DiPFJetAve60_HFJEC"] 	= ev.HLT_DiPFJetAve60_HFJEC;
      q.Value["DiPFJetAve80"] 	= ev.HLT_DiPFJetAve80;
      q.Value["DiPFJetAve80_HFJEC"] 	= ev.HLT_DiPFJetAve80_HFJEC;
      q.Value["DiSC30_18_EIso_AND_HE_Mass70"] 	= ev.HLT_DiSC30_18_EIso_AND_HE_Mass70;
      q.Value["Dimuon0_Jpsi"] 	= ev.HLT_Dimuon0_Jpsi;
      q.Value["Dimuon0_Jpsi3p5_Muon2"] 	= ev.HLT_Dimuon0_Jpsi3p5_Muon2;
      q.Value["Dimuon0_Jpsi_L1_4R_0er1p5R"] 	= ev.HLT_Dimuon0_Jpsi_L1_4R_0er1p5R;
      q.Value["Dimuon0_Jpsi_L1_NoOS"] 	= ev.HLT_Dimuon0_Jpsi_L1_NoOS;
      q.Value["Dimuon0_Jpsi_NoVertexing"] 	= ev.HLT_Dimuon0_Jpsi_NoVertexing;
      q.Value["Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R"] 	= ev.HLT_Dimuon0_Jpsi_NoVertexing_L1_4R_0er1p5R;
      q.Value["Dimuon0_Jpsi_NoVertexing_NoOS"] 	= ev.HLT_Dimuon0_Jpsi_NoVertexing_NoOS;
      q.Value["Dimuon0_LowMass"] 	= ev.HLT_Dimuon0_LowMass;
      q.Value["Dimuon0_LowMass_L1_0er1p5"] 	= ev.HLT_Dimuon0_LowMass_L1_0er1p5;
      q.Value["Dimuon0_LowMass_L1_0er1p5R"] 	= ev.HLT_Dimuon0_LowMass_L1_0er1p5R;
      q.Value["Dimuon0_LowMass_L1_4"] 	= ev.HLT_Dimuon0_LowMass_L1_4;
      q.Value["Dimuon0_LowMass_L1_4R"] 	= ev.HLT_Dimuon0_LowMass_L1_4R;
      q.Value["Dimuon0_LowMass_L1_TM530"] 	= ev.HLT_Dimuon0_LowMass_L1_TM530;
      q.Value["Dimuon0_Upsilon_L1_4p5"] 	= ev.HLT_Dimuon0_Upsilon_L1_4p5;
      q.Value["Dimuon0_Upsilon_L1_4p5NoOS"] 	= ev.HLT_Dimuon0_Upsilon_L1_4p5NoOS;
      q.Value["Dimuon0_Upsilon_L1_4p5er2p0"] 	= ev.HLT_Dimuon0_Upsilon_L1_4p5er2p0;
      q.Value["Dimuon0_Upsilon_L1_4p5er2p0M"] 	= ev.HLT_Dimuon0_Upsilon_L1_4p5er2p0M;
      q.Value["Dimuon0_Upsilon_L1_5"] 	= ev.HLT_Dimuon0_Upsilon_L1_5;
      q.Value["Dimuon0_Upsilon_L1_5M"] 	= ev.HLT_Dimuon0_Upsilon_L1_5M;
      q.Value["Dimuon0_Upsilon_Muon_L1_TM0"] 	= ev.HLT_Dimuon0_Upsilon_Muon_L1_TM0;
      q.Value["Dimuon0_Upsilon_Muon_NoL1Mass"] 	= ev.HLT_Dimuon0_Upsilon_Muon_NoL1Mass;
      q.Value["Dimuon0_Upsilon_NoVertexing"] 	= ev.HLT_Dimuon0_Upsilon_NoVertexing;
      q.Value["Dimuon10_PsiPrime_Barrel_Seagulls"] 	= ev.HLT_Dimuon10_PsiPrime_Barrel_Seagulls;
      q.Value["Dimuon10_Upsilon_Barrel_Seagulls"] 	= ev.HLT_Dimuon10_Upsilon_Barrel_Seagulls;
      q.Value["Dimuon12_Upsilon_eta1p5"] 	= ev.HLT_Dimuon12_Upsilon_eta1p5;
      q.Value["Dimuon14_Phi_Barrel_Seagulls"] 	= ev.HLT_Dimuon14_Phi_Barrel_Seagulls;
      q.Value["Dimuon18_PsiPrime"] 	= ev.HLT_Dimuon18_PsiPrime;
      q.Value["Dimuon18_PsiPrime_noCorrL1"] 	= ev.HLT_Dimuon18_PsiPrime_noCorrL1;
      q.Value["Dimuon20_Jpsi_Barrel_Seagulls"] 	= ev.HLT_Dimuon20_Jpsi_Barrel_Seagulls;
      q.Value["Dimuon24_Phi_noCorrL1"] 	= ev.HLT_Dimuon24_Phi_noCorrL1;
      q.Value["Dimuon24_Upsilon_noCorrL1"] 	= ev.HLT_Dimuon24_Upsilon_noCorrL1;
      q.Value["Dimuon25_Jpsi"] 	= ev.HLT_Dimuon25_Jpsi;
      q.Value["Dimuon25_Jpsi_noCorrL1"] 	= ev.HLT_Dimuon25_Jpsi_noCorrL1;
      q.Value["Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55"] 	= ev.HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55;
      q.Value["Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55"] 	= ev.HLT_Diphoton30EB_18EB_R9Id_OR_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55;
      q.Value["Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55"] 	= ev.HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55;
      q.Value["Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55"] 	= ev.HLT_Diphoton30PV_18PV_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55;
      q.Value["Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55"] 	= ev.HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_NoPixelVeto_Mass55;
      q.Value["Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55"] 	= ev.HLT_Diphoton30_18_PVrealAND_R9Id_AND_IsoCaloId_AND_HE_R9Id_PixelVeto_Mass55;
      q.Value["Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90"] 	= ev.HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90;
      q.Value["Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95"] 	= ev.HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass95;
      q.Value["DoubleEle24_eta2p1_WPTight_Gsf"] 	= ev.HLT_DoubleEle24_eta2p1_WPTight_Gsf;
      q.Value["DoubleEle25_CaloIdL_MW"] 	= ev.HLT_DoubleEle25_CaloIdL_MW;
      q.Value["DoubleEle27_CaloIdL_MW"] 	= ev.HLT_DoubleEle27_CaloIdL_MW;
      q.Value["DoubleEle33_CaloIdL_MW"] 	= ev.HLT_DoubleEle33_CaloIdL_MW;
      q.Value["DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350"] 	= ev.HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_DZ_PFHT350;
      q.Value["DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350"] 	= ev.HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT350;
      q.Value["DoubleIsoMu20_eta2p1"] 	= ev.HLT_DoubleIsoMu20_eta2p1;
      q.Value["DoubleIsoMu24_eta2p1"] 	= ev.HLT_DoubleIsoMu24_eta2p1;
      q.Value["DoubleL2Mu50"] 	= ev.HLT_DoubleL2Mu50;
      q.Value["DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleLooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleLooseChargedIsoPFTau35_Trk1_eta2p1_Reg;
      q.Value["DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleLooseChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleLooseChargedIsoPFTau40_Trk1_eta2p1_Reg;
      q.Value["DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleMediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleMediumChargedIsoPFTau35_Trk1_eta2p1_Reg;
      q.Value["DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleMediumChargedIsoPFTau40_Trk1_eta2p1_Reg;
      q.Value["DoubleMu20_7_Mass0to30_L1_DM4"] 	= ev.HLT_DoubleMu20_7_Mass0to30_L1_DM4;
      q.Value["DoubleMu20_7_Mass0to30_L1_DM4EG"] 	= ev.HLT_DoubleMu20_7_Mass0to30_L1_DM4EG;
      q.Value["DoubleMu20_7_Mass0to30_Photon23"] 	= ev.HLT_DoubleMu20_7_Mass0to30_Photon23;
      q.Value["DoubleMu2_Jpsi_DoubleTkMu0_Phi"] 	= ev.HLT_DoubleMu2_Jpsi_DoubleTkMu0_Phi;
      q.Value["DoubleMu2_Jpsi_DoubleTrk1_Phi"] 	= ev.HLT_DoubleMu2_Jpsi_DoubleTrk1_Phi;
      q.Value["DoubleMu3_DCA_PFMET50_PFMHT60"] 	= ev.HLT_DoubleMu3_DCA_PFMET50_PFMHT60;
      q.Value["DoubleMu3_DZ_PFMET50_PFMHT60"] 	= ev.HLT_DoubleMu3_DZ_PFMET50_PFMHT60;
      q.Value["DoubleMu3_DZ_PFMET70_PFMHT70"] 	= ev.HLT_DoubleMu3_DZ_PFMET70_PFMHT70;
      q.Value["DoubleMu3_DZ_PFMET90_PFMHT90"] 	= ev.HLT_DoubleMu3_DZ_PFMET90_PFMHT90;
      q.Value["DoubleMu3_Trk_Tau3mu"] 	= ev.HLT_DoubleMu3_Trk_Tau3mu;
      q.Value["DoubleMu3_Trk_Tau3mu_NoL1Mass"] 	= ev.HLT_DoubleMu3_Trk_Tau3mu_NoL1Mass;
      q.Value["DoubleMu43NoFiltersNoVtx"] 	= ev.HLT_DoubleMu43NoFiltersNoVtx;
      q.Value["DoubleMu48NoFiltersNoVtx"] 	= ev.HLT_DoubleMu48NoFiltersNoVtx;
      q.Value["DoubleMu4_3_Bs"] 	= ev.HLT_DoubleMu4_3_Bs;
      q.Value["DoubleMu4_3_Jpsi_Displaced"] 	= ev.HLT_DoubleMu4_3_Jpsi_Displaced;
      q.Value["DoubleMu4_JpsiTrkTrk_Displaced"] 	= ev.HLT_DoubleMu4_JpsiTrkTrk_Displaced;
      q.Value["DoubleMu4_JpsiTrk_Displaced"] 	= ev.HLT_DoubleMu4_JpsiTrk_Displaced;
      q.Value["DoubleMu4_Jpsi_Displaced"] 	= ev.HLT_DoubleMu4_Jpsi_Displaced;
      q.Value["DoubleMu4_Jpsi_NoVertexing"] 	= ev.HLT_DoubleMu4_Jpsi_NoVertexing;
      q.Value["DoubleMu4_LowMassNonResonantTrk_Displaced"] 	= ev.HLT_DoubleMu4_LowMassNonResonantTrk_Displaced;
      q.Value["DoubleMu4_Mass8_DZ_PFHT350"] 	= ev.HLT_DoubleMu4_Mass8_DZ_PFHT350;
      q.Value["DoubleMu4_PsiPrimeTrk_Displaced"] 	= ev.HLT_DoubleMu4_PsiPrimeTrk_Displaced;
      q.Value["DoubleMu8_Mass8_PFHT350"] 	= ev.HLT_DoubleMu8_Mass8_PFHT350;
      q.Value["DoublePFJets100MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets100MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["DoublePFJets100_CaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets100_CaloBTagCSV_p33;
      q.Value["DoublePFJets116MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets116MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["DoublePFJets128MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets128MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["DoublePFJets200_CaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets200_CaloBTagCSV_p33;
      q.Value["DoublePFJets350_CaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets350_CaloBTagCSV_p33;
      q.Value["DoublePFJets40_CaloBTagCSV_p33"] 	= ev.HLT_DoublePFJets40_CaloBTagCSV_p33;
      q.Value["DoublePhoton33_CaloIdL"] 	= ev.HLT_DoublePhoton33_CaloIdL;
      q.Value["DoublePhoton70"] 	= ev.HLT_DoublePhoton70;
      q.Value["DoublePhoton85"] 	= ev.HLT_DoublePhoton85;
      q.Value["DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleTightChargedIsoPFTau35_Trk1_eta2p1_Reg;
      q.Value["DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg"] 	= ev.HLT_DoubleTightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg;
      q.Value["DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg"] 	= ev.HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg;
      q.Value["ECALHT800"] 	= ev.HLT_ECALHT800;
      q.Value["EcalCalibration"] 	= ev.HLT_EcalCalibration;
      q.Value["Ele115_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele115_CaloIdVT_GsfTrkIdT;
      q.Value["Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30"] 	= ev.HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
      q.Value["Ele135_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele135_CaloIdVT_GsfTrkIdT;
      q.Value["Ele145_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele145_CaloIdVT_GsfTrkIdT;
      q.Value["Ele15_IsoVVVL_PFHT450"] 	= ev.HLT_Ele15_IsoVVVL_PFHT450;
      q.Value["Ele15_IsoVVVL_PFHT450_CaloBTagCSV_4p5"] 	= ev.HLT_Ele15_IsoVVVL_PFHT450_CaloBTagCSV_4p5;
      q.Value["Ele15_IsoVVVL_PFHT450_PFMET50"] 	= ev.HLT_Ele15_IsoVVVL_PFHT450_PFMET50;
      q.Value["Ele15_IsoVVVL_PFHT600"] 	= ev.HLT_Ele15_IsoVVVL_PFHT600;
      q.Value["Ele16_Ele12_Ele8_CaloIdL_TrackIdL"] 	= ev.HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL;
      q.Value["Ele17_CaloIdM_TrackIdM_PFJet30"] 	= ev.HLT_Ele17_CaloIdM_TrackIdM_PFJet30;
      q.Value["Ele200_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele200_CaloIdVT_GsfTrkIdT;
      q.Value["Ele20_WPLoose_Gsf"] 	= ev.HLT_Ele20_WPLoose_Gsf;
      q.Value["Ele20_WPTight_Gsf"] 	= ev.HLT_Ele20_WPTight_Gsf;
      q.Value["Ele20_eta2p1_WPLoose_Gsf"] 	= ev.HLT_Ele20_eta2p1_WPLoose_Gsf;
      q.Value["Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30"] 	= ev.HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
      q.Value["Ele23_CaloIdM_TrackIdM_PFJet30"] 	= ev.HLT_Ele23_CaloIdM_TrackIdM_PFJet30;
      q.Value["Ele23_Ele12_CaloIdL_TrackIdL_IsoVL"] 	= ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
      q.Value["Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"] 	= ev.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
      q.Value["Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_CrossL1;
      q.Value["Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_LooseChargedIsoPFTau30_eta2p1_TightID_CrossL1;
      q.Value["Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_CrossL1;
      q.Value["Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_TightID_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_MediumChargedIsoPFTau30_eta2p1_TightID_CrossL1;
      q.Value["Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_CrossL1;
      q.Value["Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_TightID_CrossL1"] 	= ev.HLT_Ele24_eta2p1_WPTight_Gsf_TightChargedIsoPFTau30_eta2p1_TightID_CrossL1;
      q.Value["Ele250_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele250_CaloIdVT_GsfTrkIdT;
      q.Value["Ele27_Ele37_CaloIdL_MW"] 	= ev.HLT_Ele27_Ele37_CaloIdL_MW;
      q.Value["Ele27_WPTight_Gsf"] 	= ev.HLT_Ele27_WPTight_Gsf;
      q.Value["Ele28_HighEta_SC20_Mass55"] 	= ev.HLT_Ele28_HighEta_SC20_Mass55;
      q.Value["Ele28_eta2p1_WPTight_Gsf_HT150"] 	= ev.HLT_Ele28_eta2p1_WPTight_Gsf_HT150;
      q.Value["Ele300_CaloIdVT_GsfTrkIdT"] 	= ev.HLT_Ele300_CaloIdVT_GsfTrkIdT;
      q.Value["Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned"] 	= ev.HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;
      q.Value["Ele32_WPTight_Gsf"] 	= ev.HLT_Ele32_WPTight_Gsf;
      q.Value["Ele32_WPTight_Gsf_L1DoubleEG"] 	= ev.HLT_Ele32_WPTight_Gsf_L1DoubleEG;
      q.Value["Ele35_WPTight_Gsf"] 	= ev.HLT_Ele35_WPTight_Gsf;
      q.Value["Ele35_WPTight_Gsf_L1EGMT"] 	= ev.HLT_Ele35_WPTight_Gsf_L1EGMT;
      q.Value["Ele38_WPTight_Gsf"] 	= ev.HLT_Ele38_WPTight_Gsf;
      q.Value["Ele40_WPTight_Gsf"] 	= ev.HLT_Ele40_WPTight_Gsf;
      q.Value["Ele50_CaloIdVT_GsfTrkIdT_PFJet165"] 	= ev.HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165;
      q.Value["Ele50_IsoVVVL_PFHT450"] 	= ev.HLT_Ele50_IsoVVVL_PFHT450;
      q.Value["Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30"] 	= ev.HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
      q.Value["Ele8_CaloIdM_TrackIdM_PFJet30"] 	= ev.HLT_Ele8_CaloIdM_TrackIdM_PFJet30;
      q.Value["FullTrack_Multiplicity100"] 	= ev.HLT_FullTrack_Multiplicity100;
      q.Value["FullTrack_Multiplicity130"] 	= ev.HLT_FullTrack_Multiplicity130;
      q.Value["FullTrack_Multiplicity155"] 	= ev.HLT_FullTrack_Multiplicity155;
      q.Value["FullTrack_Multiplicity85"] 	= ev.HLT_FullTrack_Multiplicity85;
      q.Value["HISinglePhoton10_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton10_Eta3p1ForPPRef;
      q.Value["HISinglePhoton20_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton20_Eta3p1ForPPRef;
      q.Value["HISinglePhoton30_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton30_Eta3p1ForPPRef;
      q.Value["HISinglePhoton40_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton40_Eta3p1ForPPRef;
      q.Value["HISinglePhoton50_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton50_Eta3p1ForPPRef;
      q.Value["HISinglePhoton60_Eta3p1ForPPRef"] 	= ev.HLT_HISinglePhoton60_Eta3p1ForPPRef;
      q.Value["HT300_Beamspot"] 	= ev.HLT_HT300_Beamspot;
      q.Value["HT400_DisplacedDijet40_DisplacedTrack"] 	= ev.HLT_HT400_DisplacedDijet40_DisplacedTrack;
      q.Value["HT425"] 	= ev.HLT_HT425;
      q.Value["HT430_DisplacedDijet40_DisplacedTrack"] 	= ev.HLT_HT430_DisplacedDijet40_DisplacedTrack;
      q.Value["HT430_DisplacedDijet60_DisplacedTrack"] 	= ev.HLT_HT430_DisplacedDijet60_DisplacedTrack;
      q.Value["HT430_DisplacedDijet80_DisplacedTrack"] 	= ev.HLT_HT430_DisplacedDijet80_DisplacedTrack;
      q.Value["HT450_Beamspot"] 	= ev.HLT_HT450_Beamspot;
      q.Value["HT550_DisplacedDijet60_Inclusive"] 	= ev.HLT_HT550_DisplacedDijet60_Inclusive;
      q.Value["HT550_DisplacedDijet80_Inclusive"] 	= ev.HLT_HT550_DisplacedDijet80_Inclusive;
      q.Value["HT650_DisplacedDijet60_Inclusive"] 	= ev.HLT_HT650_DisplacedDijet60_Inclusive;
      q.Value["HT650_DisplacedDijet80_Inclusive"] 	= ev.HLT_HT650_DisplacedDijet80_Inclusive;
      q.Value["HT750_DisplacedDijet80_Inclusive"] 	= ev.HLT_HT750_DisplacedDijet80_Inclusive;
      q.Value["HcalCalibration"] 	= ev.HLT_HcalCalibration;
      q.Value["HcalIsolatedbunch"] 	= ev.HLT_HcalIsolatedbunch;
      q.Value["HcalNZS"] 	= ev.HLT_HcalNZS;
      q.Value["HcalPhiSym"] 	= ev.HLT_HcalPhiSym;
      q.Value["IsoMu20"] 	= ev.HLT_IsoMu20;
      q.Value["IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_CrossL1;
      q.Value["IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_LooseChargedIsoPFTau27_eta2p1_TightID_CrossL1;
      q.Value["IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_CrossL1;
      q.Value["IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_MediumChargedIsoPFTau27_eta2p1_TightID_CrossL1;
      q.Value["IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_CrossL1;
      q.Value["IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1"] 	= ev.HLT_IsoMu20_eta2p1_TightChargedIsoPFTau27_eta2p1_TightID_CrossL1;
      q.Value["IsoMu24"] 	= ev.HLT_IsoMu24;
      q.Value["IsoMu24_eta2p1"] 	= ev.HLT_IsoMu24_eta2p1;
      q.Value["IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau20_TightID_SingleL1;
      q.Value["IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_LooseChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau20_TightID_SingleL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"] 	= ev.HLT_IsoMu24_eta2p1_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau20_TightID_SingleL1;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau35_Trk1_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_CrossL1;
      q.Value["IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1"] 	= ev.HLT_IsoMu24_eta2p1_TightChargedIsoPFTau40_Trk1_eta2p1_Reg_CrossL1;
      q.Value["IsoMu27"] 	= ev.HLT_IsoMu27;
      q.Value["IsoMu27_LooseChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu27_LooseChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu27_MediumChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu27_MediumChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu27_TightChargedIsoPFTau20_SingleL1"] 	= ev.HLT_IsoMu27_TightChargedIsoPFTau20_SingleL1;
      q.Value["IsoMu30"] 	= ev.HLT_IsoMu30;
      q.Value["IsoTrackHB"] 	= ev.HLT_IsoTrackHB;
      q.Value["IsoTrackHE"] 	= ev.HLT_IsoTrackHE;
      q.Value["L1ETMHadSeeds"] 	= ev.HLT_L1ETMHadSeeds;
      q.Value["L1MinimumBiasHF0OR"] 	= ev.HLT_L1MinimumBiasHF0OR;
      q.Value["L1MinimumBiasHF_OR"] 	= ev.HLT_L1MinimumBiasHF_OR;
      q.Value["L1NotBptxOR"] 	= ev.HLT_L1NotBptxOR;
      q.Value["L1SingleMu18"] 	= ev.HLT_L1SingleMu18;
      q.Value["L1SingleMu25"] 	= ev.HLT_L1SingleMu25;
      q.Value["L1UnpairedBunchBptxMinus"] 	= ev.HLT_L1UnpairedBunchBptxMinus;
      q.Value["L1UnpairedBunchBptxPlus"] 	= ev.HLT_L1UnpairedBunchBptxPlus;
      q.Value["L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142"] 	= ev.HLT_L1_CDC_SingleMu_3_er1p2_TOP120_DPHI2p618_3p142;
      q.Value["L1_DoubleJet30_Mass_Min400_Mu10"] 	= ev.HLT_L1_DoubleJet30_Mass_Min400_Mu10;
      q.Value["L2Mu10"] 	= ev.HLT_L2Mu10;
      q.Value["L2Mu10_NoVertex_NoBPTX"] 	= ev.HLT_L2Mu10_NoVertex_NoBPTX;
      q.Value["L2Mu10_NoVertex_NoBPTX3BX"] 	= ev.HLT_L2Mu10_NoVertex_NoBPTX3BX;
      q.Value["L2Mu40_NoVertex_3Sta_NoBPTX3BX"] 	= ev.HLT_L2Mu40_NoVertex_3Sta_NoBPTX3BX;
      q.Value["L2Mu45_NoVertex_3Sta_NoBPTX3BX"] 	= ev.HLT_L2Mu45_NoVertex_3Sta_NoBPTX3BX;
      q.Value["L2Mu50"] 	= ev.HLT_L2Mu50;
      q.Value["MET105_IsoTrk50"] 	= ev.HLT_MET105_IsoTrk50;
      q.Value["MET120_IsoTrk50"] 	= ev.HLT_MET120_IsoTrk50;
      q.Value["MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1"] 	= ev.HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1;
      q.Value["MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr"] 	= ev.HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_1pr;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET100;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET110;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET120;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET130;
      q.Value["MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90"] 	= ev.HLT_MediumChargedIsoPFTau50_Trk30_eta2p1_1pr_MET90;
      q.Value["MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight"] 	= ev.HLT_MonoCentralPFJet80_PFMETNoMu110_PFMHTNoMu110_IDTight;
      q.Value["MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight"] 	= ev.HLT_MonoCentralPFJet80_PFMETNoMu120_PFMHTNoMu120_IDTight;
      q.Value["MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight"] 	= ev.HLT_MonoCentralPFJet80_PFMETNoMu130_PFMHTNoMu130_IDTight;
      q.Value["MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight"] 	= ev.HLT_MonoCentralPFJet80_PFMETNoMu140_PFMHTNoMu140_IDTight;
      q.Value["Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60"] 	= ev.HLT_Mu10_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT350_PFMETNoMu60;
      q.Value["Mu12_DoublePFJets100_CaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets100_CaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets200_CaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets200_CaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets350_CaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets350_CaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets40MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets40_CaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets40_CaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets54MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagCSV_p33"] 	= ev.HLT_Mu12_DoublePFJets62MaxDeta1p6_DoubleCaloBTagCSV_p33;
      q.Value["Mu12_DoublePhoton20"] 	= ev.HLT_Mu12_DoublePhoton20;
      q.Value["Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"] 	= ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
      q.Value["Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"] 	= ev.HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
      q.Value["Mu15_IsoVVVL_PFHT450"] 	= ev.HLT_Mu15_IsoVVVL_PFHT450;
      q.Value["Mu15_IsoVVVL_PFHT450_CaloBTagCSV_4p5"] 	= ev.HLT_Mu15_IsoVVVL_PFHT450_CaloBTagCSV_4p5;
      q.Value["Mu15_IsoVVVL_PFHT450_PFMET50"] 	= ev.HLT_Mu15_IsoVVVL_PFHT450_PFMET50;
      q.Value["Mu15_IsoVVVL_PFHT600"] 	= ev.HLT_Mu15_IsoVVVL_PFHT600;
      q.Value["Mu17"] 	= ev.HLT_Mu17;
      q.Value["Mu17_Photon30_IsoCaloId"] 	= ev.HLT_Mu17_Photon30_IsoCaloId;
      q.Value["Mu17_TrkIsoVVL"] 	= ev.HLT_Mu17_TrkIsoVVL;
      q.Value["Mu17_TrkIsoVVL_Mu8_TrkIsoVVL"] 	= ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
      q.Value["Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ"] 	= ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
      q.Value["Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8"] 	= ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
      q.Value["Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8"] 	= ev.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
      q.Value["Mu18_Mu9"] 	= ev.HLT_Mu18_Mu9;
      q.Value["Mu18_Mu9_DZ"] 	= ev.HLT_Mu18_Mu9_DZ;
      q.Value["Mu18_Mu9_SameSign"] 	= ev.HLT_Mu18_Mu9_SameSign;
      q.Value["Mu18_Mu9_SameSign_DZ"] 	= ev.HLT_Mu18_Mu9_SameSign_DZ;
      q.Value["Mu19"] 	= ev.HLT_Mu19;
      q.Value["Mu19_TrkIsoVVL"] 	= ev.HLT_Mu19_TrkIsoVVL;
      q.Value["Mu19_TrkIsoVVL_Mu9_TrkIsoVVL"] 	= ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL;
      q.Value["Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ"] 	= ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ;
      q.Value["Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8"] 	= ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass3p8;
      q.Value["Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8"] 	= ev.HLT_Mu19_TrkIsoVVL_Mu9_TrkIsoVVL_DZ_Mass8;
      q.Value["Mu20"] 	= ev.HLT_Mu20;
      q.Value["Mu20_Mu10"] 	= ev.HLT_Mu20_Mu10;
      q.Value["Mu20_Mu10_DZ"] 	= ev.HLT_Mu20_Mu10_DZ;
      q.Value["Mu20_Mu10_SameSign"] 	= ev.HLT_Mu20_Mu10_SameSign;
      q.Value["Mu20_Mu10_SameSign_DZ"] 	= ev.HLT_Mu20_Mu10_SameSign_DZ;
      q.Value["Mu20_TkMu0_Phi"] 	= ev.HLT_Mu20_TkMu0_Phi;
      q.Value["Mu23_Mu12"] 	= ev.HLT_Mu23_Mu12;
      q.Value["Mu23_Mu12_DZ"] 	= ev.HLT_Mu23_Mu12_DZ;
      q.Value["Mu23_Mu12_SameSign"] 	= ev.HLT_Mu23_Mu12_SameSign;
      q.Value["Mu23_Mu12_SameSign_DZ"] 	= ev.HLT_Mu23_Mu12_SameSign_DZ;
      q.Value["Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL"] 	= ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
      q.Value["Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ"] 	= ev.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
      q.Value["Mu25_TkMu0_Onia"] 	= ev.HLT_Mu25_TkMu0_Onia;
      q.Value["Mu25_TkMu0_Phi"] 	= ev.HLT_Mu25_TkMu0_Phi;
      q.Value["Mu27"] 	= ev.HLT_Mu27;
      q.Value["Mu27_Ele37_CaloIdL_MW"] 	= ev.HLT_Mu27_Ele37_CaloIdL_MW;
      q.Value["Mu30_TkMu0_Onia"] 	= ev.HLT_Mu30_TkMu0_Onia;
      q.Value["Mu37_Ele27_CaloIdL_MW"] 	= ev.HLT_Mu37_Ele27_CaloIdL_MW;
      q.Value["Mu37_TkMu27"] 	= ev.HLT_Mu37_TkMu27;
      q.Value["Mu3_PFJet40"] 	= ev.HLT_Mu3_PFJet40;
      q.Value["Mu43NoFiltersNoVtx_Photon43_CaloIdL"] 	= ev.HLT_Mu43NoFiltersNoVtx_Photon43_CaloIdL;
      q.Value["Mu48NoFiltersNoVtx_Photon48_CaloIdL"] 	= ev.HLT_Mu48NoFiltersNoVtx_Photon48_CaloIdL;
      q.Value["Mu50"] 	= ev.HLT_Mu50;
      q.Value["Mu50_IsoVVVL_PFHT450"] 	= ev.HLT_Mu50_IsoVVVL_PFHT450;
      q.Value["Mu55"] 	= ev.HLT_Mu55;
      q.Value["Mu7p5_L2Mu2_Jpsi"] 	= ev.HLT_Mu7p5_L2Mu2_Jpsi;
      q.Value["Mu7p5_L2Mu2_Upsilon"] 	= ev.HLT_Mu7p5_L2Mu2_Upsilon;
      q.Value["Mu7p5_Track2_Jpsi"] 	= ev.HLT_Mu7p5_Track2_Jpsi;
      q.Value["Mu7p5_Track2_Upsilon"] 	= ev.HLT_Mu7p5_Track2_Upsilon;
      q.Value["Mu7p5_Track3p5_Jpsi"] 	= ev.HLT_Mu7p5_Track3p5_Jpsi;
      q.Value["Mu7p5_Track3p5_Upsilon"] 	= ev.HLT_Mu7p5_Track3p5_Upsilon;
      q.Value["Mu7p5_Track7_Jpsi"] 	= ev.HLT_Mu7p5_Track7_Jpsi;
      q.Value["Mu7p5_Track7_Upsilon"] 	= ev.HLT_Mu7p5_Track7_Upsilon;
      q.Value["Mu8"] 	= ev.HLT_Mu8;
      q.Value["Mu8_DiEle12_CaloIdL_TrackIdL"] 	= ev.HLT_Mu8_DiEle12_CaloIdL_TrackIdL;
      q.Value["Mu8_DiEle12_CaloIdL_TrackIdL_DZ"] 	= ev.HLT_Mu8_DiEle12_CaloIdL_TrackIdL_DZ;
      q.Value["Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350"] 	= ev.HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350;
      q.Value["Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ"] 	= ev.HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT350_DZ;
      q.Value["Mu8_TrkIsoVVL"] 	= ev.HLT_Mu8_TrkIsoVVL;
      q.Value["Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60"] 	= ev.HLT_Mu8_TrkIsoVVL_DiPFJet40_DEta3p5_MJJ750_HTT300_PFMETNoMu60;
      q.Value["Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL"] 	= ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
      q.Value["Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ"] 	= ev.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
      q.Value["OldMu100"] 	= ev.HLT_OldMu100;
      q.Value["PFHT1050"] 	= ev.HLT_PFHT1050;
      q.Value["PFHT180"] 	= ev.HLT_PFHT180;
      q.Value["PFHT250"] 	= ev.HLT_PFHT250;
      q.Value["PFHT300PT30_QuadPFJet_75_60_45_40"] 	= ev.HLT_PFHT300PT30_QuadPFJet_75_60_45_40;
      q.Value["PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0"] 	= ev.HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0;
      q.Value["PFHT350"] 	= ev.HLT_PFHT350;
      q.Value["PFHT350MinPFJet15"] 	= ev.HLT_PFHT350MinPFJet15;
      q.Value["PFHT370"] 	= ev.HLT_PFHT370;
      q.Value["PFHT380_SixPFJet32"] 	= ev.HLT_PFHT380_SixPFJet32;
      q.Value["PFHT380_SixPFJet32_DoublePFBTagCSV_2p2"] 	= ev.HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2;
      q.Value["PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"] 	= ev.HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2;
      q.Value["PFHT430"] 	= ev.HLT_PFHT430;
      q.Value["PFHT430_SixPFJet40"] 	= ev.HLT_PFHT430_SixPFJet40;
      q.Value["PFHT430_SixPFJet40_PFBTagCSV_1p5"] 	= ev.HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5;
      q.Value["PFHT500_PFMET100_PFMHT100_IDTight"] 	= ev.HLT_PFHT500_PFMET100_PFMHT100_IDTight;
      q.Value["PFHT500_PFMET110_PFMHT110_IDTight"] 	= ev.HLT_PFHT500_PFMET110_PFMHT110_IDTight;
      q.Value["PFHT510"] 	= ev.HLT_PFHT510;
      q.Value["PFHT590"] 	= ev.HLT_PFHT590;
      q.Value["PFHT680"] 	= ev.HLT_PFHT680;
      q.Value["PFHT700_PFMET85_PFMHT85_IDTight"] 	= ev.HLT_PFHT700_PFMET85_PFMHT85_IDTight;
      q.Value["PFHT700_PFMET95_PFMHT95_IDTight"] 	= ev.HLT_PFHT700_PFMET95_PFMHT95_IDTight;
      q.Value["PFHT780"] 	= ev.HLT_PFHT780;
      q.Value["PFHT800_PFMET75_PFMHT75_IDTight"] 	= ev.HLT_PFHT800_PFMET75_PFMHT75_IDTight;
      q.Value["PFHT800_PFMET85_PFMHT85_IDTight"] 	= ev.HLT_PFHT800_PFMET85_PFMHT85_IDTight;
      q.Value["PFHT890"] 	= ev.HLT_PFHT890;
      q.Value["PFJet140"] 	= ev.HLT_PFJet140;
      q.Value["PFJet200"] 	= ev.HLT_PFJet200;
      q.Value["PFJet260"] 	= ev.HLT_PFJet260;
      q.Value["PFJet320"] 	= ev.HLT_PFJet320;
      q.Value["PFJet40"] 	= ev.HLT_PFJet40;
      q.Value["PFJet400"] 	= ev.HLT_PFJet400;
      q.Value["PFJet450"] 	= ev.HLT_PFJet450;
      q.Value["PFJet500"] 	= ev.HLT_PFJet500;
      q.Value["PFJet550"] 	= ev.HLT_PFJet550;
      q.Value["PFJet60"] 	= ev.HLT_PFJet60;
      q.Value["PFJet80"] 	= ev.HLT_PFJet80;
      q.Value["PFJetFwd140"] 	= ev.HLT_PFJetFwd140;
      q.Value["PFJetFwd200"] 	= ev.HLT_PFJetFwd200;
      q.Value["PFJetFwd260"] 	= ev.HLT_PFJetFwd260;
      q.Value["PFJetFwd320"] 	= ev.HLT_PFJetFwd320;
      q.Value["PFJetFwd40"] 	= ev.HLT_PFJetFwd40;
      q.Value["PFJetFwd400"] 	= ev.HLT_PFJetFwd400;
      q.Value["PFJetFwd450"] 	= ev.HLT_PFJetFwd450;
      q.Value["PFJetFwd500"] 	= ev.HLT_PFJetFwd500;
      q.Value["PFJetFwd60"] 	= ev.HLT_PFJetFwd60;
      q.Value["PFJetFwd80"] 	= ev.HLT_PFJetFwd80;
      q.Value["PFMET100_PFMHT100_IDTight_CaloBTagCSV_3p1"] 	= ev.HLT_PFMET100_PFMHT100_IDTight_CaloBTagCSV_3p1;
      q.Value["PFMET100_PFMHT100_IDTight_PFHT60"] 	= ev.HLT_PFMET100_PFMHT100_IDTight_PFHT60;
      q.Value["PFMET110_PFMHT110_IDTight"] 	= ev.HLT_PFMET110_PFMHT110_IDTight;
      q.Value["PFMET110_PFMHT110_IDTight_CaloBTagCSV_3p1"] 	= ev.HLT_PFMET110_PFMHT110_IDTight_CaloBTagCSV_3p1;
      q.Value["PFMET120_PFMHT120_IDTight"] 	= ev.HLT_PFMET120_PFMHT120_IDTight;
      q.Value["PFMET120_PFMHT120_IDTight_CaloBTagCSV_3p1"] 	= ev.HLT_PFMET120_PFMHT120_IDTight_CaloBTagCSV_3p1;
      q.Value["PFMET120_PFMHT120_IDTight_PFHT60"] 	= ev.HLT_PFMET120_PFMHT120_IDTight_PFHT60;
      q.Value["PFMET130_PFMHT130_IDTight"] 	= ev.HLT_PFMET130_PFMHT130_IDTight;
      q.Value["PFMET130_PFMHT130_IDTight_CaloBTagCSV_3p1"] 	= ev.HLT_PFMET130_PFMHT130_IDTight_CaloBTagCSV_3p1;
      q.Value["PFMET140_PFMHT140_IDTight"] 	= ev.HLT_PFMET140_PFMHT140_IDTight;
      q.Value["PFMET140_PFMHT140_IDTight_CaloBTagCSV_3p1"] 	= ev.HLT_PFMET140_PFMHT140_IDTight_CaloBTagCSV_3p1;
      q.Value["PFMET200_HBHECleaned"] 	= ev.HLT_PFMET200_HBHECleaned;
      q.Value["PFMET200_HBHE_BeamHaloCleaned"] 	= ev.HLT_PFMET200_HBHE_BeamHaloCleaned;
      q.Value["PFMET200_NotCleaned"] 	= ev.HLT_PFMET200_NotCleaned;
      q.Value["PFMET250_HBHECleaned"] 	= ev.HLT_PFMET250_HBHECleaned;
      q.Value["PFMET300_HBHECleaned"] 	= ev.HLT_PFMET300_HBHECleaned;
      q.Value["PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60"] 	= ev.HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60;
      q.Value["PFMETNoMu110_PFMHTNoMu110_IDTight"] 	= ev.HLT_PFMETNoMu110_PFMHTNoMu110_IDTight;
      q.Value["PFMETNoMu120_PFMHTNoMu120_IDTight"] 	= ev.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
      q.Value["PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60"] 	= ev.HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
      q.Value["PFMETNoMu130_PFMHTNoMu130_IDTight"] 	= ev.HLT_PFMETNoMu130_PFMHTNoMu130_IDTight;
      q.Value["PFMETNoMu140_PFMHTNoMu140_IDTight"] 	= ev.HLT_PFMETNoMu140_PFMHTNoMu140_IDTight;
      q.Value["PFMETTypeOne100_PFMHT100_IDTight_PFHT60"] 	= ev.HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60;
      q.Value["PFMETTypeOne110_PFMHT110_IDTight"] 	= ev.HLT_PFMETTypeOne110_PFMHT110_IDTight;
      q.Value["PFMETTypeOne120_PFMHT120_IDTight"] 	= ev.HLT_PFMETTypeOne120_PFMHT120_IDTight;
      q.Value["PFMETTypeOne120_PFMHT120_IDTight_PFHT60"] 	= ev.HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60;
      q.Value["PFMETTypeOne130_PFMHT130_IDTight"] 	= ev.HLT_PFMETTypeOne130_PFMHT130_IDTight;
      q.Value["PFMETTypeOne140_PFMHT140_IDTight"] 	= ev.HLT_PFMETTypeOne140_PFMHT140_IDTight;
      q.Value["PFMETTypeOne200_HBHE_BeamHaloCleaned"] 	= ev.HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
      q.Value["Photon120"] 	= ev.HLT_Photon120;
      q.Value["Photon120_R9Id90_HE10_IsoM"] 	= ev.HLT_Photon120_R9Id90_HE10_IsoM;
      q.Value["Photon150"] 	= ev.HLT_Photon150;
      q.Value["Photon165_R9Id90_HE10_IsoM"] 	= ev.HLT_Photon165_R9Id90_HE10_IsoM;
      q.Value["Photon175"] 	= ev.HLT_Photon175;
      q.Value["Photon200"] 	= ev.HLT_Photon200;
      q.Value["Photon20_HoverELoose"] 	= ev.HLT_Photon20_HoverELoose;
      q.Value["Photon25"] 	= ev.HLT_Photon25;
      q.Value["Photon300_NoHE"] 	= ev.HLT_Photon300_NoHE;
      q.Value["Photon30_HoverELoose"] 	= ev.HLT_Photon30_HoverELoose;
      q.Value["Photon33"] 	= ev.HLT_Photon33;
      q.Value["Photon40_HoverELoose"] 	= ev.HLT_Photon40_HoverELoose;
      q.Value["Photon50"] 	= ev.HLT_Photon50;
      q.Value["Photon50_HoverELoose"] 	= ev.HLT_Photon50_HoverELoose;
      q.Value["Photon50_R9Id90_HE10_IsoM"] 	= ev.HLT_Photon50_R9Id90_HE10_IsoM;
      q.Value["Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50"] 	= ev.HLT_Photon50_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_PFMET50;
      q.Value["Photon60_HoverELoose"] 	= ev.HLT_Photon60_HoverELoose;
      q.Value["Photon60_R9Id90_CaloIdL_IsoL"] 	= ev.HLT_Photon60_R9Id90_CaloIdL_IsoL;
      q.Value["Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL"] 	= ev.HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL;
      q.Value["Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15"] 	= ev.HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT350MinPFJet15;
      q.Value["Photon75"] 	= ev.HLT_Photon75;
      q.Value["Photon75_R9Id90_HE10_IsoM"] 	= ev.HLT_Photon75_R9Id90_HE10_IsoM;
      q.Value["Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3"] 	= ev.HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3;
      q.Value["Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3"] 	= ev.HLT_Photon75_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ600DEta3;
      q.Value["Photon90"] 	= ev.HLT_Photon90;
      q.Value["Photon90_CaloIdL_PFHT700"] 	= ev.HLT_Photon90_CaloIdL_PFHT700;
      q.Value["Photon90_R9Id90_HE10_IsoM"] 	= ev.HLT_Photon90_R9Id90_HE10_IsoM;
      q.Value["Physics"] 	= ev.HLT_Physics;
      q.Value["Physics_part0"] 	= ev.HLT_Physics_part0;
      q.Value["Physics_part1"] 	= ev.HLT_Physics_part1;
      q.Value["Physics_part2"] 	= ev.HLT_Physics_part2;
      q.Value["Physics_part3"] 	= ev.HLT_Physics_part3;
      q.Value["Physics_part4"] 	= ev.HLT_Physics_part4;
      q.Value["Physics_part5"] 	= ev.HLT_Physics_part5;
      q.Value["Physics_part6"] 	= ev.HLT_Physics_part6;
      q.Value["Physics_part7"] 	= ev.HLT_Physics_part7;
      q.Value["QuadPFJet103_88_75_15"] 	= ev.HLT_QuadPFJet103_88_75_15;
      q.Value["QuadPFJet103_88_75_15_BTagCSV_p013_VBF2"] 	= ev.HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
      q.Value["QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1"] 	= ev.HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
      q.Value["QuadPFJet105_88_76_15"] 	= ev.HLT_QuadPFJet105_88_76_15;
      q.Value["QuadPFJet105_88_76_15_BTagCSV_p013_VBF2"] 	= ev.HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
      q.Value["QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1"] 	= ev.HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
      q.Value["QuadPFJet111_90_80_15"] 	= ev.HLT_QuadPFJet111_90_80_15;
      q.Value["QuadPFJet111_90_80_15_BTagCSV_p013_VBF2"] 	= ev.HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
      q.Value["QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1"] 	= ev.HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
      q.Value["QuadPFJet98_83_71_15"] 	= ev.HLT_QuadPFJet98_83_71_15;
      q.Value["QuadPFJet98_83_71_15_BTagCSV_p013_VBF2"] 	= ev.HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
      q.Value["QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1"] 	= ev.HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;
      q.Value["Random"] 	= ev.HLT_Random;
      q.Value["Rsq0p35"] 	= ev.HLT_Rsq0p35;
      q.Value["Rsq0p40"] 	= ev.HLT_Rsq0p40;
      q.Value["RsqMR300_Rsq0p09_MR200"] 	= ev.HLT_RsqMR300_Rsq0p09_MR200;
      q.Value["RsqMR300_Rsq0p09_MR200_4jet"] 	= ev.HLT_RsqMR300_Rsq0p09_MR200_4jet;
      q.Value["RsqMR320_Rsq0p09_MR200"] 	= ev.HLT_RsqMR320_Rsq0p09_MR200;
      q.Value["RsqMR320_Rsq0p09_MR200_4jet"] 	= ev.HLT_RsqMR320_Rsq0p09_MR200_4jet;
      q.Value["SingleJet30_Mu12_SinglePFJet40"] 	= ev.HLT_SingleJet30_Mu12_SinglePFJet40;
      q.Value["Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15"] 	= ev.HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15;
      q.Value["Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1"] 	= ev.HLT_Tau3Mu_Mu7_Mu1_TkMu1_IsoTau15_Charge1;
      q.Value["Tau3Mu_Mu7_Mu1_TkMu1_Tau15"] 	= ev.HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15;
      q.Value["Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1"] 	= ev.HLT_Tau3Mu_Mu7_Mu1_TkMu1_Tau15_Charge1;
      q.Value["TkMu100"] 	= ev.HLT_TkMu100;
      q.Value["Trimuon5_3p5_2_Upsilon_Muon"] 	= ev.HLT_Trimuon5_3p5_2_Upsilon_Muon;
      q.Value["TripleJet110_35_35_Mjj650_PFMET110"] 	= ev.HLT_TripleJet110_35_35_Mjj650_PFMET110;
      q.Value["TripleJet110_35_35_Mjj650_PFMET120"] 	= ev.HLT_TripleJet110_35_35_Mjj650_PFMET120;
      q.Value["TripleJet110_35_35_Mjj650_PFMET130"] 	= ev.HLT_TripleJet110_35_35_Mjj650_PFMET130;
      q.Value["TripleMu_10_5_5_DZ"] 	= ev.HLT_TripleMu_10_5_5_DZ;
      q.Value["TripleMu_12_10_5"] 	= ev.HLT_TripleMu_12_10_5;
      q.Value["TripleMu_5_3_3_Mass3p8to60_DCA"] 	= ev.HLT_TripleMu_5_3_3_Mass3p8to60_DCA;
      q.Value["TripleMu_5_3_3_Mass3p8to60_DZ"] 	= ev.HLT_TripleMu_5_3_3_Mass3p8to60_DZ;
      q.Value["TriplePhoton_20_20_20_CaloIdLV2"] 	= ev.HLT_TriplePhoton_20_20_20_CaloIdLV2;
      q.Value["TriplePhoton_20_20_20_CaloIdLV2_R9IdVL"] 	= ev.HLT_TriplePhoton_20_20_20_CaloIdLV2_R9IdVL;
      q.Value["TriplePhoton_30_30_10_CaloIdLV2"] 	= ev.HLT_TriplePhoton_30_30_10_CaloIdLV2;
      q.Value["TriplePhoton_30_30_10_CaloIdLV2_R9IdVL"] 	= ev.HLT_TriplePhoton_30_30_10_CaloIdLV2_R9IdVL;
      q.Value["TriplePhoton_35_35_5_CaloIdLV2_R9IdVL"] 	= ev.HLT_TriplePhoton_35_35_5_CaloIdLV2_R9IdVL;
      q.Value["TrkMu12_DoubleTrkMu5NoFiltersNoVtx"] 	= ev.HLT_TrkMu12_DoubleTrkMu5NoFiltersNoVtx;
      q.Value["TrkMu16_DoubleTrkMu6NoFiltersNoVtx"] 	= ev.HLT_TrkMu16_DoubleTrkMu6NoFiltersNoVtx;
      q.Value["TrkMu17_DoubleTrkMu8NoFiltersNoVtx"] 	= ev.HLT_TrkMu17_DoubleTrkMu8NoFiltersNoVtx;
      q.Value["UncorrectedJetE30_NoBPTX"] 	= ev.HLT_UncorrectedJetE30_NoBPTX;
      q.Value["UncorrectedJetE30_NoBPTX3BX"] 	= ev.HLT_UncorrectedJetE30_NoBPTX3BX;
      q.Value["UncorrectedJetE60_NoBPTX3BX"] 	= ev.HLT_UncorrectedJetE60_NoBPTX3BX;
      q.Value["UncorrectedJetE70_NoBPTX3BX"] 	= ev.HLT_UncorrectedJetE70_NoBPTX3BX;
      q.Value["VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg"] 	= ev.HLT_VBF_DoubleLooseChargedIsoPFTau20_Trk1_eta2p1_Reg;
      q.Value["VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg"] 	= ev.HLT_VBF_DoubleMediumChargedIsoPFTau20_Trk1_eta2p1_Reg;
      q.Value["VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg"] 	= ev.HLT_VBF_DoubleTightChargedIsoPFTau20_Trk1_eta2p1_Reg;
      q.Value["ZeroBias"] 	= ev.HLT_ZeroBias;
      q.Value["ZeroBias_FirstBXAfterTrain"] 	= ev.HLT_ZeroBias_FirstBXAfterTrain;
      q.Value["ZeroBias_FirstCollisionAfterAbortGap"] 	= ev.HLT_ZeroBias_FirstCollisionAfterAbortGap;
      q.Value["ZeroBias_FirstCollisionInTrain"] 	= ev.HLT_ZeroBias_FirstCollisionInTrain;
      q.Value["ZeroBias_IsolatedBunches"] 	= ev.HLT_ZeroBias_IsolatedBunches;
      q.Value["ZeroBias_LastCollisionInTrain"] 	= ev.HLT_ZeroBias_LastCollisionInTrain;
      q.Value["ZeroBias_part0"] 	= ev.HLT_ZeroBias_part0;
      q.Value["ZeroBias_part1"] 	= ev.HLT_ZeroBias_part1;
      q.Value["ZeroBias_part2"] 	= ev.HLT_ZeroBias_part2;
      q.Value["ZeroBias_part3"] 	= ev.HLT_ZeroBias_part3;
      q.Value["ZeroBias_part4"] 	= ev.HLT_ZeroBias_part4;
      q.Value["ZeroBias_part5"] 	= ev.HLT_ZeroBias_part5;
      q.Value["ZeroBias_part6"] 	= ev.HLT_ZeroBias_part6;
      q.Value["ZeroBias_part7"] 	= ev.HLT_ZeroBias_part7;

      p = q;
      return;
    }
  if ( key.Contains("MET") )
    {
      TNMObject q("MET", 
                  ev.MET_pt, 
                  0,
                  ev.MET_phi,
                  0);
      q.Value["MetUnclustEnUpDeltaX"] 	= ev.MET_MetUnclustEnUpDeltaX;
      q.Value["MetUnclustEnUpDeltaY"] 	= ev.MET_MetUnclustEnUpDeltaY;
      q.Value["covXX"] 	= ev.MET_covXX;
      q.Value["covXY"] 	= ev.MET_covXY;
      q.Value["covYY"] 	= ev.MET_covYY;
      q.Value["fiducialGenPhi"] 	= ev.MET_fiducialGenPhi;
      q.Value["fiducialGenPt"] 	= ev.MET_fiducialGenPt;
      q.Value["phi"] 	= ev.MET_phi;
      q.Value["pt"] 	= ev.MET_pt;
      q.Value["significance"] 	= ev.MET_significance;
      q.Value["sumEt"] 	= ev.MET_sumEt;

      p = q;
      return;
    }
  if ( key.Contains("GenMET") )
    {
      TNMObject q("GenMET", 
                  ev.GenMET_pt, 
                  0,
                  ev.GenMET_phi,
                  0);
      q.Value["phi"] 	= ev.GenMET_phi;
      q.Value["pt"] 	= ev.GenMET_pt;

      p = q;
      return;
    }
  if ( key.Contains("Pileup") )
    {
      TNMObject q("Pileup", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["nPU"] 	= ev.Pileup_nPU;
      q.Value["nTrueInt"] 	= ev.Pileup_nTrueInt;
      q.Value["sumEOOT"] 	= ev.Pileup_sumEOOT;
      q.Value["sumLOOT"] 	= ev.Pileup_sumLOOT;

      p = q;
      return;
    }
  if ( key.Contains("LHEWeight") )
    {
      TNMObject q("LHEWeight", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["originalXWGTUP"] 	= ev.LHEWeight_originalXWGTUP;

      p = q;
      return;
    }
  if ( key.Contains("Event") )
    {
      TNMObject q("Event", 
                  0, 
                  0,
                  0,
                  0);
      q.Value["HLTriggerFinalPath"] 	= ev.HLTriggerFinalPath;
      q.Value["HLTriggerFirstPath"] 	= ev.HLTriggerFirstPath;
      q.Value["SoftActivityJetHT"] 	= ev.SoftActivityJetHT;
      q.Value["SoftActivityJetHT10"] 	= ev.SoftActivityJetHT10;
      q.Value["SoftActivityJetHT2"] 	= ev.SoftActivityJetHT2;
      q.Value["SoftActivityJetHT5"] 	= ev.SoftActivityJetHT5;
      q.Value["SoftActivityJetNjets10"] 	= ev.SoftActivityJetNjets10;
      q.Value["SoftActivityJetNjets2"] 	= ev.SoftActivityJetNjets2;
      q.Value["SoftActivityJetNjets5"] 	= ev.SoftActivityJetNjets5;
      q.Value["event"] 	= ev.event;
      q.Value["fixedGridRhoFastjetAll"] 	= ev.fixedGridRhoFastjetAll;
      q.Value["fixedGridRhoFastjetCentralCalo"] 	= ev.fixedGridRhoFastjetCentralCalo;
      q.Value["fixedGridRhoFastjetCentralNeutral"] 	= ev.fixedGridRhoFastjetCentralNeutral;
      q.Value["genTtbarId"] 	= ev.genTtbarId;
      q.Value["genWeight"] 	= ev.genWeight;
      q.Value["luminosityBlock"] 	= ev.luminosityBlock;
      q.Value["run"] 	= ev.run;

      p = q;
      return;
    }
}
