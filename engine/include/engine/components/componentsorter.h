#pragma once
#include "engine/core/gameobject.h"
#include "engine/systems/systembase.h"

/*
* mandatory system that each scene will automatically add to itself
* revalues each objects component hierarchies and resets or updates certain values on the components
*/
class ComponentSorter : public SystemBase {
public:
	ComponentSorter(std::vector<GameObject*>& gameObjects);
	void onUpdate(float deltaTime) override;
};
