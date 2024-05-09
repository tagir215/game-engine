#pragma once
#include <engine/core/gameobject.h>
#include <engine/core/scene.h>

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject(Scene* scene, TransformComponent* transform) = 0;
};
