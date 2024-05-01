#include "wallentity.h"
#include "engine/mesh.h"

WallEntity::WallEntity(Transform transform)
{
	addTransform(transform);

	Mesh* mesh = new Mesh();
	mesh->setColor(0, 1, 0, 1);
	addMesh(mesh);
	addPhysics(Physics(1000000000, true, 1, false, 0, transform.scale.x, transform.scale.y, false));
	addShaderInfo(ShaderInfo(1));
}
