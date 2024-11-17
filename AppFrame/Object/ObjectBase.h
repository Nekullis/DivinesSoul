#pragma once
#include <string>
#include "DxLib.h"

class ObjectBase{
public:
	ObjectBase();
	virtual ~ObjectBase();
	
	virtual void Initialize();
	virtual void Process();
	virtual void Render();

protected:

	VECTOR _vPos;
	VECTOR _vDir;
	VECTOR _vMove;

	int _handle;
	int _attach_index;
	float _total_time;
	float _play_time;

};

