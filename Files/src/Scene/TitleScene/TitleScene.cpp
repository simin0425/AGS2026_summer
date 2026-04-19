#include <DxLib.h>
#include "TitleScene.h"

bool TitleScene::GameInit()
{
    return true;
}

void TitleScene::Update()
{
    // Spaceキーでゲームシーンへ
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        nextScene_ = SCENE::GAME;
    }
}

void TitleScene::Draw()
{
}

void TitleScene::DrawUI()
{
	DrawString(0, 0, "TitleScene", 0xffffff);
}

bool TitleScene::Release()
{
    return true;
}