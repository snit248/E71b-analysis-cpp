// system include
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

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
#include <TChain.h>

//BM
#include "BMBasicRecon.hpp"
#include "BMBeaminfo.hpp"
#include "BMBSD.hpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Usage: ./TrackMatch <input_BM_file.root>" << endl;
        return 1;
    }

    //変数の宣言
    string input_BabyMIND_file = argv[1];
    Int_t unixtime;

    //TChainいらなかった
    //TChain* bmchain = new TChain("tree","tree");

    BMBasicRecon *bm_basic_recon = new BMBasicRecon();
    BMBSD *bm_bsd = new BMBSD();
    BMBeaminfo *bm_beaminfo = new BMBeaminfo();

    TFile *BabyMIND_file = new TFile(input_BabyMIND_file.c_str());
    TTree *BabyMIND_tree = (TTree*)BabyMIND_file->Get("tree");

    //bmchain->SetBranchAddress("BMBasicRecon",bm_basic_recon);
    //bmchain->SetBranchAddress("BMBSD",bm_bsd);
    //bmchain->SetBranchAddress("BMBeaminfo",bm_beaminfo);

    BabyMIND_tree->SetBranchAddress("BMBasicRecon",&bm_basic_recon);
    BabyMIND_tree->SetBranchAddress("BMBSD",&bm_bsd);
    BabyMIND_tree->SetBranchAddress("BMBeaminfo",&bm_beaminfo);

    cout << "bmchain->GetEntries(): " << BabyMIND_tree->GetEntries() << endl;
    //bmchain->GetEntry(100);
    BabyMIND_tree->GetEntry(100);
    cout << "bm_basic_recon->LG.at(0): " << bm_basic_recon->LG.at(0) << endl;
    cout << "bm_basic_recon->LG.at(1): " << bm_basic_recon->LG.at(1) << endl;
    cout << "bm_basic_recon->LG.size(): " << bm_basic_recon->LG.size() << endl;

    Int_t nEntries = BabyMIND_tree->GetEntries();
    cout << "nEntries: " << nEntries << endl;

    for(Int_t i=0; i<nEntries; i++){
        if(i%1000==0){
            cout << "i: " << i << endl;
            BabyMIND_tree->GetEntry(i);
            cout << "bm_basic_recon->LG.at(0): " << bm_basic_recon->LG.at(0) << endl;
            cout << "bm_basic_recon->LG.size(): " << bm_basic_recon->LG.size() << endl;
        }
    }
}