#pragma once
#include "../SceneBase.h"

class TitleScene : public SceneBase {
public:
	enum class PAGE
    {
        TITLE,
        STAGE_SELECT,
        EXIT_SELECT,
	};

	enum class TITLE_MENU
    {
        START,
        SETTING,
        EXIT,
    };

    enum class STAGE_MENU
    {
        STAGE_1,
        STAGE_2,
        STAGE_3,
	};

    enum class EXIT_MENU
    {
        YES,
        NO,
	};

    // 初期化関数
    bool GameInit() override;
    // 更新関数
    void Update()   override;
    // 二次更新関数
    void Draw()     override;
    // 画面エフェクトを無視する描画関数
    void DrawUI()   override;
    // 解放関数
    bool Release()  override;

	void SelectTitleMenu();
	void SelectStageMenu();
	void SelectExitMenu();

	void DrawTitleMenu();
    void DrawStageMenu();
	void DrawExitMenu();

private:
    PAGE page_;
    TITLE_MENU titleMenu_;
	STAGE_MENU stageMenu_;
	EXIT_MENU exitMenu_;

	int textColor1_;
	int textColor2_;
	int textColor3_;

};