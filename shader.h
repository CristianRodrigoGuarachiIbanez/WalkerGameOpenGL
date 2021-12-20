#pragma once
#include <GL/glew.h>
#include "dataTypes.h"
#include <string>
class SHADER{
public:
    SHADER(const char* vertexShaderFilename, const char*fragmentShaderFilename);
    virtual ~SHADER();


    void bind();
    void unbind();

    GLuint getShaderID(){
        return shaderID;
    }
    
private:
    GLuint compile(std::string shaderSource, GLenum type);
    std::string parse(const char* filename);
    GLuint createShader(const char*vertexShaderFilename, const char*framentShaderFilename);
    GLuint shaderID;

};