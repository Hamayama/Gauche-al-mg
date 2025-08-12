# MML音楽演奏サンプル

## 概要
- Gauche-al を用いて、  
  MML (Music Macro Language) による音楽演奏を行うサンプルです。


## 環境のインストール方法
- Gauche, MinGW, OpenAL, freealut, Gauche-al が適切にインストールされている必要があります。

- Gauche, MinGW, OpenAL, freealut, Gauche-al については、  
  以下のページの「インストール方法」を参考にインストールを実施ください。  
  https://github.com/Hamayama/Gauche-al-mg


## 実行方法
- test1001.bat をダブルクリック等で起動します。  
  しばらくすると音楽が鳴ります。演奏が終わると終了します。


## ファイルについて
- test1001.scm の25行目の「 ($ set! pcm-raw $ mml->pcm $ string-append 」の下が、  
  MML の文字列になっています。  
  ここを書き換えることで、いろいろな音楽を演奏できます。

- MML の解釈は mmlproc.scm というモジュールで行っています。  
  mmlproc の詳細については、以下のページを参照ください。  
  https://github.com/Hamayama/mmlproc


## 環境等
- OS
  - Windows 11 24H2 (64bit)
  - Windows 8.1 (64bit)
  - Windows XP Home SP3
- 環境
  - MSYS2/MinGW-w64 UCRT64 (64bit) (gcc version 15.1.0 (Rev8, Built by MSYS2 project))
  - MSYS2/MinGW-w64 (64bit/32bit) (gcc version 9.2.0 (Rev2, Built by MSYS2 project))
  - MinGW (32bit) (gcc version 6.3.0 (MinGW.org GCC-6.3.0-1))
- 言語
  - Gauche v0.9.15
  - Gauche v0.9.9
  - Gauche v0.9.8
  - Gauche v0.9.7
  - Gauche v0.9.6
  - Gauche v0.9.5
  - Gauche v0.9.4


## 履歴
- 2015-12-24 v1.00 初版
- 2015-12-24 v1.01 不要行削除
- 2015-12-24 v1.02 音楽変更
- 2015-12-25 v1.03 サンプリングレート変更
- 2016-3-31  v1.04 mmlproc.scmをv1.15に更新(get-wav-size手続きを追加)  
  test1001.scmの演奏終了チェック処理修正(eq? → eqv?)
- 2016-3-31  v1.05 test1001.scmの演奏終了チェック処理見直し
- 2016-4-17  v1.06 mmlproc.scmをv1.16に更新
- 2016-10-12 v1.07 README修正のみ(Gauche v0.9.5 対応)
- 2016-10-14 v1.08 test1001.scmのMML文字列読み込み処理見直し等
- 2016-10-14 v1.09 mmlproc.scmをv1.17に更新
- 2018-7-9   v1.09 README修正のみ(Gauche v0.9.6 で動作確認)
- 2018-7-9   v1.10 mmlproc.scmをv1.18に更新
- 2018-12-29 v1.10 README修正のみ(Gauche v0.9.7 で動作確認)
- 2019-12-29 v1.10 README修正のみ(Gauche v0.9.9 で動作確認)
- 2025-8-12  v1.11 mmlproc.scmをv1.19に更新
  test1002.scm を追加


(2025-8-12)
