#pragma once
#include <engine/core/gameobject.h>

class LevelFactory {
public:
	virtual GameObject* buildGround(Scene* scene, TransformComponent& transform, float mass) = 0;
	virtual GameObject* buildBox(Scene* scene, TransformComponent& transform, float mass) = 0;
};