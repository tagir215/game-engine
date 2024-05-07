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
			o->getVelocityComponent().linearVelocity.x = -MOVEMENT_SPEED;
		}
		else if (inputManager.isRightPressed()) {
			o->getVelocityComponent().linearVelocity.x = MOVEMENT_SPEED;
		}
		else {
			o->getVelocityComponent().linearVelocity.x = 0;
		}
	}
}
