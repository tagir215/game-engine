#pragma once
#include "transform.h"
class Transformer {
public:
	void translate(Transform& transform, float dx, float dy, float dz);
	void rotate(Transform& transform, float dx, float dy, float dz);
	void scale(Transform& transform, float dx, float dy, float dz);

	void setPosition(Transform& transform, float x, float y, float z);
	void setRotation(Transform& transform, float x, float y, float z);
	void setScale(Transform& transform, float x, float y, float z);

	glm::mat4 getModelMatrix(const Transform& transform);
};