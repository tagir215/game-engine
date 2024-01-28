#include "gravitysystem.h"

void GravitySystem::onUpdate(float deltaTime){
	for (GameObject* object : gameObjects) {
		if (object->getMass().value != 0) {
			transformer.translate(object->getTransform(), 0, -0.1f, 0);
		}
	}
}
