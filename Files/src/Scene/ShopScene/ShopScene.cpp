#include <DxLib.h>
#include "ShopScene.h"
#include "../../Manager/InputManager.h"

bool ShopScene::GameInit()
{
    return true;
}

void ShopScene::Update()
{
    InputManager& ins = InputManager::GetInstance();
    // ÉQÅ[ÉÄÉVÅ[Éì
    if (ins.DownKey(KEY_INPUT_SPACE)) {
        nextScene_ = SCENE::GAME;
    }
}

void ShopScene::Draw()
{
}

void ShopScene::DrawUI()
{
    DrawString(0, 0, "ShopScene", 0xffffff);
}

bool ShopScene::Release()
{
    return true;
}