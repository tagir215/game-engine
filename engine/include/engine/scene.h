#pragma once
#include "renderer.h"
#include "systembase.h"
#include "camera.h"
#include <vector>
#include <memory>
#include "../assets/shaders/ShaderSource.h"
#include <unordered_map>

class Scene {
public:
	Scene(float ANIMATION_FRAME_TIME);
	~Scene();
	void render();
	void update(float deltaTime);

protected:
	std::vector<GameObject*>gameObjects;
	std::unique_ptr<Camera> camera;
	std::vector<SystemBase*>systems;
	std::unordered_map<int, Shader*>shaderMap;
	Renderer* renderer;
	const float ANIMATION_FRAME_TIME;
};

