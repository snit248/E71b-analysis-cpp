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

void ToTADCrate(){
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
        }
        if(ToTHitCounter >= hitNumThreshold && ADCHitCounter != 0){
            ToTentries++;
        }
        ADCHitCounter = 0;
        ToTHitCounter = 0;

    }
    cout << "ADC entries: " << ADCentries << endl;
    cout << "ToT entries: " << ToTentries << endl;
    cout << "ToT/ADC: " << (double)ToTentries/ADCentries << endl;

}