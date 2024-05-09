#pragma once
#include <string>
#include <unordered_map>
class Scene;

class SceneManager {
public:
	static SceneManager& getInstance() {
		static SceneManager instance; 
		return instance;
	}

	~SceneManager() {
		for (auto& pair : sceneMap) {
			delete pair.second;
		}
	}
	void nextScene();

	template<typename SceneType>
	void createScene(std::string name) {
		SceneType* scene = new SceneType();
		sceneMap[name] = scene;
		if (currentScene == nullptr) {
			currentScene = scene;
		}
	}

	void setScene(std::string name) {
		if (sceneMap.find(name) != sceneMap.end()) {
			currentScene = sceneMap[name];
		}
	}
	Scene* getCurrentScene() {
		return currentScene;
	}
private:
	std::unordered_map<std::string, Scene*>sceneMap;
	Scene* currentScene = nullptr;
	SceneManager() {}
};

