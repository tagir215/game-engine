#include "level1factory.h"

GameObject* Level1Factory::buildGround(Transform& transform, float mass) {
	GameObject* ground = new GameObject();
	Mesh* mesh = new Mesh();
	mesh->setColor(0.5f,0,0,1);
	ground->addMesh(mesh);
	ground->addTransform(transform);
	ground->addShaderInfo(ShaderInfo(1));
	ground->addPhysics(Physics(mass, true,1,false,0, 500,50, true));
	return ground;
}

GameObject* Level1Factory::buildBox(Transform& transform, float mass) {
	GameObject* box = new GameObject();
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 0, 0, 1);
	box->addMesh(mesh);
	box->addShaderInfo(ShaderInfo(1));
	box->addVelocity(Velocity(0, 0, 0));
	box->addTransform(transform);
	box->addPhysics(Physics(mass, true,1,true,0.5f, 50, 50,true));
	return box;
}

