#pragma once
#include "gameobject.h"
#include "inputmanager.h"

class SystemBase {
public:
	SystemBase(std::vector<GameObject*>& gameObjects) : gameObjects(gameObjects) {};
	virtual void onUpdate(float deltaTime) = 0;
protected:
	std::vector<GameObject*> gameObjects;
	InputManager& inputManager = InputManager::getInstance();
};