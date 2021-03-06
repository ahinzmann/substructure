#ifndef PATJETHELPER_H
#define PATJETHELPER_H
//-----------------------------------------------------------------------------
// Subsystem:   Ntuples
// Package:     substructure
// Description: TheNtupleMaker helper class for pat::Jet
// Created:     Tue May  8 17:05:51 2012
// Author:      Sezen Sekmen      
//-----------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <map>

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "PhysicsTools/TheNtupleMaker/interface/HelperFor.h"

//#include "CMGTools/External/interface/PileupJetIdentifier.h"

//-----------------------------------------------------------------------------
// Definitions:
//   helper:        object of class JetHelper
//   helped object: object of class pat::Jet
//
//
// The following variables are automatically defined and available to
//       all methods:
//
//         blockname          name of config. buffer object (config block) 
//         buffername         name of buffer in config block
//         labelname          name of label in config block (for getByLabel)
//         parameter          parameter (as key, value pairs)
//                            accessed as in the following example:
//
//                            string param = parameter("label");
//
//         0. hltconfig       pointer to HLTConfigProvider
//                            Note: this will be zero if HLTConfigProvider
//                                  has not been properly initialized
//
//         1. config          pointer to global ParameterSet object
//         2. event           pointer to the current event
//         3. object          pointer to the current helped object
//         4. oindex          index of current helped object
//
//         5. index           index of item(s) returned by helper.
//                            Note 1: an item is associated with all
//                                    helper methods (think of it as an
//                                    extension of the helped object)
//                                  
//                            Note 2: index may differ from oindex if,
//                                    for a given helped object, the count
//                                    variable (see below) differs from 1.
//
//         6. count           number of items per helped object (default=1)
//                            Note:
//                                  count = 0  ==> current helped object is
//                                                 to be skipped
//
//                                  count = 1  ==> current helped object is
//                                                 to be kept
//
//                                  count > 1  ==> current helped object is
//                                                 associated with "count"
//                                                 items, where each item
//                                                 is associated with all the
//                                                 helper methods
//
//       variables 0-6 are initialized by TheNtupleMaker.
//       variables 0-5 should not be changed.
//       variable    6 can be changed by the helper to control whether a
//                     helped object should be kept or generates more items
//-----------------------------------------------------------------------------

namespace pat
{
  /// A helper class for pat::Jet.
  class JetHelper : public HelperFor<pat::Jet>
  {
  public:
	///
	JetHelper();

	virtual ~JetHelper();

	// Uncomment if this class does some event-level analysis
	virtual void analyzeEvent();
	 
	// Uncomment if this class does some object-level analysis
	virtual void analyzeObject();

