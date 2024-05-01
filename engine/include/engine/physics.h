#pragma once

struct Physics {
	float mass;
	float elasticity;
	float friction;
	bool collidable;
	bool gravity;
	float w;
	float h;
	bool rotates;

	Physics() : mass(0), collidable(false), w(0), h(0), elasticity(0), gravity(false), friction(0), rotates(false) {};
	Physics(float mass,float collidable, float elasticity, bool gravity, float friction, float w, float h, bool rotates) 
		: mass(mass), elasticity(elasticity), collidable(collidable), w(w), h(h), gravity(gravity), friction(friction), rotates(rotates){

	}
};