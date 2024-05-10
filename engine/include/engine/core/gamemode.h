#pragma once
#include "engine/core/playerstate.h"
#include "engine/core/scenemanager.h"
#include "engine/input/inputmanager.h"

class GameMode {
public:
	static GameMode& getInstance() {
		static GameMode instance;
		return instance;
	}

	PlayerState& getPlayerState(){
		return playerState;
	}
	SceneManager& getSceneManager(){
		return sceneManager;
	}
	InputManager& getInputManager(){
		return inputManager;
	}

private:
	PlayerState playerState;
	SceneManager sceneManager;
	InputManager inputManager;
};