	// ---------------------------------------------------------
	// -- User access methods go here
	// ---------------------------------------------------------
	/*
        float puJetId_nParticles() const { return (*puJetId_)[jets_->refAt(oindex)].nParticles(); }
        float puJetId_nCharged() const { return (*puJetId_)[jets_->refAt(oindex)].nCharged(); }
        float puJetId_leadChFrac() const { return (*puJetId_)[jets_->refAt(oindex)].leadChFrac(); }
        float puJetId_secondChFrac() const { return (*puJetId_)[jets_->refAt(oindex)].secondChFrac(); }
        float puJetId_thirdChFrac() const { return (*puJetId_)[jets_->refAt(oindex)].thirdChFrac(); }
        float puJetId_fourthChFrac() const { return (*puJetId_)[jets_->refAt(oindex)].fourthChFrac(); }
        float puJetId_leadNeutFrac() const { return (*puJetId_)[jets_->refAt(oindex)].leadNeutFrac(); }
        float puJetId_secondNeutFrac() const { return (*puJetId_)[jets_->refAt(oindex)].secondNeutFrac(); }
        float puJetId_thirdNeutFrac() const { return (*puJetId_)[jets_->refAt(oindex)].thirdNeutFrac(); }
        float puJetId_fourthNeutFrac() const { return (*puJetId_)[jets_->refAt(oindex)].fourthNeutFrac(); }
        float puJetId_leadPt() const { return (*puJetId_)[jets_->refAt(oindex)].leadPt(); }
        float puJetId_leadEta() const { return (*puJetId_)[jets_->refAt(oindex)].leadEta(); }
        float puJetId_leadPhi() const { return (*puJetId_)[jets_->refAt(oindex)].leadPhi(); }
        float puJetId_secondPt() const { return (*puJetId_)[jets_->refAt(oindex)].secondPt(); }
        float puJetId_secondEta() const { return (*puJetId_)[jets_->refAt(oindex)].secondEta(); }
        float puJetId_secondPhi() const { return (*puJetId_)[jets_->refAt(oindex)].secondPhi(); }
        float puJetId_dRLeadCent() const { return (*puJetId_)[jets_->refAt(oindex)].dRLeadCent(); }
        float puJetId_dRLead2nd() const { return (*puJetId_)[jets_->refAt(oindex)].dRLead2nd(); }
        float puJetId_dRMean() const { return (*puJetId_)[jets_->refAt(oindex)].dRMean(); }
        float puJetId_dR2Mean() const { return (*puJetId_)[jets_->refAt(oindex)].dR2Mean(); }
        float puJetId_ptD() const { return (*puJetId_)[jets_->refAt(oindex)].ptD(); }
        float puJetId_ptMean() const { return (*puJetId_)[jets_->refAt(oindex)].ptMean(); }
        float puJetId_ptRMS() const { return (*puJetId_)[jets_->refAt(oindex)].ptRMS(); }
        float puJetId_pt2A() const { return (*puJetId_)[jets_->refAt(oindex)].pt2A(); }
        float puJetId_sumPt() const { return (*puJetId_)[jets_->refAt(oindex)].sumPt(); }
        float puJetId_leadFrac() const { return (*puJetId_)[jets_->refAt(oindex)].leadFrac(); }
        float puJetId_secondFrac() const { return (*puJetId_)[jets_->refAt(oindex)].secondFrac(); }
        float puJetId_frac01() const { return (*puJetId_)[jets_->refAt(oindex)].frac01(); }
        float puJetId_frac02() const { return (*puJetId_)[jets_->refAt(oindex)].frac02(); }
        float puJetId_frac03() const { return (*puJetId_)[jets_->refAt(oindex)].frac03(); }
        float puJetId_frac04() const { return (*puJetId_)[jets_->refAt(oindex)].frac04(); }
        float puJetId_frac05() const { return (*puJetId_)[jets_->refAt(oindex)].frac05(); }
        float puJetId_leadCharge() const { return (*puJetId_)[jets_->refAt(oindex)].leadCharge(); }
        float puJetId_secondCharge() const { return (*puJetId_)[jets_->refAt(oindex)].secondCharge(); }
	
        float daughter_0_puJetId_nParticles() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].nParticles():-999; }
        float daughter_0_puJetId_nCharged() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].nCharged():-999; }
        float daughter_0_puJetId_leadChFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadChFrac():-999; }
        float daughter_0_puJetId_secondChFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondChFrac():-999; }
        float daughter_0_puJetId_thirdChFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].thirdChFrac():-999; }
        float daughter_0_puJetId_fourthChFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].fourthChFrac():-999; }
        float daughter_0_puJetId_leadNeutFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadNeutFrac():-999; }
        float daughter_0_puJetId_secondNeutFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondNeutFrac():-999; }
        float daughter_0_puJetId_thirdNeutFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].thirdNeutFrac():-999; }
        float daughter_0_puJetId_fourthNeutFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].fourthNeutFrac():-999; }
        float daughter_0_puJetId_leadPt() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadPt():-999; }
        float daughter_0_puJetId_leadEta() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadEta():-999; }
        float daughter_0_puJetId_leadPhi() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadPhi():-999; }
        float daughter_0_puJetId_secondPt() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondPt():-999; }
        float daughter_0_puJetId_secondEta() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondEta():-999; }
        float daughter_0_puJetId_secondPhi() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondPhi():-999; }
        float daughter_0_puJetId_dRLeadCent() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].dRLeadCent():-999; }
        float daughter_0_puJetId_dRLead2nd() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].dRLead2nd():-999; }
        float daughter_0_puJetId_dRMean() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].dRMean():-999; }
        float daughter_0_puJetId_dR2Mean() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].dR2Mean():-999; }
        float daughter_0_puJetId_ptD() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].ptD():-999; }
        float daughter_0_puJetId_ptMean() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].ptMean():-999; }
        float daughter_0_puJetId_ptRMS() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].ptRMS():-999; }
        float daughter_0_puJetId_pt2A() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].pt2A():-999; }
        float daughter_0_puJetId_sumPt() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].sumPt():-999; }
        float daughter_0_puJetId_leadFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadFrac():-999; }
        float daughter_0_puJetId_secondFrac() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondFrac():-999; }
        float daughter_0_puJetId_frac01() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].frac01():-999; }
        float daughter_0_puJetId_frac02() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].frac02():-999; }
        float daughter_0_puJetId_frac03() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].frac03():-999; }
        float daughter_0_puJetId_frac04() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].frac04():-999; }
        float daughter_0_puJetId_frac05() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].frac05():-999; }
        float daughter_0_puJetId_leadCharge() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].leadCharge():-999; }
        float daughter_0_puJetId_secondCharge() const { return (object->numberOfDaughters()>0)?(*subJetpuJetId_)[object->daughterPtr(0)].secondCharge():-999; }

        float daughter_1_puJetId_nParticles() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].nParticles():-999; }
        float daughter_1_puJetId_nCharged() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].nCharged():-999; }
        float daughter_1_puJetId_leadChFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadChFrac():-999; }
        float daughter_1_puJetId_secondChFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondChFrac():-999; }
        float daughter_1_puJetId_thirdChFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].thirdChFrac():-999; }
        float daughter_1_puJetId_fourthChFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].fourthChFrac():-999; }
        float daughter_1_puJetId_leadNeutFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadNeutFrac():-999; }
        float daughter_1_puJetId_secondNeutFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondNeutFrac():-999; }
        float daughter_1_puJetId_thirdNeutFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].thirdNeutFrac():-999; }
        float daughter_1_puJetId_fourthNeutFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].fourthNeutFrac():-999; }
        float daughter_1_puJetId_leadPt() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadPt():-999; }
        float daughter_1_puJetId_leadEta() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadEta():-999; }
        float daughter_1_puJetId_leadPhi() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadPhi():-999; }
        float daughter_1_puJetId_secondPt() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondPt():-999; }
        float daughter_1_puJetId_secondEta() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondEta():-999; }
        float daughter_1_puJetId_secondPhi() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondPhi():-999; }
        float daughter_1_puJetId_dRLeadCent() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].dRLeadCent():-999; }
        float daughter_1_puJetId_dRLead2nd() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].dRLead2nd():-999; }
        float daughter_1_puJetId_dRMean() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].dRMean():-999; }
        float daughter_1_puJetId_dR2Mean() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].dR2Mean():-999; }
        float daughter_1_puJetId_ptD() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].ptD():-999; }
        float daughter_1_puJetId_ptMean() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].ptMean():-999; }
        float daughter_1_puJetId_ptRMS() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].ptRMS():-999; }
        float daughter_1_puJetId_pt2A() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].pt2A():-999; }
        float daughter_1_puJetId_sumPt() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].sumPt():-999; }
        float daughter_1_puJetId_leadFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadFrac():-999; }
        float daughter_1_puJetId_secondFrac() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondFrac():-999; }
        float daughter_1_puJetId_frac01() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].frac01():-999; }
        float daughter_1_puJetId_frac02() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].frac02():-999; }
        float daughter_1_puJetId_frac03() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].frac03():-999; }
        float daughter_1_puJetId_frac04() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].frac04():-999; }
        float daughter_1_puJetId_frac05() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].frac05():-999; }
        float daughter_1_puJetId_leadCharge() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].leadCharge():-999; }
        float daughter_1_puJetId_secondCharge() const { return (object->numberOfDaughters()>1)?(*subJetpuJetId_)[object->daughterPtr(1)].secondCharge():-999; }
	*/
	
	
        float getTau(int num) const;
        float tau1() const { return getTau(1); }
        float tau2() const { return getTau(2); }
        float tau3() const { return getTau(3); }

