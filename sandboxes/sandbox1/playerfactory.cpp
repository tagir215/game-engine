#include "playerfactory.h"
#include "playerkeyframes.h"
#include <engine/graphics/texturemanager.h>
#include "../assets/basicShapes/plane.h"

PlayerFactory::PlayerFactory() {
	
}

GameObject* PlayerFactory::buildGameObject(Scene* scene) {
	TextureManager textureManager;
	TextureComponent* texture = textureManager.loadTexture("walk-basic.png");
	GameObject* player = scene->newObject<GameObject>();
	Plane* mesh = new Plane();
	texture->setKeyframes(new PlayerKeyframes());
	player->addTextureComponent(texture);
	player->addMeshComponent(mesh);
	player->addPhysicsComponent(PhysicsComponent(50,true,0.5f,true,0, glm::vec3(50,50,1), false));
	player->addInputComponent(new InputComponent());
	player->addVelocityComponent(VelocityComponent(0, 0, 0));
	player->addShaderComponent(ShaderComponent(0));
	return player;
}
