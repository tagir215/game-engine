#include "engine/graphics/meshrenderer.h"
#include <iostream>

MeshRenderer::MeshRenderer(std::unordered_map<int,Shader*>shaderMap) : Renderer(shaderMap) {
}

/*
* renders each mesh object within scene, called recursively if object contains inner objects
*/
void MeshRenderer::render(const std::vector<GameObject*>& gameObjects, Camera* camera) {
	if (camera == nullptr || camera->getTransformComponent() == nullptr) return;
	glm::mat4 vpMatrix = camera->getProjectionMatrix() * glm::inverse(transformer.getModelMatrix(camera->getTransformComponent()));
	for (GameObject* object : gameObjects) {

		if (object->getMeshComponent() == nullptr || object->getShaderComponent().shaderId == -1) {
			continue;
		}
	
		if (object->getShaderComponent().shaderId == 0) {
			Shader* shader = shaderMap[0];
			shader->bind();
			shader->setUniform("MVP", vpMatrix * transformer.getModelMatrix(object->getTransformComponent()));
			shader->setUniform("texture0", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, object->getTextureComponent()->getTextureId());
		}
		else if (object->getShaderComponent().shaderId == 1) {
			Shader* shader = shaderMap[1];
			shader->bind();
			shader->setUniform("MVP", vpMatrix * transformer.getModelMatrix(object->getTransformComponent()));
			float* color = object->getMeshComponent()->getColor();
			shader->setUniform("color", color[0],color[1],color[2],color[3]);
		}

		glBindVertexArray(object->getMeshComponent()->getVao());
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}

