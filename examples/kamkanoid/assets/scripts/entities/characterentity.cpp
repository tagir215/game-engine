#include "characterentity.h"
#include "../assets/basicShapes/plane.h"

CharacterEntity::CharacterEntity(Scene* scene) : GameObject(scene)
{
}

void CharacterEntity::beginPlay()
{
	Plane* mesh = new Plane();
	mesh->setColor(1, 1, 0, 1);
	addMeshComponent(mesh);
	addTransformComponent(new TransformComponent(glm::vec3(0,-200,0),glm::vec3(0,0,0),glm::vec3(100,20,1)));
	addPhysicsComponent(PhysicsComponent(1000, true, 1, false, 0, 100, 20, false));
	addShaderComponent(ShaderComponent(1));
	addInputComponent(new InputComponent());
	addVelocityComponent(VelocityComponent(0,0,0));
	getTags().insert("paddle");
}
