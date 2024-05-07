#pragma once
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/core/object.h"

class TransformComponent : Object<TransformComponent>{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

};
