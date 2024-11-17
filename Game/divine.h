//----------------------------------------------------------------------
// @filename Divine.h
// @author: Fukuma Kyohei
// @explanation
// スキル(ディバイン)クラス
// スキル全般の処理を行うクラス
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "SkillSlot.h"
#include "Effect.h"
#include<vector>
//定数
//ディバインスキル数
constexpr auto MAX_SKILL_NUM = 8;
class Divine
{
public:
	//スキル名
	enum class SKILLNAME : int
	{
		//ブレス
		BREATH,
		//サークル
		CIRCLE,
		//レーザー
		LASER,
		//スラッシュ
		SLASH,
		//エクスプロージョン
		EXPLOSION,
		//ダッシュ
		DASH,
		//バキューム
		VACUUM,
		//ソニックウェーブ
		SONIC
	};
	//スキルの情報
	struct SKILL
	{
		//スキル名
		SKILLNAME skillName;
		//発動位置
		VECTOR vPos;
		//当たり判定用サイズ
		float size;
		//再発動までのフレーム
		float reInvocationFrame;
		//再発動までのカウント
		int divineCnt;
		//判定用カウント
		int colCnt;
		//攻撃力
		int atkPoint;
		//発動フラグ
		bool invocationFlag;
		//発動中か
		bool isPlaying;
		//総合発動時間
		float invocationFrame;
		//判定開始時間
		float startColFrame;
		//判定終了時間
		float endColFrame;
		//使うエフェクト
		Effect* effect;
		//SE識別コード
		std::string seCode;
		std::string voiceCode;
	};
	
public:
	Divine();
	virtual ~Divine();
	static Divine* _divineInstance;
	bool Process(VECTOR pos,float roty);
	bool Render();
	bool Debug();
	bool Calcalate(VECTOR pos, float roty);
	void Invocation(kindDivine skillname);
	void Reset();
	//ゲッター
	static Divine* GetInstance() { return _divineInstance; }
	bool GetHitFlag()     { return _hitFlag; }
	SKILL GetSkill(int i) { return _skill[i]; }
	VECTOR GetSkillPos(int i) { return _skill[i].vPos; }
	bool GetIsDash() { return _isDash; }
	//セッター
	void SetHitFlag(bool flag)	{ _hitFlag = flag; }
	void SetIsDash(bool i) { _isDash = i; }
protected:
	//構造体
	SKILL _skill[MAX_SKILL_NUM];
	//位置
	VECTOR _vPos;
	//当たったフラグ
	bool _hitFlag;
	bool _isDash;
	
	
	


};

