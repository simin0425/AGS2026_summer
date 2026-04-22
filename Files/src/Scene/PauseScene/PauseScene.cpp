#include <DxLib.h>
#include "PauseScene.h"
#include "../../Manager/InputManager.h"

bool PauseScene::GameInit()
{
    return true;
}

void PauseScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // ゲームシーン
    if (ins.DownKey(KEY_INPUT_P)) {
        nextScene_ = SCENE::GAME;
    }
}

void PauseScene::Draw()
{
    // ゲーム画面を暗くする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawBox(0, 0, 1280, 960, GetColor(0, 0, 0), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    // ウィンドウ
	DrawBox(240, 120, 1040, 840, 0x808080, TRUE);

}

void PauseScene::DrawUI()
{
    DrawString(0, 20, "PauseScene", 0xffffff);
}

bool PauseScene::Release()
{
    return true;
}