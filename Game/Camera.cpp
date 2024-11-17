#include "Camera.h"
#include <cmath>

Camera::Camera() {
	// カメラの設定（わかりやすい位置に・汎用性がないので初期化関数分けましょう）
	_vPos = VGet(5096.7945f, 0.0f, -683.0f + 78.93);
	_vTarget = VGet(5096.7945f, 60, -933.7149f);
	_comparison = VGet(5096.7945f, 0.0f, -933.7149f);
	_clipNear = 2.f;
	_clipFar = 100000000000.0f;
	_transition = false;
	_holdValue = 0.0f;
	_vMode = PERS::TPP;
}

Camera::~Camera() {

}

bool Camera::FPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos) {
	// 注視点位置の現在の位置
	float sx = _vTarget.x - _vPos.x;
	float sz = _vTarget.z - _vPos.z;
	// カメラ位置の現在の位置
	float mx = _vPos.x - P_Pos.x;
	float mz = _vPos.z - P_Pos.z;
	// 動かす角度は注視点もカメラもキャラの位置から共通なので同じ角度を使用できるとよい（ターゲットとカメラが同じ方向ベクトル前提）
	float rad = atan2(sz, sx);
	// それぞれの長さ（キャラからカメラの位置、カメラから注視点の位置）をとる
	float length = sqrt(sz * sz + sx * sx);
	float mlength = sqrt(mz * mz + mx * mx);
	if (_st.rx > _st.analogMin) { rad -= 0.05f; }
	if (_st.rx < -_st.analogMin) { rad += 0.05f; }
	// 注視点の基準がカメラになっているため、カメラ位置は後で動かす(ジャンプ対応のためY座標のみ先に設定)
	_vPos.y = P_Pos.y + 90.0f;

	_vTarget.x = _vPos.x + cos(rad) * length;
	_vTarget.y = _vPos.y + _holdValue;
	_vTarget.z = _vPos.z + sin(rad) * length;
	// posがあとじゃなきゃダメ
	_vPos.x = P_Pos.x + cos(rad) * mlength;
	_vPos.z = P_Pos.z + sin(rad) * mlength;

	// カメラ位置は動かさずに注視点のみ動かしている
	if (_st.ry > _st.analogMin) { _holdValue -= 0.2f; }
	if (_st.ry < -_st.analogMin) { _holdValue += 0.2f; }

	_vTarget.y = Math::Clamp(_vPos.y - 8.0f, _vPos.y + 40.0f, _vTarget.y);
	return false;
}

bool Camera::TPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos) {

	// 角度変更
	// Y軸回転
	float sx = _vPos.x - _vTarget.x;
	float sz = _vPos.z - _vTarget.z;
	float rad = atan2(sz, sx);
	float length = sqrt(sz * sz + sx * sx);
	if (_st.rx > _st.analogMin) { rad -= 0.05f; }
	if (_st.rx < -_st.analogMin) { rad += 0.05f; }
	_vPos.x = _vTarget.x + cos(rad) * length;
	_vPos.y = P_Pos.y + 200.0f + _holdValue;
	_vPos.z = _vTarget.z + sin(rad) * length;

	_vTarget.y = P_Pos.y + 90.0f;
	// Y位置
	if (_st.ry > _st.analogMin) {
		_holdValue -= 10.0f;
		if (_holdValue <= -160.0f) {
			_holdValue = -160.0f;
		}
	}
	if (_st.ry < -_st.analogMin) {
		_holdValue += 10.0f;
		if (_holdValue >= 600.0f) {
			_holdValue = 600.0f;
		}
	}
	return false;
}

bool Camera::BEV_Process(int _key, MyStruct::ANALOGSTICK _st) {
	if (_key & PAD_INPUT_5) {
		if (_st.ry > _st.analogMin) { _vPos.y -= 5.f; }
		if (_st.ry < -_st.analogMin) { _vPos.y += 5.f; }
	}
	else {
		if (_st.rx > _st.analogMin) { _vTarget.x += 5.f; }
		if (_st.rx < -_st.analogMin) { _vTarget.x -= 5.f; }
		if (_st.ry > _st.analogMin) { _vTarget.z -= 5.f; }
		if (_st.ry < -_st.analogMin) { _vTarget.z += 5.f; }

		if (_st.rx > _st.analogMin) { _vPos.x += 5.f; }
		if (_st.rx < -_st.analogMin) { _vPos.x -= 5.f; }
		if (_st.ry > _st.analogMin) { _vPos.z -= 5.f; }
		if (_st.ry < -_st.analogMin) { _vPos.z += 5.f; }
	}
	_vPos.y = Math::Clamp(1000.0f, 3000.0f, _vPos.y);
	return false;
}

void Camera::Process(int _key, MyStruct::ANALOGSTICK _st, int _trg, VECTOR P_Move, VECTOR P_Pos, VECTOR P_Dir) {
	
	// カメラ遷移処理
	if (_transition) {
		switch (_vMode) {
		case PERS::FPP: {
			int DirX = P_Dir.x / abs(P_Dir.x);
			int DirZ = P_Dir.z / abs(P_Dir.z);
			int RatioX = P_Dir.x / sqrt(std::pow((P_Dir.x + P_Dir.z), 2.0f));
			int RatioZ = P_Dir.z / sqrt(std::pow((P_Dir.x + P_Dir.z), 2.0f));
			// 不完全なので要見直し(ひとまずｚ方向の＋方向を向くようにする)
			_vPos = VGet(P_Pos.x, P_Pos.y + 90.0f, P_Pos.z + 10.0f);
			_vTarget = VGet(P_Pos.x, P_Pos.y + 90.0f, P_Pos.z + 30);
			_transition = false;
			break;
		}
		case PERS::TPP: {
			_vPos = VGet(P_Pos.x, P_Pos.y + 90.f, P_Pos.z - 300.f);
			_vTarget = VGet(P_Pos.x, P_Pos.y + 60.0f, P_Pos.z);
			_transition = false;
			break;
		}
		case PERS::BEV: {
			_vPos = VGet(0, 2000.f, -100.0f);
			_vTarget = VGet(0, 0, 10.0f);
			_transition = false;
			break;
		}
		}
	}
	// カメラ遷移後
	else if (!_transition) {
		switch (_vMode) {
		case PERS::FPP: {
			this->FPP_Process(_key, _st, P_Pos);
			break;
		}
		case PERS::TPP: {
			this->TPP_Process(_key, _st, P_Pos);
			break;
		}
		case PERS::BEV: {
			this->BEV_Process(_key, _st);
			break;
		}
		}
	}
}

void Camera::CamCollection(VECTOR vPos) {
	if (_vMode != PERSPECTIVE::BEV) {
		VECTOR dif = VSub(_vPos, _vTarget);
		_vTarget = vPos;
		_vPos = VAdd(_vTarget, dif);
		
	}
}

void Camera::Render() {
	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarget);
	SetCameraNearFar(_clipNear, _clipFar);

}