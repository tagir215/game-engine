#include "../include/engine/movementsystem.h"


void MovementSystem::onUpdate(float deltaTime) {
	for (GameObject* object : gameObjects) {
		transformer.translate(
			object->getTransform(), 
			object->getVelocity().velocity.x*deltaTime, 
			object->getVelocity().velocity.y*deltaTime, 
			object->getVelocity().velocity.z*deltaTime
		);
		transformer.rotate(object->getTransform(),
			object->getVelocity().rotation.x*deltaTime,
			object->getVelocity().rotation.y*deltaTime,
			object->getVelocity().rotation.z*deltaTime
		);
	}
}