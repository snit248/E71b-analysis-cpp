#ifndef ST_HIT_SEARCH_H
#define ST_HIT_SEARCH_H

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

class STHitSearch{
    public:
        STHitSearch(Int_t trk_channels, Float_t* trk_pe);
        ~STHitSearch();
        void findHits();
        Int_t HitNum;
        Bool_t isHit;

    private:
        Int_t chs;
        Float_t* pe;

};
#endif