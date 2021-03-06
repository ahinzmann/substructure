#$Revision: 1.29 $
import FWCore.ParameterSet.Config as cms

process = cms.Process("TheNtupleMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")
# See TheNtupleMaker twiki for a brief explanation
process.MessageLogger.destinations = cms.untracked.vstring("cerr")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.cerr.default.limit = 5

# This is required in order to configure HLTConfigProducer
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# Run on MC or data

runOnMC = True
runPF = True
runNoCHS = False
runCaloJets = False
runCA8jets = True
runQJets = False
writePatTuple = False
runTrimmedCA8jets = True

# Input file

#samplename='WW3000'
#samplename='WW3000_posCAL'
#samplename='WW3000_posECAL'
#samplename='WW3000_fixHCAL'
#samplename='WW3000_fixTRACK'
#samplename='WW3000_fixTRACK_noHCAL'
#samplename='WW3000_posHCAL_fixTRACK'
#samplename='WW3000_posHCAL_fixTRACK_showerSigma8'
#samplename='WW2000_posHCAL_fixTRACK'
#samplename='WW4000_posHCAL_fixTRACK'
#samplename='qW5000_posHCAL_fixTRACK'
#samplename='qW7000_posHCAL_fixTRACK'
#samplename='QCD30'
#samplename='QCD30_posCAL'
#samplename='QCD30_posECAL'
#samplename='QCD30_fixHCAL'
#samplename='QCD30_fixTRACK'
#samplename='QCD30_fixTRACK_noHCAL'
#samplename='QCD30_posHCAL_fixTRACK'
#samplename='QCD30_posHCAL_fixTRACK_showerSigma8'
#samplename='QCD170'
#samplename='QCD170_posCAL'
#samplename='QCD170_posECAL'
#samplename='QCD170_fixHCAL'
#samplename='QCD170_fixTRACK'
#samplename='QCD170_fixTRACK_noHCAL'
#samplename='QCD170_posHCAL_fixTRACK'
#samplename='QCD170_posHCAL_fixTRACK_showerSigma8'
#samplename='QCD1000'
#samplename='QCD1000_posCAL'
#samplename='QCD1000_posECAL'
#samplename='QCD1000_fixHCAL'
#samplename='QCD1000_fixTRACK'
#samplename='QCD1000_fixTRACK_noHCAL'
#samplename='QCD1000_posHCAL_fixTRACK'
#samplename='QCD1000_posHCAL_fixTRACK_showerSigma8'
#samplename='QCD1800_posHCAL_fixTRACK'

#samplename='WW1000_posHCAL_fixTRACK_splitPFecal'
#samplename='WW2000_posHCAL_fixTRACK_splitPFecal'
#samplename='WW3000_posHCAL_fixTRACK_splitPFecal'
#samplename='WW4000_posHCAL_fixTRACK_splitPFecal'
#samplename='qW3000_posHCAL_fixTRACK_splitPFecal'
#samplename='qW5000_posHCAL_fixTRACK_splitPFecal'
#samplename='qW7000_posHCAL_fixTRACK_splitPFecal'
#samplename='QCD30_posHCAL_fixTRACK_splitPFecal'
#samplename='QCD170_posHCAL_fixTRACK_splitPFecal'
#samplename='QCD1000_posHCAL_fixTRACK_splitPFecal'
#samplename='QCD1800_posHCAL_fixTRACK_splitPFecal'

#samplename='WW3000_posHCAL_fixTRACK_splitPFecal2'
#samplename='QCD1000_posHCAL_fixTRACK_splitPFecal2'
#samplename='WW3000_posHCAL_fixTRACK_splitPFecal3'
#samplename='WW4000_posHCAL_fixTRACK_splitPFecal3'
#samplename='QCD1000_posHCAL_fixTRACK_splitPFecal3'

#samplename='WW3000_posHCAL_PU'
#samplename='WW2000_posHCAL_PU'
#samplename='WW4000_posHCAL_PU'
#samplename='qW5000_posHCAL_PU'
#samplename='qW7000_posHCAL_PU'
#samplename='QCD30_posHCAL_PU'
#samplename='QCD170_posHCAL_PU'
#samplename='QCD1000_posHCAL_PU'
#samplename='QCD1800_posHCAL_PU'

#samplename='WW3000_posHCAL'
#samplename='WW2000_posHCAL'
#samplename='WW4000_posHCAL'
#samplename='qW5000_posHCAL'
#samplename='qW7000_posHCAL'
#samplename='QCD30_posHCAL'
#samplename='QCD170_posHCAL'
#samplename='QCD1000_posHCAL'
#samplename='QCD1800_posHCAL'

#samplename='WW3000_posHCAL_splitting'
#samplename='WW3000_posHCAL_noSplitting'
#samplename='WW4000_posHCAL_splitting'
#samplename='WW4000_posHCAL_noSplitting'

