#!/bin/bash
Pln=$1
HG=$2

input_file="/home/nu/itoshun/shell/Pln_${Pln}_HGThreshold_${HG}_Timedif_1.txt"

awk '{print $5}' "$input_file" | while read start_event; do
  # イベントディスプレイを起動
  /home/nu/itoshun/shell/EventDisplay --input-file /home/nu/itoshun/data/ninja/HitConverter/hitConv2023-12-4.root \
                 --geometry-directory /home/nu/itoshun/wagasci-babymind-monte-carlo/data/geometry \
                 --output-directory /home/nu/itoshun/data/ed \
                 --detector 5 \
                 --bunch -1 \
                 --start-event "$start_event" \
                 --true-tracks \
                 --file-extension .png \
                 --pod 3

  # ユーザーが「e」キーを押すまで待機
  echo "次のイベントディスプレイを表示するには 'e' キーを押してください..."
  while true; do
    read -n 1 key
    if [[ $key == "e" ]]; then
      break
    fi
  done
done