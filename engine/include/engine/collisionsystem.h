#pragma once
#include "systembase.h"
#include "camera.h"
#include "transformer.h"
#include <unordered_map>

class CollisionSystem : public SystemBase {
public:
	CollisionSystem(std::vector<GameObject*>gameObjects);
	void onUpdate(float deltaTime) override;
private:
	Transformer transformer;

	std::unordered_map<int, std::vector<glm::vec3>>transformVertices();

};