#samplename='WW2000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='WW3000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='WW4000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='qW5000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='qW7000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='QCD30_posHCAL_fixTRACK_splitPFecal_new'
#samplename='QCD170_posHCAL_fixTRACK_splitPFecal_new'
#samplename='QCD1000_posHCAL_fixTRACK_splitPFecal_new'
#samplename='QCD1800_posHCAL_fixTRACK_splitPFecal_new'

#samplename='WW4000_710pre8_track'

#samplename='WW2000_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='WW3000_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='qW5000_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='qW7000_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat1_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat2_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat3_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat4_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat5_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat6_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat7_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat8_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat9_710pre8_posHCAL_jetCoreTrack_clusterSplit'
#samplename='QCDflat10_710pre8_posHCAL_jetCoreTrack_clusterSplit'

#samplename='WW4000_710pre8'

#samplename='WW2000_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='WW3000_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='WW4000_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='qW5000_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='qW7000_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat1_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat2_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat3_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat4_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat5_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat6_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat7_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat8_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat9_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCDflat10_710pre8_jetCoreTrack_clusterSplit_splitMergedNeutrals'

#samplename='WW1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='WW2000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='WW3000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='WW4000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='qW5000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='qW7000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCD170_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCD1000_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'
#samplename='QCD1800_710pre8_posHCAL_jetCoreTrack_clusterSplit_splitMergedNeutrals'

samplename='WW3000_711_splitMergedNeutrals_PU40'
#samplename='WW3000_711_jetCoreTrack_splitMergedNeutrals_PU40'
#samplename='WW3000_711_jetCoreTrack_clusterSplit_splitMergedNeutrals_PU40'
#samplename='WW3000_711_splitMergedNeutrals'
#samplename='WW3000_711_jetCoreTrack_splitMergedNeutrals'
#samplename='WW3000_711_jetCoreTrack_clusterSplit_splitMergedNeutrals'

process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:///opt2/rootfiles/run_reco_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_'+samplename+'.root')
)

print 'input:', process.source.fileNames

print 'runOnMC:', runOnMC

process.load("Ntuples.substructure.ntuple_cfi")

#process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.MixingModule.mix_2012_Summer_50ns_PoissonOOTPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

GT = None
if runOnMC:
#    GT = 'START53_V15::All' # for Summer12 MC
    GT = 'START53_V23::All' # for Summer12 MC with ReReco data
else:
#    GT = 'GR_P_V39_AN3::All' # for Moriond data
    GT = 'FT_53_V21_AN4::All' # for Jan22ReReco data
process.GlobalTag.globaltag = GT

#### PF NO PU

process.load("RecoParticleFlow.PFProducer.pfLinker_cff")
process.load("CommonTools.ParticleFlow.pfNoPileUp_cff")

# note pfPileUp modified according to JetMET's recommendations
process.pfPileUp.checkClosestZVertex = False
process.pfPileUp.Vertices = 'goodOfflinePrimaryVertices'
process.pfPileUp.PFCandidates = 'particleFlowPtrs'
process.pfNoPileUp.bottomCollection = 'particleFlowPtrs'

process.load("CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi")
process.pfNoPileUpSequence.insert(0, process.goodOfflinePrimaryVertices)

process.PATCMGPileUpSubtractionSequence = cms.Sequence(
    process.particleFlowPtrs +
    process.pfNoPileUpSequence
    )

#### Adding CA8 jets and CA8 pruned jets

process.load("Ntuples.substructure.PAT_ca8jets_cff")
if not True:
    process.patJetsCA8CHS.addBTagInfo=False
    process.patJetsCA8CHS.addDiscriminators=False
    process.PATCMGJetSequenceCA8CHS.remove(process.btaggingCA8CHS)
    process.patJetsCA8CHSpruned.addBTagInfo=False
    process.patJetsCA8CHSpruned.addDiscriminators=False
    process.PATCMGJetSequenceCA8CHSpruned.remove(process.btaggingCA8CHSpruned)
    process.patJetsCA8CHSprunedSubjets.addBTagInfo=False
    process.patJetsCA8CHSprunedSubjets.addDiscriminators=False
    process.PATCMGJetSequenceCA8CHSpruned.remove(process.btaggingCA8CHSprunedSubjets)
    process.patJetsCA8CHStrimmed.addBTagInfo=False
    process.patJetsCA8CHStrimmed.addDiscriminators=False
    process.PATCMGJetSequenceCA8CHStrimmed.remove(process.btaggingCA8CHStrimmed)
