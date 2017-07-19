import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_1/170624_222405/0000/outputScoutingCalo_9.root',
  #  )
#)


import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('out.txt') 
#mylist = FileUtils.loadListFromFile ('newfile_July15.txt') 
readFiles = cms.untracked.vstring( *mylist)
process.source = cms.Source('PoolSource', fileNames = readFiles)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutput.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

process.demo = cms.EDAnalyzer('DimuonScoutingAnalyzer',
     triggerResultsScouting  = cms.InputTag("TriggerResults", "", "TEST"),
     triggerResults          = cms.InputTag("TriggerResults", "", "HLT"),
     muons                   = cms.InputTag("hltScoutingMuonPackerCalo", "", "TEST"),
     primaryVtx              = cms.InputTag("hltScoutingPrimaryVertexPacker",   "primaryVtx",     "TEST"),
     displacedVtx            = cms.InputTag("hltScoutingMuonPackerCalo",   "displacedVtx",   "TEST"),
)


process.p = cms.Path(process.demo)
