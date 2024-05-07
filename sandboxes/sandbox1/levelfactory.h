#pragma once
#include <engine/core/gameobject.h>

class LevelFactory {
public:
	virtual GameObject* buildGround(Object<GameObject>* scene, TransformComponent* transform, float mass) = 0;
	virtual GameObject* buildBox(Object<GameObject>* scene, TransformComponent* transform, float mass) = 0;
};