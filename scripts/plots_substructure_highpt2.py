import os, sys
import array
from ROOT import * 
from os import path

#gROOT.Reset()
#gROOT.SetStyle("Plain")
gROOT.ProcessLine('.L tdrstyle.C')
gStyle.SetOptStat(0)
gStyle.SetOptFit(0)
gStyle.SetTitleOffset(1.3,"Y")
gStyle.SetPadLeftMargin(0.15)
gStyle.SetPadBottomMargin(0.15)
gStyle.SetPadTopMargin(0.08)
gStyle.SetPadRightMargin(0.08)
gStyle.SetMarkerSize(0.5)
gStyle.SetHistLineWidth(1)
#gStyle.SetStatFontSize(0.020	
gStyle.SetTitleSize(0.06, "XYZ")
gStyle.SetLabelSize(0.05, "XYZ")
gStyle.SetNdivisions(506, "XYZ")
gStyle.SetLegendBorderSize(0)

TGaxis.SetMaxDigits(3)

if __name__ == '__main__':

  for resolution in [False,True]:
   for runSet in [30,31,32,33,34,35,36]: #28,29
     
     if runSet==28:
      samples = ["substructure_pas_WW2000_posHCAL_PU.root",
 		 "substructure_pas_WW3000_posHCAL_PU.root",
 		 "substructure_pas_WW4000_posHCAL_PU.root",
 		 "substructure_pas_qW5000_posHCAL_PU.root",
 		 "substructure_pas_qW7000_posHCAL_PU.root",
 		 "substructure_pas_QCD1000_posHCAL_PU.root",
 		 "substructure_pas_QCD1800_posHCAL_PU.root",
 		 ]
      names = ["pt",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents"
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
 	       ]
      colors=[2,4,6,9,1,8,15,1,1]
      styles=[1,2,3,4,5,1,3,4,5]
      widths=[2,1,2,1,3,2,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==29:
      samples = ["substructure_pas_WW2000_posHCAL.root",
 		 "substructure_pas_WW3000_posHCAL.root",
 		 "substructure_pas_WW4000_posHCAL.root",
 		 "substructure_pas_qW5000_posHCAL.root",
 		 "substructure_pas_qW7000_posHCAL.root",
 		 "substructure_pas_QCD1000_posHCAL.root",
 		 "substructure_pas_QCD1800_posHCAL.root",
 		 ]
      names = ["pt",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents"
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
 	       ]
      colors=[2,4,6,9,1,8,15,1,1]
      styles=[1,2,3,4,5,1,3,4,5]
      widths=[2,1,2,1,3,2,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==30:
      samples = [#"substructure_pas_WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 "substructure_pas_WW1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 #"substructure_pas_WW3000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 "substructure_pas_WW3000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 #"substructure_pas_qW5000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 "substructure_pas_qW7000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 "substructure_pas_QCD1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 "substructure_pas_QCD1800_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)<2.4))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)<2.4))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)<2.4))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)<2.4))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet hadron energy fraction", ),
 	       ]
      colors=[4,6,1,2,1,1]
      styles=[1,2,3,1,4,5]
      widths=[2,2,2,1,2,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==31:
      samples = ["substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "width",
	       "area",
	       "nPFblocks",
	       "nECALclusters",
	       "nHCALclusters",
	       "ak8mass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)<2.4))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)<2.4))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1width","((abs(Jet1eta)<2.4))","jet width", ),
           ("Jet1area","((abs(Jet1eta)<2.4))","jet area", ),
           ("Jet1nPFblocks","((abs(Jet1eta)<2.4))","jet PF blocks", ),
           ("Jet1nECALclusters","((abs(Jet1eta)<2.4))","jet ECAL clusters", ),
           ("Jet1nHCALclusters","((abs(Jet1eta)<2.4))","jet HCAL clusters", ),
           ("Jet1AK8Mass","((abs(Jet1eta)<2.4))","AK8 jet mass (GeV)"),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)<2.4))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)<2.4))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,6,6,1,1]
      if resolution:
        styles=[1,1,2,2,3,3]
      else:
        styles=[2,1,2,1,2,1]
      widths=[1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==32:
      samples = ["substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<1.0))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)<1.0))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)<1.0))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<1.0))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<1.0))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<1.0)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<1.0))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<1.0))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<1.0)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)<1.0))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)<1.0))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)<1.0))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<1.0))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)<1.0))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)<1.0))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)<1.0))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<1.0))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,1,1,6,6,2,2,7,7,8,8,4,4,1,1,2,2]
      styles=[2,1,2,1,2,1,2,1,2,1,2,1,3,4,3,4,3,4]
      widths=[1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==33:
      samples = ["substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)>1.0)&&(abs(Jet1eta)<1.5))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,1,1,6,6,2,2,7,7,8,8,4,4,1,1,2,2]
      styles=[2,1,2,1,2,1,2,1,2,1,2,1,3,4,3,4,3,4]
      widths=[1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==34:
      samples = ["substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1nConstituents","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)>1.5)&&(abs(Jet1eta)<2.4))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,1,1,6,6,2,2,7,7,8,8,4,4,1,1,2,2]
      styles=[2,1,2,1,2,1,2,1,2,1,2,1,3,4,3,4,3,4]
      widths=[1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==35:
      samples = ["substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW2000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW3000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW5000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_qW7000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD170_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "width",
	       "area",
	       "nPFblocks",
	       "nECALclusters",
	       "nHCALclusters",
	       "ak8mass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)<2.4))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)<2.4))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1width","((abs(Jet1eta)<2.4))","jet width", ),
           ("Jet1area","((abs(Jet1eta)<2.4))","jet area", ),
           ("Jet1nPFblocks","((abs(Jet1eta)<2.4))","jet PF blocks", ),
           ("Jet1nECALclusters","((abs(Jet1eta)<2.4))","jet ECAL clusters", ),
           ("Jet1nHCALclusters","((abs(Jet1eta)<2.4))","jet HCAL clusters", ),
           ("Jet1AK8Mass","((abs(Jet1eta)<2.4))","AK8 jet mass (GeV)"),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)<2.4))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)<2.4))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,1,1,6,6,2,2,7,7,8,8,4,4,1,1,2,2]
      styles=[2,1,2,1,2,1,2,1,2,1,2,1,3,4,3,4,3,4]
      widths=[1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     if runSet==36:
      samples = ["substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_WW4000_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 "substructure_pas_QCD1800_posHCAL_fixTRACK_splitPFecal.root",
 		 #"substructure_pas_WW4000_posHCAL_fixTRACK.root",
 		 #"substructure_pas_QCD1800_posHCAL_fixTRACK.root",
 		 ]
      names = ["pt",
 	       "eta",
 	       "phi",
 	       "ungroomedmass",
 	       "ungroomedmass_nConstituents30",
 	       "ungroomedmass_chf09",
 	       "mass",
 	       "mass_dr01",
               "trimmedmass",
               "trackmass",
               "tau21",
               "tau21_aftermass",
	       "width",
	       "area",
	       "nPFblocks",
	       "nECALclusters",
	       "nHCALclusters",
	       "ak8mass",
	       "nconstituents",
	       "chargedMultiplicity",
	       "chargedHadronEnergyFraction",
	       "neutralHadronEnergyFraction",
	       "chargedEmEnergyFraction",
	       "neutralEmEnergyFraction",
	       "chargedEnergyFraction",
	       "hadronEnergyFraction",
 	       ]
      plots = [("Jet1pt","((abs(Jet1eta)<2.4))","jet p_{T} (GeV)"),
 	       ("Jet1eta","((abs(Jet1eta)<2.4))","jet #eta"),
 	       ("Jet1phi","((abs(Jet1eta)<2.4))","jet #phi"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4))","jet mass (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4)&&(Jet1nConstituents>30))","jet mass (GeV)"),
 	       ("Jet1UnGroomedMass","((abs(Jet1eta)<2.4)&&(Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction<0.9))","jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4))","pruned jet mass (GeV)"),
 	       ("Jet1Mass","((abs(Jet1eta)<2.4)&&(abs(parton_dR_1)<0.14))","pruned jet mass (GeV)"),
           ("Jet1MassTrimmed","((abs(Jet1eta)<2.4))","trimmed jet mass (GeV)"),
           ("Jet1TrackMass","((abs(Jet1eta)<2.4))","charged jet mass (GeV)"),
           ("Jet1Nsub","((abs(Jet1eta)<2.4))","#tau_{2}/#tau_{1}", ),
           ("Jet1Nsub","((abs(Jet1eta)<2.4)&&(Jet1Mass>60)&&(Jet1Mass<100))","#tau_{2}/#tau_{1}", ),
           ("Jet1width","((abs(Jet1eta)<2.4))","jet width", ),
           ("Jet1area","((abs(Jet1eta)<2.4))","jet area", ),
           ("Jet1nPFblocks","((abs(Jet1eta)<2.4))","jet PF blocks", ),
           ("Jet1nECALclusters","((abs(Jet1eta)<2.4))","jet ECAL clusters", ),
           ("Jet1nHCALclusters","((abs(Jet1eta)<2.4))","jet HCAL clusters", ),
           ("Jet1AK8Mass","((abs(Jet1eta)<2.4))","AK8 jet mass (GeV)"),
           ("Jet1nConstituents","((abs(Jet1eta)<2.4))","jet constituents", ),
           ("Jet1chargedMultiplicity","((abs(Jet1eta)<2.4))","jet charged constituents", ),
           ("Jet1chargedHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet CHF", ),
           ("Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet NHF", ),
           ("Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet CEF", ),
           ("Jet1neutralEmEnergyFraction","((abs(Jet1eta)<2.4))","jet NEF", ),
           ("Jet1chargedHadronEnergyFraction+Jet1chargedEmEnergyFraction","((abs(Jet1eta)<2.4))","jet charged energy fraction", ),
           ("Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction","((abs(Jet1eta)<2.4))","jet hadron energy fraction", ),
 	       ]
      colors=[4,4,1,1,6,2,2,2,7,8,8,4,4,1,1,2,2]
      styles=[2,1,2,1,1,1,2,1,1,1,1,3,4,3,4,3,4]
      widths=[1,2,1,2,2,2,1,2,2,2,2,1,2,1,2,1,2]
      #colors=[4,4,2,2,6,6]
      #styles=[2,1,2,1,2,1]
      #widths=[2,1,2,1,2,1]
      sets=[""]

     results=[]
     means=[]
     means_err=[]
     rms=[]
     rms_err=[]
     fits=[]
     for plot in plots:
      print plot
      print names[plots.index(plot)]
      canvas = TCanvas("","",0,0,200,200)
      canvas.SetLogy(False)
      legend=TLegend(0.4,0.6,0.85,0.9)
      dataPlotted=False
      counter=0
      colorcounter=-1
      integral=1
      originalIntegral={}
      maximum=0
      s=0
      hists=[]
      files=[]
      firsthist=None
      for sample in samples:
       s+=1
       for gen in sets:
        colorcounter+=1
 	if (names[plots.index(plot)]=="pt" or names[plots.index(plot)]=="eta" or names[plots.index(plot)]=="npu" or names[plots.index(plot)]=="npv" or "costheta" in names[plots.index(plot)] or "Phi" in names[plots.index(plot)] or "dR" in names[plots.index(plot)]) and gen=="Gen":
 	   continue
 	if names[plots.index(plot)]=="npu" and s==2:
 	   continue
 	if (names[plots.index(plot)]=="pt" or names[plots.index(plot)]=="eta") and gen=="lowPU":
 	   continue
 	if (runSet==2 or runSet==3) and gen!="" and s==2:
 	   continue
	if runSet==30 and ("raction" in names[plots.index(plot)] or "ultiplicity" in names[plots.index(plot)] or "onstituents" in names[plots.index(plot)]) and s>=4:
	   continue
 	print sample, gen

 	f=TFile.Open(sample)
	files+=[f]
 	tree=f.Get("dijetWtag")

 	signal = "Hpp" in sample or "Py6" in sample
 	histname="plot"+names[plots.index(plot)]+gen+str(s)
 	if "sj angular resolution" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,0.2);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "sj p_{T} resolution (GeV)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-1000,1000);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "sj mass resolution (GeV)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-50,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "cos #theta" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "#Phi" in plot[2]:
 	   hist=TH1F(histname,histname,25,-3.15,3.15);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "#Delta R" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,3);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="pileup interactions":
 	   hist=TH1F(histname,histname,25,0,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="number of vertices":
 	   hist=TH1F(histname,histname,25,0,50);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet width":
 	   hist=TH1F(histname,histname,25,0,0.5);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet area":
 	   hist=TH1F(histname,histname,25,0,5);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet #eta":
 	   hist=TH1F(histname,histname,25,-2.4,2.4);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet #phi":
 	   hist=TH1F(histname,histname,25,-3.15,3.15);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "C_{2}" in plot[2]:
 	   hist=TH1F(histname,histname,25,0,0.8);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "jet charge (#kappa=0.3)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-4,4);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-4,4)
 	if "jet charge (#kappa=0.5)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-2,2);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-2,2)
 	if "jet charge (#kappa=1.0)" in plot[2]:
 	   hist=TH1F(histname,histname,25,-1,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   hist.GetXaxis().SetRangeUser(-1,1)
 	if plot[2]=="jet charged constituents" and not "71" in sample:
 	   hist=TH1F(histname,histname,20,0,60);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	elif plot[2]=="jet constituents" or plot[2]=="jet charged constituents":
 	   hist=TH1F(histname,histname,25,0,200);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet ECAL clusters" or plot[2]=="jet HCAL clusters" or plot[2]=="jet PF blocks":
 	   hist=TH1F(histname,histname,100,0,100);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="jet CHF" or plot[2]=="jet NHF" or plot[2]=="jet CEF" or plot[2]=="jet NEF" or plot[2]=="jet charged energy fraction" or plot[2]=="jet hadron energy fraction":
 	   hist=TH1F(histname,histname,25,0,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="charged particles (p_{T}^{rel}>0.1)":
 	   hist=TH1F(histname,histname,25,0,25);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="neutral particles (p_{T}^{rel}>0.1)":
 	   hist=TH1F(histname,histname,25,0,25);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="3rd charged particle p_{T}":
 	   hist=TH1F(histname,histname,25,0,250);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="3rd particle p_{T}":
 	   hist=TH1F(histname,histname,25,0,250);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if "jet p_{T}" in plot[2] and not resolution:
 	   hist=TH1F(histname,histname,40,0,4000);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	   canvas.SetLogy(True)
 	if "jet p_{T}" in plot[2] and resolution:
 	   hist=TH1F(histname,histname,40,0,4000);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	if "particle 1 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "particle 2 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "particle 3 p_{T}" in plot[2]:
 	   hist=TH1F(histname,histname,40,0,500);
 	   hist.GetYaxis().SetRangeUser(0.001,50000)
 	   #canvas.SetLogy(True)
 	if "pruned jet mass" in plot[2] or "trimmed jet mass" in plot[2] or "charged jet mass" in plot[2]:
 	   hist=TH1F(histname,histname,50,0,150);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]== "jet mass (GeV)" or plot[2]== "AK8 jet mass (GeV)":
 	   hist=TH1F(histname,histname,50,0,300);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	if plot[2]=="mass drop":
 	   hist=TH1F(histname,histname,20,0,1);
 	   hist.GetYaxis().SetRangeUser(0,60000)
 	   if "aftermass" in names[plots.index(plot)]:
 	       hist.GetYaxis().SetRangeUser(0,6000)
 	if "#tau_{2}/#tau_{1}" in plot[2]:
 	   hist=TH1F(histname,histname,20,0,1);
 	   hist.GetYaxis().SetRangeUser(0,75000)
 	   if "aftermass" in names[plots.index(plot)]:
 	       hist.GetYaxis().SetRangeUser(0,5000)

 	if gen=="lowPU":
 	    variable,cutstring=plot[0],plot[1]+"&&(nPU<17)"
 	elif gen=="Subjet":
 	    variable,cutstring="Jet1MassSubjet",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Angle":
 	    variable,cutstring="Jet1MassGenSubjetAngle",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Pt":
 	    variable,cutstring="Jet1MassGenSubjetPt",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="Mass":
 	    variable,cutstring="Jet1MassGenSubjetMass",plot[1].replace("&&(Jet1pt>1100)&&(Jet1pt<1700)","")
 	elif gen=="CHF1":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF<0.4)"
 	elif gen=="CHF2":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.4)&&(Jet1CHF<0.6)"
 	elif gen=="CHF3":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.6)&&(Jet1CHF<0.8)"
 	elif gen=="CHF4":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1CHF>0.8)"
 	elif gen=="MassWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1Mass>40)&&(Jet1Mass<60)"
 	elif gen=="PtWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(Jet1pt>1500)"
 	elif gen=="barrel":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)<1.0)"
 	elif gen=="endcap":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)>1.0)"
 	elif gen=="EtaWindow":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(Jet1eta)<0.5)"
 	elif gen=="Dr01":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.01)&&(abs(parton_dR_1)<0.14)"
 	elif gen=="Dr05":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.14)&&(abs(parton_dR_1)<0.28)"
 	elif gen=="Dr10":
 	    variable,cutstring=plot[0],plot[1]+"&&(abs(parton_dR_1)>0.28)&&(abs(parton_dR_1)<1.0)"
 	elif "TrackMass" in gen or "CaloMass" in gen or "PrunedMass" in gen or "UnGroomedMass" in gen:
 	    variable,cutstring=gen,plot[1].replace("Jet","GenJet").replace("DijetMass","GenDijetMass").replace("deta","Gendeta")
 	elif gen=="Gen" or (runSet>=31 and (s==1 or s==3 or s==5 or s==7 or s==9 or s==11 or s==13 or s==15 or s==17 or s==19 or s==21) and (runSet!=36 or s<=4)):
 	    variable,cutstring="Gen"+plot[0],plot[1].replace("Jet","GenJet").replace("DijetMass","GenDijetMass").replace("deta","Gendeta")
	    if resolution: continue
 	else:
 	    variable,cutstring=gen+plot[0],plot[1]
 	
 	if "WW" in sample or "qW" in sample:
 	  cutstring+="&&(Jet1genWhadronic==1)"
 	
	if runSet==30 and s==4:
	  cutstring+="&&(Jet1pt>800)&&(Jet1pt<1200)"
	if runSet==30 and s==5:
	  cutstring+="&&(Jet1pt>1600)&&(Jet1pt<2400)"
	
	if resolution and variable=="Jet1PrunedMass":
	    #if "WW" in sample:
	    #    variable="(Jet1PrunedMass-GenJet1Mass)"
 	    #else:
	        variable="(Jet1PrunedMass-GenJet1Mass)/GenJet1Mass"
 	if resolution and variable=="Jet1UnGroomedMass":
	    #if "WW" in sample:
                variable="(Jet1UnGroomedMass-GenJet1UnGroomedMass)"
 	    #else:
 	    #    variable="(Jet1UnGroomedMass-GenJet1UnGroomedMass)/GenJet1UnGroomedMass"
 	if resolution and variable=="Jet1TrimmedMass":
	    #if "WW" in sample:
            #    variable="(Jet1TrimmedMass-GenJet1TrimmedMass)"
 	    #else:
 	        variable="(Jet1TrimmedMass-GenJet1TrimmedMass)/GenJet1TrimmedMass"
 	if resolution and variable=="Jet1TrackMass":
	    #if "WW" in sample:
            #    variable="(Jet1TrackMass-GenJet1TrackMass)"
 	    #else:
 	        variable="(Jet1TrackMass-GenJet1TrackMass)/GenJet1TrackMass"
 	if resolution and variable=="Jet1Mass":
	    #if "WW" in sample:
 	    #    variable="(Jet1Mass-GenJet1Mass)"
 	    #else:
 	        variable="(Jet1Mass-GenJet1Mass)/GenJet1Mass"
 	if resolution and variable=="Jet1pt":
 	    variable="(Jet1pt-GenJet1pt)/GenJet1pt"
 	if resolution and variable=="Jet1eta":
 	    variable="(Jet1eta-GenJet1eta)"
 	if resolution and variable=="Jet1phi":
 	    variable="(Jet1phi-GenJet1phi)"
 	if resolution and variable=="Jet1Nsub":
 	    variable="(Jet1Nsub-GenJet1Nsub)"
 	if resolution and variable=="Jet1width":
 	    variable="(Jet1nConstituents-GenJet1width)/GenJet1width"
 	if resolution and variable=="Jet1nConstituents":
 	    variable="(Jet1nConstituents-GenJet1nConstituents)/GenJet1nConstituents"
 	if resolution and variable=="Jet1chargedMultiplicity":
 	    variable="(Jet1chargedMultiplicity-GenJet1chargedMultiplicity)/GenJet1chargedMultiplicity"
 	if resolution and variable=="Jet1chargedHadronEnergyFraction":
 	    variable="(Jet1chargedHadronEnergyFraction-GenJet1chargedHadronEnergyFraction)/GenJet1chargedHadronEnergyFraction"
 	if resolution and variable=="Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction":
 	    variable="(Jet1chargedHadronEnergyFraction+Jet1neutralHadronEnergyFraction-GenJet1chargedHadronEnergyFraction-GenJet1neutralHadronEnergyFraction)/(GenJet1chargedHadronEnergyFraction+GenJet1neutralHadronEnergyFraction)"

 	if "Mass" in variable:
 	   hist.Rebin(2)
 	
 	if resolution and "/" in variable and (variable=="(Jet1chargedMultiplicity-GenJet1chargedMultiplicity)/GenJet1chargedMultiplicity" or variable=="(Jet1nConstituents-GenJet1nConstituents)/GenJet1nConstituents"):
           hist=TH1F(histname,histname,10,-1,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	elif resolution and "/" in variable:
           hist=TH1F(histname,histname,40,-1,1);
 	   hist.GetYaxis().SetRangeUser(0,50000)
 	elif resolution and not "/" in variable:
           hist=TH1F(histname,histname,50,-100,100);
 	   hist.GetYaxis().SetRangeUser(0,50000)

 	print histname,variable,cutstring
 	tree.Project(histname,variable,cutstring)
 	if "QCD" in sample:
 	    originalIntegral[histname]=hist.Integral()
 	hist.SetTitle("")
 	hist.SetFillStyle(0)
 	hist.SetMarkerStyle(20)
 	#hist.SetMarkerSize(2)
 	hist.GetXaxis().SetTitle(plot[2])
 	if resolution:
	  if "/" in variable:
 	    hist.GetXaxis().SetTitle("(reco-gen)/gen "+plot[2].replace("(GeV)",""))
 	  else:
	    hist.GetXaxis().SetTitle("(reco-gen) "+plot[2])
 	hist.GetYaxis().SetTitle("Normalized Distribution")
 	if "Run" in sample:
 	    integral=hist.Integral()
 	if hist.Integral()>0:
 	    hist.Scale(integral/hist.Integral())

 	hists+=[hist]
        """
 	if "QCD1000" in sample:
 	    histname500="plot"+names[plots.index(plot)]+gen+str(s-1)
 	    for his in reversed(hists):
 		if histname500==his.GetName():
 		    oldIntegral=his.Integral()
 		    if his.Integral()>0:
 			his.Scale(originalIntegral[histname500]/his.Integral())
 		    if hist.Integral()>0:
 			hist.Scale(originalIntegral[histname]/hist.Integral())
 		    weight=204.0/13798133*30522161/8426.0
 		    his.Add(hist,weight)
 		    if oldIntegral>0:
 			his.Scale(oldIntegral/his.Integral())
 		    else:
 			his.Scale(integral/his.Integral())
 		    hist=his
 		    break
 	if "QCD500" in sample:
 	    continue
 	
 	if "QCDPythia8" in sample and not "170" in sample:
 	    samplenames=["170","300","470","600","800","1000","1400","1800"]
 	    samplenumbers=[800046,490042,500051,492988,400059,400050,200070,194313]
 	    samplecrossections=[37974.99,1938.868,124.8942,29.55049,3.871308,0.8031018,0.03637225,0.00197726]
 	    samplenumber=0
 	    for samplename in samplenames:
 	      if samplename in sample:
 		samplenumber=samplenames.index(samplename)
 	    histnameFirst="plot"+names[plots.index(plot)]+gen+str(s-samplenumber)
 	    for his in reversed(hists):
 		if histnameFirst==his.GetName():
 		    oldIntegral=his.Integral()
 		    if his.Integral()>0:
 			his.Scale(originalIntegral[histnameFirst]/his.Integral())
 		    if hist.Integral()>0:
 			hist.Scale(originalIntegral[histname]/hist.Integral())
 		    weight=samplecrossections[samplenumber]/samplenumbers[samplenumber]*samplenumbers[0]/samplecrossections[0]
 		    his.Add(hist,weight)
 		    if oldIntegral>0:
 			originalIntegral[histnameFirst]=his.Integral()
 			his.Scale(oldIntegral/his.Integral())
 		    elif his.Integral()>0:
 			originalIntegral[histnameFirst]=his.Integral()
 			his.Scale(integral/his.Integral())
 		    hist=his
 		    break
 	if "QCDPythia8" in sample and not "1800" in sample:
 	    continue
        """
 	hist.SetLineColor(colors[colorcounter])
 	hist.SetLineStyle(styles[colorcounter])	  
 	hist.SetLineWidth(widths[colorcounter])
 	
 	if counter==0:
 	  firsthist=hist
 	  if "Run" in sample:
 	    hist.Draw("pe")
 	  elif "Gen" in gen:
 	    hist.Draw("chist")
 	  else:
 	    hist.Draw("hist")
 	else:
 	  if "Run" in sample:
 	    hist.Draw("pesame")
 	  elif "Gen" in gen:
 	    hist.Draw("csame")
 	  else:
 	    hist.Draw("histsame")

 	if hist.GetMaximum()>maximum and hist.GetMaximum()<hist.Integral():
 	    maximum=hist.GetMaximum()

	means+=[hist.GetMean()]
	rms+=[hist.GetRMS()]
	means_err+=[hist.GetMeanError()]
	rms_err+=[hist.GetRMSError()]
	if resolution:
	  fit=TF1(hist.GetName()+"g","gaus",0,2)
	  fit.SetRange(-0.5,0.5)
  	  hist.Fit(fit,"0r")
	  fit.SetParameter(2,fit.GetParameter(2)/1.5)
	  fit.SetRange(-fit.GetParameter(2)*1.5+fit.GetParameter(1),fit.GetParameter(2)*1.5+fit.GetParameter(1))
  	  hist.Fit(fit,"0r")
	  fit.SetRange(-fit.GetParameter(2)*1.5+fit.GetParameter(1),fit.GetParameter(2)*1.5+fit.GetParameter(1))
  	  hist.Fit(fit,"0r")
	  means[-1]=fit.GetParameter(1)
	  rms[-1]=fit.GetParameter(2)
          #means_err[-1]=means[-1]/sqrt(0.000000001+hist.GetEntries()*hist.Integral(hist.FindBin(means[-1]-rms[-1]),hist.FindBin(means[-1]+rms[-1])))
          #rms_err[-1]=rms[-1]/sqrt(0.000000001+hist.GetEntries()*hist.Integral(hist.FindBin(means[-1]-rms[-1]),hist.FindBin(means[-1]+rms[-1])))
	  if runSet>31:
	    fit.Draw("lsame")
	  fits+=[fit]
          print runSet,sample,names[plots.index(plot)],"mean:", means[-1]+1., means_err[-1]
          print runSet,sample,names[plots.index(plot)],"rms:", rms[-1]/max(0.000000001,means[-1]+1.), rms_err[-1]/max(0.000000001,means[-1]+1.)

 	if "jet p_{T}" in plot[2] and not resolution:
 	    firsthist.GetYaxis().SetRangeUser(0.001,maximum*20.0)
 	else:
 	    firsthist.GetYaxis().SetRangeUser(0,maximum*2.0)

 	if gen=="Gen" and "Hpp" in  sample:
 	  legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Herwig++","l")
 	elif gen=="Gen" and "Py6" in  sample:
 	  legend.AddEntry(hist,"X #rightarrow W_{T}W_{T} Pythia6","l")
 	elif runSet<30 and s==1:
 	  legend.AddEntry(hist,"W p_{T}=1 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==2:
 	  legend.AddEntry(hist,"W p_{T}=1.5 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==3:
 	  legend.AddEntry(hist,"W p_{T}=2 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==4:
 	  legend.AddEntry(hist,"W p_{T}=2.5 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==5:
 	  legend.AddEntry(hist,"W p_{T}=3.5 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==6:
 	  legend.AddEntry(hist,"q/g p_{T}=1.2 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet<30 and s==7:
 	  legend.AddEntry(hist,"q/g p_{T}=2 TeV, <%0.3f>, RMS=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==30 and s==1:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=0.5 TeV","l")
 	elif runSet==30 and s==2:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=1.5 TeV","l")
 	elif runSet==30 and s==3:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=3.5 TeV","l")
 	elif runSet==30 and s==4:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=1 TeV","l")
 	elif runSet==30 and s==5:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=2 TeV","l")
 	elif runSet==31 and s==1:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=0.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==31 and s==2:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=0.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==31 and s==3:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=1.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==31 and s==4:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=1.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==31 and s==5:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=3.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==31 and s==6:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=3.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet==36 and s==1:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=2 TeV","l")
 	elif runSet==36 and s==2:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=2 TeV","l")
 	elif runSet==36 and s==3:
 	  legend.AddEntry(hist,"q/g Gen-jets p_{T}=2 TeV","l")
 	elif runSet==36 and s==4:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=2 TeV","l")
 	elif runSet==36 and s==5:
 	  legend.AddEntry(hist,"W PF-jets (no-split-neutral) p_{T}=2 TeV","l")
 	elif runSet==36 and s==6:
 	  legend.AddEntry(hist,"q/g PF-jets (no-split-neutral) p_{T}=2 TeV","l")
 	elif runSet>31 and s==1:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=0.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==2:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=0.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==3:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=1.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==4:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=1.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==5:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=1.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==6:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=1.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==7:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=2.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==8:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=2.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==9:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=2.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==10:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=2.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==11:
 	  legend.AddEntry(hist,"W Gen-jets p_{T}=3.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==12:
 	  legend.AddEntry(hist,"W PF-jets p_{T}=3.5 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==13:
 	  legend.AddEntry(hist,"q/g Gen-jets p_{T}=0.2 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==14:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=0.2 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==15:
 	  legend.AddEntry(hist,"q/g Gen-jets p_{T}=1.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==16:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=1.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==17:
 	  legend.AddEntry(hist,"q/g Gen-jets p_{T}=2.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	elif runSet>31 and s==18:
 	  legend.AddEntry(hist,"q/g PF-jets p_{T}=2.0 TeV, <%0.3f>, #sigma=%0.3f"%(means[-1],rms[-1]),"l")
 	else:
 	  legend.AddEntry(hist," + <PU>=22 + sim.","l")
 	counter+=1

      legend.SetTextSize(0.025)
      legend.SetFillStyle(0)
      legend.Draw("same")

      legend4=TLegend(0.23,0.85,0.5,0.9,"CA R=0.8")
      legend4.SetTextSize(0.03)
      legend4.SetFillStyle(0)
      legend4.Draw("same")

      if runSet==33:
       legend2=TLegend(0.17,0.8,0.5,0.85,"1.1 < p_{T} < 1.7 TeV")
       legend2.SetTextSize(0.03)
       legend2.SetFillStyle(0)
       legend2.Draw("same")

      legend2a=TLegend(0.24,0.75,0.5,0.8,"|#eta|<2.4")
      legend2a.SetTextSize(0.03)
      legend2a.SetFillStyle(0)
      legend2a.Draw("same")

      if "parton_dR_1" in plot[1]:
 	legend2b=TLegend(0.17,0.7,0.5,0.75,"#DeltaR(partons) < 0.14")
 	legend2b.SetTextSize(0.03)
 	legend2b.SetFillStyle(0)
 	legend2b.Draw("same")

      banner = TLatex(0.24,0.93,"CMS Preliminary Simulation, #sqrt{s} = 13 TeV");
      banner.SetNDC()
      banner.SetTextSize(0.04)
      banner.Draw();  

      if "aftermass" in names[plots.index(plot)]:
 	 legend3=TLegend(0.17,0.7,0.5,0.75,"60 < m_{j} < 100 GeV")
 	 legend3.SetTextSize(0.03)
 	 legend3.SetFillStyle(0)
 	 legend3.Draw("same")

      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+str(runSet)+str(int(resolution))+".png")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+str(runSet)+str(int(resolution))+".pdf")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+str(runSet)+str(int(resolution))+".root")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+str(runSet)+str(int(resolution))+".C")
      canvas.SaveAs("substructure_highpt_"+names[plots.index(plot)]+"_"+str(runSet)+str(int(resolution))+".eps")
      for f in files:
          f.Close()

