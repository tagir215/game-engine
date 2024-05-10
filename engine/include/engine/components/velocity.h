#pragma once

struct VelocityComponent {
	glm::vec3 linearVelocity;
	glm::vec3 rotation;
	bool active;
	VelocityComponent() : linearVelocity(0,0,0), rotation(0,0,0), active(false) {}
	VelocityComponent(float x, float y, float z) : rotation(0,0,0), active(true) {
		linearVelocity.x = x;
		linearVelocity.y = y;
		linearVelocity.z = z;
	}
};