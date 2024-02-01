#include "collisionsystem.h"
#include <cmath>

CollisionSystem::CollisionSystem(std::vector<GameObject*>gameObjects) : SystemBase(gameObjects) {
}

void CollisionSystem::onUpdate(float deltaTime) {
	GameObject* player = gameObjects[0];
	GameObject* ground = gameObjects[1];

	bool colliding = false;
		
	float py = player->getTransform().position.y;
	float gy = ground->getTransform().position.y;
	float ph = player->getPhysics().h;
	float gh = player->getPhysics().h;

	if (std::fabs((py-ph/2) - (gy+gh/2)) < 2) {
		colliding = true;
	}

	if (!colliding) {
		return;
	}

	player->getVelocity().y += std::fabs(player->getVelocity().y);
	
			
}