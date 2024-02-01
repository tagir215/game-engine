
struct Velocity {
	float x;
	float y;
	float z;
	bool active;
	Velocity() : x(0), y(0), z(0), active(false) {}
	Velocity(float x, float y, float z) : x(x), y(y), z(z), active(true) {
	}
};