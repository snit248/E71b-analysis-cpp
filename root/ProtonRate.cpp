#include <iostream>
#include <cmath>   // std::powを使用するために必要
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>

//cpp include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cmath>

void ProtonRate(){
    TFile *file = new TFile("../data/POT/E71b_ALL_POT/E71bALLPOT.root");
    TTree *tree = (TTree*)file->Get("bsd");

    Int_t trg_sec[3];
    Double_t ct_np[5][9];
    Int_t good_spill_flag;
    Int_t spill=0;

    Int_t n_entries = tree->GetEntries();
    Double_t totalPOT = 0;

    tree->SetBranchAddress("trg_sec", &trg_sec);
    tree->SetBranchAddress("ct_np", &ct_np);
    tree->SetBranchAddress("good_spill_flag", &good_spill_flag);

    for(int i=0; i<n_entries; i++){
        tree->GetEntry(i);
        totalPOT += ct_np[4][0];
        
    }
    std::cout << "Total POT: " << totalPOT << std::endl;
    std::cout << "Proton Rate: " << totalPOT/n_entries << std::endl;

}