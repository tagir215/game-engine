#include "charactersystem.h"

CharacterSystem::CharacterSystem(std::vector<GameObject*>& gameObjects) :
	SystemBase(gameObjects)
{

}

void CharacterSystem::onUpdate(float deltaTime)
{
	for (GameObject* o : gameObjects) {
		const InputComponent* input = o->getInputComponent();
		if (input == nullptr) {
			continue;
		}
		if (input->isLeftPressed()) {
			o->getVelocityComponent().linearVelocity.x = -MOVEMENT_SPEED;
		}
		else if (input->isRightPressed()) {
			o->getVelocityComponent().linearVelocity.x = MOVEMENT_SPEED;
		}
		else {
			o->getVelocityComponent().linearVelocity.x = 0;
		}
	}
}
