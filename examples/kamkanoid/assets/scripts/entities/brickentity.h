#pragma once
#include "engine/gameobject.h"

class BrickEntity : public GameObject {
public:
	BrickEntity(Scene* scene, Transform transform);
	void beginPlay() override;
};
