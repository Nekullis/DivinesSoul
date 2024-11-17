#pragma once
#include"dxlib.h"
#include"MathCollision.h"
#include"string"
#include"ApplicationGlobal.h"
class Enemy
{
public:
	enum ENEMYTYPE
	{
		NOCHARA,
		OSERO,
		CRAB,
		ROMANOFF
	};
	enum STATUS
	{
		//������
		NODISCOVERY,
		//�ҋ@
		WAIT,
		//�x�e
		REST,
		//�U��
		ATTACK,
		//�ˌ�
		ASSAULT,
		//�_���[�W
		DAMAGE,
		//���s
		RUN,
		//�x��
		CAUTION,
		//���S
		DIE,
	};
	struct ACTIONDATA
	{
		//�X�e�[�^�X
		STATUS status;
		//���[�V�����̃g�[�^���t���[��
		float motionTotalFrame;
		//�T���͈�
		float _searchArea;
	};
public:
	Enemy(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~Enemy();
	virtual bool Process(VECTOR pl_pos);
	virtual bool Render();
	virtual bool Debug();
	virtual bool Delete();
	virtual bool Damage(VECTOR pl_pos, int subpoint,int nextframe);
	virtual bool Suction(VECTOR pl_pos,  int nextframe);
	//�X�e�[�^�X�ύX
	virtual void ChangeStatus(STATUS en_status);
	//�Q�b�^�[
	VECTOR	GetPos()			{ return _vPos; }
	VECTOR	GetDir()			{ return _vDir; }
	float	GetRadius()			{ return _radius; }
	float	GetSeg()			{ return _lineSeg; }
	bool	GetAttackFlag()		{ return _isAttack; }
	VECTOR	GetWeaponPos(int i)	{ return _wPos[i]; }
	float	GetWeaponSize()		{ return _wSize; }
	bool	GetInvincible()		{ return _noDamage; }
	int		GetHp()				{ return _hp; }
	int		GetATK()			{ return _ap; }
	bool	GetDeleteFlag()		{ return _deleteFlag; }
	ENEMYTYPE GetEnemyType()	{ return _type; }
	//�Z�b�^�[
	void  SetPos(VECTOR i)		{ _vPos = VAdd(_vPos, i); }
	void  SetDir(VECTOR i)		{ _vDir = i; }
	void  SetAttackFlag(bool i)	{ _isAttack = i; }
	void  SetStatus(STATUS status) { ChangeStatus(status); }
protected:
	ENEMYTYPE _type;
	//�ʒu
	VECTOR _vPos;
	//����
	VECTOR _vDir;
	//�ړ���
	VECTOR _vMove;
	//�J�v�Z���p
	VECTOR _vCapsule[2];
	//���a
	float _radius;
	//�����̒���
	float _lineSeg;
	//�̗�
	int _hp;
	//�U����
	int _ap;
	//�J�E���g
	int _actionCnt;
	//����
	int _timeCnt;
	//���G����
	int _invincibleCnt;
	//������܂ł̃J�E���g
	int nextFrame;
	//�U������
	bool _isAttack;
	//�_���[�W���󂯂�
	bool _damage;
	//���G����
	bool _noDamage;
	//�̗͂�0���ǂ���
	bool _die;
	//��������t���O
	bool _deleteFlag;
	//���f��
	int _model;
	std::string mName;
	//�A�^�b�`����A�j���[�V�����C���f�b�N�X
	int _attachIndex;
	//�A�j���[�V�����̃g�[�^������
	float _totalTime;
	//�A�j���[�V��������
	float _playTime;
	//���탂�f��
	int _wModel;
	//����ʒu
	VECTOR _wPos[2];
	//����T�C�Y
	float _wSize;
};

