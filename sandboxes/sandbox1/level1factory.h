#pragma once

#include "levelfactory.h"

class Level1Factory : public LevelFactory {
public:
	virtual GameObject* buildGround(Transform& transform, float mass) override;
	virtual GameObject* buildBox(Transform& transform, float mass) override;
};