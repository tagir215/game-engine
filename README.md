# GameEngine Project 

## Summary
This is my Game Engine project. It's being made primarly for learning purposes, but hopefully it will grow to something unique over time. 

## How to use it
1. Clone the repository and navigate to the cloned directory:
2. Create a build directory and navigate to the build directory:
3. Generate build files using CMake (cmake ..)
4. Create a custom scene class including the scene.h 
```
#pragma once
#include "engine/core/scene.h"

class Level_1 : public Scene {
public:
	Level_1() {}

private:
	void onStart() override;
};
```

5. Make the implementation for the scene you just made. Use the newObject method provided by the scene to create objects, and use the newSystem method to create the systems you want to use. 
```
#include "level_1.h"
#include "engine/systems/collisionsystem.h"
#include "engine/systems/gravitysystem.h"
#include "engine/systems/movementsystem.h"
#include "engine/components/componentsorter.h"
#include "../scripts/systems/scoresystem.h"
#include "../scripts/systems/charactersystem.h"
#include "../scripts/entities/characterentity.h"
#include "../scripts/entities/projectileentity.h"
#include "../scripts/entities/wallentity.h"
#include "../scripts/entities/brickentity.h"
#include "../scripts/entities/uientity.h"

void Level_1::onStart()
{
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->createComponent<TransformComponent>(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    //example for creating an ui

	GameObject* ui = newObject<GameObject>();
	ui->createComponent<TransformComponent>(glm::vec3(240, 100, 0));
	
	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";

	GameObject* title = newObject<GameObject>();
	title->createComponent<TransformComponent>(glm::vec3(0, 100, 0), glm::vec3(0, 0, 0), glm::vec3(0.4f, 0.4f, 0));
	title->createComponent<TextComponent>(fontDataPath, fontImagePath);
	title->getTextComponent()->setText("KAMKANOID");
	ui->addChild(title);

	GameObject* score = newObject<GameObject>();
	score->createComponent<TransformComponent>(glm::vec3(0, 20, 0), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0));
	score->createComponent<TextComponent>(fontDataPath,fontImagePath);
	score->getTextComponent()->setText("SCORE");
	ui->addChild(score);

	GameObject* scoreNum = newObject<GameObject>();
	scoreNum->createComponent<TransformComponent>(glm::vec3(0, -0, 0), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0));
	scoreNum->createComponent<TextComponent>(fontDataPath, fontImagePath);
	scoreNum->getTextComponent()->setText("00");
	scoreNum->getTags().insert("score");
	ui->addChild(scoreNum);

	GameObject* highScore = newObject<GameObject>();
	highScore->createComponent<TransformComponent>(glm::vec3(0, -40, 0), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0));
	highScore->createComponent<TextComponent>(fontDataPath,fontImagePath);
	highScore->getTextComponent()->setText("HIGH SCORE");
	ui->addChild(highScore);

	GameObject* highScoreNum = newObject<GameObject>();
	highScoreNum->createComponent<TransformComponent>(glm::vec3(0, -60, 0), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0));
	highScoreNum->createComponent<TextComponent>(fontDataPath, fontImagePath);
	highScoreNum->getTextComponent()->setText("00");
	highScoreNum->getTags().insert("highscore");
	ui->addChild(highScoreNum);


	GameObject* logoLicense = newObject<GameObject>();
	logoLicense->createComponent<TransformComponent>(glm::vec3(0, -200, 0), glm::vec3(0, 0, 0), glm::vec3(0.3f, 0.3f, 0));
	logoLicense->createComponent<TextComponent>(fontDataPath, fontImagePath);
	logoLicense->getTextComponent()->setText("KAMK");
	ui->addChild(logoLicense);

    //examples creating objects using custom made game objects inheriting the GameObject class. 

	newObject<CharacterEntity>();
	newObject<ProjectileEntity>();

	GameObject* container = newObject<GameObject>();
	container->createComponent<TransformComponent>(glm::vec3(-50, -20, 0));

	const float X = 200;
	const float G = 10;
	const float H = 450;

	WallEntity* wallR = newObject<WallEntity>();
	wallR->createComponent<TransformComponent>(glm::vec3(X, 0, 0), glm::vec3(0, 0, 0), glm::vec3(G, H, 1));
	WallEntity* wallL = newObject<WallEntity>();
	wallL->createComponent<TransformComponent>(glm::vec3(-X, 0, 0), glm::vec3(0, 0, 0), glm::vec3(G, H, 1));
	WallEntity* wallT = newObject<WallEntity>();
	wallT->createComponent<TransformComponent>(glm::vec3(0, H / 2, 0), glm::vec3(0, 0, 0), glm::vec3(X * 2 + G, G, 1));

	WallEntity* wallB = newObject<WallEntity>();
	wallB->createComponent<TransformComponent>(glm::vec3(0, -H / 2, 0), glm::vec3(0, 0, 0), glm::vec3(X * 2 + G, G, 1));
	wallB->getTags().insert("bottomwall");

	container->addChild(wallR);
	container->addChild(wallL);
	container->addChild(wallT);
	container->addChild(wallB);

    // examples on how to create systems using systems provided by the engine and also custom made systems inheriting the SystemBase class

	newSystem<ScoreSystem>();
	newSystem<CharacterSystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();
}

```

6. include the application.h and create a custom Application class where you can attach your scnenes
```
#include <engine/application.h>
#include "scenes/level_1.h"
#include "scenes/level_2.h"
#include "scenes/mainmenu.h"


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
```


