#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include "engine/application.h"
#include "engine/core/scene.h"
#include <string>
#include "engine/core/gamemode.h"
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

	protected:
		SceneManager& sceneManager = GameMode::getInstance().getSceneManager();

	private:
		const int sizeX;
		const int sizeY;
		const std::string title;
		bool m_running;
		GLFWwindow* window;
		InputManager& inputManager = GameMode::getInstance().getInputManager();
		Scene* currentScene = nullptr;
		std::vector<Renderer*>rendererList;
		std::unordered_map<int, Shader*>shaderMap;
	};

}
