DirectX Foundation 6.1 SDK 

この CD の \DXF ディレクトリに全ての DirectX Foundation SDK コンポーネントが入っています。
__________________________________________________________________

目次
 
- インストール
- 更新されたSDK
- CDのレイアウト
- 新機能
- 既知の問題
- 対応コンパイラ
__________________________________________________________________

インストール

全ての DirectX 6.1 SDK と/または ランタイムをインストールするためには、メイン メニューから
「Install DirectX Foundation 6.1 SDK」を選択するか、CDの \DXF ディレクトリにある setup.exe を
実行してください。すでにある MSDN Platform SDK 上にインストールする場合は、この readme の
『更新されたSDK』の項目をご覧下さい。

DirectX 6.1 をインストールする前に、DirectX SDK の前のバージョンをアンインストールしてください
 (次のアンインストール参照)。ディレクトリ構造とファイル名が大きく変更されています。

アンインストール:
アンインストールするには、コントロールパネルの「アプリケーションの追加と削除」を使用してください。

__________________________________________________________________

更新されたSDK

先の DX6 リリースと同様、MSDN プラットフォーム SDK とより良く統合するようにしました。
もし以前に MSDN プラットフォーム SDK をインストールしてあれば、DX6.1 Foundation SDK は
それを検出し、そのディレクトリにインストールされるでしょう。そうでない場合は、SDKをどこに
インストールするかを選択できます。

他の大きな改善としては、DirectMusic (後述) が追加された事と、より詳細で正確なドキュメントと、
新しい機能を紹介する D3D IM サンプルです。

__________________________________________________________________

CDのレイアウト

以下に、CDの \DXF ディレクトリ内のディレクトリの簡単な説明を記します。インストール中の
オプションを選択する事により、これらのうちのいくつかのディレクトリが、ハードディスクに
インストールされます。

\Bin
  ハイレベルな DirectX アプリケーションとツール。
  「Utilitys」をインストールすると、全てスタートメニューからアクセス可能です。

\Debug
  DirectX 6.1 DLLのデバッグ版

\Doc
  DirectX APIのドキュメントが入っています。最新のDX 6.1のドキュメントは HTMLHelp で最も良く
  閲覧できます。HTMLHelp ビューアは Internet Explorer 4.0(IE4) と一つのアクティブコントロールの
  インストールが必要になります。これは Windows95 へインストールした場合に必要です。 
  詳細は \Extras\msie401\htmlhelp ディレクトリ の readme.txt ファイルを参照してください。
  もし (IE4の) インストールを選択しなかった場合でも、DXF\docs\directX6\word\ にある
  Word ファイルを見ることが出来ます。

\Essentls
  DMusProd ( Direct Music Producer )
    - Direct Music Producer は DirectMusic のオーサリング ツールです。これを使えば DLS の
      コンシステント サウンド パフォーマンスに合わせて、インタラクティブに複数の DirectMusic 
      リソースを使う事ができます。Music Producer セットアップ プログラムと全てのファイルは
      ここにあります。
  DMusProd.jpn ( Direct Music Producer with Japanese localized install )
    - 上記の ( DmusProd ) フォルダと同じですが、日本語 Windowsで正しく動作するようインストール
       されます。

\Extras
  DMusic 
    - アップデートされたNT5 用のDMusic ランタイム コンポーネントをインストールするバッチファイルが
      含まれています。操作方法は同じディレクトリの readme.txt をお読みください。
  DSound
    - Voice Manager。Voice Manager Property Set を使えば、DirectSound3D をサポートしている
      カード上で、DirectSound3D の先進のボイス マネージメントが可能です。これを使ってハードウエア 
      アクセラレートされた DirectSound3D が容易にサポートされます。
  DDSPlugin
    - ここには DDS ファイルフォーマットを使ったDXTn 圧縮テクスチャをインポート・エクスポートする
      Photoshop プラグインが入っています。

  DX6 Drivers
    - このディレクトリには DX 6 ドライバがある IHV の Web サイトへのリンクが記述されている 
      HTML ドキュメントが入っています。
  Win98
    - Win98上で開発されている方には DirectX デバッグ DLL が必要です、私たちは Dsound と 
      Dinput 両方のデバッグ DLL を既に出荷しています。DX 6.1 SDK セットアップはそれらの
      コンポーネントをアップデートしません。詳細は DXF\extras\Win98\Readme.txt をお読みください。
  
\Include
  DirectDraw, Direct3D, DirectSound, DirectInput, DirectPlay, DirectMusicのインクルード ファイルが
  入っています。

\Lib
  DirectDraw, Direct3D, DirectSound, DirectInput, DirectPlayのライブラリファイルが入っています。
  *.LIB : COFF libraries (Microsoft Visual C++ 2.0 またはそれ以降)
  Borland 11.0 版のライブラリを含むサブディレクトリもあります。

\License
  DirectX SDK と End User License Agreements そして、Redistributable License Agreementの
  テキスト版

\Redist
  DirectX 6.1 DLLの再配布可能モジュール

