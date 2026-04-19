#include <DxLib.h>
#include "GameScene.h"

bool GameScene::GameInit()
{
    return true;
}

void GameScene::Update()
{
    // Zキーでゲームクリアシーンへ
    if (CheckHitKey(KEY_INPUT_Z)) {
        nextScene_ = SCENE::CLEAR;
    }

    // Xキーでゲームオーバーシーンへ
    if (CheckHitKey(KEY_INPUT_X)) {
        nextScene_ = SCENE::OVER;
    }
}

void GameScene::Draw()
{
}

void GameScene::DrawUI()
{
	DrawString(0, 0, "GameScene", 0xffffff);
}

bool GameScene::Release()
{
    return true;
}