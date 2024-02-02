#include "application.h"

Application::Application() {
	levels.push_back(new Level1(ANIMATION_FRAME_TIME));
	currentLevel = levels[0];
}
Application::~Application() {
	for (Level* level : levels) {
		delete level;
	}
}
void Application::render(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	currentLevel->render();
}
void Application::update(float deltaTime){
	currentLevel->update(deltaTime);
}
