#include "brickentity.h"

BrickEntity::BrickEntity(Transform transform)
{
	addTransform(transform);
	Mesh* mesh = new Mesh();
	mesh->setColor(0, 0, 1, 1);
	addMesh(mesh);
	addPhysics(Physics(10000000000, true, 1, false, 0, transform.scale.x, transform.scale.y, false));
	addShaderInfo(ShaderInfo(1));
}
