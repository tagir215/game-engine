#pragma once
#include "engine/core/gameobject.h"

class ProjectileEntity : public GameObject {
public:	
	ProjectileEntity(Object* parent);
	void beginPlay() override;
};
