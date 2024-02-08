#include "../include/engine/collisionsystem.h"
#include "../include/engine/transformer.h"
#include <cmath>
#include <unordered_map>
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>

CollisionSystem::CollisionSystem(std::vector<GameObject*>gameObjects, Camera* camera) : SystemBase(gameObjects), camera(camera) {
			
}


bool checkCollision(GameObject* object1, GameObject* object2
	,std::unordered_map<GameObject*,std::vector<glm::vec3>>& transformedVertices) {
	std::vector<glm::vec3>vertices1 = transformedVertices[object1];
	std::vector<glm::vec3>vertices2 = transformedVertices[object2];

	int j = vertices1.size()-1;
	for (int i = 0; i < vertices1.size(); i++) {
		glm::vec3 vertex1 = vertices1[j];
		glm::vec3 vertex2 = vertices1[i];
		j = i;
	}
	return false;
}

void setForces(GameObject* object1, GameObject* object2, glm::vec3 collision) {
	Velocity v1 = object1->getVelocity();
	Velocity v2 = object2->getVelocity();
	Physics p1 = object1->getPhysics();
	Physics p2 = object2->getPhysics();

	Velocity newV;

	newV.x = (v1.x * p1.mass + v2.x * p2.mass) / (p1.mass + p2.mass);
	newV.y = (v1.y * p1.mass + v2.y * p2.mass) / (p1.mass + p2.mass);

	object1->getVelocity().x += (newV.x - v1.x) * collision.x;
	object1->getVelocity().y += (newV.y - v1.y) * collision.y;

	object2->getVelocity().x += (newV.x - v2.x) * collision.x;
	object2->getVelocity().y += (newV.y - v2.y) * collision.y;

}

std::unordered_map<GameObject*, std::vector<glm::vec3>> CollisionSystem::transformVertices() {
	std::unordered_map<GameObject*,std::vector<glm::vec3>> map;
	glm::mat4 VP = camera->getProjectionMatrix() * glm::inverse(transformer.getModelMatrix(camera->getTransform()));
	for (GameObject* object : gameObjects) {
		if (!object->getPhysics().collidable) continue;
		map[object] = std::vector<glm::vec3>();
		glm::mat4 MVP = VP * transformer.getModelMatrix(object->getTransform());
		std::array<float, 18>vertices = object->getMesh()->getVertices();
		for (int i = 0; i < 18; i+=3) {
			glm::vec4 vertex(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);
			map[object].push_back(MVP * vertex);
		}
	}
	return map;
}


void CollisionSystem::onUpdate(float deltaTime) {
	std::vector<std::vector<bool>>memo(gameObjects.size(), std::vector<bool>(gameObjects.size()));
	std::unordered_map<GameObject*, std::vector<glm::vec3>>map = transformVertices();

	for (int i = 0; i < gameObjects.size(); ++i) {
		for (int j = 0; j < gameObjects.size(); ++j) {
			if (i == j) continue;
			int smaller = i < j ? i : j;
			int bigger = i > j ? i : j;
			bool collision = checkCollision(gameObjects[i], gameObjects[j],map);
			if (collision && !memo[smaller][bigger]) {
				setForces(gameObjects[i], gameObjects[j], glm::vec3(0,1,0));
				memo[smaller][bigger] = true;
			}
		}
	}

}