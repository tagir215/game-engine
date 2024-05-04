#pragma once
#include "delegate.h"

struct PhysicsComponent {
	float mass;
	float elasticity;
	float friction;
	bool collidable;
	bool gravity;
	float w;
	float h;
	bool rotates;
	Delegate<void(GameObject* thisObject, GameObject* otherObject)>onHitEvent;

	PhysicsComponent() : mass(0), collidable(false), w(0), h(0), elasticity(0), gravity(false), friction(0), rotates(false) {};
	PhysicsComponent(float mass,float collidable, float elasticity, bool gravity, float friction, float w, float h, bool rotates) 
		: mass(mass), elasticity(elasticity), collidable(collidable), w(w), h(h), gravity(gravity), friction(friction), rotates(rotates){

	}
};