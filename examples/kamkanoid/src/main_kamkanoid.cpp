#include <engine/application.h>
#include "../assets/scenes/level_1.h"

class Kamkanoid : public engine::Application{
public:
	Kamkanoid() : engine::Application(800, 600, "Kamkanoid") {
		Level_1* level = new Level_1(0.1f);
		setCurrentScene(level);
		scenes.push_back(level);
	}

	virtual void update(float deltaTime) {
		// TODO: Update logic comes here
	}

	virtual void render() {
		// TODO: Redner objects using renderer methods
	}
private:
};

int main() {
	Kamkanoid kamkanoid;
	return kamkanoid.run();
}
