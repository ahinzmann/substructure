# -----------------------------------------------------------------------------
#  File:        rzrBTanalyzerlib.py
#  Description: Analyzer for ntuples created by TheNtupleMaker
#  Created:     Mon Feb 10 20:33:23 2014 by mkanalyzer.py
#  Author:      Andreas Hinzmann
# -----------------------------------------------------------------------------
import os, sys, re
from ROOT import *
from string import atof, atoi, split, strip, replace
from array import array
from math import *
from time import sleep
from sys import exit
# -----------------------------------------------------------------------------
gSystem.AddIncludePath("-Iinclude")
gROOT.ProcessLine(".L src/treestream.cc+")
gROOT.ProcessLine(".L src/pdg.cc+")
# -----------------------------------------------------------------------------
# -- Classes, procedures and functions
# -----------------------------------------------------------------------------
class outputFile:

	def __init__(self, filename, stream=None, savecount=50000):
		if stream != None:
			print "events will be skimmed to file", filename			
			self.tree = stream.tree().CloneTree(0)
			self.weight = Double()
			self.b_weight = self.tree.Branch("eventWeight", self.weight,
											 "eventWeight/D")
			self.SAVECOUNT = savecount
		else:
			self.tree = None
			self.b_weight = None

		self.entry = 0

		self.filename = filename
		self.file = TFile(filename, "recreate")

		self.hist = TH1F("counts", "", 1, 0, 1)
		self.hist.SetBit(TH1.kCanRebin)
		self.hist.SetStats(0)

		self.b_weight = 0

	def addEvent(self, weight=1.0):
		if self.tree == None: return

		self.file = self.tree.GetCurrentFile()
		self.file.cd()
		self.tree.Fill()

		self.entry += 1		
		if self.entry % self.SAVECOUNT == 0:
			self.tree.AutoSave("SaveSelf")

	def count(self, cond, w=1.0):
		self.hist.Fill(cond, w)

	def close(self):
		print "==> histograms saved to file", self.filename
		if self.tree != None:			
			print "==> events skimmed to file", self.filename
			self.file = self.tree.GetCurrentFile()

		self.file.cd()
		#self.file.Write("", TObject.kOverwrite)
		self.file.Write()
		self.file.ls()
		self.file.Close()
# -----------------------------------------------------------------------------
class commandLine:
	def __init__(self):
		pass

def decodeCommandLine():
	argv = sys.argv
	argc = len(argv)

	cl = commandLine()
	cl.progname = split(os.path.basename(argv[0]),'.')[0]

	if argc > 1:
		cl.filelist = argv[1]
	else:
		cl.filelist = "filelist.txt"

	if argc > 2: 
		cl.outputfilename = argv[2] # 2nd (optional) command line argument
	else:
		cl.outputfilename = cl.progname + "_histograms"

	# Make sure extension is ".root"
	if cl.outputfilename[:-5] != ".root": cl.outputfilename += ".root"
	print "==> output to:", cl.outputfilename

	return cl
# -----------------------------------------------------------------------------
def error(message):
	print "** error ** " + message
	sys.exit(0)
# -----------------------------------------------------------------------------
#  Read ntuple filenames from file list

def getFilenames(filelist):
	if not os.path.exists(filelist):
		error("unable to open file: " + filelist)

	# Get ntuple file names
	filenames = filter(lambda x: x != "",
					   map(strip, open(filelist).readlines()))
	v = vector("string")()
	for filename in filenames: v.push_back(filename)
	return v
