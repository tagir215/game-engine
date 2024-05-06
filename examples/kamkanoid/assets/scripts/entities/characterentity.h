#pragma once
#include "engine/core/gameobject.h"

class CharacterEntity : public GameObject {
public:	
	CharacterEntity(Scene* scene);
	void beginPlay() override;
};