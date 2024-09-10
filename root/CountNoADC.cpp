#include <iostream>

void CountNoADC() {
  const Int_t nindex = 250;
  const Float_t PE_threshold = 2.5;
  const Float_t ToT_threshold = 40;

  TString mergefilename = "../data/ST/E71b_ST_data.root";
  cout << "Reading：" << mergefilename << endl;

  TFile *mergefile = new TFile(mergefilename);
  TTree *mergetree = (TTree*)mergefile->Get("tree");

  Int_t adc[nindex];
  Int_t unixtime[nindex];
  Int_t leadtime[nindex];
  Int_t trailtime[nindex];
  Float_t pe[nindex];

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
        // tdcflagが立たなかった場合にカウントする
        noTDCflagCount++;
      }
    }
  }

  Double_t noTDCflagPercentage = (Double_t)noTDCflagCount / totalEvents * 100.0;

  // tdcflagが立たなかったイベントの数を出力
  std::cout << "Total number of events: " << totalEvents << std::endl;
  std::cout << "Number of events where tdcflag was not set: " << noTDCflagCount << std::endl;
  std::cout << "Percentage of events where tdcflag was not set: " << noTDCflagPercentage << "%" << std::endl;
}