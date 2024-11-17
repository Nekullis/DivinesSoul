#pragma once
#include "appframe.h"
class ModeEnding : public ModeBase
{
	using base = ModeBase;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _handleMovie;
};

