#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TLegend.h>

void countHitsEachModule() {
    const Int_t nindex = 250;
    const Float_t ToT_threshold = 40;
    const Float_t PE_threshold = 2.5;
    const Int_t nHistograms = 4;
    const Int_t ch_each = 31;

    TString mergefilename = "../data/ST/E71b_ST_data.root";
    //All_1700735651_1701478713_conv.root
    //1702446582
    //1702533973 E71b 9
    //1702797691 E71b 10
    //All_1700735651_1702797714_conv.root
    //1703173071
    //All_1705039280_conv.root
    //All_1705045718_conv.root
    //All_1705561018_conv.root
    //TString runtimename = "1705563849"; //E71b testLowEntries16FlatCableReverse 1/18
    //All_1705566581_conv
    //1706672531 test 1/31
    //../E71b_ALL_ST/E71b_ST_data.root
    TFile *mergefile = new TFile(mergefilename);
    TTree *mergetree = (TTree*)mergefile->Get("tree");

    if (!mergetree) {
        std::cerr << "Cannot find TTree in the file." << std::endl;
        return;
    }

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

    // ヒストグラムの作成（0-3がY、4-7がX）
    TH1F *histograms[nHistograms];
    for (int i = 0; i < nHistograms; ++i) {
        histograms[i] = new TH1F(Form("h%d", i), Form("Histogram Channel;Count"), 8, 0, 8);
        histograms[i]->SetMinimum(1);
        histograms[i]->SetMaximum(10000000);
    }

    Int_t nentries = mergetree->GetEntries();
    for(Int_t ientry = 0; ientry < nentries; ientry++) {
        mergetree->GetEntry(ientry);

        Int_t countOverThreshold[nHistograms] = {0};
        for(Int_t index = 0; index < nindex; index++) {
            if(pe[index] > PE_threshold) {
                countOverThreshold[module[index]]++;
            }
        }

        for (int i = 0; i < nHistograms; ++i) {
            histograms[i]->Fill(countOverThreshold[i]);
        }
    }

    TCanvas *c[nHistograms];
    for (int i = 0; i < nHistograms; i++) {
        c[i] = new TCanvas(Form("c%d", i), Form("Hit Count %d", i), 800, 600);
    }

    for (int i = 0; i < nHistograms; i++) {
        c[i]->cd();
        c[i]->SetGrid();

        // ゼロ以上のエントリがあるか確認してから対数スケールを設定
        if (histograms[i]->GetMaximum() > 0) {
            c[i]->SetLogy();  // Y軸を対数スケールに設定
        }

        histograms[i]->Draw();
        c[i]->SaveAs(Form("../output/hit_count_module%d.png", i));
    }
}
