#pragma once
#include "../game/gameobject.h"

class LevelFactory {
public:
	virtual GameObject* buildGround() = 0;
	virtual GameObject* buildBox() = 0;
};