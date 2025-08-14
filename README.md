# Gauche-al-mg

## 概要
- Gauche-al を MinGW 上で動くように改造したものです。  
  Gauche-al は、Gauche から OpenAL を使用するための拡張ライブラリです。

- オリジナルの情報は、以下にあります。  
  http://www.koguro.net/prog/Gauche-al/index-j.html  
  ただし、ソースコードは、  
  https://bitbucket.org/nkoguro/gauche-al  
  で最新と思われる コミット 9cf7a8a (2005-10-9) をダウンロードしてベースとしました。


## 変更点
- オリジナルからの変更点を、以下に示します。

1. ビルド関連  
   DIST を、c-wrapper のものをベースにして作成。  
   また、  
   configure.ac, Makefile.in, lib/Makefile.in, src/Makefile.in, test.scm を、
   ```
   gauche-package generate --autoconf Gauche-al al
   ```
   で作成したものをベースにして書き換えた。

2. ドキュメントファイル修正等
   - texi2html が MinGW になかったので、makeinfo --html に変更
     - doc/Makefile.in
   - ドキュメントファイルのインデックス追加
     - doc/gauche-al-refe.texi
     - doc/gauche-al-refj.texi

3. 重複行の削除
   - lib/al.scm

4. 定数の追加等
   - src/gauche-al.h
   - src/gauche-al.c

5. CiSE のバージョンアップに対応
   - src/al-lib.stub
   - src/alc-lib.stub
   - src/alut-lib.stub

6. Makefile 修正  
   コンパイル時に CFLAGS の内容を反映するようにした。
   - src/Makefile.in

7. MSYS2/MinGW-w64 (64bit/32bit) 環境でのビルドに対応  
   - automake v1.15 の使用
     - config.guess
     - config.sub
     - install-sh
   - libalut-0.dll のコピー処理追加
     - Makefile.in
   - 日本語マニュアルの文字コード変更 (EUC → UTF-8) とヘッダ情報の追加
     - doc/gauche-al-refj.texi
     - doc/Makefile.in

8. ドキュメント修正
   - AL_STOPPEND → AL_STOPPED
   - ALCdevice → ALCcontext

9. サンプルの演奏終了チェック処理修正
   - eq? → eqv?

10. al.scm の修正
    - make-u8vector → make-u32vector

11. MSYS2/MinGW-w64 UCRT64 (64bit) 環境でのビルドに対応 (2025年8月)
    - 非推奨 (deprecated) の関数を置き換え
    - example/mml/mmlproc.scm のエラーを修正


## インストール方法
- MSYS2/MinGW-w64 UCRT64 (64bit) 環境でのインストール手順を、以下に示します。

1. Gauche のインストール  
   事前に Gauche がインストールされている必要があります。  
   以下のページに Windows用バイナリインストーラ があるので、インストールを実施ください。  
   http://practical-scheme.net/gauche/download-j.html  
   (すでにインストール済みであれば本手順は不要です)

2. MSYS2/MinGW-w64 UCRT64 (64bit) のインストール  
   事前に MSYS2/MinGW-w64 UCRT64 (64bit) がインストールされている必要があります。  
   以下のページを参考に、開発環境のインストールを実施ください。  
   https://gist.github.com/Hamayama/7810d2a1a59a872a2fbc271345151f77  
   (すでにインストール済みであれば本手順は不要です)  

3. OpenAL Soft のインストール  
   https://github.com/kcat/openal-soft/releases  
   から、  
   openal-soft-X.XX.X-bin.zip  
   をダウンロードして展開します。  
   中の bin/Win64 フォルダ内の soft_oal.dll を OpenAL32.dll にリネームして、  
   C:\msys64\ucrt64\bin フォルダにコピーします。

