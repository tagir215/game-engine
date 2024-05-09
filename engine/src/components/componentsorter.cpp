#include "engine/components/componentsorter.h"

ComponentSorter::ComponentSorter(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects) {

}

void ComponentSorter::onUpdate(float deltaTime)
{
	for (GameObject* object : gameObjects) {
		if (object->getTransformComponent() != nullptr) {
			object->getTransformComponent()->useCache = false;
		}
		if (object->getParent() != nullptr) {
			object->getTransformComponent()->setParent(object->getParent()->getTransformComponent());
		}
	}
}
