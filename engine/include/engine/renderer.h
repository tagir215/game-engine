#pragma once
#include <vector>
#include "gameobject.h"
#include "camera.h"
#include "shader.h"
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include "transformer.h"

class Renderer {
public:
	Renderer(std::unordered_map<int,Shader*>shaderMap);
	void render(std::vector<GameObject*>& gameObjects, Camera* camera);
private:
	Transformer transformer;
	std::unordered_map<int,Shader*>shaderMap;
	std::unordered_map<GameObject*, std::array<float, 18>>transformVertices(std::vector<GameObject*>& gameObjects, Camera* camera);
};