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

using namespace std;

void bunchHistHitBased(){
    TFile *file = new TFile("../data/ST/E71b_ST_data.root");
    TTree *tree = (TTree*)file->Get("tree");

    Int_t adc[250];
    Int_t leadtime[250];
    Int_t trailtime[250];
    Float_t pe[250];

    //Change this value
    Int_t ToTThreshold = 40;
    Float_t peThreshold = 2.5;
    Int_t hitNumThreshold = 4;

    tree->SetBranchAddress("ADC", adc);
    tree->SetBranchAddress("LEADTIME", leadtime);
    tree->SetBranchAddress("TRAILTIME", trailtime);
    tree->SetBranchAddress("PE", pe);

    Int_t nentry = tree->GetEntries();
    Int_t ADCentries = 0;
    Int_t ToTentries = 0;
    Int_t ADCHitCounter = 0;
    Int_t ToTHitCounter = 0;

    TH1D *hBunch = new TH1D("hBunch", "Bunch", 200, 0, 4096);
    TH1D *hBunchFirst = new TH1D("hBunchFirst", "BunchFirst", 200, 0, 4096);
    TH1D *hBunchMulti = new TH1D("hBunchMulti", "BunchMulti", 200, 0, 4096);
    TH1D *hBunchNoADC = new TH1D("hBunchNoADC", "BunchNoADC", 200, 0, 4096);

    for(Int_t i=0;i<nentry;i++){
        tree->GetEntry(i);
        for(Int_t j=0;j<250;j++){
            if(pe[j] > peThreshold){
                ADCHitCounter++;
            }
            if((leadtime[j] - trailtime[j]) > ToTThreshold && pe[j] <= peThreshold){
                ToTHitCounter++;
            }
        }
        if (ADCHitCounter >= hitNumThreshold){
            ADCentries++;
            for(Int_t k=0; k<250; k++){
                if((leadtime[k] - trailtime[k]) > ToTThreshold){
                    cout << leadtime[k] << endl;
                    hBunch->Fill(leadtime[k]);
                    hBunchFirst->Fill(leadtime[k]);
                }
            }
        }
        if(ToTHitCounter >= hitNumThreshold && ADCHitCounter != 0){
            ToTentries++;
            for(Int_t k=0; k<250; k++){
                if((leadtime[k] - trailtime[k]) > ToTThreshold){
                    cout << leadtime[k] << endl;
                    hBunch->Fill(leadtime[k]);
                    hBunchMulti->Fill(leadtime[k]);
                }
            }
        }
        if(ToTHitCounter >= hitNumThreshold && ADCHitCounter == 0){
            ToTentries++;
            for(Int_t k=0; k<250; k++){
                if((leadtime[k] - trailtime[k]) > ToTThreshold){
                    cout << leadtime[k] << endl;
                    hBunchNoADC->Fill(leadtime[k]);
                }
            }
        }

        ADCHitCounter = 0;
        ToTHitCounter = 0;

    }
    cout << "ADC entries: " << ADCentries << endl;
    cout << "ToT entries: " << ToTentries << endl;
    cout << "ToT/ADC: " << (double)ToTentries/ADCentries << endl;

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
    TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
    TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);

    c1->cd();
    c1->SetGrid();
    c1->SetLogy();
    hBunch->Draw();
    c1->SaveAs("../output/bunchHistHitBased.png");

    c2->cd();
    c2->SetGrid();
    c2->SetLogy();
    hBunchFirst->Draw();
    c2->SaveAs("../output/bunchHistHitBasedFirst.png");

    c3->cd();
    c3->SetGrid();
    c3->SetLogy();
    hBunchMulti->Draw();
    c3->SaveAs("../output/bunchHistHitBasedMulti.png");

    c4->cd();
    c4->SetGrid();
    c4->SetLogy();
    hBunchNoADC->Draw();
    c4->SaveAs("../output/bunchHistHitBasedNoADC.png");

}