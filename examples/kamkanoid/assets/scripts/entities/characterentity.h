#pragma once
#include "engine/gameobject.h"

class CharacterEntity : public GameObject {
public:	
	CharacterEntity(Scene* scene);
	void beginPlay() override;
};