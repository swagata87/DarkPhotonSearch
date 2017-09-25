from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = ''
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'ConfFile_cfg.py'
config.JobType.outputFiles = ['AnalysisOutput.root']
#config.JobType.inputFiles = ['MC_pileup.root','Data_pileup_normalized.root','Data_pileup_normalized_UP.root','Data_pileup_normalized_DOWN.root', 'k_faktors_ele.root', 'k_faktors_mu.root', 'k_faktors_tau.root','METFilters_cff.py', 'qcdFakeOutput15pt_eta.root']

config.Data.inputDataset = ''
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = 'json_DCSONLY.txt'
#config.Data.lumiMask = 'Cert_294927-299649_13TeV_PromptReco_Collisions17_JSON_MuonPhys.txt'
config.Data.outLFNDirBase = '/store/user/%s/scouting_Sept4/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'scouting_Sept4'
config.Site.storageSite = 'T2_DE_RWTH'
#config.Data.ignoreLocality = True
#config.Site.whitelist = ['T2_DE_RWTH']

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'scouting_crab_projects_Sept4'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    config.General.requestName = 'ScoutingCaloMuon_Run2017C'
    config.Data.inputDataset = '/ScoutingCaloMuon/Run2017C-v1/RAW'
    config.Data.unitsPerJob = 40
    submit(config)

    config.General.requestName = 'ScoutingCaloMuon_Run2017D'
    config.Data.inputDataset = '/ScoutingCaloMuon/Run2017D-v1/RAW'
    config.Data.unitsPerJob = 20
    submit(config)

