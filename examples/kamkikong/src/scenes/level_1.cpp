#include "level_1.h"
#include "../assets/basicShapes/plane.h"
#include <engine/components/tilemap.h>
#include "../entities/player.h"
#include "../systems/inputsystem.h"
#include <engine/systems/movementsystem.h>
#include <engine/systems/gravitysystem.h>
#include "../systems/kongsystem.h"


void Level_1::onStart() {
	camera = newObject<Camera>(0, 640, 0, 480);
	camera->createComponent<TransformComponent>(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	std::string path1 = "../../../../examples/kamkikong/assets/tt1.jpg";
	std::string path2 = "../../../../examples/kamkikong/assets/kamkikong.tmx";
	std::string path3 = "../../../../examples/kamkikong/assets/donko2.tsx";

	TileMap* tilemap = newObject<TileMap>(path1,path2,path3);
	tilemap->createComponent<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0.9f, 0.9f, 1));

	//tilemap->createComponent<PhysicsComponent>(1000000000000000, false, 1, false, 1, glm::vec3(1000, 1000, 1), false);

	Player* player = newObject<Player>();
	player->createComponent<TransformComponent>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(25, 25, 1));

	createWall(glm::vec3(0, -180, 0), glm::vec3(0, 0, 0), glm::vec3(400, 10, 1));
	createWall(glm::vec3(-200, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 400, 1));
	createWall(glm::vec3(200 - 10, 0, 0), glm::vec3(0, 0, 0), glm::vec3(10, 400, 1));
	createWall(glm::vec3(0, 150, 0), glm::vec3(0, 0, 0), glm::vec3(300, 10, 1));

	createWall(glm::vec3(-50, -120, 0), glm::vec3(0, 0, -5), glm::vec3(400, 10, 1));
	createWall(glm::vec3(50, -50, 0), glm::vec3(0, 0, 5), glm::vec3(400, 10, 1));
	createWall(glm::vec3(-50, 20, 0), glm::vec3(0, 0, -5), glm::vec3(400, 10, 1));
	createWall(glm::vec3(50, 100, 0), glm::vec3(0, 0, 5), glm::vec3(400, 10, 1));

	newSystem<InputSystem>(ANIMATION_FRAME_TIME);
	newSystem<KongSystem>(this);
	newSystem<GravitySystem>();
	newSystem<CollisionSystem>();
	newSystem<MovementSystem>();
}

void Level_1::createWall(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
{
	GameObject* wall = newObject<GameObject>();
	wall->createComponent<PhysicsComponent>(1000000000000000, true, 1, false, 1, glm::vec3(1000, 1000, 1), false);
	Plane* plane = new Plane();
	wall->setMeshComponent(plane);
	wall->createComponent<TransformComponent>(pos, rot, scl);
	//wall->createComponent<ShaderComponent>(1);
}
