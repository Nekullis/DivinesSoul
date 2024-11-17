#pragma once
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "JsonUtility.h"
#include <vector>

class MapEntity
{
	typedef ApplicationGlobal::stage stage;
public:
	MapEntity();
	virtual ~MapEntity();

	void Initialize(stage global);
	void Process();
	void Render();
	bool isPlayAnimation(std::string s);
	int GetEntity() { return _mapEntity; }
	int GetWall() { return _Wall; }
	struct ANIMATIONMODEL
	{
		int model;
		float factor;
		float playTime;
		int attachIndex;
		int totalTime;
	};
protected:
	VECTOR _vPos;
	VECTOR _vDir;
	VECTOR _vMove;
//	stage Map;
	// 3Dモデル描画用
	int _mapEntity;
	int _Wall;
	int _distantView;
	
	// 3Dモデルハンドル
	std::map<std::string, int> _mapModelHandle;		// <名前, モデルハンドル>

	// 3Dブロック情報
	struct BLOCKPOS {
		std::string		name;
		double		x, y, z;	// 座標
		double		rx, ry, rz;	// 回転
		double		sx, sy, sz;	// 拡大
		int			modelHandle;	// モデルハンドル
		int			drawFrame;		// 描画フレーム
	};
	std::vector<BLOCKPOS>	_vBlockPos;
	//アニメーション用。時間があれば変更
	
	std::vector<ANIMATIONMODEL> _vAnim;
public:
//	void SetMapEntity(stage choice) { Map = choice; }


};

