#pragma once
#include "../texture_components/texture.h"
#include "../components/transform.h"
#include "../components/mesh.h"
#include "../components/mass.h"
#include "../components/velocity.h"
#include "../components/shaderinfo.h"

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
    void addVelocity(Velocity velocity) {
        this->velocity = velocity;
    }
    void addShaderInfo(ShaderInfo shaderInfo) {
        this->shaderInfo = shaderInfo;
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
    Velocity& getVelocity() {
        return velocity;
    }
    ShaderInfo& getShaderInfo() {
        return shaderInfo;
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
    Velocity velocity;
    ShaderInfo shaderInfo;
};