        float getGenTau(int num, double minPt=0, bool CHS=false) const;
        float genTau1() const { return getGenTau(1); }
        float genTau2() const { return getGenTau(2); }
        float genTau3() const { return getGenTau(3); }
        float genTau1Pt2() const { return getGenTau(1,2.0); }
        float genTau2Pt2() const { return getGenTau(2,2.0); }
        float genTau1Pt5() const { return getGenTau(1,5.0); }
        float genTau2Pt5() const { return getGenTau(2,5.0); }
        float genTau1CHS() const { return getGenTau(1,0,true); }
        float genTau2CHS() const { return getGenTau(2,0,true); }
        float genTau21PUcorrected(double minPt=0, bool CHS=false) const;
        float genTau21PUcorrectedCHS() const { return genTau21PUcorrected(0,true); }

        float getGenCaloJetMass(double calosize=0.1, bool PF=false, bool correctTracks=false) const;
        float getGenCaloJetMass0005() const { return getGenCaloJetMass(0.005,false,false); }
        float getGenCaloJetMass001() const { return getGenCaloJetMass(0.01,false,false); }
        float getGenCaloJetMass002() const { return getGenCaloJetMass(0.02,false,false); }
        float getGenCaloJetMass005() const { return getGenCaloJetMass(0.05,false,false); }
        float getGenCaloJetMass01() const { return getGenCaloJetMass(0.1,false,false); }
        float getGenCaloJetMass02() const { return getGenCaloJetMass(0.2,false,false); }
        float getGenCaloJetMass05() const { return getGenCaloJetMass(0.5,false,false); }
        float getGenCaloJetMassPF0005() const { return getGenCaloJetMass(0.005,true,false); }
        float getGenCaloJetMassPF001() const { return getGenCaloJetMass(0.01,true,false); }
        float getGenCaloJetMassPF002() const { return getGenCaloJetMass(0.02,true,false); }
        float getGenCaloJetMassPF005() const { return getGenCaloJetMass(0.05,true,false); }
        float getGenCaloJetMassPF01() const { return getGenCaloJetMass(0.1,true,false); }
        float getGenCaloJetMassPF02() const { return getGenCaloJetMass(0.2,true,false); }
        float getGenCaloJetMassPF05() const { return getGenCaloJetMass(0.5,true,false); }
        float getGenCaloJetMassPFcorrect0005() const { return getGenCaloJetMass(0.005,true,true); }
        float getGenCaloJetMassPFcorrect001() const { return getGenCaloJetMass(0.01,true,true); }
        float getGenCaloJetMassPFcorrect002() const { return getGenCaloJetMass(0.02,true,true); }
        float getGenCaloJetMassPFcorrect005() const { return getGenCaloJetMass(0.05,true,true); }
        float getGenCaloJetMassPFcorrect01() const { return getGenCaloJetMass(0.1,true,true); }
        float getGenCaloJetMassPFcorrect02() const { return getGenCaloJetMass(0.2,true,true); }
        float getGenCaloJetMassPFcorrect05() const { return getGenCaloJetMass(0.5,true,true); }
        float getGenTrackJetMass() const;
        float getCorrectedPrunedJetMass() const;
        float getSplitBlockPrunedJetMass() const;
        float getPrunedJetMass() const;
        float getTrackJetMass() const;


