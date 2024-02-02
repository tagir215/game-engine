#include "collisionsystem.h"
#include <cmath>
#include "../util/transformer.h"

CollisionSystem::CollisionSystem(std::vector<GameObject*>gameObjects) : SystemBase(gameObjects) {
	
}

glm::vec3 checkCollision(GameObject* object1, GameObject* object2) {
	float xDistance = fabs(object1->getTransform().position.x - object2->getTransform().position.x);
	float yDistance = fabs(object1->getTransform().position.y - object2->getTransform().position.y);
	float widths = object1->getPhysics().w / 2 + object2->getPhysics().w / 2;
	float heights = object1->getPhysics().h / 2 + object2->getPhysics().h / 2;
	float xCornerDistance = xDistance - widths;
	float yCornerDistance = yDistance - heights;
				


	if (xCornerDistance <= 0 && yCornerDistance <= 0) {
		if (std::fabs(xCornerDistance / widths) < std::fabs(yCornerDistance / heights)) {
			GameObject* objectWithVelocity = std::fabs(object1->getVelocity().x) > std::fabs(object2->getVelocity().x)
				? object1 : object2;
			GameObject* objectWithLessVelocity = std::fabs(object1->getVelocity().x) < std::fabs(object2->getVelocity().x)
				? object1 : object2;
			if((objectWithVelocity->getVelocity().x > 0 
				&& (objectWithVelocity->getTransform().position.x < objectWithLessVelocity->getTransform().position.x))
				||
				objectWithVelocity->getVelocity().x < 0
				&& (objectWithVelocity->getTransform().position.x > objectWithLessVelocity->getTransform().position.x))
			return glm::vec3(1, 0, 0);
		}
		else {
			GameObject* objectWithVelocity = std::fabs(object1->getVelocity().y) > std::fabs(object2->getVelocity().y)
				? object1 : object2;
			GameObject* objectWithLessVelocity = std::fabs(object1->getVelocity().y) < std::fabs(object2->getVelocity().y)
				? object1 : object2;
			if((objectWithVelocity->getVelocity().y > 0 
				&& (objectWithVelocity->getTransform().position.y < objectWithLessVelocity->getTransform().position.y))
				||
				objectWithVelocity->getVelocity().y < 0
				&& (objectWithVelocity->getTransform().position.y > objectWithLessVelocity->getTransform().position.y))
			return glm::vec3(0, 1, 0);
		}
	}
	return glm::vec3(0, 0, 0);
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


void CollisionSystem::onUpdate(float deltaTime) {
	std::vector<std::vector<bool>>memo(gameObjects.size(), std::vector<bool>(gameObjects.size()));

	for (int i = 0; i < gameObjects.size(); ++i) {
		for (int j = 0; j < gameObjects.size(); ++j) {
			if (i == j) continue;
			int smaller = i < j ? i : j;
			int bigger = i > j ? i : j;
			glm::vec3 collision = checkCollision(gameObjects[i], gameObjects[j]);
			if (collision != glm::vec3(0,0,0) && !memo[smaller][bigger]) {
				setForces(gameObjects[i], gameObjects[j], collision);
				memo[smaller][bigger] = true;
			}
		}
	}

}