#pragma once
class ModeClear : public ModeBase
{
	typedef ModeBase base;
public:
	bool Initialize();
	bool Terminate();
	bool Process();
	bool Render();

protected:
	int _cg;
};

