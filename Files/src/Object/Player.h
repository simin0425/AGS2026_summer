#pragma once
#include "ActorBase2D.h"

class Player : public ActorBase2D
{
public:
	Player(int player_num);
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	static constexpr float MOVE_SPEED = 6.0f;

	const int PLAYER_NUM;

};
