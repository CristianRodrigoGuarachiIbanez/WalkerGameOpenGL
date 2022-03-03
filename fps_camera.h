
#include "camera.h"

class fps_camera: public Camera {
protected:
    float yaw; //rotation um die y ache (links oder rechts geschaut )
    float pitch; //rotation um die x achse (oben und unten geschaut) 
    glm::vec3 lookAt;
    glm::vec3 up;
    const float mouseSensitivity = 0.3f;
public:
    fps_camera(float fov, float width, float height );
    void onMausMove(float xRel, float yRel);
    virtual void update();
    void moveFront(float amount );
    void moveSideways(float amount );

};
