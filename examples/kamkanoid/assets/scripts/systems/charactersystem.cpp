#include "charactersystem.h"

CharacterSystem::CharacterSystem(std::vector<GameObject*>& gameObjects) :
	SystemBase(gameObjects)
{

}

void CharacterSystem::onUpdate(float deltaTime)
{
	for (GameObject* o : gameObjects) {
		InputComponent* input = o->getInputComponent();
		if (input == nullptr) {
			continue;
		}
		InputManager inputManager = InputManager::getInstance();
		if (inputManager.isLeftPressed()) {
			o->getVelocity().linearVelocity.x = -MOVEMENT_SPEED;
		}
		else if (inputManager.isRightPressed()) {
			o->getVelocity().linearVelocity.x = MOVEMENT_SPEED;
		}
		else {
			o->getVelocity().linearVelocity.x = 0;
		}
	}
}
