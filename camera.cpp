#include "camera.h"


Camera::Camera(float fov, float width, float height){
    projection =glm::perspective(fov/2.0f, width/height, 0.1f, 1000.0f);
    view = glm::mat4(1.0f);
    update();
}
glm::mat4 Camera::getViewProj(){
    return viewProj;
    }

void Camera::update(){
    // einmal in Frame aufgerufen
    viewProj = projection*view;
    }

void Camera::translate(glm::vec3 v){
    // ergibt die Invertierte View Matrix
    // v gibt an, in welche Richtung die Kamera bewegt
    // view gibt an, in welche Richtung sich die Objekte bewegen müssen, damit die Kamera in 0 Punkt ist 
    view = glm::translate(view, v*-1.0f);
}
