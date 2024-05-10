#include "level_2.h"

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

void Level_2::onStart()
{
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->createComponent<TransformComponent>(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	createUI();

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

	createBricks(container);

	newSystem<ScoreSystem>();
	newSystem<CharacterSystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();
}


void Level_2::createUI() 
{
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

}


void Level_2::createBricks(GameObject* container)
{
	const int G = 10;
	const int WIDTH_GAME_SCREEN = 400;
	const int COUNT_X = 13;
	const int COUNT_Y = 8;
	const int GAP_X = 3;
	const int GAP_Y = GAP_X;
	const int WIDTH = WIDTH_GAME_SCREEN / COUNT_X; 
	const int HEIGHT = WIDTH/2;
	const int START_X = WIDTH_GAME_SCREEN/-2 + WIDTH/2 + G/2; 
	const int START_Y = 50;


	glm::vec3 colors[] = {
		glm::vec3(8,91,193),
		glm::vec3(255,255,255),
		glm::vec3(8,255,8),
	};


	int bricksToSpawn[] = {
	0,0,0,0,0,0,1,0,0,0,0,0,0,
	0,0,0,1,1,1,1,3,3,3,0,0,0,
	0,0,1,2,2,2,2,2,2,3,3,0,0,
	0,0,1,2,2,2,2,2,2,3,3,0,0,
	0,1,1,1,1,2,2,2,2,3,3,3,0,
	0,1,1,1,1,2,2,2,2,3,3,3,0,
	0,1,0,0,1,0,0,0,1,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,
	};


	int i = 0;
	for (int y = COUNT_Y-1; y >= 0; --y) {
		for (int x = 0; x < COUNT_X; ++x) {
			int brickI = bricksToSpawn[i++];
			if (brickI == 0) continue;
			BrickEntity* brick = newObject<BrickEntity>(colors[brickI - 1]);
			brick->createComponent<TransformComponent>(
				glm::vec3(START_X + WIDTH * x, START_Y + HEIGHT * y, 0),
				glm::vec3(0, 0, 0),
				glm::vec3(WIDTH - GAP_X, HEIGHT - GAP_Y, 1)
			);
			container->addChild(brick);
		}
	}

}