4. OpenAL Soft のファイルのコピー  
   3. で展開した中の include フォルダ内の AL フォルダを、  
   C:\msys64\ucrt64\include フォルダにコピーします。  
   また、libs\Win64 フォルダ内の libOpenAL32.dll.a を、  
   C:\msys64\ucrt64\lib フォルダにコピーします。

5. freealut のダウンロード  
   https://github.com/vancegroup/freealut  
   から Download Zip ボタン等でソースをダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\freealut の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

6. freealut のコンパイルとインストール  
   ＜MSYS2/MinGW-w64 UCRT64 (64bit) 環境＞  
   プログラムメニューから MSYS2 の UCRT64 Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/freealut
     ./autogen.sh
     ./configure --prefix=/ucrt64
     make
     make install
   ```
   
   - (注意) ./autogen.sh では warning が複数出ます。

7. Gauche-al のソースの展開  
   本サイト ( https://github.com/Hamayama/Gauche-al-mg ) のソースを、  
   (Download Zip ボタン等で) ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\Gauche-al の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

8. Gauche-al のコンパイル  
   ＜MSYS2/MinGW-w64 UCRT64 (64bit) 環境＞  
   プログラムメニューから MSYS2 の UCRT64 Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/Gauche-al
     ./DIST gen
     ./configure
     make
   ```

