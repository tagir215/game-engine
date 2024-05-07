#include "engine/core/gameobject.h"


int GameObject::nextId = 0;

GameObject::GameObject(Scene* scene) : scene(scene)
{
	id = nextId;
	++nextId;
}


GameObject::~GameObject() {
    delete texture;
    delete mesh;
    delete inputComponent;
    delete textComponent;
    delete transform;
}

void GameObject::beginPlay()
{
}

