#include "Camera.h"
#include <cmath>

Camera::Camera() {
	// �J�����̐ݒ�i�킩��₷���ʒu�ɁE�ėp�����Ȃ��̂ŏ������֐������܂��傤�j
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
	// �����_�ʒu�̌��݂̈ʒu
	float sx = _vTarget.x - _vPos.x;
	float sz = _vTarget.z - _vPos.z;
	// �J�����ʒu�̌��݂̈ʒu
	float mx = _vPos.x - P_Pos.x;
	float mz = _vPos.z - P_Pos.z;
	// �������p�x�͒����_���J�������L�����̈ʒu���狤�ʂȂ̂œ����p�x���g�p�ł���Ƃ悢�i�^�[�Q�b�g�ƃJ���������������x�N�g���O��j
	float rad = atan2(sz, sx);
	// ���ꂼ��̒����i�L��������J�����̈ʒu�A�J�������璍���_�̈ʒu�j���Ƃ�
	float length = sqrt(sz * sz + sx * sx);
	float mlength = sqrt(mz * mz + mx * mx);
	if (_st.rx > _st.analogMin) { rad -= 0.05f; }
	if (_st.rx < -_st.analogMin) { rad += 0.05f; }
	// �����_�̊���J�����ɂȂ��Ă��邽�߁A�J�����ʒu�͌�œ�����(�W�����v�Ή��̂���Y���W�̂ݐ�ɐݒ�)
	_vPos.y = P_Pos.y + 90.0f;

	_vTarget.x = _vPos.x + cos(rad) * length;
	_vTarget.y = _vPos.y + _holdValue;
	_vTarget.z = _vPos.z + sin(rad) * length;
	// pos�����Ƃ���Ȃ���_��
	_vPos.x = P_Pos.x + cos(rad) * mlength;
	_vPos.z = P_Pos.z + sin(rad) * mlength;

	// �J�����ʒu�͓��������ɒ����_�̂ݓ������Ă���
	if (_st.ry > _st.analogMin) { _holdValue -= 0.2f; }
	if (_st.ry < -_st.analogMin) { _holdValue += 0.2f; }

	_vTarget.y = Math::Clamp(_vPos.y - 8.0f, _vPos.y + 40.0f, _vTarget.y);
	return false;
}

bool Camera::TPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos) {

	// �p�x�ύX
	// Y����]
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
	// Y�ʒu
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
	
	// �J�����J�ڏ���
	if (_transition) {
		switch (_vMode) {
		case PERS::FPP: {
			int DirX = P_Dir.x / abs(P_Dir.x);
			int DirZ = P_Dir.z / abs(P_Dir.z);
			int RatioX = P_Dir.x / sqrt(std::pow((P_Dir.x + P_Dir.z), 2.0f));
			int RatioZ = P_Dir.z / sqrt(std::pow((P_Dir.x + P_Dir.z), 2.0f));
			// �s���S�Ȃ̂ŗv������(�ЂƂ܂��������́{�����������悤�ɂ���)
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
	// �J�����J�ڌ�
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
	// �J�����ݒ�X�V
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarget);
	SetCameraNearFar(_clipNear, _clipFar);

}