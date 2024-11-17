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
	// 3D���f���`��p
	int _mapEntity;
	int _Wall;
	int _distantView;
	
	// 3D���f���n���h��
	std::map<std::string, int> _mapModelHandle;		// <���O, ���f���n���h��>

	// 3D�u���b�N���
	struct BLOCKPOS {
		std::string		name;
		double		x, y, z;	// ���W
		double		rx, ry, rz;	// ��]
		double		sx, sy, sz;	// �g��
		int			modelHandle;	// ���f���n���h��
		int			drawFrame;		// �`��t���[��
	};
	std::vector<BLOCKPOS>	_vBlockPos;
	//�A�j���[�V�����p�B���Ԃ�����ΕύX
	
	std::vector<ANIMATIONMODEL> _vAnim;
public:
//	void SetMapEntity(stage choice) { Map = choice; }


};

