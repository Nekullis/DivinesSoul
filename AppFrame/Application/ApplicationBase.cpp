#include "ApplicationBase.h"

ApplicationBase* ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DXライブラリの初期化
	if (AppWindowed()) {
		ChangeWindowMode(true);							// ウィンドウモードに指定する
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);
	// 距離が近いところでチラツキが発生する（Z深度が足りない）対策
	SetZBufferBitDepth(32);
	SetOutApplicationLogValidFlag(FALSE);
	SetMouseDispFlag(FALSE);
	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return false;
	}
	if (Effekseer_Init(20000) == -1)
	{
		DxLib_End();
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DXライブラリ開放
	Effkseer_End();
	DxLib_End();
	
	return true;
}


bool ApplicationBase::Input() {
	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
