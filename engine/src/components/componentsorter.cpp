#include "engine/components/componentsorter.h"

ComponentSorter::ComponentSorter(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects) {

}

void ComponentSorter::onUpdate(float deltaTime)
{
	for (GameObject* object : gameObjects) {
		GameObject* parent = object->getParent();
		if (parent != nullptr) {
			object->getTransformComponent()->setParent(parent->getTransformComponent());
		}
	}
}
