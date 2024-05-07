#pragma once
#include <functional>
#include <map>
#include <iostream>
class GameObject;

/* 
* Delegate, 
*/
template<typename functionType>
class Delegate {
public:
	void addListener(GameObject* gameObject, std::function<functionType> callback) {
		if (gameObject != nullptr) {
			invocationList[gameObject] = callback;
		}
	}
	template<typename... Args>
	void broadcast(Args&&... args) {
		for (auto& pair : invocationList) {
			if (pair.first != nullptr) {
				pair.second(std::forward<Args>(args)...);
			}
		}
	}

private:
	std::map<GameObject*, std::function<functionType>> invocationList;
};

