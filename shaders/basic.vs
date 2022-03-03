#version 130  


attribute vec3 a_position;
attribute vec2 a_textCoord;
attribute vec4 a_color;


varying vec4 v_color;
varying vec2 v_textCoord;

uniform mat4 u_model;

void main(void){
   
    gl_Position = u_model * vec4(a_position,1.0f);
    v_color = a_color;

    v_textCoord = a_textCoord;

     
}