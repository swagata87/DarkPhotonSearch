#include <iostream>
#include "TLatex.h"
#include <iomanip>
#include <vector>
#include "TPad.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TSystem.h"
#include "TImage.h"
#include "TKey.h"
#include "TH1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TObjArray.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TPostScript.h"
#include <TPaveStats.h>
#include "TLegend.h"
#include <TProfile.h>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

int EffJet1050JPsi() {

  //AnalysisOutput.root
  TFile *file_in  = new TFile("../python/scouting_crab_projects_Oct7/crab_Run2017D/results/hist.root");
  //  TFile *file_in  = new TFile("../python/AnalysisOutput.root");
  TFile* outputFile = new TFile("MyEff.root","RECREATE");
  outputFile->cd();
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.10);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);
  //dxy1_Den_Mon
  TH1F* den1 = (TH1F*)file_in->Get("demo/histoDir/dimuMass_Den_1050_JPsi");
  TH1F* num1 = (TH1F*)file_in->Get("demo/histoDir/dimuMass_Num_1050_JPsi");

  //  TH1F* den2 = (TH1F*)file_in->Get("demo/histoDir/dimudR_Den_1050_JPsi");
  //  TH1F* num2 = (TH1F*)file_in->Get("demo/histoDir/dimudR_Num_1050_JPsi");
  // den2->Rebin(8);
  // num2->Rebin(8);

  TH1F* den3 = (TH1F*)file_in->Get("demo/histoDir/dxy1_Den_1050_JPsi");
  TH1F* num3 = (TH1F*)file_in->Get("demo/histoDir/dxy1_Num_1050_JPsi");
  den3->Rebin(10);
  num3->Rebin(10);

  TH1F* den4 = (TH1F*)file_in->Get("demo/histoDir/dxy2_Den_1050_JPsi");
  TH1F* num4 = (TH1F*)file_in->Get("demo/histoDir/dxy2_Num_1050_JPsi");
  den4->Rebin(10);
  num4->Rebin(10);

  TH1F* den5 = (TH1F*)file_in->Get("demo/histoDir/dz1_Den_1050_JPsi");
  TH1F* num5 = (TH1F*)file_in->Get("demo/histoDir/dz1_Num_1050_JPsi");
  den5->Rebin(20);
  num5->Rebin(20);

  TH1F* den6 = (TH1F*)file_in->Get("demo/histoDir/dz2_Den_1050_JPsi");
  TH1F* num6 = (TH1F*)file_in->Get("demo/histoDir/dz2_Num_1050_JPsi");
  den6->Rebin(20);
  num6->Rebin(20);

  //  TH1F* den7 = (TH1F*)file_in->Get("demo/histoDir/nPV_Den_1050_JPsi");
  // TH1F* num7 = (TH1F*)file_in->Get("demo/histoDir/nPV_Num_1050_JPsi");

  //  TH1F* den8 = (TH1F*)file_in->Get("demo/histoDir/nDV_Den_1050_JPsi");
  // TH1F* num8 = (TH1F*)file_in->Get("demo/histoDir/nDV_Num_1050_JPsi");

  //nPV_nDV_Num_1050_JPsi

  //  TH2F* den9 = (TH2F*)file_in->Get("demo/histoDir/nPV_nDV_Den_1050_JPsi");
  //  TH2F* num9 = (TH2F*)file_in->Get("demo/histoDir/nPV_nDV_Num_1050_JPsi");

  TH1F* den1_pt1 = (TH1F*)file_in->Get("demo/histoDir/mu1_pt_Den_1050_JPsi");
  TH1F* num1_pt1 = (TH1F*)file_in->Get("demo/histoDir/mu1_pt_Num_1050_JPsi");
  TH1F* den1_pt2 = (TH1F*)file_in->Get("demo/histoDir/mu2_pt_Den_1050_JPsi");
  TH1F* num1_pt2 = (TH1F*)file_in->Get("demo/histoDir/mu2_pt_Num_1050_JPsi");
  den1_pt1->Rebin(4);
  den1_pt2->Rebin(4);
  num1_pt1->Rebin(4);
  num1_pt2->Rebin(4);

  TH1F* den_eta1 = (TH1F*)file_in->Get("demo/histoDir/mu1_eta_Den_1050_JPsi");
  TH1F* num_eta1 = (TH1F*)file_in->Get("demo/histoDir/mu1_eta_Num_1050_JPsi");
  TH1F* den_eta2 = (TH1F*)file_in->Get("demo/histoDir/mu2_eta_Den_1050_JPsi");
  TH1F* num_eta2 = (TH1F*)file_in->Get("demo/histoDir/mu2_eta_Num_1050_JPsi");
  den_eta1->Rebin(8);
  num_eta1->Rebin(8);
  den_eta2->Rebin(8);
  num_eta2->Rebin(8);

  TH1F* den_phi1 = (TH1F*)file_in->Get("demo/histoDir/mu1_phi_Den_1050_JPsi");
  TH1F* num_phi1 = (TH1F*)file_in->Get("demo/histoDir/mu1_phi_Num_1050_JPsi");
  TH1F* den_phi2 = (TH1F*)file_in->Get("demo/histoDir/mu2_phi_Den_1050_JPsi");
  TH1F* num_phi2 = (TH1F*)file_in->Get("demo/histoDir/mu2_phi_Num_1050_JPsi");
  den_phi1->Rebin(8);
  num_phi1->Rebin(8);
  den_phi2->Rebin(8);
  num_phi2->Rebin(8);

  TH1F* den_chi2_by_ndof1 = (TH1F*)file_in->Get("demo/histoDir/muon1_chi2_by_ndof_Den_1050_JPsi");
  TH1F* num_chi2_by_ndof1 = (TH1F*)file_in->Get("demo/histoDir/muon1_chi2_by_ndof_Num_1050_JPsi");
  TH1F* den_chi2_by_ndof2 = (TH1F*)file_in->Get("demo/histoDir/muon2_chi2_by_ndof_Den_1050_JPsi");
  TH1F* num_chi2_by_ndof2 = (TH1F*)file_in->Get("demo/histoDir/muon2_chi2_by_ndof_Num_1050_JPsi");
  // den_chi2_by_ndof1->Rebin(1);
  //  num_chi2_by_ndof1->Rebin(1);
  // den_chi2_by_ndof2->Rebin(1);
  // num_chi2_by_ndof2->Rebin(1);

  TGraphAsymmErrors* eff1 = new TGraphAsymmErrors(num1,den1,"cp");
  eff1->SetTitle("");
  eff1->GetXaxis()->SetTitle("M_{#mu #mu} in GeV");
  eff1->GetYaxis()->SetTitle("Trigger efficiency");
  eff1->SetMarkerStyle(0);
  eff1->SetMarkerColor(kBlue);
  eff1->SetLineColor(kBlue);
  eff1->SetLineWidth(2);
  eff1->GetXaxis()->SetLimits(0,2);
  eff1->SetMinimum(0.0);
  eff1->SetMaximum(1.2);

  TGraphAsymmErrors* eff2 = new TGraphAsymmErrors(num1,den1,"cp");
  eff2->SetTitle("");
  eff2->GetXaxis()->SetTitle("M_{#mu #mu} in GeV");
  eff2->GetYaxis()->SetTitle("Trigger efficiency");
  eff2->SetMarkerStyle(0);
  eff2->SetMarkerColor(kBlue);
  eff2->SetLineColor(kBlue);
  eff2->SetLineWidth(2);
  eff2->GetXaxis()->SetLimits(1,50);
  eff2->SetMinimum(0.0);
  eff2->SetMaximum(1.2);

  TGraphAsymmErrors* eff3 = new TGraphAsymmErrors(num1_pt1,den1_pt1,"cp");
  eff3->SetTitle("");
  eff3->GetXaxis()->SetTitle(" #mu_1 p_T in GeV");
  eff3->GetYaxis()->SetTitle("Trigger efficiency");
  eff3->SetMarkerStyle(0);
  eff3->SetMarkerColor(kBlue);
  eff3->SetLineColor(kBlue);
  eff3->SetLineWidth(2);
  eff3->GetXaxis()->SetLimits(0,50);
  eff3->SetMinimum(0.0);
  eff3->SetMaximum(1.2);

  TGraphAsymmErrors* eff4 = new TGraphAsymmErrors(num1_pt2,den1_pt2,"cp");
  eff4->SetTitle("");
  eff4->GetXaxis()->SetTitle(" #mu_2 p_T in GeV");
  eff4->GetYaxis()->SetTitle("Trigger efficiency");
  eff4->SetMarkerStyle(0);
  eff4->SetMarkerColor(kBlue);
  eff4->SetLineColor(kBlue);
  eff4->SetLineWidth(2);
  eff4->GetXaxis()->SetLimits(0,50);
  eff4->SetMinimum(0.0);
  eff4->SetMaximum(1.2);


  TGraphAsymmErrors* eff5 = new TGraphAsymmErrors(num_eta1,den_eta1,"cp");
  eff5->SetTitle("");
  eff5->GetXaxis()->SetTitle(" #mu_1 #eta ");
  eff5->GetYaxis()->SetTitle("Trigger efficiency");
  eff5->SetMarkerStyle(0);
  eff5->SetMarkerColor(kBlue);
  eff5->SetLineColor(kBlue);
  eff5->SetLineWidth(2);
  // eff5->GetXaxis()->SetLimits(0,50);
  eff5->SetMinimum(0.0);
  eff5->SetMaximum(1.2);

  TGraphAsymmErrors* eff6 = new TGraphAsymmErrors(num_eta2,den_eta2,"cp");
  eff6->SetTitle("");
  eff6->GetXaxis()->SetTitle("#mu_2 #eta ");
  eff6->GetYaxis()->SetTitle("Trigger efficiency");
  eff6->SetMarkerStyle(0);
  eff6->SetMarkerColor(kBlue);
  eff6->SetLineColor(kBlue);
  eff6->SetLineWidth(2);
  // eff5->GetXaxis()->SetLimits(0,50);
  eff6->SetMinimum(0.0);
  eff6->SetMaximum(1.2);


  TGraphAsymmErrors* eff7 = new TGraphAsymmErrors(num_phi1,den_phi1,"cp");
  eff7->SetTitle("");
  eff7->GetXaxis()->SetTitle(" #mu_1 #phi ");
  eff7->GetYaxis()->SetTitle("Trigger efficiency");
  eff7->SetMarkerStyle(0);
  eff7->SetMarkerColor(kBlue);
  eff7->SetLineColor(kBlue);
  eff7->SetLineWidth(2);
  // eff5->GetXaxis()->SetLimits(0,50);
  eff7->SetMinimum(0.0);
  eff7->SetMaximum(1.2);

  TGraphAsymmErrors* eff8 = new TGraphAsymmErrors(num_phi2,den_phi2,"cp");
  eff8->SetTitle("");
  eff8->GetXaxis()->SetTitle(" #mu_2 #phi ");
  eff8->GetYaxis()->SetTitle("Trigger efficiency");
  eff8->SetMarkerStyle(0);
  eff8->SetMarkerColor(kBlue);
  eff8->SetLineColor(kBlue);
  eff8->SetLineWidth(2);
  // eff5->GetXaxis()->SetLimits(0,50);
  eff8->SetMinimum(0.0);
  eff8->SetMaximum(1.2);


  /*  TGraphAsymmErrors* eff9 = new TGraphAsymmErrors(num2,den2,"cp");
  eff9->SetTitle("");
  eff9->GetXaxis()->SetTitle("deltaR(mu1,mu2) ");
  eff9->GetYaxis()->SetTitle("Trigger efficiency");
  eff9->SetMarkerStyle(0);
  eff9->SetMarkerColor(kBlue);
  eff9->SetLineColor(kBlue);
  eff9->SetLineWidth(2);
  //  eff9->GetXaxis()->SetLimits(-0.4,0.4);
  eff9->SetMinimum(0.0);
  eff9->SetMaximum(1.2);
  */
  TGraphAsymmErrors* eff10 = new TGraphAsymmErrors(num3,den3,"cp");
  eff10->SetTitle("");
  eff10->GetXaxis()->SetTitle("muon1 dxy ");
  eff10->GetYaxis()->SetTitle("Trigger efficiency");
  eff10->SetMarkerStyle(0);
  eff10->SetMarkerColor(kBlue);
  eff10->SetLineColor(kBlue);
  eff10->SetLineWidth(2);
  eff10->GetXaxis()->SetLimits(-0.4,0.4);
  eff10->SetMinimum(0.0);
  eff10->SetMaximum(1.2);

  TGraphAsymmErrors* eff11 = new TGraphAsymmErrors(num4,den4,"cp");
  eff11->SetTitle("");
  eff11->GetXaxis()->SetTitle("muon2 dxy ");
  eff11->GetYaxis()->SetTitle("Trigger efficiency");
  eff11->SetMarkerStyle(0);
  eff11->SetMarkerColor(kBlue);
  eff11->SetLineColor(kBlue);
  eff11->SetLineWidth(2);
  eff11->GetXaxis()->SetLimits(-0.4,0.4);
  eff11->SetMinimum(0.0);
  eff11->SetMaximum(1.2);

  TGraphAsymmErrors* eff12 = new TGraphAsymmErrors(num5,den5,"cp");
  eff12->SetTitle("");
  eff12->GetXaxis()->SetTitle("muon1 dz ");
  eff12->GetYaxis()->SetTitle("Trigger efficiency");
  eff12->SetMarkerStyle(0);
  eff12->SetMarkerColor(kBlue);
  eff12->SetLineColor(kBlue);
  eff12->SetLineWidth(2);
  //  eff12->GetXaxis()->SetLimits(-,0.4);
  eff12->SetMinimum(0.0);
  eff12->SetMaximum(1.2);

  TGraphAsymmErrors* eff13 = new TGraphAsymmErrors(num6,den6,"cp");
  eff13->SetTitle("");
  eff13->GetXaxis()->SetTitle("muon1 dz ");
  eff13->GetYaxis()->SetTitle("Trigger efficiency");
  eff13->SetMarkerStyle(0);
  eff13->SetMarkerColor(kBlue);
  eff13->SetLineColor(kBlue);
  eff13->SetLineWidth(2);
  //  eff13->GetXaxis()->SetLimits(-0.4,0.4);
  eff13->SetMinimum(0.0);
  eff13->SetMaximum(1.2);

  /*
  TGraphAsymmErrors* eff14 = new TGraphAsymmErrors(num7,den7,"cp");
  eff14->SetTitle("");
  eff14->GetXaxis()->SetTitle("nPV ");
  eff14->GetYaxis()->SetTitle("Trigger efficiency");
  eff14->SetMarkerStyle(0);
  eff14->SetMarkerColor(kBlue);
  eff14->SetLineColor(kBlue);
  eff14->SetLineWidth(2);
  //  eff14->GetXaxis()->SetLimits(-0.4,0.4);
  eff14->SetMinimum(0.0);
  eff14->SetMaximum(1.2);

  TGraphAsymmErrors* eff15 = new TGraphAsymmErrors(num8,den8,"cp");
  eff15->SetTitle("");
  eff15->GetXaxis()->SetTitle("nDisplacedVtx ");
  eff15->GetYaxis()->SetTitle("Trigger efficiency");
  eff15->SetMarkerStyle(0);
  eff15->SetMarkerColor(kBlue);
  eff15->SetLineColor(kBlue);
  eff15->SetLineWidth(2);
  //  eff15->GetXaxis()->SetLimits(-0.4,0.4);
  eff15->SetMinimum(0.0);
  eff15->SetMaximum(1.2);

  TEfficiency* eff16 = new TEfficiency(*num9,*den9);
  eff16->SetTitle(" ;nPrimaryVtx;nDisplacedVtx");
  // eff16->SetTitle("");
  // eff16->GetXaxis()->SetTitle("nPV ");
  // eff16->GetYaxis()->SetTitle("nDV");
  //  eff16->SetMarkerStyle(0);
  //  eff16->SetMarkerColor(kBlue);
  //  eff16->SetLineColor(kBlue);
  //  eff16->SetLineWidth(2);
  //  eff16->GetXaxis()->SetLimits(-0.4,0.4);
  // eff16->SetMinimum(0.0);
  // eff16->SetMaximum(1.2);
  */
  TGraphAsymmErrors* eff17 = new TGraphAsymmErrors(num_chi2_by_ndof1,den_chi2_by_ndof1,"cp");
  eff17->SetTitle("");
  eff17->GetXaxis()->SetTitle("chi2/NDOF of mu_1");
  eff17->GetYaxis()->SetTitle("Trigger efficiency");
  eff17->SetMarkerStyle(0);
  eff17->SetMarkerColor(kBlue);
  eff17->SetLineColor(kBlue);
  eff17->SetLineWidth(2);
  eff17->GetXaxis()->SetRangeUser(0,2);
  eff17->SetMinimum(0.0);
  eff17->SetMaximum(1.2);

  TLatex* CMS_text = new TLatex(0.20,0.88,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.04);
  CMS_text->SetTextAngle(0);

  TLatex* CMS_text_2 = new TLatex(0.20,0.84,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.04);
  CMS_text_2->SetTextAngle(0);

  TLatex* CMS_text_3 = new TLatex(0.50,0.88,"w.r.t Monitoring trigger");
  CMS_text_3->SetNDC();
  CMS_text_3->SetTextFont(42);
  CMS_text_3->SetTextSize(0.03);
  CMS_text_3->SetTextAngle(0);

  //  TLatex* era_text = new TLatex(0.60,0.84,"2017 D");
  TLatex* era_text = new TLatex(0.50,0.84,"2017 Run D");
  era_text->SetNDC();
  era_text->SetTextSize(0.03);
  era_text->SetTextAngle(0);

  //  TLatex* lumi_text = new TLatex(0.70,0.84,"XX fb^{-1}");
  TLatex* lumi_text = new TLatex(0.70,0.84," ");
  lumi_text->SetNDC();
  lumi_text->SetTextSize(0.03);
  lumi_text->SetTextAngle(0);

  TCanvas* canvas_eff1 = new TCanvas("eff1","eff1",800,600);
  canvas_eff1->cd();
  canvas_eff1->SetGrid();
  //canvas_eff1->SetLogx();
  eff1->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff2 = new TCanvas("eff2","eff2",800,600);
  canvas_eff2->cd();
  canvas_eff2->SetGrid();
  //canvas_eff2->SetLogx();
  eff2->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff3 = new TCanvas("eff3","eff3",800,600);
  canvas_eff3->cd();
  canvas_eff3->SetGrid();
  //canvas_eff2->SetLogx();
  eff3->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff4 = new TCanvas("eff4","eff4",800,600);
  canvas_eff4->cd();
  canvas_eff4->SetGrid();
  //canvas_eff2->SetLogx();
  eff4->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff5 = new TCanvas("eff5","eff5",800,600);
  canvas_eff5->cd();
  canvas_eff5->SetGrid();
  //canvas_eff2->SetLogx();
  eff5->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff6 = new TCanvas("eff6","eff6",800,600);
  canvas_eff6->cd();
  canvas_eff6->SetGrid();
  //canvas_eff2->SetLogx();
  eff6->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff7 = new TCanvas("eff7","eff7",800,600);
  canvas_eff7->cd();
  canvas_eff7->SetGrid();
  //canvas_eff2->SetLogx();
  eff7->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff8 = new TCanvas("eff8","eff8",800,600);
  canvas_eff8->cd();
  canvas_eff8->SetGrid();
  //canvas_eff2->SetLogx();
  eff8->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  /*  TCanvas* canvas_eff9 = new TCanvas("eff9","eff9",800,600);
  canvas_eff9->cd();
  canvas_eff9->SetGrid();
  //canvas_eff2->SetLogx();
  eff9->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");
  */
  TCanvas* canvas_eff10 = new TCanvas("eff10","eff10",800,600);
  canvas_eff10->cd();
  canvas_eff10->SetGrid();
  //canvas_eff2->SetLogx();
  eff10->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff11 = new TCanvas("eff11","eff11",800,600);
  canvas_eff11->cd();
  canvas_eff11->SetGrid();
  //canvas_eff2->SetLogx();
  eff11->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff12 = new TCanvas("eff12","eff12",800,600);
  canvas_eff12->cd();
  canvas_eff12->SetGrid();
  //canvas_eff2->SetLogx();
  eff12->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff13 = new TCanvas("eff13","eff13",800,600);
  canvas_eff13->cd();
  canvas_eff13->SetGrid();
  //canvas_eff2->SetLogx();
  eff13->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  /*
  TCanvas* canvas_eff14 = new TCanvas("eff14","eff14",800,600);
  canvas_eff14->cd();
  canvas_eff14->SetGrid();
  //canvas_eff2->SetLogx();
  eff14->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  TCanvas* canvas_eff15 = new TCanvas("eff15","eff15",800,600);
  canvas_eff15->cd();
  canvas_eff15->SetGrid();
  //canvas_eff2->SetLogx();
  eff15->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  gStyle->SetPalette(kBird);

  TCanvas* canvas_eff16 = new TCanvas("eff16","eff16",1000,600);
  canvas_eff16->cd();
  canvas_eff16->SetGrid();
  //canvas_eff2->SetLogx();
  eff16->Draw("COLZ");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");
  */
  TCanvas* canvas_eff17 = new TCanvas("eff17","eff17",1000,600);
  canvas_eff17->cd();
  canvas_eff17->SetGrid();
  //canvas_eff2->SetLogx();
  eff17->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");
  CMS_text_3->Draw("same");
  era_text->Draw("same");
  lumi_text->Draw("same");

  canvas_eff1->Write();
  canvas_eff1->Print("eff1_1050_JPsi.pdf");

  canvas_eff2->Write();
  canvas_eff2->Print("eff2_1050_JPsi.pdf");

  canvas_eff3->Write();
  canvas_eff3->Print("eff3_1050_JPsi.pdf");

  canvas_eff4->Write();
  canvas_eff4->Print("eff4_1050_JPsi.pdf");

  canvas_eff5->Write();
  canvas_eff5->Print("eff5_1050_JPsi.pdf");

  canvas_eff6->Write();
  canvas_eff6->Print("eff6_1050_JPsi.pdf");

  canvas_eff7->Write();
  canvas_eff7->Print("eff7_1050_JPsi.pdf");

  canvas_eff8->Write();
  canvas_eff8->Print("eff8_1050_JPsi.pdf");

  //  canvas_eff9->Write();
  // canvas_eff9->Print("eff9_1050_JPsi.pdf");

  canvas_eff10->Write();
  canvas_eff10->Print("eff10_1050_JPsi.pdf");

  canvas_eff11->Write();
  canvas_eff11->Print("eff11_1050_JPsi.pdf");

  canvas_eff12->Write();
  canvas_eff12->Print("eff12_1050_JPsi.pdf");

  canvas_eff13->Write();
  canvas_eff13->Print("eff13_1050_JPsi.pdf");

  //  canvas_eff14->Write();
  // canvas_eff14->Print("eff14_1050_JPsi.pdf");

  //  canvas_eff15->Write();
  // canvas_eff15->Print("eff15_1050_JPsi.pdf");

  //  canvas_eff16->Write();
  // canvas_eff16->Print("eff16_1050_JPsi.pdf");

  canvas_eff17->Write();
  canvas_eff17->Print("eff17_1050_JPsi.pdf");

  return 0;


}
