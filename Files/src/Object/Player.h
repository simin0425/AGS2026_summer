#pragma once
#include "ActorBase2D.h"

class Player : public ActorBase2D
{
public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

};