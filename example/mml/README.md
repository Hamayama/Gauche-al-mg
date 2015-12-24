# MML音楽演奏サンプル

## 概要
- Gauche-al を用いて、  
  MML(Music Macro Language)による音楽演奏を行うサンプルです。


## 環境のインストール方法
- Gauche, MinGW(32bit), OpenAL, freealut, Gauche-al が適切にインストールされている必要があります。

- Gauche, MinGW(32bit), OpenAL, freealut, Gauche-al については、  
  以下のページの「インストール方法」を参考にインストールを実施ください。  
  https://github.com/Hamayama/Gauche-al-mg


## 実行方法
- test1001.bat をダブルクリック等で起動します。  
  (test1001.bat, test1001.scm, mmlproc.scm が同一フォルダに存在する必要があります)  
  しばらくすると音楽が鳴ります。演奏が終わると終了します。


## ファイルについて
- test1001.scm の25行目の「 (set! pcm-raw (mml->pcm 」の下がMMLの文字列になっています。  
  ここを書き換えることで、いろいろな音楽を演奏できます。

- MMLの解釈は mmlproc.scm というモジュールで行っています。  
  mmlproc の詳細については、以下のページを参照ください。  
  https://github.com/Hamayama/mmlproc


## 環境等
- OS
  - Windows 8.1 (64bit)
- 環境
  - MinGW (32bit) v4.8.1
- 言語
  - Gauche v0.9.4
  - Gauche v0.9.5_pre1

## 履歴
- 2015-12-24  v1.00 初版
- 2015-12-24  v1.01 不要行削除


(2015-12-24)
