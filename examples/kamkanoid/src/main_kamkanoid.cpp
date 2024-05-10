#include <engine/application.h>
#include "../assets/scenes/level_1.h"
#include "../assets/scenes/level_2.h"
#include "../assets/scenes/mainmenu.h"


class Kamkanoid : public engine::Application{
public:
	Kamkanoid() : engine::Application(800, 600, "Kamkanoid") {
		SceneManager::getInstance().attachScene<MainMenu>("mainmenu");
		SceneManager::getInstance().attachScene<Level_1>("level_1");
		SceneManager::getInstance().attachScene<Level_2>("level_2");
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
