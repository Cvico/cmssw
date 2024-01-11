""" Basic cmsRun file for running shower code """
import FWCore.ParameterSet.Config as cms

process = cms.Process("DTTrigPhase2ShowerProd")

process.load('Configuration.Geometry.GeometryExtended2026D49Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2026D49_cff')
process.load("L1Trigger.DTTriggerPhase2.dtTriggerPhase2Showers_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')
process.load("L1Trigger.DTTriggerPhase2.CalibratedDigis_cfi")
process.load("L1Trigger.DTTriggerPhase2.dtTriggerPhase2PrimitiveDigis_cfi")

process.CalibratedDigis.dtDigiTag = "simMuonDTDigis"
process.CalibratedDigis.scenario = 0

# Producer
process.dtTriggerPhase2Showers = process.dtTriggerPhase2Shower.clone()


process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                'root://xrootd-cms.infn.it//store/mc/Phase2HLTTDRWinter20DIGI/ZprimeToMuMu_M-6000_TuneCP5_14TeV-pythia8/GEN-SIM-DIGI-RAW/PU200_110X_mcRun4_realistic_v3-v2/40000/00E449AC-F2F5-BD49-9230-DF997178F38F.root',                            
    )
)
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))

# Configure debugging 
#process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.threshold = "DEBUG"
#process.MessageLogger.debugModules = ["DTTrigPhase2ShowerProd"]
####################### SliceTest specials ##############################
process.out = cms.OutputModule("PoolOutputModule",
                               outputCommands = cms.untracked.vstring(
                                   'drop *',
                                   'keep *_CalibratedDigis_*_*',
                                   'keep *_dtTriggerPhase2Showers_*_*',
                                   'keep *_genParticles_*_*',
                               ),
                               fileName = cms.untracked.string('DTTriggerPhase2Shower.root')
)

process.p = cms.Path(process.CalibratedDigis *
                     process.dtTriggerPhase2Showers
)

process.this_is_the_end = cms.EndPath(process.out)
