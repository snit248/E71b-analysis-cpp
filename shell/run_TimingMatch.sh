#!/bin/zsh
cd /Users/shunito/Scinti/E71b-analysis-cpp/build/src

for i in {1..18}; do
  for j in {100..18..100}; do
    ./TimingMatch /Users/shunito/Scinti/E71b-analysis-cpp/data/ST/E71b_ST_data.root \
                  /Users/shunito/Scinti/E71b-analysis-cpp/data/BM/BMBSD_BM_2023_12_4_0.root \
                  ../../output $i $j
    done
done

cd /Users/shunito/Scinti/E71b-analysis-cpp/shell