#pragma once
#include "engine/core/gameobject.h"

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject(Scene* scene, TransformComponent& transform) = 0;
};
