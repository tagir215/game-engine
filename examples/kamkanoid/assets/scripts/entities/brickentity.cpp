#include "brickentity.h"
#include "engine/scene.h"
#include "engine/collisionsystem.h"
#include "../../scenes/level_1.h"

BrickEntity::BrickEntity(Scene* scene, Transform transform, glm::vec3 color) : GameObject(scene)
{
	addTransform(transform);
	Mesh* mesh = new Mesh();
	mesh->setColor(color.x/255.0f, color.y/255.0f, color.z/255.0f, 1);
	addMesh(mesh);
	addPhysicsComponent(PhysicsComponent(10000000000, true, 1, false, 0, transform.scale.x, transform.scale.y, false));
	addShaderInfo(ShaderInfo(1));
	getTags().insert("brick");
}

void BrickEntity::beginPlay()
{
}
