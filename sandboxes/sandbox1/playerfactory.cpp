#include "playerfactory.h"
#include "playerkeyframes.h"
#include <engine/texturemanager.h>
#include "../assets/basicShapes/plane.h"

PlayerFactory::PlayerFactory() {
	
}

GameObject* PlayerFactory::buildGameObject(Scene* scene,Transform& transform) {
	TextureManager textureManager;
	Texture* texture = textureManager.loadTexture("walk-basic.png");
	GameObject* player = new GameObject(scene);
	Plane* mesh = new Plane();
	texture->setKeyframes(new PlayerKeyframes());
	player->addTexture(texture);
	player->addMesh(mesh);
	player->addPhysicsComponent(PhysicsComponent(50,true,0.5f,true,0, 50,50,false));
	player->addInputComponent(new InputComponent());
	player->addVelocity(Velocity(0, 0, 0));
	player->addShaderInfo(ShaderInfo(0));
	player->addTransform(transform);
	return player;
}
