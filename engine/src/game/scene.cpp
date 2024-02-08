#include "../include/engine/level.h"

void Level::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->render(gameObjects, camera.get());
}

void Level::update(float deltaTime) {
	for (SystemBase* system : systems) {
		system->onUpdate(deltaTime);
	}
}

Level::Level(float ANIMATION_FRAME_TIME) : ANIMATION_FRAME_TIME(ANIMATION_FRAME_TIME) {
	ShaderSource shaderSource;
	shaderMap[0] = new Shader(shaderSource.vertexShaderSource,shaderSource.fragmentShaderSource);
	shaderMap[1] = new Shader(shaderSource.vertexShaderSourceNoTexture, shaderSource.fragmentShaderSourceNoTexture);;
	renderer = new Renderer(shaderMap);
}

Level::~Level() {
	for (GameObject* gameObject : gameObjects) {
		delete gameObject;
	}
	for (SystemBase* system : systems) {
		delete system;
	}
	delete renderer;
}