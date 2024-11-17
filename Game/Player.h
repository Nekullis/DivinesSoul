#pragma once
#include "appframe.h"
#include "Divine.h"
#include "PlayerParameter.h"
#include <string>
#include <map>
//�萔
//�ő�h����
auto constexpr  ATTACKCOUNT = 4;
auto constexpr  WEAPON_ALL = 3;
//�N���X
class Player
{
public:
	//�A�j���[�V����
	enum class ANIMATION : int
	{
		//�ҋ@
		WAIT,
		//����
		WALK,
		//�U��
		//�U�����Ă��Ȃ�
		NOATTACK,
		//�ꌂ��
		FIRSTATTACK,
		//�񌂖�
		SECONDATTACK,
		//�O����
		LASTATTACK,
		//�f�B�o�C���X�L��
		SKILL,
		//���
		AVOID,
		//�_���[�W
		DAMAGE,
		//�̗�0
		DIE,
	};
	//�s��
	enum class ACTION : int
	{
		//�ҋ@
		WAIT,
		//����
		WALK,
		//�U��
		ATTACK,
		//�f�B�o�C���X�L��
		SKILL,
		//���
		AVOID,
		//�_���[�W
		DAMAGE,
		//�̗�0
		DIE
	};
	//�ʏ�U�����̏��
	struct ATTACKDATA
	{
		//���[�V�������ʔԍ�
		Player::ANIMATION animation;
		//�g�[�^���t���[��
		float motionAllFrame;
		//�{�^�����͗P�\�t���[��(�J�n)
		float pushButtonStartFrame;
		//�{�^�����͗P�\�t���[��(�I��)
		float pushButtonEndFrame;
		//���[�V�����ύX����
		float motionChangeStartFrame;
		//�U������J�n����
		float attackStartTime;
		//�U������I������
		float attackEndTime;
		//����J�v�Z�����_
		VECTOR capPoint[2];
		//�U������͈�
		float radCap;
		//�{�^�����̓t���O
		bool  pushFlug;
		//���[�V�����ύX�t���O
		bool  changeFlug;
		//�h���\��
		bool  isDerivasion;
		//�{�C�X���ʃR�[�h
		std::string voiceCode;
		//se���ʃR�[�h
		std::string seCode;
	};
	//������
	enum class WEAPON : int
	{
		//��
		SWORD,
		//��
		AX,
		//�n���}�[
		HAMMER
	};

	PP::Parameter* _pm;
	int _ATK;
	int _DEF;
	int _SPD;

public:
	Player();
	virtual ~Player();
	void Initialize(int handle,int weapon);
	//�C���X�^���X
	static Player* _plInstance;
	void ActionProcess(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//Animation:�A�j���[�V�����i�s����
	void A_Process();
	//Calcalate:�v�Z�n����
	void C_Process();
	void Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot);
	//�`��
	void Render();
public:
	//�d�͏���
	void Gravity();
	//�ړ����x
	int  SetSpeed();
	//���푕��
	void SetWeapon();
	//�U�����Ă��邩
	bool Attack();
	//�U�����[�V�����ύX����
	void AttackMotionChange(int motionId);
	//�X�L���������{�C�X
	void SkillVoice();
	//����ύX
	void WeaponChange(int weaponnum);
	//�v���C���[�ړ�����
	void PlayerMove(int key, VECTOR campos, VECTOR camtarget);
	//�v���C���[�U������
	void PlayerAttack(int trg);
	//�v���C���[�X�L������
	void PlayerSkill(int trg, int key, int rel, SkillSlot* slot,  VECTOR campos, VECTOR camtarget);
	//�v���C���[���S����
	void PlayerDie();
	//��_���[�W�㏈��
	void Invincible();
	//�X�L���̍ۂ̃A�j���[�V����
	ANIMATION SkillAnimation();
	//�_���[�W
	void Damage(VECTOR pos, int subpoint);
	//�f�o�b�O
	void PlDebug();
	//�Q�b�^�[
	static Player* GetInstance() { return _plInstance; }
	VECTOR GetMove()			 { return _vMove; }
	VECTOR GetPos()				 { return _vPos; }
	VECTOR GetDir()				 { return _vDir; }
	float  GetRadius()			 { return _rCap; }
	float  GetSeg()				 { return _lineSeg; }
	int    GetWeaponNum()		 { return _weaponNum; }
	int	   GetActionCount()		 { return _actionCnt; }
	int    GetActionNum()		 { return _actionNum; }
	int    GetCombo()			 { return  _comboCnt; }
	int	   GetLastCommand()		 { return _lastCommand; }
	bool   GetAvoidFlag()		 { return _avoidFlag; }
	int    GetHp()				 { return _hp; }
	bool   GetGameOver()		 { return _gameOverFlag; }
	bool   GetInvincible()		 { return _noDamage; }
	VECTOR GetWeaponPos(int i)	 { return _wPos[i]; }
	Divine* GetDivine()			 { return _skill; }
	//ATTACKDATA�̃Q�b�^�[
	ATTACKDATA GetAttackData()	 { return _attackData[_actionNum]; }
	//�Z�b�^�[
	void SetPos(VECTOR any)		{ _vPos = any; }
	void SetPos_y(float y)		{ _vPos.y = y; }
	void SetMove(VECTOR vec)	{ _vMove = vec; }
	void SetGravity(float gra)	{ _gravity = gra; }
	void SetAttackFlag(bool a)	{ _isAttack = a; }
	void SetCombo(int i)		{ _comboCnt = i; }
	void SetInvincible(bool i)  { _noDamage = i; }
	void SetStatusSkill(bool i) { _isSkill = i; }
	

private:
	//�ʒu
	VECTOR _vPos;
	//�p�x�A����
	VECTOR _vDir;
	//�ړ���
	VECTOR _vMove;
	//�J�v�Z���̒���
	float _lineSeg;
	//�����蔻��p
	VECTOR _vCapsule[2];
	float _rCap;
	//���픻��ʒu
	VECTOR _weapon_vPos;
	//�d�͒l
	float _gravity;
	//�̗�
	int _hp;
	//�J�E���g
	int _actionCnt;
	//���G�J�E���g
	int _invincibleCnt;
	//���[�V�����ԍ�
	int _actionNum;
	//����ԍ�
	int _weaponNum;
	//�R���{�J�E���g
	int _comboCnt;
	//�U�������ǂ���
	bool _isAttack;
	bool _noDamage;
	bool _isSkill;
	bool _isDie;
	bool _gameOverFlag;
	//����t���O
	bool _avoidFlag;
	//�Ō�ɉ������{�^��
	int _lastCommand;
	//�X�e�[�^�X
	ANIMATION _animation;
	ANIMATION _oldAnimation;
	ACTION _status;
	WEAPON _weapon;
	//�ʏ�U�����
	Player::ATTACKDATA _attackData[ATTACKCOUNT];
	//3D���f���`��p
	//�`�惂�f��
	int _model;
	//�A�^�b�`����A�j���[�V�����C���f�b�N�X
	int _attachIndex;
	//�A�j���[�V�����̃g�[�^������
	float _totalTime;
	//�A�j���[�V��������
	float _playTime;
	//���탂�f��
	int _wModel;
	VECTOR _wPos[2];
	//�ʏ�h���U���R���e�i
	std::map<int, Player::ATTACKDATA> _attackContainer;
	Divine* _skill;
};

