//-----------------------------------------------------------------------------
// File:        analyzer.cc
// Description: Analyzer for ntuples created by TheNtupleMaker
// Created:     Thu May 31 21:49:25 2012 by mkntanalyzer.py
// Author:      Andreas Hinzmann
//-----------------------------------------------------------------------------
#include "substructure_pas.h"

#ifdef PROJECT_NAME
#include "PhysicsTools/TheNtupleMaker/interface/pdg.h"
#else
#include "pdg.h"
#endif

#include "TLorentzVector.h"
#include "DataFormats/Math/interface/deltaPhi.h"

using namespace std;

Double_t DeltaRfun(Double_t eta1,Double_t eta2,Double_t phi1,Double_t phi2)
{
  return TMath::Sqrt(pow((eta1-eta2),2)+pow(deltaPhi(phi1,phi2),2));
}

Double_t fnc_dscb(Double_t *xx, Double_t *pp)
{
  Double_t x   = xx[0];
  Double_t N   = pp[0];
  Double_t mu  = pp[1];
  Double_t sig = pp[2];
  Double_t a1  = pp[3];
  Double_t p1  = pp[4];
  Double_t a2  = pp[5];
  Double_t p2  = pp[6];

  Double_t u   = (x-mu)/sig;
  Double_t A1  = TMath::Power(p1/TMath::Abs(a1),p1)*TMath::Exp(-a1*a1/2);
  Double_t A2  = TMath::Power(p2/TMath::Abs(a2),p2)*TMath::Exp(-a2*a2/2);
  Double_t B1  = p1/TMath::Abs(a1) - TMath::Abs(a1);
  Double_t B2  = p2/TMath::Abs(a2) - TMath::Abs(a2);

  Double_t result=N;
  if (u<-a1)
      result *= A1*TMath::Power(B1-u,-p1);
  else if (u<a2)
      result *= TMath::Exp(-u*u/2);
  else
      result *= A2*TMath::Power(B2+u,-p2);
  return result;
}

    //////////////////////////////////
    //// P A P E R   4 - V E C T O R   D E F I N I T I O N   O F   P H I   A N D   P H I 1
    //////////////////////////////////
void computeAngles(TLorentzVector thep4H, TLorentzVector thep4Z1, TLorentzVector thep4M11, TLorentzVector thep4M12, TLorentzVector thep4Z2, TLorentzVector thep4M21, TLorentzVector thep4M22, double& costheta1, double& costheta2, double& Phi, double& costhetastar, double& Phi1){
       
        ///////////////////////////////////////////////
        // check for z1/z2 convention, redefine all 4 vectors with convention
        ///////////////////////////////////////////////	
    TLorentzVector p4H, p4Z1, p4M11, p4M12, p4Z2, p4M21, p4M22;
    p4H = thep4H;
        
    p4Z1 = thep4Z1; p4M11 = thep4M11; p4M12 = thep4M12;
    p4Z2 = thep4Z2; p4M21 = thep4M21; p4M22 = thep4M22;
        //// costhetastar
	TVector3 boostX = -(thep4H.BoostVector());
	TLorentzVector thep4Z1inXFrame( p4Z1 );
	TLorentzVector thep4Z2inXFrame( p4Z2 );	
	thep4Z1inXFrame.Boost( boostX );
	thep4Z2inXFrame.Boost( boostX );
	TVector3 theZ1X_p3 = TVector3( thep4Z1inXFrame.X(), thep4Z1inXFrame.Y(), thep4Z1inXFrame.Z() );
	TVector3 theZ2X_p3 = TVector3( thep4Z2inXFrame.X(), thep4Z2inXFrame.Y(), thep4Z2inXFrame.Z() );    
    costhetastar = theZ1X_p3.CosTheta();

        //// --------------------------- costheta1
    TVector3 boostV1 = -(thep4Z1.BoostVector());
    TLorentzVector p4M11_BV1( p4M11 );
	TLorentzVector p4M12_BV1( p4M12 );	
    TLorentzVector p4M21_BV1( p4M21 );
	TLorentzVector p4M22_BV1( p4M22 );
    p4M11_BV1.Boost( boostV1 );
	p4M12_BV1.Boost( boostV1 );
	p4M21_BV1.Boost( boostV1 );
	p4M22_BV1.Boost( boostV1 );
    
    TLorentzVector p4V2_BV1 = p4M21_BV1 + p4M22_BV1;
        //// costheta1
    costheta1 = -p4V2_BV1.Vect().Dot( p4M11_BV1.Vect() )/p4V2_BV1.Vect().Mag()/p4M11_BV1.Vect().Mag();

        //// --------------------------- costheta2
    TVector3 boostV2 = -(thep4Z2.BoostVector());
    TLorentzVector p4M11_BV2( p4M11 );
	TLorentzVector p4M12_BV2( p4M12 );	
    TLorentzVector p4M21_BV2( p4M21 );
	TLorentzVector p4M22_BV2( p4M22 );
    p4M11_BV2.Boost( boostV2 );
	p4M12_BV2.Boost( boostV2 );
	p4M21_BV2.Boost( boostV2 );
	p4M22_BV2.Boost( boostV2 );
    
    TLorentzVector p4V1_BV2 = p4M11_BV2 + p4M12_BV2;
        //// costheta2
    costheta2 = -p4V1_BV2.Vect().Dot( p4M21_BV2.Vect() )/p4V1_BV2.Vect().Mag()/p4M21_BV2.Vect().Mag();
    
        //// --------------------------- Phi and Phi1
//    TVector3 boostX = -(thep4H.BoostVector());
    TLorentzVector p4M11_BX( p4M11 );
	TLorentzVector p4M12_BX( p4M12 );	
    TLorentzVector p4M21_BX( p4M21 );
	TLorentzVector p4M22_BX( p4M22 );	
    
	p4M11_BX.Boost( boostX );
	p4M12_BX.Boost( boostX );
	p4M21_BX.Boost( boostX );
	p4M22_BX.Boost( boostX );
    
    TVector3 tmp1 = p4M11_BX.Vect().Cross( p4M12_BX.Vect() );
    TVector3 tmp2 = p4M21_BX.Vect().Cross( p4M22_BX.Vect() );    
    
    TVector3 normal1_BX( tmp1.X()/tmp1.Mag(), tmp1.Y()/tmp1.Mag(), tmp1.Z()/tmp1.Mag() ); 
    TVector3 normal2_BX( tmp2.X()/tmp2.Mag(), tmp2.Y()/tmp2.Mag(), tmp2.Z()/tmp2.Mag() ); 

        //// Phi
    TLorentzVector p4Z1_BX = p4M11_BX + p4M12_BX;    
    double tmpSgnPhi = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normal2_BX) );
    double sgnPhi = tmpSgnPhi/fabs(tmpSgnPhi);
    Phi = sgnPhi * acos( -1.*normal1_BX.Dot( normal2_BX) );
    
    
        //////////////
    
    TVector3 beamAxis(0,0,1);
    TVector3 tmp3 = (p4M11_BX + p4M12_BX).Vect();
    
    TVector3 p3V1_BX( tmp3.X()/tmp3.Mag(), tmp3.Y()/tmp3.Mag(), tmp3.Z()/tmp3.Mag() );
    TVector3 tmp4 = beamAxis.Cross( p3V1_BX );
    TVector3 normalSC_BX( tmp4.X()/tmp4.Mag(), tmp4.Y()/tmp4.Mag(), tmp4.Z()/tmp4.Mag() );
        
        //// Phi1
    double tmpSgnPhi1 = p4Z1_BX.Vect().Dot( normal1_BX.Cross( normalSC_BX) );
    double sgnPhi1 = tmpSgnPhi1/fabs(tmpSgnPhi1);    
    Phi1 = sgnPhi1 * acos( normal1_BX.Dot( normalSC_BX) );    
    
//    std::cout << "extractAngles: " << std::endl;
//    std::cout << "costhetastar = " << costhetastar << ", costheta1 = " << costheta1 << ", costheta2 = " << costheta2 << std::endl;
//    std::cout << "Phi = " << Phi << ", Phi1 = " << Phi1 << std::endl;    

}