        int getNcharged(double relPt=0) const;
        int getNneutral(double relPt=0) const;
        int genNCHS() const;

        int getNcharged01() const { return getNcharged(0.1); }
        int getNneutral01() const { return getNneutral(0.1); }

        float getChargedPt(unsigned int num) const;
        float getPt(unsigned int num) const;

        float getChargedPt0() const { return getChargedPt(0); }
        float getChargedPt1() const { return getChargedPt(1); }
        float getChargedPt2() const { return getChargedPt(2); }
        float getChargedPt3() const { return getChargedPt(3); }
	
        float getPt0() const { return getPt(0); }
        float getPt1() const { return getPt(1); }
        float getPt2() const { return getPt(2); }
        float getPt3() const { return getPt(3); }
	
        float getJetCharge(float kappa) const;
        float getGenJetCharge(float kappa, bool CHS=false) const;
        float getDaughter_0_jetCharge(float kappa) const;
        float getDaughter_1_jetCharge(float kappa) const;

        float getC2beta(float beta) const;
        float C2beta05() const { return getC2beta(0.5); };
        float C2beta10() const { return getC2beta(1.0); };
        float C2beta15() const { return getC2beta(1.5); };
        float C2beta17() const { return getC2beta(1.7); };
        float C2beta20() const { return getC2beta(2.0); };
        float C2beta25() const { return getC2beta(2.5); };

        float getGenC2beta(float beta, bool CHS=false) const;
        float genC2beta05() const { return getGenC2beta(0.5); };
        float genC2beta10() const { return getGenC2beta(1.0); };
        float genC2beta15() const { return getGenC2beta(1.5); };
        float genC2beta17() const { return getGenC2beta(1.7); };
        float genC2beta20() const { return getGenC2beta(2.0); };
        float genC2beta25() const { return getGenC2beta(2.5); };
        float genC2beta17CHS() const { return getGenC2beta(1.7,true); };

        float jetCharge03() const { return getJetCharge(0.3); };
        float jetCharge05() const { return getJetCharge(0.5); };
        float jetCharge10() const { return getJetCharge(1.0); };

        float genJetCharge03() const { return getGenJetCharge(0.3); };
        float genJetCharge05() const { return getGenJetCharge(0.5); };
        float genJetCharge10() const { return getGenJetCharge(1.0); };

        float daughter_0_jetCharge03() const { return getDaughter_0_jetCharge(0.3); };
        float daughter_1_jetCharge03() const { return getDaughter_1_jetCharge(0.3); };
        float daughter_0_jetCharge05() const { return getDaughter_0_jetCharge(0.5); };
        float daughter_1_jetCharge05() const { return getDaughter_1_jetCharge(0.5); };
        float daughter_0_jetCharge10() const { return getDaughter_0_jetCharge(1.0); };
        float daughter_1_jetCharge10() const { return getDaughter_1_jetCharge(1.0); };

        float daughter_0_combinedSecondaryVertexBJetTags() const { return (object->numberOfDaughters()>0)?(dynamic_cast<const pat::Jet*>(object->daughter(0))->bDiscriminator("combinedSecondaryVertexBJetTags")):-999; }
        float daughter_1_combinedSecondaryVertexBJetTags() const { return (object->numberOfDaughters()>1)?(dynamic_cast<const pat::Jet*>(object->daughter(1))->bDiscriminator("combinedSecondaryVertexBJetTags")):-999; }

  private:
    // -- User internals
        edm::Handle<std::vector<pat::Jet> > jets_;
        edm::Handle<std::vector<reco::GenParticle> > genParticles_;
        //edm::Handle<edm::ValueMap<StoredPileupJetIdentifier> > puJetId_;
        //edm::Handle<edm::ValueMap<StoredPileupJetIdentifier> > subJetpuJetId_;
        //edm::Handle<edm::ValueMap<pat::JetCorrFactors> > jcf_;

