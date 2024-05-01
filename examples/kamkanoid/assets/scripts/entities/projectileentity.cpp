#include "projectileentity.h"
#include "engine/mesh.h"

ProjectileEntity::ProjectileEntity()
{
	const float WIDTH = 15;
	const float HEIGHT = 15;
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 1, 1, 1);
	addMesh(mesh);
	addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(WIDTH, HEIGHT, 1)));
	addPhysics(Physics(10, true, 1, true, 0, WIDTH, HEIGHT, false));
	addShaderInfo(ShaderInfo(1));
}
