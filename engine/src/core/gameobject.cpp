#include "engine/core/gameobject.h"


int GameObject::nextId = 0;

GameObject::GameObject(Object* parent)  
{
	id = nextId;
	++nextId;
    this->parent = parent;
}

GameObject::GameObject()  
{
	id = nextId;
	++nextId;
}

GameObject::~GameObject() {
    delete texture;
    delete mesh;
    delete inputComponent;
    delete textComponent;
}

void GameObject::beginPlay()
{
}