  public:
	
    // ---------------------------------------------------------
    // -- Access Methods
    // ---------------------------------------------------------

    // Default

    const reco::TrackRefVector associatedTracks() const
    { return object->associatedTracks(); }

    const std::vector<std::string> availableJECLevels(int set=0) const
    { return object->availableJECLevels(set); }

    const std::vector<std::string> availableJECLevels(std::string set) const
    { return object->availableJECLevels(set); }

    const std::vector<std::string> availableJECSets() const
    { return object->availableJECSets(); }

    float bDiscriminator(std::string theLabel) const
    { return object->bDiscriminator(theLabel); }

    math::XYZVector boostToCM() const { return object->boostToCM(); }

    const pat::CaloSpecific caloSpecific() const
    { return object->caloSpecific(); }

    const CaloTowerFwdPtrVector caloTowersFwdPtr() const
    { return object->caloTowersFwdPtr(); }

    int charge() const { return object->charge(); }

    float chargedEmEnergy() const { return object->chargedEmEnergy(); }

    float chargedEmEnergyFraction() const
    { return object->chargedEmEnergyFraction(); }

    float chargedHadronEnergy() const { return object->chargedHadronEnergy(); }

    float chargedHadronEnergyFraction() const
    { return object->chargedHadronEnergyFraction(); }

    int chargedHadronMultiplicity() const
    { return object->chargedHadronMultiplicity(); }

    float chargedMuEnergy() const { return object->chargedMuEnergy(); }

    float chargedMuEnergyFraction() const
    { return object->chargedMuEnergyFraction(); }

    int chargedMultiplicity() const { return object->chargedMultiplicity(); }

    float constituentEtaPhiSpread() const
    { return object->constituentEtaPhiSpread(); }

    float constituentPtDistribution() const
    { return object->constituentPtDistribution(); }

    pat::Jet
    correctedJet(std::string level, std::string flavor="none", std::string set="") const
    { return object->correctedJet(level, flavor, set); }

    const math::XYZTLorentzVector
    correctedP4(std::string level, std::string flavor="none", std::string set="") const
    { return object->correctedP4(level, flavor, set); }

    pat::JetCorrFactors::Flavor currentJECFlavor() const
    { return object->currentJECFlavor(); }

    std::string currentJECLevel() const { return object->currentJECLevel(); }

    std::string currentJECSet() const { return object->currentJECSet(); }

    reco::PFJet* daughter(int s) const
    //{ return (reco::Candidate*)object->daughter(s); }
    { return (reco::PFJet*)object->daughter(s); }

    const std::vector<edm::Ptr<reco::Candidate> > daughterPtrVector() const
    { return object->daughterPtrVector(); }

    float detectorEta(float fZVertex, float fPhysicsEta) const
    { return object->detectorEta(fZVertex, fPhysicsEta); }

    std::vector<std::pair<std::string,pat::LookupTableRecord> >
    efficiencies() const
    { return object->efficiencies(); }

    const pat::LookupTableRecord efficiency(std::string name) const
    { return object->efficiency(name); }

    const std::vector<std::string> efficiencyNames() const
    { return object->efficiencyNames(); }

    const std::vector<pat::LookupTableRecord> efficiencyValues() const
    { return object->efficiencyValues(); }

    float elecMultiplicity() const { return object->elecMultiplicity(); }

    const reco::TrackRefVector elecsInVertexInCalo() const
    { return object->elecsInVertexInCalo(); }

    const reco::TrackRefVector elecsInVertexOutCalo() const
    { return object->elecsInVertexOutCalo(); }

    const reco::TrackRefVector elecsOutVertexInCalo() const
    { return object->elecsOutVertexInCalo(); }

    float electronEnergy() const { return object->electronEnergy(); }

    float electronEnergyFraction() const
    { return object->electronEnergyFraction(); }

    int electronMultiplicity() const { return object->electronMultiplicity(); }

    float emEnergyFraction() const { return object->emEnergyFraction(); }

    float emEnergyInEB() const { return object->emEnergyInEB(); }

    float emEnergyInEE() const { return object->emEnergyInEE(); }

    float emEnergyInHF() const { return object->emEnergyInHF(); }

    double energy() const { return object->energy(); }

    float energyFractionHadronic() const
    { return object->energyFractionHadronic(); }

    double et() const { return object->et(); }

    double eta() const { return object->eta(); }

    float etaetaMoment() const { return object->etaetaMoment(); }

    float etaphiMoment() const { return object->etaphiMoment(); }

    reco::Jet::EtaPhiMoments etaPhiStatistics() const
    { return object->etaPhiStatistics(); }

    float etInAnnulus(float fRmin, float fRmax) const
    { return object->etInAnnulus(fRmin, fRmax); }

    reco::GenJet* genJet() const { return (reco::GenJet*)object->genJet(); }

