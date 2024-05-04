#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include "scene.h"
#include <string>

namespace engine {

	class Application {
	public:
		Application(int sizeX, int sizeY, const std::string& title);
		~Application();

		void stop();
		int run();
		void render(GLFWwindow* window);
		void update(float deltaTime);
		Scene* getCurrentScene() {
			return currentScene;
		}
		void setCurrentScene(Scene* scene) {
			currentScene = scene;
		}

	private:
		const float ANIMATION_FRAME_TIME = 0.1f;
		int sizeX;
		int sizeY;
		std::string title;
		bool m_running;
		Scene* currentScene;
		GLFWwindow* window;
	protected:
		std::vector<Scene*>scenes;
	};

}
