// -*- C++ -*-
//
// Package:    Analyzer/DimuonScoutingAnalyzer
// Class:      DimuonScoutingAnalyzer
// 
/**\class DimuonScoutingAnalyzer DimuonScoutingAnalyzer.cc Analyzer/DimuonScoutingAnalyzer/plugins/DimuonScoutingAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Swagata Mukherjee
//         Created:  Mon, 26 Jun 2017 09:38:37 GMT
//
//


#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include <TLorentzVector.h>
#include "TH1.h"
#include "TH2.h"

class DimuonScoutingAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit DimuonScoutingAnalyzer(const edm::ParameterSet&);
  ~DimuonScoutingAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  bool trigMatched(bool,TLorentzVector,std::vector<TLorentzVector>);

  // ----------member data ---------------------------
  //  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabelScouting_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection>            triggerObjectsScouting_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabelScouting_;
  edm::EDGetTokenT<std::vector<pat::Muon>>         muonLabel_;
  edm::EDGetTokenT<reco::VertexCollection>         primaryVtxLabel_;
  edm::EDGetTokenT<ScoutingVertexCollection>       primaryVtxLabelScouting_;
  edm::EDGetTokenT<ScoutingVertexCollection>       displacedVtxLabel_;
  edm::Service<TFileService> fs;
  /*  edm::EDGetToken algToken_;
  l1t::L1TGlobalUtil *l1GtUtils_;
  std::vector<std::string> l1Seeds_;
  */
  int passNominalTrig;
  int passMonTrig;
  int passjetTrig1050;
  bool RunOnOfflineReco;
  float asym;
  double mass;
  int nDisplacedVtx;
  int nPrimaryVtx;
  double dxy1, dxy2;
  double dz1, dz2;
  double  chi2_by_ndof1, chi2_by_ndof2 ;

  TH1F* h1_check;
  
  TH1F* h1_dimuonMass_Den_1050;
  TH1F* h1_dimuonMass_Num_1050;
  TH1F* h1_dxy1_Den_1050;
  TH1F* h1_dxy1_Num_1050;
  TH1F* h1_dxy2_Den_1050;
  TH1F* h1_dxy2_Num_1050;
  TH1F* h1_dz1_Den_1050;
  TH1F* h1_dz1_Num_1050;
  TH1F* h1_dz2_Den_1050;
  TH1F* h1_dz2_Num_1050;
  TH1F* h1_dimuondR_Den_1050;
  TH1F* h1_dimuondR_Num_1050;
  TH1F*  h1_muon1_pt_Num_1050;
  TH1F*  h1_unmatched_muon1_pt_Num_1050;
  TH1F*  h1_muon2_pt_Num_1050;
  TH1F*  h1_muon1_pt_Den_1050;
  TH1F*  h1_muon2_pt_Den_1050;
  TH1F*  h1_muon1_phi_Num_1050;
  TH1F*  h1_muon2_phi_Num_1050;
  TH1F*  h1_muon1_phi_Den_1050;
  TH1F*  h1_muon2_phi_Den_1050;
  TH1F*  h1_muon1_eta_Num_1050;
  TH1F*  h1_muon2_eta_Num_1050;
  TH1F*  h1_muon1_eta_Den_1050;
  TH1F*  h1_muon2_eta_Den_1050;
  TH1F*  h1_nPV_Den_1050;
  TH1F*  h1_nPV_Num_1050;
  TH1F*  h1_nDV_Den_1050;
  TH1F*  h1_nDV_Num_1050;
  TH2F*  h2_nPV_nDV_Num_1050;
  TH2F*  h2_nPV_nDV_Den_1050;
  TH2F*  h2_pt1_pt2_Num_1050;
  TH2F*  h2_pt1_pt2_Den_1050;

  TH2F*  h2_deta_dphi_passMon_passSig;

  TH1F*  h1_muon1_chi2_by_ndof_Num_1050;
  TH1F*  h1_muon1_chi2_by_ndof_Den_1050;
  TH1F*  h1_muon2_chi2_by_ndof_Num_1050;
  TH1F*  h1_muon2_chi2_by_ndof_Den_1050;

  TH1F* h1_dimuonMass_Den_Mon;
  TH1F* h1_dimuonMass_Num_Mon;
  TH1F* h1_dxy1_Den_Mon;
  TH1F* h1_dxy1_Num_Mon;
  TH1F* h1_dxy2_Den_Mon;
  TH1F* h1_dxy2_Num_Mon;
  TH1F* h1_dz1_Den_Mon;
  TH1F* h1_dz1_Num_Mon;
  TH1F* h1_dz2_Den_Mon;
  TH1F* h1_dz2_Num_Mon;
  TH1F* h1_dimuondR_Den_Mon;
  TH1F* h1_dimuondR_Num_Mon;
  TH1F*  h1_muon1_pt_Num_Mon;
  TH1F*  h1_unmatched_muon1_pt_Num_Mon;
  TH1F*  h1_muon2_pt_Num_Mon;
  TH1F*  h1_muon1_pt_Den_Mon;
  TH1F*  h1_muon2_pt_Den_Mon;
  TH1F*  h1_muon1_phi_Num_Mon;
  TH1F*  h1_muon2_phi_Num_Mon;
  TH1F*  h1_muon1_phi_Den_Mon;
  TH1F*  h1_muon2_phi_Den_Mon;
  TH1F*  h1_muon1_eta_Num_Mon;
  TH1F*  h1_muon2_eta_Num_Mon;
  TH1F*  h1_muon1_eta_Den_Mon;
  TH1F*  h1_muon2_eta_Den_Mon;
  TH1F*  h1_nPV_Den_Mon;
  TH1F*  h1_nPV_Num_Mon;
  TH1F*  h1_nDV_Den_Mon;
  TH1F*  h1_nDV_Num_Mon;
  TH2F*  h2_nPV_nDV_Num_Mon;
  TH2F*  h2_nPV_nDV_Den_Mon;
  TH1F*  h1_muon1_chi2_by_ndof_Num_Mon;
  TH1F*  h1_muon1_chi2_by_ndof_Den_Mon;
  TH1F*  h1_muon2_chi2_by_ndof_Num_Mon;
  TH1F*  h1_muon2_chi2_by_ndof_Den_Mon;
  TH2F*  h2_pt1_pt2_Num_Mon;
  TH2F*  h2_pt1_pt2_Den_Mon;

  TH1F* h1_dimuonMass_Den_Mon_JPsi;
  TH1F* h1_dimuonMass_Num_Mon_JPsi;
  TH1F* h1_dxy2_Den_Mon_JPsi;
  TH1F* h1_dxy2_Num_Mon_JPsi;
  TH1F* h1_dxy1_Den_Mon_JPsi;
  TH1F* h1_dxy1_Num_Mon_JPsi;
  TH1F* h1_dz1_Den_Mon_JPsi;
  TH1F* h1_dz1_Num_Mon_JPsi;
  TH1F* h1_dz2_Den_Mon_JPsi;
  TH1F* h1_dz2_Num_Mon_JPsi;
  TH1F* h1_dimuondR_Den_Mon_JPsi;
  TH1F* h1_dimuondR_Num_Mon_JPsi;
  TH1F*  h1_muon1_pt_Num_Mon_JPsi;
  TH1F*  h1_unmatched_muon1_pt_Num_Mon_JPsi;
  TH1F*  h1_muon2_pt_Num_Mon_JPsi;
  TH1F*  h1_muon1_pt_Den_Mon_JPsi;
  TH1F*  h1_muon2_pt_Den_Mon_JPsi;
  TH1F*  h1_muon1_phi_Num_Mon_JPsi;
  TH1F*  h1_muon2_phi_Num_Mon_JPsi;
  TH1F*  h1_muon1_phi_Den_Mon_JPsi;
  TH1F*  h1_muon2_phi_Den_Mon_JPsi;
  TH1F*  h1_muon1_eta_Num_Mon_JPsi;
  TH1F*  h1_muon2_eta_Num_Mon_JPsi;
  TH1F*  h1_muon1_eta_Den_Mon_JPsi;
  TH1F*  h1_muon2_eta_Den_Mon_JPsi;
  TH1F*  h1_nPV_Den_Mon_JPsi;
  TH1F*  h1_nPV_Num_Mon_JPsi;
  TH1F*  h1_nDV_Den_Mon_JPsi;
  TH1F*  h1_nDV_Num_Mon_JPsi;
  TH2F*  h2_nPV_nDV_Num_Mon_JPsi;
  TH2F*  h2_nPV_nDV_Den_Mon_JPsi;
  TH1F*  h1_muon1_chi2_by_ndof_Num_Mon_JPsi;
  TH2F*  h2_pt1_pt2_Den_Mon_JPsi;
  TH1F*  h1_muon1_chi2_by_ndof_Den_Mon_JPsi;
  TH1F*  h1_muon2_chi2_by_ndof_Num_Mon_JPsi;
  TH2F*  h2_pt1_pt2_Num_Mon_JPsi;
  TH1F*  h1_muon2_chi2_by_ndof_Den_Mon_JPsi;

  //Z
  TH1F* h1_dimuonMass_Den_Mon_Z;
  TH1F* h1_dimuonMass_Num_Mon_Z;
  TH1F* h1_dxy2_Den_Mon_Z;
  TH1F* h1_dxy2_Num_Mon_Z;
  TH1F* h1_dxy1_Den_Mon_Z;
  TH1F* h1_dxy1_Num_Mon_Z;
  TH1F* h1_dz1_Den_Mon_Z;
  TH1F* h1_dz1_Num_Mon_Z;
  TH1F* h1_dz2_Den_Mon_Z;
  TH1F* h1_dz2_Num_Mon_Z;
  TH1F* h1_dimuondR_Den_Mon_Z;
  TH1F* h1_dimuondR_Num_Mon_Z;
  TH1F*  h1_muon1_pt_Num_Mon_Z;
  TH1F*  h1_unmatched_muon1_pt_Num_Mon_Z;
  TH1F*  h1_muon2_pt_Num_Mon_Z;
  TH1F*  h1_muon1_pt_Den_Mon_Z;
  TH1F*  h1_muon2_pt_Den_Mon_Z;
  TH1F*  h1_muon1_phi_Num_Mon_Z;
  TH1F*  h1_muon2_phi_Num_Mon_Z;
  TH1F*  h1_muon1_phi_Den_Mon_Z;
  TH1F*  h1_muon2_phi_Den_Mon_Z;
  TH1F*  h1_muon1_eta_Num_Mon_Z;
  TH1F*  h1_muon2_eta_Num_Mon_Z;
  TH1F*  h1_muon1_eta_Den_Mon_Z;
  TH1F*  h1_muon2_eta_Den_Mon_Z;
  TH1F*  h1_nPV_Den_Mon_Z;
  TH1F*  h1_nPV_Num_Mon_Z;
  TH1F*  h1_nDV_Den_Mon_Z;
  TH1F*  h1_nDV_Num_Mon_Z;
  TH2F*  h2_nPV_nDV_Num_Mon_Z;
  TH2F*  h2_nPV_nDV_Den_Mon_Z;
  TH1F*  h1_muon1_chi2_by_ndof_Num_Mon_Z;
  TH2F*  h2_pt1_pt2_Den_Mon_Z;
  TH1F*  h1_muon1_chi2_by_ndof_Den_Mon_Z;
  TH1F*  h1_muon2_chi2_by_ndof_Num_Mon_Z;
  TH2F*  h2_pt1_pt2_Num_Mon_Z;
  TH1F*  h1_muon2_chi2_by_ndof_Den_Mon_Z;
  //Z

  TH2F* h2_pt1_pt2_Num_Mon_HLTonly;
  TH1F* h1_dimuonMass_Num_Mon_HLTonly;
  TH1F* h1_dimuondR_Num_Mon_HLTonly;
  TH1F* h1_muon1_pt_Num_Mon_HLTonly;
  TH1F* h1_muon2_pt_Num_Mon_HLTonly;
  TH1F* h1_muon1_eta_Num_Mon_HLTonly;
  TH1F* h1_muon2_eta_Num_Mon_HLTonly;
  TH1F* h1_muon1_phi_Num_Mon_HLTonly;
  TH1F* h1_muon2_phi_Num_Mon_HLTonly;
  //
  TH1F* h1_dimuonMass_Num_Mon_JPsi_HLTonly;
  TH1F* h1_dxy1_Num_Mon_JPsi_HLTonly;
  TH1F* h1_dxy2_Num_Mon_JPsi_HLTonly;
  TH1F* h1_dz1_Num_Mon_JPsi_HLTonly;
  TH1F* h1_dz2_Num_Mon_JPsi_HLTonly;
  TH1F* h1_dimuondR_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon1_pt_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon2_pt_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon1_phi_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon2_phi_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon1_eta_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon2_eta_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_nPV_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_nDV_Num_Mon_JPsi_HLTonly;
  TH2F*  h2_nPV_nDV_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon1_chi2_by_ndof_Num_Mon_JPsi_HLTonly;
  TH1F*  h1_muon2_chi2_by_ndof_Num_Mon_JPsi_HLTonly;
  TH2F*  h2_pt1_pt2_Num_Mon_JPsi_HLTonly;

  TH1F* h1_dimuonMass_Den_1050_JPsi;
  TH1F* h1_dimuonMass_Num_1050_JPsi;
  TH1F* h1_dxy1_Den_1050_JPsi;
  TH1F* h1_dxy1_Num_1050_JPsi;
  TH1F* h1_dxy2_Den_1050_JPsi;
  TH1F* h1_dxy2_Num_1050_JPsi;
  TH1F* h1_dz1_Den_1050_JPsi;
  TH1F* h1_dz1_Num_1050_JPsi;
  TH1F* h1_dz2_Den_1050_JPsi;
  TH1F* h1_dz2_Num_1050_JPsi;
  TH1F* h1_dimuondR_Den_1050_JPsi;
  TH1F* h1_dimuondR_Num_1050_JPsi;
  TH1F*  h1_muon1_pt_Num_1050_JPsi;
  TH1F*  h1_unmatched_muon1_pt_Num_1050_JPsi;
  TH1F*  h1_muon2_pt_Num_1050_JPsi;
  TH1F*  h1_muon1_pt_Den_1050_JPsi;
  TH1F*  h1_muon2_pt_Den_1050_JPsi;
  TH1F*  h1_muon1_phi_Num_1050_JPsi;
  TH1F*  h1_muon2_phi_Num_1050_JPsi;
  TH1F*  h1_muon1_phi_Den_1050_JPsi;
  TH1F*  h1_muon2_phi_Den_1050_JPsi;
  TH1F*  h1_muon1_eta_Num_1050_JPsi;
  TH1F*  h1_muon2_eta_Num_1050_JPsi;
  TH1F*  h1_muon1_eta_Den_1050_JPsi;
  TH1F*  h1_muon2_eta_Den_1050_JPsi;
  TH1F*  h1_nPV_Den_1050_JPsi;
  TH1F*  h1_nPV_Num_1050_JPsi;
  TH1F*  h1_nDV_Den_1050_JPsi;
  TH1F*  h1_nDV_Num_1050_JPsi;
  TH2F*  h2_nPV_nDV_Num_1050_JPsi;
  TH2F*  h2_nPV_nDV_Den_1050_JPsi;
  TH1F*  h1_muon1_chi2_by_ndof_Num_1050_JPsi;
  TH1F*  h1_muon1_chi2_by_ndof_Den_1050_JPsi;
  TH1F*  h1_muon2_chi2_by_ndof_Num_1050_JPsi;
  TH1F*  h1_muon2_chi2_by_ndof_Den_1050_JPsi;
  TH2F*  h2_pt1_pt2_Num_1050_JPsi;
  TH2F*  h2_pt1_pt2_Den_1050_JPsi;
  //
  //permuon
  TH1F* h1_permuon_pt_Den_Mon;
  TH1F* h1_permuon_eta_Den_Mon;
  TH1F* h1_permuon_phi_Den_Mon;
  TH1F* h1_permuon_pt_Num_Mon;
  TH1F* h1_permuon_eta_Num_Mon;
  TH1F* h1_permuon_phi_Num_Mon;
  //
  TH1F* h1_dimuonMass;
  TH1F* h1_dimuondR;
  TH1I *h1_nPrimaryVtx;
  TH1I *h1_nDisplacedVtx;
  TH2F* h2_nPV_nDV;
  TH2F* h2_DV_x_y;
  TH1F *h1_mu1_pt;
  TH1F *h1_mu2_pt;
  TH1F *h1_mu1_phi;
  TH1F *h1_mu2_phi;
  TH1F *h1_mu1_eta;
  TH1F *h1_mu2_eta;
  TH1F *h1_asym ;  

  //  TH1F *l1PassHisto_;

};


