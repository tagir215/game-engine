#pragma once
#include <stdio.h> 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include "./game/gameobject.h"
#include "./game/camera.h"
#include "./shader/shader.h"
#include "../assets/shaders/ShaderSource.h"
#include "./texture_components/texturestorage.h"
#include "./systems/renderer.h"
#include "./game/camera.h"
#include "./input/inputmanager.h"
#include "./systems/systembase.h"
#include "./systems/gravitysystem.h"

class Application {
public:
	Application();
	~Application();

	void render(GLFWwindow* window);
	void update(float deltaTime);

private:
	std::vector<GameObject*>gameObjects;
	std::unique_ptr<Shader>shader;
	std::unique_ptr<Camera> camera;
	std::vector<SystemBase*>systems;
	Renderer renderer;
	TextureStorage textureStorage;
	const float ANIMATION_FRAME_TIME = 0.1f;
};
