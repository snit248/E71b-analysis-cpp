#include "BMHitSearch.h"
using namespace std;

BMHitSearch::BMHitSearch(vector<double> bm_pe) : HitNum(0), isHit(false) {
    pe = bm_pe;
}

BMHitSearch::~BMHitSearch(){
}

void BMHitSearch::findHits(){
    //cout << "findHits() called" << endl;  // デバッグ用出力
    //変数の宣言
    HitNum = 0;
    Int_t peSize = pe.size();
    //cout << "pe size: " << peSize << endl;  // ベクトルサイズの確認
    Int_t HitNumThreshold = peSize/4;

    for(Int_t i=0;i<peSize;i++){
        cout << pe[i] << endl;
        if(pe[i] > 80){
            HitNum++;
        }
    }
    if(HitNum > HitNumThreshold){
        isHit = true;
    }
    else{
        isHit = false;
    }
}