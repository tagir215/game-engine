#pragma once
#include <vector>
#include "../game/gameobject.h"
#include "../game/camera.h"
#include "../shader/shader.h"
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

class Renderer {
public:
	Renderer(std::unordered_map<int,Shader*>shaderMap);
	void render(std::vector<GameObject*>& gameObjects, Camera* camera);
private:
	glm::mat4 calculateModelMatrix(const Transform& transform);
	std::unordered_map<int,Shader*>shaderMap;
};