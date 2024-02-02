#include "transformer.h"

void Transformer::translate(Transform& transform, float dx, float dy, float dz) {
    transform.position = glm::vec3(transform.position.x + dx, transform.position.y + dy, transform.position.z + dz);
}

void Transformer::rotate(Transform& transform, float dx, float dy, float dz) {
    transform.rotation = glm::vec3(transform.rotation.x + dx, transform.rotation.y + dy, transform.rotation.z + dz);
}

void Transformer::scale(Transform& transform, float dx, float dy, float dz) {
    transform.scale = glm::vec3(transform.scale.x + dx, transform.scale.y + dy, transform.scale.z + dz);
}

void Transformer::setPosition(Transform& transform, float x, float y, float z){
    transform.position = glm::vec3(x, y, z);
}

void Transformer::setRotation(Transform& transform, float x, float y, float z){
    transform.rotation = glm::vec3(x, y, z);
}

void Transformer::setScale(Transform& transform, float x, float y, float z){
    transform.scale = glm::vec3(x, y, z);
}