# -----------------------------------------------------------------------------
TEXTFONT = 42
TEXTSIZE = 0.031
#------------------------------------------------------------------------------
def setStyle():
	gROOT.SetStyle("Pub")
	style = gROOT.GetStyle("Pub")
	style.SetPalette(1)

	# For the canvas
	style.SetCanvasBorderMode(0)
	style.SetCanvasColor(kWhite)
	style.SetCanvasDefH(500)
	style.SetCanvasDefW(500)
	style.SetCanvasDefX(0)
	style.SetCanvasDefY(0)

	# For the pad
	style.SetPadBorderMode(0)
	style.SetPadColor(kWhite)
	style.SetPadGridX(kFALSE)
	style.SetPadGridY(kTRUE)
	style.SetGridColor(kGreen)
	style.SetGridStyle(3)
	style.SetGridWidth(1)

	# For the frame
	style.SetFrameBorderMode(0)
	style.SetFrameBorderSize(1)
	style.SetFrameFillColor(0)
	style.SetFrameFillStyle(0)
	style.SetFrameLineColor(1)
	style.SetFrameLineStyle(1)
	style.SetFrameLineWidth(1)

	# For the histogram
	style.SetHistLineColor(1)
	style.SetHistLineStyle(0)
	style.SetHistLineWidth(1)
	style.SetEndErrorSize(2)
	#style.SetErrorX(0.)
	style.SetMarkerSize(0.1)
	style.SetMarkerStyle(20)

	# For the fit/function
	style.SetOptFit(1)
	style.SetFitFormat("5.4g")
	style.SetFuncColor(2)
	style.SetFuncStyle(1)
	style.SetFuncWidth(1)

	#For the date
	style.SetOptDate(0)

	# For the statistics box
	style.SetOptFile(0)
	style.SetOptStat("")
	# To display the mean and RMS
	#style.SetOptStat("mr") 
	style.SetStatColor(kWhite)
	style.SetStatFont(TEXTFONT)
	style.SetStatFontSize(TEXTSIZE)
	style.SetStatTextColor(1)
	style.SetStatFormat("6.4g")
	style.SetStatBorderSize(1)
	style.SetStatH(0.2)
	style.SetStatW(0.3)

	# Margins
	style.SetPadTopMargin(0.05)
	style.SetPadBottomMargin(0.16)
	style.SetPadLeftMargin(0.16)
	style.SetPadRightMargin(0.16)

	# For the global title
	style.SetOptTitle(0)
	style.SetTitleFont(TEXTFONT)
	style.SetTitleColor(1)
	style.SetTitleTextColor(1)
	style.SetTitleFillColor(10)
	style.SetTitleFontSize(TEXTSIZE*1.1)

	# For the axis titles
	style.SetTitleColor(1, "XYZ")
	style.SetTitleFont(TEXTFONT, "XYZ")
	style.SetTitleSize(TEXTSIZE*1.2, "XYZ") # 0,05
	style.SetTitleXOffset(1.25) # 0.9
	style.SetTitleYOffset(1.25) # 1.25

	# For the axis labels
	style.SetLabelColor(1, "XYZ")
	style.SetLabelFont(TEXTFONT, "XYZ")
	style.SetLabelOffset(0.006, "XYZ")
	style.SetLabelSize(TEXTSIZE*1.2, "XYZ")

	# For the axis
	style.SetAxisColor(1, "XYZ")
	style.SetStripDecimals(kTRUE)
	style.SetTickLength(0.03, "XYZ")
	style.SetNdivisions(505, "XYZ")

	# To get tick marks on the opposite side of the frame
	style.SetPadTickX(1)  
	style.SetPadTickY(1)

	# Change for log plots
	style.SetOptLogx(0)
	style.SetOptLogy(0)
	style.SetOptLogz(0)

	# Postscript options
	style.SetPaperSize(20.,20.)

	style.cd()
