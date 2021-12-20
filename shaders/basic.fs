#version 130 
varying vec4 f_color;
varying vec4 v_color;
//out vec4 f_color;
//in vec4 v_color;
uniform vec4 u_color;

void main(void){

    gl_FragColor  = u_color ;
}