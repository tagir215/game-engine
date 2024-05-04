#pragma once
#include "engine/gameobject.h"

class ProjectileEntity : public GameObject {
public:	
	ProjectileEntity(Scene* scene);
	void beginPlay() override;
};
