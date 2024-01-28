#pragma once
#include "../texture_components/texture.h"
#include "../components/transform.h"
#include "../components/mesh.h"
#include "../components/mass.h"


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
    void addMass(Mass mass) {
        this->mass = mass;
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
    Mass& getMass() {
        return mass;
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
    Mass mass;
};
