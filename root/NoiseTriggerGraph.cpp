#include <iostream>
#include <TH1F.h>
#include <TCanvas.h>

void NoiseTriggerGraph() {
  const Int_t nindex = 250;
  const Float_t PE_threshold = 2.5;
  const Float_t ToT_threshold = 40;
  
  // TrackerIDごとにtdcflag==0をカウントするためのヒストグラムを作成
  Int_t trackerID_bins = 270; // 1000 IDごとに分けるため、100ビン
  TH1F *hist = new TH1F("hist", "Number of Events with tdcflag == 0", trackerID_bins, 0, 270000);  // x軸: TrackerID範囲(0-100000), y軸: カウント数

  TString mergefilename = "../data/ST/E71b_ST_data.root";
  cout << "Reading：" << mergefilename << endl;

  TFile *mergefile = new TFile(mergefilename);
  TTree *mergetree = (TTree*)mergefile->Get("tree");

  Int_t adc[nindex];
  Int_t unixtime[nindex];
  Int_t leadtime[nindex];
  Int_t trailtime[nindex];
  Float_t pe[nindex];
  Int_t trackerID;  // TrackerID を追加

  mergetree->SetBranchAddress("ADC", adc);
  mergetree->SetBranchAddress("UNIXTIME", unixtime);
  mergetree->SetBranchAddress("LEADTIME", leadtime);
  mergetree->SetBranchAddress("TRAILTIME", trailtime);
  mergetree->SetBranchAddress("PE", pe);

  Int_t noTDCflagCount = 0;  // tdcflagが立たなかったイベントのカウンタ
  Int_t totalEvents = 0;

  for (Int_t ientry = 0; ientry < mergetree->GetEntries(); ientry++) {
    mergetree->GetEntry(ientry);

    Int_t countOverThreshold = 0;
    for (Int_t index = 0; index < nindex; index++) {
      if ((pe[index] > PE_threshold)) {
        countOverThreshold++;
      } else if ((leadtime[index] - trailtime[index]) > ToT_threshold) {
        countOverThreshold++;
      }
    }

    if (countOverThreshold >= 2) {
        totalEvents++;
      Int_t tdcflag = 0;  // 初期化

      for (Int_t index = 0; index < 250; index++) {
        if (pe[index] > PE_threshold) {
          tdcflag = 1;
          break;  // tdcflagが立った時点でループを抜ける
        }
      }

      if (tdcflag == 0) {
        // tdcflagが立たなかった場合にカウントし、trackerIDに基づいてヒストグラムにカウントを追加
        noTDCflagCount++;
        hist->Fill(totalEvents);  // trackerIDに基づいてヒストグラムに追加
      }
    }
  }

  // tdcflagが立たなかったイベントの割合を計算
  Double_t noTDCflagPercentage = (Double_t)noTDCflagCount / totalEvents * 100.0;

  // tdcflagが立たなかったイベントの数と割合を出力
  std::cout << "Total number of events: " << totalEvents << std::endl;
  std::cout << "Number of events where tdcflag was not set: " << noTDCflagCount << std::endl;
  std::cout << "Percentage of events where tdcflag was not set: " << noTDCflagPercentage << "%" << std::endl;

  // ヒストグラムを描画
  TCanvas *c1 = new TCanvas("c1", "TDC Flag Count", 800, 600);
  hist->GetXaxis()->SetTitle("TrackerID (0-100000, 1000 ID per bin)");
  hist->GetYaxis()->SetTitle("Number of Events with tdcflag == 0");
  hist->Draw();
  c1->SaveAs("../output/TDCFlagCountHistogram.png");

  delete c1;
  delete hist;
}