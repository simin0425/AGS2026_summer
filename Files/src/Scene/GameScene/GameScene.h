#pragma once
#include "../SceneBase.h"

class GameScene : public SceneBase {
public:
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

    void SetStageNumber(unsigned int stageNum) { stageNum_ = stageNum; }

private:
    unsigned int stageNum_;

};