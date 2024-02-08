#pragma once
#include "systembase.h"
#include "camera.h"
#include "transformer.h"
#include <unordered_map>

class CollisionSystem : public SystemBase {
public:
	CollisionSystem(std::vector<GameObject*>gameObjects, Camera* camera);
	void onUpdate(float deltaTime) override;
private:
	Camera* camera;
	Transformer transformer;
	std::unordered_map<GameObject*, std::vector<glm::vec3>>transformVertices();
};