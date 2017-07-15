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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include <TLorentzVector.h>
#include "TH1.h"

class DimuonScoutingAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit DimuonScoutingAnalyzer(const edm::ParameterSet&);
  ~DimuonScoutingAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabelScouting_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabel_;
  edm::EDGetTokenT<ScoutingVertexCollection>       primaryVtxLabel_;
  edm::EDGetTokenT<ScoutingVertexCollection>       displacedVtxLabel_;
  edm::Service<TFileService> fs;
  
  int passNominalTrig;
  int passjetTrig;
  int passMonitoringTrig;
  double mass;
  int nDisplacedVtx;
  int nPrimaryVtx;
  TLorentzVector sel_muon1, sel_muon2;
  
  TH1F* h1_dimuonMass_Den;
  TH1F* h1_dimuonMass_Num;

  TH1F*  h1_muon1_pt_Num;
  TH1F*  h1_muon2_pt_Num;

  TH1F*  h1_muon1_pt_Den;
  TH1F*  h1_muon2_pt_Den;

  TH1F* h1_dimuonMass;
  TH1I *h1_nPrimaryVtx;
  TH1I *h1_nDisplacedVtx;
  TH1F *h1_mu1_pt;
  TH1F *h1_mu2_pt;
  
};


DimuonScoutingAnalyzer::DimuonScoutingAnalyzer(const edm::ParameterSet& iConfig)
  
{
  trgResultsLabelScouting_   = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultsScouting"));
  trgResultsLabel_          = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  muonLabel_                 = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  primaryVtxLabel_           = consumes<ScoutingVertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVtx"));
  displacedVtxLabel_         = consumes<ScoutingVertexCollection>(iConfig.getParameter<edm::InputTag>("displacedVtx"));
  usesResource("TFileService");
  
  TFileDirectory histoDir = fs->mkdir("histoDir");
  
  Float_t bins[] = {0.,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,25,30,40,50,60,70,80,90,100};
  Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1; // or just write the number
    
  h1_dimuonMass                = histoDir.make<TH1F>("dimuMass", "Mmumu", binnum, bins);
  
  h1_dimuonMass_Den                = histoDir.make<TH1F>("dimuMass_Den", "Mmumu_Den", binnum, bins);
  h1_dimuonMass_Num                = histoDir.make<TH1F>("dimuMass_Num", "Mmumu_Num", binnum, bins);

  h1_muon1_pt_Den                  = histoDir.make<TH1F>("mu1_pt_Den",   "mu1_pt_Den", binnum, bins);  
  h1_muon2_pt_Den                  = histoDir.make<TH1F>("mu2_pt_Den",   "mu2_pt_Den", binnum, bins);  

  h1_muon1_pt_Num                  = histoDir.make<TH1F>("mu1_pt_Num",   "mu1_pt_Num", binnum, bins);  
  h1_muon2_pt_Num                  = histoDir.make<TH1F>("mu2_pt_Num",   "mu2_pt_Num", binnum, bins);  

  h1_nPrimaryVtx                   = histoDir.make<TH1I>("nPrimaryVtx", "numPrimaryVtx", 50, -0.5, 49.5);
  h1_nDisplacedVtx                 = histoDir.make<TH1I>("nDisplacedVtx", "numDisplacedVtx", 50, -0.5, 49.5);
  h1_mu1_pt                        = histoDir.make<TH1F>("mu1_pt", "muon1_pt", 4000, 0, 400);
  h1_mu2_pt                        = histoDir.make<TH1F>("mu2_pt", "muon2_pt", 4000, 0, 400);
  
}


DimuonScoutingAnalyzer::~DimuonScoutingAnalyzer()
{
}


