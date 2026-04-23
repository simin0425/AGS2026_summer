#pragma once
#include <array>
#include <map>
#include <vector>
#include <DxLib.h>
#include "Gamepad.h"

class InputManager {
public:
	/// シングルトン
	static void CreateInstance(int pad_max) { if (instance_ == nullptr) instance_ = new InputManager(pad_max); instance_->Init(); }
	static InputManager& GetInstance() { return *instance_; }
	static void DeleteInstance() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

private:
	/// シングルトン
	static InputManager* instance_;

	InputManager(int pad_max);
	~InputManager() {}

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(InputManager&&) = delete;

public:
	enum class TAGS {
		NONE,

		FPS_COUNTER,
		DEBUG,

		START,
		SELECT,

		MOVE_BACK,
		MOVE_DOWN,
		MOVE_FRONT,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,

		ATTACK_MAIN,
		ATTACK_SUB,
		ATTACK_SPECIAL,

		DASH,
		JUMP,
	};

	using KEY_STATE_ARRAY = std::array<char, 256ULL>;
	using PAD_MAP_ARRAY = std::array<Gamepad::RAW_BUTTON, 2ULL>;
	using KEY_MAP_ARRAY = std::array<int, 2ULL>;

	struct INPUT_MAP {
		PAD_MAP_ARRAY padMap;
		KEY_MAP_ARRAY keyMap;
	};

	bool Init();
	void Update();
	bool Release();

	void AddorReplaceMap(int pad_num, TAGS tag, INPUT_MAP map);
	void AddMap(int pad_num, TAGS tag, INPUT_MAP map);
	void ReplaceMap(int pad_num, TAGS tag, INPUT_MAP map);

	void ReplaceButtonMap(int pad_num, TAGS tag, PAD_MAP_ARRAY replace);
	void ReplaceButtonMap(int pad_num, TAGS tag, Gamepad::RAW_BUTTON replace, size_t index);

	void ReplaceKeyMap(int pad_num, TAGS tag, KEY_MAP_ARRAY replace);
	void ReplaceKeyMap(int pad_num, TAGS tag, int replace, size_t index);

	bool CheckNowMap(int pad_num, TAGS tag) const;
	bool CheckPrevMap(int pad_num, TAGS tag) const;
	bool CheckDownMap(int pad_num, TAGS tag) const;
	bool CheckUpMap(int pad_num, TAGS tag) const;

	int CheckNowKey(int DxLib_KEYcode) const;
	int CheckPrevKey(int DxLib_KEYcode) const;
	bool CheckDownKey(int DxLib_KEYcode) const;
	bool CheckUpKey(int DxLib_KEYcode) const;

private:
	static constexpr double XINPUT_STICK_MULT = 1000.0 / (short)0x7fff;

	const int PAD_NUM_MAX;

	// タグと入力マップの対応表
	std::vector<std::map<TAGS, INPUT_MAP>> inputMap_;
	std::vector<Gamepad*> gamepads_;

	KEY_STATE_ARRAY nowKey_;
	KEY_STATE_ARRAY prevKey_;

	void GetKeyInput();

};