    const edm::FwdRef<std::vector<reco::GenJet>,reco::GenJet,edm::refhelper::FindUsingAdvance<std::vector<reco::GenJet>,reco::GenJet> >
    genJetFwdRef() const
    { return object->genJetFwdRef(); }

    std::vector<reco::GenParticleRef> genParticleRefs() const
    { return object->genParticleRefs(); }

    size_t genParticlesSize() const { return object->genParticlesSize(); }

    reco::GenParticle* genParton() const
    { return (reco::GenParticle*)object->genParton(); }

    CaloTowerPtr getCaloConstituent(unsigned int fIndex) const
    { return object->getCaloConstituent(fIndex); }

    const std::vector<edm::Ptr<CaloTower> > getCaloConstituents() const
    { return object->getCaloConstituents(); }

    std::vector<edm::Ptr<reco::Candidate> > getJetConstituents() const
    { return object->getJetConstituents(); }

    std::vector<const reco::Candidate*> getJetConstituentsQuick() const
    { return object->getJetConstituentsQuick(); }

    const pat::CandKinResolution getKinResolution(std::string label="") const
    { return object->getKinResolution(label); }

    const std::vector<std::pair<std::string,float> > getPairDiscri() const
    { return object->getPairDiscri(); }

    reco::PFCandidatePtr getPFConstituent(unsigned int fIndex) const
    { return object->getPFConstituent(fIndex); }

    const std::vector<edm::Ptr<reco::PFCandidate> > getPFConstituents() const
    { return object->getPFConstituents(); }

    float hadEnergyInHB() const { return object->hadEnergyInHB(); }

    float hadEnergyInHE() const { return object->hadEnergyInHE(); }

    float hadEnergyInHF() const { return object->hadEnergyInHF(); }

    float hadEnergyInHO() const { return object->hadEnergyInHO(); }

    bool hasKinResolution(std::string label="") const
    { return object->hasKinResolution(label); }

    bool hasOverlaps(std::string label) const
    { return object->hasOverlaps(label); }

    bool hasTagInfo(std::string label) const
    { return object->hasTagInfo(label); }

    bool hasUserCand(std::string key) const
    { return object->hasUserCand(key); }

    bool hasUserData(std::string key) const
    { return object->hasUserData(key); }

    bool hasUserFloat(char* key) const { return object->hasUserFloat(key); }

    bool hasUserFloat(std::string key) const
    { return object->hasUserFloat(key); }

    bool hasUserInt(std::string key) const { return object->hasUserInt(key); }

    float HFEMEnergy() const { return object->HFEMEnergy(); }

    float HFEMEnergyFraction() const { return object->HFEMEnergyFraction(); }

    int HFEMMultiplicity() const { return object->HFEMMultiplicity(); }

    float HFHadronEnergy() const { return object->HFHadronEnergy(); }

    float HFHadronEnergyFraction() const
    { return object->HFHadronEnergyFraction(); }

    int HFHadronMultiplicity() const { return object->HFHadronMultiplicity(); }

    bool isBasicJet() const { return object->isBasicJet(); }

    bool isCaloJet() const { return object->isCaloJet(); }

    bool isCaloMuon() const { return object->isCaloMuon(); }

    bool isConvertedPhoton() const { return object->isConvertedPhoton(); }

    bool isElectron() const { return object->isElectron(); }

    bool isGlobalMuon() const { return object->isGlobalMuon(); }

    bool isJet() const { return object->isJet(); }

    bool isJPTJet() const { return object->isJPTJet(); }

    bool isMuon() const { return object->isMuon(); }

    bool isPFJet() const { return object->isPFJet(); }

    bool isPhoton() const { return object->isPhoton(); }

    bool isStandAloneMuon() const { return object->isStandAloneMuon(); }

    bool isTrackerMuon() const { return object->isTrackerMuon(); }

    float
    jecFactor(std::string level, std::string flavor="none", std::string set="") const
    { return object->jecFactor(level, flavor, set); }

    bool jecSetAvailable(std::string set) const
    { return object->jecSetAvailable(set); }

    bool jecSetAvailable(unsigned int set) const
    { return object->jecSetAvailable(set); }

    bool jecSetsAvailable() const { return object->jecSetsAvailable(); }

    float jetArea() const { return object->jetArea(); }

//    float jetCharge() const { return object->jetCharge(); }

    const reco::JetID jetID() const { return object->jetID(); }

    const pat::JPTSpecific jptSpecific() const
    { return object->jptSpecific(); }

    bool longLived() const { return object->longLived(); }

    double mass() const { return object->mass(); }

    bool massConstraint() const { return object->massConstraint(); }

    double massSqr() const { return object->massSqr(); }

    float maxDistance() const { return object->maxDistance(); }

    float maxEInEmTowers() const { return object->maxEInEmTowers(); }

    float maxEInHadTowers() const { return object->maxEInHadTowers(); }

    math::XYZVector momentum() const { return object->momentum(); }

