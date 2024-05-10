#pragma once
#include "engine/graphics/meshrenderer.h"
#include "engine/systems/systembase.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include "engine/systems/collisionsystem.h"
#include "engine/graphics/uirenderer.h"
#include "engine/core/gameobject.h"
#include "engine/components/componentsorter.h"
#include "engine/core/scenemanager.h"

class Scene : public Object<GameObject> {
public:
	Scene();
	~Scene();
	void render(std::vector<Renderer*>& rendererList);
	void update(float deltaTime);

	template<typename T>
	T* getSystemByType() {
		for (SystemBase* system : systems) {
			if (typeid(*system) == typeid(T)) {
				return dynamic_cast<T*>(system);
			}
		}
		return nullptr;
	}

	void start();

	virtual void onStart() = 0;

	void clearScene();

	template<typename T, typename... Args>
	T* newObject(Args... args) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must be a subclass of GameObject");
		T* newObject = new T(this, args...);
		children.push_back(newObject);
		return newObject;
	}

	template<typename T, typename... Args>
	void newSystem(Args... args) {
		static_assert(std::is_base_of<SystemBase, T>::value, "T must be a subclass of SystemBase");
		T* newSystem = new T(children, args...);
		systems.push_back(newSystem);
	}

protected:
	Camera* camera = nullptr;
	std::vector<SystemBase*>systems;
	float ANIMATION_FRAME_TIME = 0.1f;
private:
	const float MAX_DELTA_TIME = 0.05f;
};