9. Gauche-al のインストール  
   ＜MSYS2/MinGW-w64 UCRT64 (64bit) 環境＞  
   プログラムメニューから MSYS2 の UCRT64 Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/Gauche-al
     make install
   ```
   Gaucheのライブラリフォルダに生成したファイルがコピーされます。  
   
   - (注意) 環境によっては、make install を実行すると  
     「gauche-install: no write permission of ...」もしくは  
     「*** ERROR: mkstemp failed」というエラーが発生します。  
     このエラーは、インストール先のフォルダに書き込み権限がないとき等に発生します。  
     その場合には、プログラムメニューからの開発環境の起動時に右クリックして、  
     「管理者として実行」を選択してください。  
     そして再度上記のコマンドを実行してください。

10. Gauche-al のテスト  
    ＜MSYS2/MinGW-w64 UCRT64 (64bit) 環境＞  
    プログラムメニューから MSYS2 の UCRT64 Shell を起動して、以下のコマンドを実行してください。  
    ( c:\work にソースを展開した場合)
    ```
      cd /c/work/Gauche-al
      make check
    ```
    テスト結果は test.log に記録されます。
    
    - (注意) テストで、  
      「*** ERROR: failed to link ./src/al.dll dynamically: error code 127」  
      というエラーが出る場合、  
      C:\msys64\ucrt64\bin フォルダ内の libwinpthread-1.dll を、  
      C:\Program Files\Gauche\bin フォルダ内の libwinpthread-1.dll に上書きしてみてください。  
      (現状のファイルのバックアップをとってから、上書きコピーする等)

- 以上です。


## 使い方
- example フォルダに 実行可能なサンプルがあります。

- また、以下のページで、alaudplay.scm というモジュールを使って、  
  いくつかのサンプルで効果音を出しています。  
  https://github.com/Hamayama/Gauche-gl-examples


## その他 問題点等
1. 音声ファイルの再生終了時にノイズが出る。  
   → 音声再生終了後、少し待ってから alut-exit を実行するようにしたら回避できた(2015-12-24)。

2. example フォルダのサンプル実行時に、  
   「gosh.exe - エントリ ポイントが見つかりません  
   プロシージャ エントリ ポイント nanosleep64 がダイナミック リンク ライブラリ  
   C:\Program Files\Gauche\bin\libalut-0.dll から見つかりませんでした。」  
   というエラー (メッセージボックス) が出る場合、  
   C:\msys64\ucrt64\bin フォルダ内の libwinpthread-1.dll を、  
   C:\Program Files\Gauche\bin フォルダ内の libwinpthread-1.dll に上書きしてみてください。  
   (現状のファイルのバックアップをとってから、上書きコピーする等)


## その他 ノウハウ等
1. OpenAL Soft については、  
   MSYS2 のパッケージに mingw-w64-ucrt-x86_64-openal (1.24.3-2) がありますが、  
   dll が、libstdc++-6.dll と libgcc_s_seh-1.dll に依存しています。  
   このため、現状は使用していません(2025-8-12)。

2. freealut については、  
   MSYS2 のパッケージに mingw-w64-ucrt-x86_64-freealut (1.1.0-3) がありますが、  
   2006 年の古いソースがビルドされています。  
   (このソースでは、alutLoadWAVMemory() は、バグのため動作しません)  
   このため、現状は使用していません(2025-8-12)。

3. Linux 上での利用について (参考)  
   以下は、Windows の VirtualBox 内の Linux Mint 19.3 (Cinnamon) 上で  
   動作させたときのメモです(2020-4-12)。
   ```
   # Gauche のインストール
   #  ( get-gauche.sh 内の make -j を make に置換しないと、(多分PCが非力なため) 固まった )
   sudo apt install automake
   sudo apt install libtool
   curl -f -o get-gauche.sh https://raw.githubusercontent.com/shirok/get-gauche/master/get-gauche.sh
   sed -i -e 's/make -j/make/' get-gauche.sh
   chmod +x get-gauche.sh
   ./get-gauche.sh

   # Gauche-al のインストール
   #  ( 本サイト ( https://github.com/Hamayama/Gauche-al-mg ) のソースを取得してインストール )
   sudo apt install libopenal-dev
   sudo apt install libalut-dev
   sudo apt install texinfo
   ./DIST gen
   ./configure
   make
   make check
   sudo make install

   # サンプルの実行
   cd example
   gosh play.scm
   gosh mml/test1001.scm
   ```


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
- ライセンス
  - オリジナルと同様とします


## 履歴
- 2015-12-17 v1.0-mg0001 MinGW (32bit) 対応
- 2015-12-17 v1.0-mg0002 ドキュメントファイル修正等
- 2015-12-17 v1.0-mg0003 DISTを追加し忘れていたので追加
- 2015-12-17 v1.0-mg0004 doc/Makefile.in 修正
- 2015-12-17 v1.0-mg0005 Makefile.in 修正
- 2015-12-20 v1.0-mg0005 src/Makefile.in 修正
- 2015-12-24 v1.0-mg0006 サンプルに再生終了時のノイズ対策を追加。また、MML音楽演奏サンプル追加
- 2015-12-24 v1.0-mg0007 lib/Makefile.in と src/Makefile.in を修正
- 2016-1-1   v1.0-mg0008 変更点 7. 対応
- 2016-1-6   v1.0-mg0009 ドキュメントファイル修正
- 2016-1-9   v1.0-mg0010 MSYS2/MinGW-w64(32bit)環境に暫定対応
- 2016-3-31  v1.0-mg0011 変更点 8. - 10. 対応
- 2016-10-12 v1.0-mg0012 README修正のみ(Gauche v0.9.5 で動作確認)
- 2017-5-17  v1.0-mg0013 configure.ac 修正
- 2017-5-26  v1.0-mg0014 コメント修正のみ
- 2017-6-3   v1.0-mg0015 configure.ac 修正
- 2018-7-9   v1.0-mg0015 README修正のみ(Gauche v0.9.6 で動作確認)
- 2018-12-29 v1.0-mg0016 Gauche v0.9.7 対応 (src/Makefile.in を修正)
- 2019-12-29 v1.0-mg0016 README修正のみ(Gauche v0.9.9 で動作確認)
- 2020-4-12  v1.0-mg0017 configure.ac修正(Linux上で動作確認(参考用))
- 2020-5-30  v1.0-mg0018 configure.ac修正(Mac対応(動作未確認))
- 2025-8-12  v1.0-mg0019 MSYS2/MinGW-w64 UCRT64 (64bit) 環境に対応


(2025-8-14)
