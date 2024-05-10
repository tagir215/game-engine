#pragma once
#include "engine/core/scene.h"

class Level_2 : public Scene {
public:
	Level_2(){}

private:
	void createBricks(GameObject* container);
	void createUI();
	void onStart() override;
};
