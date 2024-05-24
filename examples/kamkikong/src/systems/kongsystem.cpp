#include "kongsystem.h"
#include <../assets/basicShapes/plane.h>

void KongSystem::onUpdate(float deltaTime)
{
	cumilatedTime += deltaTime;
	if (cumilatedTime > 5) {
		cumilatedTime = 0;
		GameObject* problem = scene->newObject<GameObject>();
		problem->createComponent<TransformComponent>(glm::vec3(-100, 170, 0), glm::vec3(0), glm::vec3(15, 15, 0));

		Plane* plane = new Plane();
		plane->updateTextureBuffer(texCoords);
		problem->setTextureComponent(texture);

		problem->setMeshComponent(plane);
		problem->setShaderComponent(0);
		problem->createComponent<VelocityComponent>(100, 0, 0);
		problem->createComponent<PhysicsComponent>(100,true,0.5f,true,1,glm::vec3(problem->getTransformComponent()->scale),true);
	}
}
