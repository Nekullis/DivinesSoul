『ディバインズソウル』 説明書
--------------------------------
# 必要動作環境
 Windows 10
 DirectX
--------------------------------
# ジャンル
無双アクションゲーム（一人プレイ）
--------------------------------

# 操作説明
Directモードのゲームパッドでの操作を想定しています。

スティック（十字キー）：移動

Bボタン：通常攻撃
Aボタン：スキル（緑フレーム）、項目の決定、次へ
Xボタン：スキル（青フレーム）
Yボタン：スキル（黄フレーム）
--------------------------------
# 概要説明            
バトル中にガチャを回す、新感覚の３Dアクション無双ゲーム！
すべての敵を倒すごとに次の敵が出現し、ステージ最奥に登場するボスを撃破すればゲームクリア！
A、X、Yボタンにはそれぞれ一つずつアクションスキルがセットされており、威力や攻撃範囲がそれぞれ違うぞ！
敵を50体倒すたびにガチャが作動し、最後に使用したスキルが別のスキルへと入れ替わる！8種類のスキルを入れ替えながら戦おう！
ボスとの死闘の先に、待ち受ける結末とは…！？

スキル一覧
エクスプロージョン：前方に強力な大爆発を引き起こす
レーザー：奥に届きやすい攻撃
スラッシュ：周囲を回転攻撃する
ブレス：前方に扇状の炎攻撃
サークル：プレイヤーの周りを一定時間攻撃
ダッシュアタック：素早く移動し敵に突進する攻撃
バキューム：敵をプレイヤーの前に吸引する
ソニックウェーブ：出が早い高周波攻撃
--------------------------------
# 改良期間
2024/7/3～2024/08/7（約4か月間）
-------------------------------
# 開発体制
アミューズメントメディア総合学院
製作チーム『SOUL MATE』


企    画：ゲームクリエイター学科プランナー専攻1年
荒木  涼大（メインプランナー）
山口 雄之輔（サブプランナー）
三嶋  拓也（サブプランナー）


プログラム ：ゲームクリエイター学科ゲームプログラマー専攻1年
福間  恭兵（リード・メインシステム）
奈良  充樹（マップ・制御）
佐藤  駿斗


グラフィック：ゲーム・アニメ3DCG学科1年
中野  利美（ボスキャラモデル）
紺野  透以（プレイヤーキャラモデル）
高橋 こなつ（キャラクターモーション）
渡 邊  凛（ステージ）
具志堅 夏生（エフェクト）


キャラクターボイス：声優学科1年
片山  右京（フェルド役）
田島  健人（ロマノフ役）
三輪  純玲（ディバイン／スキル名コール役）


--------------------------------
# 開発環境
この作品の制作には、下記のソフトウェアを使用させていただきました。大変感謝致します。
OS：Windows 11
言語：C/C++


プログラム：
Microsoft Visual Studio 2022
DXライブラリ
（PNG読み込み機能）
libpng Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.
zlib Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.
（GetRand機能）
 Mersenne Twister
 Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,All rights reserved.


ビジュアル：
Adobe After Effects
Adobe Photoshop CS
Adobe Premiere Pio
CLIP STUDIO PAINT
Effekseer


3D:
Autodesk Maya
Autodesk Motion Builder
Unreal Engine5
Zbrush

サウンド：
Adobe Audition
Audacity 

--------------------------------
# 使用素材
この作品の制作には、下記の製作者様の素材を使用させていただきました。素晴らしい作品に誠に感謝申し上げます。

画像素材：
イラストAC

効果音：
効果音ラボ
 On-Jin ～音人～
ポケットサウンド – https://pocket-se.info3333
無料効果音で遊ぼう！
audioAtelier（音々亭）
OtoLogic
voicebot
ニコニ・コモンズ

BGM：
DOVA-SYNDROME
甘茶の音楽工房
--------------------------------
# 注意事項
・本作が原因で何らかの損害や障害等が発生した場合でも、当方は一切の責任を負わないものとします。