    double mt() const { return object->mt(); }

    double mtSqr() const { return object->mtSqr(); }

    float muonEnergy() const { return object->muonEnergy(); }

    float muonEnergyFraction() const { return object->muonEnergyFraction(); }

    int muonMultiplicity() const { return object->muonMultiplicity(); }

    const reco::TrackRefVector muonsInVertexInCalo() const
    { return object->muonsInVertexInCalo(); }

    const reco::TrackRefVector muonsInVertexOutCalo() const
    { return object->muonsInVertexOutCalo(); }

    const reco::TrackRefVector muonsOutVertexInCalo() const
    { return object->muonsOutVertexInCalo(); }

    int n60() const { return object->n60(); }

    int n90() const { return object->n90(); }

    int nCarrying(float fFraction) const
    { return object->nCarrying(fFraction); }

    int nConstituents() const { return object->nConstituents(); }

    float neutralEmEnergy() const { return object->neutralEmEnergy(); }

    float neutralEmEnergyFraction() const
    { return object->neutralEmEnergyFraction(); }

    float neutralHadronEnergy() const { return object->neutralHadronEnergy(); }

    float neutralHadronEnergyFraction() const
    { return object->neutralHadronEnergyFraction(); }

    int neutralHadronMultiplicity() const
    { return object->neutralHadronMultiplicity(); }

    int neutralMultiplicity() const { return object->neutralMultiplicity(); }

    int nPasses() const { return object->nPasses(); }

    size_t numberOfDaughters() const { return object->numberOfDaughters(); }

    size_t numberOfMothers() const { return object->numberOfMothers(); }

    size_t numberOfSourceCandidatePtrs() const
    { return object->numberOfSourceCandidatePtrs(); }

    reco::Candidate* originalObject() const
    { return (reco::Candidate*)object->originalObject(); }

    const edm::Ptr<reco::Candidate> originalObjectRef() const
    { return object->originalObjectRef(); }

    const std::vector<std::string> overlapLabels() const
    { return object->overlapLabels(); }

    const edm::PtrVector<reco::Candidate> overlaps(std::string label) const
    { return object->overlaps(label); }

    double p() const { return object->p(); }

    const math::XYZTLorentzVector p4() const { return object->p4(); }

    int partonFlavour() const { return object->partonFlavour(); }

    int pdgId() const { return object->pdgId(); }

    const reco::PFCandidateFwdPtrVector pfCandidatesFwdPtr() const
    { return object->pfCandidatesFwdPtr(); }

    const pat::PFSpecific pfSpecific() const { return object->pfSpecific(); }

    double phi() const { return object->phi(); }

    float phiphiMoment() const { return object->phiphiMoment(); }

    float photonEnergy() const { return object->photonEnergy(); }

    float photonEnergyFraction() const
    { return object->photonEnergyFraction(); }

    int photonMultiplicity() const { return object->photonMultiplicity(); }

    float physicsEta(float fZVertex, float fDetectorEta) const
    { return object->physicsEta(fZVertex, fDetectorEta); }

    float pileup() const { return object->pileup(); }

    const reco::TrackRefVector pionsInVertexInCalo() const
    { return object->pionsInVertexInCalo(); }

    const reco::TrackRefVector pionsInVertexOutCalo() const
    { return object->pionsInVertexOutCalo(); }

    const reco::TrackRefVector pionsOutVertexInCalo() const
    { return object->pionsOutVertexInCalo(); }

    const math::PtEtaPhiMLorentzVector polarP4() const
    { return object->polarP4(); }

    double pt() const { return object->pt(); }

    double px() const { return object->px(); }

    double py() const { return object->py(); }

    double pz() const { return object->pz(); }

    double rapidity() const { return object->rapidity(); }

    double resolE(std::string label="") const { return object->resolE(label); }

    double resolEt(std::string label="") const
    { return object->resolEt(label); }

    double resolEta(std::string label="") const
    { return object->resolEta(label); }

    double resolM(std::string label="") const { return object->resolM(label); }

    double resolP(std::string label="") const { return object->resolP(label); }

    double resolPhi(std::string label="") const
    { return object->resolPhi(label); }

    double resolPInv(std::string label="") const
    { return object->resolPInv(label); }

    double resolPt(std::string label="") const
    { return object->resolPt(label); }

    double resolPx(std::string label="") const
    { return object->resolPx(label); }

    double resolPy(std::string label="") const
    { return object->resolPy(label); }

    double resolPz(std::string label="") const
    { return object->resolPz(label); }

    double resolTheta(std::string label="") const
    { return object->resolTheta(label); }

    int status() const { return object->status(); }

    reco::BaseTagInfo* tagInfo(std::string label) const
    { return (reco::BaseTagInfo*)object->tagInfo(label); }

    reco::SecondaryVertexTagInfo*
    tagInfoSecondaryVertex(std::string label="") const
    { return (reco::SecondaryVertexTagInfo*)object->tagInfoSecondaryVertex(label); }

