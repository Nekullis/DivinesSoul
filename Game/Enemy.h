#pragma once
#include"dxlib.h"
#include"MathCollision.h"
#include"string"
#include"ApplicationGlobal.h"
class Enemy
{
public:
	enum ENEMYTYPE
	{
		NOCHARA,
		OSERO,
		CRAB,
		ROMANOFF
	};
	enum STATUS
	{
		//未発見
		NODISCOVERY,
		//待機
		WAIT,
		//休憩
		REST,
		//攻撃
		ATTACK,
		//突撃
		ASSAULT,
		//ダメージ
		DAMAGE,
		//走行
		RUN,
		//警戒
		CAUTION,
		//死亡
		DIE,
	};
	struct ACTIONDATA
	{
		//ステータス
		STATUS status;
		//モーションのトータルフレーム
		float motionTotalFrame;
		//探索範囲
		float _searchArea;
	};
public:
	Enemy(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~Enemy();
	virtual bool Process(VECTOR pl_pos);
	virtual bool Render();
	virtual bool Debug();
	virtual bool Delete();
	virtual bool Damage(VECTOR pl_pos, int subpoint,int nextframe);
	virtual bool Suction(VECTOR pl_pos,  int nextframe);
	//ステータス変更
	virtual void ChangeStatus(STATUS en_status);
	//ゲッター
	VECTOR	GetPos()			{ return _vPos; }
	VECTOR	GetDir()			{ return _vDir; }
	float	GetRadius()			{ return _radius; }
	float	GetSeg()			{ return _lineSeg; }
	bool	GetAttackFlag()		{ return _isAttack; }
	VECTOR	GetWeaponPos(int i)	{ return _wPos[i]; }
	float	GetWeaponSize()		{ return _wSize; }
	bool	GetInvincible()		{ return _noDamage; }
	int		GetHp()				{ return _hp; }
	int		GetATK()			{ return _ap; }
	bool	GetDeleteFlag()		{ return _deleteFlag; }
	ENEMYTYPE GetEnemyType()	{ return _type; }
	//セッター
	void  SetPos(VECTOR i)		{ _vPos = VAdd(_vPos, i); }
	void  SetDir(VECTOR i)		{ _vDir = i; }
	void  SetAttackFlag(bool i)	{ _isAttack = i; }
	void  SetStatus(STATUS status) { ChangeStatus(status); }
protected:
	ENEMYTYPE _type;
	//位置
	VECTOR _vPos;
	//向き
	VECTOR _vDir;
	//移動量
	VECTOR _vMove;
	//カプセル用
	VECTOR _vCapsule[2];
	//半径
	float _radius;
	//線分の長さ
	float _lineSeg;
	//体力
	int _hp;
	//攻撃力
	int _ap;
	//カウント
	int _actionCnt;
	//時間
	int _timeCnt;
	//無敵時間
	int _invincibleCnt;
	//次判定までのカウント
	int nextFrame;
	//攻撃中か
	bool _isAttack;
	//ダメージを受けた
	bool _damage;
	//無敵中か
	bool _noDamage;
	//体力が0かどうか
	bool _die;
	//消去するフラグ
	bool _deleteFlag;
	//モデル
	int _model;
	std::string mName;
	//アタッチするアニメーションインデックス
	int _attachIndex;
	//アニメーションのトータル時間
	float _totalTime;
	//アニメーション時間
	float _playTime;
	//武器モデル
	int _wModel;
	//武器位置
	VECTOR _wPos[2];
	//武器サイズ
	float _wSize;
};

