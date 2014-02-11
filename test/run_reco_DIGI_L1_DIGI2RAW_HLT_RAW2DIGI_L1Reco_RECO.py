# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: run_reco --scenario pp --conditions auto:startup --mc -s DIGI,L1,DIGI2RAW,HLT,RAW2DIGI,L1Reco,RECO --eventcontent FEVTSIM
import FWCore.ParameterSet.Config as cms

process = cms.Process('privateReRECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
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
    input = cms.untracked.int32(5000)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_7_0_0_pre11/RelValQCD_Pt_3000_3500_13/GEN-SIM-RECO/POSTLS162_V4-v1/00000/1EB55025-856A-E311-A1FB-00248C55CC97.root')
)

sample="ZpTT"
#folder="file:///tmp/hinzmann/"

if sample=="ZTT":
  folder="/store/relval/CMSSW_7_0_0_pre11/RelValZTT_13/GEN-SIM-RECO/PU25ns_POSTLS162_V4-v1/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'327688C1-726A-E311-8124-003048F1C9F2.root',
folder+'38ED2AB0-736A-E311-9A5D-0025B32038DC.root',
folder+'3ED0B219-766A-E311-BD32-003048F236DC.root',
folder+'3EFC33B5-736A-E311-A0BE-02163E00E7C6.root',
folder+'4A6DCBC3-736A-E311-95D4-003048F23838.root',
folder+'56333D67-786A-E311-BC06-003048F17C08.root',
folder+'580088E4-776A-E311-91F3-C860001BD92A.root',
folder+'6A9E1005-796A-E311-9971-0025901D6258.root',
folder+'70943058-786A-E311-86B1-002590494CA4.root',
folder+'745D69D7-706A-E311-8337-02163E00E692.root',
folder+'7C49294E-736A-E311-B331-00304894528A.root',
folder+'880425DA-746A-E311-9559-003048D3738C.root',
folder+'885681C7-796A-E311-A73A-0025901D5D92.root',
folder+'8ACE7A55-786A-E311-9DF8-02163E0079B7.root',
folder+'90C10665-706A-E311-A9C8-0025904952A4.root',
folder+'AEB54C0C-7B6A-E311-ADA8-001D09F2441B.root',
folder+'C8E900A0-716A-E311-82C2-02163E00E5E6.root',
folder+'CC2E511D-746A-E311-8A78-02163E00CF57.root',
folder+'CE30ADA9-736A-E311-850C-003048CF6552.root',
folder+'DCD1158E-776A-E311-B2DD-0025904B2CA8.root',
folder+'EC15C53E-736A-E311-B8D6-02163E00CBE8.root',
folder+'F0FB8616-726A-E311-8119-003048F239A2.root',
    )

if sample=="ZpTT":
  folder="/store/relval/CMSSW_7_0_0_pre11/RelValZpTT_1500_13TeV_Tauola/GEN-SIM-RECO/POSTLS162_V4-v1/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'08EDE771-7F6A-E311-AADF-0025905938A4.root',
folder+'2C03F793-876A-E311-BA10-002590596486.root',
folder+'3E5A47FD-8C6A-E311-9035-0026189438E2.root',
folder+'5E67A448-A86A-E311-98D6-0026189438CB.root',
folder+'70112499-856A-E311-955B-0025905A612E.root',
folder+'B27C438C-7A6A-E311-B0CB-0025905A610A.root',
folder+'D682693D-7E6A-E311-BD44-00261894398A.root',
folder+'F201E290-856A-E311-A68B-0025905964A6.root',  
    )

if sample=="WW3000":
  folder="/store/mc/Fall13/RSGravitonToWW_kMpl01_M_3000_Tune4C_13TeV_pythia8/GEN-SIM/POSTLS162_V1-v4/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'0ED92407-C35D-E311-80F0-20CF3027A589.root',
