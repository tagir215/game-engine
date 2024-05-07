#pragma once
#include "engine/core/gameobject.h"

class CharacterEntity : public GameObject {
public:	
	CharacterEntity(Object* parent);
	void beginPlay() override;
};