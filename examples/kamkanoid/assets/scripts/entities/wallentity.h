#pragma once
#include "engine/core/gameobject.h"

class WallEntity : public GameObject {
public:
	WallEntity(Scene* scene, TransformComponent transform);
};
