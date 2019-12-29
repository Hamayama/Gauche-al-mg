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


## インストール方法
- MSYS2/MinGW-w64 (64bit/32bit) 環境でのインストール手順を、以下に示します。

1. Gauche のインストール  
   事前に Gauche がインストールされている必要があります。  
   以下のページに Windows用バイナリインストーラ があるので、インストールを実施ください。  
   http://practical-scheme.net/gauche/download-j.html  
   (すでにインストール済みであれば本手順は不要です)

2. MSYS2/MinGW-w64 (64bit/32bit) のインストール  
   事前に MSYS2/MinGW-w64 (64bit/32bit) がインストールされている必要があります。  
   以下のページを参考に、開発環境のインストールを実施ください。  
   https://gist.github.com/Hamayama/eb4b4824ada3ac71beee0c9bb5fa546d  
   (すでにインストール済みであれば本手順は不要です)  

3. OpenAL のインストール  
   https://www.openal.org/downloads/  
   から OpenAL 1.1 Core SDK (zip) をダウンロードして展開し、  
   中の OpenAL11CoreSDK.exe を実行します。  
   デフォルトのフォルダにインストールしてください。  
   「Yes, launch the OpenAL redist and finish.」を選択して終了してください。

4. OpenAL のファイルのコピー  
   C:\Program Files (x86)\OpenAL 1.1 SDK\include の中のファイル一式を、  
   C:\msys64\mingw64\include\AL というフォルダを作成してそこにコピーします。  
   (32bit環境の場合には、64 の部分を 32 に読み替えてください)  
   また、  
   C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win64\OpenAL32.lib を、  
   C:\msys64\mingw64\lib に libopenal32.dll.a とリネームしてコピーします。  
   (32bit環境の場合には、64 の部分を 32 に読み替えてください)  
   
   - (注意) ここで上記のリネームをしないと、  
     手順 6. の freealut のコンパイルで libalut-0.dll の生成に失敗します。  
     失敗のときはコンパイル時に以下のメッセージが表示されます。  
     「*** Warning: linker path does not have real file for library -lopenal32 ...」  
   
   - (注意) MinGW のバージョンが古い場合、  
     OpenAL32.lib を libopenal32.dll.a にリネームしてコピーしても、  
     手順 6. の freealut のコンパイルで libalut-0.dll の生成に失敗することがあります。  
     このときは、c:\windows\system32 等にインストールされている OpenAL32.dll の方を、  
     C:\msys64\mingw64\lib に libopenal32.dll.a とリネームしてコピーしてみてください。  
     (32bit環境の場合には、64 の部分を 32 に読み替えてください)

5. freealut のダウンロード  
   https://github.com/vancegroup/freealut  
   から Download Zip ボタン等でソースをダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\freealut の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

6. freealut のコンパイルとインストール  
   ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 64bit Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/freealut
     ./autogen.sh
     ./configure --prefix=/mingw64
     make
     make install
   ```
   ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 32bit Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/freealut
     ./autogen.sh
     ./configure --prefix=/mingw32
     make
     make install
   ```
   
   - (注意) ./autogen.sh では warning が複数出ます。
   
   - (注意) MinGW のバージョンが古くて、alutUtil.c のコンパイルでエラーが発生する場合には、  
     src/alutUtil.c をテキストエディタで開いて、1行目の
     ```
     #include "alutInternal.h"
     ```
     の下に以下の行を追加してみてください。
     ```
     #if defined(__MINGW32__)
     #undef HAVE_NANOSLEEP
     #undef HAVE_USLEEP
     #endif
     ```
   
   - (注意) MinGW のバージョンが古くて、Gauche の終了時に  
     「This application has requested the Runtime to terminate it in an unusual way.  
      Please contact the application's support team for more information.」  
     というエラーが発生する場合には、  
     make clean で一度生成ファイルをクリアしてから、上記手順の  
     ./configure のオプションに LDFLAGS="-static-libgcc" を追加してみてください。  

