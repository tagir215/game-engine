#include "projectileentity.h"
#include "engine/mesh.h"
#include "engine/scene.h"

ProjectileEntity::ProjectileEntity(Scene* scene) : GameObject(scene)
{
	const float WIDTH = 15;
	const float HEIGHT = 15;
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 1, 1, 1);
	addMesh(mesh);
	addVelocity(Velocity(0, 200, 0));
	addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(WIDTH, HEIGHT, 1)));
	addPhysicsComponent(PhysicsComponent(0, true, 1, true, 0, WIDTH, HEIGHT, false));
	addShaderInfo(ShaderInfo(1));
	getTags().insert("projectile");
}

void ProjectileEntity::beginPlay()
{
	getPhysicsComponent().onHitEvent.addListener(this, [](GameObject* thisObject, GameObject* otherObject) {
		if (otherObject->getTags().find("paddle") != otherObject->getTags().end()) {
			float distanceX = otherObject->getTransform().position.x - thisObject->getTransform().position.x;
			thisObject->getVelocity().linearVelocity.x = distanceX * -2.5f;
			}
		if (otherObject->getTags().find("brick") != otherObject->getTags().end()) {
			otherObject->getParent()->deleteGameObject(otherObject);
		}
		});

}
