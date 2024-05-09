#include "mainmenusystem.h"
#include <engine/core/scenemanager.h>

MainMenuSystem::MainMenuSystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects)
{
}

void MainMenuSystem::onUpdate(float deltaTime)
{
	if (InputManager::getInstance().isSpacePressed()) {
		SceneManager::getInstance().setScene("level_1");
	}
}
