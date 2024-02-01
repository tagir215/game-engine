#pragma once
#include "../systems/renderer.h"
#include "../systems/systembase.h"
#include "../game/camera.h"
#include <vector>
#include <memory>
#include "../../assets/shaders/ShaderSource.h"
#include <unordered_map>

class Level {
public:
	Level(float ANIMATION_FRAME_TIME);
	~Level();
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

