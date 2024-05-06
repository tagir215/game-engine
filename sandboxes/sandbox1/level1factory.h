#pragma once

#include "levelfactory.h"

class Level1Factory : public LevelFactory {
public:
	virtual GameObject* buildGround(Scene* scene, TransformComponent& transform, float mass) override;
	virtual GameObject* buildBox(Scene* scene, TransformComponent& transform, float mass) override;
};