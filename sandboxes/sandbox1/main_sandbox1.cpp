#include <engine/application.h>
#include "level1.h"

class MyGame : public engine::Application {
public:
	MyGame() : engine::Application(800, 600, "Sandbox1") {
		GameMode::getInstance().getSceneManager().attachScene<Level1>("level1");
	}

private:
};

int main() {
	MyGame game;
	return game.run();
}
