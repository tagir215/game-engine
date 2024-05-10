#include "wallentity.h"
#include "../assets/basicShapes/plane.h"
#include <engine/core/scenemanager.h>

WallEntity::WallEntity(Scene* scene) : GameObject(scene)
{
}

void WallEntity::beginPlay()
{
	Plane* plane = new Plane();
	setMeshComponent(plane);
	getMeshComponent()->setColor(0.4f, 0.4f, 0.4f, 1);
	createComponent<PhysicsComponent>(1000000000, true, 1, false, 0, glm::vec3(getTransformComponent()->scale.x, getTransformComponent()->scale.y, 1), false);
	createComponent<ShaderComponent>(1);

}
