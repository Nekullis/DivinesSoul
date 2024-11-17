//----------------------------------------------------------------------
// @filename ModeGame.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// ステージを管理するクラス
//----------------------------------------------------------------------
#pragma once
#include "actioncollision.h"
#include "appframe.h"
#include "Camera.h"
#include "Effect.h"
#include "Enemy.h"
#include "GameUI.h"
#include "MapEntity.h"
#include "ObjectManager.h"
#include "SkillSlot.h"
#include "GameEvent.h"
#include "GameSystem.h"
#include <string>

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
	typedef ApplicationGlobal::stage stage;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void DIRender();

protected:

	Camera* _cam;
	//ObjectManager* _oManager;
	GameEvent* _event;
	GameSystem* _system;
	MapEntity* _gMapEntity;
	EN_Osero* _enemy;
	EN_Crab* _crab;
	ActionCollision* _aCol;
	Effect* _effect;
	SkillSlot* _slot;
	GameUI* _gameUI;
	stage ModeG;

	int  colError;
	float testDeg;

	// 3Dモデル描画用

	///　オブジェクトのクラスに移動
	int _handle;
	int _wModel[2];
	int _FloorHandle;
	int _frameMapCollision;
	int _frameMapCollision_W;
	int _frameMapCollision_T;
	int _wall;
	int _wall2;
	VECTOR _wPos;
	VECTOR _pusherPos;
	VECTOR _wPos2;
	float _ampCnt;
	float _pushCnt;
	bool _ispush;
	/// 



};

