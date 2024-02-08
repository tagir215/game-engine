#pragma once
#include <engine/gameobject.h>

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject() = 0;
};
