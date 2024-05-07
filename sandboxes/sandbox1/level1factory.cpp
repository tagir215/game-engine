#include "level1factory.h"
#include "../assets/basicShapes/plane.h"

GameObject* Level1Factory::buildGround(Object<GameObject>* scene, TransformComponent& transform, float mass) {
	GameObject* ground = new GameObject(scene);
	Plane* mesh = new Plane();
	mesh->setColor(0.5f,0,0,1);
	ground->addMeshComponent(mesh);
	ground->addTransformComponent(transform);
	ground->addShaderComponent(ShaderComponent(1));
	ground->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,false,0, 500,50, true));
	return ground;
}

GameObject* Level1Factory::buildBox(Object<GameObject>* scene, TransformComponent& transform, float mass) {
	GameObject* box = new GameObject(scene);
	Plane* mesh = new Plane();
	mesh->setColor(1, 0, 0, 1);
	box->addMeshComponent(mesh);
	box->addShaderComponent(ShaderComponent(1));
	box->addVelocityComponent(VelocityComponent(0, 0, 0));
	box->addTransformComponent(transform);
	box->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,true,0.5f, 50, 50,true));
	return box;
}

