#include "collisionsystem.h"
#include <cmath>

CollisionSystem::CollisionSystem(std::vector<GameObject*>gameObjects) : SystemBase(gameObjects) {
	
}

bool checkCollision(GameObject* object1, GameObject* object2) {
	float xDistance = fabs(object1->getTransform().position.x - object2->getTransform().position.x);
	float yDistance = fabs(object1->getTransform().position.y - object2->getTransform().position.y);
	xDistance -= (object1->getPhysics().w / 2 + object2->getPhysics().w / 2);
	yDistance -= (object1->getPhysics().h / 2 + object2->getPhysics().h / 2);
	if (xDistance < 2 && yDistance <= 0) {
		return true;
	}
	return false;
}

void setForces(GameObject* object1, GameObject* object2) {
	Velocity v1 = object1->getVelocity();
	Velocity v2 = object2->getVelocity();
	Physics p1 = object1->getPhysics();
	Physics p2 = object2->getPhysics();

	Velocity newV;
	newV.x = (v1.x + v2.x) / (p1.mass + p2.mass);
	newV.y = (v1.y + v2.y) / (p1.mass + p2.mass);
	newV.z = (v1.z + v2.z) / (p1.mass + p2.mass);

	if (object1->getVelocity().active) {
		object1->getVelocity().x += newV.x - v1.x;
		object1->getVelocity().y += newV.y - v1.y;
		object1->getVelocity().z += newV.z - v1.z;
	}
	if (object2->getVelocity().active) {
		object2->getVelocity().x += newV.x - v2.x;
		object2->getVelocity().y += newV.y - v2.y;
		object2->getVelocity().z += newV.z - v2.z;
	}
}

void CollisionSystem::onUpdate(float deltaTime) {
	std::vector<std::vector<bool>>memo(gameObjects.size(), std::vector<bool>(gameObjects.size()));

	for (int i = 0; i < gameObjects.size(); ++i) {
		for (int j = 0; j < gameObjects.size(); ++j) {
			if (i == j) continue;
			int smaller = i < j ? i : j;
			int bigger = i > j ? i : j;
			if (checkCollision(gameObjects[i], gameObjects[j]) && !memo[smaller][bigger]) {
				setForces(gameObjects[i], gameObjects[j]);
				memo[smaller][bigger] = true;
			}
		}
	}

}