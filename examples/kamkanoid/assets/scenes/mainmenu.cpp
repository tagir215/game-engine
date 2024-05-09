#include "mainmenu.h"
#include "../scripts/systems/mainmenusystem.h"

MainMenu::MainMenu() 
{
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->createComponent<TransformComponent>(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";

	GameObject* title = newObject<GameObject>();
	title->createComponent<TransformComponent>(glm::vec3(0, 100, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	title->createComponent<TextComponent>(fontDataPath, fontImagePath);
	title->getTextComponent()->setText("KAMKANOID");

	GameObject* prompt = newObject<GameObject>();
	prompt->createComponent<TransformComponent>(glm::vec3(0, 10, 0), glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 1));
	prompt->createComponent<TextComponent>(fontDataPath, fontImagePath);
	prompt->getTextComponent()->setText("PUSH SPACE TO START");

	newSystem<MainMenuSystem>();
}