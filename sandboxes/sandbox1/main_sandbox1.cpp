#include <engine/application.h>
#include "level1.h"

class MyGame : public engine::Application {
public:
	MyGame() : engine::Application(800, 600, "Sandbox1") {
		SceneManager::getInstance().createScene<Level1>("level1");
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
