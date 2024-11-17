#pragma once
#include "appframe.h"
#include "Divine.h"
#include "PlayerParameter.h"
#include <string>
#include <map>
//定数
//最大派生回数
auto constexpr  ATTACKCOUNT = 4;
auto constexpr  WEAPON_ALL = 3;
//クラス
class Player
{
public:
	//アニメーション
	enum class ANIMATION : int
	{
		//待機
		WAIT,
		//歩き
		WALK,
		//攻撃
		//攻撃していない
		NOATTACK,
		//一撃目
		FIRSTATTACK,
		//二撃目
		SECONDATTACK,
		//三撃目
		LASTATTACK,
		//ディバインスキル
		SKILL,
		//回避
		AVOID,
		//ダメージ
		DAMAGE,
		//体力0
		DIE,
	};
	//行動
	enum class ACTION : int
	{
		//待機
		WAIT,
		//歩き
		WALK,
		//攻撃
		ATTACK,
		//ディバインスキル
		SKILL,
		//回避
		AVOID,
		//ダメージ
		DAMAGE,
		//体力0
		DIE
	};
	//通常攻撃内の情報
	struct ATTACKDATA
	{
		//モーション識別番号
		Player::ANIMATION animation;
		//トータルフレーム
		float motionAllFrame;
		//ボタン入力猶予フレーム(開始)
		float pushButtonStartFrame;
		//ボタン入力猶予フレーム(終了)
		float pushButtonEndFrame;
		//モーション変更時間
		float motionChangeStartFrame;
		//攻撃判定開始時間
		float attackStartTime;
		//攻撃判定終了時間
		float attackEndTime;
		//判定カプセル頂点
		VECTOR capPoint[2];
		//攻撃判定範囲
		float radCap;
		//ボタン入力フラグ
		bool  pushFlug;
		//モーション変更フラグ
		bool  changeFlug;
		//派生可能か
		bool  isDerivasion;
		//ボイス識別コード
		std::string voiceCode;
		//se識別コード
		std::string seCode;
	};
	//武器種類
	enum class WEAPON : int
	{
		//剣
		SWORD,
		//斧
		AX,
		//ハンマー
		HAMMER
	};

	PP::Parameter* _pm;
	int _ATK;
	int _DEF;
	int _SPD;

public:
	Player();
	virtual ~Player();
	void Initialize(int handle,int weapon);
	//インスタンス
	static Player* _plInstance;
	void ActionProcess(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//Animation:アニメーション進行処理
	void A_Process();
	//Calcalate:計算系処理
	void C_Process();
	void Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//描画
	void Render();
public:
	//重力処理
	void Gravity();
	//移動速度
	int  SetSpeed();
	//武器装備
	void SetWeapon();
	//攻撃しているか
	bool Attack();
	//攻撃モーション変更処理
	void AttackMotionChange(int motionId);
	//スキル発動時ボイス
	void SkillVoice();
	//武器変更
	void WeaponChange(int weaponnum);
	//プレイヤー移動処理
	void PlayerMove(int key, VECTOR campos, VECTOR camtarget);
	//プレイヤー攻撃処理
	void PlayerAttack(int trg);
	//プレイヤースキル処理
	void PlayerSkill(int trg, int key, int rel, SkillSlot* slot,  VECTOR campos, VECTOR camtarget);
	//プレイヤー死亡処理
	void PlayerDie();
	//被ダメージ後処理
	void Invincible();
	//スキルの際のアニメーション
	ANIMATION SkillAnimation();
	//ダメージ
	void Damage(VECTOR pos, int subpoint);
	//デバッグ
	void PlDebug();
	//ゲッター
	static Player* GetInstance() { return _plInstance; }
	VECTOR GetMove()			 { return _vMove; }
	VECTOR GetPos()				 { return _vPos; }
	VECTOR GetDir()				 { return _vDir; }
	float  GetRadius()			 { return _rCap; }
	float  GetSeg()				 { return _lineSeg; }
	int    GetWeaponNum()		 { return _weaponNum; }
	int	   GetActionCount()		 { return _actionCnt; }
	int    GetActionNum()		 { return _actionNum; }
	int    GetCombo()			 { return  _comboCnt; }
	int	   GetLastCommand()		 { return _lastCommand; }
	bool   GetAvoidFlag()		 { return _avoidFlag; }
	int    GetHp()				 { return _hp; }
	bool   GetGameOver()		 { return _gameOverFlag; }
	bool   GetInvincible()		 { return _noDamage; }
	VECTOR GetWeaponPos(int i)	 { return _wPos[i]; }
	Divine* GetDivine()			 { return _skill; }
	//ATTACKDATAのゲッター
	ATTACKDATA GetAttackData()	 { return _attackData[_actionNum]; }
	//セッター
	void SetPos(VECTOR any)		{ _vPos = any; }
	void SetPos_y(float y)		{ _vPos.y = y; }
	void SetMove(VECTOR vec)	{ _vMove = vec; }
	void SetGravity(float gra)	{ _gravity = gra; }
	void SetAttackFlag(bool a)	{ _isAttack = a; }
	void SetCombo(int i)		{ _comboCnt = i; }
	void SetInvincible(bool i)  { _noDamage = i; }
	void SetStatusSkill(bool i) { _isSkill = i; }
	

private:
	//位置
	VECTOR _vPos;
	//角度、向き
	VECTOR _vDir;
	//移動量
	VECTOR _vMove;
	//カプセルの長さ
	float _lineSeg;
	//当たり判定用
	VECTOR _vCapsule[2];
	float _rCap;
	//武器判定位置
	VECTOR _weapon_vPos;
	//重力値
	float _gravity;
	//体力
	int _hp;
	//カウント
	int _actionCnt;
	//無敵カウント
	int _invincibleCnt;
	//モーション番号
	int _actionNum;
	//武器番号
	int _weaponNum;
	//コンボカウント
	int _comboCnt;
	//攻撃中かどうか
	bool _isAttack;
	bool _noDamage;
	bool _isSkill;
	bool _isDie;
	bool _gameOverFlag;
	//回避フラグ
	bool _avoidFlag;
	//最後に押したボタン
	int _lastCommand;
	//ステータス
	ANIMATION _animation;
	ANIMATION _oldAnimation;
	ACTION _status;
	WEAPON _weapon;
	//通常攻撃情報
	Player::ATTACKDATA _attackData[ATTACKCOUNT];
	//3Dモデル描画用
	//描画モデル
	int _model;
	//アタッチするアニメーションインデックス
	int _attachIndex;
	//アニメーションのトータル時間
	float _totalTime;
	//アニメーション時間
	float _playTime;
	//武器モデル
	int _wModel;
	VECTOR _wPos[2];
	//通常派生攻撃コンテナ
	std::map<int, Player::ATTACKDATA> _attackContainer;
	Divine* _skill;
};

