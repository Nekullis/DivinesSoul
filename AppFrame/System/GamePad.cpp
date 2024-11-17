#include "GamePad.h"

GamePad::GamePad() {
 _key = 0;
 _trg = 0;
 _rel = 0;
 _st.analogMin = 0.3f;
}

GamePad::~GamePad() {

}

void GamePad::InputAcquisition() {
	int keyold = _key;
	_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_trg = (_key ^ keyold) & _key;
	_rel = (_key ^ keyold) & ~_key;

	GetJoypadDirectInputState(DX_INPUT_PAD1, &_di);
	//　それぞれの入力から取れる値が1000なので、とった値を1/1000にして使いやすくしている
	_st = { (float)_di.X / 1000.f, (float)_di.Y / 1000.f,  (float)_di.Z / 1000.f,  (float)_di.Rz / 1000.f, _st.analogMin };

}