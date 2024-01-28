#pragma once
#include "systembase.h"

class PlayerBehavior : public SystemBase {
public:
	PlayerBehavior(std::vector<GameObject*>& gameObjects, float ANIMATION_FRAME_TIME) : 
		SystemBase(gameObjects), ANIMATION_FRAME_TIME(ANIMATION_FRAME_TIME) {};
	void onUpdate(float deltaTime) override;
private:
	const float ANIMATION_FRAME_TIME;
	float cumilatedTime = 0;
	const float	WALKING_SPEED = 100.0f;

	void updateAnimation(GameObject* object, float deltaTime);
	void updatePlayerPosition(GameObject* object,float deltaTime);
};