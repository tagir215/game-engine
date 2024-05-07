#pragma once
#include "engine/core/gameobject.h"

class BrickEntity : public GameObject {
public:
	BrickEntity(Object* parent, TransformComponent* transform, glm::vec3 color);
	void beginPlay() override;
};
