#pragma once
#include "engine/core/gameobject.h"

class BrickEntity : public GameObject {
public:
	BrickEntity(Scene* scene, TransformComponent* transform, glm::vec3 color);
	void beginPlay() override;
private:
	TransformComponent* transform;
	glm::vec3 color;
};
