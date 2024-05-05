#include "level1factory.h"
#include "../assets/basicShapes/plane.h"

GameObject* Level1Factory::buildGround(Scene* scene, Transform& transform, float mass) {
	GameObject* ground = new GameObject(scene);
	Plane* mesh = new Plane();
	mesh->setColor(0.5f,0,0,1);
	ground->addMesh(mesh);
	ground->addTransform(transform);
	ground->addShaderInfo(ShaderInfo(1));
	ground->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,false,0, 500,50, true));
	return ground;
}

GameObject* Level1Factory::buildBox(Scene* scene, Transform& transform, float mass) {
	GameObject* box = new GameObject(scene);
	Plane* mesh = new Plane();
	mesh->setColor(1, 0, 0, 1);
	box->addMesh(mesh);
	box->addShaderInfo(ShaderInfo(1));
	box->addVelocity(Velocity(0, 0, 0));
	box->addTransform(transform);
	box->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,true,0.5f, 50, 50,true));
	return box;
}

