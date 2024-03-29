#include "level1.h"
#include "../game/gameobject_factories/playerfactory.h"
#include "../systems/gravitysystem.h"
#include "../systems/playerbehavior.h"
#include "../systems/gravitysystem.h"
#include "../systems/movementsystem.h"
#include "../systems/collisionsystem.h"
#include "level1factory.h"

Level1::Level1(float ANIMATION_FRAME_TIME) : Level(ANIMATION_FRAME_TIME){

	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	PlayerFactory playerFactory;
	Level1Factory levelFactory;

	gameObjects.push_back(playerFactory.buildGameObject());
	gameObjects.push_back(levelFactory.buildGround());
	gameObjects.push_back(levelFactory.buildBox());

	systems.push_back(new PlayerBehavior(gameObjects,ANIMATION_FRAME_TIME));
	systems.push_back(new GravitySystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));

}