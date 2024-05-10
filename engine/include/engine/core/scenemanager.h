#pragma once
#include <string>
#include <unordered_map>
class Scene;

class SceneManager {
public:
	SceneManager() {}

	~SceneManager() {
		for (auto& pair : sceneMap) {
			delete pair.second;
		}
	}

	void nextScene();
	void setScene(std::string name);

	template<typename SceneType>
	void attachScene(std::string name) {
		SceneType* scene = new SceneType();
		sceneMap[name] = scene;
		if (currentScene == nullptr) {
			currentScene = scene;
		}
		sceneOrder.push_back(scene);
	}


	Scene* getCurrentScene() {
		return currentScene;
	}
private:
	std::unordered_map<std::string, Scene*>sceneMap;
	std::vector<Scene*>sceneOrder;
	Scene* currentScene = nullptr;
};

