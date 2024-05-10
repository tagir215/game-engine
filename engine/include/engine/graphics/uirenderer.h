#pragma once
#include "engine/graphics/renderer.h"
#include "engine/util/transformer.h"

class UiRenderer : public Renderer {
public:
	UiRenderer(const std::unordered_map<int, Shader*>shaderMap);
	void render(const std::vector<GameObject*>& gameObjects, Camera* camera) override;
protected:
	
private:
	Transformer transformer;
};
