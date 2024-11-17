#include "actioncollision.h"
ActionCollision::ActionCollision()
{
	_disDivinetoCap = 0;
	_stageModel= gGlobal.mGetModel()["ForCollison"]._handle;
}
ActionCollision::~ActionCollision()
{
}
bool ActionCollision::MapColPlayer(Player* pl)
{
	float _radius = pl->GetRadius();
	VECTOR _capsule[2] =
	{
		pl->GetPos(),
		VAdd(pl->GetPos(),VGet(0,pl->GetSeg(),0)),
	};
	_capsule[0] = VAdd(_capsule[0], pl->GetMove());
	_capsule[1] = VAdd(_capsule[0], pl->GetMove());
	for (int i = 0; i < 17; i++)
	{
		MV1_COLL_RESULT_POLY_DIM _hit_poly_chara;
		_hit_poly_chara = MV1CollCheck_Capsule(_stageModel, i, _capsule[0], _capsule[1], _radius);
		if (_hit_poly_chara.HitNum >= 1)
		{
			const int hit_num = _hit_poly_chara.HitNum;
			int j = 0;
			// ���������|���S���̐������J��Ԃ�
			for (j = 0; j < hit_num; j++)
			{
				//�����ƎO�p�`�̍ŋߓ_����炤
				tagSEGMENT_TRIANGLE_RESULT _result;
				Segment_Triangle_Analyse(&_capsule[0], &_capsule[1], &_hit_poly_chara.Dim[j].Position[0], &_hit_poly_chara.Dim[j].Position[1], &_hit_poly_chara.Dim[j].Position[2], &_result);
				//�x�N�g���̈����Z�ŉ����o���p�x�����
				VECTOR sub_dir = VSub(_result.Seg_MinDist_Pos, _result.Tri_MinDist_Pos);
				//�����ƎO�p�`�̍ŋߓ_��
				float near_point = Segment_Triangle_MinLength(_capsule[0], _capsule[1], _hit_poly_chara.Dim[j].Position[0], _hit_poly_chara.Dim[j].Position[1], _hit_poly_chara.Dim[j].Position[2]);
				//�v���C���[�̉�����������
				float sub_len = _radius - near_point;
				//�@�������ɏ�ŋ��߂��������|����
				VECTOR push_vec = VScale(VNorm(sub_dir), sub_len + 1.0f);
				if (VSize(pl->GetPos()) != VSize(VAdd(pl->GetPos(), push_vec)))
				{

				}
				if (i != 6)
				{
					pl->SetPos(VAdd(pl->GetPos(), VGet(push_vec.x, 0, push_vec.z)));
				}
			}
		}
		MV1CollResultPolyDimTerminate(_hit_poly_chara);
	}
	return true;
}

bool ActionCollision::MapColEnemy(EnemyManager* _enemy)
{
	std::list<Enemy*> _list = _enemy->GetEnemyList();
	for (auto&& enemy : _list)
	{
		float _radius = enemy->GetRadius();
		//�G�l�~�[�̔���J�v�Z��
		VECTOR _vcap_enemy[2] =
		{	//[0]���������A[1]����������
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetSeg(), 0.0f))},
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetRadius(), 0.0f))},
		};
		for (int i = 0; i < 17; i++)
		{
			MV1_COLL_RESULT_POLY_DIM _hit_poly_chara;
			_hit_poly_chara = MV1CollCheck_Capsule(_stageModel, i, _vcap_enemy[0], _vcap_enemy[1], _radius);
			if (_hit_poly_chara.HitNum >= 1)
			{
				const int hit_num = _hit_poly_chara.HitNum;
				int j = 0;
				// ���������|���S���̐������J��Ԃ�
				for (j = 0; j < hit_num; j++)
				{
					//�����ƎO�p�`�̍ŋߓ_����炤
					tagSEGMENT_TRIANGLE_RESULT _result;
					Segment_Triangle_Analyse(&_vcap_enemy[0], &_vcap_enemy[1], &_hit_poly_chara.Dim[j].Position[0], &_hit_poly_chara.Dim[j].Position[1], &_hit_poly_chara.Dim[j].Position[2], &_result);
					//�x�N�g���̈����Z�ŉ����o���p�x�����
					VECTOR sub_dir = VSub(_result.Seg_MinDist_Pos, _result.Tri_MinDist_Pos);
					//�����ƎO�p�`�̍ŋߓ_��
					float near_point = Segment_Triangle_MinLength(_vcap_enemy[0], _vcap_enemy[1], _hit_poly_chara.Dim[j].Position[0], _hit_poly_chara.Dim[j].Position[1], _hit_poly_chara.Dim[j].Position[2]);
					//�v���C���[�̉�����������
					float sub_len = _radius - near_point;
					//�@�������ɏ�ŋ��߂��������|����
					VECTOR push_vec = VScale(VNorm(sub_dir), sub_len);
					if (VSize(enemy->GetPos()) != VSize(VAdd(enemy->GetPos(), push_vec)))
					{

					}
					if (i != 6)
					{
						enemy->SetPos(VAdd(enemy->GetPos(), VGet(push_vec.x, 0, push_vec.z)));
					}
				}
			}
			MV1CollResultPolyDimTerminate(_hit_poly_chara);
		}
	}
	
	return true;
}

