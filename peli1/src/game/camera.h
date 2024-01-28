#pragma once
#include "gameobject.h"             
#include <glm/gtx/transform.hpp>   

class Camera : public GameObject {
public:
    Camera(float left, float right, float bottom, float top) : GameObject() {
        m_projection = glm::ortho(left, right, bottom, top);
    }

    ~Camera() {

    }

    const glm::mat4& getProjectionMatrix() const {
        return m_projection;
    }

private:
    glm::mat4 m_projection;
};



