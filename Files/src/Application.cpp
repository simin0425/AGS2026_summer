#include <DxLib.h>
#include <random>
#include <stdio.h>
#include "Common/Geometry.h"
#include "Manager/AudioManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/FontManager.h"
#include "Manager/FPSManager.h"
#include "Manager/InputManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Manager/ScoreManager.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_EFFECT = "Data/Effect/";

Application::Application()
{
	exit_ = false;
}

bool Application::Init()
{
	// システム初期化
	if (SystemInit() == false) return false;

	// クラス初期化
	if (ClassInit() == false) return false;

	return true;
}

void Application::GameLoop()
{
	while (!ProcessMessage() && !exit_)
	{
		// 更新処理
		Update();

		// 描画処理
		Draw();
		
		//
		FPSManager::GetInstance().CheckWait();
	}
}

bool Application::Release()
{
	AudioManager::DeleteInstance();

	FontManager::GetInstance().Release();
	FontManager::DeleteInstance();

	FPSManager::GetInstance().Release();
	FPSManager::DeleteInstance();

	InputManager::GetInstance().Release();
	InputManager::DeleteInstance();

	ResourceManager::GetInstance().Release();
	ResourceManager::DeleteInstance();

	SceneManager::GetInstance().Release();
	SceneManager::DeleteInstance();

	ScoreManager::GetInstance().Release();
	ScoreManager::DeleteInstance();

	EnemyManager::GetInstance().Release();
	EnemyManager::DeleteInstance();

	// DxLib の解放
	DxLib_End();

	return true;
}

void Application::Exit()
{
	exit_ = true;
}

bool Application::SystemInit()
{
	// ウインドウの名称
	SetWindowText("Shooooooot'Em Up!");

	// 画面設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// ウィンドウモード
	ChangeWindowMode(true);

	// DirectX のバージョン
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// DxLib の初期化
	if (DxLib_Init() == -1) return false;

	// 非同期読み込み
	//SetUseASyncLoadFlag(true);

	// 乱数生成処理の初期化
	// 非決定的な乱数
	std::random_device rd;
	// 乱数rdをシード値とした、擬似乱数生成（メルセンヌ・ツイスター）
	std::mt19937 mt(rd());
	// 一様分布生成器（今回はint型を指定）
	std::uniform_int_distribution<int> randDist(0, 9999);
	// 乱数をSRand関数に渡す
	SRand(randDist(mt));

	return true;
}

bool Application::ClassInit()
{
	// AudioManager
	AudioManager::CreateInstance();

	// FontManager
	FontManager::CreateInstance();
	FontManager::GetInstance().Init();

	// FPSManager
	FPSManager::CreateInstance(GetRefreshRate());

	// InputManager
	InputManager::CreateInstance(DX_INPUT_PAD2);
	{
		auto& ins = InputManager::GetInstance();
		using tag = InputManager::TAGS;
		using btn = Gamepad::RAW_BUTTON;

		InputManager::PAD_MAP_ARRAY nullBtns = { btn::NONE, btn::NONE };
		InputManager::KEY_MAP_ARRAY nullKeys = { 0x00, 0x00 };

		ins.AddorReplaceMap(0, tag::FPS_COUNTER,
			{ nullBtns, { KEY_INPUT_INSERT, 0x00 } });

		ins.AddorReplaceMap(0, tag::DEBUG,
			{ nullBtns, { KEY_INPUT_DELETE, 0x00 } });

		{
			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::MOVE_UP,
				{ { btn::DPAD_U, btn::LSTICK_U }, { KEY_INPUT_W, KEY_INPUT_UP } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::MOVE_DOWN,
				{ { btn::DPAD_D, btn::LSTICK_D }, { KEY_INPUT_S, KEY_INPUT_DOWN } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::MOVE_LEFT,
				{ { btn::DPAD_L, btn::LSTICK_L }, { KEY_INPUT_A, KEY_INPUT_LEFT } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::MOVE_RIGHT,
				{ { btn::DPAD_R, btn::LSTICK_R }, { KEY_INPUT_D, KEY_INPUT_RIGHT } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::START,
				{ { btn::BUTTON_7, btn::NONE }, { KEY_INPUT_RETURN, 0x00 } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::SELECT,
				{ { btn::BUTTON_6, btn::NONE }, { KEY_INPUT_BACK, KEY_INPUT_ESCAPE } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::ATTACK_MAIN,
				{ { btn::BUTTON_0, btn::NONE }, { KEY_INPUT_J, 0x00 } });

			ins.AddorReplaceMap(DX_INPUT_PAD1, tag::ATTACK_SUB,
				{ { btn::BUTTON_2, btn::NONE }, { KEY_INPUT_K, 0x00 } });
		}

		{
			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::MOVE_UP,
				{ { btn::DPAD_U, btn::LSTICK_U }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::MOVE_DOWN,
				{ { btn::DPAD_D, btn::LSTICK_D }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::MOVE_LEFT,
				{ { btn::DPAD_L, btn::LSTICK_L }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::MOVE_RIGHT,
				{ { btn::DPAD_R, btn::LSTICK_R }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::START,
				{ { btn::BUTTON_7, btn::NONE }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::SELECT,
				{ { btn::BUTTON_6, btn::NONE }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::ATTACK_MAIN,
				{ { btn::BUTTON_0, btn::NONE }, nullKeys });

			ins.AddorReplaceMap(DX_INPUT_PAD2, tag::ATTACK_SUB,
				{ { btn::BUTTON_2, btn::NONE }, nullKeys });
		}
	}

	// ResourceManager
	ResourceManager::CreateInstance();
	ResourceManager::GetInstance().Init();

	// SceneManager
	SceneManager::CreateInstance();
	SceneManager::GetInstance().Init();

	// ScoreManager
	ScoreManager::CreateInstance(DX_INPUT_PAD2);
	ScoreManager::GetInstance().Init();
	ScoreManager::GetInstance().SetExtendScore();

	// EnemyManager
	EnemyManager::CreateInstance();
	EnemyManager::GetInstance().Init();

	return true;
}

void Application::Update()
{
	InputManager::GetInstance().Update();

	FPSManager::GetInstance().Update(
		InputManager::GetInstance().CheckDownMap(0, InputManager::TAGS::FPS_COUNTER));

	SceneManager::GetInstance().Update();

	ScoreManager::GetInstance().Update();

	EnemyManager::GetInstance().Update();
}

void Application::Draw()
{
	// 描画先の画面をクリア
	ClearDrawScreen();

	// 描画先の画面
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager::GetInstance().Draw();

	EnemyManager::GetInstance().Draw();

	FPSManager::GetInstance().Draw(
		FontManager::GetInstance().GetFontHandle(FontManager::TAGS::GENERAL_SMALL));

#ifdef _DEBUG
	Vector2 center = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	DrawCircleAA(center.x, center.y, 3.0f, 12, 0x00FFFFU, true);
#endif

	// 裏画面を表画面に転写
	ScreenFlip();
}
