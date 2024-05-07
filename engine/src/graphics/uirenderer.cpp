#pragma once
#include "engine/graphics/uirenderer.h"

UiRenderer::UiRenderer(const std::unordered_map<int, Shader*> shaderMap) : Renderer(shaderMap)
{
}

void UiRenderer::render(const std::vector<GameObject*>& gameObjects, Camera* camera)
{
	glm::mat4 vpMatrix = camera->getProjectionMatrix() * glm::inverse(transformer.getModelMatrix(camera->getTransformComponent()));
	for (GameObject* object : gameObjects) {
		if (object->getTextComponent() == nullptr) {
			continue;
		}
		Shader* shader = shaderMap[0];
		shader->bind();
		shader->setUniform("MVP", vpMatrix * transformer.getModelMatrix(object->getTransformComponent()));
		shader->setUniform("texture0", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->getTextComponent()->getTextureComponent()->getTextureId());
		glBindVertexArray(object->getTextComponent()->getStaticTextMesh()->getVao());
		glDrawArrays(GL_TRIANGLES, 0, object->getTextComponent()->getStaticTextMesh()->getVertices().size());
	}
}
