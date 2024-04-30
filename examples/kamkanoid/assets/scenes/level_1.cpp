#include "level_1.h"
#include "engine/collisionsystem.h"
#include "engine/gravitysystem.h"
#include "engine/movementsystem.h"
#include "../scripts/systems/charactersystem.h"
#include "../scripts/entities/characterentity.h"

Level_1::Level_1(float ANIMATION_TIME_FRAME) : Scene(ANIMATION_TIME_FRAME)
{
	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	CharacterEntity* character = new CharacterEntity();
	gameObjects.push_back(character);

	systems.push_back(new CharacterSystem(gameObjects));
	systems.push_back(new GravitySystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));
}
