#pragma once
#include "DXLib.h"
#include "appframe.h"

class Camera
{public:
	Camera();
	~Camera();

	typedef enum class PERSPECTIVE {// last P = Perspective
		FPP, TPP, BEV  // BEV = BirdsEyeView = 俯瞰視点
	} PERS;

	bool FPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos);
	bool TPP_Process(int _key, MyStruct::ANALOGSTICK _st, VECTOR P_Pos);
	bool BEV_Process(int _key, MyStruct::ANALOGSTICK _st);
	void Process(int _key, MyStruct::ANALOGSTICK _st, int _trg, VECTOR P_Move, VECTOR P_Pos, VECTOR P_Dir);
	void CamCollection(VECTOR vPos);
	void Render();



	// ゲッター
	VECTOR GetVPos() { return _vPos; }
	VECTOR GetVTarget() { return _vTarget; }
	float GetClipN() { return _clipNear; }
	float GetClipF() { return _clipFar; }
	PERSPECTIVE GetvMode(){return _vMode;}

	// セッター
	void SetVPos(VECTOR pos) { _vPos = pos; }
	void SetVTarget(VECTOR target) { _vPos = target; }
	void GetClipN(float cNear) {_clipNear = cNear; }
	void GetClipF(float cFar) {_clipFar = cFar; }

protected:

	PERSPECTIVE _vMode;

	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	VECTOR _comparison;              // 比較用（プレイヤーが壁に当たっているかの）
	float	_clipNear, _clipFar;	// クリップ
	bool _transition;
	float _holdValue;


};

