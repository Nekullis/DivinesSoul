#include "EnemyManager.h"
#include "ApplicationMain.h"
EnemyManager::EnemyManager()
{
	_combo = 0;
}
EnemyManager::~EnemyManager()
{

}

void EnemyManager::Spawn(Enemy* enemy)
{
	_enemyList.push_back(enemy);
}

void EnemyManager::Destroy(Enemy* enemy)
{
	//指定された値の要素を全て削除する。
	_enemyList.remove(enemy);
	delete enemy;
}
void EnemyManager::Process(VECTOR pl_pos)
{
	//一時的な消去するためのコンテナを作成
	std::list<Enemy*> tempEnemiesToRemove;
	for (auto&& enemy : _enemyList)
	{
		enemy->Process(pl_pos);
		if (enemy->GetDeleteFlag())
		{
			_combo++;
			tempEnemiesToRemove.push_back(enemy);
		}
	}
	// 削除フラグが立ったエネミーをコンテナから削除する
	for (auto&& enemy : tempEnemiesToRemove)
	{
		Destroy(enemy);
	}
}

void EnemyManager::Render()
{
	for (auto&& enemy : _enemyList)
	{
		enemy->Render();
	}
}




