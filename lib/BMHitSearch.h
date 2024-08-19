#ifndef BM_HIT_SEARCH_H
#define BM_HIT_SEARCH_H

#include <iostream>
#include <vector>

// root include
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

class BMHitSearch{
    public:
        BMHitSearch(std::vector<double> bm_pe);
        ~BMHitSearch();
        void findHits();
        Int_t HitNum;
        Bool_t isHit;

    private:
        std::vector<double> pe;
};
#endif