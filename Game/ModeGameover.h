#pragma once
#include"ModeTitle.h"
//#include "appframe.h"
class ModeGameover : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _cg[2];
	int _selection;

};

