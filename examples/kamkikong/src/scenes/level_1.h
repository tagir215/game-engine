#pragma once
#include <engine/core/scene.h>

class Level_1 : public Scene {
public:
	Level_1(){}
	void onStart() override;
	void createWall(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
};