# -----------------------------------------------------------------------------
#  Define variables to be read
# -----------------------------------------------------------------------------
GenEventInfoProduct_alphaQCD	= Double()
GenEventInfoProduct_alphaQED	= Double()
GenEventInfoProduct_hasBinningValues	= Long()
GenEventInfoProduct_hasPDF	= Long()
GenEventInfoProduct_qScale	= Double()
GenEventInfoProduct_signalProcessID	= Long()
GenEventInfoProduct_weight	= Double()
PileupSummaryInfo_getBunchCrossing	= vector("int")(200)
PileupSummaryInfo_getPU_NumInteractions	= vector("int")(200)
PileupSummaryInfo_getTrueNumInteractions	= vector("float")(200)
edmEventHelper_bunchCrossing	= Long()
edmEventHelper_event	= Long()
edmEventHelper_isRealData	= Long()
edmEventHelper_luminosityBlock	= Long()
edmEventHelper_orbitNumber	= Long()
edmEventHelper_run	= Long()
nPileupSummaryInfo	= Long()
npatJetHelperCA8CHS	= Long()
npatJetHelperCA8CHSpruned	= Long()
npatJetHelperGenCA8CHS	= Long()
npatJetHelperGenCA8CHSpruned	= Long()
nrecoGenParticleHelper	= Long()
patJetHelperCA8CHS_C2beta05	= vector("float")(200)
patJetHelperCA8CHS_C2beta10	= vector("float")(200)
patJetHelperCA8CHS_C2beta15	= vector("float")(200)
patJetHelperCA8CHS_C2beta17	= vector("float")(200)
patJetHelperCA8CHS_C2beta20	= vector("float")(200)
patJetHelperCA8CHS_C2beta25	= vector("float")(200)
patJetHelperCA8CHS_chargedEmEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_chargedHadronEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_chargedMultiplicity	= vector("int")(200)
patJetHelperCA8CHS_combinedSecondaryVertexBJetTags	= vector("float")(200)
patJetHelperCA8CHS_energy	= vector("double")(200)
patJetHelperCA8CHS_et	= vector("double")(200)
patJetHelperCA8CHS_eta	= vector("double")(200)
patJetHelperCA8CHS_getChargedPt0	= vector("int")(200)
patJetHelperCA8CHS_getChargedPt1	= vector("int")(200)
patJetHelperCA8CHS_getChargedPt2	= vector("int")(200)
patJetHelperCA8CHS_getChargedPt3	= vector("int")(200)
patJetHelperCA8CHS_getCorrectedPrunedJetMass	= vector("float")(200)
patJetHelperCA8CHS_getNcharged01	= vector("int")(200)
patJetHelperCA8CHS_getNneutral01	= vector("int")(200)
patJetHelperCA8CHS_getPrunedJetMass	= vector("float")(200)
patJetHelperCA8CHS_getPt0	= vector("int")(200)
patJetHelperCA8CHS_getPt1	= vector("int")(200)
patJetHelperCA8CHS_getPt2	= vector("int")(200)
patJetHelperCA8CHS_getPt3	= vector("int")(200)
patJetHelperCA8CHS_getSplitBlockPrunedJetMass	= vector("float")(200)
patJetHelperCA8CHS_getTrackJetMass	= vector("float")(200)
patJetHelperCA8CHS_jetArea	= vector("float")(200)
patJetHelperCA8CHS_jetCharge03	= vector("float")(200)
patJetHelperCA8CHS_jetCharge05	= vector("float")(200)
patJetHelperCA8CHS_jetCharge10	= vector("float")(200)
patJetHelperCA8CHS_mass	= vector("double")(200)
patJetHelperCA8CHS_muonEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_nConstituents	= vector("int")(200)
patJetHelperCA8CHS_neutralEmEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_neutralHadronEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_partonFlavour	= vector("int")(200)
patJetHelperCA8CHS_phi	= vector("double")(200)
patJetHelperCA8CHS_photonEnergyFraction	= vector("float")(200)
patJetHelperCA8CHS_pt	= vector("double")(200)
patJetHelperCA8CHS_rapidity	= vector("double")(200)
patJetHelperCA8CHS_tau1	= vector("float")(200)
patJetHelperCA8CHS_tau2	= vector("float")(200)
patJetHelperCA8CHS_tau3	= vector("float")(200)
patJetHelperCA8CHS_uncor_energy	= vector("double")(200)
patJetHelperCA8CHS_uncor_et	= vector("double")(200)
patJetHelperCA8CHS_uncor_pt	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_0_energy	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_eta	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_jetCharge03	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_0_jetCharge05	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_0_jetCharge10	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_0_mass	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_phi	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_pt	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_0_rapidity	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_1_energy	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_eta	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_jetCharge03	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_1_jetCharge05	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_1_jetCharge10	= vector("float")(200)
patJetHelperCA8CHSpruned_daughter_1_mass	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_phi	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_pt	= vector("double")(200)
patJetHelperCA8CHSpruned_daughter_1_rapidity	= vector("double")(200)
patJetHelperCA8CHSpruned_energy	= vector("double")(200)
patJetHelperCA8CHSpruned_et	= vector("double")(200)
patJetHelperCA8CHSpruned_eta	= vector("double")(200)
patJetHelperCA8CHSpruned_jetArea	= vector("float")(200)
patJetHelperCA8CHSpruned_jetCharge03	= vector("float")(200)
patJetHelperCA8CHSpruned_jetCharge05	= vector("float")(200)
patJetHelperCA8CHSpruned_jetCharge10	= vector("float")(200)
patJetHelperCA8CHSpruned_mass	= vector("double")(200)
patJetHelperCA8CHSpruned_nConstituents	= vector("int")(200)
patJetHelperCA8CHSpruned_numberOfDaughters	= vector("size_t")(200)
patJetHelperCA8CHSpruned_partonFlavour	= vector("int")(200)
patJetHelperCA8CHSpruned_phi	= vector("double")(200)
patJetHelperCA8CHSpruned_pt	= vector("double")(200)
patJetHelperCA8CHSpruned_rapidity	= vector("double")(200)
patJetHelperCA8CHSpruned_tau1	= vector("float")(200)
patJetHelperCA8CHSpruned_tau2	= vector("float")(200)
patJetHelperCA8CHSpruned_tau3	= vector("float")(200)
patJetHelperCA8CHSpruned_uncor_energy	= vector("double")(200)
patJetHelperCA8CHSpruned_uncor_et	= vector("double")(200)
patJetHelperCA8CHSpruned_uncor_pt	= vector("double")(200)
patJetHelperGenCA8CHS_energy	= vector("double")(200)
patJetHelperGenCA8CHS_et	= vector("double")(200)
patJetHelperGenCA8CHS_eta	= vector("double")(200)
patJetHelperGenCA8CHS_genC2beta05	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta10	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta15	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta17	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta17CHS	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta20	= vector("float")(200)
patJetHelperGenCA8CHS_genC2beta25	= vector("float")(200)
patJetHelperGenCA8CHS_genJetCharge03	= vector("float")(200)
patJetHelperGenCA8CHS_genJetCharge05	= vector("float")(200)
patJetHelperGenCA8CHS_genJetCharge10	= vector("float")(200)
patJetHelperGenCA8CHS_genNCHS	= vector("float")(200)
patJetHelperGenCA8CHS_genTau1	= vector("float")(200)
patJetHelperGenCA8CHS_genTau1CHS	= vector("float")(200)
patJetHelperGenCA8CHS_genTau1Pt2	= vector("float")(200)
patJetHelperGenCA8CHS_genTau1Pt5	= vector("float")(200)
patJetHelperGenCA8CHS_genTau2	= vector("float")(200)
patJetHelperGenCA8CHS_genTau2CHS	= vector("float")(200)
patJetHelperGenCA8CHS_genTau2Pt2	= vector("float")(200)
patJetHelperGenCA8CHS_genTau2Pt5	= vector("float")(200)
patJetHelperGenCA8CHS_genTau3	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass0005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass001	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass002	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass01	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass02	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMass05	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF0005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF001	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF002	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF01	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF02	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPF05	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02	= vector("float")(200)
patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05	= vector("float")(200)
patJetHelperGenCA8CHS_getGenTrackJetMass	= vector("float")(200)
patJetHelperGenCA8CHS_jetArea	= vector("float")(200)
patJetHelperGenCA8CHS_mass	= vector("double")(200)
patJetHelperGenCA8CHS_nConstituents	= vector("int")(200)
patJetHelperGenCA8CHS_partonFlavour	= vector("int")(200)
patJetHelperGenCA8CHS_phi	= vector("double")(200)
patJetHelperGenCA8CHS_pt	= vector("double")(200)
patJetHelperGenCA8CHS_rapidity	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_energy	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_eta	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_mass	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_phi	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_pt	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_0_rapidity	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_energy	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_eta	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_mass	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_phi	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_pt	= vector("double")(200)
patJetHelperGenCA8CHSpruned_daughter_1_rapidity	= vector("double")(200)
patJetHelperGenCA8CHSpruned_energy	= vector("double")(200)
patJetHelperGenCA8CHSpruned_et	= vector("double")(200)
patJetHelperGenCA8CHSpruned_eta	= vector("double")(200)
patJetHelperGenCA8CHSpruned_genTau1	= vector("float")(200)
patJetHelperGenCA8CHSpruned_genTau2	= vector("float")(200)
patJetHelperGenCA8CHSpruned_genTau3	= vector("float")(200)
patJetHelperGenCA8CHSpruned_jetArea	= vector("float")(200)
patJetHelperGenCA8CHSpruned_jetCharge03	= vector("float")(200)
patJetHelperGenCA8CHSpruned_jetCharge05	= vector("float")(200)
patJetHelperGenCA8CHSpruned_jetCharge10	= vector("float")(200)
patJetHelperGenCA8CHSpruned_mass	= vector("double")(200)
patJetHelperGenCA8CHSpruned_nConstituents	= vector("int")(200)
patJetHelperGenCA8CHSpruned_numberOfDaughters	= vector("size_t")(200)
patJetHelperGenCA8CHSpruned_partonFlavour	= vector("int")(200)
patJetHelperGenCA8CHSpruned_phi	= vector("double")(200)
patJetHelperGenCA8CHSpruned_pt	= vector("double")(200)
patJetHelperGenCA8CHSpruned_rapidity	= vector("double")(200)
recoGenParticleHelper_charge	= vector("int")(10000)
recoGenParticleHelper_eta	= vector("double")(10000)
recoGenParticleHelper_firstDaughter	= vector("int")(10000)
recoGenParticleHelper_firstMother	= vector("int")(10000)
recoGenParticleHelper_lastDaughter	= vector("int")(10000)
recoGenParticleHelper_lastMother	= vector("int")(10000)
recoGenParticleHelper_mass	= vector("double")(10000)
recoGenParticleHelper_pdgId	= vector("int")(10000)
recoGenParticleHelper_phi	= vector("double")(10000)
recoGenParticleHelper_pt	= vector("double")(10000)
recoGenParticleHelper_status	= vector("int")(10000)

