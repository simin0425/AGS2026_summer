#include <DxLib.h>
#include "GameClearScene.h"
#include "../../Manager/InputManager.h"

bool GameClearScene::GameInit()
{
    return true;
}

void GameClearScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // タイトルシーン
    if (ins.DownKey(KEY_INPUT_SPACE)) {
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