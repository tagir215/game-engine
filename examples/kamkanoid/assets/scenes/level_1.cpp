#include "level_1.h"
#include "engine/collisionsystem.h"
#include "engine/gravitysystem.h"
#include "engine/movementsystem.h"
#include "../scripts/systems/charactersystem.h"
#include "../scripts/entities/characterentity.h"
#include "../scripts/entities/projectileentity.h"
#include "../scripts/entities/wallentity.h"
#include "../scripts/entities/brickentity.h"


Level_1::Level_1(float ANIMATION_TIME_FRAME) : Scene(ANIMATION_TIME_FRAME)
{
	camera = std::make_unique<Camera>(this,0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));



	CharacterEntity* character = new CharacterEntity(this);
	gameObjects.push_back(character);

	ProjectileEntity* projectile = new ProjectileEntity(this);
	gameObjects.push_back(projectile);

	WallEntity* wallR = new WallEntity(this,Transform(glm::vec3(300+15,0,0),glm::vec3(0,0,0),glm::vec3(30,480,1)));
	gameObjects.push_back(wallR);
	WallEntity* wallL = new WallEntity(this,Transform(glm::vec3(-300-15,0,0),glm::vec3(0,0,0),glm::vec3(30,480,1)));
	gameObjects.push_back(wallL);
	WallEntity* wallT = new WallEntity(this,Transform(glm::vec3(0,230,0),glm::vec3(0,0,0),glm::vec3(600,30,1)));
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
	const int START_X = -270;
	const int START_Y = 50;

	const int WIDTH_GAME_SCREEN = 600;
	const int COUNT_X = WIDTH_GAME_SCREEN / (WIDTH + GAP_X);
	const int COUNT_Y = 4;

	for (int x = 0; x < COUNT_X; ++x) {
		for (int y = 0; y < COUNT_Y; ++y) {
			Transform t(
				glm::vec3(START_X + (WIDTH + GAP_X) * x, START_Y + (HEIGHT + GAP_Y) * y, 0), 
				glm::vec3(0, 0, 0), 
				glm::vec3(WIDTH, HEIGHT, 1)
			);
			BrickEntity* brick = new BrickEntity(this,t);
			gameObjects.push_back(brick);
		}
	}

}
