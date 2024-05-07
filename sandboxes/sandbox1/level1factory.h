#pragma once
#include "levelfactory.h"

class Level1Factory : public LevelFactory {
public:
	virtual GameObject* buildGround(Object<GameObject>* scene, TransformComponent* transform, float mass) override;
	virtual GameObject* buildBox(Object<GameObject>* scene, TransformComponent* transform, float mass) override;
};