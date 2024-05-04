#include "characterentity.h"
#include "engine/mesh.h"

CharacterEntity::CharacterEntity(Scene* scene) : GameObject(scene)
{
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 1, 0, 1);
	addMesh(mesh);

	Transform transform(glm::vec3(0,-200,0),glm::vec3(0,0,0),glm::vec3(100,20,1));
	addTransform(transform);
	addPhysicsComponent(PhysicsComponent(1000, true, 1, false, 0, 100, 20, false));
	addShaderInfo(ShaderInfo(1));
	addInputComponent(new InputComponent());
	addVelocity(Velocity(0,0,0));
	getTags().insert("paddle");
}

void CharacterEntity::beginPlay()
{

}
