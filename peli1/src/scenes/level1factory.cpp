#include "level1factory.h"

GameObject* Level1Factory::buildGround() {
	GameObject* ground = new GameObject();
	Mesh* mesh = new Mesh();
	mesh->setColor(1,1,0,1);
	ground->addMesh(mesh);
	ground->addTransform(Transform(glm::vec3(0, -200, 0), glm::vec3(0, 0, 0), glm::vec3(1000, 100, 1)));
	ground->addShaderInfo(ShaderInfo(1));
	return ground;
}