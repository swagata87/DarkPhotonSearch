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

int Eff() {


  TFile *file_in  = new TFile("../python/AnalysisOutput.root");
  TFile* outputFile = new TFile("MyEff.root","RECREATE");
  outputFile->cd();
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);

  TH1F* den1 = (TH1F*)file_in->Get("demo/histoDir/dimuMass_Den");
  TH1F* num1 = (TH1F*)file_in->Get("demo/histoDir/dimuMass_Num");
  //  den1->Rebin(10);
  // num1->Rebin(10);

  TH1F* den1_pt1 = (TH1F*)file_in->Get("demo/histoDir/mu1_pt_Den");
  TH1F* num1_pt1 = (TH1F*)file_in->Get("demo/histoDir/mu1_pt_Num");

  TH1F* den1_pt2 = (TH1F*)file_in->Get("demo/histoDir/mu2_pt_Den");
  TH1F* num1_pt2 = (TH1F*)file_in->Get("demo/histoDir/mu2_pt_Num");

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

  TLatex* CMS_text = new TLatex(0.24,0.88,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);

  TLatex* CMS_text_2 = new TLatex(0.20,0.83,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);

  TCanvas* canvas_eff1 = new TCanvas("eff1","eff1",800,600);
  canvas_eff1->cd();
  canvas_eff1->SetGrid();
  //canvas_eff1->SetLogx();
  eff1->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");

  TCanvas* canvas_eff2 = new TCanvas("eff2","eff2",800,600);
  canvas_eff2->cd();
  canvas_eff2->SetGrid();
  //canvas_eff2->SetLogx();
  eff2->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");

  TCanvas* canvas_eff3 = new TCanvas("eff3","eff3",800,600);
  canvas_eff3->cd();
  canvas_eff3->SetGrid();
  //canvas_eff2->SetLogx();
  eff3->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");

  TCanvas* canvas_eff4 = new TCanvas("eff4","eff4",800,600);
  canvas_eff4->cd();
  canvas_eff4->SetGrid();
  //canvas_eff2->SetLogx();
  eff4->Draw("Ap");
  CMS_text->Draw("same");
  CMS_text_2->Draw("same");

  canvas_eff1->Write();
  canvas_eff1->Print("eff1.pdf");

  canvas_eff2->Write();
  canvas_eff2->Print("eff2.pdf");

  canvas_eff3->Write();
  canvas_eff3->Print("eff3.pdf");

  canvas_eff4->Write();
  canvas_eff4->Print("eff4.pdf");

  return 0;


}
