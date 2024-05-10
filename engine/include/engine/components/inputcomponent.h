#pragma once
#include <GLFW/glfw3.h>
#include "engine/core/gamemode.h"

class InputComponent {
public:
	InputComponent();

	bool isUpPressed() const { return GameMode::getInstance().getInputManager().isUpPressed(); };
	bool isDownPressed() const { return GameMode::getInstance().getInputManager().isDownPressed(); };
	bool isLeftPressed() const { return GameMode::getInstance().getInputManager().isLeftPressed(); };
	bool isRightPressed() const { return GameMode::getInstance().getInputManager().isRightPressed(); };
	bool isSpacePressed() const { return GameMode::getInstance().getInputManager().isSpacePressed(); };
};
