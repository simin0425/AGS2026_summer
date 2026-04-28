#pragma once
#include <string>

class Application {
public:
	static void CreateInstance() { if (instance_ == nullptr) instance_ = new Application; }
	static Application& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

private:
	static Application* instance_;

	Application();
	~Application() {}

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 960;

	// データパス関連
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;

	bool Init();
	void GameLoop();
	bool Release();

	void Exit();

private:
	// ゲームループの離脱フラグ
	bool exit_;

	bool SystemInit();
	bool ClassInit();
	void Update();
	void Draw();

};
