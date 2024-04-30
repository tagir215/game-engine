#include "characterentity.h"
#include "engine/mesh.h"

CharacterEntity::CharacterEntity()
{
	Mesh* mesh = new Mesh();
	mesh->setColor(1, 1, 0, 1);
	addMesh(mesh);

	Transform transform(glm::vec3(0,-150,0),glm::vec3(0,0,0),glm::vec3(100,20,1));
	addTransform(transform);

	addShaderInfo(ShaderInfo(1));
	addInputComponent(new InputComponent());

	addVelocity(Velocity(0,0,0));

}
