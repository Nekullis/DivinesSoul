//----------------------------------------------------------------------
// @filename Divine.h
// @author: Fukuma Kyohei
// @explanation
// �X�L��(�f�B�o�C��)�N���X
// �X�L���S�ʂ̏������s���N���X
//----------------------------------------------------------------------
#pragma once
#include "appframe.h"
#include "SkillSlot.h"
#include "Effect.h"
#include<vector>
//�萔
//�f�B�o�C���X�L����
constexpr auto MAX_SKILL_NUM = 8;
class Divine
{
public:
	//�X�L����
	enum class SKILLNAME : int
	{
		//�u���X
		BREATH,
		//�T�[�N��
		CIRCLE,
		//���[�U�[
		LASER,
		//�X���b�V��
		SLASH,
		//�G�N�X�v���[�W����
		EXPLOSION,
		//�_�b�V��
		DASH,
		//�o�L���[��
		VACUUM,
		//�\�j�b�N�E�F�[�u
		SONIC
	};
	//�X�L���̏��
	struct SKILL
	{
		//�X�L����
		SKILLNAME skillName;
		//�����ʒu
		VECTOR vPos;
		//�����蔻��p�T�C�Y
		float size;
		//�Ĕ����܂ł̃t���[��
		float reInvocationFrame;
		//�Ĕ����܂ł̃J�E���g
		int divineCnt;
		//����p�J�E���g
		int colCnt;
		//�U����
		int atkPoint;
		//�����t���O
		bool invocationFlag;
		//��������
		bool isPlaying;
		//������������
		float invocationFrame;
		//����J�n����
		float startColFrame;
		//����I������
		float endColFrame;
		//�g���G�t�F�N�g
		Effect* effect;
		//SE���ʃR�[�h
		std::string seCode;
		std::string voiceCode;
	};
	
public:
	Divine();
	virtual ~Divine();
	static Divine* _divineInstance;
	bool Process(VECTOR pos,float roty);
	bool Render();
	bool Debug();
	bool Calcalate(VECTOR pos, float roty);
	void Invocation(kindDivine skillname);
	void Reset();
	//�Q�b�^�[
	static Divine* GetInstance() { return _divineInstance; }
	bool GetHitFlag()     { return _hitFlag; }
	SKILL GetSkill(int i) { return _skill[i]; }
	VECTOR GetSkillPos(int i) { return _skill[i].vPos; }
	bool GetIsDash() { return _isDash; }
	//�Z�b�^�[
	void SetHitFlag(bool flag)	{ _hitFlag = flag; }
	void SetIsDash(bool i) { _isDash = i; }
protected:
	//�\����
	SKILL _skill[MAX_SKILL_NUM];
	//�ʒu
	VECTOR _vPos;
	//���������t���O
	bool _hitFlag;
	bool _isDash;
	
	
	


};

