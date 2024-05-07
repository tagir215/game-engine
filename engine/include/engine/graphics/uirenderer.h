#pragma once
#include "engine/graphics/renderer.h"
#include "engine/util/transformer.h"

class UiRenderer : Renderer {
public:
	UiRenderer(std::unordered_map<int, Shader*>shaderMap);
	void render(std::vector<GameObject*>& gameObjects, Camera* camera) override;
protected:
	
private:
	Transformer transformer;
};
