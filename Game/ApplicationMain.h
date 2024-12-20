//----------------------------------------------------------------------
// @filename ApplicationGlobal.h
// @author: Fukuma Kyohei
// @explanation
// 派生アプリケーションクラス
// 初期化時のモード登録、その他初めに初期化したいクラスを処理するクラス
//----------------------------------------------------------------------
#include "appframe.h"
#include "ApplicationGlobal.h"
#include "ModeSound.h"

class ApplicationMain :    public ApplicationBase
{
	typedef ApplicationBase base;
	typedef ResourceServer RS;
public:
	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 1920; }
	virtual int DispSizeH() { return 1080; }

protected:
	std::thread* init;
};

