#include "../include/engine/application.h"

namespace engine {

	Application::Application(int sizeX, int sizeY, const std::string& title) 
		: sizeX(sizeX), sizeY(sizeY), title(title), scenes(scenes) {

		glfwSetErrorCallback([](int error, const char* description) {
			fprintf(stderr, "Error %d: %s\n", error, description);
			});

		if (!glfwInit()) {
			std::cerr << "failed to init glfw" << std::endl;
			return;
		}

		window = glfwCreateWindow(sizeX, sizeY, "window", NULL, NULL);
		if (!window) {
			glfwTerminate();
			std::cerr << "failed to init glfw window" << std::endl;
			return;
		}

		glfwMakeContextCurrent(window);
		gladLoadGL(glfwGetProcAddress);

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				InputManager::getInstance().updatePress(key);
			}
			if (action == GLFW_RELEASE) {
				InputManager::getInstance().updateRelease(key);
			}
			});

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	Application::~Application() {
		for (Scene* scene : scenes) {
			delete scene;
		}
	}
	int Application::run() {
		currentScene->start();
		m_running = true;

		currentScene = scenes[0];


		float prevTime = (float)glfwGetTime();
		while (!glfwWindowShouldClose(window)) {
			render(window);
			glfwSwapBuffers(window);
			glfwPollEvents();
			float curTime = (float)glfwGetTime();
			float deltaTime = curTime - prevTime;
			prevTime = curTime;
			update(deltaTime);
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;
	}

	void Application::stop() {
		m_running = false;
	}

	void Application::render(GLFWwindow* window) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		currentScene->render();


	}
	void Application::update(float deltaTime) {
		currentScene->update(deltaTime);
	}

}