folder+'1AFBC5FF-C35D-E311-BD9B-003048F1B856.root',
folder+'2269868F-BC5D-E311-A07C-008CFA064704.root',
folder+'22B4F037-235D-E311-B9BF-6C3BE5B59058.root',
folder+'24316AF7-C45D-E311-B2F5-002590CB0B5A.root',
folder+'243B9A46-235D-E311-8D49-00145E551FF1.root',
folder+'360085A1-C45D-E311-93E5-B499BAABFEB0.root',
folder+'3AA5E551-BA5D-E311-9D88-782BCB20E908.root',
folder+'52998912-225D-E311-B06C-1CC1DE046F18.root',
folder+'56935D85-1D5E-E311-98D0-782BCB27F1F0.root',
folder+'5C528FE2-C45D-E311-818D-001E0B8D198C.root',
folder+'5CD9D769-235D-E311-8BB6-00266CFCCDC8.root',
folder+'62B0BF45-235D-E311-91F5-6C3BE5B50210.root',
#folder+'740EA51F-B75D-E311-A3DB-0025904C51FC.root',
#folder+'76E27D98-0C5E-E311-8064-0025904C6378.root',
#folder+'7C94C73F-235D-E311-9C03-20CF3019DF02.root',
folder+'7E5D25A2-C45D-E311-A9E0-485B39897212.root',
folder+'865D8E58-2F5D-E311-BA5D-00145E551712.root',
folder+'86E34F0E-235D-E311-8477-D4AE526DF000.root',
folder+'8A87FEF0-C55D-E311-875B-008CFA110C78.root',
folder+'8E5C1B34-245D-E311-A16B-001E4F33E1FD.root',
folder+'922ADD77-C45D-E311-A5E2-1CC1DE1CF610.root',
folder+'9E6C1EEE-235D-E311-BBA1-002590D60004.root',
folder+'A28D842E-B75D-E311-8D3C-00266CFFBDE8.root',
folder+'AECAD5E1-235D-E311-9544-00221982B6B6.root',
folder+'BE46A914-235D-E311-A8DE-001EC94BFFEB.root',
folder+'DE113665-285D-E311-A103-003048F5ADEC.root',
folder+'E606204E-6361-E311-8532-E0CB4E4408CB.root',
folder+'ECC01321-225D-E311-AA52-1CC1DE04FF50.root',
folder+'FC007F61-265D-E311-865E-003048F5B2A8.root',
    )

if sample=="QCD30":
  folder="/store/mc/Fall13/QCD_Pt-30to50_Tune4C_13TeV_pythia8/GEN-SIM/POSTLS162_V1_castor-v1/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'0030AD86-E152-E311-BCE8-0025907B4FC0.root',
folder+'0042E5FD-CC5A-E311-B27D-003048F5ADF8.root',
folder+'00819D6C-CB5A-E311-A913-B499BAAC0414.root',
folder+'008FB199-5054-E311-8C56-00259081ED0A.root',
folder+'00E761A1-B75A-E311-9BD5-001E4F32EAA2.root',
folder+'022B5AF4-B25A-E311-B3F0-0025907DE22C.root',
folder+'0236D05B-CF5A-E311-82E3-0025901D08E8.root',
folder+'02764B1D-3154-E311-B718-D48564456546.root',
folder+'027FFCB6-6F53-E311-A6E3-1CC1DE0570A0.root',
folder+'02AC72BC-555B-E311-A40F-20CF3019DEFF.root',
folder+'02CCE46C-BE5A-E311-9427-003048F1795E.root',
folder+'02F78251-1C54-E311-9EF6-003048C57350.root',
folder+'0475D684-BE5A-E311-BC97-0025904B5B6E.root',
folder+'04A665B8-8455-E311-A8A8-0002C90A363A.root',
folder+'04B1E28D-C75A-E311-B413-0025905746AA.root',
folder+'04B22D85-CF5A-E311-B02B-90B11C2C93B1.root',
folder+'060CC08A-B35A-E311-BF7E-0025907D1FC4.root',
folder+'0613DAA5-BD5A-E311-AD4A-003048FE9C68.root',
folder+'0654018A-CB5A-E311-803A-6C3BE5B50180.root',
folder+'0654B67B-E152-E311-9AF7-20CF305616DC.root',
folder+'06C0C436-AF54-E311-955D-001E6739AB19.root',
folder+'06D6D28E-BE5A-E311-BDD7-02163E00B774.root',
folder+'08449677-E152-E311-A6C9-002590D0AF74.root',
folder+'08681A72-BE5A-E311-B5B8-002590494D62.root',
folder+'0A2A63FE-3054-E311-8167-984BE164408A.root',
folder+'0A3BE407-205B-E311-85E8-0026B9FA95D0.root',
folder+'0A4E55AA-C75A-E311-8663-002590574704.root',
folder+'0A5F1B0E-4354-E311-99F5-00259082115C.root',
folder+'0C15D373-CB5A-E311-9B0A-001F29071CFA.root',
folder+'0C5B7A67-4154-E311-81E5-009C02AABB60.root',
folder+'0C61306F-4B54-E311-9DA0-00266CF95844.root',
folder+'0C68E7E1-BE5A-E311-9BD7-003048FEB91E.root',
folder+'0C82FBCC-D25A-E311-91F1-6805CA08539F.root',
folder+'0C994D52-CB5A-E311-8F61-001CC47B602C.root',
folder+'0CA09D62-AF5A-E311-8B87-008CFA1983BC.root',
folder+'0CE785D9-BD5A-E311-88CE-003048F1C9DA.root',
folder+'0CF4F27F-CF5A-E311-A6E5-00259084A6C4.root',
folder+'0CFADD90-CD5A-E311-80D6-90B11C26815E.root',
folder+'0E078713-1C54-E311-89E7-0025904CF976.root',
folder+'0E148B9A-BE5A-E311-8E67-02163E008DAE.root',
folder+'0E20F4CE-1654-E311-B7B8-D8D385AF889C.root',
)


