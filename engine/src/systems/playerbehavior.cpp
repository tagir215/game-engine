#include "../include/engine/playerbehavior.h"


void PlayerBehavior::onUpdate(float deltaTime) {

	for (GameObject* o : gameObjects) {
		if (o->getInputComponent() != nullptr) {
			inputManager = InputManager::getInstance();
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

	if (animationFrame && (inputManager.isLeftPressed() || inputManager.isRightPressed())) {
		object->getTexture()->nextFrame();
		object->getMesh()->updateTextureBuffer(object->getTexture()->getTextureCoords());
	}
}

void PlayerBehavior::updatePlayerPosition(GameObject* object,float deltaTime){
	if (inputManager.isLeftPressed()) {
		object->getVelocity().linearVelocity.x = -WALKING_SPEED;
		transformer.setRotation(object->getTransform(), 0, 180, 0);
	}
	else if (inputManager.isRightPressed()) {
		object->getVelocity().linearVelocity.x = WALKING_SPEED;
		transformer.setRotation(object->getTransform(), 0, 0, 0);
	}
	else {
		object->getVelocity().linearVelocity.x = 0;
	}

	if (inputManager.isSpacePressed()) {
		object->getVelocity().linearVelocity.y = 500.0f;
	}
}

