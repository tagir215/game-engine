#include <engine/application.h>
#include "level1.h"

class MyGame : public engine::Application {
public:
	MyGame() : engine::Application(800, 600, "Sandbox1") {
		Level1* level = new Level1(0.1f);
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
	MyGame game;
	return game.run();
}
