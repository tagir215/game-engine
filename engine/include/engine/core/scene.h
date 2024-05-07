#pragma once
#include "engine/graphics/meshrenderer.h"
#include "engine/systems/systembase.h"
#include <vector>
#include <memory>
#include "../assets/shaders/ShaderSource.h"
#include <unordered_map>
#include "engine/systems/collisionsystem.h"
#include "engine/graphics/uirenderer.h"
#include "engine/core/object.h"

class Scene : public Object<GameObject> {
public:
	Scene();
	~Scene();
	void render();
	void update(float deltaTime);

	template<typename T>
	T* getSystemByType() {
		for (SystemBase* system : systems) {
			if (typeid(*system) == typeid(T)) {
				return dynamic_cast<T*>(system);
			}
		}
		return nullptr;
	}

	void start() {
		for (GameObject* o : children) {
			o->beginPlay();
		}
	}

protected:
	std::unique_ptr<Camera> camera;
	std::vector<SystemBase*>systems;
	std::unordered_map<int, Shader*>shaderMap;
	MeshRenderer* meshRenderer = nullptr;
	UiRenderer* uiRenderer = nullptr;
	float ANIMATION_FRAME_TIME = 0.1f;
};

