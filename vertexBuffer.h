#pragma once
#include <GL/glew.h>
#include "dataTypes.h"


struct VertexBuffer {
    VertexBuffer(void * data, uint32 numVertices){
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,4,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)3);


    }
    virtual ~VertexBuffer(){
        glDeleteBuffers(1, &bufferID);

    }
    void Bind(){
        /* glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); */
        glBindVertexArray(vao);

    }
    void Unbind(){
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
    }
private:
GLuint bufferID;
GLuint vao;

};