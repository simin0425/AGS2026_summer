#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	auto res = resMng_.Load(ResourceManager::SRC::PLAYER);
	object2D_.handleId = res.handleId_;
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawRotaGraph(
		object2D_.position.x, object2D_.position.y,
		object2D_.scale, object2D_.rotation,
		object2D_.handleId, TRUE);
}
