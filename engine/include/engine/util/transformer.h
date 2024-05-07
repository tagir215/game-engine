#pragma once
#include "engine/components/transform.h"

class Transformer {
public:
	void translate(TransformComponent& transform, float dx, float dy, float dz);
	void rotate(TransformComponent& transform, float dx, float dy, float dz);
	void scale(TransformComponent& transform, float dx, float dy, float dz);

	void setPosition(TransformComponent& transform, float x, float y, float z);
	void setRotation(TransformComponent& transform, float x, float y, float z);
	void setScale(TransformComponent& transform, float x, float y, float z);

	glm::mat4 getModelMatrix(const TransformComponent& transform);
};