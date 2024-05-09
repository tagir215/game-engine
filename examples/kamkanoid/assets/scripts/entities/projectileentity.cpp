#include "projectileentity.h"
#include "engine/core/scene.h"
#include "engine/core/gameobject.h"
#include "../assets/basicShapes/plane.h"

ProjectileEntity::ProjectileEntity(Scene* scene) : GameObject(scene)
{
}

void ProjectileEntity::beginPlay()
{
	const float WIDTH = 10;
	const float HEIGHT = 10;
	Plane* plane = new Plane();
	setMeshComponent(plane);
	getMeshComponent()->setColor(1, 1, 1, 1);
	createComponent<VelocityComponent>(0, 200, 0);
	createComponent<TransformComponent>(glm::vec3(-50, 0, 0), glm::vec3(0, 0, 0), glm::vec3(WIDTH, HEIGHT, 1));
	createComponent<PhysicsComponent>(0, true, 1, true, 0, glm::vec3(WIDTH, HEIGHT, 1), false);
	createComponent<ShaderComponent>(1);
	getTags().insert("projectile");

	getPhysicsComponent().onHitEvent.addListener(this, [&](GameObject* thisObject, GameObject* otherObject) {
		if (otherObject->getTags().find("paddle") != otherObject->getTags().end()) {
			float distanceX = otherObject->getTransformComponent()->position.x - thisObject->getTransformComponent()->position.x;
			thisObject->getVelocityComponent().linearVelocity.x = distanceX * -2.5f;
			}
		if (otherObject->getTags().find("brick") != otherObject->getTags().end()) {
			otherObject->getScene()->deleteChild(otherObject);
			updateScore = true;
		}
		});

}
