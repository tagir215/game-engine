#pragma once

#include "levelfactory.h"

class Level1Factory : public LevelFactory {
public:
	virtual GameObject* buildGround() override;
	virtual GameObject* buildBox() override;
};