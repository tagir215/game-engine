#pragma once
#include <engine/gameobject.h>

class LevelFactory {
public:
	virtual GameObject* buildGround(Scene* scene, Transform& transform, float mass) = 0;
	virtual GameObject* buildBox(Scene* scene, Transform& transform, float mass) = 0;
};