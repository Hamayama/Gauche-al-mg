# Gauche-al-mg

## 概要
- Gauche-al を MinGW (32bit) 上で動くように改造したものです。  
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

2. html 生成の変更  
   texi2html が MinGW になかったので、makeinfo --html に変更。
   - doc/Makefile.in

3. 重複行の削除
   - lib/al.scm

4. 定数の追加等
   - src/gauche-al.h
   - src/gauche-al.c

5. CiSEのバージョンアップに対応
   - src/al-lib.stub
   - src/alc-lib.stub
   - src/alut-lib.stub


## インストール方法
- MinGW環境でのインストール手順を、以下に示します。

1. Gaucheのインストール  
   事前に Gauche がインストールされている必要があります。  
   以下のページに Windows用バイナリインストーラ があるので、インストールを実施ください。  
   http://practical-scheme.net/gauche/download-j.html  
   (すでにインストール済みであれば本手順は不要です)

2. MinGWのインストール  
   事前に MinGW がインストールされている必要があります。  
   以下のページを参考に、インストールを実施ください。  
   https://gist.github.com/Hamayama/362f2eb14ae26d971ca4  
   (すでにインストール済みであれば本手順は不要です)

3. OpenALのインストール  
   https://www.openal.org/downloads/  
   から OpenAL 1.1 Core SDK (zip) をダウンロードして展開し、  
   中の OpenAL11CoreSDK.exe を実行します。  
   デフォルトのフォルダにインストールしてください。  
   「Yes, launch the OpenAL redist and finish.」を選択して終了してください。

4. OpenALのファイルのコピー  
   C:\Program Files (x86)\OpenAL 1.1 SDK\include の中のファイル一式を、  
   C:\MinGW\include\AL というフォルダを作成してそこにコピーします。  
   また、  
   C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win32\OpenAL32.lib を、  
   C:\MinGW\lib に libopenal32.dll.a とリネームしてコピーします。  
   (注意) リネームしないと、(7)のコンパイルで libalut-0.dll の生成に失敗します。

5. freealut のダウンロード  
   https://github.com/vancegroup/freealut  
   から Download Zip ボタン等でソースをダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\freealut の下にファイルとフォルダ一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

6. freealut のソースの修正  
   src/alutUtil.c をテキストエディタで開いて、1行目の
   ```
     #include "alutInternal.h"
   ```
   の下に以下の行を追加してください。
   ```
     #if defined(__MINGW32__)
     #undef HAVE_NANOSLEEP
     #undef HAVE_USLEEP
     #endif
   ```

7. freealut のコンパイルとインストール  
   コマンドプロンプトを開いて以下を実行します。
   ```
     bash
     cd /c/work/freealut
     ./autogen.sh
     ./configure --prefix=/mingw LDFLAGS="-static-libgcc"
     make
     make install
   ```
   (注意) LDFLAGSの指定をしないと、Gaucheの終了時に  
   「This application has requested the Runtime to terminate it in an unusual way.  
    Please contact the application's support team for more information.」  
   というエラーが発生します。(原因は不明)

8. Gauche-alのソースの展開  
   本サイト( https://github.com/Hamayama/Gauche-al-mg )のソースを、  
   (Download Zip ボタン等で)ダウンロードして、作業用のフォルダに展開してください。  
   例えば、作業用のフォルダを c:\work とすると、  
   c:\work\Gauche-al の下にファイルとフォルダ一式が配置されるように展開してください。  
   (注意) 作業用フォルダのパスには、空白を入れないようにしてください。

9. Gauche-alのコンパイル  
   コマンドプロンプトを開いて以下を実行します。
   ```
     bash
     cd /c/work/Gauche-al
     ./DIST gen
     ./configure
     make
   ```

10. Gauche-alのインストール  
   コマンドプロンプトを開いて以下を実行します。
   ```
     bash
     cd /c/work/Gauche-al
     make install
   ```
   Gaucheのライブラリフォルダに生成したファイルがコピーされます。  
   (注意) 環境によっては make install を実行すると、  
   「*** SYSTEM-ERROR: mkstemp failed」というエラーが発生します。  
   このエラーは c:\Program Files (x86) のフォルダに 書き込み権限がないとき等に発生します。  
   その場合は、コマンドプロンプトを開くときに、  
   コマンドプロンプトのアイコンを右クリックして、「管理者として実行」を選択してください。  
   そして再度上記のコマンドを実行してください。

11. Gauche-alのテスト  
   コマンドプロンプトを開いて以下を実行します。
   ```
     bash
     cd /c/work/Gauche-al
     make check
   ```
   テスト結果はsrcフォルダ内のtest.logに記録されます。

- 以上です。


##使い方
- examples フォルダに 実行可能なサンプルがあります。


## その他 問題点等
1. 音声ファイルの再生終了時にノイズが出ます。  
   以下のページの方法で回避できるかもしれない(未確認)。  
   http://gamedev.stackexchange.com/questions/71571/how-do-i-prevent-clicking-at-the-end-of-each-sound-play-in-openal


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
   こうしないと、"undefined reference to '_imp__xxx'" のようなエラーが発生します。


## 環境等
- OS
  - Windows 8.1 (64bit)
- 環境
  - MinGW (32bit) v4.8.1
- 言語
  - Gauche v0.9.4
  - Gauche v0.9.5_pre1
- ライセンス
  - オリジナルと同様とします

## 履歴
- 2015-12-17  v1.0-mg0001 MinGW対応


(2015-12-17)
