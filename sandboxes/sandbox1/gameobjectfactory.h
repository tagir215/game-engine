#pragma once
#include <engine/gameobject.h>

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject(Scene* scene, Transform& transform) = 0;
};
