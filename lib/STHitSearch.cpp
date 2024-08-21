#include "STHitSearch.h"
using namespace std;

STHitSearch::STHitSearch(Int_t trk_channels, Float_t* trk_pe) : HitNum(0), isHit(false), chs(trk_channels) {
    pe = new Float_t[chs];

    for(Int_t i=0;i<chs;i++){
        pe[i] = trk_pe[i];
    }
}

STHitSearch::~STHitSearch(){
    delete[] pe;
}

void STHitSearch::findHits(){
    //変数の宣言
    HitNum = 0;

    for(Int_t i=0;i<chs;i++){
        if(pe[i] > 2.5){
            HitNum++;
        }
    }

    //HitNumが4以上ならtrue、そうでなければfalseを返す
    if(HitNum > 3){
        isHit = true;
    }
    else{
        isHit = false;
    }
}