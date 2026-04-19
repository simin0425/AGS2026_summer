#include <DxLib.h>
#include "GameClearScene.h"

bool GameClearScene::GameInit()
{
    return true;
}

void GameClearScene::Update()
{
    // Spaceキーでタイトルシーンへ
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        nextScene_ = SCENE::TITLE;
    }
}

void GameClearScene::Draw()
{
}

void GameClearScene::DrawUI()
{
	DrawString(0, 0, "GameClearScene", 0xffffff);
}

bool GameClearScene::Release()
{
    return true;
}