・本作の無断転載・無断商用利用は禁止です。また、ゲームに使用された画像や音声など、あらゆるデータの無断での再配布・販売も一切禁止します。
--------------------------------

# 使用ライブラリ
[DX ライブラリ](https://dxlib.xsrv.jp/)
[nlohmann-json](https://github.com/nlohmann/json)

# プロジェクト構成と起動方法
下記 DxLib ディレクトリ内に [DX ライブラリ Windows版 VisualStudio(C++)用](https://dxlib.xsrv.jp/DxLib/DxLib_VC3_24d.zip) を DownLoad して解凍後の ***プロジェクトに追加すべきファイル_VC用*** ディレクトリの内容を全てコピーします。
下記 include ディレクトリ内に[nlohmann](https://github.com/nlohmann/json)をDownLoad して解凍後のnlohmannファイルを全てコピーします。

# ディレクトリ詳細
<details>
<summary>ディレクトリ</summary>
<pre>
.
├── DxLib(ライブラリ用ディレクトリ)
│
├── AppFrame(自作ゲームフレームワーク用のライブラリ Project)
│   │
│   ├── AppFrame
│   │   │
│   │   └── Application
|   |   |   |
|   |   |   └── ApplicationBase(Dxライブラリやループ処理を行う基底クラスファイル)
|   |   |   |
|   |   |   └── WinMain(ゲーム全体の処理をするソースファイル)
│   │   │
│   │   └── CFile
|   |   |   |
|   |   |   └── CFile(外部ファイルの読み込み、書き込みに関するクラスファイル)
│   │   │
│   │   └── ModeServer
|   |   |   |
|   |   |   └── ModeBase(モードの基底クラスファイル)
|   |   |   |
|   |   |   └── ModeServer(モードの追加、削除などの管理クラスファイル)
│   │   │
│   │   └── Object
|   |   |   |
|   |   |   └── ObjectBase(ゲーム内の物体の基底クラスファイル)
│   │   │
│   │   └── Reference
|   |   |   |
|   |   |   └── ColorFormat(RGBの色フォーマットに関するヘッダーファイル)
|   |   |   |
|   |   |   └── MyCollision(当たり判定に関するクラスファイル)
|   |   |   |
|   |   |   └── MyDraw(2Dでの矩形描画クラスファイル)
|   |   |   |
|   |   |   └── MyMath(イージング、デグリーラジアンの変換などを行うクラスファイル)
|   |   |   |
|   |   |   └── MyStruct(自作構造体をまとめるクラスファイル)
│   │   │
│   │   └── ResourceServer
|   |   |   |
|   |   |   └──ResourceServer(リソース管理のクラスファイル)
│   │   │
│   │   └── System
|   |       |
|   |       └── XPad
|   |       |   |
|   |       |   └── GameXPad(Xinputの処理クラスファイル)
|   |       |
|   |       └── GamePad(DirectInputの処理クラスファイル)
│   │   
│   ├── appframe.h(ヘッダーファイル)
│   │
│   ├── UtilMacro.h(ヘッダーファイル)
│   │
│   └── AppFrame.sln(Game.sln の方を起動して下さい)
│
└── Game(ゲーム本体の Project)
│   │
│   └──── Game
│      │
│      └── Actioncollision(当たり判定後の押し戻し、攻撃判定などの処理をまとめたクラスファイル)
│      │
│      └── ApplicationGlobal(ApplicationMainに実態を持つグローバルな関数をまとめるクラスファイル)
│      │
│      └── ApplicationMain(ApplicationBaseの派生。ゲームループを処理するクラスファイル)
│      │
│      └── Camera(カメラ制御を行うクラスファイル)
│      │
│      └── divine(ゲーム内スキルDivineの処理クラスファイル)
│      │
│      └── Effect(エフェクトの発生から終了までの処理のクラスファイル)
│      │
│      └── EN_Crab(Enemyクラスの派生で、カブトガニのような敵の処理をまとめたクラスファイル)
│      │
│      └── EN_Osero(Enemyクラスの派生で、人型の敵の処理をまとめたクラスファイル)
│      │
│      └── EN_Romanoff(Enemyクラスの派生で、ボスの処理をまとめたクラスファイル)
│      │
│      └── Enemy(ObjectBaseの派生で敵に関するObjectの基底クラスファイル)
│      │
│      └── EnemyManager(敵の出現、削除など敵を管理するクラスファイル)
│      │
│      └── EnumInfo(スキルなどで使うEnumをまとめたヘッダー)
│      │
│      └── Game.sln(こちらを起動して下さい)
│      │
│      └── GameEvent(ゲーム内の進行イベントを制御するクラスファイル)
│      │
│      └── GameSystem(ゲーム内システムに関する制御クラスファイル)
│      │
│      └── gameui(ゲーム内UIを制御、描画するクラスファイル)
│      │
│      └── JsonUtility(Jsonをこのプロジェクト内でも扱えるようにするクラスファイル)
│      │
│      └── MapEntity(ソースファイル)(ゲーム内マップの背景を描画するためのクラスファイル)
│      │
│      └── MathCollision(当たり判定の制御全般を扱うクラスに扱う関数をまとめたクラスクラスファイル)
│      │
│      └── ModeEnding(クリア後の映像を描画するクラスファイル)
│      │
│      └── ModeFade(モード間のフェード用のクラスファイル) 
│      │
│      └── ModeGame(ステージを管理するクラスファイル)
│      │
│      └── ModeGameClear(クリア後の画像を描画するクラスファイル)
│      │
│      └── ModeGameover(プレイヤー死亡後の画像を描画するファイル)
│      │
│      └── ModeLoad(ロード画面を描画するクラスファイル)
│      │
│      └── ModeLogo(ロゴ画像を描画するクラスファイル)
│      │
│      └── ModeSound(音関係を再生、停止するクラスファイル)
│      │
│      └── ModeTitle(タイトル画像を描画するクラスファイル)
│      │
│      └── ObjectManager(オブジェクトの配置、挙動を管理するクラスファイル)
│      │
│      └── Player(プレイヤーの処理全般クラスファイル)
│      │
│      └── PlayerManager(プレイヤー処理を安全に上の階層で扱えるようにするクラスファイル)
│      │
│      └── ResourceServer(外部ファイルでリソースを追加しやすくするためのクラスファイル)
│      │
│      └── SkillSlot(使用できるスキルを変更させるためのクラスファイル)
│      │
│      └── SoundItem(ModeSoundに使うアイテムの処理クラスファイル)
│      │
│      └── SoundServer(音声の追加、削除するためのクラスファイル)
│
└── include(nlohmann-jsonのインクルードファイル)

</pre>
</details>

# 担当したクラスファイル
<details>
<summary>ファイル</summary>

Actioncollision
divine
Effect
EN_Crab
EN_Osero
EN_Romanoff
Enemy
EnemyManager
GameEvent
GameSystem
gameui
MapEntity(一部)
MathCollision
ModeEnding
ModeFade
ModeGame
ModeGameClear
ModeGameover
ModeLoad
ModeLogo
ModeTitle
Player
PlayerManager
SkillSlot

</details>

# AppFrame フレームワーク概要
ゲームを作成する上で定形的に必要となる機能をまとめたフレームワーク  
Static Library の形式で提供(Project 設定)

### ApplicationBase
DX ライブラリを用いた Windows アプリケーションを作成する基底クラス  
本クラスを継承したクラスを作成すれば最小のコードでアプリのメイン部分を記述出来る

### ModeBase / ModeServer
本フレームワークはモードと呼ぶ単位でプログラミング可能になっており、モードを切り替える機能も提供します。  
これによりアプリ作成者は、モード単位の実装をする事でゲームのフローを構築出来ます。  

ModeBase を継承したクラス単位でタイトルやインゲーム、設定画面など好きな単位で構築でき  
ModeServer が各モードを切り替える機能を提供します。