DimuonScoutingAnalyzer::DimuonScoutingAnalyzer(const edm::ParameterSet& iConfig)
  
{
  RunOnOfflineReco           = (iConfig.getParameter<bool>("RunOnOfflineReco_"));
  //  trgResultsLabelScouting_   = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultsScouting"));
  trgResultsLabel_           = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  triggerObjectsScouting_    = consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("objectsScouting"));
  muonLabelScouting_         = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muonsScouting"));
  muonLabel_                 = consumes<std::vector<pat::Muon>>(iConfig.getParameter<edm::InputTag>("muons"));
  primaryVtxLabel_           = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVtx"));
  primaryVtxLabelScouting_   = consumes<ScoutingVertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVtxScouting"));
  displacedVtxLabel_         = consumes<ScoutingVertexCollection>(iConfig.getParameter<edm::InputTag>("displacedVtx"));
  usesResource("TFileService");
  // l1GtUtils_ = new l1t::L1TGlobalUtil(iConfig,consumesCollector());
  // algToken_ = consumes<BXVector<GlobalAlgBlk>>(iConfig.getParameter<edm::InputTag>("AlgInputTag"));
  // l1Seeds_ = iConfig.getParameter<std::vector<std::string>>("l1Seeds");

  TFileDirectory histoDir = fs->mkdir("histoDir");
  // l1PassHisto_ = fs->make<TH1F>("L1Pass", "L1Pass", 1, 0, 1);
  // l1PassHisto_->SetCanExtend(TH1::kAllAxes);
  // l1PassHisto_->Fill("totalEvents", 0.0);
  // for (unsigned i=0; i<l1Seeds_.size(); ++i) {
  //  l1PassHisto_->Fill(l1Seeds_[i].c_str(), 0.0);
  // }
  Float_t bins[] = {0.,0.01,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,120,130,140,150,160,170,180,190,200,250,300};
  Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1; // or just write the number
    

  h1_check                              = histoDir.make<TH1F>("check", "check", 10, 0, 10);
  //
  h1_permuon_pt_Den_Mon   = histoDir.make<TH1F>("permuon_pt_Den_Mon",  "permuon_pt_Den_Mon", binnum, bins);
  h1_permuon_eta_Den_Mon  = histoDir.make<TH1F>("permuon_eta_Den_Mon", "permuon_eta_Den_Mon", 600, -3.0, 3.0);
  h1_permuon_phi_Den_Mon  = histoDir.make<TH1F>("permuon_phi_Den_Mon", "permuon_phi_Den_Mon", 800, -4.0, 4.0);
  h1_permuon_pt_Num_Mon   = histoDir.make<TH1F>("permuon_pt_Num_Mon",  "permuon_pt_Num_Mon", binnum, bins);
  h1_permuon_eta_Num_Mon  = histoDir.make<TH1F>("permuon_eta_Num_Mon", "permuon_eta_Num_Mon", 600, -3.0, 3.0);
  h1_permuon_phi_Num_Mon  = histoDir.make<TH1F>("permuon_phi_Num_Mon", "permuon_phi_Num_Mon", 800, -4.0, 4.0);
  //
  //  
  h1_dxy1_Den_1050                = histoDir.make<TH1F>("dxy1_Den_1050", "dxy1_Den_1050", 2000, -1, 1);
  h1_dxy1_Num_1050                = histoDir.make<TH1F>("dxy1_Num_1050", "dxy1_Num_1050", 2000, -1, 1);
  h1_dxy2_Den_1050                = histoDir.make<TH1F>("dxy2_Den_1050", "dxy2_Den_1050", 2000, -1, 1);
  h1_dxy2_Num_1050                = histoDir.make<TH1F>("dxy2_Num_1050", "dxy2_Num_1050", 2000, -1, 1);
  h1_dz1_Den_1050                = histoDir.make<TH1F>("dz1_Den_1050", "dz1_Den_1050", 4000, -20, 20);
  h1_dz1_Num_1050                = histoDir.make<TH1F>("dz1_Num_1050", "dz1_Num_1050", 4000, -20, 20);
  h1_dz2_Den_1050                = histoDir.make<TH1F>("dz2_Den_1050", "dz2_Den_1050", 4000, -20, 20);
  h1_dz2_Num_1050                = histoDir.make<TH1F>("dz2_Num_1050", "dz2_Num_1050", 4000, -20, 20);
  h1_dimuonMass_Den_1050                = histoDir.make<TH1F>("dimuMass_Den_1050", "Mmumu_Den_1050", binnum, bins);
  h1_dimuonMass_Num_1050                = histoDir.make<TH1F>("dimuMass_Num_1050", "Mmumu_Num_1050", binnum, bins);
  h1_dimuondR_Den_1050                = histoDir.make<TH1F>("dimudR_Den_1050", "DR_mumu_Den_1050", 1000, 0, 10);
  h1_dimuondR_Num_1050                = histoDir.make<TH1F>("dimudR_Num_1050", "DR_mumu_Num_1050", 1000, 0, 10);
  h1_muon1_pt_Den_1050                  = histoDir.make<TH1F>("mu1_pt_Den_1050",   "mu1_pt_Den_1050", binnum, bins);  
  h1_muon2_pt_Den_1050                  = histoDir.make<TH1F>("mu2_pt_Den_1050",   "mu2_pt_Den_1050", binnum, bins);  
  h1_muon1_pt_Num_1050                  = histoDir.make<TH1F>("mu1_pt_Num_1050",   "mu1_pt_Num_1050", binnum, bins);  
  h1_unmatched_muon1_pt_Num_1050        = histoDir.make<TH1F>("unmatched_mu1_pt_Num_1050",   "unmatched_mu1_pt_Num_1050", binnum, bins);  
  h1_muon2_pt_Num_1050                  = histoDir.make<TH1F>("mu2_pt_Num_1050",   "mu2_pt_Num_1050", binnum, bins);  
  h1_muon1_eta_Den_1050                  = histoDir.make<TH1F>("mu1_eta_Den_1050",   "mu1_eta_Den_1050", 600, -3.0, 3.0);  
  h1_muon2_eta_Den_1050                  = histoDir.make<TH1F>("mu2_eta_Den_1050",   "mu2_eta_Den_1050", 600, -3.0, 3.0);  
  h1_muon1_eta_Num_1050                  = histoDir.make<TH1F>("mu1_eta_Num_1050",   "mu1_eta_Num_1050", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_1050                  = histoDir.make<TH1F>("mu2_eta_Num_1050",   "mu2_eta_Num_1050", 600, -3.0, 3.0);  
  h1_muon1_phi_Den_1050                  = histoDir.make<TH1F>("mu1_phi_Den_1050",   "mu1_phi_Den_1050", 800, -4.0, 4.0);  
  h1_muon2_phi_Den_1050                  = histoDir.make<TH1F>("mu2_phi_Den_1050",   "mu2_phi_Den_1050", 800, -4.0, 4.0);  
  h1_muon1_phi_Num_1050                  = histoDir.make<TH1F>("mu1_phi_Num_1050",   "mu1_phi_Num_1050", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_1050                  = histoDir.make<TH1F>("mu2_phi_Num_1050",   "mu2_phi_Num_1050", 800, -4.0, 4.0);  
  h1_nPV_Num_1050                    = histoDir.make<TH1F>("nPV_Num_1050",   "nPV_Num_1050", 100, 0, 100);  
  h1_nPV_Den_1050                    = histoDir.make<TH1F>("nPV_Den_1050",   "nPV_Den_1050", 100, 0, 100);  
  h1_nDV_Num_1050                    = histoDir.make<TH1F>("nDV_Num_1050",   "nDV_Num_1050", 100, 0, 100);  
  h1_nDV_Den_1050                    = histoDir.make<TH1F>("nDV_Den_1050",   "nDV_Den_1050", 100, 0, 100);  
  h2_nPV_nDV_Num_1050                = histoDir.make<TH2F>("nPV_nDV_Num_1050",   "nPV_nDV_Num_1050", 100, 0, 100, 20, 0, 20)  ;
  h2_nPV_nDV_Den_1050                = histoDir.make<TH2F>("nPV_nDV_Den_1050",   "nPV_nDV_Den_1050", 100, 0, 100, 20, 0, 20)  ;
  h2_pt1_pt2_Num_1050       = histoDir.make<TH2F>("pt1_pt2_Num_1050",   "pt1_pt2_Num_1050", 150, 0, 300, 150, 0, 300)  ;
  h2_pt1_pt2_Den_1050       = histoDir.make<TH2F>("pt1_pt2_Den_1050",   "pt1_pt2_Num_1050", 150, 0, 300, 150, 0, 300)  ;
  h1_muon1_chi2_by_ndof_Num_1050     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_1050",   "muon1_chi2_by_ndof_Num_1050", 120, 0, 12);
  h1_muon1_chi2_by_ndof_Den_1050     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Den_1050",   "muon1_chi2_by_ndof_Den_1050", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Num_1050     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_1050",   "muon2_chi2_by_ndof_Num_1050", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Den_1050     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Den_1050",   "muon2_chi2_by_ndof_Den_1050", 120, 0, 12);



 //h1_nPV_Den_Mon
  h1_dxy1_Den_Mon                = histoDir.make<TH1F>("dxy1_Den_Mon", "dxy1_Den_Mon", 2000, -1, 1);
  h1_dxy1_Num_Mon                = histoDir.make<TH1F>("dxy1_Num_Mon", "dxy1_Num_Mon", 2000, -1, 1);
  h1_dxy2_Den_Mon                = histoDir.make<TH1F>("dxy2_Den_Mon", "dxy2_Den_Mon", 2000, -1, 1);
  h1_dxy2_Num_Mon                = histoDir.make<TH1F>("dxy2_Num_Mon", "dxy2_Num_Mon", 2000, -1, 1);
  h1_dz1_Den_Mon                = histoDir.make<TH1F>("dz1_Den_Mon", "dz1_Den_Mon", 4000, -20, 20);
  h1_dz1_Num_Mon                = histoDir.make<TH1F>("dz1_Num_Mon", "dz1_Num_Mon", 4000, -20, 20);
  h1_dz2_Den_Mon                = histoDir.make<TH1F>("dz2_Den_Mon", "dz2_Den_Mon", 4000, -20, 20);
  h1_dz2_Num_Mon                = histoDir.make<TH1F>("dz2_Num_Mon", "dz2_Num_Mon", 4000, -20, 20);
  h1_dimuonMass_Den_Mon                = histoDir.make<TH1F>("dimuMass_Den_Mon", "Mmumu_Den_Mon", binnum, bins);
  h1_dimuonMass_Num_Mon                = histoDir.make<TH1F>("dimuMass_Num_Mon", "Mmumu_Num_Mon", binnum, bins);
  h1_dimuonMass_Num_Mon_HLTonly        = histoDir.make<TH1F>("dimuMass_Num_Mon_HLTonly", "Mmumu_Num_Mon_HLTonly", binnum, bins);
  h1_dimuondR_Den_Mon                = histoDir.make<TH1F>("dimudR_Den_Mon", "DR_mumu_Den_Mon", 1000, 0, 10);
  h1_dimuondR_Num_Mon                = histoDir.make<TH1F>("dimudR_Num_Mon", "DR_mumu_Num_Mon", 1000, 0, 10);
  h1_dimuondR_Num_Mon_HLTonly        = histoDir.make<TH1F>("dimudR_Num_Mon_HLTonly", "DR_mumu_Num_Mon_HLTonly", 1000, 0, 10);
  h1_muon1_pt_Den_Mon                  = histoDir.make<TH1F>("mu1_pt_Den_Mon",   "mu1_pt_Den_Mon", binnum, bins);  
  h1_muon2_pt_Den_Mon                  = histoDir.make<TH1F>("mu2_pt_Den_Mon",   "mu2_pt_Den_Mon", binnum, bins);  
  h1_muon1_pt_Num_Mon                  = histoDir.make<TH1F>("mu1_pt_Num_Mon",   "mu1_pt_Num_Mon", binnum, bins);  
  h1_muon1_pt_Num_Mon_HLTonly          = histoDir.make<TH1F>("mu1_pt_Num_Mon_HLTonly",   "mu1_pt_Num_Mon_HLTonly", binnum, bins);  
  h1_unmatched_muon1_pt_Num_Mon        = histoDir.make<TH1F>("unmatched_mu1_pt_Num_Mon",   "unmatched_mu1_pt_Num_Mon", binnum, bins);  
  h1_muon2_pt_Num_Mon                  = histoDir.make<TH1F>("mu2_pt_Num_Mon",   "mu2_pt_Num_Mon", binnum, bins);  
  h1_muon2_pt_Num_Mon_HLTonly          = histoDir.make<TH1F>("mu2_pt_Num_Mon_HLTonly",   "mu2_pt_Num_Mon_HLTonly", binnum, bins);  
  h1_muon1_eta_Den_Mon                  = histoDir.make<TH1F>("mu1_eta_Den_Mon",   "mu1_eta_Den_Mon", 600, -3.0, 3.0);  
  h1_muon2_eta_Den_Mon                  = histoDir.make<TH1F>("mu2_eta_Den_Mon",   "mu2_eta_Den_Mon", 600, -3.0, 3.0);  
  h1_muon1_eta_Num_Mon                  = histoDir.make<TH1F>("mu1_eta_Num_Mon",   "mu1_eta_Num_Mon", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_Mon                  = histoDir.make<TH1F>("mu2_eta_Num_Mon",   "mu2_eta_Num_Mon", 600, -3.0, 3.0);  
 
  h1_muon1_eta_Num_Mon_HLTonly       = histoDir.make<TH1F>("mu1_eta_Num_Mon_HLTonly",   "mu1_eta_Num_Mon_HLTonly", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_Mon_HLTonly       = histoDir.make<TH1F>("mu2_eta_Num_Mon_HLTonly",   "mu2_eta_Num_Mon_HLTonly", 600, -3.0, 3.0);  
  
  h1_muon1_phi_Den_Mon                  = histoDir.make<TH1F>("mu1_phi_Den_Mon",   "mu1_phi_Den_Mon", 800, -4.0, 4.0);  
  h1_muon2_phi_Den_Mon                  = histoDir.make<TH1F>("mu2_phi_Den_Mon",   "mu2_phi_Den_Mon", 800, -4.0, 4.0);  
 
  h1_muon1_phi_Num_Mon                  = histoDir.make<TH1F>("mu1_phi_Num_Mon",   "mu1_phi_Num_Mon", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_Mon                  = histoDir.make<TH1F>("mu2_phi_Num_Mon",   "mu2_phi_Num_Mon", 800, -4.0, 4.0);  

  h1_muon1_phi_Num_Mon_HLTonly          = histoDir.make<TH1F>("mu1_phi_Num_Mon_HLTonly",   "mu1_phi_Num_Mon_HLTonly", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_Mon_HLTonly          = histoDir.make<TH1F>("mu2_phi_Num_Mon_HLTonly",   "mu2_phi_Num_Mon_HLTonly", 800, -4.0, 4.0);  
  
  h1_nPV_Num_Mon                    = histoDir.make<TH1F>("nPV_Num_Mon",   "nPV_Num_Mon", 100, 0, 100);  
  h1_nPV_Den_Mon                    = histoDir.make<TH1F>("nPV_Den_Mon",   "nPV_Den_Mon", 100, 0, 100);  
  h1_nDV_Num_Mon                    = histoDir.make<TH1F>("nDV_Num_Mon",   "nDV_Num_Mon", 100, 0, 100);  
  h1_nDV_Den_Mon                    = histoDir.make<TH1F>("nDV_Den_Mon",   "nDV_Den_Mon", 100, 0, 100);  
  h2_nPV_nDV_Num_Mon                = histoDir.make<TH2F>("nPV_nDV_Num_Mon",   "nPV_nDV_Num_Mon", 100, 0, 100, 20, 0, 20)  ;
  h2_nPV_nDV_Den_Mon                = histoDir.make<TH2F>("nPV_nDV_Den_Mon",   "nPV_nDV_Den_Mon", 100, 0, 100, 20, 0, 20)  ;
  //
  h1_muon2_chi2_by_ndof_Den_Mon     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Den_Mon",   "muon2_chi2_by_ndof_Den_Mon", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Num_Mon     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_Mon",   "muon2_chi2_by_ndof_Num_Mon", 120, 0, 12);
  h1_muon1_chi2_by_ndof_Den_Mon     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Den_Mon",   "muon1_chi2_by_ndof_Den_Mon", 120, 0, 12);
  h1_muon1_chi2_by_ndof_Num_Mon     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_Mon",   "muon1_chi2_by_ndof_Num_Mon", 120, 0, 12);
  //
  h2_deta_dphi_passMon_passSig  = histoDir.make<TH2F>("deta_dphi",   "deta_dphi", 200, 0, 4.0, 200, 0, 4.0)  ;

  h2_pt1_pt2_Num_Mon       = histoDir.make<TH2F>("pt1_pt2_Num_Mon",   "pt1_pt2_Num_Mon", 150, 0, 300, 150, 0, 300)  ;
  h2_pt1_pt2_Num_Mon_HLTonly   = histoDir.make<TH2F>("pt1_pt2_Num_Mon_HLTonly",   "pt1_pt2_Num_Mon_HLTonly", 150, 0, 300, 150, 0, 300)  ;
  h2_pt1_pt2_Den_Mon       = histoDir.make<TH2F>("pt1_pt2_Den_Mon",   "pt1_pt2_Num_Mon", 150, 0, 300, 150, 0, 300)  ;

 //h1_nPV_Den_Mon_JPsi
  h1_dxy1_Den_Mon_JPsi                = histoDir.make<TH1F>("dxy1_Den_Mon_JPsi", "dxy1_Den_Mon_JPsi", 2000, -1, 1);
  h1_dxy2_Den_Mon_JPsi                = histoDir.make<TH1F>("dxy2_Den_Mon_JPsi", "dxy2_Den_Mon_JPsi", 2000, -1, 1);
  h1_dz1_Den_Mon_JPsi                = histoDir.make<TH1F>("dz1_Den_Mon_JPsi", "dz1_Den_Mon_JPsi", 4000, -20, 20);
  h1_dz2_Den_Mon_JPsi                = histoDir.make<TH1F>("dz2_Den_Mon_JPsi", "dz2_Den_Mon_JPsi", 4000, -20, 20);
  h1_dimuonMass_Den_Mon_JPsi                = histoDir.make<TH1F>("dimuMass_Den_Mon_JPsi", "Mmumu_Den_Mon_JPsi", binnum, bins);
  h1_dimuondR_Den_Mon_JPsi                = histoDir.make<TH1F>("dimudR_Den_Mon_JPsi", "DR_mumu_Den_Mon_JPsi", 1000, 0, 10);
  h1_muon1_pt_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu1_pt_Den_Mon_JPsi",   "mu1_pt_Den_Mon_JPsi", binnum, bins);  
  h1_muon2_pt_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu2_pt_Den_Mon_JPsi",   "mu2_pt_Den_Mon_JPsi", binnum, bins);  
  h1_muon1_eta_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu1_eta_Den_Mon_JPsi",   "mu1_eta_Den_Mon_JPsi", 600, -3.0, 3.0);  
  h1_muon2_eta_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu2_eta_Den_Mon_JPsi",   "mu2_eta_Den_Mon_JPsi", 600, -3.0, 3.0);  
  h1_muon1_phi_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu1_phi_Den_Mon_JPsi",   "mu1_phi_Den_Mon_JPsi", 800, -4.0, 4.0);  
  h1_muon2_phi_Den_Mon_JPsi                  = histoDir.make<TH1F>("mu2_phi_Den_Mon_JPsi",   "mu2_phi_Den_Mon_JPsi", 800, -4.0, 4.0);  
  h1_nPV_Den_Mon_JPsi                    = histoDir.make<TH1F>("nPV_Den_Mon_JPsi",   "nPV_Den_Mon_JPsi", 100, 0, 100);  
  h1_nDV_Den_Mon_JPsi                    = histoDir.make<TH1F>("nDV_Den_Mon_JPsi",   "nDV_Den_Mon_JPsi", 100, 0, 100);  
  h2_nPV_nDV_Den_Mon_JPsi                = histoDir.make<TH2F>("nPV_nDV_Den_Mon_JPsi",   "nPV_nDV_Den_Mon_JPsi", 100, 0, 100, 20, 0, 20)  ;
  h1_muon1_chi2_by_ndof_Den_Mon_JPsi     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Den_Mon_JPsi",   "muon1_chi2_by_ndof_Den_Mon_JPsi", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Den_Mon_JPsi     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Den_Mon_JPsi",   "muon2_chi2_by_ndof_Den_Mon_JPsi", 120, 0, 12);
  h2_pt1_pt2_Den_Mon_JPsi       = histoDir.make<TH2F>("pt1_pt2_Den_Mon_JPsi",   "pt1_pt2_Num_Mon_JPsi", 150, 0, 300, 150, 0, 300)  ;
  //
  h1_unmatched_muon1_pt_Num_Mon_JPsi        = histoDir.make<TH1F>("unmatched_mu1_pt_Num_Mon_JPsi",   "unmatched_mu1_pt_Num_Mon_JPsi", binnum, bins);  
  h1_dxy1_Num_Mon_JPsi                = histoDir.make<TH1F>("dxy1_Num_Mon_JPsi", "dxy1_Num_Mon_JPsi", 2000, -1, 1);
  h1_dxy2_Num_Mon_JPsi                = histoDir.make<TH1F>("dxy2_Num_Mon_JPsi", "dxy2_Num_Mon_JPsi", 2000, -1, 1);
  h1_dz1_Num_Mon_JPsi                = histoDir.make<TH1F>("dz1_Num_Mon_JPsi", "dz1_Num_Mon_JPsi", 4000, -20, 20);
  h1_dz2_Num_Mon_JPsi                = histoDir.make<TH1F>("dz2_Num_Mon_JPsi", "dz2_Num_Mon_JPsi", 4000, -20, 20);
  h1_dimuonMass_Num_Mon_JPsi                = histoDir.make<TH1F>("dimuMass_Num_Mon_JPsi", "Mmumu_Num_Mon_JPsi", binnum, bins);
  h1_dimuondR_Num_Mon_JPsi                = histoDir.make<TH1F>("dimudR_Num_Mon_JPsi", "DR_mumu_Num_Mon_JPsi", 1000, 0, 10);
  h1_muon1_pt_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu1_pt_Num_Mon_JPsi",   "mu1_pt_Num_Mon_JPsi", binnum, bins);  
  h1_muon2_pt_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu2_pt_Num_Mon_JPsi",   "mu2_pt_Num_Mon_JPsi", binnum, bins);  
  h1_muon1_eta_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu1_eta_Num_Mon_JPsi",   "mu1_eta_Num_Mon_JPsi", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu2_eta_Num_Mon_JPsi",   "mu2_eta_Num_Mon_JPsi", 600, -3.0, 3.0);  
  h1_muon1_phi_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu1_phi_Num_Mon_JPsi",   "mu1_phi_Num_Mon_JPsi", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_Mon_JPsi                  = histoDir.make<TH1F>("mu2_phi_Num_Mon_JPsi",   "mu2_phi_Num_Mon_JPsi", 800, -4.0, 4.0);  
  h1_nPV_Num_Mon_JPsi                    = histoDir.make<TH1F>("nPV_Num_Mon_JPsi",   "nPV_Num_Mon_JPsi", 100, 0, 100);  
  h1_nDV_Num_Mon_JPsi                    = histoDir.make<TH1F>("nDV_Num_Mon_JPsi",   "nDV_Num_Mon_JPsi", 100, 0, 100);  
  h2_nPV_nDV_Num_Mon_JPsi                = histoDir.make<TH2F>("nPV_nDV_Num_Mon_JPsi",   "nPV_nDV_Num_Mon_JPsi", 100, 0, 100, 20, 0, 20)  ;
  h1_muon1_chi2_by_ndof_Num_Mon_JPsi     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_Mon_JPsi",   "muon1_chi2_by_ndof_Num_Mon_JPsi", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Num_Mon_JPsi     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_Mon_JPsi",   "muon2_chi2_by_ndof_Num_Mon_JPsi", 120, 0, 12);
  h2_pt1_pt2_Num_Mon_JPsi       = histoDir.make<TH2F>("pt1_pt2_Num_Mon_JPsi",   "pt1_pt2_Num_Mon_JPsi", 150, 0, 300, 150, 0, 300)  ;
  //Z
  h1_dxy1_Den_Mon_Z                = histoDir.make<TH1F>("dxy1_Den_Mon_Z", "dxy1_Den_Mon_Z", 2000, -1, 1);
  h1_dxy2_Den_Mon_Z                = histoDir.make<TH1F>("dxy2_Den_Mon_Z", "dxy2_Den_Mon_Z", 2000, -1, 1);
  h1_dz1_Den_Mon_Z                = histoDir.make<TH1F>("dz1_Den_Mon_Z", "dz1_Den_Mon_Z", 4000, -20, 20);
  h1_dz2_Den_Mon_Z                = histoDir.make<TH1F>("dz2_Den_Mon_Z", "dz2_Den_Mon_Z", 4000, -20, 20);
  h1_dimuonMass_Den_Mon_Z                = histoDir.make<TH1F>("dimuMass_Den_Mon_Z", "Mmumu_Den_Mon_Z", binnum, bins);
  h1_dimuondR_Den_Mon_Z                = histoDir.make<TH1F>("dimudR_Den_Mon_Z", "DR_mumu_Den_Mon_Z", 1000, 0, 10);
  h1_muon1_pt_Den_Mon_Z                  = histoDir.make<TH1F>("mu1_pt_Den_Mon_Z",   "mu1_pt_Den_Mon_Z", binnum, bins);  
  h1_muon2_pt_Den_Mon_Z                  = histoDir.make<TH1F>("mu2_pt_Den_Mon_Z",   "mu2_pt_Den_Mon_Z", binnum, bins);  
  h1_muon1_eta_Den_Mon_Z                  = histoDir.make<TH1F>("mu1_eta_Den_Mon_Z",   "mu1_eta_Den_Mon_Z", 600, -3.0, 3.0);  
  h1_muon2_eta_Den_Mon_Z                  = histoDir.make<TH1F>("mu2_eta_Den_Mon_Z",   "mu2_eta_Den_Mon_Z", 600, -3.0, 3.0);  
  h1_muon1_phi_Den_Mon_Z                  = histoDir.make<TH1F>("mu1_phi_Den_Mon_Z",   "mu1_phi_Den_Mon_Z", 800, -4.0, 4.0);  
  h1_muon2_phi_Den_Mon_Z                  = histoDir.make<TH1F>("mu2_phi_Den_Mon_Z",   "mu2_phi_Den_Mon_Z", 800, -4.0, 4.0);  
  h1_nPV_Den_Mon_Z                    = histoDir.make<TH1F>("nPV_Den_Mon_Z",   "nPV_Den_Mon_Z", 100, 0, 100);  
  h1_nDV_Den_Mon_Z                    = histoDir.make<TH1F>("nDV_Den_Mon_Z",   "nDV_Den_Mon_Z", 100, 0, 100);  
  h2_nPV_nDV_Den_Mon_Z                = histoDir.make<TH2F>("nPV_nDV_Den_Mon_Z",   "nPV_nDV_Den_Mon_Z", 100, 0, 100, 20, 0, 20)  ;
  h1_muon1_chi2_by_ndof_Den_Mon_Z     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Den_Mon_Z",   "muon1_chi2_by_ndof_Den_Mon_Z", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Den_Mon_Z     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Den_Mon_Z",   "muon2_chi2_by_ndof_Den_Mon_Z", 120, 0, 12);
  h2_pt1_pt2_Den_Mon_Z       = histoDir.make<TH2F>("pt1_pt2_Den_Mon_Z",   "pt1_pt2_Num_Mon_Z", 150, 0, 300, 150, 0, 300)  ;
  //
  h1_unmatched_muon1_pt_Num_Mon_Z        = histoDir.make<TH1F>("unmatched_mu1_pt_Num_Mon_Z",   "unmatched_mu1_pt_Num_Mon_Z", binnum, bins);  
  h1_dxy1_Num_Mon_Z                = histoDir.make<TH1F>("dxy1_Num_Mon_Z", "dxy1_Num_Mon_Z", 2000, -1, 1);
  h1_dxy2_Num_Mon_Z                = histoDir.make<TH1F>("dxy2_Num_Mon_Z", "dxy2_Num_Mon_Z", 2000, -1, 1);
  h1_dz1_Num_Mon_Z                = histoDir.make<TH1F>("dz1_Num_Mon_Z", "dz1_Num_Mon_Z", 4000, -20, 20);
  h1_dz2_Num_Mon_Z                = histoDir.make<TH1F>("dz2_Num_Mon_Z", "dz2_Num_Mon_Z", 4000, -20, 20);
  h1_dimuonMass_Num_Mon_Z                = histoDir.make<TH1F>("dimuMass_Num_Mon_Z", "Mmumu_Num_Mon_Z", binnum, bins);
  h1_dimuondR_Num_Mon_Z                = histoDir.make<TH1F>("dimudR_Num_Mon_Z", "DR_mumu_Num_Mon_Z", 1000, 0, 10);
  h1_muon1_pt_Num_Mon_Z                  = histoDir.make<TH1F>("mu1_pt_Num_Mon_Z",   "mu1_pt_Num_Mon_Z", binnum, bins);  
  h1_muon2_pt_Num_Mon_Z                  = histoDir.make<TH1F>("mu2_pt_Num_Mon_Z",   "mu2_pt_Num_Mon_Z", binnum, bins);  
  h1_muon1_eta_Num_Mon_Z                  = histoDir.make<TH1F>("mu1_eta_Num_Mon_Z",   "mu1_eta_Num_Mon_Z", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_Mon_Z                  = histoDir.make<TH1F>("mu2_eta_Num_Mon_Z",   "mu2_eta_Num_Mon_Z", 600, -3.0, 3.0);  
  h1_muon1_phi_Num_Mon_Z                  = histoDir.make<TH1F>("mu1_phi_Num_Mon_Z",   "mu1_phi_Num_Mon_Z", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_Mon_Z                  = histoDir.make<TH1F>("mu2_phi_Num_Mon_Z",   "mu2_phi_Num_Mon_Z", 800, -4.0, 4.0);  
  h1_nPV_Num_Mon_Z                    = histoDir.make<TH1F>("nPV_Num_Mon_Z",   "nPV_Num_Mon_Z", 100, 0, 100);  
  h1_nDV_Num_Mon_Z                    = histoDir.make<TH1F>("nDV_Num_Mon_Z",   "nDV_Num_Mon_Z", 100, 0, 100);  
  h2_nPV_nDV_Num_Mon_Z                = histoDir.make<TH2F>("nPV_nDV_Num_Mon_Z",   "nPV_nDV_Num_Mon_Z", 100, 0, 100, 20, 0, 20)  ;
  h1_muon1_chi2_by_ndof_Num_Mon_Z     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_Mon_Z",   "muon1_chi2_by_ndof_Num_Mon_Z", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Num_Mon_Z     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_Mon_Z",   "muon2_chi2_by_ndof_Num_Mon_Z", 120, 0, 12);
  h2_pt1_pt2_Num_Mon_Z       = histoDir.make<TH2F>("pt1_pt2_Num_Mon_Z",   "pt1_pt2_Num_Mon_Z", 150, 0, 300, 150, 0, 300)  ;
  //Z
  //--//
  h1_dxy1_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dxy1_Num_Mon_JPsi_HLTonly", "dxy1_Num_Mon_JPsi_HLTonly", 2000, -1, 1);
  h1_dxy2_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dxy2_Num_Mon_JPsi_HLTonly", "dxy2_Num_Mon_JPsi_HLTonly", 2000, -1, 1);
  h1_dz1_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dz1_Num_Mon_JPsi_HLTonly", "dz1_Num_Mon_JPsi_HLTonly", 4000, -20, 20);
  h1_dz2_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dz2_Num_Mon_JPsi_HLTonly", "dz2_Num_Mon_JPsi_HLTonly", 4000, -20, 20);
  h1_dimuonMass_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dimuMass_Num_Mon_JPsi_HLTonly", "Mmumu_Num_Mon_JPsi_HLTonly", binnum, bins);
  h1_dimuondR_Num_Mon_JPsi_HLTonly                = histoDir.make<TH1F>("dimudR_Num_Mon_JPsi_HLTonly", "DR_mumu_Num_Mon_JPsi_HLTonly", 1000, 0, 10);
  h1_muon1_pt_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu1_pt_Num_Mon_JPsi_HLTonly",   "mu1_pt_Num_Mon_JPsi_HLTonly", binnum, bins);  
  h1_muon2_pt_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu2_pt_Num_Mon_JPsi_HLTonly",   "mu2_pt_Num_Mon_JPsi_HLTonly", binnum, bins);  
  h1_muon1_eta_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu1_eta_Num_Mon_JPsi_HLTonly",   "mu1_eta_Num_Mon_JPsi_HLTonly", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu2_eta_Num_Mon_JPsi_HLTonly",   "mu2_eta_Num_Mon_JPsi_HLTonly", 600, -3.0, 3.0);  
  h1_muon1_phi_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu1_phi_Num_Mon_JPsi_HLTonly",   "mu1_phi_Num_Mon_JPsi_HLTonly", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_Mon_JPsi_HLTonly                  = histoDir.make<TH1F>("mu2_phi_Num_Mon_JPsi_HLTonly",   "mu2_phi_Num_Mon_JPsi_HLTonly", 800, -4.0, 4.0);  
  h1_nPV_Num_Mon_JPsi_HLTonly                    = histoDir.make<TH1F>("nPV_Num_Mon_JPsi_HLTonly",   "nPV_Num_Mon_JPsi_HLTonly", 100, 0, 100);  
  h1_nDV_Num_Mon_JPsi_HLTonly                    = histoDir.make<TH1F>("nDV_Num_Mon_JPsi_HLTonly",   "nDV_Num_Mon_JPsi_HLTonly", 100, 0, 100);  
  h2_nPV_nDV_Num_Mon_JPsi_HLTonly                = histoDir.make<TH2F>("nPV_nDV_Num_Mon_JPsi_HLTonly",   "nPV_nDV_Num_Mon_JPsi_HLTonly", 100, 0, 100, 20, 0, 20)  ;
  h1_muon1_chi2_by_ndof_Num_Mon_JPsi_HLTonly     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_Mon_JPsi_HLTonly",   "muon1_chi2_by_ndof_Num_Mon_JPsi_HLTonly", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Num_Mon_JPsi_HLTonly     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_Mon_JPsi_HLTonly",   "muon2_chi2_by_ndof_Num_Mon_JPsi_HLTonly", 120, 0, 12);
  h2_pt1_pt2_Num_Mon_JPsi_HLTonly       = histoDir.make<TH2F>("pt1_pt2_Num_Mon_JPsi_HLTonly",   "pt1_pt2_Num_Mon_JPsi_HLTonly", 150, 0, 300, 150, 0, 300)  ;


  //
  h1_dxy1_Den_1050_JPsi                = histoDir.make<TH1F>("dxy1_Den_1050_JPsi", "dxy1_Den_1050_JPsi", 2000, -1, 1);
  h1_dxy1_Num_1050_JPsi                = histoDir.make<TH1F>("dxy1_Num_1050_JPsi", "dxy1_Num_1050_JPsi", 2000, -1, 1);
  h1_dxy2_Den_1050_JPsi                = histoDir.make<TH1F>("dxy2_Den_1050_JPsi", "dxy2_Den_1050_JPsi", 2000, -1, 1);
  h1_dxy2_Num_1050_JPsi                = histoDir.make<TH1F>("dxy2_Num_1050_JPsi", "dxy2_Num_1050_JPsi", 2000, -1, 1);
  h1_dz1_Den_1050_JPsi                = histoDir.make<TH1F>("dz1_Den_1050_JPsi", "dz1_Den_1050_JPsi", 4000, -20, 20);
  h1_dz1_Num_1050_JPsi                = histoDir.make<TH1F>("dz1_Num_1050_JPsi", "dz1_Num_1050_JPsi", 4000, -20, 20);
  h1_dz2_Den_1050_JPsi                = histoDir.make<TH1F>("dz2_Den_1050_JPsi", "dz2_Den_1050_JPsi", 4000, -20, 20);
  h1_dz2_Num_1050_JPsi                = histoDir.make<TH1F>("dz2_Num_1050_JPsi", "dz2_Num_1050_JPsi", 4000, -20, 20);
  h1_dimuonMass_Den_1050_JPsi                = histoDir.make<TH1F>("dimuMass_Den_1050_JPsi", "Mmumu_Den_1050_JPsi", binnum, bins);
  h1_dimuonMass_Num_1050_JPsi                = histoDir.make<TH1F>("dimuMass_Num_1050_JPsi", "Mmumu_Num_1050_JPsi", binnum, bins);
  h1_dimuondR_Den_1050_JPsi                = histoDir.make<TH1F>("dimudR_Den_1050_JPsi", "DR_mumu_Den_1050_JPsi", 1000, 0, 10);
  h1_dimuondR_Num_1050_JPsi                = histoDir.make<TH1F>("dimudR_Num_1050_JPsi", "DR_mumu_Num_1050_JPsi", 1000, 0, 10);
  h1_muon1_pt_Den_1050_JPsi                  = histoDir.make<TH1F>("mu1_pt_Den_1050_JPsi",   "mu1_pt_Den_1050_JPsi", binnum, bins);  
  h1_muon2_pt_Den_1050_JPsi                  = histoDir.make<TH1F>("mu2_pt_Den_1050_JPsi",   "mu2_pt_Den_1050_JPsi", binnum, bins);  
 
  h1_muon1_pt_Num_1050_JPsi                  = histoDir.make<TH1F>("mu1_pt_Num_1050_JPsi",   "mu1_pt_Num_1050_JPsi", binnum, bins);  
  h1_unmatched_muon1_pt_Num_1050_JPsi        = histoDir.make<TH1F>("unmatched_mu1_pt_Num_1050_JPsi",   "unmatched_mu1_pt_Num_1050_JPsi", binnum, bins);  

  h1_muon2_pt_Num_1050_JPsi                  = histoDir.make<TH1F>("mu2_pt_Num_1050_JPsi",   "mu2_pt_Num_1050_JPsi", binnum, bins);  
  h1_muon1_eta_Den_1050_JPsi                  = histoDir.make<TH1F>("mu1_eta_Den_1050_JPsi",   "mu1_eta_Den_1050_JPsi", 600, -3.0, 3.0);  
  h1_muon2_eta_Den_1050_JPsi                  = histoDir.make<TH1F>("mu2_eta_Den_1050_JPsi",   "mu2_eta_Den_1050_JPsi", 600, -3.0, 3.0);  
  h1_muon1_eta_Num_1050_JPsi                  = histoDir.make<TH1F>("mu1_eta_Num_1050_JPsi",   "mu1_eta_Num_1050_JPsi", 600, -3.0, 3.0);  
  h1_muon2_eta_Num_1050_JPsi                  = histoDir.make<TH1F>("mu2_eta_Num_1050_JPsi",   "mu2_eta_Num_1050_JPsi", 600, -3.0, 3.0);  
  h1_muon1_phi_Den_1050_JPsi                  = histoDir.make<TH1F>("mu1_phi_Den_1050_JPsi",   "mu1_phi_Den_1050_JPsi", 800, -4.0, 4.0);  
  h1_muon2_phi_Den_1050_JPsi                  = histoDir.make<TH1F>("mu2_phi_Den_1050_JPsi",   "mu2_phi_Den_1050_JPsi", 800, -4.0, 4.0);  
  h1_muon1_phi_Num_1050_JPsi                  = histoDir.make<TH1F>("mu1_phi_Num_1050_JPsi",   "mu1_phi_Num_1050_JPsi", 800, -4.0, 4.0);  
  h1_muon2_phi_Num_1050_JPsi                  = histoDir.make<TH1F>("mu2_phi_Num_1050_JPsi",   "mu2_phi_Num_1050_JPsi", 800, -4.0, 4.0);  
  h1_nPV_Num_1050_JPsi                    = histoDir.make<TH1F>("nPV_Num_1050_JPsi",   "nPV_Num_1050_JPsi", 100, 0, 100);  
  h1_nPV_Den_1050_JPsi                    = histoDir.make<TH1F>("nPV_Den_1050_JPsi",   "nPV_Den_1050_JPsi", 100, 0, 100);  
  h1_nDV_Num_1050_JPsi                    = histoDir.make<TH1F>("nDV_Num_1050_JPsi",   "nDV_Num_1050_JPsi", 100, 0, 100);  
  h1_nDV_Den_1050_JPsi                    = histoDir.make<TH1F>("nDV_Den_1050_JPsi",   "nDV_Den_1050_JPsi", 100, 0, 100);  
  h2_nPV_nDV_Num_1050_JPsi                = histoDir.make<TH2F>("nPV_nDV_Num_1050_JPsi",   "nPV_nDV_Num_1050_JPsi", 100, 0, 100, 20, 0, 20)  ;
  h2_nPV_nDV_Den_1050_JPsi                = histoDir.make<TH2F>("nPV_nDV_Den_1050_JPsi",   "nPV_nDV_Den_1050_JPsi", 100, 0, 100, 20, 0, 20)  ;
  //
  h1_muon1_chi2_by_ndof_Num_1050_JPsi     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Num_1050_JPsi",   "muon1_chi2_by_ndof_Num_1050_JPsi", 120, 0, 12);
  h1_muon1_chi2_by_ndof_Den_1050_JPsi     = histoDir.make<TH1F>("muon1_chi2_by_ndof_Den_1050_JPsi",   "muon1_chi2_by_ndof_Den_1050_JPsi", 120, 0, 12);
  //
  h1_muon2_chi2_by_ndof_Num_1050_JPsi     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Num_1050_JPsi",   "muon2_chi2_by_ndof_Num_1050_JPsi", 120, 0, 12);
  h1_muon2_chi2_by_ndof_Den_1050_JPsi     = histoDir.make<TH1F>("muon2_chi2_by_ndof_Den_1050_JPsi",   "muon2_chi2_by_ndof_Den_1050_JPsi", 120, 0, 12);
  //
  h2_pt1_pt2_Num_1050_JPsi       = histoDir.make<TH2F>("pt1_pt2_Num_1050_JPsi",   "pt1_pt2_Num_1050_JPsi", 150, 0, 300, 150, 0, 300)  ;
  h2_pt1_pt2_Den_1050_JPsi       = histoDir.make<TH2F>("pt1_pt2_Den_1050_JPsi",   "pt1_pt2_Num_1050_JPsi", 150, 0, 300, 150, 0, 300)  ;


  h1_nPrimaryVtx                   = histoDir.make<TH1I>("nPrimaryVtx", "numPrimaryVtx", 50, -0.5, 49.5);
  h1_nDisplacedVtx                 = histoDir.make<TH1I>("nDisplacedVtx", "numDisplacedVtx", 50, -0.5, 49.5);
  h2_nPV_nDV                       = histoDir.make<TH2F>("nPV_nDV",   "nPV_nDV", 100, 0, 100, 20, 0, 20)  ;
  h2_DV_x_y                        =histoDir.make<TH2F>("DV_x_y",   "x_y_DV", 300, -1.5, 1.5, 300, -1.5, 1.5)  ;
  h1_dimuonMass                = histoDir.make<TH1F>("dimuMass", "Mmumu", 4000, 0, 200);
  h1_dimuondR                  = histoDir.make<TH1F>("dimudR", "dRmumu", 1000, 0, 10);
  h1_mu1_pt                        = histoDir.make<TH1F>("mu1_pt", "muon1_pt", 4000, 0, 200);
  h1_mu2_pt                        = histoDir.make<TH1F>("mu2_pt", "muon2_pt", 4000, 0, 200);
  h1_mu1_eta                        = histoDir.make<TH1F>("mu1_eta", "muon1_eta", 600, -3, 3);
  h1_mu2_eta                        = histoDir.make<TH1F>("mu2_eta", "muon2_eta", 600, -3, 3);
  h1_mu1_phi                        = histoDir.make<TH1F>("mu1_phi", "muon1_phi", 800, -4, 4);
  h1_mu2_phi                        = histoDir.make<TH1F>("mu2_phi", "muon2_phi", 800, -4, 4);
  h1_asym                      = histoDir.make<TH1F>("asym",   "muPt_asym", 2000, -1.0, 1.0);



}


