#include "ApplicationGlobal.h"

ApplicationGlobal		gGlobal;

ApplicationGlobal::ApplicationGlobal() {

}

ApplicationGlobal::~ApplicationGlobal() {
	delete _PM;
	_RS->ExcludeObject_map("res/Json/ObjectList.json");
	delete _gPad;
	delete _RS;
}


bool ApplicationGlobal::Init() {
	_isLoad = false;
	_RS = new ResourceServer();
	_PM = new PlayerManager();
	_gPad = new GamePad();
	stageNum = stage::none;

	_RS->JsonToJMap("res/Json/ObjectList.json");
	_RS->JMapToArray();
	_isLoad = true;
	return true;
}


void ApplicationGlobal::PadInput() {
	_gPad->InputAcquisition();
	_gKey = _gPad->GetKey();
	_gTrg = _gPad->GetTrg();
	_gRel = _gPad->GetRel();
	_gSti = _gPad->GetSt();
}