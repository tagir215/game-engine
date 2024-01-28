#pragma once
#include <vector>
#include "../game/gameobject.h"
#include "../game/camera.h"
#include "../shader/shader.h"
#include <glm/glm.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
	Renderer();
	void render(std::vector<GameObject*>& gameObjects, Shader* shader, Camera* camera);
private:
	glm::mat4 calculateModelMatrix(const Transform& transform);
};