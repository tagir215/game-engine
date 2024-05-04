#include "brickentity.h"
#include "engine/scene.h"
#include "engine/collisionsystem.h"
#include "../../scenes/level_1.h"

BrickEntity::BrickEntity(Scene* scene, Transform transform) : GameObject(scene)
{
	addTransform(transform);
	Mesh* mesh = new Mesh();
	mesh->setColor(0, 0, 1, 1);
	addMesh(mesh);
	addPhysicsComponent(PhysicsComponent(10000000000, true, 1, false, 0, transform.scale.x, transform.scale.y, false));
	addShaderInfo(ShaderInfo(1));
}

void BrickEntity::beginPlay()
{
	this->getPhysicsComponent().onHitEvent.addListener(this, [](GameObject* thisObject, GameObject* otherObject) {
		std::cout << "interesting " << std::endl;
		});
}
