#pragma once
#include <engine/systems/systembase.h>

class ScoreSystem : public SystemBase {
public:
	ScoreSystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects) {}
	void onUpdate(float deltaTime) override;
private:
	int oldScore = 0;
	int currentScore = 0;
	int highScore = 0;
};
