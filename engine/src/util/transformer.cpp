#include "engine/util/transformer.h"

void Transformer::translate(TransformComponent* transform, float dx, float dy, float dz) {
    transform->position = glm::vec3(transform->position.x + dx, transform->position.y + dy, transform->position.z + dz);
}

void Transformer::rotate(TransformComponent* transform, float dx, float dy, float dz) {
    const float radiansToDegrees = 180.0f / glm::pi<float>();
    dx *= radiansToDegrees;
    dy *= radiansToDegrees;
    dz *= radiansToDegrees;
    transform->rotation = glm::vec3(transform->rotation.x + dx, transform->rotation.y + dy, transform->rotation.z + dz);
}

void Transformer::scale(TransformComponent* transform, float dx, float dy, float dz) {
    transform->scale = glm::vec3(transform->scale.x + dx, transform->scale.y + dy, transform->scale.z + dz);
}

void Transformer::setPosition(TransformComponent* transform, float x, float y, float z){
    transform->position = glm::vec3(x, y, z);
}

void Transformer::setRotation(TransformComponent* transform, float x, float y, float z){
    transform->rotation = glm::vec3(x, y, z);
}

void Transformer::setScale(TransformComponent* transform, float x, float y, float z){
    transform->scale = glm::vec3(x, y, z);
}

glm::mat4 Transformer::getModelMatrix(TransformComponent* transform) {
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), transform->position);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, transform->scale);
	return modelMatrix;
}
