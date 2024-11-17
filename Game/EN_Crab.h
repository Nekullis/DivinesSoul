#pragma once
#include "Enemy.h"
class EN_Crab : public Enemy
{
	using base = Enemy;
public:
	EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir);
	virtual ~EN_Crab();
	bool C_Process(VECTOR pl_pos);
	bool Process(VECTOR pl_pos) override;
	bool Render() override;
	bool Debug() override;
	bool Delete() override;
public:
	//�����蔻��N���X�Ɏg���_���[�W�֐�
	bool Damage(VECTOR pl_pos,int subpoint, int nextframe)override;
	bool Suction(VECTOR pl_pos, int nextframe)override;
	//�X�e�[�^�X�ύX
	void ChangeStatus(STATUS en_status)override;

protected:
	//crab�̃f�[�^
	ACTIONDATA _data;
	//�s���̃f�[�^
	STATUS _status;
};
