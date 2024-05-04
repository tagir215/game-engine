#pragma once
#include "renderer.h"
#include "systembase.h"
#include <vector>
#include <memory>
#include "../assets/shaders/ShaderSource.h"
#include <unordered_map>
#include "collisionsystem.h"

class Scene {
public:
	Scene(float ANIMATION_FRAME_TIME);
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

protected:
	std::vector<GameObject*>gameObjects;
	std::unique_ptr<Camera> camera;
	std::vector<SystemBase*>systems;
	std::unordered_map<int, Shader*>shaderMap;
	Renderer* renderer;
	const float ANIMATION_FRAME_TIME;
};

