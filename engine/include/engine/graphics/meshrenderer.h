#pragma once
#include <vector>
#include "shader.h"
#include <unordered_map>
#include "engine/util/transformer.h"
#include "engine/graphics/renderer.h"

class MeshRenderer : public Renderer{
public:
	MeshRenderer(const std::unordered_map<int,Shader*>shaderMap);
	void render(const std::vector<GameObject*>& gameObjects, Camera* camera) override;
private:
	Transformer transformer;
};