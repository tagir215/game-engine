#include "characterentity.h"
#include "../assets/basicShapes/plane.h"

CharacterEntity::CharacterEntity(Scene* scene) : GameObject(scene)
{
}

void CharacterEntity::beginPlay()
{
	Plane* plane = new Plane();
	setMeshComponent(plane);
	getMeshComponent()->setColor(1, 1, 0, 1);
	createComponent<TransformComponent>(glm::vec3(-50, -200, 0), glm::vec3(0, 0, 0), glm::vec3(70, 16, 1));
	createComponent<PhysicsComponent>(1000, true, 1, false, 0, glm::vec3(70, 16, 1), false);
	createComponent<ShaderComponent>(1);
	createComponent<InputComponent>();
	createComponent<VelocityComponent>(0, 0, 0);
	getTags().insert("paddle");
}
