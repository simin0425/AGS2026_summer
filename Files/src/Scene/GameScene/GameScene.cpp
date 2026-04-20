#include <DxLib.h>
#include "GameScene.h"
#include "../../Manager/InputManager.h"

bool GameScene::GameInit()
{
    return true;
}

void GameScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // ゲームクリアシーン
    if (ins.DownKey(KEY_INPUT_Z)) {
        nextScene_ = SCENE::CLEAR;
    }

    // ゲームオーバーシーン
    if (ins.DownKey(KEY_INPUT_X)) {
        nextScene_ = SCENE::OVER;
    }

    // ショップシーン
    if (ins.DownKey(KEY_INPUT_C)) {
        nextScene_ = SCENE::SHOP;
	}

	// ポーズシーン
    if (ins.DownKey(KEY_INPUT_P)) {
        nextScene_ = SCENE::PAUSE;
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