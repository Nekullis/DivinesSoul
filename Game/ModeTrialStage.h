#pragma once
#include "appframe.h"
#include "ObjectManager.h"

class ModeTrialStage : public ModeBase
{
	typedef ModeBase base;
public:
	ModeTrialStage();
	virtual ~ModeTrialStage();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual void Input();
	virtual bool Process();
	virtual bool Render();

protected:


};

