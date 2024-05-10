#pragma once
#include "engine/core/delegate.h"

struct PhysicsComponent {
	float mass;
	float elasticity;
	float friction;
	bool collidable;
	bool gravity;
	glm::vec3 boundingVolume;
	bool rotates;
	Delegate<void(GameObject* thisObject, GameObject* otherObject)>onHitEvent;

	PhysicsComponent() : mass(0), collidable(false), boundingVolume(glm::vec3(0,0,0)), elasticity(0), gravity(false), friction(0), rotates(false) {};
	PhysicsComponent(float mass, bool collidable, float elasticity, bool gravity, float friction, glm::vec3 boundingVolume, bool rotates) 
		: mass(mass), elasticity(elasticity), collidable(collidable), boundingVolume(boundingVolume), gravity(gravity), friction(friction), rotates(rotates) {

	}
};