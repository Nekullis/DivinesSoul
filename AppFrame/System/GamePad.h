#pragma once
#include "../Reference/MyStruct.h"
#include "DXLib.h"

class GamePad
{
public:
	// ç°âÒÇÕDirectInput
	GamePad();
	~GamePad();

	void InputAcquisition();


	int GetKey() { return _key; }
	int GetTrg() { return _trg; }
	int GetRel() { return _rel; }
	MyStruct::ANALOGSTICK GetSt() { return _st; }

protected:
	int _key;
	int _trg;
	int _rel;

	DINPUT_JOYSTATE _di;
	MyStruct::ANALOGSTICK _st;
};

