#include "../include/engine/movementsystem.h"

void MovementSystem::onUpdate(float deltaTime) {
	for (GameObject* object : gameObjects) {
		transformer.translate(
			object->getTransform(), 
			object->getVelocity().linearVelocity.x*deltaTime, 
			object->getVelocity().linearVelocity.y*deltaTime, 
			object->getVelocity().linearVelocity.z*deltaTime
		);
		transformer.rotate(object->getTransform(),
			object->getVelocity().rotation.x*deltaTime,
			object->getVelocity().rotation.y*deltaTime,
			object->getVelocity().rotation.z*deltaTime
		);
	}
}