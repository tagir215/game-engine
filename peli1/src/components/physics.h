#pragma once

struct Physics {
	float mass = 0;
	bool collidable = false;
	float w;
	float h;

	Physics() {};
	Physics(float mass,float collidable,float w, float h) : mass(mass), collidable(collidable), w(w), h(h){

	}
};