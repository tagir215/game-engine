#include "projectileentity.h"
#include "engine/core/scene.h"
#include "engine/core/gameobject.h"
#include "../assets/basicShapes/plane.h"

ProjectileEntity::ProjectileEntity(Scene* scene) : GameObject(scene)
{
	const float WIDTH = 15;
	const float HEIGHT = 15;
	Plane* mesh = new Plane();
	mesh->setColor(1, 1, 1, 1);
	addMeshComponent(mesh);
	addVelocityComponent(VelocityComponent(0, 200, 0));
	addTransformComponent(TransformComponent(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(WIDTH, HEIGHT, 1)));
	addPhysicsComponent(PhysicsComponent(0, true, 1, true, 0, WIDTH, HEIGHT, false));
	addShaderComponent(ShaderComponent(1));
	getTags().insert("projectile");
}

void ProjectileEntity::beginPlay()
{
	getPhysicsComponent().onHitEvent.addListener(this, [](GameObject* thisObject, GameObject* otherObject) {
		if (otherObject->getTags().find("paddle") != otherObject->getTags().end()) {
			float distanceX = otherObject->getTransform().position.x - thisObject->getTransform().position.x;
			thisObject->getVelocityComponent().linearVelocity.x = distanceX * -2.5f;
			}
		if (otherObject->getTags().find("brick") != otherObject->getTags().end()) {
			otherObject->getParent()->deleteGameObject(otherObject);
		}
		});

}
