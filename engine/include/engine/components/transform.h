#pragma once
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/core/object.h"

class TransformComponent : public Object<TransformComponent>{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	TransformComponent(
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 rotation = glm::vec3(0, 0, 0), 
		glm::vec3 scale = glm::vec3(1, 1, 1)) 
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}

	glm::vec3 absolutePosition() {
		if (useCache) return absPos;
		TransformComponent* componentParent = dynamic_cast<TransformComponent*>(parent);
		if (componentParent != nullptr) {
			absPos = componentParent->absolutePosition() + position;
			useCache = true;
			return absPos;
		}
		return position;
	}
	bool useCache = false;
private:
	glm::vec3 absPos;
};
