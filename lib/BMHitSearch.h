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

// local include
#include "BMBasicRecon.hpp"

class BMHitSearch {
    public:
        BMHitSearch(BMBasicRecon* bm_basic_recon);
        ~BMHitSearch();
        void findHits();

        Int_t HitNum;
        Bool_t isHit;

    private:
        std::vector<double> pln;
        std::vector<double> LHG;
        std::vector<double> RHG;
        std::vector<double> THG;
        std::vector<double> BHG;
};

#endif