#pragma once
#include <string>

class Application {
public:
	// データパス関連
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;

	static void CreateInstance() { if (instance_ == nullptr) instance_ = new Application; }
	static Application& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

	bool Init();
	void GameLoop();
	bool Release();

	void Quit();

private:
	static Application* instance_;

	Application() {}
	~Application() {}

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

	bool exit_;

	bool SystemInit();
	bool ClassInit();
	void Update();
	void Draw();

};
