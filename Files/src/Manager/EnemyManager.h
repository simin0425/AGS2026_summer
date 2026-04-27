#pragma once
#include <list>

class EnemyManager
{
public:
	static void CreateInstance() { if (instance_ == nullptr) instance_ = new EnemyManager; }
	static EnemyManager& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

private:
	static EnemyManager* instance_;
	EnemyManager() {}
	~EnemyManager() {}
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager& operator=(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator=(EnemyManager&&) = delete;

public:
	bool Init();
	bool Update();
	void Draw();
	bool Release();
	void ReleaseEnemy();

	constexpr static int RESPAWN_TIME = 300;

private:
	int stageNum_;

	int imgEnemyA_;
	int imgEnemyB_;

	float enemyAPosX_;
	float enemyAPosY_;

	float enemyBPosX_;
	float enemyBPosY_;

	int enemyARespownCnt_;
	int enemyBRespownCnt_;

};