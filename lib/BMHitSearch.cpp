#include "BMHitSearch.h"
using namespace std;

BMHitSearch::BMHitSearch(BMBasicRecon* bm_basic_recon, Int_t nPlnInput, Int_t HGThresholdInput) : HitNum(0), nPln(nPlnInput), HGThreshold(HGThresholdInput), isHit(false) {
    // BMBasicRecon のデータをコピーする
    pln = bm_basic_recon->pln;
    LHG = bm_basic_recon->LHG;
    RHG = bm_basic_recon->RHG;
    THG = bm_basic_recon->THG;
    BHG = bm_basic_recon->BHG;
}

BMHitSearch::~BMHitSearch(){
}

void BMHitSearch::findHits(){
    //cout << "findHits() called" << endl;  // デバッグ用出力
    //変数の宣言
    Int_t hitNum = pln.size();
    //Int_t HitNumThreshold = 9;

    isHit = true;

    bool hitInPln1 = false;
    bool hitInPln2 = false;

    std::vector<bool> hitInPln(nPln, false);

    //上流でのヒットがあるかどうか
    for(Int_t j=1; j<=18; j++){
        for(Int_t i=0;i<hitNum;i++){
            if(pln[i] == j){
                if((LHG[i] >= HGThreshold && RHG[i] >= HGThreshold) || (THG[i] >= HGThreshold && BHG[i] >= HGThreshold)){
                    HitNum++;
                    hitInPln[j-1] = true;
                    break;
                }
            }
        }
    }

    for(Int_t i=0;i<nPln;i++){
        if(!hitInPln[i]){
            isHit = false;
        }
    }
}