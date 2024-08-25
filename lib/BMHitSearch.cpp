#include "BMHitSearch.h"
using namespace std;

BMHitSearch::BMHitSearch(BMBasicRecon* bm_basic_recon) : HitNum(0), isHit(false) {
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
    Int_t plnNum = 2;
    Int_t hitNum = pln.size();
    Int_t HGThreshold = 400;
    //Int_t HitNumThreshold = 9;

    bool hitInPln1 = false;
    bool hitInPln2 = false;

    //上流でのヒットがあるかどうか
    for(Int_t i=0;i<hitNum;i++){
        if(pln[i] == 1){
            if((LHG[i] >= HGThreshold && RHG[i] >= HGThreshold) || (THG[i] >= HGThreshold && BHG[i] >= HGThreshold)){
                HitNum++;
                hitInPln1 = true;
            }
        }
        else if(pln[i] == 2){
            if((LHG[i] >= HGThreshold && RHG[i] >= HGThreshold) || (THG[i] >= HGThreshold && BHG[i] >= HGThreshold)){
                HitNum++;
                hitInPln2 = true;
            }
        }
        else{
            break;
        }
    }
    if(hitInPln1 && hitInPln2){
        isHit = true;
    }
    else{
        isHit = false;
    }
}