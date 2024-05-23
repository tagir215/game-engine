#include <engine/components/tilemap.h>
#include <iostream>
#include <engine/application.h>
#include "scenes/level_1.h"

class Kamkikong : public engine::Application{
public:
	Kamkikong() : engine::Application(800, 600, "Kamkikong") {
		sceneManager.attachScene<Level_1>("level_1");
	}

private:
};

int main() {
	Kamkikong kamkikong;
	return kamkikong.run();
}
