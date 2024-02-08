#include "playerfactory.h"
#include "playerkeyframes.h"
#include <engine/texturemanager.h>

PlayerFactory::PlayerFactory() {
	
}

GameObject* PlayerFactory::buildGameObject() {
	TextureManager textureManager;
	Texture* texture = textureManager.loadTexture("walk-basic.png");
	GameObject* player = new GameObject();
	Mesh* mesh = new Mesh();
	texture->setKeyframes(new PlayerKeyframes());
	player->addTexture(texture);
	player->addMesh(mesh);
	player->addPhysics(Physics(50,true,0,true,0, 50,50));
	player->addVelocity(Velocity(0, 0, 0));
	player->addShaderInfo(ShaderInfo(0));
	player->addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	return player;
}
