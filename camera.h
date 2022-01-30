#pragma once
#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

class Camera{

private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 viewProj;


public:
    Camera(float fov, float width, float height );
    glm::mat4 getViewProj();
    void update();
    void translate(glm::vec3 v);
};