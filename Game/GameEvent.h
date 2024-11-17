#pragma once
#include "EnemyManager.h"
#include "JsonUtility.h"
#include "EN_Romanoff.h"
//定数
constexpr auto MAX_EVENT_NUM = 18;
constexpr auto MAX_SPAWN_WAVE = 6;
class GameEvent
{
public:
	struct EVENT
	{	//画像ハンドル
		int handleUI;
		//イベントカウント
		int eventCnt;
		//イベントカウント最大値
		int maxEventCnt;
		//イベント発生中
		bool isOccur;
		//ボイスキー
		std::string voiceCode;
	};
public:
	GameEvent();
	virtual ~GameEvent();
	//インスタンス
	static GameEvent* _evInstance;
	void Process();
	void Render();
public:
	bool GameOver();
	bool GameClear(EN_Romanoff* en);
	//イベント登録
	void RegisterEvent();
	//イベント発生
	void OccurEvent(int i);
	//wavw更新
	void EnemyWaveInit(int i);
	//イベント発生に関する処理
	void OccurProcess();
	//waveに関する処理
	void WaveProcess();
	//waveに関するイベント番号
	bool WaveNum(int i);
	//ストーリーに関するイベント番号
	bool StoryNum(int i);
	//ディバインに関するイベント番号
	bool DivineNum(int i);
	//イベントに関する処理
	void EventProcess();
	//ボスステージの敵召喚
	void CastEnemy(int i);
	//召喚に関する処理
	void CastProcess();
	//UIの表示(UIクラスに使う)
	void DrawQuest();
	void DrawWave();
	void DrawEventUI();
	//ゲッター
	static GameEvent* GetInstance() { return _evInstance; }
	EnemyManager* GetEnemyManager() { return _enManager; }
	int GetEvent() { return _storyEv; }
	int GetDivineEvent() { return _divineEv; }
	//セッター
	void SetEvent(int i) { _storyEv += i; }
	void SetDivineEvent(int i) { _divineEv += i; }
protected:
	//クエスト画像ハンドル
	int _handleQuestFeld[11];
	int _hamdleQuestRomanoff[7];
	//番号
	int _initNum;
	int _questNum;
	//モデルハンドル
	int _handle[3];
	//武器モデルハンドル
	int _wModel[2];
	//ボスの体力比較用変数
	int _hpCast;
	//イベントカウント
	int _storyEv;
	int _waveEv;
	int _hpEv;
	int _divineEv;
	//タイムカウント
	int _timeCnt;
	//敵マネージャー
	EnemyManager* _enManager;
	EVENT _event[MAX_EVENT_NUM];
	
};

