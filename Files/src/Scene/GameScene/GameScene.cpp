#include <DxLib.h>
#include "GameScene.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Object/Player.h"

bool GameScene::GameInit()
{
	players_.emplace_back(std::make_shared<Player>(1));
    //players_.emplace_back(std::make_shared<Player>(2));
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

    for (auto& player : players_)
    {
        player->Update();
	}
}

void GameScene::Draw()
{
    for (auto& player : players_)
    {
        player->Draw();
    }
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
    players_.clear();
    return true;
}