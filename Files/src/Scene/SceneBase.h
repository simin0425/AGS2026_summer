#pragma once

class SceneBase {
public:
	enum class SCENE {
		NONE,
		PAUSE,
		KEY_CONFIG,
		TITLE,
		GAME,
		CLEAR,
		OVER,

	};

	// システム初期化関数
	virtual bool SystemInit(SCENE scene, int sub_scene);
	// 初期化関数
	virtual bool GameInit() { return false; }
	// 更新関数
	virtual void Update() {}
	// 二次更新関数
	virtual void LateUpdate() {}
	// 描画関数
	virtual void Draw() {}
	// 画面エフェクトを無視する描画関数
	virtual void DrawUI() {}
	// 解放関数
	virtual bool Release() { return false; }

	SCENE GetMyScene() const;
	SCENE GetNextScene() const;

	void SetScene(SCENE scene) { myScene_ = nextScene_ = scene;	}

protected:
	// 自分のシーン
	SCENE myScene_;
	// 遷移先のシーン
	SCENE nextScene_;
	// 自分のサブシーン
	// （主にタイトルシーンからの遷移時に参照する、ステージ数や初期カーソル位置などを指定するための変数）
	int subScene_;

};
