#pragma once
#include "engine/scene.h"

class Level_1 : public Scene {
public:
	Level_1(float ANIMATION_TIME_FRAME);

private:
	void createBricks();
};