// ------------ method called for each event  ------------
void
DimuonScoutingAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  //  std::cout << "\nEVT" << std::endl;
  using namespace edm;
  passjetTrig=99;
  passNominalTrig=99;
  //  passMonitoringTrig=99;
  mass=-99.0;
  nDisplacedVtx=-99;
  nPrimaryVtx=-99;

  edm::Handle<edm::TriggerResults> trgResultsHandleScouting;
  iEvent.getByToken(trgResultsLabelScouting_, trgResultsHandleScouting);
  
  const edm::TriggerNames &trgNamesScouting = iEvent.triggerNames(*trgResultsHandleScouting);
  
  for (size_t i = 0; i < trgNamesScouting.size(); ++i) {
    const std::string &nameScouting = trgNamesScouting.triggerName(i);

    //    std::cout << "trig = " << nameScouting << std::endl;
    
    if ( (nameScouting.find("DST_DoubleMu3_noVtx_CaloScouting") != std::string::npos )) {
      passNominalTrig=trgResultsHandleScouting->accept(i);
    }
  }
  
    edm::Handle<edm::TriggerResults> trgResultsHandle;
    iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
    const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);
    for (size_t i = 0; i < trgNames.size(); ++i) {
      const std::string &name = trgNames.triggerName(i);
      //std::cout << "Other trig = " << name << std::endl;
      if ( (name.find("HLT_PFHT1050") != std::string::npos )) {
	passjetTrig=trgResultsHandle->accept(i);
      }
    }
    
    //    std::cout << " passjetTrig " << passjetTrig << std::endl;
  
  edm::Handle<ScoutingMuonCollection> muonHandle;
  iEvent.getByToken(muonLabel_, muonHandle);


  
  for (ScoutingMuonCollection::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {
    for (ScoutingMuonCollection::const_iterator jMu = iMu+1; jMu != muonHandle->end(); ++jMu) {
      
      
      std::cout <<   "\n\nglobal    "   <<  iMu->isGlobalMuon()  <<   "/" << jMu->isGlobalMuon() << std::endl; 
      std::cout <<   "tracker  "  <<	iMu->isTrackerMuon() <<   "/" << jMu->isTrackerMuon() << std::endl;   
      std::cout <<   "chi2  "  <<  iMu->chi2() << "/"  << jMu->chi2() << std::endl;
      std::cout <<   "ndof2  "  <<  iMu->ndof() << "/"  << jMu->ndof() << std::endl;
      std::cout <<   "pt  "    <<  iMu->pt()  << "/"   << jMu->pt() << std::endl;
      std::cout <<   "eta  "   <<  fabs(iMu->eta()) << "/" << fabs(jMu->eta()) << std::endl;
      std::cout <<   "nTrackerLayers  "  << iMu->nTrackerLayersWithMeasurement() << "/" << jMu->nTrackerLayersWithMeasurement()   << std::endl;
      std::cout <<   "nValidMuonHits  "  << iMu->nValidMuonHits() << "/"  << jMu->nValidMuonHits() << std::endl;
      std::cout <<   "nValidPixelHits " <<  iMu->nValidPixelHits() << "/" << jMu->nValidPixelHits() << std::endl;
      std::cout <<   "charge "   << iMu->charge() << "/" << jMu->charge() << std::endl;
      
      if (iMu->pt()>3.0 && jMu->pt()>3.0 ) {
      	if ( fabs(iMu->eta())<2.1 && fabs(jMu->eta())<2.1  ) {
	  if ( (iMu->charge())*(jMu->charge())>0 ) {
	  //    if ( iMu->nTrackerLayersWithMeasurement()>5 && jMu->nTrackerLayersWithMeasurement()>5 ) {
      //      if ( iMu->nValidMuonHits()>0 && jMu->nValidMuonHits()>0 ) {
	  
		TLorentzVector mu1, mu2 ;
		mu1.SetPtEtaPhiM(iMu->pt(), iMu->eta(), iMu->phi(), iMu->m());
		mu2.SetPtEtaPhiM(jMu->pt(), jMu->eta(), jMu->phi(), jMu->m());
		
		TLorentzVector diMuon=mu1+mu2;
		
		if (diMuon.M()>mass)   {
		  mass=diMuon.M();
		  std::cout << "mass=" << mass << std::endl;
		  if (mu1.Pt() >= mu2.Pt()) {
		    sel_muon1=mu1;
		    sel_muon2=mu2;
		  } else if (mu1.Pt() < mu2.Pt()) {
		    sel_muon1=mu2;
		    sel_muon2=mu1;
		  }
		}      
	      }
	    }

  	  }
	}
///    }
// }
  // }
  }
  //  std::cout << "dimuon mass = " << mass << std::endl;
  
  if (mass>0 && (!passNominalTrig)) std::cout << "*** **** PROBLEM **** ***" << " mass=" << mass  <<  " passNominalTrig=" << passNominalTrig 
					    <<  " passjetTrig=" << passjetTrig << std::endl;

  edm::Handle<ScoutingVertexCollection> primaryVtxHandle;
  iEvent.getByToken(primaryVtxLabel_, primaryVtxHandle);
  if (primaryVtxHandle.isValid())  nPrimaryVtx=primaryVtxHandle->size() ;

  edm::Handle<ScoutingVertexCollection> displacedVtxHandle;
  iEvent.getByToken(displacedVtxLabel_, displacedVtxHandle);
  if (displacedVtxHandle.isValid())  nDisplacedVtx=displacedVtxHandle->size() ;

  if (mass>0 && passjetTrig) {
    h1_dimuonMass_Den->Fill(mass);
    h1_muon1_pt_Den->Fill(mass);
    h1_muon2_pt_Den->Fill(mass);
  }
  if (mass>0 && passjetTrig && passNominalTrig) {
    h1_dimuonMass_Num->Fill(mass);
    h1_muon1_pt_Num->Fill(mass);
    h1_muon2_pt_Num->Fill(mass);
 
  }



  if (passNominalTrig) {
    h1_dimuonMass->Fill(mass) ;
    h1_mu1_pt->Fill(sel_muon1.Pt());
    h1_mu2_pt->Fill(sel_muon2.Pt());
    h1_nPrimaryVtx->Fill(nPrimaryVtx);
    h1_nDisplacedVtx->Fill(nDisplacedVtx);
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