    const pat::TagInfoFwdPtrCollection tagInfosFwdPtr() const
    { return object->tagInfosFwdPtr(); }

    reco::SoftLeptonTagInfo* tagInfoSoftLepton(std::string label="") const
    { return (reco::SoftLeptonTagInfo*)object->tagInfoSoftLepton(label); }

    reco::TrackIPTagInfo* tagInfoTrackIP(std::string label="") const
    { return (reco::TrackIPTagInfo*)object->tagInfoTrackIP(label); }

    double theta() const { return object->theta(); }

    int threeCharge() const { return object->threeCharge(); }

    float towersArea() const { return object->towersArea(); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatches() const
    { return object->triggerObjectMatches(); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByAlgorithm(char* nameAlgorithm, bool algoCondAccepted=true) const
    { return object->triggerObjectMatchesByAlgorithm(nameAlgorithm, algoCondAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByAlgorithm(char* nameAlgorithm, unsigned int algoCondAccepted) const
    { return object->triggerObjectMatchesByAlgorithm(nameAlgorithm, algoCondAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByAlgorithm(std::string nameAlgorithm, bool algoCondAccepted=true) const
    { return object->triggerObjectMatchesByAlgorithm(nameAlgorithm, algoCondAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByAlgorithm(std::string nameAlgorithm, unsigned int algoCondAccepted) const
    { return object->triggerObjectMatchesByAlgorithm(nameAlgorithm, algoCondAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByCollection(char* coll) const
    { return object->triggerObjectMatchesByCollection(coll); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByCollection(std::string coll) const
    { return object->triggerObjectMatchesByCollection(coll); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByCondition(char* nameCondition) const
    { return object->triggerObjectMatchesByCondition(nameCondition); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByCondition(std::string nameCondition) const
    { return object->triggerObjectMatchesByCondition(nameCondition); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByFilter(char* labelFilter) const
    { return object->triggerObjectMatchesByFilter(labelFilter); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByFilter(std::string labelFilter) const
    { return object->triggerObjectMatchesByFilter(labelFilter); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByFilterID(unsigned int triggerObjectType) const
    { return object->triggerObjectMatchesByFilterID(triggerObjectType); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByPath(char* namePath, bool pathLastFilterAccepted=false, bool pathL3FilterAccepted=true) const
    { return object->triggerObjectMatchesByPath(namePath, pathLastFilterAccepted, pathL3FilterAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByPath(char* namePath, unsigned int pathLastFilterAccepted, unsigned int pathL3FilterAccepted=1) const
    { return object->triggerObjectMatchesByPath(namePath, pathLastFilterAccepted, pathL3FilterAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByPath(std::string namePath, bool pathLastFilterAccepted=false, bool pathL3FilterAccepted=true) const
    { return object->triggerObjectMatchesByPath(namePath, pathLastFilterAccepted, pathL3FilterAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByPath(std::string namePath, unsigned int pathLastFilterAccepted, unsigned int pathL3FilterAccepted=1) const
    { return object->triggerObjectMatchesByPath(namePath, pathLastFilterAccepted, pathL3FilterAccepted); }

    const std::vector<pat::TriggerObjectStandAlone>
    triggerObjectMatchesByType(unsigned int triggerObjectType) const
    { return object->triggerObjectMatchesByType(triggerObjectType); }

    edm::Ptr<reco::Candidate> userCand(std::string key) const
    { return object->userCand(key); }

    const std::vector<std::string> userCandNames() const
    { return object->userCandNames(); }

    const std::vector<std::string> userDataNames() const
    { return object->userDataNames(); }

    const std::string userDataObjectType(std::string key) const
    { return object->userDataObjectType(key); }

    float userFloat(char* key) const { return object->userFloat(key); }

    float userFloat(std::string key) const { return object->userFloat(key); }

    const std::vector<std::string> userFloatNames() const
    { return object->userFloatNames(); }

    int userInt(std::string key) const { return object->userInt(key); }

    const std::vector<std::string> userIntNames() const
    { return object->userIntNames(); }

    const math::XYZPoint vertex() const { return object->vertex(); }

    double vertexChi2() const { return object->vertexChi2(); }

    ROOT::Math::SMatrix<double,3,3,ROOT::Math::MatRepSym<double,3> >
    vertexCovariance() const
    { return object->vertexCovariance(); }

    double vertexCovariance(int i, int j) const
    { return object->vertexCovariance(i, j); }

    double vertexNdof() const { return object->vertexNdof(); }

    double vertexNormalizedChi2() const
    { return object->vertexNormalizedChi2(); }

    double vx() const { return object->vx(); }

    double vy() const { return object->vy(); }

    double vz() const { return object->vz(); }

    double y() const { return object->y(); }

    const float zspCorrection() const { return object->zspCorrection(); }
    
    

  };
}
#endif
