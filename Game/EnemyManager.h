#pragma once
#include"dxlib.h"
#include"Enemy.h"
#include"EN_Crab.h"
#include"EN_Osero.h"
#include"EN_Romanoff.h"
#include<list>
// �G�̏��A�|�b�v�ɂ������N���X(���̃N���X�ŃC���X�^���X�𑝂₵�܂���̂��A�͂��܂��G�l�~�[�̃N���X���ő��₷���͗v�I�l)
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();
	void Process(VECTOR pl_pos);
	void Render();
	void Spawn(Enemy* enemy);
	void Destroy(Enemy* enemy);
	//�Q�b�^�[
	std::list<Enemy*> GetEnemyList() { return _enemyList; }
	int GetCombo() { return _combo; }
	//�Z�b�^�[
	void SetCombo(int i) { _combo = i; }
private:
	std::list<Enemy*> _enemyList;
	float _combo;
};

