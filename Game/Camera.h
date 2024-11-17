#pragma once
#include "DXLib.h"
#include "appframe.h"

class Camera
{public:
	Camera();
	~Camera();

	typedef enum class PERSPECTIVE {// last P = Perspective
		FPP, TPP, BEV  // BEV = BirdsEyeView = ���Վ��_
	} PERS;

	bool FPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos);
	bool TPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos);
	bool BEV_Process(int _key, MyStruct::ANALOGSTICK _st);
	void Process(int _key, MyStruct::ANALOGSTICK _st, int _trg, VECTOR P_Move, VECTOR P_Pos, VECTOR P_Dir);
	void CamCollection(VECTOR vPos);
	void Render();



	// �Q�b�^�[
	VECTOR GetVPos() { return _vPos; }
	VECTOR GetVTarget() { return _vTarget; }
	float GetClipN() { return _clipNear; }
	float GetClipF() { return _clipFar; }
	PERSPECTIVE GetvMode(){return _vMode;}

	// �Z�b�^�[
	void SetVPos(VECTOR pos) { _vPos = pos; }
	void SetVTarget(VECTOR target) { _vPos = target; }
	void GetClipN(float cNear) {_clipNear = cNear; }
	void GetClipF(float cFar) {_clipFar = cFar; }

protected:

	PERSPECTIVE _vMode;

	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	VECTOR _comparison;              // ��r�p�i�v���C���[���ǂɓ������Ă��邩�́j
	float	_clipNear, _clipFar;	// �N���b�v
	bool _transition;
	float _holdValue;


};

