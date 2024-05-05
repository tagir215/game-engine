#pragma once

#include "texture.h"
#include "transform.h"
#include "mesh.h"
#include "physics.h"
#include "velocity.h"
#include "shaderinfo.h"
#include "inputcomponent.h"
#include <set>

class Scene;

class GameObject {
public:
    GameObject(Scene* parent);
	~GameObject();

    void addTexture(Texture* texture) {
        this->texture = texture;
    }
    void addTransform(Transform transform) {
        this->transform = transform;
    }
    void addMesh(StaticMesh* mesh) {
        this->mesh = mesh;
    }
    void addPhysicsComponent(PhysicsComponent physics) {
        this->physics = physics;
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

    /* 
    * called at the start of the game 
    */
    virtual void beginPlay();

    Scene* getParent() {
        return parentScene;
    }
    Texture* getTexture() {
        return texture;
    }
    Transform& getTransform() {
        return transform;
    }
    StaticMesh* getMesh() {
        return mesh;
    }
    PhysicsComponent& getPhysicsComponent() {
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

    std::set<std::string>& getTags() {
        return tags;
    }


private:
    int id;
    static int nextId;
    Texture* texture = nullptr;
    StaticMesh* mesh = nullptr;
    InputComponent* inputComponent = nullptr;
    Transform transform;
    PhysicsComponent physics;
    Velocity velocity;
    ShaderInfo shaderInfo;
    Scene* parentScene;
    std::set<std::string>tags;

};
