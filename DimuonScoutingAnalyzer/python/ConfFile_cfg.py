import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_1/170624_222405/0000/outputScoutingCalo_9.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_101.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_102.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_103.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_104.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_105.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_106.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_107.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_108.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_109.root',
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_0/170624_222346/0000/outputScoutingCalo_110.root'
    )
)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutput.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

process.demo = cms.EDAnalyzer('DimuonScoutingAnalyzer',
     triggerResults  = cms.InputTag("TriggerResults", "", "HLT"),
     muons           = cms.InputTag("hltScoutingMuonPackerCalo", "", "TEST"),
)


process.p = cms.Path(process.demo)
