
struct Velocity {
	glm::vec3 velocity;
	glm::vec3 rotation;
	bool active;
	Velocity() : velocity(0,0,0), rotation(0,0,0), active(false) {}
	Velocity(float x, float y, float z) : rotation(0,0,0), active(true) {
		velocity.x = x;
		velocity.y = y;
		velocity.z = z;
	}
};