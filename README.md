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

5. CiSEのバージョンアップに対応
   - src/al-lib.stub
   - src/alc-lib.stub
   - src/alut-lib.stub

6. Makefile修正  
   コンパイル時に CFLAGS の内容を反映するようにした。
   - src/Makefile.in

7. MSYS2/MinGW-w64(64bit)環境でのビルドに暫定対応(実験中)  
   - automake v1.15 の使用
     - config.guess
     - config.sub
     - install-sh
   - libalut-0.dll のコピー処理追加
     - Makefile.in
   - 日本語マニュアルの文字コード変更 (EUC → UTF-8) とヘッダ情報の追加
     - doc/gauche-al-refj.texi
     - doc/Makefile.in

## インストール方法
- MinGW (32bit) 環境でのインストール手順を、以下に示します。

1. Gaucheのインストール  
   事前に Gauche がインストールされている必要があります。  
   以下のページに Windows用バイナリインストーラ があるので、インストールを実施ください。  
   http://practical-scheme.net/gauche/download-j.html  
   (すでにインストール済みであれば本手順は不要です)

2. MinGW (32bit) のインストール  
   事前に MinGW (32bit) がインストールされている必要があります。  
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
   (注意) リネームしないと、7. の freealut のコンパイルで libalut-0.dll の生成に失敗します。

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
   (注意) 上記の LDFLAGS の指定をしないと、Gaucheの終了時に  
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
   「*** ERROR: mkstemp failed」というエラーが発生します。  
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
   テスト結果は test.log に記録されます。

- 以上です。


##使い方
- examples フォルダに 実行可能なサンプルがあります。


## その他 問題点等
1. 音声ファイルの再生終了時にノイズが出る。  
   以下のページの方法で回避できるかもしれない。  
   http://gamedev.stackexchange.com/questions/71571/how-do-i-prevent-clicking-at-the-end-of-each-sound-play-in-openal  
   → 今回は、関係なかった。  
   → 音声再生終了後、少し待ってから alut-exit を実行するようにしたら回避できた(2015-12-24)。

2. freealut の deprecated (非推奨) のAPIを使用しているため、  
   Gauche-al のコンパイル時に warning が出ます。


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
  - MinGW (32bit) (gcc v4.8.1)
  - MSYS2/MinGW-w64 (64bit) (gcc version 5.3.0 (Rev1, Built by MSYS2 project)) (実験中)
- 言語
  - Gauche v0.9.4
  - Gauche v0.9.5_pre1
- ライセンス
  - オリジナルと同様とします

## 履歴
- 2015-12-17  v1.0-mg0001 MinGW (32bit) 対応
- 2015-12-17  v1.0-mg0002 ドキュメントファイル修正等
- 2015-12-17  v1.0-mg0003 DISTを追加し忘れていたので追加
- 2015-12-17  v1.0-mg0004 doc/Makefile.in 修正
- 2015-12-17  v1.0-mg0005 Makefile.in 修正
- 2015-12-20  v1.0-mg0005 src/Makefile.in 修正
- 2015-12-24  v1.0-mg0006 サンプルに再生終了時のノイズ対策を追加。また、MML音楽演奏サンプル追加
- 2015-12-24  v1.0-mg0007 lib/Makefile.in と src/Makefile.in を修正
- 2016-1-1    v1.0-mg0008 変更点 7. 対応
- 2016-1-6    v1.0-mg0009 ドキュメントファイル修正


(2016-1-6)
