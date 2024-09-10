#!/usr/bin/expect

# プログラムの実行
spawn /opt/wagasci_mc/WagasciED/bin/EventDisplay --input-file /home/nu/itoshun/data/ninja/HitConverter/hitConv2023-12-4.root \
                 --geometry-directory /home/nu/itoshun/wagasci-babymind-monte-carlo/data/geometry \
                 --output-directory /home/nu/itoshun/data/ed \
                 --detector 5 \
                 --bunch -1 \
                 --start-event 1 \
                 --true-tracks \
                 --file-extension .png \
                 --pod 3

# 無限ループで30秒ごとに "print" を送信
while {1} {
    # "print" をプログラムに送信
    send "print\n"
    
    # 30秒待機
    sleep 30
}