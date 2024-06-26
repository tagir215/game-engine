#include <engine/application.h>
#include "../assets/scenes/level_1.h"
#include "../assets/scenes/level_2.h"
#include "../assets/scenes/mainmenu.h"


class Kamkanoid : public engine::Application{
public:
	Kamkanoid() : engine::Application(800, 600, "Kamkanoid") {
		sceneManager.attachScene<MainMenu>("mainmenu");
		sceneManager.attachScene<Level_1>("level_1");
		sceneManager.attachScene<Level_2>("level_2");
	}

private:
};

int main() {
	Kamkanoid kamkanoid;
	return kamkanoid.run();
}
