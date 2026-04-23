#pragma once
#include <chrono>
#include <list>
#include "../Scene/SceneBase.h"
#include "../Scene/GameScene/GameScene.h"

class SceneBase;
class Fader;

class SceneManager {
public:
	static void CreateInstance() { if (instance_ == nullptr) instance_ = new SceneManager; }
	static SceneManager& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

private:
	static SceneManager* instance_;

	SceneManager() {}
	~SceneManager() {}

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

public:
	bool Init();
	void Update();
	void Draw();
	bool Release();
	void ReleaseScene();

	std::list<SceneBase*> GetSceneList();
	Fader* GetFaderPtr();
	float GetDeltaTime() const;

	void SetNextStartStage(unsigned int);
	bool IsPause() const;
	bool PrevPause() const;

	void SetLastScore(unsigned int);
	unsigned int GetLastScore() const;

	unsigned int GetNextStartStage() const;

private:
	GameScene* game_;

	std::list<SceneBase*> sceneList_;
	Fader* fader_;

	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	unsigned int nextStartStage_;
	bool isPause_;
	bool prevPause_;
	SceneBase::SCENE waitSceneId_;
	unsigned int lastScore_;

	bool InitClass();
	void InitParam();

	// シーン切り替え処理の準備
	void ChangeScene(SceneBase::SCENE);

	// Faderの状態に合わせて他の処理に繋げる
	bool Fade();

	// シーン切り替え処理
	void DoChangeScene(SceneBase::SCENE);

};