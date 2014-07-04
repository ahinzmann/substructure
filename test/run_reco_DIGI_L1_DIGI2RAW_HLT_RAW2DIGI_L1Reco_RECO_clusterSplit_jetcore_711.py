# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: run_reco --scenario pp --conditions auto:startup --mc -s DIGI,L1,DIGI2RAW,HLT,RAW2DIGI,L1Reco,RECO --eventcontent FEVTSIM
import FWCore.ParameterSet.Config as cms

process = cms.Process('privateReRECOsplit')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('SimGeneral.MixingModule.mix_CSA14_50ns_PoissonOOTPU_cfi')
#process.load('SimGeneral.MixingModule.mix_CSA14_inTimeOnly_cfi')
#process.load('SimGeneral.MixingModule.mix_Flat_20_50_cfi')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_7_0_0_pre11/RelValQCD_Pt_3000_3500_13/GEN-SIM-RECO/POSTLS162_V4-v1/00000/1EB55025-856A-E311-A1FB-00248C55CC97.root')
)

if hasattr(process.mix,"input"):
  process.mix.input.fileNames = cms.untracked.vstring('/store/mc/Fall13/MinBias_TuneA2MB_13TeV-pythia8/GEN-SIM/POSTLS162_V1-v1/30000/F69DBDB5-8623-E311-B248-001EC9B214BB.root')
#kaputt: /store/relval/CMSSW_7_1_0_pre8/RelValMinBias_13/GEN-SIM-RECO/PRE_LS171_V9-v1/00000/82599741-4CE2-E311-B956-00248C0BE018.root

sample="WW3000"

process.source.fileNames = cms.untracked.vstring('file:///opt2/rootfiles/run_reco_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_'+sample+'_711_splitMergedNeutrals.root')

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.19 $'),
    annotation = cms.untracked.string('run_reco nevts:1'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.FEVTSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTSIMEventContent.outputCommands,
    fileName = cms.untracked.string('/opt2/rootfiles/run_reco_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_'+sample+'_711_jetCoreTrack_clusterSplit_splitMergedNeutrals.root'),#_posHCAL_fixTRACK_splitPFecal
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

# Additional output definition

process.FEVTSIMoutput.outputCommands+=["keep *_particleFlowRecHit*_*_*"]
#process.reconstruction_fromRECO.remove(process.ak5JetID)
#process.reconstruction_fromRECO.remove(process.ak7JetID)
#process.reconstruction_fromRECO.remove(process.ic5JetID)

#process.particleFlowClusterHCAL.nNeighbours=0
#process.particleFlowClusterHCAL.showerSigma=8
#process.particleFlowClusterHCAL.posCalcNCrystal=-1
#process.particleFlowClusterECAL.posCalcNCrystal=-1

#process.particleFlowClusterHCAL.pfClusterBuilder.positionCalc.posCalcNCrystals=-1

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')
#process.GlobalTag = "PRE_LS171_V9::All"


process.siPixelClusters = cms.EDProducer("JetCoreClusterSplitter",
    pixelClusters         = cms.InputTag("siPixelClusters","","privateReRECO"),
    vertices              = cms.InputTag('offlinePrimaryVertices',"","privateReRECO"),
    pixelCPE = cms.string( "PixelCPEGeneric" ),
    verbose     = cms.bool(False),

    )

process.IdealsiPixelClusters = cms.EDProducer(
    "TrackClusterSplitter",
    stripClusters         = cms.InputTag("siStripClusters","","privateReRECO"),
    pixelClusters         = cms.InputTag("siPixelClusters","","privateReRECO"),
    useTrajectories       = cms.bool(False),
    trajTrackAssociations = cms.InputTag('generalTracks'),
    tracks                = cms.InputTag('pixelTracks'),
    propagator            = cms.string('AnalyticalPropagator'),
    vertices              = cms.InputTag('pixelVertices'),
    simSplitPixel         = cms.bool(True), # ideal pixel splitting turned OFF
    simSplitStrip         = cms.bool(False), # ideal strip splitting turned OFF
    tmpSplitPixel         = cms.bool(False), # template pixel spliting
    tmpSplitStrip         = cms.bool(False), # template strip splitting
    useStraightTracks     = cms.bool(True),
    test     = cms.bool(True)
    )

process.clusterSplit = cms.Path(process.IdealsiPixelClusters*process.siPixelClusters*process.MeasurementTrackerEvent* process.siPixelClusterShapeCache+process.siPixelRecHits+process.siStripMatchedRecHits+process.ckftracks_wodEdX+process.offlinePrimaryVertices)

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTSIMoutput_step = cms.EndPath(process.FEVTSIMoutput)

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

# Schedule definition
process.schedule = cms.Schedule(process.gen_print,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.clusterSplit,process.reconstruction_step,process.endjob_step,process.FEVTSIMoutput_step])

#process.mix.mixObjects.mixCH.input.remove(cms.InputTag("g4SimHits","CastorFI"))
#process.mix.mixObjects.mixCH.subdets.remove("CastorFI")
#print process.mix.mixObjects.mixCH
#del process.mix.digitizers.castor
#print process.mix.digitizers
#del process.simCastorDigis
#process.digi2raw_step.remove(process.castorRawData)

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
