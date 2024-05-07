#include "engine/core/scene.h"

void Scene::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	meshRenderer->render(gameObjects, camera.get());
	uiRenderer->render(gameObjects, camera.get());
}

void Scene::update(float deltaTime) {
	for (SystemBase* system : systems) {
		system->onUpdate(deltaTime);
	}
}

Scene::Scene() {
	ShaderSource shaderSource;
	shaderMap[0] = new Shader(shaderSource.vertexShaderSource,shaderSource.fragmentShaderSource);
	shaderMap[1] = new Shader(shaderSource.vertexShaderSourceNoTexture, shaderSource.fragmentShaderSourceNoTexture);
	meshRenderer = new MeshRenderer(shaderMap);
	uiRenderer = new UiRenderer(shaderMap);
}

Scene::~Scene() {
	for (GameObject* gameObject : gameObjects) {
		delete gameObject;
	}
	for (SystemBase* system : systems) {
		delete system;
	}
	delete meshRenderer;
	delete uiRenderer;
}