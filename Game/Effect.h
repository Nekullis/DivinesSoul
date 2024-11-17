//----------------------------------------------------------------------
// @filename Effect.h
// @author: Fukuma Kyohei
// @explanation
// �G�t�F�N�g�Ǘ��N���X
// �X�L���������̃G�t�F�N�g���Ǘ�����N���X
//----------------------------------------------------------------------
#pragma once
#include "dxlib.h"
#include "EffekseerForDXLib.h"
#include <string>
#include <map>
class Effect
{
public:
	Effect(std::string handle, float size);
	virtual ~Effect();
	static Effect* efInstance;
	bool Play();
	bool Stop();
	bool Process();
	bool Draw();
	bool Debug();
	//������Ăяo���K�v�̂Ȃ��֐��Ȃ̂ł��̊֐��̓}�l�[�W���[���邢�̓Q�[�����C���ɒu������
	bool Update();
	//�Q�b�^�[
	bool GetUseFlag() { return useFlag; }
	bool GetPlayFlag() { return playFlag; }
	static Effect* GetInstance() { return efInstance; }
	//�Z�b�^�[
	void SetPos(VECTOR v) { Pos=v; }
	void SetSize(float s) { Size = s; }
	void SetDir(VECTOR v)  { Dir = v; }
	void SetUseFlag(bool f) { useFlag = f; }
protected:
	//�G�t�F�N�g�����[�h����
	int effectResourceHandle;
	//�Đ��p�n���h��
	int playEffectHandle;
	//�ʒu
	VECTOR Pos;
	//�T�C�Y
	float Size;
	//����
	VECTOR Dir;
	//�Đ��\�t���O
	bool useFlag;
	//�Đ����̃t���O
	bool playFlag;
};