stream.select("GenEventInfoProduct_generator.alphaQCD", GenEventInfoProduct_alphaQCD)
stream.select("GenEventInfoProduct_generator.alphaQED", GenEventInfoProduct_alphaQED)
stream.select("GenEventInfoProduct_generator.hasBinningValues", GenEventInfoProduct_hasBinningValues)
stream.select("GenEventInfoProduct_generator.hasPDF", GenEventInfoProduct_hasPDF)
stream.select("GenEventInfoProduct_generator.qScale", GenEventInfoProduct_qScale)
stream.select("GenEventInfoProduct_generator.signalProcessID", GenEventInfoProduct_signalProcessID)
stream.select("GenEventInfoProduct_generator.weight", GenEventInfoProduct_weight)
stream.select("PileupSummaryInfo_addPileupInfo.getBunchCrossing", PileupSummaryInfo_getBunchCrossing)
stream.select("PileupSummaryInfo_addPileupInfo.getPU_NumInteractions", PileupSummaryInfo_getPU_NumInteractions)
stream.select("PileupSummaryInfo_addPileupInfo.getTrueNumInteractions", PileupSummaryInfo_getTrueNumInteractions)
stream.select("edmEventHelper_info.bunchCrossing", edmEventHelper_bunchCrossing)
stream.select("edmEventHelper_info.event", edmEventHelper_event)
stream.select("edmEventHelper_info.isRealData", edmEventHelper_isRealData)
stream.select("edmEventHelper_info.luminosityBlock", edmEventHelper_luminosityBlock)
stream.select("edmEventHelper_info.orbitNumber", edmEventHelper_orbitNumber)
stream.select("edmEventHelper_info.run", edmEventHelper_run)
stream.select("nPileupSummaryInfo_addPileupInfo", nPileupSummaryInfo)
stream.select("npatJetHelper_selectedPatJetsCA8CHSwithNsub", npatJetHelperCA8CHS)
stream.select("npatJetHelper_selectedPatJetsCA8CHSpruned", npatJetHelperCA8CHSpruned)
stream.select("npatJetHelper_patGenJetsCA8CHS", npatJetHelperGenCA8CHS)
stream.select("npatJetHelper_patGenJetsCA8CHSpruned", npatJetHelperGenCA8CHSpruned)
stream.select("nrecoGenParticleHelper_genParticles", nrecoGenParticleHelper)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta05", patJetHelperCA8CHS_C2beta05)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta10", patJetHelperCA8CHS_C2beta10)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta15", patJetHelperCA8CHS_C2beta15)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta17", patJetHelperCA8CHS_C2beta17)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta20", patJetHelperCA8CHS_C2beta20)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.C2beta25", patJetHelperCA8CHS_C2beta25)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedEmEnergyFraction", patJetHelperCA8CHS_chargedEmEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedHadronEnergyFraction", patJetHelperCA8CHS_chargedHadronEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.chargedMultiplicity", patJetHelperCA8CHS_chargedMultiplicity)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.combinedSecondaryVertexBJetTags", patJetHelperCA8CHS_combinedSecondaryVertexBJetTags)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.energy", patJetHelperCA8CHS_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.et", patJetHelperCA8CHS_et)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.eta", patJetHelperCA8CHS_eta)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt0", patJetHelperCA8CHS_getChargedPt0)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt1", patJetHelperCA8CHS_getChargedPt1)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt2", patJetHelperCA8CHS_getChargedPt2)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getChargedPt3", patJetHelperCA8CHS_getChargedPt3)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getCorrectedPrunedJetMass", patJetHelperCA8CHS_getCorrectedPrunedJetMass)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNcharged01", patJetHelperCA8CHS_getNcharged01)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getNneutral01", patJetHelperCA8CHS_getNneutral01)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPrunedJetMass", patJetHelperCA8CHS_getPrunedJetMass)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt0", patJetHelperCA8CHS_getPt0)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt1", patJetHelperCA8CHS_getPt1)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt2", patJetHelperCA8CHS_getPt2)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getPt3", patJetHelperCA8CHS_getPt3)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getSplitBlockPrunedJetMass", patJetHelperCA8CHS_getSplitBlockPrunedJetMass)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.getTrackJetMass", patJetHelperCA8CHS_getTrackJetMass)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetArea", patJetHelperCA8CHS_jetArea)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge03", patJetHelperCA8CHS_jetCharge03)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge05", patJetHelperCA8CHS_jetCharge05)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.jetCharge10", patJetHelperCA8CHS_jetCharge10)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.mass", patJetHelperCA8CHS_mass)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.muonEnergyFraction", patJetHelperCA8CHS_muonEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.nConstituents", patJetHelperCA8CHS_nConstituents)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralEmEnergyFraction", patJetHelperCA8CHS_neutralEmEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.neutralHadronEnergyFraction", patJetHelperCA8CHS_neutralHadronEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.partonFlavour", patJetHelperCA8CHS_partonFlavour)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.phi", patJetHelperCA8CHS_phi)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.photonEnergyFraction", patJetHelperCA8CHS_photonEnergyFraction)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.pt", patJetHelperCA8CHS_pt)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.rapidity", patJetHelperCA8CHS_rapidity)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau1", patJetHelperCA8CHS_tau1)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau2", patJetHelperCA8CHS_tau2)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.tau3", patJetHelperCA8CHS_tau3)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_energy", patJetHelperCA8CHS_uncor_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_et", patJetHelperCA8CHS_uncor_et)
stream.select("patJetHelper_selectedPatJetsCA8CHSwithNsub.uncor_pt", patJetHelperCA8CHS_uncor_pt)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_combinedSecondaryVertexBJetTags", patJetHelperCA8CHSpruned_daughter_0_combinedSecondaryVertexBJetTags)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_energy", patJetHelperCA8CHSpruned_daughter_0_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_eta", patJetHelperCA8CHSpruned_daughter_0_eta)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge03", patJetHelperCA8CHSpruned_daughter_0_jetCharge03)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge05", patJetHelperCA8CHSpruned_daughter_0_jetCharge05)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_jetCharge10", patJetHelperCA8CHSpruned_daughter_0_jetCharge10)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_mass", patJetHelperCA8CHSpruned_daughter_0_mass)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_phi", patJetHelperCA8CHSpruned_daughter_0_phi)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_pt", patJetHelperCA8CHSpruned_daughter_0_pt)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_0_rapidity", patJetHelperCA8CHSpruned_daughter_0_rapidity)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_combinedSecondaryVertexBJetTags", patJetHelperCA8CHSpruned_daughter_1_combinedSecondaryVertexBJetTags)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_energy", patJetHelperCA8CHSpruned_daughter_1_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_eta", patJetHelperCA8CHSpruned_daughter_1_eta)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge03", patJetHelperCA8CHSpruned_daughter_1_jetCharge03)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge05", patJetHelperCA8CHSpruned_daughter_1_jetCharge05)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_jetCharge10", patJetHelperCA8CHSpruned_daughter_1_jetCharge10)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_mass", patJetHelperCA8CHSpruned_daughter_1_mass)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_phi", patJetHelperCA8CHSpruned_daughter_1_phi)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_pt", patJetHelperCA8CHSpruned_daughter_1_pt)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.daughter_1_rapidity", patJetHelperCA8CHSpruned_daughter_1_rapidity)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.energy", patJetHelperCA8CHSpruned_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.et", patJetHelperCA8CHSpruned_et)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.eta", patJetHelperCA8CHSpruned_eta)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetArea", patJetHelperCA8CHSpruned_jetArea)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge03", patJetHelperCA8CHSpruned_jetCharge03)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge05", patJetHelperCA8CHSpruned_jetCharge05)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.jetCharge10", patJetHelperCA8CHSpruned_jetCharge10)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.mass", patJetHelperCA8CHSpruned_mass)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.nConstituents", patJetHelperCA8CHSpruned_nConstituents)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.numberOfDaughters", patJetHelperCA8CHSpruned_numberOfDaughters)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.partonFlavour", patJetHelperCA8CHSpruned_partonFlavour)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.phi", patJetHelperCA8CHSpruned_phi)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.pt", patJetHelperCA8CHSpruned_pt)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.rapidity", patJetHelperCA8CHSpruned_rapidity)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau1", patJetHelperCA8CHSpruned_tau1)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau2", patJetHelperCA8CHSpruned_tau2)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.tau3", patJetHelperCA8CHSpruned_tau3)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_energy", patJetHelperCA8CHSpruned_uncor_energy)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_et", patJetHelperCA8CHSpruned_uncor_et)
stream.select("patJetHelper_selectedPatJetsCA8CHSpruned.uncor_pt", patJetHelperCA8CHSpruned_uncor_pt)
stream.select("patJetHelper_patGenJetsCA8CHS.energy", patJetHelperGenCA8CHS_energy)
stream.select("patJetHelper_patGenJetsCA8CHS.et", patJetHelperGenCA8CHS_et)
stream.select("patJetHelper_patGenJetsCA8CHS.eta", patJetHelperGenCA8CHS_eta)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta05", patJetHelperGenCA8CHS_genC2beta05)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta10", patJetHelperGenCA8CHS_genC2beta10)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta15", patJetHelperGenCA8CHS_genC2beta15)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17", patJetHelperGenCA8CHS_genC2beta17)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta17CHS", patJetHelperGenCA8CHS_genC2beta17CHS)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta20", patJetHelperGenCA8CHS_genC2beta20)
stream.select("patJetHelper_patGenJetsCA8CHS.genC2beta25", patJetHelperGenCA8CHS_genC2beta25)
stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge03", patJetHelperGenCA8CHS_genJetCharge03)
stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge05", patJetHelperGenCA8CHS_genJetCharge05)
stream.select("patJetHelper_patGenJetsCA8CHS.genJetCharge10", patJetHelperGenCA8CHS_genJetCharge10)
stream.select("patJetHelper_patGenJetsCA8CHS.genNCHS", patJetHelperGenCA8CHS_genNCHS)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau1", patJetHelperGenCA8CHS_genTau1)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau1CHS", patJetHelperGenCA8CHS_genTau1CHS)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau1Pt2", patJetHelperGenCA8CHS_genTau1Pt2)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau1Pt5", patJetHelperGenCA8CHS_genTau1Pt5)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau2", patJetHelperGenCA8CHS_genTau2)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau2CHS", patJetHelperGenCA8CHS_genTau2CHS)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau2Pt2", patJetHelperGenCA8CHS_genTau2Pt2)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau2Pt5", patJetHelperGenCA8CHS_genTau2Pt5)
stream.select("patJetHelper_patGenJetsCA8CHS.genTau3", patJetHelperGenCA8CHS_genTau3)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass0005", patJetHelperGenCA8CHS_getGenCaloJetMass0005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass001", patJetHelperGenCA8CHS_getGenCaloJetMass001)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass002", patJetHelperGenCA8CHS_getGenCaloJetMass002)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass005", patJetHelperGenCA8CHS_getGenCaloJetMass005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass01", patJetHelperGenCA8CHS_getGenCaloJetMass01)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass02", patJetHelperGenCA8CHS_getGenCaloJetMass02)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMass05", patJetHelperGenCA8CHS_getGenCaloJetMass05)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF0005", patJetHelperGenCA8CHS_getGenCaloJetMassPF0005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF001", patJetHelperGenCA8CHS_getGenCaloJetMassPF001)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF002", patJetHelperGenCA8CHS_getGenCaloJetMassPF002)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF005", patJetHelperGenCA8CHS_getGenCaloJetMassPF005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF01", patJetHelperGenCA8CHS_getGenCaloJetMassPF01)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF02", patJetHelperGenCA8CHS_getGenCaloJetMassPF02)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPF05", patJetHelperGenCA8CHS_getGenCaloJetMassPF05)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect0005", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect0005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect001", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect001)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect002", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect002)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect005", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect005)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect01", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect01)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect02", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect02)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenCaloJetMassPFcorrect05", patJetHelperGenCA8CHS_getGenCaloJetMassPFcorrect05)
stream.select("patJetHelper_patGenJetsCA8CHS.getGenTrackJetMass", patJetHelperGenCA8CHS_getGenTrackJetMass)
stream.select("patJetHelper_patGenJetsCA8CHS.jetArea", patJetHelperGenCA8CHS_jetArea)
stream.select("patJetHelper_patGenJetsCA8CHS.mass", patJetHelperGenCA8CHS_mass)
stream.select("patJetHelper_patGenJetsCA8CHS.nConstituents", patJetHelperGenCA8CHS_nConstituents)
stream.select("patJetHelper_patGenJetsCA8CHS.partonFlavour", patJetHelperGenCA8CHS_partonFlavour)
stream.select("patJetHelper_patGenJetsCA8CHS.phi", patJetHelperGenCA8CHS_phi)
stream.select("patJetHelper_patGenJetsCA8CHS.pt", patJetHelperGenCA8CHS_pt)
stream.select("patJetHelper_patGenJetsCA8CHS.rapidity", patJetHelperGenCA8CHS_rapidity)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_energy", patJetHelperGenCA8CHSpruned_daughter_0_energy)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_eta", patJetHelperGenCA8CHSpruned_daughter_0_eta)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_mass", patJetHelperGenCA8CHSpruned_daughter_0_mass)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_phi", patJetHelperGenCA8CHSpruned_daughter_0_phi)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_pt", patJetHelperGenCA8CHSpruned_daughter_0_pt)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_0_rapidity", patJetHelperGenCA8CHSpruned_daughter_0_rapidity)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_energy", patJetHelperGenCA8CHSpruned_daughter_1_energy)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_eta", patJetHelperGenCA8CHSpruned_daughter_1_eta)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_mass", patJetHelperGenCA8CHSpruned_daughter_1_mass)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_phi", patJetHelperGenCA8CHSpruned_daughter_1_phi)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_pt", patJetHelperGenCA8CHSpruned_daughter_1_pt)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.daughter_1_rapidity", patJetHelperGenCA8CHSpruned_daughter_1_rapidity)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.energy", patJetHelperGenCA8CHSpruned_energy)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.et", patJetHelperGenCA8CHSpruned_et)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.eta", patJetHelperGenCA8CHSpruned_eta)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau1", patJetHelperGenCA8CHSpruned_genTau1)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau2", patJetHelperGenCA8CHSpruned_genTau2)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.genTau3", patJetHelperGenCA8CHSpruned_genTau3)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetArea", patJetHelperGenCA8CHSpruned_jetArea)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge03", patJetHelperGenCA8CHSpruned_jetCharge03)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge05", patJetHelperGenCA8CHSpruned_jetCharge05)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.jetCharge10", patJetHelperGenCA8CHSpruned_jetCharge10)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.mass", patJetHelperGenCA8CHSpruned_mass)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.nConstituents", patJetHelperGenCA8CHSpruned_nConstituents)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.numberOfDaughters", patJetHelperGenCA8CHSpruned_numberOfDaughters)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.partonFlavour", patJetHelperGenCA8CHSpruned_partonFlavour)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.phi", patJetHelperGenCA8CHSpruned_phi)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.pt", patJetHelperGenCA8CHSpruned_pt)
stream.select("patJetHelper_patGenJetsCA8CHSpruned.rapidity", patJetHelperGenCA8CHSpruned_rapidity)
stream.select("recoGenParticleHelper_genParticles.charge", recoGenParticleHelper_charge)
stream.select("recoGenParticleHelper_genParticles.eta", recoGenParticleHelper_eta)
stream.select("recoGenParticleHelper_genParticles.firstDaughter", recoGenParticleHelper_firstDaughter)
stream.select("recoGenParticleHelper_genParticles.firstMother", recoGenParticleHelper_firstMother)
stream.select("recoGenParticleHelper_genParticles.lastDaughter", recoGenParticleHelper_lastDaughter)
stream.select("recoGenParticleHelper_genParticles.lastMother", recoGenParticleHelper_lastMother)
stream.select("recoGenParticleHelper_genParticles.mass", recoGenParticleHelper_mass)
stream.select("recoGenParticleHelper_genParticles.pdgId", recoGenParticleHelper_pdgId)
stream.select("recoGenParticleHelper_genParticles.phi", recoGenParticleHelper_phi)
stream.select("recoGenParticleHelper_genParticles.pt", recoGenParticleHelper_pt)
stream.select("recoGenParticleHelper_genParticles.status", recoGenParticleHelper_status)
