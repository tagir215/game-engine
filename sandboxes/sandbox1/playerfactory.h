#pragma once
#include "gameobjectfactory.h"

class PlayerFactory : public GameObjectFactory {
public:
	PlayerFactory();
	virtual GameObject* buildGameObject(Scene* scene, TransformComponent* transform) override;
private:
};