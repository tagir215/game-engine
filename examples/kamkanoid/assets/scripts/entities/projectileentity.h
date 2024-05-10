#pragma once
#include "engine/core/gameobject.h"

class ProjectileEntity : public GameObject {
public:	
	ProjectileEntity(Scene* scene);
	void beginPlay() override;
	bool updateScore = false;
};
