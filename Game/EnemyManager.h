#pragma once
#include"dxlib.h"
#include"Enemy.h"
#include"EN_Crab.h"
#include"EN_Osero.h"
#include"EN_Romanoff.h"
#include<list>
// 敵の情報、ポップにかかわるクラス(このクラスでインスタンスを増やしまくるのか、はたまたエネミーのクラス内で増やすかは要選考)
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();
	void Process(VECTOR pl_pos);
	void Render();
	void Spawn(Enemy* enemy);
	void Destroy(Enemy* enemy);
	//ゲッター
	std::list<Enemy*> GetEnemyList() { return _enemyList; }
	int GetCombo() { return _combo; }
	//セッター
	void SetCombo(int i) { _combo = i; }
private:
	std::list<Enemy*> _enemyList;
	float _combo;
};