bool ActionCollision::MapColProcess(Player* pl, EnemyManager* _enemy)
{
	
	MapColPlayer(pl);
	//MapColEnemy(_enemy);
	return true;
}

bool ActionCollision::PtoEColProcess(Player* pl, EnemyManager* _enemy)
{
	//�ŒZ����������
	float _distCaptoCap = 0;
	float _distCaptoWeapon = 0;
	int frame = 0;
	std::list<Enemy*> _list = _enemy->GetEnemyList();
	Player::ATTACKDATA _data = pl->GetAttackData();
	//�e�J�v�Z���̍ŒZ���̒[�_�Ɛ��������̊����͓����Ă��Ȃ��Ă����Ȃ��̂�0�ɂ���
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//�v���C���[�̔���J�v�Z��
	VECTOR _vcap_player[2] =
	{	//[0]���������A[1]����������
		{ VAdd(pl->GetPos(), VGet(0.0f, pl->GetSeg() , 0.0f))},
		{ VAdd(pl->GetPos(), VGet(0.0f, pl->GetRadius(), 0.0f))},
	};
	//���픻��
	VECTOR _vcap_pl_weapon[2] =
	{
		{pl->GetWeaponPos(0)},
		{pl->GetWeaponPos(1)},
	};
	for (auto&& enemy : _list)
	{
		//�G�l�~�[�̔���J�v�Z��
		VECTOR _vcap_enemy[2] =
		{	//[0]���������A[1]����������
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetSeg(), 0.0f))},
			{ VAdd(enemy->GetPos(), VGet(0.0f, enemy->GetRadius(), 0.0f))},
		};
		_distCaptoCap = MathCollision::DisSegAndSeg(_vcap_player[0], _vcap_player[1], p1, t1, _vcap_enemy[0], _vcap_enemy[1], p2, t2);
		//�J�v�Z���̔���
		//�v���C���[�ƓG�̈ړ����̉����o������
		//���a�̍��v
		float add_r_pltoen = pl->GetRadius() + enemy->GetRadius();
		//�����̍ŒZ�����������a�̍��v���傫����ΏՓ˂��Ă���
		if (_distCaptoCap <= add_r_pltoen)
		{	
			if (enemy->GetEnemyType() == Enemy::ENEMYTYPE::CRAB)
			{
				if (enemy->GetAttackFlag())
				{	//�v���C���[���_���[�W�𕉂�
					if (!pl->GetInvincible())
					{
						enemy->SetStatus(EN_Crab::STATUS::REST);
						pl->Damage(enemy->GetPos(), enemy->GetATK());
						pl->SetInvincible(true);
					}
				}
			}
			//�ʒu�̍������v�Z
			VECTOR v = VSub(enemy->GetPos(), pl->GetPos());
			//�������x�N�g���̃T�C�Y�ɕϊ�
			float len = VSize(v);
			//���v�̔��a����T�C�Y������
			len = add_r_pltoen - len;
			//�����������𐳋K�����A�e�v�f�ɂ��������Ƃ��ƃG�l�~�[�̈ʒu�ɉ��Z����
			enemy->SetPos(VScale(VNorm(v), len));
		}
		//����ƓG�̃_���[�W����
		//�J�E���g���U�����蔭�����ԓ�
		if (pl->GetActionCount() >= _data.attackStartTime && pl->GetActionCount() <= _data.attackEndTime)
		{
			//�U�����Ȃ̂�true��
			pl->SetAttackFlag(true);
			//�J�v�Z���̍ŒZ�����̌v�Z
			_distCaptoWeapon = MathCollision::DisSegAndSeg(_vcap_pl_weapon[0], _vcap_pl_weapon[1], p1, t1, _vcap_enemy[0], _vcap_enemy[1], p2, t2);
			//����ƓG�̓����蔻��̔��a�𑫂�
			float add_r_weptoen = _data.radCap + enemy->GetRadius();
			//�ŒZ���������a���傫�����
			if (_distCaptoWeapon <= add_r_weptoen)
			{
				enemy->Damage(pl->GetPos(), pl->_ATK, 10);
			}
		}
		else
		{
			pl->SetAttackFlag(false);
		}
		if (enemy->GetAttackFlag())
		{	//�v���C���[���_���[�W�𕉂�
			if (!pl->GetInvincible())
			{
				if (enemy->GetEnemyType() == Enemy::ENEMYTYPE::OSERO|| enemy->GetEnemyType() == Enemy::ENEMYTYPE::ROMANOFF)
				{
					//�G���픻��
					VECTOR _vcap_en_weapon[2] =
					{
						{enemy->GetWeaponPos(0)},
						{enemy->GetWeaponPos(1)},
					};
					//�J�v�Z���̍ŒZ�����̌v�Z
					_distCaptoWeapon = MathCollision::DisSegAndSeg(_vcap_en_weapon[0], _vcap_en_weapon[1], p1, t1, _vcap_player[0], _vcap_player[1], p2, t2);
					//����ƓG�̓����蔻��̔��a�𑫂�
					float add_r_weptoen = enemy->GetWeaponSize() + pl->GetRadius();
					//�ŒZ���������a���傫�����
					if (_distCaptoWeapon <= add_r_weptoen)
					{
						//�_���[�W���󂯂�
						pl->Damage(enemy->GetPos(), enemy->GetATK());
						pl->SetInvincible(true);
					}
				}
			}
			
		}
	}
	return true;
}

