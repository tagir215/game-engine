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
	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));



	CharacterEntity* character = new CharacterEntity();
	gameObjects.push_back(character);

	ProjectileEntity* projectile = new ProjectileEntity();
	gameObjects.push_back(projectile);

	WallEntity* wall = new WallEntity(Transform(glm::vec3(200,0,0),glm::vec3(0,0,0),glm::vec3(10,400,1)));
	gameObjects.push_back(wall);

	BrickEntity* brick = new BrickEntity(Transform(glm::vec3(0, 400, 0), glm::vec3(0, 0, 0), glm::vec3(100, 40, 1)));
	gameObjects.push_back(brick);


	systems.push_back(new CharacterSystem(gameObjects));
	systems.push_back(new GravitySystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));
}
