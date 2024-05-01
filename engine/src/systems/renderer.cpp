#include "../include/engine/renderer.h"
#include <iostream>

Renderer::Renderer(std::unordered_map<int,Shader*>shaderMap) : shaderMap(shaderMap) {
}

void Renderer::render(std::vector<GameObject*>& gameObjects, Camera* camera) {
	glm::mat4 vpMatrix = camera->getProjectionMatrix() * glm::inverse(transformer.getModelMatrix(camera->getTransform()));
	glm::mat4 identityMatrix = glm::mat4(1.0f);
	for (GameObject* object : gameObjects) {
		if (object->getMesh() == nullptr || object->getShaderInfo().shaderId == -1) {
			continue;
		}
	
		if (object->getShaderInfo().shaderId == 0) {
			Shader* shader = shaderMap[0];
			shader->bind();
			shader->setUniform("MVP", vpMatrix * transformer.getModelMatrix(object->getTransform()));
			shader->setUniform("texture0", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, object->getTexture()->getTextureId());
		}
		else if (object->getShaderInfo().shaderId == 1) {
			Shader* shader = shaderMap[1];
			shader->bind();
			shader->setUniform("MVP", vpMatrix * transformer.getModelMatrix(object->getTransform()));
			float* color = object->getMesh()->getColor();
			shader->setUniform("color", color[0],color[1],color[2],color[3]);
		}


		glBindVertexArray(object->getMesh()->getVao());
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
}

