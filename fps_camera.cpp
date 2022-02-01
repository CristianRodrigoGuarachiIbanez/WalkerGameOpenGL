#include "fps_camera.h"

fps_camera::fps_camera(float fov, float width, float height) : Camera(fov, width,height)
{
    up=glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    onMausMove(0.0f, 0.0f);
    update();
}

void fps_camera::onMausMove(float xRel, float yRel){
    yaw +=xRel * mouseSensitivity;
    pitch-=yRel * mouseSensitivity;
    if(pitch > 89.0f){
        pitch =89.0f;
    }
    if(pitch<-89.0f){
        pitch = -89.0f;
    }
    glm::vec3 front;
    front.x=cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y=sin(glm::radians(pitch));
    front.z=cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    lookAt = glm::normalize(front);
    update();

}

void fps_camera::update() {
    view = glm::lookAt(position, position+lookAt, up);
    viewProj = projection * view;
} 


void fps_camera::moveFront(float amount){
    translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)*lookAt) * amount);
    update();
}

void fps_camera::moveSideways(float amount){
    // mit dem Kreuzprodukt, welcher ein dritter Vektor findet, der hortogonal zu dem beiden Vektoren verläuft
    translate(glm::normalize(glm::cross(lookAt,up))*amount); 
    //translate(lookAt*amount);
    update();
}