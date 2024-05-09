#pragma once
#include "engine/systems/systembase.h"

class MainMenuSystem : public SystemBase {
public:
	MainMenuSystem(std::vector<GameObject*>& gameObjects);
	void onUpdate(float deltaTime) override;
private:
};
