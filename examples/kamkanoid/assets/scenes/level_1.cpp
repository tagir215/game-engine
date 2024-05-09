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


Level_1::Level_1() 
{
	camera = std::make_unique<Camera>(this,0, 640, 0, 480);
	camera->addTransformComponent(new TransformComponent(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	createUI();

	newObject<CharacterEntity>();
	newObject<ProjectileEntity>();

	GameObject* container = newObject<GameObject>();
	container->addTransformComponent(new TransformComponent(glm::vec3(-50, -20, 0)));

	const float X = 200;
	const float G = 10;
	const float H = 450;

	WallEntity* wallR = newObject<WallEntity>(new TransformComponent(glm::vec3(X,0, 0), glm::vec3(0, 0, 0), glm::vec3(G, H, 1)));
	WallEntity* wallL = newObject<WallEntity>(new TransformComponent(glm::vec3(-X, 0, 0), glm::vec3(0, 0, 0), glm::vec3(G, H, 1)));
	WallEntity* wallT = newObject<WallEntity>(new TransformComponent(glm::vec3(0, H/2, 0), glm::vec3(0, 0, 0), glm::vec3(X*2 + G, G, 1)));
	container->addChild(wallR);
	container->addChild(wallL);
	container->addChild(wallT);

	createBricks(container);

	newSystem<ComponentSorter>();
	newSystem<ScoreSystem>();
	newSystem<CharacterSystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();

}

void Level_1::createUI() 
{
	GameObject* ui = newObject<GameObject>();
	ui->addTransformComponent(new TransformComponent(glm::vec3(240, 100, 0)));
	
	FontSerializer fontSerializer;
	std::string fontDataPath = "../../../../engine/assets/fonts/Monospaced.fnt";
	std::string fontImagePath = "../../../../engine/assets/fonts/Monospaced.png";

	GameObject* title = newObject<GameObject>();
	title->addTransformComponent(new TransformComponent(glm::vec3(0,100,0),glm::vec3(0,0,0),glm::vec3(0.4f,0.4f,0)));
	TextComponent* titleText = new TextComponent(fontDataPath,fontImagePath);
	titleText->setText("KAMKANOID");
	title->addTextComponent(titleText);
	ui->addChild(title);

	GameObject* score = newObject<GameObject>();
	score->addTransformComponent(new TransformComponent(glm::vec3(0,20,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* scoreText = new TextComponent(fontDataPath,fontImagePath);
	scoreText->setText("SCORE");
	score->addTextComponent(scoreText);
	ui->addChild(score);

	GameObject* scoreNum = newObject<GameObject>();
	scoreNum->addTransformComponent(new TransformComponent(glm::vec3(0,-0,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* scoreNumText = new TextComponent(fontDataPath,fontImagePath);
	scoreNumText->setText("00");
	scoreNum->addTextComponent(scoreNumText);
	scoreNum->getTags().insert("score");
	ui->addChild(scoreNum);

	GameObject* highScore = newObject<GameObject>();
	highScore->addTransformComponent(new TransformComponent(glm::vec3(0,-40,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* highScoreText = new TextComponent(fontDataPath,fontImagePath);
	highScoreText->setText("HIGH SCORE");
	highScore->addTextComponent(highScoreText);
	ui->addChild(highScore);

	GameObject* highScoreNum = newObject<GameObject>();
	highScoreNum->addTransformComponent(new TransformComponent(glm::vec3(0,-60,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* highScoreNumText = new TextComponent(fontDataPath,fontImagePath);
	highScoreNumText->setText("00");
	highScoreNum->addTextComponent(highScoreNumText);
	highScoreNum->getTags().insert("highscore");
	ui->addChild(highScoreNum);


	GameObject* logoLicense = newObject<GameObject>();
	logoLicense->addTransformComponent(new TransformComponent(glm::vec3(0,-200,0),glm::vec3(0,0,0),glm::vec3(0.3f,0.3f,0)));
	TextComponent* logoText = new TextComponent(fontDataPath,fontImagePath);
	logoText->setText("KAMK");
	logoLicense->addTextComponent(logoText);
	ui->addChild(logoLicense);

}

void Level_1::createBricks(GameObject* container)
{
	const int G = 10;
	const int WIDTH_GAME_SCREEN = 400;
	const int COUNT_X = 13;
	const int COUNT_Y = 6;
	const int GAP_X = 3;
	const int GAP_Y = GAP_X;
	const int WIDTH = WIDTH_GAME_SCREEN / COUNT_X; 
	const int HEIGHT = WIDTH/2;
	const int START_X = WIDTH_GAME_SCREEN/-2 + WIDTH/2 + G/2; 
	const int START_Y = 50;



	glm::vec3 rowColors[] = {
		glm::vec3(0,255,0),
		glm::vec3(255,0,255),
		glm::vec3(0,112,255),
		glm::vec3(255,255,0),
		glm::vec3(255,0,0),
		glm::vec3(157,157,157),
	};

	for (int x = 0; x < COUNT_X; ++x) {
		for (int y = 0; y < COUNT_Y; ++y) {
			TransformComponent* t = new TransformComponent(
				glm::vec3(START_X + WIDTH * x, START_Y + HEIGHT * y, 0), 
				glm::vec3(0, 0, 0), 
				glm::vec3(WIDTH-GAP_X, HEIGHT-GAP_Y, 1)
			);
			BrickEntity* brick = newObject<BrickEntity>(t, rowColors[y]);
			container->addChild(brick);
		}
	}

}
