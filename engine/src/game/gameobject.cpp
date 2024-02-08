#include "../include/engine/gameobject.h"

GameObject::GameObject() {
	mesh = nullptr;
	texture = nullptr;
	id = nextId;
	nextId++;
}

int GameObject::nextId = 0;

GameObject::~GameObject() {
}
