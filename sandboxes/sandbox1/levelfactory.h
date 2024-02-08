#pragma once
#include <engine/gameobject.h>

class LevelFactory {
public:
	virtual GameObject* buildGround() = 0;
	virtual GameObject* buildBox() = 0;
};