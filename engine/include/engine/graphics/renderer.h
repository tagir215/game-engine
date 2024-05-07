#pragma once
#include <vector>
#include "engine/core/gameobject.h"
#include "engine/graphics/camera.h"
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "engine/graphics/shader.h"

class Renderer {
public:
	Renderer(const std::unordered_map<int, Shader*>shaderMap) : shaderMap(shaderMap){}
	virtual void render(const std::vector<GameObject*>& gameObjects, Camera* camera) = 0;
protected:
	std::unordered_map<int,Shader*>shaderMap;
};
