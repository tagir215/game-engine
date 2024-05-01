#include "projectileentity.h"
#include "engine/mesh.h"

ProjectileEntity::ProjectileEntity()
{
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 1, 1, 1);
	addMesh(mesh);
	addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(30, 30, 1)));
	addPhysics(Physics(10, true, 1, true, 0, 100, 100, false));
	addShaderInfo(ShaderInfo(1));
}
