#include "level_1.h"
#include "engine/systems/collisionsystem.h"
#include "engine/systems/gravitysystem.h"
#include "engine/systems/movementsystem.h"
#include "../scripts/systems/charactersystem.h"
#include "../scripts/entities/characterentity.h"
#include "../scripts/entities/projectileentity.h"
#include "../scripts/entities/wallentity.h"
#include "../scripts/entities/brickentity.h"
#include "../scripts/entities/uientity.h"


Level_1::Level_1() 
{
	camera = std::make_unique<Camera>(this,0, 640, 0, 480);
	camera->addTransformComponent(TransformComponent(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	UiEntity* entity = new UiEntity(this);
	gameObjects.push_back(entity);

	CharacterEntity* character = new CharacterEntity(this);
	gameObjects.push_back(character);

	ProjectileEntity* projectile = new ProjectileEntity(this);
	gameObjects.push_back(projectile);

	WallEntity* wallR = new WallEntity(this,TransformComponent(glm::vec3(250 + 10,0,0),glm::vec3(0,0,0),glm::vec3(15,470,1)));
	gameObjects.push_back(wallR);
	WallEntity* wallL = new WallEntity(this,TransformComponent(glm::vec3(-250 - 10,0,0),glm::vec3(0,0,0),glm::vec3(15,470,1)));
	gameObjects.push_back(wallL);
	WallEntity* wallT = new WallEntity(this,TransformComponent(glm::vec3(0,230,0),glm::vec3(0,0,0),glm::vec3(510,15,1)));
	gameObjects.push_back(wallT);

	createBricks();
	systems.push_back(new CharacterSystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));

}

void Level_1::createBricks()
{
	const int WIDTH = 40; 
	const int HEIGHT = 18;
	const int GAP_X = 5;
	const int GAP_Y = 5;
	const int START_X = -250 + 25;
	const int START_Y = 50;

	const int WIDTH_GAME_SCREEN = 500;
	const int COUNT_X = WIDTH_GAME_SCREEN / (WIDTH + GAP_X);
	const int COUNT_Y = 6;

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
			TransformComponent t(
				glm::vec3(START_X + (WIDTH + GAP_X) * x, START_Y + (HEIGHT + GAP_Y) * y, 0), 
				glm::vec3(0, 0, 0), 
				glm::vec3(WIDTH, HEIGHT, 1)
			);
			BrickEntity* brick = new BrickEntity(this,t,rowColors[y]);
			gameObjects.push_back(brick);
		}
	}

}
