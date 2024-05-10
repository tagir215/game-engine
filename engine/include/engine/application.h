#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include "engine/application.h"
#include "engine/core/scene.h"
#include <string>
#include "engine/input/inputmanager.h"
#include "engine/core/scenemanager.h"
#include "../assets/shaders/ShaderSource.h"

namespace engine {

	class Application {
	public:
		Application(int sizeX, int sizeY, const std::string& title);
		~Application();

		void stop();
		int run();
		void render(GLFWwindow* window);
		void update(float deltaTime);
		void initRenderers();

	private:
		const int sizeX;
		const int sizeY;
		const std::string title;
		bool m_running;
		GLFWwindow* window;
		SceneManager& sceneManager = SceneManager::getInstance();
		Scene* currentScene = nullptr;
		std::vector<Renderer*>rendererList;
		std::unordered_map<int, Shader*>shaderMap;
	};

}
