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
	static constexpr float MOVE_SPEED = 6.0f * 60.0f;
	static constexpr int PLAYER_NUM_MIN = 1;
	static constexpr int PLAYER_NUM_MAX = 2;

	const int PLAYER_NUM;

};
