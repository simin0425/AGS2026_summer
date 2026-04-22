#include <DxLib.h>
#include "GameOverScene.h"
#include "../../Manager/InputManager.h"

bool GameOverScene::GameInit()
{
    return true;
}

void GameOverScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // タイトルシーン
    if (ins.CheckDownKey(KEY_INPUT_SPACE)) {
        nextScene_ = SCENE::TITLE;
    }
}

void GameOverScene::Draw()
{
}

void GameOverScene::DrawUI()
{
	DrawString(0, 0, "GameOverScene", 0xffffff);
}

bool GameOverScene::Release()
{
    return true;
}