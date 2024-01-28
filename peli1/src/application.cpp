#include "application.h"
#include "./texture/playerkeyframes.h"
#include "./behaviors/playerbehavior.h"

Application::Application() {

	ShaderSource shaderSource;
	shader = std::make_unique<Shader>(shaderSource.vertexShaderSource,shaderSource.fragmentShaderSource);

	camera = std::make_unique<Camera>(0, 640, 0, 480);
	camera->addTransform(Transform(glm::vec3(-320.0f, -240.0f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

	GameObject* plane = new GameObject();
	Texture* tex = textureStorage.WALK_BASIC;
	Mesh* mesh = new Mesh();
	tex->setKeyframes(new PlayerKeyframes());
	plane->addTexture(tex);
	plane->addMesh(mesh);
	plane->addTransform(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(50, 50, 1)));
	gameObjects.push_back(plane);
	systems.push_back(new PlayerBehavior(gameObjects,ANIMATION_FRAME_TIME));
}
Application::~Application() {
	for (GameObject* o : gameObjects) {
		delete o;
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