\Samples
  全てのサンプルコードとバイナリが入っています。詳細は各ディレクトリに含まれる readme.txt を
  ご覧下さい。大部分のサンプルは、スタートメニューからアクセス可能です。

__________________________________________________________________

新機能

DirectMusic

DirectX 6.1 の本リリースには DirectMusic 最終リリースが含まれています。
SDK セットアップを実行すると、DirectMusic DLL は自動的にインストールされます。

DirectMusic API のドキュメントは DirectX 6.1 ドキュメントに含まれています。DirectMusic サンプル
コードも DirectX 6.1 SDK 内にあります。これらのオプションは DX6.1 SDK セットアップから選択可能
です。

DirectMusic オーサリングツール DirectMusic Producer もこのリリースに含まれています。
DirectX 6.1 CD の DXF\essentls\DMusProd ディレクトリから別途インストールできます。
Direct Music Producer の詳細は DirectMusic セットアップ プログラムと同じディレクトリの 
readme.txt をお読みください。

DirectMusic の WDM サポートは未実装です。

__________________________________________________________________

変更点

最大の変更点は DirectMusic の最終リリースです。他の分野の API についても小さな変更と
バグ修正が行われています。以下に修正をリストします。

DDraw

- AGP コマンドバッファが可能に
- AGP マシンの ModeX  が修正

D3DIM

- DX5 RAMP ラスタライザ のパフォーマンス向上。これは追加ファイル d3dramp.dll によって
  提供されます、これは 6.1 セットアップによってインストールされます。

- ビデオメモリー 頂点バッファのサポート改善

- Clear2 の PowerVR 使用の サポート改善

- ValidateDevice を実装するデバイスは要求された場合、テクスチャ フォーマットを考慮します。

- マルチ テクスチャ ステージのカウントがより適切になりました。

- 方向(Directional) ライトと、スポット ライト タイプは Pentium II で正しく処理されます。

- RAMP ラスタライザはグレースケールに Blue チャネルを使用し平均化しません。これは以前の
  バージョンと互換性があります。

- 頂点フォグはSPECULARENABLE を FALSE に設定しても動作します。

- 16ビット RAMP ラスタライザは COPY モードをサポートします。

- 2のべき乗以外のテクスチャに関する新しい CAP ビット。
  DX6.1 ドキュメントの 「D3DPTEXTURECAPS_NONPOW2CONDITIONAL」を参照してください。

Dplay

- シリアル サービス プロバイダは同時に複数ブロックのデータを発信しようとして、コネクションを
  失う場合がありましたが、アクセスはシリアルに行われるようになりました。

- セッション不良によりあるクライアントがドロップし、他のクライアントがプレーヤ タイムアウト前に
  そのゲームに加わろうとした時、それ以降の全ての参加が失敗となっていました。ホストが
  全プレーヤのタイムアウトを完了すれば、再び参加は成功するようになりました。

__________________________________________________________________

既知の問題 

DXMedia

- DirectX Media 6.0 は DirectX Foundation 6.1 デバッグ版と互換性がありません。
  DirectAnimation や DirectTransform を含む DirectX Media のコンポーネントを使用する場合には
  DirectX Foundation リテール版をお使いください。

DMusic

- DirectMusic は MSB と LSB コマンドのペアがマッチしない MIDI ファイルでは現在のところ問題が
  あります。MIDI の仕様では必ず MSB と LSB コマンドはマッチする事になっています。
  しかし DirectMusic チームは MIDI ファイルを作成するあるシーケンサ製品では MSB を含んでいる
  のに LSB が無い事を発見しました。このファイルをこの DirectMusic ベータ版で再生すると、
  いくつかのトラックを聞く事ができません。この問題を解決するには、MIDI ファイルをロードした後で、
  セグメントにGUID_IgnoreBankSelectForGM SetParam コールを使ってください。これによって、MSB 
  と LSB コマンドを削除し、正しく再生できるようになります。

- DMusic サンプルは NT5 Beta2 では動作しません。これは DX ランタイム インストレーションが 
  NT5 コンポーネントをアップデートできないからです。NT5 DMusic DLL をアップデートし、Dmusic 
  サンプルを動作できるようにするバッチファイルがあります。これは DXF\extras\DMusic ディレクトリに
  あります。

DDraw / D3DIM

- ミップマップを作成する時、トップレベル サーフェイスの幅か高さの小さいほうの値を(1/2)^n倍した時
  n の値が1より小さくなるような DDSURFACEDESC.dwMipMapCount を指定する事は認められて
  いません。例えば、4 x 2 のミップマップは dwMipMapCount = 2 しか許されず 3 は許されません。
  実際の実装では 4 x 2 のミップマップが 2 x 1 や 1 x 1 レベルを生成すると期待してはいけません。
  DirectDraw は最小ディメンジョンとして1までは許しますが、それ以下のミップレベルは許可しません。