if sample=="QCD170":
  folder="/store/mc/Fall13/QCD_Pt-170to300_Tune4C_13TeV_pythia8/GEN-SIM/POSTLS162_V1_castor-v1/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'001AA63A-475B-E311-89AA-002590D60026.root',
folder+'0040B566-B45A-E311-A194-90B11CBCFFF7.root',
folder+'0252DBBD-7855-E311-BCDD-00074305CAF5.root',
folder+'02687181-B85A-E311-9C74-D48564591BF4.root',
folder+'02DAD2F0-6754-E311-9284-FA163EF07CBA.root',
folder+'02FB5B20-7955-E311-9279-0002C94CD11C.root',
folder+'044F1C68-CA5A-E311-A668-001B219D5C26.root',
folder+'0471C199-1954-E311-B798-002219826F40.root',
folder+'04C31980-B45A-E311-B35A-002481DE4932.root',
folder+'04DA7EBA-7B55-E311-B3D3-0002C94DBAD4.root',
folder+'0621608C-C05A-E311-B2FC-6C3BE5B5F0A0.root',
folder+'064C4F15-BE5A-E311-AE22-0025905746C8.root',
folder+'064D37FF-7755-E311-819B-00266CFCC364.root',
folder+'08245EDF-3954-E311-9594-0025901D48AA.root',
folder+'08B557B3-3F54-E311-8B6B-001E67399E89.root',
folder+'0A36BF0D-6954-E311-B0BC-FA163E2C965A.root',
folder+'0A436B29-C05A-E311-A7B5-6C3BE5B5A038.root',
folder+'0A63CADC-BF5A-E311-A19F-6C3BE5B59210.root',
folder+'0C1772B9-C65A-E311-95F6-003048F5ADF6.root',
folder+'0C2C0618-0F5B-E311-A0B9-00266CF83E54.root',
folder+'0C60FFAB-C65A-E311-9F3D-002590488694.root',
folder+'0C87FE4D-3254-E311-8812-0025904C7F5C.root',
folder+'0C8E8EEA-105B-E311-9208-7845C4FAEFE9.root',
folder+'0E0FF720-6F53-E311-81AD-1CC1DE051118.root',
folder+'0E2A6968-C05A-E311-A703-6C3BE5B513E0.root',
folder+'0E3C62C9-BD5A-E311-9D37-00259057451E.root',
folder+'0E5F91C4-7F55-E311-81D6-00074305CCC9.root',
folder+'0ED6F735-4B54-E311-8B7F-002590C1946A.root',
folder+'0EF85506-C75A-E311-9350-90B11C2AAEEC.root',
folder+'10372801-7855-E311-A1BC-008CFA0A5740.root',
folder+'10AB779B-1654-E311-97DC-003048C56E40.root',
folder+'1207FE08-6A54-E311-818F-FA163E6A3031.root',
folder+'12132BED-0E5B-E311-B821-24B6FDFFBB7F.root',
folder+'12242765-C65A-E311-AA6E-90B11C2AAEEC.root',
folder+'126D33E3-1C54-E311-8DEC-1CC1DE192802.root',
folder+'12ABFD39-4054-E311-8250-001E6739BC09.root',
folder+'14462C00-1D54-E311-872E-D4AE526A0B03.root',
folder+'147149E3-6A53-E311-AD88-D8D385FF1946.root',
folder+'149C2C4D-7D55-E311-B11E-0002C90A3700.root',
folder+'14A06DCD-C65A-E311-B08E-003048344A90.root',
)


