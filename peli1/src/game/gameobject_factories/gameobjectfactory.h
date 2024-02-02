#pragma once
#include "../gameobject.h"

class GameObjectFactory {
public:
	virtual GameObject* buildGameObject() = 0;
};