DimuonScoutingAnalyzer::~DimuonScoutingAnalyzer()
{
}


// ------------ method called for each event  ------------
void
DimuonScoutingAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //    std::cout << "\nEVT" << std::endl;
  using namespace edm;

  TLorentzVector sel_muon1, sel_muon2;
  TLorentzVector mymu;
		
  passjetTrig1050=99;
  passNominalTrig=99;
  passMonTrig=99;
  mass=-99.0;
  nDisplacedVtx=-99;
  nPrimaryVtx=-99;
  dxy1=-10;
  dxy2=-10;
  dz1=-100;
  dz2=-100;
  chi2_by_ndof1 = -100;
  chi2_by_ndof2 =-100;
  
  edm::Handle<edm::TriggerResults> trgResultsHandle;
  iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
  const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);

  for (size_t i = 0; i < trgNames.size(); ++i) {
    const std::string &name = trgNames.triggerName(i);
    //    std::cout << "trig = " << name << "  pass? " << trgResultsHandle->accept(i)  << std::endl;
    
    if ( (name.find("DST_DoubleMu3_noVtx_CaloScouting_v") != std::string::npos )) {                                                                               
      passNominalTrig=trgResultsHandle->accept(i);                                                                                                                
    }     
    if ( (name.find("DST_DoubleMu3_noVtx_CaloScouting_Monitoring_v") != std::string::npos )) {                                                                    
      passMonTrig=trgResultsHandle->accept(i);                                                                                                                   
    }     
    //    edm::Handle<edm::TriggerResults> trgResultsHandleScouting;
    // iEvent.getByToken(trgResultsLabelScouting_, trgResultsHandleScouting);
    // const edm::TriggerNames &trgNames2 = iEvent.triggerNames(*trgResultsHandleScouting);
    // for (size_t i = 0; i < trgNames2.size(); ++i) {
    // const std::string &name = trgNames2.triggerName(i);
    if ( (name.find("HLT_PFHT1050_v") != std::string::npos )) {
      passjetTrig1050=trgResultsHandle->accept(i);
    }
  }
  std::vector<TLorentzVector> v_trig_muon;
  
  if (RunOnOfflineReco) {
    
    if (!passNominalTrig && passMonTrig) {  
      
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjectsScouting;
    iEvent.getByToken(triggerObjectsScouting_, triggerObjectsScouting);
    //std::cout << "TRIGGER OBJECTS " << std::endl;
    int counter=1;
    //      for (std::vector<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {
    for (pat::TriggerObjectStandAlone obj : *triggerObjectsScouting) { // note: not "const &" since we want to call unpackPathNames
      // std::cout << "obj=" << counter ;
      obj.unpackPathNames(trgNames);
      //        if (obj.collection()=="hltIterL3MuonCandidatesNoVtx::HLT") {
      if ( (obj.collection()=="hltIterL3MuonCandidates::HLT")   || (obj.collection()=="hltIterL3MuonCandidatesNoVtx::HLT")  ) {
	// std::cout << "passNominalTrig=" << passNominalTrig << " passMonTrig=" << passMonTrig << std::endl;
	//	std::cout << counter << "Trigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
	//std::cout << "Collection: " << obj.collection() << std::endl;
	counter++;
	TLorentzVector trig_muon;
	trig_muon.SetPxPyPzE(obj.px(), obj.py(), obj.pz(), obj.energy());
	v_trig_muon.push_back(trig_muon);
	 }
    }
    }
  
  }
  
  if (RunOnOfflineReco) {
    edm::Handle<reco::VertexCollection> primaryVtxHandle;
    iEvent.getByToken(primaryVtxLabel_, primaryVtxHandle);
    if (primaryVtxHandle->empty()) return; // skip the event if no PV found
    const reco::Vertex PV = (primaryVtxHandle->front());
    nPrimaryVtx=primaryVtxHandle->size() ;
    //std::cout << "nPrimaryVtx=" << nPrimaryVtx << std::endl; 
    
    edm::Handle<std::vector<pat::Muon>>  muonHandle;
    iEvent.getByToken(muonLabel_, muonHandle);
    
    for (std::vector<pat::Muon>::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {
      for (std::vector<pat::Muon>::const_iterator jMu = iMu+1; jMu != muonHandle->end(); ++jMu) {
	
	if (iMu->pt()>3.0 && jMu->pt()>3.0 ) {
	  if ( fabs(iMu->eta())<2.1 && fabs(jMu->eta())<2.1  ) {
	    if ( (iMu->charge())*(jMu->charge())<0 ) {
	      if ( (iMu->isTightMuon(PV)) && (jMu->isTightMuon(PV)) ) { 
		if (  ((iMu->isolationR03().sumPt/iMu->pt())<0.1)  &&  ((jMu->isolationR03().sumPt/jMu->pt())<0.1)  ) {
		  TLorentzVector mu1, mu2 ;
		  mu1.SetPxPyPzE(iMu->px(), iMu->py(), iMu->pz(), iMu->energy());
		  mu2.SetPxPyPzE(jMu->px(), jMu->py(), jMu->pz(), jMu->energy());
		  
		  TLorentzVector diMuon=mu1+mu2;
		  
		  if (diMuon.M()>mass)   {
		    mass=diMuon.M();
		    //std::cout << "mass=" << mass << std::endl;
		    
		    if (mu1.Pt() >= mu2.Pt()) {
		      sel_muon1=mu1;
		      sel_muon2=mu2;
		      
		    } else if (mu1.Pt() < mu2.Pt()) {
		      sel_muon1=mu2;
		      sel_muon2=mu1;
		    }
		    chi2_by_ndof1 =0;// iMu->normChi2();   //chi2()/iMu->ndof();
		    chi2_by_ndof2 =0;// jMu->normChi2();   //chi2()/jMu->ndof();			
		    
		    dxy1 =0;//=iMu->dxy();
		    dxy2 =0;//=jMu->dxy();
		    
		    dz1= 0;//iMu->dz();
		    dz2= 0;//jMu->dz();
		    //		  std::cout << "dxy1 / dxy2 " << dxy1 << " / " << dxy2 << std::endl;  
		    int rand1 = rand();
		    // std::cout << "rand1=" << rand1 << " rand1%2=" << rand1%2 << std::endl;                        
		    if ( (rand1%2)==0 )  asym = (sel_muon1.Pt()-sel_muon2.Pt())/(sel_muon1.Pt()+sel_muon2.Pt());
		    else if ( (rand1%2)==1 )  asym = (sel_muon2.Pt()-sel_muon1.Pt())/(sel_muon1.Pt()+sel_muon2.Pt());
		  }
		}      
	      }
	    }
	  }
	}
      }
    }
      
     
      //if (RunOnOfflineReco) {
       //per muon efficiency// 
    for (std::vector<pat::Muon>::const_iterator kMu = muonHandle->begin(); kMu != muonHandle->end(); ++kMu) {
      if (kMu->pt()>3.0) {
	if ( fabs(kMu->eta())<2.1 ) {
	  if ( (kMu->isTightMuon(PV)) ) { 
	    if ((kMu->isolationR03().sumPt/kMu->pt())<0.1) {
	      mymu.Clear();
	      mymu.SetPxPyPzE(kMu->px(), kMu->py(), kMu->pz(), kMu->energy());
	      if (passMonTrig==1) {
		h1_permuon_pt_Den_Mon->Fill(mymu.Pt());
		h1_permuon_eta_Den_Mon->Fill(mymu.Eta());
		h1_permuon_phi_Den_Mon->Fill(mymu.Phi());
		// std::cout << "passNominalTrig=" << passNominalTrig << " passMonTrig=" << passMonTrig << std::endl;
		//std::cout << "offline muon found" << std::endl;
		if (trigMatched(RunOnOfflineReco,mymu,v_trig_muon) ) {
		  h1_permuon_pt_Num_Mon->Fill(mymu.Pt());
		  h1_permuon_eta_Num_Mon->Fill(mymu.Eta());
		  h1_permuon_phi_Num_Mon->Fill(mymu.Phi());
		  //std::cout << "offline muon matched to HLT muon" << std::endl;
		}
	      }
	    }      
	  }
	}
      }
    }
  }
  
  if (!RunOnOfflineReco) {
    edm::Handle<ScoutingVertexCollection> primaryVtxHandle;
    iEvent.getByToken(primaryVtxLabelScouting_, primaryVtxHandle);
    if (primaryVtxHandle.isValid())  nPrimaryVtx=primaryVtxHandle->size() ;
    
    edm::Handle<ScoutingVertexCollection> displacedVtxHandle;
    iEvent.getByToken(displacedVtxLabel_, displacedVtxHandle);
    if (displacedVtxHandle.isValid())  {
      nDisplacedVtx=displacedVtxHandle->size() ;
      
    }
    // std::cout << "nDisp = " << nDisplacedVtx << std::endl;
    
    edm::Handle<ScoutingMuonCollection>  muonHandle;
    iEvent.getByToken(muonLabelScouting_, muonHandle);
    for (ScoutingMuonCollection::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {
      for (ScoutingMuonCollection::const_iterator jMu = iMu+1; jMu != muonHandle->end(); ++jMu) {
	
	//      std::cout << "trkiso/pt <0.1? " << iMu->trackIso()/iMu->pt() << " / " << jMu->trackIso()/jMu->pt() << std::endl;      
	//	      std::cout <<   "\n\nglobal    "   <<  iMu->isGlobalMuon()  <<   "/" << jMu->isGlobalMuon() << std::endl; 
	//	      std::cout <<   "tracker  "  <<	iMu->isTrackerMuon() <<   "/" << jMu->isTrackerMuon() << std::endl;   
	// std::cout <<   "normalised chi2  "  <<  iMu->chi2()/iMu->ndof() << "/"  << jMu->chi2()/jMu->ndof() << std::endl;
	   //	      std::cout <<   "ndof2  "  <<  iMu->ndof() << "/"  << jMu->ndof() << std::endl;
	   // std::cout <<   "pt  "    <<  iMu->pt()  << "/"   << jMu->pt() << std::endl;
	   //      std::cout <<   "eta  "   <<  fabs(iMu->eta()) << "/" << fabs(jMu->eta()) << std::endl;
	   //  std::cout <<   "nTrackerLayers >5 ? "  << iMu->nTrackerLayersWithMeasurement() << "/" << jMu->nTrackerLayersWithMeasurement()   << std::endl;
	   //  std::cout <<   "nValidMuonHits >0 ? "  << iMu->nValidMuonHits() << "/"  << jMu->nValidMuonHits() << std::endl;
	   //  std::cout <<   "nValidPixelHits " <<  iMu->nValidPixelHits() << "/" << jMu->nValidPixelHits() << std::endl;
	   // std::cout <<   "charge "   << iMu->charge() << "/" << jMu->charge() << std::endl;
	   //      std::cout << "nMatchedStations >1 ? " << iMu->nMatchedStations() << "/" << jMu->nMatchedStations() << std::endl;
	   
	   if (iMu->pt()>3.0 && jMu->pt()>3.0 ) {
	     if ( fabs(iMu->eta())<2.1 && fabs(jMu->eta())<2.1  ) {
	       if ( (iMu->charge())*(jMu->charge())<0 ) {
		 if ( iMu->nTrackerLayersWithMeasurement()>5 && jMu->nTrackerLayersWithMeasurement()>5 ) {
		   if (  (iMu->chi2()/iMu->ndof())<10 && (jMu->chi2()/jMu->ndof())<10) {
		     if ( (iMu->nValidPixelHits()>0) && (jMu->nValidPixelHits()>0)) {
		       // if ( iMu->nValidMuonHits()>0 && jMu->nValidMuonHits()>0 ) {
		       // if ( iMu->nMatchedStations()>1 && jMu->nMatchedStations()>1 ) {
		       if ( (iMu->trackIso()/iMu->pt())<0.1  &&  (jMu->trackIso()/jMu->pt())<0.1 ) { 
			 
			 TLorentzVector mu1, mu2 ;
			 //mu1.SetPxPyPzE(iMu->px(), iMu->py(), iMu->pz(), iMu->energy());
			 //	mu2.SetPxPyPzE(jMu->px(), jMu->py(), jMu->pz(), jMu->energy());
			 mu1.SetPtEtaPhiM(iMu->pt(), iMu->eta(), iMu->phi(), iMu->m());
			 mu2.SetPtEtaPhiM(jMu->pt(), jMu->eta(), jMu->phi(), jMu->m());
			 
			 TLorentzVector diMuon=mu1+mu2;
			 
			 if (diMuon.M()>mass)   {
			   mass=diMuon.M();
			   //std::cout << "mass=" << mass << std::endl;
			   if (mu1.Pt() >= mu2.Pt()) {
			     sel_muon1=mu1;
			     sel_muon2=mu2;
			     
			   } else if (mu1.Pt() < mu2.Pt()) {
			     sel_muon1=mu2;
			     sel_muon2=mu1;
			   }
			   chi2_by_ndof1 = iMu->chi2()/iMu->ndof();
			   chi2_by_ndof2 =jMu->chi2()/jMu->ndof();			
			   
			   dxy1 =iMu->dxy();
			   dxy2 =jMu->dxy();
			   
			   dz1= iMu->dz();
			   dz2= jMu->dz();
			   //		  std::cout << "dxy1 / dxy2 " << dxy1 << " / " << dxy2 << std::endl;  
			   int rand1 = rand();
			   // std::cout << "rand1=" << rand1 << " rand1%2=" << rand1%2 << std::endl;                        
			   if ( (rand1%2)==0 )  asym = (sel_muon1.Pt()-sel_muon2.Pt())/(sel_muon1.Pt()+sel_muon2.Pt());
			   else if ( (rand1%2)==1 )  asym = (sel_muon2.Pt()-sel_muon1.Pt())/(sel_muon1.Pt()+sel_muon2.Pt());
			   
			 }      
		       }
		     }
		   }
		 }
	       }
	     }
	   }
	 }
       }
     }
     //    std::cout << "dimuon mass = " << mass << std::endl;
     
     if ( (!passNominalTrig) && (!passMonTrig) ) {  //std::cout << "No trig pass. Why this evt is in this dataset !" << std::endl;
       h1_check->Fill(5);
     }
     //     std::cout << "passNominalTrig = " << passNominalTrig << std::endl;
     // if (mass>0  && (!passNominalTrig) ) {
       //  std::cout << "*** **** PROBLEM **** ***" << " mass=" << mass  <<  " passNominalTrig=" << passNominalTrig 
       //	<<  " passjetTrig=" << passjetTrig1050 << " passMonTrig=" << passMonTrig << std::endl;
     // }
     //   std::cout << "\n\n";

     float dR=sel_muon1.DeltaR(sel_muon2);

     //     if (RunOnOfflineReco) {
     //     std::cout << "mu 1 matched? " <<   trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon) << std::endl;
     //  std::cout << "mu 2 matched? " <<   trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon) << std::endl;
       // }
     // std::cout << "offline dimuon mass = " << mass << std::endl;
     //  std::cout << "offline pt 1,2 " << sel_muon1.Pt() << " " << sel_muon2.Pt() <<  std::endl;
     
     if ( (mass>0) && (passjetTrig1050==1) ) {
       //std::cout << "==============================Enters denominator" << std::endl;
       h2_pt1_pt2_Den_1050->Fill(sel_muon1.Pt(),sel_muon2.Pt());
       h1_dxy1_Den_1050->Fill(dxy1);
       h1_dxy2_Den_1050->Fill(dxy2);
       h1_dz1_Den_1050->Fill(dz1);
       h1_dz2_Den_1050->Fill(dz2);
       h1_dimuonMass_Den_1050->Fill(mass);
       h1_dimuondR_Den_1050->Fill(dR);
       h1_muon1_pt_Den_1050->Fill(sel_muon1.Pt());
       h1_muon2_pt_Den_1050->Fill(sel_muon2.Pt());
       h1_muon1_eta_Den_1050->Fill(sel_muon1.Eta());
       h1_muon2_eta_Den_1050->Fill(sel_muon2.Eta());
       h1_muon1_phi_Den_1050->Fill(sel_muon1.Phi());
       h1_muon2_phi_Den_1050->Fill(sel_muon2.Phi());
       h1_nPV_Den_1050->Fill(nPrimaryVtx); 
       h1_nDV_Den_1050->Fill(nDisplacedVtx);
       h2_nPV_nDV_Den_1050->Fill(nPrimaryVtx,nDisplacedVtx);
       h1_muon1_chi2_by_ndof_Den_1050->Fill(chi2_by_ndof1);
       h1_muon2_chi2_by_ndof_Den_1050->Fill(chi2_by_ndof2);
     }

     if ( (mass>0) && (passjetTrig1050==1) && (passNominalTrig==1) ) { 
       h1_unmatched_muon1_pt_Num_1050->Fill(sel_muon1.Pt());
       if (trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon) && trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon) ) {
	 //std::cout << "===================================Enters numerator" << std::endl;
	 h2_pt1_pt2_Num_1050->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dxy1_Num_1050->Fill(dxy1);
	 h1_dxy2_Num_1050->Fill(dxy2);
	 h1_dz1_Num_1050->Fill(dz1);
	 h1_dz2_Num_1050->Fill(dz2);
	 h1_dimuonMass_Num_1050->Fill(mass);
	 h1_dimuondR_Num_1050->Fill(dR);
	 h1_muon1_pt_Num_1050->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_1050->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_1050->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_1050->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_1050->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_1050->Fill(sel_muon2.Phi());
	 h1_nPV_Num_1050->Fill(nPrimaryVtx); 
	 h1_nDV_Num_1050->Fill(nDisplacedVtx);
	 h2_nPV_nDV_Num_1050->Fill(nPrimaryVtx,nDisplacedVtx); 
	 h1_muon1_chi2_by_ndof_Num_1050->Fill(chi2_by_ndof1);
	 h1_muon2_chi2_by_ndof_Num_1050->Fill(chi2_by_ndof2);
       }
     }
     //

     if ( (mass>0) && (passMonTrig==1) ) {
       // std::cout << "===========================================Enters denominator" << std::endl;
       h2_pt1_pt2_Den_Mon->Fill(sel_muon1.Pt(),sel_muon2.Pt());
       h1_dxy1_Den_Mon->Fill(dxy1);
       h1_dxy2_Den_Mon->Fill(dxy2);
       h1_dz1_Den_Mon->Fill(dz1);
       h1_dz2_Den_Mon->Fill(dz2);
       h1_dimuonMass_Den_Mon->Fill(mass);
       h1_dimuondR_Den_Mon->Fill(dR);
       h1_muon1_pt_Den_Mon->Fill(sel_muon1.Pt());
       h1_muon2_pt_Den_Mon->Fill(sel_muon2.Pt());
       h1_muon1_eta_Den_Mon->Fill(sel_muon1.Eta());
       h1_muon2_eta_Den_Mon->Fill(sel_muon2.Eta());
       h1_muon1_phi_Den_Mon->Fill(sel_muon1.Phi());
       h1_muon2_phi_Den_Mon->Fill(sel_muon2.Phi());
       h1_nPV_Den_Mon->Fill(nPrimaryVtx);
       h1_nDV_Den_Mon->Fill(nDisplacedVtx);   
       h2_nPV_nDV_Den_Mon->Fill(nPrimaryVtx,nDisplacedVtx);
       h1_muon1_chi2_by_ndof_Den_Mon->Fill(chi2_by_ndof1);
       h1_muon2_chi2_by_ndof_Den_Mon->Fill(chi2_by_ndof2);
       
     }

     if ( (mass>0) && (passMonTrig==1) && (passNominalTrig==1)) { 
       h1_unmatched_muon1_pt_Num_Mon->Fill(sel_muon1.Pt());
       if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon) && trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	 // std::cout << "======================================Enters numerator" << std::endl;
	 //h2_deta_dphi_passMon_passSig->();
	 h2_pt1_pt2_Num_Mon->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dxy1_Num_Mon->Fill(dxy1);
	 h1_dxy2_Num_Mon->Fill(dxy2);
	 h1_dz1_Num_Mon->Fill(dz1);
	 h1_dz2_Num_Mon->Fill(dz2);
	 h1_dimuonMass_Num_Mon->Fill(mass);
	 h1_dimuondR_Num_Mon->Fill(dR);
	 h1_muon1_pt_Num_Mon->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_Mon->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_Mon->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_Mon->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_Mon->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_Mon->Fill(sel_muon2.Phi());
	 h1_nPV_Num_Mon->Fill(nPrimaryVtx);
	 h1_nDV_Num_Mon->Fill(nDisplacedVtx); 
	 h2_nPV_nDV_Num_Mon->Fill(nPrimaryVtx,nDisplacedVtx);
	 h1_muon1_chi2_by_ndof_Num_Mon->Fill(chi2_by_ndof1);
	 h1_muon2_chi2_by_ndof_Num_Mon->Fill(chi2_by_ndof2);
       }
     }

     //hltonly
     if ( (mass>0) && (passMonTrig==1) ) { 
       if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon) && trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	 // std::cout << "======================================Enters numerator" << std::endl;
	 h2_pt1_pt2_Num_Mon_HLTonly->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dimuonMass_Num_Mon_HLTonly->Fill(mass);
	 h1_dimuondR_Num_Mon_HLTonly->Fill(dR);
	 h1_muon1_pt_Num_Mon_HLTonly->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_Mon_HLTonly->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_Mon_HLTonly->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_Mon_HLTonly->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_Mon_HLTonly->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_Mon_HLTonly->Fill(sel_muon2.Phi());
       }
     }

     //
     ///////
     
     if ( (mass>3.0) && (mass<3.2) && (passMonTrig==1) ) {
       // std::cout << "==========================================Enters denominator" << std::endl;
       h2_pt1_pt2_Den_Mon_JPsi->Fill(sel_muon1.Pt(),sel_muon2.Pt());
       h1_dxy1_Den_Mon_JPsi->Fill(dxy1);
       h1_dxy2_Den_Mon_JPsi->Fill(dxy2);
       h1_dz1_Den_Mon_JPsi->Fill(dz1);
       h1_dz2_Den_Mon_JPsi->Fill(dz2);
       h1_dimuonMass_Den_Mon_JPsi->Fill(mass);
       h1_dimuondR_Den_Mon_JPsi->Fill(dR);
       h1_muon1_pt_Den_Mon_JPsi->Fill(sel_muon1.Pt());
       h1_muon2_pt_Den_Mon_JPsi->Fill(sel_muon2.Pt());
       h1_muon1_eta_Den_Mon_JPsi->Fill(sel_muon1.Eta());
       h1_muon2_eta_Den_Mon_JPsi->Fill(sel_muon2.Eta());
       h1_muon1_phi_Den_Mon_JPsi->Fill(sel_muon1.Phi());
       h1_muon2_phi_Den_Mon_JPsi->Fill(sel_muon2.Phi());
       h1_nPV_Den_Mon_JPsi->Fill(nPrimaryVtx);
       h1_nDV_Den_Mon_JPsi->Fill(nDisplacedVtx);   
       h2_nPV_nDV_Den_Mon_JPsi->Fill(nPrimaryVtx,nDisplacedVtx);
       h1_muon1_chi2_by_ndof_Den_Mon_JPsi->Fill(chi2_by_ndof1);
       h1_muon2_chi2_by_ndof_Den_Mon_JPsi->Fill(chi2_by_ndof2);
     }
     
     if ( (mass>3.0) && (mass<3.2) && (passMonTrig==1) && (passNominalTrig==1) ) { 
       h1_unmatched_muon1_pt_Num_Mon_JPsi->Fill(sel_muon1.Pt());
       if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon), trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	 // std::cout << "==========================================Enters numerator" << std::endl;
	 h2_pt1_pt2_Num_Mon_JPsi->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dxy1_Num_Mon_JPsi->Fill(dxy1);
	 h1_dxy2_Num_Mon_JPsi->Fill(dxy2);
	 h1_dz1_Num_Mon_JPsi->Fill(dz1);
	 h1_dz2_Num_Mon_JPsi->Fill(dz2);
	 h1_dimuonMass_Num_Mon_JPsi->Fill(mass);
	 h1_dimuondR_Num_Mon_JPsi->Fill(dR);
	 h1_muon1_pt_Num_Mon_JPsi->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_Mon_JPsi->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_Mon_JPsi->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_Mon_JPsi->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_Mon_JPsi->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_Mon_JPsi->Fill(sel_muon2.Phi());
	 h1_nPV_Num_Mon_JPsi->Fill(nPrimaryVtx);
	 h1_nDV_Num_Mon_JPsi->Fill(nDisplacedVtx); 
	 h2_nPV_nDV_Num_Mon_JPsi->Fill(nPrimaryVtx,nDisplacedVtx);
	 h1_muon1_chi2_by_ndof_Num_Mon_JPsi->Fill(chi2_by_ndof1);
	 h1_muon2_chi2_by_ndof_Num_Mon_JPsi->Fill(chi2_by_ndof2);
       } 
     }
     //


     //// Z ////
     if ( (mass>60.0) && (mass<120.0) && (passMonTrig==1) ) {
       // std::cout << "==========================================Enters denominator" << std::endl;
       h2_pt1_pt2_Den_Mon_Z->Fill(sel_muon1.Pt(),sel_muon2.Pt());
       h1_dxy1_Den_Mon_Z->Fill(dxy1);
       h1_dxy2_Den_Mon_Z->Fill(dxy2);
       h1_dz1_Den_Mon_Z->Fill(dz1);
       h1_dz2_Den_Mon_Z->Fill(dz2);
       h1_dimuonMass_Den_Mon_Z->Fill(mass);
       h1_dimuondR_Den_Mon_Z->Fill(dR);
       h1_muon1_pt_Den_Mon_Z->Fill(sel_muon1.Pt());
       h1_muon2_pt_Den_Mon_Z->Fill(sel_muon2.Pt());
       h1_muon1_eta_Den_Mon_Z->Fill(sel_muon1.Eta());
       h1_muon2_eta_Den_Mon_Z->Fill(sel_muon2.Eta());
       h1_muon1_phi_Den_Mon_Z->Fill(sel_muon1.Phi());
       h1_muon2_phi_Den_Mon_Z->Fill(sel_muon2.Phi());
       h1_nPV_Den_Mon_Z->Fill(nPrimaryVtx);
       h1_nDV_Den_Mon_Z->Fill(nDisplacedVtx);   
       h2_nPV_nDV_Den_Mon_Z->Fill(nPrimaryVtx,nDisplacedVtx);
       h1_muon1_chi2_by_ndof_Den_Mon_Z->Fill(chi2_by_ndof1);
       h1_muon2_chi2_by_ndof_Den_Mon_Z->Fill(chi2_by_ndof2);
     }
     
     if ( (mass>60.0) && (mass<120.0) && (passMonTrig==1) && (passNominalTrig==1) ) { 
       h1_unmatched_muon1_pt_Num_Mon_Z->Fill(sel_muon1.Pt());
       if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon), trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	 // std::cout << "==========================================Enters numerator" << std::endl;
	 h2_pt1_pt2_Num_Mon_Z->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dxy1_Num_Mon_Z->Fill(dxy1);
	 h1_dxy2_Num_Mon_Z->Fill(dxy2);
	 h1_dz1_Num_Mon_Z->Fill(dz1);
	 h1_dz2_Num_Mon_Z->Fill(dz2);
	 h1_dimuonMass_Num_Mon_Z->Fill(mass);
	 h1_dimuondR_Num_Mon_Z->Fill(dR);
	 h1_muon1_pt_Num_Mon_Z->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_Mon_Z->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_Mon_Z->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_Mon_Z->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_Mon_Z->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_Mon_Z->Fill(sel_muon2.Phi());
	 h1_nPV_Num_Mon_Z->Fill(nPrimaryVtx);
	 h1_nDV_Num_Mon_Z->Fill(nDisplacedVtx); 
	 h2_nPV_nDV_Num_Mon_Z->Fill(nPrimaryVtx,nDisplacedVtx);
	 h1_muon1_chi2_by_ndof_Num_Mon_Z->Fill(chi2_by_ndof1);
	 h1_muon2_chi2_by_ndof_Num_Mon_Z->Fill(chi2_by_ndof2);
       } 
     }

     if ( (mass>3.0) && (mass<3.2) && (passMonTrig==1) ) { 
       if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon), trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	 // std::cout << "==========================================Enters numerator" << std::endl;
	 h2_pt1_pt2_Num_Mon_JPsi_HLTonly->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	 h1_dxy1_Num_Mon_JPsi_HLTonly->Fill(dxy1);
	 h1_dxy2_Num_Mon_JPsi_HLTonly->Fill(dxy2);
	 h1_dz1_Num_Mon_JPsi_HLTonly->Fill(dz1);
	 h1_dz2_Num_Mon_JPsi_HLTonly->Fill(dz2);
	 h1_dimuonMass_Num_Mon_JPsi_HLTonly->Fill(mass);
	 h1_dimuondR_Num_Mon_JPsi_HLTonly->Fill(dR);
	 h1_muon1_pt_Num_Mon_JPsi_HLTonly->Fill(sel_muon1.Pt());
	 h1_muon2_pt_Num_Mon_JPsi_HLTonly->Fill(sel_muon2.Pt());
	 h1_muon1_eta_Num_Mon_JPsi_HLTonly->Fill(sel_muon1.Eta());
	 h1_muon2_eta_Num_Mon_JPsi_HLTonly->Fill(sel_muon2.Eta());
	 h1_muon1_phi_Num_Mon_JPsi_HLTonly->Fill(sel_muon1.Phi());
	 h1_muon2_phi_Num_Mon_JPsi_HLTonly->Fill(sel_muon2.Phi());
	 h1_nPV_Num_Mon_JPsi_HLTonly->Fill(nPrimaryVtx);
	 h1_nDV_Num_Mon_JPsi_HLTonly->Fill(nDisplacedVtx); 
	 h2_nPV_nDV_Num_Mon_JPsi_HLTonly->Fill(nPrimaryVtx,nDisplacedVtx);
	 h1_muon1_chi2_by_ndof_Num_Mon_JPsi_HLTonly->Fill(chi2_by_ndof1);
	 h1_muon2_chi2_by_ndof_Num_Mon_JPsi_HLTonly->Fill(chi2_by_ndof2);
       } 
     }

     //////// ******* //////////
     if ( (mass>3.0) && (mass<3.2) && (passjetTrig1050==1) ) {
       //  std::cout << "===============================================Enters denominator" << std::endl;
       h2_pt1_pt2_Den_1050_JPsi->Fill(sel_muon1.Pt(),sel_muon2.Pt());
       h1_dxy1_Den_1050_JPsi->Fill(dxy1);
       h1_dxy2_Den_1050_JPsi->Fill(dxy2);
       h1_dz1_Den_1050_JPsi->Fill(dz1);
       h1_dz2_Den_1050_JPsi->Fill(dz2);
       h1_dimuonMass_Den_1050_JPsi->Fill(mass);
       h1_dimuondR_Den_1050_JPsi->Fill(dR);
       h1_muon1_pt_Den_1050_JPsi->Fill(sel_muon1.Pt());
       h1_muon2_pt_Den_1050_JPsi->Fill(sel_muon2.Pt());
       h1_muon1_eta_Den_1050_JPsi->Fill(sel_muon1.Eta());
       h1_muon2_eta_Den_1050_JPsi->Fill(sel_muon2.Eta());
       h1_muon1_phi_Den_1050_JPsi->Fill(sel_muon1.Phi());
       h1_muon2_phi_Den_1050_JPsi->Fill(sel_muon2.Phi());
       h1_nPV_Den_1050_JPsi->Fill(nPrimaryVtx);
       h1_nDV_Den_1050_JPsi->Fill(nDisplacedVtx);   
       h2_nPV_nDV_Den_1050_JPsi->Fill(nPrimaryVtx,nDisplacedVtx);
       h1_muon1_chi2_by_ndof_Den_1050_JPsi->Fill(chi2_by_ndof1);
       h1_muon2_chi2_by_ndof_Den_1050_JPsi->Fill(chi2_by_ndof2);
     }
     
     if ( (mass>3.0) && (mass<3.2) && (passjetTrig1050==1) && (passNominalTrig==1) ) {
       h1_unmatched_muon1_pt_Num_1050_JPsi->Fill(sel_muon1.Pt());
	 if ( trigMatched(RunOnOfflineReco,sel_muon1,v_trig_muon), trigMatched(RunOnOfflineReco,sel_muon2,v_trig_muon)) {
	   // std::cout << "=============================================Enters numerator" << std::endl;
	   h2_pt1_pt2_Num_1050_JPsi->Fill(sel_muon1.Pt(),sel_muon2.Pt());
	   h1_dxy1_Num_1050_JPsi->Fill(dxy1);
	   h1_dxy2_Num_1050_JPsi->Fill(dxy2);
	   h1_dz1_Num_1050_JPsi->Fill(dz1);
	   h1_dz2_Num_1050_JPsi->Fill(dz2);
	   h1_dimuonMass_Num_1050_JPsi->Fill(mass);
	   h1_dimuondR_Num_1050_JPsi->Fill(dR);
	   h1_muon1_pt_Num_1050_JPsi->Fill(sel_muon1.Pt());
	   h1_muon2_pt_Num_1050_JPsi->Fill(sel_muon2.Pt());
	   h1_muon1_eta_Num_1050_JPsi->Fill(sel_muon1.Eta());
	   h1_muon2_eta_Num_1050_JPsi->Fill(sel_muon2.Eta());
	   h1_muon1_phi_Num_1050_JPsi->Fill(sel_muon1.Phi());
	   h1_muon2_phi_Num_1050_JPsi->Fill(sel_muon2.Phi());
	   h1_nPV_Num_1050_JPsi->Fill(nPrimaryVtx);
	   h1_nDV_Num_1050_JPsi->Fill(nDisplacedVtx); 
	   h2_nPV_nDV_Num_1050_JPsi->Fill(nPrimaryVtx,nDisplacedVtx);
	   h1_muon1_chi2_by_ndof_Num_1050_JPsi->Fill(chi2_by_ndof1);
	   h1_muon2_chi2_by_ndof_Num_1050_JPsi->Fill(chi2_by_ndof2);
	 }
     }

     if ( (passNominalTrig) && (mass>0) && (!RunOnOfflineReco) ) {
       edm::Handle<ScoutingVertexCollection> displacedVtxHandle;
       iEvent.getByToken(displacedVtxLabel_, displacedVtxHandle);
       if (displacedVtxHandle.isValid()) {
	 for (ScoutingVertexCollection::const_iterator iVtx = displacedVtxHandle->begin(); iVtx != displacedVtxHandle->end(); ++iVtx) {
	   //std::cout << "x,y=" << iVtx->x() << "," << iVtx->y() << std::endl;
	   h2_DV_x_y->Fill(iVtx->x(),iVtx->y());
	 }
       }
     }
     
     if (passNominalTrig && (mass>0) ) {
       h1_dimuonMass->Fill(mass) ;
       h1_dimuondR->Fill(dR) ;
       h1_mu1_pt->Fill(sel_muon1.Pt());
       h1_mu2_pt->Fill(sel_muon2.Pt());
       h1_mu1_eta->Fill(sel_muon1.Eta());
       h1_mu2_eta->Fill(sel_muon2.Eta());
       h1_mu1_phi->Fill(sel_muon1.Phi());
       h1_mu2_phi->Fill(sel_muon2.Phi());
       h1_nPrimaryVtx->Fill(nPrimaryVtx);
       h1_nDisplacedVtx->Fill(nDisplacedVtx);
       h2_nPV_nDV->Fill(nPrimaryVtx,nDisplacedVtx);
       // h2_DV_x_y->Fill();
       h1_asym->Fill(asym);                                                                                                                                            
       
     }  
  
#ifdef THIS_IS_AN_EVENT_EXAMPLE
     Handle<ExampleData> pIn;
     iEvent.getByLabel("example",pIn);
#endif
     
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
     ESHandle<SetupData> pSetup;
     iSetup.get<SetupRecord>().get(pSetup);
#endif
}



bool DimuonScoutingAnalyzer::trigMatched(bool RunOnOfflineReco_,TLorentzVector offlineMu,std::vector<TLorentzVector> onlineMuVect) {
  bool pass=false;
  if (!RunOnOfflineReco) pass=true;
  float dR12=999.0;
  int size=onlineMuVect.size();
  //  std::cout << "In trigMatched. size=" << size << std::endl;
  for (int n=0; n<size; n++) {
    float mydR12=offlineMu.DeltaR(onlineMuVect.at(n));
    if (mydR12<dR12) dR12=mydR12;
  }
  if (dR12<0.1) pass=true;
  // std::cout << "dr=" << dR12 << std::endl;
  return pass;
}

// ------------ method called once each job just before starting event loop  ------------
void 
DimuonScoutingAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DimuonScoutingAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DimuonScoutingAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DimuonScoutingAnalyzer);
