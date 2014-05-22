#ifndef RZRBTANALYZER_H
#define RZRBTANALYZER_H
//-----------------------------------------------------------------------------
// File:        rzrBTanalyzer.h
// Description: Analyzer header for ntuples created by TheNtupleMaker
// Created:     Thu May 15 21:43:06 2014 by mkanalyzer.py
// Author:      Andreas Hinzmann
//-----------------------------------------------------------------------------
// -- System

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cmath>

#include "rzrBTanalyzerutil.h"
#include "treestream.h"
#include "pdg.h"

// -- Root

#include "TROOT.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TH1F.h"
#include "TH2F.h"

namespace evt {
//-----------------------------------------------------------------------------
// --- Declare variables
//-----------------------------------------------------------------------------
double	GenEventInfoProduct_alphaQCD;
double	GenEventInfoProduct_alphaQED;
int	GenEventInfoProduct_hasBinningValues;
int	GenEventInfoProduct_hasPDF;
double	GenEventInfoProduct_qScale;
unsigned int	GenEventInfoProduct_signalProcessID;
double	GenEventInfoProduct_weight;
std::vector<int>	PileupSummaryInfo_getBunchCrossing(200,0);
std::vector<int>	PileupSummaryInfo_getPU_NumInteractions(200,0);
std::vector<float>	PileupSummaryInfo_getTrueNumInteractions(200,0);
int	edmEventHelper_bunchCrossing;
int	edmEventHelper_event;
int	edmEventHelper_isRealData;
int	edmEventHelper_luminosityBlock;
int	edmEventHelper_orbitNumber;
int	edmEventHelper_run;
int	nPileupSummaryInfo;
int	npatJetHelperCA8CHS;
int	npatJetHelperCA8CHSpruned;
int	npatJetHelperCA8CHStrimmed;
int	npatJetHelperGenCA8CHS;
int	npatJetHelperGenCA8CHSpruned;
int	npatJetHelperGenCA8CHStrimmed;
int	nrecoGenParticleHelper;
std::vector<float>	patJetHelperCA8CHS_C2beta05(200,0);
std::vector<float>	patJetHelperCA8CHS_C2beta10(200,0);
std::vector<float>	patJetHelperCA8CHS_C2beta15(200,0);
std::vector<float>	patJetHelperCA8CHS_C2beta17(200,0);
std::vector<float>	patJetHelperCA8CHS_C2beta20(200,0);
std::vector<float>	patJetHelperCA8CHS_C2beta25(200,0);
std::vector<float>	patJetHelperCA8CHS_chargedEmEnergyFraction(200,0);
std::vector<float>	patJetHelperCA8CHS_chargedHadronEnergyFraction(200,0);
std::vector<int>	patJetHelperCA8CHS_chargedMultiplicity(200,0);
std::vector<float>	patJetHelperCA8CHS_combinedSecondaryVertexBJetTags(200,0);
std::vector<double>	patJetHelperCA8CHS_energy(200,0);
std::vector<double>	patJetHelperCA8CHS_et(200,0);
std::vector<double>	patJetHelperCA8CHS_eta(200,0);
std::vector<int>	patJetHelperCA8CHS_getChargedPt0(200,0);
std::vector<int>	patJetHelperCA8CHS_getChargedPt1(200,0);
std::vector<int>	patJetHelperCA8CHS_getChargedPt2(200,0);
std::vector<int>	patJetHelperCA8CHS_getChargedPt3(200,0);
std::vector<float>	patJetHelperCA8CHS_getCorrectedPrunedJetMass(200,0);
std::vector<int>	patJetHelperCA8CHS_getNcharged01(200,0);
std::vector<int>	patJetHelperCA8CHS_getNneutral01(200,0);
std::vector<float>	patJetHelperCA8CHS_getPrunedJetMass(200,0);
std::vector<int>	patJetHelperCA8CHS_getPt0(200,0);
std::vector<int>	patJetHelperCA8CHS_getPt1(200,0);
std::vector<int>	patJetHelperCA8CHS_getPt2(200,0);
std::vector<int>	patJetHelperCA8CHS_getPt3(200,0);
std::vector<float>	patJetHelperCA8CHS_getSplitBlockPrunedJetMass(200,0);
std::vector<float>	patJetHelperCA8CHS_getTrackJetMass(200,0);
std::vector<float>	patJetHelperCA8CHS_jetArea(200,0);
std::vector<float>	patJetHelperCA8CHS_jetCharge03(200,0);
std::vector<float>	patJetHelperCA8CHS_jetCharge05(200,0);
std::vector<float>	patJetHelperCA8CHS_jetCharge10(200,0);
std::vector<double>	patJetHelperCA8CHS_mass(200,0);
std::vector<float>	patJetHelperCA8CHS_muonEnergyFraction(200,0);
std::vector<int>	patJetHelperCA8CHS_nConstituents(200,0);
std::vector<float>	patJetHelperCA8CHS_neutralEmEnergyFraction(200,0);
std::vector<float>	patJetHelperCA8CHS_neutralHadronEnergyFraction(200,0);
std::vector<int>	patJetHelperCA8CHS_partonFlavour(200,0);
std::vector<double>	patJetHelperCA8CHS_phi(200,0);
std::vector<float>	patJetHelperCA8CHS_photonEnergyFraction(200,0);
std::vector<double>	patJetHelperCA8CHS_pt(200,0);
std::vector<double>	patJetHelperCA8CHS_rapidity(200,0);
std::vector<float>	patJetHelperCA8CHS_tau1(200,0);
std::vector<float>	patJetHelperCA8CHS_tau2(200,0);
std::vector<float>	patJetHelperCA8CHS_tau3(200,0);
std::vector<double>	patJetHelperCA8CHS_uncor_energy(200,0);
std::vector<double>	patJetHelperCA8CHS_uncor_et(200,0);
std::vector<double>	patJetHelperCA8CHS_uncor_pt(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_energy(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_eta(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_0_jetCharge03(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_0_jetCharge05(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_0_jetCharge10(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_mass(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_phi(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_pt(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_0_rapidity(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_energy(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_eta(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_1_jetCharge03(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_1_jetCharge05(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_daughter_1_jetCharge10(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_mass(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_phi(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_pt(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_daughter_1_rapidity(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_energy(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_et(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_eta(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_jetArea(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_jetCharge03(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_jetCharge05(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_jetCharge10(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_mass(200,0);
std::vector<int>	patJetHelperCA8CHSpruned_nConstituents(200,0);
std::vector<size_t>	patJetHelperCA8CHSpruned_numberOfDaughters(200,0);
std::vector<int>	patJetHelperCA8CHSpruned_partonFlavour(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_phi(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_pt(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_rapidity(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_tau1(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_tau2(200,0);
std::vector<float>	patJetHelperCA8CHSpruned_tau3(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_uncor_energy(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_uncor_et(200,0);
std::vector<double>	patJetHelperCA8CHSpruned_uncor_pt(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_energy(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_et(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_eta(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_jetArea(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_jetCharge03(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_jetCharge05(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_jetCharge10(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_mass(200,0);
std::vector<int>	patJetHelperCA8CHStrimmed_nConstituents(200,0);
std::vector<size_t>	patJetHelperCA8CHStrimmed_numberOfDaughters(200,0);
std::vector<int>	patJetHelperCA8CHStrimmed_partonFlavour(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_phi(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_pt(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_rapidity(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_tau1(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_tau2(200,0);
std::vector<float>	patJetHelperCA8CHStrimmed_tau3(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_uncor_energy(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_uncor_et(200,0);
std::vector<double>	patJetHelperCA8CHStrimmed_uncor_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHS_energy(200,0);
std::vector<double>	patJetHelperGenCA8CHS_et(200,0);
std::vector<double>	patJetHelperGenCA8CHS_eta(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta05(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta10(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta15(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta17(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta17CHS(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta20(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genC2beta25(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genJetCharge03(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genJetCharge05(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genJetCharge10(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genNCHS(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau1(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau1CHS(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau1Pt2(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau1Pt5(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau2(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau2CHS(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau2Pt2(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau2Pt5(200,0);
std::vector<float>	patJetHelperGenCA8CHS_genTau3(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass0005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass001(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass002(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass01(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass02(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMass05(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF0005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF001(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF002(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF01(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF02(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPF05(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05(200,0);
std::vector<float>	patJetHelperGenCA8CHS_getGenTrackJetMass(200,0);
std::vector<float>	patJetHelperGenCA8CHS_jetArea(200,0);
std::vector<double>	patJetHelperGenCA8CHS_mass(200,0);
std::vector<int>	patJetHelperGenCA8CHS_nConstituents(200,0);
std::vector<int>	patJetHelperGenCA8CHS_partonFlavour(200,0);
std::vector<double>	patJetHelperGenCA8CHS_phi(200,0);
std::vector<double>	patJetHelperGenCA8CHS_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHS_rapidity(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_energy(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_eta(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_mass(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_phi(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_0_rapidity(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_energy(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_eta(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_mass(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_phi(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_daughter_1_rapidity(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_energy(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_et(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_eta(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_genTau1(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_genTau2(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_genTau3(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_jetArea(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_jetCharge03(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_jetCharge05(200,0);
std::vector<float>	patJetHelperGenCA8CHSpruned_jetCharge10(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_mass(200,0);
std::vector<int>	patJetHelperGenCA8CHSpruned_nConstituents(200,0);
std::vector<size_t>	patJetHelperGenCA8CHSpruned_numberOfDaughters(200,0);
std::vector<int>	patJetHelperGenCA8CHSpruned_partonFlavour(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_phi(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHSpruned_rapidity(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_energy(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_et(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_eta(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_genTau1(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_genTau2(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_genTau3(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_jetArea(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_jetCharge03(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_jetCharge05(200,0);
std::vector<float>	patJetHelperGenCA8CHStrimmed_jetCharge10(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_mass(200,0);
std::vector<int>	patJetHelperGenCA8CHStrimmed_nConstituents(200,0);
std::vector<size_t>	patJetHelperGenCA8CHStrimmed_numberOfDaughters(200,0);
std::vector<int>	patJetHelperGenCA8CHStrimmed_partonFlavour(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_phi(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_pt(200,0);
std::vector<double>	patJetHelperGenCA8CHStrimmed_rapidity(200,0);
std::vector<int>	recoGenParticleHelper_charge(10000,0);
std::vector<double>	recoGenParticleHelper_eta(10000,0);
std::vector<int>	recoGenParticleHelper_firstDaughter(10000,0);
std::vector<int>	recoGenParticleHelper_firstMother(10000,0);
std::vector<int>	recoGenParticleHelper_lastDaughter(10000,0);
std::vector<int>	recoGenParticleHelper_lastMother(10000,0);
std::vector<double>	recoGenParticleHelper_mass(10000,0);
std::vector<int>	recoGenParticleHelper_pdgId(10000,0);
std::vector<double>	recoGenParticleHelper_phi(10000,0);
std::vector<double>	recoGenParticleHelper_pt(10000,0);
std::vector<int>	recoGenParticleHelper_status(10000,0);

//-----------------------------------------------------------------------------
// --- indexmap keeps track of which objects have been flagged for selection
// --- IMPORTANT: initialize must be called every event to clear selection
std::map<std::string, std::vector<int> > indexmap;
void initialize()
{
  for(std::map<std::string, std::vector<int> >::iterator
    item=indexmap.begin(); 
    item != indexmap.end();
	++item)
	item->second.clear();
}

void select(std::string objname)
{
  indexmap[objname] = std::vector<int>();
}

void select(std::string objname, int index)
{
  try
    {
      indexmap[objname].push_back(index);
    }
  catch (...)
    {
      std::cout << "*** perhaps you failed to call select for " 
                << objname << std::endl;
      assert(0);
    }
}

//-----------------------------------------------------------------------------
// --- Structs can be filled by calling fillObjects()
// --- after the call to stream.read(...)
//-----------------------------------------------------------------------------
struct PileupSummaryInfo_s
{
  int	getPU_NumInteractions;
  int	getBunchCrossing;
  float	getTrueNumInteractions;
};
std::vector<PileupSummaryInfo_s> PileupSummaryInfo(200);

std::ostream& operator<<(std::ostream& os, const PileupSummaryInfo_s& o)
{
  char r[1024];
  os << "PileupSummaryInfo" << std::endl;
  sprintf(r, "  %-32s: %f\n", "getPU_NumInteractions", (double)o.getPU_NumInteractions); os << r;
  sprintf(r, "  %-32s: %f\n", "getBunchCrossing", (double)o.getBunchCrossing); os << r;
  sprintf(r, "  %-32s: %f\n", "getTrueNumInteractions", (double)o.getTrueNumInteractions); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperCA8CHS_s
{
  double	energy;
  double	uncor_energy;
  double	et;
  double	uncor_et;
  double	pt;
  double	uncor_pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	jetCharge03;
  float	jetCharge05;
  float	jetCharge10;
  float	chargedHadronEnergyFraction;
  float	neutralHadronEnergyFraction;
  float	chargedEmEnergyFraction;
  float	neutralEmEnergyFraction;
  float	photonEnergyFraction;
  float	muonEnergyFraction;
  int	chargedMultiplicity;
  int	nConstituents;
  int	partonFlavour;
  float	combinedSecondaryVertexBJetTags;
  float	tau1;
  float	tau2;
  float	tau3;
  float	C2beta05;
  float	C2beta10;
  float	C2beta15;
  float	C2beta17;
  float	C2beta20;
  float	C2beta25;
  float	getPrunedJetMass;
  float	getCorrectedPrunedJetMass;
  float	getSplitBlockPrunedJetMass;
  float	getTrackJetMass;
  int	getNcharged01;
  int	getNneutral01;
  int	getChargedPt0;
  int	getChargedPt1;
  int	getChargedPt2;
  int	getChargedPt3;
  int	getPt0;
  int	getPt1;
  int	getPt2;
  int	getPt3;
};
std::vector<patJetHelperCA8CHS_s> patJetHelperCA8CHS(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperCA8CHS_s& o)
{
  char r[1024];
  os << "patJetHelperCA8CHS" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_energy", (double)o.uncor_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_et", (double)o.uncor_et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_pt", (double)o.uncor_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge03", (double)o.jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge05", (double)o.jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge10", (double)o.jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedHadronEnergyFraction", (double)o.chargedHadronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralHadronEnergyFraction", (double)o.neutralHadronEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedEmEnergyFraction", (double)o.chargedEmEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "neutralEmEnergyFraction", (double)o.neutralEmEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "photonEnergyFraction", (double)o.photonEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "muonEnergyFraction", (double)o.muonEnergyFraction); os << r;
  sprintf(r, "  %-32s: %f\n", "chargedMultiplicity", (double)o.chargedMultiplicity); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "combinedSecondaryVertexBJetTags", (double)o.combinedSecondaryVertexBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "tau1", (double)o.tau1); os << r;
  sprintf(r, "  %-32s: %f\n", "tau2", (double)o.tau2); os << r;
  sprintf(r, "  %-32s: %f\n", "tau3", (double)o.tau3); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta05", (double)o.C2beta05); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta10", (double)o.C2beta10); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta15", (double)o.C2beta15); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta17", (double)o.C2beta17); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta20", (double)o.C2beta20); os << r;
  sprintf(r, "  %-32s: %f\n", "C2beta25", (double)o.C2beta25); os << r;
  sprintf(r, "  %-32s: %f\n", "getPrunedJetMass", (double)o.getPrunedJetMass); os << r;
  sprintf(r, "  %-32s: %f\n", "getCorrectedPrunedJetMass", (double)o.getCorrectedPrunedJetMass); os << r;
  sprintf(r, "  %-32s: %f\n", "getSplitBlockPrunedJetMass", (double)o.getSplitBlockPrunedJetMass); os << r;
  sprintf(r, "  %-32s: %f\n", "getTrackJetMass", (double)o.getTrackJetMass); os << r;
  sprintf(r, "  %-32s: %f\n", "getNcharged01", (double)o.getNcharged01); os << r;
  sprintf(r, "  %-32s: %f\n", "getNneutral01", (double)o.getNneutral01); os << r;
  sprintf(r, "  %-32s: %f\n", "getChargedPt0", (double)o.getChargedPt0); os << r;
  sprintf(r, "  %-32s: %f\n", "getChargedPt1", (double)o.getChargedPt1); os << r;
  sprintf(r, "  %-32s: %f\n", "getChargedPt2", (double)o.getChargedPt2); os << r;
  sprintf(r, "  %-32s: %f\n", "getChargedPt3", (double)o.getChargedPt3); os << r;
  sprintf(r, "  %-32s: %f\n", "getPt0", (double)o.getPt0); os << r;
  sprintf(r, "  %-32s: %f\n", "getPt1", (double)o.getPt1); os << r;
  sprintf(r, "  %-32s: %f\n", "getPt2", (double)o.getPt2); os << r;
  sprintf(r, "  %-32s: %f\n", "getPt3", (double)o.getPt3); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperCA8CHSpruned_s
{
  double	energy;
  double	uncor_energy;
  double	et;
  double	uncor_et;
  double	pt;
  double	uncor_pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	jetCharge03;
  float	jetCharge05;
  float	jetCharge10;
  int	nConstituents;
  int	partonFlavour;
  size_t	numberOfDaughters;
  double	daughter_0_energy;
  double	daughter_0_pt;
  double	daughter_0_eta;
  double	daughter_0_rapidity;
  double	daughter_0_phi;
  double	daughter_0_mass;
  double	daughter_1_energy;
  double	daughter_1_pt;
  double	daughter_1_eta;
  double	daughter_1_rapidity;
  double	daughter_1_phi;
  double	daughter_1_mass;
  float	tau1;
  float	tau2;
  float	tau3;
  float	daughter_0_jetCharge03;
  float	daughter_0_jetCharge05;
  float	daughter_0_jetCharge10;
  float	daughter_1_jetCharge03;
  float	daughter_1_jetCharge05;
  float	daughter_1_jetCharge10;
  float	daughter_0_combinedSecondaryVertexBJetTags;
  float	daughter_1_combinedSecondaryVertexBJetTags;
};
std::vector<patJetHelperCA8CHSpruned_s> patJetHelperCA8CHSpruned(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperCA8CHSpruned_s& o)
{
  char r[1024];
  os << "patJetHelperCA8CHSpruned" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_energy", (double)o.uncor_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_et", (double)o.uncor_et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_pt", (double)o.uncor_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge03", (double)o.jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge05", (double)o.jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge10", (double)o.jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_energy", (double)o.daughter_0_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_pt", (double)o.daughter_0_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_eta", (double)o.daughter_0_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_rapidity", (double)o.daughter_0_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_phi", (double)o.daughter_0_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_mass", (double)o.daughter_0_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_energy", (double)o.daughter_1_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_pt", (double)o.daughter_1_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_eta", (double)o.daughter_1_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_rapidity", (double)o.daughter_1_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_phi", (double)o.daughter_1_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_mass", (double)o.daughter_1_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "tau1", (double)o.tau1); os << r;
  sprintf(r, "  %-32s: %f\n", "tau2", (double)o.tau2); os << r;
  sprintf(r, "  %-32s: %f\n", "tau3", (double)o.tau3); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_jetCharge03", (double)o.daughter_0_jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_jetCharge05", (double)o.daughter_0_jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_jetCharge10", (double)o.daughter_0_jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_jetCharge03", (double)o.daughter_1_jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_jetCharge05", (double)o.daughter_1_jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_jetCharge10", (double)o.daughter_1_jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_combinedSecondaryVertexBJetTags", (double)o.daughter_0_combinedSecondaryVertexBJetTags); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_combinedSecondaryVertexBJetTags", (double)o.daughter_1_combinedSecondaryVertexBJetTags); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperCA8CHStrimmed_s
{
  double	energy;
  double	uncor_energy;
  double	et;
  double	uncor_et;
  double	pt;
  double	uncor_pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	jetCharge03;
  float	jetCharge05;
  float	jetCharge10;
  int	nConstituents;
  int	partonFlavour;
  size_t	numberOfDaughters;
  float	tau1;
  float	tau2;
  float	tau3;
};
std::vector<patJetHelperCA8CHStrimmed_s> patJetHelperCA8CHStrimmed(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperCA8CHStrimmed_s& o)
{
  char r[1024];
  os << "patJetHelperCA8CHStrimmed" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_energy", (double)o.uncor_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_et", (double)o.uncor_et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "uncor_pt", (double)o.uncor_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge03", (double)o.jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge05", (double)o.jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge10", (double)o.jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  sprintf(r, "  %-32s: %f\n", "tau1", (double)o.tau1); os << r;
  sprintf(r, "  %-32s: %f\n", "tau2", (double)o.tau2); os << r;
  sprintf(r, "  %-32s: %f\n", "tau3", (double)o.tau3); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperGenCA8CHS_s
{
  double	energy;
  double	et;
  double	pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	genJetCharge03;
  float	genJetCharge05;
  float	genJetCharge10;
  int	nConstituents;
  int	partonFlavour;
  float	genC2beta05;
  float	genC2beta10;
  float	genC2beta15;
  float	genC2beta17;
  float	genC2beta20;
  float	genC2beta25;
  float	genC2beta17CHS;
  float	genTau1;
  float	genTau2;
  float	genTau3;
  float	genTau1Pt2;
  float	genTau2Pt2;
  float	genTau1Pt5;
  float	genTau2Pt5;
  float	genTau1CHS;
  float	genTau2CHS;
  float	getGenCaloJetMass0005;
  float	getGenCaloJetMass001;
  float	getGenCaloJetMass002;
  float	getGenCaloJetMass005;
  float	getGenCaloJetMass01;
  float	getGenCaloJetMass02;
  float	getGenCaloJetMass05;
  float	getGenCaloJetMassPF0005;
  float	getGenCaloJetMassPF001;
  float	getGenCaloJetMassPF002;
  float	getGenCaloJetMassPF005;
  float	getGenCaloJetMassPF01;
  float	getGenCaloJetMassPF02;
  float	getGenCaloJetMassPF05;
  float	getGenCaloJetMassPFcorrect0005;
  float	getGenCaloJetMassPFcorrect001;
  float	getGenCaloJetMassPFcorrect002;
  float	getGenCaloJetMassPFcorrect005;
  float	getGenCaloJetMassPFcorrect01;
  float	getGenCaloJetMassPFcorrect02;
  float	getGenCaloJetMassPFcorrect05;
  float	getGenTrackJetMass;
  float	genNCHS;
};
std::vector<patJetHelperGenCA8CHS_s> patJetHelperGenCA8CHS(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperGenCA8CHS_s& o)
{
  char r[1024];
  os << "patJetHelperGenCA8CHS" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "genJetCharge03", (double)o.genJetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "genJetCharge05", (double)o.genJetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "genJetCharge10", (double)o.genJetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta05", (double)o.genC2beta05); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta10", (double)o.genC2beta10); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta15", (double)o.genC2beta15); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta17", (double)o.genC2beta17); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta20", (double)o.genC2beta20); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta25", (double)o.genC2beta25); os << r;
  sprintf(r, "  %-32s: %f\n", "genC2beta17CHS", (double)o.genC2beta17CHS); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1", (double)o.genTau1); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2", (double)o.genTau2); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau3", (double)o.genTau3); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1Pt2", (double)o.genTau1Pt2); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2Pt2", (double)o.genTau2Pt2); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1Pt5", (double)o.genTau1Pt5); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2Pt5", (double)o.genTau2Pt5); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1CHS", (double)o.genTau1CHS); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2CHS", (double)o.genTau2CHS); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass0005", (double)o.getGenCaloJetMass0005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass001", (double)o.getGenCaloJetMass001); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass002", (double)o.getGenCaloJetMass002); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass005", (double)o.getGenCaloJetMass005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass01", (double)o.getGenCaloJetMass01); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass02", (double)o.getGenCaloJetMass02); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMass05", (double)o.getGenCaloJetMass05); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF0005", (double)o.getGenCaloJetMassPF0005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF001", (double)o.getGenCaloJetMassPF001); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF002", (double)o.getGenCaloJetMassPF002); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF005", (double)o.getGenCaloJetMassPF005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF01", (double)o.getGenCaloJetMassPF01); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF02", (double)o.getGenCaloJetMassPF02); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPF05", (double)o.getGenCaloJetMassPF05); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect0005", (double)o.getGenCaloJetMassPFcorrect0005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect001", (double)o.getGenCaloJetMassPFcorrect001); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect002", (double)o.getGenCaloJetMassPFcorrect002); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect005", (double)o.getGenCaloJetMassPFcorrect005); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect01", (double)o.getGenCaloJetMassPFcorrect01); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect02", (double)o.getGenCaloJetMassPFcorrect02); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenCaloJetMassPFcorrect05", (double)o.getGenCaloJetMassPFcorrect05); os << r;
  sprintf(r, "  %-32s: %f\n", "getGenTrackJetMass", (double)o.getGenTrackJetMass); os << r;
  sprintf(r, "  %-32s: %f\n", "genNCHS", (double)o.genNCHS); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperGenCA8CHSpruned_s
{
  double	energy;
  double	et;
  double	pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	jetCharge03;
  float	jetCharge05;
  float	jetCharge10;
  int	nConstituents;
  int	partonFlavour;
  size_t	numberOfDaughters;
  double	daughter_0_energy;
  double	daughter_0_pt;
  double	daughter_0_eta;
  double	daughter_0_rapidity;
  double	daughter_0_phi;
  double	daughter_0_mass;
  double	daughter_1_energy;
  double	daughter_1_pt;
  double	daughter_1_eta;
  double	daughter_1_rapidity;
  double	daughter_1_phi;
  double	daughter_1_mass;
  float	genTau1;
  float	genTau2;
  float	genTau3;
};
std::vector<patJetHelperGenCA8CHSpruned_s> patJetHelperGenCA8CHSpruned(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperGenCA8CHSpruned_s& o)
{
  char r[1024];
  os << "patJetHelperGenCA8CHSpruned" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge03", (double)o.jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge05", (double)o.jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge10", (double)o.jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_energy", (double)o.daughter_0_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_pt", (double)o.daughter_0_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_eta", (double)o.daughter_0_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_rapidity", (double)o.daughter_0_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_phi", (double)o.daughter_0_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_0_mass", (double)o.daughter_0_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_energy", (double)o.daughter_1_energy); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_pt", (double)o.daughter_1_pt); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_eta", (double)o.daughter_1_eta); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_rapidity", (double)o.daughter_1_rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_phi", (double)o.daughter_1_phi); os << r;
  sprintf(r, "  %-32s: %f\n", "daughter_1_mass", (double)o.daughter_1_mass); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1", (double)o.genTau1); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2", (double)o.genTau2); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau3", (double)o.genTau3); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct patJetHelperGenCA8CHStrimmed_s
{
  double	energy;
  double	et;
  double	pt;
  double	phi;
  double	eta;
  double	rapidity;
  double	mass;
  float	jetArea;
  float	jetCharge03;
  float	jetCharge05;
  float	jetCharge10;
  int	nConstituents;
  int	partonFlavour;
  size_t	numberOfDaughters;
  float	genTau1;
  float	genTau2;
  float	genTau3;
};
std::vector<patJetHelperGenCA8CHStrimmed_s> patJetHelperGenCA8CHStrimmed(200);

std::ostream& operator<<(std::ostream& os, const patJetHelperGenCA8CHStrimmed_s& o)
{
  char r[1024];
  os << "patJetHelperGenCA8CHStrimmed" << std::endl;
  sprintf(r, "  %-32s: %f\n", "energy", (double)o.energy); os << r;
  sprintf(r, "  %-32s: %f\n", "et", (double)o.et); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "rapidity", (double)o.rapidity); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  sprintf(r, "  %-32s: %f\n", "jetArea", (double)o.jetArea); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge03", (double)o.jetCharge03); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge05", (double)o.jetCharge05); os << r;
  sprintf(r, "  %-32s: %f\n", "jetCharge10", (double)o.jetCharge10); os << r;
  sprintf(r, "  %-32s: %f\n", "nConstituents", (double)o.nConstituents); os << r;
  sprintf(r, "  %-32s: %f\n", "partonFlavour", (double)o.partonFlavour); os << r;
  sprintf(r, "  %-32s: %f\n", "numberOfDaughters", (double)o.numberOfDaughters); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau1", (double)o.genTau1); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau2", (double)o.genTau2); os << r;
  sprintf(r, "  %-32s: %f\n", "genTau3", (double)o.genTau3); os << r;
  return os;
}
//-----------------------------------------------------------------------------
struct recoGenParticleHelper_s
{
  int	firstMother;
  int	lastMother;
  int	firstDaughter;
  int	lastDaughter;
  int	charge;
  int	pdgId;
  int	status;
  double	pt;
  double	eta;
  double	phi;
  double	mass;
};
std::vector<recoGenParticleHelper_s> recoGenParticleHelper(10000);

std::ostream& operator<<(std::ostream& os, const recoGenParticleHelper_s& o)
{
  char r[1024];
  os << "recoGenParticleHelper" << std::endl;
  sprintf(r, "  %-32s: %f\n", "firstMother", (double)o.firstMother); os << r;
  sprintf(r, "  %-32s: %f\n", "lastMother", (double)o.lastMother); os << r;
  sprintf(r, "  %-32s: %f\n", "firstDaughter", (double)o.firstDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "lastDaughter", (double)o.lastDaughter); os << r;
  sprintf(r, "  %-32s: %f\n", "charge", (double)o.charge); os << r;
  sprintf(r, "  %-32s: %f\n", "pdgId", (double)o.pdgId); os << r;
  sprintf(r, "  %-32s: %f\n", "status", (double)o.status); os << r;
  sprintf(r, "  %-32s: %f\n", "pt", (double)o.pt); os << r;
  sprintf(r, "  %-32s: %f\n", "eta", (double)o.eta); os << r;
  sprintf(r, "  %-32s: %f\n", "phi", (double)o.phi); os << r;
  sprintf(r, "  %-32s: %f\n", "mass", (double)o.mass); os << r;
  return os;
}
//-----------------------------------------------------------------------------

inline void fillPileupSummaryInfo()
{
  PileupSummaryInfo.resize(PileupSummaryInfo_getPU_NumInteractions.size());
  for(unsigned int i=0; i < PileupSummaryInfo.size(); ++i)
    {
      PileupSummaryInfo[i].getPU_NumInteractions	= PileupSummaryInfo_getPU_NumInteractions[i];
      PileupSummaryInfo[i].getBunchCrossing	= PileupSummaryInfo_getBunchCrossing[i];
      PileupSummaryInfo[i].getTrueNumInteractions	= PileupSummaryInfo_getTrueNumInteractions[i];
    }
}

inline void fillpatJetHelperCA8CHS()
{
  patJetHelperCA8CHS.resize(patJetHelperCA8CHS_energy.size());
  for(unsigned int i=0; i < patJetHelperCA8CHS.size(); ++i)
    {
      patJetHelperCA8CHS[i].energy	= patJetHelperCA8CHS_energy[i];
      patJetHelperCA8CHS[i].uncor_energy	= patJetHelperCA8CHS_uncor_energy[i];
      patJetHelperCA8CHS[i].et	= patJetHelperCA8CHS_et[i];
      patJetHelperCA8CHS[i].uncor_et	= patJetHelperCA8CHS_uncor_et[i];
      patJetHelperCA8CHS[i].pt	= patJetHelperCA8CHS_pt[i];
      patJetHelperCA8CHS[i].uncor_pt	= patJetHelperCA8CHS_uncor_pt[i];
      patJetHelperCA8CHS[i].phi	= patJetHelperCA8CHS_phi[i];
      patJetHelperCA8CHS[i].eta	= patJetHelperCA8CHS_eta[i];
      patJetHelperCA8CHS[i].rapidity	= patJetHelperCA8CHS_rapidity[i];
      patJetHelperCA8CHS[i].mass	= patJetHelperCA8CHS_mass[i];
      patJetHelperCA8CHS[i].jetArea	= patJetHelperCA8CHS_jetArea[i];
      patJetHelperCA8CHS[i].jetCharge03	= patJetHelperCA8CHS_jetCharge03[i];
      patJetHelperCA8CHS[i].jetCharge05	= patJetHelperCA8CHS_jetCharge05[i];
      patJetHelperCA8CHS[i].jetCharge10	= patJetHelperCA8CHS_jetCharge10[i];
      patJetHelperCA8CHS[i].chargedHadronEnergyFraction	= patJetHelperCA8CHS_chargedHadronEnergyFraction[i];
      patJetHelperCA8CHS[i].neutralHadronEnergyFraction	= patJetHelperCA8CHS_neutralHadronEnergyFraction[i];
      patJetHelperCA8CHS[i].chargedEmEnergyFraction	= patJetHelperCA8CHS_chargedEmEnergyFraction[i];
      patJetHelperCA8CHS[i].neutralEmEnergyFraction	= patJetHelperCA8CHS_neutralEmEnergyFraction[i];
      patJetHelperCA8CHS[i].photonEnergyFraction	= patJetHelperCA8CHS_photonEnergyFraction[i];
      patJetHelperCA8CHS[i].muonEnergyFraction	= patJetHelperCA8CHS_muonEnergyFraction[i];
      patJetHelperCA8CHS[i].chargedMultiplicity	= patJetHelperCA8CHS_chargedMultiplicity[i];
      patJetHelperCA8CHS[i].nConstituents	= patJetHelperCA8CHS_nConstituents[i];
      patJetHelperCA8CHS[i].partonFlavour	= patJetHelperCA8CHS_partonFlavour[i];
      patJetHelperCA8CHS[i].combinedSecondaryVertexBJetTags	= patJetHelperCA8CHS_combinedSecondaryVertexBJetTags[i];
      patJetHelperCA8CHS[i].tau1	= patJetHelperCA8CHS_tau1[i];
      patJetHelperCA8CHS[i].tau2	= patJetHelperCA8CHS_tau2[i];
      patJetHelperCA8CHS[i].tau3	= patJetHelperCA8CHS_tau3[i];
      patJetHelperCA8CHS[i].C2beta05	= patJetHelperCA8CHS_C2beta05[i];
      patJetHelperCA8CHS[i].C2beta10	= patJetHelperCA8CHS_C2beta10[i];
      patJetHelperCA8CHS[i].C2beta15	= patJetHelperCA8CHS_C2beta15[i];
      patJetHelperCA8CHS[i].C2beta17	= patJetHelperCA8CHS_C2beta17[i];
      patJetHelperCA8CHS[i].C2beta20	= patJetHelperCA8CHS_C2beta20[i];
      patJetHelperCA8CHS[i].C2beta25	= patJetHelperCA8CHS_C2beta25[i];
      patJetHelperCA8CHS[i].getPrunedJetMass	= patJetHelperCA8CHS_getPrunedJetMass[i];
      patJetHelperCA8CHS[i].getCorrectedPrunedJetMass	= patJetHelperCA8CHS_getCorrectedPrunedJetMass[i];
      patJetHelperCA8CHS[i].getSplitBlockPrunedJetMass	= patJetHelperCA8CHS_getSplitBlockPrunedJetMass[i];
      patJetHelperCA8CHS[i].getTrackJetMass	= patJetHelperCA8CHS_getTrackJetMass[i];
      patJetHelperCA8CHS[i].getNcharged01	= patJetHelperCA8CHS_getNcharged01[i];
      patJetHelperCA8CHS[i].getNneutral01	= patJetHelperCA8CHS_getNneutral01[i];
      patJetHelperCA8CHS[i].getChargedPt0	= patJetHelperCA8CHS_getChargedPt0[i];
      patJetHelperCA8CHS[i].getChargedPt1	= patJetHelperCA8CHS_getChargedPt1[i];
      patJetHelperCA8CHS[i].getChargedPt2	= patJetHelperCA8CHS_getChargedPt2[i];
      patJetHelperCA8CHS[i].getChargedPt3	= patJetHelperCA8CHS_getChargedPt3[i];
      patJetHelperCA8CHS[i].getPt0	= patJetHelperCA8CHS_getPt0[i];
      patJetHelperCA8CHS[i].getPt1	= patJetHelperCA8CHS_getPt1[i];
      patJetHelperCA8CHS[i].getPt2	= patJetHelperCA8CHS_getPt2[i];
      patJetHelperCA8CHS[i].getPt3	= patJetHelperCA8CHS_getPt3[i];
    }
}

inline void fillpatJetHelperCA8CHSpruned()
{
  patJetHelperCA8CHSpruned.resize(patJetHelperCA8CHSpruned_energy.size());
  for(unsigned int i=0; i < patJetHelperCA8CHSpruned.size(); ++i)
    {
      patJetHelperCA8CHSpruned[i].energy	= patJetHelperCA8CHSpruned_energy[i];
      patJetHelperCA8CHSpruned[i].uncor_energy	= patJetHelperCA8CHSpruned_uncor_energy[i];
      patJetHelperCA8CHSpruned[i].et	= patJetHelperCA8CHSpruned_et[i];
      patJetHelperCA8CHSpruned[i].uncor_et	= patJetHelperCA8CHSpruned_uncor_et[i];
      patJetHelperCA8CHSpruned[i].pt	= patJetHelperCA8CHSpruned_pt[i];
      patJetHelperCA8CHSpruned[i].uncor_pt	= patJetHelperCA8CHSpruned_uncor_pt[i];
      patJetHelperCA8CHSpruned[i].phi	= patJetHelperCA8CHSpruned_phi[i];
      patJetHelperCA8CHSpruned[i].eta	= patJetHelperCA8CHSpruned_eta[i];
      patJetHelperCA8CHSpruned[i].rapidity	= patJetHelperCA8CHSpruned_rapidity[i];
      patJetHelperCA8CHSpruned[i].mass	= patJetHelperCA8CHSpruned_mass[i];
      patJetHelperCA8CHSpruned[i].jetArea	= patJetHelperCA8CHSpruned_jetArea[i];
      patJetHelperCA8CHSpruned[i].jetCharge03	= patJetHelperCA8CHSpruned_jetCharge03[i];
      patJetHelperCA8CHSpruned[i].jetCharge05	= patJetHelperCA8CHSpruned_jetCharge05[i];
      patJetHelperCA8CHSpruned[i].jetCharge10	= patJetHelperCA8CHSpruned_jetCharge10[i];
      patJetHelperCA8CHSpruned[i].nConstituents	= patJetHelperCA8CHSpruned_nConstituents[i];
      patJetHelperCA8CHSpruned[i].partonFlavour	= patJetHelperCA8CHSpruned_partonFlavour[i];
      patJetHelperCA8CHSpruned[i].numberOfDaughters	= patJetHelperCA8CHSpruned_numberOfDaughters[i];
      patJetHelperCA8CHSpruned[i].daughter_0_energy	= patJetHelperCA8CHSpruned_daughter_0_energy[i];
      patJetHelperCA8CHSpruned[i].daughter_0_pt	= patJetHelperCA8CHSpruned_daughter_0_pt[i];
      patJetHelperCA8CHSpruned[i].daughter_0_eta	= patJetHelperCA8CHSpruned_daughter_0_eta[i];
      patJetHelperCA8CHSpruned[i].daughter_0_rapidity	= patJetHelperCA8CHSpruned_daughter_0_rapidity[i];
      patJetHelperCA8CHSpruned[i].daughter_0_phi	= patJetHelperCA8CHSpruned_daughter_0_phi[i];
      patJetHelperCA8CHSpruned[i].daughter_0_mass	= patJetHelperCA8CHSpruned_daughter_0_mass[i];
      patJetHelperCA8CHSpruned[i].daughter_1_energy	= patJetHelperCA8CHSpruned_daughter_1_energy[i];
      patJetHelperCA8CHSpruned[i].daughter_1_pt	= patJetHelperCA8CHSpruned_daughter_1_pt[i];
      patJetHelperCA8CHSpruned[i].daughter_1_eta	= patJetHelperCA8CHSpruned_daughter_1_eta[i];
      patJetHelperCA8CHSpruned[i].daughter_1_rapidity	= patJetHelperCA8CHSpruned_daughter_1_rapidity[i];
      patJetHelperCA8CHSpruned[i].daughter_1_phi	= patJetHelperCA8CHSpruned_daughter_1_phi[i];
      patJetHelperCA8CHSpruned[i].daughter_1_mass	= patJetHelperCA8CHSpruned_daughter_1_mass[i];
      patJetHelperCA8CHSpruned[i].tau1	= patJetHelperCA8CHSpruned_tau1[i];
      patJetHelperCA8CHSpruned[i].tau2	= patJetHelperCA8CHSpruned_tau2[i];
      patJetHelperCA8CHSpruned[i].tau3	= patJetHelperCA8CHSpruned_tau3[i];
      patJetHelperCA8CHSpruned[i].daughter_0_jetCharge03	= patJetHelperCA8CHSpruned_daughter_0_jetCharge03[i];
      patJetHelperCA8CHSpruned[i].daughter_0_jetCharge05	= patJetHelperCA8CHSpruned_daughter_0_jetCharge05[i];
      patJetHelperCA8CHSpruned[i].daughter_0_jetCharge10	= patJetHelperCA8CHSpruned_daughter_0_jetCharge10[i];
      patJetHelperCA8CHSpruned[i].daughter_1_jetCharge03	= patJetHelperCA8CHSpruned_daughter_1_jetCharge03[i];
      patJetHelperCA8CHSpruned[i].daughter_1_jetCharge05	= patJetHelperCA8CHSpruned_daughter_1_jetCharge05[i];
      patJetHelperCA8CHSpruned[i].daughter_1_jetCharge10	= patJetHelperCA8CHSpruned_daughter_1_jetCharge10[i];
      patJetHelperCA8CHSpruned[i].daughter_0_combinedSecondaryVertexBJetTags	= patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags[i];
      patJetHelperCA8CHSpruned[i].daughter_1_combinedSecondaryVertexBJetTags	= patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags[i];
    }
}

inline void fillpatJetHelperCA8CHStrimmed()
{
  patJetHelperCA8CHStrimmed.resize(patJetHelperCA8CHStrimmed_energy.size());
  for(unsigned int i=0; i < patJetHelperCA8CHStrimmed.size(); ++i)
    {
      patJetHelperCA8CHStrimmed[i].energy	= patJetHelperCA8CHStrimmed_energy[i];
      patJetHelperCA8CHStrimmed[i].uncor_energy	= patJetHelperCA8CHStrimmed_uncor_energy[i];
      patJetHelperCA8CHStrimmed[i].et	= patJetHelperCA8CHStrimmed_et[i];
      patJetHelperCA8CHStrimmed[i].uncor_et	= patJetHelperCA8CHStrimmed_uncor_et[i];
      patJetHelperCA8CHStrimmed[i].pt	= patJetHelperCA8CHStrimmed_pt[i];
      patJetHelperCA8CHStrimmed[i].uncor_pt	= patJetHelperCA8CHStrimmed_uncor_pt[i];
      patJetHelperCA8CHStrimmed[i].phi	= patJetHelperCA8CHStrimmed_phi[i];
      patJetHelperCA8CHStrimmed[i].eta	= patJetHelperCA8CHStrimmed_eta[i];
      patJetHelperCA8CHStrimmed[i].rapidity	= patJetHelperCA8CHStrimmed_rapidity[i];
      patJetHelperCA8CHStrimmed[i].mass	= patJetHelperCA8CHStrimmed_mass[i];
      patJetHelperCA8CHStrimmed[i].jetArea	= patJetHelperCA8CHStrimmed_jetArea[i];
      patJetHelperCA8CHStrimmed[i].jetCharge03	= patJetHelperCA8CHStrimmed_jetCharge03[i];
      patJetHelperCA8CHStrimmed[i].jetCharge05	= patJetHelperCA8CHStrimmed_jetCharge05[i];
      patJetHelperCA8CHStrimmed[i].jetCharge10	= patJetHelperCA8CHStrimmed_jetCharge10[i];
      patJetHelperCA8CHStrimmed[i].nConstituents	= patJetHelperCA8CHStrimmed_nConstituents[i];
      patJetHelperCA8CHStrimmed[i].partonFlavour	= patJetHelperCA8CHStrimmed_partonFlavour[i];
      patJetHelperCA8CHStrimmed[i].numberOfDaughters	= patJetHelperCA8CHStrimmed_numberOfDaughters[i];
      patJetHelperCA8CHStrimmed[i].tau1	= patJetHelperCA8CHStrimmed_tau1[i];
      patJetHelperCA8CHStrimmed[i].tau2	= patJetHelperCA8CHStrimmed_tau2[i];
      patJetHelperCA8CHStrimmed[i].tau3	= patJetHelperCA8CHStrimmed_tau3[i];
    }
}

inline void fillpatJetHelperGenCA8CHS()
{
  patJetHelperGenCA8CHS.resize(patJetHelperGenCA8CHS_energy.size());
  for(unsigned int i=0; i < patJetHelperGenCA8CHS.size(); ++i)
    {
      patJetHelperGenCA8CHS[i].energy	= patJetHelperGenCA8CHS_energy[i];
      patJetHelperGenCA8CHS[i].et	= patJetHelperGenCA8CHS_et[i];
      patJetHelperGenCA8CHS[i].pt	= patJetHelperGenCA8CHS_pt[i];
      patJetHelperGenCA8CHS[i].phi	= patJetHelperGenCA8CHS_phi[i];
      patJetHelperGenCA8CHS[i].eta	= patJetHelperGenCA8CHS_eta[i];
      patJetHelperGenCA8CHS[i].rapidity	= patJetHelperGenCA8CHS_rapidity[i];
      patJetHelperGenCA8CHS[i].mass	= patJetHelperGenCA8CHS_mass[i];
      patJetHelperGenCA8CHS[i].jetArea	= patJetHelperGenCA8CHS_jetArea[i];
      patJetHelperGenCA8CHS[i].genJetCharge03	= patJetHelperGenCA8CHS_genJetCharge03[i];
      patJetHelperGenCA8CHS[i].genJetCharge05	= patJetHelperGenCA8CHS_genJetCharge05[i];
      patJetHelperGenCA8CHS[i].genJetCharge10	= patJetHelperGenCA8CHS_genJetCharge10[i];
      patJetHelperGenCA8CHS[i].nConstituents	= patJetHelperGenCA8CHS_nConstituents[i];
      patJetHelperGenCA8CHS[i].partonFlavour	= patJetHelperGenCA8CHS_partonFlavour[i];
      patJetHelperGenCA8CHS[i].genC2beta05	= patJetHelperGenCA8CHS_genC2beta05[i];
      patJetHelperGenCA8CHS[i].genC2beta10	= patJetHelperGenCA8CHS_genC2beta10[i];
      patJetHelperGenCA8CHS[i].genC2beta15	= patJetHelperGenCA8CHS_genC2beta15[i];
      patJetHelperGenCA8CHS[i].genC2beta17	= patJetHelperGenCA8CHS_genC2beta17[i];
      patJetHelperGenCA8CHS[i].genC2beta20	= patJetHelperGenCA8CHS_genC2beta20[i];
      patJetHelperGenCA8CHS[i].genC2beta25	= patJetHelperGenCA8CHS_genC2beta25[i];
      patJetHelperGenCA8CHS[i].genC2beta17CHS	= patJetHelperGenCA8CHS_genC2beta17CHS[i];
      patJetHelperGenCA8CHS[i].genTau1	= patJetHelperGenCA8CHS_genTau1[i];
      patJetHelperGenCA8CHS[i].genTau2	= patJetHelperGenCA8CHS_genTau2[i];
      patJetHelperGenCA8CHS[i].genTau3	= patJetHelperGenCA8CHS_genTau3[i];
      patJetHelperGenCA8CHS[i].genTau1Pt2	= patJetHelperGenCA8CHS_genTau1Pt2[i];
      patJetHelperGenCA8CHS[i].genTau2Pt2	= patJetHelperGenCA8CHS_genTau2Pt2[i];
      patJetHelperGenCA8CHS[i].genTau1Pt5	= patJetHelperGenCA8CHS_genTau1Pt5[i];
      patJetHelperGenCA8CHS[i].genTau2Pt5	= patJetHelperGenCA8CHS_genTau2Pt5[i];
      patJetHelperGenCA8CHS[i].genTau1CHS	= patJetHelperGenCA8CHS_genTau1CHS[i];
      patJetHelperGenCA8CHS[i].genTau2CHS	= patJetHelperGenCA8CHS_genTau2CHS[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass0005	= patJetHelperGenCA8CHS_getGenCaloJetMass0005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass001	= patJetHelperGenCA8CHS_getGenCaloJetMass001[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass002	= patJetHelperGenCA8CHS_getGenCaloJetMass002[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass005	= patJetHelperGenCA8CHS_getGenCaloJetMass005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass01	= patJetHelperGenCA8CHS_getGenCaloJetMass01[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass02	= patJetHelperGenCA8CHS_getGenCaloJetMass02[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMass05	= patJetHelperGenCA8CHS_getGenCaloJetMass05[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF0005	= patJetHelperGenCA8CHS_getGenCaloJetMassPF0005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF001	= patJetHelperGenCA8CHS_getGenCaloJetMassPF001[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF002	= patJetHelperGenCA8CHS_getGenCaloJetMassPF002[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF005	= patJetHelperGenCA8CHS_getGenCaloJetMassPF005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF01	= patJetHelperGenCA8CHS_getGenCaloJetMassPF01[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF02	= patJetHelperGenCA8CHS_getGenCaloJetMassPF02[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPF05	= patJetHelperGenCA8CHS_getGenCaloJetMassPF05[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect0005	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect001	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect002	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect005	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect01	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect02	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02[i];
      patJetHelperGenCA8CHS[i].getGenCaloJetMassPFcorrect05	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05[i];
      patJetHelperGenCA8CHS[i].getGenTrackJetMass	= patJetHelperGenCA8CHS_getGenTrackJetMass[i];
      patJetHelperGenCA8CHS[i].genNCHS	= patJetHelperGenCA8CHS_genNCHS[i];
    }
}

inline void fillpatJetHelperGenCA8CHSpruned()
{
  patJetHelperGenCA8CHSpruned.resize(patJetHelperGenCA8CHSpruned_energy.size());
  for(unsigned int i=0; i < patJetHelperGenCA8CHSpruned.size(); ++i)
    {
      patJetHelperGenCA8CHSpruned[i].energy	= patJetHelperGenCA8CHSpruned_energy[i];
      patJetHelperGenCA8CHSpruned[i].et	= patJetHelperGenCA8CHSpruned_et[i];
      patJetHelperGenCA8CHSpruned[i].pt	= patJetHelperGenCA8CHSpruned_pt[i];
      patJetHelperGenCA8CHSpruned[i].phi	= patJetHelperGenCA8CHSpruned_phi[i];
      patJetHelperGenCA8CHSpruned[i].eta	= patJetHelperGenCA8CHSpruned_eta[i];
      patJetHelperGenCA8CHSpruned[i].rapidity	= patJetHelperGenCA8CHSpruned_rapidity[i];
      patJetHelperGenCA8CHSpruned[i].mass	= patJetHelperGenCA8CHSpruned_mass[i];
      patJetHelperGenCA8CHSpruned[i].jetArea	= patJetHelperGenCA8CHSpruned_jetArea[i];
      patJetHelperGenCA8CHSpruned[i].jetCharge03	= patJetHelperGenCA8CHSpruned_jetCharge03[i];
      patJetHelperGenCA8CHSpruned[i].jetCharge05	= patJetHelperGenCA8CHSpruned_jetCharge05[i];
      patJetHelperGenCA8CHSpruned[i].jetCharge10	= patJetHelperGenCA8CHSpruned_jetCharge10[i];
      patJetHelperGenCA8CHSpruned[i].nConstituents	= patJetHelperGenCA8CHSpruned_nConstituents[i];
      patJetHelperGenCA8CHSpruned[i].partonFlavour	= patJetHelperGenCA8CHSpruned_partonFlavour[i];
      patJetHelperGenCA8CHSpruned[i].numberOfDaughters	= patJetHelperGenCA8CHSpruned_numberOfDaughters[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_energy	= patJetHelperGenCA8CHSpruned_daughter_0_energy[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_pt	= patJetHelperGenCA8CHSpruned_daughter_0_pt[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_eta	= patJetHelperGenCA8CHSpruned_daughter_0_eta[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_rapidity	= patJetHelperGenCA8CHSpruned_daughter_0_rapidity[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_phi	= patJetHelperGenCA8CHSpruned_daughter_0_phi[i];
      patJetHelperGenCA8CHSpruned[i].daughter_0_mass	= patJetHelperGenCA8CHSpruned_daughter_0_mass[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_energy	= patJetHelperGenCA8CHSpruned_daughter_1_energy[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_pt	= patJetHelperGenCA8CHSpruned_daughter_1_pt[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_eta	= patJetHelperGenCA8CHSpruned_daughter_1_eta[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_rapidity	= patJetHelperGenCA8CHSpruned_daughter_1_rapidity[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_phi	= patJetHelperGenCA8CHSpruned_daughter_1_phi[i];
      patJetHelperGenCA8CHSpruned[i].daughter_1_mass	= patJetHelperGenCA8CHSpruned_daughter_1_mass[i];
      patJetHelperGenCA8CHSpruned[i].genTau1	= patJetHelperGenCA8CHSpruned_genTau1[i];
      patJetHelperGenCA8CHSpruned[i].genTau2	= patJetHelperGenCA8CHSpruned_genTau2[i];
      patJetHelperGenCA8CHSpruned[i].genTau3	= patJetHelperGenCA8CHSpruned_genTau3[i];
    }
}

inline void fillpatJetHelperGenCA8CHStrimmed()
{
  patJetHelperGenCA8CHStrimmed.resize(patJetHelperGenCA8CHStrimmed_energy.size());
  for(unsigned int i=0; i < patJetHelperGenCA8CHStrimmed.size(); ++i)
    {
      patJetHelperGenCA8CHStrimmed[i].energy	= patJetHelperGenCA8CHStrimmed_energy[i];
      patJetHelperGenCA8CHStrimmed[i].et	= patJetHelperGenCA8CHStrimmed_et[i];
      patJetHelperGenCA8CHStrimmed[i].pt	= patJetHelperGenCA8CHStrimmed_pt[i];
      patJetHelperGenCA8CHStrimmed[i].phi	= patJetHelperGenCA8CHStrimmed_phi[i];
      patJetHelperGenCA8CHStrimmed[i].eta	= patJetHelperGenCA8CHStrimmed_eta[i];
      patJetHelperGenCA8CHStrimmed[i].rapidity	= patJetHelperGenCA8CHStrimmed_rapidity[i];
      patJetHelperGenCA8CHStrimmed[i].mass	= patJetHelperGenCA8CHStrimmed_mass[i];
      patJetHelperGenCA8CHStrimmed[i].jetArea	= patJetHelperGenCA8CHStrimmed_jetArea[i];
      patJetHelperGenCA8CHStrimmed[i].jetCharge03	= patJetHelperGenCA8CHStrimmed_jetCharge03[i];
      patJetHelperGenCA8CHStrimmed[i].jetCharge05	= patJetHelperGenCA8CHStrimmed_jetCharge05[i];
      patJetHelperGenCA8CHStrimmed[i].jetCharge10	= patJetHelperGenCA8CHStrimmed_jetCharge10[i];
      patJetHelperGenCA8CHStrimmed[i].nConstituents	= patJetHelperGenCA8CHStrimmed_nConstituents[i];
      patJetHelperGenCA8CHStrimmed[i].partonFlavour	= patJetHelperGenCA8CHStrimmed_partonFlavour[i];
      patJetHelperGenCA8CHStrimmed[i].numberOfDaughters	= patJetHelperGenCA8CHStrimmed_numberOfDaughters[i];
      patJetHelperGenCA8CHStrimmed[i].genTau1	= patJetHelperGenCA8CHStrimmed_genTau1[i];
      patJetHelperGenCA8CHStrimmed[i].genTau2	= patJetHelperGenCA8CHStrimmed_genTau2[i];
      patJetHelperGenCA8CHStrimmed[i].genTau3	= patJetHelperGenCA8CHStrimmed_genTau3[i];
    }
}

inline void fillrecoGenParticleHelper()
{
  recoGenParticleHelper.resize(recoGenParticleHelper_firstMother.size());
  for(unsigned int i=0; i < recoGenParticleHelper.size(); ++i)
    {
      recoGenParticleHelper[i].firstMother	= recoGenParticleHelper_firstMother[i];
      recoGenParticleHelper[i].lastMother	= recoGenParticleHelper_lastMother[i];
      recoGenParticleHelper[i].firstDaughter	= recoGenParticleHelper_firstDaughter[i];
      recoGenParticleHelper[i].lastDaughter	= recoGenParticleHelper_lastDaughter[i];
      recoGenParticleHelper[i].charge	= recoGenParticleHelper_charge[i];
      recoGenParticleHelper[i].pdgId	= recoGenParticleHelper_pdgId[i];
      recoGenParticleHelper[i].status	= recoGenParticleHelper_status[i];
      recoGenParticleHelper[i].pt	= recoGenParticleHelper_pt[i];
      recoGenParticleHelper[i].eta	= recoGenParticleHelper_eta[i];
      recoGenParticleHelper[i].phi	= recoGenParticleHelper_phi[i];
      recoGenParticleHelper[i].mass	= recoGenParticleHelper_mass[i];
    }
}


void fillObjects()
{
  fillPileupSummaryInfo();
  fillpatJetHelperCA8CHS();
  fillpatJetHelperCA8CHSpruned();
  fillpatJetHelperCA8CHStrimmed();
  fillpatJetHelperGenCA8CHS();
  fillpatJetHelperGenCA8CHSpruned();
  fillpatJetHelperGenCA8CHStrimmed();
  fillrecoGenParticleHelper();
}

//-----------------------------------------------------------------------------
// --- Call saveSelectedObjects() just before call to addEvent if
// --- you wish to save only the selected objects
//-----------------------------------------------------------------------------
// Select objects for which the select function was called
void saveSelectedObjects()
{
  int n = 0;

  n = 0;
  try
    {
       n = indexmap["PileupSummaryInfo"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["PileupSummaryInfo"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          PileupSummaryInfo_getPU_NumInteractions[i]	= PileupSummaryInfo_getPU_NumInteractions[j];
          PileupSummaryInfo_getBunchCrossing[i]	= PileupSummaryInfo_getBunchCrossing[j];
          PileupSummaryInfo_getTrueNumInteractions[i]	= PileupSummaryInfo_getTrueNumInteractions[j];
        }
      nPileupSummaryInfo = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperCA8CHS"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperCA8CHS"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperCA8CHS_energy[i]	= patJetHelperCA8CHS_energy[j];
          patJetHelperCA8CHS_uncor_energy[i]	= patJetHelperCA8CHS_uncor_energy[j];
          patJetHelperCA8CHS_et[i]	= patJetHelperCA8CHS_et[j];
          patJetHelperCA8CHS_uncor_et[i]	= patJetHelperCA8CHS_uncor_et[j];
          patJetHelperCA8CHS_pt[i]	= patJetHelperCA8CHS_pt[j];
          patJetHelperCA8CHS_uncor_pt[i]	= patJetHelperCA8CHS_uncor_pt[j];
          patJetHelperCA8CHS_phi[i]	= patJetHelperCA8CHS_phi[j];
          patJetHelperCA8CHS_eta[i]	= patJetHelperCA8CHS_eta[j];
          patJetHelperCA8CHS_rapidity[i]	= patJetHelperCA8CHS_rapidity[j];
          patJetHelperCA8CHS_mass[i]	= patJetHelperCA8CHS_mass[j];
          patJetHelperCA8CHS_jetArea[i]	= patJetHelperCA8CHS_jetArea[j];
          patJetHelperCA8CHS_jetCharge03[i]	= patJetHelperCA8CHS_jetCharge03[j];
          patJetHelperCA8CHS_jetCharge05[i]	= patJetHelperCA8CHS_jetCharge05[j];
          patJetHelperCA8CHS_jetCharge10[i]	= patJetHelperCA8CHS_jetCharge10[j];
          patJetHelperCA8CHS_chargedHadronEnergyFraction[i]	= patJetHelperCA8CHS_chargedHadronEnergyFraction[j];
          patJetHelperCA8CHS_neutralHadronEnergyFraction[i]	= patJetHelperCA8CHS_neutralHadronEnergyFraction[j];
          patJetHelperCA8CHS_chargedEmEnergyFraction[i]	= patJetHelperCA8CHS_chargedEmEnergyFraction[j];
          patJetHelperCA8CHS_neutralEmEnergyFraction[i]	= patJetHelperCA8CHS_neutralEmEnergyFraction[j];
          patJetHelperCA8CHS_photonEnergyFraction[i]	= patJetHelperCA8CHS_photonEnergyFraction[j];
          patJetHelperCA8CHS_muonEnergyFraction[i]	= patJetHelperCA8CHS_muonEnergyFraction[j];
          patJetHelperCA8CHS_chargedMultiplicity[i]	= patJetHelperCA8CHS_chargedMultiplicity[j];
          patJetHelperCA8CHS_nConstituents[i]	= patJetHelperCA8CHS_nConstituents[j];
          patJetHelperCA8CHS_partonFlavour[i]	= patJetHelperCA8CHS_partonFlavour[j];
          patJetHelperCA8CHS_combinedSecondaryVertexBJetTags[i]	= patJetHelperCA8CHS_combinedSecondaryVertexBJetTags[j];
          patJetHelperCA8CHS_tau1[i]	= patJetHelperCA8CHS_tau1[j];
          patJetHelperCA8CHS_tau2[i]	= patJetHelperCA8CHS_tau2[j];
          patJetHelperCA8CHS_tau3[i]	= patJetHelperCA8CHS_tau3[j];
          patJetHelperCA8CHS_C2beta05[i]	= patJetHelperCA8CHS_C2beta05[j];
          patJetHelperCA8CHS_C2beta10[i]	= patJetHelperCA8CHS_C2beta10[j];
          patJetHelperCA8CHS_C2beta15[i]	= patJetHelperCA8CHS_C2beta15[j];
          patJetHelperCA8CHS_C2beta17[i]	= patJetHelperCA8CHS_C2beta17[j];
          patJetHelperCA8CHS_C2beta20[i]	= patJetHelperCA8CHS_C2beta20[j];
          patJetHelperCA8CHS_C2beta25[i]	= patJetHelperCA8CHS_C2beta25[j];
          patJetHelperCA8CHS_getPrunedJetMass[i]	= patJetHelperCA8CHS_getPrunedJetMass[j];
          patJetHelperCA8CHS_getCorrectedPrunedJetMass[i]	= patJetHelperCA8CHS_getCorrectedPrunedJetMass[j];
          patJetHelperCA8CHS_getSplitBlockPrunedJetMass[i]	= patJetHelperCA8CHS_getSplitBlockPrunedJetMass[j];
          patJetHelperCA8CHS_getTrackJetMass[i]	= patJetHelperCA8CHS_getTrackJetMass[j];
          patJetHelperCA8CHS_getNcharged01[i]	= patJetHelperCA8CHS_getNcharged01[j];
          patJetHelperCA8CHS_getNneutral01[i]	= patJetHelperCA8CHS_getNneutral01[j];
          patJetHelperCA8CHS_getChargedPt0[i]	= patJetHelperCA8CHS_getChargedPt0[j];
          patJetHelperCA8CHS_getChargedPt1[i]	= patJetHelperCA8CHS_getChargedPt1[j];
          patJetHelperCA8CHS_getChargedPt2[i]	= patJetHelperCA8CHS_getChargedPt2[j];
          patJetHelperCA8CHS_getChargedPt3[i]	= patJetHelperCA8CHS_getChargedPt3[j];
          patJetHelperCA8CHS_getPt0[i]	= patJetHelperCA8CHS_getPt0[j];
          patJetHelperCA8CHS_getPt1[i]	= patJetHelperCA8CHS_getPt1[j];
          patJetHelperCA8CHS_getPt2[i]	= patJetHelperCA8CHS_getPt2[j];
          patJetHelperCA8CHS_getPt3[i]	= patJetHelperCA8CHS_getPt3[j];
        }
      npatJetHelperCA8CHS = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperCA8CHSpruned"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperCA8CHSpruned"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperCA8CHSpruned_energy[i]	= patJetHelperCA8CHSpruned_energy[j];
          patJetHelperCA8CHSpruned_uncor_energy[i]	= patJetHelperCA8CHSpruned_uncor_energy[j];
          patJetHelperCA8CHSpruned_et[i]	= patJetHelperCA8CHSpruned_et[j];
          patJetHelperCA8CHSpruned_uncor_et[i]	= patJetHelperCA8CHSpruned_uncor_et[j];
          patJetHelperCA8CHSpruned_pt[i]	= patJetHelperCA8CHSpruned_pt[j];
          patJetHelperCA8CHSpruned_uncor_pt[i]	= patJetHelperCA8CHSpruned_uncor_pt[j];
          patJetHelperCA8CHSpruned_phi[i]	= patJetHelperCA8CHSpruned_phi[j];
          patJetHelperCA8CHSpruned_eta[i]	= patJetHelperCA8CHSpruned_eta[j];
          patJetHelperCA8CHSpruned_rapidity[i]	= patJetHelperCA8CHSpruned_rapidity[j];
          patJetHelperCA8CHSpruned_mass[i]	= patJetHelperCA8CHSpruned_mass[j];
          patJetHelperCA8CHSpruned_jetArea[i]	= patJetHelperCA8CHSpruned_jetArea[j];
          patJetHelperCA8CHSpruned_jetCharge03[i]	= patJetHelperCA8CHSpruned_jetCharge03[j];
          patJetHelperCA8CHSpruned_jetCharge05[i]	= patJetHelperCA8CHSpruned_jetCharge05[j];
          patJetHelperCA8CHSpruned_jetCharge10[i]	= patJetHelperCA8CHSpruned_jetCharge10[j];
          patJetHelperCA8CHSpruned_nConstituents[i]	= patJetHelperCA8CHSpruned_nConstituents[j];
          patJetHelperCA8CHSpruned_partonFlavour[i]	= patJetHelperCA8CHSpruned_partonFlavour[j];
          patJetHelperCA8CHSpruned_numberOfDaughters[i]	= patJetHelperCA8CHSpruned_numberOfDaughters[j];
          patJetHelperCA8CHSpruned_daughter_0_energy[i]	= patJetHelperCA8CHSpruned_daughter_0_energy[j];
          patJetHelperCA8CHSpruned_daughter_0_pt[i]	= patJetHelperCA8CHSpruned_daughter_0_pt[j];
          patJetHelperCA8CHSpruned_daughter_0_eta[i]	= patJetHelperCA8CHSpruned_daughter_0_eta[j];
          patJetHelperCA8CHSpruned_daughter_0_rapidity[i]	= patJetHelperCA8CHSpruned_daughter_0_rapidity[j];
          patJetHelperCA8CHSpruned_daughter_0_phi[i]	= patJetHelperCA8CHSpruned_daughter_0_phi[j];
          patJetHelperCA8CHSpruned_daughter_0_mass[i]	= patJetHelperCA8CHSpruned_daughter_0_mass[j];
          patJetHelperCA8CHSpruned_daughter_1_energy[i]	= patJetHelperCA8CHSpruned_daughter_1_energy[j];
          patJetHelperCA8CHSpruned_daughter_1_pt[i]	= patJetHelperCA8CHSpruned_daughter_1_pt[j];
          patJetHelperCA8CHSpruned_daughter_1_eta[i]	= patJetHelperCA8CHSpruned_daughter_1_eta[j];
          patJetHelperCA8CHSpruned_daughter_1_rapidity[i]	= patJetHelperCA8CHSpruned_daughter_1_rapidity[j];
          patJetHelperCA8CHSpruned_daughter_1_phi[i]	= patJetHelperCA8CHSpruned_daughter_1_phi[j];
          patJetHelperCA8CHSpruned_daughter_1_mass[i]	= patJetHelperCA8CHSpruned_daughter_1_mass[j];
          patJetHelperCA8CHSpruned_tau1[i]	= patJetHelperCA8CHSpruned_tau1[j];
          patJetHelperCA8CHSpruned_tau2[i]	= patJetHelperCA8CHSpruned_tau2[j];
          patJetHelperCA8CHSpruned_tau3[i]	= patJetHelperCA8CHSpruned_tau3[j];
          patJetHelperCA8CHSpruned_daughter_0_jetCharge03[i]	= patJetHelperCA8CHSpruned_daughter_0_jetCharge03[j];
          patJetHelperCA8CHSpruned_daughter_0_jetCharge05[i]	= patJetHelperCA8CHSpruned_daughter_0_jetCharge05[j];
          patJetHelperCA8CHSpruned_daughter_0_jetCharge10[i]	= patJetHelperCA8CHSpruned_daughter_0_jetCharge10[j];
          patJetHelperCA8CHSpruned_daughter_1_jetCharge03[i]	= patJetHelperCA8CHSpruned_daughter_1_jetCharge03[j];
          patJetHelperCA8CHSpruned_daughter_1_jetCharge05[i]	= patJetHelperCA8CHSpruned_daughter_1_jetCharge05[j];
          patJetHelperCA8CHSpruned_daughter_1_jetCharge10[i]	= patJetHelperCA8CHSpruned_daughter_1_jetCharge10[j];
          patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags[i]	= patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags[j];
          patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags[i]	= patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags[j];
        }
      npatJetHelperCA8CHSpruned = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperCA8CHStrimmed"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperCA8CHStrimmed"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperCA8CHStrimmed_energy[i]	= patJetHelperCA8CHStrimmed_energy[j];
          patJetHelperCA8CHStrimmed_uncor_energy[i]	= patJetHelperCA8CHStrimmed_uncor_energy[j];
          patJetHelperCA8CHStrimmed_et[i]	= patJetHelperCA8CHStrimmed_et[j];
          patJetHelperCA8CHStrimmed_uncor_et[i]	= patJetHelperCA8CHStrimmed_uncor_et[j];
          patJetHelperCA8CHStrimmed_pt[i]	= patJetHelperCA8CHStrimmed_pt[j];
          patJetHelperCA8CHStrimmed_uncor_pt[i]	= patJetHelperCA8CHStrimmed_uncor_pt[j];
          patJetHelperCA8CHStrimmed_phi[i]	= patJetHelperCA8CHStrimmed_phi[j];
          patJetHelperCA8CHStrimmed_eta[i]	= patJetHelperCA8CHStrimmed_eta[j];
          patJetHelperCA8CHStrimmed_rapidity[i]	= patJetHelperCA8CHStrimmed_rapidity[j];
          patJetHelperCA8CHStrimmed_mass[i]	= patJetHelperCA8CHStrimmed_mass[j];
          patJetHelperCA8CHStrimmed_jetArea[i]	= patJetHelperCA8CHStrimmed_jetArea[j];
          patJetHelperCA8CHStrimmed_jetCharge03[i]	= patJetHelperCA8CHStrimmed_jetCharge03[j];
          patJetHelperCA8CHStrimmed_jetCharge05[i]	= patJetHelperCA8CHStrimmed_jetCharge05[j];
          patJetHelperCA8CHStrimmed_jetCharge10[i]	= patJetHelperCA8CHStrimmed_jetCharge10[j];
          patJetHelperCA8CHStrimmed_nConstituents[i]	= patJetHelperCA8CHStrimmed_nConstituents[j];
          patJetHelperCA8CHStrimmed_partonFlavour[i]	= patJetHelperCA8CHStrimmed_partonFlavour[j];
          patJetHelperCA8CHStrimmed_numberOfDaughters[i]	= patJetHelperCA8CHStrimmed_numberOfDaughters[j];
          patJetHelperCA8CHStrimmed_tau1[i]	= patJetHelperCA8CHStrimmed_tau1[j];
          patJetHelperCA8CHStrimmed_tau2[i]	= patJetHelperCA8CHStrimmed_tau2[j];
          patJetHelperCA8CHStrimmed_tau3[i]	= patJetHelperCA8CHStrimmed_tau3[j];
        }
      npatJetHelperCA8CHStrimmed = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperGenCA8CHS"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperGenCA8CHS"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperGenCA8CHS_energy[i]	= patJetHelperGenCA8CHS_energy[j];
          patJetHelperGenCA8CHS_et[i]	= patJetHelperGenCA8CHS_et[j];
          patJetHelperGenCA8CHS_pt[i]	= patJetHelperGenCA8CHS_pt[j];
          patJetHelperGenCA8CHS_phi[i]	= patJetHelperGenCA8CHS_phi[j];
          patJetHelperGenCA8CHS_eta[i]	= patJetHelperGenCA8CHS_eta[j];
          patJetHelperGenCA8CHS_rapidity[i]	= patJetHelperGenCA8CHS_rapidity[j];
          patJetHelperGenCA8CHS_mass[i]	= patJetHelperGenCA8CHS_mass[j];
          patJetHelperGenCA8CHS_jetArea[i]	= patJetHelperGenCA8CHS_jetArea[j];
          patJetHelperGenCA8CHS_genJetCharge03[i]	= patJetHelperGenCA8CHS_genJetCharge03[j];
          patJetHelperGenCA8CHS_genJetCharge05[i]	= patJetHelperGenCA8CHS_genJetCharge05[j];
          patJetHelperGenCA8CHS_genJetCharge10[i]	= patJetHelperGenCA8CHS_genJetCharge10[j];
          patJetHelperGenCA8CHS_nConstituents[i]	= patJetHelperGenCA8CHS_nConstituents[j];
          patJetHelperGenCA8CHS_partonFlavour[i]	= patJetHelperGenCA8CHS_partonFlavour[j];
          patJetHelperGenCA8CHS_genC2beta05[i]	= patJetHelperGenCA8CHS_genC2beta05[j];
          patJetHelperGenCA8CHS_genC2beta10[i]	= patJetHelperGenCA8CHS_genC2beta10[j];
          patJetHelperGenCA8CHS_genC2beta15[i]	= patJetHelperGenCA8CHS_genC2beta15[j];
          patJetHelperGenCA8CHS_genC2beta17[i]	= patJetHelperGenCA8CHS_genC2beta17[j];
          patJetHelperGenCA8CHS_genC2beta20[i]	= patJetHelperGenCA8CHS_genC2beta20[j];
          patJetHelperGenCA8CHS_genC2beta25[i]	= patJetHelperGenCA8CHS_genC2beta25[j];
          patJetHelperGenCA8CHS_genC2beta17CHS[i]	= patJetHelperGenCA8CHS_genC2beta17CHS[j];
          patJetHelperGenCA8CHS_genTau1[i]	= patJetHelperGenCA8CHS_genTau1[j];
          patJetHelperGenCA8CHS_genTau2[i]	= patJetHelperGenCA8CHS_genTau2[j];
          patJetHelperGenCA8CHS_genTau3[i]	= patJetHelperGenCA8CHS_genTau3[j];
          patJetHelperGenCA8CHS_genTau1Pt2[i]	= patJetHelperGenCA8CHS_genTau1Pt2[j];
          patJetHelperGenCA8CHS_genTau2Pt2[i]	= patJetHelperGenCA8CHS_genTau2Pt2[j];
          patJetHelperGenCA8CHS_genTau1Pt5[i]	= patJetHelperGenCA8CHS_genTau1Pt5[j];
          patJetHelperGenCA8CHS_genTau2Pt5[i]	= patJetHelperGenCA8CHS_genTau2Pt5[j];
          patJetHelperGenCA8CHS_genTau1CHS[i]	= patJetHelperGenCA8CHS_genTau1CHS[j];
          patJetHelperGenCA8CHS_genTau2CHS[i]	= patJetHelperGenCA8CHS_genTau2CHS[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass0005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass0005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass001[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass001[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass002[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass002[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass01[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass01[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass02[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass02[j];
          patJetHelperGenCA8CHS_getGenCaloJetMass05[i]	= patJetHelperGenCA8CHS_getGenCaloJetMass05[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF0005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF0005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF001[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF001[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF002[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF002[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF01[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF01[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF02[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF02[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPF05[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPF05[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02[j];
          patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05[i]	= patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05[j];
          patJetHelperGenCA8CHS_getGenTrackJetMass[i]	= patJetHelperGenCA8CHS_getGenTrackJetMass[j];
          patJetHelperGenCA8CHS_genNCHS[i]	= patJetHelperGenCA8CHS_genNCHS[j];
        }
      npatJetHelperGenCA8CHS = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperGenCA8CHSpruned"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperGenCA8CHSpruned"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperGenCA8CHSpruned_energy[i]	= patJetHelperGenCA8CHSpruned_energy[j];
          patJetHelperGenCA8CHSpruned_et[i]	= patJetHelperGenCA8CHSpruned_et[j];
          patJetHelperGenCA8CHSpruned_pt[i]	= patJetHelperGenCA8CHSpruned_pt[j];
          patJetHelperGenCA8CHSpruned_phi[i]	= patJetHelperGenCA8CHSpruned_phi[j];
          patJetHelperGenCA8CHSpruned_eta[i]	= patJetHelperGenCA8CHSpruned_eta[j];
          patJetHelperGenCA8CHSpruned_rapidity[i]	= patJetHelperGenCA8CHSpruned_rapidity[j];
          patJetHelperGenCA8CHSpruned_mass[i]	= patJetHelperGenCA8CHSpruned_mass[j];
          patJetHelperGenCA8CHSpruned_jetArea[i]	= patJetHelperGenCA8CHSpruned_jetArea[j];
          patJetHelperGenCA8CHSpruned_jetCharge03[i]	= patJetHelperGenCA8CHSpruned_jetCharge03[j];
          patJetHelperGenCA8CHSpruned_jetCharge05[i]	= patJetHelperGenCA8CHSpruned_jetCharge05[j];
          patJetHelperGenCA8CHSpruned_jetCharge10[i]	= patJetHelperGenCA8CHSpruned_jetCharge10[j];
          patJetHelperGenCA8CHSpruned_nConstituents[i]	= patJetHelperGenCA8CHSpruned_nConstituents[j];
          patJetHelperGenCA8CHSpruned_partonFlavour[i]	= patJetHelperGenCA8CHSpruned_partonFlavour[j];
          patJetHelperGenCA8CHSpruned_numberOfDaughters[i]	= patJetHelperGenCA8CHSpruned_numberOfDaughters[j];
          patJetHelperGenCA8CHSpruned_daughter_0_energy[i]	= patJetHelperGenCA8CHSpruned_daughter_0_energy[j];
          patJetHelperGenCA8CHSpruned_daughter_0_pt[i]	= patJetHelperGenCA8CHSpruned_daughter_0_pt[j];
          patJetHelperGenCA8CHSpruned_daughter_0_eta[i]	= patJetHelperGenCA8CHSpruned_daughter_0_eta[j];
          patJetHelperGenCA8CHSpruned_daughter_0_rapidity[i]	= patJetHelperGenCA8CHSpruned_daughter_0_rapidity[j];
          patJetHelperGenCA8CHSpruned_daughter_0_phi[i]	= patJetHelperGenCA8CHSpruned_daughter_0_phi[j];
          patJetHelperGenCA8CHSpruned_daughter_0_mass[i]	= patJetHelperGenCA8CHSpruned_daughter_0_mass[j];
          patJetHelperGenCA8CHSpruned_daughter_1_energy[i]	= patJetHelperGenCA8CHSpruned_daughter_1_energy[j];
          patJetHelperGenCA8CHSpruned_daughter_1_pt[i]	= patJetHelperGenCA8CHSpruned_daughter_1_pt[j];
          patJetHelperGenCA8CHSpruned_daughter_1_eta[i]	= patJetHelperGenCA8CHSpruned_daughter_1_eta[j];
          patJetHelperGenCA8CHSpruned_daughter_1_rapidity[i]	= patJetHelperGenCA8CHSpruned_daughter_1_rapidity[j];
          patJetHelperGenCA8CHSpruned_daughter_1_phi[i]	= patJetHelperGenCA8CHSpruned_daughter_1_phi[j];
          patJetHelperGenCA8CHSpruned_daughter_1_mass[i]	= patJetHelperGenCA8CHSpruned_daughter_1_mass[j];
          patJetHelperGenCA8CHSpruned_genTau1[i]	= patJetHelperGenCA8CHSpruned_genTau1[j];
          patJetHelperGenCA8CHSpruned_genTau2[i]	= patJetHelperGenCA8CHSpruned_genTau2[j];
          patJetHelperGenCA8CHSpruned_genTau3[i]	= patJetHelperGenCA8CHSpruned_genTau3[j];
        }
      npatJetHelperGenCA8CHSpruned = n;
    }

  n = 0;
  try
    {
       n = indexmap["patJetHelperGenCA8CHStrimmed"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["patJetHelperGenCA8CHStrimmed"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          patJetHelperGenCA8CHStrimmed_energy[i]	= patJetHelperGenCA8CHStrimmed_energy[j];
          patJetHelperGenCA8CHStrimmed_et[i]	= patJetHelperGenCA8CHStrimmed_et[j];
          patJetHelperGenCA8CHStrimmed_pt[i]	= patJetHelperGenCA8CHStrimmed_pt[j];
          patJetHelperGenCA8CHStrimmed_phi[i]	= patJetHelperGenCA8CHStrimmed_phi[j];
          patJetHelperGenCA8CHStrimmed_eta[i]	= patJetHelperGenCA8CHStrimmed_eta[j];
          patJetHelperGenCA8CHStrimmed_rapidity[i]	= patJetHelperGenCA8CHStrimmed_rapidity[j];
          patJetHelperGenCA8CHStrimmed_mass[i]	= patJetHelperGenCA8CHStrimmed_mass[j];
          patJetHelperGenCA8CHStrimmed_jetArea[i]	= patJetHelperGenCA8CHStrimmed_jetArea[j];
          patJetHelperGenCA8CHStrimmed_jetCharge03[i]	= patJetHelperGenCA8CHStrimmed_jetCharge03[j];
          patJetHelperGenCA8CHStrimmed_jetCharge05[i]	= patJetHelperGenCA8CHStrimmed_jetCharge05[j];
          patJetHelperGenCA8CHStrimmed_jetCharge10[i]	= patJetHelperGenCA8CHStrimmed_jetCharge10[j];
          patJetHelperGenCA8CHStrimmed_nConstituents[i]	= patJetHelperGenCA8CHStrimmed_nConstituents[j];
          patJetHelperGenCA8CHStrimmed_partonFlavour[i]	= patJetHelperGenCA8CHStrimmed_partonFlavour[j];
          patJetHelperGenCA8CHStrimmed_numberOfDaughters[i]	= patJetHelperGenCA8CHStrimmed_numberOfDaughters[j];
          patJetHelperGenCA8CHStrimmed_genTau1[i]	= patJetHelperGenCA8CHStrimmed_genTau1[j];
          patJetHelperGenCA8CHStrimmed_genTau2[i]	= patJetHelperGenCA8CHStrimmed_genTau2[j];
          patJetHelperGenCA8CHStrimmed_genTau3[i]	= patJetHelperGenCA8CHStrimmed_genTau3[j];
        }
      npatJetHelperGenCA8CHStrimmed = n;
    }

  n = 0;
  try
    {
       n = indexmap["recoGenParticleHelper"].size();
    }
  catch (...)
    {}
  if ( n > 0 )
    {
      std::vector<int>& index = indexmap["recoGenParticleHelper"];
      for(int i=0; i < n; ++i)
        {
          int j = index[i];
          recoGenParticleHelper_firstMother[i]	= recoGenParticleHelper_firstMother[j];
          recoGenParticleHelper_lastMother[i]	= recoGenParticleHelper_lastMother[j];
          recoGenParticleHelper_firstDaughter[i]	= recoGenParticleHelper_firstDaughter[j];
          recoGenParticleHelper_lastDaughter[i]	= recoGenParticleHelper_lastDaughter[j];
          recoGenParticleHelper_charge[i]	= recoGenParticleHelper_charge[j];
          recoGenParticleHelper_pdgId[i]	= recoGenParticleHelper_pdgId[j];
          recoGenParticleHelper_status[i]	= recoGenParticleHelper_status[j];
          recoGenParticleHelper_pt[i]	= recoGenParticleHelper_pt[j];
          recoGenParticleHelper_eta[i]	= recoGenParticleHelper_eta[j];
          recoGenParticleHelper_phi[i]	= recoGenParticleHelper_phi[j];
          recoGenParticleHelper_mass[i]	= recoGenParticleHelper_mass[j];
        }
      nrecoGenParticleHelper = n;
    }
}

//-----------------------------------------------------------------------------
// --- Select variables to be read
//-----------------------------------------------------------------------------
void selectVariables(itreestream& stream)
{
  stream.select("GenEventInfoProduct_generator.alphaQCD", GenEventInfoProduct_alphaQCD);
  stream.select("GenEventInfoProduct_generator.alphaQED", GenEventInfoProduct_alphaQED);
  stream.select("GenEventInfoProduct_generator.hasBinningValues", GenEventInfoProduct_hasBinningValues);
  stream.select("GenEventInfoProduct_generator.hasPDF", GenEventInfoProduct_hasPDF);
  stream.select("GenEventInfoProduct_generator.qScale", GenEventInfoProduct_qScale);
  stream.select("GenEventInfoProduct_generator.signalProcessID", GenEventInfoProduct_signalProcessID);
  stream.select("GenEventInfoProduct_generator.weight", GenEventInfoProduct_weight);
  stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", PileupSummaryInfo_getBunchCrossing);
  stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", PileupSummaryInfo_getPU_NumInteractions);
  stream.select("PileupSummaryInfo_addPileupInfo.getTrueNumInteractions", PileupSummaryInfo_getTrueNumInteractions);
  stream.select("edmEventHelper_info.bunchCrossing", edmEventHelper_bunchCrossing);
  stream.select("edmEventHelper_info.event", edmEventHelper_event);
  stream.select("edmEventHelper_info.isRealData", edmEventHelper_isRealData);
  stream.select("edmEventHelper_info.luminosityBlock", edmEventHelper_luminosityBlock);
  stream.select("edmEventHelper_info.orbitNumber", edmEventHelper_orbitNumber);
  stream.select("edmEventHelper_info.run", edmEventHelper_run);
  stream.select("nPileupSummaryInfo_addPileupInfo", nPileupSummaryInfo);
  stream.select("npatJetHelper_selectedPatJetsCA8CHSwithNsub", npatJetHelperCA8CHS);
  stream.select("npatJetHelper_selectedPatJetsCA8CHSpruned", npatJetHelperCA8CHSpruned);
  stream.select("npatJetHelper_selectedPatJetsCA8CHStrimmed", npatJetHelperCA8CHStrimmed);
  stream.select("npatJetHelper_patGenJetsCA8CHS", npatJetHelperGenCA8CHS);
  stream.select("npatJetHelper_patGenJetsCA8CHSpruned", npatJetHelperGenCA8CHSpruned);
  stream.select("npatJetHelper_patGenJetsCA8CHStrimmed", npatJetHelperGenCA8CHStrimmed);
  stream.select("nrecoGenParticleHelper_genParticles", nrecoGenParticleHelper);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta05", patJetHelperCA8CHS_C2beta05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta10", patJetHelperCA8CHS_C2beta10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta15", patJetHelperCA8CHS_C2beta15);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta17", patJetHelperCA8CHS_C2beta17);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta20", patJetHelperCA8CHS_C2beta20);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta25", patJetHelperCA8CHS_C2beta25);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedEmEnergyFraction", patJetHelperCA8CHS_chargedEmEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedHadronEnergyFraction", patJetHelperCA8CHS_chargedHadronEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedMultiplicity", patJetHelperCA8CHS_chargedMultiplicity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.combinedSecondaryVertexBJetTags", patJetHelperCA8CHS_combinedSecondaryVertexBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.energy", patJetHelperCA8CHS_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.et", patJetHelperCA8CHS_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.eta", patJetHelperCA8CHS_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt0", patJetHelperCA8CHS_getChargedPt0);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt1", patJetHelperCA8CHS_getChargedPt1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt2", patJetHelperCA8CHS_getChargedPt2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt3", patJetHelperCA8CHS_getChargedPt3);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getCorrectedPrunedJetMass", patJetHelperCA8CHS_getCorrectedPrunedJetMass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNcharged01", patJetHelperCA8CHS_getNcharged01);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNneutral01", patJetHelperCA8CHS_getNneutral01);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPrunedJetMass", patJetHelperCA8CHS_getPrunedJetMass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt0", patJetHelperCA8CHS_getPt0);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt1", patJetHelperCA8CHS_getPt1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt2", patJetHelperCA8CHS_getPt2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt3", patJetHelperCA8CHS_getPt3);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getSplitBlockPrunedJetMass", patJetHelperCA8CHS_getSplitBlockPrunedJetMass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getTrackJetMass", patJetHelperCA8CHS_getTrackJetMass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetArea", patJetHelperCA8CHS_jetArea);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge03", patJetHelperCA8CHS_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge05", patJetHelperCA8CHS_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge10", patJetHelperCA8CHS_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.mass", patJetHelperCA8CHS_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.muonEnergyFraction", patJetHelperCA8CHS_muonEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.nConstituents", patJetHelperCA8CHS_nConstituents);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralEmEnergyFraction", patJetHelperCA8CHS_neutralEmEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralHadronEnergyFraction", patJetHelperCA8CHS_neutralHadronEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.partonFlavour", patJetHelperCA8CHS_partonFlavour);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.phi", patJetHelperCA8CHS_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.photonEnergyFraction", patJetHelperCA8CHS_photonEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.pt", patJetHelperCA8CHS_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.rapidity", patJetHelperCA8CHS_rapidity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau1", patJetHelperCA8CHS_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau2", patJetHelperCA8CHS_tau2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau3", patJetHelperCA8CHS_tau3);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_energy", patJetHelperCA8CHS_uncor_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_et", patJetHelperCA8CHS_uncor_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_pt", patJetHelperCA8CHS_uncor_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_combinedSecondaryVertexBJetTags", patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_energy", patJetHelperCA8CHSpruned_daughter_0_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_eta", patJetHelperCA8CHSpruned_daughter_0_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge03", patJetHelperCA8CHSpruned_daughter_0_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge05", patJetHelperCA8CHSpruned_daughter_0_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge10", patJetHelperCA8CHSpruned_daughter_0_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_mass", patJetHelperCA8CHSpruned_daughter_0_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_phi", patJetHelperCA8CHSpruned_daughter_0_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_pt", patJetHelperCA8CHSpruned_daughter_0_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_rapidity", patJetHelperCA8CHSpruned_daughter_0_rapidity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_combinedSecondaryVertexBJetTags", patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_energy", patJetHelperCA8CHSpruned_daughter_1_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_eta", patJetHelperCA8CHSpruned_daughter_1_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge03", patJetHelperCA8CHSpruned_daughter_1_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge05", patJetHelperCA8CHSpruned_daughter_1_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge10", patJetHelperCA8CHSpruned_daughter_1_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_mass", patJetHelperCA8CHSpruned_daughter_1_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_phi", patJetHelperCA8CHSpruned_daughter_1_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_pt", patJetHelperCA8CHSpruned_daughter_1_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_rapidity", patJetHelperCA8CHSpruned_daughter_1_rapidity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.energy", patJetHelperCA8CHSpruned_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.et", patJetHelperCA8CHSpruned_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.eta", patJetHelperCA8CHSpruned_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetArea", patJetHelperCA8CHSpruned_jetArea);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge03", patJetHelperCA8CHSpruned_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge05", patJetHelperCA8CHSpruned_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge10", patJetHelperCA8CHSpruned_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.mass", patJetHelperCA8CHSpruned_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.nConstituents", patJetHelperCA8CHSpruned_nConstituents);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.numberOfDaughters", patJetHelperCA8CHSpruned_numberOfDaughters);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.partonFlavour", patJetHelperCA8CHSpruned_partonFlavour);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.phi", patJetHelperCA8CHSpruned_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.pt", patJetHelperCA8CHSpruned_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.rapidity", patJetHelperCA8CHSpruned_rapidity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau1", patJetHelperCA8CHSpruned_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau2", patJetHelperCA8CHSpruned_tau2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau3", patJetHelperCA8CHSpruned_tau3);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_energy", patJetHelperCA8CHSpruned_uncor_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_et", patJetHelperCA8CHSpruned_uncor_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_pt", patJetHelperCA8CHSpruned_uncor_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.energy", patJetHelperCA8CHStrimmed_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.et", patJetHelperCA8CHStrimmed_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.eta", patJetHelperCA8CHStrimmed_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.jetArea", patJetHelperCA8CHStrimmed_jetArea);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.jetCharge03", patJetHelperCA8CHStrimmed_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.jetCharge05", patJetHelperCA8CHStrimmed_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.jetCharge10", patJetHelperCA8CHStrimmed_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.mass", patJetHelperCA8CHStrimmed_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.nConstituents", patJetHelperCA8CHStrimmed_nConstituents);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.numberOfDaughters", patJetHelperCA8CHStrimmed_numberOfDaughters);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.partonFlavour", patJetHelperCA8CHStrimmed_partonFlavour);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.phi", patJetHelperCA8CHStrimmed_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.pt", patJetHelperCA8CHStrimmed_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.rapidity", patJetHelperCA8CHStrimmed_rapidity);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.tau1", patJetHelperCA8CHStrimmed_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.tau2", patJetHelperCA8CHStrimmed_tau2);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.tau3", patJetHelperCA8CHStrimmed_tau3);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.uncor_energy", patJetHelperCA8CHStrimmed_uncor_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.uncor_et", patJetHelperCA8CHStrimmed_uncor_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.uncor_pt", patJetHelperCA8CHStrimmed_uncor_pt);
  stream.select("patJetHelper_patGenJetsCA8CHS.energy", patJetHelperGenCA8CHS_energy);
  stream.select("patJetHelper_patGenJetsCA8CHS.et", patJetHelperGenCA8CHS_et);
  stream.select("patJetHelper_patGenJetsCA8CHS.eta", patJetHelperGenCA8CHS_eta);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta05", patJetHelperGenCA8CHS_genC2beta05);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta10", patJetHelperGenCA8CHS_genC2beta10);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta15", patJetHelperGenCA8CHS_genC2beta15);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17", patJetHelperGenCA8CHS_genC2beta17);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17CHS", patJetHelperGenCA8CHS_genC2beta17CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta20", patJetHelperGenCA8CHS_genC2beta20);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta25", patJetHelperGenCA8CHS_genC2beta25);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge03", patJetHelperGenCA8CHS_genJetCharge03);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge05", patJetHelperGenCA8CHS_genJetCharge05);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge10", patJetHelperGenCA8CHS_genJetCharge10);
  stream.select("patJetHelper_patGenJetsCA8CHS.genNCHS", patJetHelperGenCA8CHS_genNCHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1", patJetHelperGenCA8CHS_genTau1);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1CHS", patJetHelperGenCA8CHS_genTau1CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1Pt2", patJetHelperGenCA8CHS_genTau1Pt2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1Pt5", patJetHelperGenCA8CHS_genTau1Pt5);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2", patJetHelperGenCA8CHS_genTau2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2CHS", patJetHelperGenCA8CHS_genTau2CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2Pt2", patJetHelperGenCA8CHS_genTau2Pt2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2Pt5", patJetHelperGenCA8CHS_genTau2Pt5);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau3", patJetHelperGenCA8CHS_genTau3);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass0005", patJetHelperGenCA8CHS_getGenCaloJetMass0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass001", patJetHelperGenCA8CHS_getGenCaloJetMass001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass002", patJetHelperGenCA8CHS_getGenCaloJetMass002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass005", patJetHelperGenCA8CHS_getGenCaloJetMass005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass01", patJetHelperGenCA8CHS_getGenCaloJetMass01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass02", patJetHelperGenCA8CHS_getGenCaloJetMass02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass05", patJetHelperGenCA8CHS_getGenCaloJetMass05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF0005", patJetHelperGenCA8CHS_getGenCaloJetMassPF0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF001", patJetHelperGenCA8CHS_getGenCaloJetMassPF001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF002", patJetHelperGenCA8CHS_getGenCaloJetMassPF002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF005", patJetHelperGenCA8CHS_getGenCaloJetMassPF005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF01", patJetHelperGenCA8CHS_getGenCaloJetMassPF01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF02", patJetHelperGenCA8CHS_getGenCaloJetMassPF02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF05", patJetHelperGenCA8CHS_getGenCaloJetMassPF05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect0005", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect001", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect002", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect005", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect01", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect02", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect05", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenTrackJetMass", patJetHelperGenCA8CHS_getGenTrackJetMass);
  stream.select("patJetHelper_patGenJetsCA8CHS.jetArea", patJetHelperGenCA8CHS_jetArea);
  stream.select("patJetHelper_patGenJetsCA8CHS.mass", patJetHelperGenCA8CHS_mass);
  stream.select("patJetHelper_patGenJetsCA8CHS.nConstituents", patJetHelperGenCA8CHS_nConstituents);
  stream.select("patJetHelper_patGenJetsCA8CHS.partonFlavour", patJetHelperGenCA8CHS_partonFlavour);
  stream.select("patJetHelper_patGenJetsCA8CHS.phi", patJetHelperGenCA8CHS_phi);
  stream.select("patJetHelper_patGenJetsCA8CHS.pt", patJetHelperGenCA8CHS_pt);
  stream.select("patJetHelper_patGenJetsCA8CHS.rapidity", patJetHelperGenCA8CHS_rapidity);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_energy", patJetHelperGenCA8CHSpruned_daughter_0_energy);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_eta", patJetHelperGenCA8CHSpruned_daughter_0_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_mass", patJetHelperGenCA8CHSpruned_daughter_0_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_phi", patJetHelperGenCA8CHSpruned_daughter_0_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_pt", patJetHelperGenCA8CHSpruned_daughter_0_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_rapidity", patJetHelperGenCA8CHSpruned_daughter_0_rapidity);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_energy", patJetHelperGenCA8CHSpruned_daughter_1_energy);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_eta", patJetHelperGenCA8CHSpruned_daughter_1_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_mass", patJetHelperGenCA8CHSpruned_daughter_1_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_phi", patJetHelperGenCA8CHSpruned_daughter_1_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_pt", patJetHelperGenCA8CHSpruned_daughter_1_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_rapidity", patJetHelperGenCA8CHSpruned_daughter_1_rapidity);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.energy", patJetHelperGenCA8CHSpruned_energy);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.et", patJetHelperGenCA8CHSpruned_et);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.eta", patJetHelperGenCA8CHSpruned_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau1", patJetHelperGenCA8CHSpruned_genTau1);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau2", patJetHelperGenCA8CHSpruned_genTau2);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau3", patJetHelperGenCA8CHSpruned_genTau3);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetArea", patJetHelperGenCA8CHSpruned_jetArea);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge03", patJetHelperGenCA8CHSpruned_jetCharge03);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge05", patJetHelperGenCA8CHSpruned_jetCharge05);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge10", patJetHelperGenCA8CHSpruned_jetCharge10);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.mass", patJetHelperGenCA8CHSpruned_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.nConstituents", patJetHelperGenCA8CHSpruned_nConstituents);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.numberOfDaughters", patJetHelperGenCA8CHSpruned_numberOfDaughters);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.partonFlavour", patJetHelperGenCA8CHSpruned_partonFlavour);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.phi", patJetHelperGenCA8CHSpruned_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.pt", patJetHelperGenCA8CHSpruned_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.rapidity", patJetHelperGenCA8CHSpruned_rapidity);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.energy", patJetHelperGenCA8CHStrimmed_energy);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.et", patJetHelperGenCA8CHStrimmed_et);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.eta", patJetHelperGenCA8CHStrimmed_eta);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.genTau1", patJetHelperGenCA8CHStrimmed_genTau1);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.genTau2", patJetHelperGenCA8CHStrimmed_genTau2);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.genTau3", patJetHelperGenCA8CHStrimmed_genTau3);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.jetArea", patJetHelperGenCA8CHStrimmed_jetArea);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.jetCharge03", patJetHelperGenCA8CHStrimmed_jetCharge03);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.jetCharge05", patJetHelperGenCA8CHStrimmed_jetCharge05);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.jetCharge10", patJetHelperGenCA8CHStrimmed_jetCharge10);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.mass", patJetHelperGenCA8CHStrimmed_mass);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.nConstituents", patJetHelperGenCA8CHStrimmed_nConstituents);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.numberOfDaughters", patJetHelperGenCA8CHStrimmed_numberOfDaughters);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.partonFlavour", patJetHelperGenCA8CHStrimmed_partonFlavour);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.phi", patJetHelperGenCA8CHStrimmed_phi);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.pt", patJetHelperGenCA8CHStrimmed_pt);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.rapidity", patJetHelperGenCA8CHStrimmed_rapidity);
  stream.select("recoGenParticleHelper_genParticles.charge", recoGenParticleHelper_charge);
  stream.select("recoGenParticleHelper_genParticles.eta", recoGenParticleHelper_eta);
  stream.select("recoGenParticleHelper_genParticles.firstDaughter", recoGenParticleHelper_firstDaughter);
  stream.select("recoGenParticleHelper_genParticles.firstMother", recoGenParticleHelper_firstMother);
  stream.select("recoGenParticleHelper_genParticles.lastDaughter", recoGenParticleHelper_lastDaughter);
  stream.select("recoGenParticleHelper_genParticles.lastMother", recoGenParticleHelper_lastMother);
  stream.select("recoGenParticleHelper_genParticles.mass", recoGenParticleHelper_mass);
  stream.select("recoGenParticleHelper_genParticles.pdgId", recoGenParticleHelper_pdgId);
  stream.select("recoGenParticleHelper_genParticles.phi", recoGenParticleHelper_phi);
  stream.select("recoGenParticleHelper_genParticles.pt", recoGenParticleHelper_pt);
  stream.select("recoGenParticleHelper_genParticles.status", recoGenParticleHelper_status);

}
}; // end namespace evt
#endif
