import FWCore.ParameterSet.Config as cms

from ElectroWeakAnalysis.ZReco.zToMuMuSequences_cff import *
from ElectroWeakAnalysis.ZReco.zToMuMuHLTFilter_cfi import *
from ElectroWeakAnalysis.ZReco.goodZToMuMuFilter_cfi import *
from ElectroWeakAnalysis.ZReco.goodZToMuMuOneTrackFilter_cfi import *
from ElectroWeakAnalysis.ZReco.goodZToMuMuOneStandAloneMuonTrackFilter_cfi import *
zToMuMuPath = cms.Path(zToMuMuHLTFilter+goodMuonRecoForZToMuMu+goodZToMuMu+goodZToMuMuFilter)
zToMuMuOneTrackPath = cms.Path(zToMuMuHLTFilter+goodMuonRecoForZToMuMu+goodZToMuMuOneTrack+goodZToMuMuOneTrackFilter)
zToMuMuOneStandAloneMuonTrackPath = cms.Path(zToMuMuHLTFilter+goodMuonRecoForZToMuMu+goodZToMuMuOneStandAloneMuonTrack+goodZToMuMuOneStandAloneMuonTrackFilter)
zToMuMuMCTruth = cms.Path(zToMuMuHLTFilter+mcTruthForZToMuMu+mcTruthForZToMuMuOneTrack+mcTruthForZToMuMuOneStandAloneMuonTrack+goodZMCMatch)

