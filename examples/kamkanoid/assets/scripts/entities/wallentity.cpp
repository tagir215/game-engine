#include "wallentity.h"
#include "../assets/basicShapes/plane.h"

WallEntity::WallEntity(Scene* scene, TransformComponent* transform) : GameObject(scene)
{
	this->transform = transform;
}

void WallEntity::beginPlay()
{
	addTransformComponent(transform);
	Plane* mesh = new Plane();
	mesh->setColor(0.4f, 0.4f, 0.4f, 1);
	addMeshComponent(mesh);
	addPhysicsComponent(PhysicsComponent(1000000000, true, 1, false, 0, glm::vec3(transform->scale.x, transform->scale.y,1), false));
	addShaderComponent(ShaderComponent(1));
}