- カラーバッファとZバッファが同じビット数でないとレンダリング ターゲットが作成できないボードが
  あります。次のような制限があります:
      16 ビット カラーバッファには 16ビット Z バッファが必要 ( ステンシル無し )
      32 ビット カラーバッファには 32 ビット Z バッファ ( うち 8 ビットは ステンシルになり得る )
  もしこの条件を満たさないと、 CreateDevice() あるいは SetTendertarget() が成功しません。
  この場合 GetDeviceIdentifier() を使って問題を避けてください。

DPlay

- DirectPlay4A::EnumConnections() API はシステム上の有効なサービスプロバイダについて必ず
  シングルバイト キャラクタ の文字列を返します。アプリケーション全体を Unicode に変更せず
  ローカライズしたマルチバイトの文字列を得るには、次の手順を行います。

      a) IDirectPlay4 インターフェイス(Unicode)で、QueryInterface
      b) IDirectPlay4::EnumConnections をコール - これによって Unicode 文字列を取得
      c) それぞれのストリングを Windows のWideCharacterToMultiByte() 関数を使って ANSI に変換
      d) IDirectPlay4 インターフェイスをリリース
      e) IDirectPlay4A インターフェイスを以降のアプリケーションでは使用し続ける。

  もう一つの方法として、IDirectPlay3A インターフェイスで QueryInterface をする事もできます。
  これも ローカライズされたマルチバイト キャラクタ 文字列を返し、ステップ c) で列挙できます。

- US Roboticsモデムの最新のドライバはセッションをホストする際に問題を引き起こすことがあります。
  これはドライバのバグです。

- モデム セッションを列挙している際に、電話回線を切断するとロックアップします。


サンプル

- DMusic サンプルは NT5 Beta2 では動作しません。これは DX ランタイム インストレーションが 
  NT5 コンポーネントをアップデートできないからです。NT5 DMusic DLL をアップデートし、Dmusic 
  サンプルを動作できるようにするバッチファイルがあります。これは DXF\extras\DMusic ディレクトリに
  あります。

- D3DIM サンプルは、DX 6.1 ソフトウェア ラスタライザ上で動作可能です。しかしながらレジストリ
  キーは、デフォルトで設定されておりません。
  正しいレジストリ設定は、DXF\samples\Multimedia\D3DIM\bin ディレクトリのファイルを使って行う
  ことができます。ソフトウェア ラスタライザのレジストリキーの設定を行わないと、バンプマップなどの
  DX 6.1特有のサンプルを最初に起動したときにそれを可能にするようメッセージが出るでしょう。
  これは、  ソフトウェア ラスタライザなので、非常に低いフレームレートであることをご了承下さい。

- デスクトップの解像度と、システムのビデオメモリーの使用可能な量によりますが、サンプル 
  テクスチャに対して十分なビデオメモリーが無い場合があります。この場合 D3DIM サンプルは
  動作しますが、テクスチャを表示できません(サーフェイスは白になるでしょう)。テクスチャを表示
  させるにはデスクトップの解像度をより低くするか、ディスプレイカードにより多くのメモリーを搭載
  してください。

- 新しいサンプル ( EnumTex) が SDK に追加されました。このサンプルでは開発者が知っておくべき
   テクスチャ列挙のロジックと範囲を示します。残念ながらこのサンプルに関するドキュメントの参照は
   ありません。

- DMHook DLL ( DMShell のヘルパー DLL ) は Watcom や Borland のコンパイラではコンパイル
  できません。Watcom と Borland ユーザーはSDK サンプルバイナリで提供される、既に作成された
  DMHook.dll をお使いください。

- 特定のハードウェアやドライバで、様々な問題があります。貴方がサンプルやドライバに起因すると
  思える問題はぜひお知らせ下さい。

- 日本語版の Windows を使っている場合、サンプル プログラムのダイアログ ボックス テキストで
  漢字が表示できないかもしれません。漢字を表示させるには、.RC ファイルを編集してダイアログ 
  フォントを日本語に変更してください。

- サンプルの詳細な情報は <drive>:\(sdk_path)\samples\multimedia の dxreadme.txt を参照して
  ください。

デバッグ インストール

- デバッグ インストレーション内に retail とマークされたファイルが表示される場合があります
  ( Ddrawex.dll と Dsound.vxd )。これはエラーではありません。これらのファイルはデバッグ版を使う
  必要がありません。

__________________________________________________________________

対応コンパイラ

DX 6.1 サンプルは VC++ 4.2またはそれ以降、Watcom 11.0、Borland C Builder 3で対応しています。
私どもは最も多く使われているコンパイラの対応への努力を続けてきました。VCプロジェクトファイル 
( VC4.2 用の .mdp )やVC、Watcom、Borland で動作するmakeファイルを含んでいます。

ビルド環境の設定には、CDRom:\DXF\samples\Multimedia\DXReadme.TXT をご覧下さい。
この README に次のようなビルド方法のセクションがあります、Note for VC++ Users、
Note for Watcom Users、Note for Borland Users。SDK はこの readme ファイルを 
<drive:>\(sdk_path)\samples\multimedia にインストールします。

いくつかのサンプルは Borland あるいは Watcom ではコンパイルできません。
これは大部分はDirectX 以外のコンポーネントやヘッダーファイルに要求されている変更が必要でした。
