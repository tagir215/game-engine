#pragma once
#include "../texture/texture.h"
#include "transform.h"
#include "mesh.h"


class GameObject {
public:
    GameObject();
	~GameObject();

    void addTexture(Texture* texture) {
        this->texture = texture;
    }
    void addTransform(Transform transform) {
        this->transform = transform;
    }
    void addMesh(Mesh* mesh) {
        this->mesh = mesh;
    }

    Texture* getTexture() {
        return texture;
    }
    Transform& getTransform() {
        return transform;
    }
    Mesh* getMesh() {
        return mesh;
    }

    int getId() {
        return id;
    }

private:
    int id;
    static int nextId;
    Texture* texture;
    Transform transform;
    Mesh* mesh;
};
