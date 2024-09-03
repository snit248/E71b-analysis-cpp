#include <iostream>
#include <cmath>   // std::powを使用するために必要
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>

void ToTTest(){
    TFile *file = new TFile("../data/ST/E71b_ST_data.root");
    TTree *tree = (TTree*)file->Get("tree");

    Int_t adc[250];
    Int_t leadtime[250];
    Int_t trailtime[250];
    Float_t pe;

    //Change this value
    Int_t ToTThreshold = 0;

    tree->SetBranchAddress("ADC", adc);
    tree->SetBranchAddress("LEADTIME", leadtime);
    tree->SetBranchAddress("TRAILTIME", trailtime);

    TH2D *h = new TH2D("h", "h", 250, 0, 250, 100, 0, 100);
    h->SetTitle("ToT vs PE");
    h->GetXaxis()->SetTitle("ToT");
    h->GetYaxis()->SetTitle("PE");

    Int_t nentry = tree->GetEntries();
    for(Int_t ientry = 0; ientry < nentry; ientry++) {
        tree->GetEntry(ientry);
        for(Int_t index = 0; index < 250; index++) {
            Int_t ToT = leadtime[index] - trailtime[index];
            if(leadtime[index] != -1 && trailtime[index] != -1 && ToT > ToTThreshold) {
                pe = 20.635 * std::pow(static_cast<double>(ToT), 0.3654) + 10.347;
                std::cout << "ToT: " << ToT << ", PE: " << pe << std::endl;
                h->Fill(ToT, pe);
            }
        }
    }
    
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    h->Draw("colz");
    c1->SaveAs("ToTtest.png");
}