//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // Get file list and histogram filename from command line

  cout << "Start program" << endl;

  commandLine cmdline;
  decodeCommandLine(argc, argv, cmdline);

  // Get names of ntuple files to be processed and open chain of ntuples

  vector<string> filenames = getFilenames(cmdline.filelist);
  cout << "Open file stream" << endl;
  itreestream stream(filenames, "Events");
  if ( !stream.good() ) error("unable to open ntuple file(s)");

  // Get number of events to be read

  int nevents = stream.size();
  cout << "Number of events: " << nevents << endl;

  // Select variables to be read

  //selectVariables(stream);

  stream.select("edmEventHelper_info.bunchCrossing", eventhelper_bunchCrossing);
  stream.select("edmEventHelper_info.event", eventhelper_event);
  stream.select("edmEventHelper_info.isRealData", eventhelper_isRealData);
  stream.select("edmEventHelper_info.luminosityBlock", eventhelper_luminosityBlock);
  stream.select("edmEventHelper_info.orbitNumber", eventhelper_orbitNumber);
  stream.select("edmEventHelper_info.run", eventhelper_run);
  /*stream.select("edmEventHelperExtra_info.dijetCHS_invmass", eventhelperextra_dijetCHS_invmass);
  stream.select("edmEventHelperExtra_info.dijet_invmass", eventhelperextra_dijet_invmass);
  stream.select("edmEventHelperExtra_info.wj1CHS_energy", eventhelperextra_wj1CHS_energy);
  stream.select("edmEventHelperExtra_info.wj1CHS_eta", eventhelperextra_wj1CHS_eta);
  stream.select("edmEventHelperExtra_info.wj1CHS_mass", eventhelperextra_wj1CHS_mass);
  stream.select("edmEventHelperExtra_info.wj1CHS_nconst", eventhelperextra_wj1CHS_nconst);
  stream.select("edmEventHelperExtra_info.wj1CHS_phi", eventhelperextra_wj1CHS_phi);
  stream.select("edmEventHelperExtra_info.wj1CHS_pt", eventhelperextra_wj1CHS_pt);
  stream.select("edmEventHelperExtra_info.wj1_energy", eventhelperextra_wj1_energy);
  stream.select("edmEventHelperExtra_info.wj1_eta", eventhelperextra_wj1_eta);
  stream.select("edmEventHelperExtra_info.wj1_mass", eventhelperextra_wj1_mass);
  stream.select("edmEventHelperExtra_info.wj1_nconst", eventhelperextra_wj1_nconst);
  stream.select("edmEventHelperExtra_info.wj1_phi", eventhelperextra_wj1_phi);
  stream.select("edmEventHelperExtra_info.wj1_pt", eventhelperextra_wj1_pt);
  stream.select("edmEventHelperExtra_info.wj1wj2CHS_invmass", eventhelperextra_wj1wj2CHS_invmass);
  stream.select("edmEventHelperExtra_info.wj1wj2CHS_nconst", eventhelperextra_wj1wj2CHS_nconst);
  stream.select("edmEventHelperExtra_info.wj1wj2_invmass", eventhelperextra_wj1wj2_invmass);
  stream.select("edmEventHelperExtra_info.wj1wj2_nconst", eventhelperextra_wj1wj2_nconst);
  stream.select("edmEventHelperExtra_info.wj2CHS_energy", eventhelperextra_wj2CHS_energy);
  stream.select("edmEventHelperExtra_info.wj2CHS_eta", eventhelperextra_wj2CHS_eta);
  stream.select("edmEventHelperExtra_info.wj2CHS_mass", eventhelperextra_wj2CHS_mass);
  stream.select("edmEventHelperExtra_info.wj2CHS_nconst", eventhelperextra_wj2CHS_nconst);
  stream.select("edmEventHelperExtra_info.wj2CHS_phi", eventhelperextra_wj2CHS_phi);
  stream.select("edmEventHelperExtra_info.wj2CHS_pt", eventhelperextra_wj2CHS_pt);
  stream.select("edmEventHelperExtra_info.wj2_energy", eventhelperextra_wj2_energy);
  stream.select("edmEventHelperExtra_info.wj2_eta", eventhelperextra_wj2_eta);
  stream.select("edmEventHelperExtra_info.wj2_mass", eventhelperextra_wj2_mass);
  stream.select("edmEventHelperExtra_info.wj2_nconst", eventhelperextra_wj2_nconst);
  stream.select("edmEventHelperExtra_info.wj2_phi", eventhelperextra_wj2_phi);
  stream.select("edmEventHelperExtra_info.wj2_pt", eventhelperextra_wj2_pt);
  stream.select("edmEventHelperExtra_info.wj2_pt", eventhelperextra_wj2_pt);
  */
  stream.select("edmEventHelperExtra_info.numberOfPrimaryVertices", eventhelperextra_numberOfPrimaryVertices);
  stream.select("GenEventInfoProduct_generator.weight", geneventinfoproduct_weight);
  
  stream.select("patJetHelper_patJetsWithVar.chargedEmEnergyFraction", jethelperNoCHS_chargedEmEnergyFraction);
  stream.select("patJetHelper_patJetsWithVar.chargedHadronEnergyFraction", jethelperNoCHS_chargedHadronEnergyFraction);
  stream.select("patJetHelper_patJetsWithVar.chargedMultiplicity", jethelperNoCHS_chargedMultiplicity);
  stream.select("patJetHelper_patJetsWithVar.energy", jethelperNoCHS_energy);
  stream.select("patJetHelper_patJetsWithVar.eta", jethelperNoCHS_eta);
  stream.select("patJetHelper_patJetsWithVar.rapidity", jethelperNoCHS_rapidity);
  stream.select("patJetHelper_patJetsWithVar.mass", jethelperNoCHS_mass);
  stream.select("patJetHelper_patJetsWithVar.muonEnergyFraction", jethelperNoCHS_muonEnergyFraction);
  stream.select("patJetHelper_patJetsWithVar.nConstituents", jethelperNoCHS_nConstituents);
  stream.select("patJetHelper_patJetsWithVar.neutralEmEnergyFraction", jethelperNoCHS_neutralEmEnergyFraction);
  stream.select("patJetHelper_patJetsWithVar.neutralHadronEnergyFraction", jethelperNoCHS_neutralHadronEnergyFraction);
  stream.select("patJetHelper_patJetsWithVar.phi", jethelperNoCHS_phi);
  stream.select("patJetHelper_patJetsWithVar.pt", jethelperNoCHS_pt);
  stream.select("patJetHelper_patJetsWithVarCHS.chargedEmEnergyFraction", jethelper_chargedEmEnergyFraction);
  stream.select("patJetHelper_patJetsWithVarCHS.chargedHadronEnergyFraction", jethelper_chargedHadronEnergyFraction);
  stream.select("patJetHelper_patJetsWithVarCHS.chargedMultiplicity", jethelper_chargedMultiplicity);
  stream.select("patJetHelper_patJetsWithVarCHS.combinedSecondaryVertexBJetTags", jethelper_combinedSecondaryVertexBJetTags);
  stream.select("patJetHelper_patJetsWithVarCHS.combinedSecondaryVertexMVABJetTags", jethelper_combinedSecondaryVertexMVABJetTags);
  stream.select("patJetHelper_patJetsWithVarCHS.energy", jethelper_energy);
  stream.select("patJetHelper_patJetsWithVarCHS.eta", jethelper_eta);
  stream.select("patJetHelper_patJetsWithVarCHS.rapidity", jethelper_rapidity);
  stream.select("patJetHelper_patJetsWithVarCHS.jetBProbabilityBJetTags", jethelper_jetBProbabilityBJetTags);
  stream.select("patJetHelper_patJetsWithVarCHS.jetProbabilityBJetTags", jethelper_jetProbabilityBJetTags);
  stream.select("patJetHelper_patJetsWithVarCHS.mass", jethelper_mass);
  stream.select("patJetHelper_patJetsWithVarCHS.muonEnergyFraction", jethelper_muonEnergyFraction);
  stream.select("patJetHelper_patJetsWithVarCHS.nConstituents", jethelper_nConstituents);
  stream.select("patJetHelper_patJetsWithVarCHS.neutralEmEnergyFraction", jethelper_neutralEmEnergyFraction);
  stream.select("patJetHelper_patJetsWithVarCHS.neutralHadronEnergyFraction", jethelper_neutralHadronEnergyFraction);
  stream.select("patJetHelper_patJetsWithVarCHS.phi", jethelper_phi);
  stream.select("patJetHelper_patJetsWithVarCHS.pt", jethelper_pt);
  
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.combinedSecondaryVertexBJetTags", jethelperCA8_combinedSecondaryVertexBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.combinedSecondaryVertexMVABJetTags", jethelperCA8_combinedSecondaryVertexMVABJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.energy", jethelperCA8_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.et", jethelperCA8_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.eta", jethelperCA8_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetArea", jethelperCA8_jetArea);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetBProbabilityBJetTags", jethelperCA8_jetBProbabilityBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetProbabilityBJetTags", jethelperCA8_jetProbabilityBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.mass", jethelperCA8_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPrunedJetMass", jethelperCA8_prunedjetmass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getCorrectedPrunedJetMass", jethelperCA8_correctedprunedjetmass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getTrackJetMass", jethelperCA8_trackjetmass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getSplitBlockPrunedJetMass", jethelperCA8_splitblockprunedjetmass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetWidth", jethelperCA8_width);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getAK8JetMass", jethelperCA8_ak8mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetPFblocks", jethelperCA8_nPFblocks);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetECALclusters", jethelperCA8_nECALclusters);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetHCALclusters", jethelperCA8_nHCALclusters);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.nConstituents", jethelperCA8_nConstituents);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.partonFlavour", jethelperCA8_partonFlavour);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedEmEnergyFraction", jethelperCA8_chargedEmEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedHadronEnergyFraction", jethelperCA8_chargedHadronEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedMultiplicity", jethelperCA8_chargedMultiplicity);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.muonEnergyFraction", jethelperCA8_muonEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralEmEnergyFraction", jethelperCA8_neutralEmEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralHadronEnergyFraction", jethelperCA8_neutralHadronEnergyFraction);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.phi", jethelperCA8_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.pt", jethelperCA8_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.trackCountingHighEffBJetTags", jethelperCA8_trackCountingHighEffBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.trackCountingHighPurBJetTags", jethelperCA8_trackCountingHighPurBJetTags);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_energy", jethelperCA8_uncor_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_et", jethelperCA8_uncor_et);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_pt", jethelperCA8_uncor_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau1", jethelperCA8_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau2", jethelperCA8_tau2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta05", jethelperCA8_C2beta05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta10", jethelperCA8_C2beta10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta15", jethelperCA8_C2beta15);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta17", jethelperCA8_C2beta17);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta20", jethelperCA8_C2beta20);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta25", jethelperCA8_C2beta25);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge03", jethelperCA8_jetCharge03);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge05", jethelperCA8_jetCharge05);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge10", jethelperCA8_jetCharge10);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNcharged01", jethelperCA8_Ncharged01);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNneutral01", jethelperCA8_Nneutral01);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt2", jethelperCA8_ChargedPt2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt2", jethelperCA8_Pt2);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.mass", jethelperCA8pruned_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.pt", jethelperCA8pruned_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.eta", jethelperCA8pruned_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.phi", jethelperCA8pruned_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_pt", jethelperCA8pruned_uncor_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.numberOfDaughters", jethelperCA8pruned_numberOfDaughters);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_energy", jethelperCA8pruned_daughter_0_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_eta", jethelperCA8pruned_daughter_0_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_mass", jethelperCA8pruned_daughter_0_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_phi", jethelperCA8pruned_daughter_0_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_pt", jethelperCA8pruned_daughter_0_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_energy", jethelperCA8pruned_daughter_1_energy);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_eta", jethelperCA8pruned_daughter_1_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_mass", jethelperCA8pruned_daughter_1_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_phi", jethelperCA8pruned_daughter_1_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_pt", jethelperCA8pruned_daughter_1_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau1", jethelperCA8pruned_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau2", jethelperCA8pruned_tau2);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.mass", jethelperCA8trimmed_mass);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.pt", jethelperCA8trimmed_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.eta", jethelperCA8trimmed_eta);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.phi", jethelperCA8trimmed_phi);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.uncor_pt", jethelperCA8trimmed_uncor_pt);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.numberOfDaughters", jethelperCA8trimmed_numberOfDaughters);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.tau1", jethelperCA8trimmed_tau1);
  stream.select("patJetHelper_selectedPatJetsCA8CHStrimmed.tau2", jethelperCA8trimmed_tau2);

  stream.select("patJetHelper_patGenJetsCA8CHS.energy", jethelperGenCA8_energy);
  stream.select("patJetHelper_patGenJetsCA8CHS.et", jethelperGenCA8_et);
  stream.select("patJetHelper_patGenJetsCA8CHS.eta", jethelperGenCA8_eta);
  stream.select("patJetHelper_patGenJetsCA8CHS.jetArea", jethelperGenCA8_jetArea);
  stream.select("patJetHelper_patGenJetsCA8CHS.mass", jethelperGenCA8_mass);

  stream.select("patJetHelper_patGenJetsCA8CHS.genJetWidth", jethelperGenCA8_width);
  stream.select("patJetHelper_patGenJetsCA8CHS.nConstituents", jethelperGenCA8_nConstituents);
  stream.select("patJetHelper_patGenJetsCA8CHS.genChargedEmEnergyFraction", jethelperGenCA8_chargedEmEnergyFraction);
  stream.select("patJetHelper_patGenJetsCA8CHS.genChargedHadronEnergyFraction", jethelperGenCA8_chargedHadronEnergyFraction);
  stream.select("patJetHelper_patGenJetsCA8CHS.genChargedMultiplicity", jethelperGenCA8_chargedMultiplicity);
  stream.select("patJetHelper_patGenJetsCA8CHS.genNeutralEmEnergyFraction", jethelperGenCA8_neutralEmEnergyFraction);
  stream.select("patJetHelper_patGenJetsCA8CHS.genNeutralHadronEnergyFraction", jethelperGenCA8_neutralHadronEnergyFraction);

  stream.select("patJetHelper_patGenJetsCA8CHS.partonFlavour", jethelperGenCA8_partonFlavour);
  stream.select("patJetHelper_patGenJetsCA8CHS.phi", jethelperGenCA8_phi);
  stream.select("patJetHelper_patGenJetsCA8CHS.pt", jethelperGenCA8_pt);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1", jethelperGenCA8_tau1);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2", jethelperGenCA8_tau2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1Pt2", jethelperGenCA8_tau1Pt2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2Pt2", jethelperGenCA8_tau2Pt2);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau1CHS", jethelperGenCA8_tau1CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau2CHS", jethelperGenCA8_tau2CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau21PUcorrected", jethelperGenCA8_tau21PUcorrected);
  stream.select("patJetHelper_patGenJetsCA8CHS.genTau21PUcorrectedCHS", jethelperGenCA8_tau21PUcorrectedCHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass0005", jethelperGenCA8_calojetmass0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass001", jethelperGenCA8_calojetmass001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass002", jethelperGenCA8_calojetmass002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass005", jethelperGenCA8_calojetmass005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass01", jethelperGenCA8_calojetmass01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass02", jethelperGenCA8_calojetmass02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass05", jethelperGenCA8_calojetmass05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF0005", jethelperGenCA8_calojetmassPF0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF001", jethelperGenCA8_calojetmassPF001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF002", jethelperGenCA8_calojetmassPF002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF005", jethelperGenCA8_calojetmassPF005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF01", jethelperGenCA8_calojetmassPF01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF02", jethelperGenCA8_calojetmassPF02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF05", jethelperGenCA8_calojetmassPF05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect0005", jethelperGenCA8_calojetmassPFcorrect0005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect001", jethelperGenCA8_calojetmassPFcorrect001);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect002", jethelperGenCA8_calojetmassPFcorrect002);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect005", jethelperGenCA8_calojetmassPFcorrect005);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect01", jethelperGenCA8_calojetmassPFcorrect01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect02", jethelperGenCA8_calojetmassPFcorrect02);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect05", jethelperGenCA8_calojetmassPFcorrect05);
  stream.select("patJetHelper_patGenJetsCA8CHS.getGenTrackJetMass", jethelperGenCA8_trackjetmass);
  stream.select("patJetHelper_patGenJetsCA8CHS.genNCHS", jethelperGenCA8_NCHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta05", jethelperGenCA8_C2beta05);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta10", jethelperGenCA8_C2beta10);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta15", jethelperGenCA8_C2beta15);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17", jethelperGenCA8_C2beta17);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta20", jethelperGenCA8_C2beta20);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta25", jethelperGenCA8_C2beta25);
  stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17CHS", jethelperGenCA8_C2beta17CHS);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge03", jethelperGenCA8_jetCharge03);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge05", jethelperGenCA8_jetCharge05);
  stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge10", jethelperGenCA8_jetCharge10);
  stream.select("patJetHelper_patGenJetsCA8CHS.getNcharged01", jethelperGenCA8_Ncharged01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getNneutral01", jethelperGenCA8_Nneutral01);
  stream.select("patJetHelper_patGenJetsCA8CHS.getChargedPt2", jethelperGenCA8_ChargedPt2);
  stream.select("patJetHelper_patGenJetsCA8CHS.getPt2", jethelperGenCA8_Pt2);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.mass", jethelperGenCA8pruned_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.pt", jethelperGenCA8pruned_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.eta", jethelperGenCA8pruned_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.phi", jethelperGenCA8pruned_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.numberOfDaughters", jethelperGenCA8pruned_numberOfDaughters);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_energy", jethelperGenCA8pruned_daughter_0_energy);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_eta", jethelperGenCA8pruned_daughter_0_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_mass", jethelperGenCA8pruned_daughter_0_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_phi", jethelperGenCA8pruned_daughter_0_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_pt", jethelperGenCA8pruned_daughter_0_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_energy", jethelperGenCA8pruned_daughter_1_energy);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_eta", jethelperGenCA8pruned_daughter_1_eta);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_mass", jethelperGenCA8pruned_daughter_1_mass);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_phi", jethelperGenCA8pruned_daughter_1_phi);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_pt", jethelperGenCA8pruned_daughter_1_pt);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau1", jethelperGenCA8pruned_tau1);
  stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau2", jethelperGenCA8pruned_tau2);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.mass", jethelperGenCA8trimmed_mass);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.pt", jethelperGenCA8trimmed_pt);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.eta", jethelperGenCA8trimmed_eta);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.phi", jethelperGenCA8trimmed_phi);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.numberOfDaughters", jethelperGenCA8trimmed_numberOfDaughters);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.genTau1", jethelperGenCA8trimmed_tau1);
  stream.select("patJetHelper_patGenJetsCA8CHStrimmed.genTau2", jethelperGenCA8trimmed_tau2);

  stream.select("patMET_patMETsRaw.et", met2_et);
  stream.select("patMET_patMETsRaw.sumEt", met2_sumEt);
  stream.select("nrecoVertex_offlinePrimaryVertices", nvertex);
  stream.select("nPileupSummaryInfo_addPileupInfo", nPileupSummaryInfo);
  stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", pileupsummaryinfo_getBunchCrossing);
  stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", pileupsummaryinfo_getPU_NumInteractions);
  stream.select("PileupSummaryInfo_addPileupInfo.getTrueNumInteractions", pileupsummaryinfo_getTrueNumInteractions);
  stream.select("sdouble_kt6PFJets_rho.value", sdouble_kt6PFJets_rho_value);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v1", triggerresultshelper_HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v2", triggerresultshelper_HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v3", triggerresultshelper_HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v4", triggerresultshelper_HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v5", triggerresultshelper_HLT_FatDiPFJetMass750_DR1p1_Deta1p5_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT500_v1", triggerresultshelper_HLT_HT500_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT500_v2", triggerresultshelper_HLT_HT500_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT500_v3", triggerresultshelper_HLT_HT500_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT550_v1", triggerresultshelper_HLT_HT550_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT550_v2", triggerresultshelper_HLT_HT550_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT550_v3", triggerresultshelper_HLT_HT550_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT650_v1", triggerresultshelper_HLT_HT650_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT650_v2", triggerresultshelper_HLT_HT650_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT650_v3", triggerresultshelper_HLT_HT650_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT750_v1", triggerresultshelper_HLT_HT750_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT750_v2", triggerresultshelper_HLT_HT750_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_HT750_v3", triggerresultshelper_HLT_HT750_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v1", triggerresultshelper_HLT_PFHT650_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v2", triggerresultshelper_HLT_PFHT650_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v3", triggerresultshelper_HLT_PFHT650_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v4", triggerresultshelper_HLT_PFHT650_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v5", triggerresultshelper_HLT_PFHT650_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v6", triggerresultshelper_HLT_PFHT650_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v7", triggerresultshelper_HLT_PFHT650_v7);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT650_v8", triggerresultshelper_HLT_PFHT650_v8);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v1", triggerresultshelper_HLT_PFHT700_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v2", triggerresultshelper_HLT_PFHT700_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v3", triggerresultshelper_HLT_PFHT700_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v4", triggerresultshelper_HLT_PFHT700_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v5", triggerresultshelper_HLT_PFHT700_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT700_v6", triggerresultshelper_HLT_PFHT700_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v1", triggerresultshelper_HLT_PFHT750_v1);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v2", triggerresultshelper_HLT_PFHT750_v2);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v3", triggerresultshelper_HLT_PFHT750_v3);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v4", triggerresultshelper_HLT_PFHT750_v4);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v5", triggerresultshelper_HLT_PFHT750_v5);
  stream.select("edmTriggerResultsHelper_TriggerResults_HLT.HLT_PFHT750_v6", triggerresultshelper_HLT_PFHT750_v6);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.hcalLaserEventFilterPath", triggerresultshelper_hcalLaserEventFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.noscrapingFilterPath", triggerresultshelper_noscrapingFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.primaryVertexFilterPath", triggerresultshelper_primaryVertexFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.trackingFailureFilterPath", triggerresultshelper_trackingFailureFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.CSCTightHaloFilterPath", triggerresultshelper_CSCTightHaloFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.EcalDeadCellBoundaryEnergyFilterPath", triggerresultshelper_EcalDeadCellBoundaryEnergyFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.EcalDeadCellTriggerPrimitiveFilterPath", triggerresultshelper_EcalDeadCellTriggerPrimitiveFilterPath);
  stream.select("edmTriggerResultsHelper_TriggerResults_PAT.HBHENoiseFilterPath", triggerresultshelper_HBHENoiseFilterPath);
  stream.select("sint_hcallasereventfilter2012.value", triggerresultshelper_hcallasereventfilter2012);

  stream.select("nrecoGenParticleHelper_genParticles", ngenparticlehelper);
  stream.select("recoGenParticleHelper_genParticles.firstDaughter", genparticlehelper_firstDaughter);
  stream.select("recoGenParticleHelper_genParticles.firstMother", genparticlehelper_firstMother);
  stream.select("recoGenParticleHelper_genParticles.lastDaughter", genparticlehelper_lastDaughter);
  stream.select("recoGenParticleHelper_genParticles.lastMother", genparticlehelper_lastMother);
  stream.select("recoGenParticleHelper_genParticles.pdgId", genparticlehelper_pdgId);
  stream.select("recoGenParticleHelper_genParticles.status", genparticlehelper_status);
  stream.select("recoGenParticleHelper_genParticles.charge", genparticlehelper_charge);
  stream.select("recoGenParticleHelper_genParticles.eta", genparticlehelper_eta);
  stream.select("recoGenParticleHelper_genParticles.phi", genparticlehelper_phi);
  stream.select("recoGenParticleHelper_genParticles.pt", genparticlehelper_pt);
  stream.select("recoGenParticleHelper_genParticles.mass", genparticlehelper_mass);

  stream.select("sdouble_vertexWeightSummer12MC53X2012ABCDData.value", vertexWeight);
