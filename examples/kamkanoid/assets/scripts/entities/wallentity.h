#pragma once
#include "engine/core/gameobject.h"

class WallEntity : public GameObject {
public:
	WallEntity(Object* parent, TransformComponent transform);
};
