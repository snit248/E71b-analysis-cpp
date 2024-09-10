#include <unistd.h>  // access 関数を使うために必要

void EventDisplay_NoADC(){

  const Int_t nindex = 250;
  const Float_t PE_threshold = 2.5;
  const Float_t ADC_threshold = 900; 
  const Float_t ToT_threshold = 40; 

  const Int_t offsety[4]  = {20,  4, 16,  0};
  const Int_t offsetx[4]  = { 0, 16,  4, 20};
  const Int_t offsetz[4]  = { 1,  7, 10, 16};

  TString mergefilename = "../data/ST/E71b_ST_data.root";
  cout << "Reading：" << mergefilename << endl;

  TFile *mergefile = new TFile(mergefilename);
  TTree *mergetree = (TTree*)mergefile->Get("tree");

  Int_t adc[nindex];
  Int_t unixtime[nindex];
  Int_t leadtime[nindex];
  Int_t trailtime[nindex];
  Float_t pe[nindex];

  std::string msg;

  mergetree->SetBranchAddress("ADC", adc);
  mergetree->SetBranchAddress("UNIXTIME", unixtime);
  mergetree->SetBranchAddress("LEADTIME", leadtime);
  mergetree->SetBranchAddress("TRAILTIME", trailtime);
  mergetree->SetBranchAddress("PE", pe);

  mergetree->GetEntries();

  Char_t buffer[256];
  TString mapname = "/Users/shunito/Scinti/E71b/Controller/src/channel_new.dat";
  std::ifstream map(mapname);
  if (!map.is_open()) {
      std::cerr << "Failed to open the file." << std::endl;
      return;
  }
  map.getline(buffer, 100);
  Int_t tmp, module[nindex], ch_mod[nindex];
  Int_t view[nindex], pln[nindex], ch[nindex];
  for(Int_t index = 0; index < nindex; index++) {
      map >> tmp >> module[index] >> ch_mod[index] >> view[index] >> pln[index] >> ch[index];
  }

  Int_t counter=0;

  for(Int_t ientry=0; ientry<mergetree->GetEntries(); ientry++){
    mergetree->GetEntry(ientry);
    Int_t countOverThresholdADC = 0;
    Int_t countOverThresholdToT = 0;

    for(Int_t index = 0; index < nindex; index++) {
        if((pe[index] > PE_threshold)) {
          countOverThresholdADC++;
        }
        else if(((leadtime[index]-trailtime[index]) > ToT_threshold)) {
          countOverThresholdToT++;
        }
    }

    if(countOverThresholdADC == 0 && countOverThresholdToT >= 2) {
      counter++;

      // 保存するファイルの名前を作成
      TString filename = Form("../output/eventdisplay/ST/ED_NoADC_ID%d_%d.png", ientry, unixtime[0]);

      // 同名ファイルが存在するか確認する
      /*
      if (access(filename.Data(), F_OK) != -1) {
          // ファイルが存在する場合はスキップ
          std::cout << "File " << filename << " already exists, skipping..." << std::endl;
          continue;
      }
      */

      if (gROOT->FindObject("c")) delete gROOT->FindObject("c");
      if (gROOT->FindObject("sidehist")) delete gROOT->FindObject("sidehist");
      if (gROOT->FindObject("tophist")) delete gROOT->FindObject("tophist");

      TCanvas *c = new TCanvas("c", "c", 750, 1000);
      c->Divide(2,1);
      c->cd(1)->DrawFrame(0 , -500, 20, 500, "Event Display (Sideview);z [mm];y [mm]");
      c->cd(2)->DrawFrame(20, -500, 40, 500, "Event Display (Topview);z [mm];x [mm]");

      TH2F *sidehist = new TH2F("sidehist", "", 20, 0,  20, 250, -500, 500);
      sidehist->SetMinimum(0);
      sidehist->SetMaximum(20);
      TH2F *tophist  = new TH2F("tophist",  "", 20, 20, 40, 250, -500, 500);
      tophist->SetMinimum(0);
      tophist->SetMaximum(20);

      TBox *scint = new TBox();

      for(Int_t index=0; index<250; index++){
        
        scint->SetFillColor(19);
        if(pe[index] <= PE_threshold && (leadtime[index]-trailtime[index]) > ToT_threshold) scint->SetFillColor(9);
        if(view[index]==0){
          c->cd(1);
          scint->DrawBox(offsetz[pln[index]], -500+32*ch[index]+offsety[pln[index]], offsetz[pln[index]]+3, -500+32*ch[index]+24+offsety[pln[index]]);
        }
        else if(view[index]==1){
          c->cd(2);
          scint->DrawBox(offsetz[pln[index]]+20, 500-32*ch[index]-offsetx[pln[index]], offsetz[pln[index]]+23, 500-32*ch[index]-24-offsetx[pln[index]]);
        }
      }

      c->cd(1);
      sidehist->Draw("same colz");
      c->cd(2);
      tophist->Draw("same colz");

      // 自動的にPNGファイルとして保存し、イベントディスプレイを表示しない
      c->SaveAs(filename);

      c->Update();
      gSystem->ProcessEvents();
      std::cout << "Input q to quit." << std::endl;
      getline(std::cin, msg);
      if(msg == "q"){
          break;
      }

      // メモリ解放
      delete sidehist;
      delete tophist;
      delete scint;
      delete c;
    }
  }
}