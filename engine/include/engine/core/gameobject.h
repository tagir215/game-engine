#pragma once

#include "engine/graphics/texture.h"
#include "engine/components/mesh.h"
#include "engine/components/inputcomponent.h"
#include "engine/components/physics.h"
#include "engine/components/velocity.h"
#include "engine/components/transform.h"
#include "engine/input/inputmanager.h"
#include "engine/graphics/shaderinfo.h"
#include "engine/components/textcomponent.h"
#include "engine/core/object.h"
#include <set>

/*
* base class for all game objects
*/
class GameObject : public Object<GameObject>{
public:
    GameObject(Object* parent);
    GameObject();
	~GameObject();

    void addTextureComponent(TextureComponent* texture) {
        this->texture = texture;
    }
    void addTransformComponent(TransformComponent* transform) {
        this->transform = transform;
    }
    void addMeshComponent(StaticMesh* mesh) {
        this->mesh = mesh;
    }
    void addPhysicsComponent(PhysicsComponent physics) {
        this->physics = physics;
    }
    void addVelocityComponent(VelocityComponent velocity) {
        this->velocity = velocity;
    }
    void addShaderComponent(ShaderComponent shaderInfo) {
        this->shaderComponent = shaderInfo;
    }
    void addInputComponent(InputComponent* inputComponent) {
        this->inputComponent = inputComponent;
    }
    void addTextComponent(TextComponent* textComponent) {
        this->textComponent = textComponent;
    }

    /* 
    * called at the start of the game 
    */
    virtual void beginPlay();

    TextureComponent* getTextureComponent() {
        return texture;
    }
    TransformComponent* getTransformComponent() {
        return transform;
    }
    StaticMesh* getMeshComponent() {
        return mesh;
    }
    PhysicsComponent& getPhysicsComponent() {
        return physics;
    }
    VelocityComponent& getVelocityComponent() {
        return velocity;
    }
    ShaderComponent& getShaderComponent() {
        return shaderComponent;
    }
    InputComponent* getInputComponent() {
        return inputComponent;
    }
    TextComponent* getTextComponent() {
        return textComponent;
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
    TextureComponent* texture = nullptr;
    StaticMesh* mesh = nullptr;
    InputComponent* inputComponent = nullptr;
    TextComponent* textComponent = nullptr;
    TransformComponent* transform = nullptr;
    PhysicsComponent physics;
    VelocityComponent velocity;
    ShaderComponent shaderComponent;
    std::set<std::string>tags;

};