/*
  stream.select("cmgPFJet_cmgPFJetSel.energy", jethelperCMG_energy);
  stream.select("cmgPFJet_cmgPFJetSel.eta", jethelperCMG_eta);
  stream.select("cmgPFJet_cmgPFJetSel.rapidity", jethelperCMG_rapidity);
  stream.select("cmgPFJet_cmgPFJetSel.mass", jethelperCMG_mass);
  stream.select("cmgPFJet_cmgPFJetSel.phi", jethelperCMG_phi);
  stream.select("cmgPFJet_cmgPFJetSel.pt", jethelperCMG_pt);
*/
  // The root application is needed to make canvases visible during
  // program execution. If this is not needed, just comment out the following
  // line

  TApplication app("analyzer", &argc, argv);

  /*
	 Notes:
	
	 1. Use
	   ofile = outputFile(cmdline.outputfile, stream)
	
	 to skim events to output file in addition to writing out histograms.
	
	 2. Use
	   ofile.addEvent(event-weight)
	
	 to specify that the current event is to be added to the output file.
	 If omitted, the event-weight is defaulted to 1.
	
	 3. Use
	    ofile.count(cut-name, event-weight)
	
	 to keep track, in the count histogram, of the number of events
	 passing a given cut. If omitted, the event-weight is taken to be 1.
	 If you want the counts in the count histogram to appear in a given
	 order, specify the order, before entering the event loop, as in
	 the example below
	 
	    ofile.count("NoCuts", 0)
		ofile.count("GoodEvent", 0)
		ofile.count("Vertex", 0)
		ofile.count("MET", 0)
  */
  
  outputFile ofile(cmdline.outputfilename);

  std::cout << "file open" << std::endl;

  //---------------------------------------------------------------------------
  // Declare histograms
  //---------------------------------------------------------------------------