bool ActionCollision::EntoEnColProcess(EnemyManager* _enemy)
{
	//�ŒZ����������
	float _distCaptoCap = 0;
	std::list<Enemy*> _list = _enemy->GetEnemyList();
	//�e�J�v�Z���̍ŒZ���̒[�_�Ɛ��������̊����͓����Ă��Ȃ��Ă����Ȃ��̂�0�ɂ���
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	if (_list.size() > 1)
	{
		for (auto&& enemy_i : _list)
		{
			for (auto&& enemy_j : _list)
			{
				if (enemy_i == enemy_j) { continue; }
				//�G�l�~�[�̔���J�v�Z��
				VECTOR _vcap_i[2] =
				{	//[0]���������A[1]����������
					{ VAdd(enemy_i->GetPos(), VGet(0.0f, enemy_i->GetSeg() , 0.0f))},
					{ VAdd(enemy_i->GetPos(), VGet(0.0f, enemy_i->GetRadius(), 0.0f))},
				};
				VECTOR _vcap_j[2] =
				{	//[0]���������A[1]����������
					{ VAdd(enemy_j->GetPos(), VGet(0.0f, enemy_j->GetSeg() , 0.0f))},
					{ VAdd(enemy_j->GetPos(), VGet(0.0f, enemy_j->GetRadius(), 0.0f))},
				};
				//�v���C���[�ƓG�̈ړ����̉����o������
				_distCaptoCap = MathCollision::DisSegAndSeg(_vcap_i[0], _vcap_i[1], p1, t1, _vcap_j[0], _vcap_j[1], p2, t2);
				//���a�̍��v
				float add_r_pltoen = enemy_i->GetRadius() + enemy_j->GetRadius();
				//�����̍ŒZ�����������a�̍��v���傫����ΏՓ˂��Ă���
				if (_distCaptoCap <= add_r_pltoen)
				{	//�ʒu�̍������v�Z
					VECTOR v = VSub(p1, p2);
					//�������x�N�g���̃T�C�Y�ɕϊ�
					float len = VSize(v);
					//���v�̔��a����T�C�Y������
					len = add_r_pltoen - len;
					//�����������𐳋K�����A�e�v�f�ɂ��������Ƃ��ƃG�l�~�[�̈ʒu�ɉ��Z����
					enemy_i->SetPos(VScale(VNorm(v), len));
				}
			}
		}
	}
	return true;
}

