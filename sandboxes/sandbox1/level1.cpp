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
	camera->addTransformComponent(new TransformComponent(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	PlayerFactory playerFactory;
	Level1Factory levelFactory;

	playerFactory.buildGameObject(this,
		new TransformComponent(glm::vec3(-100, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));

	levelFactory.buildGround(this,
		new TransformComponent(glm::vec3(10, -100, 0), glm::vec3(0, 0, 0), glm::vec3(500, 50, 1)),100000000000000000);

	levelFactory.buildBox(this,
		new TransformComponent(glm::vec3(0, 10, 1), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)),100);

	levelFactory.buildBox(this,
		new TransformComponent(glm::vec3(100, 100, 1), glm::vec3(0, 0, 0), glm::vec3(60, 60, 1)),500000);

	levelFactory.buildBox(this,
		new TransformComponent(glm::vec3(50, 200, 1), glm::vec3(0, 0, 0), glm::vec3(200, 30, 1)),300);

	newSystem<PlayerBehavior>(ANIMATION_FRAME_TIME);
	newSystem<GravitySystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();

}