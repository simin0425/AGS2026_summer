#include <algorithm>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/FPSManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "Player.h"

Player::Player(int player_num)
	: PLAYER_NUM(std::clamp(player_num, PLAYER_NUM_MIN, PLAYER_NUM_MAX))
{
}

Player::~Player()
{
}

void Player::Init()
{
	auto a = (int)ResourceManager::SRC::PLAYER1 - 1;

	auto& res = resMng_.Load(ResourceManager::SRC(a + PLAYER_NUM));
	object2D_.handleId = res.handleId_;
}

void Player::Update()
{
	auto& ins = InputManager::GetInstance();
	using tag = InputManager::TAGS;
	auto spd = MOVE_SPEED * FPSManager::GetInstance().GetDeltaTime();

	if (ins.CheckNowMap(PLAYER_NUM, tag::MOVE_UP))
	{
		// ãˆÚ“®‚Ìˆ—
		object2D_.position.y -= spd;
	}
	if (ins.CheckNowMap(PLAYER_NUM, tag::MOVE_DOWN))
	{
		// ‰ºˆÚ“®‚Ìˆ—
		object2D_.position.y += spd;
	}
	if (ins.CheckNowMap(PLAYER_NUM, tag::MOVE_LEFT))
	{
		// ¶ˆÚ“®‚Ìˆ—
		object2D_.position.x -= spd;
	}
	if (ins.CheckNowMap(PLAYER_NUM, tag::MOVE_RIGHT))
	{
		// ‰EˆÚ“®‚Ìˆ—
		object2D_.position.x += spd;
	}

	int sizeX, sizeY;
	GetGraphSize(object2D_.handleId, &sizeX, &sizeY);

	// ‰æ–ÊŠO‚Éo‚È‚¢‚æ‚¤‚É‚·‚é
	object2D_.position.x = std::clamp(object2D_.position.x,
		0.0f + sizeX / 2.0f, static_cast<float>(Application::SCREEN_WIDTH - sizeX / 2.0f));
	object2D_.position.y = std::clamp(object2D_.position.y,
		0.0f + sizeY / 2.0f, static_cast<float>(Application::SCREEN_HEIGHT - sizeY / 2.0f));
}

void Player::Draw()
{
	DrawRotaGraphF(
		object2D_.position.x, object2D_.position.y,
		object2D_.scale, object2D_.rotation,
		object2D_.handleId, TRUE);
}
