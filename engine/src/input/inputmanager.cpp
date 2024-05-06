#include "engine/input/inputmanager.h"

void InputManager::update(int key, bool b) {
	switch (key) {
	case GLFW_KEY_LEFT: left = b; break;
	case GLFW_KEY_RIGHT: right = b; break;
	case GLFW_KEY_UP: up = b; break;
	case GLFW_KEY_DOWN: down = b; break;
	case GLFW_KEY_SPACE: space = b; break;
	}
}

void InputManager::updatePress(int key){
	update(key, true);
}

void InputManager::updateRelease(int key){
	update(key, false);
}
