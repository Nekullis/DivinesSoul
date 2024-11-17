#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../ModeServer/ModeServer.h"
#include "../System/GamePad.h"
#include "../Reference/MyStruct.h"
#include "EffekseerForDXLib.h"

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 1920; }
	virtual int DispSizeH() { return 1080; }

	static	ApplicationBase* GetInstance() { return _lpInstance; }


protected:
	static	ApplicationBase* _lpInstance;

 ModeServer* _serverMode;

};

