#include "../include/engine/gameobject.h"

GameObject::GameObject() {
	id = nextId;
	nextId++;
}

int GameObject::nextId = 0;

GameObject::~GameObject() {
}
