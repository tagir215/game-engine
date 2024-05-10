#include "brickentity.h"
#include "../../scenes/level_1.h"
#include "../assets/basicShapes/plane.h"

BrickEntity::BrickEntity(Scene* scene,  glm::vec3 color) : GameObject(scene)
{
	this->color = color;
}

void BrickEntity::beginPlay()
{
	Plane* plane = new Plane();
	setMeshComponent(plane);
	getMeshComponent()->setColor(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, 1);
	createComponent<PhysicsComponent>(10000000000, true, 1, false, 0, glm::vec3(getTransformComponent()->scale.x, getTransformComponent()->scale.y, 1), false);
	createComponent<ShaderComponent>(1);
	getTags().insert("brick");
}
