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

/*
* Contains all gameobjects and systems within the scene
*/
class Scene : public Object<GameObject> {
public:
	Scene();
	~Scene();
	void render(std::vector<Renderer*>& rendererList);
	void update(float deltaTime);


	/*
	* called when scene is supposed to be set active
	*/
	void start();

	/*
	* called when start is called...
	*/
	virtual void onStart() = 0;

	/*
	* called when a new scene is set. Deletes all gameobjects and systems associated with the scene
	*/
	void clearScene();

	/*
	* All game objects should probably be created here!
	* Creates the object adding itself as a parameter, and also inserts the object to 
	* gameobjects list (or children list, it's kinda weird maybe)
	*/
	template<typename T, typename... Args>
	T* newObject(Args... args) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must be a subclass of GameObject");
		T* newObject = new T(this, args...);
		children.push_back(newObject);
		return newObject;
	}

	/*
	* All systems should probably be created here!
	* Creates the system, adds the gameobjects as a parameter, and inserts the system to systems list
	*/
	template<typename T, typename... Args>
	void newSystem(Args... args) {
		static_assert(std::is_base_of<SystemBase, T>::value, "T must be a subclass of SystemBase");
		T* newSystem = new T(children, args...);
		systems.push_back(newSystem);
	}

	/*
	* Gets the system by it's type
	*/
	template<typename T>
	T* getSystemByType() {
		for (SystemBase* system : systems) {
			if (typeid(*system) == typeid(T)) {
				return dynamic_cast<T*>(system);
			}
		}
		return nullptr;
	}

protected:
	Camera* camera = nullptr;
	std::vector<SystemBase*>systems;
	float ANIMATION_FRAME_TIME = 0.1f;
private:
	const float MAX_DELTA_TIME = 0.05f;
};

