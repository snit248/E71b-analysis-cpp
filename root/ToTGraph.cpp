#include <iostream>
#include <cmath>   // std::powを使用するために必要
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>

void ToTGraph(){
    TFile *file = new TFile("../data/ST/E71b_ST_data.root");
    TTree *tree = (TTree*)file->Get("tree");

    Int_t adc[250];
    Int_t leadtime[250];
    Int_t trailtime[250];
    Float_t pe[250];

    //Change this value
    Int_t ToTThreshold = 0;

    tree->SetBranchAddress("ADC", adc);
    tree->SetBranchAddress("LEADTIME", leadtime);
    tree->SetBranchAddress("TRAILTIME", trailtime);
    tree->SetBranchAddress("PE", pe);

    TH2D *h = new TH2D("h", "h", 80, 0, 80, 130, 0, 130);
    h->SetTitle("ToT vs PE");
    h->GetXaxis()->SetTitle("p.e.");
    h->GetYaxis()->SetTitle("ToT");

    Int_t nentry = tree->GetEntries();
    for(Int_t ientry = 0; ientry < nentry; ientry++) {
        tree->GetEntry(ientry);
        for(Int_t index = 0; index < 250; index++) {
            Int_t ToT = leadtime[index] - trailtime[index];
            if(leadtime[index] != -1 && trailtime[index] != -1 && ToT > ToTThreshold) {
                h->Fill(pe[index], ToT);
            }
        }
    }
    
    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    h->Draw("colz");
    c1->SaveAs("../output/ToTvsPE.png");
}