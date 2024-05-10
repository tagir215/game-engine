#pragma once
#include "engine/core/scene.h"

class Level_1 : public Scene {
public:
	Level_1() {}

private:
	void createBricks(GameObject* container);
	void createUI();
	void onStart() override;
};