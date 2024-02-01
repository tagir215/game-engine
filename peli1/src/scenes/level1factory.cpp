#include "level1factory.h"

GameObject* Level1Factory::buildGround() {
	GameObject* ground = new GameObject();
	Mesh* mesh = new Mesh();
	mesh->setColor(0.5f,0,0,1);
	ground->addMesh(mesh);
	ground->addTransform(Transform(glm::vec3(0, -100, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 50, 1)));
	ground->addShaderInfo(ShaderInfo(1));
	ground->addPhysics(Physics(10000, true,1000,50));
	return ground;
}