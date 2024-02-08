#pragma once
#include "application.h"
#include <stdio.h> 
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include <memory>
#include "./input/inputmanager.h"

int main(){
	glfwSetErrorCallback([](int error, const char* description) {
		fprintf(stderr, "Error %d: %s\n", error, description);
		});

	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	std::unique_ptr<Application>g_app = std::make_unique<Application>();

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

	float prevTime = (float)glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		g_app->render(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		float curTime = (float)glfwGetTime();
		float deltaTime = curTime - prevTime;
		prevTime = curTime;
		g_app->update(deltaTime);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
