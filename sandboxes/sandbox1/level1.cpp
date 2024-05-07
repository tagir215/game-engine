#include "level1.h"
#include "playerfactory.h"
#include <engine/systems/gravitysystem.h>
#include <engine/systems/playerbehavior.h>
#include <engine/systems/gravitysystem.h>
#include <engine/systems/movementsystem.h>
#include <engine/systems/collisionsystem.h>
#include <engine/graphics/texturemanager.h>
#include "level1factory.h"

Level1::Level1() {

	camera = std::make_unique<Camera>(this,0, 640, 0, 480);
	camera->addTransformComponent(TransformComponent(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	PlayerFactory playerFactory;
	Level1Factory levelFactory;

	TransformComponent transformP = TransformComponent(glm::vec3(-100, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1));
	gameObjects.push_back(playerFactory.buildGameObject(this,transformP));

	TransformComponent transformG = TransformComponent(TransformComponent(glm::vec3(10, -100, 0), glm::vec3(0, 0, 0), glm::vec3(500, 50, 1)));
	gameObjects.push_back(levelFactory.buildGround(this,transformG,100000000000000000));

	TransformComponent transformB = TransformComponent(TransformComponent(glm::vec3(0, 10, 1), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	gameObjects.push_back(levelFactory.buildBox(this,transformB,100));

	TransformComponent transformB2 = TransformComponent(TransformComponent(glm::vec3(100, 100, 1), glm::vec3(0, 0, 0), glm::vec3(60, 60, 1)));
	gameObjects.push_back(levelFactory.buildBox(this,transformB2,500000));

	TransformComponent transformB3 = TransformComponent(TransformComponent(glm::vec3(50, 200, 1), glm::vec3(0, 0, 0), glm::vec3(200, 30, 1)));
	gameObjects.push_back(levelFactory.buildBox(this,transformB3,300));

	systems.push_back(new PlayerBehavior(gameObjects,ANIMATION_FRAME_TIME));
	systems.push_back(new GravitySystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));

}