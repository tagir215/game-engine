#include "engine/core/scenemanager.h"

void SceneManager::nextScene() {
	for (int i = 0; i < sceneOrder.size(); ++i) {
		if (currentScene != sceneOrder[i]) {
			continue;
		}
		if (i < sceneOrder.size() - 1) {
			currentScene = sceneOrder[i + 1];
			return;
		}
		else {
			currentScene = sceneOrder[0];
			return;
		}
	}
}

void SceneManager::setScene(std::string name) {
	if (sceneMap.find(name) != sceneMap.end()) {
		currentScene = sceneMap[name];
	}
}
