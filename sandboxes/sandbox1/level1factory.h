#pragma once
#include "level1factory.h"
#include <glm/glm.hpp>
#include <engine/core/gameobject.h>
#include <engine/core/scene.h>

class Level1Factory {
public:
	GameObject* buildGround(Scene* scene, float mass, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
	GameObject* buildBox(Scene* scene, float mass, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
	GameObject* buildPlayer(Scene* scene, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
};