#include "level1.h"
#include <engine/systems/gravitysystem.h>
#include <engine/systems/playerbehavior.h>
#include <engine/systems/gravitysystem.h>
#include <engine/systems/movementsystem.h>
#include <engine/systems/collisionsystem.h>
#include <engine/graphics/texturemanager.h>
#include "level1factory.h"

void Level1::onStart()
{
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->createComponent<TransformComponent>(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Level1Factory levelFactory;
	//levelFactory.buildBox(this, 2000, glm::vec3(-100, 20, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1));
	//levelFactory.buildBox(this, 2000, glm::vec3(100, 20, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1));
	//levelFactory.buildBox(this, 7000, glm::vec3(100, 200, 0), glm::vec3(0, 0, 0), glm::vec3(60, 60, 1));
	//levelFactory.buildBox(this, 600, glm::vec3(0, 100, 0), glm::vec3(0, 0, 0), glm::vec3(300, 20, 1));
	//levelFactory.buildBox(this, 100, glm::vec3(-20, 200, 0), glm::vec3(0, 0, 80), glm::vec3(100, 15, 1));
	levelFactory.buildGround(this, 10000000000000, glm::vec3(0, -90, 0), glm::vec3(0, 0, 0), glm::vec3(400, 40, 1));
	levelFactory.buildPlayer(this, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1));


	newSystem<PlayerBehavior>(ANIMATION_FRAME_TIME);
	newSystem<GravitySystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();
}