if sample=="QCD1000":
  folder="/store/mc/Fall13/QCD_Pt-1000to1400_Tune4C_13TeV_pythia8/GEN-SIM/POSTLS162_V1_castor-v1/00000/"
  process.source.fileNames = cms.untracked.vstring(
folder+'002AE203-F452-E311-9837-0002C94D5648.root',
folder+'004D5E7B-0A53-E311-BA6C-0025901D5DFA.root',
folder+'00A4AFFE-E352-E311-8A43-D485644C2C1F.root',
folder+'00B5BB1F-0A53-E311-8504-003048F16F9C.root',
folder+'00D8C3A4-E152-E311-A5DF-001EC9B48C29.root',
folder+'00E5EC7C-E752-E311-B105-0002C9560E26.root',
folder+'020E3924-E252-E311-9909-002590488694.root',
folder+'02581B25-E252-E311-992A-0023AEFDE6C0.root',
folder+'025C1644-E252-E311-9B73-02163E00DF8C.root',
folder+'02D8A5FE-7F53-E311-A909-78E7D165F328.root',
folder+'04366C67-E752-E311-BFA4-0002C94D5610.root',
folder+'04758BA5-FF52-E311-97F5-0002C94D5522.root',
folder+'04C99D10-EF5A-E311-930E-848F69FBC0FD.root',
folder+'04FE85E0-E152-E311-AD80-002481CFE80A.root',
folder+'0651F11A-E252-E311-9252-FA163EB39272.root',
folder+'067A256B-E452-E311-A5B1-001E6724807F.root',
folder+'06947300-E252-E311-9B6B-BCAEC53296F4.root',
folder+'06DA980C-E352-E311-8C32-1CC1DE051060.root',
folder+'06DE3FD6-E152-E311-885F-0026B92E0ED7.root',
folder+'06EDE700-E252-E311-8F22-0025904AC2CA.root',
folder+'06FF04FA-E152-E311-8DAE-0025901D08E6.root',
folder+'08029C62-E252-E311-811E-002590494E46.root',
folder+'083EFCA8-EB52-E311-B476-0002C94DBB0C.root',
folder+'0855C4AA-E252-E311-A115-0002C90C5AC0.root',
folder+'08592A87-E252-E311-A2C3-003048FEC15C.root',
folder+'085D2ED0-E152-E311-A0F9-002481DE48D8.root',
folder+'087F6AA3-E252-E311-B847-D485644C8B33.root',
folder+'08A25C32-E952-E311-B0F1-0002C94CD150.root',
folder+'08BDD3E3-E152-E311-89DB-001E4F33EABC.root',
folder+'08DAE1E5-E152-E311-9DF0-002481DE485A.root',
folder+'08F00E43-E252-E311-BB6F-02163E009D5A.root',
folder+'0A1ED72C-E252-E311-A9C9-0023AEFDE9DC.root',
folder+'0A45BF0C-7553-E311-BD15-6805CA02F2AB.root',
folder+'0A492D97-E252-E311-B04A-002590494C40.root',
folder+'0A51C5ED-E152-E311-BEA0-02163E00CFD0.root',
folder+'0A6AC5ED-E152-E311-8380-B499BAAC0626.root',
folder+'0AAF9104-E252-E311-83E4-1CC1DE1CF44E.root',
folder+'0ACF0DD2-E652-E311-A859-0002C94D5618.root',
folder+'0AEC7DC1-E252-E311-80DA-1CC1DE0500F0.root',
folder+'0C0F25CC-E352-E311-86AC-0002C94CD31A.root',
)

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
    fileName = cms.untracked.string('/tmp/hinzmann/run_reco_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_'+sample+'_posHCAL.root'),#_posCAL_fixTRACK_noHCAL
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

# Additional output definition

process.FEVTSIMoutput.outputCommands+=["keep *_particleFlowRecHit*_*_*"]
process.reconstruction_fromRECO.remove(process.ak5JetID)
process.reconstruction_fromRECO.remove(process.ak7JetID)
process.reconstruction_fromRECO.remove(process.ic5JetID)

#process.particleFlowClusterHCAL.nNeighbours=0
process.particleFlowClusterHCAL.posCalcNCrystal=-1
#process.particleFlowClusterECAL.posCalcNCrystal=-1

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTSIMoutput_step = cms.EndPath(process.FEVTSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.FEVTSIMoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
