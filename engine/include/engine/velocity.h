
struct Velocity {
	glm::vec3 linearVelocity;
	glm::vec3 rotation;
	bool active;
	Velocity() : linearVelocity(0,0,0), rotation(0,0,0), active(false) {}
	Velocity(float x, float y, float z) : rotation(0,0,0), active(true) {
		linearVelocity.x = x;
		linearVelocity.y = y;
		linearVelocity.z = z;
	}
};