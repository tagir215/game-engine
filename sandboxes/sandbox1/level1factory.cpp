#include "level1factory.h"
#include "../assets/basicShapes/plane.h"

GameObject* Level1Factory::buildGround(Scene* scene, TransformComponent* transform, float mass) {
	GameObject* ground = scene->newObject<GameObject>();
	Plane* mesh = new Plane();
	mesh->setColor(0.5f,0,0,1);
	ground->addMeshComponent(mesh);
	ground->addTransformComponent(transform);
	ground->addShaderComponent(ShaderComponent(1));
	ground->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,false,0, glm::vec3(500,50,1), true));
	return ground;
}

GameObject* Level1Factory::buildBox(Scene* scene, TransformComponent* transform, float mass) {
	GameObject* box = scene->newObject<GameObject>(); 
	Plane* mesh = new Plane();
	mesh->setColor(1, 0, 0, 1);
	box->addMeshComponent(mesh);
	box->addShaderComponent(ShaderComponent(1));
	box->addVelocityComponent(VelocityComponent(0, 0, 0));
	box->addTransformComponent(transform);
	box->addPhysicsComponent(PhysicsComponent(mass, true,0.4f,true,0.5f, glm::vec3(50, 50,0), true));
	return box;
}

