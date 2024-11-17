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
	//�w�肳�ꂽ�l�̗v�f��S�č폜����B
	_enemyList.remove(enemy);
	delete enemy;
}
void EnemyManager::Process(VECTOR pl_pos)
{
	//�ꎞ�I�ȏ������邽�߂̃R���e�i���쐬
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
	// �폜�t���O���������G�l�~�[���R���e�i����폜����
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




