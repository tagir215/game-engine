#include "engine/core/scene.h"

void Scene::render(std::vector<Renderer*>& rendererList) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Renderer* renderer : rendererList) {
		renderer->render(children, camera);
	}
}

void Scene::update(float deltaTime) {
	for (SystemBase* system : systems) {
		if (deltaTime > MAX_DELTA_TIME) {
			system->onUpdate(MAX_DELTA_TIME);
		}
		else {
			system->onUpdate(deltaTime);
		}
	}
}

void Scene::clearScene()
{
	for (GameObject* gameObject : children) {
		delete gameObject;
	}
	for (SystemBase* system : systems) {
		delete system;
	}
	children.clear();
	systems.clear();
	camera = nullptr;
}

Scene::Scene(){
}

Scene::~Scene() {
	clearScene();
}

void Scene::start() {
	newSystem<ComponentSorter>();
	onStart();

	for (GameObject* o : children) {
		o->beginPlay();
	}
}