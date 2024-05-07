#pragma once
#include <engine/core/gameobject.h>
#include <engine/util/fontserializer.h>

class UiEntity : public GameObject {
public:		
	UiEntity(Scene* scene);
	void beginPlay() override;
};
