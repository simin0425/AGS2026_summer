#include "../Common/Geometry.h"
#include "InputManager.h"

InputManager* InputManager::instance_ = nullptr;


InputManager::InputManager(int pad_max)
	:
	PAD_NUM_MAX(pad_max <= DX_INPUT_PAD16 ? pad_max + 1 : DX_INPUT_PAD16 + 1)
{
	// inputMap_[0]はキーボード操作専用として扱う。
	// デバッグとかFPS表示に使えるかも
	inputMap_.resize(PAD_NUM_MAX);

	// gamepads_[0]は未使用とする（inputMap_と数を合わせるため）。
	// ゲーム側が想定している最大プレイ人数分の領域を確保しておく
	gamepads_.resize(PAD_NUM_MAX);

	// キー入力の状態を初期化
	nowKey_.fill(0);
	prevKey_.fill(0);
}

bool InputManager::Init()
{
	// DxLib上ではゲームパッドは1から始まる
	for (int i = 1; i < gamepads_.size(); ++i)
	{
		gamepads_[i] = new Gamepad(i);
	}

	return true;
}

void InputManager::Update()
{
	GetKeyInput();

	// ゲームパッドの状態を更新
	// ※gamepads_[0]はnullptrなので接触しないように注意
	for (int i = 1; i < gamepads_.size(); ++i)
	{
		gamepads_[i]->Update();
	}
}

bool InputManager::Release()
{
	inputMap_.clear();
	
	for (auto& p : gamepads_)
	{
		delete p;
		p = nullptr;
	}
	gamepads_.clear();

	return true;
}

void InputManager::AddorReplaceMap(int pad_num, TAGS tag, INPUT_MAP map)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	inputMap_[pad_num][tag] = map;
}

void InputManager::AddMap(int pad_num, TAGS tag, INPUT_MAP map)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	if (inputMap_[pad_num].find(tag) != inputMap_[pad_num].end()) return;

	inputMap_[pad_num].emplace(tag, map);
}

void InputManager::ReplaceMap(int pad_num, TAGS tag, INPUT_MAP map)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
		(*it).second = map;
}

void InputManager::ReplaceButtonMap(int pad_num, TAGS tag, PAD_MAP_ARRAY replace)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
		(*it).second.padMap = replace;
}

void InputManager::ReplaceButtonMap(int pad_num, TAGS tag, Gamepad::RAW_BUTTON replace, size_t index)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
		(*it).second.padMap[index] = replace;
}

void InputManager::ReplaceKeyMap(int pad_num, TAGS tag, KEY_MAP_ARRAY replace)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
		(*it).second.keyMap = replace;
}

void InputManager::ReplaceKeyMap(int pad_num, TAGS tag, int replace, size_t index)
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
		(*it).second.keyMap[index] = replace;
}

bool InputManager::CheckNowMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		int p1 = 0, p2 = 0;
		if (pad_num > 0)
		{
			p1 = gamepads_[pad_num]->NowButton((*it).second.padMap[0]);
			p2 = gamepads_[pad_num]->NowButton((*it).second.padMap[1]);
		}
		auto k1 = CheckNowKey((*it).second.keyMap[0]);
		auto k2 = CheckNowKey((*it).second.keyMap[1]);
		return p1 || p2 || k1 || k2;
	}

	return false;
}

bool InputManager::CheckPrevMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		int p1 = 0, p2 = 0;
		if (pad_num > 0)
		{
			p1 = gamepads_[pad_num]->PrevButton((*it).second.padMap[0]);
			p2 = gamepads_[pad_num]->PrevButton((*it).second.padMap[1]);
		}
		auto k1 = CheckPrevKey((*it).second.keyMap[0]);
		auto k2 = CheckPrevKey((*it).second.keyMap[1]);
		return p1 || p2 || k1 || k2;
	}

	return false;
}

bool InputManager::CheckDownMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		return !CheckPrevMap(pad_num, tag) && CheckNowMap(pad_num, tag);
	}

	return false;
}

bool InputManager::CheckUpMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		return CheckPrevMap(pad_num, tag) && !CheckNowMap(pad_num, tag);
	}

	return false;
}

int InputManager::CheckNowKey(int d) const
{
	return nowKey_[d];
}

int InputManager::CheckPrevKey(int d) const
{
	return prevKey_[d];
}

bool InputManager::CheckDownKey(int d) const
{
	return CheckNowKey(d) && !CheckPrevKey(d);
}

bool InputManager::CheckUpKey(int d) const
{
	return !CheckNowKey(d) && CheckPrevKey(d);
}

void InputManager::GetKeyInput()
{
	prevKey_ = nowKey_;
	GetHitKeyStateAll(nowKey_.data());
}
