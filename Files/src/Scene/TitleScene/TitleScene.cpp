#include <DxLib.h>
#include "TitleScene.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"

bool TitleScene::GameInit()
{
    page_ = PAGE::TITLE;
    titleMenu_ = TITLE_MENU::START;
    stageMenu_ = STAGE_MENU::STAGE_1;
    textColor1_ = 0x000000;
    textColor2_ = 0x000000;
    textColor3_ = 0x000000;
    return true;
}

void TitleScene::Update()
{
    InputManager& ins = InputManager::GetInstance();

    // メニュー選択
    switch (page_)
    {
    case PAGE::TITLE:
        SelectTitleMenu();
        break;
    case PAGE::STAGE_SELECT:
        SelectStageMenu();
        break;
    case PAGE::EXIT_SELECT:
        SelectExitMenu();
        break;
    }
}

void TitleScene::Draw()
{
}

void TitleScene::DrawUI()
{
#ifdef _DEBUG
    DrawString(0, 0, "TitleScene", 0xffffff);
#endif //DEBUG

    // メニュー描画
    switch (page_)
    {
    case PAGE::TITLE:
        DrawTitleMenu();
        break;
    case PAGE::STAGE_SELECT:
        DrawStageMenu();
        break;
    case PAGE::EXIT_SELECT:
        DrawExitMenu();
        break;
    }
}

bool TitleScene::Release()
{
    return true;
}

void TitleScene::SelectTitleMenu()
{
    InputManager& ins = InputManager::GetInstance();
    // 選択肢移動
    if (ins.CheckDownKey(KEY_INPUT_UP) || ins.CheckDownKey(KEY_INPUT_W))
    {
        // 上移動
        if (titleMenu_ != TITLE_MENU::START)
        {
            titleMenu_ = static_cast<TITLE_MENU>(static_cast<int>(titleMenu_) - 1);
        }
        else
        {
            titleMenu_ = TITLE_MENU::EXIT;
        }
    }
    else if (ins.CheckDownKey(KEY_INPUT_DOWN) || ins.CheckDownKey(KEY_INPUT_S))
    {
        // 下移動
        if (titleMenu_ != TITLE_MENU::EXIT)
        {
            titleMenu_ = static_cast<TITLE_MENU>(static_cast<int>(titleMenu_) + 1);
        }
        else
        {
            titleMenu_ = TITLE_MENU::START;
        }
    }

    // 選択肢決定
    if (ins.CheckDownKey(KEY_INPUT_RETURN) || ins.CheckDownKey(KEY_INPUT_SPACE))
    {
        switch (titleMenu_)
        {
        case TITLE_MENU::START:
            // ステージ選択画面へ
            page_ = PAGE::STAGE_SELECT;
            stageMenu_ = STAGE_MENU::STAGE_1;
            break;
        case TITLE_MENU::SETTING:
            // 設定画面

            break;
        case TITLE_MENU::EXIT:
            // ゲーム終了
            page_ = PAGE::EXIT_SELECT;
            exitMenu_ = EXIT_MENU::YES;
            break;
        }
    }
}

void TitleScene::SelectStageMenu()
{
    InputManager& ins = InputManager::GetInstance();
    // 選択肢移動
    if (ins.CheckDownKey(KEY_INPUT_UP) || ins.CheckDownKey(KEY_INPUT_W))
    {
        // 上移動
        if (stageMenu_ != STAGE_MENU::STAGE_1)
        {
            stageMenu_ = static_cast<STAGE_MENU>(static_cast<int>(stageMenu_) - 1);
        }
        else
        {
            stageMenu_ = STAGE_MENU::STAGE_3;
        }
    }
    else if (ins.CheckDownKey(KEY_INPUT_DOWN) || ins.CheckDownKey(KEY_INPUT_S))
    {
        // 下移動
        if (stageMenu_ != STAGE_MENU::STAGE_3)
        {
            stageMenu_ = static_cast<STAGE_MENU>(static_cast<int>(stageMenu_) + 1);
        }
        else
        {
            stageMenu_ = STAGE_MENU::STAGE_1;
        }
    }

    // 選択肢決定
    if (ins.CheckDownKey(KEY_INPUT_RETURN) || ins.CheckDownKey(KEY_INPUT_SPACE))
    {
        int stageNum = static_cast<int>(stageMenu_);
        SceneManager::GetInstance().SetNextStartStage(stageNum);
        nextScene_ = SCENE::GAME;
    }

    // タイトルメニューへ
    if (ins.CheckDownKey(KEY_INPUT_ESCAPE) || ins.CheckDownKey(KEY_INPUT_BACK))
    {
        page_ = PAGE::TITLE;
        titleMenu_ = TITLE_MENU::START;
    }
}

