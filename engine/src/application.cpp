#include "engine/application.h"

namespace engine {

	Application::Application(int sizeX, int sizeY, const std::string& title) 
		: sizeX(sizeX), sizeY(sizeY), title(title) {

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
				GameMode::getInstance().getInputManager().updatePress(key);
			}
			if (action == GLFW_RELEASE) {
				GameMode::getInstance().getInputManager().updateRelease(key);
			}
			});

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		initRenderers();
	}

	void Application::initRenderers() {
		ShaderSource shaderSource;
		shaderMap[0] = new Shader(shaderSource.vertexShaderSource, shaderSource.fragmentShaderSource);
		shaderMap[1] = new Shader(shaderSource.vertexShaderSourceNoTexture, shaderSource.fragmentShaderSourceNoTexture);
		rendererList.push_back(new MeshRenderer(shaderMap));
		rendererList.push_back(new UiRenderer(shaderMap));
	}

	Application::~Application() {
	}
	int Application::run() {
		sceneManager.getCurrentScene()->start();
		m_running = true;


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

		for (auto r : rendererList) {
			delete r;
		}
		for (auto& pair : shaderMap) {
			delete pair.second;
		}
		return 0;
	}

	void Application::stop() {
		m_running = false;
	}

	void Application::render(GLFWwindow* window) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		sceneManager.getCurrentScene()->render(rendererList);
	}
	void Application::update(float deltaTime) {
		if (sceneManager.getCurrentScene() != currentScene) {
			if (currentScene != nullptr) currentScene->clearScene();
			currentScene = sceneManager.getCurrentScene();
			currentScene->start();
		}
		currentScene->update(deltaTime);
	}

}
