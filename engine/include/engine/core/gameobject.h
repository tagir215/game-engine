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
class Scene;

/*
* base class for all game objects
*/
class GameObject : public Object<GameObject> {
public:
    GameObject(Scene* scene);
	~GameObject();

	/*
	* game object will create the components. I'm not sure about raw poiniters 
	* in c++ so this way it's easier to change later
	*/
	template<typename ComponentType, typename... Args>
	void createComponent(Args... args) {
		if constexpr (std::is_same<ComponentType, TextureComponent>::value) {
			delete texture;
			texture = new TextureComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, TransformComponent>::value) {
			delete transform;
			transform = new TransformComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, StaticMesh>::value) {
			delete mesh;
			mesh = new StaticMesh(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, PhysicsComponent>::value) {
			physics = PhysicsComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, VelocityComponent>::value) {
			velocity = VelocityComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, ShaderComponent>::value) {
			shaderComponent = ShaderComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, InputComponent>::value) {
			delete inputComponent;
			inputComponent = new InputComponent(std::forward<Args>(args)...);
		}
		else if constexpr (std::is_same<ComponentType, TextComponent>::value) {
			delete textComponent;
			textComponent = new TextComponent(std::forward<Args>(args)...);
		}
		else {
			std::cerr << "Unknowe component type!" << std::endl;
		}
	}


	/*
	* called at the start of the game
	*/
	virtual void beginPlay();

	TextureComponent* getTextureComponent() const {
		return texture;
	}
	TransformComponent* getTransformComponent() const {
		return transform;
	}
	StaticMesh* getMeshComponent() const {
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
	InputComponent* getInputComponent() const {
		return inputComponent;
	}
	TextComponent* getTextComponent() const {
		return textComponent;
	}
	Scene* getScene() const {
		return scene;
	}
	

	void setTextureComponent(TextureComponent* newTexture) {
		texture = newTexture;
	}
	void setTransformComponent(TransformComponent* newTransform) {
		transform = newTransform;
	}
	void setMeshComponent(StaticMesh* newMesh) {
		mesh = newMesh;
	}
	void setPhysicsComponent(const PhysicsComponent& newPhysics) {
		physics = newPhysics;
	}
	void setVelocityComponent(const VelocityComponent& newVelocity) {
		velocity = newVelocity;
	}
	void setShaderComponent(const ShaderComponent& newShader) {
		shaderComponent = newShader;
	}
	void setInputComponent(InputComponent* newInputComponent) {
		inputComponent = newInputComponent;
	}
	void setTextComponent(TextComponent* newTextComponent) {
		textComponent = newTextComponent;
	}
	void setScene(Scene* newScene) {
		scene = newScene;
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
	Scene* scene = nullptr;
};
