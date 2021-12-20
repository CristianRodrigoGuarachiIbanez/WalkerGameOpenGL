#version 130  
//in vec3 a_position;
//in vec4 a_color;
attribute vec3 a_position;
attribute vec4 a_color;

//out vec4 v_color;
varying vec4 v_color;

void main(void){
    //convert vec3 to vec4;
    gl_Position = vec4(a_position,1.0f);
    v_color = a_color;
    //v_color = gl_Color;

     
}