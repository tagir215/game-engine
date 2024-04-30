#include "level1.h"
#include "playerfactory.h"
#include <engine/gravitysystem.h>
#include <engine/playerbehavior.h>
#include <engine/gravitysystem.h>
#include <engine/movementsystem.h>
#include <engine/collisionsystem.h>
#include <engine/texturemanager.h>
#include "level1factory.h"

Level1::Level1(float ANIMATION_FRAME_TIME) : Scene(ANIMATION_FRAME_TIME){

	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	PlayerFactory playerFactory;
	Level1Factory levelFactory;

	Transform transformP = Transform(glm::vec3(-100, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1));
	gameObjects.push_back(playerFactory.buildGameObject(transformP));

	Transform transformG = Transform(Transform(glm::vec3(10, -100, 0), glm::vec3(0, 0, 0), glm::vec3(500, 50, 1)));
	gameObjects.push_back(levelFactory.buildGround(transformG,100000000000000000));

	Transform transformB = Transform(Transform(glm::vec3(0, 10, 1), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	gameObjects.push_back(levelFactory.buildBox(transformB,100));

	Transform transformB2 = Transform(Transform(glm::vec3(100, 100, 1), glm::vec3(0, 0, 0), glm::vec3(60, 60, 1)));
	gameObjects.push_back(levelFactory.buildBox(transformB2,500000));

	Transform transformB3 = Transform(Transform(glm::vec3(50, 200, 1), glm::vec3(0, 0, 0), glm::vec3(200, 30, 1)));
	gameObjects.push_back(levelFactory.buildBox(transformB3,300));

	systems.push_back(new PlayerBehavior(gameObjects,ANIMATION_FRAME_TIME));
	systems.push_back(new GravitySystem(gameObjects));
	systems.push_back(new CollisionSystem(gameObjects));
	systems.push_back(new MovementSystem(gameObjects));

}