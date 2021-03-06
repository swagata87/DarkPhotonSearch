import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.load('PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.load("EventFilter.L1TRawToDigi.gtStage2Digis_cfi")
process.gtStage2Digis.InputLabel = cms.InputTag( "hltFEDSelectorL1" )

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_HLT_v7', '') 
process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v9', '') 


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:ZEE_13TeV_TuneCUETP8M1_AODSIM.root'
#        '/store/data/Run2017C/JetHT/MINIAOD/PromptReco-v3/000/300/742/00000/266BB971-8B7E-E711-A675-02163E01A5A5.root'
#        '/store/data/Run2017D/ParkingScoutingMonitor/MINIAOD/PromptReco-v1/000/302/031/00000/008A8AFA-458F-E711-91B9-02163E011CF7.root',
#        '/store/data/Run2017D/ParkingScoutingMonitor/MINIAOD/PromptReco-v1/000/302/031/00000/24AC007E-3D8F-E711-B81E-02163E019B45.root'
#        '/store/user/swmukher/crab_Trig_Sep26_v2/HLTPhysics/Trig_Sep26_v2/170926_103547/0000/outputScoutingCaloMuon_100.root',
#        '/store/data/Run2017D/ScoutingCaloMuon/RAW/v1/000/302/031/00000/301F9B4E-648D-E711-8480-02163E012748.root'
#        '/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/300/817/00000/8857569C-A37D-E711-8D2C-02163E019C2E.root'
#        '/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/300/079/00000/5474DB72-1374-E711-B0E1-02163E01A582.root',
#        '/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/300/106/00000/B212F1F5-5A74-E711-B42F-02163E0135FC.root',
    )
)


#import FWCore.Utilities.FileUtils as FileUtils
#mylist = FileUtils.loadListFromFile ('mu_out.txt') 
#mylist = FileUtils.loadListFromFile ('newfile_July15.txt') 
#readFiles = cms.untracked.vstring( *mylist)
#process.source = cms.Source('PoolSource', fileNames = readFiles)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutput.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

process.demo = cms.EDAnalyzer('DimuonScoutingAnalyzer',
    RunOnOfflineReco_        = cms.bool(True),
#    RunOnOfflineReco_        = cms.bool(False),
#    triggerResultsScouting  = cms.InputTag("TriggerResults", "", "HLT"),
    triggerResults          = cms.InputTag("TriggerResults", "", "HLT"),
    objectsScouting = cms.InputTag("slimmedPatTrigger"),
    muonsScouting           = cms.InputTag("hltScoutingMuonPackerCalo", "", "HLT"),
    muons                   = cms.InputTag("slimmedMuons"),
    primaryVtx              = cms.InputTag("offlineSlimmedPrimaryVertices"),
    primaryVtxScouting      = cms.InputTag("hltScoutingPrimaryVertexPackerCaloMuon",   "primaryVtx",     "HLT"),
    displacedVtx            = cms.InputTag("hltScoutingMuonPackerCalo",   "displacedVtx",   "HLT"),
    AlgInputTag             = cms.InputTag("gtStage2Digis"),
    l1tAlgBlkInputTag       = cms.InputTag("gtStage2Digis"),
    l1tExtBlkInputTag       = cms.InputTag("gtStage2Digis"),
    l1Seeds                 = cms.vstring('L1_DoubleMu_12_5', 'L1_DoubleMu_12_8', 'L1_DoubleMu_13_6', 'L1_DoubleMu_15_5', 'L1_DoubleMu_15_7', 'L1_DoubleMu18er2p1', 'L1_DoubleMu22er2p1', 'L1_TripleMu_4_4_4', 'L1_TripleMu_5_0_0', 'L1_TripleMu_5_3_3', 'L1_TripleMu_5_5_3', 'L1_QuadMu0', 'L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4', 'L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18', 'L1_DoubleMu4_SQ_OS_dR_Max1p2', 'L1_DoubleMu5_SQ_OS_Mass7to18', 'L1_DoubleMu_20_2_SQ_Mass_Max20', 'L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4', 'L1_DoubleMu4p5_SQ_OS_dR_Max1p2', 'L1_DoubleMu6_SQ_OS')

)


process.p = cms.Path(process.demo)
