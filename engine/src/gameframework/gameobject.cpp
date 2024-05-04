#include "../include/engine/gameobject.h"


int GameObject::nextId = 0;

GameObject::GameObject(Scene* parent) : parentScene(parent)
{
	id = nextId;
	++nextId;
}

GameObject::~GameObject() {
    delete texture;
    delete mesh;
    delete inputComponent;
}

void GameObject::beginPlay()
{
}

