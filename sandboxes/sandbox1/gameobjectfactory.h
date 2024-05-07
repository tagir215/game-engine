#pragma once
#include "engine/core/gameobject.h"

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject(Object<GameObject>* scene, TransformComponent* transform) = 0;
};
