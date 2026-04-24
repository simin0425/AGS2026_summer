#include <DxLib.h>
#include "GameScene.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"

bool GameScene::GameInit()
{
    return true;
}

void GameScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // ステージクリアシーン
    if (ins.CheckDownKey(KEY_INPUT_LSHIFT))
    {
        nextScene_ = SCENE::STAGE_CLEAR;
    }

    // ゲームクリアシーン
    if (ins.CheckDownKey(KEY_INPUT_Z))
    {
        nextScene_ = SCENE::GAME_CLEAR;
    }

    // ゲームオーバーシーン
    if (ins.CheckDownKey(KEY_INPUT_X))
    {
        nextScene_ = SCENE::OVER;
    }

    // ショップシーン
    if (ins.CheckDownKey(KEY_INPUT_C))
    {
        nextScene_ = SCENE::SHOP;
    }

    // ポーズシーン
    if (ins.CheckDownKey(KEY_INPUT_P))
    {
        nextScene_ = SCENE::PAUSE;
    }
}

void GameScene::Draw()
{
}

void GameScene::DrawUI()
{
    DrawString(0, 0, "GameScene", 0xffffff);

    // ステージ名表示
    const char* stageNames[] = { "ステージ１", "ステージ２", "ステージ３" };

    SetFontSize(18);
    DrawFormatString(0, 40, 0xffffff, "%s", stageNames[stageNum_]);
}

bool GameScene::Release()
{
    return true;
}