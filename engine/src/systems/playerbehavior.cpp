#include "engine/systems/playerbehavior.h"
#include "engine/core/gamemode.h"


void PlayerBehavior::onUpdate(float deltaTime) {

	for (GameObject* o : gameObjects) {
		if (o->getInputComponent() != nullptr) {
			updateAnimation(o,deltaTime);
			updatePlayerPosition(o,deltaTime);
		}
	}
}

void PlayerBehavior::updateAnimation(GameObject* object, float deltaTime){
	bool animationFrame = false;
	cumilatedTime += deltaTime;
	if (cumilatedTime >= ANIMATION_FRAME_TIME) {
		animationFrame = true;
		cumilatedTime = 0;
	}

	InputComponent* inputComponent = object->getInputComponent();
	if (animationFrame && (inputComponent->isLeftPressed() || inputComponent->isRightPressed())) {
		object->getTextureComponent()->nextFrame();
		object->getMeshComponent()->updateTextureBuffer(object->getTextureComponent()->getTextureCoords());
	}
}

void PlayerBehavior::updatePlayerPosition(GameObject* object,float deltaTime){
	InputComponent* inputComponent = object->getInputComponent();
	if (inputComponent->isLeftPressed()) {
		object->getVelocityComponent().linearVelocity.x = -WALKING_SPEED;
		transformer.setRotation(object->getTransformComponent(), 0, 180, 0);
	}
	else if (inputComponent->isRightPressed()) {
		object->getVelocityComponent().linearVelocity.x = WALKING_SPEED;
		transformer.setRotation(object->getTransformComponent(), 0, 0, 0);
	}
	else {
		object->getVelocityComponent().linearVelocity.x = 0;
	}

	if (inputComponent->isSpacePressed()) {
		object->getVelocityComponent().linearVelocity.y = 500.0f;
	}
}

