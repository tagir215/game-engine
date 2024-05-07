#include "engine/systems/movementsystem.h"

void MovementSystem::onUpdate(float deltaTime) {
	for (GameObject* object : gameObjects) {
		if (object->getTransformComponent() == nullptr) {
			continue;
		}
		transformer.translate(
			object->getTransformComponent(), 
			object->getVelocityComponent().linearVelocity.x*deltaTime, 
			object->getVelocityComponent().linearVelocity.y*deltaTime, 
			object->getVelocityComponent().linearVelocity.z*deltaTime
		);
		transformer.rotate(object->getTransformComponent(),
			object->getVelocityComponent().rotation.x*deltaTime,
			object->getVelocityComponent().rotation.y*deltaTime,
			object->getVelocityComponent().rotation.z*deltaTime
		);
	}
}