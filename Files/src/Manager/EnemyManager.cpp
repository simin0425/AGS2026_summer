#include <DxLib.h>
#include "EnemyManager.h"
#include "SceneManager.h"
#include "../Application.h"

EnemyManager* EnemyManager::instance_ = nullptr;

bool EnemyManager::Init()
{
	// 現在のステージ番号を取得
	stageNum_ = SceneManager::GetInstance().GetNextStartStage();

	// 画像を読み込む
	imgEnemyA_ = LoadGraph((Application::PATH_IMAGE + "EnemyA.png").c_str());
	imgEnemyB_ = LoadGraph((Application::PATH_IMAGE + "EnemyB.png").c_str());

	// 敵の初期位置
	enemyAPosX_ = 300.0f;
	enemyAPosY_ = 0.0f;
	enemyBPosX_ = 900.0f;
	enemyBPosY_ = 0.0f;

	enemyARespownCnt_ = 0;
	enemyBRespownCnt_ = 0;

	return true;
}

bool EnemyManager::Update()
{
	// ゲームシーンかを取得
	if (SceneManager::GetInstance().GetSceneList().back()->GetMyScene() == SceneBase::SCENE::GAME)
	{
		enemyAPosY_ += 3.0f;
		enemyBPosY_ += 2.5f;
	}

	//enemyAPosY_ += 3.0f;
	//enemyBPosY_ += 2.5f;

	if (enemyAPosY_ > Application::SCREEN_HEIGHT)
	{
		enemyARespownCnt_++;
		if(enemyARespownCnt_ >= RESPAWN_TIME)
		{
			enemyARespownCnt_ = 0;
			enemyAPosY_ = 0.0f;
		}
	}

	if (enemyBPosY_ > Application::SCREEN_HEIGHT)
	{
		enemyBRespownCnt_++;
		if(enemyBRespownCnt_ >= RESPAWN_TIME)
		{
			enemyBRespownCnt_ = 0;
			enemyBPosY_ = 0.0f;
		}
	}

	return true;
}

void EnemyManager::Draw()
{
	// ゲームシーンかを取得
	if (SceneManager::GetInstance().GetSceneList().back()->GetMyScene() == SceneBase::SCENE::GAME)
	{
		DrawRotaGraph(enemyAPosX_, enemyAPosY_, 1.0, 0.0, imgEnemyA_, TRUE);
		DrawRotaGraph(enemyBPosX_, enemyBPosY_, 1.0, 0.0, imgEnemyB_, TRUE);
	}

	//DrawRotaGraph(enemyAPosX_, enemyAPosY_, 1.0, 0.0, imgEnemyA_, TRUE);
	//DrawRotaGraph(enemyBPosX_, enemyBPosY_, 1.0, 0.0, imgEnemyB_, TRUE);
}

bool EnemyManager::Release()
{
	DeleteGraph(imgEnemyA_);
	DeleteGraph(imgEnemyB_);
	return true;
}

void EnemyManager::ReleaseEnemy()
{
}