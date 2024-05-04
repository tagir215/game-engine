#pragma once
#include "engine/gameobject.h"

class BrickEntity : public GameObject {
public:
	BrickEntity(Scene* scene, Transform transform, glm::vec3 color);
	void beginPlay() override;
};
