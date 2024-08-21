#include "BMHitSearch.h"
using namespace std;

BMHitSearch::BMHitSearch(vector<double> bm_lhg) : HitNum(0), isHit(false) {
    lhg = bm_lhg;
}

BMHitSearch::~BMHitSearch(){
}

void BMHitSearch::findHits(){
    //cout << "findHits() called" << endl;  // デバッグ用出力
    //変数の宣言
    HitNum = 0;
    Int_t lhgSize = lhg.size();
    //cout << "lhg size: " << lhgSize << endl;  // ベクトルサイズの確認
    Int_t HitNumThreshold = lhgSize/2;

    for(Int_t i=0;i<lhgSize;i++){
        cout << lhg[i] << endl;
        if(lhg[i] > 200){
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