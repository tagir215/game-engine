#include "mainmenu.h"
#include "../scripts/systems/mainmenusystem.h"

MainMenu::MainMenu() 
{
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->addTransformComponent(new TransformComponent(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";

	GameObject* title = newObject<GameObject>();
	title->addTransformComponent(new TransformComponent(glm::vec3(0, 100, 0),glm::vec3(0,0,0),glm::vec3(1,1,1)));
	TextComponent* textComponent = new TextComponent(fontDataPath,fontImagePath);
	textComponent->setText("KAMKANOID");
	title->addTextComponent(textComponent);

	GameObject* prompt = newObject<GameObject>();
	prompt->addTransformComponent(new TransformComponent(glm::vec3(0, 10, 0),glm::vec3(0,0,0),glm::vec3(0.5f,0.5f,1)));
	TextComponent* promptText = new TextComponent(fontDataPath,fontImagePath);
	promptText->setText("PUSH SPACE TO START");
	prompt->addTextComponent(promptText);

	newSystem<MainMenuSystem>();
}