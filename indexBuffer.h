#pragma once
#include <GL/glew.h>
#include "dataTypes.h"


struct IndexBuffer {
    IndexBuffer(void * data, uint32 numIndices, uint8 elementSize){

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);
    }
    virtual ~IndexBuffer(){
        glDeleteBuffers(1, &bufferID);

    }
    void Bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);

    }
    void Unbind(){
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        
    }
private:
GLuint bufferID;

};