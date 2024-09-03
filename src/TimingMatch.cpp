// system include
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <utility>  // std::pair を使うために必要

//boost include
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

// root include
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TH1D.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

//BM include
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

// local include
#include "STHitSearch.h"
#include "BMHitSearch.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 6){
        cout << "Usage: ./TrackMatch <input_tracker_file.root> <input_BabyMIND_file.root> <output_file_dir> <nPln> <HGThreshold>" << endl;
        return 1;
    }

    //変数の宣言
    const int trk_channels = 250;

    Int_t trk_unixtime[trk_channels];
    Float_t trk_pe[trk_channels];

    Int_t bm_unixtime;

    //BMブランチ（枝）
    BMBasicRecon *bm_basic_recon = new BMBasicRecon();
    BMBSD *bm_bsd = new BMBSD();
    BMBeaminfo *bm_beaminfo = new BMBeaminfo();

    //トラッカーとBMファイルの読み込み
    string input_tracker_file = argv[1];
    string input_BabyMIND_file = argv[2];
    string output_file_dir = argv[3];
    Int_t nPln = atoi(argv[4]);
    Int_t HGThreshold = atoi(argv[5]);

    TFile *tracker_file = new TFile(input_tracker_file.c_str());
    TFile *BabyMIND_file = new TFile(input_BabyMIND_file.c_str());

    TTree* tracker_tree = (TTree*)tracker_file->Get("tree");
    TTree* BabyMIND_tree = (TTree*)BabyMIND_file->Get("tree");

    //TString output_file_name = output_file;

    tracker_tree->SetBranchAddress("UNIXTIME", trk_unixtime);
    tracker_tree->SetBranchAddress("PE", trk_pe);

    BabyMIND_tree->SetBranchAddress("BMBasicRecon",&bm_basic_recon);
    BabyMIND_tree->SetBranchAddress("BMBSD",&bm_bsd);
    BabyMIND_tree->SetBranchAddress("BMBeaminfo",&bm_beaminfo);

    ///ここから具体的な処理///
    
    //BMの開始時間と終了時間を取得
    //最初と最後が-1なので、２番と最後から２番目のエントリーを取得
    Int_t nEntriesBM = BabyMIND_tree->GetEntries();
    BabyMIND_tree->GetEntry(1);
    Int_t start_unixtime = bm_bsd->unixtime;
    cout << "start_unixtime: " << start_unixtime << endl;

    BabyMIND_tree->GetEntry(nEntriesBM-2);
    Int_t end_unixtime = bm_bsd->unixtime;
    cout << "end_unixtime: " << end_unixtime << endl;

    //BMの開始時間と終了時間のトラッカーのエントリー番号を取得
    Int_t start_trk_entry;
    Int_t end_trk_entry;

    for(Int_t i=0;i<tracker_tree->GetEntries();i++){
        tracker_tree->GetEntry(i);
        if(trk_unixtime[0] < start_unixtime || trk_unixtime[0] > end_unixtime){
            //cout << "trk_unixtime[0]: " << trk_unixtime[0] << ", start_unixtime: " << start_unixtime << ", end_unixtime: " << end_unixtime << endl;
            continue;
        }
        else if(trk_unixtime[0]==start_unixtime){
            start_trk_entry = i;
            cout << "start_trk_entry: " << start_trk_entry << endl;
        }
        else if(trk_unixtime[0]==end_unixtime){
            end_trk_entry = i;
            cout << "end_trk_entry: " << end_trk_entry << endl;
            //終了時間を見つけたらループを抜ける
            break;
        }
    }

    TString output_file_name_dif;
    Int_t match_counter = 0;

    Int_t Nentry = start_trk_entry + 6;

    Int_t NentryST = Nentry;
    Int_t NentryBM = Nentry - start_trk_entry;

    Int_t timeDif = 5;
    std::vector<Int_t> totalMatch;

    TH1D *h = new TH1D("h", "h", 2*timeDif+1, -timeDif, timeDif+1);

    //時間差-5から5の間でトラッカーとBMの一致を探す
    for(Int_t i=-timeDif;i<=timeDif;i++){
        //output_file_name_dif = output_file_name + "_" + i + ".txt";
        //ofstream output_file_dif(output_file_name_dif);

        //BMの時間内でトラッカーのエントリーを探す
        while(NentryBM <= end_trk_entry-6){
            //エントリーの読み込み
            tracker_tree->GetEntry(NentryST);
            //2番目のデータなので+1
            BabyMIND_tree->GetEntry(NentryBM + i);
            bm_unixtime = bm_bsd->unixtime + i;

            //bmのunixtimeが飛んだ時の処理
            if(bm_unixtime < 100){
                NentryBM += 1;

                BabyMIND_tree->GetEntry(NentryBM + i);
                bm_unixtime = bm_bsd->unixtime + i;
                if(bm_unixtime < 100)continue;

                if(bm_unixtime - trk_unixtime[0] == 0)continue;
                
                while(bm_unixtime - trk_unixtime[0] > 0 || trk_unixtime[0] - bm_unixtime > 0){
                    if(bm_unixtime - trk_unixtime[0] > 0){
                        NentryST++;
                        tracker_tree->GetEntry(NentryST);
                        //cout << "bm_unixtime: " << bm_unixtime << ", trk_unixtime[0]: " << trk_unixtime[0] << ", bm_unixtime - trk_unixtime[0]: " << bm_unixtime - trk_unixtime[0] << endl;
                    }
                    else if(trk_unixtime[0] - bm_unixtime > 0){
                        NentryBM++;
                        BabyMIND_tree->GetEntry(NentryBM + i);
                        bm_unixtime = bm_bsd->unixtime + i;
                        //cout << "bm_unixtime: " << bm_unixtime << ", trk_unixtime[0]: " << trk_unixtime[0] << ", trk_unixtime[0] - bm_unixtime: " << trk_unixtime[0] - bm_unixtime << endl;
                    }
                }
                //output_file_dif << -1 << " " << -1 << " " << -1 << " " << -1 << " " << -1 << " " << -1 << endl;
                continue;
            }

            STHitSearch HitSearchST(trk_channels, trk_pe);
            HitSearchST.findHits();
            //cout << "ST HitNum: " << HitSearchST.HitNum << endl;
            //cout << "ST isHit: " << HitSearchST.isHit << endl;

            BMHitSearch HitSearchBM(bm_basic_recon, nPln, HGThreshold);
            HitSearchBM.findHits();
            //cout << "BM HitNum: " << HitSearchBM.HitNum << endl;
            //cout << "BM isHit: " << HitSearchBM.isHit << endl;

            if(HitSearchST.isHit && HitSearchBM.isHit){
                match_counter++;
                //cout << "Match found! " << "trk_unixtime: " << trk_unixtime[0] << " bm_unixtime: " << bm_unixtime << " " << endl;
                //output_file_dif << match_counter << " " << trk_unixtime[0] << " " << NentryST << " " << HitSearchST.HitNum << " " << NentryBM + i << " " << HitSearchBM.HitNum << endl;
                h->Fill(i);
            }
            NentryBM++;
            NentryST++;
        }
        cout << "Finished " << i << "Total match is " << match_counter << endl;
        totalMatch.push_back(match_counter);

        //初期値に戻す
        match_counter = 0;
        NentryST = Nentry;
        NentryBM = Nentry - start_trk_entry;
        //output_file_dif.close();
    }

    ///ヒストグラム描写///
    TCanvas *c = new TCanvas("c", "c");
    c->SetGrid();

    h->Draw();
    c->SaveAs((output_file_dir + "/nPln_" + std::to_string(nPln) + "_HGThreshold_" + std::to_string(HGThreshold) + "_hist.png").c_str());

    return 0;
}
