#pragma once
#include "texture.h"
#include "transform.h"
#include "mesh.h"
#include "physics.h"
#include "velocity.h"
#include "shaderinfo.h"
#include "inputcomponent.h"

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
    void addPhysics(Physics mass) {
        this->physics = mass;
    }
    void addVelocity(Velocity velocity) {
        this->velocity = velocity;
    }
    void addShaderInfo(ShaderInfo shaderInfo) {
        this->shaderInfo = shaderInfo;
    }
    void addInputComponent(InputComponent* inputComponent) {
        this->inputComponent = inputComponent;
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
    Physics& getPhysics() {
        return physics;
    }
    Velocity& getVelocity() {
        return velocity;
    }
    ShaderInfo& getShaderInfo() {
        return shaderInfo;
    }
    InputComponent* getInputComponent() {
        return inputComponent;
    }

    int getId() {
        return id;
    }

private:
    int id;
    static int nextId;
    Texture* texture = nullptr;
    Transform transform;
    Mesh* mesh = nullptr;
    InputComponent* inputComponent = nullptr;
    Physics physics;
    Velocity velocity;
    ShaderInfo shaderInfo;
};
