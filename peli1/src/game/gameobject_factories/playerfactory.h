#pragma once
#include "gameobjectfactory.h"

class PlayerFactory : public GameObjectFactory {
public:
	virtual GameObject* buildGameObject() override;
};