//  const int NBINS = 104;
//  Double_t BOUNDARIES[NBINS] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
//  354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687,
//  1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
//  4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 
//  10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

  double nJetsCA8;
  double nGenJetsCA8;
  double weight;
  double Jet1MassSubjet;
  double Jet1Sj1AngleResolution;
  double Jet1Sj1PtResolution;
  double Jet1Sj1MassResolution;
  double Jet1MassGenSubjetAngle;
  double Jet1MassGenSubjetPt;
  double Jet1MassGenSubjetMass;
  double Jet1CA8Mass;
  double Jet1CA8MassTrimmed;
  double Jet1CA8MassDrop;
  double Jet1CA8Nsub;
  double Jet1CA8NsubPruned;
  double Jet1CA8NsubTrimmed;
  double Jet1GenCA8Mass;
  double Jet1GenCA8MassTrimmed;
  double Jet1GenCA8MassDrop;
  double Jet1GenCA8Nsub;
  double Jet1GenCA8NsubPruned;
  double Jet1GenCA8NsubTrimmed;
  double Jet1GenCA8NsubPt2;
  double Jet1GenCA8NsubCHS;
  double DijetMassCA8=0;
  double deta=0;
  double GenDijetMassCA8=0;
  double Gendeta=0;
  
  int genWcharge=0;
  int genWhadronic=0;
  int Jet1quarkgluon=0;
  double costheta1=0;
  double costheta2=0;
  double parton_dR_1=0;
  double parton_dR_2=0;
  double Phi=0;
  double costhetastar=0;
  double Phi1=0;

  TTree *dijetWtag = new TTree("dijetWtag", "dijetWtag");
  dijetWtag->Branch("nPU",&pileupsummaryinfo_getPU_NumInteractions[0],"nPU/I");
  dijetWtag->Branch("nJets",&nJetsCA8,"nJets/D");
  dijetWtag->Branch("deta",&deta,"deta/D");
  dijetWtag->Branch("DijetMass",&DijetMassCA8,"DijetMass/D");
  dijetWtag->Branch("Jet1pt",&jethelperCA8_pt[0],"Jet1pt/D");
  dijetWtag->Branch("Jet1eta",&jethelperCA8_eta[0],"Jet1eta/D");
  dijetWtag->Branch("Jet1phi",&jethelperCA8_phi[0],"Jet1phi/D");
  dijetWtag->Branch("Jet1Mass",&Jet1CA8Mass,"Jet1Mass/D");
  dijetWtag->Branch("Jet1PrunedMass",&jethelperCA8_prunedjetmass[0],"Jet1PrunedMass/D");
  dijetWtag->Branch("Jet1CorrectedPrunedMass",&jethelperCA8_correctedprunedjetmass[0],"Jet1CorrectedPrunedMass/D");
  dijetWtag->Branch("Jet1TrackMass",&jethelperCA8_trackjetmass[0],"Jet1TrackMass/D");
  dijetWtag->Branch("Jet1SplitBlockPrunedMass",&jethelperCA8_splitblockprunedjetmass[0],"Jet1SplitBlockPrunedMass/D");
  dijetWtag->Branch("Jet1MassSubjet",&Jet1MassSubjet,"Jet1MassSubjet/D");
  dijetWtag->Branch("Jet1Sj1AngleResolution",&Jet1Sj1AngleResolution,"Jet1Sj1AngleResolution/D");
  dijetWtag->Branch("Jet1Sj1PtResolution",&Jet1Sj1PtResolution,"Jet1Sj1PtResolution/D");
  dijetWtag->Branch("Jet1Sj1MassResolution",&Jet1Sj1MassResolution,"Jet1Sj1MassResolution/D");
  dijetWtag->Branch("Jet1MassGenSubjetAngle",&Jet1MassGenSubjetAngle,"Jet1MassGenSubjetAngle/D");
  dijetWtag->Branch("Jet1MassGenSubjetPt",&Jet1MassGenSubjetPt,"Jet1MassGenSubjetPt/D");
  dijetWtag->Branch("Jet1MassGenSubjetMass",&Jet1MassGenSubjetMass,"Jet1MassGenSubjetMass/D");
  dijetWtag->Branch("Jet1UnGroomedMass",&jethelperCA8_mass[0],"Jet1UnGroomedMass/D");
  dijetWtag->Branch("Jet1MassTrimmed",&Jet1CA8MassTrimmed,"Jet1MassTrimmed/D");
  dijetWtag->Branch("Jet1MassDrop",&Jet1CA8MassDrop,"Jet1MassDrop/D");
  dijetWtag->Branch("Jet1Nsub",&Jet1CA8Nsub,"Jet1Nsub/D");
  dijetWtag->Branch("Jet1NsubPruned",&Jet1CA8NsubPruned,"Jet1NsubPruned/D");
  dijetWtag->Branch("Jet1NsubTrimmed",&Jet1CA8NsubTrimmed,"Jet1NsubTrimmed/D");
  dijetWtag->Branch("Jet1C2beta05",&jethelperCA8_C2beta05[0],"Jet1C2beta05/D");
  dijetWtag->Branch("Jet1C2beta10",&jethelperCA8_C2beta10[0],"Jet1C2beta10/D");
  dijetWtag->Branch("Jet1C2beta15",&jethelperCA8_C2beta15[0],"Jet1C2beta15/D");
  dijetWtag->Branch("Jet1C2beta17",&jethelperCA8_C2beta17[0],"Jet1C2beta17/D");
  dijetWtag->Branch("Jet1C2beta20",&jethelperCA8_C2beta20[0],"Jet1C2beta20/D");
  dijetWtag->Branch("Jet1C2beta25",&jethelperCA8_C2beta25[0],"Jet1C2beta25/D");
  dijetWtag->Branch("Jet1jetCharge03",&jethelperCA8_jetCharge03[0],"Jet1jetCharge03/D");
  dijetWtag->Branch("Jet1jetCharge05",&jethelperCA8_jetCharge05[0],"Jet1jetCharge05/D");
  dijetWtag->Branch("Jet1jetCharge10",&jethelperCA8_jetCharge10[0],"Jet1jetCharge10/D");
  dijetWtag->Branch("Jet1width",&jethelperCA8_width[0],"Jet1width/F");
  dijetWtag->Branch("Jet1area",&jethelperCA8_jetArea[0],"Jet1area/F");
  dijetWtag->Branch("Jet1AK8Mass",&jethelperCA8_ak8mass[0],"Jet1AK8Mass/D");
  dijetWtag->Branch("Jet1nPFblocks",&jethelperCA8_nPFblocks[0],"Jet1nPFblocks/I");
  dijetWtag->Branch("Jet1nECALclusters",&jethelperCA8_nECALclusters[0],"Jet1nECALclusters/I");
  dijetWtag->Branch("Jet1nHCALclusters",&jethelperCA8_nHCALclusters[0],"Jet1nHCALclusters/I");
  dijetWtag->Branch("Jet1nConstituents",&jethelperCA8_nConstituents[0],"Jet1nConstituents/I");
  dijetWtag->Branch("Jet1chargedMultiplicity",&jethelperCA8_chargedMultiplicity[0],"Jet1chargedMultiplicity/I");
  dijetWtag->Branch("Jet1chargedHadronEnergyFraction",&jethelperCA8_chargedHadronEnergyFraction[0],"Jet1chargedHadronEnergyFraction/F");
  dijetWtag->Branch("Jet1neutralHadronEnergyFraction",&jethelperCA8_neutralHadronEnergyFraction[0],"Jet1neutralHadronEnergyFraction/F");
  dijetWtag->Branch("Jet1chargedEmEnergyFraction",&jethelperCA8_chargedEmEnergyFraction[0],"Jet1chargedEmEnergyFraction/F");
  dijetWtag->Branch("Jet1neutralEmEnergyFraction",&jethelperCA8_neutralEmEnergyFraction[0],"Jet1neutralEmEnergyFraction/F");
  dijetWtag->Branch("Jet1Ncharged01",&jethelperCA8_Ncharged01[0],"Jet1Ncharged01/I");
  dijetWtag->Branch("Jet1Nneutral01",&jethelperCA8_Nneutral01[0],"Jet1Nneutral01/I");
  dijetWtag->Branch("Jet1ChargedPt2",&jethelperCA8_ChargedPt2[0],"Jet1ChargedPt2/D");
  dijetWtag->Branch("Jet1Pt2",&jethelperCA8_Pt2[0],"Jet1Pt2/D");

  dijetWtag->Branch("Jet1genWcharge",&genWcharge,"Jet1genWcharge/I");
  dijetWtag->Branch("Jet1genWhadronic",&genWhadronic,"Jet1genWhadronic/I");
  dijetWtag->Branch("Jet1quarkgluon",&Jet1quarkgluon,"Jet1quarkgluon/I");
  dijetWtag->Branch("costheta1",&costheta1,"costheta1/D");
  dijetWtag->Branch("costheta2",&costheta2,"costheta2/D");
  dijetWtag->Branch("parton_dR_1",&parton_dR_1,"parton_dR_1/D");
  dijetWtag->Branch("parton_dR_2",&parton_dR_2,"parton_dR_2/D");
  dijetWtag->Branch("Phi",&Phi,"Phi/D");
  dijetWtag->Branch("costhetastar",&costhetastar,"costhetastar/D");
  dijetWtag->Branch("Phi1",&Phi1,"Phi1/D");

  double GenJet1pt;
  double GenJet1eta;
  double GenJet1phi;
  double GenJet1CaloMass0005;
  double GenJet1CaloMass001;
  double GenJet1CaloMass002;
  double GenJet1CaloMass005;
  double GenJet1CaloMass01;
  double GenJet1CaloMass02;
  double GenJet1CaloMass05;
  double GenJet1CaloMassPF0005;
  double GenJet1CaloMassPF001;
  double GenJet1CaloMassPF002;
  double GenJet1CaloMassPF005;
  double GenJet1CaloMassPF01;
  double GenJet1CaloMassPF02;
  double GenJet1CaloMassPF05;
  double GenJet1CaloMassPFcorrect0005;
  double GenJet1CaloMassPFcorrect001;
  double GenJet1CaloMassPFcorrect002;
  double GenJet1CaloMassPFcorrect005;
  double GenJet1CaloMassPFcorrect01;
  double GenJet1CaloMassPFcorrect02;
  double GenJet1CaloMassPFcorrect05;
  double GenJet1TrackMass;
  double GenJet1UnGroomedMass;
  double GenJet1NsubPUcorrected;
  double GenJet1NsubPUcorrectedCHS;
  int GenJet1NCHS;
  double GenJet1C2beta05;
  double GenJet1C2beta10;
  double GenJet1C2beta15;
  double GenJet1C2beta17;
  double GenJet1C2beta20;
  double GenJet1C2beta25;
  double GenJet1C2beta17CHS;
  double GenJet1jetCharge03;
  double GenJet1jetCharge05;
  double GenJet1jetCharge10;

  float GenJet1width;
  float GenJet1area;
  int GenJet1nConstituents;
  int GenJet1chargedMultiplicity;
  float GenJet1chargedHadronEnergyFraction;
  float GenJet1neutralHadronEnergyFraction;
  float GenJet1chargedEmEnergyFraction;
  float GenJet1neutralEmEnergyFraction;

  int GenJet1Ncharged01;
  int GenJet1Nneutral01;
  double GenJet1ChargedPt2;
  double GenJet1Pt2;


  dijetWtag->Branch("nGenJets",&nGenJetsCA8,"nGenJets/D");
  dijetWtag->Branch("Gendeta",&Gendeta,"Gendeta/D");
  dijetWtag->Branch("GenDijetMass",&GenDijetMassCA8,"GenDijetMass/D");
  dijetWtag->Branch("GenJet1pt",&GenJet1pt,"GenJet1pt/D");
  dijetWtag->Branch("GenJet1eta",&GenJet1eta,"GenJet1eta/D");
  dijetWtag->Branch("GenJet1phi",&GenJet1phi,"GenJet1phi/D");
  dijetWtag->Branch("GenJet1Mass",&Jet1GenCA8Mass,"GenJet1Mass/D");
  dijetWtag->Branch("GenJet1CaloMass0005",&GenJet1CaloMass0005,"GenJet1CaloMass0005/D");
  dijetWtag->Branch("GenJet1CaloMass001",&GenJet1CaloMass001,"GenJet1CaloMass001/D");
  dijetWtag->Branch("GenJet1CaloMass002",&GenJet1CaloMass002,"GenJet1CaloMass002/D");
  dijetWtag->Branch("GenJet1CaloMass005",&GenJet1CaloMass005,"GenJet1CaloMass005/D");
  dijetWtag->Branch("GenJet1CaloMass01",&GenJet1CaloMass01,"GenJet1CaloMass01/D");
  dijetWtag->Branch("GenJet1CaloMass02",&GenJet1CaloMass02,"GenJet1CaloMass02/D");
  dijetWtag->Branch("GenJet1CaloMass05",&GenJet1CaloMass05,"GenJet1CaloMass05/D");
  dijetWtag->Branch("GenJet1CaloMassPF0005",&GenJet1CaloMassPF0005,"GenJet1CaloMassPF0005/D");
  dijetWtag->Branch("GenJet1CaloMassPF001",&GenJet1CaloMassPF001,"GenJet1CaloMassPF001/D");
  dijetWtag->Branch("GenJet1CaloMassPF002",&GenJet1CaloMassPF002,"GenJet1CaloMassPF002/D");
  dijetWtag->Branch("GenJet1CaloMassPF005",&GenJet1CaloMassPF005,"GenJet1CaloMassPF005/D");
  dijetWtag->Branch("GenJet1CaloMassPF01",&GenJet1CaloMassPF01,"GenJet1CaloMassPF01/D");
  dijetWtag->Branch("GenJet1CaloMassPF02",&GenJet1CaloMassPF02,"GenJet1CaloMassPF02/D");
  dijetWtag->Branch("GenJet1CaloMassPF05",&GenJet1CaloMassPF05,"GenJet1CaloMassPF05/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect0005",&GenJet1CaloMassPFcorrect0005,"GenJet1CaloMassPFcorrect0005/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect001",&GenJet1CaloMassPFcorrect001,"GenJet1CaloMassPFcorrect001/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect002",&GenJet1CaloMassPFcorrect002,"GenJet1CaloMassPFcorrect002/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect005",&GenJet1CaloMassPFcorrect005,"GenJet1CaloMassPFcorrect005/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect01",&GenJet1CaloMassPFcorrect01,"GenJet1CaloMassPFcorrect01/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect02",&GenJet1CaloMassPFcorrect02,"GenJet1CaloMassPFcorrect02/D");
  dijetWtag->Branch("GenJet1CaloMassPFcorrect05",&GenJet1CaloMassPFcorrect05,"GenJet1CaloMassPFcorrect05/D");
  dijetWtag->Branch("GenJet1TrackMass",&GenJet1TrackMass,"GenJet1TrackMass/D");
  dijetWtag->Branch("GenJet1UnGroomedMass",&GenJet1UnGroomedMass,"GenJet1UnGroomedMass/D");
  dijetWtag->Branch("GenJet1MassTrimmed",&Jet1GenCA8MassTrimmed,"GenJet1MassTrimmed/D");
  dijetWtag->Branch("GenJet1MassDrop",&Jet1GenCA8MassDrop,"GenJet1MassDrop/D");
  dijetWtag->Branch("GenJet1Nsub",&Jet1GenCA8Nsub,"GenJet1Nsub/D");
  dijetWtag->Branch("GenJet1NsubPruned",&Jet1GenCA8NsubPruned,"GenJet1NsubPruned/D");
  dijetWtag->Branch("GenJet1NsubTrimmed",&Jet1GenCA8NsubTrimmed,"GenJet1NsubTrimmed/D");
  dijetWtag->Branch("GenJet1NsubPt2",&Jet1GenCA8NsubPt2,"GenJet1NsubPt2/D");
  dijetWtag->Branch("GenJet1NsubCHS",&Jet1GenCA8NsubCHS,"GenJet1NsubCHS/D");
  dijetWtag->Branch("GenJet1NsubPUcorrected",&GenJet1NsubPUcorrected,"GenJet1NsubPUcorrected/D");
  dijetWtag->Branch("GenJet1NsubPUcorrectedCHS",&GenJet1NsubPUcorrectedCHS,"GenJet1NsubPUcorrectedCHS/D");
  dijetWtag->Branch("GenJet1NCHS",&GenJet1NCHS,"GenJet1NCHS/I");
  dijetWtag->Branch("GenJet1C2beta05",&GenJet1C2beta05,"GenJet1C2beta05/D");
  dijetWtag->Branch("GenJet1C2beta10",&GenJet1C2beta10,"GenJet1C2beta10/D");
  dijetWtag->Branch("GenJet1C2beta15",&GenJet1C2beta15,"GenJet1C2beta15/D");
  dijetWtag->Branch("GenJet1C2beta17",&GenJet1C2beta17,"GenJet1C2beta17/D");
  dijetWtag->Branch("GenJet1C2beta20",&GenJet1C2beta20,"GenJet1C2beta20/D");
  dijetWtag->Branch("GenJet1C2beta25",&GenJet1C2beta25,"GenJet1C2beta25/D");
  dijetWtag->Branch("GenJet1C2beta17CHS",&GenJet1C2beta17CHS,"GenJet1C2beta17CHS/D");
  dijetWtag->Branch("GenJet1jetCharge03",&GenJet1jetCharge03,"GenJet1jetCharge03/D");
  dijetWtag->Branch("GenJet1jetCharge05",&GenJet1jetCharge05,"GenJet1jetCharge05/D");
  dijetWtag->Branch("GenJet1jetCharge10",&GenJet1jetCharge10,"GenJet1jetCharge10/D");
  
  dijetWtag->Branch("GenJet1width",&GenJet1width,"GenJet1width/F");
  dijetWtag->Branch("GenJet1area",&GenJet1area,"GenJet1area/F");
  dijetWtag->Branch("GenJet1nConstituents",&GenJet1nConstituents,"GenJet1nConstituents/I");
  dijetWtag->Branch("GenJet1chargedMultiplicity",&GenJet1chargedMultiplicity,"GenJet1chargedMultiplicity/I");
  dijetWtag->Branch("GenJet1chargedHadronEnergyFraction",&GenJet1chargedHadronEnergyFraction,"GenJet1chargedHadronEnergyFraction/F");
  dijetWtag->Branch("GenJet1neutralHadronEnergyFraction",&GenJet1neutralHadronEnergyFraction,"GenJet1neutralHadronEnergyFraction/F");
  dijetWtag->Branch("GenJet1chargedEmEnergyFraction",&GenJet1chargedEmEnergyFraction,"GenJet1chargedEmEnergyFraction/F");
  dijetWtag->Branch("GenJet1neutralEmEnergyFraction",&GenJet1neutralEmEnergyFraction,"GenJet1neutralEmEnergyFraction/F");

  dijetWtag->Branch("GenJet1Ncharged01",&GenJet1Ncharged01,"GenJet1Ncharged01/D");
  dijetWtag->Branch("GenJet1Nneutral01",&GenJet1Nneutral01,"GenJet1Nneutral01/D");
  dijetWtag->Branch("GenJet1ChargedPt2",&GenJet1ChargedPt2,"GenJet1ChargedPt2/D");
  dijetWtag->Branch("GenJet1Pt2",&GenJet1Pt2,"GenJet1Pt2/D");
  dijetWtag->Branch("weight",&weight,"weight/D");
  dijetWtag->Branch("vertexWeight",&vertexWeight,"vertexWeight/D");
  dijetWtag->Branch("numberOfPrimaryVertices",&eventhelperextra_numberOfPrimaryVertices,"numberOfPrimaryVertices/I");

  //---------------------------------------------------------------------------
  // Loop over events
  //---------------------------------------------------------------------------

  bool hcallasereventfilter2012active=false;
  bool datafiltersactive=false;

  for(int entry=0; entry < nevents; ++entry)
	{
	  // Read event into memory
	  stream.read(entry);

	  // Uncomment the following line if you wish to copy variables into
	  // structs. See the header file analyzer.h to find out what structs
	  // are available. Each struct contains the field "selected", which
	  // can be set as needed. Call saveSelectedObjects() before a call to
	  // addEvent if you wish to save only the selected objects.
	  
	  // fillObjects();
	  
	  // ---------------------
	  // -- event selection --
	  // ---------------------

          nJetsCA8=0;
	  Jet1CA8Mass=0;
	  Jet1CA8MassDrop=0;
	  Jet1CA8Nsub=0;
	  if(jethelperCA8_pt.size()>=1)
          {
	  for(unsigned n=0;n<jethelperCA8_pt.size();n++)
	     if(jethelperCA8_pt[n]>100)
	         nJetsCA8++;
	  unsigned prunedJetIndex=0;
	  for(unsigned n=0;n<jethelperCA8pruned_pt.size();n++)
	  {
           if (DeltaRfun(jethelperCA8pruned_eta[n],jethelperCA8_eta[0],jethelperCA8pruned_phi[n],jethelperCA8_phi[0])<0.1) {
	      prunedJetIndex=n;
	      break;
	      }
	  } 
	  unsigned trimmedJetIndex=0;
	  for(unsigned n=0;n<jethelperCA8trimmed_pt.size();n++)
	  { 
           if (DeltaRfun(jethelperCA8trimmed_eta[n],jethelperCA8_eta[0],jethelperCA8trimmed_phi[n],jethelperCA8_phi[0])<0.1) {
	      trimmedJetIndex=n;
	      break;
	      }
	  } 
          Jet1CA8Mass = jethelperCA8pruned_mass[prunedJetIndex];
          Jet1CA8MassTrimmed = jethelperCA8trimmed_mass[trimmedJetIndex];
          Jet1CA8MassDrop = max(jethelperCA8pruned_daughter_0_mass[prunedJetIndex],jethelperCA8pruned_daughter_1_mass[prunedJetIndex])/jethelperCA8pruned_mass[prunedJetIndex]/jethelperCA8pruned_uncor_pt[prunedJetIndex]*jethelperCA8pruned_pt[prunedJetIndex];
	  if ((jethelperCA8pruned_daughter_0_mass[prunedJetIndex]<0.0001)||(jethelperCA8pruned_daughter_1_mass[prunedJetIndex]<0.0001)) Jet1CA8MassDrop = 2;

          double Subjet1Dr=1;
          double Subjet1Pt=0;
          double Subjet1Eta=0;
          double Subjet1Phi=0;
          double Subjet1Mass=0;
          double Subjet2Dr=1;
          double Subjet2Pt=0;
          double Subjet2Eta=0;
          double Subjet2Phi=0;
          double Subjet2Mass=0;
	  for(unsigned n=0;n<jethelperGenCA8pruned_daughter_0_pt.size();n++)
	  {
           if (DeltaRfun(jethelperGenCA8pruned_daughter_0_eta[n],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_0_phi[n],jethelperCA8pruned_daughter_0_phi[prunedJetIndex])<Subjet1Dr)
	   {
             Subjet1Dr=DeltaRfun(jethelperGenCA8pruned_daughter_0_eta[n],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_0_phi[n],jethelperCA8pruned_daughter_0_phi[prunedJetIndex]);
             Subjet1Pt=jethelperGenCA8pruned_daughter_0_pt[n];
             Subjet1Eta=jethelperGenCA8pruned_daughter_0_eta[n];
             Subjet1Phi=jethelperGenCA8pruned_daughter_0_phi[n];
             Subjet1Mass=jethelperGenCA8pruned_daughter_0_mass[n];
	   }
           if (DeltaRfun(jethelperGenCA8pruned_daughter_0_eta[n],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_0_phi[n],jethelperCA8pruned_daughter_1_phi[prunedJetIndex])<Subjet2Dr)
	   {
             Subjet2Dr=DeltaRfun(jethelperGenCA8pruned_daughter_0_eta[n],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_0_phi[n],jethelperCA8pruned_daughter_1_phi[prunedJetIndex]);
             Subjet2Pt=jethelperGenCA8pruned_daughter_0_pt[n];
             Subjet2Eta=jethelperGenCA8pruned_daughter_0_eta[n];
             Subjet2Phi=jethelperGenCA8pruned_daughter_0_phi[n];
             Subjet2Mass=jethelperGenCA8pruned_daughter_0_mass[n];
	   }
           if (DeltaRfun(jethelperGenCA8pruned_daughter_1_eta[n],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_1_phi[n],jethelperCA8pruned_daughter_0_phi[prunedJetIndex])<Subjet1Dr)
           {
	     Subjet1Dr=DeltaRfun(jethelperGenCA8pruned_daughter_1_eta[n],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_1_phi[n],jethelperCA8pruned_daughter_0_phi[prunedJetIndex]);
	     Subjet1Pt=jethelperGenCA8pruned_daughter_1_pt[n];
             Subjet1Eta=jethelperGenCA8pruned_daughter_1_eta[n];
             Subjet1Phi=jethelperGenCA8pruned_daughter_1_phi[n];
             Subjet1Mass=jethelperGenCA8pruned_daughter_1_mass[n];
	   }
           if (DeltaRfun(jethelperGenCA8pruned_daughter_1_eta[n],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_1_phi[n],jethelperCA8pruned_daughter_1_phi[prunedJetIndex])<Subjet2Dr)
           {
	     Subjet2Dr=DeltaRfun(jethelperGenCA8pruned_daughter_1_eta[n],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperGenCA8pruned_daughter_1_phi[n],jethelperCA8pruned_daughter_1_phi[prunedJetIndex]);
	     Subjet2Pt=jethelperGenCA8pruned_daughter_1_pt[n];
             Subjet2Eta=jethelperGenCA8pruned_daughter_1_eta[n];
             Subjet2Phi=jethelperGenCA8pruned_daughter_1_phi[n];
             Subjet2Mass=jethelperGenCA8pruned_daughter_1_mass[n];
	   }
          }

          Jet1Sj1AngleResolution=DeltaRfun(Subjet1Eta,jethelperCA8pruned_daughter_0_eta[prunedJetIndex],Subjet1Phi,jethelperCA8pruned_daughter_0_phi[prunedJetIndex]);
          Jet1Sj1PtResolution=jethelperCA8pruned_daughter_0_pt[prunedJetIndex]-Subjet1Pt;
          Jet1Sj1MassResolution=jethelperCA8pruned_daughter_0_mass[prunedJetIndex]-Subjet1Mass;
          TLorentzVector SubJet1;
          TLorentzVector SubJet2;
	  SubJet1.SetPtEtaPhiE(jethelperCA8pruned_daughter_0_pt[prunedJetIndex],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperCA8pruned_daughter_0_phi[prunedJetIndex],jethelperCA8pruned_daughter_0_energy[prunedJetIndex]);
          SubJet2.SetPtEtaPhiE(jethelperCA8pruned_daughter_1_pt[prunedJetIndex],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperCA8pruned_daughter_1_phi[prunedJetIndex],jethelperCA8pruned_daughter_1_energy[prunedJetIndex]);
          Jet1MassSubjet = (SubJet1+SubJet2).M();
	  SubJet1.SetPtEtaPhiM(Subjet1Pt,jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperCA8pruned_daughter_0_phi[prunedJetIndex],Subjet1Mass);
          SubJet2.SetPtEtaPhiM(Subjet2Pt,jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperCA8pruned_daughter_1_phi[prunedJetIndex],Subjet2Mass);
          Jet1MassGenSubjetPt = (SubJet1+SubJet2).M();
	  SubJet1.SetPtEtaPhiE(jethelperCA8pruned_daughter_0_pt[prunedJetIndex],Subjet1Eta,Subjet1Phi,jethelperCA8pruned_daughter_0_energy[prunedJetIndex]);
          SubJet2.SetPtEtaPhiE(jethelperCA8pruned_daughter_1_pt[prunedJetIndex],Subjet2Eta,Subjet2Phi,jethelperCA8pruned_daughter_1_energy[prunedJetIndex]);
          Jet1MassGenSubjetAngle = (SubJet1+SubJet2).M();
SubJet1.SetPtEtaPhiM(jethelperCA8pruned_daughter_0_pt[prunedJetIndex],jethelperCA8pruned_daughter_0_eta[prunedJetIndex],jethelperCA8pruned_daughter_0_phi[prunedJetIndex],Subjet1Mass);
          SubJet2.SetPtEtaPhiM(jethelperCA8pruned_daughter_1_pt[prunedJetIndex],jethelperCA8pruned_daughter_1_eta[prunedJetIndex],jethelperCA8pruned_daughter_1_phi[prunedJetIndex],Subjet2Mass);
          Jet1MassGenSubjetMass = (SubJet1+SubJet2).M();
          Jet1CA8Nsub = jethelperCA8_tau2[0]/jethelperCA8_tau1[0];
          Jet1CA8NsubPruned = jethelperCA8pruned_tau2[prunedJetIndex]/jethelperCA8pruned_tau1[prunedJetIndex];
          Jet1CA8NsubTrimmed = jethelperCA8trimmed_tau2[trimmedJetIndex]/jethelperCA8trimmed_tau1[trimmedJetIndex];
          }           

          nGenJetsCA8=0;
	  Jet1GenCA8Mass=0;
	  Jet1GenCA8MassDrop=0;
	  Jet1GenCA8Nsub=0;
	  Jet1GenCA8NsubPt2=0;
	  Jet1GenCA8NsubCHS=0;
	  if(jethelperGenCA8_pt.size()>=1)
          {
	  for(unsigned n=0;n<jethelperGenCA8_pt.size();n++)
	     if(jethelperGenCA8_pt[n]>100)
	         nGenJetsCA8++;
	  unsigned genJetIndex=0;
	  for(unsigned n=0;n<jethelperGenCA8_pt.size();n++)
	  {
           if (DeltaRfun(jethelperGenCA8_eta[n],jethelperCA8_eta[0],jethelperGenCA8_phi[n],jethelperCA8_phi[0])<0.1) {
	      genJetIndex=n;
	      }
	  } 
	  unsigned prunedJetIndex=0;
	  for(unsigned n=0;n<jethelperGenCA8pruned_pt.size();n++)
	  {
           if (DeltaRfun(jethelperGenCA8pruned_eta[n],jethelperGenCA8_eta[genJetIndex],jethelperGenCA8pruned_phi[n],jethelperGenCA8_phi[genJetIndex])<0.1) {
	      prunedJetIndex=n;
	      }
	  } 
	  unsigned trimmedJetIndex=0;
	  for(unsigned n=0;n<jethelperGenCA8trimmed_pt.size();n++)
	  {
           if (DeltaRfun(jethelperGenCA8trimmed_eta[n],jethelperGenCA8_eta[genJetIndex],jethelperGenCA8trimmed_phi[n],jethelperGenCA8_phi[genJetIndex])<0.2)
	      trimmedJetIndex=n;
	  } 
          Jet1GenCA8Mass = jethelperGenCA8pruned_mass[prunedJetIndex];
          Jet1GenCA8MassTrimmed = jethelperGenCA8trimmed_mass[trimmedJetIndex];
          Jet1GenCA8MassDrop = max(jethelperGenCA8pruned_daughter_0_mass[prunedJetIndex],jethelperGenCA8pruned_daughter_1_mass[prunedJetIndex])/jethelperGenCA8pruned_mass[prunedJetIndex]/jethelperGenCA8pruned_pt[prunedJetIndex]*jethelperGenCA8pruned_pt[prunedJetIndex];
	  if ((jethelperGenCA8pruned_daughter_0_mass[prunedJetIndex]<0.0001)||(jethelperGenCA8pruned_daughter_1_mass[prunedJetIndex]<0.0001)) Jet1GenCA8MassDrop = 2;
          Jet1GenCA8Nsub = jethelperGenCA8_tau2[genJetIndex]/jethelperGenCA8_tau1[genJetIndex];
          Jet1GenCA8NsubPruned = jethelperGenCA8pruned_tau2[prunedJetIndex]/jethelperGenCA8pruned_tau1[prunedJetIndex];
          Jet1GenCA8NsubTrimmed = jethelperGenCA8trimmed_tau2[trimmedJetIndex]/jethelperGenCA8trimmed_tau1[trimmedJetIndex];
          Jet1GenCA8NsubPt2 = jethelperGenCA8_tau2Pt2[genJetIndex]/jethelperGenCA8_tau1Pt2[genJetIndex];
          Jet1GenCA8NsubCHS = jethelperGenCA8_tau2CHS[genJetIndex]/jethelperGenCA8_tau1CHS[genJetIndex];

          GenJet1pt=jethelperGenCA8_pt[genJetIndex];
          GenJet1eta=jethelperGenCA8_eta[genJetIndex];
          GenJet1phi=jethelperGenCA8_phi[genJetIndex];
          GenJet1CaloMass0005=jethelperGenCA8_calojetmass0005[genJetIndex];
          GenJet1CaloMass001=jethelperGenCA8_calojetmass001[genJetIndex];
          GenJet1CaloMass002=jethelperGenCA8_calojetmass002[genJetIndex];
          GenJet1CaloMass005=jethelperGenCA8_calojetmass005[genJetIndex];
          GenJet1CaloMass01=jethelperGenCA8_calojetmass01[genJetIndex];
          GenJet1CaloMass02=jethelperGenCA8_calojetmass02[genJetIndex];
          GenJet1CaloMass05=jethelperGenCA8_calojetmass05[genJetIndex];
          GenJet1CaloMassPF0005=jethelperGenCA8_calojetmassPF0005[genJetIndex];
          GenJet1CaloMassPF001=jethelperGenCA8_calojetmassPF001[genJetIndex];
          GenJet1CaloMassPF002=jethelperGenCA8_calojetmassPF002[genJetIndex];
          GenJet1CaloMassPF005=jethelperGenCA8_calojetmassPF005[genJetIndex];
          GenJet1CaloMassPF01=jethelperGenCA8_calojetmassPF01[genJetIndex];
          GenJet1CaloMassPF02=jethelperGenCA8_calojetmassPF02[genJetIndex];
          GenJet1CaloMassPF05=jethelperGenCA8_calojetmassPF05[genJetIndex];
          GenJet1CaloMassPFcorrect0005=jethelperGenCA8_calojetmassPFcorrect0005[genJetIndex];
          GenJet1CaloMassPFcorrect001=jethelperGenCA8_calojetmassPFcorrect001[genJetIndex];
          GenJet1CaloMassPFcorrect002=jethelperGenCA8_calojetmassPFcorrect002[genJetIndex];
          GenJet1CaloMassPFcorrect005=jethelperGenCA8_calojetmassPFcorrect005[genJetIndex];
          GenJet1CaloMassPFcorrect01=jethelperGenCA8_calojetmassPFcorrect01[genJetIndex];
          GenJet1CaloMassPFcorrect02=jethelperGenCA8_calojetmassPFcorrect02[genJetIndex];
          GenJet1CaloMassPFcorrect05=jethelperGenCA8_calojetmassPFcorrect05[genJetIndex];
          GenJet1TrackMass=jethelperGenCA8_trackjetmass[genJetIndex];
          GenJet1UnGroomedMass=jethelperGenCA8_mass[genJetIndex];
          GenJet1NsubPUcorrected=jethelperGenCA8_tau21PUcorrected[genJetIndex];
          GenJet1NsubPUcorrectedCHS=jethelperGenCA8_tau21PUcorrectedCHS[genJetIndex];
          GenJet1NCHS=jethelperGenCA8_NCHS[genJetIndex];
          GenJet1C2beta05=jethelperGenCA8_C2beta05[genJetIndex];
          GenJet1C2beta10=jethelperGenCA8_C2beta10[genJetIndex];
          GenJet1C2beta15=jethelperGenCA8_C2beta15[genJetIndex];
          GenJet1C2beta17=jethelperGenCA8_C2beta17[genJetIndex];
          GenJet1C2beta20=jethelperGenCA8_C2beta20[genJetIndex];
          GenJet1C2beta25=jethelperGenCA8_C2beta25[genJetIndex];
          GenJet1C2beta17CHS=jethelperGenCA8_C2beta17CHS[genJetIndex];
          GenJet1jetCharge03=jethelperGenCA8_jetCharge03[genJetIndex];
          GenJet1jetCharge05=jethelperGenCA8_jetCharge05[genJetIndex];
          GenJet1jetCharge10=jethelperGenCA8_jetCharge10[genJetIndex];

          GenJet1width=jethelperGenCA8_width[genJetIndex];
          GenJet1area=jethelperGenCA8_jetArea[genJetIndex];
          GenJet1nConstituents=jethelperGenCA8_nConstituents[genJetIndex];
          GenJet1chargedMultiplicity=jethelperGenCA8_chargedMultiplicity[genJetIndex];
          GenJet1chargedHadronEnergyFraction=jethelperGenCA8_chargedHadronEnergyFraction[genJetIndex];
          GenJet1neutralHadronEnergyFraction=jethelperGenCA8_neutralHadronEnergyFraction[genJetIndex];
          GenJet1chargedEmEnergyFraction=jethelperGenCA8_chargedEmEnergyFraction[genJetIndex];
          GenJet1neutralEmEnergyFraction=jethelperGenCA8_neutralEmEnergyFraction[genJetIndex];

          GenJet1Ncharged01=jethelperGenCA8_Ncharged01[genJetIndex];
          GenJet1Nneutral01=jethelperGenCA8_Nneutral01[genJetIndex];
          GenJet1ChargedPt2=jethelperGenCA8_ChargedPt2[genJetIndex];
          GenJet1Pt2=jethelperGenCA8_Pt2[genJetIndex];

	  
	  /*
	  if(jethelperCA8_nConstituents[0]<5)
          for(int i=0;i<ngenparticlehelper;++i)
	  {
	   if (DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2)
	    std::cerr << genparticlehelper_pdgId[i] << "," << genparticlehelper_charge[i] << "," << DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0]) << std::endl;
	      if(i>100) break;
	  }
	  */
	  
	  genWcharge=0;
	  genWhadronic=-1;
	  Jet1quarkgluon=0;
//   std::cerr << ngenparticlehelper << std::endl;
          for(int i=0;i<ngenparticlehelper;++i)
	  {
//if((DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2))
//   std::cerr << genparticlehelper_pdgId[i] << "," << genparticlehelper_charge[i] << "," << DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0]) << std::endl;
//	      if((abs(genparticlehelper_pdgId[i])==24)||(i==854)) {
//   std::cerr << genparticlehelper_pdgId[i] << "," << genparticlehelper_pt[i] << "," << DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0]) << std::endl;
//              }
	      if((abs(genparticlehelper_pdgId[i])==24)&&(genparticlehelper_charge[i]<0)&&(DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2)) {
                  genWcharge=-1;
		  if((genparticlehelper_firstDaughter[i]>=0)&&(genparticlehelper_firstDaughter[i]<ngenparticlehelper)&&(genparticlehelper_pdgId[genparticlehelper_firstDaughter[i]]>=11))
		     genWhadronic=0;
		  if((genWhadronic<0))
		     genWhadronic=1;
		  }
if((abs(genparticlehelper_pdgId[i])==24)&&(genparticlehelper_charge[i]>0)&&(DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2)) {
                  genWcharge=1;
		  if((genparticlehelper_firstDaughter[i]>=0)&&(genparticlehelper_firstDaughter[i]<ngenparticlehelper)&&(genparticlehelper_pdgId[genparticlehelper_firstDaughter[i]]>=11))
		     genWhadronic=0;
		  if((genWhadronic<0))
		     genWhadronic=1;
		  }
if((abs(genparticlehelper_pdgId[i])<=6)&&(genparticlehelper_status[i]==3)&&(DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2))
                  Jet1quarkgluon=1;
if(((abs(genparticlehelper_pdgId[i])==9)||(abs(genparticlehelper_pdgId[i])==21))&&(genparticlehelper_status[i]==3)&&(DeltaRfun(genparticlehelper_eta[i],jethelperCA8_eta[0],genparticlehelper_phi[i],jethelperCA8_phi[0])<0.2))
                  Jet1quarkgluon=2;
	      if((genWcharge!=0)||(Jet1quarkgluon!=0)) break;
          }

          TLorentzVector H,W1,W2,j11,j12,j21,j22;
          for(int i=0;i<ngenparticlehelper;++i)
	  {    
	      if((abs(genparticlehelper_pdgId[i])>=23)&&(abs(genparticlehelper_pdgId[i])<=25)&&(genparticlehelper_charge[i]<0)&&
(genparticlehelper_firstDaughter[i]>=0)&&(genparticlehelper_lastDaughter[i]>=0)&&(genparticlehelper_firstDaughter[i]<ngenparticlehelper)&&(genparticlehelper_lastDaughter[i]<ngenparticlehelper)&&(abs(genparticlehelper_pdgId[genparticlehelper_firstDaughter[i]])<23)&&(abs(genparticlehelper_pdgId[genparticlehelper_lastDaughter[i]]<23)))
	      {
                  W1.SetPtEtaPhiM(genparticlehelper_pt[i],genparticlehelper_eta[i],genparticlehelper_phi[i],genparticlehelper_mass[i]);
                   j11.SetPtEtaPhiM(genparticlehelper_pt[genparticlehelper_firstDaughter[i]],genparticlehelper_eta[genparticlehelper_firstDaughter[i]],genparticlehelper_phi[genparticlehelper_firstDaughter[i]],genparticlehelper_mass[genparticlehelper_firstDaughter[i]]);
                   j12.SetPtEtaPhiM(genparticlehelper_pt[genparticlehelper_lastDaughter[i]],genparticlehelper_eta[genparticlehelper_lastDaughter[i]],genparticlehelper_phi[genparticlehelper_lastDaughter[i]],genparticlehelper_mass[genparticlehelper_lastDaughter[i]]);
              }
	      else if((abs(genparticlehelper_pdgId[i])>=23)&&(abs(genparticlehelper_pdgId[i])<=25)&&(genparticlehelper_charge[i]>0)&&
(genparticlehelper_firstDaughter[i]>=0)&&(genparticlehelper_lastDaughter[i]>=0)&&(genparticlehelper_firstDaughter[i]<ngenparticlehelper)&&(genparticlehelper_lastDaughter[i]<ngenparticlehelper)&&(abs(genparticlehelper_pdgId[genparticlehelper_firstDaughter[i]])<23)&&(abs(genparticlehelper_pdgId[genparticlehelper_lastDaughter[i]]<23)))
              {
	          W2.SetPtEtaPhiM(genparticlehelper_pt[i],genparticlehelper_eta[i],genparticlehelper_phi[i],genparticlehelper_mass[i]);
                   j21.SetPtEtaPhiM(genparticlehelper_pt[genparticlehelper_firstDaughter[i]],genparticlehelper_eta[genparticlehelper_firstDaughter[i]],genparticlehelper_phi[genparticlehelper_firstDaughter[i]],genparticlehelper_mass[genparticlehelper_firstDaughter[i]]);
                   j22.SetPtEtaPhiM(genparticlehelper_pt[genparticlehelper_lastDaughter[i]],genparticlehelper_eta[genparticlehelper_lastDaughter[i]],genparticlehelper_phi[genparticlehelper_lastDaughter[i]],genparticlehelper_mass[genparticlehelper_lastDaughter[i]]);
              }
	      if((W1.Pt()>0)&&(W2.Pt()>0)) break;
	      //if((W1.Pt()==0)&&(W2.Pt()==0)&&(i>100)) break;
          }

          H=W1+W2;
	  //std::cerr << H.Pt() << "," << W1.Pt() <<  "," << W2.Pt() <<  "," << j11.Pt() <<  "," << j12.Pt() <<  "," << j21.Pt() <<  "," << j22.Pt() <<  std::endl;
	  if(H.Pt()>0){
             computeAngles(H, W1, j11, j12, W2, j21, j22, costheta1, costheta2, Phi, costhetastar, Phi1);
             parton_dR_1 = DeltaRfun(j11.Eta(),j12.Eta(),j11.Phi(),j12.Phi());
             parton_dR_2 = DeltaRfun(j21.Eta(),j22.Eta(),j21.Phi(),j22.Phi());
             if (DeltaRfun(W2.Eta(),jethelperGenCA8_eta[genJetIndex],W2.Phi(),jethelperGenCA8_phi[genJetIndex])<0.2)
	     {
	        double tmp=parton_dR_2;
		parton_dR_2=parton_dR_1;
		parton_dR_1=tmp;
	        tmp=costheta2;
		costheta2=costheta1;
		costheta1=tmp;
	     }
          }

          }

          if (triggerresultshelper_hcallasereventfilter2012!=0)
	     hcallasereventfilter2012active=true;

	  if((triggerresultshelper_primaryVertexFilterPath!=0)&&
	     (triggerresultshelper_noscrapingFilterPath!=0)&&
	     (triggerresultshelper_trackingFailureFilterPath!=0)&&
	     (triggerresultshelper_hcalLaserEventFilterPath!=0)&&
	     (triggerresultshelper_HBHENoiseFilterPath!=0)&&
	     (triggerresultshelper_CSCTightHaloFilterPath!=0)&&
	     (triggerresultshelper_EcalDeadCellTriggerPrimitiveFilterPath!=0))
	     datafiltersactive=true;

          DijetMassCA8=0;
	  deta=0;
          if(jethelperCA8_pt.size()>=2)
	  {
              TLorentzVector Jet1;
              TLorentzVector Jet2;
              Jet1.SetPtEtaPhiE(jethelperCA8_pt[0],jethelperCA8_eta[0],jethelperCA8_phi[0],jethelperCA8_energy[0]);
              Jet2.SetPtEtaPhiE(jethelperCA8_pt[1],jethelperCA8_eta[1],jethelperCA8_phi[1],jethelperCA8_energy[1]);
              DijetMassCA8 = (Jet1+Jet2).M();
              deta = fabs(jethelperCA8_eta[0]-jethelperCA8_eta[1]);
          }
          GenDijetMassCA8=0;
	  Gendeta=0;
          if(jethelperGenCA8_pt.size()>=2)
	  {
              TLorentzVector Jet1;
              TLorentzVector Jet2;
              Jet1.SetPtEtaPhiE(jethelperGenCA8_pt[0],jethelperGenCA8_eta[0],jethelperGenCA8_phi[0],jethelperGenCA8_energy[0]);
              Jet2.SetPtEtaPhiE(jethelperGenCA8_pt[1],jethelperGenCA8_eta[1],jethelperGenCA8_phi[1],jethelperGenCA8_energy[1]);
              GenDijetMassCA8 = (Jet1+Jet2).M();
              Gendeta = fabs(jethelperGenCA8_eta[0]-jethelperGenCA8_eta[1]);
          }

	  if(!((((jethelperCA8_pt.size()>=2)&&(jethelperCA8_pt[0]>30)&&(fabs(jethelperCA8_eta[0])<2.5))||
	        ((jethelperGenCA8_pt.size()>=2)&&(jethelperGenCA8_pt[0]>30)&&(fabs(jethelperGenCA8_eta[0])<2.5)))&&
	     
	   (((jethelperCA8_muonEnergyFraction[0]<0.80)&&
	     //(jethelper_neutralHadronEnergyFraction[0]<0.99)&&
	     (jethelperCA8_neutralHadronEnergyFraction[0]<0.90)&&
	     //(jethelper_neutralEmEnergyFraction[0]<0.99)&&
	     (jethelperCA8_neutralEmEnergyFraction[0]<0.90)&&
	     (jethelperCA8_nConstituents[0]>1)&&
	     ((fabs(jethelperCA8_eta[0])>2.4)||
	      ((jethelperCA8_chargedHadronEnergyFraction[0]>0.01)&&
	       (jethelperCA8_chargedMultiplicity[0]>0)&&
	       (jethelperCA8_chargedEmEnergyFraction[0]<0.99)))&&
	     (((sdouble_kt6PFJets_rho_value<40)&&
	       (triggerresultshelper_primaryVertexFilterPath!=0)&&
	       (triggerresultshelper_noscrapingFilterPath!=0)&&
	       (triggerresultshelper_trackingFailureFilterPath!=0)&&
	       (triggerresultshelper_hcalLaserEventFilterPath!=0)&&
	       (triggerresultshelper_HBHENoiseFilterPath!=0)&&
	       (triggerresultshelper_CSCTightHaloFilterPath!=0)&&
	       (triggerresultshelper_EcalDeadCellTriggerPrimitiveFilterPath!=0))||
	      (datafiltersactive==false))&&
	     ((triggerresultshelper_hcallasereventfilter2012!=0)||(hcallasereventfilter2012active==false))
	     )||((jethelperGenCA8_pt.size()>=1)))
	    )) continue;

	  // ---------------------
	  // -- fill histograms --
	  // ---------------------	  

          /*if((jethelperCA8pruned_mass[0]>40)&&(jethelperCA8pruned_mass[0]<60)&&
	  (jethelperGenCA8pruned_mass[0]>70)&&(jethelperGenCA8pruned_mass[0]<100)&&
	  (abs(jethelperCA8_eta[0])<2.4)&&(deta<1.3)&&(DijetMassCA8>890)&&(jethelperCA8_pt[0]>1100)&&(jethelperCA8_pt[0]<1400))
             std::cout << eventhelper_run << ":" << eventhelper_luminosityBlock << ":" << eventhelper_event << "," << jethelperCA8_pt[0]  << "," << (fabs(jethelperCA8_eta[0])) << "," << jethelperCA8pruned_mass[0] << std::endl;
          */
          if(geneventinfoproduct_weight>0)
	      weight=geneventinfoproduct_weight;
	  else
	      weight=1;
          if(vertexWeight==0)
	      vertexWeight=1;

          dijetWtag->Fill();

	}

  stream.close();
  ofile.close();

  return 0;
}
