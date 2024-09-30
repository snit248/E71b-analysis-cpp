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
#include <cmath>

// 階乗を計算する関数
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// 組み合わせ C(n, k) を計算する関数
unsigned long long combination(int n, int k) {
    if (k > n) return 0; // kがnより大きい場合は0を返す
    return factorial(n) / (factorial(k) * factorial(n - k));
}

void MultiRateCalc(){
    int bunch = 8;
    double eventRate = 0.129022 * 0.855013;
    double oneBunchRate = eventRate/bunch;
    double multiRateAll = 0;
    double multiRate[8] = {0};

    for(int i=1; i<=bunch; i++){
        multiRate[i-1] = combination(bunch, i)*pow(oneBunchRate, i);
        std::cout << "i = " << i << ", multiRate = " << multiRate[i-1] << std::endl;
        multiRateAll += combination(bunch, i)*pow(oneBunchRate, i);
    }

    std::cout << "multiRateAll = " << multiRateAll << std::endl;
    std::cout << "multiRate[2]/eventRate = " << multiRate[1]/eventRate << std::endl;

}