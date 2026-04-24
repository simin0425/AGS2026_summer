#include <DxLib.h>
#include "StageClearScene.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

bool StageClearScene::GameInit()
{
    // 現在のステージ番号を取得
    stageNum_ = SceneManager::GetInstance().GetNextStartStage();
    return true;
}

void StageClearScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    if (ins.CheckDownKey(KEY_INPUT_SPACE))
    {
        if (stageNum_ <= 1)
        {
            // ショップシーンへ＆ステージを次に進める
            SceneManager::GetInstance().SetNextStartStage(stageNum_ + 1);
            nextScene_ = SCENE::SHOP;
        }
        else
        {
            // ゲームクリアシーンへ
            nextScene_ = SCENE::GAME_CLEAR;
        }
    }
}

void StageClearScene::Draw()
{
}

void StageClearScene::DrawUI()
{
    DrawString(0, 0, "StageClearScene", 0xffffff);
}

bool StageClearScene::Release()
{
    return true;
}