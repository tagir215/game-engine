#include "mainmenusystem.h"
#include "engine/core/gamemode.h"

MainMenuSystem::MainMenuSystem(std::vector<GameObject*>& gameObjects) : SystemBase(gameObjects)
{
}

void MainMenuSystem::onUpdate(float deltaTime)
{
	if (GameMode::getInstance().getInputManager().isSpacePressed()) {
		GameMode::getInstance().getSceneManager().setScene("level_1");
	}
}
