#pragma once
#include <GLFW/glfw3.h>

class InputManager {
public:
	static InputManager& getInstance() {
		static InputManager instance;
		return instance;
	}

	void updatePress(int key);
	void updateRelease(int key);

	bool isUpPressed() const { return up; };
	bool isDownPressed() const { return down; };
	bool isLeftPressed() const { return left; };
	bool isRightPressed() const { return right; };
	bool isSpacePressed() const { return space; };
	
private:

	InputManager() {

	}

	void update(int key, bool b);

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool space = false;
};