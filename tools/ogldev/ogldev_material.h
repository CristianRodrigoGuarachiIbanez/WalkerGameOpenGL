#ifndef OGLDEV_MATERIAL_H
#define OGLDEV_MATERIAL_H

#include "ogldev_texture.h"

class Material {

 public:
    Vector3f AmbientColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f DiffuseColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f SpecularColor = Vector3f(0.0f, 0.0f, 0.0f);

    // TODO: need to deallocate these
    Texture* pDiffuse = NULL; // base color of the material
    Texture* pSpecularExponent = NULL;
};


#endif