7. Gauche-al のソースの展開  
   本サイト ( https://github.com/Hamayama/Gauche-al-mg ) のソースを、  
   (Download Zip ボタン等で) ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\Gauche-al の下にファイル一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

8. Gauche-al のコンパイル  
   ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 64bit Shell を起動して、以下のコマンドを実行してください。  
   ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 32bit Shell を起動して、以下のコマンドを実行してください。  
   ( c:\work にソースを展開した場合)
   ```
     cd /c/work/Gauche-al
     ./DIST gen
     ./configure
     make
   ```
   
   - (注意) freealut の deprecated (非推奨) のAPIを使用しているため、  
     コンパイル時に warning が出ます。
   
   - (注意) MinGW のバージョンが古くて、C99モードではないというエラーが発生する場合には、  
     make clean で一度生成ファイルをクリアしてから、上記手順の  
     ./configure のオプションに   
     CFLAGS="-g -O2 -std=gnu99"  
     または、  
     CPPFLAGS="-D_STAT_DEFINED -D_WSTAT_DEFINED" CFLAGS="-g -O2 -std=gnu99"  
     を追加してみてください。

9. Gauche-al のインストール  
   ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 64bit Shell を起動して、以下のコマンドを実行してください。  
   ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
   プログラムメニューから MSYS2 の MinGW 32bit Shell を起動して、以下のコマンドを実行してください。  
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
    ＜MSYS2/MinGW-w64 (64bit) 環境の場合＞  
    プログラムメニューから MSYS2 の MinGW 64bit Shell を起動して、以下のコマンドを実行してください。  
    ＜MSYS2/MinGW-w64 (32bit) 環境の場合＞  
    プログラムメニューから MSYS2 の MinGW 32bit Shell を起動して、以下のコマンドを実行してください。  
    ( c:\work にソースを展開した場合)
    ```
      cd /c/work/Gauche-al
      make check
    ```
    テスト結果は test.log に記録されます。

- 以上です。


## 使い方
- example フォルダに 実行可能なサンプルがあります。  
  (注意) 古いPC (Windows XP SP3) では、音楽が鳴ったり鳴らなかったりする場合がありました。  
  このとき、オーディオの詳細プロパティで、「ハードウェア アクセラレータ」の設定を、  
  「最大」から「標準」に変更したところ、改善したケースがありました。

- また、以下のページで、alaudplay.scm というモジュールを使って、  
  いくつかのサンプルで効果音を出しています。  
  https://github.com/Hamayama/Gauche-gl-examples


## その他 問題点等
1. 音声ファイルの再生終了時にノイズが出る。  
   以下のページの方法で回避できるかもしれない。  
   http://gamedev.stackexchange.com/questions/71571/how-do-i-prevent-clicking-at-the-end-of-each-sound-play-in-openal  
   (ヘッダーにあるデータ長の分だけデータを読み込むようにする)  
   → 今回は、関係なかった。  
   → 音声再生終了後、少し待ってから alut-exit を実行するようにしたら回避できた(2015-12-24)。


## その他 ノウハウ等
1. freealut の静的リンクについて  
   今回は行いませんが、freealut を静的にリンクしたい場合には、  
   include/AL/alut.h の23行目の  
   ```
     #define ALUT_API __declspec(dllimport)
   ```
   
   を、  
   ```
     #define ALUT_API extern
   ```
   
   に変更する必要があります。  
   こうしないと、`undefined reference to '_imp__xxx'` のようなエラーが発生します。


## 環境等
- OS
  - Windows 8.1 (64bit)
  - Windows XP Home SP3
- 環境
  - MSYS2/MinGW-w64 (64bit/32bit) (gcc version 9.2.0 (Rev2, Built by MSYS2 project))
  - MinGW (32bit) (gcc version 6.3.0 (MinGW.org GCC-6.3.0-1))
- 言語
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


(2019-12-29)
