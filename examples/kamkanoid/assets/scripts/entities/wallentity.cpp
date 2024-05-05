#include "wallentity.h"
#include "../assets/basicShapes/plane.h"

WallEntity::WallEntity(Scene* scene, Transform transform) : GameObject(scene)
{
	addTransform(transform);

	Plane* mesh = new Plane();
	mesh->setColor(0.4f, 0.4f, 0.4f, 1);
	addMesh(mesh);
	addPhysicsComponent(PhysicsComponent(1000000000, true, 1, false, 0, transform.scale.x, transform.scale.y, false));
	addShaderInfo(ShaderInfo(1));
}
