#include "playerfactory.h"
#include "../../texture_components/texturestorage.h"
#include "../../texture_components/playerkeyframes.h"

GameObject* PlayerFactory::buildGameObject() {
	GameObject* player = new GameObject();
	Texture* tex = TextureStorage::getInstance().WALK_BASIC;
	Mesh* mesh = new Mesh();
	tex->setKeyframes(new PlayerKeyframes());
	player->addTexture(tex);
	player->addMesh(mesh);
	player->addPhysics(Physics(1.0f,true,50,50));
	player->addVelocity(Velocity(0, 0, 0));
	player->addShaderInfo(ShaderInfo(0));
	player->addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	return player;
}