if not runOnMC:
    process.PATCMGJetSequenceCA8CHS.remove( process.jetMCSequenceCA8CHS )
    process.patJetsCA8CHS.addGenJetMatch = False
    process.patJetsCA8CHS.addGenPartonMatch = False
    process.patJetCorrFactorsCA8CHS.levels.append('L2L3Residual')
    process.PATCMGJetSequenceCA8CHSpruned.remove( process.jetMCSequenceCA8CHSpruned )
    process.patJetsCA8CHSpruned.addGenJetMatch = False
    process.patJetsCA8CHSpruned.addGenPartonMatch = False
    process.patJetCorrFactorsCA8CHSpruned.levels.append('L2L3Residual')
    process.PATCMGJetSequenceCA8CHStrimmed.remove( process.jetMCSequenceCA8CHStrimmed )
    process.patJetsCA8CHStrimmed.addGenJetMatch = False
    process.patJetsCA8CHStrimmed.addGenPartonMatch = False
    process.patJetCorrFactorsCA8CHStrimmed.levels.append('L2L3Residual')

if not runQJets:
    process.selectedPatJetsCA8CHSwithQjets.cutoff=100000.0
else:    
    process.selectedPatJetsCA8CHSwithQjets.cutoff=400.0

###REMOVE CHS

if runNoCHS:
    process.ca8PFJetsCHS.src = cms.InputTag("particleFlow")
    process.ca8PFJetsCHSpruned.src = cms.InputTag("particleFlow")
    process.ca8PFJetsCHStrimmed.src = cms.InputTag("particleFlow")

###RUN CALO jets

if runCaloJets:
    process.ca8PFJetsCHS.src = cms.InputTag("towerMaker")
    process.ca8PFJetsCHS.srcPVs = cms.InputTag("offlinePrimaryVertices")
    process.ca8PFJetsCHS.jetType = cms.string("CaloJet")
    process.ca8PFJetsCHS.inputEtMin = cms.double(0.3)
    process.ca8PFJetsCHS.doPVCorrection = cms.bool(True)
    process.ca8PFJetsCHSpruned.src = cms.InputTag("towerMaker")
    process.ca8PFJetsCHSpruned.srcPVs = cms.InputTag("offlinePrimaryVertices")
    process.ca8PFJetsCHSpruned.jetType = cms.string("CaloJet")
    process.ca8PFJetsCHSpruned.inputEtMin = cms.double(0.3)
    process.ca8PFJetsCHSpruned.doPVCorrection = cms.bool(True)
    process.ca8PFJetsCHStrimmed.src = cms.InputTag("towerMaker")
    process.ca8PFJetsCHStrimmed.srcPVs = cms.InputTag("offlinePrimaryVertices")
    process.ca8PFJetsCHStrimmed.jetType = cms.string("CaloJet")
    process.ca8PFJetsCHStrimmed.inputEtMin = cms.double(0.3)
    process.ca8PFJetsCHStrimmed.doPVCorrection = cms.bool(True)

##### Sequence

print 'Global tag       : ', process.GlobalTag.globaltag

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree2 = cms.EDAnalyzer("ParticleTreeDrawer",
                                   src = cms.InputTag("genParticles"),                                                                 
                                   printP4 = cms.untracked.bool(False),
                                   printPtEtaPhi = cms.untracked.bool(False),
                                   printVertex = cms.untracked.bool(False),
                                   printStatus = cms.untracked.bool(False),
                                   printIndex = cms.untracked.bool(False),
                                   status = cms.untracked.vint32( -1 )
                                   )
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(1),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("genParticles")
)
process.gen_print = cms.Path(process.printTree)

process.p = cms.Path()
process.schedule = cms.Schedule(process.gen_print,process.p)

process.tnmc1 = cms.Sequence(process.PATCMGPileUpSubtractionSequence)
if runCA8jets:
    process.tnmc1 += process.PATCMGJetSequenceCA8CHS+process.PATCMGJetSequenceCA8CHSpruned+process.selectedPatJetsCA8CHSwithNsub #+process.selectedPatJetsCA8CHSwithQjets
if runTrimmedCA8jets:
    process.tnmc1 += process.PATCMGJetSequenceCA8CHStrimmed
process.tnmc1 += process.demo
process.p += process.tnmc1

#### evaluate speed

#print 'Fastjet instances (dominating our processing time...):'
#from CMGTools.Common.Tools.visitorUtils import SeqVisitor
#v = SeqVisitor('FastjetJetProducer')
#process.p.visit(v)

if writePatTuple:
  process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('/tmp/hinzmann/patTuple_'+samplename+'.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save PAT Layer 1 output; you need a '*' to
                               # unpack the list of commands 'patEventContent'
                               outputCommands = cms.untracked.vstring('keep *')
                               )
  process.outpath = cms.EndPath(process.out)
  process.schedule.append(process.outpath)

process.demo.ntupleName=cms.untracked.string('/opt2/rootfiles/ntuple_'+samplename+'.root')
