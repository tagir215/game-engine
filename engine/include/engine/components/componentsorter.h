#pragma once
#include "engine/core/gameobject.h"
#include "engine/systems/systembase.h"

class ComponentSorter : public SystemBase {
public:
	ComponentSorter(std::vector<GameObject*>& gameObjects);
	void onUpdate(float deltaTime) override;
};
