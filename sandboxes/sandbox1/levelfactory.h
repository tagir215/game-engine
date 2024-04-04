#pragma once
#include <engine/gameobject.h>

class LevelFactory {
public:
	virtual GameObject* buildGround(Transform& transform, float mass) = 0;
	virtual GameObject* buildBox(Transform& transform, float mass) = 0;
};