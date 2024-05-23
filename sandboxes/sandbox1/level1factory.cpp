#include "level1factory.h"
#include "../assets/basicShapes/plane.h"
#include "playerkeyframes.h"

GameObject* Level1Factory::buildGround(Scene* scene, float mass, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
	GameObject* ground = scene->newObject<GameObject>();
	Plane* mesh = new Plane();
	mesh->setColor(0.5f,0,0,1);
	ground->setMeshComponent(mesh);
	ground->createComponent<ShaderComponent>(1);
	ground->createComponent<TransformComponent>(pos,rot,scl);
	ground->createComponent<PhysicsComponent>(mass, true, 0.4f, false, 0, glm::vec3(ground->getTransformComponent()->scale.x*2, ground->getTransformComponent()->scale.x*2, 1), false);
	return ground;
}

GameObject* Level1Factory::buildBox(Scene* scene, float mass, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
	GameObject* box = scene->newObject<GameObject>(); 
	Plane* mesh = new Plane();
	mesh->setColor(1, 0, 0, 1);
	box->setMeshComponent(mesh);
	box->createComponent<ShaderComponent>(1);
	box->createComponent<VelocityComponent>(0, 0, 0);
	box->createComponent<TransformComponent>(pos,rot,scl);
	box->createComponent<PhysicsComponent>(mass, true,0.4f,true,0.5f, glm::vec3(box->getTransformComponent()->scale.x*2, box->getTransformComponent()->scale.x*2, 0), true);
	return box;
}

GameObject* Level1Factory::buildPlayer(Scene* scene, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
	TextureManager textureManager;
	TextureComponent* texture = textureManager.loadTexture("walk-basic.png");
	GameObject* player = scene->newObject<GameObject>();
	Plane* mesh = new Plane();
	texture->setKeyframes(new PlayerKeyframes());
	player->setTextureComponent(texture);
	player->setMeshComponent(mesh);
	player->createComponent<TransformComponent>(pos, rot, scl);
	player->createComponent<PhysicsComponent>(150, true, 0.3f, true, 0, scl, false);
	player->createComponent<InputComponent>();
	player->createComponent<VelocityComponent>(0, 0, 0);
	player->createComponent<ShaderComponent>(0);
	return player;
}
