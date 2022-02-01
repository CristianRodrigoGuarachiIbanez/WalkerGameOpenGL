#include "fps_camera.h"

class FloatingCamera : public fps_camera {
public:
    FloatingCamera(float fov, float width, float height): fps_camera(fov, width, height) {}
    void moveUp(float amount){
        translate(up * amount);
    }

};