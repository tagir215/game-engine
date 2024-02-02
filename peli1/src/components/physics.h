#pragma once

struct Physics {
	float mass;
	float elasticity;
	bool collidable;
	float w;
	float h;

	Physics() : mass(0), collidable(false), w(0), h(0), elasticity(0) {};
	Physics(float mass,float collidable, float elasticity, float w, float h) : mass(mass), collidable(collidable), w(w), h(h){

	}
};