void TitleScene::SelectExitMenu()
{
    InputManager& ins = InputManager::GetInstance();
    // 選択肢移動
    if (ins.CheckDownKey(KEY_INPUT_UP) || ins.CheckDownKey(KEY_INPUT_W))
    {
        // 上移動
        if (exitMenu_ != EXIT_MENU::YES)
        {
            exitMenu_ = static_cast<EXIT_MENU>(static_cast<int>(exitMenu_) - 1);
        }
        else
        {
            exitMenu_ = EXIT_MENU::NO;
        }
    }
    else if (ins.CheckDownKey(KEY_INPUT_DOWN) || ins.CheckDownKey(KEY_INPUT_S))
    {
        // 下移動
        if (exitMenu_ != EXIT_MENU::NO)
        {
            exitMenu_ = static_cast<EXIT_MENU>(static_cast<int>(exitMenu_) + 1);
        }
        else
        {
            exitMenu_ = EXIT_MENU::YES;
        }
    }

    // 選択肢決定
    if ((ins.CheckDownKey(KEY_INPUT_RETURN) || ins.CheckDownKey(KEY_INPUT_SPACE)))
    {
        switch (exitMenu_)
        {
        case EXIT_MENU::YES:
            // ゲーム終了
            break;
        case EXIT_MENU::NO:
            // タイトル画面へ
            page_ = PAGE::TITLE;
            titleMenu_ = TITLE_MENU::START;
            break;
        }
    }

    // タイトルメニューへ
    if (ins.CheckDownKey(KEY_INPUT_ESCAPE) || ins.CheckDownKey(KEY_INPUT_BACK))
    {
        page_ = PAGE::TITLE;
        titleMenu_ = TITLE_MENU::START;
    }
}

void TitleScene::DrawTitleMenu()
{
    // 選択肢カラー初期化(黒)
    textColor1_ = 0x000000;
    textColor2_ = 0x000000;
    textColor3_ = 0x000000;

    // 選択中(黄)
    switch (titleMenu_)
    {
    case TitleScene::TITLE_MENU::START:
        textColor1_ = 0xffff00;
        break;
    case TitleScene::TITLE_MENU::SETTING:
        textColor2_ = 0xffff00;
        break;
    case TitleScene::TITLE_MENU::EXIT:
        textColor3_ = 0xffff00;
        break;
    }

    // 選択肢表示
    SetFontSize(50);
    DrawFormatString(480, 200, textColor1_, "ステージ選択");
    DrawFormatString(590, 450, textColor2_, "設定");
    DrawFormatString(520, 700, textColor3_, "ゲーム終了");
}

void TitleScene::DrawStageMenu()
{
    // 選択肢カラー初期化(黒)
    textColor1_ = 0x000000;
    textColor2_ = 0x000000;
    textColor3_ = 0x000000;

    // 選択中(黄)
    switch (stageMenu_)
    {
    case TitleScene::STAGE_MENU::STAGE_1:
        textColor1_ = 0xffff00;
        break;
    case TitleScene::STAGE_MENU::STAGE_2:
        textColor2_ = 0xffff00;
        break;
    case TitleScene::STAGE_MENU::STAGE_3:
        textColor3_ = 0xffff00;
        break;
    }

    // 選択肢表示
    SetFontSize(50);
    DrawFormatString(520, 200, textColor1_, "ステージ１");
    DrawFormatString(520, 450, textColor2_, "ステージ２");
    DrawFormatString(520, 700, textColor3_, "ステージ３");
}

void TitleScene::DrawExitMenu()
{
    // 選択肢カラー初期化(黒)
    textColor1_ = 0x000000;
    textColor2_ = 0x000000;

    // 選択中(黄)
    switch (exitMenu_)
    {
    case TitleScene::EXIT_MENU::YES:
        textColor1_ = 0xffff00;
        break;
    case TitleScene::EXIT_MENU::NO:
        textColor2_ = 0xffff00;
        break;
    }

    // 選択肢表示
    SetFontSize(50);
    DrawFormatString(360, 300, 0x000000, "ゲームを終了しますか？");
    DrawFormatString(590, 550, textColor1_, "はい");
    DrawFormatString(565, 700, textColor2_, "いいえ");
}