//----------------------------------------------------------------------
// @filename ModeSound.h
// @author: Fukuma Kyohei
// @explanation
// 音関係を再生、停止するモード
//----------------------------------------------------------------------
#include "appframe.h"
#include <string>
#include "SoundItem.h"
#include "ApplicationGlobal.h"
// モード
class ModeSound : public ModeBase
{
	typedef ModeBase base;

public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:



};



