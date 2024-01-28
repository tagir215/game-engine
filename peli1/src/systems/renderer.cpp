#include "renderer.h"

Renderer::Renderer() {
}

void Renderer::render(std::vector<GameObject*>& gameObjects, Shader* shader, Camera* camera) {
	glm::mat4 vpMatrix = camera->getProjectionMatrix() * glm::inverse(calculateModelMatrix(camera->getTransform()));
	for (GameObject* object : gameObjects) {

		shader->bind();

		shader->setUniform("MVP", vpMatrix * calculateModelMatrix(object->getTransform()));
		shader->setUniform("texture0", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->getTexture()->getTextureId());


		glBindVertexArray(object->getMesh()->getVao());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

glm::mat4 Renderer::calculateModelMatrix(const Transform& transform) {
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), transform.position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, transform.scale);
	return modelMatrix;
}
