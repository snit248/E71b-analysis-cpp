#!/usr/bin/env python2
import subprocess
import time

# プログラムの実行
proc = subprocess.Popen(
    ['/home/nu/itoshun/shell/EventDisplay', 
     '--input-file', '/home/nu/itoshun/data/ninja/HitConverter/hitConv2023-12-4.root',
     '--geometry-directory', '/home/nu/itoshun/wagasci-babymind-monte-carlo/data/geometry',
     '--output-directory', '/home/nu/itoshun/data/ed',
     '--detector', '5',
     '--bunch', '-1',
     '--start-event', '1',
     '--true-tracks',
     '--file-extension', '.png',
     '--pod', '3'],
    stdin=subprocess.PIPE,  # 標準入力をパイプで受け取る
    stdout=subprocess.PIPE,  # 標準出力をパイプで受け取る（必要なら）
    stderr=subprocess.PIPE   # 標準エラー出力もパイプで受け取る（必要なら）
)

# 30秒おきに「print」を送信
try:
    while proc.poll() is None:  # プロセスがまだ動いているかチェック
        proc.stdin.write("print\n")  # 「print」を送信
        proc.stdin.flush()  # 送信内容を即座に反映
        time.sleep(30)  # 30秒待機
except Exception as e:
    print("エラーが発生しました: ", e)
finally:
    proc.stdin.close()