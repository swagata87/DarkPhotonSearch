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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
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
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabel_;
  edm::Service<TFileService> fs;

  bool passNominalTrig;
  bool passMonitoringTrig;
  double mass;

  TH1F *h1_dimuonMass_nominal_monitoring;
  TH1F *h1_dimuonMass_monitoring;
  TH1F *h1_dimuonMass_nominal;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DimuonScoutingAnalyzer::DimuonScoutingAnalyzer(const edm::ParameterSet& iConfig)

{
  trgResultsLabel_         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  muonLabel_               = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  usesResource("TFileService");

  TFileDirectory histoDir = fs->mkdir("histoDir");

  h1_dimuonMass_nominal_monitoring = histoDir.make<TH1F>("dimuMass_nominal_monitoring", "Mmumu_nominal_monitoring", 400, 0, 400);
  h1_dimuonMass_nominal            = histoDir.make<TH1F>("dimuMass_nominal", "Mmumu_nominal", 400, 0, 400);
  h1_dimuonMass_monitoring         = histoDir.make<TH1F>("dimuMass_monitoring", "Mmumu_monitoring", 400, 0, 400);
  
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
   passNominalTrig=0;
   passMonitoringTrig=0;
   mass=0.0;
   edm::Handle<edm::TriggerResults> trgResultsHandle;
   iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
   
   const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);
   for (size_t i = 0; i < trgNames.size(); ++i) {
     const std::string &name = trgNames.triggerName(i);
     if ( (name.find("DST_DoubleMu3_noVtx_CaloScouting") != std::string::npos )) {
       //std::cout << "trgName=" << name << std::endl;
       passNominalTrig=1;
     }
     if ( (name.find("DST_DoubleMu3_noVtx_CaloScouting_Monitoring") != std::string::npos )) {
       //std::cout << "trgName=" << name << std::endl;
       passMonitoringTrig=1;
     }
     
   }
   
   //   std::cout << passNominalTrig << " " << passMonitoringTrig << std::endl;
   
   
   edm::Handle<ScoutingMuonCollection> muonHandle;
   iEvent.getByToken(muonLabel_, muonHandle);
   
   for (ScoutingMuonCollection::const_iterator iMu = muonHandle->begin(); iMu != muonHandle->end(); ++iMu) {
     for (ScoutingMuonCollection::const_iterator jMu = iMu+1; jMu != muonHandle->end(); ++jMu) {
       
       if ( iMu->nTrackerLayersWithMeasurement()>5 && jMu->nTrackerLayersWithMeasurement()>5 ) {
	 if ( iMu->nValidMuonHits()>0 && jMu->nValidMuonHits()>0 ) {
	   
	   TLorentzVector mu1, mu2 ;
	   mu1.SetPtEtaPhiM(iMu->pt(), iMu->eta(), iMu->phi(), iMu->m());
	   mu2.SetPtEtaPhiM(jMu->pt(), jMu->eta(), jMu->phi(), jMu->m());
	   
	   TLorentzVector diMuon=mu1+mu2;
	   if (diMuon.M()>mass)   mass=diMuon.M();
	   
	   //	   std::cout << "dimuon mass = " << mass << std::endl;
	 }
       }
     }
   }

   if (passNominalTrig && passMonitoringTrig) h1_dimuonMass_nominal_monitoring->Fill(mass) ;
   if (passNominalTrig) h1_dimuonMass_nominal->Fill(mass) ;
   if (passMonitoringTrig) h1_dimuonMass_monitoring->Fill(mass) ;


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
