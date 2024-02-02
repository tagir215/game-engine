#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h> 
#include <vector>
#include <iostream>
#include "./scenes/level.h"
#include "./scenes/level1.h"

class Application {
public:
	Application();
	~Application();

	void render(GLFWwindow* window);
	void update(float deltaTime);

private:
	const float ANIMATION_FRAME_TIME = 0.1f;
	std::vector<Level*>levels;
	Level* currentLevel;
};
