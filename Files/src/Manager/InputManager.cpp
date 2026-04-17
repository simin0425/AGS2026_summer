#include "../Common/Geometry.h"
#include "InputManager.h"

InputManager* InputManager::instance_ = nullptr;


InputManager::InputManager(int pad_max)
	:
	PAD_NUM_MAX(pad_max)
{
	inputMap_.resize(PAD_NUM_MAX);
	gamepads_.resize(PAD_NUM_MAX);
	nowKey_.fill(0);
	prevKey_.fill(0);
}

bool InputManager::Init()
{
	for (int i = 0; i < gamepads_.size(); ++i)
	{
		gamepads_[i] = new Gamepad(i + 1);
	}

	return true;
}

void InputManager::Update()
{
	GetKeyInput();

	for (int i = 0; i < gamepads_.size(); ++i)
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

bool InputManager::NowMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end()) {
		auto p1 = gamepads_[pad_num]->NowButton((*it).second.padMap[0]);
		auto p2 = gamepads_[pad_num]->NowButton((*it).second.padMap[1]);
		auto k1 = NowKey((*it).second.keyMap[0]);
		auto k2 = NowKey((*it).second.keyMap[1]);
		return p1 || p2 || k1 || k2;
	}

	return false;
}

bool InputManager::PrevMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end()) {
		auto p1 = gamepads_[pad_num]->PrevButton((*it).second.padMap[0]);
		auto p2 = gamepads_[pad_num]->PrevButton((*it).second.padMap[1]);
		auto k1 = PrevKey((*it).second.keyMap[0]);
		auto k2 = PrevKey((*it).second.keyMap[1]);
		return p1 || p2 || k1 || k2;
	}

	return false;
}

bool InputManager::DownMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		auto np1 = gamepads_[pad_num]->NowButton((*it).second.padMap[0]);
		auto np2 = gamepads_[pad_num]->NowButton((*it).second.padMap[1]);
		auto nk1 = NowKey((*it).second.keyMap[0]);
		auto nk2 = NowKey((*it).second.keyMap[1]);

		auto pp1 = gamepads_[pad_num]->PrevButton((*it).second.padMap[0]);
		auto pp2 = gamepads_[pad_num]->PrevButton((*it).second.padMap[1]);
		auto pk1 = PrevKey((*it).second.keyMap[0]);
		auto pk2 = PrevKey((*it).second.keyMap[1]);

		return !(pp1 || pp2 || pk1 || pk2) && (np1 || np2 || nk1 || nk2);
	}

	return false;
}

bool InputManager::UpMap(int pad_num, TAGS tag) const
{
	if (pad_num < 0 || pad_num >= PAD_NUM_MAX) return false;

	auto it = inputMap_[pad_num].find(tag);

	if (it != inputMap_[pad_num].end())
	{
		auto np1 = gamepads_[pad_num]->NowButton((*it).second.padMap[0]);
		auto np2 = gamepads_[pad_num]->NowButton((*it).second.padMap[1]);
		auto nk1 = NowKey((*it).second.keyMap[0]);
		auto nk2 = NowKey((*it).second.keyMap[1]);

		auto pp1 = gamepads_[pad_num]->PrevButton((*it).second.padMap[0]);
		auto pp2 = gamepads_[pad_num]->PrevButton((*it).second.padMap[1]);
		auto pk1 = PrevKey((*it).second.keyMap[0]);
		auto pk2 = PrevKey((*it).second.keyMap[1]);

		return !(np1 || np2 || nk1 || nk2) && (pp1 || pp2 || pk1 || pk2);
	}

	return false;
}

int InputManager::NowKey(int d) const
{
	return nowKey_[d];
}

int InputManager::PrevKey(int d) const
{
	return prevKey_[d];
}

bool InputManager::DownKey(int d) const
{
	return NowKey(d) && !PrevKey(d);
}

bool InputManager::UpKey(int d) const
{
	return !NowKey(d) && PrevKey(d);
}

void InputManager::GetKeyInput()
{
	prevKey_ = nowKey_;
	GetHitKeyStateAll(nowKey_.data());
}
