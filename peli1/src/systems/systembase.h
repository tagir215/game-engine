#pragma once
#include "../game/gameobject.h"
#include "../input/inputmanager.h"
#include "../util/transformer.h"

class SystemBase {
public:
	SystemBase(std::vector<GameObject*>& gameObjects) : gameObjects(gameObjects) {};
	virtual void onUpdate(float deltaTime) = 0;
protected:
	std::vector<GameObject*> gameObjects;
	InputManager& inputManager = InputManager::getInstance();
	Transformer transformer;
};