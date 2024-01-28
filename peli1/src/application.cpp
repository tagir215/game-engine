#include "application.h"
#include "./texture_components/playerkeyframes.h"
#include "./systems/playerbehavior.h"

Application::Application() {

	ShaderSource shaderSource;
	shader = std::make_unique<Shader>(shaderSource.vertexShaderSource,shaderSource.fragmentShaderSource);

	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	GameObject* player = new GameObject();
	Texture* tex = textureStorage.WALK_BASIC;
	Mesh* mesh = new Mesh();
	tex->setKeyframes(new PlayerKeyframes());
	player->addTexture(tex);
	player->addMesh(mesh);
	player->addMass(Mass(1.0f));
	player->addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	gameObjects.push_back(player);
	systems.push_back(new PlayerBehavior(gameObjects,ANIMATION_FRAME_TIME));
	systems.push_back(new GravitySystem(gameObjects));
}
Application::~Application() {
	for (GameObject* gameObject : gameObjects) {
		delete gameObject;
	}
	for (SystemBase* system : systems) {
		delete system;
	}
}
void Application::render(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.render(gameObjects, shader.get(), camera.get());
}
void Application::update(float deltaTime){

	for (SystemBase* system : systems) {
		system->onUpdate(deltaTime);
	}
}
