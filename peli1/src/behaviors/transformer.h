#pragma once
#include "../game/transform.h"
class Transformer {
public:
	void translate(Transform& transform, float dx, float dy, float dz);
	void rotate(Transform& transform, float dx, float dy, float dz);
	void scale(Transform& transform, float dx, float dy, float dz);
};