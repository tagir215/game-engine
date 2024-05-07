#include "playerfactory.h"
#include "playerkeyframes.h"
#include <engine/graphics/texturemanager.h>
#include "../assets/basicShapes/plane.h"

PlayerFactory::PlayerFactory() {
	
}

GameObject* PlayerFactory::buildGameObject(Object* scene,TransformComponent& transform) {
	TextureManager textureManager;
	TextureComponent* texture = textureManager.loadTexture("walk-basic.png");
	GameObject* player = new GameObject(scene);
	Plane* mesh = new Plane();
	texture->setKeyframes(new PlayerKeyframes());
	player->addTextureComponent(texture);
	player->addMeshComponent(mesh);
	player->addPhysicsComponent(PhysicsComponent(50,true,0.5f,true,0, 50,50,false));
	player->addInputComponent(new InputComponent());
	player->addVelocityComponent(VelocityComponent(0, 0, 0));
	player->addShaderComponent(ShaderComponent(0));
	player->addTransformComponent(transform);
	return player;
}