bool ActionCollision::DivineColCircle(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = VSize(VSub(p_pos, e_pos));
	//���������v���a��菬����
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColBreath(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos)
{
	float size = 500;
	float len = VSize(VSub(e_pos, p_pos));
	//�����x�N�g���̂��߂Ƀ}�g���N�X�쐬
	MATRIX m = MGetRotY(p_fvec.y);
	//�}�g���N�X�̐�������t�H���[�h�x�N�g�����쐬
	VECTOR fvec = VScale(VGet(m.m[2][0], m.m[2][1], m.m[2][2]), -1);
	//�G�ʒu�ƃv���C���[�ʒu�̍����x�N�g�������߂�
	VECTOR sub_vec = VSub(e_pos, p_pos);
	if (MathCollision::CollisionPointAndFan(fvec, sub_vec, cos))
	{
		if (len <= size)
		{
			return true;
		}
	}
	return false;
}

bool ActionCollision::DivineColLaser(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = MathCollision::DisSegAndSeg(p_e_pos, p_s_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	//���������v���a��菬����
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColSlash(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = VSize(VSub(p_pos, e_pos));
	//���������v���a��菬����
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColExplosion(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = MathCollision::DisSegAndSeg(p_s_pos, p_e_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColDash(VECTOR p_s_pos, VECTOR p_e_pos, float p_r, VECTOR e_s_pos, VECTOR e_e_pos, float e_r)
{
	VECTOR p1 = VGet(0, 0, 0);
	VECTOR p2 = VGet(0, 0, 0);
	float t1 = 0;
	float t2 = 0;
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = MathCollision::DisSegAndSeg(p_s_pos, p_e_pos, p1, t1, e_s_pos, e_e_pos, p2, t2);
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColVacuum(VECTOR p_pos, VECTOR p_fvec, VECTOR e_pos, float cos)
{
	float size = 700;
	float len = VSize(VSub(e_pos, p_pos));
	//�����x�N�g���̂��߂Ƀ}�g���N�X�쐬
	MATRIX m = MGetRotY(p_fvec.y);
	//�}�g���N�X�̐�������t�H���[�h�x�N�g�����쐬
	VECTOR fvec = VScale(VGet(m.m[2][0], m.m[2][1], m.m[2][2]), -1);
	//�G�ʒu�ƃv���C���[�ʒu�̍����x�N�g�������߂�
	VECTOR sub_vec = VSub(e_pos, p_pos);
	if (MathCollision::CollisionPointAndFan(fvec, sub_vec, cos))
	{
		if (len <= size)
		{
			return true;
		}
	}
	return false;
}

bool ActionCollision::DivineColSonic(VECTOR p_pos, float p_r, VECTOR e_pos, float e_r)
{
	//���v���a���o��
	float add_radius = p_r + e_r;
	//�����Ɛ����̍ŒZ�������o��
	_disDivinetoCap = VSize(VSub(p_pos, e_pos));
	//���������v���a��菬����
	if (_disDivinetoCap <= add_radius)
	{
		return true;
	}
	return false;
}

bool ActionCollision::DivineColProcess(Player* pl, EnemyManager* _enemy)
{
	//�v���C���[�p�����蔻��J�v�Z��
	VECTOR cap[2] =
	{
		{0,0,0},
		{0,0,0},
	};
	//���[�J���̃R���e�i
	std::list<Enemy*> _list = _enemy->GetEnemyList();
	//����p���[�J���ϐ�
	bool iscol = false;
	int frame = 20;
	int attack = 0;
	//�R���e�i�̃G�l�~�[�̐������͈�for������
	for (auto&& enemy : _list)
	{
		//�G�l�~�[�p�����蔻��J�v�Z��
		VECTOR encap[2] =
		{
			enemy->GetPos(),
			VAdd(enemy->GetPos(),VGet(0,enemy->GetSeg(),0)),
		};
		//���X�L�������J��Ԃ�
		for (auto i = 0; i < MAX_SKILL_NUM; i++)
		{
			if (pl->GetDivine()->GetSkill(i).colCnt >= pl->GetDivine()->GetSkill(i).startColFrame && pl->GetDivine()->GetSkill(i).colCnt <= pl->GetDivine()->GetSkill(i).endColFrame)
			{
				//�e�X�L���ŏ�����ύX
				switch (pl->GetDivine()->GetSkill(i).skillName)
				{
				//�u���X
				case Divine::SKILLNAME::BREATH:
					cap[0] = pl->GetPos();
					iscol = DivineColBreath(cap[0], pl->GetDir(), encap[0], 30);
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�T�[�N��
				case Divine::SKILLNAME::CIRCLE:
					//�v���C���[�̈ʒu
					cap[0] = pl->GetPos();
					iscol = DivineColCircle(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//���[�U�[
				case Divine::SKILLNAME::LASER:
					//�v���C���[�̈ʒu
					cap[0] = pl->GetPos();
					//�ݒ肵�Ă������X�L���̈ʒu
					cap[1] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColLaser(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�X���b�V��
				case Divine::SKILLNAME::SLASH:
					//�v���C���[�̈ʒu
					cap[0] = pl->GetPos();
					iscol = DivineColSlash(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�G�N�X�v���[�W����
				case Divine::SKILLNAME::EXPLOSION:
					//�ݒ肵�Ă����X�L���̈ʒu
					cap[0] = pl->GetDivine()->GetSkill(i).vPos;
					cap[1] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColExplosion(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());;
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�_�b�V��
				case Divine::SKILLNAME::DASH:
					pl->GetDivine()->SetIsDash(true);
					//�v���C���[�̈ʒu
					cap[0] = pl->GetPos();
					//�g���𑫂��ďc�J�v�Z����
					cap[1] = VAdd(pl->GetPos(), VGet(0, pl->GetSeg(), 0));
					//�����̍ŒZ�������o��
					iscol = DivineColDash(cap[0], cap[1], pl->GetDivine()->GetSkill(i).size, encap[0], encap[1], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�o�L���[��
				case Divine::SKILLNAME::VACUUM:
					cap[0] = pl->GetDivine()->GetSkill(i).vPos;
					iscol = DivineColVacuum(cap[0], pl->GetDir(), encap[0], 30);
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				//�\�j�b�N�E�F�[�u
				case Divine::SKILLNAME::SONIC:
					//�v���C���[�̈ʒu
					cap[0] = pl->GetPos();
					//�v���C���[�̓G�̋������o��
					iscol = DivineColSonic(cap[0], pl->GetDivine()->GetSkill(i).size, encap[0], enemy->GetRadius());
					attack = pl->GetDivine()->GetSkill(i).atkPoint;
					break;
				}
				//�������Ă���
				if (iscol)
				{
					if (pl->GetDivine()->GetSkill(i).skillName == Divine::SKILLNAME::VACUUM)
					{
						enemy->Suction(cap[0], 20);
					}
					else
					{
						//�_���[�W�𕉂�
						enemy->Damage(cap[0], attack, 20);
					}
					
				}
			}
		}
	}
	return true;
}

bool ActionCollision::ActionColProcess(Player* pl, EnemyManager* _enemy)
{
	PtoEColProcess(pl, _enemy);
	EntoEnColProcess(_enemy);
	return true;
}

bool ActionCollision::Process(Player* pl, EnemyManager* _enemy)
{
	ActionColProcess(pl, _enemy);
	DivineColProcess(pl, _enemy);
	MapColProcess(pl, _enemy);
	return true;
}

bool ActionCollision::Debug(Player* pl) 
{
	clsDx();
	printfDx("%f",pl->GetDivine()->GetSkill(2).vPos.z);
	return false;
}