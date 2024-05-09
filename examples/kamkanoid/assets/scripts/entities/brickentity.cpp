#include "brickentity.h"
#include "../../scenes/level_1.h"
#include "../assets/basicShapes/plane.h"

BrickEntity::BrickEntity(Scene* scene, TransformComponent* transform, glm::vec3 color) : GameObject(scene)
{
	this->transform = transform;
	this->color = color;
}

void BrickEntity::beginPlay()
{
	addTransformComponent(transform);
	Plane* mesh = new Plane();
	mesh->setColor(color.x/255.0f, color.y/255.0f, color.z/255.0f, 1);
	addMeshComponent(mesh);
	addPhysicsComponent(PhysicsComponent(10000000000, true, 1, false, 0, glm::vec3(transform->scale.x, transform->scale.y,1), false));
	addShaderComponent(ShaderComponent(1));
	getTags().insert("brick");
}
