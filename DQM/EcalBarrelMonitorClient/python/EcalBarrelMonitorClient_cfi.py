import FWCore.ParameterSet.Config as cms

ecalBarrelMonitorClient = cms.EDFilter("EcalBarrelMonitorClient",
    dbPassword = cms.untracked.string(''),
    verbose = cms.untracked.bool(False),
    hostName = cms.untracked.string('localhost'),
    maskFile = cms.untracked.string('maskfile.dat'),
    inputFile = cms.untracked.string(''),
    dbRefreshTime = cms.untracked.int32(15),
    mergeRuns = cms.untracked.bool(False),
    enableUpdate = cms.untracked.bool(False),
    enabledClients = cms.untracked.vstring('Integrity', 'StatusFlags', 'Occupancy', 'PedestalOnline', 'Pedestal', 'TestPulse', 'Laser', 'Timing', 'Cosmic', 'BeamCalo', 'BeamHodo', 'Summary'),
    enableCleanup = cms.untracked.bool(False),
    superModules = cms.untracked.vint32(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36),
    location = cms.untracked.string(''),
    enableSubRunHtml = cms.untracked.bool(False),
    dbHostPort = cms.untracked.int32(1521),
    dbUserName = cms.untracked.string(''),
    htmlRefreshTime = cms.untracked.int32(5),
    hostPort = cms.untracked.int32(9090),
    cloneME = cms.untracked.bool(True),
    baseHtmlDir = cms.untracked.string(''),
    enableMonitorDaemon = cms.untracked.bool(False),
    enableSubRunDb = cms.untracked.bool(False),
    dbName = cms.untracked.string(''),
    clientName = cms.untracked.string('EcalBarrelMonitorClient'),
    dbHostName = cms.untracked.string('')
)


