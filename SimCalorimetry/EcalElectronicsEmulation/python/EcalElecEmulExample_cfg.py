import FWCore.ParameterSet.Config as cms

process = cms.Process("EcalSimRawData")
#
#
#
# Digitization
#
process.load("Configuration.StandardSequences.Digi_cff")

process.load("Configuration.StandardSequences.MixingNoPileUp_cff")

# TPG: defines the ecalTriggerPrimitiveDigis module
process.load("SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_cfi")

#
#
#
# Simulation of raw data. Defines the ecalSimRawData module:
#
process.load("SimCalorimetry.EcalElectronicsEmulation.EcalSimRawData_cfi")

# Set ecalSimRawData.unsuppressedDigiProducer to "source" if the digis
# are produced by the EcalSimpleSource module, keep the default value
# otherwise:
#replace ecalSimRawData.unsuppressedDigiProducer = "source"
# Set ecalSimRawData.trigPrimProducer to "source" if the TP digis
# are produced by the EcalSimpleSource module, keep the default value
# otherwise:
#replace ecalSimRawData.trigPrimProducer = "source"
#
#
#
# Geometry
#
process.load("Geometry.CMSCommonData.cmsSimIdealGeometryXML_cfi")

# Calo geometry service model
process.load("Geometry.CaloEventSetup.CaloGeometry_cff")

# Description of EE trigger tower map
process.load("Geometry.CaloEventSetup.EcalTrigTowerConstituents_cfi")

process.source = cms.Source("EcalSimpleSource",
    # number of events to generate:
    maxEvents = cms.untracked.int32(1),
    #xtal channel digis. Set to empty string for no digis.
    # some realistic shape. Gain 12 (ID=1, see 1<<12). Every crystals with a 
    # 160 ADC count amplitude above a 200 ADC count baseline. 
    # string formula = "min(4095.,200+160.*((isample0==3)*.01+(isample0==4)*.76+(isample0==5)*1.+(isample0==6)*.89+(isample0==7)*.67+(isample0==8)*.47+(isample0==9)*.32))+1<<12"
    formula = cms.string(''),
    # sim hits. Set to empty string for no sim hit.
    # Pattern example with energy set to (eta index in EB)*10MeV in first event 
    # and then incremented by 10MeV at each event:
    simHitFormula = cms.string('(ieta0+ievt0)/100.'),
    #TT samples. Set to empy string for no TP digis.
    #  TT sample format:
    #        | 10 |    9 - 0    |
    #        |fgvb|      Et     |
    # Pattern example with energy set to TT id within SM in first event and then 
    # incremented at each event:
    # string tpFormula = "max(1023, itt0+ievt0)"
    tpFormula = cms.string(''),
    #verbosity switch:
    verbose = cms.untracked.bool(False)
)

process.EcalTrivialConditionRetriever = cms.ESSource("EcalTrivialConditionRetriever")

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('file:toto.root')
)

process.p = cms.Path(process.mix*process.ecalUnsuppressedDigis*process.ecalTriggerPrimitiveDigis*process.ecalDigis*process.ecalSimRawData)
process.fine = cms.EndPath(process.out)
process.ecalTriggerPrimitiveDigis.Label = 'ecalUnsuppressedDigis'
process.ecalTriggerPrimitiveDigis.InstanceEB = ''
process.ecalTriggerPrimitiveDigis.InstanceEE = ''
process.ecalTriggerPrimitiveDigis.TcpOutput = True
process.ecalDigis.dumpFlags = 10
process.ecalDigis.trigPrimBypass = False
process.ecalDigis.writeSrFlags = True

