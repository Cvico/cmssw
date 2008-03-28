import FWCore.ParameterSet.Config as cms

process = cms.Process("test")
process.source = cms.Source("FragmentInput")

process.out = cms.EDFilter("EventStreamFileWriter",
    streamLabel = cms.string('A'),
    max_queue_depth = cms.untracked.int32(5),
    maxSize = cms.int32(1000000000),
    compression_level = cms.untracked.int32(1),
    use_compression = cms.untracked.bool(False),
    max_event_size = cms.untracked.int32(7000000)
)

process.e1 = cms.EndPath(process.out)

