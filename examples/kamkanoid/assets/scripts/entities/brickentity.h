#pragma once
#include "engine/core/gameobject.h"

class BrickEntity : public GameObject {
public:
	BrickEntity(Scene* scene,  glm::vec3 color);
	void beginPlay() override;
private:
	glm::vec3 color;
};
