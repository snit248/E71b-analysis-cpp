// system include
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

//boost include
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

// root include
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 4){
        cout << "Usage: ./TrackMatch <input_tracker_file.root> <input_BabyMIND_file.root> <output>" << endl;
        return 1;
    }

    //変数の宣言
    int trk_channels=250;

    Int_t trk_unixtime[trk_channels];
    Float_t trk_pe[trk_channels];

    Int_t bm_unixtime;
    vector<double> bm_lg;

    //トラッカーとBMファイルの読み込み
    string input_tracker_file = argv[1];
    string input_BabyMIND_file = argv[2];
    string output_file = argv[3];

    TFile *tracker_file = new TFile(input_tracker_file.c_str());
    TFile *BabyMIND_file = new TFile(input_BabyMIND_file.c_str());

    TTree* tracker_tree = (TTree*)tracker_file->Get("tree");
    TTree* BabyMIND_tree = (TTree*)BabyMIND_file->Get("tree");

    TString output_file_name = output_file;

    tracker_tree->SetBranchAddress("UNIXTIME", trk_unixtime);
    tracker_tree->SetBranchAddress("PE", trk_pe);

    BabyMIND_tree->SetBranchAddress("unixtime", &bm_unixtime);
    BabyMIND_tree->SetBranchAddress("LG", &bm_lg);

    //ここから具体的な処理
    BabyMIND_tree->GetEntry(0);
    Int_t start_unixtime = bm_unixtime;

    BabyMIND_tree->GetEntry(-1);
    Int_t end_unixtime = bm_unixtime;

    //BMの開始時間と終了時間のトラッカーのエントリー番号を取得
    Int_t start_trk_entry;
    Int_t end_trk_entry;

    for(Int_t i=0;i<tracker_tree->GetEntries();i++){
        tracker_tree->GetEntry(i);
        if(trk_unixtime[0] < start_unixtime || trk_unixtime[0] > end_unixtime){
            continue;
        }
        else if(trk_unixtime[0]==start_unixtime){
            start_trk_entry = i;
        }
        else if(trk_unixtime[0]==end_unixtime){
            end_trk_entry = i;
            //終了時間を見つけたらループを抜ける
            break;
        }
    }

    TString output_file_name_dif;
    Int_t match_counter = 0;

    //時間差-5から5の間でトラッカーとBMの一致を探す
    for(Int_t i=-5;i<=5;i++){
        output_file_name_dif = output_file_name + "_" + i + ".txt";
        ofstream output_file_dif(output_file_name_dif);
        for(Int_t j=start_trk_entry;j<=end_trk_entry;j++){
            tracker_tree->GetEntry(j);
            
        }
    }

    return 0;
}
